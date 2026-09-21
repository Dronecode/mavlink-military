# Guide

- [Message ID Allocation](id_allocation.md): the `53000-53999` range, reserved blocks, and the mapping from earlier development IDs.
- [Private Extensions](private_extensions.md): defining program-specific messages in the private block without changing the shared dialect.
- [Safety-Critical Enum Encoding](status_field_encoding.md): the enums that use Hamming codewords, the codeword table, and how receivers, senders, bridges and gateways handle an invalid value.
- [Refusals and Resends](refusals_and_resends.md): what a receiver records when it refuses a message, what the sender sends again, and how consent and clearance are shown after a refusal or a restart.

For the underlying protocol (framing, serialization, signing, routing, and
microservices) see the [MAVLink Developer Guide](https://mavlink.io/en/guide/).
