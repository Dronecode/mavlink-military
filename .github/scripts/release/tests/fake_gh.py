#!/usr/bin/env python3
"""A stand-in for the gh command line, for the release scripts' tests.

FakeGh writes a wrapper script that the scripts run through GH. Each call is
answered by the first response whose args equal the call's arguments (or start
with them, for a response marked prefix), holds every string of its contains
somewhere in the call, and is not used up (a response with times answers that
many calls), printing its stdout and stderr,
writing its files into the directory after --dir or into the path after
--output, and exiting with its code. A call with no response fails with exit 1
and "fake gh: no response". Every call is logged, so a test can assert what
was asked and in what order.
"""

from __future__ import annotations

import json
import sys
from pathlib import Path


def answer(config: Path, args: list[str]) -> int:
    setup = json.loads(config.read_text(encoding="utf-8"))
    with open(setup["log"], "a", encoding="utf-8") as log:
        log.write(json.dumps(args) + "\n")
    for index, response in enumerate(setup["responses"]):
        wanted = response["args"]
        joined = " ".join(args)
        if response.get("contains") and not all(part in joined for part in response["contains"]):
            continue
        if args == wanted or (response.get("prefix") and args[: len(wanted)] == wanted):
            if response.get("times") is not None:
                used = config.with_name(f"{config.name}.used-{index}")
                count = int(used.read_text()) if used.exists() else 0
                if count >= response["times"]:
                    continue
                used.write_text(str(count + 1))
            target = None
            if "--dir" in args:
                target = Path(args[args.index("--dir") + 1])
            for name, text in response.get("files", {}).items():
                path = target / name if target else Path(args[args.index("--output") + 1])
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(text.encode("latin-1"))
            sys.stdout.write(response.get("stdout", ""))
            sys.stderr.write(response.get("stderr", ""))
            return response.get("exit", 0)
    sys.stderr.write(f"fake gh: no response for {args}\n")
    return 1


class FakeGh:
    """Responses for one test, and the log of the calls made."""

    def __init__(self, directory: Path) -> None:
        self.directory = directory
        self.config = directory / "fake-gh.json"
        self.log = directory / "fake-gh.log"
        self.responses: list[dict] = []
        self.command = directory / "gh"
        self.command.write_text(
            f'#!/bin/sh\nexec "{sys.executable}" "{Path(__file__).resolve()}" "{self.config}" "$@"\n',
            encoding="utf-8",
        )
        self.command.chmod(0o755)
        self.save()

    def save(self) -> None:
        self.config.write_text(
            json.dumps({"responses": self.responses, "log": str(self.log)}), encoding="utf-8"
        )

    def on(self, *args: str, stdout: object = "", exit: int = 0, stderr: str = "",
           files: dict | None = None, prefix: bool = False, times: int | None = None,
           contains: list[str] | None = None) -> None:  # fmt: skip
        """Answer a call; a stdout that is not a string is sent as JSON."""
        text = stdout if isinstance(stdout, str) else json.dumps(stdout)
        entry = {"args": list(args), "stdout": text, "exit": exit, "stderr": stderr,
                 "prefix": prefix, "times": times, "contains": contains}  # fmt: skip
        if files:
            entry["files"] = {
                k: v.decode("latin-1") if isinstance(v, bytes) else v for k, v in files.items()
            }
        self.responses.append(entry)
        self.save()

    def calls(self) -> list[list[str]]:
        if not self.log.exists():
            return []
        return [json.loads(line) for line in self.log.read_text(encoding="utf-8").splitlines()]

    def env(self) -> dict[str, str]:
        return {"GH": str(self.command), "GH_RETRIES": "1", "GH_RETRY_DELAY": "0"}


if __name__ == "__main__":
    sys.exit(answer(Path(sys.argv[1]), sys.argv[2:]))
