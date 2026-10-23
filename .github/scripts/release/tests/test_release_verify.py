#!/usr/bin/env python3
"""Tests for release_verify.py, with a stand-in gh. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_release_verify.py'
"""

from __future__ import annotations

import base64
import contextlib
import hashlib
import io
import json
import os
import runpy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
sys.path.insert(0, str(HERE))
import archive  # noqa: E402
import release_verify as rv  # noqa: E402
from fake_gh import FakeGh  # noqa: E402

REPO = "Dronecode/mavlink-military"
GEN = "slsa-framework/slsa-github-generator"
WORKFLOW = f"{GEN}/.github/workflows/generator_generic_slsa3.yml"
COMMIT = "f" * 40
SHA = "c" * 40
RELEASE_YML = f"env:\n  GENERATOR_WORKFLOW: {WORKFLOW}\n  GENERATOR_TAG: v2.1.0\n  GENERATOR_COMMIT: {COMMIT}\n"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


class VerifyCase(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)
        self.checkout = self.tmp / "checkout"
        (self.checkout / ".github" / "workflows").mkdir(parents=True)
        (self.checkout / ".github" / "workflows" / "release.yml").write_text(RELEASE_YML)
        self.gh = FakeGh(self.tmp)
        self.releases: list[dict] = []
        self.tags: list[dict] = []
        self.site: dict[str, dict] = {}
        patcher = mock.patch.dict(
            os.environ,
            {**self.gh.env(), "GITHUB_REPOSITORY": REPO, "DOCS_SITE": "https://docs.example.org"},
        )
        patcher.start()
        self.addCleanup(patcher.stop)

    def release(self, tag: str, **changes: object) -> dict:
        """A published release whose files, record and attestations all check out."""
        v = tag[1:]
        files = {
            f"mavlink-m-{v}-c.tar.gz": b"c",
            f"mavlink-m-{v}-notes.md": f"# MAVLink-M {v}\n".encode(),
        }
        sums = "".join(f"{digest(d)}  {n}\n" for n, d in sorted(files.items())).encode()
        bundle = json.dumps(
            {"dsseEnvelope": {"payload": base64.b64encode(b"{}").decode()}}
        ).encode()
        record_assets = {f"mavlink-m-{v}.intoto.jsonl": f"sha256:{digest(bundle)}"}
        record = json.dumps({"assets": record_assets}).encode()
        assets = {
            **files,
            "SHA256SUMS": sums,
            f"mavlink-m-{v}.intoto.jsonl": bundle,
            f"mavlink-m-{v}-publish.json": record,
        }
        entry = {
            "tag_name": tag, "name": f"MAVLink-M {v}", "draft": False, "prerelease": False, "immutable": True,
            "body": files[f"mavlink-m-{v}-notes.md"].decode(),
            "assets": [{"name": n, "digest": f"sha256:{digest(d)}"} for n, d in assets.items()],
        }  # fmt: skip
        entry.update(changes)
        self.releases.append(entry)
        self.tags.append({"name": tag})
        self.gh.on("release", "download", tag, "--repo", REPO, "--dir", prefix=True, files=assets)
        self.gh.on(
            "api",
            "-H",
            "Accept: application/vnd.github.raw",
            f"repos/{REPO}/contents/.github/workflows/release.yml?ref={tag}",
            stdout=RELEASE_YML,
        )
        self.gh.on("api", f"repos/{REPO}/commits/{tag}", stdout={"sha": SHA})
        certificate = {
            "buildConfigURI": f"https://github.com/{REPO}/.github/workflows/release.yml@refs/tags/{tag}"
        }
        self.gh.on("attestation", "verify", prefix=True, contains=[f"refs/tags/{tag}"],
                   stdout=[{"verificationResult": {"signature": {"certificate": certificate}}}])  # fmt: skip
        self.gh.on("release", "verify", tag, "--repo", REPO)
        self.gh.on("release", "verify-asset", tag, prefix=True)
        self.site[f"https://docs.example.org/{tag}/version.json"] = {"version": tag, "commit": SHA}
        return entry

    def generator(
        self,
        sha: str = COMMIT,
        archived: bool = False,
        advisories: list | None = None,
        newest: str = "v2.1.0",
    ) -> None:
        self.gh.on(
            "api",
            f"repos/{GEN}/git/ref/tags/v2.1.0",
            stdout={"object": {"type": "commit", "sha": sha}},
        )
        self.gh.on("api", f"repos/{GEN}", stdout={"archived": archived})
        self.gh.on(
            "api", f"repos/{GEN}/releases/tags/v2.1.0", stdout={"draft": False, "prerelease": False}
        )
        self.gh.on("api", f"/advisories?affects={GEN}&per_page=100", stdout=advisories or [])
        self.gh.on("api", f"repos/{GEN}/security-advisories?per_page=100", stdout=[])
        self.gh.on("api", f"repos/{GEN}/releases/latest", stdout={"tag_name": newest})

    def listings(self, latest: str | None = None) -> None:
        self.gh.on("api", f"repos/{REPO}/releases?per_page=100&page=1", stdout=self.releases)
        self.gh.on("api", f"repos/{REPO}/tags?per_page=100&page=1", stdout=self.tags)
        self.gh.on("attestation", "trusted-root", stdout='{"root": 1}\n')
        if latest:
            self.gh.on("api", f"repos/{REPO}/releases/latest", stdout={"tag_name": latest})

    def run_main(self, *args: str, output: Path | None = None) -> tuple[int, str]:
        out = io.StringIO()
        cwd = os.getcwd()
        os.chdir(self.checkout)
        env = {"GITHUB_OUTPUT": str(output)} if output else {}
        try:
            with mock.patch.dict(os.environ, env), mock.patch.object(
                rv, "site_record", side_effect=lambda url: self.site[url]
            ):
                if not output:
                    # The runner sets GITHUB_OUTPUT for every step, the test step among them.
                    os.environ.pop("GITHUB_OUTPUT", None)
                with contextlib.redirect_stdout(out), contextlib.redirect_stderr(io.StringIO()):
                    code = rv.main(["release_verify.py", *args])
        finally:
            os.chdir(cwd)
        return code, out.getvalue()

    def verify(self) -> tuple[int, str, dict]:
        report = self.tmp / "report.json"
        code, out = self.run_main("verify", str(report))
        return code, out, json.loads(report.read_text()) if report.exists() else {}


