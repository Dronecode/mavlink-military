#pragma once
// MESSAGE TARGET_CUE PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_TARGET_CUE 53001


typedef struct __mavlink_target_cue_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint32_t cue_id; /*<  Unique identifier of this cue, assigned by the originator.*/
 uint32_t target_set_id; /*<  Parent target set identifier, if associated. 0 = none.*/
 int32_t lat; /*< [degE7] Cue latitude, WGS84.*/
 int32_t lon; /*< [degE7] Cue longitude, WGS84.*/
 float alt; /*< [m] Cue altitude, MSL. NaN if unknown.*/
 float vx; /*< [m/s] Velocity north (NED) if the point is moving. NaN if unknown/static.*/
 float vy; /*< [m/s] Velocity east (NED) if the point is moving. NaN if unknown/static.*/
 float vz; /*< [m/s] Velocity down (NED) if the point is moving. NaN if unknown/static.*/
 float confidence_score; /*<  Confidence of the geolocation and of the provisional class/force read [0.0-1.0]. NaN if not provided.*/
 uint8_t origin_sysid; /*<  MAVLink system ID of the originating (sensing) platform.*/
 uint8_t cue_type; /*<  Intent of the cue. Non-kinetic.*/
 uint8_t target_class; /*<  Provisional target classification from the sensing platform, qualified by confidence_score. A hint, not an identification.*/
 uint8_t target_force; /*<  Provisional force affiliation from the sensing platform, qualified by confidence_score. A hint, not a combat-ID determination; do not use as a release input.*/
 char name[20]; /*<  Short human-readable label (null-terminated).*/
} mavlink_target_cue_t;

#define MAVLINK_MSG_ID_TARGET_CUE_LEN 68
#define MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN 68
#define MAVLINK_MSG_ID_53001_LEN 68
#define MAVLINK_MSG_ID_53001_MIN_LEN 68

#define MAVLINK_MSG_ID_TARGET_CUE_CRC 11
#define MAVLINK_MSG_ID_53001_CRC 11

#define MAVLINK_MSG_TARGET_CUE_FIELD_NAME_LEN 20

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TARGET_CUE { \
    53001, \
    "TARGET_CUE", \
    15, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_cue_t, time_usec) }, \
         { "cue_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_target_cue_t, cue_id) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_target_cue_t, target_set_id) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_target_cue_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_target_cue_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_target_cue_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_cue_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_cue_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_cue_t, vz) }, \
         { "confidence_score", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_target_cue_t, confidence_score) }, \
         { "origin_sysid", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_target_cue_t, origin_sysid) }, \
         { "cue_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_target_cue_t, cue_type) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 46, offsetof(mavlink_target_cue_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 47, offsetof(mavlink_target_cue_t, target_force) }, \
         { "name", NULL, MAVLINK_TYPE_CHAR, 20, 48, offsetof(mavlink_target_cue_t, name) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TARGET_CUE { \
    "TARGET_CUE", \
    15, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_cue_t, time_usec) }, \
         { "cue_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_target_cue_t, cue_id) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_target_cue_t, target_set_id) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_target_cue_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_target_cue_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_target_cue_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_cue_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_cue_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_cue_t, vz) }, \
         { "confidence_score", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_target_cue_t, confidence_score) }, \
         { "origin_sysid", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_target_cue_t, origin_sysid) }, \
         { "cue_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_target_cue_t, cue_type) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 46, offsetof(mavlink_target_cue_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 47, offsetof(mavlink_target_cue_t, target_force) }, \
         { "name", NULL, MAVLINK_TYPE_CHAR, 20, 48, offsetof(mavlink_target_cue_t, name) }, \
         } \
}
#endif

