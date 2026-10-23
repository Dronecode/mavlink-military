"""Tests for check_pins_upstream.py, with a stand-in for the GitHub API.
From the repository root:

python3 -m unittest discover --start-directory .github/scripts/generate_c_lib/tests
"""

from __future__ import annotations

import contextlib
import importlib
import io
import os
import re
import runpy
import subprocess
import sys
import tempfile
import unittest
import urllib.error
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
check = importlib.import_module("check_pins_upstream")

ACTION = Path(__file__).resolve().parents[3] / "actions" / "setup-mavlink-tooling" / "action.yml"
PINS = Path(__file__).resolve().parents[3] / "mavlink-pins.env"
API = "https://api.example.test"
MAVLINK = "1" * 40
PYMAVLINK = "2" * 40
REPOSITORIES = {"mavlink": "example/one", "pymavlink": "example/two"}
SHA = "0" * 40
# An action in the shape of setup-mavlink-tooling, with what the reader
# must pass over: block scalars that look like steps or settings, a step
# that is not a checkout, a comment, an env: mapping and a key after the
# steps.
FIXTURE = f"""\
name: Set up the tooling
description: >-
  - path: mavlink
runs:
  using: composite
  steps:
    - name: Read the pins
      id: pins
      run: |
        - path: mavlink
          repository: inside/a-scalar
    - name: Cache
      uses: actions/cache@{SHA}
      with:
        path: mavlink
    - uses: actions/checkout@{SHA} # v0
      with:
        repository: example/one
        ref: ${{{{ steps.pins.outputs.mavlink }}}}
        path: mavlink
        # a comment inside the mapping
        sparse-checkout: |
          repository: not/this-one

    - name: Check out the second
      uses: actions/checkout@{SHA}
      env:
        path: pymavlink
      with:
        repository: example/two
        ref: ${{{{ steps.pins.outputs.pymavlink }}}}
        path: pymavlink
outputs:
  path: pymavlink
"""
SECOND = FIXTURE[FIXTURE.index("    - name: Check out the second") : FIXTURE.index("outputs:")]


class Response(io.BytesIO):
    """A stand-in for the object urlopen returns, usable with "with"."""


def opener_from(answers: list[object]):
    """An opener that returns or raises each answer in turn, recording each
    request it receives."""
    requests = []

    def opener(request, timeout):
        requests.append(request)
        answer = answers.pop(0)
        if isinstance(answer, Exception):
            raise answer
        return Response(answer)

    return opener, requests


def http_error(code: int) -> urllib.error.HTTPError:
    return urllib.error.HTTPError(f"{API}/x", code, "error", {}, io.BytesIO(b""))


def fake_api(statuses: dict[str, str], repositories: dict[str, str] = REPOSITORIES):
    """A get() that answers for the given repositories, comparing each pin
    with the given status."""

    def get(url: str):
        for key, repository in repositories.items():
            if url == f"{API}/repos/{repository}":
                return {"default_branch": "master"}
            if url.startswith(f"{API}/repos/{repository}/compare/master..."):
                return {"status": statuses[key], "behind_by": 13, "ahead_by": 0}
        raise AssertionError(url)

    return get


class ReadPinsTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.pins = Path(tmp.name) / "mavlink-pins.env"

    def test_reads_both_pins_through_read_pins_sh(self) -> None:
        self.pins.write_text(f"MAVLINK_REF={MAVLINK}\nPYMAVLINK_REF={PYMAVLINK}\n", "utf-8")
        self.assertEqual(
            check.read_pins(str(self.pins)), {"mavlink": MAVLINK, "pymavlink": PYMAVLINK}
        )

    def test_a_pins_file_read_pins_sh_rejects_is_an_error(self) -> None:
        self.pins.write_text(f"MAVLINK_REF=87da370\nPYMAVLINK_REF={PYMAVLINK}\n", "utf-8")
        with self.assertRaisesRegex(ValueError, "MAVLINK_REF must be set once"):
            check.read_pins(str(self.pins))


class RepositoriesTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.action = Path(tmp.name) / "action.yml"

    def read(self, text: str) -> dict[str, str]:
        self.action.write_text(text, "utf-8")
        return check.read_repositories(self.action, ["mavlink", "pymavlink"])

    def test_reads_each_pin_s_repository_from_the_setup_action(self) -> None:
        self.assertEqual(check.ACTION, ACTION)
        keys = list(check.read_pins(str(PINS)))
        repositories = check.read_repositories(check.ACTION, keys)
        self.assertEqual(list(repositories), keys)
        # Read another way: each repository: line and the pin its ref: names.
        found = {
            key: repository
            for repository, key in re.findall(
                r"repository: (\S+)\n\s+ref: \$\{\{ steps\.pins\.outputs\.(\w+) \}\}",
                ACTION.read_text(encoding="utf-8"),
            )
        }
        self.assertEqual(repositories, found)

    def test_reads_only_the_checkout_steps_settings(self) -> None:
        self.assertEqual(self.read(FIXTURE), REPOSITORIES)

    def test_a_missing_checkout_step_fails(self) -> None:
        with self.assertRaisesRegex(ValueError, "0 actions/checkout steps have path: pymavlink"):
            self.read(FIXTURE.replace(SECOND, ""))

    def test_a_duplicate_checkout_step_fails(self) -> None:
        duplicate = SECOND.replace("pymavlink", "mavlink").replace("example/two", "example/one")
        with self.assertRaisesRegex(ValueError, "2 actions/checkout steps have path: mavlink"):
            self.read(FIXTURE.replace(SECOND, SECOND + duplicate))

    def test_a_repository_not_exactly_owner_and_name_fails(self) -> None:
        for line in (
            "repository: example",
            "repository: example/two/three",
            "repository: 'example/two'",
            "repository: ${{ inputs.repository }}",
            "repository: example/..",
            "repository: -example/two",
            "repository: example/two # a comment",
            "repository:",
            "repository: example/two\n        repository: example/two",
            "",
        ):
            with self.subTest(line=line), self.assertRaisesRegex(ValueError, "once, as owner/name"):
                self.read(FIXTURE.replace("repository: example/two", line))

    def test_a_missing_action_file_fails(self) -> None:
        absent = self.action.with_name("absent.yml")
        with self.assertRaisesRegex(ValueError, "absent.yml: cannot read the action file: "):
            check.read_repositories(absent, ["mavlink"])

    def test_an_unreadable_action_file_fails(self) -> None:
        # A directory in the file's place cannot be read on any platform.
        self.action.mkdir()
        with self.assertRaisesRegex(ValueError, "action.yml: cannot read the action file: "):
            check.read_repositories(self.action, ["mavlink"])

    def test_an_action_file_that_is_not_utf8_fails_without_quoting_it(self) -> None:
        self.action.write_bytes(b"runs:\n  steps:\n    - uses: \xff\n")
        with self.assertRaises(ValueError) as caught:
            check.read_repositories(self.action, ["mavlink"])
        self.assertEqual(str(caught.exception), f"{self.action}: the action file is not UTF-8 text")


