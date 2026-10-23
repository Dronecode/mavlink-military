"""Tests for check_c_library.py, against local git repositories and a
stand-in for the GitHub API. Needs git. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/verify_c_library/tests
"""

from __future__ import annotations

import contextlib
import importlib
import io
import os
import runpy
import subprocess
import sys
import tempfile
import time
import unittest
import urllib.error
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
lib = importlib.import_module("check_c_library")

REPO = "example/dialect"
SERVER = "https://github.example"
API = "https://api.github.example"
WORKFLOW = """name: Generate

on:
  # Publishes on a push that changes an input.
  push:
    branches:
      - main
    paths:
      - "military.xml"
      - ".github/mavlink-pins.env"
      - ".github/scripts/generate_c_lib/**"
  pull_request:
  workflow_dispatch:

jobs: {}
"""
PINS = "# Pins.\nMAVLINK_REF=" + "1" * 40 + "\nPYMAVLINK_REF=" + "2" * 40 + "\n"


def git(directory: Path, *args: str) -> str:
    command = ["git", "-c", "user.name=test", "-c", "user.email=test@example.org"]
    return subprocess.run(
        [*command, "-C", str(directory), *args], capture_output=True, text=True, check=True
    ).stdout.strip()


def record(sha: str, repository: str = REPO, short: str | None = None, pins: str = "") -> str:
    pins = pins or f"mavlink:   {'1' * 40}\npymavlink: {'2' * 40}\n"
    return (
        f"feat(dialect): a change\n\nGenerated from {repository}@{short or sha[:7]}\n"
        f"{SERVER}/{repository}/commit/{sha}\n\n{pins}"
    )


class Api:
    """Deployments and runs, answered from dictionaries, one page each
    unless a test splits them."""

    def __init__(self) -> None:
        self.deployments: list[dict] = []
        self.statuses: dict[int, list[dict]] = {}
        self.runs: dict[str, dict] = {}
        self.pages: dict[str, tuple[object, str | None]] = {}

    def deploy(
        self, sha: str, states: list[str], run: str = "7", created: str = "", **status
    ) -> None:
        number = len(self.deployments) + 1
        created = created or time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
        self.deployments.insert(
            0,
            {
                "id": number,
                "sha": sha,
                "statuses_url": f"{API}/statuses/{number}",
                "created_at": created,
            },
        )
        log_url = f"{SERVER}/{REPO}/actions/runs/{run}/job/1"
        self.statuses[number] = [dict({"state": s, "log_url": log_url}, **status) for s in states]
        self.runs.setdefault(
            run,
            {
                "path": ".github/workflows/generate_c_lib.yml",
                "head_sha": sha,
                "head_branch": "main",
                "event": "push",
                "repository": {"full_name": REPO},
            },
        )

    def __call__(self, url: str):
        if url in self.pages:
            return self.pages[url]
        if url == f"{API}/repos/{REPO}/deployments?environment=c-library&per_page=100":
            return self.deployments, None
        if url.startswith(f"{API}/statuses/"):
            return self.statuses[int(url.split("/")[-1].split("?")[0])], None
        if url.startswith(f"{API}/repos/{REPO}/actions/runs/"):
            return self.runs[url.rsplit("/", 1)[1]], None
        raise AssertionError(url)


class CheckTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)
        self.source = self.tmp / "source"
        self.source.mkdir()
        git(self.source, "init", "-q", "-b", "main")
        self.commit_files(
            {
                ".github/workflows/generate_c_lib.yml": WORKFLOW,
                ".github/mavlink-pins.env": PINS,
                "military.xml": "<mavlink/>\n",
            }
        )
        self.first = git(self.source, "rev-parse", "HEAD")
        self.remote = self.tmp / "library.git"
        git(self.tmp, "init", "-q", "--bare", "-b", "main", str(self.remote))
        self.library = self.tmp / "library"
        git(self.tmp, "clone", "-q", str(self.remote), str(self.library))
        self.publish(record(self.first))
        self.api = Api()
        self.api.deploy(self.first, ["success", "in_progress", "queued"])
        patcher = mock.patch.dict(
            os.environ,
            {"GITHUB_REPOSITORY": REPO, "GITHUB_SERVER_URL": SERVER, "GITHUB_API_URL": API},
        )
        patcher.start()
        self.addCleanup(patcher.stop)
        for name in ("GITHUB_ACTIONS", "GITHUB_OUTPUT"):
            os.environ.pop(name, None)

    def commit_files(self, files: dict[str, str], message: str = "a change") -> str:
        for path, text in files.items():
            file = self.source / path
            file.parent.mkdir(parents=True, exist_ok=True)
            file.write_text(text, encoding="utf-8")
            git(self.source, "add", path)
        git(self.source, "commit", "-q", "-m", message)
        return git(self.source, "rev-parse", "HEAD")

    def publish(self, message: str) -> None:
        (self.library / "military.h").write_text(message, encoding="utf-8")
        git(self.library, "add", "military.h")
        git(self.library, "commit", "-q", "-m", message)
        git(self.library, "push", "-q", "origin", "HEAD:main")

    def run_check(self, *extra: str) -> tuple[int, str, str]:
        argv = ["--library", str(self.library), "--source", str(self.source), *extra]
        out, err = io.StringIO(), io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            code = lib.main(argv, get=self.api)
        return code, out.getvalue(), err.getvalue()

    def assert_fails(self, text: str) -> None:
        code, _, err = self.run_check()
        self.assertEqual(code, 1, err)
        self.assertIn(text, err)


