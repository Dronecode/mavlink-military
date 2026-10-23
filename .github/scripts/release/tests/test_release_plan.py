#!/usr/bin/env python3
"""Tests for release_plan.py, in temporary git repositories, with a stand-in gh
and stand-ins for the two wire-report scripts. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_release_plan.py'
"""

from __future__ import annotations

import contextlib
import hashlib
import io
import json
import os
import runpy
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
sys.path.insert(0, str(HERE))
import gh_api  # noqa: E402
import release_plan as rp  # noqa: E402
from fake_gh import FakeGh  # noqa: E402
from release_plan import Release, Version  # noqa: E402

MAVPIN, PYMPIN = "a" * 40, "b" * 40
REPO = "Dronecode/mavlink-military"
# The setup action's two checkouts, as the plan reads them; example/one stands for
# pymavlink's repository.
ACTION = """runs:
  using: composite
  steps:
    - uses: actions/checkout@0000000000000000000000000000000000000000
      with:
        repository: mavlink/mavlink
        path: mavlink
    - uses: actions/checkout@0000000000000000000000000000000000000000
      with:
        repository: example/one
        path: pymavlink
"""
CLEAN = (
    "0 wire-breaking change(s), 0 extension-only change(s), 0 addition(s), 2 message(s) untouched"
)


def dialect(
    messages: dict[int, str] | None = None,
    commands: dict[int, str] | None = None,
    version: str = "3",
    number: str = "0",
) -> str:
    msgs = "".join(
        f'<message id="{i}" name="{n}"><description>d</description></message>'
        for i, n in (messages or {53000: "ONE"}).items()
    )
    cmds = "".join(f'<entry value="{v}" name="{n}"/>' for v, n in (commands or {}).items())
    return (
        f'<?xml version="1.0"?>\n<mavlink><include>common.xml</include><version>{version}</version><dialect>{number}</dialect>'
        f'<enums><enum name="OTHER"/><enum name="MAV_CMD">{cmds}</enum></enums><messages>{msgs}</messages></mavlink>\n'
    )


class Reports:
    """Stand-in for runs of check_wire_compat.py and check_api_break.py."""

    def __init__(self) -> None:
        self.wire = [(0, CLEAN + "\n", "")]
        self.api = (0, "No XML files changed.\n", "")
        self.calls: list[list[str]] = []

    def __call__(self, command: list[str], env: dict[str, str]):
        self.calls.append(command)
        self.env = env
        if command[1].endswith("check_wire_compat.py"):
            code, out, err = self.wire[0] if len(self.wire) == 1 else self.wire.pop(0)
        else:
            code, out, err = self.api
        return subprocess.CompletedProcess(command, code, out, err)


