#!/usr/bin/env python3
"""Assemble the documentation site that docs_deploy.yml deploys.

Usage: assemble_site.py <main> <site>
  main  main's built pages, from docs.yml with DOCS_VERSION=main
  site  the directory to write the site into; it must not exist yet

The site holds:

- main/: main's pages, as docs.yml built them.
- index.html: a page that sends a visitor on to the version the root serves,
  main/, keeping any #anchor; and 404.html, main's not-found page, whose links
  name main/ in full and so work from any path.
- A redirect page at every page path the site had before it had versions:
  each page of main's en/, at en/..., sends a visitor to the same page below
  the version the root serves, so links made before keep working.
- sitemap.xml: an index of each version's own sitemap.
- versions.json: the versions the site serves, for the version menu and
  banners: main, at main/, with the status development.

Redirect pages name their targets relative to themselves, so the site works
below any base path. Anything missing from main's build stops the assembly,
so a broken site is never deployed. Prints a Markdown summary.
"""

from __future__ import annotations

import html
import json
import shutil
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

SITEMAP_NS = "http://www.sitemaps.org/schemas/sitemap/0.9"


class AssemblyError(Exception):
    """Something that must stop the deploy."""


def redirect_page(target: str) -> str:
    """A page that sends its visitor to target, a path relative to the page."""
    # json.dumps quotes the target for the script; < is escaped too, so no
    # target can close the script element.
    attr, script = html.escape(target), json.dumps(target).replace("<", "\\u003c")
    return (
        '<!doctype html>\n<html lang="en">\n<head>\n<meta charset="utf-8">\n'
        "<title>MAVLink-M</title>\n"
        '<meta name="robots" content="noindex">\n'
        f'<link rel="canonical" href="{attr}">\n'
        f'<meta http-equiv="refresh" content="0; url={attr}">\n'
        f"<script>location.replace({script} + location.hash)</script>\n"
        f'</head>\n<body><p>This page is at <a href="{attr}">{attr}</a>.</p></body>\n</html>\n'
    )


def site_address(main: Path) -> str:
    """The site's address, from the first URL of main's sitemap (<address>main/...)."""
    try:
        root = ET.parse(main / "sitemap.xml").getroot()
    except (OSError, ET.ParseError) as error:
        raise AssemblyError(f"main's sitemap.xml cannot be read: {error}") from error
    first = next((loc.text or "" for loc in root.iter(f"{{{SITEMAP_NS}}}loc")), "")
    if "/main/" not in first:
        raise AssemblyError(f"main's sitemap names no page below main/: {first!r}")
    return first[: first.index("/main/") + 1]


def sitemap_index(address: str, paths: list[str]) -> str:
    entries = "".join(
        f"<sitemap><loc>{html.escape(address + p)}sitemap.xml</loc></sitemap>" for p in paths
    )
    return (
        '<?xml version="1.0" encoding="UTF-8"?>\n'
        f'<sitemapindex xmlns="{SITEMAP_NS}">{entries}</sitemapindex>\n'
    )


def legacy_pages(main: Path) -> list[str]:
    """The pages of main's en/, as paths below the site's root."""
    return sorted(p.relative_to(main).as_posix() for p in (main / "en").rglob("*.html"))


def assemble(main: Path, site: Path) -> dict:
    for needed in ("index.html", "404.html", "sitemap.xml", "version.json", "en"):
        if not (main / needed).exists():
            raise AssemblyError(f"main's build has no {needed}")
    if json.loads((main / "version.json").read_text(encoding="utf-8")).get("version") != "main":
        raise AssemblyError("the build given as main documents another version")
    address = site_address(main)
    if site.exists():
        raise AssemblyError(f"{site} exists already")
    shutil.copytree(main, site / "main")
    served = "main/"
    (site / "index.html").write_text(redirect_page(served), encoding="utf-8")
    shutil.copyfile(main / "404.html", site / "404.html")
    legacy = legacy_pages(main)
    for page in legacy:
        stub = site / page
        stub.parent.mkdir(parents=True, exist_ok=True)
        up = "../" * page.count("/")
        stub.write_text(redirect_page(f"{up}{served}{page}"), encoding="utf-8")
    versions = {
        "schema": 1,
        "versions": [{"version": "main", "path": "main/", "status": "development"}],
    }
    (site / "versions.json").write_text(json.dumps(versions, indent=2) + "\n", encoding="utf-8")
    (site / "sitemap.xml").write_text(sitemap_index(address, ["main/"]), encoding="utf-8")
    return {"served": served, "legacy": len(legacy), "versions": versions["versions"]}


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        print(__doc__, file=sys.stderr)
        return 2
    try:
        result = assemble(Path(argv[1]), Path(argv[2]))
    except AssemblyError as error:
        print(f"::error title=docs site::{error}")
        return 1
    print("## Docs site\n")
    print(
        f"The root serves {result['served']}; {result['legacy']} page(s) from before the versions redirect there.\n"
    )
    print("| Version | Path | Status |\n| --- | --- | --- |")
    for entry in result["versions"]:
        print(f"| {entry['version']} | {entry['path']} | {entry['status']} |")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
