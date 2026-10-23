#!/usr/bin/env python3
"""Re-verify every published release, and watch the generator that signs them.

Usage: release_verify.py list
       release_verify.py verify <report.json>
       release_verify.py plan <tag> <out>
       release_verify.py compare <tag> <build>

Run by release_verify.yml, with gh (GH, default "gh") and GITHUB_REPOSITORY;
DOCS_SITE (default https://mavlink-m.dronecode.org/) is the docs site. The
generator to watch is the one release.yml in the checkout names.

list     Every vX.Y.Z tag must have exactly one release, published and final,
         and every release must sit on such a tag: tags cannot be deleted or
         moved, so a tag without its release shows a deleted release.
         GITHUB_OUTPUT receives tags, the JSON list of released tags, and
         count.
verify   For each release: it is immutable; its title is "MAVLink-M X.Y.Z"
         and its notes equal its notes asset; its assets are exactly the files
         SHA256SUMS lists, SHA256SUMS, the provenance bundle and the publish
         record, each with the server-side digest SHA256SUMS or the publish
         record gives; every file verifies against the bundle with the
         generator identity that release.yml names at the tag, online, and
         SHA256SUMS also offline with a trusted root saved at the start; gh
         release verify and gh release verify-asset accept the release and
         every asset; and the docs site serves its version.json for that tag
         and commit. The latest release must be the highest one not withdrawn.
         Then the generator: its tag still names the reviewed commit, its
         repository is not archived, and it has no security advisory that
         .github/release-status.json does not list as reviewed; a newer
         generator release is a notice. With no release, only the generator
         is checked. The report lists every check with its outcome.
plan     Write the plan that <tag>'s release was built from, out of its
         evidence bundle, to <out>/plan.json, for a rebuild.
compare  The package that <build> holds, rebuilt from <tag> with that tag's
         own release_package.py and plan, matches the release's SHA256SUMS
         line for every package file, byte for byte.

Each prints what it found and exits 1 on any failure.
"""

from __future__ import annotations

import json
import os
import re
import sys
import tempfile
import urllib.request
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import archive  # noqa: E402
import gh_api  # noqa: E402
import release_generator  # noqa: E402
import release_publish  # noqa: E402

TAG = re.compile(r"v(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)")  # ASCII digits only
GENERATOR = re.compile(r"^  (GENERATOR_WORKFLOW|GENERATOR_TAG|GENERATOR_COMMIT): (\S+)$", re.M)
WORKFLOW = Path(".github/workflows/release.yml")
STATUS_FILE = Path(".github/release-status.json")
DOCS_SITE = "https://mavlink-m.dronecode.org/"


class VerifyError(Exception):
    """A failure the report must carry."""


def key(tag: str) -> tuple[int, ...]:
    return tuple(map(int, TAG.fullmatch(tag).groups()))


def paged(path: str) -> list[dict]:
    found, page = [], 1
    while True:
        entries = gh_api.api(f"{path}?per_page=100&page={page}") or []
        found += entries
        if len(entries) < 100:
            return found
        page += 1


def releases(repo: str) -> list[dict]:
    """The releases, checked against the tags; the highest version first."""
    listed = paged(f"repos/{repo}/releases")
    tags = {t["name"] for t in paged(f"repos/{repo}/tags") if TAG.fullmatch(t["name"])}
    problems = []
    for release in listed:
        if not TAG.fullmatch(release["tag_name"]):
            problems.append(f"release {release['tag_name']!r} is not on a vX.Y.Z tag")
        elif release["draft"] or release["prerelease"]:
            problems.append(f"release {release['tag_name']} is a draft or a pre-release")
    on_tags = [r["tag_name"] for r in listed if TAG.fullmatch(r["tag_name"])]
    problems += [
        f"tag {t} has {on_tags.count(t)} releases" for t in sorted(tags) if on_tags.count(t) != 1
    ]
    if problems:
        raise VerifyError("; ".join(problems))
    return sorted(
        (r for r in listed if TAG.fullmatch(r["tag_name"])),
        key=lambda r: key(r["tag_name"]),
        reverse=True,
    )


def status() -> dict:
    return json.loads(STATUS_FILE.read_text(encoding="utf-8")) if STATUS_FILE.is_file() else {}


def site_record(url: str) -> dict:
    with urllib.request.urlopen(url, timeout=60) as response:
        return json.loads(response.read())


