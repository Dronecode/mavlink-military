#!/usr/bin/env python3
"""Tests for release_generator.py and release_settings.py, with a stand-in gh.
From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_release_generator.py'
"""

from __future__ import annotations

import contextlib
import io
import json
import os
import runpy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
sys.path.insert(0, str(HERE))
import release_generator as rg  # noqa: E402
import release_settings as rs  # noqa: E402
from fake_gh import FakeGh  # noqa: E402

GEN = "slsa-framework/slsa-github-generator"
WORKFLOW = f"{GEN}/.github/workflows/generator_generic_slsa3.yml"
COMMIT = "f" * 40
REPO = "Dronecode/mavlink-military"
SHA = "c" * 40
ENV = {
    "GENERATOR_WORKFLOW": WORKFLOW, "GENERATOR_TAG": "v2.1.0", "GENERATOR_COMMIT": COMMIT,
    "GENERATOR_ACTIONS": f"{GEN}@v2.1.0={COMMIT} actions/checkout@{'1' * 40}={'1' * 40}",
    "GITHUB_REPOSITORY": REPO, "GITHUB_SHA": SHA, "GITHUB_RUN_ID": "77", "GITHUB_RUN_ATTEMPT": "2",
    "GENERATOR_JOB": "Sign the provenance", "GITHUB_ACTOR": "tagger", "GITHUB_TRIGGERING_ACTOR": "rerunner",
}  # fmt: skip


def log(
    *downloads: tuple[str, str], permissions: tuple[str, ...] = ("Actions: read", "Contents: read")
) -> str:
    lines = [
        "2026-10-20T02:32:39.0Z Current runner version: '2.337.0'",
        "2026-10-20T02:32:39.1Z ##[group]GITHUB_TOKEN Permissions",
    ]
    lines += [f"2026-10-20T02:32:39.1Z {p}" for p in permissions] + [
        "2026-10-20T02:32:39.1Z ##[endgroup]"
    ]
    lines += [
        f"2026-10-20T02:32:39.4Z Download action repository '{a}' (SHA:{s})" for a, s in downloads
    ]
    lines += [
        "2026-10-20T02:32:40.0Z Contents: write appears in a later step's output, outside the block"
    ]
    return "\n".join(lines) + "\n"


class GhCase(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)
        self.gh = FakeGh(self.tmp)
        patcher = mock.patch.dict(os.environ, {**self.gh.env(), **ENV})
        patcher.start()
        self.addCleanup(patcher.stop)
        self.gen = rg.expected(dict(os.environ))

    def main(self, module, *args: str) -> tuple[int, str]:
        out = io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(io.StringIO()):
            code = module.main([module.__name__ + ".py", *args])
        return code, out.getvalue()


