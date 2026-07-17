# MAVLink Military Messages

`military.xml` is the shared MAVLink-M dialect. Extension boundaries have been
folded into the base message definitions, so fields that belong to a shared
message live directly in that message.

`military_extensions.xml` is a downstream/private extension example only. It
shows implementors how to include the shared dialect and define local messages in
the reserved `53900-53999` block without making those messages part of the
shared generated dialect.
