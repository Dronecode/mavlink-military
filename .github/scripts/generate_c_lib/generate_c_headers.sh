#!/bin/sh
# Generate MAVLink 2 C headers for the MAVLink-M dialect.
#
# Usage: generate_c_headers.sh <source> <mavlink> <pymavlink> <out>
#   source     checkout of this repository
#   mavlink    checkout of mavlink/mavlink (provides common.xml and friends)
#   pymavlink  checkout of ArduPilot/pymavlink (provides mavgen)
#   out        output directory for the generated headers
set -eu

if [ $# -ne 4 ]; then
	echo "usage: $0 <source> <mavlink> <pymavlink> <out>" >&2
	exit 1
fi

source_dir=$1
mavlink_dir=$2
pymavlink_dir=$3
out_dir=$4
defs=$mavlink_dir/message_definitions/v1.0

# military.xml includes common.xml by relative path, so it has to sit next to
# the upstream definitions for mavgen to resolve it.
cp "$source_dir/military.xml" "$defs/"

python "$pymavlink_dir/tools/mavgen.py" \
	--lang=C \
	--wire-protocol=2.0 \
	--output="$out_dir" \
	"$defs/military.xml"

mkdir -p "$out_dir/message_definitions"
for xml in military common standard minimal; do
	cp "$defs/$xml.xml" "$out_dir/message_definitions/"
done
