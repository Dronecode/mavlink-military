#!/usr/bin/env python3
"""Generate the message reference pages from military.xml.

Uses the upstream MAVLink markdown generator (mavlink/doc/mavlink_xml_to_markdown.py),
the same one that produces https://mavlink.io/en/messages/, pinned to the
MAVLINK_REF used for the C headers in .github/workflows/generate_c_lib.yml.

Usage:
    generate_messages.py [--mavlink-dir DIR]

Without --mavlink-dir, mavlink/mavlink is cloned at the pinned ref into
docs/.cache/mavlink. Output goes to docs/en/messages/ (git-ignored).
Requires: beautifulsoup4, lxml.
"""

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
DOCS = os.path.dirname(HERE)
ROOT = os.path.dirname(DOCS)
OUT = os.path.join(DOCS, "en", "messages") + os.sep
REPO = "https://github.com/Dronecode/mavlink-military"

# Links in the upstream templates that point at devguide pages we don't host.
UPSTREAM_LINKS = {
    "../guide/define_xml_element.md": "https://mavlink.io/en/guide/define_xml_element.html",
    "../guide/xml_schema.md": "https://mavlink.io/en/guide/xml_schema.html",
    "../messages/README.md": "https://mavlink.io/en/messages/",
}

MILITARY_HEADER = f"""\
<!-- THIS FILE IS AUTO-GENERATED from military.xml by docs/scripts/generate_messages.py. Do not edit. -->

# Dialect: MAVLink-M (military.xml)

This page is a human-readable form of the dialect definition file
[military.xml]({REPO}/blob/main/military.xml).
To change a message, edit the XML and open a pull request.

Entities included from [common.xml](common.md) are listed as headings only, with a link to their full definition.

"""


def pinned_ref():
    wf = os.path.join(ROOT, ".github", "workflows", "generate_c_lib.yml")
    with open(wf) as f:
        m = re.search(r"^\s*MAVLINK_REF:\s*(\S+)", f.read(), re.M)
    if not m:
        sys.exit(f"MAVLINK_REF not found in {wf}")
    return m.group(1)


def fetch_mavlink(ref):
    dest = os.path.join(DOCS, ".cache", "mavlink")
    if not os.path.isdir(os.path.join(dest, ".git")):
        subprocess.check_call(["git", "init", "-q", dest])
        subprocess.check_call(
            ["git", "-C", dest, "remote", "add", "origin", "https://github.com/mavlink/mavlink.git"]
        )
    head = subprocess.run(
        ["git", "-C", dest, "rev-parse", "HEAD"], capture_output=True, text=True
    ).stdout.strip()
    if head != ref:
        subprocess.check_call(["git", "-C", dest, "fetch", "-q", "--depth", "1", "origin", ref])
        subprocess.check_call(["git", "-C", dest, "checkout", "-q", "FETCH_HEAD"])
    return dest


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--mavlink-dir", help="existing mavlink/mavlink checkout")
    args = parser.parse_args()

    mavlink_dir = args.mavlink_dir or fetch_mavlink(pinned_ref())
    sys.path.insert(0, os.path.join(mavlink_dir, "doc"))
    import mavlink_xml_to_markdown as gen

    upstream_header = gen.MAVXML.get_top_level_docs

    def top_level_docs(self, filename):
        text = upstream_header(self, filename)
        if filename == "military":
            # Keep the shared legend/style block, replace the upstream-dialect preamble.
            text = MILITARY_HEADER + text[text.index('<span id="mav2_extension_field">') :]
        return text

    gen.MAVXML.get_top_level_docs = top_level_docs

    # military.xml includes common.xml by relative path, so stage it next to the
    # upstream definitions it depends on.
    with tempfile.TemporaryDirectory() as defs:
        for name in ("common", "standard", "minimal"):
            shutil.copy(os.path.join(mavlink_dir, "message_definitions", "v1.0", f"{name}.xml"), defs)
        shutil.copy(os.path.join(ROOT, "military.xml"), defs)

        if os.path.isdir(OUT):
            shutil.rmtree(OUT)
        gen.XMLFiles(dialect="military", source_dir=defs + os.sep).generateDocs(OUT)

    for page in os.listdir(OUT):
        path = os.path.join(OUT, page)
        with open(path, encoding="utf-8") as f:
            text = f.read()
        for old, new in UPSTREAM_LINKS.items():
            text = text.replace(f"]({old}", f"]({new}")
        if page == "military.md":
            front = "---\neditLink_path: military.xml\n---\n\n"
        else:
            front = "---\neditLink: false\n---\n\n"
        with open(path, "w", encoding="utf-8") as f:
            f.write(front + text)


if __name__ == "__main__":
    main()
