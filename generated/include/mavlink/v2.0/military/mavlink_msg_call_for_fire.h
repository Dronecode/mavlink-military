#pragma once
// MESSAGE CALL_FOR_FIRE PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_CALL_FOR_FIRE 53024


typedef struct __mavlink_call_for_fire_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint16_t sequence; /*<  Fire-mission sequence number this CFF applies to.*/
 uint16_t rounds; /*<  Number of rounds for fire for effect. 0 = unspecified.*/
 uint16_t duration_s; /*< [s] Duration of fire. 0 = unspecified.*/
 uint16_t sheaf_length_m; /*< [m] Linear-target sheaf length (special sheaf). 0 if N/A.*/
 uint16_t sheaf_width_m; /*< [m] Linear-target sheaf width (special sheaf). 0 if N/A.*/
 uint16_t sheaf_attitude_cdeg; /*< [cdeg] Linear-target sheaf attitude (special sheaf), centidegrees [0..35999]. 0xFFFF = N/A (0 is a valid attitude, due north).*/
 uint16_t ot_direction_cdeg; /*< [cdeg] Virtual observer-target direction (bearing observer/drone to target), centidegrees [0..35999]. Lets the gateway orient VMF K02.22 relative corrections (Add/Drop, L/R) from an absolute-coordinate edge feed. 0xFFFF = not provided (0 is a valid bearing, due north).*/
 uint16_t ot_factor_dm; /*< [dm] Observer-target factor: OT range / 1000, in decimeters of shift per mil. Supports relative-correction math at the gateway. 0xFFFF = not provided.*/
 uint8_t mission_type; /*<  Warning-order mission type.*/
 uint8_t location_method; /*<  Method of target location.*/
 uint8_t adjustment_type; /*<  Area vs precision.*/
 uint8_t trajectory; /*<  Low/high angle.*/
 uint8_t sheaf; /*<  Distribution / sheaf.*/
 uint8_t control_method; /*<  Method of fire and control.*/
 uint8_t danger_close; /*<  1 = danger close (target within doctrinal threshold of friendlies); 0 = not. Flag only, no RED table.*/
 uint8_t tle_category; /*<  Target-location-error category label.*/
 uint8_t mensurated; /*<  1 = coordinate mensurated from precision imagery; 0 = map spot.*/
 uint8_t effect_verb; /*<  Mission-effect task verb (suppress/neutralize/destroy/...), descriptive tasking intent. Distinct from mission_type and from the fuze-effect intent carried on FIRES.requested_effect.*/
 uint8_t track_uid[16]; /*<  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.*/
} mavlink_call_for_fire_t;

#define MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN 50
#define MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN 50
#define MAVLINK_MSG_ID_53024_LEN 50
#define MAVLINK_MSG_ID_53024_MIN_LEN 50

#define MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC 236
#define MAVLINK_MSG_ID_53024_CRC 236

#define MAVLINK_MSG_CALL_FOR_FIRE_FIELD_TRACK_UID_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CALL_FOR_FIRE { \
    53024, \
    "CALL_FOR_FIRE", \
    20, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_call_for_fire_t, time_usec) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_call_for_fire_t, sequence) }, \
         { "mission_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_call_for_fire_t, mission_type) }, \
         { "location_method", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_call_for_fire_t, location_method) }, \
         { "adjustment_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_call_for_fire_t, adjustment_type) }, \
         { "trajectory", NULL, MAVLINK_TYPE_UINT8_T, 0, 27, offsetof(mavlink_call_for_fire_t, trajectory) }, \
         { "sheaf", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_call_for_fire_t, sheaf) }, \
         { "control_method", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_call_for_fire_t, control_method) }, \
         { "danger_close", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_call_for_fire_t, danger_close) }, \
         { "rounds", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_call_for_fire_t, rounds) }, \
         { "duration_s", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_call_for_fire_t, duration_s) }, \
         { "tle_category", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_call_for_fire_t, tle_category) }, \
         { "mensurated", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_call_for_fire_t, mensurated) }, \
         { "sheaf_length_m", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_call_for_fire_t, sheaf_length_m) }, \
         { "sheaf_width_m", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_call_for_fire_t, sheaf_width_m) }, \
         { "sheaf_attitude_cdeg", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_call_for_fire_t, sheaf_attitude_cdeg) }, \
         { "ot_direction_cdeg", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_call_for_fire_t, ot_direction_cdeg) }, \
         { "ot_factor_dm", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_call_for_fire_t, ot_factor_dm) }, \
         { "effect_verb", NULL, MAVLINK_TYPE_UINT8_T, 0, 33, offsetof(mavlink_call_for_fire_t, effect_verb) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 34, offsetof(mavlink_call_for_fire_t, track_uid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CALL_FOR_FIRE { \
    "CALL_FOR_FIRE", \
    20, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_call_for_fire_t, time_usec) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_call_for_fire_t, sequence) }, \
         { "mission_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_call_for_fire_t, mission_type) }, \
         { "location_method", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_call_for_fire_t, location_method) }, \
         { "adjustment_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_call_for_fire_t, adjustment_type) }, \
         { "trajectory", NULL, MAVLINK_TYPE_UINT8_T, 0, 27, offsetof(mavlink_call_for_fire_t, trajectory) }, \
         { "sheaf", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_call_for_fire_t, sheaf) }, \
         { "control_method", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_call_for_fire_t, control_method) }, \
         { "danger_close", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_call_for_fire_t, danger_close) }, \
         { "rounds", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_call_for_fire_t, rounds) }, \
         { "duration_s", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_call_for_fire_t, duration_s) }, \
         { "tle_category", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_call_for_fire_t, tle_category) }, \
         { "mensurated", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_call_for_fire_t, mensurated) }, \
         { "sheaf_length_m", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_call_for_fire_t, sheaf_length_m) }, \
         { "sheaf_width_m", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_call_for_fire_t, sheaf_width_m) }, \
         { "sheaf_attitude_cdeg", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_call_for_fire_t, sheaf_attitude_cdeg) }, \
         { "ot_direction_cdeg", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_call_for_fire_t, ot_direction_cdeg) }, \
         { "ot_factor_dm", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_call_for_fire_t, ot_factor_dm) }, \
         { "effect_verb", NULL, MAVLINK_TYPE_UINT8_T, 0, 33, offsetof(mavlink_call_for_fire_t, effect_verb) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 34, offsetof(mavlink_call_for_fire_t, track_uid) }, \
         } \
}
#endif