class PlanTestCase(unittest.TestCase):
    """A temporary repository on main, generator checkouts, a stand-in gh."""

    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)
        self.repo = self.tmp / "repo"
        self.out = self.tmp / "out"
        self.output = self.tmp / "github_output"
        self.repo.mkdir()
        self.git("init", "-q", "--initial-branch=main")
        (self.repo / ".github").mkdir()
        self.action = self.repo / ".github" / "actions" / "setup-mavlink-tooling" / "action.yml"
        self.action.parent.mkdir(parents=True)
        self.action.write_text(ACTION, encoding="utf-8")
        self.pins(MAVPIN, PYMPIN)
        self.commit("chore(repo): start the dialect", dialect())
        self.mavlink = self.tmp / "mavlink"
        (self.mavlink / "message_definitions" / "v1.0").mkdir(parents=True)
        for name in rp.UPSTREAM_DEFINITIONS:
            (self.mavlink / "message_definitions" / "v1.0" / f"{name}.xml").write_text(f"<{name}/>")
        self.pymavlink = self.tmp / "pymavlink"
        (self.pymavlink / "generator" / "C" / "include_v2.0").mkdir(parents=True)
        (self.pymavlink / "__init__.py").write_text("__version__ = '2.4.50'\n")
        for name in rp.FIXED_HEADERS:
            (self.pymavlink / "generator" / "C" / "include_v2.0" / name).write_text(f"// {name}\n")
        self.gh = FakeGh(self.tmp)
        self.reports = Reports()
        self.releases: list[dict] = []
        self.answer_pins(MAVPIN, PYMPIN)

    def git(self, *args: str) -> str:
        command = ["git", "-c", "user.name=Test", "-c", "user.email=test@example.org", *args]
        return subprocess.run(
            command, cwd=self.repo, check=True, capture_output=True, text=True
        ).stdout.strip()

    def pins(self, mavlink: str, pymavlink: str) -> None:
        (self.repo / ".github" / "mavlink-pins.env").write_text(
            f"# pins\nMAVLINK_REF={mavlink}\nPYMAVLINK_REF={pymavlink}\n", encoding="utf-8"
        )

    def commit(self, message: str, xml: str | None = None) -> str:
        if xml is not None:
            (self.repo / "military.xml").write_text(xml, encoding="utf-8")
        self.git("add", "--all")
        self.git("commit", "-q", "--allow-empty", "-m", message)
        self.git("update-ref", "refs/remotes/origin/main", "HEAD")
        return self.git("rev-parse", "HEAD")

    def tag(self, name: str, message: str | None = "release", commit: str = "HEAD") -> None:
        if message is None:
            self.git("tag", name, commit)
        else:
            self.git("tag", "-a", name, "-m", message, commit)

    def answer_pins(
        self, mavlink: str, pymavlink: str, status: str = "ahead", gitlink: str | None = None
    ) -> None:
        self.gh.on(
            "api", f"repos/mavlink/mavlink/compare/{mavlink}...master", stdout={"status": status}
        )
        self.gh.on(
            "api",
            f"repos/example/one/compare/{pymavlink}...master",
            stdout={"status": "identical"},
        )
        self.gh.on(
            "api",
            f"repos/mavlink/mavlink/contents/pymavlink?ref={mavlink}",
            stdout={"sha": gitlink or pymavlink},
        )
        self.gh.on(
            "api",
            f"repos/example/one/compare/v2.4.50...{pymavlink}",
            stdout={"ahead_by": 17, "behind_by": 0},
        )

    def publish(
        self, tag: str, draft: bool = False, prerelease: bool = False, xml: bytes | None = None
    ) -> None:
        """A release on GitHub, with its military.xml asset and SHA256SUMS."""
        self.releases.append({"tag_name": tag, "draft": draft, "prerelease": prerelease})
        data = xml if xml is not None else self.git_bytes(f"{tag}:military.xml")
        name = f"mavlink-m-{tag[1:]}-military.xml"
        sums = f"{hashlib.sha256(data).hexdigest()}  {name}\n"
        self.gh.on("release", "download", tag, "--repo", REPO, "--dir", prefix=True,
                   files={"SHA256SUMS": sums, name: data})  # fmt: skip

    def git_bytes(self, spec: str) -> bytes:
        return subprocess.run(
            ["git", "show", spec], cwd=self.repo, check=True, capture_output=True
        ).stdout

    def env(self, event: str = "pull_request", tag: str = "", repo: str = REPO) -> dict[str, str]:
        env = {"GITHUB_REPOSITORY": repo, "GITHUB_EVENT_NAME": event, "GITHUB_OUTPUT": str(self.output),
               "MAVLINK_DIR": str(self.mavlink), "PYMAVLINK_DIR": str(self.pymavlink), **self.gh.env()}  # fmt: skip
        if tag:
            env.update(GITHUB_REF=f"refs/tags/{tag}", GITHUB_REF_NAME=tag, GITHUB_REF_TYPE="tag")
        else:
            env.update(
                GITHUB_REF="refs/pull/7/merge", GITHUB_REF_NAME="7/merge", GITHUB_REF_TYPE="branch"
            )
        return env

    def plan(
        self,
        event: str = "pull_request",
        tag: str = "",
        repo: str = REPO,
        argv: list[str] | None = None,
    ):
        """Run release_plan.main in the repository; (status, stdout, stderr)."""
        self.gh.on("api", f"repos/{repo}/releases?per_page=100&page=1", stdout=self.releases)
        out, err = io.StringIO(), io.StringIO()
        cwd = os.getcwd()
        os.chdir(self.repo)
        try:
            with mock.patch.dict(os.environ, self.env(event, tag, repo)), mock.patch.object(
                rp, "run_report", self.reports
            ):
                os.environ.pop("RELEASE_MAIN", None)
                os.environ.pop("RELEASE_UPSTREAM", None)
                with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
                    status = rp.main(argv or ["release_plan.py", str(self.out)])
        finally:
            os.chdir(cwd)
        self.gh.responses.pop()  # the releases listing, answered afresh each run
        self.gh.save()
        return status, out.getvalue(), err.getvalue()

    def result(self) -> dict:
        return json.loads((self.out / "plan.json").read_text(encoding="utf-8"))

    def assert_breach(self, status: int, out: str, text: str) -> None:
        self.assertEqual(status, 1)
        self.assertIn("::error title=release plan::", out)
        self.assertIn(text, out)
        self.assertFalse((self.out / "plan.json").exists())


