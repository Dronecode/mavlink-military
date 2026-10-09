#!/bin/sh
# Download a release archive, check it against its SHA-256 and extract it.
# The workflows install their pinned tools this way: the checksum is what
# pins a release, since its assets can be re-uploaded under the same URL.
#
# Usage: fetch_release.sh <url> <sha256> <dest>
#   url     the archive; tar detects its compression (gzip, xz, ...)
#   sha256  the archive's expected SHA-256
#   dest    the directory to extract into, created if missing
set -eu

if [ $# -ne 3 ]; then
	echo "usage: $0 <url> <sha256> <dest>" >&2
	exit 1
fi

archive=$(mktemp)
trap 'rm -f "$archive"' EXIT
curl --fail --silent --show-error --location --output "$archive" "$1"
# sha256sum on Linux, shasum on macOS, whose sha256sum takes other options.
# Comparing the digest itself needs no --check, which they spell differently.
if command -v sha256sum >/dev/null && sha256sum --version >/dev/null 2>&1; then
	actual=$(sha256sum "$archive")
else
	actual=$(shasum -a 256 "$archive")
fi
actual=${actual%% *}
if [ "$actual" != "$2" ]; then
	echo "error: $1 does not have SHA-256 $2" >&2
	exit 1
fi
mkdir -p "$3"
tar -xf "$archive" -C "$3"
echo "$1: SHA-256 OK, extracted into $3"