class PassingTest(CheckTest):
    def test_a_published_head_with_its_deployment_passes(self) -> None:
        output = self.tmp / "output"
        os.environ["GITHUB_OUTPUT"] = str(output)
        code, out, err = self.run_check()
        self.assertEqual((code, err), (0, ""))
        self.assertIn(f"regenerate at {self.first}", out)
        self.assertEqual(output.read_text(), f"result=verify\nsource={self.first}\n")

    def test_later_commits_that_leave_the_inputs_alone_pass(self) -> None:
        head = self.commit_files({"README.md": "Docs.\n"})
        later = self.commit_files({"docs/a.md": "More.\n"})
        self.api.deploy(head, ["success"], run="8")
        code, out, _ = self.run_check()
        self.assertEqual(code, 0)
        self.assertIn(f"regenerate at {later}", out)

    def test_a_running_publish_is_left_for_the_next_run(self) -> None:
        output = self.tmp / "output"
        os.environ["GITHUB_OUTPUT"] = str(output)
        os.environ["GITHUB_ACTIONS"] = "true"
        head = self.commit_files({"military.xml": "<mavlink><!-- new --></mavlink>\n"})
        self.api.deploy(head, ["in_progress", "queued"], run="8")
        code, out, _ = self.run_check()
        self.assertEqual(code, 0)
        self.assertIn("::notice title=C library::a c-library deployment is running", out)
        self.assertEqual(output.read_text(), "result=running\n")

    def test_a_deployment_without_a_status_counts_as_running(self) -> None:
        self.api.deploy(self.first, [], run="8")
        code, _, err = self.run_check()
        self.assertEqual(code, 0)
        self.assertIn("is running", err)

    def test_a_deployment_pending_for_less_than_the_limit_counts_as_running(self) -> None:
        recent = time.gmtime(time.time() - lib.RUNNING_LIMIT + 300)
        self.api.deploy(
            self.first, ["waiting"], run="8", created=time.strftime("%Y-%m-%dT%H:%M:%SZ", recent)
        )
        self.assertEqual(self.run_check()[0], 0)

    def test_the_remote_defaults_to_the_clone_origin_and_pages_are_followed(self) -> None:
        url = f"{API}/repos/{REPO}/deployments?environment=c-library&per_page=100"
        self.api.pages[url] = ([], f"{API}/page/2")
        self.api.pages[f"{API}/page/2"] = (self.api.deployments, None)
        code, _, err = self.run_check()
        self.assertEqual((code, err), (0, ""))

    def test_a_status_without_a_log_url_names_its_run_by_target_url(self) -> None:
        status = self.api.statuses[1][0]
        status["target_url"] = status.pop("log_url")
        self.assertEqual(self.run_check()[0], 0)


