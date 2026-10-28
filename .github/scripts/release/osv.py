#!/usr/bin/env python3
"""The release's vulnerability record: what OSV knows about each component.

One batch query to the OSV API (OSV_URL, default https://api.osv.dev/v1/querybatch)
asks about every component the SBOM lists that OSV can match: the generator and
the MAVLink definitions by commit, lxml as a PyPI package and every npm package
installed for the docs build. The record lists each component with the IDs of
the advisories found, "none found" included, and the UTC time of the query. It
does not block a release: which findings should, and how they are handled, is
for the maintainers to set; they read the record in the release's evidence
and in its run's summary. A failed query fails, so a release never carries a record that was not made.
"""

from __future__ import annotations

import json
import os
import time
import urllib.request
from datetime import datetime, timezone

OSV_URL = "https://api.osv.dev/v1/querybatch"


class OsvError(Exception):
    """A query that failed for good."""


def components(plan: dict, tools: dict, npm: list[dict]) -> list[tuple[str, dict]]:
    pins = plan["pins"]
    found = [
        (f"pkg:github/{plan['generator']['repository']}@{pins['pymavlink']}", {"commit": pins["pymavlink"]}),
        (f"pkg:github/mavlink/mavlink@{pins['mavlink']}", {"commit": pins["mavlink"]}),
        (f"pkg:pypi/lxml@{tools['lxml']}", {"package": {"name": "lxml", "ecosystem": "PyPI"}, "version": tools["lxml"]}),
    ]  # fmt: skip
    for item in npm:
        if item["key"]:
            name, version = item["name"], item["version"]
            found.append(
                (
                    f"npm:{name}@{version}",
                    {"package": {"name": name, "ecosystem": "npm"}, "version": version},
                )
            )
    return found


def post(url: str, body: dict) -> dict:
    request = urllib.request.Request(
        url, data=json.dumps(body).encode(), headers={"Content-Type": "application/json"}
    )
    with urllib.request.urlopen(request, timeout=60) as response:
        return json.loads(response.read())


def ask(send, url: str, body: dict, attempts: int, delay: float) -> dict:
    """send(url, body), retried with growing delays; OsvError once the last attempt fails."""
    for attempt in range(1, attempts + 1):
        try:
            return send(url, body)
        except (OSError, ValueError) as error:
            if attempt == attempts:
                raise OsvError(f"the OSV query failed: {error}") from error
            time.sleep(delay * attempt)
    raise AssertionError("unreachable")  # pragma: no cover - the loop returns or raises


def record(
    plan: dict, tools: dict, npm: list[dict], send=post, attempts: int = 3, delay: float = 5.0
) -> dict:
    url = os.environ.get("OSV_URL", OSV_URL)
    asked = components(plan, tools, npm)
    answer = ask(send, url, {"queries": [query for _, query in asked]}, attempts, delay)
    results = answer.get("results", [])
    if len(results) != len(asked):
        raise OsvError(f"OSV answered {len(results)} of {len(asked)} queries")
    rows = []
    for (component, _), result in zip(asked, results):
        ids = sorted(v["id"] for v in result.get("vulns", []))
        rows.append({
            "component": component, "findings": ids,
            "complete": "next_page_token" not in result,
            "disposition": "listed for review" if ids else "none found",
        })  # fmt: skip
    return {
        "source": "OSV",
        "endpoint": url,
        "queried": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ"),
        "components": rows,
        "with_findings": sum(1 for r in rows if r["findings"]),
    }