/**
 * @brief Pack a call_for_fire message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sequence  Fire-mission sequence number this CFF applies to.
 * @param mission_type  Warning-order mission type.
 * @param location_method  Method of target location.
 * @param adjustment_type  Area vs precision.
 * @param trajectory  Low/high angle.
 * @param sheaf  Distribution / sheaf.
 * @param control_method  Method of fire and control.
 * @param danger_close  1 = danger close (target within doctrinal threshold of friendlies); 0 = not. Flag only, no RED table.
 * @param rounds  Number of rounds for fire for effect. 0 = unspecified.
 * @param duration_s [s] Duration of fire. 0 = unspecified.
 * @param tle_category  Target-location-error category label.
 * @param mensurated  1 = coordinate mensurated from precision imagery; 0 = map spot.
 * @param sheaf_length_m [m] Linear-target sheaf length (special sheaf). 0 if N/A.
 * @param sheaf_width_m [m] Linear-target sheaf width (special sheaf). 0 if N/A.
 * @param sheaf_attitude_cdeg [cdeg] Linear-target sheaf attitude (special sheaf), centidegrees [0..35999]. 0xFFFF = N/A (0 is a valid attitude, due north).
 * @param ot_direction_cdeg [cdeg] Virtual observer-target direction (bearing observer/drone to target), centidegrees [0..35999]. Lets the gateway orient VMF K02.22 relative corrections (Add/Drop, L/R) from an absolute-coordinate edge feed. 0xFFFF = not provided (0 is a valid bearing, due north).
 * @param ot_factor_dm [dm] Observer-target factor: OT range / 1000, in decimeters of shift per mil. Supports relative-correction math at the gateway. 0xFFFF = not provided.
 * @param effect_verb  Mission-effect task verb (suppress/neutralize/destroy/...), descriptive tasking intent. Distinct from mission_type and from the fuze-effect intent carried on FIRES.requested_effect.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_call_for_fire_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint16_t sequence, uint8_t mission_type, uint8_t location_method, uint8_t adjustment_type, uint8_t trajectory, uint8_t sheaf, uint8_t control_method, uint8_t danger_close, uint16_t rounds, uint16_t duration_s, uint8_t tle_category, uint8_t mensurated, uint16_t sheaf_length_m, uint16_t sheaf_width_m, uint16_t sheaf_attitude_cdeg, uint16_t ot_direction_cdeg, uint16_t ot_factor_dm, uint8_t effect_verb, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint16_t(buf, 10, rounds);
    _mav_put_uint16_t(buf, 12, duration_s);
    _mav_put_uint16_t(buf, 14, sheaf_length_m);
    _mav_put_uint16_t(buf, 16, sheaf_width_m);
    _mav_put_uint16_t(buf, 18, sheaf_attitude_cdeg);
    _mav_put_uint16_t(buf, 20, ot_direction_cdeg);
    _mav_put_uint16_t(buf, 22, ot_factor_dm);
    _mav_put_uint8_t(buf, 24, mission_type);
    _mav_put_uint8_t(buf, 25, location_method);
    _mav_put_uint8_t(buf, 26, adjustment_type);
    _mav_put_uint8_t(buf, 27, trajectory);
    _mav_put_uint8_t(buf, 28, sheaf);
    _mav_put_uint8_t(buf, 29, control_method);
    _mav_put_uint8_t(buf, 30, danger_close);
    _mav_put_uint8_t(buf, 31, tle_category);
    _mav_put_uint8_t(buf, 32, mensurated);
    _mav_put_uint8_t(buf, 33, effect_verb);
    _mav_put_uint8_t_array(buf, 34, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN);
#else
    mavlink_call_for_fire_t packet;
    packet.time_usec = time_usec;
    packet.sequence = sequence;
    packet.rounds = rounds;
    packet.duration_s = duration_s;
    packet.sheaf_length_m = sheaf_length_m;
    packet.sheaf_width_m = sheaf_width_m;
    packet.sheaf_attitude_cdeg = sheaf_attitude_cdeg;
    packet.ot_direction_cdeg = ot_direction_cdeg;
    packet.ot_factor_dm = ot_factor_dm;
    packet.mission_type = mission_type;
    packet.location_method = location_method;
    packet.adjustment_type = adjustment_type;
    packet.trajectory = trajectory;
    packet.sheaf = sheaf;
    packet.control_method = control_method;
    packet.danger_close = danger_close;
    packet.tle_category = tle_category;
    packet.mensurated = mensurated;
    packet.effect_verb = effect_verb;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CALL_FOR_FIRE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC);
}

/**
 * @brief Pack a call_for_fire message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sequence  Fire-mission sequence number this CFF applies to.
 * @param mission_type  Warning-order mission type.
 * @param location_method  Method of target location.
 * @param adjustment_type  Area vs precision.
 * @param trajectory  Low/high angle.
 * @param sheaf  Distribution / sheaf.
 * @param control_method  Method of fire and control.
 * @param danger_close  1 = danger close (target within doctrinal threshold of friendlies); 0 = not. Flag only, no RED table.
 * @param rounds  Number of rounds for fire for effect. 0 = unspecified.
 * @param duration_s [s] Duration of fire. 0 = unspecified.
 * @param tle_category  Target-location-error category label.
 * @param mensurated  1 = coordinate mensurated from precision imagery; 0 = map spot.
 * @param sheaf_length_m [m] Linear-target sheaf length (special sheaf). 0 if N/A.
 * @param sheaf_width_m [m] Linear-target sheaf width (special sheaf). 0 if N/A.
 * @param sheaf_attitude_cdeg [cdeg] Linear-target sheaf attitude (special sheaf), centidegrees [0..35999]. 0xFFFF = N/A (0 is a valid attitude, due north).
 * @param ot_direction_cdeg [cdeg] Virtual observer-target direction (bearing observer/drone to target), centidegrees [0..35999]. Lets the gateway orient VMF K02.22 relative corrections (Add/Drop, L/R) from an absolute-coordinate edge feed. 0xFFFF = not provided (0 is a valid bearing, due north).
 * @param ot_factor_dm [dm] Observer-target factor: OT range / 1000, in decimeters of shift per mil. Supports relative-correction math at the gateway. 0xFFFF = not provided.
 * @param effect_verb  Mission-effect task verb (suppress/neutralize/destroy/...), descriptive tasking intent. Distinct from mission_type and from the fuze-effect intent carried on FIRES.requested_effect.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_call_for_fire_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint16_t sequence, uint8_t mission_type, uint8_t location_method, uint8_t adjustment_type, uint8_t trajectory, uint8_t sheaf, uint8_t control_method, uint8_t danger_close, uint16_t rounds, uint16_t duration_s, uint8_t tle_category, uint8_t mensurated, uint16_t sheaf_length_m, uint16_t sheaf_width_m, uint16_t sheaf_attitude_cdeg, uint16_t ot_direction_cdeg, uint16_t ot_factor_dm, uint8_t effect_verb, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint16_t(buf, 10, rounds);
    _mav_put_uint16_t(buf, 12, duration_s);
    _mav_put_uint16_t(buf, 14, sheaf_length_m);
    _mav_put_uint16_t(buf, 16, sheaf_width_m);
    _mav_put_uint16_t(buf, 18, sheaf_attitude_cdeg);
    _mav_put_uint16_t(buf, 20, ot_direction_cdeg);
    _mav_put_uint16_t(buf, 22, ot_factor_dm);
    _mav_put_uint8_t(buf, 24, mission_type);
    _mav_put_uint8_t(buf, 25, location_method);
    _mav_put_uint8_t(buf, 26, adjustment_type);
    _mav_put_uint8_t(buf, 27, trajectory);
    _mav_put_uint8_t(buf, 28, sheaf);
    _mav_put_uint8_t(buf, 29, control_method);
    _mav_put_uint8_t(buf, 30, danger_close);
    _mav_put_uint8_t(buf, 31, tle_category);
    _mav_put_uint8_t(buf, 32, mensurated);
    _mav_put_uint8_t(buf, 33, effect_verb);
    _mav_put_uint8_t_array(buf, 34, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN);
#else
    mavlink_call_for_fire_t packet;
    packet.time_usec = time_usec;
    packet.sequence = sequence;
    packet.rounds = rounds;
    packet.duration_s = duration_s;
    packet.sheaf_length_m = sheaf_length_m;
    packet.sheaf_width_m = sheaf_width_m;
    packet.sheaf_attitude_cdeg = sheaf_attitude_cdeg;
    packet.ot_direction_cdeg = ot_direction_cdeg;
    packet.ot_factor_dm = ot_factor_dm;
    packet.mission_type = mission_type;
    packet.location_method = location_method;
    packet.adjustment_type = adjustment_type;
    packet.trajectory = trajectory;
    packet.sheaf = sheaf;
    packet.control_method = control_method;
    packet.danger_close = danger_close;
    packet.tle_category = tle_category;
    packet.mensurated = mensurated;
    packet.effect_verb = effect_verb;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CALL_FOR_FIRE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN);
#endif
}

/**
 * @brief Pack a call_for_fire message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sequence  Fire-mission sequence number this CFF applies to.
 * @param mission_type  Warning-order mission type.
 * @param location_method  Method of target location.
 * @param adjustment_type  Area vs precision.
 * @param trajectory  Low/high angle.
 * @param sheaf  Distribution / sheaf.
 * @param control_method  Method of fire and control.
 * @param danger_close  1 = danger close (target within doctrinal threshold of friendlies); 0 = not. Flag only, no RED table.
 * @param rounds  Number of rounds for fire for effect. 0 = unspecified.
 * @param duration_s [s] Duration of fire. 0 = unspecified.
 * @param tle_category  Target-location-error category label.
 * @param mensurated  1 = coordinate mensurated from precision imagery; 0 = map spot.
 * @param sheaf_length_m [m] Linear-target sheaf length (special sheaf). 0 if N/A.
 * @param sheaf_width_m [m] Linear-target sheaf width (special sheaf). 0 if N/A.
 * @param sheaf_attitude_cdeg [cdeg] Linear-target sheaf attitude (special sheaf), centidegrees [0..35999]. 0xFFFF = N/A (0 is a valid attitude, due north).
 * @param ot_direction_cdeg [cdeg] Virtual observer-target direction (bearing observer/drone to target), centidegrees [0..35999]. Lets the gateway orient VMF K02.22 relative corrections (Add/Drop, L/R) from an absolute-coordinate edge feed. 0xFFFF = not provided (0 is a valid bearing, due north).
 * @param ot_factor_dm [dm] Observer-target factor: OT range / 1000, in decimeters of shift per mil. Supports relative-correction math at the gateway. 0xFFFF = not provided.
 * @param effect_verb  Mission-effect task verb (suppress/neutralize/destroy/...), descriptive tasking intent. Distinct from mission_type and from the fuze-effect intent carried on FIRES.requested_effect.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_call_for_fire_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint16_t sequence,uint8_t mission_type,uint8_t location_method,uint8_t adjustment_type,uint8_t trajectory,uint8_t sheaf,uint8_t control_method,uint8_t danger_close,uint16_t rounds,uint16_t duration_s,uint8_t tle_category,uint8_t mensurated,uint16_t sheaf_length_m,uint16_t sheaf_width_m,uint16_t sheaf_attitude_cdeg,uint16_t ot_direction_cdeg,uint16_t ot_factor_dm,uint8_t effect_verb,const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint16_t(buf, 10, rounds);
    _mav_put_uint16_t(buf, 12, duration_s);
    _mav_put_uint16_t(buf, 14, sheaf_length_m);
    _mav_put_uint16_t(buf, 16, sheaf_width_m);
    _mav_put_uint16_t(buf, 18, sheaf_attitude_cdeg);
    _mav_put_uint16_t(buf, 20, ot_direction_cdeg);
    _mav_put_uint16_t(buf, 22, ot_factor_dm);
    _mav_put_uint8_t(buf, 24, mission_type);
    _mav_put_uint8_t(buf, 25, location_method);
    _mav_put_uint8_t(buf, 26, adjustment_type);
    _mav_put_uint8_t(buf, 27, trajectory);
    _mav_put_uint8_t(buf, 28, sheaf);
    _mav_put_uint8_t(buf, 29, control_method);
    _mav_put_uint8_t(buf, 30, danger_close);
    _mav_put_uint8_t(buf, 31, tle_category);
    _mav_put_uint8_t(buf, 32, mensurated);
    _mav_put_uint8_t(buf, 33, effect_verb);
    _mav_put_uint8_t_array(buf, 34, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN);
#else
    mavlink_call_for_fire_t packet;
    packet.time_usec = time_usec;
    packet.sequence = sequence;
    packet.rounds = rounds;
    packet.duration_s = duration_s;
    packet.sheaf_length_m = sheaf_length_m;
    packet.sheaf_width_m = sheaf_width_m;
    packet.sheaf_attitude_cdeg = sheaf_attitude_cdeg;
    packet.ot_direction_cdeg = ot_direction_cdeg;
    packet.ot_factor_dm = ot_factor_dm;
    packet.mission_type = mission_type;
    packet.location_method = location_method;
    packet.adjustment_type = adjustment_type;
    packet.trajectory = trajectory;
    packet.sheaf = sheaf;
    packet.control_method = control_method;
    packet.danger_close = danger_close;
    packet.tle_category = tle_category;
    packet.mensurated = mensurated;
    packet.effect_verb = effect_verb;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CALL_FOR_FIRE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC);
}

/**
 * @brief Encode a call_for_fire struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param call_for_fire C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_call_for_fire_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_call_for_fire_t* call_for_fire)
{
    return mavlink_msg_call_for_fire_pack(system_id, component_id, msg, call_for_fire->time_usec, call_for_fire->sequence, call_for_fire->mission_type, call_for_fire->location_method, call_for_fire->adjustment_type, call_for_fire->trajectory, call_for_fire->sheaf, call_for_fire->control_method, call_for_fire->danger_close, call_for_fire->rounds, call_for_fire->duration_s, call_for_fire->tle_category, call_for_fire->mensurated, call_for_fire->sheaf_length_m, call_for_fire->sheaf_width_m, call_for_fire->sheaf_attitude_cdeg, call_for_fire->ot_direction_cdeg, call_for_fire->ot_factor_dm, call_for_fire->effect_verb, call_for_fire->track_uid);
}

/**
 * @brief Encode a call_for_fire struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param call_for_fire C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_call_for_fire_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_call_for_fire_t* call_for_fire)
{
    return mavlink_msg_call_for_fire_pack_chan(system_id, component_id, chan, msg, call_for_fire->time_usec, call_for_fire->sequence, call_for_fire->mission_type, call_for_fire->location_method, call_for_fire->adjustment_type, call_for_fire->trajectory, call_for_fire->sheaf, call_for_fire->control_method, call_for_fire->danger_close, call_for_fire->rounds, call_for_fire->duration_s, call_for_fire->tle_category, call_for_fire->mensurated, call_for_fire->sheaf_length_m, call_for_fire->sheaf_width_m, call_for_fire->sheaf_attitude_cdeg, call_for_fire->ot_direction_cdeg, call_for_fire->ot_factor_dm, call_for_fire->effect_verb, call_for_fire->track_uid);
}

/**
 * @brief Encode a call_for_fire struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param call_for_fire C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_call_for_fire_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_call_for_fire_t* call_for_fire)
{
    return mavlink_msg_call_for_fire_pack_status(system_id, component_id, _status, msg,  call_for_fire->time_usec, call_for_fire->sequence, call_for_fire->mission_type, call_for_fire->location_method, call_for_fire->adjustment_type, call_for_fire->trajectory, call_for_fire->sheaf, call_for_fire->control_method, call_for_fire->danger_close, call_for_fire->rounds, call_for_fire->duration_s, call_for_fire->tle_category, call_for_fire->mensurated, call_for_fire->sheaf_length_m, call_for_fire->sheaf_width_m, call_for_fire->sheaf_attitude_cdeg, call_for_fire->ot_direction_cdeg, call_for_fire->ot_factor_dm, call_for_fire->effect_verb, call_for_fire->track_uid);
}

/**
 * @brief Send a call_for_fire message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sequence  Fire-mission sequence number this CFF applies to.
 * @param mission_type  Warning-order mission type.
 * @param location_method  Method of target location.
 * @param adjustment_type  Area vs precision.
 * @param trajectory  Low/high angle.
 * @param sheaf  Distribution / sheaf.
 * @param control_method  Method of fire and control.
 * @param danger_close  1 = danger close (target within doctrinal threshold of friendlies); 0 = not. Flag only, no RED table.
 * @param rounds  Number of rounds for fire for effect. 0 = unspecified.
 * @param duration_s [s] Duration of fire. 0 = unspecified.
 * @param tle_category  Target-location-error category label.
 * @param mensurated  1 = coordinate mensurated from precision imagery; 0 = map spot.
 * @param sheaf_length_m [m] Linear-target sheaf length (special sheaf). 0 if N/A.
 * @param sheaf_width_m [m] Linear-target sheaf width (special sheaf). 0 if N/A.
 * @param sheaf_attitude_cdeg [cdeg] Linear-target sheaf attitude (special sheaf), centidegrees [0..35999]. 0xFFFF = N/A (0 is a valid attitude, due north).
 * @param ot_direction_cdeg [cdeg] Virtual observer-target direction (bearing observer/drone to target), centidegrees [0..35999]. Lets the gateway orient VMF K02.22 relative corrections (Add/Drop, L/R) from an absolute-coordinate edge feed. 0xFFFF = not provided (0 is a valid bearing, due north).
 * @param ot_factor_dm [dm] Observer-target factor: OT range / 1000, in decimeters of shift per mil. Supports relative-correction math at the gateway. 0xFFFF = not provided.
 * @param effect_verb  Mission-effect task verb (suppress/neutralize/destroy/...), descriptive tasking intent. Distinct from mission_type and from the fuze-effect intent carried on FIRES.requested_effect.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_call_for_fire_send(mavlink_channel_t chan, uint64_t time_usec, uint16_t sequence, uint8_t mission_type, uint8_t location_method, uint8_t adjustment_type, uint8_t trajectory, uint8_t sheaf, uint8_t control_method, uint8_t danger_close, uint16_t rounds, uint16_t duration_s, uint8_t tle_category, uint8_t mensurated, uint16_t sheaf_length_m, uint16_t sheaf_width_m, uint16_t sheaf_attitude_cdeg, uint16_t ot_direction_cdeg, uint16_t ot_factor_dm, uint8_t effect_verb, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint16_t(buf, 10, rounds);
    _mav_put_uint16_t(buf, 12, duration_s);
    _mav_put_uint16_t(buf, 14, sheaf_length_m);
    _mav_put_uint16_t(buf, 16, sheaf_width_m);
    _mav_put_uint16_t(buf, 18, sheaf_attitude_cdeg);
    _mav_put_uint16_t(buf, 20, ot_direction_cdeg);
    _mav_put_uint16_t(buf, 22, ot_factor_dm);
    _mav_put_uint8_t(buf, 24, mission_type);
    _mav_put_uint8_t(buf, 25, location_method);
    _mav_put_uint8_t(buf, 26, adjustment_type);
    _mav_put_uint8_t(buf, 27, trajectory);
    _mav_put_uint8_t(buf, 28, sheaf);
    _mav_put_uint8_t(buf, 29, control_method);
    _mav_put_uint8_t(buf, 30, danger_close);
    _mav_put_uint8_t(buf, 31, tle_category);
    _mav_put_uint8_t(buf, 32, mensurated);
    _mav_put_uint8_t(buf, 33, effect_verb);
    _mav_put_uint8_t_array(buf, 34, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CALL_FOR_FIRE, buf, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC);
#else
    mavlink_call_for_fire_t packet;
    packet.time_usec = time_usec;
    packet.sequence = sequence;
    packet.rounds = rounds;
    packet.duration_s = duration_s;
    packet.sheaf_length_m = sheaf_length_m;
    packet.sheaf_width_m = sheaf_width_m;
    packet.sheaf_attitude_cdeg = sheaf_attitude_cdeg;
    packet.ot_direction_cdeg = ot_direction_cdeg;
    packet.ot_factor_dm = ot_factor_dm;
    packet.mission_type = mission_type;
    packet.location_method = location_method;
    packet.adjustment_type = adjustment_type;
    packet.trajectory = trajectory;
    packet.sheaf = sheaf;
    packet.control_method = control_method;
    packet.danger_close = danger_close;
    packet.tle_category = tle_category;
    packet.mensurated = mensurated;
    packet.effect_verb = effect_verb;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CALL_FOR_FIRE, (const char *)&packet, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC);
#endif
}

/**
 * @brief Send a call_for_fire message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_call_for_fire_send_struct(mavlink_channel_t chan, const mavlink_call_for_fire_t* call_for_fire)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_call_for_fire_send(chan, call_for_fire->time_usec, call_for_fire->sequence, call_for_fire->mission_type, call_for_fire->location_method, call_for_fire->adjustment_type, call_for_fire->trajectory, call_for_fire->sheaf, call_for_fire->control_method, call_for_fire->danger_close, call_for_fire->rounds, call_for_fire->duration_s, call_for_fire->tle_category, call_for_fire->mensurated, call_for_fire->sheaf_length_m, call_for_fire->sheaf_width_m, call_for_fire->sheaf_attitude_cdeg, call_for_fire->ot_direction_cdeg, call_for_fire->ot_factor_dm, call_for_fire->effect_verb, call_for_fire->track_uid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CALL_FOR_FIRE, (const char *)call_for_fire, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC);
#endif
}

#if MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_call_for_fire_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint16_t sequence, uint8_t mission_type, uint8_t location_method, uint8_t adjustment_type, uint8_t trajectory, uint8_t sheaf, uint8_t control_method, uint8_t danger_close, uint16_t rounds, uint16_t duration_s, uint8_t tle_category, uint8_t mensurated, uint16_t sheaf_length_m, uint16_t sheaf_width_m, uint16_t sheaf_attitude_cdeg, uint16_t ot_direction_cdeg, uint16_t ot_factor_dm, uint8_t effect_verb, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint16_t(buf, 10, rounds);
    _mav_put_uint16_t(buf, 12, duration_s);
    _mav_put_uint16_t(buf, 14, sheaf_length_m);
    _mav_put_uint16_t(buf, 16, sheaf_width_m);
    _mav_put_uint16_t(buf, 18, sheaf_attitude_cdeg);
    _mav_put_uint16_t(buf, 20, ot_direction_cdeg);
    _mav_put_uint16_t(buf, 22, ot_factor_dm);
    _mav_put_uint8_t(buf, 24, mission_type);
    _mav_put_uint8_t(buf, 25, location_method);
    _mav_put_uint8_t(buf, 26, adjustment_type);
    _mav_put_uint8_t(buf, 27, trajectory);
    _mav_put_uint8_t(buf, 28, sheaf);
    _mav_put_uint8_t(buf, 29, control_method);
    _mav_put_uint8_t(buf, 30, danger_close);
    _mav_put_uint8_t(buf, 31, tle_category);
    _mav_put_uint8_t(buf, 32, mensurated);
    _mav_put_uint8_t(buf, 33, effect_verb);
    _mav_put_uint8_t_array(buf, 34, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CALL_FOR_FIRE, buf, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC);
#else
    mavlink_call_for_fire_t *packet = (mavlink_call_for_fire_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->sequence = sequence;
    packet->rounds = rounds;
    packet->duration_s = duration_s;
    packet->sheaf_length_m = sheaf_length_m;
    packet->sheaf_width_m = sheaf_width_m;
    packet->sheaf_attitude_cdeg = sheaf_attitude_cdeg;
    packet->ot_direction_cdeg = ot_direction_cdeg;
    packet->ot_factor_dm = ot_factor_dm;
    packet->mission_type = mission_type;
    packet->location_method = location_method;
    packet->adjustment_type = adjustment_type;
    packet->trajectory = trajectory;
    packet->sheaf = sheaf;
    packet->control_method = control_method;
    packet->danger_close = danger_close;
    packet->tle_category = tle_category;
    packet->mensurated = mensurated;
    packet->effect_verb = effect_verb;
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CALL_FOR_FIRE, (const char *)packet, MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN, MAVLINK_MSG_ID_CALL_FOR_FIRE_CRC);
#endif
}
#endif

#endif

// MESSAGE CALL_FOR_FIRE UNPACKING


/**
 * @brief Get field time_usec from call_for_fire message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_call_for_fire_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field sequence from call_for_fire message
 *
 * @return  Fire-mission sequence number this CFF applies to.
 */
