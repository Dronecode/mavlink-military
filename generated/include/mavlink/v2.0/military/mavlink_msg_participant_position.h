#pragma once
// MESSAGE PARTICIPANT_POSITION PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_PARTICIPANT_POSITION 53003


typedef struct __mavlink_participant_position_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 int32_t lat; /*< [degE7] Participant latitude, WGS84.*/
 int32_t lon; /*< [degE7] Participant longitude, WGS84.*/
 float alt; /*< [m] Participant altitude, MSL. NaN if unknown.*/
 float vx; /*< [m/s] Velocity north (NED). NaN if unknown.*/
 float vy; /*< [m/s] Velocity east (NED). NaN if unknown.*/
 float vz; /*< [m/s] Velocity down (NED). NaN if unknown.*/
 float course; /*< [deg] Course over ground. NaN if unknown.*/
 char external_track_number[20]; /*<  External/joint track number or URN for this participant. Empty if none.*/
 char callsign[50]; /*<  Human-readable callsign/designation (null-terminated).*/
 uint8_t origin_sysid; /*<  System ID of the reporting participant.*/
 uint8_t external_track_type; /*<  Namespace of external_track_number.*/
 uint8_t stanag_identity; /*<  Standard identity (normally FRIEND for own-force PPLI).*/
 uint8_t ppli_type; /*<  Participant environment/type.*/
} mavlink_participant_position_t;

#define MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN 110
#define MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN 110
#define MAVLINK_MSG_ID_53003_LEN 110
#define MAVLINK_MSG_ID_53003_MIN_LEN 110

#define MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC 126
#define MAVLINK_MSG_ID_53003_CRC 126

#define MAVLINK_MSG_PARTICIPANT_POSITION_FIELD_EXTERNAL_TRACK_NUMBER_LEN 20
#define MAVLINK_MSG_PARTICIPANT_POSITION_FIELD_CALLSIGN_LEN 50

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PARTICIPANT_POSITION { \
    53003, \
    "PARTICIPANT_POSITION", \
    14, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_participant_position_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_participant_position_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_participant_position_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_participant_position_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_participant_position_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_participant_position_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_participant_position_t, vz) }, \
         { "course", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_participant_position_t, course) }, \
         { "external_track_number", NULL, MAVLINK_TYPE_CHAR, 20, 36, offsetof(mavlink_participant_position_t, external_track_number) }, \
         { "callsign", NULL, MAVLINK_TYPE_CHAR, 50, 56, offsetof(mavlink_participant_position_t, callsign) }, \
         { "origin_sysid", NULL, MAVLINK_TYPE_UINT8_T, 0, 106, offsetof(mavlink_participant_position_t, origin_sysid) }, \
         { "external_track_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 107, offsetof(mavlink_participant_position_t, external_track_type) }, \
         { "stanag_identity", NULL, MAVLINK_TYPE_UINT8_T, 0, 108, offsetof(mavlink_participant_position_t, stanag_identity) }, \
         { "ppli_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 109, offsetof(mavlink_participant_position_t, ppli_type) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PARTICIPANT_POSITION { \
    "PARTICIPANT_POSITION", \
    14, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_participant_position_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_participant_position_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_participant_position_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_participant_position_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_participant_position_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_participant_position_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_participant_position_t, vz) }, \
         { "course", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_participant_position_t, course) }, \
         { "external_track_number", NULL, MAVLINK_TYPE_CHAR, 20, 36, offsetof(mavlink_participant_position_t, external_track_number) }, \
         { "callsign", NULL, MAVLINK_TYPE_CHAR, 50, 56, offsetof(mavlink_participant_position_t, callsign) }, \
         { "origin_sysid", NULL, MAVLINK_TYPE_UINT8_T, 0, 106, offsetof(mavlink_participant_position_t, origin_sysid) }, \
         { "external_track_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 107, offsetof(mavlink_participant_position_t, external_track_type) }, \
         { "stanag_identity", NULL, MAVLINK_TYPE_UINT8_T, 0, 108, offsetof(mavlink_participant_position_t, stanag_identity) }, \
         { "ppli_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 109, offsetof(mavlink_participant_position_t, ppli_type) }, \
         } \
}
#endif

