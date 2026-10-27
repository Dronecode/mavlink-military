#!/usr/bin/env python3
"""Check the repository settings that a publication relies on, and fail closed.

Usage: release_settings.py

Run by the preflight job of a run that may publish. For GITHUB_REPOSITORY,
read-only through gh_api, it requires:

- the rules on main: a pull request with at least one approval, no force
  push and no deletion, from active rulesets;
- a tag ruleset on every tag (~ALL, with nothing excluded): active,
  restricting creation, update and deletion, so only those it lets bypass,
  the repository's administrators, can push a release tag;
- for each of those rulesets, current_user_can_bypass is never: this run's
  own token cannot get around them. Where the run can read a ruleset's bypass
  list (GitHub shows it only to those who can edit the ruleset), it may name
  the repository admin role and organisation administrators, and nothing
  else;
- the repository's configuration variables, as the run sees them (VARS_JSON,
  toJSON(vars)), are empty: the provenance generator publishes them.

It prints rule types and booleans and exits 1 on any shortfall or failed read.
"""

from __future__ import annotations

import json
import os
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import gh_api  # noqa: E402

MAIN_RULES = {"pull_request", "non_fast_forward", "deletion"}
TAG_RULES = {"creation", "update", "deletion"}
# The repository admin role (actor_id 5) and organisation administrators.
ADMIN_BYPASS = {("RepositoryRole", 5), ("OrganizationAdmin", 1)}


def bypass_findings(repo: str, ids: set[int], what: str) -> list[str]:
    findings = []
    for ruleset_id in sorted(ids):
        ruleset = gh_api.api(f"repos/{repo}/rulesets/{ruleset_id}?includes_parents=true")
        if ruleset.get("current_user_can_bypass") != "never":
            findings.append(
                f"{what} ruleset {ruleset_id}: this run's token can bypass it ({ruleset.get('current_user_can_bypass')})"
            )
        actors = {
            (actor.get("actor_type"), actor.get("actor_id"))
            for actor in ruleset.get("bypass_actors") or []
        }
        if actors - ADMIN_BYPASS:
            findings.append(
                f"{what} ruleset {ruleset_id}: its bypass list names more than the administrators"
            )
    return findings


def main_findings(repo: str) -> list[str]:
    rules = gh_api.api(f"repos/{repo}/rules/branches/main?per_page=100") or []
    found = {r["type"] for r in rules}
    findings = [f"main: no active rule {t}" for t in sorted(MAIN_RULES - found)]
    approvals = [
        (r.get("parameters") or {}).get("required_approving_review_count", 0) for r in rules if r["type"] == "pull_request"
    ]  # fmt: skip
    if approvals and max(approvals) < 1:
        findings.append("main: a pull request needs no approval")
    ids = {r["ruleset_id"] for r in rules if r["type"] in MAIN_RULES and "ruleset_id" in r}
    return findings + bypass_findings(repo, ids, "main")


def tag_findings(repo: str) -> list[str]:
    for summary in gh_api.api(f"repos/{repo}/rulesets?includes_parents=true&per_page=100") or []:
        if summary.get("target") != "tag" or summary.get("enforcement") != "active":
            continue
        ruleset = gh_api.api(f"repos/{repo}/rulesets/{summary['id']}?includes_parents=true")
        names = (ruleset.get("conditions") or {}).get("ref_name", {})
        rules = {rule.get("type") for rule in ruleset.get("rules", [])}
        # An exclusion would leave the tags it names, the release tags among
        # them perhaps, outside the ruleset.
        if "~ALL" in names.get("include", []) and not names.get("exclude") and TAG_RULES <= rules:
            return bypass_findings(repo, {summary["id"]}, "tag")
    return [
        f"no active tag ruleset covers every tag (~ALL) with nothing excluded and the rules {sorted(TAG_RULES)}"
    ]


def vars_findings(text: str | None) -> list[str]:
    try:
        variables = json.loads(text or "null")
    except json.JSONDecodeError:
        variables = None
    if variables != {}:
        names = sorted(variables) if isinstance(variables, dict) else "unreadable"
        return [f"configuration variables are set ({names}); the provenance would publish them"]
    return []


def check(env: dict) -> list[str]:
    repo = env["GITHUB_REPOSITORY"]
    return vars_findings(env.get("VARS_JSON")) + main_findings(repo) + tag_findings(repo)


def main(argv: list[str]) -> int:
    if len(argv) != 1:
        print(__doc__, file=sys.stderr)
        return 2
    try:
        findings = check(dict(os.environ))
    except gh_api.GitHubError as error:
        findings = [f"could not read the settings: {error}"]
    for finding in findings:
        print(f"::error title=release settings::{finding}")
    if findings:
        print(
            f"{len(findings)} release setting(s) fall short; nothing is published", file=sys.stderr
        )
        return 1
    print("the rulesets on main and on every tag, and the variables hold")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
