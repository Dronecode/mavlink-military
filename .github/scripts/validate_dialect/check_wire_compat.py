#!/usr/bin/env python3
"""Report wire-format differences between two versions of military.xml.

Both versions are parsed with pymavlink's own generator, and each message is
compared by the row mavgen writes for it in the MAVLINK_MESSAGE_CRCS table of
the C headers: {msgid, CRC_EXTRA, min_length, max_length, flags,
target_system offset, target_component offset}. CRC_EXTRA covers the message
name and the name and type of every field before <extensions/>, in wire
order, and a peer whose CRC_EXTRA for a message differs from the sender's
drops that message without an error. The lengths are the payload size
without and with the extension fields. The flags (1 for target_system, 2 for
target_component) and the two offsets are what a router reads to find a
message's destination.

The report lists, by message ID and with the old and new rows:

- messages removed, or renamed on an existing ID (a rename changes
  CRC_EXTRA too, and is named as a rename)
- messages whose CRC_EXTRA changes: a field before <extensions/> added,
  removed, retyped or renamed, or moved within the wire order. These are
  the wire-breaking changes.
- messages whose row changes while CRC_EXTRA stays: extension fields
  added, removed or resized, target fields among them. Older peers still
  accept these messages, so they are listed for information.
- messages added (for information; the policy check owns the allocation)

An extension field renamed, or retyped to a type of the same size, leaves
the row alone, and enum values are in no row, so this report cannot see
either; mavlink's check_api_break.py, which the same job runs, covers them.

By default it only reports: while the dialect is still changing, replacing
a message body is sometimes the right call, and that is for review to
decide. Findings go to the run log and the step summary. Set
WIRE_COMPAT_ENFORCE=1 to fail on the wire-breaking ones once message IDs are
frozen.

Usage: check_wire_compat.py <base military.xml> <head military.xml>
Requires pymavlink importable, e.g. PYTHONPATH pointing at the directory
that contains a pymavlink checkout. Includes are not followed: a message's
row depends only on what the file itself defines.
"""

from __future__ import annotations

import os
import sys
from pathlib import Path
from typing import NamedTuple

from pymavlink.generator import mavparse


class Entry(NamedTuple):
    """A message's row in mavgen's MAVLINK_MESSAGE_CRCS table."""

    msg_id: int
    crc_extra: int
    min_length: int
    max_length: int
    flags: int
    target_system_ofs: int
    target_component_ofs: int

    def __str__(self) -> str:
        return "{" + ", ".join(str(value) for value in self) + "}"


def wire_map(path: str) -> dict[int, tuple[str, Entry]]:
    """Each message's name and entry row, as mavgen computes them."""
    xml = mavparse.MAVXML(path, wire_protocol_version=mavparse.PROTOCOL_2_0)
    return {
        m.id: (
            m.name,
            Entry(
                m.id,
                m.crc_extra,
                m.wire_min_length,
                m.wire_length,
                m.message_flags,
                m.target_system_ofs,
                m.target_component_ofs,
            ),
        )
        for m in xml.message
    }


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        print(__doc__, file=sys.stderr)
        return 2
    base = wire_map(argv[1])
    head = wire_map(argv[2])

    breaking = []
    extension_only = []
    for msg_id in sorted(base.keys() & head.keys()):
        (base_name, old), (head_name, new) = base[msg_id], head[msg_id]
        if base_name != head_name or old.crc_extra != new.crc_extra:
            what = f"CRC_EXTRA {old.crc_extra} -> {new.crc_extra}, entry {old} -> {new}"
            if base_name != head_name:
                what = f"renamed to {head_name}, {what}"
            breaking.append(f"BREAKING: message {msg_id} {base_name}: {what}")
        elif old != new:
            extension_only.append(
                f"INFO: message {msg_id} {base_name}: entry {old} -> {new}, "
                "CRC_EXTRA unchanged (extension fields)"
            )
    removed = [
        f"BREAKING: message {msg_id} {base[msg_id][0]} removed (entry {base[msg_id][1]})"
        for msg_id in sorted(base.keys() - head.keys())
    ]
    added = [
        f"INFO: message {msg_id} {head[msg_id][0]} added (entry {head[msg_id][1]})"
        for msg_id in sorted(head.keys() - base.keys())
    ]

    lines = removed + breaking + extension_only + added
    for line in lines:
        prefix = "::warning title=wire-format change::" if line.startswith("BREAKING") else ""
        print(prefix + line)

    total_breaks = len(removed) + len(breaking)
    untouched = len(base.keys() & head.keys()) - len(breaking) - len(extension_only)
    verdict = (
        f"{total_breaks} wire-breaking change(s), {len(extension_only)} extension-only "
        f"change(s), {len(added)} addition(s), {untouched} message(s) untouched on the wire"
    )
    print(verdict)

    summary_path = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary_path:
        with Path(summary_path).open("a", encoding="utf-8") as summary:
            summary.write("## Wire-compatibility report\n\n")
            if lines:
                summary.write("\n".join(f"- {line}" for line in lines))
                summary.write("\n\n")
            summary.write(f"{verdict}\n\n")
            if total_breaks:
                summary.write(
                    "A peer built from the base definitions drops these messages "
                    "without an error. If the change is intended, everything generated "
                    "from this repository has to be regenerated, on both ends of a link.\n"
                )
            if extension_only:
                summary.write(
                    "Older peers still accept the extension-only changes. A sender built "
                    "without the new extension fields leaves them out and the receiver "
                    "reads zeros, so a target field added as an extension reads as "
                    "broadcast for those senders.\n"
                )

    if total_breaks and os.environ.get("WIRE_COMPAT_ENFORCE") == "1":
        print("WIRE_COMPAT_ENFORCE=1: failing on wire-breaking changes", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
