#!/usr/bin/env python3
"""Tests for sbom.py and release_notes.py. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_sbom.py'
"""

from __future__ import annotations

import base64
import copy
import hashlib
import json
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import release_notes  # noqa: E402
import sbom  # noqa: E402

LINE = "=" * 72
NOTICES = (
    "Third-party notices\n\nheader\n\n"
    f"{LINE}\n@scope/pkg 1.0.0 (MIT)\nnode_modules/@scope/pkg\n\n--- LICENSE\n\ntext\n\n"
    f"{LINE}\nplain 2.0.0 ((MPL-2.0 OR Apache-2.0))\nnode_modules/plain\n\n(no file)\n\n"
    f"{LINE}\nodd 3.0.0 (not declared)\nnode_modules/odd\n\n"
    f"{LINE}\nbroken line without a key\n\n"
    f"{LINE}\nInter font (bundled by the VitePress theme)\n\nOFL text\n"
)
INTEGRITY = "sha512-" + base64.b64encode(b"\x01" * 64).decode()
COMMON = b"<common/>"


def member(path: str, data: bytes, **extra) -> dict:
    return {"path": path, "sha1": hashlib.sha1(data).hexdigest(),
            "sha256": hashlib.sha256(data).hexdigest(), **extra}  # fmt: skip


def members() -> dict:
    generated = {
        "license": "LicenseRef-MAVLink-generated-code",
        "copyright": ["Copyright (C) the example project"],
    }
    return {
        "mavlink-m-1.2.3-definitions.tar.gz": [
            member("message_definitions/v1.0/common.xml", COMMON, license="MIT", copyright=["NOASSERTION"]),
            member("message_definitions/v1.0/military.xml", b"<military/>", license="MIT", copyright=["holder"]),
        ],
        "mavlink-m-1.2.3-c.tar.gz": [
            member("LICENSE", b"MIT", covered=False),
            member("common/common.h", b"c", **generated),
            member("mavlink_sha256.h", b"sha", license="BSD-3-Clause AND LicenseRef-MAVLink-generated-code",
                   copyright=["kth", "Copyright (C) the example project"]),
            member("message_definitions/common.xml", COMMON, license="MIT", copyright=["NOASSERTION"]),
            member("message_definitions/military.xml", b"<military/>", license="MIT", copyright=["holder"]),
            member("message_definitions/minimal.xml", b"<changed/>", license="MIT", copyright=["NOASSERTION"]),
            member("military/military.h", b"m", **generated),
        ],
        "mavlink-m-1.2.3-python.tar.gz": [member("military.py", b"import fastcrc", **generated)],
        "mavlink-m-1.2.3-docs.tar.gz": [member("assets/a_b.js", b"1"), member("assets/a-b.js", b"2")],
    }  # fmt: skip


def facts() -> dict:
    plan = {
        "version": "1.2.3", "tag": "v1.2.3", "repository": "Dronecode/mavlink-military", "commit": "c" * 40,
        "source_date_epoch": 1700000000, "pins": {"mavlink": "a" * 40, "pymavlink": "b" * 40},
        "generator": {"repository": "example/one", "commit": "b" * 40},
    }  # fmt: skip
    manifest = {"archives": {
        "mavlink-m-1.2.3-c.tar.gz": {"files": [
            {"path": "military/x.h", "license": "LicenseRef-MAVLink-generated-code", "copyright": ["Copyright (C) the example project"]},
            {"path": "mavlink_sha256.h", "license": "BSD-3-Clause AND LicenseRef-MAVLink-generated-code", "copyright": ["kth"]},
            {"path": "LICENSE", "covered": False},
        ]},
        "mavlink-m-1.2.3-definitions.tar.gz": {"files": [
            {"path": "message_definitions/v1.0/common.xml", "license": "MIT", "copyright": ["NOASSERTION"]},
        ]},
    }}  # fmt: skip
    files = {n: hashlib.sha256(n.encode()).hexdigest() for n in (
        "mavlink-m-1.2.3-c.tar.gz", "mavlink-m-1.2.3-definitions.tar.gz", "mavlink-m-1.2.3-python.tar.gz",
        "mavlink-m-1.2.3-military.xml", "mavlink-m-1.2.3-docs.tar.gz")}  # fmt: skip
    lock = {"packages": {
        "": {"name": "docs"},
        "node_modules/@scope/pkg": {"version": "1.0.0", "resolved": "https://registry.npmjs.org/@scope/pkg/-/pkg-1.0.0.tgz", "integrity": INTEGRITY},
        "node_modules/plain": {"version": "2.0.0", "integrity": "sha1-abc"},
    }}  # fmt: skip
    return {
        "plan": plan, "manifest": manifest, "files": files, "lock": lock, "notices": NOTICES,
        "upstream": {
            "common.xml": {"sha1": hashlib.sha1(COMMON).hexdigest(), "sha256": hashlib.sha256(COMMON).hexdigest()},
            "minimal.xml": {"sha1": "1" * 40, "sha256": "2" * 64},
        },
        "members": members(), "optional": ["fastcrc"],
        "tools": {"python": "3.12.15", "lxml": "6.1.3"}, "grant": "GRANT TEXT\n", "grant_lines": [7, 33],
        "holder": "Copyright (c) 2026 Dronecode Project, Inc", "license_list_version": "3.29",
    }  # fmt: skip


