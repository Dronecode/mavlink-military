#!/usr/bin/env python3
"""Build a release's package: the definitions, the C headers, the Python module,
military.xml, the wire table and the manifest, with their SHA256SUMS.

Usage: release_package.py <plan.json> <out>
  plan.json  the release plan the preflight job wrote
  out        directory for the package; it must not exist yet

Run from a checkout of this repository at the plan's commit. MAVLINK_DIR and
PYMAVLINK_DIR (default mavlink and pymavlink) name clean checkouts at the plan's
pins; the pymavlink checkout's directory must be named pymavlink, and lxml must
be importable, or mavgen would skip the schema validation.

Every input comes from git objects at the pinned commits, never from a working
tree: military.xml, IDMAPPING.md and LICENSE from the release commit, and
common.xml, standard.xml and minimal.xml from mavlink at MAVLINK_REF. mavgen at
PYMAVLINK_REF generates the C headers and the Python module from exactly the
definitions the definitions archive carries, with validation and
--strict-units, and the build fails if mavgen reports validation skipped.
MAVLINK_BUILD_DATE becomes the commit's date. The whole generation runs twice,
the second time with another time zone, locale, umask, hash seed and file
times, and both runs must give the same bytes. The C archive's copies of the
definitions are the same bytes as the definitions archive's, from one read.

Checks before anything is written: the four definitions validate against the
pinned generator's mavschema.xsd; the fixed C headers are byte-identical to the
generator's own; a C11 compile of the headers at -Wall -Wextra -Werror, with
static assertions of every dialect message's ID, CRC_EXTRA and wire lengths
against the wire table (struct sizes are not wire lengths: the generated
structs are not packed), and a run of the compiled probe that reports
MAVLINK_VERSION, sizeof(mavlink_message_t), MAVLINK_MAX_PACKET_LEN and whether
the headers define the SYSID32 and TARGET32 incompatibility flags; every
message's C CRC table row and Python class against the same table; no two
archive members whose names differ only by case; and the license map
(license-map.json): both generator COPYING files at the pins still have the
reviewed digests, every archive member matches exactly one class, and the
REUSE.toml written from the map covers every member and names a license file
for every license it uses.

The wire table lists every message, the dialect's and the included files'
(marked upstream), with its ID, CRC_EXTRA, lengths, flags and target offsets,
every enum entry and command number of the dialect, the probe's C facts and
HEARTBEAT's mavlink_version from minimal.xml. The manifest lists every archive
member with its SHA-256, size, license and copyright, each archive's
uncompressed tar digest, the other package files' digests, the tag, commit,
pins, generator identity, generator command lines, lxml's version and the
previous release; tool versions that differ between machines are recorded in
leg/toolchain.json instead, so a rebuild elsewhere gives the same bytes.

Writes to out: mavlink-m-<version>-definitions.tar.gz, -c.tar.gz,
-python.tar.gz, -military.xml, -wire.json and -manifest.json, and SHA256SUMS
over them; out/leg/checks.json and out/leg/toolchain.json record what this run
checked and with which tools. GITHUB_OUTPUT receives sums_sha256, the SHA-256
of SHA256SUMS.
"""

from __future__ import annotations

import contextlib
import fnmatch
import hashlib
import importlib
import io
import json
import os
import platform
import re
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
import zlib
from datetime import datetime, timezone
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import archive  # noqa: E402

