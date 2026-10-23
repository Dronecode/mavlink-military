#!/usr/bin/env python3
"""Tests for assemble_site.py, with a stand-in gh. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/docs_deploy/tests
"""

from __future__ import annotations

import base64
import contextlib
import hashlib
import io
import json
import os
import re
import runpy
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET
from pathlib import Path
from unittest import mock

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
sys.path.insert(0, str(HERE.parents[1] / "release" / "tests"))
import assemble_site  # noqa: E402
from assemble_site import archive  # noqa: E402
from fake_gh import FakeGh  # noqa: E402

ADDRESS = "https://docs.example.org/"
NS = {"s": assemble_site.SITEMAP_NS}
REPO = "Dronecode/mavlink-military"
GEN = "slsa-framework/slsa-github-generator/.github/workflows/generator_generic_slsa3.yml"
RELEASE_YML = f"env:\n  GENERATOR_WORKFLOW: {GEN}\n  GENERATOR_COMMIT: {'f' * 40}\n"


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
        self.work = self.tmp / "work"
        self.checkout = self.tmp / "checkout"
        (self.checkout / ".github").mkdir(parents=True)
        for page in ("index.html", "404.html", "en/index.html", "en/messages/military.html"):
            self.write(page, f"<html>{page}</html>")
        self.write("version.json", json.dumps({"schema": 1, "version": "main"}))
        self.write(
            "sitemap.xml",
            f'<urlset xmlns="{assemble_site.SITEMAP_NS}"><url><loc>{ADDRESS}main/en/</loc></url></urlset>',
        )
        self.gh = FakeGh(self.tmp)
        self.releases: list[dict] = []
        patcher = mock.patch.dict(os.environ, {**self.gh.env(), "GITHUB_REPOSITORY": REPO})
        patcher.start()
        self.addCleanup(patcher.stop)

    def write(self, rel: str, text: str) -> None:
        path = self.main / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def status(self, withdrawn: dict) -> None:
        (self.checkout / ".github" / "release-status.json").write_text(
            json.dumps({"schema": 1, "withdrawn": withdrawn})
        )

    def release(
        self,
        tag: str,
        pages: dict[str, str] | None = None,
        sums_ok: bool = True,
        verified: bool = True,
    ) -> None:
        """A published release with its docs archive, SHA256SUMS and provenance bundle."""
        version = tag[1:]
        self.releases.append({"tag_name": tag, "draft": False, "prerelease": False})
        build = self.tmp / f"build-{tag}.tar.gz"
        files = {
            k: v.encode()
            for k, v in (
                pages or {"index.html": f"<html>{tag}</html>", "en/index.html": "<html>en</html>"}
            ).items()
        }
        archive.write(build, f"mavlink-m-{version}-docs", files, 1700000000)
        data = build.read_bytes()
        digest = hashlib.sha256(data if sums_ok else b"other").hexdigest()
        name = f"mavlink-m-{version}-docs.tar.gz"
        payload = base64.b64encode(json.dumps({"subject": []}).encode()).decode()
        self.gh.on("release", "download", tag, "--repo", REPO, "--dir", prefix=True, files={
            "SHA256SUMS": f"{digest}  {name}\n", name: data,
            f"mavlink-m-{version}.intoto.jsonl": json.dumps({"dsseEnvelope": {"payload": payload}}) + "\n"})  # fmt: skip
        self.gh.on(
            "api",
            "-H",
            "Accept: application/vnd.github.raw",
            f"repos/{REPO}/contents/.github/workflows/release.yml?ref={tag}",
            stdout=RELEASE_YML,
        )
        self.gh.on("api", f"repos/{REPO}/commits/{tag}", stdout={"sha": "c" * 40})
        certificate = {
            "buildConfigURI": f"https://github.com/{REPO}/.github/workflows/release.yml@refs/tags/{tag}"
        }
        self.gh.on("attestation", "verify", str(self.work / tag / name), prefix=True,
                   stdout=[{"verificationResult": {"signature": {"certificate": certificate}}}],
                   exit=0 if verified else 1, stderr="" if verified else "expected BuildSignerDigest\n")  # fmt: skip
        self.gh.on("release", "verify", tag, "--repo", REPO)
        self.gh.on("release", "verify-asset", tag, str(self.work / tag / name), "--repo", REPO)

    def run_main(self, *args: str) -> tuple[int, str, str]:
        self.gh.on("api", f"repos/{REPO}/releases?per_page=100&page=1", stdout=self.releases)
        out, err = io.StringIO(), io.StringIO()
        cwd = os.getcwd()
        os.chdir(self.checkout)
        try:
            with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
                code = assemble_site.main(["assemble_site.py", *args])
        finally:
            os.chdir(cwd)
        return code, out.getvalue(), err.getvalue()

    def assemble(self) -> tuple[int, str, str]:
        return self.run_main(str(self.main), str(self.site), str(self.work))

    def versions(self) -> list[tuple[str, str]]:
        data = json.loads((self.site / "versions.json").read_text())
        return [(e["version"], e["status"]) for e in data["versions"]]


