#!/usr/bin/env python3
"""Publish a release, after checking it as a consumer would.

Usage: release_publish.py <files> <bundle> <audit.json>
  files       the release files the assemble job wrote, SHA256SUMS among them
  bundle      the generator's provenance, mavlink-m-<version>.intoto.jsonl
  audit.json  the generator-audit job's record

RELEASE_TAG and RELEASE_VERSION name the release; GENERATOR_WORKFLOW and
GENERATOR_COMMIT the generator; the GITHUB_* variables the run. Every GitHub
call goes through gh (gh_api), with the job token, which may write contents.

Before anything is created on GitHub:
1. the bundle has the expected name, and the subjects it signs are exactly
   SHA256SUMS's lines plus SHA256SUMS itself;
2. every release file verifies against the bundle with the consumer policy:
   gh attestation verify with --bundle, this repository, the generator's
   workflow and commit as signer, this tag and commit as source, the SLSA
   v0.2 predicate and GitHub-hosted runners only; and the certificate's
   buildConfigURI is this repository's release.yml at this tag;
3. the generator's tag still names its reviewed commit;
4. the release tag, read again through the API (peeled if annotated), still
   names the commit this run built.

Then it creates a draft release with every file and the bundle, checks every
asset's server-side SHA-256, adds the publish record (the generator's jobs,
the certificate, the asset digests), and publishes the release as the
latest. A draft that a failed attempt left is deleted first; a published
release is never touched. Last, it downloads the published release into a
new directory and checks every file again, the provenance included.
"""

from __future__ import annotations

import base64
import hashlib
import json
import os
import re
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import gh_api  # noqa: E402
import release_generator  # noqa: E402

PREDICATE = "https://slsa.dev/provenance/v0.2"
SUMS_LINE = re.compile(r"([0-9a-f]{64})  ([A-Za-z0-9._-]+)")
CERTIFICATE = (
    "buildSignerURI", "buildSignerDigest", "buildConfigURI",
    "sourceRepositoryRef", "sourceRepositoryDigest", "runnerEnvironment",
)  # fmt: skip


class PublishError(Exception):
    """A check that must stop the publication."""


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def sums(files: Path) -> list[tuple[str, str]]:
    found = []
    for line in (files / "SHA256SUMS").read_text(encoding="ascii").splitlines():
        match = SUMS_LINE.fullmatch(line)
        if match is None:
            raise PublishError(f"SHA256SUMS has a malformed line: {line!r}")
        found.append((match.group(2), match.group(1)))
    for name, digest in found:
        if not (files / name).is_file() or sha256(files / name) != digest:
            raise PublishError(f"{name} is missing or does not match SHA256SUMS")
    return found


def signed_subjects(bundle: Path) -> list[tuple[str, str]]:
    lines = [line for line in bundle.read_text(encoding="utf-8").splitlines() if line.strip()]
    try:
        envelope = json.loads(lines[0])["dsseEnvelope"]
        statement = json.loads(base64.b64decode(envelope["payload"]))
        return sorted((s["name"], s["digest"]["sha256"]) for s in statement["subject"])
    except (IndexError, KeyError, TypeError, ValueError) as error:
        raise PublishError(f"{bundle.name} holds no signed in-toto statement: {error}") from error


def verify(path: Path, bundle: Path, env: dict) -> dict:
    """gh attestation verify with the consumer policy; the certificate's fields."""
    output = gh_api.run(
        "attestation", "verify", str(path), "--bundle", str(bundle),
        "--repo", env["GITHUB_REPOSITORY"],
        "--signer-workflow", env["GENERATOR_WORKFLOW"], "--signer-digest", env["GENERATOR_COMMIT"],
        "--source-ref", env["GITHUB_REF"], "--source-digest", env["GITHUB_SHA"],
        "--predicate-type", PREDICATE, "--deny-self-hosted-runners", "--format", "json",
    )  # fmt: skip
    try:
        certificate = json.loads(output)[0]["verificationResult"]["signature"]["certificate"]
    except (IndexError, KeyError, TypeError, ValueError) as error:
        raise PublishError(
            f"{path.name}: gh attestation verify gave no certificate: {error}"
        ) from error
    expected = f"https://github.com/{env['GITHUB_REPOSITORY']}/.github/workflows/release.yml@{env['GITHUB_REF']}"
    if certificate.get("buildConfigURI") != expected:
        raise PublishError(
            f"{path.name}: the provenance was built by {certificate.get('buildConfigURI')}, not {expected}"
        )
    return {key: certificate.get(key) for key in CERTIFICATE}


def tag_commit(repo: str, tag: str) -> str:
    """The commit a tag names now, read through the API and peeled if annotated."""
    target = gh_api.api(f"repos/{repo}/git/ref/tags/{tag}")["object"]
    while target["type"] == "tag":
        target = gh_api.api(f"repos/{repo}/git/tags/{target['sha']}")["object"]
    return target["sha"]


