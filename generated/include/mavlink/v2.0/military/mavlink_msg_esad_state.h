#pragma once
// MESSAGE ESAD_STATE PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_ESAD_STATE 53030


typedef struct __mavlink_esad_state_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint32_t arming_challenge_hash; /*<  Challenge hash for arming authentication of this ESAD instance.*/
 uint32_t fault_flags; /*<  Active fault flag bitmask.*/
 float input_1; /*<  Analog/digital input 1 (implementation-defined). For the standard safety inputs use the typed fields below instead.*/
 float input_2; /*<  Analog/digital input 2 (implementation-defined). For the standard safety inputs use the typed fields below instead.*/
 int16_t arm_delay_remaining_s; /*< [s] Live arming-delay countdown: seconds remaining after the in-flight-event signal until arming is permitted. -1 = not counting / not applicable. Distinct from arm_delay_setting (the switch position).*/
 uint8_t esad_id; /*<  Vehicle-local ESAD instance identifier. Must be 1-254. 0 is invalid for ESAD_STATE, 255 is reserved. Systems that support broadcast arming set the same arming_challenge_hash on each target ESAD before accepting ESAD_ARMING.esad_id = 0.*/
 uint8_t sw_version_hash[8]; /*<  Software version as 8-byte short Git hash.*/
 uint8_t arming_status; /*<  Current arming state.*/
 uint8_t munition_status; /*<  Current munition state.*/
 uint8_t ignition_status; /*<  Current ignition circuit state.*/
 uint8_t munition_type; /*<  Munition/store type identifier (implementation-defined).*/
 uint8_t store_id; /*<  Store instance identifier. Fixed physical bay assignment: a bay keeps its store_id permanently, and when a store is expended the bay may be reloaded under the same store_id. IDs never renumber. 0 = not applicable / single store. This is the canonical definition of store_id across the dialect.*/
 uint8_t pin_state; /*<  Physical safety pull-pin state (read-only status).*/
 uint8_t arm_delay_setting; /*<  Selected arming-delay switch position (90/60/30 s). The chosen setting.*/
 uint8_t trigger_distance_mode; /*<  Trigger-distance standoff mode currently in effect (coarse selection, not a distance value).*/
 uint8_t track_uid[16]; /*<  Track UID (UUID) of the engagement this store is armed for, when applicable. Ties the armed state to a specific authorized track so a monitoring station sees "armed against track X," not merely "an ESAD is hot." All-zero if not associated with a track.*/
} mavlink_esad_state_t;

#define MAVLINK_MSG_ID_ESAD_STATE_LEN 59
#define MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN 59
#define MAVLINK_MSG_ID_53030_LEN 59
#define MAVLINK_MSG_ID_53030_MIN_LEN 59

#define MAVLINK_MSG_ID_ESAD_STATE_CRC 81
#define MAVLINK_MSG_ID_53030_CRC 81

