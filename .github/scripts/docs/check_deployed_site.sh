#!/bin/sh
# Check a deployed documentation site: its root, a page path from before the
# site had versions (en/) and versions.json load; then, for each version that
# versions.json lists, its version.json names that version, its main pages
# and its sitemap load, and the sitemap's first URL lies under the version
# and loads too.
#
# Usage: check_deployed_site.sh <site>
#   site  the site's address, e.g. https://mavlink-m.dronecode.org/
#
# Environment: CHECK_RETRIES (default 5) and CHECK_RETRY_DELAY in seconds
# (default 10) set how often curl retries each request, since the CDN can lag
# behind a fresh deploy. Needs curl and jq.
set -eu

if [ $# -ne 1 ]; then
	echo "usage: $0 <site>" >&2
	exit 1
fi

site="${1%/}/"
retries=${CHECK_RETRIES:-5}
delay=${CHECK_RETRY_DELAY:-10}
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT

fetch() {
	curl --fail --silent --show-error --location \
		--retry "$retries" --retry-delay "$delay" --retry-all-errors "$@"
}

fail() {
	if [ "${GITHUB_ACTIONS:-}" = "true" ]; then
		echo "::error::$1"
	fi
	echo "$1" >&2
	exit 1
}

for path in "" en/; do
	fetch --output /dev/null "$site$path"
	echo "OK $site$path"
done
fetch --output "$work/versions.json" "${site}versions.json"
echo "OK ${site}versions.json"
jq -e 'any(.versions[]; .path == "main/")' "$work/versions.json" >/dev/null 2>&1 ||
	fail "versions.json does not list main/"
for version in $(jq -r '.versions[].path' "$work/versions.json"); do
	# The deploy writes main/ and release tags' directories, nothing else.
	echo "$version" | grep -Eqx 'main/|v(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)/' ||
		fail "versions.json lists '$version', which is no version's directory"
	fetch --output "$work/version.json" "$site${version}version.json"
	[ "$(jq -r .version "$work/version.json" 2>/dev/null)" = "${version%/}" ] ||
		fail "$site${version}version.json does not name ${version%/}"
	echo "OK $site${version}version.json"
	for page in "" en/ en/messages/military.html; do
		fetch --output /dev/null "$site$version$page"
		echo "OK $site$version$page"
	done
	fetch --output "$work/sitemap.xml" "$site${version}sitemap.xml"
	echo "OK $site${version}sitemap.xml"
	# sed reads to the end, so grep never writes into a closed pipe.
	first=$(grep -o '<loc>[^<]*</loc>' "$work/sitemap.xml" | sed -n '1s/<[^>]*>//gp' || true)
	case "$first" in
	"$site$version"?*)
		fetch --output /dev/null "$first"
		echo "OK $first"
		;;
	*)
		fail "sitemap URL '$first' is not under $site$version"
		;;
	esac
done