class FirstReleaseTest(PlanTestCase):
    def test_a_rehearsal_before_any_release_plans_0_0_0(self) -> None:
        status, out, _ = self.plan()
        self.assertEqual(status, 0, out)
        self.assertIn("v0.0.0 (rehearsal), previous release none, publish False", out)
        plan = self.result()
        self.assertEqual(
            (plan["mode"], plan["version"], plan["previous"], plan["publish"]),
            ("rehearsal", "0.0.0", None, False),
        )
        self.assertEqual(plan["pins"], {"mavlink": MAVPIN, "pymavlink": PYMPIN})
        self.assertEqual(
            plan["generator"],
            {
                "repository": "example/one",
                "commit": PYMPIN,
                "reports_version": "2.4.50",
                "release_tag": "v2.4.50",
                "ahead_by": 17,
                "behind_by": 0,
            },
        )
        self.assertEqual(
            plan["dialect"],
            {"version": "3", "dialect": "0", "previous": None, "previous_dialect": None},
        )
        self.assertEqual(plan["commit"], self.git("rev-parse", "HEAD"))
        self.assertEqual(plan["tree"], self.git("rev-parse", "HEAD^{tree}"))
        self.assertEqual(plan["source_date_epoch"], int(self.git("log", "-1", "--format=%ct")))
        self.assertEqual(
            [c["subject"] for c in plan["changes"]], ["chore(repo): start the dialect"]
        )
        self.assertEqual(
            self.output.read_text(),
            f"tag=v0.0.0\nversion=0.0.0\ncommit={plan['commit']}\nprevious=none\npublish=false\n",
        )
        self.assertEqual(self.reports.calls, [])

    def test_a_first_release_may_take_any_version(self) -> None:
        self.tag("v2.5.0", "first release\n\nDecision: https://example.org/decisions/1")
        status, out, _ = self.plan(event="push", tag="v2.5.0")
        self.assertEqual(status, 0, out)
        plan = self.result()
        self.assertEqual(
            (plan["mode"], plan["version"], plan["publish"]), ("release", "2.5.0", True)
        )
        self.assertEqual(plan["decision"], "https://example.org/decisions/1")

    def test_a_tag_outside_dronecode_never_publishes(self) -> None:
        self.tag("v1.0.0")
        status, _, _ = self.plan(event="push", tag="v1.0.0", repo="fork/mavlink-military")
        self.assertEqual((status, self.result()["publish"]), (0, False))

    def test_subjects_outside_the_convention_warn(self) -> None:
        self.commit("Update military.xml")
        self.commit('Revert "chore(repo): start the dialect"')
        status, out, _ = self.plan()
        self.assertEqual(status, 0)
        self.assertIn("subject not in type(scope): form", out)
        self.assertEqual(out.count("subject not in type(scope): form"), 1)

    def test_trailers_are_recorded(self) -> None:
        self.commit(
            "feat(dialect)!: change a message\n\nWhy.\n\nAssisted-by: Tool:model-1\nSigned-off-by: A <a@example.org>"
        )
        _, _, _ = self.plan()
        change = self.result()["changes"][-1]
        self.assertEqual(
            (change["kind"], change["change"], change["signed_off"], change["assisted_by"]),
            ("feat", "breaking", True, ["Tool:model-1"]),
        )
        # Only the subject, the classification and the trailers' facts are kept: no body,
        # so no name or address in it reaches a published asset.
        self.assertEqual(
            sorted(change), ["assisted_by", "change", "commit", "kind", "signed_off", "subject"]
        )
        self.assertNotIn("a@example.org", json.dumps(self.result()))

    def test_only_ascii_digits_make_a_release_tag(self) -> None:
        self.assertIsNone(Version.parse("v\uff11.0.0"))  # a full-width digit one
        self.assertIsNone(Version.parse("v1.0.\u0660"))  # an Arabic-Indic digit zero
        self.assertEqual(Version.parse("v10.0.1"), Version(10, 0, 1))