class PinTest(GhCase):
    def answer(self, ref: dict, archived: bool = False, release: dict | None = None) -> None:
        self.gh.on("api", f"repos/{GEN}/git/ref/tags/v2.1.0", stdout={"object": ref})
        self.gh.on("api", f"repos/{GEN}", stdout={"archived": archived})
        self.gh.on(
            "api",
            f"repos/{GEN}/releases/tags/v2.1.0",
            stdout=release or {"draft": False, "prerelease": False},
        )

    def test_a_lightweight_tag_on_the_reviewed_commit_passes(self) -> None:
        self.answer({"type": "commit", "sha": COMMIT})
        code, out = self.main(rg, "pin")
        self.assertEqual(code, 0)
        self.assertIn(f"{GEN} v2.1.0 names {COMMIT}", out)

    def test_an_annotated_tag_is_peeled(self) -> None:
        self.gh.on(
            "api",
            f"repos/{GEN}/git/tags/{'a' * 40}",
            stdout={"object": {"type": "commit", "sha": COMMIT}},
        )
        self.answer({"type": "tag", "sha": "a" * 40})
        self.assertEqual(self.main(rg, "pin")[0], 0)

    def test_a_moved_tag_an_archived_repository_or_a_pre_release_fail(self) -> None:
        for ref, archived, release, message in (
            ({"type": "commit", "sha": "0" * 40}, False, None, f"names {'0' * 40}, not the reviewed {COMMIT}"),
            ({"type": "commit", "sha": COMMIT}, True, None, f"{GEN} is archived"),
            ({"type": "commit", "sha": COMMIT}, False, {"draft": False, "prerelease": True}, "is a draft or a pre-release"),
        ):  # fmt: skip
            with self.subTest(message=message):
                self.gh.responses.clear()
                self.answer(ref, archived, release)
                code, out = self.main(rg, "pin")
                self.assertEqual(code, 1)
                self.assertIn(message, out)

    def test_a_failed_read_fails(self) -> None:
        code, out = self.main(rg, "pin")
        self.assertEqual(code, 1)
        self.assertIn("::error title=release generator::", out)

    def test_usage(self) -> None:
        for args in ((), ("other",), ("audit",), ("pin", "extra")):
            with self.subTest(args=args):
                self.assertEqual(self.main(rg, *args)[0], 2)

    def test_runs_as_a_script(self) -> None:
        with mock.patch.object(sys, "argv", ["release_generator.py"]), contextlib.redirect_stderr(
            io.StringIO()
        ):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(rg.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


class RunTest(GhCase):
    def answer(self, *called: dict) -> None:
        self.gh.on(
            "api",
            f"repos/{REPO}/actions/runs/77/attempts/2",
            stdout={"referenced_workflows": list(called)},
        )

    def generator(self, **changes: str) -> dict:
        return {"path": f"{WORKFLOW}@v2.1.0", "ref": "refs/tags/v2.1.0", "sha": COMMIT, **changes}

    def local(self, name: str, sha: str = SHA) -> dict:
        return {
            "path": f"{REPO}/.github/workflows/{name}@{sha}",
            "ref": "refs/tags/v1.0.0",
            "sha": sha,
        }

    def test_the_generator_and_this_repositorys_workflows_pass(self) -> None:
        self.answer(self.local("docs.yml"), self.generator(), self.local("validate_dialect.yml"))
        code, out = self.main(rg, "run")
        self.assertEqual(code, 0)
        self.assertIn(f"loaded the generator at {COMMIT} and 2 workflow(s) of {REPO} at {SHA}", out)

    def test_anything_else_fails(self) -> None:
        for called, message in (
            ((self.generator(sha="0" * 40),), "not the generator alone"),
            ((self.generator(ref="refs/heads/main"),), "not the generator alone"),
            ((self.generator(path=f"{WORKFLOW}@main"),), "not the generator alone"),
            ((self.generator(), self.generator()), "not the generator alone"),
            ((), "not the generator alone"),
            ((self.generator(), {"path": "other/repo/.github/workflows/x.yml@v1", "sha": "1" * 40}), "not the generator alone"),
            ((self.generator(), self.local("docs.yml", sha="2" * 40)), "called workflows not at this run's commit"),
        ):  # fmt: skip
            with self.subTest(called=called):
                self.gh.responses.clear()
                self.answer(*called)
                code, out = self.main(rg, "run")
                self.assertEqual(code, 1)
                self.assertIn(message, out)


class AuditTest(GhCase):
    def answer(self, jobs: list[dict], logs: dict[int, str]) -> None:
        self.gh.on(
            "api",
            f"repos/{REPO}/actions/runs/77/attempts/2/jobs?per_page=100",
            stdout={"jobs": jobs},
        )
        for job_id, text in logs.items():
            self.gh.on("api", f"repos/{REPO}/actions/jobs/{job_id}/logs", stdout=text)

    def job(self, job_id: int, name: str, conclusion: str = "success") -> dict:
        return {"id": job_id, "name": f"Sign the provenance / {name}", "conclusion": conclusion,
                "started_at": "2026-10-20T02:32:39Z", "completed_at": "2026-10-20T02:34:00Z"}  # fmt: skip

    def test_a_clean_run_is_recorded(self) -> None:
        jobs = [self.job(1, "detect-env"), self.job(2, "generator"), self.job(3, "upload-assets", "skipped"),
                {"id": 9, "name": "Publish the release", "conclusion": "success"}]  # fmt: skip
        self.answer(
            jobs,
            {
                1: log((f"{GEN}@v2.1.0", COMMIT)),
                2: log((f"{GEN}@v2.1.0", COMMIT), (f"actions/checkout@{'1' * 40}", "1" * 40)),
            },
        )
        record_path = self.tmp / "audit.json"
        code, out = self.main(rg, "audit", str(record_path))
        self.assertEqual(code, 0, out)
        self.assertIn("2 generator job(s) audited", out)
        record = json.loads(record_path.read_text())
        self.assertEqual(
            [j["name"] for j in record["jobs"]],
            ["Sign the provenance / detect-env", "Sign the provenance / generator"],
        )
        self.assertEqual(record["jobs"][0]["seconds"], 81)
        self.assertEqual(record["jobs"][1]["token"], {"Actions": "read", "Contents": "read"})
        self.assertNotIn("approvals", record)

    def test_an_unknown_action_a_moved_inner_action_or_a_write_token_fails(self) -> None:
        for text, message in (
            (log(("other/action@v1", "2" * 40)), "downloaded other/action@v1"),
            (log((f"{GEN}@v2.1.0", "3" * 40)), f"downloaded {GEN}@v2.1.0 at {'3' * 40}"),
            (log(permissions=("Contents: write",)), "ran with a Contents: write token"),
            ("no permissions block at all\n", "has no GITHUB_TOKEN Permissions block"),
            (log(permissions=("Contents: read", "a note")), "an unexpected line in a GITHUB_TOKEN Permissions block"),
            ("x ##[group]GITHUB_TOKEN Permissions\nx Contents: read\n", "a GITHUB_TOKEN Permissions block does not end"),
        ):  # fmt: skip
            with self.subTest(message=message):
                self.gh.responses.clear()
                self.answer([self.job(1, "generator")], {1: text})
                code, out = self.main(rg, "audit", str(self.tmp / "audit.json"))
                self.assertEqual(code, 1)
                self.assertIn(message, out)

    def test_no_generator_job_fails(self) -> None:
        self.answer([self.job(3, "upload-assets", "skipped")], {})
        code, out = self.main(rg, "audit", str(self.tmp / "audit.json"))
        self.assertEqual(code, 1)
        self.assertIn("no job of Sign the provenance ran in this attempt", out)

    def test_a_job_without_times(self) -> None:
        job = self.job(1, "generator")
        job["completed_at"] = None
        self.answer([job], {1: log()})
        record_path = self.tmp / "audit.json"
        self.assertEqual(self.main(rg, "audit", str(record_path))[0], 0)
        self.assertIsNone(json.loads(record_path.read_text())["jobs"][0]["seconds"])


SETTINGS_ENV = {"VARS_JSON": "{}"}


class SettingsTest(GhCase):
    def answer(self, main_rules: list | None = None, rulesets: list | None = None,
               details: dict | None = None) -> None:  # fmt: skip
        self.gh.on("api", f"repos/{REPO}/rules/branches/main?per_page=100", stdout=main_rules if main_rules is not None else [
            {"type": "pull_request", "parameters": {"required_approving_review_count": 1}, "ruleset_id": 1},
            {"type": "non_fast_forward", "ruleset_id": 1}, {"type": "deletion", "ruleset_id": 1}])  # fmt: skip
        self.gh.on("api", f"repos/{REPO}/rulesets?includes_parents=true&per_page=100", stdout=rulesets if rulesets is not None else [
            {"id": 1, "target": "branch", "enforcement": "active"}, {"id": 5, "target": "tag", "enforcement": "disabled"},
            {"id": 2, "target": "tag", "enforcement": "active"}])  # fmt: skip
        found = {
            1: {"current_user_can_bypass": "never"},
            2: {"current_user_can_bypass": "never", "conditions": {"ref_name": {"include": ["~ALL"]}},
                "rules": [{"type": "creation"}, {"type": "update"}, {"type": "deletion"}]},
        }  # fmt: skip
        found.update(details or {})
        for ruleset_id, body in found.items():
            self.gh.on(
                "api", f"repos/{REPO}/rulesets/{ruleset_id}?includes_parents=true", stdout=body
            )

    def run_settings(self, env: dict | None = None) -> tuple[int, str]:
        with mock.patch.dict(os.environ, {**SETTINGS_ENV, **(env or {})}):
            return self.main(rs)

    def test_every_setting_holding_passes(self) -> None:
        self.answer()
        code, out = self.run_settings()
        self.assertEqual(code, 0, out)
        self.assertIn("the rulesets on main and on every tag, and the variables hold", out)

    def test_the_administrators_may_bypass(self) -> None:
        admins = [{"actor_type": "RepositoryRole", "actor_id": 5, "bypass_mode": "always"},
                  {"actor_type": "OrganizationAdmin", "actor_id": 1, "bypass_mode": "always"}]  # fmt: skip
        self.answer(details={
            1: {"current_user_can_bypass": "never", "bypass_actors": admins},
            2: {"current_user_can_bypass": "never", "conditions": {"ref_name": {"include": ["~ALL"]}},
                "rules": [{"type": "creation"}, {"type": "update"}, {"type": "deletion"}], "bypass_actors": admins},
        })  # fmt: skip
        code, out = self.run_settings()
        self.assertEqual(code, 0, out)

    def test_main_shortfalls(self) -> None:
        for rules, details, message in (
            ([{"type": "non_fast_forward", "ruleset_id": 1}], None, "main: no active rule deletion"),
            ([{"type": "pull_request", "parameters": {"required_approving_review_count": 0}, "ruleset_id": 1},
              {"type": "non_fast_forward", "ruleset_id": 1}, {"type": "deletion", "ruleset_id": 1}], None, "a pull request needs no approval"),
            (None, {1: {"current_user_can_bypass": "always"}}, "this run's token can bypass it (always)"),
            (None, {1: {"current_user_can_bypass": "never", "bypass_actors": [{"actor_type": "Team", "actor_id": 9}]}},
             "main ruleset 1: its bypass list names more than the administrators"),
        ):  # fmt: skip
            with self.subTest(message=message):
                self.gh.responses.clear()
                self.answer(main_rules=rules, details=details)
                code, out = self.run_settings()
                self.assertEqual(code, 1)
                self.assertIn(message, out)

    def test_tag_shortfalls(self) -> None:
        narrow = {2: {"current_user_can_bypass": "never", "conditions": {"ref_name": {"include": ["refs/tags/v*"]}},
                      "rules": [{"type": "creation"}, {"type": "update"}, {"type": "deletion"}]}}  # fmt: skip
        # Every tag but the release tags: ~ALL with an exclusion protects nothing a release uses.
        excluding = {2: {"current_user_can_bypass": "never",
                         "conditions": {"ref_name": {"include": ["~ALL"], "exclude": ["refs/tags/v*"]}},
                         "rules": [{"type": "creation"}, {"type": "update"}, {"type": "deletion"}]}}  # fmt: skip
        for rulesets, details, message in (
            ([], None, "no active tag ruleset covers every tag (~ALL)"),
            (None, narrow, "no active tag ruleset covers every tag (~ALL)"),
            (None, excluding, "no active tag ruleset covers every tag (~ALL)"),
            (None, {2: {"current_user_can_bypass": "pull_requests_only", "conditions": {"ref_name": {"include": ["~ALL"]}},
                        "rules": [{"type": "creation"}, {"type": "update"}, {"type": "deletion"}]}}, "tag ruleset 2: this run's token can bypass it"),
        ):  # fmt: skip
            with self.subTest(message=message):
                self.gh.responses.clear()
                self.answer(rulesets=rulesets, details=details)
                code, out = self.run_settings()
                self.assertEqual(code, 1)
                self.assertIn(message, out)

    def test_variables_must_be_empty(self) -> None:
        for text, message in (
            ('{"A": "1", "B": "2"}', "['A', 'B']"),
            ("not json", "unreadable"),
            ("", "unreadable"),
        ):
            with self.subTest(text=text):
                self.gh.responses.clear()
                self.answer()
                code, out = self.run_settings({"VARS_JSON": text})
                self.assertEqual(code, 1)
                self.assertIn(f"configuration variables are set ({message})", out)

    def test_a_failed_read_fails_closed(self) -> None:
        code, out = self.run_settings()
        self.assertEqual(code, 1)
        self.assertIn("could not read the settings: gh api", out)

    def test_usage_and_script(self) -> None:
        self.assertEqual(self.main(rs, "extra")[0], 2)
        with mock.patch.object(
            sys, "argv", ["release_settings.py", "x"]
        ), contextlib.redirect_stderr(io.StringIO()):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(rs.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
