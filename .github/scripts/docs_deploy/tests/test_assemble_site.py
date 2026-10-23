#!/usr/bin/env python3
"""Tests for assemble_site.py. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/docs_deploy/tests
"""

from __future__ import annotations

import contextlib
import io
import json
import re
import runpy
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import assemble_site  # noqa: E402

ADDRESS = "https://docs.example.org/"
NS = {"s": assemble_site.SITEMAP_NS}


def target_of(page: str) -> str:
    """The redirect target a redirect page names, checked in all three places."""
    refresh = re.search(r'content="0; url=([^"]*)"', page).group(1)
    script = re.search(r"location\.replace\((\"[^)]*\") \+ location\.hash\)", page).group(1)
    canonical = re.search(r'rel="canonical" href="([^"]*)"', page).group(1)
    assert refresh == canonical
    return json.loads(script)


class AssembleTestCase(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)
        self.main = self.tmp / "main-build"
        self.site = self.tmp / "site"
        for page in ("index.html", "404.html", "en/index.html", "en/messages/military.html"):
            self.write(page, f"<html>{page}</html>")
        self.write("version.json", json.dumps({"schema": 1, "version": "main"}))
        self.write(
            "sitemap.xml",
            f'<urlset xmlns="{assemble_site.SITEMAP_NS}"><url><loc>{ADDRESS}main/en/</loc></url></urlset>',
        )

    def write(self, rel: str, text: str) -> None:
        path = self.main / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def run_main(self, *args: str) -> tuple[int, str, str]:
        out, err = io.StringIO(), io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            code = assemble_site.main(["assemble_site.py", *args])
        return code, out.getvalue(), err.getvalue()


class AssembleTest(AssembleTestCase):
    def test_main_sits_below_the_root_with_redirects_and_lists(self) -> None:
        code, out, _ = self.run_main(str(self.main), str(self.site))
        self.assertEqual(code, 0)
        self.assertEqual(
            (self.site / "main" / "en" / "messages" / "military.html").read_text(),
            "<html>en/messages/military.html</html>",
        )
        self.assertEqual(target_of((self.site / "index.html").read_text()), "main/")
        self.assertEqual((self.site / "404.html").read_text(), "<html>404.html</html>")
        self.assertEqual(
            target_of((self.site / "en" / "index.html").read_text()), "../main/en/index.html"
        )
        self.assertEqual(
            target_of((self.site / "en" / "messages" / "military.html").read_text()),
            "../../main/en/messages/military.html",
        )
        self.assertEqual(
            json.loads((self.site / "versions.json").read_text()),
            {
                "schema": 1,
                "versions": [{"version": "main", "path": "main/", "status": "development"}],
            },
        )
        index = ET.parse(self.site / "sitemap.xml").getroot()
        self.assertEqual(index.tag, f"{{{assemble_site.SITEMAP_NS}}}sitemapindex")
        self.assertEqual(
            [e.text for e in index.findall("s:sitemap/s:loc", NS)], [f"{ADDRESS}main/sitemap.xml"]
        )
        self.assertIn(
            "The root serves main/; 2 page(s) from before the versions redirect there.", out
        )
        self.assertIn("| main | main/ | development |", out)

    def test_every_stub_resolves_to_its_page_below_main(self) -> None:
        self.run_main(str(self.main), str(self.site))
        for stub in (self.site / "en").rglob("*.html"):
            rel = stub.relative_to(self.site).as_posix()
            resolved = (stub.parent / target_of(stub.read_text())).resolve()
            self.assertEqual(resolved, (self.site / "main" / rel).resolve())
            self.assertTrue(resolved.is_file())

    def test_a_redirect_page_escapes_its_target(self) -> None:
        page = assemble_site.redirect_page('a&b"</script>.html')
        self.assertIn('href="a&amp;b&quot;&lt;/script&gt;.html"', page)
        self.assertNotIn("</script>.html", page)
        self.assertEqual(target_of(page), 'a&b"</script>.html')
        self.assertIn('<meta name="robots" content="noindex">', page)

    def test_the_address_comes_from_mains_sitemap(self) -> None:
        self.assertEqual(assemble_site.site_address(self.main), ADDRESS)


class RefusalTest(AssembleTestCase):
    def assert_refused(self, message: str) -> None:
        code, out, _ = self.run_main(str(self.main), str(self.site))
        self.assertEqual(code, 1)
        self.assertIn(f"::error title=docs site::{message}", out)

    def test_a_build_missing_a_needed_file_is_refused(self) -> None:
        for needed in ("index.html", "404.html", "sitemap.xml", "version.json"):
            with self.subTest(needed=needed):
                saved = (self.main / needed).read_text()
                (self.main / needed).unlink()
                self.assert_refused(f"main's build has no {needed}")
                self.write(needed, saved)
        (self.main / "en" / "messages" / "military.html").unlink()
        (self.main / "en" / "messages").rmdir()
        (self.main / "en" / "index.html").unlink()
        (self.main / "en").rmdir()
        self.assert_refused("main's build has no en")
        self.assertFalse(self.site.exists())

    def test_a_build_of_another_version_is_refused(self) -> None:
        self.write("version.json", json.dumps({"schema": 1, "version": "v1.0.0"}))
        self.assert_refused("the build given as main documents another version")

    def test_an_unreadable_sitemap_is_refused(self) -> None:
        self.write("sitemap.xml", "<urlset")
        self.assert_refused("main's sitemap.xml cannot be read: ")

    def test_a_sitemap_without_a_page_below_main_is_refused(self) -> None:
        for body in ("", f"<url><loc>{ADDRESS}en/</loc></url>", "<url><loc/></url>"):
            with self.subTest(body=body):
                self.write(
                    "sitemap.xml", f'<urlset xmlns="{assemble_site.SITEMAP_NS}">{body}</urlset>'
                )
                self.assert_refused("main's sitemap names no page below main/")

    def test_an_existing_site_is_refused(self) -> None:
        self.site.mkdir()
        self.assert_refused(f"{self.site} exists already")
        self.assertEqual(list(self.site.iterdir()), [])

    def test_usage(self) -> None:
        code, _, err = self.run_main(str(self.main))
        self.assertEqual(code, 2)
        self.assertIn("Usage: assemble_site.py <main> <site>", err)


class ScriptTest(AssembleTestCase):
    def test_runs_as_a_script(self) -> None:
        argv = ["assemble_site.py", str(self.main), str(self.site)]
        with mock.patch.object(sys, "argv", argv), contextlib.redirect_stdout(io.StringIO()):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(assemble_site.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 0)
        self.assertTrue((self.site / "versions.json").is_file())


if __name__ == "__main__":
    unittest.main()
