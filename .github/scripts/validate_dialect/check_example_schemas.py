#!/usr/bin/env python3
"""Check that the metadata examples are valid metadata: each one validates
against its schema, and the catalogue and profile examples meet the rules
those schemas state but their structure cannot enforce.

- payloads.example.json validates against payloads.schema.json, and
  definition-manifest.example.json against definition-manifest.schema.json.
- Each capability-profile*.example.json validates against the
  capabilityProfileDocument definition of payloads.schema.json.
- events.example.json and general.example.json are upstream Component
  Metadata types, which this repository has no schema for; any other example
  without a schema here is reported, so no example goes unchecked.
- No JSON object repeats a key.
- The catalogue repeats no payloadId, no functionId within a payload, no
  inhibitId or measurementId within a function, and no instanceKey or
  constraintKey.
- A profile repeats no propertyId, actionId, bindingId, propertyKey,
  actionKey, bindingKey, resourceKey, constraintKey, eventId, or outputId,
  and the profiles bound to one function declare no propertyId, actionId,
  bindingId, eventId, or outputId twice between them.
- Each catalogue constraint member names a bound instanceKey and a key the
  profile bound under it declares, the members name at least two
  instanceKeys, and an owner is one of the members.
- Each object an inhibition's prevents lists names an instanceKey bound to
  that inhibition's function and a key the profile bound under it declares.

A capabilityProfileRef is resolved to the profile example with the same
profileId and profileVersion, as check_example_digests.py resolves it.

Requires jsonschema, at the version pinned in requirements.txt beside this
script.

Usage: check_example_schemas.py [<repository root>]
"""

from __future__ import annotations

import json
import sys
from collections import Counter
from collections.abc import Iterable, Iterator
from pathlib import Path
from typing import Any

import jsonschema
import jsonschema.validators
import referencing
import referencing.jsonschema

METADATA = Path("component_metadata")
EXAMPLES = METADATA / "examples"
CATALOGUE = "payloads.example.json"
SCHEMAS = {
    CATALOGUE: "payloads.schema.json",
    "definition-manifest.example.json": "definition-manifest.schema.json",
}
PROFILE_PREFIX = "capability-profile"
PROFILE_DEFINITION = "/definitions/capabilityProfileDocument"
UPSTREAM_TYPES = {"events.example.json", "general.example.json"}

PROFILE_KEYS = (
    ("propertyId", "properties"),
    ("actionId", "actions"),
    ("bindingId", "bindings"),
    ("propertyKey", "properties"),
    ("actionKey", "actions"),
    ("bindingKey", "bindings"),
    ("resourceKey", "resources"),
    ("constraintKey", "constraints"),
    ("eventId", "events"),
    ("outputId", "outputs"),
)
COMPOSED_KEYS = ("propertyId", "actionId", "bindingId", "eventId", "outputId")


class DuplicateKey(ValueError):
    pass


def reject_duplicates(pairs: list[tuple[str, object]]) -> dict:
    keys = Counter(key for key, _ in pairs)
    repeated = sorted(key for key, count in keys.items() if count > 1)
    if repeated:
        raise DuplicateKey(f"repeats the key {', '.join(repeated)}")
    return dict(pairs)


def load(path: Path) -> Any:
    return json.loads(path.read_text(encoding="utf-8"), object_pairs_hook=reject_duplicates)


def repeated(values: Iterable[object]) -> list[object]:
    """Each value that occurs more than once, in first-seen order."""
    counts = Counter(values)
    return [value for value in counts if counts[value] > 1]


def declarations(profile: dict, collection: str) -> Iterator[dict]:
    """The entries of one of a profile's arrays. Bindings are declared inside
    properties and actions, so "bindings" gathers them from both."""
    if collection != "bindings":
        yield from profile.get(collection, [])
        return
    for item in (*profile.get("properties", []), *profile.get("actions", [])):
        yield from item.get("bindings", [])


def profile_problems(name: str, profile: dict) -> list[str]:
    problems = []
    for key, collection in PROFILE_KEYS:
        values = [d[key] for d in declarations(profile, collection) if key in d]
        for value in repeated(values):
            problems.append(f"{name}: {key} {value!r} is declared more than once")
    return problems


def member_problem(member: dict, refs: dict[str, dict], profiles: dict) -> str | None:
    """Why a catalogueConstraintMember does not resolve, or None if it does."""
    ref = refs.get(member["instanceKey"])
    if ref is None:
        return f"instanceKey {member['instanceKey']!r} has no binding in the catalogue"
    profile = profiles.get((ref["profileId"], ref["profileVersion"]))
    if profile is None:
        return None  # reported once, for the reference itself
    for key, collection in (("actionKey", "actions"), ("propertyKey", "properties")):
        if key in member and member[key] not in {d.get(key) for d in profile.get(collection, [])}:
            return (
                f"{key} {member[key]!r} is not declared by profile {ref['profileId']} "
                f"version {ref['profileVersion']}, bound under {member['instanceKey']!r}"
            )
    return None