class MainOnlyTest(AssembleTestCase):
    def test_main_sits_below_the_root_with_redirects_and_lists(self) -> None:
        code, out, _ = self.assemble()
        self.assertEqual(code, 0, out)
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
        self.assertEqual(self.versions(), [("main", "development")])
        index = ET.parse(self.site / "sitemap.xml").getroot()
        self.assertEqual(
            [e.text for e in index.findall("s:sitemap/s:loc", NS)], [f"{ADDRESS}main/sitemap.xml"]
        )
        self.assertIn(
            "The root serves main/; 2 page(s) from before the versions redirect there.", out
        )
        self.assertNotIn("| Release |", out)

    def test_every_stub_resolves_to_its_page(self) -> None:
        self.assemble()
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


class ReleaseTest(AssembleTestCase):
    def test_every_release_is_verified_and_served_below_its_tag(self) -> None:
        self.release("v1.0.0")
        self.release("v1.1.0", {"index.html": "<html>v1.1.0</html>", "en/index.html": "<html>en</html>",
                                "en/messages/military.html": "<html>msgs</html>"})  # fmt: skip
        self.releases.append({"tag_name": "nightly", "draft": False, "prerelease": False})
        self.releases.append({"tag_name": "v2.0.0", "draft": True, "prerelease": False})
        # a tag with a full-width digit is no release tag
        self.releases.append({"tag_name": "v\uff13.0.0", "draft": False, "prerelease": False})
        code, out, _ = self.assemble()
        self.assertEqual(code, 0, out)
        self.assertEqual(
            self.versions(), [("main", "development"), ("v1.1.0", "latest"), ("v1.0.0", "outdated")]
        )
        entries = json.loads((self.site / "versions.json").read_text())["versions"]
        self.assertNotIn("docs_sha256", entries[0])
        for entry in entries[1:]:
            build = (self.tmp / f"build-{entry['version']}.tar.gz").read_bytes()
            self.assertEqual(entry["docs_sha256"], hashlib.sha256(build).hexdigest())
        self.assertEqual(
            (self.site / "v1.1.0" / "en" / "messages" / "military.html").read_text(),
            "<html>msgs</html>",
        )
        self.assertEqual(target_of((self.site / "index.html").read_text()), "v1.1.0/")
        self.assertEqual(
            target_of((self.site / "en" / "messages" / "military.html").read_text()),
            "../../v1.1.0/en/messages/military.html",
        )
        index = ET.parse(self.site / "sitemap.xml").getroot()
        self.assertEqual(len(index.findall("s:sitemap", NS)), 3)
        self.assertIn("| v1.1.0 | 3 | SHA256SUMS, provenance, release and asset verified |", out)
        verify = [c for c in self.gh.calls() if c[:2] == ["attestation", "verify"]]
        self.assertEqual(len(verify), 2)
        for flag, value in (("--signer-workflow", GEN), ("--signer-digest", "f" * 40), ("--source-digest", "c" * 40),
                            ("--predicate-type", "https://slsa.dev/provenance/v0.2")):  # fmt: skip
            self.assertEqual(verify[0][verify[0].index(flag) + 1], value)
        self.assertIn(["release", "verify", "v1.1.0", "--repo", REPO], self.gh.calls())

    def test_a_page_the_served_release_lacks_redirects_to_main(self) -> None:
        self.release("v1.0.0")
        self.assemble()
        self.assertEqual(
            target_of((self.site / "en" / "index.html").read_text()), "../v1.0.0/en/index.html"
        )
        self.assertEqual(
            target_of((self.site / "en" / "messages" / "military.html").read_text()),
            "../../main/en/messages/military.html",
        )

    def test_a_withdrawn_release_is_served_but_never_at_the_root(self) -> None:
        self.release("v1.0.0")
        self.release("v1.1.0")
        self.status(
            {"v1.1.0": {"reason": "a wrong CRC_EXTRA", "decision": "https://example.org/d/2"}}
        )
        code, out, _ = self.assemble()
        self.assertEqual(code, 0, out)
        self.assertEqual(
            self.versions(),
            [("main", "development"), ("v1.1.0", "withdrawn"), ("v1.0.0", "latest")],
        )
        self.assertEqual(target_of((self.site / "index.html").read_text()), "v1.0.0/")
        self.assertTrue((self.site / "v1.1.0" / "index.html").is_file())

    def test_only_withdrawn_releases_leave_the_root_on_main(self) -> None:
        self.release("v1.0.0")
        self.status({"v1.0.0": {"reason": "r"}})
        self.assemble()
        self.assertEqual(target_of((self.site / "index.html").read_text()), "main/")

    def test_more_than_a_page_of_releases_is_read(self) -> None:
        self.release("v1.0.0")
        self.gh.on("api", f"repos/{REPO}/releases?per_page=100&page=2", stdout=self.releases)
        self.releases = [
            {"tag_name": f"x{i}", "draft": False, "prerelease": False} for i in range(100)
        ]
        code, out, _ = self.assemble()
        self.assertEqual(code, 0, out)
        self.assertEqual(self.versions(), [("main", "development"), ("v1.0.0", "latest")])


