#!/usr/bin/env python3
"""Check the SLSA generator that signs the release's provenance, three ways.

Usage: release_generator.py pin
       release_generator.py run
       release_generator.py audit <record.json>

The generator is referenced by its version tag, as its verifier requires, so
these checks bind the run to the reviewed commit of that tag. They read
release.yml's GENERATOR_WORKFLOW, GENERATOR_TAG, GENERATOR_COMMIT and
GENERATOR_ACTIONS, and talk to GitHub only through gh_api, read-only:

pin    The tag still names GENERATOR_COMMIT (peeled if annotated), the
       generator repository is not archived, and its release for the tag is
       published, not a draft or a pre-release. Run by the preflight and
       again by the publish job just before it publishes.
run    This run attempt's record lists, among the workflows it called,
       exactly one from outside this repository: the generator at
       refs/tags/<tag> and GENERATOR_COMMIT. Every other entry is one of this
       repository's workflows at this run's commit. GitHub loads a called
       workflow when the run is created, so this is the code that runs.
audit  The logs of the generator's jobs in this attempt show every action
       they downloaded at a commit GENERATOR_ACTIONS lists, the generator's
       own at GENERATOR_COMMIT, and no job token with Contents: write. The
       run holds an approval of the release environment, and no approval
       comes from the account that pushed the tag or started this attempt
       (GITHUB_ACTOR, GITHUB_TRIGGERING_ACTOR), which a re-run could
       otherwise let through. The record keeps each job's duration and each
       approval's state, environments and the decision link its comment
       gives, never who approved nor the comment's text.

Each prints what it checked and exits 1 on any shortfall or failed read.
"""

from __future__ import annotations

import json
import os
import re
import sys
from datetime import datetime
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import gh_api  # noqa: E402

DOWNLOAD = re.compile(r"Download action repository '([^']+)' \(SHA:([0-9a-f]{40})\)")
PERMISSION = re.compile(r"^\S+ ([A-Za-z-]+): (read|write)$")
GROUP_START, GROUP_END = "##[group]GITHUB_TOKEN Permissions", "##[endgroup]"
DECISION = re.compile(r"^Decision: (https://[A-Za-z0-9._~:/?#\[\]@!$&'()*+,;=%-]+)$", re.M)
ENVIRONMENT = "release"


class GeneratorError(Exception):
    """A shortfall that must stop the release."""


def expected(env: dict) -> dict:
    actions = {}
    for line in env["GENERATOR_ACTIONS"].split():
        action, _, sha = line.rpartition("=")
        actions[action] = sha
    return {
        "workflow": env["GENERATOR_WORKFLOW"],
        "tag": env["GENERATOR_TAG"],
        "commit": env["GENERATOR_COMMIT"],
        "actions": actions,
        "repository": "/".join(env["GENERATOR_WORKFLOW"].split("/")[:2]),
    }


def check_pin(gen: dict) -> str:
    repo, tag = gen["repository"], gen["tag"]
    ref = gh_api.api(f"repos/{repo}/git/ref/tags/{tag}")["object"]
    if ref["type"] == "tag":
        ref = gh_api.api(f"repos/{repo}/git/tags/{ref['sha']}")["object"]
    if ref["sha"] != gen["commit"]:
        raise GeneratorError(
            f"{repo} tag {tag} names {ref['sha']}, not the reviewed {gen['commit']}"
        )
    if gh_api.api(f"repos/{repo}")["archived"]:
        raise GeneratorError(f"{repo} is archived")
    release = gh_api.api(f"repos/{repo}/releases/tags/{tag}")
    if release["draft"] or release["prerelease"]:
        raise GeneratorError(f"{repo} release {tag} is a draft or a pre-release")
    return f"{repo} {tag} names {gen['commit']}; the release is published and the repository active"


def check_run(gen: dict, env: dict) -> str:
    repo, sha = env["GITHUB_REPOSITORY"], env["GITHUB_SHA"]
    record = gh_api.api(
        f"repos/{repo}/actions/runs/{env['GITHUB_RUN_ID']}/attempts/{env['GITHUB_RUN_ATTEMPT']}"
    )
    called = record.get("referenced_workflows") or []
    outside = [w for w in called if not w["path"].startswith(f"{repo}/.github/workflows/")]
    wanted = {
        "path": f"{gen['workflow']}@{gen['tag']}",
        "ref": f"refs/tags/{gen['tag']}",
        "sha": gen["commit"],
    }
    if [{k: w.get(k) for k in wanted} for w in outside] != [wanted]:
        raise GeneratorError(
            f"this run calls {outside} from outside {repo}, not the generator alone at {wanted}"
        )
    local = [w for w in called if w not in outside]
    stray = [w["path"] for w in local if w.get("sha") != sha or not w["path"].endswith(f"@{sha}")]
    if stray:
        raise GeneratorError(f"called workflows not at this run's commit {sha}: {stray}")
    return f"this attempt loaded the generator at {gen['commit']} and {len(local)} workflow(s) of {repo} at {sha}"


