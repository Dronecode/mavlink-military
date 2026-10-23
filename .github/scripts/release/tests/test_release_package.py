#!/usr/bin/env python3
"""Tests for release_package.py. They run the real generator, so MAVLINK_DIR
and PYMAVLINK_DIR must name checkouts at the pins in .github/mavlink-pins.env
(the second a clean one, in a directory named pymavlink), lxml must be
installed and gcc on PATH. From the repository root:

    MAVLINK_DIR=... PYMAVLINK_DIR=... python3 -m unittest discover \\
        --start-directory .github/scripts/release/tests --pattern 'test_release_package.py'
"""

from __future__ import annotations

import contextlib
import copy
import hashlib
import io
import json
import os
import runpy
import shutil
import subprocess
import sys
import tarfile
import tempfile
import unittest
import xml.etree.ElementTree as ET
from pathlib import Path
from unittest import mock

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
import archive  # noqa: E402
import release_package as rp  # noqa: E402

REPO = HERE.parents[3]
MAVLINK = Path(os.environ.get("MAVLINK_DIR", "mavlink")).resolve()
PYMAVLINK = Path(os.environ.get("PYMAVLINK_DIR", "pymavlink")).resolve()
EPOCH = 1700000000  # Tue Nov 14 2023, 22:13:20 UTC


def git(cwd: Path, *args: str) -> str:
    return subprocess.run(
        ["git", "-c", "advice.detachedHead=false", "-C", str(cwd), *args],
        check=True, capture_output=True, text=True,
    ).stdout.strip()  # fmt: skip


@contextlib.contextmanager
def inside(path: Path):
    before = os.getcwd()
    os.chdir(path)
    try:
        yield
    finally:
        os.chdir(before)


class Fixture(unittest.TestCase):
    """A one-commit repository with this checkout's dialect, IDMAPPING.md and LICENSE."""

    @classmethod
    def setUpClass(cls) -> None:
        tmp = tempfile.TemporaryDirectory()
        cls.addClassCleanup(tmp.cleanup)
        cls.tmp = Path(tmp.name)
        cls.repo = cls.tmp / "repo"
        cls.repo.mkdir()
        for name in ("military.xml", "IDMAPPING.md", "LICENSE"):
            shutil.copyfile(REPO / name, cls.repo / name)
        git(cls.repo, "init", "-q")
        git(cls.repo, "add", "military.xml", "IDMAPPING.md", "LICENSE")
        git(
            cls.repo,
            "-c",
            "user.name=Test",
            "-c",
            "user.email=test@example.invalid",
            "commit",
            "-q",
            "-m",
            "fixture",
        )
        cls.plan = {
            "schema": 1,
            "version": "9.9.9",
            "tag": "v9.9.9",
            "commit": git(cls.repo, "rev-parse", "HEAD"),
            "tree": git(cls.repo, "rev-parse", "HEAD^{tree}"),
            "source_date_epoch": EPOCH,
            "repository": "example/mavlink-military",
            "pins": {
                "mavlink": git(MAVLINK, "rev-parse", "HEAD"),
                "pymavlink": git(PYMAVLINK, "rev-parse", "HEAD"),
            },
        }
        cls.lmap = json.loads(rp.LICENSE_MAP.read_text(encoding="utf-8"))

    def build(self, out: Path, plan: dict | None = None) -> dict:
        with inside(self.repo):
            return rp.build(plan or self.plan, out, MAVLINK, PYMAVLINK)


