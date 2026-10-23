#!/usr/bin/env python3
"""Assemble the documentation site that docs_deploy.yml deploys.

Usage: assemble_site.py <main> <site> <work>
  main  main's built pages, from docs.yml with DOCS_VERSION=main
  site  the directory to write the site into; it must not exist yet
  work  a directory for the downloads, created if missing

Run from a checkout of main, with gh (the command in GH, default "gh") and
GITHUB_REPOSITORY. The site holds:

- main/: main's pages, as docs.yml built them.
- <tag>/ for every published final release vX.Y.Z: that release's own pages,
  unpacked from the docs archive attached to it, never rebuilt. Each archive
  is checked first as a consumer checks a release file: its SHA256SUMS line;
  its SLSA provenance, with gh attestation verify against the bundle attached
  to the release, the generator workflow and commit that release.yml names at
  that tag, the tag and its commit as source, and release.yml at the tag as
  the workflow that built it; and the release and the asset with gh release
  verify and gh release verify-asset.
- index.html: a page that sends a visitor on to the version the root serves,
  the highest release not withdrawn, or main/ while there is none, keeping any
  #anchor; and 404.html, main's not-found page, whose links name main/ in full.
- A redirect page at every page path the site had before it had versions:
  each page of main's en/, at en/..., sends a visitor to the same page in the
  version the root serves, or in main/ where that version lacks the page.
- sitemap.xml: an index of each version's own sitemap.
- versions.json: the versions, for the version menu and banners: main
  (development), then the releases from the highest down, each latest,
  outdated or withdrawn, with the SHA-256 of the docs archive its pages come
  from. .github/release-status.json lists the withdrawn
  releases, each with its reason and decision link; a withdrawn release keeps
  its pages, with a banner, and the root never serves it.

Redirect pages name their targets relative to themselves, so the site works
below any base path. Anything missing or failing a check stops the assembly,
so a released version is never dropped, altered or served unverified. Prints
a Markdown summary.
"""

from __future__ import annotations

import hashlib
import html
import json
import os
import re
import shutil
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import NamedTuple

RELEASE_SCRIPTS = Path(__file__).resolve().parents[1] / "release"
sys.path.insert(0, str(RELEASE_SCRIPTS))
import archive  # noqa: E402
import gh_api  # noqa: E402
import release_publish  # noqa: E402

SITEMAP_NS = "http://www.sitemaps.org/schemas/sitemap/0.9"
TAG = re.compile(r"v(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)")  # ASCII digits only
STATUS_FILE = Path(".github/release-status.json")
GENERATOR = re.compile(r"^  (GENERATOR_WORKFLOW|GENERATOR_COMMIT): (\S+)$", re.M)
SUMS_LINE = re.compile(r"([0-9a-f]{64})  ([A-Za-z0-9._-]+)")


class AssemblyError(Exception):
    """Something that must stop the deploy."""


class Release(NamedTuple):
    tag: str
    key: tuple[int, int, int]

    @property
    def version(self) -> str:
        return self.tag[1:]


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


def withdrawn_releases(path: Path) -> dict[str, dict]:
    data = json.loads(path.read_text(encoding="utf-8")) if path.is_file() else {"withdrawn": {}}
    withdrawn = data.get("withdrawn")
    if not isinstance(withdrawn, dict):
        raise AssemblyError(f"{path}: withdrawn must map release tags to their reasons")
    for tag, entry in withdrawn.items():
        if TAG.fullmatch(tag) is None or not isinstance(entry, dict) or not entry.get("reason"):
            raise AssemblyError(f"{path}: {tag!r} needs to be a release tag with a reason")
    return withdrawn


def published(repo: str) -> list[Release]:
    """The published final releases, from the highest version down."""
    found, page = [], 1
    while True:
        entries = gh_api.api(f"repos/{repo}/releases?per_page=100&page={page}") or []
        for entry in entries:
            match = TAG.fullmatch(entry["tag_name"])
            if match and not entry["draft"] and not entry["prerelease"]:
                found.append(Release(entry["tag_name"], tuple(map(int, match.groups()))))
        if len(entries) < 100:
            return sorted(found, key=lambda r: r.key, reverse=True)
        page += 1


def release_generator(repo: str, tag: str) -> dict[str, str]:
    """The generator workflow and commit that release.yml names at a tag."""
    text = gh_api.run(
        "api", "-H", "Accept: application/vnd.github.raw",
        f"repos/{repo}/contents/.github/workflows/release.yml?ref={tag}",
    )  # fmt: skip
    found = dict(GENERATOR.findall(text))
    if set(found) != {"GENERATOR_WORKFLOW", "GENERATOR_COMMIT"}:
        raise AssemblyError(f"{tag}: release.yml at the tag names no generator workflow and commit")
    return found


