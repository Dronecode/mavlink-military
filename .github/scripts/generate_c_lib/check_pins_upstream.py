#!/usr/bin/env python3
"""Check that each generator pin names a commit on its upstream default
branch.

Usage: check_pins_upstream.py <pins>
  pins  the pins file, .github/mavlink-pins.env, read with read_pins.sh

A commit SHA can be checked out through a repository even when the commit
exists only in a fork of it, so a pin is checked by its ancestry: GitHub's
compare API must find the pinned commit behind, or identical to, the head
of the repository's default branch. The calls only read public data. When
GH_TOKEN or GITHUB_TOKEN is set it authenticates them (the job token is
enough), and GITHUB_API_URL names the API (https://api.github.com by
default).

Each pin's repository is the one the setup-mavlink-tooling action checks
out at it: the repository: of the action's actions/checkout step whose
path: is the key read_pins.sh prints for the pin. The action stays the one
place that names the repositories.

Exit status: 0 when every pin is on its default branch, 1 when one is not,
2 on a usage error, a pins file read_pins.sh rejects, an action file that
is missing or unreadable or whose checkout steps do not name each pin's
repository once as owner/name, or an API error.
"""

from __future__ import annotations

import json
import os
import re
import subprocess
import sys
import time
import urllib.error
import urllib.request
from collections.abc import Callable, Iterable
from pathlib import Path
from typing import Any

READ_PINS = Path(__file__).resolve().with_name("read_pins.sh")
ACTION = Path(__file__).resolve().parents[2] / "actions" / "setup-mavlink-tooling" / "action.yml"
CHECKOUT = "actions/checkout@"
# A repository as owner/name, with nothing around it.
REPOSITORY = re.compile(r"[A-Za-z0-9][A-Za-z0-9-]*/(?!\.\.?$)[A-Za-z0-9._-]+")
# The block-style YAML lines the action reader needs: a list item, and a
# key with an optional value.
ITEM = re.compile(r"(?P<indent> *)- (?P<rest>.*)")
PAIR = re.compile(r"(?P<key>[A-Za-z0-9_-]+):(?:[ \t]+(?P<value>.*))?")
# Server errors and network failures are retried this many times in all.
ATTEMPTS = 3
ON_BRANCH = ("behind", "identical")


class ApiError(Exception):
    """A request failed, or answered with something other than JSON."""


def escape(value: str) -> str:
    """Escape a message for a GitHub Actions workflow command."""
    return value.replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")


def report_error(message: str) -> None:
    if os.environ.get("GITHUB_ACTIONS") == "true":
        print(f"::error title=generator pins::{escape(message)}")
    else:
        print(f"error: {message}", file=sys.stderr)


def read_pins(path: str) -> dict[str, str]:
    """Return the pins as read_pins.sh prints them, by key."""
    result = subprocess.run(
        ["sh", str(READ_PINS), path], capture_output=True, text=True, check=False
    )
    if result.returncode != 0:
        raise ValueError(result.stderr.strip())
    return dict(line.split("=", 1) for line in result.stdout.splitlines())


def list_items(text: str) -> list[dict[str, list[str]]]:
    """Return the uses:, path: and repository: values of each list item of
    block-style YAML, read line by line: uses: from the item itself, path:
    and repository: from its with: mapping. Block scalars are skipped."""
    items: list[dict[str, list[str]]] = []
    item: dict[str, list[str]] | None = None
    body = with_at = scalar = -1
    for line in text.splitlines():
        content = line.strip()
        indent = len(line) - len(line.lstrip(" "))
        if not content or 0 <= scalar < indent:
            continue
        scalar = -1
        start = ITEM.fullmatch(line)
        if start:
            item = {}
            items.append(item)
            body, with_at = len(start["indent"]) + 2, -1
            indent, content = body, start["rest"].strip()
        elif item is not None and indent < body:
            item = None
        pair = PAIR.fullmatch(content)
        if pair is None:
            continue
        key, value = pair["key"], (pair["value"] or "").strip()
        if value[:1] in ("|", ">"):
            scalar = indent
        if item is None:
            continue
        if indent == body:
            with_at = indent if key == "with" and not value else -1
            if key == "uses":
                item.setdefault(key, []).append(value)
        elif with_at >= 0 and key in ("path", "repository"):
            item.setdefault(key, []).append(value)
    return items