class SbomTest(unittest.TestCase):
    def setUp(self) -> None:
        self.doc = sbom.document(facts())
        self.by_id = {p["SPDXID"]: p for p in self.doc["packages"]}
        self.rel = {
            (r["spdxElementId"], r["relationshipType"], r["relatedSpdxElement"])
            for r in self.doc["relationships"]
        }

    def test_the_document_is_deterministic_spdx_2_3(self) -> None:
        self.assertEqual(
            json.dumps(sbom.document(facts()), sort_keys=True), json.dumps(self.doc, sort_keys=True)
        )
        self.assertEqual(
            (self.doc["spdxVersion"], self.doc["dataLicense"]), ("SPDX-2.3", "CC0-1.0")
        )
        self.assertEqual(self.doc["creationInfo"]["created"], "2023-11-14T22:13:20Z")
        self.assertEqual(
            self.doc["documentNamespace"],
            f"https://github.com/Dronecode/mavlink-military/releases/tag/v1.2.3#spdx-{'c' * 40}",
        )
        self.assertEqual([p["SPDXID"] for p in self.doc["packages"]], sorted(self.by_id))

    def test_the_release_and_its_files(self) -> None:
        release = self.by_id["SPDXRef-Package-mavlink-m"]
        self.assertEqual(release["supplier"], "Organization: Dronecode Project, Inc")
        self.assertEqual(
            release["externalRefs"][0]["referenceLocator"],
            "pkg:github/Dronecode/mavlink-military@v1.2.3",
        )
        c = self.by_id["SPDXRef-File-mavlink-m-1.2.3-c.tar.gz"]
        self.assertEqual(
            c["licenseConcluded"], "BSD-3-Clause AND LicenseRef-MAVLink-generated-code"
        )
        self.assertEqual(c["copyrightText"], "Copyright (C) the example project\nkth")
        self.assertEqual(c["primaryPackagePurpose"], "ARCHIVE")
        self.assertEqual(
            self.by_id["SPDXRef-File-mavlink-m-1.2.3-definitions.tar.gz"]["copyrightText"],
            "NOASSERTION",
        )
        xml = self.by_id["SPDXRef-File-mavlink-m-1.2.3-military.xml"]
        self.assertEqual((xml["licenseConcluded"], xml["primaryPackagePurpose"]), ("MIT", "FILE"))
        self.assertEqual(
            self.by_id["SPDXRef-File-mavlink-m-1.2.3-python.tar.gz"]["licenseConcluded"], "MIT"
        )
        docs = self.by_id["SPDXRef-File-mavlink-m-1.2.3-docs.tar.gz"]
        self.assertEqual(docs["licenseConcluded"], "NOASSERTION")
        self.assertIn("THIRD-PARTY-NOTICES.txt", docs["comment"])
        self.assertIn(("SPDXRef-DOCUMENT", "DESCRIBES", "SPDXRef-Package-mavlink-m"), self.rel)
        self.assertIn(
            (
                "SPDXRef-File-mavlink-m-1.2.3-c.tar.gz",
                "GENERATED_FROM",
                "SPDXRef-File-mavlink-m-1.2.3-military.xml",
            ),
            self.rel,
        )

    def test_the_upstream_definitions(self) -> None:
        self.assertEqual(
            self.by_id["SPDXRef-Package-mavlink-message-definitions"]["copyrightText"],
            "NOASSERTION",
        )
        files = {f["SPDXID"]: f for f in self.doc["files"]}
        self.assertEqual(
            files["SPDXRef-File-mavlink-minimal.xml"]["checksums"][0],
            {"algorithm": "SHA1", "checksumValue": "1" * 40},
        )
        self.assertIn(
            ("SPDXRef-Package-mavlink-message-definitions", "CONTAINS", "SPDXRef-File-mavlink-common.xml"),
            self.rel,
        )  # fmt: skip
        # Each archive's copy is a file of its archive and a copy of the upstream file.
        for copy_id in (
            "SPDXRef-File-definitions-message-definitions-v1.0-common.xml",
            "SPDXRef-File-c-message-definitions-common.xml",
        ):
            self.assertIn((copy_id, "COPY_OF", "SPDXRef-File-mavlink-common.xml"), self.rel)
        self.assertFalse(
            any(r[2] == "SPDXRef-File-mavlink-common.xml" and r[1] == "CONTAINS" and "tar.gz" in r[0]
                for r in self.rel)
        )  # fmt: skip

    def test_every_archive_member_is_a_file_of_its_archive(self) -> None:
        files = {f["SPDXID"]: f for f in self.doc["files"]}
        self.assertEqual(list(files), sorted(files))
        header = files["SPDXRef-File-c-mavlink-sha256.h"]
        self.assertEqual(header["fileName"], "./mavlink_sha256.h")
        self.assertEqual(
            header["checksums"],
            [{"algorithm": "SHA1", "checksumValue": hashlib.sha1(b"sha").hexdigest()},
             {"algorithm": "SHA256", "checksumValue": hashlib.sha256(b"sha").hexdigest()}],
        )  # fmt: skip
        self.assertEqual(
            (header["licenseConcluded"], header["licenseInfoInFiles"], header["copyrightText"]),
            ("BSD-3-Clause AND LicenseRef-MAVLink-generated-code", ["NOASSERTION"],
             "Copyright (C) the example project\nkth"),
        )  # fmt: skip
        license_file = files["SPDXRef-File-c-LICENSE"]
        self.assertEqual(
            (license_file["licenseConcluded"], license_file["comment"]), ("NOASSERTION", sbom.UNCOVERED)
        )  # fmt: skip
        self.assertEqual(files["SPDXRef-File-definitions-message-definitions-v1.0-common.xml"]["copyrightText"],
                         "NOASSERTION")  # fmt: skip
        # Two docs paths that map to one ID get a digest of the path in the second.
        docs = sorted(i for i in files if i.startswith("SPDXRef-File-docs-"))
        self.assertEqual(len(docs), 2)
        self.assertIn("SPDXRef-File-docs-assets-a-b.js", docs)
        suffix = hashlib.sha1(b"docs-assets/a-b.js").hexdigest()[:12]
        self.assertIn(f"SPDXRef-File-docs-assets-a-b.js-{suffix}", docs)
        self.assertEqual(files[docs[0]]["comment"], sbom.DOCS_FILE)
        c = self.by_id["SPDXRef-File-mavlink-m-1.2.3-c.tar.gz"]
        self.assertIs(c["filesAnalyzed"], True)
        sha1s = sorted(m["sha1"] for m in members()["mavlink-m-1.2.3-c.tar.gz"])
        self.assertEqual(
            c["packageVerificationCode"]["packageVerificationCodeValue"],
            hashlib.sha1("".join(sha1s).encode()).hexdigest(),
        )
        self.assertIs(
            self.by_id["SPDXRef-File-mavlink-m-1.2.3-military.xml"]["filesAnalyzed"], False
        )
        self.assertEqual(sbom.check_coverage(self.doc, members()), 12)

    def test_generated_files_come_from_their_definitions(self) -> None:
        military = "SPDXRef-File-definitions-message-definitions-v1.0-military.xml"
        common = "SPDXRef-File-definitions-message-definitions-v1.0-common.xml"
        self.assertIn(("SPDXRef-File-c-military-military.h", "GENERATED_FROM", military), self.rel)
        self.assertIn(("SPDXRef-File-c-common-common.h", "GENERATED_FROM", common), self.rel)
        self.assertFalse(
            any(
                r[0] == "SPDXRef-File-c-mavlink-sha256.h" and r[1] == "GENERATED_FROM"
                for r in self.rel
            )
        )
        self.assertIn(("SPDXRef-File-python-military.py", "GENERATED_FROM", military), self.rel)
        self.assertIn(("SPDXRef-File-python-military.py", "GENERATED_FROM", common), self.rel)
        # The C archive's minimal.xml differs from the upstream file, so it is no copy of it.
        self.assertFalse(any(r[0] == "SPDXRef-File-c-message-definitions-minimal.xml" for r in self.rel
                             if r[1] == "COPY_OF"))  # fmt: skip
        self.assertIn(
            (
                "SPDXRef-Package-fastcrc",
                "OPTIONAL_DEPENDENCY_OF",
                "SPDXRef-File-python-military.py",
            ),
            self.rel,
        )
        self.assertIn("pure Python", self.by_id["SPDXRef-Package-fastcrc"]["comment"])  # fmt: skip

    def test_without_the_optional_dependency_or_the_definitions(self) -> None:
        f = facts()
        f["optional"] = []
        del f["members"]["mavlink-m-1.2.3-definitions.tar.gz"]
        doc = sbom.document(f)
        self.assertNotIn("SPDXRef-Package-fastcrc", {p["SPDXID"] for p in doc["packages"]})
        self.assertFalse(any(r["relationshipType"] == "GENERATED_FROM" and r["spdxElementId"].startswith("SPDXRef-File-c-")
                             for r in doc["relationships"]))  # fmt: skip
        self.assertEqual(sbom.check_coverage(doc, f["members"]), 10)

    def test_coverage_fails_on_a_dropped_an_extra_or_a_changed_file(self) -> None:
        def dropped(doc):
            doc["files"] = [f for f in doc["files"] if f["SPDXID"] != "SPDXRef-File-c-LICENSE"]

        def extra(doc):
            doc["files"].append({"SPDXID": "SPDXRef-File-x", "fileName": "./x", "checksums": []})
            doc["relationships"].append(
                {
                    "spdxElementId": "SPDXRef-File-mavlink-m-1.2.3-c.tar.gz",
                    "relationshipType": "CONTAINS",
                    "relatedSpdxElement": "SPDXRef-File-x",
                }
            )

        def changed(doc):
            next(f for f in doc["files"] if f["SPDXID"] == "SPDXRef-File-c-LICENSE")["checksums"][
                1
            ]["checksumValue"] = ("0" * 64)

        for change in (dropped, extra, changed):
            with self.subTest(change=change.__name__):
                doc = copy.deepcopy(self.doc)
                change(doc)
                with self.assertRaises(sbom.SbomError) as caught:
                    sbom.check_coverage(doc, members())
                self.assertIn("mavlink-m-1.2.3-c.tar.gz: the SBOM lists", str(caught.exception))
        with self.assertRaises(sbom.SbomError):
            sbom.check_coverage(self.doc, {"mavlink-m-1.2.3-other.tar.gz": members()["mavlink-m-1.2.3-c.tar.gz"]})  # fmt: skip

    def test_the_creation_info_states_the_context(self) -> None:
        info = self.doc["creationInfo"]
        self.assertEqual(info["creators"][0], f"Tool: release_assemble.py-{'c' * 40}")
        self.assertIn("Generation context: build.", info["comment"])
        self.assertIn("no value is withheld", info["comment"])

    def test_the_build_tools(self) -> None:
        generator = self.by_id["SPDXRef-Package-pymavlink"]
        self.assertEqual(generator["licenseDeclared"], "NOASSERTION")
        # Where the setup action checks the generator out from, and that repository's owner.
        self.assertEqual(
            (generator["supplier"], generator["downloadLocation"], generator["externalRefs"][0]["referenceLocator"]),
            ("Organization: example", f"git+https://github.com/example/one.git@{'b' * 40}",
             f"pkg:github/example/one@{'b' * 40}"),
        )  # fmt: skip
        self.assertEqual(self.by_id["SPDXRef-Package-lxml"]["supplier"], "NOASSERTION")
        self.assertEqual(
            self.by_id["SPDXRef-Package-lxml"]["externalRefs"][0]["referenceLocator"],
            "pkg:pypi/lxml@6.1.3",
        )
        self.assertIn(
            (
                "SPDXRef-Package-CPython",
                "BUILD_TOOL_OF",
                "SPDXRef-File-mavlink-m-1.2.3-python.tar.gz",
            ),
            self.rel,
        )
        self.assertEqual(self.doc["hasExtractedLicensingInfos"][0]["extractedText"], "GRANT TEXT\n")
        self.assertIn("lines 7 to 33", self.doc["hasExtractedLicensingInfos"][0]["comment"])

    def test_the_docs_build_tools(self) -> None:
        scoped = self.by_id["SPDXRef-Package-docs-node-modules-scope-pkg"]
        self.assertEqual(
            scoped["externalRefs"][0]["referenceLocator"], "pkg:npm/%40scope/pkg@1.0.0"
        )
        self.assertEqual(scoped["checksums"], [{"algorithm": "SHA512", "checksumValue": "01" * 64}])
        plain = self.by_id["SPDXRef-Package-docs-node-modules-plain"]
        self.assertEqual(
            (plain["licenseDeclared"], plain["downloadLocation"]),
            ("(MPL-2.0 OR Apache-2.0)", "NOASSERTION"),
        )
        self.assertNotIn("checksums", plain)
        self.assertEqual(
            self.by_id["SPDXRef-Package-docs-node-modules-odd"]["licenseDeclared"], "NOASSERTION"
        )
        inter = self.by_id["SPDXRef-Package-docs-Inter"]
        self.assertEqual(
            (inter["versionInfo"], inter["licenseDeclared"]), ("NOASSERTION", "OFL-1.1")
        )
        self.assertIn(
            (
                "SPDXRef-Package-docs-Inter",
                "BUILD_TOOL_OF",
                "SPDXRef-File-mavlink-m-1.2.3-docs.tar.gz",
            ),
            self.rel,
        )
        self.assertEqual(len(sbom.installed_packages(NOTICES)), 4)

    def test_missing_files_leave_out_their_relationships(self) -> None:
        f = facts()
        f["files"] = {}
        f["holder"] = "Unknown"
        doc = sbom.document(f)
        kinds = {r["relationshipType"] for r in doc["relationships"]}
        self.assertEqual(kinds, {"DESCRIBES", "CONTAINS"})
        self.assertEqual(doc["packages"][0]["supplier"] if doc["packages"][0]["SPDXID"].endswith("mavlink-m") else
                         next(p for p in doc["packages"] if p["SPDXID"] == "SPDXRef-Package-mavlink-m")["supplier"],
                         "Organization: NOASSERTION")  # fmt: skip

    def test_helpers(self) -> None:
        self.assertEqual(sbom.spdx_id("File", "a b/c@d"), "SPDXRef-File-a-b-c-d")
        self.assertIsNone(sbom.sha512_hex(None))
        self.assertEqual(sbom.declared(None), "NOASSERTION")
        self.assertEqual(sbom.declared("MIT; or else"), "NOASSERTION")
        self.assertEqual(sbom.licenses_of([{"path": "LICENSE", "covered": False}]), "NOASSERTION")


