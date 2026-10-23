#!/usr/bin/env python3
"""Check the repository's CI files against its supply-chain policy.

Usage: check_ci_policy.py [<root>]
  root  the repository checkout, the current directory by default

Reads the workflows (.github/workflows/*.yml and *.yaml), the composite
actions (.github/actions/*/action.yml and action.yaml), the shell scripts
under .github/scripts and the requirement files in .github/requirements/
(*.txt), and reports:

Errors, which fail the check:
  - a pip install that is not hash-locked: it needs --require-hashes,
    --only-binary :all:, --no-deps and one or more -r <file> naming an
    existing file in .github/requirements/, and names no package itself
  - a requirement line other than an exact == pin followed by one or more
    --hash=sha256:<digest>
  - npm install, update, rebuild, exec or npx, or npm ci (in any of its
    spellings) without --ignore-scripts
  - a pull_request trigger with a paths, paths-ignore, branches or
    branches-ignore filter: a check that does not run on every pull request
    cannot be a required check; settings taken from a YAML alias or merge
    key count as a filter, since this check does not resolve them
Warnings:
  - a runs-on label other than ubuntu-24.04
  - a python-version that is not an exact X.Y.Z version

The YAML is read line by line, which the repository's block-style files
allow, so no YAML library is needed. Messages name the file and line.
The check runs from the tree it reads, a pull request's own included, so
it keeps these rules from slipping by mistake; a change to the check
itself, or a command written in a form it does not read, rests on review.
Exit status: 0 without errors, 1 with errors, 2 on a usage error.
"""

from __future__ import annotations

import os
import re
import shlex
import sys
from pathlib import Path
from typing import NamedTuple

RUNNER = "ubuntu-24.04"
REQUIREMENTS = Path(".github/requirements")
PIP = re.compile(r"\bpip(?:3(?:\.\d+)?)?\s+install\b")
NPM = re.compile(r"\bnpm\s+(?P<command>[a-z-]+)")
NPX = re.compile(r"\bnpx\s")
# npm commands that resolve versions or run package code, by every alias npm
# accepts, and the spellings of npm ci (cit also runs the test script).
NPM_INSTALL = {"install", "i", "add", "in", "ins", "inst", "insta", "instal", "isnt", "isntall"}
NPM_INSTALL |= {"install-test", "it", "update", "up", "upgrade", "udpate", "rebuild", "rb"}
NPM_INSTALL |= {"exec", "x"}
NPM_CI = {"ci", "clean-install", "ic", "install-clean", "isntall-clean", "install-ci-test", "cit"}
# pip options a locked install may carry besides the required ones.
PIP_QUIET = {"-q", "--quiet", "-qq", "--disable-pip-version-check", "--no-cache-dir", "--no-input"}
REQUIREMENT_FILE = re.compile(r"(?:^|/)\.github/requirements/(?P<name>[^/]+\.txt)$")
PIN = re.compile(
    r"^[A-Za-z0-9][A-Za-z0-9._-]*(?:\[[A-Za-z0-9,._-]+\])?==[A-Za-z0-9][A-Za-z0-9.+!_-]*"
    r"(?:\s*;[^\\]+?)?(?:\s+--hash=sha256:[0-9a-f]{64})+$"
)
ON = re.compile(r"""^["']?on["']?:\s*(?P<value>.*)$""")
KEY = re.compile(r"^(?P<indent>\s*)(?P<key>[A-Za-z_-]+|<<):\s*(?P<value>.*)$")
PR_KEY = re.compile(r"\bpull_request(?:_target)?\b")
PR_FILTER = re.compile(r"\b(?:paths|paths-ignore|branches|branches-ignore)\b")
PR_FILTERS = {"paths", "paths-ignore", "branches", "branches-ignore"}
EXACT_VERSION = re.compile(r"^\d+\.\d+\.\d+$")
# A comment, as pip's requirement parser finds one.
COMMENT = re.compile(r"(^|\s+)#.*$")
STEP_NAME = re.compile(r"^\s*(?:-\s+)?name:")


class Finding(NamedTuple):
    level: str
    path: str
    line: int
    message: str


def escape(value: str, prop: bool = False) -> str:
    """Escape a value for a GitHub Actions workflow command."""
    value = value.replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")
    if prop:
        value = value.replace(":", "%3A").replace(",", "%2C")
    return value


def report(finding: Finding) -> None:
    if os.environ.get("GITHUB_ACTIONS") == "true":
        props = f"file={escape(finding.path, True)},line={finding.line},title=CI policy"
        print(f"::{finding.level} {props}::{escape(finding.message)}")
    else:
        print(f"{finding.level}: {finding.path}:{finding.line}: {finding.message}", file=sys.stderr)


