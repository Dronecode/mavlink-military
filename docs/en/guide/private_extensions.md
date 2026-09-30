# Private Extensions

The shared dialect reserves `53900-53999` for downstream, program-specific
messages. IDs in that block are not assigned by the shared spec and are not
interoperable unless the participating systems share the same private ICD.

[`military_extensions.xml`](https://github.com/Dronecode/mavlink-military/blob/main/military_extensions.xml)
is a template for this. It:

- includes `military.xml`, so generated bindings see the shared dialect first;
- uses unique example message and enum names to avoid colliding with the shared dialect;
- uses IDs at the low end of the private block.

To use it, copy the file into your downstream project, replace the example
names and fields with your program's private ICD, and generate that dialect as
a separate build artifact:

```sh
cp military.xml military_extensions.xml mavlink/message_definitions/v1.0/
python3 -m pymavlink.tools.mavgen \
  --lang=C --wire-protocol=2.0 \
  --output=out mavlink/message_definitions/v1.0/military_extensions.xml
```

The template is not part of the shared dialect and is not generated or
published by this repository.

::: tip
If a private message turns out to be broadly useful, propose it for the shared
dialect instead of keeping it private. See [Contributing](../contributing.md).
:::
