#!/usr/bin/env python3
"""Plan a release: decide its version, check it against the version policy, record its changes.

Usage: release_plan.py <out>
  out  directory for plan.json, created if missing

Run from a checkout of this repository with its full history and tags, as the
release workflow's preflight job does, for the push of a version tag vX.Y.Z:
the release of that tag. Any other run is refused.

A release must pass, in this order: the tag is an annotated tag of the form
vX.Y.Z and names the checked-out commit; the checkout is not shallow; the
commit lies on main (RELEASE_MAIN, default origin/main). Then the version
policy: the changes since the previous release are breaking (a "!" subject; a
wire-breaking row from check_wire_compat.py; a break mavlink's
check_api_break.py reports for military.xml; a breaking row in common.xml,
standard.xml or minimal.xml when MAVLINK_REF moved; a change to the fixed C
headers when PYMAVLINK_REF moved; or a message or command number that an
earlier release gave another name), additions (a feat subject, an
extension-only or added row, a new row upstream, a change of military.xml's
<version>, which sets the C MAVLINK_VERSION constant) or other. From 1.0.0 they
call for a major, minor or patch bump; before 1.0.0 a breaking change calls for
a minor bump and anything else for a patch. The version must be one of the
previous release's successors at that level or above, and above every release.
Any breach stops the plan.

The previous release is the highest final release published on GitHub whose
tag is an ancestor of the commit and below the version; its military.xml asset
must match both its SHA256SUMS and the tag's blob. Its absence makes this the
first release, which may take any version.

The run may publish only if, independently of the workflow's own condition,
the repository is RELEASE_UPSTREAM (default Dronecode/mavlink-military) and the
event is a push of a vX.Y.Z tag. GITHUB_OUTPUT receives tag, version, commit,
previous and publish. MAVLINK_DIR and PYMAVLINK_DIR name the pinned checkouts,
and PYTHONPATH must give pymavlink to check_wire_compat.py. pymavlink's repository
is the one the setup-mavlink-tooling action checks it out from, read from this
checkout's action as check_pins_upstream.py reads it; the plan records it with
the generator's identity.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import NamedTuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
import gh_api  # noqa: E402

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "generate_c_lib"))
import check_pins_upstream  # noqa: E402

HERE = Path(__file__).resolve().parent
TAG = re.compile(r"v(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)")  # ASCII digits only
SUBJECT = re.compile(r"(feat|fix|docs|ci|chore)\(([A-Za-z0-9_-]+)\)(!)?: (.+)")
DECISION = re.compile(r"^Decision: (https://[A-Za-z0-9._~:/?#\[\]@!$&'()*+,;=%-]+)$", re.M)
PAGE = 100  # releases per page of the releases API
LEVELS = ("patch", "minor", "major")
WIRE_PREFIX = "::warning title=wire-format change::"
BREAKS_IN = "Name removals/changes detected in "
UPSTREAM_DEFINITIONS = ("common", "standard", "minimal")
# The setup action, which checks the pins out and names pymavlink's repository.
ACTION = Path(".github/actions/setup-mavlink-tooling/action.yml")
FIXED_HEADERS = (
    "checksum.h",
    "mavlink_conversions.h",
    "mavlink_get_info.h",
    "mavlink_helpers.h",
    "mavlink_sha256.h",
    "mavlink_types.h",
    "protocol.h",
)


class PlanError(Exception):
    """A breach that stops a release."""


class Version(NamedTuple):
    major: int
    minor: int
    patch: int

    @classmethod
    def parse(cls, text: str) -> Version | None:
        match = TAG.fullmatch(text)
        return cls(*map(int, match.groups())) if match else None

    def __str__(self) -> str:
        return f"{self.major}.{self.minor}.{self.patch}"

    @property
    def tag(self) -> str:
        return f"v{self}"


def successors(previous: Version) -> dict[str, Version]:
    """The next version at each bump level."""
    major, minor, patch = previous
    return {
        "patch": Version(major, minor, patch + 1),
        "minor": Version(major, minor + 1, 0),
        "major": Version(major + 1, 0, 0),
    }


def level_for(change: str, previous: Version) -> str:
    """The bump a class of change calls for after the release previous."""
    if previous.major == 0:
        return "minor" if change == "breaking" else "patch"
    return {"breaking": "major", "addition": "minor", "other": "patch"}[change]


def run(command: list[str], **kwargs) -> str:
    return subprocess.run(command, check=True, capture_output=True, text=True, **kwargs).stdout


def git(*args: str) -> str:
    return run(["git", *args])


def is_ancestor(commit: str, of: str) -> bool:
    return subprocess.run(["git", "merge-base", "--is-ancestor", commit, of]).returncode == 0


def blob_sha256(commit: str, path: str) -> str:
    data = subprocess.run(
        ["git", "show", f"{commit}:{path}"], check=True, capture_output=True
    ).stdout
    return hashlib.sha256(data).hexdigest()


class Release(NamedTuple):
    version: Version
    commit: str


def release_listing(repo: str) -> list[dict]:
    """Every release of the repository, read a page at a time until a short page."""
    listing: list[dict] = []
    page = 1
    while True:
        entries = gh_api.api(f"repos/{repo}/releases?per_page={PAGE}&page={page}") or []
        listing += entries
        if len(entries) < PAGE:
            return listing
        page += 1


def published_releases(repo: str) -> list[Release]:
    """The final releases published on GitHub whose tags this checkout holds."""
    found = []
    for entry in release_listing(repo):
        version = Version.parse(entry["tag_name"])
        if entry["draft"] or entry["prerelease"] or version is None:
            continue
        try:
            commit = git("rev-parse", f"refs/tags/{version.tag}^{{commit}}").strip()
        except subprocess.CalledProcessError:
            raise PlanError(
                f"release {version.tag} is published but its tag is not in this checkout"
            )
        found.append(Release(version, commit))
    return sorted(found)


def verify_previous_xml(repo: str, previous: Release) -> None:
    """The previous release's military.xml asset matches its SHA256SUMS and its tag."""
    name = f"mavlink-m-{previous.version}-military.xml"
    with tempfile.TemporaryDirectory() as work:
        gh_api.run(
            "release", "download", previous.version.tag, "--repo", repo, "--dir", work,
            "--pattern", "SHA256SUMS", "--pattern", name,
        )  # fmt: skip
        sums = dict(
            reversed(line.split("  ", 1))
            for line in Path(work, "SHA256SUMS").read_text(encoding="utf-8").splitlines()
            if "  " in line
        )
        asset = hashlib.sha256(Path(work, name).read_bytes()).hexdigest()
    if sums.get(name) != asset or asset != blob_sha256(previous.commit, "military.xml"):
        raise PlanError(
            f"{previous.version.tag}: its military.xml asset does not match its SHA256SUMS and tag"
        )