LICENSE_MAP = HERE / "license-map.json"
LICENSE_TEXTS = HERE / "licenses"
UPSTREAM = ("common", "standard", "minimal")
GENERATED_CODE = "LicenseRef-MAVLink-generated-code"
BUILD_DATE = re.compile(rb'^#define MAVLINK_BUILD_DATE "[^"\n]*"$', re.M)
CRC_TABLE = re.compile(r"^#define MAVLINK_MESSAGE_CRCS \{(.*)\}$", re.M)
CRC_ROW = re.compile(r"\{([0-9]+), ([0-9]+), ([0-9]+), ([0-9]+), ([0-9]+), ([0-9]+), ([0-9]+)\}")
FIXED_HEADERS = (
    "checksum.h", "mavlink_conversions.h", "mavlink_get_info.h", "mavlink_helpers.h",
    "mavlink_sha256.h", "mavlink_types.h", "protocol.h",
)  # fmt: skip
COMMANDS = (
    "mavgen.py --lang=C --wire-protocol=2.0 --strict-units --output=<c> message_definitions/v1.0/military.xml",
    "mavgen.py --lang=Python3 --wire-protocol=2.0 --strict-units --output=<py>/military.py "
    "message_definitions/v1.0/military.xml",
)
HOLDER = re.compile(r"^Copyright \(c\) .+$", re.M)
SKIPPED = ("Validation skipped", "Failed to import lxml")
DAYS = ("Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun")
MONTHS = ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec")
# The second generation run differs from the first in everything that must not
# reach the output.
VARIANTS = (
    {"TZ": "UTC", "LC_ALL": "C.UTF-8", "PYTHONHASHSEED": "0", "umask": 0o022, "days": 0},
    {
        "TZ": "Pacific/Kiritimati",
        "LC_ALL": "C",
        "PYTHONHASHSEED": "4242",
        "umask": 0o077,
        "days": 400,
    },
)
# The C facts the compiled probe prints after its static assertions.
C_FACTS = """
#include <stdio.h>
#if defined(MAVLINK_IFLAG_SYSID32) && defined(MAVLINK_IFLAG_TARGET32)
#define PROBE_ID32 1
#else
#define PROBE_ID32 0
#endif
int main(void) {
    printf("%d %zu %d %d\\n", (int)MAVLINK_VERSION, sizeof(mavlink_message_t), (int)MAVLINK_MAX_PACKET_LEN,
           PROBE_ID32);
    return 0;
}
"""
# What the probe compile and the Python import check read, kept short so a
# failure names the message.
PY_PROBE = """
import importlib.util, json, sys
spec = importlib.util.spec_from_file_location("military", sys.argv[1])
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
print(json.dumps({str(i): [c.msgname, c.crc_extra, c.unpacker.size] for i, c in module.mavlink_map.items()}))
"""


class PackageError(Exception):
    """Anything that must stop the release build."""


def run(command: list[str], **kwargs) -> subprocess.CompletedProcess:
    return subprocess.run(command, capture_output=True, **kwargs)


def git_blob(repo: Path, commit: str, path: str) -> bytes:
    result = run(["git", "-C", str(repo), "cat-file", "blob", f"{commit}:{path}"])
    if result.returncode != 0:
        raise PackageError(f"{repo}: no {path} at {commit}")
    return result.stdout


def head(repo: Path) -> str:
    return run(["git", "-C", str(repo), "rev-parse", "HEAD"], text=True).stdout.strip()


def build_date(epoch: int) -> str:
    """mavgen's "%a %b %d %Y" for a time, in English and UTC whatever the locale."""
    day = datetime.fromtimestamp(epoch, timezone.utc)
    return f"{DAYS[day.weekday()]} {MONTHS[day.month - 1]} {day.day:02d} {day.year}"


def check_checkouts(plan: dict, mavlink: Path, pymavlink: Path) -> None:
    expected = (
        (Path("."), plan["commit"]),
        (mavlink, plan["pins"]["mavlink"]),
        (pymavlink, plan["pins"]["pymavlink"]),
    )
    for repo, commit in expected:
        if head(repo) != commit:
            raise PackageError(f"{repo} is not checked out at {commit}")
    if pymavlink.name != "pymavlink":
        raise PackageError(
            f"{pymavlink}: the generator checkout must be a directory named pymavlink"
        )
    if run(["git", "-C", str(pymavlink), "status", "--porcelain"], text=True).stdout.strip():
        raise PackageError(f"{pymavlink} has local changes; mavgen runs from its working tree")
    try:
        importlib.import_module("lxml.etree")
    except ImportError as error:
        raise PackageError(f"lxml is missing, so mavgen would skip validation: {error}") from error


