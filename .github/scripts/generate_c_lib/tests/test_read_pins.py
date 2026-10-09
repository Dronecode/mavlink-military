#!/usr/bin/env python3
"""Tests for read_pins.sh. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/generate_c_lib/tests
"""

from __future__ import annotations

import subprocess
import tempfile
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "read_pins.sh"
PINS = Path(__file__).resolve().parents[3] / "mavlink-pins.env"
MAVLINK = "1" * 40
PYMAVLINK = "2" * 40


class ReadPinsTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.pins = Path(tmp.name) / "mavlink-pins.env"

    def read(self, text: str | None = None, args: list[str] | None = None):
        if text is not None:
            self.pins.write_text(text, encoding="utf-8")
        if args is None:
            args = [str(self.pins)]
        return subprocess.run(["sh", str(SCRIPT), *args], capture_output=True, text=True)

    def test_prints_both_pins_for_github_output(self) -> None:
        result = self.read(f"# comment\nMAVLINK_REF={MAVLINK}\nPYMAVLINK_REF={PYMAVLINK}\n")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout, f"mavlink={MAVLINK}\npymavlink={PYMAVLINK}\n")

    def test_the_repository_pins_are_valid(self) -> None:
        result = self.read(args=[str(PINS)])
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertRegex(result.stdout, r"^mavlink=[0-9a-f]{40}\npymavlink=[0-9a-f]{40}\n$")

    def test_a_short_sha_is_rejected(self) -> None:
        result = self.read(f"MAVLINK_REF=87da370\nPYMAVLINK_REF={PYMAVLINK}\n")
        self.assertEqual(result.returncode, 1)
        self.assertEqual(result.stdout, "")
        self.assertIn(
            "MAVLINK_REF must be set once, to a full 40-character commit SHA", result.stderr
        )

    def test_a_missing_pin_is_rejected(self) -> None:
        result = self.read(f"MAVLINK_REF={MAVLINK}\n")
        self.assertEqual(result.returncode, 1)
        self.assertIn("PYMAVLINK_REF must be set once", result.stderr)

    def test_a_pin_set_twice_is_rejected(self) -> None:
        result = self.read(
            f"MAVLINK_REF={MAVLINK}\nMAVLINK_REF={PYMAVLINK}\nPYMAVLINK_REF={PYMAVLINK}\n"
        )
        self.assertEqual(result.returncode, 1)
        self.assertIn("MAVLINK_REF must be set once", result.stderr)

    def test_a_missing_file_fails(self) -> None:
        result = self.read(args=[str(self.pins)])
        self.assertNotEqual(result.returncode, 0)

    def test_usage(self) -> None:
        result = self.read(args=[])
        self.assertEqual(result.returncode, 1)
        self.assertIn("usage:", result.stderr)


if __name__ == "__main__":
    unittest.main()