class FailingTest(CheckTest):
    def test_another_branch_in_the_library_fails(self) -> None:
        git(self.library, "push", "-q", "origin", "HEAD:refs/heads/extra")
        self.assert_fails("the library's branches are ['extra', 'main'], not only main")

    def test_a_tag_in_the_library_fails(self) -> None:
        git(self.library, "tag", "-a", "-m", "a release", "v1.0.0")
        git(self.library, "push", "-q", "origin", "v1.0.0")
        self.assert_fails("the library has tags, which no publish run makes: ['refs/tags/v1.0.0'")

    def test_a_deployment_pending_for_more_than_a_day_fails(self) -> None:
        for states in ([], ["in_progress"], ["waiting", "queued"]):
            with self.subTest(states=states):
                self.api.deploy(self.first, states, run="8", created="2026-01-01T05:17:00Z")
                self.assert_fails("has been pending since 2026-01-01T05:17:00Z")
                self.api.deployments.pop(0)

    def test_a_head_without_a_record_fails(self) -> None:
        self.publish("chore: an edit made by hand")
        self.assert_fails("carries no complete source record")

    def test_a_record_naming_another_repository_fails(self) -> None:
        self.publish(record(self.first, repository="someone/else"))
        self.assert_fails("names someone/else as its source")

    def test_a_short_commit_that_does_not_match_fails(self) -> None:
        self.publish(record(self.first, short="abcdef0"))
        self.assert_fails("short and full source commits differ")

    def test_a_source_commit_off_the_branch_fails(self) -> None:
        git(self.source, "checkout", "-q", "-b", "side")
        side = self.commit_files({"military.xml": "<mavlink><!-- side --></mavlink>\n"})
        git(self.source, "checkout", "-q", "main")
        self.publish(record(side))
        self.assert_fails(f"source commit {side} is not on main")

    def test_a_source_commit_the_repository_lacks_fails(self) -> None:
        self.publish(record("f" * 40))
        self.assert_fails("is not on main")

    def test_pins_other_than_the_source_sets_fail(self) -> None:
        self.publish(record(self.first, pins=f"mavlink:   {'3' * 40}\npymavlink: {'2' * 40}\n"))
        self.assert_fails("records other pins than")

    def test_a_source_commit_without_a_pins_file_fails(self) -> None:
        git(self.source, "rm", "-q", ".github/mavlink-pins.env")
        git(self.source, "commit", "-q", "-m", "no pins")
        bare = git(self.source, "rev-parse", "HEAD")
        self.publish(record(bare))
        self.assert_fails(f"the pins file at {bare} does not set each pin once")

    def test_no_deployment_fails(self) -> None:
        self.api.deployments.clear()
        self.assert_fails("has no c-library deployment")

    def test_no_successful_deployment_fails(self) -> None:
        self.api.statuses[1] = [{"state": "failure", "log_url": ""}]
        self.assert_fails("no c-library deployment of example/dialect succeeded")

    def test_a_deployment_that_links_no_run_fails(self) -> None:
        self.api.statuses[1][0]["log_url"] = "https://elsewhere.example/run/1"
        self.assert_fails(f"the deployment of {self.first} links no run")
        del self.api.statuses[1][0]["log_url"]
        self.assert_fails("links no run")

    def test_a_deployment_from_another_workflow_or_event_fails(self) -> None:
        run = self.api.runs["7"]
        for field, value in (("path", ".github/workflows/other.yml"), ("event", "schedule")):
            with self.subTest(field=field):
                saved = run[field]
                run[field] = value
                self.assert_fails("which is not a push or manual run")
                run[field] = saved

    def test_a_source_commit_never_deployed_fails(self) -> None:
        head = self.commit_files({"military.xml": "<mavlink><!-- 2 --></mavlink>\n"})
        self.publish(record(head))
        self.api.statuses[1] = [{"state": "failure"}]
        self.api.deploy(self.first, ["success"], run="8")
        self.api.runs["8"]["head_sha"] = self.first
        self.assert_fails(f"source commit {head} has no successful c-library deployment")

    def test_a_source_commit_newer_than_the_newest_deployment_fails(self) -> None:
        head = self.commit_files({"military.xml": "<mavlink><!-- 2 --></mavlink>\n"})
        self.publish(record(head))
        self.api.deploy(head, ["success"], run="8")
        self.api.deployments.reverse()
        self.assert_fails(f"is not the newest deployed commit {self.first} or one of its")

    def test_a_deployed_commit_off_the_branch_fails(self) -> None:
        git(self.source, "checkout", "-q", "-b", "side")
        side = self.commit_files({"docs/x.md": "Side.\n"})
        git(self.source, "checkout", "-q", "main")
        self.api.deploy(side, ["success"], run="8")
        self.assert_fails(f"is not the newest deployed commit {side}")

    def test_an_input_changed_after_the_newest_deployment_fails(self) -> None:
        self.commit_files({".github/scripts/generate_c_lib/x.sh": "true\n"})
        self.assert_fails("main changes the generator inputs after")


