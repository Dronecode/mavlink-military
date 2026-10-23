#!/usr/bin/env python3
"""Tests for write_site_files.py, in a temporary git repository with a stand-in
node_modules. Run from docs/: python3 -m unittest discover --start-directory scripts/tests
"""

from __future__ import annotations

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

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import write_site_files  # noqa: E402

PINS = f"MAVLINK_REF={'a' * 40}\nPYMAVLINK_REF={'b' * 40}\n"
XML = b'<?xml version="1.0"?>\n<mavlink><version>1</version></mavlink>\n'
LOCK = {
    "name": "site",
    "lockfileVersion": 3,
    "packages": {
        "": {"name": "site", "devDependencies": {"zeta": "^1"}},
        "node_modules/zeta": {"version": "1.2.0", "license": "MIT"},
        "node_modules/@scope/alpha": {"version": "0.9.1", "license": "ISC"},
        "node_modules/zeta/node_modules/inner": {"version": "3.0.0"},
        "node_modules/@esbuild/other-os": {"version": "0.21.5", "optional": True},
    },
}


class WriteSiteFilesTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.repo = Path(tmp.name) / "repo"
        self.docs = self.repo / "docs"
        self.dist = self.docs / ".vitepress" / "dist"
        self.dist.mkdir(parents=True)
        (self.dist / "index.html").write_text("<html></html>", encoding="utf-8")
        (self.repo / ".github").mkdir()
        (self.repo / ".github" / "mavlink-pins.env").write_text(PINS, encoding="utf-8")
        (self.repo / "military.xml").write_bytes(XML)
        (self.repo / "LICENSE").write_text(
            "MIT License\n\nCopyright (c) placeholder\n", encoding="utf-8"
        )
        (self.docs / "package-lock.json").write_text(json.dumps(LOCK), encoding="utf-8")
        modules = self.docs / "node_modules"
        self.module(
            modules / "zeta", {"LICENSE": "zeta license text\n", "README.md": "not a license"}
        )
        self.module(
            modules / "@scope" / "alpha",
            {"LICENSE.md": "alpha license\n", "NOTICE": "alpha notice\n"},
        )
        self.module(
            modules / "zeta" / "node_modules" / "inner",
            {"package.json": '{"license": "BSD-3-Clause"}'},
        )
        self.git("init", "-q")
        self.git("add", "--all")
        self.git("commit", "-q", "-m", "chore(repo): start")
        self.patch = mock.patch.object(write_site_files, "DOCS", self.docs)
        self.patch.start()
        self.addCleanup(self.patch.stop)

    @staticmethod
    def module(folder: Path, files: dict[str, str]) -> None:
        folder.mkdir(parents=True, exist_ok=True)
        for name, text in files.items():
            (folder / name).write_text(text, encoding="utf-8")

    def git(self, *args: str) -> str:
        command = ["git", "-c", "user.name=Test", "-c", "user.email=test@example.org", *args]
        return subprocess.run(
            command, cwd=self.repo, check=True, capture_output=True, text=True
        ).stdout

    def write(self, version: str | None = None, argv: list[str] | None = None):
        out, err = io.StringIO(), io.StringIO()
        with mock.patch.dict(os.environ):
            os.environ.pop("DOCS_VERSION", None)
            if version is not None:
                os.environ["DOCS_VERSION"] = version
            with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
                status = write_site_files.main(argv or ["write_site_files.py", str(self.dist)])
        return status, out.getvalue(), err.getvalue()

    def record(self) -> dict:
        return json.loads((self.dist / "version.json").read_text(encoding="utf-8"))

    def test_main_records_its_commit_and_inputs(self) -> None:
        for version in (None, "main"):
            with self.subTest(version=version):
                status, out, err = self.write(version)
                self.assertEqual((status, err), (0, ""))
                self.assertIn(
                    "wrote version.json (main), LICENSE.txt and THIRD-PARTY-NOTICES.txt", out
                )
                self.assertEqual(
                    self.record(),
                    {
                        "schema": 1,
                        "version": "main",
                        "commit": self.git("rev-parse", "HEAD").strip(),
                        "commit_date": self.git("log", "-1", "--format=%cI").strip(),
                        "military_xml_sha256": hashlib.sha256(XML).hexdigest(),
                        "mavlink_ref": "a" * 40,
                        "release": None,
                    },
                )

    def test_a_release_links_its_release_page(self) -> None:
        self.assertEqual(self.write("v1.2.3")[0], 0)
        self.assertEqual(
            self.record()["release"],
            "https://github.com/Dronecode/mavlink-military/releases/tag/v1.2.3",
        )

    def test_a_tag_with_a_non_ascii_digit_links_no_release(self) -> None:
        self.assertEqual(self.write("v1.\uff12.3")[0], 0)
        self.assertIsNone(self.record()["release"])

    def test_the_record_comes_from_the_commit_not_the_working_tree(self) -> None:
        (self.repo / "military.xml").write_bytes(b"edited")
        (self.repo / ".github" / "mavlink-pins.env").write_text(
            "MAVLINK_REF=short\n", encoding="utf-8"
        )
        self.assertEqual(self.write()[0], 0)
        self.assertEqual(self.record()["military_xml_sha256"], hashlib.sha256(XML).hexdigest())
        self.assertEqual(self.record()["mavlink_ref"], "a" * 40)

    def test_a_commit_without_a_mavlink_pin_records_none(self) -> None:
        (self.repo / ".github" / "mavlink-pins.env").write_text(
            "PYMAVLINK_REF=x\n", encoding="utf-8"
        )
        self.git("commit", "-q", "-am", "chore(repo): drop the pin")
        self.assertEqual(self.write()[0], 0)
        self.assertIsNone(self.record()["mavlink_ref"])

    def test_the_license_is_the_commits(self) -> None:
        self.assertEqual(self.write()[0], 0)
        self.assertEqual(
            (self.dist / "LICENSE.txt").read_text(encoding="utf-8"),
            "MIT License\n\nCopyright (c) placeholder\n",
        )

    def test_notices_list_every_installed_package_with_its_license_files(self) -> None:
        self.assertEqual(self.write()[0], 0)
        text = (self.dist / "THIRD-PARTY-NOTICES.txt").read_text(encoding="utf-8")
        self.assertTrue(text.startswith("Third-party notices for this documentation site\n"))
        alpha = text.index(
            "@scope/alpha 0.9.1 (ISC)\nnode_modules/@scope/alpha\n\n--- LICENSE.md\n\nalpha license\n"
        )
        zeta = text.index(
            "zeta 1.2.0 (MIT)\nnode_modules/zeta\n\n--- LICENSE\n\nzeta license text\n"
        )
        inner = text.index(
            "inner 3.0.0 (BSD-3-Clause)\nnode_modules/zeta/node_modules/inner\n\n(The package ships no license file.)\n"
        )
        self.assertLess(alpha, zeta)
        self.assertLess(zeta, inner)
        self.assertIn("--- NOTICE\n\nalpha notice\n", text)
        self.assertNotIn("not a license", text)
        self.assertNotIn("other-os", text)
        self.assertIn(
            "Inter font (bundled by the VitePress theme)\n\nCopyright (c) 2016 The Inter Project Authors",
            text,
        )

    def test_a_package_without_a_declared_license_says_so(self) -> None:
        (
            self.docs / "node_modules" / "zeta" / "node_modules" / "inner" / "package.json"
        ).write_text('{"license": {"type": "old form"}}', encoding="utf-8")
        (self.docs / "node_modules" / "@scope" / "alpha" / "package.json").unlink(missing_ok=True)
        lock = dict(LOCK, packages=dict(LOCK["packages"]))
        lock["packages"]["node_modules/@scope/alpha"] = {"version": "0.9.1"}
        (self.docs / "package-lock.json").write_text(json.dumps(lock), encoding="utf-8")
        self.assertEqual(self.write()[0], 0)
        text = (self.dist / "THIRD-PARTY-NOTICES.txt").read_text(encoding="utf-8")
        self.assertIn("@scope/alpha 0.9.1 (not declared)", text)
        self.assertIn("inner 3.0.0 (not declared)", text)

    def test_the_same_commit_gives_the_same_files(self) -> None:
        self.assertEqual(self.write("v1.0.0")[0], 0)
        first = {p.name: p.read_bytes() for p in self.dist.iterdir()}
        self.assertEqual(self.write("v1.0.0")[0], 0)
        self.assertEqual(first, {p.name: p.read_bytes() for p in self.dist.iterdir()})

    def test_without_a_built_site_nothing_is_written(self) -> None:
        (self.dist / "index.html").unlink()
        status, _, err = self.write()
        self.assertEqual(status, 1)
        self.assertIn("no built site in", err)
        self.assertFalse((self.dist / "version.json").exists())

    def test_reads_the_default_build_directory(self) -> None:
        with mock.patch.object(write_site_files, "DIST", self.dist):
            self.assertEqual(self.write(argv=["write_site_files.py"])[0], 0)
        self.assertTrue((self.dist / "version.json").is_file())

    def test_runs_as_a_script(self) -> None:
        # The script's own DOCS is this repository's docs/, so it reads this checkout.
        argv = ["write_site_files.py", str(self.dist)]
        with mock.patch.object(sys, "argv", argv), contextlib.redirect_stdout(io.StringIO()):
            with mock.patch.dict(os.environ, {"DOCS_VERSION": "main"}):
                with self.assertRaises(SystemExit) as exit_:
                    runpy.run_path(write_site_files.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 0)


if __name__ == "__main__":
    unittest.main()
