#!/usr/bin/env python3
"""Tests for release_tag.py, with a stand-in gh and the real gpg.
From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/release/tests --pattern 'test_release_tag.py'
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

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
sys.path.insert(0, str(HERE))
import release_tag as rt  # noqa: E402
from fake_gh import FakeGh  # noqa: E402

REPO = "Dronecode/mavlink-military"
TAG_SHA = "a" * 40
ENV = {"GITHUB_REPOSITORY": REPO, "GITHUB_REF_NAME": "v1.0.0", "GITHUB_ACTOR": "maintainer"}
# A detached signature that a throwaway ed25519 key, 4D2E041DF55658B6, made over
# a tag's text; gpg reads its key ID without the key.
KEY = "4D2E041DF55658B6"
SIGNATURE = """-----BEGIN PGP SIGNATURE-----

iJEEABYKADkWIQRK4BeQDmzZ9r2yn8pNLgQd9VZYtgUCauEXnRsUgAAAAAAEAA5t
YW51MiwyLjUrMS4xMiwwLDMACgkQTS4EHfVWWLaNSwEAkTpDC5jv6BY20YnvhqFD
x1cB7Wi/b0jO8eV4xeDUENYBANQ+d9QxDZ0OEzVepytXTMzMCSZ6u7OYqEfvndvY
RdYL
=VwJX
-----END PGP SIGNATURE-----
"""


class TagTest(unittest.TestCase):
    def setUp(self) -> None:
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.gh = FakeGh(Path(tmp.name))
        patcher = mock.patch.dict(os.environ, {**self.gh.env(), **ENV})
        patcher.start()
        self.addCleanup(patcher.stop)

    def answer(self, ref_type: str = "tag", verification: dict | None = None,
               keys: list | None = None) -> None:  # fmt: skip
        self.gh.on("api", f"repos/{REPO}/git/ref/tags/v1.0.0",
                   stdout={"object": {"type": ref_type, "sha": TAG_SHA}})  # fmt: skip
        if verification is None:
            verification = {"verified": True, "reason": "valid", "signature": SIGNATURE}
        self.gh.on("api", f"repos/{REPO}/git/tags/{TAG_SHA}", stdout={"verification": verification})
        if keys is None:
            keys = [{"key_id": "1111111111111111", "subkeys": [{"key_id": KEY.lower()}]}]
        self.gh.on("api", "users/maintainer/gpg_keys?per_page=100", stdout=keys)

    def main(self, *args: str) -> tuple[int, str]:
        out = io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(io.StringIO()):
            code = rt.main(["release_tag.py", *args])
        return code, out.getvalue()

    def test_a_tag_signed_by_its_pusher_passes(self) -> None:
        for keys in (
            [{"key_id": "1111111111111111", "subkeys": [{"key_id": KEY.lower()}]}],
            [{"key_id": KEY, "subkeys": None}],
        ):
            with self.subTest(keys=keys):
                self.gh.responses.clear()
                self.answer(keys=keys)
                code, out = self.main()
                self.assertEqual(code, 0, out)
                self.assertIn(f"v1.0.0 is signed with GPG key {KEY} of maintainer", out)

    def test_shortfalls(self) -> None:
        ssh = "-----BEGIN SSH SIGNATURE-----\nAAAA\n-----END SSH SIGNATURE-----\n"
        for answer, message in (
            ({"ref_type": "commit"}, "v1.0.0 is a lightweight tag"),
            ({"verification": {"verified": False, "reason": "unsigned", "signature": None}},
             "GitHub does not verify the signature of v1.0.0 (unsigned)"),
            ({"verification": {}}, "GitHub does not verify the signature of v1.0.0 (None)"),
            ({"verification": {"verified": True, "reason": "valid", "signature": ssh}},
             "v1.0.0 is not signed with GPG"),
            ({"verification": {"verified": True, "reason": "valid"}}, "v1.0.0 is not signed with GPG"),
            ({"verification": {"verified": True, "reason": "valid", "signature": "-----BEGIN PGP SIGNATURE-----\n\nnot a packet\n"}},
             "gpg reads no single signing key from the tag's signature: []"),
            ({"keys": [{"key_id": "1111111111111111", "subkeys": []}]},
             f"v1.0.0 is signed with key {KEY}, which is not a GPG key of maintainer"),
            ({"keys": []}, f"v1.0.0 is signed with key {KEY}, which is not a GPG key of maintainer"),
        ):  # fmt: skip
            with self.subTest(message=message):
                self.gh.responses.clear()
                self.answer(**answer)
                code, out = self.main()
                self.assertEqual(code, 1)
                self.assertIn(message, out)

    def test_a_failed_read_fails(self) -> None:
        code, out = self.main()
        self.assertEqual(code, 1)
        self.assertIn("::error title=release tag::gh api", out)

    def test_usage_and_script(self) -> None:
        self.assertEqual(self.main("extra")[0], 2)
        with mock.patch.object(
            sys, "argv", ["release_tag.py", "x"]
        ), contextlib.redirect_stderr(io.StringIO()):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(rt.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