/**
 * @brief Pack a target_cue message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param cue_id  Unique identifier of this cue, assigned by the originator.
 * @param target_set_id  Parent target set identifier, if associated. 0 = none.
 * @param lat [degE7] Cue latitude, WGS84.
 * @param lon [degE7] Cue longitude, WGS84.
 * @param alt [m] Cue altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north (NED) if the point is moving. NaN if unknown/static.
 * @param vy [m/s] Velocity east (NED) if the point is moving. NaN if unknown/static.
 * @param vz [m/s] Velocity down (NED) if the point is moving. NaN if unknown/static.
 * @param confidence_score  Confidence of the geolocation and of the provisional class/force read [0.0-1.0]. NaN if not provided.
 * @param origin_sysid  MAVLink system ID of the originating (sensing) platform.
 * @param cue_type  Intent of the cue. Non-kinetic.
 * @param target_class  Provisional target classification from the sensing platform, qualified by confidence_score. A hint, not an identification.
 * @param target_force  Provisional force affiliation from the sensing platform, qualified by confidence_score. A hint, not a combat-ID determination; do not use as a release input.
 * @param name  Short human-readable label (null-terminated).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_cue_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t cue_id, uint32_t target_set_id, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float confidence_score, uint8_t origin_sysid, uint8_t cue_type, uint8_t target_class, uint8_t target_force, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_CUE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, cue_id);
    _mav_put_uint32_t(buf, 12, target_set_id);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_float(buf, 28, vx);
    _mav_put_float(buf, 32, vy);
    _mav_put_float(buf, 36, vz);
    _mav_put_float(buf, 40, confidence_score);
    _mav_put_uint8_t(buf, 44, origin_sysid);
    _mav_put_uint8_t(buf, 45, cue_type);
    _mav_put_uint8_t(buf, 46, target_class);
    _mav_put_uint8_t(buf, 47, target_force);
    _mav_put_char_array(buf, 48, name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_CUE_LEN);
#else
    mavlink_target_cue_t packet;
    packet.time_usec = time_usec;
    packet.cue_id = cue_id;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.confidence_score = confidence_score;
    packet.origin_sysid = origin_sysid;
    packet.cue_type = cue_type;
    packet.target_class = target_class;
    packet.target_force = target_force;
    mav_array_memcpy(packet.name, name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_CUE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_CUE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN, MAVLINK_MSG_ID_TARGET_CUE_CRC);
}

/**
 * @brief Pack a target_cue message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param cue_id  Unique identifier of this cue, assigned by the originator.
 * @param target_set_id  Parent target set identifier, if associated. 0 = none.
 * @param lat [degE7] Cue latitude, WGS84.
 * @param lon [degE7] Cue longitude, WGS84.
 * @param alt [m] Cue altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north (NED) if the point is moving. NaN if unknown/static.
 * @param vy [m/s] Velocity east (NED) if the point is moving. NaN if unknown/static.
 * @param vz [m/s] Velocity down (NED) if the point is moving. NaN if unknown/static.
 * @param confidence_score  Confidence of the geolocation and of the provisional class/force read [0.0-1.0]. NaN if not provided.
 * @param origin_sysid  MAVLink system ID of the originating (sensing) platform.
 * @param cue_type  Intent of the cue. Non-kinetic.
 * @param target_class  Provisional target classification from the sensing platform, qualified by confidence_score. A hint, not an identification.
 * @param target_force  Provisional force affiliation from the sensing platform, qualified by confidence_score. A hint, not a combat-ID determination; do not use as a release input.
 * @param name  Short human-readable label (null-terminated).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_cue_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t cue_id, uint32_t target_set_id, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float confidence_score, uint8_t origin_sysid, uint8_t cue_type, uint8_t target_class, uint8_t target_force, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_CUE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, cue_id);
    _mav_put_uint32_t(buf, 12, target_set_id);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_float(buf, 28, vx);
    _mav_put_float(buf, 32, vy);
    _mav_put_float(buf, 36, vz);
    _mav_put_float(buf, 40, confidence_score);
    _mav_put_uint8_t(buf, 44, origin_sysid);
    _mav_put_uint8_t(buf, 45, cue_type);
    _mav_put_uint8_t(buf, 46, target_class);
    _mav_put_uint8_t(buf, 47, target_force);
    _mav_put_char_array(buf, 48, name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_CUE_LEN);
#else
    mavlink_target_cue_t packet;
    packet.time_usec = time_usec;
    packet.cue_id = cue_id;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.confidence_score = confidence_score;
    packet.origin_sysid = origin_sysid;
    packet.cue_type = cue_type;
    packet.target_class = target_class;
    packet.target_force = target_force;
    mav_array_memcpy(packet.name, name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_CUE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_CUE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN, MAVLINK_MSG_ID_TARGET_CUE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN);
#endif
}

/**
 * @brief Pack a target_cue message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param cue_id  Unique identifier of this cue, assigned by the originator.
 * @param target_set_id  Parent target set identifier, if associated. 0 = none.
 * @param lat [degE7] Cue latitude, WGS84.
 * @param lon [degE7] Cue longitude, WGS84.
 * @param alt [m] Cue altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north (NED) if the point is moving. NaN if unknown/static.
 * @param vy [m/s] Velocity east (NED) if the point is moving. NaN if unknown/static.
 * @param vz [m/s] Velocity down (NED) if the point is moving. NaN if unknown/static.
 * @param confidence_score  Confidence of the geolocation and of the provisional class/force read [0.0-1.0]. NaN if not provided.
 * @param origin_sysid  MAVLink system ID of the originating (sensing) platform.
 * @param cue_type  Intent of the cue. Non-kinetic.
 * @param target_class  Provisional target classification from the sensing platform, qualified by confidence_score. A hint, not an identification.
 * @param target_force  Provisional force affiliation from the sensing platform, qualified by confidence_score. A hint, not a combat-ID determination; do not use as a release input.
 * @param name  Short human-readable label (null-terminated).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_cue_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t cue_id,uint32_t target_set_id,int32_t lat,int32_t lon,float alt,float vx,float vy,float vz,float confidence_score,uint8_t origin_sysid,uint8_t cue_type,uint8_t target_class,uint8_t target_force,const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_CUE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, cue_id);
    _mav_put_uint32_t(buf, 12, target_set_id);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_float(buf, 28, vx);
    _mav_put_float(buf, 32, vy);
    _mav_put_float(buf, 36, vz);
    _mav_put_float(buf, 40, confidence_score);
    _mav_put_uint8_t(buf, 44, origin_sysid);
    _mav_put_uint8_t(buf, 45, cue_type);
    _mav_put_uint8_t(buf, 46, target_class);
    _mav_put_uint8_t(buf, 47, target_force);
    _mav_put_char_array(buf, 48, name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_CUE_LEN);
#else
    mavlink_target_cue_t packet;
    packet.time_usec = time_usec;
    packet.cue_id = cue_id;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.confidence_score = confidence_score;
    packet.origin_sysid = origin_sysid;
    packet.cue_type = cue_type;
    packet.target_class = target_class;
    packet.target_force = target_force;
    mav_array_memcpy(packet.name, name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_CUE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_CUE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN, MAVLINK_MSG_ID_TARGET_CUE_CRC);
}

/**
 * @brief Encode a target_cue struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param target_cue C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_cue_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_target_cue_t* target_cue)
{
    return mavlink_msg_target_cue_pack(system_id, component_id, msg, target_cue->time_usec, target_cue->cue_id, target_cue->target_set_id, target_cue->lat, target_cue->lon, target_cue->alt, target_cue->vx, target_cue->vy, target_cue->vz, target_cue->confidence_score, target_cue->origin_sysid, target_cue->cue_type, target_cue->target_class, target_cue->target_force, target_cue->name);
}

/**
 * @brief Encode a target_cue struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_cue C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_cue_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_target_cue_t* target_cue)
{
    return mavlink_msg_target_cue_pack_chan(system_id, component_id, chan, msg, target_cue->time_usec, target_cue->cue_id, target_cue->target_set_id, target_cue->lat, target_cue->lon, target_cue->alt, target_cue->vx, target_cue->vy, target_cue->vz, target_cue->confidence_score, target_cue->origin_sysid, target_cue->cue_type, target_cue->target_class, target_cue->target_force, target_cue->name);
}

/**
 * @brief Encode a target_cue struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param target_cue C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_cue_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_target_cue_t* target_cue)
{
    return mavlink_msg_target_cue_pack_status(system_id, component_id, _status, msg,  target_cue->time_usec, target_cue->cue_id, target_cue->target_set_id, target_cue->lat, target_cue->lon, target_cue->alt, target_cue->vx, target_cue->vy, target_cue->vz, target_cue->confidence_score, target_cue->origin_sysid, target_cue->cue_type, target_cue->target_class, target_cue->target_force, target_cue->name);
}

/**
 * @brief Send a target_cue message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param cue_id  Unique identifier of this cue, assigned by the originator.
 * @param target_set_id  Parent target set identifier, if associated. 0 = none.
 * @param lat [degE7] Cue latitude, WGS84.
 * @param lon [degE7] Cue longitude, WGS84.
 * @param alt [m] Cue altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north (NED) if the point is moving. NaN if unknown/static.
 * @param vy [m/s] Velocity east (NED) if the point is moving. NaN if unknown/static.
 * @param vz [m/s] Velocity down (NED) if the point is moving. NaN if unknown/static.
 * @param confidence_score  Confidence of the geolocation and of the provisional class/force read [0.0-1.0]. NaN if not provided.
 * @param origin_sysid  MAVLink system ID of the originating (sensing) platform.
 * @param cue_type  Intent of the cue. Non-kinetic.
 * @param target_class  Provisional target classification from the sensing platform, qualified by confidence_score. A hint, not an identification.
 * @param target_force  Provisional force affiliation from the sensing platform, qualified by confidence_score. A hint, not a combat-ID determination; do not use as a release input.
 * @param name  Short human-readable label (null-terminated).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_target_cue_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t cue_id, uint32_t target_set_id, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float confidence_score, uint8_t origin_sysid, uint8_t cue_type, uint8_t target_class, uint8_t target_force, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_CUE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, cue_id);
    _mav_put_uint32_t(buf, 12, target_set_id);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_float(buf, 28, vx);
    _mav_put_float(buf, 32, vy);
    _mav_put_float(buf, 36, vz);
    _mav_put_float(buf, 40, confidence_score);
    _mav_put_uint8_t(buf, 44, origin_sysid);
    _mav_put_uint8_t(buf, 45, cue_type);
    _mav_put_uint8_t(buf, 46, target_class);
    _mav_put_uint8_t(buf, 47, target_force);
    _mav_put_char_array(buf, 48, name, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_CUE, buf, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN, MAVLINK_MSG_ID_TARGET_CUE_CRC);
#else
    mavlink_target_cue_t packet;
    packet.time_usec = time_usec;
    packet.cue_id = cue_id;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.confidence_score = confidence_score;
    packet.origin_sysid = origin_sysid;
    packet.cue_type = cue_type;
    packet.target_class = target_class;
    packet.target_force = target_force;
    mav_array_memcpy(packet.name, name, sizeof(char)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_CUE, (const char *)&packet, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN, MAVLINK_MSG_ID_TARGET_CUE_CRC);
#endif
}

/**
 * @brief Send a target_cue message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_target_cue_send_struct(mavlink_channel_t chan, const mavlink_target_cue_t* target_cue)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_target_cue_send(chan, target_cue->time_usec, target_cue->cue_id, target_cue->target_set_id, target_cue->lat, target_cue->lon, target_cue->alt, target_cue->vx, target_cue->vy, target_cue->vz, target_cue->confidence_score, target_cue->origin_sysid, target_cue->cue_type, target_cue->target_class, target_cue->target_force, target_cue->name);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_CUE, (const char *)target_cue, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN, MAVLINK_MSG_ID_TARGET_CUE_CRC);
#endif
}

#if MAVLINK_MSG_ID_TARGET_CUE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_target_cue_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t cue_id, uint32_t target_set_id, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float confidence_score, uint8_t origin_sysid, uint8_t cue_type, uint8_t target_class, uint8_t target_force, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, cue_id);
    _mav_put_uint32_t(buf, 12, target_set_id);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_float(buf, 28, vx);
    _mav_put_float(buf, 32, vy);
    _mav_put_float(buf, 36, vz);
    _mav_put_float(buf, 40, confidence_score);
    _mav_put_uint8_t(buf, 44, origin_sysid);
    _mav_put_uint8_t(buf, 45, cue_type);
    _mav_put_uint8_t(buf, 46, target_class);
    _mav_put_uint8_t(buf, 47, target_force);
    _mav_put_char_array(buf, 48, name, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_CUE, buf, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN, MAVLINK_MSG_ID_TARGET_CUE_CRC);
#else
    mavlink_target_cue_t *packet = (mavlink_target_cue_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->cue_id = cue_id;
    packet->target_set_id = target_set_id;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->vx = vx;
    packet->vy = vy;
    packet->vz = vz;
    packet->confidence_score = confidence_score;
    packet->origin_sysid = origin_sysid;
    packet->cue_type = cue_type;
    packet->target_class = target_class;
    packet->target_force = target_force;
    mav_array_memcpy(packet->name, name, sizeof(char)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_CUE, (const char *)packet, MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN, MAVLINK_MSG_ID_TARGET_CUE_LEN, MAVLINK_MSG_ID_TARGET_CUE_CRC);
#endif
}
#endif

#endif

// MESSAGE TARGET_CUE UNPACKING


/**
 * @brief Get field time_usec from target_cue message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_cue_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field cue_id from target_cue message
 *
 * @return  Unique identifier of this cue, assigned by the originator.
 */
