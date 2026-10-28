"""Tests for check_commits.sh, on a scratch repository built for each test.

From the repository root:

python3 -m unittest discover --start-directory .github/scripts/commit_checks/tests
"""

from __future__ import annotations

import os
import subprocess
import tempfile
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "check_commits.sh"
GITHUB = ("GitHub", "noreply@github.com")
PERSON = ("A Contributor", "contributor@example.com")
# 70 characters: within the limit on its own, over it once a squash merge
# appends " (#24)".
SUBJECT = "docs(site): " + "x" * 58


class CheckCommitsTest(unittest.TestCase):
    def setUp(self) -> None:
        self.tmp = tempfile.TemporaryDirectory()
        self.repo = Path(self.tmp.name)
        self.git("init", "-q")
        self.commit("chore(repo): start the history", PERSON)
        self.base = self.git("rev-parse", "HEAD")

    def tearDown(self) -> None:
        self.tmp.cleanup()

    def git(self, *args: str, env: dict[str, str] | None = None) -> str:
        done = subprocess.run(
            ["git", *args], cwd=self.repo, env=env, check=True, capture_output=True, text=True
        )
        return done.stdout.strip()

    def commit(self, subject: str, committer: tuple[str, str]) -> None:
        env = dict(
            os.environ,
            GIT_AUTHOR_NAME=PERSON[0],
            GIT_AUTHOR_EMAIL=PERSON[1],
            GIT_COMMITTER_NAME=committer[0],
            GIT_COMMITTER_EMAIL=committer[1],
        )
        self.git("commit", "-q", "--allow-empty", "-m", subject, env=env)

    def check(self, *args: str) -> subprocess.CompletedProcess[str]:
        env = {k: v for k, v in os.environ.items() if k != "GITHUB_ACTIONS"}
        return subprocess.run(
            ["sh", str(SCRIPT), *args], cwd=self.repo, env=env, capture_output=True, text=True
        )

    def assert_too_long(self, done: subprocess.CompletedProcess[str]) -> None:
        self.assertEqual(done.returncode, 1, done.stderr)
        self.assertIn("longer than 72 characters", done.stderr)

    def test_a_squash_merge_is_measured_without_its_pull_request_number(self) -> None:
        self.commit(SUBJECT + " (#24)", GITHUB)
        done = self.check(f"{self.base}..HEAD")
        self.assertEqual(done.returncode, 0, done.stderr)

    def test_a_commit_a_person_made_counts_every_character(self) -> None:
        self.commit(SUBJECT + " (#24)", PERSON)
        self.assert_too_long(self.check(f"{self.base}..HEAD"))

    def test_a_squash_subject_still_fits_the_limit_without_its_number(self) -> None:
        self.commit(SUBJECT + "yzw (#24)", GITHUB)
        self.assert_too_long(self.check(f"{self.base}..HEAD"))

    def test_only_a_trailing_number_is_left_out(self) -> None:
        self.commit("docs(site): " + "x" * 55 + " (#24) yz", GITHUB)
        self.assert_too_long(self.check(f"{self.base}..HEAD"))

    def test_the_pull_request_title_counts_every_character(self) -> None:
        self.assert_too_long(self.check("--title", SUBJECT + " (#24)"))


if __name__ == "__main__":
    unittest.main()