class SetupTest(CheckTest):
    def test_a_pending_deployment_without_a_readable_date_is_an_error(self) -> None:
        for created in (None, "yesterday"):
            with self.subTest(created=created):
                self.api.deploy(self.first, [], run="8")
                if created is None:
                    del self.api.deployments[0]["created_at"]
                else:
                    self.api.deployments[0]["created_at"] = created
                code, _, err = self.run_check()
                self.assertEqual(code, 2)
                self.assertIn("has no readable created_at", err)
                self.api.deployments.pop(0)

    def test_a_workflow_without_push_paths_is_an_error(self) -> None:
        self.commit_files({".github/workflows/generate_c_lib.yml": "on:\n  push:\n"})
        code, _, err = self.run_check()
        self.assertEqual(code, 2)
        self.assertIn("no paths filter to read", err)

    def test_a_library_that_is_not_a_clone_is_an_error(self) -> None:
        empty = self.tmp / "empty"
        empty.mkdir()
        self.library = empty
        os.environ["GIT_CEILING_DIRECTORIES"] = str(self.tmp)
        code, _, err = self.run_check()
        self.assertEqual(code, 2)
        self.assertIn("git remote get-url origin", err)

    def test_without_github_repository_it_is_an_error(self) -> None:
        del os.environ["GITHUB_REPOSITORY"]
        code, _, err = self.run_check("--remote", str(self.remote))
        self.assertEqual(code, 2)
        self.assertIn("GITHUB_REPOSITORY must name", err)

    def test_usage_errors_and_help(self) -> None:
        with contextlib.redirect_stderr(io.StringIO()), contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(lib.main([]), 2)
            self.assertEqual(lib.main(["--help"]), 0)

    def test_runs_as_a_script(self) -> None:
        with (
            mock.patch.object(sys, "argv", ["check_c_library.py"]),
            contextlib.redirect_stderr(io.StringIO()),
            self.assertRaises(SystemExit) as exit_,
        ):
            runpy.run_path(lib.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


class Response(io.BytesIO):
    def __init__(self, body: bytes, link: str | None = None) -> None:
        super().__init__(body)
        self.headers = {"Link": link} if link else {}


class GetJsonTest(unittest.TestCase):
    def setUp(self) -> None:
        patcher = mock.patch.dict(os.environ)
        patcher.start()
        self.addCleanup(patcher.stop)
        for name in ("GH_TOKEN", "GITHUB_TOKEN"):
            os.environ.pop(name, None)
        self.sleeps: list[float] = []

    def get(self, answers: list[object]):
        self.requests = []

        def opener(request, timeout):
            self.requests.append(request)
            answer = answers.pop(0)
            if isinstance(answer, Exception):
                raise answer
            return answer

        return lib.get_json(f"{API}/x", opener=opener, sleep=self.sleeps.append)

    def test_returns_the_answer_and_the_next_page(self) -> None:
        link = f'<{API}/x?page=2>; rel="next", <{API}/x?page=9>; rel="last"'
        self.assertEqual(self.get([Response(b"[1]", link)]), ([1], f"{API}/x?page=2"))
        self.assertNotIn("Authorization", dict(self.requests[0].header_items()))
        self.assertEqual(self.get([Response(b"[]")]), ([], None))

    def test_sends_a_token_when_one_is_set(self) -> None:
        os.environ["GITHUB_TOKEN"] = "token-b"
        self.get([Response(b"{}")])
        self.assertEqual(self.requests[0].get_header("Authorization"), "Bearer token-b")
        os.environ["GH_TOKEN"] = "token-a"
        self.get([Response(b"{}")])
        self.assertEqual(self.requests[0].get_header("Authorization"), "Bearer token-a")

    def test_retries_server_errors_and_network_failures(self) -> None:
        error = urllib.error.HTTPError(f"{API}/x", 502, "bad gateway", {}, io.BytesIO(b""))
        failure = urllib.error.URLError("unreachable")
        self.assertEqual(self.get([error, failure, Response(b"{}")]), ({}, None))
        self.assertEqual(self.sleeps, [2, 4])

    def test_gives_up_with_a_setup_error(self) -> None:
        not_found = urllib.error.HTTPError(f"{API}/x", 404, "not found", {}, io.BytesIO(b""))
        failure = urllib.error.URLError("unreachable")
        error = urllib.error.HTTPError(f"{API}/x", 503, "unavailable", {}, io.BytesIO(b""))
        for answers, text in (
            ([not_found], "HTTP 404"),
            ([failure] * lib.ATTEMPTS, "unreachable"),
            ([error] * lib.ATTEMPTS, "HTTP 503"),
            ([Response(b"<html>")], "not JSON"),
        ):
            with self.subTest(text=text), self.assertRaisesRegex(lib.SetupError, text):
                self.get(list(answers))

    def test_get_all_stops_after_the_page_limit(self) -> None:
        calls = []

        def endless(url: str):
            calls.append(url)
            return [len(calls)], f"{API}/next"

        self.assertEqual(lib.get_all(f"{API}/first", endless), list(range(1, lib.PAGES + 1)))

    def test_escape(self) -> None:
        self.assertEqual(lib.escape("a%b\r\nc"), "a%25b%0D%0Ac")


if __name__ == "__main__":
    unittest.main()