class GetJsonTest(unittest.TestCase):
    def setUp(self) -> None:
        patcher = mock.patch.dict(os.environ)
        patcher.start()
        self.addCleanup(patcher.stop)
        for name in ("GH_TOKEN", "GITHUB_TOKEN"):
            os.environ.pop(name, None)
        self.sleeps: list[float] = []

    def get(self, answers: list[object]):
        opener, self.requests = opener_from(answers)
        return check.get_json(f"{API}/x", opener=opener, sleep=self.sleeps.append)

    def test_decodes_the_answer_and_sends_no_token_without_one(self) -> None:
        self.assertEqual(self.get([b'{"a": 1}']), {"a": 1})
        headers = dict(self.requests[0].header_items())
        self.assertNotIn("Authorization", headers)
        self.assertEqual(headers["Accept"], "application/vnd.github+json")

    def test_sends_gh_token_as_a_bearer_token(self) -> None:
        os.environ["GH_TOKEN"] = "token-a"
        os.environ["GITHUB_TOKEN"] = "token-b"
        self.get([b"{}"])
        self.assertEqual(self.requests[0].get_header("Authorization"), "Bearer token-a")

    def test_falls_back_to_github_token(self) -> None:
        os.environ["GITHUB_TOKEN"] = "token-b"
        self.get([b"{}"])
        self.assertEqual(self.requests[0].get_header("Authorization"), "Bearer token-b")

    def test_a_client_error_fails_at_once(self) -> None:
        with self.assertRaisesRegex(check.ApiError, "HTTP 404"):
            self.get([http_error(404)])
        self.assertEqual(self.sleeps, [])

    def test_a_server_error_is_retried(self) -> None:
        self.assertEqual(self.get([http_error(502), b"[]"]), [])
        self.assertEqual(self.sleeps, [2])

    def test_server_errors_on_every_attempt_fail(self) -> None:
        with self.assertRaisesRegex(check.ApiError, "HTTP 503"):
            self.get([http_error(503)] * check.ATTEMPTS)
        self.assertEqual(self.sleeps, [2, 4])

    def test_a_network_failure_is_retried_then_fails(self) -> None:
        failure = urllib.error.URLError("unreachable")
        self.assertEqual(self.get([failure, b"{}"]), {})
        with self.assertRaisesRegex(check.ApiError, "unreachable"):
            self.get([failure] * check.ATTEMPTS)

    def test_an_answer_that_is_not_json_fails(self) -> None:
        with self.assertRaisesRegex(check.ApiError, "not JSON"):
            self.get([b"<html>"])


class CheckPinTest(unittest.TestCase):
    def test_a_pin_behind_or_at_the_head_is_on_the_branch(self) -> None:
        for status in ("behind", "identical"):
            ok, message = check.check_pin(
                "mavlink", MAVLINK, "example/one", API, fake_api({"mavlink": status})
            )
            self.assertTrue(ok)
            self.assertEqual(
                message,
                f"mavlink pin {MAVLINK} is on example/one master, 13 commit(s) behind its head",
            )

    def test_a_pin_ahead_of_or_beside_the_branch_is_not_on_it(self) -> None:
        for status in ("ahead", "diverged"):
            ok, message = check.check_pin(
                "pymavlink", PYMAVLINK, "example/two", API, fake_api({"pymavlink": status})
            )
            self.assertFalse(ok)
            self.assertIn(f"pymavlink pin {PYMAVLINK} is not on example/two", message)
            self.assertIn(f"'{status}'", message)


class MainTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.pins = Path(tmp.name) / "mavlink-pins.env"
        self.pins.write_text(f"MAVLINK_REF={MAVLINK}\nPYMAVLINK_REF={PYMAVLINK}\n", "utf-8")
        self.action = Path(tmp.name) / "action.yml"
        self.action.write_text(FIXTURE, "utf-8")
        patcher = mock.patch.dict(os.environ, {"GITHUB_API_URL": API + "/"})
        patcher.start()
        self.addCleanup(patcher.stop)
        os.environ.pop("GITHUB_ACTIONS", None)

    def run_main(self, argv: list[str], get, **kwargs) -> tuple[int, str, str]:
        out, err = io.StringIO(), io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            code = check.main(argv, get=get, **{"action": self.action, **kwargs})
        return code, out.getvalue(), err.getvalue()

    def test_passes_when_both_pins_are_on_their_branches(self) -> None:
        code, out, err = self.run_main(
            [str(self.pins)], fake_api({"mavlink": "behind", "pymavlink": "identical"})
        )
        self.assertEqual((code, err), (0, ""))
        self.assertEqual(len(out.splitlines()), 2)
        self.assertIn("is on example/two master", out)

    def test_reads_the_setup_action_by_default(self) -> None:
        repositories = check.read_repositories(check.ACTION, ["mavlink", "pymavlink"])
        code, out, err = self.run_main(
            [str(self.pins)],
            fake_api({"mavlink": "behind", "pymavlink": "behind"}, repositories),
            action=check.ACTION,
        )
        self.assertEqual((code, err), (0, ""))
        self.assertIn(f"is on {repositories['pymavlink']} master", out)

    def test_fails_when_a_pin_is_not_on_its_branch(self) -> None:
        code, out, err = self.run_main(
            [str(self.pins)], fake_api({"mavlink": "behind", "pymavlink": "diverged"})
        )
        self.assertEqual(code, 1)
        self.assertIn("mavlink pin", out)
        self.assertIn("error: pymavlink pin", err)

    def test_reports_an_annotation_in_github_actions(self) -> None:
        os.environ["GITHUB_ACTIONS"] = "true"
        code, out, _ = self.run_main(
            [str(self.pins)], fake_api({"mavlink": "ahead", "pymavlink": "behind"})
        )
        self.assertEqual(code, 1)
        self.assertIn("::error title=generator pins::mavlink pin", out)
        self.assertEqual(check.escape("a%b\r\nc"), "a%25b%0D%0Ac")

    def test_an_api_error_is_exit_status_2(self) -> None:
        def get(url: str):
            raise check.ApiError(f"{url}: HTTP 404")

        code, out, err = self.run_main([str(self.pins)], get)
        self.assertEqual((code, out), (2, ""))
        self.assertIn("HTTP 404", err)

    def test_an_action_without_a_pin_s_checkout_is_exit_status_2(self) -> None:
        self.action.write_text(FIXTURE.replace(SECOND, ""), "utf-8")
        code, out, err = self.run_main([str(self.pins)], fake_api({}))
        self.assertEqual((code, out), (2, ""))
        self.assertIn("error: ", err)
        self.assertIn("0 actions/checkout steps have path: pymavlink, not one", err)

    def test_a_tree_without_the_action_file_is_exit_status_2(self) -> None:
        # The script on its own, as in a checkout that lacks the action.
        root = self.pins.parent / "tree"
        scripts = root / ".github" / "scripts" / "generate_c_lib"
        scripts.mkdir(parents=True)
        for name in ("check_pins_upstream.py", "read_pins.sh"):
            (scripts / name).write_bytes((Path(check.__file__).parent / name).read_bytes())
        env = {
            key: value
            for key, value in os.environ.items()
            if key not in ("GH_TOKEN", "GITHUB_TOKEN")
        }
        run = subprocess.run(
            [sys.executable, str(scripts / "check_pins_upstream.py"), str(self.pins)],
            capture_output=True,
            text=True,
            env=env,
            check=False,
        )
        self.assertEqual((run.returncode, run.stdout), (2, ""))
        self.assertTrue(run.stderr.startswith("error: "), run.stderr)
        self.assertIn("action.yml: cannot read the action file: ", run.stderr)
        self.assertNotIn("Traceback", run.stderr)

    def test_a_bad_pins_file_is_exit_status_2(self) -> None:
        self.pins.write_text("MAVLINK_REF=\n", "utf-8")
        code, _, err = self.run_main([str(self.pins)], fake_api({}))
        self.assertEqual(code, 2)
        self.assertIn("MAVLINK_REF must be set once", err)

    def test_a_wrong_argument_count_is_a_usage_error(self) -> None:
        code, _, err = self.run_main([], fake_api({}))
        self.assertEqual(code, 2)
        self.assertIn("usage:", err)

    def test_runs_as_a_script(self) -> None:
        with (
            mock.patch.object(sys, "argv", ["check_pins_upstream.py"]),
            contextlib.redirect_stderr(io.StringIO()),
            self.assertRaises(SystemExit) as exit_,
        ):
            runpy.run_path(check.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