def check_release(repo: str, release: dict, root: Path, work: Path) -> list[str]:
    tag, version = release["tag_name"], release["tag_name"][1:]
    folder = work / tag
    folder.mkdir(parents=True)
    gh_api.run("release", "download", tag, "--repo", repo, "--dir", str(folder))
    files = release_publish.sums(folder)
    bundle = f"mavlink-m-{version}.intoto.jsonl"
    record_name = f"mavlink-m-{version}-publish.json"
    found = []
    if release.get("immutable") is not True:
        found.append(f"{tag}: the release is not immutable")
    if release.get("name") != f"MAVLink-M {version}":
        found.append(f"{tag}: the title is {release.get('name')!r}")
    if release.get("body", "") != (folder / f"mavlink-m-{version}-notes.md").read_text(
        encoding="utf-8"
    ):
        found.append(f"{tag}: the release notes differ from the notes asset")
    record = json.loads((folder / record_name).read_text(encoding="utf-8"))
    expected = {name: f"sha256:{digest}" for name, digest in files}
    expected["SHA256SUMS"] = f"sha256:{release_publish.sha256(folder / 'SHA256SUMS')}"
    expected[bundle] = record["assets"].get(bundle)
    expected[record_name] = f"sha256:{release_publish.sha256(folder / record_name)}"
    server = {a["name"]: a.get("digest") for a in release.get("assets", [])}
    if server != expected:
        found.append(
            f"{tag}: the assets differ from SHA256SUMS and the publish record: {sorted(set(server.items()) ^ set(expected.items()))}"
        )
    text = gh_api.run(
        "api",
        "-H",
        "Accept: application/vnd.github.raw",
        f"repos/{repo}/contents/.github/workflows/release.yml?ref={tag}",
    )
    generator = dict(GENERATOR.findall(text))
    commit = gh_api.api(f"repos/{repo}/commits/{tag}")["sha"]
    env = {"GITHUB_REPOSITORY": repo, "GITHUB_REF": f"refs/tags/{tag}", "GITHUB_SHA": commit,
           "GENERATOR_WORKFLOW": generator.get("GENERATOR_WORKFLOW", ""), "GENERATOR_COMMIT": generator.get("GENERATOR_COMMIT", "")}  # fmt: skip
    for name in [n for n, _ in files] + ["SHA256SUMS"]:
        release_publish.verify(folder / name, folder / bundle, env)
    gh_api.run(
        "attestation", "verify", str(folder / "SHA256SUMS"), "--bundle", str(folder / bundle),
        "--repo", repo, "--signer-workflow", env["GENERATOR_WORKFLOW"], "--signer-digest", env["GENERATOR_COMMIT"],
        "--source-ref", env["GITHUB_REF"], "--source-digest", commit, "--predicate-type", release_publish.PREDICATE,
        "--deny-self-hosted-runners", "--custom-trusted-root", str(root),
    )  # fmt: skip
    gh_api.run("release", "verify", tag, "--repo", repo)
    for name in sorted(server):
        gh_api.run("release", "verify-asset", tag, str(folder / name), "--repo", repo)
    site = os.environ.get("DOCS_SITE", DOCS_SITE).rstrip("/") + "/"
    deployed = site_record(f"{site}{tag}/version.json")
    if (deployed.get("version"), deployed.get("commit")) != (tag, commit):
        found.append(
            f"{tag}: the docs site serves {deployed.get('version')} at {deployed.get('commit')}"
        )
    return found


def advisories(gen: dict, reviewed: list[str]) -> list[str]:
    repo = gen["repository"]
    found = [a["ghsa_id"] for a in gh_api.api(f"/advisories?affects={repo}&per_page=100") or []]
    found += [
        a["ghsa_id"] for a in gh_api.api(f"repos/{repo}/security-advisories?per_page=100") or []
    ]
    return sorted(set(found) - set(reviewed))


