#!/usr/bin/env python3
"""The release notes: what changed, what the wire reports say, what the files are.

notes() is a pure function of the plan and the release files' digests, so the
notes asset is the same for the same release. Commit subjects and the reports'
lines are text from the repository's history, so each is shown as a code span,
which renders it literally: no link, mention, HTML or formatting in it takes
effect. A decision link is shown only if it is a plain https URL.
"""

from __future__ import annotations

import re

URL = re.compile(r"https://[A-Za-z0-9._~:/?#\[\]@!$&'()*+,;=%-]+")
EMAIL = re.compile(r"[A-Za-z0-9._%+-]+@[A-Za-z0-9-]+(\.[A-Za-z0-9-]+)+")
KINDS = (("breaking", "Breaking"), ("addition", "Additions"), ("other", "Other changes"))
# The first line of the dialect's message-signing rule in military.xml's comment.
SIGNING_RULE = re.compile(r"^ *- Message signing\. ", re.M)


def code(text: str) -> str:
    """text as a CommonMark code span, whatever backticks it holds."""
    longest = max((len(run) for run in re.findall(r"`+", text)), default=0)
    fence = "`" * (longest + 1)
    pad = " " if text.startswith("`") or text.endswith("`") or not text.strip() else ""
    return f"{fence}{pad}{text}{pad}{fence}"


def change_lines(plan: dict) -> list[str]:
    lines = []
    for kind, title in KINDS:
        found = [c for c in plan["changes"] if c["change"] == kind]
        if found:
            lines += ["", f"### {title}", ""]
            lines += [
                f"- {code(EMAIL.sub('[email]', c['subject']))} ({code(c['commit'][:12])})"
                for c in found
            ]
    return lines or ["", "No commits."]


def wire_lines(plan: dict) -> list[str]:
    previous = plan["previous"]
    if previous is None:
        return [
            "- This is the first release, so there is no earlier version to compare with; it may take any version number."
        ]
    policy = plan["policy"]
    lines = [
        f"- Version policy: the changes since {previous['tag']} call for a {policy['required'] or 'patch'} step, "
        f"and {plan['tag']} takes it."
    ]
    wire = plan["wire"]
    lines.append(
        f"- CRC_EXTRA and lengths, per message: {len(wire['breaking'])} wire-breaking change(s), "
        f"{len(wire['info'])} for information ({code(wire['verdict'])})."
    )
    lines += [f"  - {code(line)}" for line in wire["breaking"] + wire["info"]]
    lines.append(
        f"- Names (mavlink's API-break checker): {len(wire['api_breaks'])} removal(s) or change(s)."
    )
    lines += [f"  - {code(line)}" for line in wire["api_breaks"]]
    if plan["closure"]:
        closure = plan["closure"]
        lines.append(
            f"- The included MAVLink definitions moved ({code(closure['from'][:12])} to {code(closure['to'][:12])}): "
            f"{len(closure['breaking'])} wire-breaking, {len(closure['info'])} for information."
        )
        lines += [f"  - {code(line)}" for line in closure["breaking"] + closure["info"]]
    if plan["generator_change"]:
        change = plan["generator_change"]
        headers = ", ".join(code(h) for h in change["fixed_headers_changed"]) or "none"
        lines.append(
            f"- The generator moved ({code(change['from'][:12])} to {code(change['to'][:12])}, "
            f"{len(change['commits'])} commit(s)); fixed C headers changed: {headers}."
        )
    for line in plan["id_reuse"]:
        lines.append(f"- A number given another name: {code(line)}")
    fields = plan["dialect"]
    if fields["previous"] is not None and fields["version"] != fields["previous"]:
        lines.append(
            f"- military.xml's `<version>` changes from {code(str(fields['previous']))} to "
            f"{code(str(fields['version']))}, so the C `MAVLINK_VERSION` constant changes."
        )
    if (
        fields.get("previous_dialect") is not None
        and fields["dialect"] != fields["previous_dialect"]
    ):
        lines.append(
            "- military.xml's `<dialect>` changes; it has no effect on the generated code."
        )
    for line in policy["mismatches"]:
        lines.append(f"- Note: {line}")
    return lines


