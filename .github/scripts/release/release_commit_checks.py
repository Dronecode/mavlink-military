#!/usr/bin/env python3
"""Re-run, for a release, the commit checks this repository runs on pull requests.

Usage: release_commit_checks.py <previous> <record.json>
  previous     the previous release's tag, or none
  record.json  where the record of the checks goes

Runs .github/scripts/commit_checks/check_commits.sh over <previous>..HEAD, and
check_contribution.py over the same range when the commit carries that script,
with its sign-off rule at its default (required). Each check's command, exit
status and output go into the record for the evidence bundle. A failure over a
range since an earlier release fails the job. Before the first release the
range is the whole history, which holds commits from before the convention
existed; there the record is kept and the job does not fail.
"""

from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

CHECKS = Path(".github/scripts/commit_checks")


def run(command: list[str]) -> dict:
    result = subprocess.run(command, capture_output=True, text=True)
    return {
        "command": command,
        "exit": result.returncode,
        "output": (result.stdout + result.stderr)[-20000:],
    }


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        print(__doc__, file=sys.stderr)
        return 2
    previous = argv[1]
    if previous == "none":
        root = subprocess.run(
            ["git", "rev-list", "--max-parents=0", "HEAD"],
            capture_output=True,
            text=True,
            check=True,
        ).stdout.split()[-1]
        span, binding = f"{root}..HEAD", False
    else:
        span, binding = f"{previous}..HEAD", True
    checks = [run(["sh", str(CHECKS / "check_commits.sh"), span])]
    if (CHECKS / "check_contribution.py").is_file():
        checks.append(run([sys.executable, str(CHECKS / "check_contribution.py"), span]))
    failed = [c for c in checks if c["exit"] != 0]
    record = {
        "schema": 1,
        "range": span,
        "binding": binding,
        "checks": checks,
        "passed": not failed,
    }
    Path(argv[2]).write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    for check in failed:
        level = "error" if binding else "notice"
        print(
            f"::{level} title=commit checks::{' '.join(check['command'][1:2])} exited {check['exit']} over {span}"
        )
        print(check["output"])
    if failed and not binding:
        print(
            f"Before the first release, {span} holds history from before the convention; recorded, not enforced."
        )
    return 1 if failed and binding else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
