#!/usr/bin/env python3
"""Tests for check_example_schemas.py, on a copy of this repository's
component_metadata/ that each test breaks in one way. From the repository root:

    python3 -m unittest discover --start-directory .github/scripts/validate_dialect/tests
"""

from __future__ import annotations

import contextlib
import io
import json
import runpy
import shutil
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_example_schemas  # noqa: E402

REPOSITORY = Path(__file__).resolve().parents[4]
CATALOGUE = "payloads.example.json"
ACTUATOR = "capability-profile.example.json"
MOVE = "com.example.linear-actuator.move-to-position"


class CheckExampleSchemasTest(unittest.TestCase):
    def setUp(self) -> None:
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name)
        shutil.copytree(REPOSITORY / "component_metadata", self.root / "component_metadata")
        self.examples = self.root / "component_metadata" / "examples"

    def read(self, name: str) -> dict:
        return json.loads((self.examples / name).read_text(encoding="utf-8"))

    def write(self, name: str, document: dict) -> None:
        (self.examples / name).write_text(json.dumps(document, indent=2) + "\n", encoding="utf-8")

    def check(self) -> list[str]:
        with contextlib.redirect_stdout(io.StringIO()):
            return check_example_schemas.check(self.root)

    def assertOneProblem(self, *parts: str) -> None:
        problems = self.check()
        self.assertEqual(len(problems), 1, problems)
        for part in parts:
            self.assertIn(part, problems[0])

    def catalogue(self) -> dict:
        return self.read(CATALOGUE)

    @staticmethod
    def function(catalogue: dict, payload_id: int, function_id: int) -> dict:
        payload = next(p for p in catalogue["payloads"] if p["payloadId"] == payload_id)
        return next(f for f in payload["functions"] if f["functionId"] == function_id)

    def test_the_repository_examples_are_valid(self) -> None:
        self.assertEqual(self.check(), [])

    def test_upstream_types_are_skipped(self) -> None:
        with contextlib.redirect_stdout(io.StringIO()) as out:
            check_example_schemas.check(self.root)
        self.assertIn("skipped   events.example.json", out.getvalue())
        self.assertIn("skipped   general.example.json", out.getvalue())

    def test_a_schema_violation_fails_at_its_path(self) -> None:
        catalogue = self.catalogue()
        del catalogue["payloads"][0]["label"]
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem(CATALOGUE, "payloads/0", "'label' is a required property")

    def test_a_profile_is_validated_against_the_profile_definition(self) -> None:
        profile = self.read(ACTUATOR)
        profile["unexpected"] = True
        self.write(ACTUATOR, profile)
        self.assertOneProblem(ACTUATOR, "'unexpected' was unexpected")

    def test_an_invalid_schema_fails(self) -> None:
        path = self.root / "component_metadata" / "definition-manifest.schema.json"
        schema = json.loads(path.read_text(encoding="utf-8"))
        schema["type"] = 5
        path.write_text(json.dumps(schema), encoding="utf-8")
        self.assertOneProblem("definition-manifest.schema.json", "is not valid")

    def test_a_repeated_json_key_fails(self) -> None:
        text = (self.examples / CATALOGUE).read_text(encoding="utf-8")
        text = text.replace('"schemaVersion"', '"catalogueRevision": 1,\n  "schemaVersion"', 1)
        (self.examples / CATALOGUE).write_text(text, encoding="utf-8")
        self.assertOneProblem(CATALOGUE, "repeats the key catalogueRevision")

    def test_an_example_without_a_schema_fails(self) -> None:
        self.write("winch.example.json", {})
        self.assertOneProblem("winch.example.json", "no schema")

    def test_a_repeated_payload_id_fails(self) -> None:
        catalogue = self.catalogue()
        catalogue["payloads"][1]["payloadId"] = catalogue["payloads"][0]["payloadId"]
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem("payloadId 10 is repeated")

    def test_a_repeated_function_id_fails(self) -> None:
        catalogue = self.catalogue()
        self.function(catalogue, 10, 2)["functionId"] = 1
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem("payload 10", "functionId 1 is repeated")

    def test_a_repeated_measurement_id_fails(self) -> None:
        catalogue = self.catalogue()
        measurements = self.function(catalogue, 10, 1)["measurements"]
        measurements[1]["measurementId"] = measurements[0]["measurementId"]
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem("payload 10 function 1", "measurementId 1 is repeated")

    def test_a_repeated_instance_key_fails(self) -> None:
        catalogue = self.catalogue()
        self.function(catalogue, 13, 2)["capabilityProfiles"][0]["instanceKey"] = "dual-actuator-a"
        self.write(CATALOGUE, catalogue)
        problems = self.check()
        self.assertTrue(any("instanceKey 'dual-actuator-a' is repeated" in p for p in problems), problems)

    def test_a_repeated_constraint_key_fails(self) -> None:
        catalogue = self.catalogue()
        twin = dict(catalogue["constraints"][0], description="The same key again.")
        catalogue["constraints"].append(twin)
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem("constraintKey 'dual-actuator-exclusive-motion' is repeated")

    def test_a_profile_that_repeats_a_key_fails(self) -> None:
        profile = self.read(ACTUATOR)
        profile["properties"][1]["propertyKey"] = profile["properties"][0]["propertyKey"]
        self.write(ACTUATOR, profile)
        self.assertOneProblem(ACTUATOR, "propertyKey", "declared more than once")

    def test_a_profile_that_repeats_a_binding_id_fails(self) -> None:
        profile = self.read(ACTUATOR)
        profile["actions"][0]["bindings"][0]["bindingId"] = 1
        self.write(ACTUATOR, profile)
        self.assertOneProblem(ACTUATOR, "bindingId 1 is declared more than once")

    def test_bound_profiles_whose_ids_collide_fail(self) -> None:
        catalogue = self.catalogue()
        actuator = self.function(catalogue, 13, 1)["capabilityProfiles"][0]
        self.function(catalogue, 11, 1)["capabilityProfiles"].append(
            dict(actuator, instanceKey="parachute-actuator")
        )
        self.write(CATALOGUE, catalogue)
        problems = self.check()
        self.assertTrue(problems, "a collision should be reported")
        self.assertTrue(all("payload 11 function 1" in p for p in problems), problems)
        self.assertTrue(all("more than one bound profile" in p for p in problems), problems)

    def test_a_reference_to_a_missing_profile_fails(self) -> None:
        (self.examples / "capability-profile-survey-sensor.example.json").unlink()
        self.assertOneProblem("no profile example is com.example.survey.sensor version 1")

    def test_a_constraint_member_on_an_unbound_instance_fails(self) -> None:
        catalogue = self.catalogue()
        catalogue["constraints"][0]["members"][1]["instanceKey"] = "dual-actuator-c"
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem("instanceKey 'dual-actuator-c' has no binding")

    def test_a_constraint_member_with_an_undeclared_key_fails(self) -> None:
        catalogue = self.catalogue()
        catalogue["constraints"][0]["members"][1]["actionKey"] = "com.example.linear-actuator.spin"
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem("actionKey 'com.example.linear-actuator.spin' is not declared")

    def test_a_constraint_on_one_instance_fails(self) -> None:
        catalogue = self.catalogue()
        constraint = catalogue["constraints"][0]
        constraint["kind"] = "configuration-owner"
        constraint["members"] = [
            {"instanceKey": "dual-actuator-a", "propertyKey": "com.example.linear-actuator.position"},
            {"instanceKey": "dual-actuator-a", "propertyKey": "com.example.linear-actuator.hold-force"},
        ]
        constraint["owner"] = constraint["members"][0]
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem("fewer than two different instanceKeys")

    def test_an_owner_that_is_not_a_member_fails(self) -> None:
        catalogue = self.catalogue()
        constraint = catalogue["constraints"][0]
        constraint["kind"] = "configuration-owner"
        constraint["owner"] = {"instanceKey": "dual-actuator-a", "actionKey": MOVE.replace("move", "park")}
        self.write(CATALOGUE, catalogue)
        problems = self.check()
        self.assertTrue(any("owner is not one of its members" in p for p in problems), problems)

    def test_an_inhibition_naming_another_functions_instance_fails(self) -> None:
        catalogue = self.catalogue()
        prevents = self.function(catalogue, 11, 1)["inhibitions"][0]["prevents"]
        prevents.append({"instanceKey": "dual-actuator-a", "actionKey": MOVE})
        self.write(CATALOGUE, catalogue)
        self.assertOneProblem("inhibition 9 prevents", "not bound to this function")

    def drive_fault(self, action_key: str) -> None:
        """Give the first actuator an inhibition that prevents one of its actions."""
        catalogue = self.catalogue()
        self.function(catalogue, 13, 1)["inhibitions"] = [
            {
                "inhibitId": 1,
                "label": "Drive fault",
                "description": "The shared drive reports a fault.",
                "prevents": [{"instanceKey": "dual-actuator-a", "actionKey": action_key}],
            }
        ]
        self.write(CATALOGUE, catalogue)

    def test_an_inhibition_naming_a_declared_action_passes(self) -> None:
        self.drive_fault(MOVE)
        self.assertEqual(self.check(), [])

    def test_an_inhibition_naming_an_undeclared_key_fails(self) -> None:
        self.drive_fault("com.example.linear-actuator.spin")
        self.assertOneProblem("inhibition 1 prevents", "is not declared")

    def test_main_exit_codes(self) -> None:
        root = str(self.root)
        with contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(check_example_schemas.main(["check", root]), 0)
            self.write("winch.example.json", {})
            with contextlib.redirect_stderr(io.StringIO()) as err:
                self.assertEqual(check_example_schemas.main(["check", root]), 1)
        self.assertIn("INVALID", err.getvalue())
        with contextlib.redirect_stderr(io.StringIO()) as err:
            self.assertEqual(check_example_schemas.main(["check", root, "extra"]), 2)
        self.assertIn("Usage:", err.getvalue())

    def test_runs_as_a_script_from_the_repository_root(self) -> None:
        script = Path(check_example_schemas.__file__)
        with (
            mock.patch.object(sys, "argv", [str(script), str(self.root)]),
            contextlib.redirect_stdout(io.StringIO()) as out,
            self.assertRaises(SystemExit) as exit_,
        ):
            runpy.run_path(str(script), run_name="__main__")
        self.assertEqual(exit_.exception.code, 0)
        self.assertIn("ok        payloads.example.json", out.getvalue())


if __name__ == "__main__":
    unittest.main()