def license_terms(lmap: dict, mavlink: Path, pymavlink: Path, pins: dict) -> str:
    """The generator grant, once both COPYING files have their reviewed digests."""
    copying = {
        "mavlink": git_blob(mavlink, pins["mavlink"], "COPYING"),
        "pymavlink": git_blob(pymavlink, pins["pymavlink"], "COPYING"),
    }
    for name, data in copying.items():
        if hashlib.sha256(data).hexdigest() != lmap["copying_sha256"][name]:
            raise PackageError(
                f"{name} COPYING at the pin differs from the reviewed one in license-map.json"
            )
    first, last = lmap["generated_code_grant"]["lines"]
    lines = copying["pymavlink"].decode("utf-8").splitlines(keepends=True)[first - 1 : last]
    grant = "".join(lines)
    if hashlib.sha256(grant.encode("utf-8")).hexdigest() != lmap["generated_code_grant"]["sha256"]:
        raise PackageError("the generator grant lines are not the reviewed text")
    return grant


def holder(license_text: bytes) -> str:
    """This repository's copyright line, line 3 of LICENSE."""
    found = HOLDER.findall(license_text.decode("utf-8"))
    if len(found) != 1:
        raise PackageError("LICENSE does not hold exactly one copyright line")
    return found[0]


def validate(defs: dict[str, bytes], pymavlink: Path, pin: str) -> int:
    """Every definitions file against the pinned generator's mavschema.xsd, as the schema job does."""
    etree = importlib.import_module("lxml.etree")
    schema = etree.XMLSchema(etree.fromstring(git_blob(pymavlink, pin, "generator/mavschema.xsd")))
    for name, data in sorted(defs.items()):
        if not schema.validate(etree.fromstring(data)):
            raise PackageError(
                f"{name} does not validate against mavschema.xsd: {schema.error_log.last_error}"
            )
    return len(defs)


def check_fixed_headers(c: dict[str, bytes], pymavlink: Path, pin: str) -> int:
    """The fixed C headers ship exactly as the pinned generator holds them."""
    for name in FIXED_HEADERS:
        if c.get(name) != git_blob(pymavlink, pin, f"generator/C/include_v2.0/{name}"):
            raise PackageError(f"{name} differs from the pinned generator's copy")
    return len(FIXED_HEADERS)


def definitions(plan: dict, mavlink: Path) -> dict[str, bytes]:
    found = {"military.xml": git_blob(Path("."), plan["commit"], "military.xml")}
    for name in UPSTREAM:
        found[f"{name}.xml"] = git_blob(
            mavlink, plan["pins"]["mavlink"], f"message_definitions/v1.0/{name}.xml"
        )
    return found


def read_tree(root: Path) -> dict[str, bytes]:
    return {
        p.relative_to(root).as_posix(): p.read_bytes()
        for p in sorted(root.rglob("*"))
        if p.is_file()
    }


def mavgen(pymavlink: Path, lang: str, output: Path, xml: Path, env: dict, umask: int) -> None:
    command = [
        sys.executable,
        str(pymavlink / "tools" / "mavgen.py"),
        f"--lang={lang}",
        "--wire-protocol=2.0",
        "--strict-units",
        f"--output={output}",
        str(xml),
    ]
    result = run(command, env=env, text=True, umask=umask)
    log = result.stdout + result.stderr
    if result.returncode != 0:
        raise PackageError(f"mavgen --lang={lang} exited {result.returncode}: {log.strip()[-800:]}")
    skipped = [mark for mark in SKIPPED if mark in log]
    if skipped:
        raise PackageError(f"mavgen --lang={lang} did not validate the definitions ({skipped[0]})")


