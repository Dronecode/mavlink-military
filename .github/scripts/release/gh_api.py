#!/usr/bin/env python3
"""The one way the release scripts talk to GitHub: the gh command line.

Every read and write goes through run() or api(), so the tests replace gh with a
stand-in on GH and inject any failure. A call that fails with a server error or
a rate limit is retried with growing delays; any other failure, and a call that
still fails after the last retry, raises GitHubError, so an unknown answer is
never taken for a missing thing. GH names the gh command (default "gh");
GH_RETRIES (default 3) and GH_RETRY_DELAY in seconds (default 5) set the retries.
"""

from __future__ import annotations

import json
import os
import subprocess
import time

TRANSIENT = ("HTTP 500", "HTTP 502", "HTTP 503", "HTTP 504", "rate limit", "timed out")


class GitHubError(Exception):
    """A gh call that failed for good."""


def run(*args: str) -> str:
    """Run gh with the arguments and return its standard output."""
    attempts = int(os.environ.get("GH_RETRIES", "3")) + 1
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
