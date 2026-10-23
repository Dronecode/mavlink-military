#!/usr/bin/env python3
"""The release's SBOM, an SPDX 2.3 JSON document, from facts the build records.

document() is a pure function of its inputs, so the same release gives the same
bytes: created is the release commit's time, the namespace is derived from the
repository, version and commit, and every list is sorted. It describes:

- the release itself, with its purl and its download location at the tag;
- each release file as a package of its own, with its SHA-256 and the
  licenses of what it holds (from the package manifest);
- every member of every archive as a file of its archive, with its SHA-1 and
  SHA-256 and, for the package archives, the license and copyright the
  manifest gives it; each generated file is GENERATED_FROM the definitions
  file it comes from, and each copy of an upstream file is a COPY_OF it;
- the MAVLink message definitions at MAVLINK_REF, as a package whose three
  files the definitions and C archives contain unchanged, declared MIT on
  the MAVLink project's statement, copyright NOASSERTION because the files
  carry no notice;
- the generator (pymavlink at PYMAVLINK_REF), lxml and CPython as build tools
  of the generated archives; the generator is not shipped;
- every npm package installed for the docs build, and the Inter font, as
  build tools of the docs archive, from that archive's third-party notices,
  with the integrity hash and the download location the docs lockfile records;
- fastcrc as an optional dependency of military.py, when the module imports it;
- the generator grant as the extracted licence text of
  LicenseRef-MAVLink-generated-code.

What is not known is written NOASSERTION: creationInfo.comment says that it
marks a value the build does not determine and that nothing is withheld, and
each package that has one says why in its comment. check_coverage() fails
unless every archive member appears exactly once, with its digests.
"""

from __future__ import annotations

import base64
import hashlib
import re
from datetime import datetime, timezone

SECTION = "=" * 72
LICENSE_EXPRESSION = re.compile(r"[A-Za-z0-9.+\-() ]+")
NOTICE_HEAD = re.compile(r"(\S+) (\S+) \((.+)\)")
GENERATED_CODE = "LicenseRef-MAVLink-generated-code"
KINDS = ("definitions", "c", "python", "docs")
# The C headers of each definitions file go to a directory named after it.
GENERATED_DIRS = {
    f"{n}/": f"message_definitions/v1.0/{n}.xml"
    for n in ("military", "common", "standard", "minimal")
}
CONTEXT = (
    "Generation context: build. The release workflow writes this document from the build's own records. "
    "NOASSERTION marks a value this build does not determine; no value is withheld. licenseInfoInFiles is "
    "NOASSERTION because the build does not scan file text for license notices: each archive's REUSE.toml "
    "and each file's licenseConcluded give its license."
)
UNCOVERED = "A license text or licensing metadata file, which REUSE does not license itself."
DOCS_FILE = (
    "A page or asset of the built site: the pages are under the repository's MIT license, and code bundled "
    "from npm packages is under their licenses, listed in THIRD-PARTY-NOTICES.txt; the build does not "
    "conclude a license per file."
)


class SbomError(Exception):
    """The SBOM does not describe the archives exactly."""


def spdx_id(kind: str, name: str) -> str:
    return f"SPDXRef-{kind}-" + re.sub(r"[^A-Za-z0-9.-]+", "-", name).strip("-")


def unique_id(kind: str, name: str, used: set[str]) -> str:
    """spdx_id, made unique with a digest of the name when another name maps to the same ID."""
    found = spdx_id(kind, name)
    if found in used:
        found = f"{found}-{hashlib.sha1(name.encode('utf-8')).hexdigest()[:12]}"
    used.add(found)
    return found


def archive_kind(name: str, version: str) -> str | None:
    return next((k for k in KINDS if name == f"mavlink-m-{version}-{k}.tar.gz"), None)


def verification_code(sha1s: list[str]) -> str:
    """SPDX 2.3 clause 7.9: the SHA-1 of the files' SHA-1 values, sorted and concatenated."""
    return hashlib.sha1("".join(sorted(sha1s)).encode("ascii")).hexdigest()