/**
 * @brief Pack a participant_position message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Participant latitude, WGS84.
 * @param lon [degE7] Participant longitude, WGS84.
 * @param alt [m] Participant altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north (NED). NaN if unknown.
 * @param vy [m/s] Velocity east (NED). NaN if unknown.
 * @param vz [m/s] Velocity down (NED). NaN if unknown.
 * @param course [deg] Course over ground. NaN if unknown.
 * @param external_track_number  External/joint track number or URN for this participant. Empty if none.
 * @param callsign  Human-readable callsign/designation (null-terminated).
 * @param origin_sysid  System ID of the reporting participant.
 * @param external_track_type  Namespace of external_track_number.
 * @param stanag_identity  Standard identity (normally FRIEND for own-force PPLI).
 * @param ppli_type  Participant environment/type.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_participant_position_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float course, const char *external_track_number, const char *callsign, uint8_t origin_sysid, uint8_t external_track_type, uint8_t stanag_identity, uint8_t ppli_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, course);
    _mav_put_uint8_t(buf, 106, origin_sysid);
    _mav_put_uint8_t(buf, 107, external_track_type);
    _mav_put_uint8_t(buf, 108, stanag_identity);
    _mav_put_uint8_t(buf, 109, ppli_type);
    _mav_put_char_array(buf, 36, external_track_number, 20);
    _mav_put_char_array(buf, 56, callsign, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN);
#else
    mavlink_participant_position_t packet;
    packet.time_usec = time_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.course = course;
    packet.origin_sysid = origin_sysid;
    packet.external_track_type = external_track_type;
    packet.stanag_identity = stanag_identity;
    packet.ppli_type = ppli_type;
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet.callsign, callsign, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PARTICIPANT_POSITION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC);
}

/**
 * @brief Pack a participant_position message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Participant latitude, WGS84.
 * @param lon [degE7] Participant longitude, WGS84.
 * @param alt [m] Participant altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north (NED). NaN if unknown.
 * @param vy [m/s] Velocity east (NED). NaN if unknown.
 * @param vz [m/s] Velocity down (NED). NaN if unknown.
 * @param course [deg] Course over ground. NaN if unknown.
 * @param external_track_number  External/joint track number or URN for this participant. Empty if none.
 * @param callsign  Human-readable callsign/designation (null-terminated).
 * @param origin_sysid  System ID of the reporting participant.
 * @param external_track_type  Namespace of external_track_number.
 * @param stanag_identity  Standard identity (normally FRIEND for own-force PPLI).
 * @param ppli_type  Participant environment/type.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_participant_position_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float course, const char *external_track_number, const char *callsign, uint8_t origin_sysid, uint8_t external_track_type, uint8_t stanag_identity, uint8_t ppli_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, course);
    _mav_put_uint8_t(buf, 106, origin_sysid);
    _mav_put_uint8_t(buf, 107, external_track_type);
    _mav_put_uint8_t(buf, 108, stanag_identity);
    _mav_put_uint8_t(buf, 109, ppli_type);
    _mav_put_char_array(buf, 36, external_track_number, 20);
    _mav_put_char_array(buf, 56, callsign, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN);
#else
    mavlink_participant_position_t packet;
    packet.time_usec = time_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.course = course;
    packet.origin_sysid = origin_sysid;
    packet.external_track_type = external_track_type;
    packet.stanag_identity = stanag_identity;
    packet.ppli_type = ppli_type;
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet.callsign, callsign, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PARTICIPANT_POSITION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN);
#endif
}

/**
 * @brief Pack a participant_position message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Participant latitude, WGS84.
 * @param lon [degE7] Participant longitude, WGS84.
 * @param alt [m] Participant altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north (NED). NaN if unknown.
 * @param vy [m/s] Velocity east (NED). NaN if unknown.
 * @param vz [m/s] Velocity down (NED). NaN if unknown.
 * @param course [deg] Course over ground. NaN if unknown.
 * @param external_track_number  External/joint track number or URN for this participant. Empty if none.
 * @param callsign  Human-readable callsign/designation (null-terminated).
 * @param origin_sysid  System ID of the reporting participant.
 * @param external_track_type  Namespace of external_track_number.
 * @param stanag_identity  Standard identity (normally FRIEND for own-force PPLI).
 * @param ppli_type  Participant environment/type.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_participant_position_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,int32_t lat,int32_t lon,float alt,float vx,float vy,float vz,float course,const char *external_track_number,const char *callsign,uint8_t origin_sysid,uint8_t external_track_type,uint8_t stanag_identity,uint8_t ppli_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, course);
    _mav_put_uint8_t(buf, 106, origin_sysid);
    _mav_put_uint8_t(buf, 107, external_track_type);
    _mav_put_uint8_t(buf, 108, stanag_identity);
    _mav_put_uint8_t(buf, 109, ppli_type);
    _mav_put_char_array(buf, 36, external_track_number, 20);
    _mav_put_char_array(buf, 56, callsign, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN);
#else
    mavlink_participant_position_t packet;
    packet.time_usec = time_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.course = course;
    packet.origin_sysid = origin_sysid;
    packet.external_track_type = external_track_type;
    packet.stanag_identity = stanag_identity;
    packet.ppli_type = ppli_type;
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet.callsign, callsign, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PARTICIPANT_POSITION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC);
}

/**
 * @brief Encode a participant_position struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param participant_position C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_participant_position_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_participant_position_t* participant_position)
{
    return mavlink_msg_participant_position_pack(system_id, component_id, msg, participant_position->time_usec, participant_position->lat, participant_position->lon, participant_position->alt, participant_position->vx, participant_position->vy, participant_position->vz, participant_position->course, participant_position->external_track_number, participant_position->callsign, participant_position->origin_sysid, participant_position->external_track_type, participant_position->stanag_identity, participant_position->ppli_type);
}

/**
 * @brief Encode a participant_position struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param participant_position C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_participant_position_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_participant_position_t* participant_position)
{
    return mavlink_msg_participant_position_pack_chan(system_id, component_id, chan, msg, participant_position->time_usec, participant_position->lat, participant_position->lon, participant_position->alt, participant_position->vx, participant_position->vy, participant_position->vz, participant_position->course, participant_position->external_track_number, participant_position->callsign, participant_position->origin_sysid, participant_position->external_track_type, participant_position->stanag_identity, participant_position->ppli_type);
}

/**
 * @brief Encode a participant_position struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param participant_position C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_participant_position_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_participant_position_t* participant_position)
{
    return mavlink_msg_participant_position_pack_status(system_id, component_id, _status, msg,  participant_position->time_usec, participant_position->lat, participant_position->lon, participant_position->alt, participant_position->vx, participant_position->vy, participant_position->vz, participant_position->course, participant_position->external_track_number, participant_position->callsign, participant_position->origin_sysid, participant_position->external_track_type, participant_position->stanag_identity, participant_position->ppli_type);
}

/**
 * @brief Send a participant_position message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Participant latitude, WGS84.
 * @param lon [degE7] Participant longitude, WGS84.
 * @param alt [m] Participant altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north (NED). NaN if unknown.
 * @param vy [m/s] Velocity east (NED). NaN if unknown.
 * @param vz [m/s] Velocity down (NED). NaN if unknown.
 * @param course [deg] Course over ground. NaN if unknown.
 * @param external_track_number  External/joint track number or URN for this participant. Empty if none.
 * @param callsign  Human-readable callsign/designation (null-terminated).
 * @param origin_sysid  System ID of the reporting participant.
 * @param external_track_type  Namespace of external_track_number.
 * @param stanag_identity  Standard identity (normally FRIEND for own-force PPLI).
 * @param ppli_type  Participant environment/type.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_participant_position_send(mavlink_channel_t chan, uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float course, const char *external_track_number, const char *callsign, uint8_t origin_sysid, uint8_t external_track_type, uint8_t stanag_identity, uint8_t ppli_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, course);
    _mav_put_uint8_t(buf, 106, origin_sysid);
    _mav_put_uint8_t(buf, 107, external_track_type);
    _mav_put_uint8_t(buf, 108, stanag_identity);
    _mav_put_uint8_t(buf, 109, ppli_type);
    _mav_put_char_array(buf, 36, external_track_number, 20);
    _mav_put_char_array(buf, 56, callsign, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PARTICIPANT_POSITION, buf, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC);
#else
    mavlink_participant_position_t packet;
    packet.time_usec = time_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.course = course;
    packet.origin_sysid = origin_sysid;
    packet.external_track_type = external_track_type;
    packet.stanag_identity = stanag_identity;
    packet.ppli_type = ppli_type;
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet.callsign, callsign, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PARTICIPANT_POSITION, (const char *)&packet, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC);
#endif
}

/**
 * @brief Send a participant_position message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_participant_position_send_struct(mavlink_channel_t chan, const mavlink_participant_position_t* participant_position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_participant_position_send(chan, participant_position->time_usec, participant_position->lat, participant_position->lon, participant_position->alt, participant_position->vx, participant_position->vy, participant_position->vz, participant_position->course, participant_position->external_track_number, participant_position->callsign, participant_position->origin_sysid, participant_position->external_track_type, participant_position->stanag_identity, participant_position->ppli_type);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PARTICIPANT_POSITION, (const char *)participant_position, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC);
#endif
}

#if MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_participant_position_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float course, const char *external_track_number, const char *callsign, uint8_t origin_sysid, uint8_t external_track_type, uint8_t stanag_identity, uint8_t ppli_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, course);
    _mav_put_uint8_t(buf, 106, origin_sysid);
    _mav_put_uint8_t(buf, 107, external_track_type);
    _mav_put_uint8_t(buf, 108, stanag_identity);
    _mav_put_uint8_t(buf, 109, ppli_type);
    _mav_put_char_array(buf, 36, external_track_number, 20);
    _mav_put_char_array(buf, 56, callsign, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PARTICIPANT_POSITION, buf, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC);
#else
    mavlink_participant_position_t *packet = (mavlink_participant_position_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->vx = vx;
    packet->vy = vy;
    packet->vz = vz;
    packet->course = course;
    packet->origin_sysid = origin_sysid;
    packet->external_track_type = external_track_type;
    packet->stanag_identity = stanag_identity;
    packet->ppli_type = ppli_type;
    mav_array_memcpy(packet->external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet->callsign, callsign, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PARTICIPANT_POSITION, (const char *)packet, MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN, MAVLINK_MSG_ID_PARTICIPANT_POSITION_CRC);
#endif
}
#endif

#endif

// MESSAGE PARTICIPANT_POSITION UNPACKING


/**
 * @brief Get field time_usec from participant_position message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_participant_position_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field lat from participant_position message
 *
 * @return [degE7] Participant latitude, WGS84.
 */
