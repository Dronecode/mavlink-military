#!/usr/bin/env python3
"""Tests for check_deployed_site.sh, against a site served from a temporary
directory. Needs curl. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/docs/tests
"""

from __future__ import annotations

import functools
import http.server
import os
import subprocess
import tempfile
import threading
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "check_deployed_site.sh"


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
        for page in ("index.html", "en/index.html", "en/messages/military.html", "en/guide.html"):
            self.write(page, "<html></html>")
        self.sitemap(self.site + "en/guide.html")

    def write(self, rel: str, text: str) -> None:
        path = self.root / "site" / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def sitemap(self, *urls: str) -> None:
        locs = "".join(f"<url><loc>{u}</loc></url>" for u in urls)
        self.write(
            "sitemap.xml",
            f'<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">{locs}</urlset>',
        )

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
        self.assertIn(f"OK {self.site}en/messages/military.html", result.stdout)
        self.assertTrue(result.stdout.endswith(f"OK {self.site}en/guide.html\n"))

    def test_a_sitemap_outside_the_site_fails(self) -> None:
        self.sitemap(self.site.replace("/site/", "/") + "en/guide.html")
        result = self.check()
        self.assertEqual(result.returncode, 1)
        self.assertIn("is not under " + self.site, result.stderr)
        self.assertNotIn("::error::", result.stdout)

    def test_the_mismatch_is_an_annotation_under_github_actions(self) -> None:
        self.sitemap()
        result = self.check(actions=True)
        self.assertEqual(result.returncode, 1)
        self.assertIn(f"::error::sitemap URL '' is not under {self.site}", result.stdout)

    def test_a_missing_page_fails(self) -> None:
        (self.root / "site" / "en" / "messages" / "military.html").unlink()
        result = self.check()
        self.assertNotEqual(result.returncode, 0)
        self.assertNotIn("military.html", result.stdout)

    def test_usage(self) -> None:
        result = self.check(args=[])
        self.assertEqual(result.returncode, 1)
        self.assertIn("usage:", result.stderr)


if __name__ == "__main__":
    unittest.main()