class ReleaseChecksTest(PlanTestCase):
    def test_a_tag_that_is_no_release_tag_is_refused(self) -> None:
        for tag in ("v1.0", "v01.0.0", "1.0.0", "v1.0.0-rc.1"):
            with self.subTest(tag=tag):
                self.tag(tag)
                status, out, _ = self.plan(event="push", tag=tag)
                self.assert_breach(status, out, f"'{tag}' is no release tag of the form vX.Y.Z")

    def test_a_tag_seen_by_a_rehearsal_must_be_a_release_tag(self) -> None:
        self.tag("v1.0")
        status, out, _ = self.plan(event="workflow_dispatch", tag="v1.0")
        self.assert_breach(status, out, "'v1.0' is no release tag of the form vX.Y.Z")

    def test_a_shallow_checkout_is_refused(self) -> None:
        self.tag("v1.0.0")
        with mock.patch.object(
            rp,
            "git",
            side_effect=lambda *a: (
                "true\n" if a == ("rev-parse", "--is-shallow-repository") else real_git(*a)
            ),
        ):
            status, out, _ = self.plan(event="push", tag="v1.0.0")
        self.assert_breach(status, out, "the checkout is shallow")

    def test_a_lightweight_tag_is_refused(self) -> None:
        self.tag("v1.0.0", message=None)
        status, out, _ = self.plan(event="push", tag="v1.0.0")
        self.assert_breach(status, out, "v1.0.0 is a lightweight tag")

    def test_a_tag_on_another_commit_is_refused(self) -> None:
        self.tag("v1.0.0")
        self.commit("fix(repo): later")
        status, out, _ = self.plan(event="push", tag="v1.0.0")
        self.assert_breach(status, out, "v1.0.0 does not name the checked-out commit")

    def test_a_tag_off_main_is_refused(self) -> None:
        first = self.git("rev-parse", "HEAD")
        self.git("checkout", "-q", "-b", "side")
        self.commit("fix(repo): on a side branch")
        self.git("update-ref", "refs/remotes/origin/main", first)
        self.tag("v1.0.0")
        status, out, _ = self.plan(event="push", tag="v1.0.0")
        self.assert_breach(
            status, out, "v1.0.0 is not on origin/main; releases come from main only"
        )

    def test_a_git_failure_is_an_annotation(self) -> None:
        error = subprocess.CalledProcessError(128, ["git", "show"], stderr="fatal: bad object\n")
        with mock.patch.object(rp, "pins", side_effect=error):
            status, out, _ = self.plan()
        self.assert_breach(status, out, "git show: fatal: bad object")

    def test_a_github_failure_is_an_annotation(self) -> None:
        self.gh.responses.clear()
        self.gh.save()
        status, out, _ = self.plan()
        self.assert_breach(status, out, "fake gh: no response")

    def test_usage(self) -> None:
        status, _, err = self.plan(argv=["release_plan.py"])
        self.assertEqual(status, 2)
        self.assertIn("Usage: release_plan.py <out>", err)


def real_git(*args: str) -> str:
    return subprocess.run(["git", *args], check=True, capture_output=True, text=True).stdout