def existing(repo: str, tag: str) -> dict | None:
    """The release on a tag, drafts included, or None."""
    for release in gh_api.api(f"repos/{repo}/releases?per_page=100") or []:
        if release["tag_name"] == tag:
            return release
    return None


def publish(files: Path, bundle: Path, audit: dict, env: dict) -> dict:
    repo, tag, version = env["GITHUB_REPOSITORY"], env["RELEASE_TAG"], env["RELEASE_VERSION"]
    if bundle.name != f"mavlink-m-{version}.intoto.jsonl":
        raise PublishError(f"the provenance is {bundle.name}, not mavlink-m-{version}.intoto.jsonl")
    listed = sums(files)
    subjects = sorted(listed + [("SHA256SUMS", sha256(files / "SHA256SUMS"))])
    if signed_subjects(bundle) != subjects:
        raise PublishError("the provenance signs other subjects than SHA256SUMS lists")
    certificate = None
    for name, _ in subjects:
        certificate = verify(files / name, bundle, env)
    gen = release_generator.expected(env)
    release_generator.check_pin(gen)
    named = tag_commit(repo, tag)
    if named != env["GITHUB_SHA"]:
        raise PublishError(
            f"{tag} names {named} now, not {env['GITHUB_SHA']}, the commit this run built"
        )
    found = existing(repo, tag)
    if found and not found["draft"]:
        raise PublishError(f"{tag} is published already; a published release is never changed")
    if found:
        gh_api.run("api", "-X", "DELETE", f"repos/{repo}/releases/{found['id']}")
    assets = [str(files / name) for name, _ in subjects] + [str(bundle)]
    notes = files / f"mavlink-m-{version}-notes.md"
    gh_api.run("release", "create", tag, "--repo", repo, "--draft", "--verify-tag",
               "--title", f"MAVLink-M {version}", "--notes-file", str(notes), *assets)  # fmt: skip
    draft = existing(repo, tag)
    if draft is None or not draft["draft"]:
        raise PublishError(f"no draft release appeared for {tag}")
    server = {
        a["name"]: a.get("digest")
        for a in gh_api.api(f"repos/{repo}/releases/{draft['id']}/assets?per_page=100")
    }
    local = {Path(a).name: f"sha256:{sha256(Path(a))}" for a in assets}
    if server != local:
        raise PublishError(
            f"the draft's assets differ from the files: {sorted(set(server.items()) ^ set(local.items()))}"
        )
    record = {
        "schema": 1,
        "tag": tag,
        "version": version,
        "commit": env["GITHUB_SHA"],
        "repository": repo,
        "run": {"id": env.get("GITHUB_RUN_ID"), "attempt": env.get("GITHUB_RUN_ATTEMPT"),
                "url": f"{env.get('GITHUB_SERVER_URL')}/{repo}/actions/runs/{env.get('GITHUB_RUN_ID')}"},  # fmt: skip
        "generator": {**audit["generator"], "jobs": audit["jobs"]},
        "provenance": {"bundle": bundle.name, "sha256": sha256(bundle), "certificate": certificate},
        "assets": dict(sorted(server.items())),
    }
    with tempfile.TemporaryDirectory() as work:
        path = Path(work, f"mavlink-m-{version}-publish.json")
        path.write_text(json.dumps(record, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        gh_api.run("release", "upload", tag, "--repo", repo, str(path))
        record_digest = f"sha256:{sha256(path)}"
    gh_api.run("release", "edit", tag, "--repo", repo, "--draft=false", "--latest")
    with tempfile.TemporaryDirectory() as work:
        gh_api.run("release", "download", tag, "--repo", repo, "--dir", work)
        downloaded = {p.name: f"sha256:{sha256(p)}" for p in Path(work).iterdir()}
        expected = {**local, f"mavlink-m-{version}-publish.json": record_digest}
        if downloaded != expected:
            raise PublishError("the published release's files differ from what was uploaded")
        verify(Path(work, "SHA256SUMS"), Path(work, bundle.name), env)
    return record


def main(argv: list[str]) -> int:
    if len(argv) != 4:
        print(__doc__, file=sys.stderr)
        return 2
    try:
        audit = json.loads(Path(argv[3]).read_text(encoding="utf-8"))
        record = publish(Path(argv[1]), Path(argv[2]), audit, dict(os.environ))
    except (
        PublishError,
        gh_api.GitHubError,
        release_generator.GeneratorError,
        OSError,
        ValueError,
    ) as error:
        print(f"::error title=release publish::{error}")
        return 1
    certificate = record["provenance"]["certificate"]
    print(f"published {record['tag']} with {len(record['assets']) + 1} assets")
    summary = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary:
        with open(summary, "a", encoding="utf-8") as stream:
            stream.write(
                f"## Published {record['tag']}\n\nSigner: {certificate['buildSignerURI']} at {certificate['buildSignerDigest']}\n\n"
            )
            stream.write(
                f"Built by: {certificate['buildConfigURI']}\n\n| Asset | Server digest |\n| --- | --- |\n"
            )
            stream.write(
                "".join(f"| {name} | {digest} |\n" for name, digest in record["assets"].items())
            )
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