def generate(defs: dict[str, bytes], pymavlink: Path, epoch: int, variant: dict) -> dict:
    """The C and Python outputs of one generation run, with the build date normalised."""
    with tempfile.TemporaryDirectory() as work:
        root = Path(work)
        source = root / "message_definitions" / "v1.0"
        source.mkdir(parents=True)
        when = epoch + variant["days"] * 86400
        for name, data in defs.items():
            (source / name).write_bytes(data)
            os.utime(source / name, (when, when))
        env = dict(os.environ, TZ=variant["TZ"], LC_ALL=variant["LC_ALL"])
        env["PYTHONHASHSEED"] = variant["PYTHONHASHSEED"]
        (root / "py").mkdir()
        mavgen(pymavlink, "C", root / "c", source / "military.xml", env, variant["umask"])
        mavgen(
            pymavlink,
            "Python3",
            root / "py" / "military.py",
            source / "military.xml",
            env,
            variant["umask"],
        )
        c, python = read_tree(root / "c"), read_tree(root / "py")
    dated = sorted(name for name in c if name.endswith("/version.h"))
    if len(dated) != len(defs):
        raise PackageError(
            f"mavgen wrote {len(dated)} version.h files for {len(defs)} definitions files"
        )
    stamp = f'#define MAVLINK_BUILD_DATE "{build_date(epoch)}"'.encode()
    for name in dated:
        text, count = BUILD_DATE.subn(stamp, c[name])
        if count != 1:
            raise PackageError(f"{name} has {count} MAVLINK_BUILD_DATE lines, not one")
        c[name] = text
    return {"c": c, "python": python}


def same_output(first: dict, second: dict) -> None:
    for kind in ("c", "python"):
        names = sorted(set(first[kind]) | set(second[kind]))
        differ = [n for n in names if first[kind].get(n) != second[kind].get(n)]
        if differ:
            raise PackageError(
                f"two generation runs differ in {len(differ)} {kind} file(s), first {differ[0]}"
            )


def parse(pymavlink: Path, name: str, data: bytes):
    sys.path.insert(0, str(pymavlink.parent))
    mavparse = importlib.import_module("pymavlink.generator.mavparse")
    with tempfile.TemporaryDirectory() as work, contextlib.redirect_stdout(io.StringIO()):
        path = Path(work, name)
        path.write_bytes(data)
        return mavparse.MAVXML(str(path), wire_protocol_version="2.0")


def wire_table(pymavlink: Path, defs: dict[str, bytes], plan: dict) -> dict:
    """Every message's wire facts from pymavlink's parser, the dialect's and the included
    files' marked apart, and the dialect's enums and commands."""
    messages = []
    for name in ("military.xml", *(f"{n}.xml" for n in UPSTREAM)):
        for m in parse(pymavlink, name, defs[name]).message:
            messages.append({"id": m.id, "name": m.name, "crc_extra": m.crc_extra,
                             "min_length": m.wire_min_length, "max_length": m.wire_length,
                             "source": name, "upstream": name != "military.xml"})  # fmt: skip
    military = parse(pymavlink, "military.xml", defs["military.xml"])
    enums = [
        {"name": e.name, "entries": sorted(({"name": x.name, "value": x.value} for x in e.entry if not x.end_marker),
                                           key=lambda x: (x["value"], x["name"]))}
        for e in military.enum
    ]  # fmt: skip
    commands = [
        {"value": int(entry.get("value")), "name": entry.get("name")}
        for enum in ET.fromstring(defs["military.xml"]).iter("enum")
        if enum.get("name") == "MAV_CMD"
        for entry in enum.iter("entry")
    ]
    minimal = ET.fromstring(defs["minimal.xml"]).findtext("version")
    return {
        "schema": 1,
        "version": plan["version"],
        "commit": plan["commit"],
        "dialect": "military.xml",
        "messages": sorted(messages, key=lambda m: m["id"]),
        "enums": sorted(enums, key=lambda e: e["name"]),
        "commands": sorted(commands, key=lambda c: c["value"]),
        "heartbeat_mavlink_version": int(minimal) if minimal else None,
    }