class Change(NamedTuple):
    commit: str
    subject: str
    body: str
    kind: str
    breaking: bool
    signed_off: bool
    assisted: tuple[str, ...]

    @property
    def change(self) -> str:
        return "breaking" if self.breaking else "addition" if self.kind == "feat" else "other"


def changes(since: str | None) -> tuple[list[Change], list[str]]:
    """The commits since a release (or all, for a first one), oldest first, and
    warnings about subjects that do not follow the convention."""
    span = f"{since}..HEAD" if since else "HEAD"
    log = git("log", "--reverse", "--no-merges", "--format=%H%x1f%s%x1f%b%x1e", span)
    found, warnings = [], []
    for record in filter(None, (r.strip("\n") for r in log.split("\x1e"))):
        commit, subject, body = record.split("\x1f")
        match = SUBJECT.fullmatch(subject)
        if match is None and not subject.startswith('Revert "'):
            warnings.append(f"{commit[:12]}: subject not in type(scope): form")
        trailers = re.findall(r"^Assisted-by: (\S+)", body, re.M)
        found.append(
            Change(
                commit,
                subject,
                body.strip(),
                match.group(1) if match else "other",
                bool(match and match.group(3)),
                bool(re.search(r"^Signed-off-by: ", body, re.M)),
                tuple(trailers),
            )
        )
    return found, warnings


