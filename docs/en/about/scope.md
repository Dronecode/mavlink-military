# Scope and Boundaries

MAVLink-M is a message-schema dialect. It defines field layouts on top of open
MAVLink; it is not an implementation, and it does not describe how any device
works internally.

What the dialect deliberately does and does not carry is the core of its design:

- **It carries descriptive intent and observation**: what was seen, what is
  requested, and the current status of a participant. This is the information a
  cooperating system needs to coordinate.
- **It excludes device-internal configuration**: no fuze timing values, no
  laser codes, no performance or effectiveness data. The messages describe
  coordination between participants, never the internal programming of a device.
- **Kinetic and non-kinetic intent are separable**: observation cueing is a
  distinct message from action requests, so a consumer can tell "observe this"
  from "act on this" by message ID alone.
- **Accountability is a record, not a trigger**: messages that record a
  decision or authorization are exactly that: a record for audit and shared
  awareness, not a command that causes an action.

These boundaries are intentional. They keep the dialect a coordination and
telemetry vocabulary that interoperates across systems, and keep the internal
programming of any device off the wire.

Proposed additions to the shared dialect are reviewed against these rules. See
[Contributing](../contributing.md).
