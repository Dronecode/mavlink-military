#!/usr/bin/env python3
"""Tests for check_site.py, run against small sites written to a temporary directory.

Run from docs/: python3 -m unittest discover --start-directory scripts/tests
"""

from __future__ import annotations

import contextlib
import io
import os
import runpy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_site  # noqa: E402

BASE = "/site/"
HOST = "https://example.org/site"


def page(body: str) -> str:
    return f"<!doctype html><html><body>{body}</body></html>"


class CheckSiteTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.dist = Path(tmp.name)
        self.write("index.html", page('<a href="/site/en/">Docs</a>'))
        self.write(
            "en/index.html",
            page(
                '<h2 id="intro">Intro</h2>'
                '<a href="./guide.html#se%74up">Setup</a>'
                '<a href="https://other.example/page.html">elsewhere</a>'
            ),
        )
        self.write(
            "en/guide.html",
            page(
                '<h2 id="setup">Setup</h2><a name="old-name"></a>'
                '<a href="#setup">here</a><a href="../logo.svg">logo</a>'
            ),
        )
        self.write("logo.svg", "<svg/>")
        self.write(
            "en/messages/military.html", page('<h3 id="FIRES">FIRES</h3><a href="#FIRES">x</a>')
        )
        self.sitemap("", "en/", "en/guide.html", "en/messages/military.html")

    def write(self, rel: str, text: str) -> None:
        path = self.dist / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def sitemap(self, *paths: str, host: str = HOST) -> None:
        locs = "".join(f"<url><loc>{host}/{path}</loc></url>" for path in paths)
        self.write(
            "sitemap.xml",
            '<?xml version="1.0" encoding="UTF-8"?>'
            f'<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">{locs}</urlset>',
        )

    def check(self, env: dict[str, str | None] | None = None, argv: list[str] | None = None):
        """Run the check with DOCS_BASE and DOCS_HOSTNAME set for the test site, at its root.

        A None value in env removes that variable. Returns (status, stdout, stderr).
        """
        values: dict[str, str | None] = {
            "DOCS_BASE": BASE,
            "DOCS_HOSTNAME": HOST,
            "DOCS_VERSION": None,
            "GITHUB_STEP_SUMMARY": None,
        }
        values.update(env or {})
        out, err = io.StringIO(), io.StringIO()
        with mock.patch.dict(os.environ):
            for name, value in values.items():
                if value is None:
                    os.environ.pop(name, None)
                else:
                    os.environ[name] = value
            with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
                status = check_site.main(argv or ["check_site.py", str(self.dist)])
        return status, out.getvalue(), err.getvalue()

    def test_clean_site_passes(self) -> None:
        status, out, _ = self.check()
        self.assertEqual(status, 0)
        self.assertNotIn("::error", out)
        self.assertIn(
            "4 pages, 4 sitemap URLs and 5 links checked: 0 error(s), "
            "0 dead anchor(s) in the generated reference",
            out,
        )

    def test_sitemap_url_outside_the_site_fails(self) -> None:
        # What VitePress writes when the hostname has no trailing slash.
        self.sitemap("en/guide.html", host="https://example.org")
        status, out, _ = self.check()
        self.assertEqual(status, 1)
        self.assertIn(
            "::error title=docs site::sitemap.xml: https://example.org/en/guide.html "
            "is not under the site address https://example.org/site/",
            out,
        )

    def test_sitemap_url_without_a_page_fails(self) -> None:
        self.sitemap("en/missing.html")
        status, out, _ = self.check()
        self.assertEqual(status, 1)
        self.assertIn("sitemap.xml: https://example.org/site/en/missing.html names no page", out)

    def test_missing_sitemap_fails(self) -> None:
        (self.dist / "sitemap.xml").unlink()
        status, out, _ = self.check()
        self.assertEqual(status, 1)
        self.assertIn("sitemap.xml: the build wrote no sitemap", out)

    def test_missing_build_fails(self) -> None:
        (self.dist / "index.html").unlink()
        status, out, err = self.check()
        self.assertEqual(status, 1)
        self.assertEqual(out, "")
        self.assertIn("no built site in", err)

    def test_dead_link_fails(self) -> None:
        self.write("en/index.html", page('<a href="./nowhere.html">gone</a>'))
        status, out, _ = self.check()
        self.assertEqual(status, 1)
        self.assertIn("en/index.html: link ./nowhere.html names no page in the build", out)

    def test_dead_anchor_on_a_hand_written_page_fails(self) -> None:
        self.write("en/index.html", page('<a href="./guide.html#teardown">gone</a>'))
        status, out, _ = self.check()
        self.assertEqual(status, 1)
        self.assertIn(
            "en/index.html: link ./guide.html#teardown names no anchor #teardown on en/guide.html",
            out,
        )

    def test_named_anchor_resolves(self) -> None:
        self.write("en/index.html", page('<a href="./guide.html#old-name">old</a>'))
        status, out, _ = self.check()
        self.assertEqual(status, 0, out)

    def test_dead_anchors_in_the_generated_reference_warn(self) -> None:
        self.write(
            "en/messages/military.html",
            page('<h3 id="FIRES">FIRES</h3><a href="#MAV_CMD_X">x</a><a href="#MAV_TYPE_Y">y</a>'),
        )
        status, out, _ = self.check()
        self.assertEqual(status, 0)
        self.assertNotIn("::error", out)
        self.assertIn(
            "::warning title=docs site::en/messages/military.html: 2 link(s) name an anchor "
            "the page lacks (from the upstream reference generator)",
            out,
        )
        self.assertIn("0 error(s), 2 dead anchor(s) in the generated reference", out)

    def test_links_outside_the_site_are_not_checked(self) -> None:
        self.write(
            "en/index.html",
            page(
                '<a href="/elsewhere/page.html">a</a><a href="mailto:ops@example.org">b</a>'
                '<a href="//cdn.example.org/lib.js">c</a>'
            ),
        )
        status, out, _ = self.check()
        self.assertEqual(status, 0, out)
        self.assertIn("4 links checked", out)

    def test_site_at_the_root_of_a_domain(self) -> None:
        self.write("index.html", page('<a href="/en/">Docs</a>'))
        self.sitemap("", "en/", host="https://docs.example.org")
        status, out, _ = self.check(
            {"DOCS_BASE": "/", "DOCS_HOSTNAME": "https://docs.example.org/"}
        )
        self.assertEqual(status, 0, out)

    def test_defaults_match_the_vitepress_config(self) -> None:
        # Without the variables, config.mjs builds for "/" on the project domain.
        self.write("index.html", page('<a href="/en/">Docs</a>'))
        self.sitemap("en/", host="https://mavlink-m.dronecode.org")
        status, out, _ = self.check({"DOCS_BASE": None, "DOCS_HOSTNAME": None})
        self.assertEqual(status, 0, out)

    def versioned(self, version: str) -> None:
        """The test site as config.mjs builds it for a version, below the root."""
        self.write("index.html", page(f'<a href="/site/{version}/en/">Docs</a>'))
        self.write("en/index.html", page(f'<a href="/site/{version}/en/guide.html">Guide</a>'))
        self.sitemap("", "en/", host=f"{HOST}/{version}")

    def test_main_and_releases_are_checked_below_the_root(self) -> None:
        for version in ("main", "v0.1.0", "v12.0.3"):
            with self.subTest(version=version):
                self.versioned(version)
                status, out, _ = self.check({"DOCS_VERSION": version})
                self.assertEqual(status, 0, out)
                # The two links above, and the three relative links of the guide and reference.
                self.assertIn("4 pages, 2 sitemap URLs and 5 links checked: 0 error(s)", out)

    def test_a_version_with_sitemap_urls_at_the_root_fails(self) -> None:
        status, out, _ = self.check({"DOCS_VERSION": "v1.0.0"})
        self.assertEqual(status, 1)
        self.assertIn(
            "sitemap.xml: https://example.org/site/en/guide.html is not under the site address "
            "https://example.org/site/v1.0.0/",
            out,
        )
        # The home page's link to /site/en/ lies outside this version's pages, so of the
        # five links only the four relative ones are checked.
        self.assertIn("4 sitemap URLs and 4 links checked: 4 error(s)", out)

    def test_a_version_that_is_no_release_tag_fails(self) -> None:
        for version in (
            "1.0.0",
            "v1.0",
            "v01.0.0",
            "v1.0.0-rc.1",
            "v1.0.0+1",
            "develop",
            "v1.\uff10.0",
        ):
            with self.subTest(version=version):
                status, out, err = self.check({"DOCS_VERSION": version})
                self.assertEqual((status, out), (1, ""))
                self.assertIn(f"DOCS_VERSION {version} is neither main nor a release tag", err)

    def test_reads_the_default_build_directory(self) -> None:
        with mock.patch.object(check_site, "DIST", self.dist):
            status, out, _ = self.check(argv=["check_site.py"])
        self.assertEqual(status, 0, out)

    def test_step_summary_lists_every_finding(self) -> None:
        self.write("en/index.html", page('<a href="./nowhere.html">gone</a>'))
        self.write("en/messages/military.html", page('<a href="#MAV_CMD_X">x</a>'))
        summary = self.dist.parent / f"{self.dist.name}-summary.md"
        self.addCleanup(summary.unlink, missing_ok=True)
        status, _, _ = self.check({"GITHUB_STEP_SUMMARY": str(summary)})
        self.assertEqual(status, 1)
        text = summary.read_text(encoding="utf-8")
        self.assertTrue(text.startswith("## Docs site check\n\n4 pages,"))
        self.assertIn("- en/index.html: link ./nowhere.html names no page in the build\n", text)
        self.assertIn("<details><summary>Dead anchors in the generated reference</summary>", text)
        self.assertIn(
            "- en/messages/military.html: link #MAV_CMD_X names no anchor #MAV_CMD_X", text
        )

    def test_step_summary_of_a_clean_site_has_only_the_verdict(self) -> None:
        summary = self.dist.parent / f"{self.dist.name}-summary.md"
        self.addCleanup(summary.unlink, missing_ok=True)
        status, _, _ = self.check({"GITHUB_STEP_SUMMARY": str(summary)})
        self.assertEqual(status, 0)
        self.assertEqual(
            summary.read_text(encoding="utf-8"),
            "## Docs site check\n\n4 pages, 4 sitemap URLs and 5 links checked: 0 error(s), "
            "0 dead anchor(s) in the generated reference\n\n",
        )

    def test_annotations_escape_workflow_command_characters(self) -> None:
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            check_site.annotate("error", "a%20b\nc\rd")
        self.assertEqual(out.getvalue(), "::error title=docs site::a%2520b%0Ac%0Dd\n")

    def test_runs_as_a_script(self) -> None:
        with mock.patch.object(sys, "argv", ["check_site.py", str(self.dist)]):
            with mock.patch.dict(os.environ, {"DOCS_BASE": BASE, "DOCS_HOSTNAME": HOST}):
                os.environ.pop("GITHUB_STEP_SUMMARY", None)
                # The fixture site sits at the root; docs.yml sets DOCS_VERSION for
                # every step, the step that runs these tests among them.
                os.environ.pop("DOCS_VERSION", None)
                with contextlib.redirect_stdout(io.StringIO()):
                    with self.assertRaises(SystemExit) as exit_:
                        runpy.run_path(check_site.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 0)


if __name__ == "__main__":
    unittest.main()
