#!/usr/bin/env python3
"""Tests for archive.py. From the repository root:

python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_archive.py'
"""

from __future__ import annotations

import gzip
import hashlib
import io
import sys
import tarfile
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import archive  # noqa: E402

FILES = {"b/two.txt": b"two\n", "a.txt": b"one\n", "b/c/three.txt": b"three\n"}


class ArchiveTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.tmp = Path(tmp.name)

    def test_the_same_files_give_the_same_bytes(self) -> None:
        first = archive.write(self.tmp / "1.tar.gz", "top", FILES, 1700000000)
        second = archive.write(
            self.tmp / "2.tar.gz", "top", dict(reversed(list(FILES.items()))), 1700000000
        )
        self.assertEqual((self.tmp / "1.tar.gz").read_bytes(), (self.tmp / "2.tar.gz").read_bytes())
        self.assertEqual(first, second)
        self.assertEqual(first["files"], 3)
        raw = gzip.decompress((self.tmp / "1.tar.gz").read_bytes())
        self.assertEqual(first["tar_sha256"], hashlib.sha256(raw).hexdigest())
        header = (self.tmp / "1.tar.gz").read_bytes()[:10]
        self.assertEqual(header[3], 0)  # no file name in the gzip header
        self.assertEqual(header[4:8], b"\0\0\0\0")  # gzip mtime 0

    def test_entries_are_sorted_normalised_ustar(self) -> None:
        archive.write(self.tmp / "a.tar.gz", "top", FILES, 1700000000)
        with tarfile.open(self.tmp / "a.tar.gz") as tar:
            members = tar.getmembers()
        self.assertEqual(
            [m.name for m in members],
            ["top", "top/a.txt", "top/b", "top/b/c", "top/b/c/three.txt", "top/b/two.txt"],
        )
        for m in members:
            self.assertEqual((m.mtime, m.uid, m.gid, m.uname, m.gname), (1700000000, 0, 0, "", ""))
            self.assertEqual(m.mode, 0o755 if m.isdir() else 0o644)
        raw = gzip.decompress((self.tmp / "a.tar.gz").read_bytes())
        self.assertEqual(raw[257:263], b"ustar\0")

    def test_read_returns_the_files(self) -> None:
        archive.write(self.tmp / "a.tar.gz", "top", FILES, 0)
        self.assertEqual(archive.read(self.tmp / "a.tar.gz", "top"), FILES)

    def test_a_path_that_is_not_plain_is_refused(self) -> None:
        for name in ("", "/abs", "a//b", "a/../b", "./a", "a/"):
            with self.subTest(name=name), self.assertRaises(archive.ArchiveError) as caught:
                archive.write(self.tmp / "x.tar.gz", "top", {name: b""}, 0)
            self.assertIn("is not a plain relative path", str(caught.exception))

    def test_a_name_ustar_cannot_hold_is_refused(self) -> None:
        with self.assertRaises(archive.ArchiveError) as caught:
            archive.write(self.tmp / "x.tar.gz", "top", {"n" * 200: b""}, 0)
        self.assertIn("top/" + "n" * 200, str(caught.exception))

    def write_raw(self, name: str, *members: tarfile.TarInfo) -> Path:
        path = self.tmp / name
        with tarfile.open(path, "w:gz") as tar:
            for member in members:
                tar.addfile(member, io.BytesIO(b"") if member.isfile() else None)
        return path

    def test_read_refuses_a_member_outside_the_top(self) -> None:
        for name in ("other/a.txt", "/top/a.txt", "top/../a.txt"):
            with self.subTest(name=name):
                path = self.write_raw("bad.tar.gz", tarfile.TarInfo(name))
                with self.assertRaises(archive.ArchiveError) as caught:
                    archive.read(path, "top")
                self.assertIn("is not under top/", str(caught.exception))

    def test_read_refuses_a_link(self) -> None:
        link = tarfile.TarInfo("top/link")
        link.type, link.linkname = tarfile.SYMTYPE, "/etc/passwd"
        path = self.write_raw("link.tar.gz", link)
        with self.assertRaises(archive.ArchiveError) as caught:
            archive.read(path, "top")
        self.assertIn("is neither a file nor a directory", str(caught.exception))


if __name__ == "__main__":
    unittest.main()
