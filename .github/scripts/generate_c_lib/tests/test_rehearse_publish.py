#!/usr/bin/env python3
"""Tests for rehearse_publish.sh, against local git repositories. Needs git
and rsync. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/generate_c_lib/tests
"""

from __future__ import annotations

import os
import subprocess
import tempfile
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "rehearse_publish.sh"
FIRES = "military/mavlink_msg_fires.h"


def git(cwd: Path, *args: str) -> str:
    command = ["git", "-c", "user.name=test", "-c", "user.email=test@example.org", *args]
    return subprocess.run(command, cwd=cwd, check=True, capture_output=True, text=True).stdout


def write(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


class RehearsePublishTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        # The C library the rehearsal reads from and must never change.
        self.library = root / "library.git"
        git(root, "init", "-q", "--bare", "--initial-branch=main", str(self.library))
        seed = root / "seed"
        git(root, "clone", "-q", str(self.library), str(seed))
        write(seed / FIRES, "#define MAVLINK_MSG_ID_FIRES_CRC 16\n")
        git(seed, "add", "--all")
        git(seed, "commit", "-q", "-m", "Add the first headers")
        git(seed, "push", "-q", "origin", "HEAD:main")
        self.published = git(self.library, "rev-parse", "main")
        # This repository, with its generator pins.
        self.source = root / "source"
        git(root, "init", "-q", str(self.source))
        write(
            self.source / ".github/mavlink-pins.env",
            f"MAVLINK_REF={'a' * 40}\nPYMAVLINK_REF={'b' * 40}\n",
        )
        git(self.source, "add", "--all")
        git(self.source, "commit", "-q", "-m", "fix(FIRES): correct the CRC")
        self.out = root / "out"
        write(self.out / FIRES, "#define MAVLINK_MSG_ID_FIRES_CRC 24\n")
        self.work = root / "work"
        self.work.mkdir()

    def rehearse(self, library: str | None = None, args: list[str] | None = None):
        env = dict(
            os.environ,
            GITHUB_EVENT_NAME="pull_request",
            GITHUB_REPOSITORY="Dronecode/mavlink-military",
            GITHUB_SERVER_URL="https://github.com",
        )
        if args is None:
            args = [str(self.source), str(self.out), library or str(self.library), str(self.work)]
        return subprocess.run(["sh", str(SCRIPT), *args], env=env, capture_output=True, text=True)

    def test_a_change_is_summarized_and_the_library_is_untouched(self) -> None:
        result = self.rehearse()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue(
            result.stdout.startswith(
                f"## C library publish rehearsal\n\nPublishing these headers pushes this commit to {self.library}:\n"
            )
        )
        self.assertIn("fix(FIRES): correct the CRC", result.stdout)
        self.assertIn(FIRES, result.stdout)
        self.assertEqual(git(self.library, "rev-parse", "main"), self.published)

    def test_headers_the_library_holds_are_no_change(self) -> None:
        write(self.out / FIRES, "#define MAVLINK_MSG_ID_FIRES_CRC 16\n")
        result = self.rehearse()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(
            result.stdout,
            f"## C library publish rehearsal\n\nNo change: {self.library} already holds these headers.\n",
        )

    def test_an_unreachable_library_fails(self) -> None:
        result = self.rehearse(library=str(self.work / "missing.git"))
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(result.stdout, "")

    def test_usage(self) -> None:
        result = self.rehearse(args=[str(self.source)])
        self.assertEqual(result.returncode, 1)
        self.assertIn("usage:", result.stderr)


if __name__ == "__main__":
    unittest.main()