#define MAVLINK_MSG_ESAD_STATE_FIELD_SW_VERSION_HASH_LEN 8
#define MAVLINK_MSG_ESAD_STATE_FIELD_TRACK_UID_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ESAD_STATE { \
    53030, \
    "ESAD_STATE", \
    17, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_esad_state_t, time_usec) }, \
         { "esad_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_esad_state_t, esad_id) }, \
         { "arming_challenge_hash", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_esad_state_t, arming_challenge_hash) }, \
         { "fault_flags", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_esad_state_t, fault_flags) }, \
         { "input_1", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_esad_state_t, input_1) }, \
         { "input_2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_esad_state_t, input_2) }, \
         { "sw_version_hash", NULL, MAVLINK_TYPE_UINT8_T, 8, 27, offsetof(mavlink_esad_state_t, sw_version_hash) }, \
         { "arming_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 35, offsetof(mavlink_esad_state_t, arming_status) }, \
         { "munition_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 36, offsetof(mavlink_esad_state_t, munition_status) }, \
         { "ignition_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 37, offsetof(mavlink_esad_state_t, ignition_status) }, \
         { "munition_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 38, offsetof(mavlink_esad_state_t, munition_type) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 39, offsetof(mavlink_esad_state_t, store_id) }, \
         { "pin_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_esad_state_t, pin_state) }, \
         { "arm_delay_setting", NULL, MAVLINK_TYPE_UINT8_T, 0, 41, offsetof(mavlink_esad_state_t, arm_delay_setting) }, \
         { "arm_delay_remaining_s", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_esad_state_t, arm_delay_remaining_s) }, \
         { "trigger_distance_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_esad_state_t, trigger_distance_mode) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 43, offsetof(mavlink_esad_state_t, track_uid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ESAD_STATE { \
    "ESAD_STATE", \
    17, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_esad_state_t, time_usec) }, \
         { "esad_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_esad_state_t, esad_id) }, \
         { "arming_challenge_hash", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_esad_state_t, arming_challenge_hash) }, \
         { "fault_flags", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_esad_state_t, fault_flags) }, \
         { "input_1", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_esad_state_t, input_1) }, \
         { "input_2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_esad_state_t, input_2) }, \
         { "sw_version_hash", NULL, MAVLINK_TYPE_UINT8_T, 8, 27, offsetof(mavlink_esad_state_t, sw_version_hash) }, \
         { "arming_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 35, offsetof(mavlink_esad_state_t, arming_status) }, \
         { "munition_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 36, offsetof(mavlink_esad_state_t, munition_status) }, \
         { "ignition_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 37, offsetof(mavlink_esad_state_t, ignition_status) }, \
         { "munition_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 38, offsetof(mavlink_esad_state_t, munition_type) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 39, offsetof(mavlink_esad_state_t, store_id) }, \
         { "pin_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_esad_state_t, pin_state) }, \
         { "arm_delay_setting", NULL, MAVLINK_TYPE_UINT8_T, 0, 41, offsetof(mavlink_esad_state_t, arm_delay_setting) }, \
         { "arm_delay_remaining_s", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_esad_state_t, arm_delay_remaining_s) }, \
         { "trigger_distance_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_esad_state_t, trigger_distance_mode) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 43, offsetof(mavlink_esad_state_t, track_uid) }, \
         } \
}
#endif

