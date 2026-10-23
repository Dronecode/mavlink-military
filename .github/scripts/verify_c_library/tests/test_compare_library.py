"""Tests for compare_library.py, on small trees in a temporary directory.
From the repository root:

python3 -m unittest discover --start-directory .github/scripts/verify_c_library/tests
"""

from __future__ import annotations

import contextlib
import importlib
import io
import os
import runpy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
compare = importlib.import_module("compare_library")

VERSION = (
    "#pragma once\n\n"
    '#define MAVLINK_BUILD_DATE "{date}"\n'
    '#define MAVLINK_WIRE_PROTOCOL_VERSION "2.0"\n'
)
HEADER = "#pragma once\nstatic inline int mavlink_answer(void) { return 42; }\n"


class CompareTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.out = Path(tmp.name) / "out"
        self.library = Path(tmp.name) / "library"
        # A regeneration on one day, and the library a publish wrote on another.
        self.write(self.out, VERSION.format(date="Fri Oct 23 2026"))
        self.write(self.library, VERSION.format(date="Mon Oct 12 2026"))
        (self.library / "README.md").write_text("The library.\n", encoding="utf-8")
        (self.library / "LICENSE").write_text("MIT\n", encoding="utf-8")
        (self.library / ".git").mkdir()
        (self.library / ".git" / "HEAD").write_text("ref: refs/heads/main\n", encoding="utf-8")
        patcher = mock.patch.dict(os.environ)
        patcher.start()
        self.addCleanup(patcher.stop)
        os.environ.pop("GITHUB_ACTIONS", None)

    @staticmethod
    def write(root: Path, version: str) -> None:
        (root / "military").mkdir(parents=True)
        (root / "military" / "version.h").write_text(version, encoding="utf-8")
        (root / "mavlink_helpers.h").write_text(HEADER, encoding="utf-8")

    def run_main(self, argv: list[str] | None = None) -> tuple[int, str, str]:
        out, err = io.StringIO(), io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            code = compare.main(argv or [str(self.out), str(self.library)])
        return code, out.getvalue(), err.getvalue()

    def assert_differs(self, *lines: str) -> None:
        code, out, err = self.run_main()
        self.assertEqual(code, 1, out)
        self.assertEqual(out.splitlines(), list(lines))
        self.assertIn(f"differs from a regeneration at main in {len(lines)} path(s)", err)

    def edit(self, relative: str, old: str, new: str) -> None:
        path = self.library / relative
        path.write_text(path.read_text(encoding="utf-8").replace(old, new), encoding="utf-8")


class EqualTest(CompareTest):
    def test_only_the_date_the_readme_the_license_and_git_may_differ(self) -> None:
        code, out, err = self.run_main()
        self.assertEqual((code, err), (0, ""))
        self.assertIn("equals the regeneration, apart from the build date", out)


class DifferTest(CompareTest):
    def test_anything_after_the_date_differs(self) -> None:
        for tail in (" \\", " /* more */", "x"):
            with self.subTest(tail=tail):
                self.edit("military/version.h", '2026"\n', f'2026"{tail}\n')
                self.assert_differs("differs: military/version.h")
                self.edit("military/version.h", f'2026"{tail}\n', '2026"\n')

    def test_a_second_date_line_differs(self) -> None:
        line = '#define MAVLINK_BUILD_DATE "Mon Oct 12 2026"\n'
        self.edit("military/version.h", line, line + line)
        self.assert_differs("differs: military/version.h")

    def test_a_date_line_in_another_header_differs(self) -> None:
        self.edit(
            "mavlink_helpers.h", "#pragma once\n", '#pragma once\n#define MAVLINK_BUILD_DATE ""\n'
        )
        self.assert_differs("differs: mavlink_helpers.h")

    def test_an_edit_to_a_header_differs(self) -> None:
        self.edit("mavlink_helpers.h", "42", "41")
        self.assert_differs("differs: mavlink_helpers.h")

    def test_a_readme_or_license_below_the_root_differs(self) -> None:
        (self.library / "military" / "README.md").write_text("Note.\n", encoding="utf-8")
        (self.library / "military" / "LICENSE").write_text("Other.\n", encoding="utf-8")
        self.assert_differs(
            "only in the library: military/LICENSE", "only in the library: military/README.md"
        )

    def test_a_file_missing_from_either_tree_differs(self) -> None:
        (self.out / "military" / "extra.h").write_text(HEADER, encoding="utf-8")
        (self.library / "extra.h").write_text(HEADER, encoding="utf-8")
        self.assert_differs(
            "only in the regeneration: military/extra.h", "only in the library: extra.h"
        )

    def test_a_link_or_other_entry_differs(self) -> None:
        (self.library / "mavlink_helpers.h").unlink()
        (self.library / "mavlink_helpers.h").symlink_to(self.out / "mavlink_helpers.h")
        (self.library / "linked").symlink_to(self.library / "military", target_is_directory=True)
        os.mkfifo(self.library / "fifo")
        self.assert_differs(
            "not a regular file: fifo",
            "not a regular file: linked",
            "not a regular file: mavlink_helpers.h",
            "only in the regeneration: mavlink_helpers.h",
        )

    def test_a_git_directory_below_the_root_differs(self) -> None:
        (self.library / "military" / ".git").mkdir()
        (self.library / "military" / ".git" / "HEAD").write_text("x\n", encoding="utf-8")
        self.assert_differs("only in the library: military/.git/HEAD")

    def test_no_name_in_the_library_reads_as_a_workflow_command(self) -> None:
        (self.library / "::warning::x\n::error::y%").write_text(HEADER, encoding="utf-8")
        self.assert_differs("only in the library: ::warning::x%0A::error::y%25")

    def test_a_difference_is_an_annotation_on_github(self) -> None:
        os.environ["GITHUB_ACTIONS"] = "true"
        self.edit("mavlink_helpers.h", "42", "41")
        code, out, _ = self.run_main()
        self.assertEqual(code, 1)
        self.assertIn("::error title=C library::the library differs", out)


class UsageTest(CompareTest):
    def test_usage_errors(self) -> None:
        for argv in ([str(self.out)], [str(self.out), str(self.library / "README.md")]):
            with self.subTest(argv=argv):
                code, _, err = self.run_main(argv)
                self.assertEqual(code, 2)
                self.assertIn("usage:", err)

    def test_runs_as_a_script(self) -> None:
        with (
            mock.patch.object(sys, "argv", ["compare_library.py"]),
            contextlib.redirect_stderr(io.StringIO()),
            self.assertRaises(SystemExit) as exit_,
        ):
            runpy.run_path(compare.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
