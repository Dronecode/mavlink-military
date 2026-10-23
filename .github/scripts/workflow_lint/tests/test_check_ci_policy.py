"""Tests for check_ci_policy.py, on small repositories in a temporary
directory and on this repository. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/workflow_lint/tests
"""

from __future__ import annotations

import contextlib
import importlib
import io
import os
import runpy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
policy = importlib.import_module("check_ci_policy")

REPOSITORY = Path(__file__).resolve().parents[4]
HASH = "--hash=sha256:" + "0" * 64
LOCK = f"# A lock.\nlxml==6.1.3 \\\n    {HASH} \\\n    {HASH}\n"
LOCKED = (
    "python3 -m pip install --quiet --require-hashes --only-binary :all: --no-deps "
    "-r .github/requirements/a.txt"
)


def workflow(on: str, steps: str = "", runs_on: str = "ubuntu-24.04") -> str:
    return f"""name: Test

on:
{on}
permissions:
  contents: read

jobs:
  test:
    runs-on: {runs_on}
    steps:
{steps}"""


def run_step(script: str) -> str:
    lines = "".join(f"          {line}\n" for line in script.split("\n"))
    return f"      - name: Run\n        run: |\n{lines}"


class PolicyTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.root = Path(tmp.name)
        self.write(".github/requirements/a.txt", LOCK)

    def write(self, path: str, text: str) -> None:
        file = self.root / path
        file.parent.mkdir(parents=True, exist_ok=True)
        file.write_text(text, encoding="utf-8")

    def findings(self) -> list[tuple[str, str, int, str]]:
        return [tuple(f) for f in policy.check(self.root)]

    def messages(self, level: str = "error") -> list[str]:
        return [f.message for f in policy.check(self.root) if f.level == level]


class PipTest(PolicyTest):
    def check_command(self, command: str) -> list[str]:
        self.write(".github/workflows/w.yml", workflow("  push:\n", run_step(command)))
        return self.messages()

    def test_a_locked_install_passes(self) -> None:
        self.assertEqual(self.check_command(LOCKED), [])

    def test_every_spelling_of_the_options_is_read(self) -> None:
        for command in (
            (
                "pip install -q --require-hashes --only-binary=:all: --no-deps "
                "-r.github/requirements/a.txt"
            ),
            (
                "pip3 install --require-hashes --no-deps --only-binary :all: "
                "--requirement=../.github/requirements/a.txt"
            ),
            (
                "pip install --require-hashes --no-deps --only-binary :all: \\\n"
                "  --requirement .github/requirements/a.txt  # a comment"
            ),
        ):
            with self.subTest(command=command):
                self.assertEqual(self.check_command(command), [])

    def test_an_unlocked_install_is_an_error_naming_each_problem(self) -> None:
        (message,) = self.check_command("pip install --user future lxml")
        self.assertEqual(
            message,
            "not a hash-locked install: uses --user, which a locked install does not need; "
            "names the package future instead of a lock file; names the package lxml instead "
            "of a lock file; lacks --require-hashes; lacks --only-binary :all:; lacks --no-deps; "
            "reads no -r file from .github/requirements/",
        )

    def test_a_lock_outside_the_directory_or_missing_is_an_error(self) -> None:
        (message,) = self.check_command(
            "pip install --require-hashes --only-binary :all: --no-deps "
            "-r requirements.txt -r .github/requirements/missing.txt"
        )
        self.assertIn("reads requirements.txt, which is not in .github/requirements/", message)
        self.assertIn("reads .github/requirements/missing.txt, which does not exist", message)

    def test_a_versioned_pip_command_is_read(self) -> None:
        self.assertEqual(len(self.check_command("pip3.12 install lxml")), 1)

    def test_options_without_their_values_are_errors(self) -> None:
        (message,) = self.check_command("pip install --require-hashes --no-deps --only-binary")
        self.assertIn("lacks --only-binary :all:", message)
        (message,) = self.check_command(
            "pip install --require-hashes --no-deps --only-binary :all: -r"
        )
        self.assertIn("reads , which is not in .github/requirements/", message)

    def test_an_unreadable_command_is_an_error(self) -> None:
        self.assertEqual(
            self.check_command("pip install 'unbalanced"), ["cannot read this pip install command"]
        )

    def test_comments_and_step_names_are_not_commands(self) -> None:
        self.assertEqual(self.check_command("# pip install future\necho done"), [])
        self.write(
            ".github/workflows/w.yml",
            workflow("  push:\n", "      - name: pip install the packages\n        run: true\n"),
        )
        self.assertEqual(self.messages(), [])

    def test_actions_and_scripts_are_read_too(self) -> None:
        self.write(
            ".github/actions/setup/action.yml",
            "runs:\n  using: composite\n  steps:\n    - shell: bash\n      run: pip install x\n",
        )
        self.write(".github/scripts/area/do.sh", "#!/bin/sh\nnpm install\n")
        self.assertEqual(
            [(f[1], f[2]) for f in self.findings()],
            [(".github/actions/setup/action.yml", 5), (".github/scripts/area/do.sh", 2)],
        )


