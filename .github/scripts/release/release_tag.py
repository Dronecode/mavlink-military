#!/usr/bin/env python3
"""Check that the release tag is GPG-signed by the administrator who pushed it.

Usage: release_tag.py

Run by the preflight job of a run that may publish, for the tag
GITHUB_REF_NAME of GITHUB_REPOSITORY, which GITHUB_ACTOR pushed. Read-only,
through gh_api, it requires:

- the tag is annotated: its ref names a tag object, not a commit;
- GitHub verifies the tag's signature, which it does only when the signing
  key is registered on the GitHub account that has the tagger's email
  address verified;
- the signature is an OpenPGP one, not an SSH or S/MIME one;
- the key that made it, as gpg reads it from the signature (GPG names the
  command, default "gpg"), is one of the GPG keys or subkeys GITHUB_ACTOR has
  registered on GitHub, so the account that pushed the tag also signed it.

The tag ruleset lets only the repository's administrators push a tag, so a
release takes an administrator's GitHub account and their private key. It
prints the key ID and exits 1 on any shortfall or failed read.
"""

from __future__ import annotations

import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import gh_api  # noqa: E402

PGP = "-----BEGIN PGP SIGNATURE-----"
KEY_ID = re.compile(r"\bkeyid ([0-9A-F]{16})\b")


class TagError(Exception):
    """A shortfall that must stop the release."""


def signing_key(signature: str) -> str:
    """The long key ID that made the signature, as gpg reads it, without verifying it."""
    with tempfile.TemporaryDirectory() as home:
        result = subprocess.run(
            [os.environ.get("GPG", "gpg"), "--batch", "--list-packets"],
            input=signature,
            capture_output=True,
            text=True,
            check=False,
            env={**os.environ, "GNUPGHOME": home},
        )
    found = set(KEY_ID.findall(result.stdout))
    if len(found) != 1:
        raise TagError(f"gpg reads no single signing key from the tag's signature: {sorted(found)}")
    return found.pop()


def check(env: dict) -> str:
    repo, tag, actor = env["GITHUB_REPOSITORY"], env["GITHUB_REF_NAME"], env["GITHUB_ACTOR"]
    ref = gh_api.api(f"repos/{repo}/git/ref/tags/{tag}")["object"]
    if ref["type"] != "tag":
        raise TagError(f"{tag} is a lightweight tag; releases come from signed tags (git tag -s)")
    verification = gh_api.api(f"repos/{repo}/git/tags/{ref['sha']}").get("verification") or {}
    if verification.get("verified") is not True:
        raise TagError(
            f"GitHub does not verify the signature of {tag} ({verification.get('reason')}); "
            "sign it with git tag -s and a GPG key on your GitHub account"
        )
    signature = verification.get("signature") or ""
    if not signature.startswith(PGP):
        raise TagError(f"{tag} is not signed with GPG; a release takes an OpenPGP signature")
    key = signing_key(signature)
    keys = gh_api.api(f"users/{actor}/gpg_keys?per_page=100") or []
    ids = {k["key_id"].upper() for k in keys}
    ids |= {s["key_id"].upper() for k in keys for s in k.get("subkeys") or []}
    if key not in ids:
        raise TagError(f"{tag} is signed with key {key}, which is not a GPG key of {actor}")
    return f"{tag} is signed with GPG key {key} of {actor}, who pushed it, and GitHub verifies it"


def main(argv: list[str]) -> int:
    if len(argv) != 1:
        print(__doc__, file=sys.stderr)
        return 2
    try:
        print(check(dict(os.environ)))
    except (TagError, gh_api.GitHubError, KeyError) as error:
        print(f"::error title=release tag::{error}")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
