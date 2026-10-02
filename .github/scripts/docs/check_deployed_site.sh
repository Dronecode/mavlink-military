#!/bin/sh
# Check a deployed documentation site: its main pages and its sitemap load,
# and the sitemap's first URL lies under the site and loads too.
#
# Usage: check_deployed_site.sh <site>
#   site  the site's address, e.g. https://dronecode.github.io/mavlink-military/
#
# Environment: CHECK_RETRIES (default 5) and CHECK_RETRY_DELAY in seconds
# (default 10) set how often curl retries each request, since the CDN can lag
# behind a fresh deploy.
set -eu

if [ $# -ne 1 ]; then
	echo "usage: $0 <site>" >&2
	exit 1
fi

site="${1%/}/"
retries=${CHECK_RETRIES:-5}
delay=${CHECK_RETRY_DELAY:-10}
sitemap=$(mktemp)
trap 'rm -f "$sitemap"' EXIT

fetch() {
	curl --fail --silent --show-error --location \
		--retry "$retries" --retry-delay "$delay" --retry-all-errors "$@"
}

for path in "" en/ en/messages/military.html; do
	fetch --output /dev/null "$site$path"
	echo "OK $site$path"
done
fetch --output "$sitemap" "${site}sitemap.xml"
echo "OK ${site}sitemap.xml"

# sed reads to the end, so grep never writes into a closed pipe.
first=$(grep -o '<loc>[^<]*</loc>' "$sitemap" | sed -n '1s/<[^>]*>//gp' || true)
case "$first" in
"$site"?*)
	fetch --output /dev/null "$first"
	echo "OK $first"
	;;
*)
	if [ "${GITHUB_ACTIONS:-}" = "true" ]; then
		echo "::error::sitemap URL '$first' is not under $site"
	fi
	echo "sitemap URL '$first' is not under $site" >&2
	exit 1
	;;
esac