class NpmTest(PolicyTest):
    def check_command(self, command: str) -> list[str]:
        self.write(".github/workflows/w.yml", workflow("  push:\n", run_step(command)))
        return self.messages()

    def test_npm_ci_without_install_scripts_passes(self) -> None:
        self.assertEqual(self.check_command("npm ci --ignore-scripts\nnpm run build"), [])

    def test_npm_ci_with_install_scripts_is_an_error(self) -> None:
        self.assertEqual(
            self.check_command("npm ci"), ["npm ci runs install scripts; add --ignore-scripts"]
        )

    def test_npm_install_is_an_error(self) -> None:
        self.assertEqual(
            self.check_command("npm i lodash"),
            ["npm i resolves versions or runs package code; use npm ci --ignore-scripts"],
        )

    def test_every_spelling_of_npm_ci_needs_ignore_scripts(self) -> None:
        for command in ("clean-install", "ic", "install-clean", "cit"):
            with self.subTest(command=command):
                self.assertEqual(
                    self.check_command(f"npm {command}"),
                    [f"npm {command} runs install scripts; add --ignore-scripts"],
                )
                self.assertEqual(self.check_command(f"npm {command} --ignore-scripts"), [])

    def test_commands_that_resolve_or_run_package_code_are_errors(self) -> None:
        for command in ("update", "rebuild", "exec vitepress", "it"):
            with self.subTest(command=command):
                self.assertEqual(len(self.check_command(f"npm {command}")), 1)
        self.assertEqual(
            self.check_command("npx vitepress build"),
            ["npx can fetch and run a package the lockfile does not pin; use npm run"],
        )


class TriggerTest(PolicyTest):
    def check_on(self, on: str) -> list[tuple[int, str]]:
        self.write(".github/workflows/w.yml", workflow(on))
        return [(f.line, f.message) for f in policy.check(self.root) if f.level == "error"]

    def test_an_unfiltered_pull_request_trigger_passes(self) -> None:
        on = (
            "  # Every pull request.\n"
            "  pull_request:\n"
            "    types: [opened, synchronize]\n"
            "  push:\n"
            "    branches: [main]\n"
            "    paths:\n"
            '      - "docs/**"\n'
        )
        self.assertEqual(self.check_on(on), [])

    def test_each_pull_request_filter_is_an_error(self) -> None:
        for name in ("paths", "paths-ignore", "branches", "branches-ignore"):
            with self.subTest(name=name):
                found = self.check_on(f'  pull_request_target:\n    {name}:\n      - "x"\n')
                self.assertEqual([line for line, _ in found], [5])
                self.assertIn("cannot be required", found[0][1])

    def test_a_filter_in_a_flow_mapping_is_an_error(self) -> None:
        self.assertEqual(
            [line for line, _ in self.check_on("  pull_request: {paths: [x]}  # filtered\n")], [4]
        )

    def test_settings_from_an_alias_or_merge_key_count_as_a_filter(self) -> None:
        aliased = "  push: &filters\n    paths: [docs/**]\n  pull_request: *filters\n"
        merged = "  push: &filters\n    paths: [docs/**]\n  pull_request:\n    <<: *filters\n"
        self.assertEqual([line for line, _ in self.check_on(aliased)], [6])
        self.assertEqual([line for line, _ in self.check_on(merged)], [7])
        self.assertEqual(self.check_on("  pull_request: &pr\n    types: [opened]\n"), [])
        self.assertEqual(self.check_on("  pull_request:\n    types: *kinds\n"), [])

    def test_a_filter_in_a_flow_mapping_on_is_an_error(self) -> None:
        for on, lines in (
            ("on: {push: {}, pull_request: {paths: [x]}}", [2]),
            ("on: {pull_request: {types: [opened]}}", []),
            ("on: {push: {paths: [x]}}", []),
        ):
            with self.subTest(on=on):
                self.write(".github/workflows/w.yml", f"name: Test\n{on}\njobs: {{}}\n")
                self.assertEqual([f.line for f in policy.check(self.root)], lines)

    def test_a_flow_or_scalar_on_has_no_filter(self) -> None:
        for on in ('"on": [push, pull_request]', "on: pull_request"):
            self.write(".github/workflows/w.yml", f"name: Test\n{on}\njobs: {{}}\n")
            self.assertEqual(self.messages(), [])

    def test_triggers_are_read_only_in_workflows(self) -> None:
        self.write(
            ".github/actions/a/action.yml", "on:\n  pull_request:\n    paths: [x]\nruns: {}\n"
        )
        self.assertEqual(self.messages(), [])


