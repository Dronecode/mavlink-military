#!/usr/bin/env python3
"""The one way the release scripts talk to GitHub: the gh command line.

Every read and write goes through run() or api(), so the tests replace gh with a
stand-in on GH and inject any failure. A read that fails with a server error or
a rate limit is retried with growing delays. A write is sent once: a server
error does not say the write failed, and sending it again could make a second
release or asset. Any other failure, and a read that still fails after the last
retry, raises GitHubError, so an unknown answer is never taken for a missing
thing. A call is a read when it is a gh api GET or one of READS; anything else
counts as a write. GH names the gh command (default "gh"); GH_RETRIES (default 3)
and GH_RETRY_DELAY in seconds (default 5) set the retries.
"""

from __future__ import annotations

import json
import os
import subprocess
import time

TRANSIENT = ("HTTP 500", "HTTP 502", "HTTP 503", "HTTP 504", "rate limit", "timed out")
READS = {
    ("release", "download"), ("release", "view"), ("release", "verify"), ("release", "verify-asset"),
    ("attestation", "verify"), ("attestation", "trusted-root"),
}  # fmt: skip
# gh api sends a POST when a field or an input is given and no method is.
FIELDS = ("-f", "-F", "--field", "--raw-field", "--input")


class GitHubError(Exception):
    """A gh call that failed for good."""


def is_read(args: tuple[str, ...]) -> bool:
    """Whether a gh call only reads, so that sending it again changes nothing."""
    if args[:1] != ("api",):
        return args[:2] in READS
    fields = any(a in FIELDS or a.startswith(tuple(f"{f}=" for f in FIELDS[2:])) for a in args)
    method = "POST" if fields else "GET"
    for i, arg in enumerate(args):
        if arg in ("-X", "--method"):
            method = args[i + 1] if i + 1 < len(args) else ""
        elif arg.startswith("--method="):
            method = arg.removeprefix("--method=")
    return method.upper() == "GET"


def run(*args: str) -> str:
    """Run gh with the arguments and return its standard output."""
    attempts = int(os.environ.get("GH_RETRIES", "3")) + 1 if is_read(args) else 1
    delay = float(os.environ.get("GH_RETRY_DELAY", "5"))
    for attempt in range(1, attempts + 1):
        result = subprocess.run(
            [os.environ.get("GH", "gh"), *args], capture_output=True, text=True, check=False
        )
        if result.returncode == 0:
            return result.stdout
        error = result.stderr.strip() or f"exit {result.returncode}"
        if attempt == attempts or not any(mark in error for mark in TRANSIENT):
            raise GitHubError(f"gh {' '.join(args)}: {error}")
        time.sleep(delay * attempt)
    raise AssertionError("unreachable")  # pragma: no cover - the loop returns or raises


def api(path: str, *args: str) -> object:
    """A REST call through gh api, its JSON answer decoded."""
    text = run("api", path, *args)
    try:
        return json.loads(text) if text.strip() else None
    except json.JSONDecodeError as error:
        raise GitHubError(f"gh api {path}: not JSON: {error}") from error
