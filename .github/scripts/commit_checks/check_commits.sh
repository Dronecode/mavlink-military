#!/bin/sh
# Check commit subjects or a PR title against the convention in
# CONTRIBUTING.md: type(scope)!: description, at most 72 characters.
#
# Usage:
#   check_commits.sh <revision-range>   e.g. origin/main..HEAD
#   check_commits.sh --title "<PR title>"
#
# Every subject needs a scope. For ci it is a workflow basename under
# .github/workflows; otherwise an upper-case scope must be defined in
# military.xml or military_extensions.xml, or a lower-case one is an area.

set -eu

# Character ranges such as [A-Z] must not follow locale collation.
export LC_ALL=C

types='feat|fix|docs|ci|chore'
areas='dialect|ids|private|site|repo'
pattern="^($types)\\(([A-Z][A-Z0-9_]*|[a-z][a-z0-9_-]*)\\)!?: [^ ].{3,}\$"

root=$(git rev-parse --show-toplevel)
failed=0

report() {
	# $1 = label, $2 = subject, $3 = reason
	if [ "${GITHUB_ACTIONS:-}" = "true" ]; then
		echo "::error title=$1::$3: $2"
	else
		echo "error: $1: $3: $2" >&2
	fi
	failed=1
}

check() {
	label=$1
	subject=$2

	case $subject in
	'Revert "'*) return ;;
	esac

	if [ "${#subject}" -gt 72 ]; then
		report "$label" "$subject" "longer than 72 characters"
	fi

	if ! printf '%s\n' "$subject" | grep -Eq "$pattern"; then
		report "$label" "$subject" "not in type(scope): description form (see CONTRIBUTING.md)"
		return
	fi

	type=${subject%%[(!:]*}
	scope=$(printf '%s\n' "$subject" | sed -n 's/^[a-z]*(\([^)]*\)).*/\1/p')

	if [ "$type" = ci ]; then
		if [ ! -f "$root/.github/workflows/$scope.yml" ]; then
			report "$label" "$subject" "ci scope must name a workflow in .github/workflows (e.g. ci(generate_c_lib))"
		fi
		return
	fi

	case $scope in
	[A-Z]*)
		if ! grep -Fqs "name=\"$scope\"" "$root/military.xml" "$root/military_extensions.xml"; then
			report "$label" "$subject" "scope $scope is not defined in military.xml or military_extensions.xml"
		fi
		;;
	*)
		if ! printf '%s\n' "$scope" | grep -Eqx "$areas"; then
			report "$label" "$subject" "scope $scope is not an XML name or one of: $areas"
		fi
		;;
	esac
}

if [ "${1:-}" = "--title" ]; then
	[ $# -eq 2 ] || { echo "usage: $0 --title <title>" >&2; exit 2; }
	check "PR title" "$2"
else
	[ $# -eq 1 ] || { echo "usage: $0 <revision-range> | --title <title>" >&2; exit 2; }
	list=$(mktemp)
	trap 'rm -f "$list"' EXIT
	git log --no-merges --format='%h %s' "$1" >"$list"
	while read -r sha subject; do
		check "$sha" "$subject"
	done <"$list"
fi

exit "$failed"