def strip_comment(value: str) -> str:
    """Drop a YAML comment and surrounding quotes from a one-line value."""
    value = re.sub(r"\s+#.*$", "", value).strip()
    return value.strip("\"'")


def indent_of(line: str) -> int:
    return len(line) - len(line.lstrip(" "))


def logical_lines(text: str) -> list[tuple[int, str]]:
    """Join the lines that end in a backslash, as pip and the shell do: a
    line with a comment never continues, and it ends the line it follows.
    Returns (first line number, text) pairs."""
    joined: list[tuple[int, str]] = []
    first, parts = 0, []
    for number, line in enumerate(text.split("\n"), 1):
        if not parts:
            first = number
        if line.endswith("\\") and not COMMENT.search(line):
            parts.append(line[:-1])
            continue
        joined.append((first, " ".join([*parts, line])))
        parts = []
    if parts:
        joined.append((first, " ".join(parts)))
    return joined


def check_pip(path: str, number: int, command: str, root: Path) -> list[Finding]:
    """Check one pip install command line (from 'pip install' on)."""
    try:
        words = shlex.split(command, comments=True)
    except ValueError:
        return [Finding("error", path, number, "cannot read this pip install command")]
    words = words[words.index("install") + 1 :]
    flags: set[str] = set()
    files: list[str] = []
    problems: list[str] = []
    i = 0
    while i < len(words):
        word = words[i]
        name, equals, value = word.partition("=")
        if name in ("-r", "--requirement") or (word.startswith("-r") and len(word) > 2):
            if name in ("-r", "--requirement") and not equals:
                i += 1
                value = words[i] if i < len(words) else ""
            elif not equals:
                value = word[2:]
            files.append(value)
        elif name == "--only-binary":
            if not equals:
                i += 1
                value = words[i] if i < len(words) else ""
            flags.add(f"--only-binary {value}")
        elif word in ("--require-hashes", "--no-deps"):
            flags.add(word)
        elif word in PIP_QUIET:
            pass
        elif word.startswith("-"):
            problems.append(f"uses {word}, which a locked install does not need")
        else:
            problems.append(f"names the package {word} instead of a lock file")
        i += 1
    for required in ("--require-hashes", "--only-binary :all:", "--no-deps"):
        if required not in flags:
            problems.append(f"lacks {required}")
    if not files:
        problems.append("reads no -r file from .github/requirements/")
    for name in files:
        match = REQUIREMENT_FILE.search(name)
        if not match:
            problems.append(f"reads {name}, which is not in .github/requirements/")
        elif not (root / REQUIREMENTS / match.group("name")).is_file():
            problems.append(f"reads {name}, which does not exist")
    if not problems:
        return []
    return [Finding("error", path, number, "not a hash-locked install: " + "; ".join(problems))]


def check_commands(path: str, text: str, root: Path) -> list[Finding]:
    """Check every pip and npm command in a workflow, action or script."""
    findings: list[Finding] = []
    for number, line in logical_lines(text):
        if line.lstrip().startswith("#") or STEP_NAME.match(line):
            continue
        pip = PIP.search(line)
        if pip:
            findings += check_pip(path, number, line[pip.start() :], root)
        for npm in NPM.finditer(line):
            command = npm.group("command")
            rest = line[npm.end() :].split()
            if command in NPM_INSTALL:
                findings.append(
                    Finding(
                        "error",
                        path,
                        number,
                        f"npm {command} resolves versions or runs package code; "
                        "use npm ci --ignore-scripts",
                    )
                )
            elif command in NPM_CI and "--ignore-scripts" not in rest:
                findings.append(
                    Finding(
                        "error",
                        path,
                        number,
                        f"npm {command} runs install scripts; add --ignore-scripts",
                    )
                )
        if NPX.search(line):
            findings.append(
                Finding(
                    "error",
                    path,
                    number,
                    "npx can fetch and run a package the lockfile does not pin; use npm run",
                )
            )
    return findings


