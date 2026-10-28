#!/usr/bin/env python3
"""Assemble a release's files from its two package builds, its docs and its records.

Usage: release_assemble.py <plan.json> <build-a> <build-b> <docs> <records> <out>
  plan.json         the preflight job's plan
  build-a, build-b  the two independent package builds, each with SHA256SUMS
                    and leg/checks.json and leg/toolchain.json
  docs              the release's built pages, from docs.yml at the release tag
  records           the other jobs' records: coverage.json and zizmor.sarif
                    from the test job, commit-checks.json from the commit checks
  out               directory for the release files; it must not exist yet

Run from a checkout at the plan's commit. NEEDS_JSON is the job's needs context
as JSON; the GITHUB_* variables describe the run.

1. The two builds must agree byte for byte: the same SHA256SUMS, every file it
   lists present and matching in both, and nothing else in either; and they
   must hold exactly the six package files.
2. The docs must be the release's: version.json names the tag and the commit;
   every entry is a regular file. They become the docs archive.
3. Every member of the package archives must match its manifest entry, and
   the manifest must list no other. The SBOM (SPDX 2.3) is written and must
   list every member of the four archives exactly once, with its digests; then
   the notes and the vulnerability record (OSV), then the evidence bundle:
   every job this one needs succeeded, and each required record is present,
   or the assembly fails.
4. SHA256SUMS lists every release file, sorted, in sha256sum's text format,
   with names of letters, digits, dots, underscores and hyphens only.

GITHUB_OUTPUT receives subjects, the base64 of SHA256SUMS followed by the line
for SHA256SUMS itself, which is what the provenance generator signs, and
subjects_sha256, the SHA-256 of that text. A Markdown summary of what the
release holds goes to GITHUB_STEP_SUMMARY: the tag and commit, the builds'
agreement and checks, the job results, the vulnerability record, every file's
SHA-256 and the notes.
"""

from __future__ import annotations

import base64
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import archive  # noqa: E402
import osv  # noqa: E402
import release_notes  # noqa: E402
import release_package  # noqa: E402
import sbom  # noqa: E402

NAME = re.compile(r"[A-Za-z0-9._-]+")
SUMS_LINE = re.compile(r"([0-9a-f]{64})  ([A-Za-z0-9._-]+)")
NEEDED = ("preflight", "validate", "lint", "docs", "commit-checks", "test", "build", "rebuild")
RECORDS = ("coverage.json", "zizmor.sarif", "commit-checks.json")
PACKAGE = (
    "definitions.tar.gz",
    "c.tar.gz",
    "python.tar.gz",
    "military.xml",
    "wire.json",
    "manifest.json",
)
KNOWN_GAPS = [
    "The provenance and the server-side digests come after this bundle; the publish record holds them.",
    "The called workflows (validate_dialect.yml, workflow_lint.yml, docs.yml) are recorded by their job results; "
    "their logs are in the run.",
    "The vulnerability record lists findings; which of them would block a release is for the maintainers to set.",
]


class AssembleError(Exception):
    """Anything that must stop the release."""


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def read_sums(folder: Path) -> list[tuple[str, str]]:
    lines = []
    for line in (folder / "SHA256SUMS").read_text(encoding="ascii").splitlines():
        match = SUMS_LINE.fullmatch(line)
        if match is None:
            raise AssembleError(f"{folder}/SHA256SUMS has a malformed line: {line!r}")
        lines.append((match.group(2), match.group(1)))
    return lines


def compare(a: Path, b: Path) -> dict:
    """The two builds, compared; their common list of files."""
    if (a / "SHA256SUMS").read_bytes() != (b / "SHA256SUMS").read_bytes():
        raise AssembleError("the two builds' SHA256SUMS differ")
    listed = read_sums(a)
    names = {name for name, _ in listed}
    for leg in (a, b):
        present = {p.name for p in leg.iterdir() if p.is_file() and p.name != "SHA256SUMS"}
        if present != names:
            raise AssembleError(
                f"{leg} holds {sorted(present ^ names)} beyond or short of its SHA256SUMS"
            )
        for name, digest in listed:
            if sha256((leg / name).read_bytes()) != digest:
                raise AssembleError(f"{leg}/{name} does not match its SHA256SUMS line")
    return {
        "equal": True,
        "files": len(listed),
        "sums_sha256": sha256((a / "SHA256SUMS").read_bytes()),
        "toolchains": [json.loads((leg / "leg" / "toolchain.json").read_text()) for leg in (a, b)],
    }


