#!/usr/bin/env python3
"""Check the dialect files against this repository's allocation policy.

The policy enforced here is the one the repository documents in README.md,
IDMAPPING.md and the military.xml header, not a new one:

- Upstream MAVLink (all.xml) reserves message IDs 53000-53999 for this
  dialect.
- military.xml, the shared dialect, allocates messages and MAV_CMD entries
  from the shared window 53000-53899 (53000-53099 active, 53100-53899
  reserved for future shared growth).
- 53900-53999 is the private/downstream block: military.xml must never
  allocate from it, and military_extensions.xml, the downstream template,
  must allocate only from it.
- Message, enum and enum-entry names are UPPER_SNAKE_CASE and field names
  are lower_snake_case, matching MAVLink conventions.
- No duplicate message IDs or names inside a file, and the template must
  not collide with a shared message or enum name.
- IDMAPPING.md lists every military.xml message once, in its "Shared
  messages" table or in a table of its own for a family of messages under
  a "## <family> messages" heading, and every MAV_CMD entry in its
  "MAV_CMD entries" table, each at the ID military.xml gives it ("New ID"
  where a table maps development IDs, "ID" in a family's table of new
  messages), and lists nothing military.xml does not define. No ID in use falls inside a range
  its "Reserved blocks" table holds for the shared dialect. Its history
  table is not checked.

Structure beyond this policy (schema conformance, field types, duplicates
against common.xml) is owned by the schema check and by mavgen, which parse
the full include tree. This script runs on the Python standard library only
so it needs no checkout besides this repository.

Each violation is printed as "file:line: message"; under GitHub Actions
it is also an error annotation on that line of the pull request.

Exit status: 0 when every check passes, 1 with one line per violation.
"""

from __future__ import annotations

import os
import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import NamedTuple
from xml.parsers import expat

REPO_ROOT = Path(__file__).resolve().parents[3]

DIALECT_RESERVATION = range(53000, 54000)  # upstream all.xml reservation
SHARED_ALLOCATION = range(53000, 53900)  # military.xml draws from here
PRIVATE_ALLOCATION = range(53900, 54000)  # military_extensions.xml only

UPPER_SNAKE = re.compile(r"^[A-Z][A-Z0-9_]*$")
LOWER_SNAKE = re.compile(r"^[a-z][a-z0-9_]*$")

IDMAPPING = "IDMAPPING.md"
NAME_CELL = re.compile(r"^`?([A-Z][A-Z0-9_]*)")  # "TARGET (formerly TARGET_COORD)" is TARGET
NUMBER_CELL = re.compile(r"^`?(\d+)`?$")
RANGE_CELL = re.compile(r"^`?(\d+)-(\d+)`?$")


class Finding(NamedTuple):
    """One policy violation, at a line of a dialect file."""

    file: str
    line: int
    message: str

    def __str__(self) -> str:
        return f"{self.file}:{self.line}: {self.message}"


def parse(path: Path) -> tuple[ET.Element, dict[ET.Element, int]]:
    """Parse an XML file, recording the line each element starts on.

    ElementTree keeps no line numbers, so this drives expat with an
    ElementTree builder and notes the parser's line at each start tag.
    """
    builder = ET.TreeBuilder()
    lines: dict[ET.Element, int] = {}
    parser = expat.ParserCreate()

    def start(tag: str, attrs: dict[str, str]) -> None:
        lines[builder.start(tag, attrs)] = parser.CurrentLineNumber

    parser.StartElementHandler = start
    parser.EndElementHandler = builder.end
    parser.CharacterDataHandler = builder.data
    with path.open("rb") as xml:
        parser.ParseFile(xml)
    return builder.close(), lines


class Dialect:
    """The names and IDs one dialect file defines (includes not followed).

    Each entry carries the line of its element, for findings.
    """

    def __init__(self, path: Path):
        self.path = path
        root, self.lines = parse(path)
        messages = root.findall("./messages/message")
        self.messages = [(int(m.get("id")), m.get("name"), self.lines[m]) for m in messages]
        self.enums = root.findall("./enums/enum")
        self.commands = [
            (int(e.get("value")), e.get("name"), self.lines[e])
            for enum in self.enums
            if enum.get("name") == "MAV_CMD"
            for e in enum.findall("entry")
        ]
        self.fields = [
            (m.get("name"), f.get("name"), self.lines[f])
            for m in messages
            for f in m.findall("field")
        ]

    def finding(self, line: int, message: str) -> Finding:
        return Finding(self.path.name, line, message)


def check_allocation(d: Dialect, allocation: range, label: str) -> list[Finding]:
    errors = []
    for kind, entries in (("message", d.messages), ("MAV_CMD entry", d.commands)):
        for value, name, line in entries:
            if value not in DIALECT_RESERVATION:
                errors.append(
                    d.finding(
                        line,
                        f"{kind} {name} uses ID {value}, outside the 53000-53999 "
                        "block upstream all.xml reserves for this dialect",
                    )
                )
            elif value not in allocation:
                errors.append(
                    d.finding(
                        line,
                        f"{kind} {name} uses ID {value}, outside the {label} "
                        f"allocation {allocation.start}-{allocation.stop - 1}",
                    )
                )
    return errors