static inline uint32_t mavlink_msg_target_cue_get_cue_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field target_set_id from target_cue message
 *
 * @return  Parent target set identifier, if associated. 0 = none.
 */
static inline uint32_t mavlink_msg_target_cue_get_target_set_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field lat from target_cue message
 *
 * @return [degE7] Cue latitude, WGS84.
 */
static inline int32_t mavlink_msg_target_cue_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field lon from target_cue message
 *
 * @return [degE7] Cue longitude, WGS84.
 */
static inline int32_t mavlink_msg_target_cue_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field alt from target_cue message
 *
 * @return [m] Cue altitude, MSL. NaN if unknown.
 */
static inline float mavlink_msg_target_cue_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field vx from target_cue message
 *
 * @return [m/s] Velocity north (NED) if the point is moving. NaN if unknown/static.
 */
static inline float mavlink_msg_target_cue_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field vy from target_cue message
 *
 * @return [m/s] Velocity east (NED) if the point is moving. NaN if unknown/static.
 */
static inline float mavlink_msg_target_cue_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field vz from target_cue message
 *
 * @return [m/s] Velocity down (NED) if the point is moving. NaN if unknown/static.
 */
static inline float mavlink_msg_target_cue_get_vz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field confidence_score from target_cue message
 *
 * @return  Confidence of the geolocation and of the provisional class/force read [0.0-1.0]. NaN if not provided.
 */