class RefusalTest(AssembleTestCase):
    def assert_refused(self, message: str) -> None:
        code, out, _ = self.assemble()
        self.assertEqual(code, 1)
        self.assertIn(f"::error title=docs site::{message}", out)

    def test_a_build_missing_a_needed_file_is_refused(self) -> None:
        for needed in ("index.html", "404.html", "sitemap.xml", "version.json"):
            with self.subTest(needed=needed):
                saved = (self.main / needed).read_text()
                (self.main / needed).unlink()
                self.assert_refused(f"main's build has no {needed}")
                self.write(needed, saved)

    def test_a_build_of_another_version_is_refused(self) -> None:
        self.write("version.json", json.dumps({"schema": 1, "version": "v1.0.0"}))
        self.assert_refused("the build given as main documents another version")

    def test_an_unreadable_or_foreign_sitemap_is_refused(self) -> None:
        self.write("sitemap.xml", "<urlset")
        self.assert_refused("main's sitemap.xml cannot be read: ")
        for body in ("", f"<url><loc>{ADDRESS}en/</loc></url>", "<url><loc/></url>"):
            with self.subTest(body=body):
                self.write(
                    "sitemap.xml", f'<urlset xmlns="{assemble_site.SITEMAP_NS}">{body}</urlset>'
                )
                self.assert_refused("main's sitemap names no page below main/")

    def test_an_existing_site_is_refused(self) -> None:
        self.site.mkdir()
        self.assert_refused(f"{self.site} exists already")

    def test_a_release_whose_archive_does_not_match_its_sums_is_refused(self) -> None:
        self.release("v1.0.0", sums_ok=False)
        self.assert_refused(
            "v1.0.0: mavlink-m-1.0.0-docs.tar.gz does not match its SHA256SUMS line"
        )
        self.assertFalse((self.site / "v1.0.0").exists())

    def test_a_release_whose_provenance_does_not_verify_is_refused(self) -> None:
        self.release("v1.0.0", verified=False)
        code, out, _ = self.assemble()
        self.assertEqual(code, 1)
        self.assertIn("::error title=docs site::gh attestation verify", out)
        self.assertIn("expected BuildSignerDigest", out)

    def test_a_release_whose_workflow_names_no_generator_is_refused(self) -> None:
        self.gh.on(
            "api",
            "-H",
            "Accept: application/vnd.github.raw",
            f"repos/{REPO}/contents/.github/workflows/release.yml?ref=v1.0.0",
            stdout="env: {}\n",
        )
        self.release("v1.0.0")
        self.assert_refused("v1.0.0: release.yml at the tag names no generator workflow and commit")

    def test_an_archive_without_an_index_is_refused(self) -> None:
        self.release("v1.0.0", {"en/index.html": "x"})
        self.assert_refused("v1.0.0: mavlink-m-1.0.0-docs.tar.gz has no index.html")

    def test_a_release_status_file_that_is_wrong_is_refused(self) -> None:
        for withdrawn, message in (
            ([], "withdrawn must map release tags to their reasons"),
            ({"v1.0": {"reason": "r"}}, "'v1.0' needs to be a release tag with a reason"),
            ({"v1.0.0": {}}, "'v1.0.0' needs to be a release tag with a reason"),
            ({"v9.0.0": {"reason": "r"}}, "withdraws releases that are not published: ['v9.0.0']"),
        ):  # fmt: skip
            with self.subTest(withdrawn=withdrawn):
                self.status(withdrawn)
                self.assert_refused("")
                self.assertIn(message, self.assemble()[1])

    def test_a_failed_listing_is_refused(self) -> None:
        self.gh.on("api", f"repos/{REPO}/releases?per_page=100&page=1", exit=1, stderr="HTTP 401\n")
        self.assert_refused(
            "gh api repos/Dronecode/mavlink-military/releases?per_page=100&page=1: HTTP 401"
        )

    def test_usage_and_script(self) -> None:
        self.assertEqual(self.run_main(str(self.main))[0], 2)
        with mock.patch.object(sys, "argv", ["assemble_site.py"]), contextlib.redirect_stderr(
            io.StringIO()
        ):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(assemble_site.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