def check_duplicates(d: Dialect) -> list[Finding]:
    errors = []
    for kind, entries in (
        ("message ID", [(i, line) for i, _, line in d.messages]),
        ("message name", [(n, line) for _, n, line in d.messages]),
        ("MAV_CMD value", [(v, line) for v, _, line in d.commands]),
    ):
        seen: set = set()
        for item, line in entries:
            if item in seen:
                errors.append(d.finding(line, f"duplicate {kind} {item}"))
            seen.add(item)
    return errors


def check_naming(d: Dialect) -> list[Finding]:
    errors = []
    for _, name, line in d.messages:
        if not UPPER_SNAKE.match(name or ""):
            errors.append(d.finding(line, f"message name {name} is not UPPER_SNAKE_CASE"))
    for enum in d.enums:
        enum_name = enum.get("name") or ""
        if not UPPER_SNAKE.match(enum_name):
            errors.append(
                d.finding(d.lines[enum], f"enum name {enum_name} is not UPPER_SNAKE_CASE")
            )
        for entry in enum.findall("entry"):
            entry_name = entry.get("name") or ""
            if not UPPER_SNAKE.match(entry_name):
                errors.append(
                    d.finding(d.lines[entry], f"enum entry {entry_name} is not UPPER_SNAKE_CASE")
                )
    for message_name, field_name, line in d.fields:
        if not LOWER_SNAKE.match(field_name or ""):
            errors.append(
                d.finding(line, f"field {message_name}.{field_name} is not lower_snake_case")
            )
    return errors


def check_template_collisions(shared: Dialect, template: Dialect) -> list[Finding]:
    errors = []
    shared_ids = {i for i, _, _ in shared.messages}
    shared_names = {n for _, n, _ in shared.messages}
    shared_enums = {e.get("name") for e in shared.enums} - {"MAV_CMD"}
    for msg_id, name, line in template.messages:
        if msg_id in shared_ids:
            errors.append(
                template.finding(line, f"message {name} reuses shared dialect ID {msg_id}")
            )
        if name in shared_names:
            errors.append(
                template.finding(line, f"message name {name} collides with the shared dialect")
            )
    for enum in template.enums:
        if enum.get("name") in shared_enums:
            errors.append(
                template.finding(
                    template.lines[enum],
                    f"enum {enum.get('name')} collides with the shared dialect",
                )
            )
    return errors


class Table(NamedTuple):
    """A Markdown pipe table: its header cells and, by line, its rows."""

    line: int
    header: list[str]
    rows: list[tuple[int, list[str]]]


def markdown_tables(path: Path) -> dict[str, Table]:
    """The first pipe table under each "## " heading, by heading text."""
    tables: dict[str, Table] = {}
    heading = None
    current = None
    for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), start=1):
        if line.startswith("## "):
            heading, current = line[3:].strip(), None
        elif not line.startswith("|"):
            current = None
        elif heading is not None:
            cells = [cell.strip() for cell in line.strip().strip("|").split("|")]
            if current is None and heading not in tables:
                current = tables[heading] = Table(number, cells, [])
            elif current is not None and not all(cell and set(cell) <= set(":-") for cell in cells):
                current.rows.append((number, cells))
    return tables


def message_tables(tables: dict[str, Table]) -> list[str]:
    """ "Shared messages", then the heading of each family's "## <family> messages" table."""
    shared = "Shared messages"
    return [shared] + [h for h in tables if h.endswith(" messages") and h != shared]


def documented_ids(
    tables: dict[str, Table], headings: list[str], columns: tuple[str, ...], errors: list[Finding]
) -> dict[str, tuple[int, int]] | None:
    """Name to (ID, line) across IDMAPPING.md tables, or None if the first is missing.

    The first heading is required; the others are the tables found beside it.
    Each table gives its IDs in the first of columns it has. A name listed
    twice is a finding at its second listing.
    """
    ids: dict[str, tuple[int, int]] = {}
    for heading in headings:
        table = tables.get(heading)
        column = next((c for c in columns if table and c in table.header), None)
        if table is None or "Name" not in table.header or column is None:
            errors.append(
                Finding(
                    IDMAPPING,
                    table.line if table else 1,
                    f'no "{heading}" table with Name and {" or ".join(columns)} columns',
                )
            )
            if heading == headings[0]:
                return None
            continue
        name_at, id_at = table.header.index("Name"), table.header.index(column)
        for line, cells in table.rows:
            name = NAME_CELL.match(cells[name_at]) if len(cells) > max(name_at, id_at) else None
            value = NUMBER_CELL.match(cells[id_at]) if name else None
            if value is None:
                errors.append(Finding(IDMAPPING, line, f'"{heading}" row has no name and {column}'))
            elif name.group(1) in ids:
                first = ids[name.group(1)][1]
                errors.append(
                    Finding(
                        IDMAPPING, line, f"{name.group(1)} is listed again, first on line {first}"
                    )
                )
            else:
                ids[name.group(1)] = (int(value.group(1)), line)
    return ids