def token_permissions(log: str) -> dict[str, str]:
    lines = log.splitlines()
    if not any(line.endswith(GROUP_START) for line in lines):
        raise GeneratorError("a generator job's log has no GITHUB_TOKEN Permissions block")
    start = next(i for i, line in enumerate(lines) if line.endswith(GROUP_START))
    found = {}
    for line in lines[start + 1 :]:
        if line.endswith(GROUP_END):
            return found
        match = PERMISSION.match(line)
        if match is None:
            # The runner's log format is no documented interface; anything
            # unexpected stops the release rather than being skipped.
            raise GeneratorError(
                f"an unexpected line in a GITHUB_TOKEN Permissions block: {line!r}"
            )
        found[match.group(1)] = match.group(2)
    raise GeneratorError("a GITHUB_TOKEN Permissions block does not end")


def seconds(job: dict) -> int | None:
    if not job.get("started_at") or not job.get("completed_at"):
        return None
    start, end = (
        datetime.fromisoformat(job[k].replace("Z", "+00:00"))
        for k in ("started_at", "completed_at")
    )
    return int((end - start).total_seconds())


def approvals_record(approvals: list[dict], env: dict) -> list[dict]:
    """The run's approvals as the evidence keeps them, after the two-person checks."""
    actors = {env.get("GITHUB_ACTOR"), env.get("GITHUB_TRIGGERING_ACTOR")} - {None, ""}
    record, approved = [], False
    for approval in approvals:
        environments = sorted(e["name"] for e in approval.get("environments", []))
        if approval.get("state") == "approved":
            if (approval.get("user") or {}).get("login") in actors:
                raise GeneratorError(
                    "an approval comes from the account that pushed the tag or started this attempt"
                )
            approved = approved or ENVIRONMENT in environments
        decision = DECISION.search(approval.get("comment") or "")
        record.append({"state": approval.get("state"), "environments": environments,
                       "decision": decision.group(1) if decision else None})  # fmt: skip
    if not approved:
        raise GeneratorError(f"this run holds no approval of the {ENVIRONMENT} environment")
    return record


def audit(gen: dict, env: dict) -> dict:
    repo, run_id, attempt = (
        env["GITHUB_REPOSITORY"],
        env["GITHUB_RUN_ID"],
        env["GITHUB_RUN_ATTEMPT"],
    )
    prefix = env["GENERATOR_JOB"] + " / "
    jobs = gh_api.api(f"repos/{repo}/actions/runs/{run_id}/attempts/{attempt}/jobs?per_page=100")[
        "jobs"
    ]
    ran = [j for j in jobs if j["name"].startswith(prefix) and j["conclusion"] != "skipped"]
    if not ran:
        raise GeneratorError(f"no job of {env['GENERATOR_JOB']} ran in this attempt")
    record = {"generator": {k: gen[k] for k in ("workflow", "tag", "commit")}, "jobs": []}
    for job in ran:
        log = gh_api.run("api", f"repos/{repo}/actions/jobs/{job['id']}/logs")
        downloads = DOWNLOAD.findall(log)
        for action, sha in downloads:
            if gen["actions"].get(action) != sha:
                raise GeneratorError(
                    f"{job['name']} downloaded {action} at {sha}, which the reviewed pin does not list"
                )
        permissions = token_permissions(log)
        if permissions.get("Contents") == "write":
            raise GeneratorError(f"{job['name']} ran with a Contents: write token")
        record["jobs"].append({
            "name": job["name"], "conclusion": job["conclusion"], "seconds": seconds(job),
            "downloads": [f"{a}={s}" for a, s in downloads], "token": permissions,
        })  # fmt: skip
    approvals = gh_api.api(f"repos/{repo}/actions/runs/{run_id}/approvals") or []
    record["approvals"] = approvals_record(approvals, env)
    return record


def main(argv: list[str]) -> int:
    if (
        len(argv) < 2
        or argv[1] not in ("pin", "run", "audit")
        or (argv[1] == "audit") != (len(argv) == 3)
    ):
        print(__doc__, file=sys.stderr)
        return 2
    env = dict(os.environ)
    gen = expected(env)
    try:
        if argv[1] == "pin":
            print(check_pin(gen))
        elif argv[1] == "run":
            print(check_run(gen, env))
        else:
            record = audit(gen, env)
            Path(argv[2]).write_text(
                json.dumps(record, indent=2, sort_keys=True) + "\n", encoding="utf-8"
            )
            print(
                f"{len(record['jobs'])} generator job(s) audited; {len(record['approvals'])} approval(s) recorded"
            )
    except (GeneratorError, gh_api.GitHubError, KeyError) as error:
        print(f"::error title=release generator::{error}")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
