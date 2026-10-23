#!/usr/bin/env python3
"""Contract tests of release.yml and of what every workflow may do, read with
PyYAML from the hash-locked test requirements. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_release_workflow.py'
"""

from __future__ import annotations

import re
import unittest
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[4]
WORKFLOWS = ROOT / ".github" / "workflows"
PINNED = re.compile(r"[\w.-]+/[\w./-]+@[0-9a-f]{40}")
# Spelled in two parts so that this file's own source does not match it.
PRAGMA = "pragma: " + "no cover"


def load(path: Path) -> dict:
    data = yaml.safe_load(path.read_text(encoding="utf-8"))
    # YAML 1.1 reads the key on as true.
    data["on"] = data.pop(True, data.get("on"))
    return data


RELEASE = load(WORKFLOWS / "release.yml")
JOBS = RELEASE["jobs"]
CALLS = {name: job for name, job in JOBS.items() if "uses" in job}
STEPS = {name: job for name, job in JOBS.items() if "steps" in job}
SETUP = "./.github/actions/setup-mavlink-tooling"
TOOLING = yaml.safe_load((ROOT / SETUP / "action.yml").read_text(encoding="utf-8"))


def as_run(steps: list[dict]) -> list[dict]:
    """Steps as the runner runs them: the setup action's own steps in place of each use of
    it, with its python-version input resolved."""
    found = []
    for step in steps:
        if step.get("uses") != SETUP:
            found.append(step)
            continue
        python = step.get("with", {}).get(
            "python-version", TOOLING["inputs"]["python-version"]["default"]
        )
        for inner in TOOLING["runs"]["steps"]:
            inputs = {
                key: python if value == "${{ inputs.python-version }}" else value
                for key, value in inner.get("with", {}).items()
            }
            found.append({**inner, "with": inputs} if "with" in inner else inner)
    return found


RUNS = {name: as_run(job["steps"]) for name, job in STEPS.items()}


class TriggerTest(unittest.TestCase):
    def test_final_version_tags_pull_requests_and_manual_runs_only(self) -> None:
        self.assertEqual(sorted(RELEASE["on"]), ["pull_request", "push", "workflow_dispatch"])
        self.assertEqual(RELEASE["on"]["push"], {"tags": ["v[0-9]+.[0-9]+.[0-9]+"]})
        self.assertIsNone(RELEASE["on"]["workflow_dispatch"])  # no inputs

    def test_every_pull_request_rehearses(self) -> None:
        # No path or branch filter: a workflow a filter skips reports no check, so the
        # rehearsal could not be a required one.
        self.assertIsNone(RELEASE["on"]["pull_request"])

    def test_no_workflow_starts_from_another_workflow_or_a_dispatch(self) -> None:
        # A job token with contents: write can send repository_dispatch events,
        # which start runs; no workflow here listens to them, nor to workflow_run
        # or pull_request_target.
        for path in sorted(WORKFLOWS.glob("*.y*ml")):
            with self.subTest(workflow=path.name):
                on = load(path)["on"]
                events = (
                    set(on) if isinstance(on, dict) else set(on if isinstance(on, list) else [on])
                )
                self.assertFalse(
                    events & {"repository_dispatch", "workflow_run", "pull_request_target"}
                )


class PermissionTest(unittest.TestCase):
    def test_the_workflow_grants_nothing_and_every_job_names_its_own(self) -> None:
        self.assertEqual(RELEASE["permissions"], {})
        for name, job in JOBS.items():
            with self.subTest(job=name):
                self.assertIn("permissions", job)

    def test_each_job_holds_exactly_its_permissions(self) -> None:
        read = {"contents": "read"}
        expected = {
            "preflight": {"contents": "read", "actions": "read"},
            "validate": read, "lint": read, "docs": read, "commit-checks": read, "test": read,
            "build": read, "rebuild": read, "assemble": read,
            "approve": {},
            "generator-check": {"contents": "read", "actions": "read"},
            "provenance": {"actions": "read", "id-token": "write", "contents": "write"},
            "generator-audit": {"contents": "read", "actions": "read"},
            "publish": {"contents": "write"},
        }  # fmt: skip
        self.assertEqual({name: job["permissions"] for name, job in JOBS.items()}, expected)

    def test_only_the_generator_call_signs_and_only_it_and_publish_write(self) -> None:
        for name, job in JOBS.items():
            with self.subTest(job=name):
                if name != "provenance":
                    self.assertNotIn("id-token", job["permissions"])
                if name not in ("provenance", "publish"):
                    self.assertNotIn("write", job["permissions"].values())