def check_idmapping(shared: Dialect, path: Path) -> list[Finding]:
    """IDMAPPING.md matches the IDs military.xml allocates."""
    if not path.is_file():
        return [Finding(IDMAPPING, 1, "missing: it documents the allocation military.xml follows")]
    tables = markdown_tables(path)
    errors: list[Finding] = []
    for headings, columns, kind, entries in (
        # A table that maps development IDs gives the ID a message has now as
        # its New ID; a family of messages that never had another ID lists ID.
        (message_tables(tables), ("New ID", "ID"), "message", shared.messages),
        (["MAV_CMD entries"], ("New value",), "MAV_CMD entry", shared.commands),
    ):
        documented = documented_ids(tables, headings, columns, errors)
        if documented is None:
            continue
        where = " or ".join(f'"{heading}"' for heading in headings)
        for value, name, line in entries:
            if name not in documented:
                errors.append(
                    shared.finding(
                        line,
                        f"{kind} {name} ({value}) is not in the {where} table of {IDMAPPING}",
                    )
                )
            elif documented[name][0] != value:
                errors.append(
                    Finding(
                        IDMAPPING,
                        documented[name][1],
                        f"{name} is listed at {documented[name][0]}, but military.xml gives it {value}",
                    )
                )
        defined = {name for _, name, _ in entries}
        for name, (value, line) in documented.items():
            if name not in defined:
                errors.append(
                    Finding(
                        IDMAPPING,
                        line,
                        f"{name} ({value}) is listed, but military.xml defines no {kind} {name}",
                    )
                )

    table = tables.get("Reserved blocks")
    if table is None or "Range" not in table.header:
        errors.append(
            Finding(
                IDMAPPING,
                table.line if table else 1,
                'no "Reserved blocks" table with a Range column',
            )
        )
        return errors
    range_at = table.header.index("Range")
    in_use = [("message", *m) for m in shared.messages] + [
        ("MAV_CMD entry", *c) for c in shared.commands
    ]
    for row_line, cells in table.rows:
        bounds = RANGE_CELL.match(cells[range_at]) if len(cells) > range_at else None
        if bounds is None:
            errors.append(
                Finding(IDMAPPING, row_line, '"Reserved blocks" row has no Range like 53100-53899')
            )
            continue
        low, high = int(bounds.group(1)), int(bounds.group(2))
        if low not in SHARED_ALLOCATION or high not in SHARED_ALLOCATION:
            continue  # the private block; check_allocation keeps military.xml out of it
        for kind, value, name, line in in_use:
            if low <= value <= high:
                errors.append(
                    shared.finding(
                        line,
                        f"{kind} {name} uses ID {value}, which {IDMAPPING} reserves ({low}-{high}); "
                        "update its tables",
                    )
                )
    return errors


def report(finding: Finding) -> None:
    """Print a finding, as an annotation on its line when run by GitHub Actions."""
    if os.environ.get("GITHUB_ACTIONS") == "true":
        text = str(finding).replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")
        print(
            f"::error file={finding.file},line={finding.line},title=dialect policy::{text}",
            file=sys.stderr,
        )
    else:
        print(f"ERROR: {finding}", file=sys.stderr)


def main(argv: list[str]) -> int:
    root = Path(argv[1]) if len(argv) > 1 else REPO_ROOT
    dialects = []
    for name in ("military.xml", "military_extensions.xml"):
        try:
            dialects.append(Dialect(root / name))
        except expat.ExpatError as error:
            # The schema job reports this too; a finding reads better than a traceback.
            report(
                Finding(name, error.lineno, f"not well-formed XML: {expat.ErrorString(error.code)}")
            )
            print("FAIL: 1 policy violation(s)", file=sys.stderr)
            return 1
    shared, template = dialects

    errors = []
    errors += check_allocation(shared, SHARED_ALLOCATION, "shared")
    errors += check_allocation(template, PRIVATE_ALLOCATION, "private/downstream")
    for dialect in (shared, template):
        errors += check_duplicates(dialect)
        errors += check_naming(dialect)
    errors += check_template_collisions(shared, template)
    errors += check_idmapping(shared, root / IDMAPPING)

    for error in errors:
        report(error)
    if errors:
        print(f"FAIL: {len(errors)} policy violation(s)", file=sys.stderr)
        return 1

    print(
        f"PASS: {shared.path.name}: {len(shared.messages)} messages and "
        f"{len(shared.commands)} MAV_CMD entries inside "
        f"{SHARED_ALLOCATION.start}-{SHARED_ALLOCATION.stop - 1}; "
        f"{template.path.name}: {len(template.messages)} template messages inside "
        f"{PRIVATE_ALLOCATION.start}-{PRIVATE_ALLOCATION.stop - 1}; "
        f"naming, duplicate and {IDMAPPING} checks clean"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