PLAN = {
    "version": "1.1.0", "tag": "v1.1.0", "commit": "c" * 40, "mode": "release", "decision": None,
    "repository": "Dronecode/mavlink-military", "pin_notes": ["PYMAVLINK_REF is not mavlink's submodule"],
    "dialect": {"version": "4", "previous": "3", "dialect": "1", "previous_dialect": "0"},
    "previous": {"tag": "v1.0.0", "commit": "p" * 40}, "pins": {"mavlink": "a" * 40, "pymavlink": "b" * 40},
    "generator": {"commit": "b" * 40, "reports_version": "2.4.50", "release_tag": "v2.4.50", "ahead_by": 17, "behind_by": 0},
    "changes": [
        {"commit": "1" * 40, "subject": "feat(dialect): add `X` <b>@someone</b>", "change": "addition"},
        {"commit": "3" * 40, "subject": "docs(site): thank Ann <ann.b+x@mail.example.org>", "change": "other"},
        {"commit": "2" * 40, "subject": "fix(dialect)!: retype a field", "change": "breaking"},
    ],
    "policy": {"required": "minor", "breaches": [], "mismatches": ["a note"]},
    "wire": {"breaking": ["BREAKING: message 1 X: retyped"], "info": ["INFO: message 2 Y added"], "api_breaks": ["MAV_X renamed"], "verdict": "1 wire-breaking change(s)"},
    "closure": {"from": "a" * 40, "to": "d" * 40, "breaking": [], "info": ["common.xml: INFO: message 3 Z added"]},
    "generator_change": {"from": "b" * 40, "to": "e" * 40, "fixed_headers_changed": ["protocol.h"], "commits": ["x"]},
    "id_reuse": ["message 53000 was ONE in v1.0.0, is TWO"],
}  # fmt: skip