class ListTest(VerifyCase):
    def test_no_release_lists_none(self) -> None:
        self.listings()
        output = self.tmp / "out"
        code, out = self.run_main("list", output=output)
        self.assertEqual((code, out), (0, "0 release(s): none\n"))
        self.assertEqual(output.read_text(), "tags=[]\ncount=0\n")

    def test_releases_are_listed_from_the_highest(self) -> None:
        self.release("v1.0.0")
        self.release("v1.2.0")
        self.tags.append({"name": "nightly"})
        self.listings()
        output = self.tmp / "out"
        self.assertEqual(self.run_main("list", output=output)[0], 0)
        self.assertEqual(output.read_text(), 'tags=["v1.2.0", "v1.0.0"]\ncount=2\n')
        self.assertEqual(self.run_main("list")[0], 0)

    def test_tags_and_releases_that_disagree_fail(self) -> None:
        self.release("v1.0.0")
        self.releases.append({"tag_name": "beta", "draft": False, "prerelease": False})
        self.releases.append({"tag_name": "v2.0.0", "draft": True, "prerelease": False})
        self.releases.append({"tag_name": "v\uff14.0.0", "draft": False, "prerelease": False})
        self.tags.append({"name": "v3.0.0"})
        self.listings()
        code, out = self.run_main("list")
        self.assertEqual(code, 1)
        self.assertIn("release 'beta' is not on a vX.Y.Z tag", out)
        self.assertIn("release 'v\uff14.0.0' is not on a vX.Y.Z tag", out)  # a full-width digit
        self.assertIn("release v2.0.0 is a draft or a pre-release", out)
        self.assertIn("tag v3.0.0 has 0 releases", out)

    def test_more_than_a_page_is_read(self) -> None:
        self.release("v1.0.0")
        self.gh.on("api", f"repos/{REPO}/releases?per_page=100&page=2", stdout=self.releases)
        self.releases = [{"tag_name": "v1.0.0", "draft": False, "prerelease": False}] * 0 + [
            {"tag_name": f"v0.0.{i}", "draft": False, "prerelease": False} for i in range(100)]  # fmt: skip
        self.tags += [{"name": f"v0.0.{i}"} for i in range(100)]
        self.gh.on("api", f"repos/{REPO}/tags?per_page=100&page=2", stdout=self.tags[100:])
        self.tags = self.tags[:100]
        self.listings()
        output = self.tmp / "out"
        self.assertEqual(self.run_main("list", output=output)[0], 0)
        self.assertIn("count=101", output.read_text())


