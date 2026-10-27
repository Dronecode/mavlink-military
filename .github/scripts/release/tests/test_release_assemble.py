#!/usr/bin/env python3
"""Tests for release_assemble.py, osv.py and release_commit_checks.py, on a
small synthetic release. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_release_assemble.py'
"""

from __future__ import annotations

import base64
import contextlib
import hashlib
import io
import json
import os
import runpy
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
import archive  # noqa: E402
import osv  # noqa: E402
import release_assemble as ra  # noqa: E402
import release_commit_checks as rcc  # noqa: E402

V = "1.2.3"
NEEDS = {name: {"result": "success"} for name in ra.NEEDED}
LINE = "=" * 72
NOTICES = f"Notices\n\n{LINE}\npkg 1.0.0 (MIT)\nnode_modules/pkg\n\ntext\n"
HOLDER = ["Copyright (c) 2026 Example Project"]
C_FACTS = {
    "MAVLINK_VERSION": 3,
    "sizeof_mavlink_message_t": 298,
    "MAVLINK_MAX_PACKET_LEN": 287,
    "id32_flags": True,
}
MILITARY = b"<mavlink>\n  <!--\n  SAFETY BOUNDARIES\n    - Message signing. Every system signs.\n  -->\n</mavlink>\n"
CONTENTS = {
    "definitions": {**{f"message_definitions/v1.0/{n}": f"<{n}/>".encode()
                       for n in ("common.xml", "minimal.xml", "standard.xml")},
                    "message_definitions/v1.0/military.xml": MILITARY},
    "c": {"LICENSES/LicenseRef-MAVLink-generated-code.txt": b"GRANT\n", "military/military.h": b"// h\n",
          "message_definitions/common.xml": b"<common.xml/>"},
    "python": {"LICENSE": b"MIT\n", "military.py": b"try:\n    import fastcrc\nexcept Exception:\n    pass\n"},
}  # fmt: skip


def manifest_of(contents: dict[str, dict[str, bytes]]) -> dict:
    """The package manifest's archive entries for the given archive contents."""
    archives = {}
    for kind, files in contents.items():
        archives[f"mavlink-m-{V}-{kind}.tar.gz"] = {"files": [
            {"path": p, "sha256": hashlib.sha256(d).hexdigest(), "size": len(d),
             **({"covered": False} if p.startswith("LICENSE") else {"license": "MIT", "copyright": HOLDER})}
            for p, d in sorted(files.items())
        ]}  # fmt: skip
    return {"archives": archives}


def git(cwd: Path, *args: str) -> str:
    return subprocess.run(
        ["git", "-c", "user.name=T", "-c", "user.email=t@example.invalid", *args],
        cwd=cwd, check=True, capture_output=True, text=True,
    ).stdout.strip()  # fmt: skip


def answer_none(url: str, body: dict) -> dict:
    return {"results": [{} for _ in body["queries"]]}