static inline int32_t mavlink_msg_participant_position_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field lon from participant_position message
 *
 * @return [degE7] Participant longitude, WGS84.
 */
static inline int32_t mavlink_msg_participant_position_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field alt from participant_position message
 *
 * @return [m] Participant altitude, MSL. NaN if unknown.
 */
static inline float mavlink_msg_participant_position_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field vx from participant_position message
 *
 * @return [m/s] Velocity north (NED). NaN if unknown.
 */
static inline float mavlink_msg_participant_position_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field vy from participant_position message
 *
 * @return [m/s] Velocity east (NED). NaN if unknown.
 */
static inline float mavlink_msg_participant_position_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field vz from participant_position message
 *
 * @return [m/s] Velocity down (NED). NaN if unknown.
 */
static inline float mavlink_msg_participant_position_get_vz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field course from participant_position message
 *
 * @return [deg] Course over ground. NaN if unknown.
 */
static inline float mavlink_msg_participant_position_get_course(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field external_track_number from participant_position message
 *
 * @return  External/joint track number or URN for this participant. Empty if none.
 */
static inline uint16_t mavlink_msg_participant_position_get_external_track_number(const mavlink_message_t* msg, char *external_track_number)
{
    return _MAV_RETURN_char_array(msg, external_track_number, 20,  36);
}

/**
 * @brief Get field callsign from participant_position message
 *
 * @return  Human-readable callsign/designation (null-terminated).
 */
static inline uint16_t mavlink_msg_participant_position_get_callsign(const mavlink_message_t* msg, char *callsign)
{
    return _MAV_RETURN_char_array(msg, callsign, 50,  56);
}

/**
 * @brief Get field origin_sysid from participant_position message
 *
 * @return  System ID of the reporting participant.
 */
static inline uint8_t mavlink_msg_participant_position_get_origin_sysid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  106);
}