def run_report(command: list[str], env: dict[str, str]) -> subprocess.CompletedProcess[str]:
    return subprocess.run(command, capture_output=True, text=True, env=env)


def report_env() -> dict[str, str]:
    """The environment for the report scripts, without what makes them post or guess."""
    drop = {"GITHUB_STEP_SUMMARY", "GITHUB_EVENT_PATH", "GITHUB_EVENT_NAME"}
    drop |= {"GITHUB_BASE_REF", "MAVLINK_BASE_REF", "WIRE_COMPAT_ENFORCE"}
    return {k: v for k, v in os.environ.items() if k not in drop}


def wire_rows(base: str, head: str, work: Path, name: str) -> dict:
    """check_wire_compat.py on two versions of one definitions file."""
    old, new = work / f"old-{name}.xml", work / f"new-{name}.xml"
    old.write_text(base, encoding="utf-8")
    new.write_text(head, encoding="utf-8")
    compat = HERE.parent / "validate_dialect" / "check_wire_compat.py"
    result = run_report([sys.executable, str(compat), str(old), str(new)], report_env())
    if result.returncode != 0:
        raise PlanError(f"check_wire_compat.py exited {result.returncode}: {result.stderr.strip()}")
    lines = [line.removeprefix(WIRE_PREFIX) for line in result.stdout.splitlines()]
    return {
        "breaking": [line for line in lines if line.startswith("BREAKING: ")],
        "info": [line for line in lines if line.startswith("INFO: ")],
        "verdict": lines[-1] if lines else "",
    }


def api_breaks(output: str) -> list[str]:
    """The breaks check_api_break.py lists for military.xml. The template,
    military_extensions.xml, is no part of the dialect, so its breaks do not count."""
    breaks, current = [], None
    for line in output.splitlines():
        if line.startswith(BREAKS_IN):
            current = line[len(BREAKS_IN) :].rstrip(":")
        elif line.startswith(" - ") and current == "military.xml":
            breaks.append(line[3:])
        elif not line.startswith(" - "):
            current = None
    return breaks


def api_report(previous: Release) -> list[str]:
    checker = Path(os.environ.get("MAVLINK_DIR", "mavlink")) / "scripts" / "check_api_break.py"
    command = [sys.executable, str(checker), "--base", previous.version.tag]
    result = run_report(command, report_env())
    if result.returncode not in (0, 1) or (
        result.returncode == 1 and BREAKS_IN not in result.stdout
    ):
        raise PlanError(
            f"check_api_break.py exited {result.returncode} without a verdict: "
            f"{(result.stdout + result.stderr).strip()[-500:]}"
        )
    return api_breaks(result.stdout) if result.returncode == 1 else []


def pins(commit: str = "HEAD") -> dict[str, str]:
    """The generator pins at a commit."""
    text = git("show", f"{commit}:.github/mavlink-pins.env")
    found = dict(re.findall(r"^(MAVLINK_REF|PYMAVLINK_REF)=([0-9a-f]{40})$", text, re.M))
    if set(found) != {"MAVLINK_REF", "PYMAVLINK_REF"}:
        raise PlanError(
            f"{commit}: .github/mavlink-pins.env lacks a full MAVLINK_REF or PYMAVLINK_REF"
        )
    return {"mavlink": found["MAVLINK_REF"], "pymavlink": found["PYMAVLINK_REF"]}


def raw(repo: str, path: str, ref: str) -> str:
    return gh_api.run(
        "api", "-H", "Accept: application/vnd.github.raw", f"repos/{repo}/contents/{path}?ref={ref}"
    )


def closure_report(old: str, new: str, work: Path) -> dict:
    """The wire rows of the included upstream files between two MAVLINK_REFs."""
    mavlink = Path(os.environ.get("MAVLINK_DIR", "mavlink"))
    report = {"from": old, "to": new, "breaking": [], "info": []}
    for name in UPSTREAM_DEFINITIONS:
        path = f"message_definitions/v1.0/{name}.xml"
        rows = wire_rows(
            raw("mavlink/mavlink", path, old),
            (mavlink / path).read_text(encoding="utf-8"),
            work,
            name,
        )
        report["breaking"] += [f"{name}.xml: {line}" for line in rows["breaking"]]
        report["info"] += [f"{name}.xml: {line}" for line in rows["info"]]
    return report