def check_crc_rows(c: dict[str, bytes], table: dict) -> int:
    """Every message's C CRC table row agrees with the wire table; its routing facts join the table."""
    match = CRC_TABLE.search(c["military/military.h"].decode("utf-8"))
    if match is None:
        raise PackageError("military/military.h defines no MAVLINK_MESSAGE_CRCS")
    rows = {int(r[0]): tuple(map(int, r[1:])) for r in CRC_ROW.findall(match.group(1))}
    for m in table["messages"]:
        row = rows.get(m["id"])
        if row is None or row[:3] != (m["crc_extra"], m["min_length"], m["max_length"]):
            raise PackageError(f"{m['name']}: the C CRC table row disagrees with the wire table")
        m.update(flags=row[3], target_system_offset=row[4], target_component_offset=row[5])
    return len(table["messages"])


def probe_source(table: dict) -> str:
    lines = ['#include "military/mavlink.h"']
    for m in (m for m in table["messages"] if not m["upstream"]):
        name = m["name"]
        for macro, value in (
            (f"MAVLINK_MSG_ID_{name}", m["id"]),
            (f"MAVLINK_MSG_ID_{name}_CRC", m["crc_extra"]),
            (f"MAVLINK_MSG_ID_{name}_MIN_LEN", m["min_length"]),
            (f"MAVLINK_MSG_ID_{name}_LEN", m["max_length"]),
        ):
            lines.append(f'_Static_assert({macro} == {value}, "{name}: {macro}");')
    return "\n".join(lines) + "\n" + C_FACTS


def probe_c(c: dict[str, bytes], table: dict) -> int:
    """Compile the headers with static assertions against the wire table, at -Werror, then run
    the probe for the C facts it prints, which join the table."""
    flags = ["-std=c11", "-Wall", "-Wextra", "-Werror", "-Wno-address-of-packed-member"]
    with tempfile.TemporaryDirectory() as work:
        root = Path(work)
        for name, data in c.items():
            (root / "c" / name).parent.mkdir(parents=True, exist_ok=True)
            (root / "c" / name).write_bytes(data)
        (root / "probe.c").write_text(probe_source(table), encoding="utf-8")
        compiled = run(
            [
                "gcc",
                *flags,
                "-I",
                str(root / "c"),
                str(root / "probe.c"),
                "-o",
                str(root / "probe"),
            ],
            text=True,
        )
        if compiled.returncode != 0:
            raise PackageError(f"the C probe does not compile: {compiled.stderr.strip()[-800:]}")
        ran = run([str(root / "probe")], text=True)
    values = ran.stdout.split()
    if ran.returncode != 0 or len(values) != 4:
        raise PackageError(f"the C probe did not report its facts: {ran.stdout!r} {ran.stderr!r}")
    table["c"] = {"MAVLINK_VERSION": int(values[0]), "sizeof_mavlink_message_t": int(values[1]),
                  "MAVLINK_MAX_PACKET_LEN": int(values[2]), "id32_flags": values[3] == "1"}  # fmt: skip
    return 4 * sum(1 for m in table["messages"] if not m["upstream"])


def check_python(module: bytes, table: dict) -> int:
    with tempfile.TemporaryDirectory() as work:
        path = Path(work, "military.py")
        path.write_bytes(module)
        result = run([sys.executable, "-I", "-c", PY_PROBE, str(path)], text=True)
    if result.returncode != 0:
        raise PackageError(f"military.py does not import: {result.stderr.strip()[-800:]}")
    classes = json.loads(result.stdout)
    for m in table["messages"]:
        if classes.get(str(m["id"])) != [m["name"], m["crc_extra"], m["max_length"]]:
            raise PackageError(f"{m['name']}: military.py disagrees with the wire table")
    return len(table["messages"])


