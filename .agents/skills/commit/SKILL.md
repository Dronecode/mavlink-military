---
name: commit
description: Create a MAVLink-M commit following CONTRIBUTING.md
argument-hint: "[optional: description of changes]"
allowed-tools: Bash Read Glob Grep
---

# MAVLink-M Commit

Follow the "Commit messages" and "AI-assisted contributions" sections of
[CONTRIBUTING.md](../../../CONTRIBUTING.md). Read them first if you haven't this
session.

For the `Assisted-by` trailer, AGENT is the harness you are running in and
MODEL is your exact model ID without context-window suffixes such as `[1m]`.
Omit `:MODEL` rather than guess it.

## Steps

1. If on `main`, create a branch `<username>/<description>`, with
   `<username>` from `gh api user --jq .login`.
2. Run `git status` and `git diff --staged`. If nothing is staged, ask what
   to stage. Stage files by name.
3. If `military.xml` changed, check it is well formed:
   `xmllint --noout military.xml`.
4. Commit without `-s`, then run
   `.github/scripts/check_commits.sh origin/main..HEAD` and fix anything it
   rejects.
5. Tell the user to review and sign off. Apply the sign-off for them only if
   they explicitly ask. Do not push unless asked.