class BuildTest(Fixture):
    @classmethod
    def setUpClass(cls) -> None:
        super().setUpClass()
        cls.out = cls.tmp / "out"
        with inside(cls.repo):
            cls.result = rp.build(cls.plan, cls.out, MAVLINK, PYMAVLINK)

    def members(self, kind: str) -> dict[str, bytes]:
        return archive.read(self.out / f"mavlink-m-9.9.9-{kind}.tar.gz", f"mavlink-m-9.9.9-{kind}")

    def test_the_package_files_and_their_checksums(self) -> None:
        names = [
            "mavlink-m-9.9.9-c.tar.gz",
            "mavlink-m-9.9.9-definitions.tar.gz",
            "mavlink-m-9.9.9-manifest.json",
            "mavlink-m-9.9.9-military.xml",
            "mavlink-m-9.9.9-python.tar.gz",
            "mavlink-m-9.9.9-wire.json",
        ]
        self.assertEqual(self.result["files"], names)
        sums = (self.out / "SHA256SUMS").read_text(encoding="ascii")
        self.assertEqual(
            sums,
            "".join(
                f"{hashlib.sha256((self.out / n).read_bytes()).hexdigest()}  {n}\n" for n in names
            ),
        )
        self.assertEqual(self.result["sums_sha256"], hashlib.sha256(sums.encode()).hexdigest())
        self.assertEqual(
            sorted(p.name for p in (self.out / "leg").iterdir()), ["checks.json", "toolchain.json"]
        )

    def test_a_second_build_gives_the_same_bytes(self) -> None:
        again = self.tmp / "again"
        with mock.patch.dict(os.environ, {"TZ": "Pacific/Kiritimati"}):
            self.build(again)
        self.assertEqual(
            (again / "SHA256SUMS").read_bytes(), (self.out / "SHA256SUMS").read_bytes()
        )

    def test_the_definitions_are_the_git_objects(self) -> None:
        files = self.members("definitions")
        self.assertEqual(
            files["message_definitions/v1.0/military.xml"], (REPO / "military.xml").read_bytes()
        )
        common = subprocess.run(
            ["git", "-C", str(MAVLINK), "show", "HEAD:message_definitions/v1.0/common.xml"],
            check=True, capture_output=True,
        ).stdout  # fmt: skip
        self.assertEqual(files["message_definitions/v1.0/common.xml"], common)
        self.assertEqual(
            files["message_definitions/v1.0/common.xml"],
            self.members("c")["message_definitions/common.xml"],
        )
        self.assertEqual(
            (self.out / "mavlink-m-9.9.9-military.xml").read_bytes(),
            (REPO / "military.xml").read_bytes(),
        )

    def test_the_build_date_is_the_commit_date(self) -> None:
        files = self.members("c")
        dated = [n for n in files if n.endswith("/version.h")]
        self.assertEqual(len(dated), 4)
        for name in dated:
            self.assertIn(b'#define MAVLINK_BUILD_DATE "Tue Nov 14 2023"', files[name])

    def test_every_archive_carries_its_licenses(self) -> None:
        grant = rp.license_terms(self.lmap, MAVLINK, PYMAVLINK, self.plan["pins"])
        expected = {
            "definitions": ["MIT"],
            "c": ["BSD-3-Clause", "LicenseRef-MAVLink-generated-code", "MIT"],
            "python": ["LicenseRef-MAVLink-generated-code", "MIT"],
        }
        for kind, ids in expected.items():
            files = self.members(kind)
            self.assertEqual(sorted(n[9:-4] for n in files if n.startswith("LICENSES/")), ids, kind)
            self.assertEqual(files["LICENSE"], (REPO / "LICENSE").read_bytes())
            self.assertIn(b"Copyright (c) 2026 Dronecode Project, Inc", files["REUSE.toml"])
            if "LicenseRef-MAVLink-generated-code" in ids:
                self.assertEqual(
                    files["LICENSES/LicenseRef-MAVLink-generated-code.txt"], grant.encode()
                )
                self.assertIn(b"pymavlink, is not\nincluded", files["NOTICE"])
            else:
                self.assertNotIn(b"generator's grant", files["NOTICE"])
        self.assertIn(b'path = ["military/**"', self.members("c")["REUSE.toml"])
        self.assertNotIn(b"common.xml", self.members("python")["NOTICE"])

    def test_the_wire_table_and_the_checks(self) -> None:
        table = json.loads((self.out / "mavlink-m-9.9.9-wire.json").read_text())
        messages = table["messages"]
        self.assertEqual(len(messages), self.result["checks"]["crc_rows"])
        self.assertEqual(messages, sorted(messages, key=lambda m: m["id"]))
        dialect = [m for m in messages if not m["upstream"]]
        self.assertEqual({m["source"] for m in dialect}, {"military.xml"})
        self.assertEqual(
            {m["source"] for m in messages if m["upstream"]},
            {"common.xml", "standard.xml", "minimal.xml"},
        )
        heartbeat = next(m for m in messages if m["name"] == "HEARTBEAT")
        self.assertEqual((heartbeat["id"], heartbeat["source"]), (0, "minimal.xml"))
        for m in messages:
            self.assertTrue({"flags", "target_system_offset", "target_component_offset"} <= set(m))
        self.assertTrue(table["commands"])
        self.assertTrue(table["enums"])
        for enum in table["enums"]:
            values = [(e["value"], e["name"]) for e in enum["entries"]]
            self.assertEqual(values, sorted(values), enum["name"])
        checks = self.result["checks"]
        self.assertEqual(checks["c_static_assertions"], 4 * len(dialect))
        self.assertEqual(checks["python_classes"], checks["crc_rows"])
        self.assertEqual(checks["generation_runs_identical"], 2)
        self.assertEqual(checks["fixed_headers_identical"], len(rp.FIXED_HEADERS))
        self.assertEqual(checks["schema_valid_files"], 4)

    def test_the_c_facts_are_measured(self) -> None:
        # The values the compiled probe prints at the pinned generator: military.xml's
        # <version> becomes MAVLINK_VERSION, and the 32-bit system ID extension makes the
        # message struct 298 bytes and the largest frame 287 (255 payload, 12 header and
        # checksum, 7 extension and 13 signature bytes).
        table = json.loads((self.out / "mavlink-m-9.9.9-wire.json").read_text())
        version = int(ET.fromstring((REPO / "military.xml").read_bytes()).findtext("version"))
        self.assertEqual(
            table["c"],
            {"MAVLINK_VERSION": version, "sizeof_mavlink_message_t": 298,
             "MAVLINK_MAX_PACKET_LEN": 287, "id32_flags": True},
        )  # fmt: skip
        self.assertEqual(table["heartbeat_mavlink_version"], 3)

    def test_the_manifest_describes_every_member(self) -> None:
        manifest = json.loads((self.out / "mavlink-m-9.9.9-manifest.json").read_text())
        python = manifest["archives"]["mavlink-m-9.9.9-python.tar.gz"]
        by_path = {f["path"]: f for f in python["files"]}
        self.assertEqual(by_path["military.py"]["license"], "LicenseRef-MAVLink-generated-code")
        self.assertEqual(by_path["LICENSE"], {
            "path": "LICENSE", "covered": False, "size": len((REPO / "LICENSE").read_bytes()),
            "sha256": hashlib.sha256((REPO / "LICENSE").read_bytes()).hexdigest()})  # fmt: skip
        tar = tarfile.open(self.out / "mavlink-m-9.9.9-python.tar.gz")
        raw = gzip_payload(self.out / "mavlink-m-9.9.9-python.tar.gz")
        self.assertEqual(python["tar_sha256"], hashlib.sha256(raw).hexdigest())
        tar.close()
        common = {
            f["path"]: f
            for f in manifest["archives"]["mavlink-m-9.9.9-definitions.tar.gz"]["files"]
        }
        self.assertEqual(
            common["message_definitions/v1.0/common.xml"]["copyright"], ["NOASSERTION"]
        )
        self.assertEqual(manifest["commands"], list(rp.COMMANDS))
        self.assertEqual(manifest["lxml"], "6.1.3")
        self.assertEqual((manifest["generator"], manifest["previous"]), (None, None))
        for name in ("mavlink-m-9.9.9-military.xml", "mavlink-m-9.9.9-wire.json"):
            self.assertEqual(
                manifest["files"][name], hashlib.sha256((self.out / name).read_bytes()).hexdigest()
            )

    def test_the_c_notice_carries_the_bsd_notice(self) -> None:
        notice = self.members("c")["NOTICE"].decode("utf-8")
        self.assertIn(self.lmap["copyright"]["kth"], notice)
        self.assertIn("(clause 2)", notice)
        self.assertNotIn("Kungliga", self.members("python")["NOTICE"].decode("utf-8"))

    def test_the_package_does_not_depend_on_the_mode(self) -> None:
        # What a rehearsal builds is what a release publishes: the build reads neither the
        # plan's mode nor its publish flag.
        for mode, publish in (("release", True), ("rehearsal", False)):
            with self.subTest(mode=mode):
                out = self.tmp / f"mode-{mode}"
                self.build(out, dict(self.plan, mode=mode, publish=publish))
                self.assertEqual(
                    (out / "SHA256SUMS").read_bytes(), (self.out / "SHA256SUMS").read_bytes()
                )

    def test_the_toolchain_is_recorded(self) -> None:
        record = json.loads((self.out / "leg" / "toolchain.json").read_text())
        self.assertEqual(record["lxml"], "6.1.3")
        self.assertTrue(record["gcc"])
        self.assertEqual(record["locks"], {})  # the fixture repository has no locks
        with inside(REPO):
            locks = rp.toolchain()["locks"]
        found = sorted(p.name for p in (REPO / ".github" / "requirements").glob("*.txt"))
        self.assertEqual(sorted(locks), found)
        self.assertTrue(found)
        for name in found:
            data = (REPO / ".github" / "requirements" / name).read_bytes()
            self.assertEqual(locks[name], hashlib.sha256(data).hexdigest())