class IsolationTest(unittest.TestCase):
    def test_every_job_runs_on_the_pinned_hosted_image(self) -> None:
        for name, job in STEPS.items():
            with self.subTest(job=name):
                self.assertEqual(job["runs-on"], "ubuntu-24.04")

    def test_no_job_uses_a_cache(self) -> None:
        for name, steps in RUNS.items():
            for step in steps:
                with self.subTest(job=name, step=step.get("name")):
                    self.assertNotIn("actions/cache", step.get("uses", ""))
                    self.assertNotIn("cache", step.get("with", {}))

    def test_every_action_is_pinned_by_commit_and_no_checkout_keeps_credentials(self) -> None:
        for name, steps in RUNS.items():
            for step in steps:
                if "uses" not in step:
                    continue
                with self.subTest(job=name, step=step.get("name"), uses=step["uses"]):
                    self.assertRegex(step["uses"], PINNED)
                    if step["uses"].startswith("actions/checkout@"):
                        self.assertIs(step["with"]["persist-credentials"], False)

    def test_every_python_install_is_hash_locked_and_wheel_only(self) -> None:
        runs = [s.get("run", "") for steps in RUNS.values() for s in steps]
        commands = [line for run in runs for line in run.replace("\\\n", " ").splitlines()]
        installs = [line for line in commands if "pip install" in line]
        # The setup action's generator lock in four jobs, and the test tools.
        self.assertEqual(len(installs), 5)
        for line in installs:
            with self.subTest(line=line.strip()):
                for flag in (
                    "--require-hashes",
                    "--only-binary :all:",
                    "--no-deps",
                    "-r .github/requirements/",
                ):
                    self.assertIn(flag, line)

    def test_one_exact_python_for_every_job(self) -> None:
        found = {
            step["with"]["python-version"]
            for steps in RUNS.values()
            for step in steps
            if step.get("uses", "").startswith("actions/setup-python@")
        }
        self.assertEqual(len(found), 1, found)
        self.assertRegex(found.pop(), r"^3\.[0-9]+\.[0-9]+$")

    def test_no_expression_reaches_a_shell(self) -> None:
        for name, steps in RUNS.items():
            for step in steps:
                with self.subTest(job=name, step=step.get("name")):
                    self.assertNotIn("${{", step.get("run", ""))


class RunTest(unittest.TestCase):
    def test_every_job_with_steps_has_a_timeout(self) -> None:
        for name, job in STEPS.items():
            with self.subTest(job=name):
                self.assertIsInstance(job.get("timeout-minutes"), int)
                self.assertLessEqual(job["timeout-minutes"], 30)

    def test_one_run_per_ref_and_no_queue(self) -> None:
        self.assertEqual(
            RELEASE["concurrency"],
            {
                "group": "${{ github.workflow }}-release-${{ github.ref }}",
                "cancel-in-progress": "${{ github.event_name == 'pull_request' }}",
            },
        )
        for name, job in JOBS.items():
            with self.subTest(job=name):
                self.assertNotIn("concurrency", job)
        self.assertNotIn("queue", (WORKFLOWS / "release.yml").read_text(encoding="utf-8"))

    def test_the_plan_reads_the_whole_history(self) -> None:
        checkout = JOBS["preflight"]["steps"][0]
        self.assertTrue(checkout["uses"].startswith("actions/checkout@"))
        self.assertEqual(checkout["with"]["fetch-depth"], 0)

    def test_the_plan_has_what_the_api_break_checker_imports(self) -> None:
        # Once a release exists, the plan runs mavlink's check_api_break.py,
        # which imports lxml, so the job installs the generator lock first.
        steps = RUNS["preflight"]
        names = [step.get("name") for step in steps]
        installs = [
            index
            for index, step in enumerate(steps)
            if "-r .github/requirements/generator.txt" in step.get("run", "")
        ]
        self.assertTrue(installs, "no step installs the generator lock")
        self.assertLess(
            installs[0], names.index("Plan the version and check it against the version policy")
        )

    def test_the_workflow_scan_reads_this_repository_alone(self) -> None:
        # The test job checks mavlink and pymavlink out beside the repository,
        # and their workflows must not enter the release's evidence.
        steps = {step.get("name"): step for step in JOBS["test"]["steps"]}
        run = steps["Record zizmor's findings as SARIF"]["run"]
        self.assertRegex(run, r"zizmor --no-progress --format sarif \.github >")


class PragmaTest(unittest.TestCase):
    def test_every_coverage_exclusion_says_why(self) -> None:
        # An exclusion is for code no test can reach; its reason follows it on the line.
        scripts = sorted((ROOT / ".github" / "scripts").rglob("*.py")) + sorted(
            (ROOT / "docs" / "scripts").rglob("*.py")
        )
        self.assertTrue(scripts)
        found = 0
        for path in scripts:
            for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
                if PRAGMA in line:
                    found += 1
                    with self.subTest(file=str(path.relative_to(ROOT)), line=number):
                        self.assertRegex(line, re.escape(PRAGMA) + r" - \S")
        self.assertGreater(found, 0)


