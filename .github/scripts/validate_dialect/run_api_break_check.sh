#!/bin/sh
# Run mavlink's check_api_break.py in this repository and turn its result
# into a verdict: a break is a warning, or an error when enforcing, and a run
# that ends without the checker's verdict is an error either way. The
# checker's output goes to stdout, and to the step summary when
# GITHUB_STEP_SUMMARY is set.
#
# Usage: run_api_break_check.sh <checker> <enforce>
#   checker  mavlink's scripts/check_api_break.py
#   enforce  1 to fail on a break, 0 to report it
set -eu

if [ $# -ne 2 ]; then
	echo "usage: $0 <checker> <enforce>" >&2
	exit 1
fi

report() {
	# $1 = error or warning, $2 = title, $3 = message
	if [ "${GITHUB_ACTIONS:-}" = "true" ]; then
		echo "::$1 title=$2::$3"
	else
		echo "$1: $3" >&2
	fi
}

output=$(mktemp)
trap 'rm -f "$output"' EXIT
status=0
python3 "$1" >"$output" 2>&1 || status=$?
cat "$output"
if [ -n "${GITHUB_STEP_SUMMARY:-}" ]; then
	{
		echo "## mavlink API break check"
		echo
		echo '```text'
		cat "$output"
		echo '```'
	} >>"$GITHUB_STEP_SUMMARY"
fi

if [ "$status" -eq 0 ]; then
	exit 0
fi
# A break exits 1 after this line; any other exit is the tool failing.
if ! grep -q '^Name removals/changes detected in ' "$output"; then
	report error "API break check" "check_api_break.py exited $status without a verdict"
	exit "$status"
fi
message="check_api_break.py reports breaking changes"
if [ -n "${GITHUB_STEP_SUMMARY:-}" ]; then
	message="$message, listed in the step summary"
fi
if [ "$2" = 1 ]; then
	report error "API break" "$message"
	exit 1
fi
report warning "API break" "$message"
