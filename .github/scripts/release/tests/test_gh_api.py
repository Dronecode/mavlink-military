#!/usr/bin/env python3
"""Tests for gh_api.py, with a stand-in gh. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_gh_api.py'
"""

from __future__ import annotations

import os
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import gh_api  # noqa: E402
from fake_gh import FakeGh  # noqa: E402


class GhApiTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.gh = FakeGh(Path(tmp.name))
        patcher = mock.patch.dict(os.environ, self.gh.env())
        patcher.start()
        self.addCleanup(patcher.stop)

    def test_a_call_returns_its_output(self) -> None:
        self.gh.on("api", "repos/o/r", stdout={"name": "r"})
        self.assertEqual(gh_api.api("repos/o/r"), {"name": "r"})
        self.assertEqual(gh_api.run("api", "repos/o/r"), '{"name": "r"}')

    def test_an_empty_answer_is_none(self) -> None:
        self.gh.on("api", "repos/o/r/dispatches", stdout="")
        self.assertIsNone(gh_api.api("repos/o/r/dispatches"))

    def test_an_answer_that_is_not_json_fails(self) -> None:
        self.gh.on("api", "repos/o/r", stdout="<html>")
        with self.assertRaises(gh_api.GitHubError) as caught:
            gh_api.api("repos/o/r")
        self.assertIn("gh api repos/o/r: not JSON", str(caught.exception))

    def test_a_lasting_failure_is_not_retried(self) -> None:
        self.gh.on("api", "repos/o/r", exit=1, stderr="gh: Not Found (HTTP 404)\n")
        with self.assertRaises(gh_api.GitHubError) as caught:
            gh_api.api("repos/o/r")
        self.assertEqual(str(caught.exception), "gh api repos/o/r: gh: Not Found (HTTP 404)")
        self.assertEqual(len(self.gh.calls()), 1)

    def test_a_failure_without_a_message_names_its_exit_status(self) -> None:
        self.gh.on("api", "repos/o/r", exit=4)
        with self.assertRaises(gh_api.GitHubError) as caught:
            gh_api.run("api", "repos/o/r")
        self.assertEqual(str(caught.exception), "gh api repos/o/r: exit 4")

    def test_a_server_error_is_retried(self) -> None:
        self.gh.on("api", "repos/o/r", exit=1, stderr="HTTP 502: Bad Gateway\n", times=1)
        self.gh.on("api", "repos/o/r", stdout={"ok": True})
        with mock.patch.object(gh_api.time, "sleep") as sleep:
            self.assertEqual(gh_api.api("repos/o/r"), {"ok": True})
        self.assertEqual(len(self.gh.calls()), 2)
        sleep.assert_called_once_with(0.0)

    def test_retries_end_with_a_failure(self) -> None:
        self.gh.on("api", "repos/o/r", exit=1, stderr="API rate limit exceeded\n")
        with mock.patch.dict(
            os.environ, {"GH_RETRIES": "2", "GH_RETRY_DELAY": "1.5"}
        ), mock.patch.object(gh_api.time, "sleep") as sleep:
            with self.assertRaises(gh_api.GitHubError) as caught:
                gh_api.api("repos/o/r")
        self.assertIn("rate limit", str(caught.exception))
        self.assertEqual(len(self.gh.calls()), 3)
        self.assertEqual([c.args for c in sleep.call_args_list], [(1.5,), (3.0,)])

    def test_a_write_is_sent_once(self) -> None:
        for args in (
            ("api", "-X", "DELETE", "repos/o/r/releases/1"),
            ("api", "--method=PATCH", "repos/o/r/releases/1"),
            ("api", "repos/o/r/releases", "-f", "tag_name=v1.0.0"),
            ("api", "repos/o/r/releases", "--input=release.json"),
            ("release", "create", "v1.0.0", "--draft"),
            ("release", "upload", "v1.0.0", "file"),
        ):
            with self.subTest(args=args):
                self.gh.responses.clear()
                self.gh.on(*args, exit=1, stderr="HTTP 502: Bad Gateway\n")
                before = len(self.gh.calls())
                with mock.patch.object(gh_api.time, "sleep") as sleep:
                    with self.assertRaises(gh_api.GitHubError):
                        gh_api.run(*args)
                self.assertEqual(len(self.gh.calls()) - before, 1)
                sleep.assert_not_called()

    def test_reads(self) -> None:
        for args in (
            ("api", "repos/o/r"),
            ("api", "-X", "GET", "search/code", "-f", "q=x"),
            ("api", "--method", "get", "repos/o/r"),
            ("release", "download", "v1.0.0"),
            ("attestation", "verify", "file"),
        ):
            with self.subTest(args=args):
                self.assertTrue(gh_api.is_read(args))
        self.assertFalse(gh_api.is_read(("api", "-X")))

    def test_the_command_defaults_to_gh(self) -> None:
        with mock.patch.dict(os.environ), mock.patch.object(gh_api.subprocess, "run") as run:
            os.environ.pop("GH", None)
            run.return_value = mock.Mock(returncode=0, stdout="[]", stderr="")
            self.assertEqual(gh_api.api("repos/o/r"), [])
        self.assertEqual(run.call_args.args[0], ["gh", "api", "repos/o/r"])


if __name__ == "__main__":
    unittest.main()
