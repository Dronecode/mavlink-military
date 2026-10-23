#!/usr/bin/env python3
"""Check the repository settings that a publication relies on, and fail closed.

Usage: release_settings.py

Run by the preflight job of a run that may publish. For GITHUB_REPOSITORY,
read-only through gh_api, it requires:

- the release environment (RELEASE_ENVIRONMENT, default release): it exists,
  administrators cannot bypass it, a required-reviewers rule names at least one
  reviewer and prevents self-review, and deployments are allowed only from tags
  that match v* (a custom policy of that one tag entry). GitHub creates an
  environment a workflow names but the repository lacks, with no protection,
  so a missing or weakened environment stops the publication.
- the rules on main: a pull request with at least one approval, no force
  push and no deletion, from active rulesets;
- a tag ruleset on every tag (~ALL, with nothing excluded): active,
  restricting creation, update and deletion;
- for each of those rulesets, current_user_can_bypass is never: this run's
  own token cannot get around them. GitHub shows a ruleset's bypass list only
  to those who can edit the ruleset, so an empty bypass list on main is a
  setting the maintainers confirm, not something this run can read;
- the repository's configuration variables, as the run sees them (VARS_JSON,
  toJSON(vars)), are empty: the provenance generator publishes them.

It prints rule types and booleans, never who the reviewers are, and exits 1 on
any shortfall or failed read.
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


def environment_findings(repo: str, name: str) -> list[str]:
    try:
        env = gh_api.api(f"repos/{repo}/environments/{name}")
    except gh_api.GitHubError as error:
        if "HTTP 404" not in str(error):
            raise
        return [f"environment {name} does not exist; a run naming it would create it unprotected"]
    findings = []
    if env.get("can_admins_bypass") is not False:
        findings.append(f"environment {name}: administrators can bypass its protection rules")
    reviewers = [
        r for r in env.get("protection_rules", []) if r.get("type") == "required_reviewers"
    ]
    if not reviewers:
        findings.append(f"environment {name}: no required reviewers")
    elif not reviewers[0].get("reviewers"):
        findings.append(f"environment {name}: its required-reviewers rule names no reviewer")
    elif reviewers[0].get("prevent_self_review") is not True:
        findings.append(f"environment {name}: the person who starts a release can approve it")
    policy = env.get("deployment_branch_policy") or {}
    if policy != {"protected_branches": False, "custom_branch_policies": True}:
        findings.append(f"environment {name}: deployments are not limited to selected tags")
    else:
        listed = gh_api.api(f"repos/{repo}/environments/{name}/deployment-branch-policies")
        entries = [(p.get("type"), p.get("name")) for p in listed.get("branch_policies", [])]
        if entries != [("tag", "v*")]:
            findings.append(
                f"environment {name}: deployments are allowed from {entries}, not tags v* alone"
            )
    return findings


def bypass_findings(repo: str, ids: set[int], what: str) -> list[str]:
    findings = []
    for ruleset_id in sorted(ids):
        ruleset = gh_api.api(f"repos/{repo}/rulesets/{ruleset_id}?includes_parents=true")
        if ruleset.get("current_user_can_bypass") != "never":
            findings.append(
                f"{what} ruleset {ruleset_id}: this run's token can bypass it ({ruleset.get('current_user_can_bypass')})"
            )
        if ruleset.get("bypass_actors"):
            findings.append(f"{what} ruleset {ruleset_id}: its bypass list is not empty")
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
    name = env.get("RELEASE_ENVIRONMENT", "release")
    return (
        vars_findings(env.get("VARS_JSON"))
        + environment_findings(repo, name)
        + main_findings(repo)
        + tag_findings(repo)
    )


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
    print("the release environment, the rulesets on main and on every tag, and the variables hold")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
