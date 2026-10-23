#!/usr/bin/env python3
"""Check that the published C library is what this repository's publish
job made from main.

Usage:
  check_c_library.py --library <dir> --source <dir> [--remote <url>]
                     [--branch <name>] [--environment <name>]
                     [--workflow <path>]

  --library      a clone of the C library at the head of --branch
  --source       a checkout of this repository at the head of --branch,
                 with its history
  --remote       the library's URL, for the list of its branches (default:
                 the library clone's origin)
  --branch       the branch the library and this repository publish from
                 (default main)
  --environment  the environment the publish job deploys to (default
                 c-library)
  --workflow     the workflow whose runs publish (default
                 .github/workflows/generate_c_lib.yml)

Checks, in order, and fails on the first that does not hold:
  - the library has one branch, --branch, and no tag;
  - the head commit of the library records its source (the "Generated
    from" line, the commit URL and both generator pins, as
    publish_c_library.sh writes them), and that source is this
    repository;
  - the source commit is on this repository's --branch, and its pins are
    the recorded ones;
  - when the newest deployment of --environment is still running, the
    result is "running" and nothing else is checked: the next run checks.
    A deployment still pending RUNNING_LIMIT after it was created fails
    instead, since a publish run ends well within it;
  - the newest successful deployment was made by a run of --workflow, for
    a push or a manual run on --branch, at that deployment's commit;
  - the source commit has a successful deployment of its own and is that
    newest deployed commit or an ancestor of it, on --branch;
  - no change to the generator inputs (the push paths of --workflow) lands
    on --branch after the newest deployed commit, so a regeneration at the
    head of --branch must give the published headers.

The caller then regenerates the headers at the head of --branch and
compares them with the library. Read-only. Environment: GITHUB_REPOSITORY
(this repository, owner/name), GITHUB_SERVER_URL and GITHUB_API_URL
(github.com by default), GH_TOKEN or GITHUB_TOKEN when set, GITHUB_OUTPUT
for result=verify|running and source=<the head of --branch>.

Exit status: 0 when the checks hold or a publish is running, 1 when one
fails, 2 on a usage, git or API error.
"""

from __future__ import annotations

import argparse
import calendar
import json
import os
import re
import subprocess
import sys
import time
import urllib.error
import urllib.request
from collections.abc import Callable
from typing import Any, NamedTuple

PENDING = {"queued", "pending", "waiting", "in_progress"}
EVENTS = {"push", "workflow_dispatch"}
# Server errors and network failures are retried this many times in all.
ATTEMPTS = 3
# Deployments and statuses are read at most this many pages deep.
PAGES = 10
# The jobs of a publish run time out after 35 minutes in all, so a
# deployment still pending a day after it was created is stuck, or no
# publish run made it, and must not keep deferring the comparison.
RUNNING_LIMIT = 24 * 3600  # seconds
PIN = re.compile(r"^(MAVLINK_REF|PYMAVLINK_REF)=([0-9a-f]{40})$", re.MULTILINE)
LINK_NEXT = re.compile(r'<([^>]+)>;\s*rel="next"')


class CheckError(Exception):
    """A check the library does not pass."""


class SetupError(Exception):
    """A usage, git or API error: the checks could not run."""


class Record(NamedTuple):
    sha: str
    mavlink: str
    pymavlink: str


def escape(value: str) -> str:
    """Escape a message for a GitHub Actions workflow command."""
    return value.replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")


def annotate(level: str, message: str) -> None:
    if os.environ.get("GITHUB_ACTIONS") == "true":
        print(f"::{level} title=C library::{escape(message)}")
    else:
        print(f"{level}: {message}", file=sys.stderr)


def git(directory: str, *args: str) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        ["git", "-C", directory, *args], capture_output=True, text=True, check=False
    )


def git_out(directory: str, *args: str) -> str:
    result = git(directory, *args)
    if result.returncode != 0:
        raise SetupError(f"git {' '.join(args)}: {result.stderr.strip()}")
    return result.stdout


def is_ancestor(directory: str, ancestor: str, descendant: str) -> bool:
    """Whether ancestor is descendant or one of its ancestors; False also
    when the repository does not hold ancestor at all."""
    return git(directory, "merge-base", "--is-ancestor", ancestor, descendant).returncode == 0


def get_json(
    url: str,
    opener: Callable[..., Any] = urllib.request.urlopen,
    sleep: Callable[[float], None] = time.sleep,
) -> tuple[Any, str | None]:
    """GET a GitHub API URL; return its JSON and the next page's URL."""
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
                link = LINK_NEXT.search(response.headers.get("Link") or "")
                return json.load(response), link.group(1) if link else None
        except urllib.error.HTTPError as err:
            if err.code < 500 or attempt >= ATTEMPTS:
                raise SetupError(f"{url}: HTTP {err.code}") from err
        except json.JSONDecodeError as err:
            raise SetupError(f"{url}: the answer is not JSON") from err
        except OSError as err:
            if attempt >= ATTEMPTS:
                raise SetupError(f"{url}: {err}") from err
        sleep(2**attempt)
        attempt += 1