static inline float mavlink_msg_target_cue_get_confidence_score(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field origin_sysid from target_cue message
 *
 * @return  MAVLink system ID of the originating (sensing) platform.
 */
static inline uint8_t mavlink_msg_target_cue_get_origin_sysid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  44);
}

/**
 * @brief Get field cue_type from target_cue message
 *
 * @return  Intent of the cue. Non-kinetic.
 */
static inline uint8_t mavlink_msg_target_cue_get_cue_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  45);
}

/**
 * @brief Get field target_class from target_cue message
 *
 * @return  Provisional target classification from the sensing platform, qualified by confidence_score. A hint, not an identification.
 */
static inline uint8_t mavlink_msg_target_cue_get_target_class(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  46);
}

/**
 * @brief Get field target_force from target_cue message
 *
 * @return  Provisional force affiliation from the sensing platform, qualified by confidence_score. A hint, not a combat-ID determination; do not use as a release input.
 */
static inline uint8_t mavlink_msg_target_cue_get_target_force(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  47);
}

/**
 * @brief Get field name from target_cue message
 *
 * @return  Short human-readable label (null-terminated).
 */
static inline uint16_t mavlink_msg_target_cue_get_name(const mavlink_message_t* msg, char *name)
{
    return _MAV_RETURN_char_array(msg, name, 20,  48);
}