def classify(lmap: dict, kind: str, path: str) -> dict:
    found = [
        c for c in lmap["classes"]
        if c["archive"] == kind and any(fnmatch.fnmatchcase(path, p) for p in c["paths"])
    ]  # fmt: skip
    if len(found) != 1:
        raise PackageError(f"{kind} archive: {path} matches {len(found)} license classes, not one")
    return found[0]


def copyright_lines(lmap: dict, names: list[str], holder_line: str) -> list[str]:
    lines = [holder_line if n == "holder" else lmap["copyright"][n] for n in names]
    return lines or ["NOASSERTION"]


def toml_string(value: str) -> str:
    return '"' + value.replace("\\", "\\\\").replace('"', '\\"') + '"'


def reuse_toml(lmap: dict, kind: str, holder_line: str) -> str:
    """REUSE.toml for one archive, one annotation per license class."""
    out = ["version = 1"]
    for c in (c for c in lmap["classes"] if c["archive"] == kind):
        paths = ", ".join(toml_string(p[:-1] + "**" if p.endswith("/*") else p) for p in c["paths"])
        texts = ", ".join(
            toml_string(t) for t in copyright_lines(lmap, c["copyright"], holder_line)
        )
        out += [
            "",
            "[[annotations]]",
            f"path = [{paths}]",
            f"SPDX-FileCopyrightText = [{texts}]",
            f"SPDX-License-Identifier = {toml_string(c['license'])}",
        ]
    return "\n".join(out) + "\n"


def license_ids(expression: str) -> list[str]:
    return [part.strip() for part in expression.split(" AND ")]


def check_reuse(lmap: dict, kind: str, files: dict[str, bytes]) -> int:
    """Every covered member has one class; the license files are exactly those the classes use."""
    covered = [
        n for n in files if n not in ("LICENSE", "REUSE.toml") and not n.startswith("LICENSES/")
    ]
    used = set()
    for name in covered:
        used |= set(license_ids(classify(lmap, kind, name)["license"]))
    present = {n[len("LICENSES/") : -len(".txt")] for n in files if n.startswith("LICENSES/")}
    if used != present:
        raise PackageError(
            f"{kind} archive: LICENSES/ holds {sorted(present)} but its files use {sorted(used)}"
        )
    return len(covered)


def check_case(kind: str, files: dict[str, bytes]) -> None:
    seen: dict[str, str] = {}
    for name in sorted(files):
        other = seen.setdefault(name.casefold(), name)
        if other != name:
            raise PackageError(f"{kind} archive: {name} and {other} differ only by case")


NOTICES = {
    "definitions": "the MAVLink-M message definitions, military.xml, with the MAVLink definitions it includes",
    "c": "MAVLink 2 C headers for the MAVLink-M dialect, generated by mavgen",
    "python": "the MAVLink 2 Python module for the MAVLink-M dialect, generated by mavgen",
}


def notice(plan: dict, kind: str, holder_line: str, lmap: dict) -> bytes:
    pins = plan["pins"]
    text = (
        f"MAVLink-M {plan['version']}: {NOTICES[kind]}.\n\n"
        f"This archive belongs to release {plan['tag']} of {plan['repository']}, built from commit\n"
        f"{plan['commit']}, with mavlink/mavlink at\n{pins['mavlink']} and pymavlink at\n"
        f"{pins['pymavlink']}.\n\n"
        f"REUSE.toml gives the license and copyright of every file, and LICENSES/ holds\n"
        f"each license text. This repository's files are under the MIT license (LICENSE,\n"
        f"{holder_line}).\n"
    )
    if kind != "python":
        text += (
            "common.xml, standard.xml and minimal.xml come unchanged from mavlink/mavlink,\n"
            "whose project states that its message definitions are under the MIT license;\n"
            "the files carry no copyright notice.\n"
        )
    if kind != "definitions":
        text += (
            f"The generated code is under the generator's grant in\n"
            f"LICENSES/{GENERATED_CODE}.txt, whose notice must be kept in all\n"
            "copies or substantial portions. The generator itself, pymavlink, is not\n"
            "included; it is under the (L)GPL v3.\n"
        )
    if kind == "c":
        text += (
            "mavlink_sha256.h keeps its own BSD-3-Clause notice (LICENSES/BSD-3-Clause.txt),\n"
            f"{lmap['copyright']['kth']}.\n"
            "Whoever redistributes it in binary form reproduces that notice in the\n"
            "documentation or other materials (clause 2).\n"
        )
    return text.encode("utf-8")