class VerifyTest(VerifyCase):
    def test_a_good_release_and_generator_pass(self) -> None:
        self.release("v1.0.0")
        self.listings(latest="v1.0.0")
        self.generator(newest="v2.2.0")
        code, out, report = self.verify()
        self.assertEqual(code, 0, out)
        self.assertIn(
            "::notice title=release verification::the generator has a newer release, v2.2.0", out
        )
        self.assertIn("1 release(s) checked at", out)
        self.assertEqual(report["releases"], [{"tag": "v1.0.0", "failures": []}])
        offline = [
            c
            for c in self.gh.calls()
            if c[:2] == ["attestation", "verify"] and "--custom-trusted-root" in c
        ]
        self.assertEqual(len(offline), 1)
        self.assertEqual(sum(1 for c in self.gh.calls() if c[:2] == ["release", "verify-asset"]), 5)

    def test_no_release_checks_the_generator_alone(self) -> None:
        self.listings()
        self.generator()
        code, _, report = self.verify()
        self.assertEqual((code, report["releases"], report["failures"]), (0, [], []))
        self.assertNotIn(["attestation", "trusted-root"], self.gh.calls())

    def test_every_release_check_reports_its_failure(self) -> None:
        self.release("v1.0.0", immutable=False, name="Other", body="other")
        self.site["https://docs.example.org/v1.0.0/version.json"] = {
            "version": "v0.9.0",
            "commit": SHA,
        }
        self.listings(latest="v1.0.0")
        self.generator()
        code, out, report = self.verify()
        self.assertEqual(code, 1)
        failures = report["releases"][0]["failures"]
        self.assertEqual(len(failures), 4)
        self.assertIn("v1.0.0: the release is not immutable", failures)
        self.assertIn("v1.0.0: the title is 'Other'", failures)
        self.assertIn("v1.0.0: the release notes differ from the notes asset", failures)
        self.assertIn("v1.0.0: the docs site serves v0.9.0 at " + SHA, failures)

    def test_assets_that_differ_and_a_failed_check_are_reported(self) -> None:
        entry = self.release("v1.0.0")
        entry["assets"] = entry["assets"][:-1]
        self.release("v1.1.0")
        self.gh.responses.insert(0, {"args": ["release", "verify", "v1.1.0", "--repo", REPO], "stdout": "", "exit": 1,
                                     "stderr": "no attestation found\n", "prefix": False, "times": None})  # fmt: skip
        self.gh.save()
        self.listings(latest="v1.1.0")
        self.generator()
        code, out, report = self.verify()
        self.assertEqual(code, 1)
        self.assertIn("v1.0.0: the assets differ from SHA256SUMS and the publish record", out)
        self.assertIn("v1.1.0: gh release verify v1.1.0", out)

    def test_the_latest_flag_must_sit_on_the_highest_release_not_withdrawn(self) -> None:
        self.release("v1.0.0")
        self.release("v1.1.0")
        (self.checkout / ".github" / "release-status.json").write_text(
            json.dumps({"withdrawn": {"v1.1.0": {"reason": "r"}}})
        )
        self.listings(latest="v1.1.0")
        self.generator()
        code, out, _ = self.verify()
        self.assertEqual(code, 1)
        self.assertIn("the latest release is v1.1.0, not v1.0.0", out)

    def test_generator_shortfalls_fail(self) -> None:
        for kwargs, message in (
            ({"sha": "0" * 40}, "generator: "),
            ({"advisories": [{"ghsa_id": "GHSA-xxxx"}]}, "generator advisories to review: ['GHSA-xxxx']"),
        ):  # fmt: skip
            with self.subTest(message=message):
                self.gh.responses.clear()
                self.listings()
                self.generator(**kwargs)
                code, out, _ = self.verify()
                self.assertEqual(code, 1)
                self.assertIn(message, out)

    def test_a_reviewed_advisory_passes(self) -> None:
        (self.checkout / ".github" / "release-status.json").write_text(
            json.dumps({"reviewed_generator_advisories": ["GHSA-xxxx"]})
        )
        self.listings()
        self.generator(advisories=[{"ghsa_id": "GHSA-xxxx"}])
        self.assertEqual(self.verify()[0], 0)

    def test_a_failed_listing_fails_the_run(self) -> None:
        code, out, report = self.verify()
        self.assertEqual((code, report), (1, {}))
        self.assertIn("::error title=release verification::", out)


