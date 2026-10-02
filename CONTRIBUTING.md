# Contributing to MAVLink-M

MAVLink-M is a message-schema dialect: `military.xml`, its ID map, and the
documentation site. Contributions are reviewed for wire compatibility and for
fit with the [scope and boundaries](README.md#scope-and-boundaries) of the
dialect, so keep each pull request focused on one change and explain it in
plain terms.

## Developer Certificate of Origin

Every commit must carry a `Signed-off-by` trailer, certifying under the
[Developer Certificate of Origin](https://developercertificate.org/) that you
wrote the change or otherwise have the right to submit it under the project
license. Add it with `-s`:

```sh
git commit -s
```

The sign-off name and email must match the commit author. The DCO check on
pull requests blocks merging until every commit is signed off. To fix a branch
after the fact:

```sh
git rebase --signoff origin/main
git push --force-with-lease
```

## Commit messages

```
type(scope): short imperative description
```

The subject is at most 72 characters. Commit subjects and PR titles end up in
the changelog of the generated
[C library](https://github.com/Dronecode/mavlink-military-c_library_v2), so
write them for someone reading that log.

### Types

| Type | Use |
| --- | --- |
| `feat` | Something new on the wire or in the vocabulary: a message, an extension field, an enum entry, a `MAV_CMD` |
| `fix` | A definition that was wrong: field type, units, enum value, or a meaning described incorrectly |
| `docs` | Description text only (in the XML or elsewhere). No change to generated code |
| `ci` | Workflows, `.github/scripts`, generator pin bumps |
| `chore` | Anything else with no wire effect: XML reordering or whitespace, `.gitignore`, license |

### Scopes

Every commit has exactly one scope.

- **A message, enum or command name**, copied exactly as it appears in the XML:
  `TARGET_HANDOVER`, `MAVLINK_M_ACK_RESULT`, `MAV_CMD_MAVLINK_M_STORE_ARM`.
  This keeps `git log --grep='(RWS_POSE)'` useful. For a message and its own
  enum, scope the message and mention the enum in the body. A new message uses
  its own name.
- **An area**, in lowercase, when the change is not about one definition:

| Scope | Area |
| --- | --- |
| `dialect` | Changes spanning several definitions in `military.xml`, or the file as a whole |
| `ids` | `IDMAPPING.md` and ID allocation |
| `private` | `military_extensions.xml`, the private-message template |
| `site` | The documentation site under `docs/` |
| `repo` | `README.md`, `CONTRIBUTING.md`, `AGENTS.md`, licensing and other top-level files |

- **For `ci`, the workflow name**: the basename of the file under
  `.github/workflows/` that the change affects. A script change uses the
  workflow that runs it; a change touching several workflows uses the main
  one.

| Commit | Changes |
| --- | --- |
| `ci(generate_c_lib): bump pymavlink pin` | `.github/mavlink-pins.env` |
| `ci(generate_c_lib): skip publish when headers are unchanged` | `.github/scripts/generate_c_lib/publish_c_library.sh` |
| `ci(docs): cache npm dependencies` | `docs.yml` |
| `ci(commit_checks): allow fixup commits on draft PRs` | `.github/scripts/commit_checks/check_commits.sh` |

Each workflow's scripts live in `.github/scripts/<workflow>/`, and their tests
in its `tests/` folder, which that workflow runs.

### Breaking changes

Append `!` before the colon when an existing sender or receiver would misread
the message, or reject it because its CRC_EXTRA changed:

- removing, reordering or retyping a field, or changing an array length
- adding a field anywhere other than after `<extensions/>`
- renaming a field or message
- changing a message ID or command number
- renumbering, removing or reusing an enum value or bitmask bit
- changing the meaning of an existing field or value

Explain in the commit body what implementations must change. Appending fields
after `<extensions/>`, adding enum entries and editing description text are not
breaking.

### Examples

```
feat(TRACK_IDENTITY): append stanag_track_number as extension field
feat(MAVLINK_M_TARGET_CLASS): add counter-UAS entries
fix(RWS_POSE)!: change elevation from int16 to float
fix(CALL_FOR_FIRE): correct sheaf units to meters
docs(LOITER_MUNITION_CONTROL): clarify the human-consent gate sequence
feat(dialect)!: move ESAD and store messages to 53030-53039
docs(ids): record the development-block history for STORE_MUNITION
ci(generate_c_lib): bump pymavlink pin
chore(repo): ignore editor swap files
```

These fail the check:

```
Update military.xml                 # no type or scope
feat: add field                     # no scope
feat(target_handover): add field    # message names are upper case, as in the XML
feat(TARGET,FIRES): add flags       # one scope; use dialect
ci: bump pymavlink pin              # no scope
ci(ci): bump pymavlink pin          # name the workflow: ci(generate_c_lib)
```

The subject is an imperative sentence that stands on its own in `git log
--oneline`: "add counter-UAS entries", not "adding entries" or "update enum".

### Body

Optional for trivial changes. Otherwise explain why the change is needed and
any decision a reader can't see in the XML: the interoperability case it
serves, the alternative you rejected, a known shortcoming. Wrap at 72 columns.
The diff already says what changed.

## Pull requests

The PR title follows the same `type(scope): description` format and is checked
by CI.

The description is a permanent record that someone will read years from now
while deciding whether a field can change. Write it for that person, in plain
prose:

- **What** changes, in a sentence or two.
- **Why**: the operational or interoperability need, and the reasoning behind
  choices that aren't obvious from the XML.
- **Wire impact**: compatible, or breaking and what implementations must do.

For most changes that is one or two short paragraphs. Please don't:

- restate the diff, list changed files, or paste field tables the XML already
  shows
- add headings and checklists for a change that fits in a paragraph
- rely on a link alone for context; links rot or sit behind access controls,
  so summarize what the reader needs
- describe testing or validation that did not happen

If review changes the PR, update the description before it merges so it still
matches what lands.

### Keep changes small

One PR is one self-contained change. Small PRs get reviewed faster and more
carefully, and every merge to `main` regenerates and publishes the C headers,
so each one ships on its own.

- A new message, a fix to another message and a docs cleanup are three PRs.
- Keep together what belongs together: a new message, its enums, its
  `IDMAPPING.md` entry go in one PR. A message without its
  ID allocation is not self-contained.
- Put pure reordering, reformatting or renaming in its own PR, separate from
  any change in meaning, so reviewers can check one without hunting through
  the other.
- Don't merge a half-defined message expecting a follow-up to finish it. It
  gets published as soon as it lands.
- A message family that has to arrive together, or a restructure across the
  dialect, may be large. Open an issue or discussion first and agree the shape
  with the maintainers before sending it.

## Review

Reviewers look at:

- **Wire compatibility**: field order and types, `<extensions/>` placement,
  enum stability, and `!` where it applies.
- **Scope**: intent and observation only, no device-internal configuration.
- **Interoperability**: whether a gateway can map the message onto the
  external standard it claims to follow, and whether units and frames are
  stated.
- **Naming and descriptions**: consistency with existing MAVLink-M and common
  MAVLink naming, units on physical quantities, descriptions a third party can
  implement from.
- **IDs and docs**: `IDMAPPING.md` and the docs site updated where needed.

Changes to the shared dialect need review by someone other than the author.
Pairing with a colleague or an AI tool does not count as that review.

## Message IDs

Shared messages are allocated from the reserved blocks in
[`IDMAPPING.md`](IDMAPPING.md). Message IDs are stable once assigned. Private,
implementor-specific messages belong in `53900-53999` in your own downstream
file, not in `military.xml`; see `military_extensions.xml` for the template.

## AI-assisted contributions

AI tools are welcome. The same rules apply as for any other contribution, plus
these:

- **You are the author.** You must understand, and be able to defend, every
  line you submit. An AI tool is never an author or co-author: no
  `Co-Authored-By` naming one, and never in a `Signed-off-by`.
- **Disclose it.** Every commit with AI-generated or AI-assisted content
  carries an `Assisted-by` trailer naming the agent (the harness you used),
  the exact model, and optionally any specialized tools it ran, based on the
  [Linux kernel convention](https://docs.kernel.org/process/coding-assistants.html):

  ```
  Assisted-by: AGENT:MODEL [TOOL1] [TOOL2]
  ```

  For example `Assisted-by: Claude-Code:claude-opus-5-5` or
  `Assisted-by: Copilot:gpt-5 xmllint`. Write a multi-word agent name with
  hyphens. Leave out `:MODEL` rather than guess it. Formatters, linters and
  plain editor autocomplete don't need disclosing on their own.
- **Disclose it in the PR too.** End the PR description with the same line,
  in italics: `*Assisted-by: Claude-Code:claude-opus-5-5*`. No other
  generated footers ("Generated with ...").
- **The sign-off is yours.** An agent never signs off on its own initiative.
  It may apply your `Signed-off-by` mechanically, the way `git commit -s`
  does, but only when you explicitly ask it to after reviewing the change.
  The certification is still yours.
- **Don't post model output you don't understand** as a review reply.

## Documentation site

The site is built with [VitePress](https://vitepress.dev) from `docs/`. See
[the contributing page](docs/en/contributing.md) for how to build and preview
it locally.