def gzip_payload(path: Path) -> bytes:
    import gzip

    with gzip.open(path) as stream:
        return stream.read()


class RefusalTest(Fixture):
    def assert_refused(
        self, message: str, plan: dict | None = None, out: Path | None = None
    ) -> None:
        with self.assertRaises(rp.PackageError) as caught:
            self.build(out or self.tmp / "refused", plan)
        self.assertIn(message, str(caught.exception))
        self.assertFalse((self.tmp / "refused").exists())

    def test_an_existing_output_is_refused(self) -> None:
        out = self.tmp / "exists"
        out.mkdir()
        self.assert_refused("exists already", out=out)

    def test_a_checkout_at_another_commit_is_refused(self) -> None:
        for pin, value in (("commit", "0" * 40), ("mavlink", "1" * 40), ("pymavlink", "2" * 40)):
            with self.subTest(pin=pin):
                plan = copy.deepcopy(self.plan)
                if pin == "commit":
                    plan["commit"] = value
                else:
                    plan["pins"][pin] = value
                self.assert_refused(f"is not checked out at {value}", plan)

    def test_a_generator_checkout_named_otherwise_is_refused(self) -> None:
        other = self.tmp / "generator"
        if not other.exists():
            subprocess.run(
                ["git", "clone", "-q", "--shared", "--no-checkout", str(PYMAVLINK), str(other)],
                check=True,
            )
            git(other, "checkout", "-q", self.plan["pins"]["pymavlink"])
        with inside(self.repo), self.assertRaises(rp.PackageError) as caught:
            rp.check_checkouts(self.plan, MAVLINK, other)
        self.assertIn("must be a directory named pymavlink", str(caught.exception))

    def test_a_dirty_generator_checkout_is_refused(self) -> None:
        dirty = self.tmp / "dirty" / "pymavlink"
        subprocess.run(
            ["git", "clone", "-q", "--shared", "--no-checkout", str(PYMAVLINK), str(dirty)],
            check=True,
        )
        git(dirty, "checkout", "-q", self.plan["pins"]["pymavlink"])
        (dirty / "generator" / "planted.py").write_text("raise SystemExit(1)\n")
        with inside(self.repo), self.assertRaises(rp.PackageError) as caught:
            rp.check_checkouts(self.plan, MAVLINK, dirty)
        self.assertIn("has local changes", str(caught.exception))

    def test_a_missing_lxml_is_refused(self) -> None:
        with mock.patch.object(rp.importlib, "import_module", side_effect=ImportError("no lxml")):
            self.assert_refused("lxml is missing, so mavgen would skip validation: no lxml")

    def test_changed_license_terms_are_refused(self) -> None:
        for change, message in (
            (lambda m: m["copying_sha256"].update(mavlink="0" * 64), "mavlink COPYING at the pin differs"),
            (lambda m: m["copying_sha256"].update(pymavlink="0" * 64), "pymavlink COPYING at the pin differs"),
            (lambda m: m["generated_code_grant"].update(lines=[7, 32]), "the generator grant lines are not the reviewed text"),
        ):  # fmt: skip
            with self.subTest(message=message):
                lmap = copy.deepcopy(self.lmap)
                change(lmap)
                with self.assertRaises(rp.PackageError) as caught:
                    rp.license_terms(lmap, MAVLINK, PYMAVLINK, self.plan["pins"])
                self.assertIn(message, str(caught.exception))

    def test_a_missing_blob_is_refused(self) -> None:
        with self.assertRaises(rp.PackageError) as caught:
            rp.git_blob(self.repo, self.plan["commit"], "absent.xml")
        self.assertIn("no absent.xml at", str(caught.exception))

    def test_a_license_without_one_copyright_line_is_refused(self) -> None:
        for text in (b"MIT License\n", b"Copyright (c) A\nCopyright (c) B\n"):
            with self.subTest(text=text), self.assertRaises(rp.PackageError):
                rp.holder(text)
        self.assertEqual(
            rp.holder(b"MIT License\n\nCopyright (c) 2026 X\n"), "Copyright (c) 2026 X"
        )


