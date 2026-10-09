---
name: pr
description: Open a MAVLink-M pull request following CONTRIBUTING.md
argument-hint: "[optional: target branch or description]"
allowed-tools: Bash Read Glob Grep
---

# MAVLink-M Pull Request

Follow the "Pull requests" and "AI-assisted contributions" sections of
[CONTRIBUTING.md](../../../CONTRIBUTING.md). Read them first if you haven't this
session. The last line of the body is required: `*Assisted-by: AGENT:MODEL*`,
matching the commit trailer.

## Steps

1. Gather context: `git log --oneline origin/main..HEAD` and
   `git diff origin/main...HEAD --stat`.
2. If the branch mixes unrelated changes, tell the user and suggest a split
   before opening anything.
3. Check every commit is signed off:
   `git log --format='%h %(trailers:key=Signed-off-by)' origin/main..HEAD`.
   If any isn't, stop and ask the user to review and sign off, or to tell you
   to apply their sign-off.
4. Check the title with `.github/scripts/commit_checks/check_commits.sh --title "<title>"`.
5. Ask the user what testing or validation they did; never describe testing
   that didn't happen.
6. Push with `-u` once the user confirms, then `gh pr create` against `main`
   unless told otherwise. Return the PR URL.
