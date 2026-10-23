# Releases and Versions

A release is a fixed version of the dialect to depend on: the definitions, the C headers and the Python module generated from them, that version's documentation, and machine-readable records of every check the release passed, all signed with SLSA provenance. Releases are published from version tags on `main`, after a maintainer approves them. The `main` branch, and the [C library](https://github.com/Dronecode/mavlink-military-c_library_v2) generated from it, are the development channel.

The [releases page](https://github.com/Dronecode/mavlink-military/releases) lists every published version. [Verifying a Release](verify.md) shows how to check a file you downloaded; [Making a Release](maintainers.md) is the maintainers' procedure.

## What a release holds

| File | What it is |
| --- | --- |
| `mavlink-m-X.Y.Z-definitions.tar.gz` | `message_definitions/v1.0/` with `military.xml` and the MAVLink files it includes, at the commit the release pins. Run mavgen on `military.xml` there to generate any language; with the same generator commit, C and Python come out as in the release. |
| `mavlink-m-X.Y.Z-c.tar.gz` | MAVLink 2 C headers. Include `military/mavlink.h`. |
| `mavlink-m-X.Y.Z-python.tar.gz` | `military.py`, a MAVLink 2 Python module that needs no other package. |
| `mavlink-m-X.Y.Z-military.xml` | The dialect file alone. |
| `mavlink-m-X.Y.Z-wire.json` | Every message's ID, CRC_EXTRA, lengths, flags and target offsets, those of the included MAVLink files marked upstream; the dialect's enums and command numbers; and the C facts the build measured, such as `MAVLINK_VERSION` and the largest frame. |
| `mavlink-m-X.Y.Z-manifest.json` | Every file in the archives, with its SHA-256, license and copyright. |
| `mavlink-m-X.Y.Z-docs.tar.gz` | This version's documentation site, as the site serves it at `/vX.Y.Z/`. |
| `mavlink-m-X.Y.Z.spdx.json` | The SBOM, an SPDX 2.3 document: every file, the MAVLink definitions it includes, the generator and the other build tools, with versions, identifiers, licenses and relationships. |
| `mavlink-m-X.Y.Z-evidence.tar.gz` | The release's check records: its plan, both package builds' checks and tool versions, the tests' coverage, the workflow scan, the commit checks and the vulnerability record. |
| `mavlink-m-X.Y.Z-notes.md` | The release notes, which are also the release's description. |
| `SHA256SUMS` | The SHA-256 of every file above. |
| `mavlink-m-X.Y.Z.intoto.jsonl` | The SLSA provenance, which signs every file `SHA256SUMS` lists and `SHA256SUMS` itself. |
| `mavlink-m-X.Y.Z-publish.json` | The publication record: the approval, the identity of the provenance signer and every asset's server-side digest. |

Each archive carries `LICENSE`, `LICENSES/`, `REUSE.toml` and `NOTICE`. The dialect and this repository's files are under the MIT license. The generated C and Python code is under the generator's grant, `LicenseRef-MAVLink-generated-code`, whose notice must be kept in all copies or substantial portions. The MAVLink definitions that `military.xml` includes are under the MIT license, as the MAVLink project states. The generator itself is not included.

The package files are reproducible: the release builds them twice, on separate runners with different time zones, locales and umasks, and publishes only if both builds give the same bytes. [Verifying a Release](verify.md#rebuild-it) shows how to rebuild them yourself.

## Version numbers

Versions follow [Semantic Versioning](https://semver.org/) as `vX.Y.Z`. Every release is a final release; there are no pre-release tags.

| Change since the previous release | Before 1.0.0 | From 1.0.0 |
| --- | --- | --- |
| Breaking | minor version | major version |
| Addition | patch version | minor version |
| Anything else | patch version | patch version |

A change is breaking when any of these holds:

- a commit is marked with `!` in its subject;
- a message is removed or renamed, or its CRC_EXTRA changes: a field before `<extensions/>` added, removed, renamed, retyped or moved;
- mavlink's API-break checker reports a removed or changed name, such as an enum entry;
- the included MAVLink definitions move to another commit and change in a breaking way;
- the generator moves to another commit and changes the C library's fixed headers;
- a message ID or command number gets another name than an earlier release gave it.

An addition is a `feat` commit; a message or an extension field added, which the wire report lists for information; an addition to the included MAVLink definitions when they move to another commit; or a change of `military.xml`'s `<version>`, which sets the C `MAVLINK_VERSION` constant. A release whose number is below what its changes call for does not build. The first release may take any number.

Whether to release a version is the working group's decision. A `Decision:` line in the release tag's message, or in the approval's comment, can link the public record of that decision; the notes show the tag's link and the publication record shows the approval's. Link only a record that anyone can read.

## Documentation versions

The site serves each release's documentation at `/vX.Y.Z/`, exactly as that release built it, and the development version at `/main/`. The site's root, and the page addresses it had before it had versions, lead to the latest release, or to `/main/` while there is none. A banner marks `main` as the development version, an older release as outdated and a withdrawn one as withdrawn, and the version menu lists every version.

## Withdrawn releases

A published release is never changed. If one must not be used, a reviewed pull request lists it in `.github/release-status.json` with its reason and the decision that withdrew it. Its files and pages stay, its pages show a withdrawn banner, and the site's root moves to the latest release that is not withdrawn; the maintainers also move the release's latest marker to that release. A fix comes as a new release.