/**
 * @brief Pack a esad_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param esad_id  Vehicle-local ESAD instance identifier. Must be 1-254. 0 is invalid for ESAD_STATE, 255 is reserved. Systems that support broadcast arming set the same arming_challenge_hash on each target ESAD before accepting ESAD_ARMING.esad_id = 0.
 * @param arming_challenge_hash  Challenge hash for arming authentication of this ESAD instance.
 * @param fault_flags  Active fault flag bitmask.
 * @param input_1  Analog/digital input 1 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 * @param input_2  Analog/digital input 2 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 * @param sw_version_hash  Software version as 8-byte short Git hash.
 * @param arming_status  Current arming state.
 * @param munition_status  Current munition state.
 * @param ignition_status  Current ignition circuit state.
 * @param munition_type  Munition/store type identifier (implementation-defined).
 * @param store_id  Store instance identifier. Fixed physical bay assignment: a bay keeps its store_id permanently, and when a store is expended the bay may be reloaded under the same store_id. IDs never renumber. 0 = not applicable / single store. This is the canonical definition of store_id across the dialect.
 * @param pin_state  Physical safety pull-pin state (read-only status).
 * @param arm_delay_setting  Selected arming-delay switch position (90/60/30 s). The chosen setting.
 * @param arm_delay_remaining_s [s] Live arming-delay countdown: seconds remaining after the in-flight-event signal until arming is permitted. -1 = not counting / not applicable. Distinct from arm_delay_setting (the switch position).
 * @param trigger_distance_mode  Trigger-distance standoff mode currently in effect (coarse selection, not a distance value).
 * @param track_uid  Track UID (UUID) of the engagement this store is armed for, when applicable. Ties the armed state to a specific authorized track so a monitoring station sees "armed against track X," not merely "an ESAD is hot." All-zero if not associated with a track.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint8_t esad_id, uint32_t arming_challenge_hash, uint32_t fault_flags, float input_1, float input_2, const uint8_t *sw_version_hash, uint8_t arming_status, uint8_t munition_status, uint8_t ignition_status, uint8_t munition_type, uint8_t store_id, uint8_t pin_state, uint8_t arm_delay_setting, int16_t arm_delay_remaining_s, uint8_t trigger_distance_mode, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_int16_t(buf, 24, arm_delay_remaining_s);
    _mav_put_uint8_t(buf, 26, esad_id);
    _mav_put_uint8_t(buf, 35, arming_status);
    _mav_put_uint8_t(buf, 36, munition_status);
    _mav_put_uint8_t(buf, 37, ignition_status);
    _mav_put_uint8_t(buf, 38, munition_type);
    _mav_put_uint8_t(buf, 39, store_id);
    _mav_put_uint8_t(buf, 40, pin_state);
    _mav_put_uint8_t(buf, 41, arm_delay_setting);
    _mav_put_uint8_t(buf, 42, trigger_distance_mode);
    _mav_put_uint8_t_array(buf, 27, sw_version_hash, 8);
    _mav_put_uint8_t_array(buf, 43, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#else
    mavlink_esad_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.fault_flags = fault_flags;
    packet.input_1 = input_1;
    packet.input_2 = input_2;
    packet.arm_delay_remaining_s = arm_delay_remaining_s;
    packet.esad_id = esad_id;
    packet.arming_status = arming_status;
    packet.munition_status = munition_status;
    packet.ignition_status = ignition_status;
    packet.munition_type = munition_type;
    packet.store_id = store_id;
    packet.pin_state = pin_state;
    packet.arm_delay_setting = arm_delay_setting;
    packet.trigger_distance_mode = trigger_distance_mode;
    mav_array_memcpy(packet.sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
}

/**
 * @brief Pack a esad_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param esad_id  Vehicle-local ESAD instance identifier. Must be 1-254. 0 is invalid for ESAD_STATE, 255 is reserved. Systems that support broadcast arming set the same arming_challenge_hash on each target ESAD before accepting ESAD_ARMING.esad_id = 0.
 * @param arming_challenge_hash  Challenge hash for arming authentication of this ESAD instance.
 * @param fault_flags  Active fault flag bitmask.
 * @param input_1  Analog/digital input 1 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 * @param input_2  Analog/digital input 2 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 * @param sw_version_hash  Software version as 8-byte short Git hash.
 * @param arming_status  Current arming state.
 * @param munition_status  Current munition state.
 * @param ignition_status  Current ignition circuit state.
 * @param munition_type  Munition/store type identifier (implementation-defined).
 * @param store_id  Store instance identifier. Fixed physical bay assignment: a bay keeps its store_id permanently, and when a store is expended the bay may be reloaded under the same store_id. IDs never renumber. 0 = not applicable / single store. This is the canonical definition of store_id across the dialect.
 * @param pin_state  Physical safety pull-pin state (read-only status).
 * @param arm_delay_setting  Selected arming-delay switch position (90/60/30 s). The chosen setting.
 * @param arm_delay_remaining_s [s] Live arming-delay countdown: seconds remaining after the in-flight-event signal until arming is permitted. -1 = not counting / not applicable. Distinct from arm_delay_setting (the switch position).
 * @param trigger_distance_mode  Trigger-distance standoff mode currently in effect (coarse selection, not a distance value).
 * @param track_uid  Track UID (UUID) of the engagement this store is armed for, when applicable. Ties the armed state to a specific authorized track so a monitoring station sees "armed against track X," not merely "an ESAD is hot." All-zero if not associated with a track.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_state_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint8_t esad_id, uint32_t arming_challenge_hash, uint32_t fault_flags, float input_1, float input_2, const uint8_t *sw_version_hash, uint8_t arming_status, uint8_t munition_status, uint8_t ignition_status, uint8_t munition_type, uint8_t store_id, uint8_t pin_state, uint8_t arm_delay_setting, int16_t arm_delay_remaining_s, uint8_t trigger_distance_mode, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_int16_t(buf, 24, arm_delay_remaining_s);
    _mav_put_uint8_t(buf, 26, esad_id);
    _mav_put_uint8_t(buf, 35, arming_status);
    _mav_put_uint8_t(buf, 36, munition_status);
    _mav_put_uint8_t(buf, 37, ignition_status);
    _mav_put_uint8_t(buf, 38, munition_type);
    _mav_put_uint8_t(buf, 39, store_id);
    _mav_put_uint8_t(buf, 40, pin_state);
    _mav_put_uint8_t(buf, 41, arm_delay_setting);
    _mav_put_uint8_t(buf, 42, trigger_distance_mode);
    _mav_put_uint8_t_array(buf, 27, sw_version_hash, 8);
    _mav_put_uint8_t_array(buf, 43, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#else
    mavlink_esad_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.fault_flags = fault_flags;
    packet.input_1 = input_1;
    packet.input_2 = input_2;
    packet.arm_delay_remaining_s = arm_delay_remaining_s;
    packet.esad_id = esad_id;
    packet.arming_status = arming_status;
    packet.munition_status = munition_status;
    packet.ignition_status = ignition_status;
    packet.munition_type = munition_type;
    packet.store_id = store_id;
    packet.pin_state = pin_state;
    packet.arm_delay_setting = arm_delay_setting;
    packet.trigger_distance_mode = trigger_distance_mode;
    mav_array_memcpy(packet.sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_STATE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#endif
}

/**
 * @brief Pack a esad_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param esad_id  Vehicle-local ESAD instance identifier. Must be 1-254. 0 is invalid for ESAD_STATE, 255 is reserved. Systems that support broadcast arming set the same arming_challenge_hash on each target ESAD before accepting ESAD_ARMING.esad_id = 0.
 * @param arming_challenge_hash  Challenge hash for arming authentication of this ESAD instance.
 * @param fault_flags  Active fault flag bitmask.
 * @param input_1  Analog/digital input 1 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 * @param input_2  Analog/digital input 2 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 * @param sw_version_hash  Software version as 8-byte short Git hash.
 * @param arming_status  Current arming state.
 * @param munition_status  Current munition state.
 * @param ignition_status  Current ignition circuit state.
 * @param munition_type  Munition/store type identifier (implementation-defined).
 * @param store_id  Store instance identifier. Fixed physical bay assignment: a bay keeps its store_id permanently, and when a store is expended the bay may be reloaded under the same store_id. IDs never renumber. 0 = not applicable / single store. This is the canonical definition of store_id across the dialect.
 * @param pin_state  Physical safety pull-pin state (read-only status).
 * @param arm_delay_setting  Selected arming-delay switch position (90/60/30 s). The chosen setting.
 * @param arm_delay_remaining_s [s] Live arming-delay countdown: seconds remaining after the in-flight-event signal until arming is permitted. -1 = not counting / not applicable. Distinct from arm_delay_setting (the switch position).
 * @param trigger_distance_mode  Trigger-distance standoff mode currently in effect (coarse selection, not a distance value).
 * @param track_uid  Track UID (UUID) of the engagement this store is armed for, when applicable. Ties the armed state to a specific authorized track so a monitoring station sees "armed against track X," not merely "an ESAD is hot." All-zero if not associated with a track.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint8_t esad_id,uint32_t arming_challenge_hash,uint32_t fault_flags,float input_1,float input_2,const uint8_t *sw_version_hash,uint8_t arming_status,uint8_t munition_status,uint8_t ignition_status,uint8_t munition_type,uint8_t store_id,uint8_t pin_state,uint8_t arm_delay_setting,int16_t arm_delay_remaining_s,uint8_t trigger_distance_mode,const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_int16_t(buf, 24, arm_delay_remaining_s);
    _mav_put_uint8_t(buf, 26, esad_id);
    _mav_put_uint8_t(buf, 35, arming_status);
    _mav_put_uint8_t(buf, 36, munition_status);
    _mav_put_uint8_t(buf, 37, ignition_status);
    _mav_put_uint8_t(buf, 38, munition_type);
    _mav_put_uint8_t(buf, 39, store_id);
    _mav_put_uint8_t(buf, 40, pin_state);
    _mav_put_uint8_t(buf, 41, arm_delay_setting);
    _mav_put_uint8_t(buf, 42, trigger_distance_mode);
    _mav_put_uint8_t_array(buf, 27, sw_version_hash, 8);
    _mav_put_uint8_t_array(buf, 43, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#else
    mavlink_esad_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.fault_flags = fault_flags;
    packet.input_1 = input_1;
    packet.input_2 = input_2;
    packet.arm_delay_remaining_s = arm_delay_remaining_s;
    packet.esad_id = esad_id;
    packet.arming_status = arming_status;
    packet.munition_status = munition_status;
    packet.ignition_status = ignition_status;
    packet.munition_type = munition_type;
    packet.store_id = store_id;
    packet.pin_state = pin_state;
    packet.arm_delay_setting = arm_delay_setting;
    packet.trigger_distance_mode = trigger_distance_mode;
    mav_array_memcpy(packet.sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
}

/**
 * @brief Encode a esad_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param esad_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_esad_state_t* esad_state)
{
    return mavlink_msg_esad_state_pack(system_id, component_id, msg, esad_state->time_usec, esad_state->esad_id, esad_state->arming_challenge_hash, esad_state->fault_flags, esad_state->input_1, esad_state->input_2, esad_state->sw_version_hash, esad_state->arming_status, esad_state->munition_status, esad_state->ignition_status, esad_state->munition_type, esad_state->store_id, esad_state->pin_state, esad_state->arm_delay_setting, esad_state->arm_delay_remaining_s, esad_state->trigger_distance_mode, esad_state->track_uid);
}

/**
 * @brief Encode a esad_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param esad_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_esad_state_t* esad_state)
{
    return mavlink_msg_esad_state_pack_chan(system_id, component_id, chan, msg, esad_state->time_usec, esad_state->esad_id, esad_state->arming_challenge_hash, esad_state->fault_flags, esad_state->input_1, esad_state->input_2, esad_state->sw_version_hash, esad_state->arming_status, esad_state->munition_status, esad_state->ignition_status, esad_state->munition_type, esad_state->store_id, esad_state->pin_state, esad_state->arm_delay_setting, esad_state->arm_delay_remaining_s, esad_state->trigger_distance_mode, esad_state->track_uid);
}

/**
 * @brief Encode a esad_state struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param esad_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_state_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_esad_state_t* esad_state)
{
    return mavlink_msg_esad_state_pack_status(system_id, component_id, _status, msg,  esad_state->time_usec, esad_state->esad_id, esad_state->arming_challenge_hash, esad_state->fault_flags, esad_state->input_1, esad_state->input_2, esad_state->sw_version_hash, esad_state->arming_status, esad_state->munition_status, esad_state->ignition_status, esad_state->munition_type, esad_state->store_id, esad_state->pin_state, esad_state->arm_delay_setting, esad_state->arm_delay_remaining_s, esad_state->trigger_distance_mode, esad_state->track_uid);
}

/**
 * @brief Send a esad_state message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param esad_id  Vehicle-local ESAD instance identifier. Must be 1-254. 0 is invalid for ESAD_STATE, 255 is reserved. Systems that support broadcast arming set the same arming_challenge_hash on each target ESAD before accepting ESAD_ARMING.esad_id = 0.
 * @param arming_challenge_hash  Challenge hash for arming authentication of this ESAD instance.
 * @param fault_flags  Active fault flag bitmask.
 * @param input_1  Analog/digital input 1 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 * @param input_2  Analog/digital input 2 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 * @param sw_version_hash  Software version as 8-byte short Git hash.
 * @param arming_status  Current arming state.
 * @param munition_status  Current munition state.
 * @param ignition_status  Current ignition circuit state.
 * @param munition_type  Munition/store type identifier (implementation-defined).
 * @param store_id  Store instance identifier. Fixed physical bay assignment: a bay keeps its store_id permanently, and when a store is expended the bay may be reloaded under the same store_id. IDs never renumber. 0 = not applicable / single store. This is the canonical definition of store_id across the dialect.
 * @param pin_state  Physical safety pull-pin state (read-only status).
 * @param arm_delay_setting  Selected arming-delay switch position (90/60/30 s). The chosen setting.
 * @param arm_delay_remaining_s [s] Live arming-delay countdown: seconds remaining after the in-flight-event signal until arming is permitted. -1 = not counting / not applicable. Distinct from arm_delay_setting (the switch position).
 * @param trigger_distance_mode  Trigger-distance standoff mode currently in effect (coarse selection, not a distance value).
 * @param track_uid  Track UID (UUID) of the engagement this store is armed for, when applicable. Ties the armed state to a specific authorized track so a monitoring station sees "armed against track X," not merely "an ESAD is hot." All-zero if not associated with a track.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_esad_state_send(mavlink_channel_t chan, uint64_t time_usec, uint8_t esad_id, uint32_t arming_challenge_hash, uint32_t fault_flags, float input_1, float input_2, const uint8_t *sw_version_hash, uint8_t arming_status, uint8_t munition_status, uint8_t ignition_status, uint8_t munition_type, uint8_t store_id, uint8_t pin_state, uint8_t arm_delay_setting, int16_t arm_delay_remaining_s, uint8_t trigger_distance_mode, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_int16_t(buf, 24, arm_delay_remaining_s);
    _mav_put_uint8_t(buf, 26, esad_id);
    _mav_put_uint8_t(buf, 35, arming_status);
    _mav_put_uint8_t(buf, 36, munition_status);
    _mav_put_uint8_t(buf, 37, ignition_status);
    _mav_put_uint8_t(buf, 38, munition_type);
    _mav_put_uint8_t(buf, 39, store_id);
    _mav_put_uint8_t(buf, 40, pin_state);
    _mav_put_uint8_t(buf, 41, arm_delay_setting);
    _mav_put_uint8_t(buf, 42, trigger_distance_mode);
    _mav_put_uint8_t_array(buf, 27, sw_version_hash, 8);
    _mav_put_uint8_t_array(buf, 43, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, buf, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#else
    mavlink_esad_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.fault_flags = fault_flags;
    packet.input_1 = input_1;
    packet.input_2 = input_2;
    packet.arm_delay_remaining_s = arm_delay_remaining_s;
    packet.esad_id = esad_id;
    packet.arming_status = arming_status;
    packet.munition_status = munition_status;
    packet.ignition_status = ignition_status;
    packet.munition_type = munition_type;
    packet.store_id = store_id;
    packet.pin_state = pin_state;
    packet.arm_delay_setting = arm_delay_setting;
    packet.trigger_distance_mode = trigger_distance_mode;
    mav_array_memcpy(packet.sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, (const char *)&packet, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#endif
}

/**
 * @brief Send a esad_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_esad_state_send_struct(mavlink_channel_t chan, const mavlink_esad_state_t* esad_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_esad_state_send(chan, esad_state->time_usec, esad_state->esad_id, esad_state->arming_challenge_hash, esad_state->fault_flags, esad_state->input_1, esad_state->input_2, esad_state->sw_version_hash, esad_state->arming_status, esad_state->munition_status, esad_state->ignition_status, esad_state->munition_type, esad_state->store_id, esad_state->pin_state, esad_state->arm_delay_setting, esad_state->arm_delay_remaining_s, esad_state->trigger_distance_mode, esad_state->track_uid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, (const char *)esad_state, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_ESAD_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_esad_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint8_t esad_id, uint32_t arming_challenge_hash, uint32_t fault_flags, float input_1, float input_2, const uint8_t *sw_version_hash, uint8_t arming_status, uint8_t munition_status, uint8_t ignition_status, uint8_t munition_type, uint8_t store_id, uint8_t pin_state, uint8_t arm_delay_setting, int16_t arm_delay_remaining_s, uint8_t trigger_distance_mode, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_int16_t(buf, 24, arm_delay_remaining_s);
    _mav_put_uint8_t(buf, 26, esad_id);
    _mav_put_uint8_t(buf, 35, arming_status);
    _mav_put_uint8_t(buf, 36, munition_status);
    _mav_put_uint8_t(buf, 37, ignition_status);
    _mav_put_uint8_t(buf, 38, munition_type);
    _mav_put_uint8_t(buf, 39, store_id);
    _mav_put_uint8_t(buf, 40, pin_state);
    _mav_put_uint8_t(buf, 41, arm_delay_setting);
    _mav_put_uint8_t(buf, 42, trigger_distance_mode);
    _mav_put_uint8_t_array(buf, 27, sw_version_hash, 8);
    _mav_put_uint8_t_array(buf, 43, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, buf, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#else
    mavlink_esad_state_t *packet = (mavlink_esad_state_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->arming_challenge_hash = arming_challenge_hash;
    packet->fault_flags = fault_flags;
    packet->input_1 = input_1;
    packet->input_2 = input_2;
    packet->arm_delay_remaining_s = arm_delay_remaining_s;
    packet->esad_id = esad_id;
    packet->arming_status = arming_status;
    packet->munition_status = munition_status;
    packet->ignition_status = ignition_status;
    packet->munition_type = munition_type;
    packet->store_id = store_id;
    packet->pin_state = pin_state;
    packet->arm_delay_setting = arm_delay_setting;
    packet->trigger_distance_mode = trigger_distance_mode;
    mav_array_memcpy(packet->sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, (const char *)packet, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE ESAD_STATE UNPACKING


/**
 * @brief Get field time_usec from esad_state message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_esad_state_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field esad_id from esad_state message
 *
 * @return  Vehicle-local ESAD instance identifier. Must be 1-254. 0 is invalid for ESAD_STATE, 255 is reserved. Systems that support broadcast arming set the same arming_challenge_hash on each target ESAD before accepting ESAD_ARMING.esad_id = 0.
 */
