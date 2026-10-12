# Status and Roadmap

MAVLink-M is a public draft. Message IDs are stable once assigned, but message
layouts can still change until the standard freezes in November 2026. Feedback
closes at the freeze, so now is the time to check that the messages your
systems need are there and right.

## What the draft means for implementers

- A change that would break an existing sender or receiver is marked with `!`
  in its commit subject, and its commit body says what implementations must
  change. Commit subjects also make up the changelog of the generated
  [C library](https://github.com/Dronecode/mavlink-military-c_library_v2).
- Build against a pinned revision of `military.xml` or of the C library, and
  check the changes marked with `!` before moving to a newer one.

## Roadmap

| Phase | When | What happens |
| --- | --- | --- |
| Draft feedback | August to September 2026 | Done: review of the public draft |
| Path to stable | September to November 2026 | The feedback is worked through, and the standard freezes in November |
| Validation baseline | November 2026 to January 2027 | A multi-vendor range demonstration, and a self-validation toolkit for checking an implementation |
| Continued work | 2027 onward | Further messages and extensions, through the same public process |

## How it started

- **May 7, 2026:** kickoff in Washington, D.C., with defense vendors, drone
  makers and government in one room.
- **Twelve weeks later:** a 48-hour hackathon, where 14 companies built 7
  working integrations.

## Take part

Join the working group on the
[MAVLink-M mailing list](https://lists.dronecode.org/g/mavlink-m), and see
[Contributing](../contributing.md) to propose a change.