class RunnerTest(PolicyTest):
    def test_a_moving_runner_label_is_a_warning(self) -> None:
        self.write(".github/workflows/w.yml", workflow("  push:\n", runs_on="ubuntu-latest"))
        self.assertEqual(self.messages("warning"), ["runs-on ubuntu-latest, not ubuntu-24.04"])
        self.assertEqual(self.messages(), [])

    def test_a_runner_list_is_a_warning(self) -> None:
        self.write(".github/workflows/w.yml", "jobs:\n  a:\n    runs-on:\n      - self-hosted\n")
        self.assertEqual(self.messages("warning"), ["runs-on (a list), not ubuntu-24.04"])

    def test_python_versions_must_be_exact(self) -> None:
        steps = (
            "      - uses: actions/setup-python@0 # v7\n"
            "        with:\n"
            '          python-version: "3.12.15"  # exact\n'
            "      - uses: actions/setup-python@0 # v7\n"
            "        with:\n"
            "          python-version: 3.x\n"
        )
        self.write(".github/workflows/w.yml", workflow("  push:\n", steps))
        self.assertEqual(self.messages("warning"), ["python-version '3.x' is not an exact X.Y.Z"])

    def test_an_action_input_default_is_checked_and_its_use_is_not(self) -> None:
        action = (
            "inputs:\n"
            "  python-version:\n"
            "    description: Python\n"
            "\n"
            '    default: "3.12"\n'
            "runs:\n"
            "  steps:\n"
            "    - uses: actions/setup-python@0 # v7\n"
            "      with:\n"
            "        python-version: ${{ inputs.python-version }}\n"
        )
        self.write(".github/actions/a/action.yml", action)
        self.assertEqual(self.messages("warning"), ["python-version '3.12' is not an exact X.Y.Z"])

    def test_an_input_without_a_default_is_a_warning(self) -> None:
        for action in (
            "inputs:\n  python-version:\nruns: {}\n",
            "runs: {}\ninputs:\n  python-version:\n    description: Python\n",
        ):
            with self.subTest(action=action):
                self.write(".github/actions/a/action.yml", action)
                self.assertEqual(
                    self.messages("warning"), ["python-version '' is not an exact X.Y.Z"]
                )

    def test_an_expression_naming_something_else_is_a_warning(self) -> None:
        steps = "        with:\n          python-version: ${{ matrix.python }}\n"
        self.write(".github/workflows/w.yml", workflow("  push:\n", steps))
        self.assertEqual(
            self.messages("warning"),
            ["python-version '${{ matrix.python }}' is not an exact X.Y.Z"],
        )