static inline uint8_t mavlink_msg_esad_state_get_esad_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  26);
}

/**
 * @brief Get field arming_challenge_hash from esad_state message
 *
 * @return  Challenge hash for arming authentication of this ESAD instance.
 */
static inline uint32_t mavlink_msg_esad_state_get_arming_challenge_hash(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field fault_flags from esad_state message
 *
 * @return  Active fault flag bitmask.
 */
static inline uint32_t mavlink_msg_esad_state_get_fault_flags(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field input_1 from esad_state message
 *
 * @return  Analog/digital input 1 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 */
static inline float mavlink_msg_esad_state_get_input_1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field input_2 from esad_state message
 *
 * @return  Analog/digital input 2 (implementation-defined). For the standard safety inputs use the typed fields below instead.
 */
static inline float mavlink_msg_esad_state_get_input_2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field sw_version_hash from esad_state message
 *
 * @return  Software version as 8-byte short Git hash.
 */
static inline uint16_t mavlink_msg_esad_state_get_sw_version_hash(const mavlink_message_t* msg, uint8_t *sw_version_hash)
{
    return _MAV_RETURN_uint8_t_array(msg, sw_version_hash, 8,  27);
}

/**
 * @brief Get field arming_status from esad_state message
 *
 * @return  Current arming state.
 */
static inline uint8_t mavlink_msg_esad_state_get_arming_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  35);
}