def get_all(url: str, get: Callable[[str], tuple[Any, str | None]]) -> list[Any]:
    """Every item of a paged list, up to PAGES pages."""
    items: list[Any] = []
    next_url: str | None = url
    for _ in range(PAGES):
        page, next_url = get(next_url)
        items += page
        if next_url is None:
            break
    return items


def parse_record(message: str, repository: str, server: str) -> Record:
    generated = re.search(r"^Generated from (\S+)@([0-9a-f]{7,40})$", message, re.MULTILINE)
    url = re.search(rf"^{re.escape(server)}/(\S+)/commit/([0-9a-f]{{40}})$", message, re.MULTILINE)
    pins = dict(re.findall(r"^(mavlink|pymavlink):\s+([0-9a-f]{40})$", message, re.MULTILINE))
    if not generated or not url or len(pins) != 2:
        raise CheckError(
            "the library's head commit carries no complete source record (the Generated from "
            "line, the commit URL and both pins), so no publish run made it"
        )
    if {generated.group(1), url.group(1)} != {repository}:
        raise CheckError(
            f"the library's head commit names {generated.group(1)} as its source, "
            f"not {repository}"
        )
    if not url.group(2).startswith(generated.group(2)):
        raise CheckError("the record's short and full source commits differ")
    return Record(url.group(2), pins["mavlink"], pins["pymavlink"])


def pins_at(source: str, sha: str) -> tuple[str, str]:
    shown = git(source, "show", f"{sha}:.github/mavlink-pins.env")
    found = PIN.findall(shown.stdout) if shown.returncode == 0 else []
    pins = dict(found)
    if len(found) != 2 or len(pins) != 2:
        raise CheckError(f"the pins file at {sha} does not set each pin once")
    return pins["MAVLINK_REF"], pins["PYMAVLINK_REF"]


def push_paths(workflow: str) -> list[str]:
    """The paths filter of the workflow's push trigger, as git pathspecs."""
    paths: list[str] = []
    in_on = in_push = in_paths = False
    for line in workflow.split("\n"):
        stripped = line.strip()
        if not stripped or stripped.startswith("#"):
            continue
        indent = len(line) - len(line.lstrip(" "))
        if indent == 0:
            in_on, in_push, in_paths = stripped == "on:", False, False
        elif in_on and indent == 2:
            in_push, in_paths = stripped == "push:", False
        elif in_push and indent == 4:
            in_paths = stripped == "paths:"
        elif in_paths and stripped.startswith("- "):
            paths.append(":(glob)" + stripped[2:].strip().strip("\"'"))
    if not paths:
        raise SetupError("the publish workflow's push trigger has no paths filter to read")
    return paths


class Deployments:
    """The environment's deployments, newest first, with their statuses
    read when first needed."""

    def __init__(self, api: str, repository: str, environment: str, get) -> None:
        self.get = get
        self.items = get_all(
            f"{api}/repos/{repository}/deployments?environment={environment}&per_page=100", get
        )
        self.cache: dict[int, list[dict[str, Any]]] = {}

    def statuses(self, deployment: dict[str, Any]) -> list[dict[str, Any]]:
        if deployment["id"] not in self.cache:
            self.cache[deployment["id"]] = get_all(
                deployment["statuses_url"] + "?per_page=100", self.get
            )
        return self.cache[deployment["id"]]

    def running(self) -> bool:
        statuses = self.statuses(self.items[0])
        return not statuses or statuses[0]["state"] in PENDING

    def success(self, deployment: dict[str, Any]) -> dict[str, Any] | None:
        return next((s for s in self.statuses(deployment) if s["state"] == "success"), None)

    def newest_success(self) -> tuple[dict[str, Any], dict[str, Any]] | None:
        for deployment in self.items:
            status = self.success(deployment)
            if status is not None:
                return deployment, status
        return None

    def succeeded(self, sha: str) -> bool:
        return any(d["sha"] == sha and self.success(d) for d in self.items)


def created(deployment: dict[str, Any]) -> float:
    """When a deployment was created, in seconds since the epoch."""
    try:
        return calendar.timegm(time.strptime(deployment["created_at"], "%Y-%m-%dT%H:%M:%SZ"))
    except (KeyError, TypeError, ValueError) as err:
        raise SetupError(f"deployment {deployment.get('id')} has no readable created_at") from err


def check_run(
    status: dict[str, Any], sha: str, args: argparse.Namespace, env: dict[str, str], get
) -> None:
    """The deployment's run is the publish workflow's, on the branch, at sha."""
    base = f"{env['server']}/{env['repository']}/actions/runs/"
    url = status.get("log_url") or status.get("target_url") or ""
    match = re.match(rf"^{re.escape(base)}(\d+)(?:/|$)", url)
    if not match:
        raise CheckError(f"the deployment of {sha} links no run of {env['repository']}")
    run, _ = get(f"{env['api']}/repos/{env['repository']}/actions/runs/{match.group(1)}")
    expected = (args.workflow, sha, args.branch, env["repository"])
    actual = (run["path"], run["head_sha"], run["head_branch"], run["repository"]["full_name"])
    if actual != expected or run["event"] not in EVENTS:
        raise CheckError(
            f"the deployment of {sha} comes from run {match.group(1)}, which is not a push or "
            f"manual run of {args.workflow} on {args.branch} at that commit"
        )


