#!/usr/bin/env python3
"""Check every SHA-256 digest that the metadata examples declare against the
exact bytes of the file it names, so an example never teaches a stale value.

- Each entry of the definition manifest example names its file by URI. A URI
  that pins a mavlink commit on raw.githubusercontent.com is fetched as it is;
  any other URI names the file of this repository with the same last path
  segment, at the top level or in component_metadata/.
- The catalogue example's definitionManifest is the manifest example.
- Each capabilityProfileRef in the catalogue example is the profile example
  with the same profileId and profileVersion.

Usage: check_example_digests.py [<repository root>]
"""

from __future__ import annotations

import hashlib
import json
import re
import sys
import urllib.request
from collections.abc import Callable, Iterator
from pathlib import Path

EXAMPLES = Path("component_metadata/examples")
MANIFEST = "definition-manifest.example.json"
CATALOGUE = "payloads.example.json"
PINNED_UPSTREAM = re.compile(
    r"https://raw\.githubusercontent\.com/mavlink/mavlink/[0-9a-f]{40}/\S+"
)


def fetch_upstream(uri: str) -> bytes:
    """The bytes at an upstream URI, which its pinned commit makes immutable."""
    with urllib.request.urlopen(uri, timeout=30) as response:
        return response.read()


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def repository_file(root: Path, uri: str) -> Path:
    """The file of this repository that a non-upstream URI names."""
    name = uri.rstrip("/").rsplit("/", 1)[-1]
    found = [p for p in (root / name, root / "component_metadata" / name) if p.is_file()]
    if len(found) != 1:
        raise LookupError(f"{uri} names {len(found)} files of this repository, not one")
    return found[0]


def profile_refs(node: object) -> Iterator[dict]:
    """Every object in the catalogue that references a profile by its digest."""
    if isinstance(node, dict):
        if {"profileId", "profileVersion", "sha256"} <= node.keys():
            yield node
        for value in node.values():
            yield from profile_refs(value)
    elif isinstance(node, list):
        for value in node:
            yield from profile_refs(value)


def check(root: Path, fetch: Callable[[str], bytes] | None = None) -> list[str]:
    """Problems found, one line each; an empty list means every digest matches. fetch reads
    an upstream URI, fetch_upstream unless a test passes another."""
    fetch = fetch or fetch_upstream
    examples = root / EXAMPLES
    problems = []

    def compare(what: str, declared: str, data: bytes) -> None:
        actual = sha256(data)
        if actual == declared:
            print(f"ok        {what}")
        else:
            problems.append(f"{what}: declares {declared}, the file hashes to {actual}")

    manifest = examples / MANIFEST
    for entry in json.loads(manifest.read_text(encoding="utf-8"))["files"]:
        uri = entry["uri"]
        what = f"{MANIFEST} {entry['role']} {uri}"
        try:
            if PINNED_UPSTREAM.fullmatch(uri):
                data = fetch(uri)
            else:
                data = repository_file(root, uri).read_bytes()
        except (LookupError, OSError) as error:
            problems.append(f"{what}: {error}")
            continue
        compare(what, entry["sha256"], data)

    catalogue = json.loads((examples / CATALOGUE).read_text(encoding="utf-8"))
    compare(
        f"{CATALOGUE} definitionManifest",
        catalogue["definitionManifest"]["sha256"],
        manifest.read_bytes(),
    )

    profiles: dict[tuple[str, int], Path] = {}
    for path in sorted(examples.glob("*.json")):
        document = json.loads(path.read_text(encoding="utf-8"))
        if isinstance(document, dict) and {"profileId", "profileVersion"} <= document.keys():
            key = (document["profileId"], document["profileVersion"])
            if key in profiles:
                problems.append(f"{path.name} and {profiles[key].name} are both profile {key}")
            profiles[key] = path
    for ref in profile_refs(catalogue):
        key = (ref["profileId"], ref["profileVersion"])
        what = f"{CATALOGUE} capabilityProfileRef {key[0]} version {key[1]}"
        if key not in profiles:
            problems.append(f"{what}: no profile example has this profileId and profileVersion")
            continue
        compare(what, ref["sha256"], profiles[key].read_bytes())

    return problems


def main(argv: list[str]) -> int:
    if len(argv) > 2:
        print(__doc__, file=sys.stderr)
        return 2
    problems = check(Path(argv[1] if len(argv) == 2 else "."))
    for problem in problems:
        print(f"MISMATCH  {problem}", file=sys.stderr)
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