/**
 * @brief Get field munition_status from esad_state message
 *
 * @return  Current munition state.
 */
static inline uint8_t mavlink_msg_esad_state_get_munition_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  36);
}

/**
 * @brief Get field ignition_status from esad_state message
 *
 * @return  Current ignition circuit state.
 */
static inline uint8_t mavlink_msg_esad_state_get_ignition_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  37);
}

/**
 * @brief Get field munition_type from esad_state message
 *
 * @return  Munition/store type identifier (implementation-defined).
 */
static inline uint8_t mavlink_msg_esad_state_get_munition_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  38);
}

/**
 * @brief Get field store_id from esad_state message
 *
 * @return  Store instance identifier. Fixed physical bay assignment: a bay keeps its store_id permanently, and when a store is expended the bay may be reloaded under the same store_id. IDs never renumber. 0 = not applicable / single store. This is the canonical definition of store_id across the dialect.
 */
static inline uint8_t mavlink_msg_esad_state_get_store_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  39);
}

/**
 * @brief Get field pin_state from esad_state message
 *
 * @return  Physical safety pull-pin state (read-only status).
 */
static inline uint8_t mavlink_msg_esad_state_get_pin_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  40);
}

/**
 * @brief Get field arm_delay_setting from esad_state message
 *
 * @return  Selected arming-delay switch position (90/60/30 s). The chosen setting.
 */