def generator_repository() -> str:
    """The repository the setup action checks pymavlink out from, as owner/name."""
    try:
        return check_pins_upstream.read_repositories(ACTION, ["pymavlink"])["pymavlink"]
    except (OSError, ValueError) as error:
        raise PlanError(f"the generator's repository: {error}") from error


def generator_report(repository: str, old: str, new: str) -> dict:
    """The pymavlink commits between two PYMAVLINK_REFs and the fixed C headers they change."""
    pymavlink = Path(os.environ.get("PYMAVLINK_DIR", "pymavlink"))
    changed = [
        name
        for name in FIXED_HEADERS
        if raw(repository, f"generator/C/include_v2.0/{name}", old)
        != (pymavlink / "generator" / "C" / "include_v2.0" / name).read_text(encoding="utf-8")
    ]
    compare = gh_api.api(f"repos/{repository}/compare/{old}...{new}")
    commits = [c["commit"]["message"].splitlines()[0] for c in compare.get("commits", [])]
    return {"from": old, "to": new, "fixed_headers_changed": changed, "commits": commits}


def generator_identity(repository: str, pin: str) -> dict:
    """pymavlink's repository, its own version string at the pin, and where the pin sits
    against its release tag."""
    init = (Path(os.environ.get("PYMAVLINK_DIR", "pymavlink")) / "__init__.py").read_text(
        encoding="utf-8"
    )
    match = re.search(r"""__version__ = ['"]([^'"]+)['"]""", init)
    version = match.group(1) if match else None
    identity = {"repository": repository, "commit": pin, "reports_version": version}
    if version:
        compare = gh_api.api(f"repos/{repository}/compare/v{version}...{pin}")
        identity.update(
            release_tag=f"v{version}", ahead_by=compare["ahead_by"], behind_by=compare["behind_by"]
        )
    return identity


def pin_checks(current: dict[str, str], generator: str) -> list[str]:
    """Each pin lies on its upstream default branch, and pymavlink is mavlink's own submodule commit."""
    notes = []
    for repo, pin, branch in (
        ("mavlink/mavlink", current["mavlink"], "master"),
        (generator, current["pymavlink"], "master"),
    ):
        status = gh_api.api(f"repos/{repo}/compare/{pin}...{branch}")["status"]
        if status not in ("ahead", "identical"):
            raise PlanError(f"{repo} pin {pin} is not on {branch} ({status})")
    gitlink = gh_api.api(f"repos/mavlink/mavlink/contents/pymavlink?ref={current['mavlink']}")
    if gitlink.get("sha") != current["pymavlink"]:
        notes.append(
            f"PYMAVLINK_REF differs from mavlink's pymavlink submodule at MAVLINK_REF ({gitlink.get('sha')})"
        )
    return notes


def message_names(commit: str) -> dict[str, str]:
    """Message IDs and MAV_CMD values of military.xml at a commit, with their names."""
    root = ET.fromstring(git("show", f"{commit}:military.xml"))
    names = {f"message {m.get('id')}": m.get("name") for m in root.iter("message")}
    for enum in root.iter("enum"):
        if enum.get("name") == "MAV_CMD":
            names.update({f"MAV_CMD {e.get('value')}": e.get("name") for e in enum.iter("entry")})
    return names


def id_reuse(earlier: list[Release], head: str) -> list[str]:
    """IDs that an earlier release gave a name and this commit gives another."""
    now = message_names(head)
    reused = {}
    for release in earlier:
        for key, name in message_names(release.commit).items():
            if key in now and now[key] != name:
                reused.setdefault(key, f"{key} was {name} in {release.version.tag}, is {now[key]}")
    return [reused[key] for key in sorted(reused)]


def dialect_fields(commit: str) -> dict[str, str | None]:
    root = ET.fromstring(git("show", f"{commit}:military.xml"))
    return {name: root.findtext(name) for name in ("version", "dialect")}