class GeneratorTest(Fixture):
    def defs(self) -> dict[str, bytes]:
        with inside(self.repo):
            return rp.definitions(self.plan, MAVLINK)

    def test_a_mavgen_failure_is_refused(self) -> None:
        defs = self.defs()
        defs["military.xml"] = b"<mavlink><messages><message></mavlink>"
        with self.assertRaises(rp.PackageError) as caught:
            rp.generate(defs, PYMAVLINK, EPOCH, rp.VARIANTS[0])
        self.assertIn("mavgen --lang=C exited", str(caught.exception))

    def test_skipped_validation_is_refused(self) -> None:
        skipped = subprocess.CompletedProcess([], 0, "Validation skipped for military.xml.\n", "")
        with mock.patch.object(rp, "run", return_value=skipped), self.assertRaises(
            rp.PackageError
        ) as caught:
            rp.mavgen(PYMAVLINK, "C", self.tmp / "c", self.tmp / "military.xml", {}, 0o022)
        self.assertIn(
            "did not validate the definitions (Validation skipped)", str(caught.exception)
        )

    def fake_mavgen(self, version_h: bytes, dialects: tuple[str, ...]):
        def write(pymavlink, lang, output, xml, env, umask):
            if lang == "C":
                for name in dialects:
                    (output / name).mkdir(parents=True)
                    (output / name / "version.h").write_bytes(version_h)
            else:
                output.write_bytes(b"# module\n")

        return mock.patch.object(rp, "mavgen", side_effect=write)

    def test_output_without_one_version_header_per_definitions_file_is_refused(self) -> None:
        line = b'#define MAVLINK_BUILD_DATE "Mon Jan 01 2024"\n'
        for dialects in ((), ("military",), ("military", "common", "standard")):
            with self.subTest(dialects=dialects), self.fake_mavgen(line, dialects):
                with self.assertRaises(rp.PackageError) as caught:
                    rp.generate(self.defs(), PYMAVLINK, EPOCH, rp.VARIANTS[0])
            self.assertIn(
                f"mavgen wrote {len(dialects)} version.h files for 4 definitions files",
                str(caught.exception),
            )

    def test_a_version_header_without_one_build_date_is_refused(self) -> None:
        line = b'#define MAVLINK_BUILD_DATE "Mon Jan 01 2024"\n'
        every = ("common", "military", "minimal", "standard")
        for text, count in ((b"// none\n", 0), (line + line, 2)):
            with self.subTest(count=count), self.fake_mavgen(text, every), self.assertRaises(
                rp.PackageError
            ) as caught:
                rp.generate(self.defs(), PYMAVLINK, EPOCH, rp.VARIANTS[0])
            self.assertIn(
                f"common/version.h has {count} MAVLINK_BUILD_DATE lines", str(caught.exception)
            )

    def test_definitions_that_do_not_validate_are_refused(self) -> None:
        defs = self.defs()
        self.assertEqual(rp.validate(defs, PYMAVLINK, self.plan["pins"]["pymavlink"]), 4)
        defs["military.xml"] = b"<mavlink><unknown/></mavlink>"
        with self.assertRaises(rp.PackageError) as caught:
            rp.validate(defs, PYMAVLINK, self.plan["pins"]["pymavlink"])
        self.assertIn("military.xml does not validate against mavschema.xsd", str(caught.exception))

    def test_runs_that_differ_are_refused(self) -> None:
        first = {"c": {"a.h": b"1"}, "python": {"military.py": b"x"}}
        rp.same_output(first, copy.deepcopy(first))
        for kind, second in (
            ("c", {"c": {"a.h": b"2"}, "python": {"military.py": b"x"}}),
            ("python", {"c": {"a.h": b"1"}, "python": {}}),
        ):
            with self.subTest(kind=kind), self.assertRaises(rp.PackageError) as caught:
                rp.same_output(first, second)
            self.assertIn(f"differ in 1 {kind} file(s)", str(caught.exception))

    def test_the_build_date_is_english_utc(self) -> None:
        self.assertEqual(rp.build_date(EPOCH), "Tue Nov 14 2023")
        self.assertEqual(rp.build_date(0), "Thu Jan 01 1970")
        with mock.patch.dict(os.environ, {"TZ": "Pacific/Kiritimati", "LC_ALL": "de_DE.UTF-8"}):
            self.assertEqual(rp.build_date(EPOCH), "Tue Nov 14 2023")