static inline uint16_t mavlink_msg_call_for_fire_get_sequence(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field mission_type from call_for_fire message
 *
 * @return  Warning-order mission type.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_mission_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field location_method from call_for_fire message
 *
 * @return  Method of target location.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_location_method(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  25);
}

/**
 * @brief Get field adjustment_type from call_for_fire message
 *
 * @return  Area vs precision.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_adjustment_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  26);
}

/**
 * @brief Get field trajectory from call_for_fire message
 *
 * @return  Low/high angle.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_trajectory(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  27);
}

/**
 * @brief Get field sheaf from call_for_fire message
 *
 * @return  Distribution / sheaf.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_sheaf(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  28);
}

/**
 * @brief Get field control_method from call_for_fire message
 *
 * @return  Method of fire and control.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_control_method(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  29);
}

/**
 * @brief Get field danger_close from call_for_fire message
 *
 * @return  1 = danger close (target within doctrinal threshold of friendlies); 0 = not. Flag only, no RED table.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_danger_close(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  30);
}

/**
 * @brief Get field rounds from call_for_fire message
 *
 * @return  Number of rounds for fire for effect. 0 = unspecified.
 */
static inline uint16_t mavlink_msg_call_for_fire_get_rounds(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Get field duration_s from call_for_fire message
 *
 * @return [s] Duration of fire. 0 = unspecified.
 */
static inline uint16_t mavlink_msg_call_for_fire_get_duration_s(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field tle_category from call_for_fire message
 *
 * @return  Target-location-error category label.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_tle_category(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  31);
}

/**
 * @brief Get field mensurated from call_for_fire message
 *
 * @return  1 = coordinate mensurated from precision imagery; 0 = map spot.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_mensurated(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  32);
}

/**
 * @brief Get field sheaf_length_m from call_for_fire message
 *
 * @return [m] Linear-target sheaf length (special sheaf). 0 if N/A.
 */
static inline uint16_t mavlink_msg_call_for_fire_get_sheaf_length_m(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Get field sheaf_width_m from call_for_fire message
 *
 * @return [m] Linear-target sheaf width (special sheaf). 0 if N/A.
 */
static inline uint16_t mavlink_msg_call_for_fire_get_sheaf_width_m(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field sheaf_attitude_cdeg from call_for_fire message
 *
 * @return [cdeg] Linear-target sheaf attitude (special sheaf), centidegrees [0..35999]. 0xFFFF = N/A (0 is a valid attitude, due north).
 */
static inline uint16_t mavlink_msg_call_for_fire_get_sheaf_attitude_cdeg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  18);
}

/**
 * @brief Get field ot_direction_cdeg from call_for_fire message
 *
 * @return [cdeg] Virtual observer-target direction (bearing observer/drone to target), centidegrees [0..35999]. Lets the gateway orient VMF K02.22 relative corrections (Add/Drop, L/R) from an absolute-coordinate edge feed. 0xFFFF = not provided (0 is a valid bearing, due north).
 */
static inline uint16_t mavlink_msg_call_for_fire_get_ot_direction_cdeg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field ot_factor_dm from call_for_fire message
 *
 * @return [dm] Observer-target factor: OT range / 1000, in decimeters of shift per mil. Supports relative-correction math at the gateway. 0xFFFF = not provided.
 */
static inline uint16_t mavlink_msg_call_for_fire_get_ot_factor_dm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  22);
}