def usage_lines(plan: dict, facts: dict) -> list[str]:
    v, pins, gen = plan["version"], plan["pins"], plan["generator"]
    built = f"pymavlink at {code(pins['pymavlink'])}"
    if gen.get("release_tag"):
        built += f" (it reports {gen['reports_version']}, {gen['ahead_by']} commit(s) after {gen['release_tag']})"
    if facts.get("python"):
        built += f", on Python {facts['python']}"
    raw = f"https://raw.githubusercontent.com/{plan['repository']}/{plan['tag']}/military.xml"
    return [
        f"- `mavlink-m-{v}-definitions.tar.gz`: `message_definitions/v1.0/` with `military.xml` and the MAVLink "
        f"files it includes, at mavlink {code(pins['mavlink'])}. Run mavgen on `military.xml` there to generate "
        "bindings for another language; with pymavlink at the same commit, C and Python come out as in this release.",
        f"- `mavlink-m-{v}-c.tar.gz`: MAVLink 2 C headers; include `military/mavlink.h`. Generated by {built}. "
        "Their `MAVLINK_BUILD_DATE` is the release commit's date, so they rebuild byte for byte.",
        f"- `mavlink-m-{v}-python.tar.gz`: `military.py`, a MAVLink 2 module that needs no other package.",
        f"- `mavlink-m-{v}-military.xml`: the dialect file alone, also at <{raw}>.",
        f"- `mavlink-m-{v}-wire.json`: every message's ID, CRC_EXTRA and lengths, and every command number.",
        f"- `mavlink-m-{v}-manifest.json`: every file in the archives, with its SHA-256 and license.",
        f"- `mavlink-m-{v}-docs.tar.gz`: this version's documentation site, as served at `/{plan['tag']}/`.",
        f"- `mavlink-m-{v}.spdx.json`: the SPDX 2.3 SBOM; `mavlink-m-{v}-evidence.tar.gz`: the checks this "
        "release passed, as machine-readable records.",
        "",
        "The C library branch that this repository publishes from main is a development channel. A release is "
        "the fixed version to depend on.",
    ] + [f"- Note: {line}" for line in plan.get("pin_notes", [])]


def signing_rule(xml: str) -> int | None:
    """The line where military.xml's SAFETY BOUNDARIES state the dialect's message-signing
    rule, if they do."""
    start = xml.find("SAFETY BOUNDARIES")
    found = SIGNING_RULE.search(xml, start) if start >= 0 else None
    return xml.count("\n", 0, found.start()) + 1 if found else None


def protocol_lines(plan: dict, facts: dict) -> list[str]:
    """What the generated bindings need from a peer, measured by the build, and where the
    dialect states its signing rule."""
    c = facts.get("c")
    if not c:
        return []
    lines = ["", "## Protocol", "", "- MAVLink 2 only."]
    rule = facts.get("signing_rule")
    if rule:
        url = f"https://github.com/{plan['repository']}/blob/{plan['tag']}/military.xml#L{rule}"
        lines.append(
            f"- Message signing: the dialect's rule is in `military.xml`, under SAFETY BOUNDARIES: <{url}>."
        )
    lines.append(
        f"- C: `MAVLINK_VERSION` is {c['MAVLINK_VERSION']}, `sizeof(mavlink_message_t)` is "
        f"{c['sizeof_mavlink_message_t']} bytes and `MAVLINK_MAX_PACKET_LEN` is {c['MAVLINK_MAX_PACKET_LEN']}; "
        f"HEARTBEAT's `mavlink_version` on the wire is {facts.get('heartbeat_mavlink_version')}, minimal.xml's."
    )
    return lines + (
        [
            "- The C headers support 32-bit system IDs through the `SYSID32` and `TARGET32` incompatibility "
            "flags, which a frame sets only for a system ID above 255; a receiver whose MAVLink library lacks "
            "them drops such a frame."
        ]
        if c.get("id32_flags")
        else []
    )


