# Message Map

MAVLink-M's messages and commands fall into four areas, plus one
acknowledgment that serves them all. Each name links to its full definition in
the [message reference](../messages/military.md).

## Safety and arming

Arming, ignition and fault state for each Electronic Safe and Arm Device
(ESAD), and the readiness of each store before release.

| Message | ID | What it carries |
| --- | --- | --- |
| [ESAD_STATE](../messages/military.md#ESAD_STATE) | 53030 | Arming, munition and ignition state, fault flags and software identity of one ESAD |
| [ESAD_ARMING](../messages/military.md#ESAD_ARMING) | 53031 | Arms or disarms ESADs. An arm must carry the challenge the ESAD advertises; a disarm always applies |
| [ESAD_CONFIG](../messages/military.md#ESAD_CONFIG) | 53032 | Sets a live safe/arm parameter, checked against the same challenge as an arm |
| [STORE_STATUS](../messages/military.md#STORE_STATUS) | 53033 | One readiness value per store, from ESAD state and sensor health, to gate release |
| [STORE_SENSOR_STATUS](../messages/military.md#STORE_SENSOR_STATUS) | 53034 | Health and reading of one deceleration or landing-trigger sensor |
| [STORE_MUNITION](../messages/military.md#STORE_MUNITION) | 53035 | What a store holds, for joint weapon-status reports, without fuze or employment settings |

| Command | Number | What it does |
| --- | --- | --- |
| [MAV_CMD_MAVLINK_M_STORE_ARM](../messages/military.md#MAV_CMD_MAVLINK_M_STORE_ARM) | 53090 | Safes a store's ESAD. Arming goes through ESAD_ARMING |
| [MAV_CMD_MAVLINK_M_STORE_RUN_BIT](../messages/military.md#MAV_CMD_MAVLINK_M_STORE_RUN_BIT) | 53091 | Runs a built-in self-test on a store |
| [MAV_CMD_MAVLINK_M_STORE_REQUEST_STATUS](../messages/military.md#MAV_CMD_MAVLINK_M_STORE_REQUEST_STATUS) | 53092 | Asks a store to push its status |
| [MAV_CMD_MAVLINK_M_STORE_SET_DECEL_THRESHOLD](../messages/military.md#MAV_CMD_MAVLINK_M_STORE_SET_DECEL_THRESHOLD) | 53093 | Sets a store's deceleration or landing trigger threshold |

## Targeting and engagement

Targets, fire missions, close air support and loitering munitions, from the
first report to the damage assessment.

| Message | ID | What it carries |
| --- | --- | --- |
| [TARGET](../messages/military.md#TARGET) | 53010 | Position, velocity, classification and engagement context of one target. It does not authorize action |
| [TARGET_SET_COORD](../messages/military.md#TARGET_SET_COORD) | 53011 | A circular area grouping targets that share an operational context |
| [TARGET_BOX_COORD](../messages/military.md#TARGET_BOX_COORD) | 53012 | A four-corner area grouping targets |
| [TARGET_AUTHORIZATION](../messages/military.md#TARGET_AUTHORIZATION) | 53013 | A record of the human authority's identification and clearance for a track, for audit. Never a trigger |
| [TARGET_HANDOVER](../messages/military.md#TARGET_HANDOVER) | 53002 | Hands tracking of a target to another system, with its state, classification and authorization |
| [CALL_FOR_FIRE](../messages/military.md#CALL_FOR_FIRE) | 53024 | Call-for-fire method elements, mappable to VMF K02.4 |
| [FIRES](../messages/military.md#FIRES) | 53020 | Fire mission order: engage a coordinate, with the expected impact time and accuracy |
| [ENGAGEMENT_DIRECTIVE](../messages/military.md#ENGAGEMENT_DIRECTIVE) | 53023 | Abort, check fire, resume or re-target a mission. Abort and check fire act on receipt |
| [SPLASH_CORRECTION](../messages/military.md#SPLASH_CORRECTION) | 53021 | Spotting after impact, to correct a fire mission |
| [BATTLE_DAMAGE_ASSESSMENT](../messages/military.md#BATTLE_DAMAGE_ASSESSMENT) | 53022 | Assessed damage to an engaged target, with a confidence |
| [CAS_9LINE](../messages/military.md#CAS_9LINE) | 53060 | Close air support 9-line brief |
| [TERMINAL_CONTROL](../messages/military.md#TERMINAL_CONTROL) | 53061 | Terminal attack control: clearances, aborts and aircraft status calls |
| [LOITER_MUNITION_CONTROL](../messages/military.md#LOITER_MUNITION_CONTROL) | 53036 | Control and human-consent handshake for a loitering munition, including abort and wave-off |

## Remote weapon systems

Where a mounted weapon system sits on its host, and what state it is in.

| Message | ID | What it carries |
| --- | --- | --- |
| [RWS_POSE](../messages/military.md#RWS_POSE) | 53040 | Mounting offset and orientation on the host vehicle, plus position and velocity when known |
| [RWS_STATE](../messages/military.md#RWS_STATE) | 53041 | Operational state, arming status and loaded weapon |

## Tracks and awareness

Who and what is where, shared across the force.

| Message | ID | What it carries |
| --- | --- | --- |
| [TRACK_IDENTITY](../messages/military.md#TRACK_IDENTITY) | 53000 | One track ID for a real-world object, kept from detection to assessment, with how it was identified |
| [TARGET_CUE](../messages/military.md#TARGET_CUE) | 53001 | Points a consumer at a location to observe, kept apart from engagement messages |
| [PARTICIPANT_POSITION](../messages/military.md#PARTICIPANT_POSITION) | 53003 | A friendly participant's identity and position, for the common operational picture |
| [SENSOR_TASKING](../messages/military.md#SENSOR_TASKING) | 53050 | Sensor or payload tasking from a UCI command node, and the platform's status reply |

## Across all areas

| Message | ID | What it carries |
| --- | --- | --- |
| [MAVLINK_M_ACK](../messages/military.md#MAVLINK_M_ACK) | 53004 | Acknowledges delivery and acceptance of a MAVLink-M message, matched to the message it answers |