class RequirementsTest(PolicyTest):
    def check_lock(self, text: str) -> list[tuple[int, str]]:
        self.write(".github/requirements/a.txt", text)
        return [(f.line, f.message) for f in policy.check(self.root)]

    def test_exact_pins_with_hashes_pass(self) -> None:
        lock = (
            LOCK + f"# a comment line ending in a backslash does not continue \\\n"
            f'tomli==2.0.1 ; python_version < "3.11" {HASH}  # inline\n'
            f"name[extra]==1.0 \\\n    {HASH}\n\n"
        )
        self.assertEqual(self.check_lock(lock), [])

    def test_anything_else_is_an_error(self) -> None:
        for line in (
            "lxml>=6.1.0",
            "lxml==6.1.3",
            "-e .",
            "--index-url https://example.test/simple",
        ):
            with self.subTest(line=line):
                self.assertEqual(
                    self.check_lock(f"# Lock.\n{line}\n"),
                    [(2, "not an exact == pin with --hash=sha256: digests (no other options)")],
                )

    def test_an_option_after_a_comment_with_a_backslash_is_still_read(self) -> None:
        found = self.check_lock(LOCK + "# a note \\\n--extra-index-url https://example.test\n")
        self.assertEqual([line for line, _ in found], [6])

    def test_a_file_that_pins_nothing_is_an_error(self) -> None:
        self.assertEqual(self.check_lock("# Nothing.\n"), [(1, "the file pins no package")])

    def test_a_continuation_at_the_end_of_the_file_is_read(self) -> None:
        self.assertEqual(self.check_lock(f"lxml==6.1.3 {HASH} \\"), [])


class LogicalLinesTest(unittest.TestCase):
    def test_joins_continued_lines_and_keeps_the_first_line_number(self) -> None:
        self.assertEqual(
            policy.logical_lines("a \\\nb \\\nc\nd # e \\\nf"),
            [(1, "a  b  c"), (4, "d # e \\"), (5, "f")],
        )


class MainTest(PolicyTest):
    def run_main(self, argv: list[str]) -> tuple[int, str, str]:
        out, err = io.StringIO(), io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            code = policy.main(argv)
        return code, out.getvalue(), err.getvalue()

    def setUp(self) -> None:
        super().setUp()
        patcher = mock.patch.dict(os.environ)
        patcher.start()
        self.addCleanup(patcher.stop)
        os.environ.pop("GITHUB_ACTIONS", None)

    def test_errors_fail_and_warnings_do_not(self) -> None:
        self.write(".github/workflows/w.yml", workflow("  push:\n", runs_on="ubuntu-latest"))
        code, out, err = self.run_main([str(self.root)])
        self.assertEqual(code, 0)
        self.assertEqual(out, "CI policy: 0 error(s), 1 warning(s)\n")
        self.assertIn("warning: .github/workflows/w.yml:11: runs-on ubuntu-latest", err)
        self.write(".github/workflows/w.yml", workflow("  push:\n", run_step("npm ci")))
        code, out, _ = self.run_main([str(self.root)])
        self.assertEqual((code, out), (1, "CI policy: 1 error(s), 0 warning(s)\n"))

    def test_findings_are_annotations_in_github_actions(self) -> None:
        os.environ["GITHUB_ACTIONS"] = "true"
        self.write(".github/workflows/w.yml", workflow("  push:\n", run_step("npm ci")))
        code, out, _ = self.run_main([str(self.root)])
        self.assertEqual(code, 1)
        self.assertIn(
            "::error file=.github/workflows/w.yml,line=15,title=CI policy::npm ci runs", out
        )
        self.assertEqual(policy.escape("a:b,c%\n", True), "a%3Ab%2Cc%25%0A")

    def test_the_current_directory_is_the_default_root(self) -> None:
        with mock.patch.object(policy, "check", return_value=[]) as check:
            code, _, _ = self.run_main([])
        self.assertEqual(code, 0)
        self.assertEqual(check.call_args.args, (Path("."),))

    def test_a_root_without_github_is_a_usage_error(self) -> None:
        code, _, err = self.run_main([str(self.root / "nowhere")])
        self.assertEqual(code, 2)
        self.assertIn("has no .github directory", err)

    def test_too_many_arguments_is_a_usage_error(self) -> None:
        code, _, err = self.run_main(["a", "b"])
        self.assertEqual(code, 2)
        self.assertIn("usage:", err)

    def test_runs_as_a_script(self) -> None:
        with (
            mock.patch.object(sys, "argv", ["check_ci_policy.py", "a", "b"]),
            contextlib.redirect_stderr(io.StringIO()),
            self.assertRaises(SystemExit) as exit_,
        ):
            runpy.run_path(policy.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


class RepositoryTest(unittest.TestCase):
    def test_this_repository_meets_the_policy(self) -> None:
        errors = [f for f in policy.check(REPOSITORY) if f.level == "error"]
        self.assertEqual(errors, [])


if __name__ == "__main__":
    unittest.main()
