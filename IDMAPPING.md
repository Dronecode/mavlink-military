# MAVLink-M message ID mapping

**Status: active allocation for this dialect.** Upstream MAVLink `all.xml`
reserves `53000-53999`; this dialect uses `53000-53099` for the initial shared
MAVLink-M messages and commands, `53100-53899` for future shared growth, and
`53900-53999` for private/downstream implementor-specific messages.

The earlier development block used `60000-60099`, which collides with upstream
`storm32` and `AVSSUAS` allocations. The former optional extension messages have
been folded into `military.xml`. The `military_extensions.xml` file remains only
as an example/template for downstream private messages in `53900-53999`; it is
not part of the shared generated dialect in this repository.

## Shared messages

| Name | Old development ID | New ID |
| --- | --- | --- |
| TRACK_IDENTITY | 60000 | 53000 |
| TARGET_CUE | 60001 | 53001 |
| TARGET_HANDOVER | 60002 | 53002 |
| PARTICIPANT_POSITION | 60003 | 53003 |
| MAVLINK_M_ACK | 60004 | 53004 |
| TARGET (formerly TARGET_COORD) | 60010 | 53010 |
| TARGET_SET_COORD | 60011 | 53011 |
| TARGET_BOX_COORD | 60012 | 53012 |
| TARGET_AUTHORIZATION | 60013 | 53013 |
| FIRES | 60020 | 53020 |
| SPLASH_CORRECTION | 60021 | 53021 |
| BATTLE_DAMAGE_ASSESSMENT | 60022 | 53022 |
| ENGAGEMENT_DIRECTIVE | 60023 | 53023 |
| CALL_FOR_FIRE | 60024 | 53024 |
| ESAD_STATE | 60030 | 53030 |
| ESAD_ARMING | 60031 | 53031 |
| ESAD_CONFIG | 60032 | 53032 |
| STORE_STATUS | 60033 | 53033 |
| STORE_SENSOR_STATUS | 60034 | 53034 |
| STORE_MUNITION | 60035 | 53035 |
| LOITER_MUNITION_CONTROL | 60036 | 53036 |
| RWS_POSE | 60040 | 53040 |
| RWS_STATE | 60041 | 53041 |
| SENSOR_TASKING | 60050 | 53050 |
| CAS_9LINE | 60060 | 53060 |
| TERMINAL_CONTROL | 60061 | 53061 |

Rule for message IDs from the development block: **new = old - 7000**. Internal
functional grouping is preserved.

## MAV_CMD entries

| Name | Old value | New value |
| --- | --- | --- |
| MAV_CMD_MAVLINK_M_STORE_ARM | 60100 | 53090 |
| MAV_CMD_MAVLINK_M_STORE_RUN_BIT | 60101 | 53091 |
| MAV_CMD_MAVLINK_M_STORE_REQUEST_STATUS | 60102 | 53092 |
| MAV_CMD_MAVLINK_M_STORE_SET_DECEL_THRESHOLD | 60103 | 53093 |

Commands are placed at `53090-53093` to keep them inside the same `53000-53099`
window as the messages.

## Reserved blocks

| Range | Use |
| --- | --- |
| 53062-53089 | Future shared MAVLink-M messages accepted into this dialect. |
| 53094-53099 | Future shared MAVLink-M command entries. |
| 53100-53899 | Future shared MAVLink-M allocations as the dialect grows. |
| 53900-53999 | Private/downstream implementor-specific messages. These are not shared IDs and require a private ICD between participating systems. |

## Prior Dronecode `military.xml` IDs

The Dronecode/mavlink-military repo previously carried an 11-message preliminary
spec at `53000-53010`. Those messages map to the current IDs as follows:

| Name | Old ID | Current ID |
| --- | --- | --- |
| TARGET_SET_COORD | 53000 | 53011 |
| TARGET_BOX_COORD | 53001 | 53012 |
| TARGET_COORD | 53002 | 53010 (`TARGET`) |
| FIRES | 53003 | 53020 |
| SPLASH_CORRECTION | 53004 | 53021 |
| TARGET_HANDOVER | 53005 | 53002 |
| BATTLE_DAMAGE_ASSESSMENT | 53006 | 53022 |
| ESAD_STATE | 53007 | 53030 |
| ESAD_ARMING | 53008 | 53031 |
| RWS_POSE | 53009 | 53040 |
| RWS_STATE | 53010 | 53041 |