def verify(env: dict) -> dict:
    repo = env["GITHUB_REPOSITORY"]
    report = {
        "checked": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ"),
        "releases": [],
        "failures": [],
        "notices": [],
    }
    listed = releases(repo)
    withdrawn = status().get("withdrawn", {})
    with tempfile.TemporaryDirectory() as work:
        root = Path(work, "trusted_root.jsonl")
        if listed:  # saved once, for the offline check of every release
            root.write_text(gh_api.run("attestation", "trusted-root"), encoding="utf-8")
        for release in listed:
            try:
                failures = check_release(repo, release, root, Path(work))
            except (
                VerifyError,
                gh_api.GitHubError,
                release_publish.PublishError,
                OSError,
                ValueError,
                KeyError,
            ) as error:
                failures = [f"{release['tag_name']}: {error}"]
            report["releases"].append({"tag": release["tag_name"], "failures": failures})
            report["failures"] += failures
    candidates = [r["tag_name"] for r in listed if r["tag_name"] not in withdrawn]
    if candidates:
        latest = gh_api.api(f"repos/{repo}/releases/latest")["tag_name"]
        if latest != candidates[0]:
            report["failures"].append(f"the latest release is {latest}, not {candidates[0]}")
    named = dict(GENERATOR.findall(WORKFLOW.read_text(encoding="utf-8")))
    gen = release_generator.expected({**named, "GENERATOR_ACTIONS": ""})
    try:
        report["generator"] = release_generator.check_pin(gen)
        unreviewed = advisories(gen, status().get("reviewed_generator_advisories", []))
        if unreviewed:
            report["failures"].append(f"generator advisories to review: {unreviewed}")
        newest = gh_api.api(f"repos/{gen['repository']}/releases/latest")["tag_name"]
        if newest != gen["tag"]:
            report["notices"].append(
                f"the generator has a newer release, {newest}; release.yml pins {gen['tag']}"
            )
    except (release_generator.GeneratorError, gh_api.GitHubError) as error:
        report["failures"].append(f"generator: {error}")
    return report


def read_sums(path: Path) -> dict[str, str]:
    lines = path.read_text(encoding="ascii").splitlines()
    found = {m.group(2): m.group(1) for m in map(release_publish.SUMS_LINE.fullmatch, lines) if m}
    if len(found) != len(lines):
        raise VerifyError(f"{path} has a malformed line")
    return found


def compare(repo: str, tag: str, build: Path) -> int:
    with tempfile.TemporaryDirectory() as work:
        gh_api.run(
            "release", "download", tag, "--repo", repo, "--dir", work, "--pattern", "SHA256SUMS"
        )
        published = read_sums(Path(work, "SHA256SUMS"))
    rebuilt = read_sums(build / "SHA256SUMS")
    differ = sorted(name for name, digest in rebuilt.items() if published.get(name) != digest)
    if differ:
        raise VerifyError(f"{tag}: the rebuild differs from the release in {differ}")
    return len(rebuilt)


def release_plan(repo: str, tag: str, out: Path) -> Path:
    name = f"mavlink-m-{tag[1:]}-evidence.tar.gz"
    with tempfile.TemporaryDirectory() as work:
        gh_api.run("release", "download", tag, "--repo", repo, "--dir", work, "--pattern", name)
        bundle = archive.read(Path(work, name), name[: -len(".tar.gz")])
    out.mkdir(parents=True, exist_ok=True)
    (out / "plan.json").write_bytes(bundle["plan.json"])
    return out / "plan.json"


FAILURES = (
    VerifyError, gh_api.GitHubError, release_publish.PublishError, archive.ArchiveError,
    release_generator.GeneratorError, OSError, ValueError, KeyError,
)  # fmt: skip


def main(argv: list[str]) -> int:
    usage = {"list": 2, "verify": 3, "plan": 4, "compare": 4}
    if len(argv) < 2 or usage.get(argv[1]) != len(argv):
        print(__doc__, file=sys.stderr)
        return 2
    env = dict(os.environ)
    repo = env.get("GITHUB_REPOSITORY", "")
    try:
        if argv[1] == "list":
            tags = [r["tag_name"] for r in releases(repo)]
            print(f"{len(tags)} release(s): {', '.join(tags) or 'none'}")
            output = env.get("GITHUB_OUTPUT")
            if output:
                with open(output, "a", encoding="utf-8") as stream:
                    stream.write(f"tags={json.dumps(tags)}\ncount={len(tags)}\n")
            return 0
        if argv[1] == "plan":
            print(f"{argv[2]}: plan written to {release_plan(repo, argv[2], Path(argv[3]))}")
            return 0
        if argv[1] == "compare":
            count = compare(repo, argv[2], Path(argv[3]))
            print(f"{argv[2]}: {count} package files rebuilt byte for byte")
            return 0
        report = verify(env)
    except FAILURES as error:
        print(f"::error title=release verification::{error}")
        return 1
    Path(argv[2]).write_text(json.dumps(report, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    for notice in report["notices"]:
        print(f"::notice title=release verification::{notice}")
    for failure in report["failures"]:
        print(f"::error title=release verification::{failure}")
    checked = len(report["releases"])
    print(
        f"{checked} release(s) checked at {report['checked']}, {len(report['failures'])} failure(s)"
    )
    return 1 if report["failures"] else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