class AssembleCase(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)
        self.repo = self.tmp / "repo"
        (self.repo / "docs").mkdir(parents=True)
        (self.repo / "LICENSE").write_text("MIT License\n\nCopyright (c) 2026 Example Project\n")
        (self.repo / "docs" / "package-lock.json").write_text(
            json.dumps({"packages": {"node_modules/pkg": {"version": "1.0.0"}}})
        )
        git(self.repo, "init", "-q")
        git(self.repo, "add", ".")
        git(self.repo, "commit", "-q", "-m", "fixture")
        commit = git(self.repo, "rev-parse", "HEAD")
        self.plan = {
            "schema": 1, "version": V, "tag": f"v{V}", "commit": commit, "tree": "t" * 40, "mode": "rehearsal",
            "repository": "example/mavlink-military", "source_date_epoch": 1700000000, "decision": None,
            "pins": {"mavlink": "a" * 40, "pymavlink": "b" * 40}, "previous": None,
            "generator": {"repository": "example/one", "commit": "b" * 40, "reports_version": None},
            "changes": [{"commit": "1" * 40, "subject": "feat(x): y", "change": "addition", "signed_off": True,
                         "assisted_by": ["Tool:model"]},
                        {"commit": "2" * 40, "subject": "fix(x): z", "change": "other", "signed_off": False,
                         "assisted_by": []}],
            "dialect": {"version": "3", "previous": None, "dialect": "0", "previous_dialect": None},
            "pin_notes": [],
            "policy": {"required": None, "breaches": [], "mismatches": []},
            "wire": None, "closure": None, "generator_change": None, "id_reuse": [],
        }  # fmt: skip
        self.a, self.b = self.leg("a"), self.leg("b")
        self.docs = self.tmp / "docs"
        self.docs.mkdir()
        (self.docs / "index.html").write_text("<html></html>")
        (self.docs / "assets").mkdir()
        (self.docs / "assets" / "app.js").write_text("// app\n")
        (self.docs / "version.json").write_text(json.dumps({"version": f"v{V}", "commit": commit}))
        (self.docs / "THIRD-PARTY-NOTICES.txt").write_text(NOTICES)
        self.records = self.tmp / "records"
        self.records.mkdir()
        for name in ra.RECORDS:
            (self.records / name).write_text("{}")
        self.out = self.tmp / "out"

    def leg(self, name: str, manifest: dict | None = None) -> Path:
        leg = self.tmp / f"build-{name}"
        (leg / "leg").mkdir(parents=True)
        for kind, files in CONTENTS.items():
            archive.write(
                leg / f"mavlink-m-{V}-{kind}.tar.gz", f"mavlink-m-{V}-{kind}", files, 1700000000
            )
        (leg / f"mavlink-m-{V}-military.xml").write_bytes(
            CONTENTS["definitions"]["message_definitions/v1.0/military.xml"]
        )
        (leg / f"mavlink-m-{V}-wire.json").write_text(
            json.dumps({"c": C_FACTS, "heartbeat_mavlink_version": 3})
        )
        (leg / f"mavlink-m-{V}-manifest.json").write_text(
            json.dumps(manifest or manifest_of(CONTENTS))
        )
        self.sums(leg)  # fmt: skip
        (leg / "leg" / "checks.json").write_text('{"crc_rows": 1, "python_classes": 1}')
        (leg / "leg" / "toolchain.json").write_text(
            json.dumps({"python": "3.12.15", "lxml": "6.1.3", "leg": name})
        )
        return leg

    @staticmethod
    def sums(leg: Path) -> None:
        names = sorted(p.name for p in leg.iterdir() if p.is_file() and p.name != "SHA256SUMS")
        (leg / "SHA256SUMS").write_text(
            "".join(f"{hashlib.sha256((leg / n).read_bytes()).hexdigest()}  {n}\n" for n in names)
        )

    def paths(self) -> dict:
        return {
            "a": self.a,
            "b": self.b,
            "docs": self.docs,
            "records": self.records,
            "out": self.out,
        }

    def assemble(self, env: dict | None = None, send=answer_none) -> dict:
        cwd = os.getcwd()
        os.chdir(self.repo)
        try:
            return ra.assemble(
                self.paths(), self.plan, {"NEEDS_JSON": json.dumps(NEEDS), **(env or {})}, send=send
            )
        finally:
            os.chdir(cwd)

    def refused(self, message: str, env: dict | None = None, send=answer_none) -> None:
        with self.assertRaises((ra.AssembleError, osv.OsvError)) as caught:
            self.assemble(env, send)
        self.assertIn(message, str(caught.exception))