def docs_files(docs: Path, plan: dict) -> dict[str, bytes]:
    record = json.loads((docs / "version.json").read_text(encoding="utf-8"))
    if record.get("version") != plan["tag"] or record.get("commit") != plan["commit"]:
        raise AssembleError(
            f"the docs are not {plan['tag']}'s: version.json names {record.get('version')} at {record.get('commit')}"
        )
    files = {}
    for path in sorted(docs.rglob("*")):
        if path.is_symlink() or not (path.is_file() or path.is_dir()):
            raise AssembleError(
                f"docs: {path.relative_to(docs)} is not a regular file or directory"
            )
        if path.is_file():
            files[path.relative_to(docs).as_posix()] = path.read_bytes()
    return files


def members(out: Path, version: str, manifest: dict) -> dict[str, list[dict]]:
    """Every member of the four archives with its SHA-1 and SHA-256, and, for the package
    archives, the manifest's license, copyright and covered flag; a package archive's members
    and its manifest entries must be the same files with the same digests."""
    found = {}
    for kind in sbom.KINDS:
        name, top = f"mavlink-m-{version}-{kind}.tar.gz", f"mavlink-m-{version}-{kind}"
        content = archive.read(out / name, top)
        entries = {e["path"]: e for e in manifest["archives"].get(name, {}).get("files", [])}
        if kind != "docs" and {p: e["sha256"] for p, e in entries.items()} != {
            p: sha256(d) for p, d in content.items()
        }:
            raise AssembleError(f"{name} does not hold exactly the files its manifest entry lists")
        keep = ("license", "copyright", "covered")
        found[name] = [
            {"path": path, "sha1": hashlib.sha1(data).hexdigest(), "sha256": sha256(data),
             **{k: entries[path][k] for k in keep if k in entries.get(path, {})}}
            for path, data in sorted(content.items())
        ]  # fmt: skip
    return found


def needs_results(text: str | None) -> dict[str, str]:
    needs = json.loads(text or "{}")
    results = {name: needs.get(name, {}).get("result", "missing") for name in NEEDED}
    failed = {k: v for k, v in results.items() if v != "success"}
    if failed:
        raise AssembleError(f"jobs this release needs did not succeed: {failed}")
    return results


def inbound(plan: dict) -> dict:
    tools: dict[str, int] = {}
    for change in plan["changes"]:
        for trailer in change["assisted_by"]:
            tools[trailer] = tools.get(trailer, 0) + 1
    return {
        "changes": len(plan["changes"]),
        "signed_off": sum(1 for c in plan["changes"] if c["signed_off"]),
        "assisted_by": dict(sorted(tools.items())),
        "assisted_none": sum(1 for c in plan["changes"] if not c["assisted_by"]),
        "marked_breaking": sum(1 for c in plan["changes"] if c["change"] == "breaking"),
    }


def run_record(env: dict) -> dict:
    server, repo, run_id = (
        env.get("GITHUB_SERVER_URL", ""),
        env.get("GITHUB_REPOSITORY", ""),
        env.get("GITHUB_RUN_ID", ""),
    )
    return {
        "id": run_id,
        "attempt": env.get("GITHUB_RUN_ATTEMPT"),
        "url": f"{server}/{repo}/actions/runs/{run_id}" if server and run_id else None,
        "workflow_ref": env.get("GITHUB_WORKFLOW_REF"),
        "event": env.get("GITHUB_EVENT_NAME"),
        "ref": env.get("GITHUB_REF"),
        "sha": env.get("GITHUB_SHA"),
        "runner_image": env.get("ImageOS"),
        "runner_image_version": env.get("ImageVersion"),
    }


def dumps(value: object) -> bytes:
    return (json.dumps(value, indent=2, sort_keys=True) + "\n").encode("ascii")


def git_show(spec: str) -> bytes:
    result = subprocess.run(["git", "show", spec], capture_output=True)
    if result.returncode != 0:
        raise AssembleError(
            f"git show {spec} failed: {result.stderr.decode(errors='replace').strip()}"
        )
    return result.stdout