def iso(epoch: int) -> str:
    return datetime.fromtimestamp(epoch, timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def npm_purl(name: str, version: str) -> str:
    return f"pkg:npm/{name.replace('@', '%40', 1) if name.startswith('@') else name}@{version}"


def installed_packages(notices: str) -> list[dict]:
    """The npm packages and the font that the docs archive's notices list."""
    found = []
    for section in notices.split(f"\n{SECTION}\n")[1:]:
        lines = section.split("\n")
        head = NOTICE_HEAD.fullmatch(lines[0])
        if head and len(lines) > 1 and lines[1].startswith("node_modules/"):
            found.append(
                {
                    "name": head.group(1),
                    "version": head.group(2),
                    "license": head.group(3),
                    "key": lines[1],
                }
            )
        elif lines[0].startswith("Inter font"):
            found.append({"name": "Inter", "version": None, "license": "OFL-1.1", "key": None})
    return found


def declared(license_text: str | None) -> str:
    if (
        license_text
        and LICENSE_EXPRESSION.fullmatch(license_text)
        and license_text != "not declared"
    ):
        return license_text
    return "NOASSERTION"


def sha512_hex(integrity: str | None) -> str | None:
    if integrity and integrity.startswith("sha512-"):
        return base64.b64decode(integrity[len("sha512-") :]).hex()
    return None


def licenses_of(entries: list[dict]) -> str:
    ids = sorted({part for e in entries if "license" in e for part in e["license"].split(" AND ")})
    return " AND ".join(ids) if ids else "NOASSERTION"


def copyrights_of(entries: list[dict]) -> str:
    lines = sorted({c for e in entries for c in e.get("copyright", []) if c != "NOASSERTION"})
    return "\n".join(lines) if lines else "NOASSERTION"


def member_file(fid: str, kind: str, entry: dict) -> dict:
    """An archive member as an SPDX file: its digests, and the manifest's license and copyright."""
    lines = [c for c in entry.get("copyright", []) if c != "NOASSERTION"]
    found = {
        "SPDXID": fid,
        "fileName": f"./{entry['path']}",
        "checksums": [{"algorithm": "SHA1", "checksumValue": entry["sha1"]},
                      {"algorithm": "SHA256", "checksumValue": entry["sha256"]}],
        "licenseConcluded": entry.get("license", "NOASSERTION"),
        "licenseInfoInFiles": ["NOASSERTION"],
        "copyrightText": "\n".join(sorted(lines)) if lines else "NOASSERTION",
    }  # fmt: skip
    if kind == "docs":
        found["comment"] = DOCS_FILE
    elif entry.get("covered") is False:
        found["comment"] = UNCOVERED
    return found


def check_coverage(doc: dict, members: dict[str, list[dict]]) -> int:
    """Every archive member appears exactly once among its archive's files, with its SHA-1 and
    SHA-256, and the archive holds no file the document does not list; the number checked."""
    names = {p["SPDXID"]: p["name"] for p in doc["packages"]}
    files = {f["SPDXID"]: f for f in doc["files"]}
    held: dict[str, list[tuple]] = {}
    for r in doc["relationships"]:
        if r["relationshipType"] == "CONTAINS" and r["relatedSpdxElement"] in files:
            f = files[r["relatedSpdxElement"]]
            sums = {c["algorithm"]: c["checksumValue"] for c in f["checksums"]}
            held.setdefault(names.get(r["spdxElementId"], ""), []).append(
                (f["fileName"], sums.get("SHA1"), sums.get("SHA256"))
            )
    for name, entries in members.items():
        want = sorted((f"./{e['path']}", e["sha1"], e["sha256"]) for e in entries)
        have = sorted(held.get(name, []))
        if have != want:
            missing = sorted(set(want) - set(have))[:3]
            extra = sorted(set(have) - set(want))[:3]
            raise SbomError(
                f"{name}: the SBOM lists {len(have)} files for {len(want)} members "
                f"(missing or changed {missing}, not in the archive {extra})"
            )
    return sum(len(e) for e in members.values())


def document(facts: dict) -> dict:
    """facts: plan, manifest, files (name: sha256), lock (docs package-lock.json),
    notices (the docs archive's THIRD-PARTY-NOTICES.txt), upstream (name:
    {sha1, sha256}), tools (python, lxml), grant and grant_lines (its text and
    lines in the generator's COPYING), holder, license_list_version, and
    optionally members (archive name: its members, each with path, sha1,
    sha256 and the manifest's license, copyright and covered) and optional (the
    optional dependencies military.py imports)."""
    plan, version, tag = facts["plan"], facts["plan"]["version"], facts["plan"]["tag"]
    repo, commit = plan["repository"], plan["commit"]
    owner = facts["holder"].split(" ", 3)[-1] if facts["holder"].count(" ") >= 3 else "NOASSERTION"
    release_id = spdx_id("Package", "mavlink-m")
    packages = [{
        "SPDXID": release_id, "name": "mavlink-m", "versionInfo": version,
        "supplier": f"Organization: {owner}", "downloadLocation": f"git+https://github.com/{repo}.git@{tag}",
        "filesAnalyzed": False, "licenseConcluded": "MIT", "licenseDeclared": "MIT",
        "copyrightText": facts["holder"], "primaryPackagePurpose": "SOURCE",
        "externalRefs": [{"referenceCategory": "PACKAGE-MANAGER", "referenceType": "purl",
                          "referenceLocator": f"pkg:github/{repo}@{tag}"}],
        "comment": f"Release {tag} of the MAVLink-M dialect, from commit {commit}.",
    }]  # fmt: skip
    relationships = [("SPDXRef-DOCUMENT", "DESCRIBES", release_id)]
    archives = facts["manifest"]["archives"]
    members = facts.get("members", {})
    used = {release_id} | {spdx_id("File", n) for n in facts["files"]}
    used |= {spdx_id("File", f"mavlink-{n}") for n in facts["upstream"]}
    file_ids, files, member_ids, member_entries = {}, [], {}, {}
    for name, digest in sorted(facts["files"].items()):
        entries = archives.get(name, {}).get("files", [])
        pid = spdx_id("File", name)
        file_ids[name] = pid
        concluded, copyright_text = (
            (licenses_of(entries), copyrights_of(entries)) if entries else ("MIT", facts["holder"])
        )
        comment = None
        if name.endswith("-docs.tar.gz"):
            concluded, copyright_text = "NOASSERTION", "NOASSERTION"
            comment = ("The pages are under the repository's MIT license; the code bundled from the npm "
                       "packages below is under their licenses, listed in THIRD-PARTY-NOTICES.txt inside the archive.")  # fmt: skip
        package = {
            "SPDXID": pid, "name": name, "versionInfo": version, "supplier": f"Organization: {owner}",
            "downloadLocation": f"https://github.com/{repo}/releases/download/{tag}/{name}",
            "filesAnalyzed": False, "checksums": [{"algorithm": "SHA256", "checksumValue": digest}],
            "licenseConcluded": concluded, "licenseDeclared": "NOASSERTION", "copyrightText": copyright_text,
            "primaryPackagePurpose": "ARCHIVE" if name.endswith(".tar.gz") else "FILE",
        }  # fmt: skip
        if comment:
            package["comment"] = comment
        kind = archive_kind(name, version)
        if kind and name in members:
            package.update(
                filesAnalyzed=True,
                packageVerificationCode={
                    "packageVerificationCodeValue": verification_code(
                        [e["sha1"] for e in members[name]]
                    )
                },
                licenseInfoFromFiles=["NOASSERTION"],
            )
            for entry in members[name]:
                fid = unique_id("File", f"{kind}-{entry['path']}", used)
                member_ids[(kind, entry["path"])] = fid
                member_entries[(kind, entry["path"])] = entry
                files.append(member_file(fid, kind, entry))
                relationships.append((pid, "CONTAINS", fid))
        packages.append(package)
        relationships.append((release_id, "CONTAINS", pid))
    mavlink = plan["pins"]["mavlink"]
    defs_id = spdx_id("Package", "mavlink-message-definitions")
    packages.append({
        "SPDXID": defs_id, "name": "mavlink message definitions", "versionInfo": mavlink,
        "supplier": "Organization: MAVLink", "downloadLocation": f"git+https://github.com/mavlink/mavlink.git@{mavlink}",
        "filesAnalyzed": False, "licenseConcluded": "MIT", "licenseDeclared": "MIT", "copyrightText": "NOASSERTION",
        "externalRefs": [{"referenceCategory": "PACKAGE-MANAGER", "referenceType": "purl",
                          "referenceLocator": f"pkg:github/mavlink/mavlink@{mavlink}"}],
        "comment": "common.xml, standard.xml and minimal.xml, unchanged. Declared MIT on the MAVLink project's "
                   "statement that its message definitions are under the MIT license; the files carry no "
                   "copyright notice, so the copyright is unknown, not withheld.",
    })  # fmt: skip
    for name, digests in sorted(facts["upstream"].items()):
        fid = spdx_id("File", f"mavlink-{name}")
        files.append({
            "SPDXID": fid, "fileName": f"./message_definitions/v1.0/{name}",
            "checksums": [{"algorithm": "SHA1", "checksumValue": digests["sha1"]},
                          {"algorithm": "SHA256", "checksumValue": digests["sha256"]}],
            "licenseConcluded": "MIT", "licenseInfoInFiles": ["NOASSERTION"], "copyrightText": "NOASSERTION",
        })  # fmt: skip
        relationships.append((defs_id, "CONTAINS", fid))
        for kind, path in (
            ("definitions", f"message_definitions/v1.0/{name}"),
            ("c", f"message_definitions/{name}"),
        ):
            entry = member_entries.get((kind, path))
            if entry and entry["sha256"] == digests["sha256"]:
                relationships.append((member_ids[(kind, path)], "COPY_OF", fid))
    sources = {path: member_ids.get(("definitions", path)) for path in GENERATED_DIRS.values()}
    for (kind, path), fid in sorted(member_ids.items()):
        if kind == "c":
            source = next(
                (sources[s] for d, s in GENERATED_DIRS.items() if path.startswith(d)), None
            )
            relationships += [(fid, "GENERATED_FROM", source)] if source else []
        elif kind == "python" and path == "military.py":
            relationships += [(fid, "GENERATED_FROM", s) for s in sources.values() if s]
            if "fastcrc" in facts.get("optional", []):
                packages.append({
                    "SPDXID": "SPDXRef-Package-fastcrc", "name": "fastcrc", "versionInfo": "NOASSERTION",
                    "supplier": "NOASSERTION", "downloadLocation": "https://pypi.org/project/fastcrc/",
                    "filesAnalyzed": False, "licenseConcluded": "NOASSERTION", "licenseDeclared": "NOASSERTION",
                    "copyrightText": "NOASSERTION",
                    "externalRefs": [{"referenceCategory": "PACKAGE-MANAGER", "referenceType": "purl",
                                      "referenceLocator": "pkg:pypi/fastcrc"}],
                    "comment": "Optional and not shipped: military.py computes its CRC with fastcrc when it is "
                               "installed, in any version, and in pure Python otherwise.",
                })  # fmt: skip
                relationships.append(("SPDXRef-Package-fastcrc", "OPTIONAL_DEPENDENCY_OF", fid))
    generated = [
        file_ids[n]
        for n in (f"mavlink-m-{version}-c.tar.gz", f"mavlink-m-{version}-python.tar.gz")
        if n in file_ids
    ]
    source = file_ids.get(f"mavlink-m-{version}-military.xml")
    if source:
        relationships += [(target, "GENERATED_FROM", source) for target in generated]
    pymavlink = plan["pins"]["pymavlink"]
    # The repository the setup action checks the generator out from, and its owner.
    generator = plan["generator"]["repository"]
    tools = [
        ("pymavlink", pymavlink, f"Organization: {generator.split('/')[0]}",
         f"git+https://github.com/{generator}.git@{pymavlink}", f"pkg:github/{generator}@{pymavlink}", "NOASSERTION",
         "The generator, at PYMAVLINK_REF. Its COPYING says (L)GPL v3 without saying whether later versions "
         "apply, so the declared license is NOASSERTION. It is not shipped; its grant covers the generated code."),
        ("lxml", facts["tools"]["lxml"], "NOASSERTION", "https://pypi.org/project/lxml/",
         f"pkg:pypi/lxml@{facts['tools']['lxml']}", "BSD-3-Clause",
         "Schema validation of the definitions during generation, from the hash-locked build requirements."),
        ("CPython", facts["tools"]["python"], "NOASSERTION", "https://www.python.org/",
         f"pkg:generic/cpython@{facts['tools']['python']}", "PSF-2.0", "The interpreter that ran the generator."),
    ]  # fmt: skip
    for name, tool_version, supplier, location, purl, license_id, comment in tools:
        tid = spdx_id("Package", name)
        packages.append({
            "SPDXID": tid, "name": name, "versionInfo": tool_version, "supplier": supplier,
            "downloadLocation": location, "filesAnalyzed": False, "licenseConcluded": "NOASSERTION",
            "licenseDeclared": license_id, "copyrightText": "NOASSERTION", "comment": comment,
            "externalRefs": [{"referenceCategory": "PACKAGE-MANAGER", "referenceType": "purl", "referenceLocator": purl}],
        })  # fmt: skip
        relationships += [(tid, "BUILD_TOOL_OF", target) for target in generated]
    docs = file_ids.get(f"mavlink-m-{version}-docs.tar.gz")
    lock = facts["lock"].get("packages", {})
    for item in installed_packages(facts["notices"]):
        entry = lock.get(item["key"], {}) if item["key"] else {}
        pid = spdx_id("Package", f"docs-{item['key'] or item['name']}")
        package = {
            "SPDXID": pid, "name": item["name"], "versionInfo": item["version"] or "NOASSERTION",
            "supplier": "NOASSERTION", "downloadLocation": entry.get("resolved", "NOASSERTION"),
            "filesAnalyzed": False, "licenseConcluded": "NOASSERTION", "licenseDeclared": declared(item["license"]),
            "copyrightText": "NOASSERTION",
        }  # fmt: skip
        digest = sha512_hex(entry.get("integrity"))
        if digest:
            package["checksums"] = [{"algorithm": "SHA512", "checksumValue": digest}]
        if item["key"]:
            package["externalRefs"] = [{"referenceCategory": "PACKAGE-MANAGER", "referenceType": "purl",
                                        "referenceLocator": npm_purl(item["name"], item["version"])}]  # fmt: skip
        else:
            package["comment"] = (
                "The font the docs theme bundles; its license text is in the archive's notices."
            )
        packages.append(package)
        if docs:
            relationships.append((pid, "BUILD_TOOL_OF", docs))
    return {
        "spdxVersion": "SPDX-2.3",
        "dataLicense": "CC0-1.0",
        "SPDXID": "SPDXRef-DOCUMENT",
        "name": f"mavlink-m-{version}",
        "documentNamespace": f"https://github.com/{repo}/releases/tag/{tag}#spdx-{commit}",
        "creationInfo": {
            "created": iso(plan["source_date_epoch"]),
            "creators": [f"Tool: release_assemble.py-{commit}", f"Organization: {owner}"],
            "licenseListVersion": facts["license_list_version"],
            "comment": CONTEXT,
        },
        "packages": sorted(packages, key=lambda p: p["SPDXID"]),
        "files": sorted(files, key=lambda f: f["SPDXID"]),
        "hasExtractedLicensingInfos": [{
            "licenseId": GENERATED_CODE, "name": "MAVLink generated code", "extractedText": facts["grant"],
            "comment": f"pymavlink COPYING lines {facts['grant_lines'][0]} to {facts['grant_lines'][1]} at "
                       f"{pymavlink}, verbatim: the generator's grant for its output.",
        }],  # fmt: skip
        "relationships": [
            {"spdxElementId": a, "relationshipType": kind, "relatedSpdxElement": b}
            for a, kind, b in sorted(set(relationships))
        ],
    }
