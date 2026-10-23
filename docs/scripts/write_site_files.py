#!/usr/bin/env python3
"""Write the files every docs build carries beside its pages.

Run from docs/ after `vitepress build` (npm run docs:build does), with the
DOCS_VERSION the build used. It writes into .vitepress/dist, or into the
directory given as its argument:

- version.json: which version of the docs this is, and the commit it was built
  from, with that commit's date, military.xml's SHA-256 and the MAVLINK_REF the
  message reference used. Every value comes from the commit, never from the
  build machine, so the same commit gives the same file.
- LICENSE.txt: the repository's license, which covers the site's content.
- THIRD-PARTY-NOTICES.txt: the license and notices of every npm package
  installed for the build, from docs/package-lock.json and the license files
  each package ships, and of the Inter font the theme bundles. The pages and
  their scripts carry code from these packages, so their notices go with them.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
DOCS = HERE.parent
DIST = DOCS / ".vitepress" / "dist"
INTER = HERE / "licenses" / "Inter-LICENSE.txt"
REPO = "https://github.com/Dronecode/mavlink-military"
RELEASE_TAG = re.compile(r"v(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)")  # ASCII digits only
LICENSE_FILE = re.compile(r"(LICEN[CS]E|COPYING|NOTICE)([.-].*)?", re.I)


def git(*args: str) -> str:
    return subprocess.run(
        ["git", "-C", str(DOCS), *args], check=True, capture_output=True, text=True
    ).stdout


def version_record(version: str) -> dict:
    """version.json's content, from the checked-out commit."""
    pins = git("show", "HEAD:.github/mavlink-pins.env")
    mavlink = re.search(r"^MAVLINK_REF=([0-9a-f]{40})$", pins, re.M)
    xml = subprocess.run(
        ["git", "-C", str(DOCS), "show", "HEAD:military.xml"], check=True, capture_output=True
    ).stdout
    release = RELEASE_TAG.fullmatch(version)
    return {
        "schema": 1,
        "version": version or "main",
        "commit": git("rev-parse", "HEAD").strip(),
        "commit_date": git("log", "-1", "--format=%cI", "HEAD").strip(),
        "military_xml_sha256": hashlib.sha256(xml).hexdigest(),
        "mavlink_ref": mavlink.group(1) if mavlink else None,
        "release": f"{REPO}/releases/tag/{version}" if release else None,
    }


def package_license(entry: dict, folder: Path) -> str:
    """A package's declared license: the lockfile's, else its package.json's."""
    if entry.get("license"):
        return entry["license"]
    manifest = folder / "package.json"
    if manifest.is_file():
        declared = json.loads(manifest.read_text(encoding="utf-8")).get("license")
        if isinstance(declared, str) and declared:
            return declared
    return "not declared"


def notices(docs: Path) -> str:
    """THIRD-PARTY-NOTICES.txt for the packages installed under docs/node_modules."""
    lock = json.loads((docs / "package-lock.json").read_text(encoding="utf-8"))
    sections = []
    for key in sorted(k for k in lock["packages"] if k.startswith("node_modules/")):
        folder = docs / key
        if not folder.is_dir():
            continue  # another platform's optional package, never installed or bundled
        entry = lock["packages"][key]
        name = key.rsplit("node_modules/", 1)[1]
        texts = [
            f"--- {path.name}\n\n{path.read_text(encoding='utf-8', errors='replace').strip()}\n"
            for path in sorted(folder.iterdir())
            if path.is_file() and LICENSE_FILE.fullmatch(path.name)
        ]
        body = "\n".join(texts) if texts else "(The package ships no license file.)\n"
        sections.append(
            f"{'=' * 72}\n{name} {entry.get('version', '')} ({package_license(entry, folder)})\n"
            f"{key}\n\n{body}"
        )
    header = (
        "Third-party notices for this documentation site\n\n"
        "The site's pages, styles and scripts are built with the npm packages below,\n"
        "and carry code from them. Each package is listed with its version, its\n"
        "declared license and the license files it ships. The theme also bundles the\n"
        "Inter font, whose license follows the packages.\n\n"
    )
    inter = f"{'=' * 72}\nInter font (bundled by the VitePress theme)\n\n{INTER.read_text(encoding='utf-8')}"
    return header + "\n".join(sections) + "\n" + inter


def main(argv: list[str]) -> int:
    dist = Path(argv[1]) if len(argv) > 1 else DIST
    if not (dist / "index.html").is_file():
        print(f"error: no built site in {dist}; run vitepress build first", file=sys.stderr)
        return 1
    record = version_record(os.environ.get("DOCS_VERSION", ""))
    (dist / "version.json").write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    license_text = git("show", "HEAD:LICENSE")
    (dist / "LICENSE.txt").write_text(license_text, encoding="utf-8")
    (dist / "THIRD-PARTY-NOTICES.txt").write_text(notices(DOCS), encoding="utf-8")
    print(
        f"wrote version.json ({record['version']}), LICENSE.txt and THIRD-PARTY-NOTICES.txt to {dist}"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