def check_policy(
    version: Version,
    previous: Release | None,
    required: str | None,
    known: list[Release],
    head: str,
) -> list[str]:
    """Every way version breaks the version policy (empty if none)."""
    breaches = []
    if any(r.version == version for r in known):
        breaches.append(f"{version.tag} is released already")
    elif known and version <= known[-1].version:
        breaches.append(f"{version.tag} is not above the highest release, {known[-1].version.tag}")
    if previous is not None:
        steps = {v: level for level, v in successors(previous.version).items()}
        level = steps.get(version)
        if level is None:
            breaches.append(
                f"{version.tag} does not follow {previous.version.tag}: the next versions are "
                + ", ".join(v.tag for v in successors(previous.version).values())
            )
        elif required is not None and LEVELS.index(level) < LEVELS.index(required):
            breaches.append(
                f"the changes since {previous.version.tag} call for a {required} bump, "
                f"but {version.tag} is a {level} bump"
            )
        if previous.commit == head:
            breaches.append(f"nothing changed since {previous.version.tag}")
    return breaches


def publishing(env: dict[str, str]) -> bool:
    """Whether this run may publish: Dronecode's repository, a push of a vX.Y.Z tag."""
    upstream = env.get("RELEASE_UPSTREAM", "Dronecode/mavlink-military")
    ref = env.get("GITHUB_REF", "")
    return (
        env.get("GITHUB_REPOSITORY") == upstream
        and env.get("GITHUB_EVENT_NAME") == "push"
        and env.get("GITHUB_REF_TYPE") == "tag"
        and ref.startswith("refs/tags/")
        and Version.parse(ref.removeprefix("refs/tags/")) is not None
    )


def release_checks(tag: str, head: str) -> str:
    """The checks a tag must pass before anything is built for it; its decision link, if any."""
    if Version.parse(tag) is None:
        raise PlanError(f"{tag!r} is no release tag of the form vX.Y.Z")
    if git("rev-parse", "--is-shallow-repository").strip() != "false":
        raise PlanError(
            "the checkout is shallow; the release needs the full history (fetch-depth: 0)"
        )
    if git("cat-file", "-t", f"refs/tags/{tag}").strip() != "tag":
        raise PlanError(
            f"{tag} is a lightweight tag; releases come from annotated tags (git tag -a)"
        )
    if git("rev-parse", f"refs/tags/{tag}^{{commit}}").strip() != head:
        raise PlanError(f"{tag} does not name the checked-out commit {head}")
    main_ref = os.environ.get("RELEASE_MAIN", "origin/main")
    if not is_ancestor(head, main_ref):
        raise PlanError(f"{tag} is not on {main_ref}; releases come from main only")
    decision = DECISION.search(git("cat-file", "tag", f"refs/tags/{tag}"))
    return decision.group(1) if decision else None


def classes_of(
    found: list[Change],
    wire: dict | None,
    closure: dict | None,
    generator: dict | None,
    reused: list[str],
    fields: dict | None = None,
) -> set[str]:
    classes = {c.change for c in found}
    if fields and fields["previous"] is not None and fields["version"] != fields["previous"]:
        classes.add("addition")  # the C MAVLINK_VERSION constant changes
    if wire and (wire["breaking"] or wire["api_breaks"]):
        classes.add("breaking")
    if wire and wire["info"]:
        classes.add("addition")
    if closure:
        classes |= {"breaking"} if closure["breaking"] else set()
        classes |= {"addition"} if closure["info"] else set()
    if (generator and generator["fixed_headers_changed"]) or reused:
        classes.add("breaking")
    return classes