def assemble(paths: dict[str, Path], plan: dict, env: dict, send=osv.post) -> dict:
    out, version, epoch = paths["out"], plan["version"], plan["source_date_epoch"]
    if out.exists():
        raise AssembleError(f"{out} exists already")
    results = needs_results(env.get("NEEDS_JSON"))
    records = {}
    for name in RECORDS:
        if not (paths["records"] / name).is_file():
            raise AssembleError(f"the record {name} is missing")
        records[name] = (paths["records"] / name).read_bytes()
    reproducible = compare(paths["a"], paths["b"])
    package = {name for name, _ in read_sums(paths["a"])}
    expected = {f"mavlink-m-{version}-{suffix}" for suffix in PACKAGE}
    if package != expected:
        raise AssembleError(
            f"the builds hold {sorted(package ^ expected)} beyond or short of the package files"
        )
    docs = docs_files(paths["docs"], plan)
    out.mkdir(parents=True)
    for name, _ in read_sums(paths["a"]):
        shutil.copyfile(paths["a"] / name, out / name)
    docs_name = f"mavlink-m-{version}-docs.tar.gz"
    archive.write(out / docs_name, f"mavlink-m-{version}-docs", docs, epoch)
    definitions = archive.read(
        out / f"mavlink-m-{version}-definitions.tar.gz", f"mavlink-m-{version}-definitions"
    )
    c_files = archive.read(out / f"mavlink-m-{version}-c.tar.gz", f"mavlink-m-{version}-c")
    python = archive.read(out / f"mavlink-m-{version}-python.tar.gz", f"mavlink-m-{version}-python")
    manifest = json.loads((out / f"mavlink-m-{version}-manifest.json").read_text())
    wire = json.loads((out / f"mavlink-m-{version}-wire.json").read_text())
    upstream = {
        name: {"sha1": hashlib.sha1(definitions[f"message_definitions/v1.0/{name}"]).hexdigest(),
               "sha256": sha256(definitions[f"message_definitions/v1.0/{name}"])}
        for name in ("common.xml", "minimal.xml", "standard.xml")
    }  # fmt: skip
    lmap = json.loads(release_package.LICENSE_MAP.read_text(encoding="utf-8"))
    toolchain = reproducible["toolchains"][0]
    tools = {"python": toolchain["python"], "lxml": toolchain["lxml"]}
    notices = docs.get("THIRD-PARTY-NOTICES.txt", b"").decode("utf-8")
    holder = release_package.holder(git_show(f"{plan['commit']}:LICENSE"))
    facts = {
        "plan": plan,
        "manifest": manifest,
        "members": members(out, version, manifest),
        "optional": ["fastcrc"] if b"import fastcrc" in python.get("military.py", b"") else [],
        "files": {p.name: sha256(p.read_bytes()) for p in sorted(out.iterdir())},
        "lock": json.loads(git_show(f"{plan['commit']}:docs/package-lock.json")),
        "notices": notices,
        "upstream": upstream,
        "tools": tools,
        "grant": c_files[f"LICENSES/{release_package.GENERATED_CODE}.txt"].decode("utf-8"),
        "grant_lines": lmap["generated_code_grant"]["lines"],
        "holder": holder,
        "license_list_version": lmap["license_list_version"],
    }
    document = sbom.document(facts)
    sbom.check_coverage(document, facts["members"])
    (out / f"mavlink-m-{version}.spdx.json").write_bytes(dumps(document))
    files = {p.name: sha256(p.read_bytes()) for p in sorted(out.iterdir())}
    generator = None
    if env.get("GENERATOR_COMMIT"):
        generator = {k: env[f"GENERATOR_{k.upper()}"] for k in ("workflow", "tag", "commit")}
    notes = release_notes.notes(
        plan,
        files,
        {
            "python": toolchain["python"],
            "c": wire.get("c"),
            "heartbeat_mavlink_version": wire.get("heartbeat_mavlink_version"),
            "signing_rule": release_notes.signing_rule(
                definitions["message_definitions/v1.0/military.xml"].decode("utf-8")
            ),
        },
        generator,
    )
    (out / f"mavlink-m-{version}-notes.md").write_text(notes, encoding="utf-8")
    vulnerabilities = osv.record(plan, tools, sbom.installed_packages(notices), send=send)
    files = {p.name: sha256(p.read_bytes()) for p in sorted(out.iterdir())}
    bundle = {
        "plan.json": dumps(plan),
        "build-a/checks.json": (paths["a"] / "leg" / "checks.json").read_bytes(),
        "build-a/toolchain.json": (paths["a"] / "leg" / "toolchain.json").read_bytes(),
        "build-b/checks.json": (paths["b"] / "leg" / "checks.json").read_bytes(),
        "build-b/toolchain.json": (paths["b"] / "leg" / "toolchain.json").read_bytes(),
        "osv.json": dumps(vulnerabilities),
        **{f"records/{name}": data for name, data in records.items()},
    }
    index = {
        "schema": 1,
        "version": version,
        "tag": plan["tag"],
        "commit": plan["commit"],
        "tree": plan["tree"],
        "repository": plan["repository"],
        "run": run_record(env),
        "jobs": results,
        "records": sorted(bundle),
        "reproducibility": {k: v for k, v in reproducible.items() if k != "toolchains"},
        "inbound": inbound(plan),
        "vulnerabilities": {
            "components": len(vulnerabilities["components"]),
            "with_findings": vulnerabilities["with_findings"],
        },
        "files": files,
        "known_gaps": KNOWN_GAPS,
    }
    bundle["evidence.json"] = dumps(index)
    archive.write(
        out / f"mavlink-m-{version}-evidence.tar.gz", f"mavlink-m-{version}-evidence", bundle, epoch
    )
    names = sorted(p.name for p in out.iterdir())
    bad = [n for n in names if not NAME.fullmatch(n)]
    if bad:
        raise AssembleError(f"release file names outside [A-Za-z0-9._-]: {bad}")
    sums = "".join(f"{sha256((out / n).read_bytes())}  {n}\n" for n in names)
    (out / "SHA256SUMS").write_text(sums, encoding="ascii")
    subjects = sums + f"{sha256(sums.encode('ascii'))}  SHA256SUMS\n"
    return {
        "files": names + ["SHA256SUMS"],
        "subjects": base64.b64encode(subjects.encode("ascii")).decode("ascii"),
        "subjects_sha256": sha256(subjects.encode("ascii")),
        "reproducible": reproducible,
        "checks": json.loads((paths["a"] / "leg" / "checks.json").read_text()),
        "jobs": results,
        "vulnerabilities": vulnerabilities,
        "sums": sums,
        "notes": notes,
    }


