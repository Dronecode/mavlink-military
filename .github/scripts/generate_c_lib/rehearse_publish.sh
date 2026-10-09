#!/bin/sh
# Rehearse publish_c_library.sh without touching the C library: clone it
# into a local bare repository, publish the headers through a clone of that,
# and print in Markdown what a real publish would push. The publish log goes
# to stderr.
#
# Usage: rehearse_publish.sh <source> <out> <library> <work>
#   source   checkout of this repository
#   out      directory produced by generate_c_headers.sh
#   library  URL of the C library repository, only read
#   work     empty directory for the local copies
set -eu

if [ $# -ne 4 ]; then
	echo "usage: $0 <source> <out> <library> <work>" >&2
	exit 1
fi

library=$3
bare=$4/c_library.git

git clone --quiet --bare "$library" "$bare"
git clone --quiet "$bare" "$4/c_library"
before=$(git -C "$bare" rev-parse HEAD)
"$(dirname "$0")/publish_c_library.sh" "$1" "$2" "$4/c_library" >&2
after=$(git -C "$bare" rev-parse HEAD)

echo "## C library publish rehearsal"
echo
if [ "$before" = "$after" ]; then
	echo "No change: $library already holds these headers."
else
	echo "Publishing these headers pushes this commit to $library:"
	echo
	echo '```text'
	git -C "$bare" show --stat --stat-count=40 --format='%s%n%n%b' "$after"
	echo '```'
fi
