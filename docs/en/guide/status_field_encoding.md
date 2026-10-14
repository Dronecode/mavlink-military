# Safety-Critical Enum Encoding

## Introduction

MAVLink-M numbers most enums sequentially, so two valid values can differ in a single bit, as `MAVLINK_M_ESAD_ARMING_DISARMED` (0) and `MAVLINK_M_ESAD_ARMING_ARMED` (1) did.
The packet [checksum](https://mavlink.io/en/guide/serialization.html#checksum) already detects any such change in transit, and this encoding neither replaces nor supplements it.

The encoding targets faults the checksum can't see: on the sender before the checksum is computed, such as a bit flip in stored state or while the value is copied into the payload, and on the receiver after the checksum is validated, such as corruption in a buffer, queue or shared-memory copy.
Twenty-two safety-critical enums use values at least four bits apart, so those faults are more likely to produce a detectably invalid value.

The protection starts wherever the value is held as a codeword.
A sender should hold the state as the codeword, since a sender that keeps sequential values and converts them when it builds the message turns a corrupted stored value into a valid codeword.
[Bridges and Gateways](#bridges-and-gateways) covers a bridge to a component bus and a gateway to another network or protocol.

The FIELD CONVENTIONS in the [military.xml](https://github.com/Dronecode/mavlink-military/blob/main/military.xml) header summarise the encoding and refer to this page for the affected fields, the codeword table and the receiver and sender requirements, and to [Refusals and Resends](refusals_and_resends.md) for what follows a refused message.

## Concepts

### Scope

An enum is in scope if a corrupted value could change whether a device is treated as safe, armed, consented-to-strike, released or terminated, whether fires start, hold or stop, whether a fire mission or attack is handled as danger close, how many attacks a clearance covers, or whether a designator lases.
That includes:

- a value a receiver folds into such a state, as store sensor health is folded into release readiness
- a precondition a receiver checks before it acts on a clearance, as `TERMINAL_CONTROL.abort_authority_present` is for `MAVLINK_M_CAS_CLEARED_HOT`
- a declaration whose unset or zeroed value would otherwise assert the less cautious reading, as `danger_close` does in `CALL_FOR_FIRE` and `CAS_9LINE`, which is why those two-state fields are enums
- the result of an acknowledgment, which for several commanded messages is the sender's only confirmation that a stop took effect

Assessments of a target that people weigh before they decide, such as [MAVLINK_M_PID_STATUS](../messages/military.md#MAVLINK_M_PID_STATUS), [MAVLINK_M_CDE_LEVEL](../messages/military.md#MAVLINK_M_CDE_LEVEL), [MAVLINK_M_ROE_STATE](../messages/military.md#MAVLINK_M_ROE_STATE) and [MAVLINK_M_NOSTRIKE_STATUS](../messages/military.md#MAVLINK_M_NOSTRIKE_STATUS), are out of scope: no receiver acts on them by itself, and a decision taken on them travels in an in-scope field, such as a withdrawal of consent or a terminate.
In [LOITER_MUNITION_CONTROL](../messages/military.md#LOITER_MUNITION_CONTROL), `pid_status` and `cde_level` record what the consent rests on, and the munition acts only on `consent_state` and `terminate`.

Any other enum keeps sequential numbering unless its own description gives a minimum pairwise Hamming distance between its values.

Each in-scope field is either reported, carrying the sender's current state, or commanded, asking the receiver to act:

| Enum                                                                                                 | Reported in                                                                              | Commanded in                                                                                                               |
| ---------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- |
| [MAVLINK_M_ESAD_ARMING_STATUS](../messages/military.md#MAVLINK_M_ESAD_ARMING_STATUS)                 | `ESAD_STATE.arming_status`, `STORE_STATUS.arming_status`, `STORE_MUNITION.arming_status` |                                                                                                                            |
| [MAVLINK_M_ESAD_ARMING_REQUEST](../messages/military.md#MAVLINK_M_ESAD_ARMING_REQUEST)               |                                                                                          | `ESAD_ARMING.arming_request`, [MAV_CMD_MAVLINK_M_STORE_SAFE](../messages/military.md#MAV_CMD_MAVLINK_M_STORE_SAFE) param 2 |
| [MAVLINK_M_ESAD_MUNITION_STATUS](../messages/military.md#MAVLINK_M_ESAD_MUNITION_STATUS)             | `ESAD_STATE.munition_status`                                                             |                                                                                                                            |
| [MAVLINK_M_ESAD_IGNITION_STATUS](../messages/military.md#MAVLINK_M_ESAD_IGNITION_STATUS)             | `ESAD_STATE.ignition_status`                                                             |                                                                                                                            |
| [MAVLINK_M_ESAD_PIN_STATE](../messages/military.md#MAVLINK_M_ESAD_PIN_STATE)                         | `ESAD_STATE.pin_state`                                                                   |                                                                                                                            |
| [MAVLINK_M_ESAD_ARM_DELAY_SETTING](../messages/military.md#MAVLINK_M_ESAD_ARM_DELAY_SETTING)         | `ESAD_STATE.arm_delay_setting`                                                           |                                                                                                                            |
| [MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE](../messages/military.md#MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE) | `ESAD_STATE.trigger_distance_mode`                                                       | `ESAD_CONFIG.trigger_distance_mode`                                                                                        |
| [MAVLINK_M_RWS_ARMING_STATE](../messages/military.md#MAVLINK_M_RWS_ARMING_STATE)                     | `RWS_STATE.arming_state`                                                                 |                                                                                                                            |
| [MAVLINK_M_LM_CONSENT_STATE](../messages/military.md#MAVLINK_M_LM_CONSENT_STATE)                     |                                                                                          | `LOITER_MUNITION_CONTROL.consent_state`                                                                                    |
| [MAVLINK_M_LM_TERMINATE](../messages/military.md#MAVLINK_M_LM_TERMINATE)                             |                                                                                          | `LOITER_MUNITION_CONTROL.terminate`                                                                                        |
| [MAVLINK_M_STORE_READINESS](../messages/military.md#MAVLINK_M_STORE_READINESS)                       | `STORE_STATUS.readiness`                                                                 |                                                                                                                            |
| [MAVLINK_M_SENSOR_HEALTH](../messages/military.md#MAVLINK_M_SENSOR_HEALTH)                           | `STORE_SENSOR_STATUS.health`                                                             |                                                                                                                            |
| [MAVLINK_M_ENGAGEMENT_DIRECTIVE](../messages/military.md#MAVLINK_M_ENGAGEMENT_DIRECTIVE)             |                                                                                          | `ENGAGEMENT_DIRECTIVE.directive`                                                                                           |
| [MAVLINK_M_CAS_CLEARANCE](../messages/military.md#MAVLINK_M_CAS_CLEARANCE)                           |                                                                                          | `TERMINAL_CONTROL.clearance`                                                                                               |
| [MAVLINK_M_TAC_TYPE](../messages/military.md#MAVLINK_M_TAC_TYPE)                                     |                                                                                          | `TERMINAL_CONTROL.tac_type`                                                                                                |
| [ABORT_AUTHORITY](../messages/military.md#ABORT_AUTHORITY)                                           |                                                                                          | `TERMINAL_CONTROL.abort_authority_present`                                                                                 |
| [MAVLINK_M_FIRE_MISSION_COMMAND](../messages/military.md#MAVLINK_M_FIRE_MISSION_COMMAND)             |                                                                                          | `SPLASH_CORRECTION.command`                                                                                                |
| [MAVLINK_M_FIRE_CONTROL_METHOD](../messages/military.md#MAVLINK_M_FIRE_CONTROL_METHOD)               |                                                                                          | `CALL_FOR_FIRE.control_method`                                                                                             |
| [DANGER_CLOSE](../messages/military.md#DANGER_CLOSE)                                                 |                                                                                          | `CALL_FOR_FIRE.danger_close`, `CAS_9LINE.danger_close`                                                                     |
| [MAVLINK_M_SENSOR_MODE](../messages/military.md#MAVLINK_M_SENSOR_MODE)                               | `SENSOR_TASKING.sensor_mode` in a status response                                        | `SENSOR_TASKING.sensor_mode` in a request                                                                                  |
| [MAVLINK_M_TASKING_STATUS](../messages/military.md#MAVLINK_M_TASKING_STATUS)                         | `SENSOR_TASKING.status`                                                                  |                                                                                                                            |
| [MAVLINK_M_ACK_RESULT](../messages/military.md#MAVLINK_M_ACK_RESULT)                                 | `MAVLINK_M_ACK.result`                                                                   |                                                                                                                            |

Producers and consumers of these fields inherit the new values.

[TERMINAL_CONTROL](../messages/military.md#TERMINAL_CONTROL) and [LOITER_MUNITION_CONTROL](../messages/military.md#LOITER_MUNITION_CONTROL) travel both ways: an aircraft's call carries `clearance`, `tac_type` and `abort_authority_present` (`ABORT_AUTHORITY_UNKNOWN`, since the controller establishes the abort authority), and a munition's consent request carries `consent_state` and `terminate`, so the controller or human authority that receives them checks those fields the same way.

Values are defined per enum: a value taken from another enum, such as a generic payload operation or health state, is mapped by entry name, never copied by number.

### Codewords

Each in-scope enum is one `uint8_t` with at most 16 entries, except that param 2 of [MAV_CMD_MAVLINK_M_STORE_SAFE](../messages/military.md#MAV_CMD_MAVLINK_M_STORE_SAFE) carries a `MAVLINK_M_ESAD_ARMING_REQUEST` value as a float, compared exactly as that parameter's description says.
Its entries use the 16 codewords of the extended Hamming[8,4,4] code (4 data bits, 3 Hamming parity bits and 1 overall parity bit), in ascending order.
A new entry takes the next codeword its enum has not assigned and is listed after the existing entries, so no existing value changes.
The twenty-two enums in scope use this table:

| Order index | Wire value | Binary     |
| ----------- | ---------- | ---------- |
| 0           | 0          | `00000000` |
| 1           | 15         | `00001111` |
| 2           | 51         | `00110011` |
| 3           | 60         | `00111100` |
| 4           | 85         | `01010101` |
| 5           | 90         | `01011010` |
| 6           | 102        | `01100110` |
| 7           | 105        | `01101001` |
| 8           | 150        | `10010110` |
| 9           | 153        | `10011001` |
| 10          | 165        | `10100101` |
| 11          | 170        | `10101010` |
| 12          | 195        | `11000011` |
| 13          | 204        | `11001100` |
| 14          | 240        | `11110000` |
| 15          | 255        | `11111111` |

Order index 0 is wire value 0, and every in-scope enum reserves it for an `UNKNOWN`, `UNSPECIFIED` or `NONE` entry, as the FIELD CONVENTIONS require.
A zero-filled reported field therefore decodes as unknown, never as a real state such as disarmed or safe, and a zero-filled commanded field decodes as a request for nothing, which [Commanded Values](#commanded-values) covers.

Any change of one to three bits to a codeword gives a byte that is not a codeword.
A change of four or more bits can give another valid value, and every pair of values these enums use is four bits apart, such as 15 (`MAVLINK_M_ESAD_ARMING_DISARMED`) and 51 (`MAVLINK_M_ESAD_ARMING_ARMED`), except complementary codewords such as 60 and 195, which are eight bits apart.

A byte overwritten with an arbitrary value lands on another valid value with probability (n − 1)/255 for an enum with n entries, at most 12/255 (about 4.7%) for the 13-entry [MAVLINK_M_FIRE_MISSION_COMMAND](../messages/military.md#MAVLINK_M_FIRE_MISSION_COMMAND).
The encoding shows only whether a byte is a defined value, not whether it is current or correct: a stale value, or a wrong value the sender chose or stored, is still a codeword.

The encoding covers only the in-scope enum fields.
The other fields of the same messages have no protection beyond the packet checksum, so a fault outside the checksum's window can change them to another valid value:

- the identifiers that select which store, ESAD, effector or mission a command applies to, some of which select all of them at 0, which only a stop, a status request or a built-in test may use (FIELD CONVENTIONS in the `military.xml` header)
- coordinates and times
- the mission type, munition, fuze and effect selections and spotting values of a fire mission
- boolean fields such as `CALL_FOR_FIRE.mensurated`
- bitmask fields such as `ESAD_STATE.fault_flags`, which can't use codewords at all

A `NONE` that a fault puts in `LOITER_MUNITION_CONTROL`, `TERMINAL_CONTROL` or `SPLASH_CORRECTION`, where `NONE` is a valid request for no change, is not detected either.

The encoding also gives no protection against a message that is deliberately changed, injected or replayed, which carries defined values and a valid checksum: [MAVLink 2 message signing](https://mavlink.io/en/guide/message_signing.html), which the dialect requires (SAFETY BOUNDARIES in the `military.xml` header), authenticates each packet and rejects a replayed one, and this encoding is a check on top of it.

## Receiving an Encoded Field

This dialect adopts detection only.
Each in-scope enum's description requires a receiver to treat an unrecognised reported value as unknown, to reject an unrecognised commanded value, and never to correct either into a defined value.
A value is unrecognised when it is not one of the enum's listed values, even if it is a codeword: a change of four bits can turn a listed value into a codeword that the enum does not use.
In addition, a receiver of an in-scope field:

- must match the received byte exactly against the enum's listed values before acting on it
- can use a value that matches one of the enum's listed values once it also passes the receiver's own freshness and consistency checks. Those checks never hold back a stop: the receiver applies a stop on receipt, never rejects one for its time, and never declines one because one of its selectors does not match
- must not act on a value that matches none of the enum's listed values, and must apply to it the fault or stale-data handling it already uses for an out-of-range enum value. Such a value is either a byte that is not one of the 16 codewords in [Codewords](#codewords), which only a fault produces, or a codeword the enum does not list, which a fault or a sender built from a later revision that added an entry can produce

A range check against the generated `_ENUM_END` constant does not work: _mavgen_ sets it to one more than the largest listed value (_pymavlink_ `generator/mavparse.py`), so a `value < _ENUM_END` check accepts every invalid byte below it, including most single-bit changes of the listed values.
The generated enum tables also hold the `_ENUM_END` entry itself, often one bit from the largest listed value (61 next to 60, as for `MAVLINK_M_LM_TERMINATE_SELF_DESTRUCT`), so a membership test against a generated table must leave that entry out.

The code could correct single-bit errors by nearest-codeword decoding, but correction is excluded on purpose.
On these fields it means acting on a guess about what the sender meant, where a wrong guess has physical consequences: arming a live munition, waiving a consent gate, or skipping a self-destruct.

The receiver's other checks remain responsible for the values the encoding cannot detect (see [Codewords](#codewords)).

`military.xml` and the bindings generated from it define the codeword values only, not the validation, fault handling and resend rules described here and in [Refusals and Resends](refusals_and_resends.md).
Each implementation has to implement these requirements itself, and needs its own evidence, such as code review and tests that feed it values that are not listed, before it can rely on this encoding.
These requirements apply only to the twenty-two enums in scope.

### Reported Values

A reported value that is not one of the enum's listed values is treated as unknown, as each enum's description requires.
A byte that is not one of the 16 codewords comes from a fault, or from a peer on an older revision (see [Migrating From Sequential Values](#migrating-from-sequential-values)), and the same fault may have turned the message's other in-scope fields into other listed values, so a receiver:

- shows the message's in-scope fields as a detected invalid value, not as the enum's `UNKNOWN` entry or a `FAULT` the device reported, and acts on none of them
- keeps the last listed value it accepted for each of those fields in view, marked as not current, until a report whose in-scope fields are all listed values arrives

A codeword the enum does not list can also come from a peer built from a later revision that added an entry, so it is shown as `UNKNOWN`.
A reported `UNKNOWN`, a `FAULT` or a value that is not listed never removes from view the last other listed value reported for that field, so neither a fault nor an unknown hides that a device was last reported armed, ready or with its pin removed.

A sender that receives a [MAVLINK_M_ACK](../messages/military.md#MAVLINK_M_ACK) whose `result` is not a listed value, or is `MAVLINK_M_ACK_UNKNOWN`, handles it as an acknowledgment that did not arrive: it sends the message again unchanged, as the `MAVLINK_M_ACK` description allows, and the receiver answers that copy with its latest answer without acting on it a second time, or, for a message it refused, checks the copy again (see [What a Refusal Records](refusals_and_resends.md#what-a-refusal-records)).
A requester handles a [SENSOR_TASKING](../messages/military.md#SENSOR_TASKING) status response whose `status` or `sensor_mode` is not a listed value the same way, as a response that did not arrive, and treats the state of that task as unknown.

### Commanded Values

A receiver must refuse a message whose commanded field (see [Scope](#scope)) is not one of its enum's listed values, also one sent with `target_system` 0, since such a value may be a damaged stop.
It also refuses an [ESAD_ARMING](../messages/military.md#ESAD_ARMING), [ESAD_CONFIG](../messages/military.md#ESAD_CONFIG) or [ENGAGEMENT_DIRECTIVE](../messages/military.md#ENGAGEMENT_DIRECTIVE) addressed to it whose commanded field is its enum's 0 entry, since those messages carry nothing else to act on and a cleared field decodes as 0.
One of these sent with `target_system` 0 that carries that entry is not acted on or answered.

In [LOITER_MUNITION_CONTROL](../messages/military.md#LOITER_MUNITION_CONTROL), [TERMINAL_CONTROL](../messages/military.md#TERMINAL_CONTROL) and [SPLASH_CORRECTION](../messages/military.md#SPLASH_CORRECTION), `NONE` is a valid request for no change.
A receiver treats `ABORT_AUTHORITY_UNKNOWN` as `ABORT_AUTHORITY_NOT_ESTABLISHED`, and `DANGER_CLOSE_UNKNOWN` in a [CALL_FOR_FIRE](../messages/military.md#CALL_FOR_FIRE) or [CAS_9LINE](../messages/military.md#CAS_9LINE) as `DANGER_CLOSE_YES`, so an unset or zeroed value never asserts the less cautious reading.

A receiver that refuses a message:

- acts on none of its fields, so it arms, safes, releases, reconfigures and terminates nothing, except that a munition still applies a stop that the other commanded field of a `LOITER_MUNITION_CONTROL` carries, and an aircraft still acts on `MAVLINK_M_CAS_ABORT` or `MAVLINK_M_CAS_CEASE_FIRE` in a `TERMINAL_CONTROL` whose `tac_type` or `abort_authority_present` is not listed, since a stop fails toward safe
- shows the refusal to any operator who acts on what the message commands
- answers it in `MAVLINK_M_ACK` with result `MAVLINK_M_ACK_FAILED`, never `MAVLINK_M_ACK_NOT_APPLICABLE` or another result that depends on the field it could not read, and a `reason` naming that field, addressed and keyed like any acknowledgment of that message. Each commanded message's description gives its `ack_instance`

A message sent with `target_system` 0, and a component's copy of one sent with `target_component` 0, is answered only where its other fields select something the receiver holds, as the `MAVLINK_M_ACK` description has it for any message sent to every system.

A sensor acts on nothing in a `SENSOR_TASKING` request whose `sensor_mode` is not a listed value, and a receiver acts on nothing in one whose `status` is not a listed value, which is neither a request nor a response.
Neither answers it or keeps it as processed, so a requester that gets no status response sends its request again, unchanged, up to the number of times set for the network and only while it has sent that sensor no later request, and the sensor checks that copy again.

A receiver refuses [MAV_CMD_MAVLINK_M_STORE_SAFE](../messages/military.md#MAV_CMD_MAVLINK_M_STORE_SAFE) in [COMMAND_ACK](https://mavlink.io/en/messages/common.html#COMMAND_ACK) with `MAV_RESULT_DENIED` when param 2 is not exactly `MAVLINK_M_ESAD_REQUEST_DISARM`, records the refusal as a stop, and leaves the store's arming as it was.

What a refusal records and ends, and what the sender sends again, are in [Refusals and Resends](refusals_and_resends.md).

### Bridges and Gateways

A bridge to a component bus, as the TRANSPORT AND BRIDGING notes in the `military.xml` header describe, is a receiver on one side and a sender on the other, and answers as part of the receiving system:

- a bridge that receives a commanded field must apply the checks above, and must refuse a message whose commanded field is not one of its enum's listed values instead of forwarding it, answering as [Commanded Values](#commanded-values) says. For a command it forwards, it answers only with the device's result, and it does not refuse a copy that differs from a message it has forwarded only in commanded fields whose values are not listed: it neither forwards nor answers that copy and records nothing for it
- a bridge that maps a component-bus value onto a reported field must send a value it can't map as the enum's `FAULT` entry, or as `UNKNOWN` if the enum has none, and never as another defined state
- where the component bus carries the same values, as the header's aligned value assignments require, a bridge passes each value on unchanged and the protection continues across it; where the other side uses other values, the protection ends where the bridge converts a value out of a codeword and starts again where it converts one into a codeword, so the bridge converts by exact lookup straight from the codeword it received and straight into the codeword it sends

A gateway to another network or protocol follows the ADDRESSING AND GATEWAYS rules in the `military.xml` header: it applies these checks before it translates, never translates a commanded value that is not one of its enum's listed values, and refuses such a message as a receiver does, answering `MAVLINK_M_ACK_FAILED` for one addressed to a participant it represents and nothing for one sent to every system.
Like a receiver, it does not keep a refused message as processed (see [What a Refusal Records](refusals_and_resends.md#what-a-refusal-records)), so it carries every repeat of a stop, and it does not refuse a copy that differs from a message it has forwarded only in commanded fields whose values are not listed: it neither forwards nor answers that copy and records nothing for it.

A gateway sends a far-side value it can't map onto a reported field as the enum's `FAULT` entry, or as `UNKNOWN` if the enum has none.
A receiver behind a bridge or gateway can't tell a `FAULT` or `UNKNOWN` sent for a value that could not be mapped from one the device reported.

A router that forwards frames unchanged, as [MAVLink routing](https://mavlink.io/en/guide/routing.html) requires, needs no step of its own: the sender's checksum still covers the value.

## Migrating From Sequential Values

The new values are a deliberate breaking wire-format change for the twenty-two in-scope enums, and the codeword form of the store safe command is a new command, `MAV_CMD_MAVLINK_M_STORE_SAFE`; no other enum changes value.
The dialect keeps message IDs stable once assigned, and its [contribution rules](https://github.com/Dronecode/mavlink-military/blob/main/CONTRIBUTING.md#breaking-changes) make renumbering an enum value a breaking change; this one is deliberate.

Message lengths, field layouts and `CRC_EXTRA` don't change, because the [`CRC_EXTRA` calculation](https://mavlink.io/en/guide/serialization.html#crc_extra) covers the message name and each field's type and name, not enum values.
A peer on the old values and a peer on the new ones therefore exchange the affected messages with no checksum or length error, and nothing in the frame tells the two apart:

- a receiver on the new values reads every old 0 as `UNKNOWN` or `NONE`, so it refuses an old `DISARM` or `ABORT` addressed to it, which were 0, and does not act on one sent to every system (see [Commanded Values](#commanded-values)), and handles an old `danger_close` 0 as danger close. It refuses every other old commanded value and shows every other old reported value as a detected fault
- a receiver on the old values reads the new `UNKNOWN` or `NONE` (0) of the eight enums whose old 0 was a real state as that state (`DISARMED`, `DISARM`, `NOT_PRESENT`, `OPEN`, `SAFE`, `ABORT`, the sensor health `NOT_PRESENT` or `RECEIVED`), and every other new value as out of range. A receiver on the old values that:
  - tests `abort_authority_present` as a nonzero flag reads both of its new values as established
  - tests `danger_close` as a nonzero flag reads both of its new values as danger close, the cautious reading, and an unset 0 as not danger close, as it does today
  - compares `danger_close` with 1 reads every new value, `DANGER_CLOSE_YES` included, as not danger close
  - treats any nonzero `arming_request` as an arm reads a new `DISARM` as an arm, and arms if that `DISARM` carries the challenge its ESAD advertises

Both ends must therefore be built from the same dialect revision.

Each enum kept its relative order, which was its old sequential numbering (the first-listed entry was 0, the second 1, and so on), except the two in the third item:

- The twelve enums whose 0 was already `UNKNOWN`, `UNSPECIFIED` or `NONE` ([MAVLINK_M_ESAD_PIN_STATE](../messages/military.md#MAVLINK_M_ESAD_PIN_STATE), [MAVLINK_M_ESAD_ARM_DELAY_SETTING](../messages/military.md#MAVLINK_M_ESAD_ARM_DELAY_SETTING), [MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE](../messages/military.md#MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE), [MAVLINK_M_LM_CONSENT_STATE](../messages/military.md#MAVLINK_M_LM_CONSENT_STATE), [MAVLINK_M_LM_TERMINATE](../messages/military.md#MAVLINK_M_LM_TERMINATE), [MAVLINK_M_STORE_READINESS](../messages/military.md#MAVLINK_M_STORE_READINESS), [MAVLINK_M_CAS_CLEARANCE](../messages/military.md#MAVLINK_M_CAS_CLEARANCE), [MAVLINK_M_FIRE_MISSION_COMMAND](../messages/military.md#MAVLINK_M_FIRE_MISSION_COMMAND), [MAVLINK_M_TAC_TYPE](../messages/military.md#MAVLINK_M_TAC_TYPE), [MAVLINK_M_FIRE_CONTROL_METHOD](../messages/military.md#MAVLINK_M_FIRE_CONTROL_METHOD), [MAVLINK_M_SENSOR_MODE](../messages/military.md#MAVLINK_M_SENSOR_MODE) and [MAVLINK_M_TASKING_STATUS](../messages/military.md#MAVLINK_M_TASKING_STATUS)) use the old value as the order index. Old value 1 now encodes as 15, 2 as 51, and so on.
- Six of the others ([MAVLINK_M_ESAD_ARMING_STATUS](../messages/military.md#MAVLINK_M_ESAD_ARMING_STATUS), [MAVLINK_M_ESAD_MUNITION_STATUS](../messages/military.md#MAVLINK_M_ESAD_MUNITION_STATUS), [MAVLINK_M_ESAD_IGNITION_STATUS](../messages/military.md#MAVLINK_M_ESAD_IGNITION_STATUS), [MAVLINK_M_RWS_ARMING_STATE](../messages/military.md#MAVLINK_M_RWS_ARMING_STATE), [MAVLINK_M_ENGAGEMENT_DIRECTIVE](../messages/military.md#MAVLINK_M_ENGAGEMENT_DIRECTIVE) and [MAVLINK_M_ACK_RESULT](../messages/military.md#MAVLINK_M_ACK_RESULT)) used 0 for a real state (`DISARMED`, `NOT_PRESENT`, `OPEN`, `SAFE`, `ABORT` and `RECEIVED`), so a cleared buffer or unset field read as that state. Each gained an `UNKNOWN` or `NONE` entry at 0, so old value `v` moves to order index `v + 1`: old 0 now encodes as 15, and old 1 as 51, as for `MAVLINK_M_ESAD_ARMING_ARMED`.
- [MAVLINK_M_ESAD_ARMING_REQUEST](../messages/military.md#MAVLINK_M_ESAD_ARMING_REQUEST) gained `NONE` at 0 as well and lists `ARM` before `DISARM`, so `ARM` is 15 and `DISARM` is 51; [MAVLINK_M_SENSOR_HEALTH](../messages/military.md#MAVLINK_M_SENSOR_HEALTH) gained `UNKNOWN` at 0 and lists `OK`, `DEGRADED` and `FAULT` first (15, 51 and 60), then `NOT_PRESENT`, `CALIBRATING` and `OUT_OF_RANGE` (85, 90 and 102).
- `TERMINAL_CONTROL.abort_authority_present` takes [ABORT_AUTHORITY](../messages/military.md#ABORT_AUTHORITY): its old 0 (not established) and 1 (established) now encode as 15 and 51, behind a new `UNKNOWN` at 0.
- `CALL_FOR_FIRE.danger_close` and `CAS_9LINE.danger_close` take [DANGER_CLOSE](../messages/military.md#DANGER_CLOSE): their old 0 (not danger close) and 1 (danger close) now encode as 15 and 51, behind a new `UNKNOWN` at 0, which a receiver handles as danger close.

`MAV_CMD_MAVLINK_M_STORE_SAFE` (53094) takes the `MAVLINK_M_ESAD_ARMING_REQUEST` value in param 2, so a receiver built before it answers `MAV_RESULT_UNSUPPORTED` instead of reading that value by an old meaning.
[MAV_CMD_MAVLINK_M_STORE_ARM](../messages/military.md#MAV_CMD_MAVLINK_M_STORE_ARM) keeps its param 2 values, 0 to safe and 1 for an arm, which receivers deny, and is deprecated in its favour.

The current values are always those in `military.xml`; this page does not repeat them per enum, so the two cannot drift apart.

The entries other than `UNKNOWN` and `MANUAL` of `MAVLINK_M_ESAD_ARM_DELAY_SETTING` and `MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE` are renamed to device-defined numbered settings: `MAVLINK_M_ESAD_ARM_DELAY_SETTING_1` to `_3`, and `MAVLINK_M_ESAD_TRIG_DIST_STANDOFF_1` and `_2`, with `MAVLINK_M_ESAD_TRIG_DIST_MANUAL` unchanged.
Order is preserved, so the old entry at order index n is now `SETTING_n` or `STANDOFF_n`, and each entry's description says its delay or standoff is defined in the device ICD.