class NotesTest(unittest.TestCase):
    def test_a_release_with_everything(self) -> None:
        text = release_notes.notes(PLAN, {"b.tar.gz": "2" * 64, "a.json": "1" * 64})
        self.assertTrue(
            text.startswith("# MAVLink-M 1.1.0\n\nRelease v1.1.0 of the MAVLink-M dialect")
        )
        self.assertNotIn("rehearsal", text)
        self.assertIn("## Changes since v1.0.0", text)
        self.assertIn("- ``feat(dialect): add `X` <b>@someone</b>`` (`111111111111`)", text)
        self.assertLess(text.index("### Breaking"), text.index("### Additions"))
        self.assertIn("- `docs(site): thank Ann <[email]>` (`333333333333`)", text)
        self.assertNotIn("mail.example.org", text)
        self.assertIn("call for a minor step, and v1.1.0 takes it", text)
        self.assertIn("  - `BREAKING: message 1 X: retyped`", text)
        self.assertIn("  - `MAV_X renamed`", text)
        self.assertIn(
            "The included MAVLink definitions moved (`aaaaaaaaaaaa` to `dddddddddddd`): 0 wire-breaking, 1 for information.",
            text,
        )
        self.assertIn("fixed C headers changed: `protocol.h`.", text)
        self.assertIn(
            "- A number given another name: `message 53000 was ONE in v1.0.0, is TWO`", text
        )
        self.assertIn("- Note: a note", text)
        self.assertIn("(it reports 2.4.50, 17 commit(s) after v2.4.50)", text)
        self.assertLess(text.index("| `a.json` |"), text.index("| `b.tar.gz` |"))
        self.assertIn(
            "military.xml's `<version>` changes from `3` to `4`, so the C `MAVLINK_VERSION`", text
        )
        self.assertIn(
            "military.xml's `<dialect>` changes; it has no effect on the generated code.", text
        )
        self.assertIn("- Note: PYMAVLINK_REF is not mavlink's submodule", text)
        self.assertIn(
            "also at <https://raw.githubusercontent.com/Dronecode/mavlink-military/v1.1.0/military.xml>",
            text,
        )
        self.assertIn("Their `MAVLINK_BUILD_DATE` is the release commit's date", text)
        self.assertNotIn("## Protocol", text)

    def test_the_protocol_facts(self) -> None:
        c = {
            "MAVLINK_VERSION": 4,
            "sizeof_mavlink_message_t": 298,
            "MAVLINK_MAX_PACKET_LEN": 287,
            "id32_flags": True,
        }
        facts = {"python": "3.12.15", "c": c, "heartbeat_mavlink_version": 3}
        text = release_notes.notes(PLAN, {}, facts)
        self.assertIn("2.4.50), on Python 3.12.15.", text)
        self.assertIn("## Protocol\n\n- MAVLink 2 only.", text)
        self.assertIn(
            "`MAVLINK_VERSION` is 4, `sizeof(mavlink_message_t)` is 298 bytes and "
            "`MAVLINK_MAX_PACKET_LEN` is 287; HEARTBEAT's `mavlink_version` on the wire is 3",
            text,
        )
        self.assertIn(
            "32-bit system IDs through the `SYSID32` and `TARGET32` incompatibility flags", text
        )
        self.assertLess(text.index("## Protocol"), text.index("## Licenses"))
        self.assertNotIn("Message signing", text)
        # The notes link the dialect's signing rule where military.xml states it.
        signed = release_notes.notes(PLAN, {}, {**facts, "signing_rule": 229})
        self.assertIn(
            "- MAVLink 2 only.\n- Message signing: the dialect's rule is in `military.xml`, under "
            "SAFETY BOUNDARIES: <https://github.com/Dronecode/mavlink-military/blob/v1.1.0/military.xml#L229>.\n",
            signed,
        )
        rule = "  SAFETY BOUNDARIES (normative)\n    - Message signing. Every system signs.\n"
        self.assertEqual(release_notes.signing_rule("<mavlink>\n<!--\n" + rule), 4)
        self.assertIsNone(
            release_notes.signing_rule("    - Message signing. Not under the heading.\n")
        )
        self.assertIsNone(
            release_notes.signing_rule("  SAFETY BOUNDARIES\n    - Replay protection.\n")
        )
        military = (Path(__file__).resolve().parents[4] / "military.xml").read_text(
            encoding="utf-8"
        )
        self.assertIsNotNone(release_notes.signing_rule(military))
        without = release_notes.notes(PLAN, {}, dict(facts, c=dict(c, id32_flags=False)))
        self.assertIn("## Protocol", without)
        self.assertNotIn("SYSID32", without)  # fmt: skip

    def test_a_rehearsal_of_a_first_release(self) -> None:
        plan = copy.deepcopy(PLAN)
        plan.update(mode="rehearsal", previous=None, changes=[], decision="https://example.org/d/1",
                    generator={"commit": "b" * 40, "reports_version": None}, pin_notes=[],
                    dialect={"version": "4", "previous": None, "dialect": "1", "previous_dialect": None})  # fmt: skip
        text = release_notes.notes(plan, {})
        self.assertIn(
            "This is a rehearsal of the release process. Nothing of it is published.", text
        )
        self.assertIn("## Changes in this first release\n\nNo commits.", text)
        self.assertIn("This is the first release", text)
        self.assertIn("Decision: <https://example.org/d/1>", text)
        self.assertIn(f"Generated by pymavlink at `{'b' * 40}`.", text)

    def test_a_decision_that_is_no_plain_url_is_left_out(self) -> None:
        plan = copy.deepcopy(PLAN)
        plan.update(decision="javascript:alert(1)", closure=None, generator_change=None)
        plan["dialect"] = {
            "version": "3",
            "previous": "3",
            "dialect": "0",
        }  # a plan without previous_dialect
        plan["policy"]["required"] = None
        text = release_notes.notes(plan, {})
        self.assertNotIn("Decision", text)
        self.assertNotIn("`<version>`", text)
        self.assertNotIn("`<dialect>`", text)
        self.assertIn("call for a patch step", text)
        self.assertNotIn("definitions moved", text)

    def test_a_signed_release_says_how_to_verify_it(self) -> None:
        generator = {"workflow": "slsa-framework/slsa-github-generator/.github/workflows/generator_generic_slsa3.yml",
                     "tag": "v2.1.0", "commit": "f" * 40}  # fmt: skip
        plan = dict(PLAN, repository="Dronecode/mavlink-military")
        text = release_notes.notes(plan, {}, generator=generator)
        self.assertIn("## Verifying it", text)
        self.assertIn("slsa-github-generator v2.1.0 at commit `" + "f" * 40 + "`", text)
        self.assertIn(
            "gh attestation verify FILE --bundle mavlink-m-1.1.0.intoto.jsonl --repo Dronecode/mavlink-military \\\n",
            text,
        )
        self.assertIn(f"  --source-ref refs/tags/v1.1.0 --source-digest {'c' * 40} \\\n", text)
        self.assertIn(
            "--builder-id https://github.com/slsa-framework/slsa-github-generator/.github/workflows/generator_generic_slsa3.yml@refs/tags/v2.1.0",
            text,
        )
        self.assertIn("includes the account that pushed the release tag", text)
        self.assertNotIn("## Verifying it", release_notes.notes(plan, {}))

    def test_code_spans(self) -> None:
        self.assertEqual(release_notes.code("plain"), "`plain`")
        self.assertEqual(release_notes.code("a `b` c"), "``a `b` c``")
        self.assertEqual(release_notes.code("`edge`"), "`` `edge` ``")
        self.assertEqual(release_notes.code(" "), "`   `")


if __name__ == "__main__":
    unittest.main()
