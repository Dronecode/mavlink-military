#!/usr/bin/env python3
"""Deterministic .tar.gz archives: the same files give the same bytes.

Entries are sorted by path, each directory before what it holds; the format is
USTAR, so no PAX header records anything (a name that does not fit fails);
every entry has the mtime given (the release commit's time), uid and gid 0 and
no owner names; files are 0644 and directories 0755; gzip writes no file name
and mtime 0, at level 9. The bytes of the .tar.gz also depend on the deflate
implementation, so write() returns the SHA-256 of the uncompressed tar too,
which proves the same content wherever another zlib compresses it differently.
"""

from __future__ import annotations

import gzip
import hashlib
import io
import tarfile
from pathlib import PurePosixPath


class ArchiveError(Exception):
    """An archive that cannot be written or read as the release needs."""


def write(path, top: str, files: dict[str, bytes], mtime: int) -> dict:
    """Write files (archive path below top: bytes) to path; its digests and file count."""
    names = set()
    for name in files:
        parts = PurePosixPath(name).parts
        if not parts or name != "/".join(parts) or any(p in ("", ".", "..") for p in parts):
            raise ArchiveError(f"{name!r} is not a plain relative path")
        names.update("/".join(parts[:i]) for i in range(1, len(parts)))
    entries = [(top, None)] + sorted(
        [(f"{top}/{d}", None) for d in names] + [(f"{top}/{n}", data) for n, data in files.items()]
    )
    raw = io.BytesIO()
    with tarfile.open(fileobj=raw, mode="w", format=tarfile.USTAR_FORMAT) as tar:
        for name, data in entries:
            info = tarfile.TarInfo(name)
            info.mtime, info.uid, info.gid, info.uname, info.gname = mtime, 0, 0, "", ""
            if data is None:
                info.type, info.mode = tarfile.DIRTYPE, 0o755
            else:
                info.size, info.mode = len(data), 0o644
            try:
                tar.addfile(info, io.BytesIO(data) if data is not None else None)
            except ValueError as error:
                raise ArchiveError(f"{name}: {error}") from error
    stream = raw.getvalue()
    with open(path, "wb") as out:
        with gzip.GzipFile(filename="", mode="wb", fileobj=out, mtime=0, compresslevel=9) as gz:
            gz.write(stream)
    return {"tar_sha256": hashlib.sha256(stream).hexdigest(), "files": len(files)}


def read(path, top: str) -> dict[str, bytes]:
    """The regular files of an archive below its top directory; anything else fails."""
    files = {}
    with tarfile.open(path, "r:gz") as tar:
        for member in tar:
            parts = PurePosixPath(member.name).parts
            if member.name.startswith("/") or not parts or parts[0] != top or ".." in parts:
                raise ArchiveError(f"{member.name!r} is not under {top}/")
            if member.isfile():
                files["/".join(parts[1:])] = tar.extractfile(member).read()
            elif not member.isdir():
                raise ArchiveError(f"{member.name!r} is neither a file nor a directory")
    return files