class RebuildTest(VerifyCase):
    def test_the_plan_comes_from_the_evidence_bundle(self) -> None:
        evidence = self.tmp / "e.tar.gz"
        archive.write(evidence, "mavlink-m-1.0.0-evidence", {"plan.json": b'{"tag": "v1.0.0"}'}, 0)
        self.gh.on("release", "download", "v1.0.0", "--repo", REPO, "--dir", prefix=True,
                   files={"mavlink-m-1.0.0-evidence.tar.gz": evidence.read_bytes()})  # fmt: skip
        code, out = self.run_main("plan", "v1.0.0", str(self.tmp / "plan"))
        self.assertEqual(code, 0, out)
        self.assertEqual(
            json.loads((self.tmp / "plan" / "plan.json").read_text()), {"tag": "v1.0.0"}
        )

    def build(self, files: dict[str, bytes]) -> Path:
        build = self.tmp / "build"
        build.mkdir(exist_ok=True)
        (build / "SHA256SUMS").write_text("".join(f"{digest(d)}  {n}\n" for n, d in files.items()))
        return build

    def test_a_rebuild_that_matches_passes_and_one_that_differs_fails(self) -> None:
        published = f"{digest(b'c')}  a.tar.gz\n{digest(b'n')}  notes.md\n"
        self.gh.on(
            "release",
            "download",
            "v1.0.0",
            "--repo",
            REPO,
            "--dir",
            prefix=True,
            files={"SHA256SUMS": published},
        )
        code, out = self.run_main("compare", "v1.0.0", str(self.build({"a.tar.gz": b"c"})))
        self.assertEqual((code, out), (0, "v1.0.0: 1 package files rebuilt byte for byte\n"))
        code, out = self.run_main("compare", "v1.0.0", str(self.build({"a.tar.gz": b"other"})))
        self.assertEqual(code, 1)
        self.assertIn("v1.0.0: the rebuild differs from the release in ['a.tar.gz']", out)

    def test_a_malformed_sums_file_fails(self) -> None:
        self.gh.on(
            "release",
            "download",
            "v1.0.0",
            "--repo",
            REPO,
            "--dir",
            prefix=True,
            files={"SHA256SUMS": "bad\n"},
        )
        code, out = self.run_main("compare", "v1.0.0", str(self.build({})))
        self.assertEqual(code, 1)
        self.assertIn("has a malformed line", out)

    def test_the_site_record_is_read_over_http(self) -> None:
        response = mock.MagicMock()
        response.__enter__.return_value.read.return_value = b'{"version": "v1.0.0"}'
        with mock.patch.object(rv.urllib.request, "urlopen", return_value=response):
            self.assertEqual(
                rv.site_record("https://docs.example.org/v1.0.0/version.json"),
                {"version": "v1.0.0"},
            )

    def test_usage_and_script(self) -> None:
        for args in ((), ("verify",), ("other", "x"), ("compare", "v1.0.0")):
            with self.subTest(args=args):
                self.assertEqual(self.run_main(*args)[0], 2)
        with mock.patch.object(sys, "argv", ["release_verify.py"]), contextlib.redirect_stderr(
            io.StringIO()
        ):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(rv.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
