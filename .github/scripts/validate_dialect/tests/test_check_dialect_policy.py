#!/usr/bin/env python3
"""Tests for check_dialect_policy.py, on small dialects in a temporary directory.

From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/validate_dialect/tests
"""

from __future__ import annotations

import contextlib
import io
import os
import runpy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_dialect_policy as policy  # noqa: E402

SHARED = """<?xml version="1.0"?>
<mavlink>
  <enums>
    <enum name="MAV_CMD">
      <entry value="53090" name="MAV_CMD_TEST_ARM"/>
      <entry value="53091" name="MAV_CMD_TEST_STATUS"/>
    </enum>
    <enum name="TEST_MODE">
      <entry value="0" name="TEST_MODE_OFF"/>
    </enum>
  </enums>
  <messages>
    <message id="53000" name="TEST_TRACK">
      <field type="uint32_t" name="track_uid">Track UID.</field>
    </message>
    <message id="53001" name="TEST_STATUS">
      <field type="uint8_t" name="state">State.</field>
    </message>
  </messages>
</mavlink>
"""

TEMPLATE = """<?xml version="1.0"?>
<mavlink>
  <enums>
    <enum name="PRIVATE_MODE">
      <entry value="0" name="PRIVATE_MODE_OFF"/>
    </enum>
  </enums>
  <messages>
    <message id="53900" name="PRIVATE_STATUS">
      <field type="uint8_t" name="state">State.</field>
    </message>
  </messages>
</mavlink>
"""

IDMAPPING = """# Test ID mapping

| NOT_UNDER_A_HEADING | 1 | 2 |

## Shared messages

| Name | Old development ID | New ID |
| --- | --- | --- |
| TEST_TRACK (formerly TRACK) | 60000 | 53000 |
| `TEST_STATUS` | 60001 | `53001` |

A second table in a section is not part of the allocation:

| Name | Old development ID | New ID |
| --- | --- | --- |
| UNRELATED | 1 | 2 |

## MAV_CMD entries

| Name | Old value | New value |
| :--- | :---: | ---: |
| MAV_CMD_TEST_ARM | 60100 | 53090 |
| MAV_CMD_TEST_STATUS | 60101 | 53091 |

## Reserved blocks

| Range | Use |
| --- | --- |
| 53002-53089 | Future shared messages. |
| 53092-53899 | Future shared commands and growth. |
| 53900-53999 | Private block. |

## Prior IDs

| Name | Old ID | Current ID |
| --- | --- | --- |
| OLD_TRACK | 53500 | 53009 |
"""


def line_of(text: str, needle: str, occurrence: int = 1) -> int:
    """The 1-based line of text holding the given occurrence of needle."""
    numbers = [n for n, line in enumerate(text.splitlines(), start=1) if needle in line]
    if len(numbers) < occurrence:
        raise AssertionError(f"{needle!r} is not in the test dialect {occurrence} time(s)")
    return numbers[occurrence - 1]


def with_family_table(idmapping: str, header: str, row: str) -> str:
    """idmapping with a "Test status messages" table before its MAV_CMD entries."""
    rule = "|" + " --- |" * header.count(" | ") + " --- |"
    table = f"## Test status messages\n\n{header}\n{rule}\n{row}\n\n"
    return idmapping.replace("## MAV_CMD entries", table + "## MAV_CMD entries")


class PolicyTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.root = Path(tmp.name)

    def check(
        self,
        shared: str = SHARED,
        template: str = TEMPLATE,
        idmapping: str | None = IDMAPPING,
        actions: bool = False,
    ):
        """Run the policy check on the files; returns (status, stdout, stderr).

        idmapping=None leaves IDMAPPING.md out.
        """
        (self.root / "military.xml").write_text(shared, encoding="utf-8")
        (self.root / "military_extensions.xml").write_text(template, encoding="utf-8")
        if idmapping is not None:
            (self.root / "IDMAPPING.md").write_text(idmapping, encoding="utf-8")
        out, err = io.StringIO(), io.StringIO()
        with mock.patch.dict(os.environ):
            if actions:
                os.environ["GITHUB_ACTIONS"] = "true"
            else:
                os.environ.pop("GITHUB_ACTIONS", None)
            with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
                status = policy.main(["check_dialect_policy.py", str(self.root)])
        return status, out.getvalue(), err.getvalue()

    def assert_findings(self, err: str, *expected: str) -> None:
        """err holds exactly the expected "file:line: message" findings, in order."""
        findings = [
            line[len("ERROR: ") :] for line in err.splitlines() if line.startswith("ERROR: ")
        ]
        self.assertEqual(findings, list(expected))
        self.assertIn(f"FAIL: {len(expected)} policy violation(s)", err)

    def test_clean_dialect_passes(self) -> None:
        status, out, err = self.check()
        self.assertEqual(status, 0)
        self.assertEqual(err, "")
        self.assertEqual(
            out,
            "PASS: military.xml: 2 messages and 2 MAV_CMD entries inside 53000-53899; "
            "military_extensions.xml: 1 template messages inside 53900-53999; "
            "naming, duplicate and IDMAPPING.md checks clean\n",
        )

    def test_message_outside_the_reservation(self) -> None:
        shared = SHARED.replace('id="53001"', 'id="54010"')
        status, _, err = self.check(shared, idmapping=IDMAPPING.replace("`53001`", "`54010`"))
        self.assertEqual(status, 1)
        self.assert_findings(
            err,
            f"military.xml:{line_of(shared, '54010')}: message TEST_STATUS uses ID 54010, "
            "outside the 53000-53999 block upstream all.xml reserves for this dialect",
        )

    def test_shared_message_in_the_private_block(self) -> None:
        shared = SHARED.replace('id="53001"', 'id="53950"')
        _, _, err = self.check(shared, idmapping=IDMAPPING.replace("`53001`", "`53950`"))
        self.assert_findings(
            err,
            f"military.xml:{line_of(shared, '53950')}: message TEST_STATUS uses ID 53950, "
            "outside the shared allocation 53000-53899",
        )

    def test_command_outside_the_shared_allocation(self) -> None:
        shared = SHARED.replace('value="53091"', 'value="53950"')
        _, _, err = self.check(
            shared, idmapping=IDMAPPING.replace("| 60101 | 53091 |", "| 60101 | 53950 |")
        )
        self.assert_findings(
            err,
            f"military.xml:{line_of(shared, '53950')}: MAV_CMD entry MAV_CMD_TEST_STATUS "
            "uses ID 53950, outside the shared allocation 53000-53899",
        )

    def test_template_message_outside_the_private_block(self) -> None:
        template = TEMPLATE.replace('id="53900"', 'id="53050"')
        _, _, err = self.check(template=template)
        self.assert_findings(
            err,
            f"military_extensions.xml:{line_of(template, '53050')}: message PRIVATE_STATUS "
            "uses ID 53050, outside the private/downstream allocation 53900-53999",
        )

    def test_duplicates_point_at_the_second_definition(self) -> None:
        shared = SHARED.replace('id="53001" name="TEST_STATUS"', 'id="53000" name="TEST_TRACK"')
        shared = shared.replace('value="53091"', 'value="53090"')
        idmapping = IDMAPPING.replace("| `TEST_STATUS` | 60001 | `53001` |\n", "").replace(
            "| 60101 | 53091 |", "| 60101 | 53090 |"
        )
        _, _, err = self.check(shared, idmapping=idmapping)
        second = line_of(shared, '<message id="53000" name="TEST_TRACK">', occurrence=2)
        self.assert_findings(
            err,
            f"military.xml:{second}: duplicate message ID 53000",
            f"military.xml:{second}: duplicate message name TEST_TRACK",
            f"military.xml:{line_of(shared, 'MAV_CMD_TEST_STATUS')}: duplicate MAV_CMD value 53090",
        )

    def test_naming_conventions(self) -> None:
        # The bad message name goes in the template, which IDMAPPING.md does not list.
        shared = (
            SHARED.replace('name="TEST_MODE"', 'name="TestMode"')
            .replace('name="TEST_MODE_OFF"', 'name="test_mode_off"')
            .replace('name="track_uid"', 'name="trackUid"')
        )
        template = TEMPLATE.replace('name="PRIVATE_STATUS"', 'name="private_status"')
        _, _, err = self.check(shared, template)
        self.assert_findings(
            err,
            f"military.xml:{line_of(shared, 'TestMode')}: enum name TestMode is not UPPER_SNAKE_CASE",
            f"military.xml:{line_of(shared, 'test_mode_off')}: enum entry test_mode_off "
            "is not UPPER_SNAKE_CASE",
            f"military.xml:{line_of(shared, 'trackUid')}: field TEST_TRACK.trackUid "
            "is not lower_snake_case",
            f"military_extensions.xml:{line_of(template, 'private_status')}: message name "
            "private_status is not UPPER_SNAKE_CASE",
        )

    def test_template_collisions(self) -> None:
        template = TEMPLATE.replace('name="PRIVATE_STATUS"', 'name="TEST_STATUS"').replace(
            'name="PRIVATE_MODE"', 'name="TEST_MODE"'
        )
        _, _, err = self.check(template=template)
        self.assert_findings(
            err,
            f"military_extensions.xml:{line_of(template, 'TEST_STATUS')}: message name "
            "TEST_STATUS collides with the shared dialect",
            f"military_extensions.xml:{line_of(template, 'TEST_MODE')}: enum TEST_MODE "
            "collides with the shared dialect",
        )

    def test_template_reusing_a_shared_id(self) -> None:
        # 53000 is outside the private block as well, so both rules report it.
        template = TEMPLATE.replace('id="53900"', 'id="53000"')
        _, _, err = self.check(template=template)
        line = line_of(template, "53000")
        self.assert_findings(
            err,
            f"military_extensions.xml:{line}: message PRIVATE_STATUS uses ID 53000, "
            "outside the private/downstream allocation 53900-53999",
            f"military_extensions.xml:{line}: message PRIVATE_STATUS reuses shared dialect ID 53000",
        )

    def test_template_may_extend_mav_cmd(self) -> None:
        template = TEMPLATE.replace(
            "  <enums>\n",
            '  <enums>\n    <enum name="MAV_CMD">\n'
            '      <entry value="53990" name="MAV_CMD_PRIVATE_TEST"/>\n    </enum>\n',
        )
        status, out, err = self.check(template=template)
        self.assertEqual(status, 0, err)
        self.assertIn("military_extensions.xml: 1 template messages", out)

    def test_findings_are_annotations_under_github_actions(self) -> None:
        shared = SHARED.replace('id="53001"', 'id="53950"')
        _, _, err = self.check(shared, actions=True)
        line = line_of(shared, "53950")
        self.assertIn(
            f"::error file=military.xml,line={line},title=dialect policy::military.xml:{line}: "
            "message TEST_STATUS uses ID 53950, outside the shared allocation 53000-53899\n",
            err,
        )
        self.assertNotIn("ERROR: ", err)

    def test_annotations_escape_workflow_command_characters(self) -> None:
        err = io.StringIO()
        with (
            mock.patch.dict(os.environ, {"GITHUB_ACTIONS": "true"}),
            contextlib.redirect_stderr(err),
        ):
            policy.report(policy.Finding("military.xml", 7, "50% of\r\nit"))
        self.assertEqual(
            err.getvalue(),
            "::error file=military.xml,line=7,title=dialect policy::military.xml:7: 50%25 of%0D%0Ait\n",
        )

    def test_malformed_xml_is_a_finding(self) -> None:
        broken = SHARED.replace("    </message>\n  </messages>", "  </messages>")
        status, _, err = self.check(broken)
        self.assertEqual(status, 1)
        self.assert_findings(
            err,
            f"military.xml:{line_of(broken, '</messages>')}: not well-formed XML: mismatched tag",
        )
        _, _, err = self.check(template="<mavlink>")
        self.assert_findings(
            err, "military_extensions.xml:1: not well-formed XML: no element found"
        )

    def test_message_and_command_missing_from_idmapping(self) -> None:
        idmapping = IDMAPPING.replace("| `TEST_STATUS` | 60001 | `53001` |\n", "").replace(
            "| MAV_CMD_TEST_STATUS | 60101 | 53091 |\n", ""
        )
        status, _, err = self.check(idmapping=idmapping)
        self.assertEqual(status, 1)
        self.assert_findings(
            err,
            f"military.xml:{line_of(SHARED, 'TEST_STATUS', 2)}: message TEST_STATUS (53001) "
            'is not in the "Shared messages" table of IDMAPPING.md',
            f"military.xml:{line_of(SHARED, 'MAV_CMD_TEST_STATUS')}: MAV_CMD entry "
            'MAV_CMD_TEST_STATUS (53091) is not in the "MAV_CMD entries" table of IDMAPPING.md',
        )

    def test_a_family_table_lists_its_own_messages(self) -> None:
        idmapping = with_family_table(
            IDMAPPING.replace("| `TEST_STATUS` | 60001 | `53001` |\n", ""),
            "| Name | ID |",
            "| TEST_STATUS | 53001 |",
        )
        status, out, err = self.check(idmapping=idmapping)
        self.assertEqual((status, err), (0, ""))
        self.assertIn("IDMAPPING.md checks clean", out)

    def test_a_message_listed_twice(self) -> None:
        idmapping = with_family_table(
            IDMAPPING, "| Name | Old development ID | New ID |", "| TEST_STATUS | 60001 | 53001 |"
        )
        _, _, err = self.check(idmapping=idmapping)
        self.assert_findings(
            err,
            f"IDMAPPING.md:{line_of(idmapping, '| TEST_STATUS |')}: TEST_STATUS is listed again, "
            f"first on line {line_of(idmapping, '`TEST_STATUS`')}",
        )

    def test_a_family_table_without_its_columns(self) -> None:
        idmapping = with_family_table(
            IDMAPPING.replace("| `TEST_STATUS` | 60001 | `53001` |\n", ""),
            "| Message | Old ID | ID |",
            "| TEST_STATUS | 60001 | 53001 |",
        )
        _, _, err = self.check(idmapping=idmapping)
        self.assert_findings(
            err,
            f'IDMAPPING.md:{line_of(idmapping, "| Message |")}: no "Test status messages" '
            "table with Name and New ID or ID columns",
            f"military.xml:{line_of(SHARED, 'TEST_STATUS', 2)}: message TEST_STATUS (53001) is not "
            'in the "Shared messages" or "Test status messages" table of IDMAPPING.md',
        )

    def test_idmapping_lists_a_different_id(self) -> None:
        idmapping = IDMAPPING.replace("| 60000 | 53000 |", "| 60000 | 53005 |")
        _, _, err = self.check(idmapping=idmapping)
        self.assert_findings(
            err,
            f"IDMAPPING.md:{line_of(idmapping, '53005')}: TEST_TRACK is listed at 53005, "
            "but military.xml gives it 53000",
        )

    def test_idmapping_lists_what_military_xml_lacks(self) -> None:
        idmapping = IDMAPPING.replace(
            "| MAV_CMD_TEST_STATUS | 60101 | 53091 |\n",
            "| MAV_CMD_TEST_STATUS | 60101 | 53091 |\n| MAV_CMD_TEST_GONE | 60102 | 53092 |\n",
        )
        _, _, err = self.check(idmapping=idmapping)
        self.assert_findings(
            err,
            f"IDMAPPING.md:{line_of(idmapping, 'MAV_CMD_TEST_GONE')}: MAV_CMD_TEST_GONE (53092) "
            "is listed, but military.xml defines no MAV_CMD entry MAV_CMD_TEST_GONE",
        )

    def test_ids_in_use_inside_a_reserved_block(self) -> None:
        idmapping = IDMAPPING.replace("| 53002-53089 |", "| 53001-53089 |").replace(
            "| 53092-53899 |", "| 53091-53899 |"
        )
        _, _, err = self.check(idmapping=idmapping)
        self.assert_findings(
            err,
            f"military.xml:{line_of(SHARED, 'TEST_STATUS', 2)}: message TEST_STATUS uses ID "
            "53001, which IDMAPPING.md reserves (53001-53089); update its tables",
            f"military.xml:{line_of(SHARED, 'MAV_CMD_TEST_STATUS')}: MAV_CMD entry "
            "MAV_CMD_TEST_STATUS uses ID 53091, which IDMAPPING.md reserves (53091-53899); "
            "update its tables",
        )

    def test_missing_idmapping(self) -> None:
        _, _, err = self.check(idmapping=None)
        self.assert_findings(
            err, "IDMAPPING.md:1: missing: it documents the allocation military.xml follows"
        )

    def test_idmapping_without_its_tables(self) -> None:
        idmapping = (
            IDMAPPING.replace("## Shared messages", "## Messages")
            .replace("| Name | Old value | New value |", "| Name | Old value | Value |")
            .replace("| Range | Use |", "| Block | Use |")
        )
        _, _, err = self.check(idmapping=idmapping)
        self.assert_findings(
            err,
            'IDMAPPING.md:1: no "Shared messages" table with Name and New ID or ID columns',
            f'IDMAPPING.md:{line_of(idmapping, "| Value |")}: no "MAV_CMD entries" table '
            "with Name and New value columns",
            f'IDMAPPING.md:{line_of(idmapping, "| Block |")}: no "Reserved blocks" table '
            "with a Range column",
        )
        _, _, err = self.check(idmapping=IDMAPPING.replace("## Reserved blocks", "## Spare"))
        self.assert_findings(err, 'IDMAPPING.md:1: no "Reserved blocks" table with a Range column')

    def test_idmapping_rows_without_a_name_id_or_range(self) -> None:
        idmapping = (
            IDMAPPING.replace(
                "| `TEST_STATUS` | 60001 | `53001` |", "| `TEST_STATUS` | 60001 | soon |"
            )
            .replace("| MAV_CMD_TEST_ARM | 60100 | 53090 |", "| MAV_CMD_TEST_ARM |")
            .replace("| 53900-53999 |", "| private |")
        )
        _, _, err = self.check(idmapping=idmapping)
        self.assert_findings(
            err,
            f'IDMAPPING.md:{line_of(idmapping, "soon")}: "Shared messages" row has no name and New ID',
            f"military.xml:{line_of(SHARED, 'TEST_STATUS', 2)}: message TEST_STATUS (53001) "
            'is not in the "Shared messages" table of IDMAPPING.md',
            f'IDMAPPING.md:{line_of(idmapping, "| MAV_CMD_TEST_ARM |")}: "MAV_CMD entries" row '
            "has no name and New value",
            f"military.xml:{line_of(SHARED, 'MAV_CMD_TEST_ARM')}: MAV_CMD entry MAV_CMD_TEST_ARM "
            '(53090) is not in the "MAV_CMD entries" table of IDMAPPING.md',
            f'IDMAPPING.md:{line_of(idmapping, "| private |")}: "Reserved blocks" row has no '
            "Range like 53100-53899",
        )

    def test_runs_as_a_script(self) -> None:
        (self.root / "military.xml").write_text(SHARED, encoding="utf-8")
        (self.root / "military_extensions.xml").write_text(TEMPLATE, encoding="utf-8")
        (self.root / "IDMAPPING.md").write_text(IDMAPPING, encoding="utf-8")
        with mock.patch.object(sys, "argv", ["check_dialect_policy.py", str(self.root)]):
            with contextlib.redirect_stdout(io.StringIO()):
                with self.assertRaises(SystemExit) as exit_:
                    runpy.run_path(policy.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 0)


if __name__ == "__main__":
    unittest.main()