class CheckTest(Fixture):
    @classmethod
    def setUpClass(cls) -> None:
        super().setUpClass()
        with inside(cls.repo):
            defs = rp.definitions(cls.plan, MAVLINK)
        cls.output = rp.generate(defs, PYMAVLINK, EPOCH, rp.VARIANTS[0])
        cls.table = rp.wire_table(PYMAVLINK, defs, cls.plan)

    def altered(self) -> dict:
        """The table with one dialect message's CRC_EXTRA changed."""
        table = copy.deepcopy(self.table)
        first = next(m for m in table["messages"] if not m["upstream"])
        first["crc_extra"] = (first["crc_extra"] + 1) % 256
        return table

    def test_a_crc_row_that_disagrees_or_is_missing_is_refused(self) -> None:
        with self.assertRaises(rp.PackageError) as caught:
            rp.check_crc_rows(self.output["c"], self.altered())
        self.assertIn("the C CRC table row disagrees with the wire table", str(caught.exception))
        table = copy.deepcopy(self.table)
        table["messages"].append(dict(table["messages"][0], id=16777215, name="ABSENT"))
        with self.assertRaises(rp.PackageError) as caught:
            rp.check_crc_rows(self.output["c"], table)
        self.assertIn("ABSENT: the C CRC table row disagrees", str(caught.exception))
        with self.assertRaises(rp.PackageError) as caught:
            rp.check_crc_rows({"military/military.h": b"// nothing\n"}, self.table)
        self.assertIn("defines no MAVLINK_MESSAGE_CRCS", str(caught.exception))

    def test_a_changed_fixed_header_is_refused(self) -> None:
        pin = self.plan["pins"]["pymavlink"]
        self.assertEqual(rp.check_fixed_headers(self.output["c"], PYMAVLINK, pin), 7)
        changed = dict(self.output["c"], **{"protocol.h": self.output["c"]["protocol.h"] + b"\n"})
        with self.assertRaises(rp.PackageError) as caught:
            rp.check_fixed_headers(changed, PYMAVLINK, pin)
        self.assertIn("protocol.h differs from the pinned generator's copy", str(caught.exception))

    def test_a_probe_that_reports_no_facts_is_refused(self) -> None:
        real = rp.run

        def silent(command, **kwargs):
            if command[0].endswith("/probe"):
                return subprocess.CompletedProcess(command, 0, "1 2\n", "")
            return real(command, **kwargs)

        with mock.patch.object(rp, "run", side_effect=silent), self.assertRaises(
            rp.PackageError
        ) as caught:
            rp.probe_c(self.output["c"], copy.deepcopy(self.table))
        self.assertIn("the C probe did not report its facts: '1 2\\n'", str(caught.exception))

    def test_headers_without_the_32_bit_id_flags_say_so(self) -> None:
        real = rp.run

        def without(command, **kwargs):
            if command[0].endswith("/probe"):
                return subprocess.CompletedProcess(command, 0, "2 291 280 0\n", "")
            return real(command, **kwargs)

        table = copy.deepcopy(self.table)
        with mock.patch.object(rp, "run", side_effect=without):
            rp.probe_c(self.output["c"], table)
        self.assertEqual(
            table["c"],
            {"MAVLINK_VERSION": 2, "sizeof_mavlink_message_t": 291,
             "MAVLINK_MAX_PACKET_LEN": 280, "id32_flags": False},
        )  # fmt: skip

    def test_a_probe_that_fails_to_compile_is_refused(self) -> None:
        with self.assertRaises(rp.PackageError) as caught:
            rp.probe_c(self.output["c"], self.altered())
        self.assertIn("the C probe does not compile", str(caught.exception))
        self.assertIn("_CRC", str(caught.exception))

    def test_a_python_module_that_disagrees_or_fails_is_refused(self) -> None:
        with self.assertRaises(rp.PackageError) as caught:
            rp.check_python(self.output["python"]["military.py"], self.altered())
        self.assertIn("military.py disagrees with the wire table", str(caught.exception))
        with self.assertRaises(rp.PackageError) as caught:
            rp.check_python(b"raise ImportError('broken')\n", self.table)
        self.assertIn("military.py does not import", str(caught.exception))