def checked_archive(repo: str, release: Release, work: Path) -> Path:
    """A release's docs archive, once it verifies as a consumer would check it."""
    folder = work / release.tag
    folder.mkdir(parents=True, exist_ok=True)
    name = f"mavlink-m-{release.version}-docs.tar.gz"
    bundle = f"mavlink-m-{release.version}.intoto.jsonl"
    gh_api.run(
        "release", "download", release.tag, "--repo", repo, "--dir", str(folder), "--clobber",
        "--pattern", "SHA256SUMS", "--pattern", name, "--pattern", bundle,
    )  # fmt: skip
    lines = (folder / "SHA256SUMS").read_text(encoding="ascii").splitlines()
    sums = {m.group(2): m.group(1) for m in map(SUMS_LINE.fullmatch, lines) if m}
    if sums.get(name) != hashlib.sha256((folder / name).read_bytes()).hexdigest():
        raise AssemblyError(f"{release.tag}: {name} does not match its SHA256SUMS line")
    generator = release_generator(repo, release.tag)
    commit = gh_api.api(f"repos/{repo}/commits/{release.tag}")["sha"]
    env = {
        "GITHUB_REPOSITORY": repo, "GITHUB_REF": f"refs/tags/{release.tag}", "GITHUB_SHA": commit,
        "GENERATOR_WORKFLOW": generator["GENERATOR_WORKFLOW"], "GENERATOR_COMMIT": generator["GENERATOR_COMMIT"],
    }  # fmt: skip
    release_publish.verify(folder / name, folder / bundle, env)
    gh_api.run("release", "verify", release.tag, "--repo", repo)
    gh_api.run("release", "verify-asset", release.tag, str(folder / name), "--repo", repo)
    return folder / name


def unpack(release: Release, path: Path, site: Path) -> int:
    """Unpack a docs archive below <site>/<tag>/; the number of files."""
    target = site / release.tag
    files = archive.read(path, f"mavlink-m-{release.version}-docs")
    if "index.html" not in files:
        raise AssemblyError(f"{release.tag}: {path.name} has no index.html")
    for name, data in files.items():
        (target / name).parent.mkdir(parents=True, exist_ok=True)
        (target / name).write_bytes(data)
    return len(files)


def assemble(main: Path, site: Path, work: Path, repo: str) -> dict:
    for needed in ("index.html", "404.html", "sitemap.xml", "version.json", "en"):
        if not (main / needed).exists():
            raise AssemblyError(f"main's build has no {needed}")
    if json.loads((main / "version.json").read_text(encoding="utf-8")).get("version") != "main":
        raise AssemblyError("the build given as main documents another version")
    address = site_address(main)
    if site.exists():
        raise AssemblyError(f"{site} exists already")
    withdrawn = withdrawn_releases(STATUS_FILE)
    releases = published(repo)
    unknown = sorted(set(withdrawn) - {r.tag for r in releases})
    if unknown:
        raise AssemblyError(f"{STATUS_FILE} withdraws releases that are not published: {unknown}")
    shutil.copytree(main, site / "main")
    rows, digests = [], {}
    for release in releases:
        path = checked_archive(repo, release, work)
        digests[release.tag] = hashlib.sha256(path.read_bytes()).hexdigest()
        files = unpack(release, path, site)
        rows.append(
            f"| {release.tag} | {files} | SHA256SUMS, provenance, release and asset verified |"
        )
    latest = next((r for r in releases if r.tag not in withdrawn), None)
    served = f"{latest.tag}/" if latest else "main/"
    (site / "index.html").write_text(redirect_page(served), encoding="utf-8")
    shutil.copyfile(main / "404.html", site / "404.html")
    legacy = legacy_pages(main)
    for page in legacy:
        stub = site / page
        stub.parent.mkdir(parents=True, exist_ok=True)
        version = served if (site / served / page).is_file() else "main/"
        stub.write_text(redirect_page("../" * page.count("/") + version + page), encoding="utf-8")
    entries = [{"version": "main", "path": "main/", "status": "development"}]
    for release in releases:
        status = (
            "withdrawn"
            if release.tag in withdrawn
            else "latest" if release is latest else "outdated"
        )
        entries.append({"version": release.tag, "path": f"{release.tag}/", "status": status,
                        "docs_sha256": digests[release.tag]})  # fmt: skip
    versions = {"schema": 1, "versions": entries}
    (site / "versions.json").write_text(json.dumps(versions, indent=2) + "\n", encoding="utf-8")
    (site / "sitemap.xml").write_text(
        sitemap_index(address, [e["path"] for e in entries]), encoding="utf-8"
    )
    return {"served": served, "legacy": len(legacy), "versions": entries, "rows": rows}


def main(argv: list[str]) -> int:
    if len(argv) != 4:
        print(__doc__, file=sys.stderr)
        return 2
    failures = (
        AssemblyError,
        gh_api.GitHubError,
        release_publish.PublishError,
        archive.ArchiveError,
    )
    try:
        repo = os.environ["GITHUB_REPOSITORY"]
        result = assemble(Path(argv[1]), Path(argv[2]), Path(argv[3]), repo)
    except (*failures, KeyError, OSError, ValueError) as error:
        print(f"::error title=docs site::{error}")
        return 1
    print("## Docs site\n")
    print(
        f"The root serves {result['served']}; {result['legacy']} page(s) from before the versions redirect there.\n"
    )
    print("| Version | Path | Status |\n| --- | --- | --- |")
    for entry in result["versions"]:
        print(f"| {entry['version']} | {entry['path']} | {entry['status']} |")
    if result["rows"]:
        print("\n| Release | Files | Checks |\n| --- | --- | --- |")
        print("\n".join(result["rows"]))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
