#!/usr/bin/env python3
"""Compare a regeneration of the C headers with a clone of the C library.

Usage: compare_library.py <regeneration> <library>

The two trees must hold the same files with the same bytes. Three things
may differ: the library's .git directory, the README.md and LICENSE at the
library's root, which the publish leaves alone, and the date mavgen stamps
into each version.h. That line counts as the date only in the exact form
mavgen writes it, so a line that carries anything after the date, or a
second such line, differs like any other change. Every entry has to be a
regular file: a symbolic link, or any other kind of entry, differs too.

Exit status: 0 when the trees are equal, 1 when they differ (each path is
listed after a fixed word, with %, CR and LF escaped, so no name in the
library can read as a workflow command), 2 on a usage error.
"""

from __future__ import annotations

import os
import re
import sys
from pathlib import Path

# The library's own files at its root, which no regeneration writes.
LIBRARY_ONLY = {"README.md", "LICENSE"}
# The generation date, exactly as mavgen writes it, in each version.h.
BUILD_DATE = re.compile(rb'^#define MAVLINK_BUILD_DATE "[A-Za-z0-9 :]*"$', re.MULTILINE)


def escape(value: str) -> str:
    """Keep a path on one line, as workflow commands escape their data."""
    return value.replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")


def annotate(message: str) -> None:
    if os.environ.get("GITHUB_ACTIONS") == "true":
        print(f"::error title=C library::{message}")
    else:
        print(f"error: {message}", file=sys.stderr)


def tree(root: Path) -> tuple[dict[str, Path], list[str]]:
    """The regular files below root by their path relative to it, and the
    paths of every other entry; the .git directory at root is left out."""
    files: dict[str, Path] = {}
    others: list[str] = []
    for directory, dirs, names in os.walk(root):
        here = Path(directory)
        if here == root and ".git" in dirs:
            dirs.remove(".git")
        for name in [*dirs, *names]:
            path = here / name
            relative = path.relative_to(root).as_posix()
            if path.is_symlink() or not (path.is_file() or path.is_dir()):
                others.append(relative)
            elif path.is_file():
                files[relative] = path
    return files, others


def content(relative: str, path: Path) -> bytes:
    data = path.read_bytes()
    if relative.rsplit("/", 1)[-1] == "version.h":
        data = BUILD_DATE.sub(b'#define MAVLINK_BUILD_DATE ""', data)
    return data


def differences(regeneration: Path, library: Path) -> list[str]:
    ours, our_others = tree(regeneration)
    theirs, their_others = tree(library)
    found = [f"not a regular file: {path}" for path in sorted({*our_others, *their_others})]
    found += [f"only in the regeneration: {path}" for path in sorted(ours.keys() - theirs.keys())]
    found += [
        f"only in the library: {path}"
        for path in sorted(theirs.keys() - ours.keys())
        if path not in LIBRARY_ONLY
    ]
    found += [
        f"differs: {path}"
        for path in sorted(ours.keys() & theirs.keys())
        if content(path, ours[path]) != content(path, theirs[path])
    ]
    return [escape(line) for line in found]


def main(argv: list[str]) -> int:
    if len(argv) != 2 or not all(Path(arg).is_dir() for arg in argv):
        print("usage: compare_library.py <regeneration> <library>", file=sys.stderr)
        return 2
    found = differences(Path(argv[0]), Path(argv[1]))
    if not found:
        print("The library equals the regeneration, apart from the build date.")
        return 0
    for line in found:
        print(line)
    annotate(f"the library differs from a regeneration at main in {len(found)} path(s)")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