class GraphTest(unittest.TestCase):
    def test_the_repository_checks_run_through_their_own_workflows(self) -> None:
        self.assertEqual(
            {n: j["uses"] for n, j in CALLS.items() if n != "provenance"},
            {
                "validate": "./.github/workflows/validate_dialect.yml",
                "lint": "./.github/workflows/workflow_lint.yml",
                "docs": "./.github/workflows/docs.yml",
            },
        )
        self.assertEqual(
            CALLS["docs"]["with"],
            {"version": "${{ needs.preflight.outputs.tag }}", "artifact": "release-docs"},
        )

    def test_two_builds_and_an_assembly_that_needs_everything(self) -> None:
        self.assertEqual(
            sorted(JOBS["assemble"]["needs"]),
            sorted(
                [
                    "preflight",
                    "validate",
                    "lint",
                    "docs",
                    "commit-checks",
                    "test",
                    "build",
                    "rebuild",
                ]
            ),
        )
        for name in ("build", "rebuild", "commit-checks", "test", "validate", "lint", "docs"):
            with self.subTest(job=name):
                self.assertEqual(JOBS[name]["needs"], "preflight")
        self.assertEqual(JOBS["rebuild"]["env"]["TZ"], "Pacific/Kiritimati")
        build_steps = [s.get("name") for s in JOBS["build"]["steps"]]
        self.assertEqual(build_steps, [s.get("name") for s in JOBS["rebuild"]["steps"]])

    def test_the_builds_check_out_the_planned_commit(self) -> None:
        for name in ("build", "rebuild", "assemble", "test", "commit-checks"):
            with self.subTest(job=name):
                self.assertEqual(
                    JOBS[name]["steps"][0]["with"]["ref"], "${{ needs.preflight.outputs.commit }}"
                )


GENERATOR_LINE = (
    "    uses: slsa-framework/slsa-github-generator/.github/workflows/generator_generic_slsa3.yml@v2.1.0"
    " # f7dd8c54c2067bafc12ca7a55595d5ee9b75204a"
)
GUARD = (
    "github.repository == 'Dronecode/mavlink-military' && github.event_name == 'push' && "
    "startsWith(github.ref, 'refs/tags/v')"
)


class GeneratorTest(unittest.TestCase):
    def test_one_call_by_tag_with_the_reviewed_commit_beside_it(self) -> None:
        text = (WORKFLOWS / "release.yml").read_text(encoding="utf-8")
        self.assertEqual(
            [line for line in text.splitlines() if "slsa-framework/" in line and "uses:" in line],
            [GENERATOR_LINE],
        )
        env = RELEASE["env"]
        self.assertEqual(
            f"    uses: {env['GENERATOR_WORKFLOW']}@{env['GENERATOR_TAG']} # {env['GENERATOR_COMMIT']}",
            GENERATOR_LINE,
        )
        self.assertEqual(
            CALLS["provenance"]["uses"], f"{env['GENERATOR_WORKFLOW']}@{env['GENERATOR_TAG']}"
        )

    def test_no_other_workflow_uses_the_slsa_projects_code(self) -> None:
        for path in sorted(WORKFLOWS.glob("*.y*ml")):
            if path.name != "release.yml":
                with self.subTest(workflow=path.name):
                    self.assertNotIn("slsa-framework/", path.read_text(encoding="utf-8"))

    def test_every_input_is_set_and_nothing_uploads(self) -> None:
        self.assertEqual(
            CALLS["provenance"]["with"],
            {
                "base64-subjects": "${{ needs.assemble.outputs.subjects }}",
                "upload-assets": False,
                "provenance-name": "mavlink-m-${{ needs.preflight.outputs.version }}.intoto.jsonl",
                "compile-generator": False,
                "private-repository": False,
                "continue-on-error": False,
            },
        )

    def test_the_call_holds_nothing_but_the_call(self) -> None:
        self.assertLessEqual(
            set(CALLS["provenance"]), {"name", "if", "needs", "permissions", "uses", "with"}
        )
        self.assertNotIn("secrets", CALLS["provenance"])

    def test_the_reviewed_actions_are_listed_with_their_commits(self) -> None:
        env = RELEASE["env"]
        entries = env["GENERATOR_ACTIONS"].split()
        for entry in entries:
            with self.subTest(entry=entry):
                self.assertRegex(entry, r"^[\w.-]+/[\w.-]+@[\w.-]+=[0-9a-f]{40}$")
        self.assertIn(
            f"slsa-framework/slsa-github-generator@{env['GENERATOR_TAG']}={env['GENERATOR_COMMIT']}",
            entries,
        )