def summary(plan: dict, result: dict) -> str:
    lines = [f"## {plan['tag']}", "", f"Commit `{plan['commit']}`.", ""]
    lines.append(
        f"The two package builds agree: {result['reproducible']['files']} files, SHA256SUMS {result['reproducible']['sums_sha256']}."
    )
    lines.append(
        "Checks: " + ", ".join(f"{k} {v}" for k, v in sorted(result["checks"].items())) + "."
    )
    lines += ["", "| Job | Result |", "| --- | --- |"]
    lines += [f"| {job} | {state} |" for job, state in result["jobs"].items()]
    v = result["vulnerabilities"]
    lines += [
        "",
        f"OSV: {len(v['components'])} components queried, {v['with_findings']} with findings.",
    ]
    lines += [
        f"- {r['component']}: {', '.join(r['findings'])}" for r in v["components"] if r["findings"]
    ]
    lines += ["", "| File | SHA-256 |", "| --- | --- |"]
    lines += [f"| {line[66:]} | {line[:64]} |" for line in result["sums"].splitlines()]
    lines += ["", "<details><summary>Release notes</summary>", "", result["notes"], "</details>"]
    return "\n".join(lines) + "\n"


def main(argv: list[str]) -> int:
    if len(argv) != 7:
        print(__doc__, file=sys.stderr)
        return 2
    plan = json.loads(Path(argv[1]).read_text(encoding="utf-8"))
    paths = dict(zip(("a", "b", "docs", "records", "out"), map(Path, argv[2:])))
    try:
        result = assemble(paths, plan, dict(os.environ))
    except (
        AssembleError,
        osv.OsvError,
        archive.ArchiveError,
        release_package.PackageError,
        sbom.SbomError,
    ) as error:
        print(f"::error title=release assembly::{error}")
        return 1
    print(f"assembled {len(result['files'])} release files for {plan['tag']}")
    output = os.environ.get("GITHUB_OUTPUT")
    if output:
        with open(output, "a", encoding="utf-8") as stream:
            stream.write(
                f"subjects={result['subjects']}\nsubjects_sha256={result['subjects_sha256']}\n"
            )
    step = os.environ.get("GITHUB_STEP_SUMMARY")
    if step:
        with open(step, "a", encoding="utf-8") as stream:
            stream.write(summary(plan, result))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