def catalogue_problems(catalogue: dict, profiles: dict, present: set) -> list[str]:
    """profiles holds the valid profile examples; present also names those that
    failed validation, whose problems are already reported."""
    problems = []

    def problem(where: str, text: str) -> None:
        problems.append(f"{CATALOGUE}: {where}: {text}")

    payloads = catalogue.get("payloads", [])
    for value in repeated(p["payloadId"] for p in payloads):
        problem("payloads", f"payloadId {value} is repeated")

    refs: dict[str, dict] = {}
    for payload in payloads:
        where = f"payload {payload['payloadId']}"
        functions = payload.get("functions", [])
        for value in repeated(f["functionId"] for f in functions):
            problem(where, f"functionId {value} is repeated")
        for function in functions:
            fwhere = f"{where} function {function['functionId']}"
            for key, collection in (("inhibitId", "inhibitions"), ("measurementId", "measurements")):
                for value in repeated(item[key] for item in function.get(collection, [])):
                    problem(fwhere, f"{key} {value} is repeated")

            bound = function.get("capabilityProfiles", [])
            for ref in bound:
                if ref["instanceKey"] in refs:
                    problem(fwhere, f"instanceKey {ref['instanceKey']!r} is repeated")
                refs.setdefault(ref["instanceKey"], ref)
                if (ref["profileId"], ref["profileVersion"]) not in present:
                    problem(
                        fwhere,
                        f"no profile example is {ref['profileId']} version {ref['profileVersion']}",
                    )

            documents = [
                profiles[(r["profileId"], r["profileVersion"])]
                for r in bound
                if (r["profileId"], r["profileVersion"]) in profiles
            ]
            for key in COMPOSED_KEYS:
                collection = next(c for k, c in PROFILE_KEYS if k == key)
                # Within one document, profile_problems reports a repeat.
                values = [
                    value
                    for document in documents
                    for value in {d[key] for d in declarations(document, collection) if key in d}
                ]
                for value in repeated(values):
                    problem(fwhere, f"{key} {value!r} is declared by more than one bound profile")

            own = {ref["instanceKey"] for ref in bound}
            for inhibition in function.get("inhibitions", []):
                for item in inhibition["prevents"]:
                    if not isinstance(item, dict):
                        continue
                    iwhere = f"{fwhere} inhibition {inhibition['inhibitId']} prevents"
                    if item["instanceKey"] not in own:
                        problem(
                            iwhere, f"instanceKey {item['instanceKey']!r} is not bound to this function"
                        )
                    elif text := member_problem(item, refs, profiles):
                        problem(iwhere, text)

    constraints = catalogue.get("constraints", [])
    for value in repeated(c["constraintKey"] for c in constraints):
        problem("constraints", f"constraintKey {value!r} is repeated")
    for constraint in constraints:
        where = f"constraint {constraint['constraintKey']!r}"
        members = constraint["members"]
        for member in members:
            if text := member_problem(member, refs, profiles):
                problem(where, text)
        if len({m["instanceKey"] for m in members}) < 2:
            problem(where, "members name fewer than two different instanceKeys")
        if "owner" in constraint and constraint["owner"] not in members:
            problem(where, "owner is not one of its members")
    return problems


def check(root: Path) -> list[str]:
    """Problems found, one line each; an empty list means every example is valid."""
    problems: list[str] = []
    registry: referencing.Registry = referencing.Registry()
    schemas: dict[str, dict] = {}
    for name in sorted(set(SCHEMAS.values())):
        try:
            schema = load(root / METADATA / name)
            jsonschema.validators.validator_for(schema).check_schema(schema)
        except (OSError, ValueError, jsonschema.SchemaError) as error:
            problems.append(f"{name}: {error}")
            continue
        schemas[name] = schema
        # Each schema's own #/definitions references resolve against its $id.
        resource = referencing.jsonschema.DRAFT7.create_resource(schema)
        registry = registry.with_resource(schema.get("$id", name), resource)
    if problems:
        return problems

    payloads_schema = schemas[SCHEMAS[CATALOGUE]]
    profile_schema = {"$ref": f"{payloads_schema.get('$id', '')}#{PROFILE_DEFINITION}"}
    documents: dict[str, Any] = {}
    present: set[tuple[object, object]] = set()
    for path in sorted((root / EXAMPLES).glob("*.json")):
        name = path.name
        if name in UPSTREAM_TYPES:
            print(f"skipped   {name} (upstream Component Metadata type)")
            continue
        if name in SCHEMAS:
            schema = schemas[SCHEMAS[name]]
        elif name.startswith(PROFILE_PREFIX):
            schema = profile_schema
        else:
            problems.append(f"{name}: no schema in this repository describes this example")
            continue
        try:
            document = load(path)
        except ValueError as error:
            problems.append(f"{name}: {error}")
            continue
        if name.startswith(PROFILE_PREFIX) and isinstance(document, dict):
            present.add((document.get("profileId"), document.get("profileVersion")))
        validator = jsonschema.Draft7Validator(schema, registry=registry)
        errors = sorted(validator.iter_errors(document), key=lambda e: list(e.absolute_path))
        for error in errors:
            at = "/".join(str(part) for part in error.absolute_path) or "(root)"
            problems.append(f"{name}: {at}: {error.message}")
        if not errors:
            print(f"ok        {name}")
            documents[name] = document

    profiles: dict[tuple[str, int], dict] = {}
    for name, document in documents.items():
        if name.startswith(PROFILE_PREFIX):
            problems.extend(profile_problems(name, document))
            profiles[(document["profileId"], document["profileVersion"])] = document
    if CATALOGUE in documents:
        problems.extend(catalogue_problems(documents[CATALOGUE], profiles, present))
    return problems


def main(argv: list[str]) -> int:
    if len(argv) > 2:
        print(__doc__, file=sys.stderr)
        return 2
    problems = check(Path(argv[1] if len(argv) == 2 else "."))
    for problem in problems:
        print(f"INVALID   {problem}", file=sys.stderr)
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