class AssembleTest(AssembleCase):
    def test_a_release_is_assembled(self) -> None:
        env = {
            "GITHUB_SERVER_URL": "https://github.com",
            "GITHUB_REPOSITORY": "example/mavlink-military",
            "GITHUB_RUN_ID": "9",
        }
        result = self.assemble(env)
        names = sorted(p.name for p in self.out.iterdir())
        self.assertEqual(names, sorted([
            f"mavlink-m-{V}-c.tar.gz", f"mavlink-m-{V}-definitions.tar.gz", f"mavlink-m-{V}-docs.tar.gz",
            f"mavlink-m-{V}-evidence.tar.gz", f"mavlink-m-{V}-manifest.json", f"mavlink-m-{V}-notes.md",
            f"mavlink-m-{V}-python.tar.gz", f"mavlink-m-{V}-military.xml", f"mavlink-m-{V}-wire.json",
            f"mavlink-m-{V}.spdx.json", "SHA256SUMS"]))  # fmt: skip
        sums = (self.out / "SHA256SUMS").read_text()
        self.assertEqual(sums.splitlines(), sorted(sums.splitlines(), key=lambda line: line[66:]))
        subjects = base64.b64decode(result["subjects"]).decode()
        self.assertEqual(
            subjects, sums + f"{hashlib.sha256(sums.encode()).hexdigest()}  SHA256SUMS\n"
        )
        self.assertEqual(result["subjects_sha256"], hashlib.sha256(subjects.encode()).hexdigest())
        docs = archive.read(self.out / f"mavlink-m-{V}-docs.tar.gz", f"mavlink-m-{V}-docs")
        self.assertEqual(
            sorted(docs), ["THIRD-PARTY-NOTICES.txt", "assets/app.js", "index.html", "version.json"]
        )
        evidence = archive.read(
            self.out / f"mavlink-m-{V}-evidence.tar.gz", f"mavlink-m-{V}-evidence"
        )
        index = json.loads(evidence["evidence.json"])
        self.assertEqual(index["jobs"], {name: "success" for name in ra.NEEDED})
        self.assertEqual(
            index["run"]["url"], "https://github.com/example/mavlink-military/actions/runs/9"
        )
        self.assertEqual(
            index["inbound"],
            {"changes": 2, "signed_off": 1, "assisted_by": {"Tool:model": 1}, "assisted_none": 1,
             "marked_breaking": 0},
        )  # fmt: skip
        self.assertEqual(index["reproducibility"]["files"], 6)
        self.assertNotIn(f"mavlink-m-{V}-evidence.tar.gz", index["files"])
        self.assertIn(f"mavlink-m-{V}-notes.md", index["files"])
        self.assertIn("records/zizmor.sarif", index["records"])
        self.assertEqual(json.loads(evidence["build-b/toolchain.json"])["leg"], "b")
        sbom = json.loads((self.out / f"mavlink-m-{V}.spdx.json").read_text())
        self.assertEqual(sbom["hasExtractedLicensingInfos"][0]["extractedText"], "GRANT\n")
        # every member of the four archives is a file: 4 + 3 + 2 package members and 4 docs files
        self.assertEqual(
            len([f for f in sbom["files"] if not f["SPDXID"].startswith("SPDXRef-File-mavlink-")]),
            13,
        )
        self.assertIn("SPDXRef-Package-fastcrc", {p["SPDXID"] for p in sbom["packages"]})
        notes = (self.out / f"mavlink-m-{V}-notes.md").read_text()
        self.assertIn("This is a rehearsal", notes)
        self.assertIn(
            "`MAVLINK_MAX_PACKET_LEN` is 287; HEARTBEAT's `mavlink_version` on the wire is 3", notes
        )
        self.assertIn("on Python 3.12.15", notes)
        self.assertIn(
            "- Message signing: the dialect's rule is in `military.xml`, under SAFETY BOUNDARIES: "
            f"<https://github.com/example/mavlink-military/blob/v{V}/military.xml#L4>.",
            notes,
        )
        self.assertNotIn("## Verifying it", notes)
        self.assertEqual(json.loads(evidence["osv.json"])["with_findings"], 0)
        self.assertEqual(result["jobs"], {name: "success" for name in ra.NEEDED})
        self.assertEqual(result["notes"], notes)
        text = ra.summary(self.plan, result)
        self.assertIn(f"Commit `{self.plan['commit']}`.", text)
        self.assertIn("Checks: crc_rows 1, python_classes 1.", text)
        self.assertIn("| commit-checks | success |", text)
        self.assertIn("<details><summary>Release notes</summary>\n\n# MAVLink-M 1.2.3", text)  # fmt: skip

    def test_the_builds_must_hold_the_package_files(self) -> None:
        for leg in (self.a, self.b):
            (leg / f"mavlink-m-{V}-wire.json").unlink()
            (leg / "extra.json").write_text("{}")
            self.sums(leg)
        self.refused(
            f"the builds hold ['extra.json', 'mavlink-m-{V}-wire.json'] beyond or short of the package files"
        )

    def test_a_manifest_that_does_not_match_its_archive_is_refused(self) -> None:
        manifest = manifest_of(CONTENTS)
        manifest["archives"][f"mavlink-m-{V}-python.tar.gz"]["files"][1]["sha256"] = "0" * 64
        self.a, self.b = self.leg("a2", manifest), self.leg("b2", manifest)
        self.refused(
            f"mavlink-m-{V}-python.tar.gz does not hold exactly the files its manifest entry lists"
        )

    def test_an_sbom_that_misses_a_member_is_refused(self) -> None:
        real = ra.sbom.document

        def short(facts: dict) -> dict:
            doc = real(facts)
            doc["files"] = [f for f in doc["files"] if f["fileName"] != "./military.py"]
            return doc

        with mock.patch.object(ra.sbom, "document", side_effect=short):
            with self.assertRaises(ra.sbom.SbomError) as caught:
                self.assemble()
        self.assertIn(f"mavlink-m-{V}-python.tar.gz: the SBOM lists 1 files for 2 members", str(caught.exception))  # fmt: skip

    def test_signed_releases_carry_the_verification_commands(self) -> None:
        env = {"GENERATOR_WORKFLOW": "slsa-framework/slsa-github-generator/.github/workflows/generator_generic_slsa3.yml",
               "GENERATOR_TAG": "v2.1.0", "GENERATOR_COMMIT": "f" * 40}  # fmt: skip
        self.assemble(env)
        self.assertIn(
            "--signer-digest " + "f" * 40, (self.out / f"mavlink-m-{V}-notes.md").read_text()
        )

    def test_the_two_builds_must_agree(self) -> None:
        (self.b / "SHA256SUMS").write_text("0" * 64 + "  x\n")
        self.refused("the two builds' SHA256SUMS differ")

    def test_a_build_with_an_extra_or_missing_file_is_refused(self) -> None:
        (self.b / "extra.txt").write_text("x")
        self.refused("beyond or short of its SHA256SUMS")

    def test_a_file_that_does_not_match_its_line_is_refused(self) -> None:
        (self.a / f"mavlink-m-{V}-manifest.json").write_text("{}")
        self.refused(f"mavlink-m-{V}-manifest.json does not match its SHA256SUMS line")

    def test_a_malformed_sums_line_is_refused(self) -> None:
        for leg in (self.a, self.b):
            (leg / "SHA256SUMS").write_text("not a line\n")
        self.refused("SHA256SUMS has a malformed line: 'not a line'")

    def test_docs_of_another_version_or_with_a_link_are_refused(self) -> None:
        (self.docs / "version.json").write_text(
            json.dumps({"version": "main", "commit": self.plan["commit"]})
        )
        self.refused(f"the docs are not v{V}'s: version.json names main")
        (self.docs / "version.json").write_text(
            json.dumps({"version": f"v{V}", "commit": self.plan["commit"]})
        )
        (self.docs / "link").symlink_to("index.html")
        self.refused("docs: link is not a regular file or directory")

    def test_a_job_that_did_not_succeed_is_refused(self) -> None:
        needs = dict(NEEDS, lint={"result": "failure"})
        del needs["docs"]
        with self.assertRaises(ra.AssembleError) as caught:
            ra.needs_results(json.dumps(needs))
        self.assertIn("'lint': 'failure'", str(caught.exception))
        self.assertIn("'docs': 'missing'", str(caught.exception))
        with self.assertRaises(ra.AssembleError):
            ra.needs_results(None)

    def test_a_missing_record_is_refused(self) -> None:
        (self.records / "zizmor.sarif").unlink()
        self.refused("the record zizmor.sarif is missing")

    def test_an_existing_output_is_refused(self) -> None:
        self.out.mkdir()
        self.refused("exists already")

    def test_a_release_file_with_another_name_is_refused(self) -> None:
        for leg in (self.a, self.b):
            (leg / "bad name.txt").write_text("x")
            (leg / "SHA256SUMS").write_text(
                (leg / "SHA256SUMS").read_text()
                + f"{hashlib.sha256(b'x').hexdigest()}  bad name.txt\n"
            )
        self.refused("SHA256SUMS has a malformed line")

    def test_a_name_outside_the_charset_is_refused_at_the_end(self) -> None:
        real = ra.release_notes.notes

        def notes_and_a_stray_file(
            plan: dict, files: dict, facts: dict, generator: dict | None
        ) -> str:
            (self.out / "a b.md").write_text("x")
            return real(plan, files, facts, generator)

        with mock.patch.object(ra.release_notes, "notes", side_effect=notes_and_a_stray_file):
            self.refused("release file names outside [A-Za-z0-9._-]: ['a b.md']")

    def test_a_failed_git_show_is_refused(self) -> None:
        self.plan["commit"] = "0" * 40
        (self.docs / "version.json").write_text(
            json.dumps({"version": f"v{V}", "commit": "0" * 40})
        )
        self.refused(f"git show {'0' * 40}:LICENSE failed")

    def test_osv_findings_are_recorded(self) -> None:
        def findings(url: str, body: dict) -> dict:
            results = [{} for _ in body["queries"]]
            results[-1] = {"vulns": [{"id": "GHSA-2"}, {"id": "GHSA-1"}], "next_page_token": "t"}
            return {"results": results}

        result = self.assemble(send=findings)
        rows = result["vulnerabilities"]["components"]
        self.assertEqual(rows[-1], {"component": "npm:pkg@1.0.0", "findings": ["GHSA-1", "GHSA-2"], "complete": False,
                                    "disposition": "listed for review"})  # fmt: skip
        self.assertEqual(rows[0]["component"], f"pkg:github/example/one@{'b' * 40}")
        self.assertIn("- npm:pkg@1.0.0: GHSA-1, GHSA-2", ra.summary(self.plan, result))