def archive_files(kind: str, content: dict[str, bytes], ctx: dict) -> dict[str, bytes]:
    files = dict(content)
    files["NOTICE"] = notice(ctx["plan"], kind, ctx["holder"], ctx["lmap"])
    files["LICENSE"] = ctx["license"]
    files["REUSE.toml"] = reuse_toml(ctx["lmap"], kind, ctx["holder"]).encode("utf-8")
    used = set()
    for name in files:
        if name not in ("LICENSE", "REUSE.toml"):
            used |= set(license_ids(classify(ctx["lmap"], kind, name)["license"]))
    for license_id in sorted(used):
        vendored = LICENSE_TEXTS / f"{license_id}.txt"
        if license_id == GENERATED_CODE:
            files[f"LICENSES/{license_id}.txt"] = ctx["grant"].encode("utf-8")
        elif vendored.is_file():
            files[f"LICENSES/{license_id}.txt"] = vendored.read_bytes()
        else:
            raise PackageError(f"no license text for {license_id} in {LICENSE_TEXTS}")
    return files


def manifest_entry(lmap: dict, kind: str, name: str, data: bytes, holder_line: str) -> dict:
    entry = {"path": name, "sha256": hashlib.sha256(data).hexdigest(), "size": len(data)}
    if name in ("LICENSE", "REUSE.toml") or name.startswith("LICENSES/"):
        entry["covered"] = False
    else:
        c = classify(lmap, kind, name)
        entry.update(
            license=c["license"], copyright=copyright_lines(lmap, c["copyright"], holder_line)
        )
    return entry


def toolchain() -> dict:
    gcc = run(["gcc", "--version"], text=True).stdout.splitlines()
    import lxml.etree

    return {
        "python": platform.python_version(),
        "implementation": platform.python_implementation(),
        "platform": platform.platform(),
        "lxml": lxml.etree.__version__,
        "libxml2": ".".join(map(str, lxml.etree.LIBXML_VERSION)),
        "zlib": zlib.ZLIB_VERSION,
        "zlib_runtime": zlib.ZLIB_RUNTIME_VERSION,
        "gcc": gcc[0] if gcc else None,
        "git": run(["git", "--version"], text=True).stdout.strip(),
        "runner_image": os.environ.get("ImageOS"),
        "runner_image_version": os.environ.get("ImageVersion"),
        "locks": {
            p.name: hashlib.sha256(p.read_bytes()).hexdigest()
            for p in sorted(Path(".github/requirements").glob("*.txt"))
        },
    }


def dumps(value: object) -> bytes:
    return (json.dumps(value, indent=2, sort_keys=True) + "\n").encode("ascii")