/**
 * @brief Get field effect_verb from call_for_fire message
 *
 * @return  Mission-effect task verb (suppress/neutralize/destroy/...), descriptive tasking intent. Distinct from mission_type and from the fuze-effect intent carried on FIRES.requested_effect.
 */
static inline uint8_t mavlink_msg_call_for_fire_get_effect_verb(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  33);
}

/**
 * @brief Get field track_uid from call_for_fire message
 *
 * @return  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 */
static inline uint16_t mavlink_msg_call_for_fire_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  34);
}

/**
 * @brief Decode a call_for_fire message into a struct
 *
 * @param msg The message to decode
 * @param call_for_fire C-struct to decode the message contents into
 */
static inline void mavlink_msg_call_for_fire_decode(const mavlink_message_t* msg, mavlink_call_for_fire_t* call_for_fire)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    call_for_fire->time_usec = mavlink_msg_call_for_fire_get_time_usec(msg);
    call_for_fire->sequence = mavlink_msg_call_for_fire_get_sequence(msg);
    call_for_fire->rounds = mavlink_msg_call_for_fire_get_rounds(msg);
    call_for_fire->duration_s = mavlink_msg_call_for_fire_get_duration_s(msg);
    call_for_fire->sheaf_length_m = mavlink_msg_call_for_fire_get_sheaf_length_m(msg);
    call_for_fire->sheaf_width_m = mavlink_msg_call_for_fire_get_sheaf_width_m(msg);
    call_for_fire->sheaf_attitude_cdeg = mavlink_msg_call_for_fire_get_sheaf_attitude_cdeg(msg);
    call_for_fire->ot_direction_cdeg = mavlink_msg_call_for_fire_get_ot_direction_cdeg(msg);
    call_for_fire->ot_factor_dm = mavlink_msg_call_for_fire_get_ot_factor_dm(msg);
    call_for_fire->mission_type = mavlink_msg_call_for_fire_get_mission_type(msg);
    call_for_fire->location_method = mavlink_msg_call_for_fire_get_location_method(msg);
    call_for_fire->adjustment_type = mavlink_msg_call_for_fire_get_adjustment_type(msg);
    call_for_fire->trajectory = mavlink_msg_call_for_fire_get_trajectory(msg);
    call_for_fire->sheaf = mavlink_msg_call_for_fire_get_sheaf(msg);
    call_for_fire->control_method = mavlink_msg_call_for_fire_get_control_method(msg);
    call_for_fire->danger_close = mavlink_msg_call_for_fire_get_danger_close(msg);
    call_for_fire->tle_category = mavlink_msg_call_for_fire_get_tle_category(msg);
    call_for_fire->mensurated = mavlink_msg_call_for_fire_get_mensurated(msg);
    call_for_fire->effect_verb = mavlink_msg_call_for_fire_get_effect_verb(msg);
    mavlink_msg_call_for_fire_get_track_uid(msg, call_for_fire->track_uid);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN? msg->len : MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN;
        memset(call_for_fire, 0, MAVLINK_MSG_ID_CALL_FOR_FIRE_LEN);
    memcpy(call_for_fire, _MAV_PAYLOAD(msg), len);
#endif
}