class OsvTest(AssembleCase):
    def test_a_failing_query_is_retried_then_fails(self) -> None:
        calls = []

        def down(url: str, body: dict) -> dict:
            calls.append(url)
            raise OSError("unreachable")

        with mock.patch.object(osv.time, "sleep"), mock.patch.dict(
            os.environ, {"OSV_URL": "https://osv.invalid/q"}
        ):
            with self.assertRaises(osv.OsvError) as caught:
                osv.record(self.plan, {"lxml": "6.1.3"}, [], send=down)
        self.assertEqual(calls, ["https://osv.invalid/q"] * 3)
        self.assertIn("the OSV query failed: unreachable", str(caught.exception))

    def test_a_retry_that_succeeds_is_enough(self) -> None:
        answers = [ValueError("bad json"), {"results": [{}, {}, {}]}]

        def flaky(url: str, body: dict) -> dict:
            answer = answers.pop(0)
            if isinstance(answer, Exception):
                raise answer
            return answer

        with mock.patch.object(osv.time, "sleep") as sleep:
            record = osv.record(
                self.plan,
                {"lxml": "6.1.3"},
                [{"name": "Inter", "version": None, "key": None}],
                send=flaky,
            )
        self.assertEqual(len(record["components"]), 3)
        sleep.assert_called_once_with(5.0)

    def test_a_short_answer_fails(self) -> None:
        with self.assertRaises(osv.OsvError) as caught:
            osv.record(self.plan, {"lxml": "6.1.3"}, [], send=lambda url, body: {"results": []})
        self.assertIn("OSV answered 0 of 3 queries", str(caught.exception))

    def test_post_sends_json(self) -> None:
        response = mock.MagicMock()
        response.__enter__.return_value.read.return_value = b'{"results": []}'
        with mock.patch.object(osv.urllib.request, "urlopen", return_value=response) as urlopen:
            self.assertEqual(osv.post("https://osv.invalid/q", {"queries": []}), {"results": []})
        request = urlopen.call_args.args[0]
        self.assertEqual((request.full_url, request.data, request.get_header("Content-type")),
                         ("https://osv.invalid/q", b'{"queries": []}', "application/json"))  # fmt: skip