/**
 * @brief Decode a target_cue message into a struct
 *
 * @param msg The message to decode
 * @param target_cue C-struct to decode the message contents into
 */
static inline void mavlink_msg_target_cue_decode(const mavlink_message_t* msg, mavlink_target_cue_t* target_cue)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    target_cue->time_usec = mavlink_msg_target_cue_get_time_usec(msg);
    target_cue->cue_id = mavlink_msg_target_cue_get_cue_id(msg);
    target_cue->target_set_id = mavlink_msg_target_cue_get_target_set_id(msg);
    target_cue->lat = mavlink_msg_target_cue_get_lat(msg);
    target_cue->lon = mavlink_msg_target_cue_get_lon(msg);
    target_cue->alt = mavlink_msg_target_cue_get_alt(msg);
    target_cue->vx = mavlink_msg_target_cue_get_vx(msg);
    target_cue->vy = mavlink_msg_target_cue_get_vy(msg);
    target_cue->vz = mavlink_msg_target_cue_get_vz(msg);
    target_cue->confidence_score = mavlink_msg_target_cue_get_confidence_score(msg);
    target_cue->origin_sysid = mavlink_msg_target_cue_get_origin_sysid(msg);
    target_cue->cue_type = mavlink_msg_target_cue_get_cue_type(msg);
    target_cue->target_class = mavlink_msg_target_cue_get_target_class(msg);
    target_cue->target_force = mavlink_msg_target_cue_get_target_force(msg);
    mavlink_msg_target_cue_get_name(msg, target_cue->name);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TARGET_CUE_LEN? msg->len : MAVLINK_MSG_ID_TARGET_CUE_LEN;
        memset(target_cue, 0, MAVLINK_MSG_ID_TARGET_CUE_LEN);
    memcpy(target_cue, _MAV_PAYLOAD(msg), len);
#endif
}
