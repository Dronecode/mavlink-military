#!/usr/bin/env python3
"""Tests for fetch_release.sh, with release archives served from a temporary
directory. Needs curl. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/workflow_lint/tests
"""

from __future__ import annotations

import functools
import hashlib
import http.server
import io
import os
import subprocess
import tarfile
import tempfile
import threading
import unittest
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "fetch_release.sh"
TOOL = b"#!/bin/sh\necho tool 1.0\n"
WRONG_SHA = "0" * 64


class QuietHandler(http.server.SimpleHTTPRequestHandler):
    def log_message(self, *args: object) -> None:
        pass


class FetchReleaseTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.dir = Path(tmp.name)
        for sub in ("srv", "tmp"):
            (self.dir / sub).mkdir()
        handler = functools.partial(QuietHandler, directory=str(self.dir / "srv"))
        self.server = http.server.ThreadingHTTPServer(("127.0.0.1", 0), handler)
        threading.Thread(target=self.server.serve_forever, daemon=True).start()
        self.addCleanup(self.server.server_close)
        self.addCleanup(self.server.shutdown)
        self.base = f"http://127.0.0.1:{self.server.server_address[1]}/"
        self.dest = self.dir / "dest"

    def release(self, name: str, mode: str) -> str:
        """Serve an archive holding tool-v1/tool, as the shellcheck release
        lays its binary out, and return the archive's SHA-256."""
        path = self.dir / "srv" / name
        with tarfile.open(path, mode) as tar:
            info = tarfile.TarInfo("tool-v1/tool")
            info.size = len(TOOL)
            info.mode = 0o755
            tar.addfile(info, io.BytesIO(TOOL))
        return hashlib.sha256(path.read_bytes()).hexdigest()

    def fetch(self, *args: str) -> subprocess.CompletedProcess[str]:
        env = dict(os.environ, TMPDIR=str(self.dir / "tmp"))
        return subprocess.run(["sh", str(SCRIPT), *args], env=env, capture_output=True, text=True)

    def test_a_gzip_archive_with_its_checksum_is_extracted(self) -> None:
        url = self.base + "tool.tar.gz"
        result = self.fetch(url, self.release("tool.tar.gz", "w:gz"), str(self.dest))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout, f"{url}: SHA-256 OK, extracted into {self.dest}\n")
        tool = self.dest / "tool-v1" / "tool"
        self.assertEqual(tool.read_bytes(), TOOL)
        self.assertTrue(os.access(tool, os.X_OK))

    def test_an_xz_archive_is_extracted_too(self) -> None:
        url = self.base + "tool.tar.xz"
        result = self.fetch(url, self.release("tool.tar.xz", "w:xz"), str(self.dest))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual((self.dest / "tool-v1" / "tool").read_bytes(), TOOL)

    def test_a_checksum_mismatch_extracts_nothing(self) -> None:
        self.release("tool.tar.gz", "w:gz")
        url = self.base + "tool.tar.gz"
        result = self.fetch(url, WRONG_SHA, str(self.dest))
        self.assertEqual(result.returncode, 1)
        self.assertIn(f"error: {url} does not have SHA-256 {WRONG_SHA}\n", result.stderr)
        self.assertFalse(self.dest.exists())

    def test_a_missing_release_fails(self) -> None:
        result = self.fetch(self.base + "missing.tar.gz", WRONG_SHA, str(self.dest))
        # 22 is curl's exit code for an HTTP error under --fail.
        self.assertEqual(result.returncode, 22)
        self.assertIn("404", result.stderr)
        self.assertFalse(self.dest.exists())

    def test_the_download_is_removed_either_way(self) -> None:
        url = self.base + "tool.tar.gz"
        self.fetch(url, self.release("tool.tar.gz", "w:gz"), str(self.dest))
        self.fetch(url, WRONG_SHA, str(self.dest))
        self.assertEqual(list((self.dir / "tmp").iterdir()), [])

    def test_usage(self) -> None:
        result = self.fetch("only", "two")
        self.assertEqual(result.returncode, 1)
        self.assertIn("usage:", result.stderr)


if __name__ == "__main__":
    unittest.main()