def check_triggers(path: str, lines: list[str]) -> list[Finding]:
    """Report path and branch filters on a workflow's pull_request trigger."""
    findings: list[Finding] = []
    in_on = False
    pr_indent: int | None = None
    for number, line in enumerate(lines, 1):
        stripped = line.strip()
        if not stripped or stripped.startswith("#"):
            continue
        if indent_of(line) == 0:
            on = ON.match(line)
            value = strip_comment(on.group("value")) if on else None
            in_on = value == ""
            if value and value.startswith("{") and PR_KEY.search(value) and PR_FILTER.search(value):
                findings.append(filter_finding(path, number))
            pr_indent = None
            continue
        if not in_on:
            continue
        key = KEY.match(line)
        if pr_indent is not None and indent_of(line) <= pr_indent:
            pr_indent = None
        if key is None:
            continue
        value = strip_comment(key.group("value"))
        if key.group("key") in ("pull_request", "pull_request_target"):
            pr_indent = indent_of(line)
            if PR_FILTER.search(value) or value.startswith("*"):
                findings.append(filter_finding(path, number))
        elif pr_indent is not None and key.group("key") in (*PR_FILTERS, "<<"):
            findings.append(filter_finding(path, number))
    return findings


def filter_finding(path: str, number: int) -> Finding:
    return Finding(
        "error",
        path,
        number,
        "the pull_request trigger is filtered, so its checks do not report on every pull "
        "request and cannot be required; let it run on every pull request",
    )


def check_runners(path: str, lines: list[str]) -> list[Finding]:
    """Warn about runner labels and Python versions that can move."""
    findings: list[Finding] = []
    for number, line in enumerate(lines, 1):
        key = KEY.match(line)
        if key is None:
            continue
        value = strip_comment(key.group("value"))
        if key.group("key") == "runs-on" and value != RUNNER:
            findings.append(
                Finding("warning", path, number, f"runs-on {value or '(a list)'}, not {RUNNER}")
            )
        elif key.group("key") == "python-version":
            if value == "":
                value = input_default(lines, number)
            if value.startswith("${{") and "inputs.python-version" in value:
                continue
            if not EXACT_VERSION.match(value):
                findings.append(
                    Finding(
                        "warning", path, number, f"python-version {value!r} is not an exact X.Y.Z"
                    )
                )
    return findings


def input_default(lines: list[str], number: int) -> str:
    """The default: of the input declared at line number, or ''."""
    indent = indent_of(lines[number - 1])
    for line in lines[number:]:
        if line.strip() and indent_of(line) <= indent:
            break
        key = KEY.match(line)
        if key and key.group("key") == "default":
            return strip_comment(key.group("value"))
    return ""


def check_requirements(path: str, text: str) -> list[Finding]:
    """Every requirement is an exact pin with one or more hashes."""
    findings: list[Finding] = []
    pins = 0
    for number, line in logical_lines(text):
        content = COMMENT.sub("", line).strip()
        if not content:
            continue
        if PIN.match(content):
            pins += 1
        else:
            findings.append(
                Finding(
                    "error",
                    path,
                    number,
                    "not an exact == pin with --hash=sha256: digests (no other options)",
                )
            )
    if pins == 0 and not findings:
        findings.append(Finding("error", path, 1, "the file pins no package"))
    return findings


def files(root: Path, pattern: str) -> list[Path]:
    return sorted(p for p in root.glob(pattern) if p.is_file())


def check(root: Path) -> list[Finding]:
    findings: list[Finding] = []
    ci = [
        *files(root, ".github/workflows/*.yml"),
        *files(root, ".github/workflows/*.yaml"),
        *files(root, ".github/actions/*/action.yml"),
        *files(root, ".github/actions/*/action.yaml"),
    ]
    for file in ci:
        path = file.relative_to(root).as_posix()
        text = file.read_text(encoding="utf-8")
        lines = text.split("\n")
        findings += check_commands(path, text, root)
        if path.startswith(".github/workflows/"):
            findings += check_triggers(path, lines)
        findings += check_runners(path, lines)
    for file in files(root, ".github/scripts/**/*.sh"):
        findings += check_commands(
            file.relative_to(root).as_posix(), file.read_text(encoding="utf-8"), root
        )
    for file in files(root, ".github/requirements/*.txt"):
        findings += check_requirements(
            file.relative_to(root).as_posix(), file.read_text(encoding="utf-8")
        )
    return findings


def main(argv: list[str]) -> int:
    if len(argv) > 1:
        print("usage: check_ci_policy.py [<root>]", file=sys.stderr)
        return 2
    root = Path(argv[0] if argv else ".")
    if not (root / ".github").is_dir():
        print(f"error: {root} has no .github directory", file=sys.stderr)
        return 2
    findings = check(root)
    for finding in findings:
        report(finding)
    errors = sum(1 for f in findings if f.level == "error")
    warnings = len(findings) - errors
    print(f"CI policy: {errors} error(s), {warnings} warning(s)")
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
