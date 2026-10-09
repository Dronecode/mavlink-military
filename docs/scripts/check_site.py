#!/usr/bin/env python3
"""Check the built documentation site before it is deployed.

Run from docs/ after `npm run docs:build`, with the DOCS_BASE and
DOCS_HOSTNAME the build used (docs.yml sets both for CI). It reads the
site from .vitepress/dist, or from the directory given as its argument.
It checks:

- sitemap.xml: every URL starts with the site's address, DOCS_HOSTNAME
  with a trailing slash, and names a page the build produced.
- Links between pages: every link to a page of this site names a page
  the build produced, and every #anchor names an id on that page.

A dead link, or a dead anchor on a hand-written page, fails the check.
Dead anchors in the generated message reference (en/messages/) are
reported as warnings only: they come from the upstream generator, which
links the names of included common.xml entities to anchors that the
dialect page does not have.
"""

from __future__ import annotations

import os
import sys
from collections import Counter
import xml.etree.ElementTree as ET
from html.parser import HTMLParser
from pathlib import Path
from urllib.parse import unquote, urljoin, urlsplit

DIST = Path(__file__).resolve().parents[1] / ".vitepress" / "dist"
GENERATED = "en/messages/"
SITEMAP_NS = "{http://www.sitemaps.org/schemas/sitemap/0.9}"


class Page(HTMLParser):
    """The ids a page defines and the links it contains."""

    def __init__(self) -> None:
        super().__init__()
        self.ids: set[str] = set()
        self.links: list[str] = []

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        values = dict(attrs)
        if values.get("id"):
            self.ids.add(values["id"])
        if tag == "a":
            if values.get("name"):
                self.ids.add(values["name"])
            if values.get("href"):
                self.links.append(values["href"])


def slash(value: str) -> str:
    return value if value.endswith("/") else value + "/"


def annotate(level: str, message: str) -> None:
    """Print a GitHub Actions annotation, escaped as workflow commands need."""
    message = message.replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")
    print(f"::{level} title=docs site::{message}")


def page_file(rel: str) -> str:
    """Map a site path below the base to the file the build writes for it."""
    if rel == "" or rel.endswith("/"):
        return rel + "index.html"
    return rel


def main(argv: list[str]) -> int:
    dist = Path(argv[1]) if len(argv) > 1 else DIST
    base = slash("/" + os.environ.get("DOCS_BASE", "/").strip("/"))
    hostname = slash(
        os.environ.get("DOCS_HOSTNAME", "https://dronecode.github.io/mavlink-military")
    )
    if not (dist / "index.html").is_file():
        print(f"ERROR: no built site in {dist}; run npm run docs:build first", file=sys.stderr)
        return 1

    pages: dict[str, Page] = {}
    for path in sorted(dist.rglob("*.html")):
        page = Page()
        page.feed(path.read_text(encoding="utf-8"))
        pages[path.relative_to(dist).as_posix()] = page

    errors: list[str] = []
    warnings: list[str] = []

    sitemap = dist / "sitemap.xml"
    locations: list[str] = []
    if sitemap.is_file():
        locations = [loc.text or "" for loc in ET.parse(sitemap).getroot().iter(f"{SITEMAP_NS}loc")]
    else:
        errors.append("sitemap.xml: the build wrote no sitemap")
    for loc in locations:
        if not loc.startswith(hostname):
            errors.append(f"sitemap.xml: {loc} is not under the site address {hostname}")
        elif page_file(loc[len(hostname) :]) not in pages:
            errors.append(f"sitemap.xml: {loc} names no page in the build")

    links = 0
    for name, page in pages.items():
        here = base + name
        for href in page.links:
            parts = urlsplit(urljoin(here, href))
            if parts.scheme or parts.netloc or not parts.path.startswith(base):
                continue  # another site, or outside this one
            links += 1
            target = page_file(unquote(parts.path[len(base) :]))
            if target not in pages:
                if not (dist / target).is_file():  # downloads and other assets are files too
                    errors.append(f"{name}: link {href} names no page in the build")
                continue
            anchor = unquote(parts.fragment)
            if anchor and anchor not in pages[target].ids:
                finding = f"{name}: link {href} names no anchor #{anchor} on {target}"
                (warnings if name.startswith(GENERATED) else errors).append(finding)

    for finding in errors:
        annotate("error", finding)
    per_page = Counter(finding.split(":", 1)[0] for finding in warnings)
    for name, count in sorted(per_page.items()):
        annotate(
            "warning",
            f"{name}: {count} link(s) name an anchor the page lacks "
            "(from the upstream reference generator)",
        )
    verdict = (
        f"{len(pages)} pages, {len(locations)} sitemap URLs and {links} links checked: "
        f"{len(errors)} error(s), {len(warnings)} dead anchor(s) in the generated reference"
    )
    print(verdict)

    summary = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary:
        with open(summary, "a", encoding="utf-8") as out:
            out.write(f"## Docs site check\n\n{verdict}\n\n")
            for finding in errors:
                out.write(f"- {finding}\n")
            if warnings:
                out.write(
                    "\n<details><summary>Dead anchors in the generated reference</summary>\n\n"
                )
                out.write("".join(f"- {finding}\n" for finding in warnings))
                out.write("\n</details>\n")
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