/**
 * @brief Get field external_track_type from participant_position message
 *
 * @return  Namespace of external_track_number.
 */
static inline uint8_t mavlink_msg_participant_position_get_external_track_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  107);
}

/**
 * @brief Get field stanag_identity from participant_position message
 *
 * @return  Standard identity (normally FRIEND for own-force PPLI).
 */
static inline uint8_t mavlink_msg_participant_position_get_stanag_identity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  108);
}

/**
 * @brief Get field ppli_type from participant_position message
 *
 * @return  Participant environment/type.
 */
static inline uint8_t mavlink_msg_participant_position_get_ppli_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  109);
}

/**
 * @brief Decode a participant_position message into a struct
 *
 * @param msg The message to decode
 * @param participant_position C-struct to decode the message contents into
 */
static inline void mavlink_msg_participant_position_decode(const mavlink_message_t* msg, mavlink_participant_position_t* participant_position)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    participant_position->time_usec = mavlink_msg_participant_position_get_time_usec(msg);
    participant_position->lat = mavlink_msg_participant_position_get_lat(msg);
    participant_position->lon = mavlink_msg_participant_position_get_lon(msg);
    participant_position->alt = mavlink_msg_participant_position_get_alt(msg);
    participant_position->vx = mavlink_msg_participant_position_get_vx(msg);
    participant_position->vy = mavlink_msg_participant_position_get_vy(msg);
    participant_position->vz = mavlink_msg_participant_position_get_vz(msg);
    participant_position->course = mavlink_msg_participant_position_get_course(msg);
    mavlink_msg_participant_position_get_external_track_number(msg, participant_position->external_track_number);
    mavlink_msg_participant_position_get_callsign(msg, participant_position->callsign);
    participant_position->origin_sysid = mavlink_msg_participant_position_get_origin_sysid(msg);
    participant_position->external_track_type = mavlink_msg_participant_position_get_external_track_type(msg);
    participant_position->stanag_identity = mavlink_msg_participant_position_get_stanag_identity(msg);
    participant_position->ppli_type = mavlink_msg_participant_position_get_ppli_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN? msg->len : MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN;
        memset(participant_position, 0, MAVLINK_MSG_ID_PARTICIPANT_POSITION_LEN);
    memcpy(participant_position, _MAV_PAYLOAD(msg), len);
#endif
}
