#!/bin/sh
# Print the generator pins as mavlink=<sha> and pymavlink=<sha> lines, the
# form GITHUB_OUTPUT takes, after checking that each is set once and is a
# full commit SHA.
#
# Usage: read_pins.sh <pins>
#   pins  the pins file, .github/mavlink-pins.env (KEY=value lines)
set -eu

if [ $# -ne 1 ]; then
	echo "usage: $0 <pins>" >&2
	exit 1
fi

pin() {
	value=$(sed -n "s/^$1=\([0-9a-f]\{40\}\)\$/\1/p" "$2")
	count=$(grep -c "^$1=" "$2" || true)
	if [ -z "$value" ] || [ "$count" -ne 1 ]; then
		echo "$2: $1 must be set once, to a full 40-character commit SHA" >&2
		exit 1
	fi
	echo "$value"
}

mavlink=$(pin MAVLINK_REF "$1")
pymavlink=$(pin PYMAVLINK_REF "$1")
echo "mavlink=$mavlink"
echo "pymavlink=$pymavlink"
