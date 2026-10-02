#!/bin/sh
# Sync generated headers into a checkout of the C library repository, commit
# and push. The commit subject mirrors the source commit so the C library log
# reads like this repository's log.
#
# Usage: publish_c_library.sh <source> <out> <c_library>
#   source     checkout of this repository
#   out        directory produced by generate_c_headers.sh
#   c_library  checkout of the C library repository, with push access
#
# Environment: MAVLINK_REF, PYMAVLINK_REF, and the GitHub Actions defaults
# GITHUB_EVENT_NAME, GITHUB_REPOSITORY, GITHUB_SERVER_URL.
set -eu

if [ $# -ne 3 ]; then
	echo "usage: $0 <source> <out> <c_library>" >&2
	exit 1
fi

source_dir=$1
out_dir=$2
c_library_dir=$3

sha=$(git -C "$source_dir" rev-parse HEAD)
short=$(git -C "$source_dir" rev-parse --short HEAD)
subject=$(git -C "$source_dir" log -1 --format=%s)

# GitHub merge commits: use the PR title from the body instead.
pr=$(printf '%s\n' "$subject" | sed -n 's/^Merge pull request #\([0-9][0-9]*\).*/\1/p')
if [ -n "$pr" ]; then
	title=$(git -C "$source_dir" log -1 --format=%b | sed -n '1{/./p;}')
	if [ -n "$title" ]; then
		subject="$title (#$pr)"
	fi
fi

if [ "${GITHUB_EVENT_NAME:-}" = "workflow_dispatch" ]; then
	subject="Regenerate: $subject"
fi

rsync -a --delete \
	--exclude .git --exclude README.md --exclude LICENSE \
	"$out_dir/" "$c_library_dir/"

cd "$c_library_dir"
git config user.name "github-actions[bot]"
git config user.email "41898282+github-actions[bot]@users.noreply.github.com"
git add --all
if git diff --cached --quiet; then
	echo "No changes to commit."
	exit 0
fi

git commit -F - <<MSG
$subject

Generated from $GITHUB_REPOSITORY@$short
$GITHUB_SERVER_URL/$GITHUB_REPOSITORY/commit/$sha

mavlink:   $MAVLINK_REF
pymavlink: $PYMAVLINK_REF
MSG

git push