class LicenseTest(Fixture):
    def test_a_member_must_match_exactly_one_class(self) -> None:
        with self.assertRaises(rp.PackageError) as caught:
            rp.classify(self.lmap, "python", "extra.py")
        self.assertIn("extra.py matches 0 license classes", str(caught.exception))
        lmap = copy.deepcopy(self.lmap)
        lmap["classes"].append(
            {"archive": "python", "paths": ["*.py"], "license": "MIT", "copyright": []}
        )
        with self.assertRaises(rp.PackageError) as caught:
            rp.classify(lmap, "python", "military.py")
        self.assertIn("military.py matches 2 license classes", str(caught.exception))

    def test_copyright_lines(self) -> None:
        self.assertEqual(rp.copyright_lines(self.lmap, ["pymavlink", "holder"], "Copyright (c) X"),
                         ["Copyright (C) the ArduPilot project", "Copyright (c) X"])  # fmt: skip
        self.assertEqual(rp.copyright_lines(self.lmap, [], "Copyright (c) X"), ["NOASSERTION"])

    def test_toml_strings_are_escaped(self) -> None:
        self.assertEqual(rp.toml_string('a"b\\c'), '"a\\"b\\\\c"')

    def test_license_files_must_match_the_licenses_used(self) -> None:
        files = {
            "military.py": b"",
            "NOTICE": b"",
            "LICENSE": b"",
            "REUSE.toml": b"",
            "LICENSES/MIT.txt": b"",
        }
        with self.assertRaises(rp.PackageError) as caught:
            rp.check_reuse(self.lmap, "python", files)
        self.assertIn("LICENSES/ holds ['MIT'] but its files use ['LicenseRef-MAVLink-generated-code', 'MIT']",
                      str(caught.exception))  # fmt: skip
        files["LICENSES/LicenseRef-MAVLink-generated-code.txt"] = b""
        self.assertEqual(rp.check_reuse(self.lmap, "python", files), 2)

    def test_a_license_without_a_text_is_refused(self) -> None:
        lmap = copy.deepcopy(self.lmap)
        lmap["classes"][-1]["license"] = "Apache-2.0"
        ctx = {
            "plan": self.plan,
            "lmap": lmap,
            "license": b"",
            "holder": "Copyright (c) X",
            "grant": "",
        }
        with self.assertRaises(rp.PackageError) as caught:
            rp.archive_files("python", {"military.py": b""}, ctx)
        self.assertIn("no license text for Apache-2.0", str(caught.exception))

    def test_names_that_differ_only_by_case_are_refused(self) -> None:
        rp.check_case("c", {"a.h": b"", "b.h": b""})
        with self.assertRaises(rp.PackageError) as caught:
            rp.check_case("c", {"military/A.h": b"", "military/a.h": b""})
        self.assertIn("military/a.h and military/A.h differ only by case", str(caught.exception))

    def test_a_toolchain_without_gcc_records_none(self) -> None:
        real = rp.run

        def fake(command, **kwargs):
            if command[0] == "gcc":
                return subprocess.CompletedProcess(command, 1, "", "")
            return real(command, **kwargs)

        with mock.patch.object(rp, "run", side_effect=fake):
            self.assertIsNone(rp.toolchain()["gcc"])


