#!/usr/bin/env python3
"""Tests for run_api_break_check.sh, with stand-in checkers that print what
mavlink's check_api_break.py prints. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/validate_dialect/tests
"""

from __future__ import annotations

import os
import subprocess
import tempfile
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "run_api_break_check.sh"
BREAK = (
    "Name removals/changes detected in military.xml:\\n - Changed enum entry X.Y (value: 4 -> 40)"
)


class RunApiBreakCheckTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.dir = Path(tmp.name)

    def checker(self, output: str, status: int) -> str:
        path = self.dir / "check_api_break.py"
        path.write_text(f'import sys\nprint("{output}")\nsys.exit({status})\n', encoding="utf-8")
        return str(path)

    def run_check(
        self,
        checker: str,
        enforce: str = "0",
        actions: bool = True,
        summary: Path | None = None,
        args: list[str] | None = None,
    ):
        env = dict(os.environ)
        for name in ("GITHUB_ACTIONS", "GITHUB_STEP_SUMMARY"):
            env.pop(name, None)
        if actions:
            env["GITHUB_ACTIONS"] = "true"
        if summary is not None:
            env["GITHUB_STEP_SUMMARY"] = str(summary)
        if args is None:
            args = [checker, enforce]
        return subprocess.run(["sh", str(SCRIPT), *args], env=env, capture_output=True, text=True)

    def test_no_break_passes(self) -> None:
        result = self.run_check(self.checker("No XML files changed.", 0))
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout, "No XML files changed.\n")

    def test_a_break_warns_when_not_enforcing(self) -> None:
        result = self.run_check(self.checker(BREAK, 1))
        self.assertEqual(result.returncode, 0)
        self.assertIn(
            "::warning title=API break::check_api_break.py reports breaking changes\n",
            result.stdout,
        )

    def test_a_break_fails_when_enforcing(self) -> None:
        result = self.run_check(self.checker(BREAK, 1), enforce="1")
        self.assertEqual(result.returncode, 1)
        self.assertIn(
            "::error title=API break::check_api_break.py reports breaking changes\n", result.stdout
        )

    def test_a_run_without_a_verdict_fails_either_way(self) -> None:
        for enforce in ("0", "1"):
            result = self.run_check(
                self.checker("Traceback (most recent call last):", 2), enforce=enforce
            )
            self.assertEqual(result.returncode, 2)
            self.assertIn(
                "::error title=API break check::check_api_break.py exited 2 without a verdict",
                result.stdout,
            )

    def test_outside_github_actions_findings_go_to_stderr(self) -> None:
        result = self.run_check(self.checker(BREAK, 1), actions=False)
        self.assertEqual(result.returncode, 0)
        self.assertNotIn("::warning", result.stdout)
        self.assertIn("warning: check_api_break.py reports breaking changes\n", result.stderr)

    def test_the_output_goes_to_the_step_summary(self) -> None:
        summary = self.dir / "summary.md"
        self.run_check(self.checker("No XML files changed.", 0), summary=summary)
        self.assertEqual(
            summary.read_text(encoding="utf-8"),
            "## mavlink API break check\n\n```text\nNo XML files changed.\n```\n",
        )

    def test_a_break_points_at_the_step_summary(self) -> None:
        result = self.run_check(self.checker(BREAK, 1), summary=self.dir / "summary.md")
        self.assertIn(
            "::warning title=API break::check_api_break.py reports breaking changes,"
            " listed in the step summary\n",
            result.stdout,
        )

    def test_usage(self) -> None:
        result = self.run_check("", args=["only-one"])
        self.assertEqual(result.returncode, 1)
        self.assertIn("usage:", result.stderr)


if __name__ == "__main__":
    unittest.main()