class LaterReleaseTest(PlanTestCase):
    def setUp(self) -> None:
        super().setUp()
        self.first = self.git("rev-parse", "HEAD")
        self.tag("v1.0.0")
        self.publish("v1.0.0")

    def test_the_next_rehearsal_follows_the_previous_release(self) -> None:
        self.commit("fix(dialect): describe a field")
        status, out, _ = self.plan()
        self.assertEqual(status, 0, out)
        plan = self.result()
        self.assertEqual(
            (plan["version"], plan["previous"]["tag"], plan["policy"]["required"]),
            ("1.0.1", "v1.0.0", "patch"),
        )
        self.assertEqual(plan["wire"]["verdict"], CLEAN)
        self.assertEqual(plan["wire"]["api_breaks"], [])
        self.assertEqual(plan["dialect"]["previous"], "3")
        self.assertIsNone(plan["closure"])
        self.assertIsNone(plan["generator_change"])
        self.assertIn("previous release v1.0.0", out)
        self.assertNotIn("PYTHONHASHSEED", self.reports.env)
        self.assertNotIn("GITHUB_STEP_SUMMARY", self.reports.env)

    def test_a_changed_dialect_version_is_an_addition(self) -> None:
        # military.xml's <version> sets the C MAVLINK_VERSION constant; <dialect> changes nothing.
        self.commit("fix(dialect): renumber the dialect", dialect(version="4", number="7"))
        status, out, _ = self.plan()
        self.assertEqual(status, 0, out)
        plan = self.result()
        self.assertEqual(
            plan["dialect"],
            {"version": "4", "dialect": "7", "previous": "3", "previous_dialect": "0"},
        )
        self.assertEqual((plan["version"], plan["policy"]["required"]), ("1.1.0", "minor"))

    def test_a_feature_calls_for_a_minor_bump(self) -> None:
        self.commit("feat(dialect): add a message", dialect({53000: "ONE", 53001: "TWO"}))
        self.reports.wire = [(0, "INFO: message 53001 TWO added (entry x)\nverdict\n", "")]
        self.plan()
        self.assertEqual(
            (self.result()["version"], self.result()["policy"]["required"]), ("1.1.0", "minor")
        )

    def test_a_patch_tag_below_a_required_minor_is_refused(self) -> None:
        self.commit("feat(dialect): add a message")
        self.tag("v1.0.1")
        status, out, _ = self.plan(event="push", tag="v1.0.1")
        self.assert_breach(
            status,
            out,
            "the changes since v1.0.0 call for a minor bump, but v1.0.1 is a patch bump",
        )

    def test_a_rehearsal_reports_breaches_as_warnings(self) -> None:
        self.commit("feat(dialect): add a message")
        self.tag("v1.0.1")
        status, out, _ = self.plan(event="workflow_dispatch", tag="v1.0.1")
        self.assertEqual(status, 0)
        self.assertIn(
            "::warning title=release plan::the changes since v1.0.0 call for a minor bump", out
        )
        self.assertEqual(
            self.result()["policy"]["breaches"],
            ["the changes since v1.0.0 call for a minor bump, but v1.0.1 is a patch bump"],
        )

    def test_a_tag_that_skips_a_version_is_refused(self) -> None:
        self.commit("fix(dialect): describe a field")
        self.tag("v1.0.2")
        status, out, _ = self.plan(event="push", tag="v1.0.2")
        self.assert_breach(
            status,
            out,
            "v1.0.2 does not follow v1.0.0: the next versions are v1.0.1, v1.1.0, v2.0.0",
        )

    def test_a_breaking_change_calls_for_a_major_bump_from_1_0(self) -> None:
        self.commit("fix(dialect)!: retype a field")
        self.reports.wire = [
            (
                0,
                "::warning title=wire-format change::BREAKING: message 53000 ONE: field retyped\nverdict\n",
                "",
            )
        ]
        self.plan()
        plan = self.result()
        self.assertEqual(
            (plan["version"], plan["wire"]["breaking"]),
            ("2.0.0", ["BREAKING: message 53000 ONE: field retyped"]),
        )
        self.assertEqual(plan["policy"]["mismatches"], [])

    def test_a_wire_break_without_a_marked_commit_is_a_mismatch(self) -> None:
        self.commit("fix(dialect): retype a field")
        self.reports.wire = [(0, "BREAKING: message 53000 ONE: field retyped\nverdict\n", "")]
        self.plan()
        self.assertEqual(
            self.result()["policy"]["mismatches"],
            ["the wire reports show breaking changes that no commit marks with !"],
        )

    def test_a_marked_commit_without_a_wire_break_is_a_mismatch(self) -> None:
        self.commit("fix(dialect)!: change a meaning")
        self.plan()
        self.assertEqual(
            self.result()["policy"]["mismatches"],
            ["commits marked with ! change no wire row: each declares a change of meaning"],
        )

    def test_an_api_break_is_breaking(self) -> None:
        self.commit("fix(dialect): rename an enum value")
        self.reports.api = (
            1,
            "Name removals/changes detected in military_extensions.xml:\n - X\nName removals/changes detected in military.xml:\n - MAV_X renamed\nSummary\n",
            "",
        )
        self.plan()
        plan = self.result()
        self.assertEqual(
            (plan["wire"]["api_breaks"], plan["version"]), (["MAV_X renamed"], "2.0.0")
        )
        self.assertEqual(self.reports.calls[-1][-2:], ["--base", "v1.0.0"])

    def test_an_api_checker_without_a_verdict_fails(self) -> None:
        self.commit("fix(dialect): change")
        for api in ((1, "Traceback\n", ""), (2, "", "usage\n")):
            with self.subTest(code=api[0]):
                self.reports.api = api
                status, out, _ = self.plan()
                self.assert_breach(
                    status, out, f"check_api_break.py exited {api[0]} without a verdict"
                )

    def test_a_wire_report_failure_fails(self) -> None:
        self.commit("fix(dialect): change")
        self.reports.wire = [(1, "", "Traceback\n")]
        status, out, _ = self.plan()
        self.assert_breach(status, out, "check_wire_compat.py exited 1: Traceback")

    def test_an_id_given_another_name_is_breaking(self) -> None:
        self.commit("fix(dialect): rename", dialect({53000: "RENAMED"}, {45000: "MAV_CMD_B"}))
        self.plan()
        self.assertEqual(self.result()["id_reuse"], ["message 53000 was ONE in v1.0.0, is RENAMED"])
        self.assertEqual(self.result()["version"], "2.0.0")

    def test_release_assets_that_disagree_are_refused(self) -> None:
        self.releases.clear()
        self.gh.responses = [
            r for r in self.gh.responses if r["args"][:2] != ["release", "download"]
        ]
        self.publish("v1.0.0", xml=b"<other/>")
        self.commit("fix(dialect): describe")
        status, out, _ = self.plan()
        self.assert_breach(
            status, out, "v1.0.0: its military.xml asset does not match its SHA256SUMS and tag"
        )

    def test_drafts_pre_releases_and_other_tags_are_not_releases(self) -> None:
        self.releases += [
            {"tag_name": "v9.0.0", "draft": True, "prerelease": False},
            {"tag_name": "v8.0.0", "draft": False, "prerelease": True},
            {"tag_name": "nightly", "draft": False, "prerelease": False},
        ]
        self.commit("fix(dialect): describe")
        self.plan()
        self.assertEqual(self.result()["version"], "1.0.1")

    def test_a_published_release_whose_tag_is_missing_fails(self) -> None:
        self.releases.append({"tag_name": "v1.5.0", "draft": False, "prerelease": False})
        status, out, _ = self.plan()
        self.assert_breach(
            status, out, "release v1.5.0 is published but its tag is not in this checkout"
        )

    def test_more_than_a_page_of_releases_is_read(self) -> None:
        page = [{"tag_name": f"x{i}", "draft": False, "prerelease": False} for i in range(100)]
        self.gh.on("api", f"repos/{REPO}/releases?per_page=100&page=2", stdout=self.releases)
        self.releases = page
        self.commit("fix(dialect): describe")
        status, out, _ = self.plan()
        self.assertEqual(status, 0, out)
        self.assertEqual(self.result()["previous"]["tag"], "v1.0.0")

    def test_the_version_is_not_released_twice_or_lowered(self) -> None:
        self.commit("fix(dialect): describe")
        self.tag("v1.0.1")
        self.publish("v1.0.1")
        self.commit("fix(dialect): again")
        self.tag("v1.0.0b", message="x")
        breaches = rp.check_policy(Version(1, 0, 1), Release(Version(1, 0, 0), self.first), "patch",
                                   [Release(Version(1, 0, 0), self.first), Release(Version(1, 0, 1), "c")], "h")  # fmt: skip
        self.assertEqual(breaches, ["v1.0.1 is released already"])
        breaches = rp.check_policy(Version(1, 0, 1), Release(Version(1, 0, 0), self.first), None,
                                   [Release(Version(1, 0, 2), "c")], self.first)  # fmt: skip
        self.assertEqual(
            breaches,
            ["v1.0.1 is not above the highest release, v1.0.2", "nothing changed since v1.0.0"],
        )

    def test_moved_pins_are_reported(self) -> None:
        new_mav, new_pym = "c" * 40, "d" * 40
        self.pins(new_mav, new_pym)
        self.commit("chore(repo): bump the generator pins")
        self.answer_pins(new_mav, new_pym)
        for name in rp.UPSTREAM_DEFINITIONS:
            self.gh.on("api", "-H", "Accept: application/vnd.github.raw",
                       f"repos/mavlink/mavlink/contents/message_definitions/v1.0/{name}.xml?ref={MAVPIN}", stdout=f"<{name} old/>")  # fmt: skip
        for name in rp.FIXED_HEADERS:
            old = f"// {name}\n" if name != "protocol.h" else "// older\n"
            self.gh.on("api", "-H", "Accept: application/vnd.github.raw",
                       f"repos/example/one/contents/generator/C/include_v2.0/{name}?ref={PYMPIN}", stdout=old)  # fmt: skip
        self.gh.on("api", f"repos/example/one/compare/{PYMPIN}...{new_pym}",
                   stdout={"commits": [{"commit": {"message": "Change the protocol header\n\nbody"}}]})  # fmt: skip
        self.reports.wire = [(0, CLEAN + "\n", "")] * 1 + [
            (0, "BREAKING: message 1 X: retyped\nv\n", ""), (0, "INFO: message 2 Y added\nv\n", ""), (0, "v\n", ""),
        ]  # fmt: skip
        status, out, _ = self.plan()
        self.assertEqual(status, 0, out)
        plan = self.result()
        self.assertEqual(
            plan["closure"]["breaking"], ["common.xml: BREAKING: message 1 X: retyped"]
        )
        self.assertEqual(plan["closure"]["info"], ["standard.xml: INFO: message 2 Y added"])
        self.assertEqual(plan["generator_change"]["fixed_headers_changed"], ["protocol.h"])
        self.assertEqual(plan["generator_change"]["commits"], ["Change the protocol header"])
        self.assertEqual(plan["version"], "2.0.0")
        self.assertEqual(
            plan["policy"]["mismatches"],
            ["the wire reports show breaking changes that no commit marks with !"],
        )


