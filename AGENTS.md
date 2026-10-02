# MAVLink-M

A MAVLink 2 dialect: `military.xml`, its ID map `IDMAPPING.md`, and a
VitePress site under `docs/`. No application code.

[CONTRIBUTING.md](CONTRIBUTING.md) holds the rules for commits, PRs, wire
compatibility, IDs and AI disclosure. Read it before committing or opening a
PR. The points below are specific to agents.

- **Commits and PRs:** use the `commit` and `pr` skills.
- **Attribution:** disclose via the `Assisted-by` commit trailer and the
  matching italic last line of the PR description, filled from your actual
  harness and model ID. No `Co-Authored-By` naming an AI, no other
  generated-by footer.
- **DCO:** never add `Signed-off-by` on your own. Apply the user's sign-off
  (`git commit -s`, `git rebase --signoff`) only when they explicitly ask,
  after they have reviewed the change.
- **Wire compatibility:** never make a breaking change unless the user asks
  for one.
- **Dialect scope:** read the README's "Scope and boundaries" before adding
  or changing messages.
- **Staging:** stage files by name, never `git add -A` or `git add .`. The
  repo root holds untracked files that must not be committed.