def check(args: argparse.Namespace, env: dict[str, str], get) -> tuple[str, str]:
    """Run the checks; return the result and a line describing it."""
    listed = git_out(args.source, "ls-remote", "--heads", "--tags", args.remote).split("\n")
    refs = [line.split("\t", 1)[1] for line in listed if line]
    branches = sorted(ref[len("refs/heads/") :] for ref in refs if ref.startswith("refs/heads/"))
    if branches != [args.branch]:
        raise CheckError(f"the library's branches are {branches}, not only {args.branch}")
    tags = sorted(ref for ref in refs if not ref.startswith("refs/heads/"))
    if tags:
        raise CheckError(f"the library has tags, which no publish run makes: {tags}")
    record = parse_record(
        git_out(args.library, "log", "-1", "--format=%B"), env["repository"], env["server"]
    )
    head = git_out(args.source, "rev-parse", "HEAD").strip()
    if not is_ancestor(args.source, record.sha, head):
        raise CheckError(f"the library's source commit {record.sha} is not on {args.branch}")
    if pins_at(args.source, record.sha) != (record.mavlink, record.pymavlink):
        raise CheckError(f"the library records other pins than {record.sha} sets")
    deployments = Deployments(env["api"], env["repository"], args.environment, get)
    if not deployments.items:
        raise CheckError(f"{env['repository']} has no {args.environment} deployment")
    if deployments.running():
        newest = deployments.items[0]
        if time.time() - created(newest) > RUNNING_LIMIT:
            raise CheckError(
                f"the newest {args.environment} deployment, of {newest['sha']}, has been "
                f"pending since {newest['created_at']}, longer than a publish run takes"
            )
        return "running", f"a {args.environment} deployment is running; the next run checks"
    newest = deployments.newest_success()
    if newest is None:
        raise CheckError(f"no {args.environment} deployment of {env['repository']} succeeded")
    deployment, status = newest
    deployed = deployment["sha"]
    check_run(status, deployed, args, env, get)
    if not deployments.succeeded(record.sha):
        raise CheckError(
            f"the library's source commit {record.sha} has no successful {args.environment} "
            "deployment, so no publish run made the library's head"
        )
    if not is_ancestor(args.source, record.sha, deployed) or not is_ancestor(
        args.source, deployed, head
    ):
        raise CheckError(
            f"the library's source commit {record.sha} is not the newest deployed commit "
            f"{deployed} or one of its ancestors on {args.branch}"
        )
    workflow = git_out(args.source, "show", f"{head}:{args.workflow}")
    changed = git(args.source, "diff", "--quiet", deployed, head, "--", *push_paths(workflow))
    if changed.returncode != 0:
        raise CheckError(
            f"{args.branch} changes the generator inputs after {deployed}, the newest "
            f"successful {args.environment} deployment, so the publish of a later commit is "
            "missing or failed"
        )
    return "verify", head


def parse_args(argv: list[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--library", required=True)
    parser.add_argument("--source", required=True)
    parser.add_argument("--remote")
    parser.add_argument("--branch", default="main")
    parser.add_argument("--environment", default="c-library")
    parser.add_argument("--workflow", default=".github/workflows/generate_c_lib.yml")
    args = parser.parse_args(argv)
    if args.remote is None:
        args.remote = git_out(args.library, "remote", "get-url", "origin").strip()
    return args


def main(argv: list[str], get=get_json) -> int:
    try:
        args = parse_args(argv)
        repository = os.environ.get("GITHUB_REPOSITORY", "")
        if not re.fullmatch(r"[\w.-]+/[\w.-]+", repository):
            raise SetupError("GITHUB_REPOSITORY must name this repository as owner/name")
        env = {
            "repository": repository,
            "server": os.environ.get("GITHUB_SERVER_URL", "https://github.com").rstrip("/"),
            "api": os.environ.get("GITHUB_API_URL", "https://api.github.com").rstrip("/"),
        }
        result, detail = check(args, env, get)
    except SystemExit as exit_:
        return 0 if exit_.code == 0 else 2
    except SetupError as err:
        annotate("error", str(err))
        return 2
    except CheckError as err:
        annotate("error", str(err))
        return 1
    output = os.environ.get("GITHUB_OUTPUT")
    if output:
        with open(output, "a", encoding="utf-8") as file:
            file.write(f"result={result}\n")
            if result == "verify":
                file.write(f"source={detail}\n")
    if result == "running":
        annotate("notice", detail)
    else:
        print(f"The library's head checks out; regenerate at {detail} and compare.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