class MainTest(AssembleCase):
    def run_main(self, argv: list[str], env: dict) -> tuple[int, str]:
        out = io.StringIO()
        cwd = os.getcwd()
        os.chdir(self.repo)
        try:
            with mock.patch.dict(os.environ, env), mock.patch.object(ra.osv, "post", answer_none):
                with contextlib.redirect_stdout(out), contextlib.redirect_stderr(io.StringIO()):
                    code = ra.main(argv)
        finally:
            os.chdir(cwd)
        return code, out.getvalue()

    def argv(self) -> list[str]:
        plan = self.tmp / "plan.json"
        plan.write_text(json.dumps(self.plan))
        return [
            "release_assemble.py",
            str(plan),
            str(self.a),
            str(self.b),
            str(self.docs),
            str(self.records),
            str(self.out),
        ]

    def test_outputs_and_summary(self) -> None:
        output, step = self.tmp / "output", self.tmp / "summary"
        code, out = self.run_main(
            self.argv(),
            {
                "NEEDS_JSON": json.dumps(NEEDS),
                "GITHUB_OUTPUT": str(output),
                "GITHUB_STEP_SUMMARY": str(step),
            },
        )
        self.assertEqual(code, 0, out)
        self.assertIn(f"assembled 11 release files for v{V}", out)
        lines = output.read_text().splitlines()
        self.assertTrue(
            lines[0].startswith("subjects=") and lines[1].startswith("subjects_sha256=")
        )
        self.assertIn(f"## v{V} (rehearsal)", step.read_text())

    def test_no_outputs_without_their_files(self) -> None:
        with mock.patch.dict(os.environ):
            os.environ.pop("GITHUB_OUTPUT", None)
            os.environ.pop("GITHUB_STEP_SUMMARY", None)
            code, _ = self.run_main(self.argv(), {"NEEDS_JSON": json.dumps(NEEDS)})
        self.assertEqual(code, 0)

    def test_a_failure_is_an_annotation(self) -> None:
        code, out = self.run_main(self.argv(), {"NEEDS_JSON": "{}"})
        self.assertEqual(code, 1)
        self.assertIn(
            "::error title=release assembly::jobs this release needs did not succeed", out
        )

    def test_usage_and_script(self) -> None:
        self.assertEqual(self.run_main(["release_assemble.py"], {})[0], 2)
        with mock.patch.object(sys, "argv", ["release_assemble.py"]), contextlib.redirect_stderr(
            io.StringIO()
        ):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(ra.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


class CommitChecksTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.repo = Path(tmp.name)
        checks = self.repo / ".github" / "scripts" / "commit_checks"
        checks.mkdir(parents=True)
        (checks / "check_commits.sh").write_text(
            '#!/bin/sh\necho "subjects $1"\nexit "${FAIL_SUBJECTS:-0}"\n'
        )
        git(self.repo, "init", "-q")
        git(self.repo, "add", ".")
        git(self.repo, "commit", "-q", "-m", "chore(repo): start")
        git(self.repo, "tag", "v1.0.0")
        git(self.repo, "commit", "-q", "--allow-empty", "-m", "fix(repo): later")
        self.checks = checks

    def run_main(self, previous: str, env: dict | None = None) -> tuple[int, str, dict]:
        record = self.repo / "record.json"
        out = io.StringIO()
        cwd = os.getcwd()
        os.chdir(self.repo)
        try:
            with mock.patch.dict(os.environ, env or {}), contextlib.redirect_stdout(out):
                code = rcc.main(["release_commit_checks.py", previous, str(record)])
        finally:
            os.chdir(cwd)
        return code, out.getvalue(), json.loads(record.read_text())

    def test_checks_since_a_release_bind(self) -> None:
        code, _, record = self.run_main("v1.0.0")
        self.assertEqual(
            (code, record["range"], record["binding"], record["passed"]),
            (0, "v1.0.0..HEAD", True, True),
        )
        self.assertEqual(len(record["checks"]), 1)
        code, out, record = self.run_main("v1.0.0", {"FAIL_SUBJECTS": "1"})
        self.assertEqual((code, record["passed"]), (1, False))
        self.assertIn("::error title=commit checks::", out)

    def test_the_contribution_check_runs_when_present(self) -> None:
        (self.checks / "check_contribution.py").write_text(
            "import sys\nprint('contribution', sys.argv[1])\n"
        )
        code, _, record = self.run_main("v1.0.0")
        self.assertEqual([c["exit"] for c in record["checks"]], [0, 0])
        self.assertIn("contribution v1.0.0..HEAD", record["checks"][1]["output"])

    def test_before_the_first_release_the_record_is_kept_without_failing(self) -> None:
        root = git(self.repo, "rev-list", "--max-parents=0", "HEAD")
        code, out, record = self.run_main("none", {"FAIL_SUBJECTS": "1"})
        self.assertEqual(
            (code, record["range"], record["binding"], record["passed"]),
            (0, f"{root}..HEAD", False, False),
        )
        self.assertIn("::notice title=commit checks::", out)
        self.assertIn("recorded, not enforced", out)

    def test_usage_and_script(self) -> None:
        with contextlib.redirect_stderr(io.StringIO()):
            self.assertEqual(rcc.main(["release_commit_checks.py"]), 2)
        with mock.patch.object(
            sys, "argv", ["release_commit_checks.py"]
        ), contextlib.redirect_stderr(io.StringIO()):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(rcc.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
