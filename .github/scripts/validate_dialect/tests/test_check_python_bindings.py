#!/usr/bin/env python3
"""Tests for check_python_bindings.py, with stand-in generated modules. From
the repository root:

    python3 -m unittest discover --start-directory .github/scripts/validate_dialect/tests
"""

from __future__ import annotations

import contextlib
import io
import runpy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_python_bindings  # noqa: E402

DIALECT = """<?xml version="1.0"?>
<mavlink>
  <messages>
    <message id="53000" name="TEST_TRACK"><description>Track.</description></message>
    <message id="53001" name="TEST_STATUS"><description>Status.</description></message>
  </messages>
</mavlink>
"""


class CheckPythonBindingsTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.dir = Path(tmp.name)
        self.dialect = self.write("military.xml", DIALECT)

    def write(self, name: str, text: str) -> str:
        path = self.dir / name
        path.write_text(text, encoding="utf-8")
        return str(path)

    def run_main(self, *args: str) -> tuple[int, str, str]:
        out, err = io.StringIO(), io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            status = check_python_bindings.main(["check_python_bindings.py", *args])
        return status, out.getvalue(), err.getvalue()

    def test_every_dialect_message_in_the_map_passes(self) -> None:
        # 0 stands in for the messages that the dialect's includes bring.
        module = self.write("military.py", "mavlink_map = {0: None, 53000: None, 53001: None}\n")
        status, out, err = self.run_main(module, self.dialect)
        self.assertEqual((status, err), (0, ""))
        self.assertEqual(out, "3 messages in the generated map, all 2 dialect messages present\n")

    def test_a_message_missing_from_the_map_fails(self) -> None:
        module = self.write("military.py", "mavlink_map = {53000: None}\n")
        status, out, err = self.run_main(module, self.dialect)
        self.assertEqual((status, out), (1, ""))
        self.assertEqual(err, "dialect messages missing from the generated map: [53001]\n")

    def test_a_module_that_does_not_load_fails(self) -> None:
        module = self.write("military.py", "import module_that_does_not_exist\n")
        with self.assertRaises(ModuleNotFoundError):
            self.run_main(module, self.dialect)

    def test_a_module_without_a_map_fails(self) -> None:
        module = self.write("military.py", "MAVLINK_MAP = {}\n")
        with self.assertRaises(AttributeError):
            self.run_main(module, self.dialect)

    def test_the_module_loads_from_any_file_name(self) -> None:
        module = self.write("bindings.txt", "mavlink_map = {53000: None, 53001: None}\n")
        self.assertEqual(self.run_main(module, self.dialect)[0], 0)
        self.assertNotIn("bindings", sys.modules)

    def test_usage(self) -> None:
        status, out, err = self.run_main(self.dialect)
        self.assertEqual((status, out), (2, ""))
        self.assertIn("Usage: check_python_bindings.py <generated module> <military.xml>", err)

    def test_runs_as_a_script(self) -> None:
        module = self.write("military.py", "mavlink_map = {53000: None, 53001: None}\n")
        argv = ["check_python_bindings.py", module, self.dialect]
        with mock.patch.object(sys, "argv", argv), contextlib.redirect_stdout(io.StringIO()):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(check_python_bindings.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 0)


if __name__ == "__main__":
    unittest.main()
