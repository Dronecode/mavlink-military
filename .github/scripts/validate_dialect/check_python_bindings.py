#!/usr/bin/env python3
"""Check the Python bindings mavgen generates for military.xml: the module
loads, and every message military.xml defines is in its mavlink_map, the
table the generated parser decodes by. A frame whose message ID is missing
from that table decodes as MAVLink_unknown, raw bytes without fields.

The module is imported from its file and needs only the standard library.

Usage: check_python_bindings.py <generated module> <military.xml>
"""

from __future__ import annotations

import importlib.machinery
import importlib.util
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from types import ModuleType


def load(path: str) -> ModuleType:
    """Import the module in the file at path, named after the file."""
    loader = importlib.machinery.SourceFileLoader(Path(path).stem, path)
    module = importlib.util.module_from_spec(importlib.util.spec_from_loader(loader.name, loader))
    loader.exec_module(module)
    return module


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        print(__doc__, file=sys.stderr)
        return 2
    mavlink_map = load(argv[1]).mavlink_map
    ids = {int(m.get("id")) for m in ET.parse(argv[2]).getroot().iter("message")}
    missing = sorted(ids - set(mavlink_map))
    if missing:
        print(f"dialect messages missing from the generated map: {missing}", file=sys.stderr)
        return 1
    print(
        f"{len(mavlink_map)} messages in the generated map, all {len(ids)} dialect messages present"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