def plan(env: dict[str, str]) -> dict:
    repo = env["GITHUB_REPOSITORY"]
    head = git("rev-parse", "HEAD").strip()
    tag = env.get("GITHUB_REF_NAME", "") if env.get("GITHUB_REF_TYPE") == "tag" else ""
    if env.get("GITHUB_EVENT_NAME") != "push" or not tag:
        raise PlanError("a release plan runs only for the push of a version tag vX.Y.Z")
    decision = release_checks(tag, head)
    target = Version.parse(tag)
    known = [r for r in published_releases(repo) if r.version != target]
    earlier = [r for r in known if is_ancestor(r.commit, head) and r.version < target]
    previous = earlier[-1] if earlier else None
    current = pins()
    generator_repo = generator_repository()
    notes = pin_checks(current, generator_repo)
    found, warnings = changes(previous.commit if previous else None)
    wire = closure = generator = None
    reused: list[str] = []
    if previous:
        verify_previous_xml(repo, previous)
        before = pins(previous.commit)
        with tempfile.TemporaryDirectory() as work:
            wire = wire_rows(
                git("show", f"{previous.commit}:military.xml"),
                git("show", "HEAD:military.xml"),
                Path(work),
                "military",
            )
            wire["api_breaks"] = api_report(previous)
            if before["mavlink"] != current["mavlink"]:
                closure = closure_report(before["mavlink"], current["mavlink"], Path(work))
        if before["pymavlink"] != current["pymavlink"]:
            generator = generator_report(generator_repo, before["pymavlink"], current["pymavlink"])
        reused = id_reuse(earlier, head)
    fields = dialect_fields(head)
    before = dialect_fields(previous.commit) if previous else {"version": None, "dialect": None}
    fields["previous"], fields["previous_dialect"] = before["version"], before["dialect"]
    classes = classes_of(found, wire, closure, generator, reused, fields)
    required = (
        max((level_for(c, previous.version) for c in classes), key=LEVELS.index)
        if previous and classes
        else None
    )
    breaches = check_policy(target, previous, required, known, head)
    if breaches:
        raise PlanError("; ".join(breaches))
    marked = any(c.breaking for c in found)
    tool_breaks = bool(
        wire and (wire["breaking"] or wire["api_breaks"]) or closure and closure["breaking"]
    )
    mismatches = []
    if tool_breaks and not marked:
        mismatches.append("the wire reports show breaking changes that no commit marks with !")
    if marked and previous and not tool_breaks:
        mismatches.append(
            "commits marked with ! change no wire row: each declares a change of meaning"
        )
    return {
        "schema": 1,
        "publish": publishing(env),
        "repository": repo,
        "version": str(target),
        "tag": target.tag,
        "commit": head,
        "tree": git("rev-parse", "HEAD^{tree}").strip(),
        "source_date_epoch": int(git("log", "-1", "--format=%ct", "HEAD")),
        "previous": {"tag": previous.version.tag, "commit": previous.commit} if previous else None,
        "decision": decision,
        "pins": current,
        "generator": generator_identity(generator_repo, current["pymavlink"]),
        "pin_notes": notes,
        "dialect": fields,
        "policy": {"required": required, "mismatches": mismatches},
        "changes": [
            {"commit": c.commit, "subject": c.subject, "kind": c.kind, "change": c.change,
             "signed_off": c.signed_off, "assisted_by": list(c.assisted)}
            for c in found
        ],  # fmt: skip
        "wire": wire,
        "closure": closure,
        "generator_change": generator,
        "id_reuse": reused,
        "warnings": warnings,
    }


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print(__doc__, file=sys.stderr)
        return 2
    out = Path(argv[1])
    out.mkdir(parents=True, exist_ok=True)
    (out / "plan.json").unlink(missing_ok=True)  # a failed plan leaves none behind
    try:
        result = plan(dict(os.environ))
    except (PlanError, gh_api.GitHubError) as error:
        print(f"::error title=release plan::{error}")
        return 1
    except subprocess.CalledProcessError as error:
        print(f"::error title=release plan::{' '.join(error.cmd)}: {error.stderr.strip()}")
        return 1
    (out / "plan.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    for warning in result["warnings"] + result["pin_notes"] + result["policy"]["mismatches"]:
        print(f"::warning title=release plan::{warning}")
    previous = result["previous"]["tag"] if result["previous"] else "none"
    print(
        f"{result['tag']}, previous release {previous}, publish {result['publish']}"
    )
    output = os.environ.get("GITHUB_OUTPUT")
    if output:
        with open(output, "a", encoding="utf-8") as stream:
            for key in ("tag", "version", "commit"):
                stream.write(f"{key}={result[key]}\n")
            stream.write(f"previous={previous}\npublish={str(result['publish']).lower()}\n")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
