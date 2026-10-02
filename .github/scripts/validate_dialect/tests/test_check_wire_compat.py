#!/usr/bin/env python3
"""Tests for check_wire_compat.py.

Needs pymavlink importable, as check_wire_compat.py does. From the
repository root, with a pymavlink checkout in ./pymavlink:

    PYTHONPATH=. python3 -m unittest discover \
        --start-directory .github/scripts/validate_dialect/tests
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
import check_wire_compat  # noqa: E402

TRACK = """
    <message id="53000" name="TEST_TRACK">
      <description>Track.</description>
      <field type="uint32_t" name="track_uid">Track UID.</field>
      <field type="uint8_t" name="state">State.</field>
      <field type="uint8_t" name="quality">Quality.</field>
    </message>"""

STATUS = """
    <message id="53001" name="TEST_STATUS">
      <description>Status.</description>
      <field type="float" name="value">Value.</field>
      <extensions/>
      <field type="uint8_t" name="flags">Flags.</field>
    </message>"""


def dialect(*messages: str) -> str:
    return (
        '<?xml version="1.0"?>\n<mavlink>\n  <version>3</version>\n  <messages>'
        + "".join(messages)
        + "\n  </messages>\n</mavlink>\n"
    )


class CheckWireCompatTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.dir = Path(tmp.name)
        self.base = self.write("base.xml", dialect(TRACK, STATUS))

    def write(self, name: str, text: str) -> str:
        path = self.dir / name
        path.write_text(text, encoding="utf-8")
        return str(path)

    def compare(self, head: str, enforce: str | None = None, summary: Path | None = None):
        """Compare the base with head; returns (status, stdout, stderr)."""
        out, err = io.StringIO(), io.StringIO()
        with mock.patch.dict(os.environ):
            for name, value in (("WIRE_COMPAT_ENFORCE", enforce), ("GITHUB_STEP_SUMMARY", summary)):
                if value is None:
                    os.environ.pop(name, None)
                else:
                    os.environ[name] = str(value)
            with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
                status = check_wire_compat.main(["check_wire_compat.py", self.base, head])
        return status, out.getvalue(), err.getvalue()

    def test_identical_definitions_report_nothing(self) -> None:
        status, out, _ = self.compare(self.base)
        self.assertEqual(status, 0)
        self.assertEqual(
            out,
            "0 wire-breaking change(s), 0 extension-only change(s), 0 addition(s), "
            "2 message(s) untouched on the wire\n",
        )

    def test_entry_reads_as_mavgen_writes_it(self) -> None:
        entry = check_wire_compat.Entry(53004, 224, 69, 69, 3, 16, 17)
        self.assertEqual(str(entry), "{53004, 224, 69, 69, 3, 16, 17}")

    def test_retyped_field_changes_crc_extra_and_length(self) -> None:
        head = self.write(
            "head.xml",
            dialect(TRACK.replace('"uint8_t" name="quality"', '"uint16_t" name="quality"'), STATUS),
        )
        status, out, _ = self.compare(head)
        self.assertEqual(status, 0)
        self.assertRegex(
            out,
            r"::warning title=wire-format change::BREAKING: message 53000 TEST_TRACK: "
            r"CRC_EXTRA (\d+) -> (\d+), entry \{53000, \1, 6, 6, 0, 0, 0\} -> "
            r"\{53000, \2, 7, 7, 0, 0, 0\}\n",
        )
        self.assertIn(
            "1 wire-breaking change(s), 0 extension-only change(s), 0 addition(s), "
            "1 message(s) untouched",
            out,
        )

    def test_reordered_fields_of_one_size_change_crc_extra(self) -> None:
        swapped = TRACK.replace(
            '<field type="uint8_t" name="state">State.</field>\n'
            '      <field type="uint8_t" name="quality">Quality.</field>',
            '<field type="uint8_t" name="quality">Quality.</field>\n'
            '      <field type="uint8_t" name="state">State.</field>',
        )
        self.assertNotEqual(swapped, TRACK)
        status, out, _ = self.compare(self.write("head.xml", dialect(swapped, STATUS)))
        self.assertEqual(status, 0)
        self.assertRegex(
            out,
            r"BREAKING: message 53000 TEST_TRACK: CRC_EXTRA (\d+) -> (\d+), "
            r"entry \{53000, \1, 6, 6, 0, 0, 0\} -> \{53000, \2, 6, 6, 0, 0, 0\}",
        )

    def test_rename_on_the_same_id_is_named(self) -> None:
        head = self.write("head.xml", dialect(TRACK.replace("TEST_TRACK", "TEST_TRACK_V2"), STATUS))
        _, out, _ = self.compare(head)
        self.assertRegex(
            out, r"BREAKING: message 53000 TEST_TRACK: renamed to TEST_TRACK_V2, CRC_EXTRA"
        )

    def test_target_fields_in_the_base_give_the_row_its_flags_and_offsets(self) -> None:
        addressed = TRACK.replace(
            '<field type="uint32_t" name="track_uid">',
            '<field type="uint8_t" name="target_system">System ID.</field>\n'
            '      <field type="uint8_t" name="target_component">Component ID.</field>\n'
            '      <field type="uint32_t" name="track_uid">',
        )
        status, out, _ = self.compare(self.write("head.xml", dialect(addressed, STATUS)))
        self.assertEqual(status, 0)
        # The uint32 sorts first, then the uint8 fields in XML order: targets at 4 and 5.
        self.assertRegex(
            out,
            r"BREAKING: message 53000 TEST_TRACK: CRC_EXTRA (\d+) -> (\d+), "
            r"entry \{53000, \1, 6, 6, 0, 0, 0\} -> \{53000, \2, 8, 8, 3, 4, 5\}\n",
        )

    def test_target_fields_in_the_extensions_keep_crc_extra(self) -> None:
        extended = STATUS.replace(
            '<field type="uint8_t" name="flags">Flags.</field>',
            '<field type="uint8_t" name="flags">Flags.</field>\n'
            '      <field type="uint8_t" name="target_system">System ID.</field>\n'
            '      <field type="uint8_t" name="target_component">Component ID.</field>',
        )
        summary = self.dir / "summary.md"
        status, out, _ = self.compare(
            self.write("head.xml", dialect(TRACK, extended)), enforce="1", summary=summary
        )
        self.assertEqual(status, 0)
        self.assertRegex(
            out,
            r"^INFO: message 53001 TEST_STATUS: entry \{53001, (\d+), 4, 5, 0, 0, 0\} -> "
            r"\{53001, \1, 4, 7, 3, 5, 6\}, CRC_EXTRA unchanged \(extension fields\)\n",
        )
        self.assertNotIn("::warning", out)
        self.assertIn(
            "0 wire-breaking change(s), 1 extension-only change(s), 0 addition(s), "
            "1 message(s) untouched",
            out,
        )
        text = summary.read_text(encoding="utf-8")
        self.assertIn("so a target field added as an extension reads as broadcast", text)
        self.assertNotIn("drops these messages", text)

    def test_removed_and_added_messages(self) -> None:
        added = STATUS.replace('id="53001" name="TEST_STATUS"', 'id="53002" name="TEST_EVENT"')
        status, out, _ = self.compare(self.write("head.xml", dialect(TRACK, added)))
        self.assertEqual(status, 0)
        self.assertRegex(
            out,
            r"::warning title=wire-format change::BREAKING: message 53001 TEST_STATUS removed "
            r"\(entry \{53001, \d+, 4, 5, 0, 0, 0\}\)\n",
        )
        self.assertRegex(
            out, r"\nINFO: message 53002 TEST_EVENT added \(entry \{53002, \d+, 4, 5, 0, 0, 0\}\)\n"
        )
        self.assertIn(
            "1 wire-breaking change(s), 0 extension-only change(s), 1 addition(s), "
            "1 message(s) untouched",
            out,
        )

    def test_extension_fields_keep_crc_extra(self) -> None:
        extended = STATUS.replace(
            '<field type="uint8_t" name="flags">Flags.</field>',
            '<field type="uint8_t" name="flags">Flags.</field>\n'
            '      <field type="uint16_t" name="mode">Mode.</field>',
        )
        status, out, _ = self.compare(self.write("head.xml", dialect(TRACK, extended)))
        self.assertEqual(status, 0)
        self.assertRegex(
            out,
            r"INFO: message 53001 TEST_STATUS: entry \{53001, (\d+), 4, 5, 0, 0, 0\} -> "
            r"\{53001, \1, 4, 7, 0, 0, 0\}, CRC_EXTRA unchanged",
        )

    def test_enforce_fails_on_a_break_only(self) -> None:
        head = self.write("head.xml", dialect(TRACK))
        status, _, err = self.compare(head, enforce="1")
        self.assertEqual(status, 1)
        self.assertIn("WIRE_COMPAT_ENFORCE=1: failing on wire-breaking changes", err)
        status, _, _ = self.compare(self.base, enforce="1")
        self.assertEqual(status, 0)
        status, _, _ = self.compare(head, enforce="0")
        self.assertEqual(status, 0)

    def test_step_summary(self) -> None:
        summary = self.dir / "summary.md"
        self.compare(self.write("head.xml", dialect(TRACK)), summary=summary)
        text = summary.read_text(encoding="utf-8")
        self.assertRegex(
            text,
            r"^## Wire-compatibility report\n\n- BREAKING: message 53001 TEST_STATUS removed "
            r"\(entry \{53001, \d+, 4, 5, 0, 0, 0\}\)\n\n",
        )
        self.assertIn(
            "A peer built from the base definitions drops these messages without an error.", text
        )
        self.assertNotIn("extension-only changes.", text)
        summary.unlink()
        self.compare(self.base, summary=summary)
        self.assertEqual(
            summary.read_text(encoding="utf-8"),
            "## Wire-compatibility report\n\n"
            "0 wire-breaking change(s), 0 extension-only change(s), 0 addition(s), "
            "2 message(s) untouched on the wire\n\n",
        )

    def test_usage(self) -> None:
        err = io.StringIO()
        with contextlib.redirect_stderr(err):
            status = check_wire_compat.main(["check_wire_compat.py", self.base])
        self.assertEqual(status, 2)
        self.assertIn(
            "Usage: check_wire_compat.py <base military.xml> <head military.xml>", err.getvalue()
        )

    def test_runs_as_a_script(self) -> None:
        with mock.patch.object(sys, "argv", ["check_wire_compat.py", self.base, self.base]):
            with mock.patch.dict(os.environ):
                os.environ.pop("GITHUB_STEP_SUMMARY", None)
                with contextlib.redirect_stdout(io.StringIO()):
                    with self.assertRaises(SystemExit) as exit_:
                        runpy.run_path(check_wire_compat.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 0)


if __name__ == "__main__":
    unittest.main()
