#!/usr/bin/env python3
"""Tests for publish_c_library.sh, run against local git repositories.

Needs git and rsync. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/generate_c_lib/tests
"""

from __future__ import annotations

import os
import subprocess
import tempfile
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "publish_c_library.sh"
OLD_DATE = '#define MAVLINK_BUILD_DATE "Tue Sep 29 2026"\n'
NEW_DATE = '#define MAVLINK_BUILD_DATE "Fri Oct 02 2026"\n'  # same length as OLD_DATE
OLD_CRC = "#define MAVLINK_MSG_ID_FIRES_CRC 16\n"
NEW_CRC = "#define MAVLINK_MSG_ID_FIRES_CRC 24\n"  # same length as OLD_CRC
FIRES = "military/mavlink_msg_fires.h"


def git(cwd: Path, *args: str) -> str:
    """Run git with a fixed identity, for setting up the test repositories."""
    command = ["git", "-c", "user.name=test", "-c", "user.email=test@example.org", *args]
    return subprocess.run(command, cwd=cwd, check=True, capture_output=True, text=True).stdout


def write(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


class PublishCLibraryTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)

        # The C library, as a bare repository with one published commit.
        self.bare = root / "c_library.git"
        git(root, "init", "-q", "--bare", "--initial-branch=main", str(self.bare))
        seed = root / "seed"
        git(root, "clone", "-q", str(self.bare), str(seed))
        write(seed / "military/version.h", OLD_DATE)
        write(seed / FIRES, OLD_CRC)
        write(seed / "military/old.h", "/* a header the generator no longer writes */\n")
        write(seed / "README.md", "C library\n")
        write(seed / "LICENSE", "MIT\n")
        git(seed, "add", "--all")
        git(seed, "commit", "-q", "-m", "Add the first headers")
        git(seed, "push", "-q", "origin", "HEAD:main")

        # The checkout publish_c_library.sh pushes through.
        self.library = root / "c_library"
        git(root, "clone", "-q", str(self.bare), str(self.library))

        # This repository: its HEAD commit names the published commit.
        self.source = root / "source"
        git(root, "init", "-q", str(self.source))
        write(
            self.source / ".github/mavlink-pins.env",
            f"MAVLINK_REF={'a' * 40}\nPYMAVLINK_REF={'b' * 40}\n",
        )
        self.commit_source("fix(dialect): correct FIRES")

        # The generated headers.
        self.out = root / "out"
        write(self.out / "military/version.h", NEW_DATE)
        write(self.out / FIRES, NEW_CRC)

    def commit_source(self, message: str) -> None:
        git(self.source, "commit", "-q", "--allow-empty", "-m", message)

    def publish(self, event: str = "push", args: list[str] | None = None):
        env = dict(os.environ)
        for name in (
            "GIT_AUTHOR_NAME",
            "GIT_AUTHOR_EMAIL",
            "GIT_COMMITTER_NAME",
            "GIT_COMMITTER_EMAIL",
        ):
            env.pop(name, None)
        env.update(
            GITHUB_EVENT_NAME=event,
            GITHUB_REPOSITORY="Dronecode/mavlink-military",
            GITHUB_SERVER_URL="https://github.com",
        )
        if args is None:
            args = [str(self.source), str(self.out), str(self.library)]
        return subprocess.run(["sh", str(SCRIPT), *args], env=env, capture_output=True, text=True)

    def published(self, path: str) -> str:
        return git(self.bare, "show", f"main:{path}")

    def published_message(self) -> str:
        # %B ends with the message's newline, and git log adds one more.
        return git(self.bare, "log", "-1", "--format=%B", "main").removesuffix("\n")

    def test_headers_the_library_holds_publish_nothing(self) -> None:
        write(self.out / "military/version.h", OLD_DATE)
        write(self.out / FIRES, OLD_CRC)
        write(self.out / "military/old.h", "/* a header the generator no longer writes */\n")
        before = git(self.bare, "rev-parse", "main")
        result = self.publish()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("No changes to commit.", result.stdout)
        self.assertEqual(git(self.bare, "rev-parse", "main"), before)

    def test_removed_headers_go_and_readme_and_license_stay(self) -> None:
        self.assertEqual(self.publish().returncode, 0)
        files = git(self.bare, "ls-tree", "-r", "--name-only", "main").split()
        self.assertEqual(files, ["LICENSE", "README.md", FIRES, "military/version.h"])

    def test_commit_names_its_source(self) -> None:
        self.assertEqual(self.publish().returncode, 0)
        sha = git(self.source, "rev-parse", "HEAD").strip()
        short = git(self.source, "rev-parse", "--short", "HEAD").strip()
        self.assertEqual(
            self.published_message(),
            "fix(dialect): correct FIRES\n\n"
            f"Generated from Dronecode/mavlink-military@{short}\n"
            f"https://github.com/Dronecode/mavlink-military/commit/{sha}\n\n"
            f"mavlink:   {'a' * 40}\n"
            f"pymavlink: {'b' * 40}\n",
        )
        self.assertEqual(
            git(self.bare, "log", "-1", "--format=%an <%ae>", "main").strip(),
            "github-actions[bot] <41898282+github-actions[bot]@users.noreply.github.com>",
        )

    def test_a_merge_commit_takes_the_pull_request_title(self) -> None:
        self.commit_source("Merge pull request #12 from Dronecode/split\n\nci: publish C headers")
        self.assertEqual(self.publish().returncode, 0)
        self.assertTrue(self.published_message().startswith("ci: publish C headers (#12)\n"))

    def test_a_merge_commit_without_a_title_keeps_its_subject(self) -> None:
        self.commit_source("Merge pull request #12 from Dronecode/split")
        self.assertEqual(self.publish().returncode, 0)
        self.assertTrue(
            self.published_message().startswith("Merge pull request #12 from Dronecode/split\n")
        )

    def test_a_manual_run_is_marked(self) -> None:
        self.assertEqual(self.publish(event="workflow_dispatch").returncode, 0)
        self.assertTrue(
            self.published_message().startswith("Regenerate: fix(dialect): correct FIRES\n")
        )

    def test_usage(self) -> None:
        result = self.publish(args=[str(self.source), str(self.out)])
        self.assertEqual(result.returncode, 1)
        self.assertIn("usage:", result.stderr)


if __name__ == "__main__":
    unittest.main()