class PinTest(PlanTestCase):
    def test_a_pin_off_its_upstream_branch_fails(self) -> None:
        self.gh.responses.clear()
        self.answer_pins(MAVPIN, PYMPIN, status="diverged")
        status, out, _ = self.plan()
        self.assert_breach(status, out, f"mavlink/mavlink pin {MAVPIN} is not on master (diverged)")

    def test_a_generator_pin_other_than_mavlinks_submodule_is_a_note(self) -> None:
        self.gh.responses.clear()
        self.answer_pins(MAVPIN, PYMPIN, gitlink="e" * 40)
        status, out, _ = self.plan()
        self.assertEqual(status, 0)
        self.assertIn(
            f"PYMAVLINK_REF differs from mavlink's pymavlink submodule at MAVLINK_REF ({'e' * 40})",
            out,
        )

    def test_a_pins_file_without_both_pins_fails(self) -> None:
        (self.repo / ".github" / "mavlink-pins.env").write_text("MAVLINK_REF=short\n")
        self.commit("chore(repo): break the pins")
        status, out, _ = self.plan()
        self.assert_breach(
            status, out, ".github/mavlink-pins.env lacks a full MAVLINK_REF or PYMAVLINK_REF"
        )

    def test_a_generator_without_a_version_string(self) -> None:
        (self.pymavlink / "__init__.py").write_text("# no version\n")
        status, _, _ = self.plan()
        self.assertEqual(status, 0)
        self.assertEqual(
            self.result()["generator"],
            {"repository": "example/one", "commit": PYMPIN, "reports_version": None},
        )

    def test_the_generator_repository_comes_from_the_setup_action(self) -> None:
        # The plan asks GitHub about the repository the action names, and only
        # an action that names it once, as owner/name, gives one.
        status, out, _ = self.plan()
        self.assertEqual(status, 0, out)
        self.assertEqual(self.result()["generator"]["repository"], "example/one")
        self.action.write_text(ACTION.replace("example/one", "example/one/two"), encoding="utf-8")
        status, out, _ = self.plan()
        self.assert_breach(status, out, "the generator's repository: ")
        self.assertIn("must name its repository: once, as owner/name", out)
        self.action.unlink()
        status, out, _ = self.plan()
        self.assert_breach(status, out, "the generator's repository: ")
        self.assertIn("No such file or directory", out)