class PublicationGraphTest(unittest.TestCase):
    def test_only_the_approval_names_the_release_environment(self) -> None:
        self.assertEqual({n for n, j in JOBS.items() if "environment" in j}, {"approve"})
        self.assertEqual(JOBS["approve"]["environment"], "release")
        self.assertEqual([s.get("uses") for s in JOBS["approve"]["steps"]], [None])

    def test_the_approval_waits_for_two_builds_that_agree(self) -> None:
        condition = " ".join(JOBS["approve"]["if"].split())
        self.assertTrue(condition.startswith(GUARD))
        self.assertIn("needs.preflight.outputs.publish == 'true'", condition)
        self.assertIn("needs.build.outputs.sums_sha256 != ''", condition)
        self.assertIn(
            "needs.build.outputs.sums_sha256 == needs.rebuild.outputs.sums_sha256", condition
        )
        self.assertEqual(
            sorted(JOBS["approve"]["needs"]), ["assemble", "build", "preflight", "rebuild"]
        )

    def test_signing_and_publishing_follow_the_approval_and_the_checks(self) -> None:
        self.assertEqual(JOBS["generator-check"]["needs"], "approve")
        self.assertEqual(
            sorted(JOBS["provenance"]["needs"]), ["assemble", "generator-check", "preflight"]
        )
        self.assertEqual(JOBS["generator-audit"]["needs"], "provenance")
        self.assertEqual(
            sorted(JOBS["publish"]["needs"]), ["generator-audit", "preflight", "provenance"]
        )
        self.assertIn("needs.provenance.result == 'success'", JOBS["publish"]["if"])
        for name in ("approve", "generator-check", "provenance", "generator-audit", "publish"):
            with self.subTest(job=name):
                self.assertTrue(" ".join(JOBS[name]["if"].split()).startswith(GUARD))

    def test_the_publish_job_downloads_only_and_runs_the_script(self) -> None:
        uses = [s["uses"].split("@")[0] for s in JOBS["publish"]["steps"] if "uses" in s]
        self.assertEqual(
            uses, ["actions/checkout", "actions/setup-python", "actions/download-artifact"]
        )

    def test_the_settings_check_runs_only_where_a_release_may_be_published(self) -> None:
        steps = {s.get("name"): s for s in JOBS["preflight"]["steps"]}
        settings = steps["Check the settings a publication relies on"]
        self.assertEqual(settings["if"], "steps.plan.outputs.publish == 'true'")
        self.assertEqual(settings["env"]["VARS_JSON"], "${{ toJSON(vars) }}")
        self.assertNotIn(
            "if", steps["Check that the generator's tag still names its reviewed commit"]
        )


class VerifyWorkflowTest(unittest.TestCase):
    def setUp(self) -> None:
        self.workflow = load(WORKFLOWS / "release_verify.yml")

    def test_weekly_and_by_hand_only(self) -> None:
        # No pull request trigger: its script's tests run in release.yml on every pull request,
        # and a pull request run would read every release for nothing.
        on = self.workflow["on"]
        self.assertEqual(sorted(on), ["schedule", "workflow_dispatch"])
        self.assertEqual(on["schedule"], [{"cron": "23 6 * * 1"}])
        self.assertIs(self.workflow["concurrency"]["cancel-in-progress"], False)

    def test_it_only_reads(self) -> None:
        self.assertEqual(self.workflow["permissions"], {})
        jobs = self.workflow["jobs"]
        self.assertEqual(
            jobs["verify"]["permissions"], {"contents": "read", "attestations": "read"}
        )
        self.assertEqual(jobs["rebuild"]["permissions"], {"contents": "read"})

    def test_every_release_is_rebuilt_from_its_tag_when_there_is_one(self) -> None:
        rebuild = self.workflow["jobs"]["rebuild"]
        self.assertEqual(rebuild["if"], "needs.verify.outputs.count != '0'")
        self.assertEqual(
            rebuild["strategy"]["matrix"]["tag"], "${{ fromJSON(needs.verify.outputs.tags) }}"
        )
        self.assertEqual(rebuild["steps"][0]["with"]["ref"], "refs/tags/${{ matrix.tag }}")
        # The tag's checkout brings the tag's own setup action: its pins, Python and lock.
        self.assertEqual(rebuild["steps"][1]["uses"], SETUP)
        self.assertFalse(rebuild["strategy"]["fail-fast"])


if __name__ == "__main__":
    unittest.main()
