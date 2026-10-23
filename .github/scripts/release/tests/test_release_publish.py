#!/usr/bin/env python3
"""Tests for release_publish.py, with a stand-in gh. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_release_publish.py'
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
import release_publish as rp  # noqa: E402
from fake_gh import FakeGh  # noqa: E402

GEN = "slsa-framework/slsa-github-generator"
WORKFLOW = f"{GEN}/.github/workflows/generator_generic_slsa3.yml"
COMMIT = "f" * 40
REPO = "Dronecode/mavlink-military"
SHA = "c" * 40
TAG, V = "v1.2.3", "1.2.3"
ENV = {
    "GENERATOR_WORKFLOW": WORKFLOW, "GENERATOR_TAG": "v2.1.0", "GENERATOR_COMMIT": COMMIT,
    "GENERATOR_ACTIONS": f"{GEN}@v2.1.0={COMMIT}", "GITHUB_REPOSITORY": REPO, "GITHUB_SHA": SHA,
    "GITHUB_REF": f"refs/tags/{TAG}", "GITHUB_RUN_ID": "77", "GITHUB_RUN_ATTEMPT": "1",
    "GITHUB_SERVER_URL": "https://github.com", "RELEASE_TAG": TAG, "RELEASE_VERSION": V,
}  # fmt: skip
CERTIFICATE = {
    "buildSignerURI": f"https://github.com/{WORKFLOW}@refs/tags/v2.1.0", "buildSignerDigest": COMMIT,
    "buildConfigURI": f"https://github.com/{REPO}/.github/workflows/release.yml@refs/tags/{TAG}",
    "sourceRepositoryRef": f"refs/tags/{TAG}", "sourceRepositoryDigest": SHA, "runnerEnvironment": "github-hosted",
}  # fmt: skip
AUDIT = {"generator": {"workflow": WORKFLOW, "tag": "v2.1.0", "commit": COMMIT},
         "jobs": [{"name": "Sign the provenance / generator", "seconds": 90}],
         "approvals": [{"state": "approved", "comment": "", "environments": ["release"]}]}  # fmt: skip


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


class PublishCase(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)
        self.files = self.tmp / "files"
        self.files.mkdir()
        self.contents = {f"mavlink-m-{V}-c.tar.gz": b"c", f"mavlink-m-{V}-notes.md": b"# notes\n"}
        for name, data in self.contents.items():
            (self.files / name).write_bytes(data)
        sums = "".join(f"{digest(d)}  {n}\n" for n, d in sorted(self.contents.items())).encode()
        (self.files / "SHA256SUMS").write_bytes(sums)
        self.contents["SHA256SUMS"] = sums
        self.bundle = self.tmp / f"mavlink-m-{V}.intoto.jsonl"
        self.sign(sorted((n, digest(d)) for n, d in self.contents.items()))
        self.gh = FakeGh(self.tmp)
        patcher = mock.patch.dict(os.environ, {**self.gh.env(), **ENV})
        patcher.start()
        self.addCleanup(patcher.stop)

    def sign(self, subjects: list[tuple[str, str]]) -> None:
        statement = {"subject": [{"name": n, "digest": {"sha256": d}} for n, d in subjects]}
        payload = base64.b64encode(json.dumps(statement).encode()).decode()
        self.bundle.write_text(json.dumps({"dsseEnvelope": {"payload": payload}}) + "\n")

    def happy(self, certificate: dict | None = None, existing: list | None = None, server: dict | None = None,
              downloaded: dict | None = None) -> None:  # fmt: skip
        self.gh.on("attestation", "verify", prefix=True,
                   stdout=[{"verificationResult": {"signature": {"certificate": certificate or CERTIFICATE}}}])  # fmt: skip
        self.gh.on(
            "api",
            f"repos/{GEN}/git/ref/tags/v2.1.0",
            stdout={"object": {"type": "commit", "sha": COMMIT}},
        )
        self.gh.on("api", f"repos/{GEN}", stdout={"archived": False})
        self.gh.on(
            "api", f"repos/{GEN}/releases/tags/v2.1.0", stdout={"draft": False, "prerelease": False}
        )
        # The release tag is annotated: its ref names the tag object, which names the commit.
        self.gh.on(
            "api",
            f"repos/{REPO}/git/ref/tags/{TAG}",
            stdout={"object": {"type": "tag", "sha": "a" * 40}},
        )
        self.gh.on("api", f"repos/{REPO}/git/tags/{'a' * 40}", stdout={"object": {"type": "commit", "sha": SHA}})  # fmt: skip
        self.gh.on(
            "api",
            f"repos/{REPO}/releases?per_page=100",
            stdout=existing if existing is not None else [],
            times=1,
        )
        self.gh.on("api", "-X", "DELETE", f"repos/{REPO}/releases/5")
        self.gh.on("release", "create", TAG, prefix=True)
        self.gh.on(
            "api",
            f"repos/{REPO}/releases?per_page=100",
            stdout=[{"tag_name": TAG, "draft": True, "id": 9}],
        )
        assets = dict(self.contents, **{self.bundle.name: self.bundle.read_bytes()})
        self.gh.on("api", f"repos/{REPO}/releases/9/assets?per_page=100", stdout=[
            {"name": n, "digest": f"sha256:{digest(d)}"} for n, d in (server or assets).items()])  # fmt: skip
        self.gh.on("release", "upload", TAG, prefix=True)
        self.gh.on("release", "edit", TAG, "--repo", REPO, "--draft=false", "--latest")
        self.downloads = downloaded if downloaded is not None else assets
        self.gh.on(
            "release", "download", TAG, "--repo", REPO, "--dir", prefix=True, files=self.downloads
        )

    def run_main(self, env: dict | None = None) -> tuple[int, str]:
        audit = self.tmp / "audit.json"
        audit.write_text(json.dumps(AUDIT))
        out = io.StringIO()
        with mock.patch.dict(os.environ, env or {}), contextlib.redirect_stdout(
            out
        ), contextlib.redirect_stderr(io.StringIO()):
            code = rp.main(["release_publish.py", str(self.files), str(self.bundle), str(audit)])
        return code, out.getvalue()


class PublishTest(PublishCase):
    def test_a_verified_release_is_published_and_verified_again(self) -> None:
        self.happy(existing=[{"tag_name": "v1.0.0", "draft": False, "id": 3}])
        # The publish record is uploaded before publication and is downloaded with the rest.
        record_holder = {}
        real_run = rp.gh_api.run

        def capture(*args: str) -> str:
            if args[:2] == ("release", "upload"):
                record = Path(args[-1])
                record_holder["data"] = record.read_bytes()
                self.gh.responses[-1]["files"][record.name] = record_holder["data"].decode(
                    "latin-1"
                )
                self.gh.save()
            return real_run(*args)

        summary = self.tmp / "summary.md"
        with mock.patch.object(rp.gh_api, "run", side_effect=capture):
            code, out = self.run_main({"GITHUB_STEP_SUMMARY": str(summary)})
        self.assertEqual(code, 0, out)
        self.assertIn(f"published {TAG} with 5 assets", out)
        record = json.loads(record_holder["data"])
        self.assertEqual(record["provenance"]["certificate"], CERTIFICATE)
        self.assertEqual(record["approvals"], AUDIT["approvals"])
        self.assertEqual(sorted(record["assets"]), sorted(list(self.contents) + [self.bundle.name]))
        calls = self.gh.calls()
        verify = [c for c in calls if c[:2] == ["attestation", "verify"]]
        self.assertEqual(len(verify), 4)  # three subjects, then SHA256SUMS again after publication
        self.assertEqual(verify[0][verify[0].index("--signer-digest") + 1], COMMIT)
        self.assertIn("--deny-self-hosted-runners", verify[0])
        self.assertEqual(
            verify[0][verify[0].index("--predicate-type") + 1], "https://slsa.dev/provenance/v0.2"
        )
        create = next(c for c in calls if c[:2] == ["release", "create"])
        self.assertIn("--draft", create)
        self.assertIn("--verify-tag", create)
        order = [c[:2] for c in calls if c[0] == "release"]
        self.assertEqual(
            order,
            [
                ["release", "create"],
                ["release", "upload"],
                ["release", "edit"],
                ["release", "download"],
            ],
        )
        self.assertIn(f"Built by: {CERTIFICATE['buildConfigURI']}", summary.read_text())

    def test_a_draft_left_by_a_failed_attempt_is_replaced(self) -> None:
        self.happy(existing=[{"tag_name": TAG, "draft": True, "id": 5}])
        with mock.patch.object(rp, "sha256", side_effect=rp.sha256):
            code, out = self.run_main()
        self.assertIn(["api", "-X", "DELETE", f"repos/{REPO}/releases/5"], self.gh.calls())
        self.assertEqual(
            code, 1
        )  # the stand-in download does not hold the record, so the last check fails
        self.assertIn("the published release's files differ from what was uploaded", out)

    def test_a_published_release_is_never_touched(self) -> None:
        self.happy(existing=[{"tag_name": TAG, "draft": False, "id": 5}])
        code, out = self.run_main()
        self.assertEqual(code, 1)
        self.assertIn(f"{TAG} is published already", out)
        self.assertFalse(any(c[:2] == ["release", "create"] for c in self.gh.calls()))


class RefusalTest(PublishCase):
    def assert_refused(self, message: str) -> None:
        code, out = self.run_main()
        self.assertEqual(code, 1)
        self.assertIn(message, out)
        self.assertFalse(any(c[:2] == ["release", "create"] for c in self.gh.calls()))

    def test_a_bundle_with_another_name_is_refused(self) -> None:
        other = self.tmp / "other.intoto.jsonl"
        self.bundle.rename(other)
        self.bundle = other
        self.happy()
        self.assert_refused(f"the provenance is other.intoto.jsonl, not mavlink-m-{V}.intoto.jsonl")

    def test_subjects_that_differ_from_the_sums_are_refused(self) -> None:
        self.sign([("SHA256SUMS", "0" * 64)])
        self.happy()
        self.assert_refused("the provenance signs other subjects than SHA256SUMS lists")

    def test_a_bundle_without_a_statement_is_refused(self) -> None:
        self.bundle.write_text("{}\n")
        self.happy()
        self.assert_refused("holds no signed in-toto statement")

    def test_a_file_that_does_not_match_the_sums_is_refused(self) -> None:
        (self.files / f"mavlink-m-{V}-c.tar.gz").write_bytes(b"changed")
        self.happy()
        self.assert_refused(f"mavlink-m-{V}-c.tar.gz is missing or does not match SHA256SUMS")

    def test_a_malformed_sums_line_is_refused(self) -> None:
        (self.files / "SHA256SUMS").write_text("bad line\n")
        self.happy()
        self.assert_refused("SHA256SUMS has a malformed line")

    def test_a_failed_verification_is_refused(self) -> None:
        self.gh.on(
            "attestation",
            "verify",
            prefix=True,
            exit=1,
            stderr="expected BuildSignerDigest to be f...\n",
        )
        self.assert_refused("expected BuildSignerDigest")

    def test_provenance_built_by_another_workflow_is_refused(self) -> None:
        self.happy(
            certificate=dict(
                CERTIFICATE,
                buildConfigURI=f"https://github.com/{REPO}/.github/workflows/other.yml@refs/tags/{TAG}",
            )
        )
        self.assert_refused("the provenance was built by")

    def test_a_verification_without_a_certificate_is_refused(self) -> None:
        self.gh.on("attestation", "verify", prefix=True, stdout=[])
        self.assert_refused("gh attestation verify gave no certificate")

    def test_a_release_tag_that_names_another_commit_now_is_refused(self) -> None:
        self.gh.on(
            "api",
            f"repos/{REPO}/git/ref/tags/{TAG}",
            stdout={"object": {"type": "commit", "sha": "0" * 40}},
        )
        self.happy()
        self.assert_refused(f"{TAG} names {'0' * 40} now, not {SHA}, the commit this run built")  # fmt: skip

    def test_a_lightweight_release_tag_on_the_commit_passes_that_check(self) -> None:
        self.assertEqual(self.lightweight(), SHA)

    def lightweight(self) -> str:
        self.gh.on(
            "api",
            f"repos/{REPO}/git/ref/tags/{TAG}",
            stdout={"object": {"type": "commit", "sha": SHA}},
        )
        return rp.tag_commit(REPO, TAG)  # fmt: skip

    def test_a_moved_generator_tag_is_refused(self) -> None:
        self.gh.on(
            "api",
            f"repos/{GEN}/git/ref/tags/v2.1.0",
            stdout={"object": {"type": "commit", "sha": "0" * 40}},
        )
        self.happy()
        self.assert_refused("not the reviewed")


class DraftTest(PublishCase):
    def test_no_draft_after_creation_fails(self) -> None:
        self.happy()
        self.gh.responses = [
            r
            for r in self.gh.responses
            if not (
                r["args"] == ["api", f"repos/{REPO}/releases?per_page=100"] and r["times"] is None
            )
        ]
        self.gh.on("api", f"repos/{REPO}/releases?per_page=100", stdout=[])
        code, out = self.run_main()
        self.assertEqual(code, 1)
        self.assertIn(f"no draft release appeared for {TAG}", out)

    def test_server_digests_that_differ_fail(self) -> None:
        self.happy(server={f"mavlink-m-{V}-c.tar.gz": b"other"})
        code, out = self.run_main()
        self.assertEqual(code, 1)
        self.assertIn("the draft's assets differ from the files", out)
        self.assertFalse(any(c[:2] == ["release", "edit"] for c in self.gh.calls()))


class MainTest(PublishCase):
    def test_usage_and_script(self) -> None:
        with contextlib.redirect_stderr(io.StringIO()):
            self.assertEqual(rp.main(["release_publish.py"]), 2)
        with mock.patch.object(sys, "argv", ["release_publish.py"]), contextlib.redirect_stderr(
            io.StringIO()
        ):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(rp.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)

    def test_an_unreadable_audit_record_fails(self) -> None:
        audit = self.tmp / "missing.json"
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            code = rp.main(["release_publish.py", str(self.files), str(self.bundle), str(audit)])
        self.assertEqual(code, 1)
        self.assertIn("::error title=release publish::", out.getvalue())

    def test_no_summary_without_its_file(self) -> None:
        record = {
            "tag": TAG,
            "assets": {"a": "sha256:0"},
            "provenance": {"certificate": CERTIFICATE},
        }
        with mock.patch.object(rp, "publish", return_value=record), mock.patch.dict(os.environ):
            os.environ.pop("GITHUB_STEP_SUMMARY", None)
            code, out = self.run_main()
        self.assertEqual((code, out), (0, f"published {TAG} with 2 assets\n"))


if __name__ == "__main__":
    unittest.main()