def verify_lines(plan: dict, generator: dict) -> list[str]:
    """How to check a file against the release's provenance, with gh and with slsa-verifier."""
    tag, v, repo, gen = plan["tag"], plan["version"], plan["repository"], generator
    bundle = f"mavlink-m-{v}.intoto.jsonl"
    return [
        "",
        "## Verifying it",
        "",
        "Every file that `SHA256SUMS` lists, and `SHA256SUMS` itself, is covered by SLSA Build Level 3 provenance "
        "(SLSA v1.0 Build track), "
        f"generated by the SLSA project's generic generator, slsa-github-generator {gen['tag']} at commit "
        f"`{gen['commit']}`, in the SLSA Provenance v0.2 format: `{bundle}`. Check a file with gh:",
        "",
        "```sh",
        f"gh attestation verify FILE --bundle {bundle} --repo {repo} \\",
        f"  --signer-workflow {gen['workflow']} \\",
        f"  --signer-digest {gen['commit']} \\",
        f"  --source-ref refs/tags/{tag} --source-digest {plan['commit']} \\",
        "  --predicate-type https://slsa.dev/provenance/v0.2 --deny-self-hosted-runners",
        "```",
        "",
        "Offline, add `--custom-trusted-root trusted_root.jsonl`, saved earlier with "
        "`gh attestation trusted-root > trusted_root.jsonl`. With the SLSA project's verifier, online:",
        "",
        "```sh",
        f"slsa-verifier verify-artifact FILE --provenance-path {bundle} \\",
        f"  --source-uri github.com/{repo} --source-tag {tag} \\",
        f"  --builder-id https://github.com/{gen['workflow']}@refs/tags/{gen['tag']}",
        "```",
        "",
        "The provenance also records the release run's GitHub context, which includes the account that "
        "pushed the release tag; the release documentation says what it holds.",
    ]


def notes(
    plan: dict, files: dict[str, str], facts: dict | None = None, generator: dict | None = None
) -> str:
    """The notes for a release, given the plan, the release files' SHA-256 by name, the build's
    facts (the Python version, the C facts and HEARTBEAT's version from wire.json, and the line
    of military.xml's signing rule) and, where the release is signed, the generator that signs
    its provenance."""
    facts = facts or {}
    lines = [f"# MAVLink-M {plan['version']}", ""]
    if plan["mode"] != "release":
        lines += ["This is a rehearsal of the release process. Nothing of it is published.", ""]
    intro = (
        f"Release {plan['tag']} of the MAVLink-M dialect, built from commit {code(plan['commit'])}."
    )
    if plan.get("decision") and URL.fullmatch(plan["decision"]):
        intro += f" Decision: <{plan['decision']}>"
    lines.append(intro)
    since = f"since {plan['previous']['tag']}" if plan["previous"] else "in this first release"
    lines += ["", f"## Changes {since}"] + change_lines(plan)
    lines += ["", "## Wire format", ""] + wire_lines(plan)
    lines += ["", "## Files", ""] + usage_lines(plan, facts)
    lines += ["", "| File | SHA-256 |", "| --- | --- |"]
    lines += [f"| `{name}` | `{digest}` |" for name, digest in sorted(files.items())]
    lines += [
        "",
        "Check a download against `SHA256SUMS` with `sha256sum --check --ignore-missing SHA256SUMS`.",
    ]
    lines += protocol_lines(plan, facts)
    if generator:
        lines += verify_lines(plan, generator)
    lines += [
        "",
        "## Licenses",
        "",
        "Each archive carries `LICENSE`, `LICENSES/`, `REUSE.toml` and `NOTICE`. The dialect and this "
        "repository's files are under the MIT license; the generated C and Python code is under the "
        "generator's grant (`LicenseRef-MAVLink-generated-code`), whose notice must be kept in all copies or "
        "substantial portions; the MAVLink definitions it includes are under the MIT license.",
    ]
    return "\n".join(lines) + "\n"