class MainTest(Fixture):
    def run_main(self, *args: str, output: Path | None = None) -> tuple[int, str]:
        env = {"MAVLINK_DIR": str(MAVLINK), "PYMAVLINK_DIR": str(PYMAVLINK)}
        if output:
            env["GITHUB_OUTPUT"] = str(output)
        stdout = io.StringIO()
        with inside(self.repo), mock.patch.dict(os.environ, env), contextlib.redirect_stdout(
            stdout
        ):
            with contextlib.redirect_stderr(io.StringIO()):
                code = rp.main(["release_package.py", *args])
        return code, stdout.getvalue()

    def plan_file(self, plan: dict) -> str:
        path = self.tmp / f"plan-{len(list(self.tmp.iterdir()))}.json"
        path.write_text(json.dumps(plan))
        return str(path)

    def test_usage(self) -> None:
        self.assertEqual(self.run_main()[0], 2)

    def test_a_build_writes_the_outputs(self) -> None:
        output = self.tmp / "github_output"
        code, out = self.run_main(
            self.plan_file(self.plan), str(self.tmp / "main-out"), output=output
        )
        self.assertEqual(code, 0)
        self.assertIn("wrote mavlink-m-9.9.9-c.tar.gz", out)
        self.assertIn("checks: c_reuse_covered", out)
        sums = (self.tmp / "main-out" / "SHA256SUMS").read_bytes()
        self.assertEqual(output.read_text(), f"sums_sha256={hashlib.sha256(sums).hexdigest()}\n")

    def test_a_build_without_github_output_prints_only(self) -> None:
        result = {"files": ["a.tar.gz"], "sums_sha256": "0" * 64, "checks": {"crc_rows": 1}}
        with mock.patch.object(rp, "build", return_value=result), mock.patch.dict(os.environ):
            os.environ.pop("GITHUB_OUTPUT", None)
            code, out = self.run_main(self.plan_file(self.plan), str(self.tmp / "unused"))
        self.assertEqual((code, out), (0, "wrote a.tar.gz\nchecks: crc_rows 1\n"))

    def test_a_failure_is_an_annotation(self) -> None:
        plan = copy.deepcopy(self.plan)
        plan["commit"] = "0" * 40
        code, out = self.run_main(self.plan_file(plan), str(self.tmp / "failed"))
        self.assertEqual(code, 1)
        self.assertIn("::error title=release package::. is not checked out at", out)

    def test_an_archive_failure_is_an_annotation(self) -> None:
        with mock.patch.object(rp.archive, "write", side_effect=archive.ArchiveError("too long")):
            code, out = self.run_main(self.plan_file(self.plan), str(self.tmp / "archive-failed"))
        self.assertEqual(code, 1)
        self.assertIn("::error title=release package::too long", out)

    def test_runs_as_a_script(self) -> None:
        argv = ["release_package.py"]
        with mock.patch.object(sys, "argv", argv), contextlib.redirect_stderr(io.StringIO()):
            with self.assertRaises(SystemExit) as exit_:
                runpy.run_path(rp.__file__, run_name="__main__")
        self.assertEqual(exit_.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