def build(plan: dict, out: Path, mavlink: Path, pymavlink: Path) -> dict:
    if out.exists():
        raise PackageError(f"{out} exists already")
    check_checkouts(plan, mavlink, pymavlink)
    lmap = json.loads(LICENSE_MAP.read_text(encoding="utf-8"))
    license_text = git_blob(Path("."), plan["commit"], "LICENSE")
    ctx = {
        "plan": plan,
        "lmap": lmap,
        "license": license_text,
        "holder": holder(license_text),
        "grant": license_terms(lmap, mavlink, pymavlink, plan["pins"]),
    }
    defs = definitions(plan, mavlink)
    epoch = plan["source_date_epoch"]
    pin = plan["pins"]["pymavlink"]
    checks = {"schema_valid_files": validate(defs, pymavlink, pin)}
    first = generate(defs, pymavlink, epoch, VARIANTS[0])
    same_output(first, generate(defs, pymavlink, epoch, VARIANTS[1]))
    table = wire_table(pymavlink, defs, plan)
    checks.update(
        generation_runs_identical=2,
        fixed_headers_identical=check_fixed_headers(first["c"], pymavlink, pin),
        crc_rows=check_crc_rows(first["c"], table),
        c_static_assertions=probe_c(first["c"], table),
        python_classes=check_python(first["python"]["military.py"], table),
    )
    contents = {
        "definitions": {
            **{f"message_definitions/v1.0/{name}": data for name, data in defs.items()},
            "IDMAPPING.md": git_blob(Path("."), plan["commit"], "IDMAPPING.md"),
        },
        "c": {**first["c"], **{f"message_definitions/{name}": data for name, data in defs.items()}},
        "python": first["python"],
    }
    version = plan["version"]
    out.mkdir(parents=True)
    lxml_version = importlib.import_module("lxml.etree").__version__
    manifest = {"schema": 1, "version": version, "tag": plan["tag"], "commit": plan["commit"],
                "tree": plan["tree"], "source_date_epoch": epoch, "pins": plan["pins"],
                "generator": plan.get("generator"), "previous": plan.get("previous"),
                "commands": list(COMMANDS), "lxml": lxml_version, "archives": {}, "files": {}}  # fmt: skip
    for kind, content in contents.items():
        files = archive_files(kind, content, ctx)
        check_case(kind, files)
        checks[f"{kind}_reuse_covered"] = check_reuse(lmap, kind, files)
        name = f"mavlink-m-{version}-{kind}.tar.gz"
        top = f"mavlink-m-{version}-{kind}"
        digests = archive.write(out / name, top, files, epoch)
        manifest["archives"][name] = {
            "top": top,
            "tar_sha256": digests["tar_sha256"],
            "files": [
                manifest_entry(lmap, kind, n, files[n], ctx["holder"]) for n in sorted(files)
            ],
        }
    for name, data in ((f"mavlink-m-{version}-military.xml", defs["military.xml"]),
                       (f"mavlink-m-{version}-wire.json", dumps(table))):  # fmt: skip
        (out / name).write_bytes(data)
        manifest["files"][name] = hashlib.sha256(data).hexdigest()
    (out / f"mavlink-m-{version}-manifest.json").write_bytes(dumps(manifest))
    names = sorted(p.name for p in out.iterdir())
    sums = "".join(f"{hashlib.sha256((out / n).read_bytes()).hexdigest()}  {n}\n" for n in names)
    (out / "SHA256SUMS").write_text(sums, encoding="ascii")
    (out / "leg").mkdir()
    (out / "leg" / "checks.json").write_bytes(dumps(checks))
    (out / "leg" / "toolchain.json").write_bytes(dumps(toolchain()))
    return {
        "files": names,
        "sums_sha256": hashlib.sha256(sums.encode("ascii")).hexdigest(),
        "checks": checks,
    }


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        print(__doc__, file=sys.stderr)
        return 2
    plan = json.loads(Path(argv[1]).read_text(encoding="utf-8"))
    mavlink = Path(os.environ.get("MAVLINK_DIR", "mavlink")).resolve()
    pymavlink = Path(os.environ.get("PYMAVLINK_DIR", "pymavlink")).resolve()
    try:
        result = build(plan, Path(argv[2]), mavlink, pymavlink)
    except (PackageError, archive.ArchiveError) as error:
        print(f"::error title=release package::{error}")
        return 1
    for name in result["files"]:
        print(f"wrote {name}")
    print("checks: " + ", ".join(f"{k} {v}" for k, v in sorted(result["checks"].items())))
    output = os.environ.get("GITHUB_OUTPUT")
    if output:
        with open(output, "a", encoding="utf-8") as stream:
            stream.write(f"sums_sha256={result['sums_sha256']}\n")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