class UnitTest(unittest.TestCase):
    def test_versions(self) -> None:
        self.assertEqual(Version.parse("v1.2.3"), Version(1, 2, 3))
        self.assertIsNone(Version.parse("v1.2.3-rc.1"))
        self.assertEqual((str(Version(1, 2, 3)), Version(1, 2, 3).tag), ("1.2.3", "v1.2.3"))
        self.assertEqual(
            rp.successors(Version(0, 4, 1)),
            {"patch": Version(0, 4, 2), "minor": Version(0, 5, 0), "major": Version(1, 0, 0)},
        )

    def test_levels_before_and_after_1_0(self) -> None:
        self.assertEqual(
            [rp.level_for(c, Version(0, 3, 0)) for c in ("breaking", "addition", "other")],
            ["minor", "patch", "patch"],
        )
        self.assertEqual(
            [rp.level_for(c, Version(1, 0, 0)) for c in ("breaking", "addition", "other")],
            ["major", "minor", "patch"],
        )

    def test_publishing_needs_dronecode_a_push_and_a_release_tag(self) -> None:
        base = {
            "GITHUB_REPOSITORY": REPO,
            "GITHUB_EVENT_NAME": "push",
            "GITHUB_REF_TYPE": "tag",
            "GITHUB_REF": "refs/tags/v1.0.0",
        }
        self.assertTrue(rp.publishing(base))
        for change in ({"GITHUB_REPOSITORY": "fork/m"}, {"GITHUB_EVENT_NAME": "workflow_dispatch"},
                       {"GITHUB_REF_TYPE": "branch"}, {"GITHUB_REF": "refs/heads/v1.0.0"}, {"GITHUB_REF": "refs/tags/v1.0"}):  # fmt: skip
            with self.subTest(change=change):
                self.assertFalse(rp.publishing({**base, **change}))
        self.assertTrue(
            rp.publishing({**base, "GITHUB_REPOSITORY": "fork/m", "RELEASE_UPSTREAM": "fork/m"})
        )

    def test_classes(self) -> None:
        none = rp.classes_of([], None, None, None, [])
        self.assertEqual(none, set())
        wire = {"breaking": [], "api_breaks": [], "info": ["INFO"]}
        self.assertEqual(rp.classes_of([], wire, None, None, []), {"addition"})
        closure = {"breaking": [], "info": []}
        self.assertEqual(rp.classes_of([], None, closure, {"fixed_headers_changed": []}, []), set())
        self.assertEqual(rp.classes_of([], None, None, None, ["reused"]), {"breaking"})
        same = {"version": "3", "previous": "3"}
        self.assertEqual(rp.classes_of([], None, None, None, [], same), set())
        first = {"version": "3", "previous": None}
        self.assertEqual(rp.classes_of([], None, None, None, [], first), set())
        moved = {"version": "4", "previous": "3"}
        self.assertEqual(rp.classes_of([], None, None, None, [], moved), {"addition"})

    def test_api_breaks_counts_military_xml_only(self) -> None:
        text = ("Name removals/changes detected in military.xml:\n - A\n - B\nother line\n - C\n"
                "Name removals/changes detected in common.xml:\n - D\n")  # fmt: skip
        self.assertEqual(rp.api_breaks(text), ["A", "B"])

    def test_report_env_drops_what_makes_reports_post(self) -> None:
        with mock.patch.dict(
            os.environ, {"GITHUB_STEP_SUMMARY": "x", "WIRE_COMPAT_ENFORCE": "1", "KEEP": "y"}
        ):
            env = rp.report_env()
        self.assertNotIn("GITHUB_STEP_SUMMARY", env)
        self.assertNotIn("WIRE_COMPAT_ENFORCE", env)
        self.assertEqual(env["KEEP"], "y")

    def test_run_report_runs_the_command(self) -> None:
        result = rp.run_report([sys.executable, "-c", "print('ok')"], dict(os.environ))
        self.assertEqual((result.returncode, result.stdout), (0, "ok\n"))

    def test_a_plan_without_github_output_prints_only(self) -> None:
        result = {"warnings": [], "pin_notes": [], "policy": {"mismatches": []}, "previous": None,
                  "tag": "v0.0.0", "mode": "rehearsal", "publish": False}  # fmt: skip
        with tempfile.TemporaryDirectory() as out, mock.patch.object(
            rp, "plan", return_value=result
        ), mock.patch.dict(os.environ):
            os.environ.pop("GITHUB_OUTPUT", None)
            stdout = io.StringIO()
            with contextlib.redirect_stdout(stdout):
                self.assertEqual(rp.main(["release_plan.py", out]), 0)
        self.assertEqual(
            stdout.getvalue(), "v0.0.0 (rehearsal), previous release none, publish False\n"
        )

    def test_runs_as_a_script(self) -> None:
        with mock.patch.object(sys, "argv", ["release_plan.py"]), contextlib.redirect_stderr(
            io.StringIO()
        ):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(rp.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)

    def test_gh_errors_reach_main(self) -> None:
        with tempfile.TemporaryDirectory() as out, mock.patch.object(
            rp, "plan", side_effect=gh_api.GitHubError("down")
        ):
            stdout = io.StringIO()
            with contextlib.redirect_stdout(stdout):
                self.assertEqual(rp.main(["release_plan.py", out]), 1)
        self.assertEqual(stdout.getvalue(), "::error title=release plan::down\n")


if __name__ == "__main__":
    unittest.main()