static inline uint8_t mavlink_msg_esad_state_get_arm_delay_setting(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  41);
}

/**
 * @brief Get field arm_delay_remaining_s from esad_state message
 *
 * @return [s] Live arming-delay countdown: seconds remaining after the in-flight-event signal until arming is permitted. -1 = not counting / not applicable. Distinct from arm_delay_setting (the switch position).
 */
static inline int16_t mavlink_msg_esad_state_get_arm_delay_remaining_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  24);
}

/**
 * @brief Get field trigger_distance_mode from esad_state message
 *
 * @return  Trigger-distance standoff mode currently in effect (coarse selection, not a distance value).
 */
static inline uint8_t mavlink_msg_esad_state_get_trigger_distance_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  42);
}

/**
 * @brief Get field track_uid from esad_state message
 *
 * @return  Track UID (UUID) of the engagement this store is armed for, when applicable. Ties the armed state to a specific authorized track so a monitoring station sees "armed against track X," not merely "an ESAD is hot." All-zero if not associated with a track.
 */
static inline uint16_t mavlink_msg_esad_state_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  43);
}

/**
 * @brief Decode a esad_state message into a struct
 *
 * @param msg The message to decode
 * @param esad_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_esad_state_decode(const mavlink_message_t* msg, mavlink_esad_state_t* esad_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    esad_state->time_usec = mavlink_msg_esad_state_get_time_usec(msg);
    esad_state->arming_challenge_hash = mavlink_msg_esad_state_get_arming_challenge_hash(msg);
    esad_state->fault_flags = mavlink_msg_esad_state_get_fault_flags(msg);
    esad_state->input_1 = mavlink_msg_esad_state_get_input_1(msg);
    esad_state->input_2 = mavlink_msg_esad_state_get_input_2(msg);
    esad_state->arm_delay_remaining_s = mavlink_msg_esad_state_get_arm_delay_remaining_s(msg);
    esad_state->esad_id = mavlink_msg_esad_state_get_esad_id(msg);
    mavlink_msg_esad_state_get_sw_version_hash(msg, esad_state->sw_version_hash);
    esad_state->arming_status = mavlink_msg_esad_state_get_arming_status(msg);
    esad_state->munition_status = mavlink_msg_esad_state_get_munition_status(msg);
    esad_state->ignition_status = mavlink_msg_esad_state_get_ignition_status(msg);
    esad_state->munition_type = mavlink_msg_esad_state_get_munition_type(msg);
    esad_state->store_id = mavlink_msg_esad_state_get_store_id(msg);
    esad_state->pin_state = mavlink_msg_esad_state_get_pin_state(msg);
    esad_state->arm_delay_setting = mavlink_msg_esad_state_get_arm_delay_setting(msg);
    esad_state->trigger_distance_mode = mavlink_msg_esad_state_get_trigger_distance_mode(msg);
    mavlink_msg_esad_state_get_track_uid(msg, esad_state->track_uid);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ESAD_STATE_LEN? msg->len : MAVLINK_MSG_ID_ESAD_STATE_LEN;
        memset(esad_state, 0, MAVLINK_MSG_ID_ESAD_STATE_LEN);
    memcpy(esad_state, _MAV_PAYLOAD(msg), len);
#endif
}
