#!/usr/bin/env python3
"""Tests for check_deployed_site.sh, against a site served from a temporary
directory. Needs curl and jq. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/docs/tests
"""

from __future__ import annotations

import functools
import http.server
import json
import os
import shutil
import subprocess
import tempfile
import threading
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "check_deployed_site.sh"
PAGES = ("index.html", "en/index.html", "en/messages/military.html", "en/guide.html")


class QuietHandler(http.server.SimpleHTTPRequestHandler):
    def log_message(self, *args: object) -> None:
        pass


class CheckDeployedSiteTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.root = Path(tmp.name)
        handler = functools.partial(QuietHandler, directory=str(self.root))
        self.server = http.server.ThreadingHTTPServer(("127.0.0.1", 0), handler)
        threading.Thread(target=self.server.serve_forever, daemon=True).start()
        self.addCleanup(self.server.server_close)
        self.addCleanup(self.server.shutdown)
        self.site = f"http://127.0.0.1:{self.server.server_address[1]}/site/"
        self.write("index.html", "<html></html>")
        self.write("en/index.html", "<html></html>")
        self.version("main")
        self.versions("main/")

    def write(self, rel: str, text: str) -> None:
        path = self.root / "site" / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def version(self, name: str) -> None:
        for page in PAGES:
            self.write(f"{name}/{page}", "<html></html>")
        self.write(f"{name}/version.json", json.dumps({"schema": 1, "version": name}))
        self.sitemap(name, f"{self.site}{name}/en/guide.html")

    def sitemap(self, name: str, *urls: str) -> None:
        locs = "".join(f"<url><loc>{u}</loc></url>" for u in urls)
        self.write(
            f"{name}/sitemap.xml",
            f'<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">{locs}</urlset>',
        )

    def versions(self, *paths: str) -> None:
        entries = [{"version": p.rstrip("/"), "path": p, "status": "latest"} for p in paths]
        self.write("versions.json", json.dumps({"schema": 1, "versions": entries}))

    def check(self, site: str | None = None, actions: bool = False, args: list[str] | None = None):
        env = dict(os.environ, CHECK_RETRIES="0", CHECK_RETRY_DELAY="0")
        env.pop("GITHUB_ACTIONS", None)
        if actions:
            env["GITHUB_ACTIONS"] = "true"
        if args is None:
            args = [site or self.site]
        return subprocess.run(["sh", str(SCRIPT), *args], env=env, capture_output=True, text=True)

    def test_a_good_site_passes(self) -> None:
        result = self.check(self.site.rstrip("/"))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn(f"OK {self.site}versions.json", result.stdout)
        self.assertIn(f"OK {self.site}main/version.json", result.stdout)
        self.assertIn(f"OK {self.site}main/en/messages/military.html", result.stdout)
        self.assertTrue(result.stdout.endswith(f"OK {self.site}main/en/guide.html\n"))

    def test_every_listed_release_is_checked(self) -> None:
        self.version("v1.0.0")
        self.versions("main/", "v1.0.0/")
        result = self.check()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn(f"OK {self.site}v1.0.0/en/messages/military.html", result.stdout)
        self.assertTrue(result.stdout.endswith(f"OK {self.site}v1.0.0/en/guide.html\n"))

    def test_a_missing_listed_release_fails(self) -> None:
        self.versions("main/", "v1.0.0/")
        result = self.check()
        self.assertNotEqual(result.returncode, 0)
        self.assertNotIn("OK " + self.site + "v1.0.0/", result.stdout)

    def test_a_list_without_main_fails(self) -> None:
        self.version("v1.0.0")
        self.versions("v1.0.0/")
        result = self.check(actions=True)
        self.assertEqual(result.returncode, 1)
        self.assertIn("::error::versions.json does not list main/", result.stdout)

    def test_a_malformed_list_fails(self) -> None:
        self.write("versions.json", "not json")
        result = self.check()
        self.assertEqual(result.returncode, 1)
        self.assertIn("versions.json does not list main/", result.stderr)

    def test_a_path_that_is_no_version_fails(self) -> None:
        for path in ("../", "v1.0/", "main", "v01.0.0/"):
            with self.subTest(path=path):
                self.versions("main/", path)
                result = self.check()
                self.assertEqual(result.returncode, 1)
                self.assertIn(f"lists '{path}', which is no version's directory", result.stderr)

    def test_a_build_of_another_version_fails(self) -> None:
        self.write("main/version.json", json.dumps({"schema": 1, "version": "v1.0.0"}))
        result = self.check()
        self.assertEqual(result.returncode, 1)
        self.assertIn(f"{self.site}main/version.json does not name main", result.stderr)

    def test_a_sitemap_outside_its_version_fails(self) -> None:
        self.sitemap("main", self.site + "en/guide.html")
        result = self.check()
        self.assertEqual(result.returncode, 1)
        self.assertIn(f"is not under {self.site}main/", result.stderr)
        self.assertNotIn("::error::", result.stdout)

    def test_the_mismatch_is_an_annotation_under_github_actions(self) -> None:
        self.sitemap("main")
        result = self.check(actions=True)
        self.assertEqual(result.returncode, 1)
        self.assertIn(f"::error::sitemap URL '' is not under {self.site}main/", result.stdout)

    def test_a_missing_page_fails(self) -> None:
        (self.root / "site" / "main" / "en" / "messages" / "military.html").unlink()
        result = self.check()
        self.assertNotEqual(result.returncode, 0)
        self.assertNotIn("military.html", result.stdout)

    def test_a_missing_page_from_before_the_versions_fails(self) -> None:
        # The test server lists a directory without an index; Pages answers 404.
        shutil.rmtree(self.root / "site" / "en")
        result = self.check()
        self.assertNotEqual(result.returncode, 0)
        self.assertNotIn(f"OK {self.site}en/", result.stdout)

    def test_usage(self) -> None:
        result = self.check(args=[])
        self.assertEqual(result.returncode, 1)
        self.assertIn("usage:", result.stderr)


if __name__ == "__main__":
    unittest.main()