def read_repositories(action: Path, keys: Iterable[str]) -> dict[str, str]:
    """Return, by pin key, the repository the action checks out at that pin:
    the repository: of its one actions/checkout step whose path: is the key."""
    try:
        text = action.read_text(encoding="utf-8")
    except OSError as err:
        reason = err.strerror or type(err).__name__
        raise ValueError(f"{action}: cannot read the action file: {reason}") from err
    except UnicodeDecodeError as err:
        raise ValueError(f"{action}: the action file is not UTF-8 text") from err
    checkouts = [
        item for item in list_items(text) if item.get("uses", [""])[0].startswith(CHECKOUT)
    ]
    repositories = {}
    for key in keys:
        steps = [item for item in checkouts if item.get("path") == [key]]
        if len(steps) != 1:
            raise ValueError(
                f"{action}: {len(steps)} actions/checkout steps have path: {key}, not one"
            )
        found = steps[0].get("repository", [])
        if len(found) != 1 or not REPOSITORY.fullmatch(found[0]):
            raise ValueError(
                f"{action}: the actions/checkout step with path: {key} must name its "
                "repository: once, as owner/name"
            )
        repositories[key] = found[0]
    return repositories


def get_json(
    url: str,
    opener: Callable[..., Any] = urllib.request.urlopen,
    sleep: Callable[[float], None] = time.sleep,
) -> Any:
    """GET a GitHub API URL and decode its JSON, retrying server errors and
    network failures."""
    headers = {
        "Accept": "application/vnd.github+json",
        "X-GitHub-Api-Version": "2022-11-28",
        "User-Agent": "mavlink-military-ci",
    }
    token = os.environ.get("GH_TOKEN") or os.environ.get("GITHUB_TOKEN")
    if token:
        headers["Authorization"] = f"Bearer {token}"
    attempt = 1
    while True:
        try:
            with opener(urllib.request.Request(url, headers=headers), timeout=30) as response:
                return json.load(response)
        except urllib.error.HTTPError as err:
            if err.code < 500 or attempt >= ATTEMPTS:
                raise ApiError(f"{url}: HTTP {err.code}") from err
        except json.JSONDecodeError as err:
            raise ApiError(f"{url}: the answer is not JSON") from err
        except OSError as err:
            if attempt >= ATTEMPTS:
                raise ApiError(f"{url}: {err}") from err
        sleep(2**attempt)
        attempt += 1


def check_pin(
    key: str, sha: str, repository: str, api: str, get: Callable[[str], Any] = get_json
) -> tuple[bool, str]:
    """Return whether the pin is on its repository's default branch, and a
    line saying so."""
    branch = get(f"{api}/repos/{repository}")["default_branch"]
    comparison = get(f"{api}/repos/{repository}/compare/{branch}...{sha}")
    status = comparison["status"]
    if status in ON_BRANCH:
        return True, (
            f"{key} pin {sha} is on {repository} {branch}, "
            f"{comparison['behind_by']} commit(s) behind its head"
        )
    return False, (
        f"{key} pin {sha} is not on {repository} {branch}: the comparison is "
        f"'{status}', so the commit is missing from that branch's history"
    )


def main(argv: list[str], get: Callable[[str], Any] = get_json, action: Path = ACTION) -> int:
    if len(argv) != 1:
        print("usage: check_pins_upstream.py <pins>", file=sys.stderr)
        return 2
    api = os.environ.get("GITHUB_API_URL", "https://api.github.com").rstrip("/")
    try:
        pins = read_pins(argv[0])
        repositories = read_repositories(action, pins)
        results = [check_pin(key, pins[key], repositories[key], api, get) for key in pins]
    except (ValueError, ApiError) as err:
        report_error(str(err))
        return 2
    failed = False
    for ok, message in results:
        if ok:
            print(message)
        else:
            report_error(message)
            failed = True
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
