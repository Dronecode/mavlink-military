#!/usr/bin/env python3
"""Tests for check_example_digests.py, on a small stand-in repository. From
the repository root:

    python3 -m unittest discover --start-directory .github/scripts/validate_dialect/tests
"""

from __future__ import annotations

import contextlib
import hashlib
import io
import json
import runpy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_example_digests  # noqa: E402

UPSTREAM = (
    "https://raw.githubusercontent.com/mavlink/mavlink/"
    "87da370c02e40f6f9a2eacf1b162d7f07e640467/message_definitions/v1.0/common.xml"
)
COMMON = b"<mavlink></mavlink>\n"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


class StandInRepository:
    """A repository with a dialect, a schema, a manifest, a catalogue and one profile, whose
    digests all match until a test changes them."""

    def __init__(self, root: Path) -> None:
        self.root = root
        self.examples = root / "component_metadata" / "examples"
        self.examples.mkdir(parents=True)
        (root / "military.xml").write_bytes(b"<mavlink><messages/></mavlink>\n")
        (root / "component_metadata" / "payloads.schema.json").write_bytes(b"{}\n")
        self.profile = self.examples / "capability-profile.example.json"
        self.profile.write_bytes(b'{"profileId": "com.example.winch", "profileVersion": 1}\n')
        self.manifest = {
            "files": [
                self.entry("dialect", "https://example.org/defs/military.xml", "military.xml"),
                {"role": "included-dialect", "uri": UPSTREAM, "sha256": digest(COMMON)},
                self.entry(
                    "metadata-schema",
                    "https://example.org/defs/payloads.schema.json",
                    "component_metadata/payloads.schema.json",
                ),
            ]
        }
        self.write_manifest()
        self.ref = {
            "profileId": "com.example.winch",
            "profileVersion": 1,
            "sha256": digest(self.profile.read_bytes()),
        }
        self.write_catalogue()

    def entry(self, role: str, uri: str, path: str) -> dict:
        return {"role": role, "uri": uri, "sha256": digest((self.root / path).read_bytes())}

    def write_manifest(self) -> None:
        text = json.dumps(self.manifest, indent=2) + "\n"
        (self.examples / "definition-manifest.example.json").write_text(text, encoding="utf-8")

    def write_catalogue(self, manifest_digest: str | None = None) -> None:
        if manifest_digest is None:
            manifest = self.examples / "definition-manifest.example.json"
            manifest_digest = digest(manifest.read_bytes())
        catalogue = {
            "definitionManifest": {
                "uri": "https://example.org/manifest.json",
                "sha256": manifest_digest,
            },
            "payloads": [{"functions": [{"capabilityProfiles": [self.ref]}]}],
        }
        text = json.dumps(catalogue, indent=2) + "\n"
        (self.examples / "payloads.example.json").write_text(text, encoding="utf-8")


def upstream(uri: str) -> bytes:
    """The stand-in for the pinned upstream file; no test reaches the network."""
    assert uri == UPSTREAM, uri
    return COMMON


