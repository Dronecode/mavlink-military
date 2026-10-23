#!/usr/bin/env python3
"""Contract test of docs_deploy.yml's job graph, read as text, since this workflow's tests use
the standard library only. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/docs_deploy/tests --pattern 'test_workflow.py'
"""

from __future__ import annotations

import re
import unittest
from pathlib import Path

WORKFLOW = Path(__file__).resolve().parents[3] / "workflows" / "docs_deploy.yml"


def jobs(text: str) -> dict[str, list[str]]:
    """Each job's lines, by its name, from the block-style jobs: mapping."""
    lines = text.split("\n")
    found: dict[str, list[str]] = {}
    name = None
    for line in lines[lines.index("jobs:") + 1 :]:
        match = re.match(r"^  ([A-Za-z0-9_-]+):$", line)
        if match:
            name = match.group(1)
            found[name] = []
        elif name:
            found[name].append(line)
    return found


class GraphTest(unittest.TestCase):
    def test_the_pins_are_checked_before_any_mavlink_code_runs(self) -> None:
        graph = jobs(WORKFLOW.read_text(encoding="utf-8"))
        self.assertEqual(list(graph), ["pins", "build", "assemble", "deploy"])
        self.assertIn(
            "        run: python3 .github/scripts/generate_c_lib/check_pins_upstream.py .github/mavlink-pins.env",
            graph["pins"],
        )
        for job, needed in (("build", "pins"), ("assemble", "build"), ("deploy", "assemble")):
            with self.subTest(job=job):
                self.assertIn(f"    needs: {needed}", graph[job])


if __name__ == "__main__":
    unittest.main()