class CheckExampleDigestsTest(unittest.TestCase):
    def setUp(self) -> None:
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.repo = StandInRepository(Path(directory.name))

    def check(self, fetch=upstream) -> list[str]:
        with contextlib.redirect_stdout(io.StringIO()):
            return check_example_digests.check(self.repo.root, fetch)

    def test_matching_digests_pass(self) -> None:
        self.assertEqual(self.check(), [])

    def test_stale_dialect_digest_fails(self) -> None:
        (self.repo.root / "military.xml").write_bytes(b"<mavlink><enums/></mavlink>\n")
        problems = self.check()
        self.assertEqual(len(problems), 1)
        self.assertIn("dialect https://example.org/defs/military.xml", problems[0])

    def test_stale_manifest_digest_in_catalogue_fails(self) -> None:
        self.repo.write_catalogue(manifest_digest="0" * 64)
        problems = self.check()
        self.assertEqual(len(problems), 1)
        self.assertIn("definitionManifest", problems[0])

    def test_stale_profile_digest_fails(self) -> None:
        self.repo.profile.write_bytes(b'{"profileId": "com.example.winch", "profileVersion": 1}')
        problems = self.check()
        self.assertEqual(len(problems), 1)
        self.assertIn("capabilityProfileRef com.example.winch version 1", problems[0])

    def test_profile_without_an_example_fails(self) -> None:
        self.repo.ref["profileVersion"] = 2
        self.repo.write_catalogue()
        problems = self.check()
        self.assertEqual(len(problems), 1)
        self.assertIn("no profile example", problems[0])

    def test_two_examples_of_one_profile_fail(self) -> None:
        copy = self.repo.examples / "capability-profile-copy.example.json"
        copy.write_bytes(self.repo.profile.read_bytes())
        problems = self.check()
        self.assertEqual(len(problems), 1)
        self.assertIn("are both profile", problems[0])

    def test_changed_upstream_file_fails(self) -> None:
        problems = self.check(fetch=lambda uri: COMMON + b"<!-- changed -->\n")
        self.assertEqual(len(problems), 1)
        self.assertIn(UPSTREAM, problems[0])

    def test_unreachable_upstream_file_fails(self) -> None:
        def unreachable(uri: str) -> bytes:
            raise OSError("network unreachable")

        problems = self.check(fetch=unreachable)
        self.assertEqual(len(problems), 1)
        self.assertIn("network unreachable", problems[0])

    def test_uri_naming_no_repository_file_fails(self) -> None:
        self.repo.manifest["files"][0]["uri"] = "https://example.org/defs/missing.xml"
        self.repo.write_manifest()
        self.repo.write_catalogue()
        problems = self.check()
        self.assertEqual(len(problems), 1)
        self.assertIn("names 0 files", problems[0])

    def test_uri_naming_two_repository_files_fails(self) -> None:
        (self.repo.root / "payloads.schema.json").write_bytes(b"{}\n")
        problems = self.check()
        self.assertEqual(len(problems), 1)
        self.assertIn("names 2 files", problems[0])

    def test_unpinned_upstream_uri_is_read_from_the_repository(self) -> None:
        # Only a URI that pins a full commit is fetched; a branch name is not immutable.
        self.repo.manifest["files"][1]["uri"] = (
            "https://raw.githubusercontent.com/mavlink/mavlink/master/message_definitions/v1.0/common.xml"
        )
        self.repo.write_manifest()
        self.repo.write_catalogue()
        problems = self.check(fetch=lambda uri: self.fail(f"fetched {uri}"))
        self.assertEqual(len(problems), 1)
        self.assertIn("names 0 files", problems[0])

    def test_fetch_upstream_reads_the_response(self) -> None:
        response = mock.MagicMock()
        response.__enter__.return_value.read.return_value = COMMON
        urllib_request = check_example_digests.urllib.request
        with mock.patch.object(urllib_request, "urlopen", return_value=response) as urlopen:
            self.assertEqual(check_example_digests.fetch_upstream(UPSTREAM), COMMON)
        urlopen.assert_called_once_with(UPSTREAM, timeout=30)

    def test_main_exit_codes(self) -> None:
        root = str(self.repo.root)
        with (
            mock.patch.object(check_example_digests, "fetch_upstream", upstream),
            contextlib.redirect_stdout(io.StringIO()),
        ):
            self.assertEqual(check_example_digests.main(["check", root]), 0)
            self.repo.write_catalogue(manifest_digest="0" * 64)
            with contextlib.redirect_stderr(io.StringIO()) as err:
                self.assertEqual(check_example_digests.main(["check", root]), 1)
        self.assertIn("MISMATCH", err.getvalue())
        with contextlib.redirect_stderr(io.StringIO()) as err:
            self.assertEqual(check_example_digests.main(["check", root, "extra"]), 2)
        self.assertIn("Usage:", err.getvalue())

    def test_runs_as_a_script_from_the_repository_root(self) -> None:
        script = Path(check_example_digests.__file__)
        with (
            mock.patch.object(sys, "argv", [str(script), str(self.repo.root)]),
            mock.patch("urllib.request.urlopen", side_effect=OSError("offline")),
            contextlib.redirect_stdout(io.StringIO()),
            contextlib.redirect_stderr(io.StringIO()) as err,
            self.assertRaises(SystemExit) as exit_,
        ):
            runpy.run_path(str(script), run_name="__main__")
        self.assertEqual(exit_.exception.code, 1)
        self.assertIn("offline", err.getvalue())


if __name__ == "__main__":
    unittest.main()
