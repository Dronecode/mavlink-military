#pragma once
// MESSAGE TARGET_HANDOVER PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_TARGET_HANDOVER 53002


typedef struct __mavlink_target_handover_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint64_t detected_first_usec; /*< [us] Time target was first detected (UNIX epoch, microseconds UTC).*/
 uint64_t valid_until_usec; /*< [us] Handover data validity expiry (UNIX epoch, microseconds UTC).*/
 int32_t lat; /*< [degE7] Target latitude, WGS84.*/
 int32_t lon; /*< [degE7] Target longitude, WGS84.*/
 float alt; /*< [m] Target altitude, MSL.*/
 float vx; /*< [m/s] Velocity north component (NED).*/
 float vy; /*< [m/s] Velocity east component (NED).*/
 float vz; /*< [m/s] Velocity down component (NED).*/
 float cov_pos_x; /*<  Position covariance, north axis (m^2).*/
 float cov_pos_y; /*<  Position covariance, east axis (m^2).*/
 float cov_pos_z; /*<  Position covariance, down axis (m^2).*/
 float cov_vel_x; /*<  Velocity covariance, north axis (m^2/s^2).*/
 float cov_vel_y; /*<  Velocity covariance, east axis (m^2/s^2).*/
 float cov_vel_z; /*<  Velocity covariance, down axis (m^2/s^2).*/
 uint32_t target_set_id; /*<  Parent target set identifier.*/
 float confidence_score; /*<  Confidence score of identification [0.0-1.0].*/
 char target_name[50]; /*<  Human-readable target name (null-terminated).*/
 char match_media_url[50]; /*<  Short URL referencing matching media asset (null-terminated).*/
 uint8_t authorization[8]; /*<  Opaque authorization token.*/
 uint8_t target_class; /*<  Target classification.*/
 uint8_t target_force; /*<  Force affiliation.*/
 uint8_t match_media_type; /*<  Type of matching media referenced by match_media_url.*/
 uint8_t track_uid[16]; /*<  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this handover transfers. The authoritative correlation handle across aircraft; target_name is a human label only. All-zero if not associated with a track.*/
} mavlink_target_handover_t;

#define MAVLINK_MSG_ID_TARGET_HANDOVER_LEN 207
#define MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN 207
#define MAVLINK_MSG_ID_53002_LEN 207
#define MAVLINK_MSG_ID_53002_MIN_LEN 207

#define MAVLINK_MSG_ID_TARGET_HANDOVER_CRC 253
#define MAVLINK_MSG_ID_53002_CRC 253

#define MAVLINK_MSG_TARGET_HANDOVER_FIELD_TARGET_NAME_LEN 50
#define MAVLINK_MSG_TARGET_HANDOVER_FIELD_MATCH_MEDIA_URL_LEN 50
#define MAVLINK_MSG_TARGET_HANDOVER_FIELD_AUTHORIZATION_LEN 8
#define MAVLINK_MSG_TARGET_HANDOVER_FIELD_TRACK_UID_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TARGET_HANDOVER { \
    53002, \
    "TARGET_HANDOVER", \
    24, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_handover_t, time_usec) }, \
         { "detected_first_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_target_handover_t, detected_first_usec) }, \
         { "valid_until_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_target_handover_t, valid_until_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_target_handover_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_target_handover_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_handover_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_handover_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_target_handover_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_target_handover_t, vz) }, \
         { "cov_pos_x", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_target_handover_t, cov_pos_x) }, \
         { "cov_pos_y", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_target_handover_t, cov_pos_y) }, \
         { "cov_pos_z", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_target_handover_t, cov_pos_z) }, \
         { "cov_vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_target_handover_t, cov_vel_x) }, \
         { "cov_vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_target_handover_t, cov_vel_y) }, \
         { "cov_vel_z", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_target_handover_t, cov_vel_z) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 72, offsetof(mavlink_target_handover_t, target_set_id) }, \
         { "target_name", NULL, MAVLINK_TYPE_CHAR, 50, 80, offsetof(mavlink_target_handover_t, target_name) }, \
         { "match_media_url", NULL, MAVLINK_TYPE_CHAR, 50, 130, offsetof(mavlink_target_handover_t, match_media_url) }, \
         { "confidence_score", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_target_handover_t, confidence_score) }, \
         { "authorization", NULL, MAVLINK_TYPE_UINT8_T, 8, 180, offsetof(mavlink_target_handover_t, authorization) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 188, offsetof(mavlink_target_handover_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 189, offsetof(mavlink_target_handover_t, target_force) }, \
         { "match_media_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 190, offsetof(mavlink_target_handover_t, match_media_type) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 191, offsetof(mavlink_target_handover_t, track_uid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TARGET_HANDOVER { \
    "TARGET_HANDOVER", \
    24, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_handover_t, time_usec) }, \
         { "detected_first_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_target_handover_t, detected_first_usec) }, \
         { "valid_until_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_target_handover_t, valid_until_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_target_handover_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_target_handover_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_handover_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_handover_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_target_handover_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_target_handover_t, vz) }, \
         { "cov_pos_x", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_target_handover_t, cov_pos_x) }, \
         { "cov_pos_y", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_target_handover_t, cov_pos_y) }, \
         { "cov_pos_z", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_target_handover_t, cov_pos_z) }, \
         { "cov_vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_target_handover_t, cov_vel_x) }, \
         { "cov_vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_target_handover_t, cov_vel_y) }, \
         { "cov_vel_z", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_target_handover_t, cov_vel_z) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 72, offsetof(mavlink_target_handover_t, target_set_id) }, \
         { "target_name", NULL, MAVLINK_TYPE_CHAR, 50, 80, offsetof(mavlink_target_handover_t, target_name) }, \
         { "match_media_url", NULL, MAVLINK_TYPE_CHAR, 50, 130, offsetof(mavlink_target_handover_t, match_media_url) }, \
         { "confidence_score", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_target_handover_t, confidence_score) }, \
         { "authorization", NULL, MAVLINK_TYPE_UINT8_T, 8, 180, offsetof(mavlink_target_handover_t, authorization) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 188, offsetof(mavlink_target_handover_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 189, offsetof(mavlink_target_handover_t, target_force) }, \
         { "match_media_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 190, offsetof(mavlink_target_handover_t, match_media_type) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 191, offsetof(mavlink_target_handover_t, track_uid) }, \
         } \
}
#endif

/**
 * @brief Pack a target_handover message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param detected_first_usec [us] Time target was first detected (UNIX epoch, microseconds UTC).
 * @param valid_until_usec [us] Handover data validity expiry (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED).
 * @param vy [m/s] Velocity east component (NED).
 * @param vz [m/s] Velocity down component (NED).
 * @param cov_pos_x  Position covariance, north axis (m^2).
 * @param cov_pos_y  Position covariance, east axis (m^2).
 * @param cov_pos_z  Position covariance, down axis (m^2).
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2).
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2).
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param match_media_url  Short URL referencing matching media asset (null-terminated).
 * @param confidence_score  Confidence score of identification [0.0-1.0].
 * @param authorization  Opaque authorization token.
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @param match_media_type  Type of matching media referenced by match_media_url.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this handover transfers. The authoritative correlation handle across aircraft; target_name is a human label only. All-zero if not associated with a track.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_handover_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint64_t detected_first_usec, uint64_t valid_until_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, uint32_t target_set_id, const char *target_name, const char *match_media_url, float confidence_score, const uint8_t *authorization, uint8_t target_class, uint8_t target_force, uint8_t match_media_type, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_HANDOVER_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, detected_first_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_int32_t(buf, 24, lat);
    _mav_put_int32_t(buf, 28, lon);
    _mav_put_float(buf, 32, alt);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, vz);
    _mav_put_float(buf, 48, cov_pos_x);
    _mav_put_float(buf, 52, cov_pos_y);
    _mav_put_float(buf, 56, cov_pos_z);
    _mav_put_float(buf, 60, cov_vel_x);
    _mav_put_float(buf, 64, cov_vel_y);
    _mav_put_float(buf, 68, cov_vel_z);
    _mav_put_uint32_t(buf, 72, target_set_id);
    _mav_put_float(buf, 76, confidence_score);
    _mav_put_uint8_t(buf, 188, target_class);
    _mav_put_uint8_t(buf, 189, target_force);
    _mav_put_uint8_t(buf, 190, match_media_type);
    _mav_put_char_array(buf, 80, target_name, 50);
    _mav_put_char_array(buf, 130, match_media_url, 50);
    _mav_put_uint8_t_array(buf, 180, authorization, 8);
    _mav_put_uint8_t_array(buf, 191, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN);
#else
    mavlink_target_handover_t packet;
    packet.time_usec = time_usec;
    packet.detected_first_usec = detected_first_usec;
    packet.valid_until_usec = valid_until_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.cov_pos_x = cov_pos_x;
    packet.cov_pos_y = cov_pos_y;
    packet.cov_pos_z = cov_pos_z;
    packet.cov_vel_x = cov_vel_x;
    packet.cov_vel_y = cov_vel_y;
    packet.cov_vel_z = cov_vel_z;
    packet.target_set_id = target_set_id;
    packet.confidence_score = confidence_score;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.match_media_type = match_media_type;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet.match_media_url, match_media_url, sizeof(char)*50);
    mav_array_memcpy(packet.authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_HANDOVER;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_CRC);
}

/**
 * @brief Pack a target_handover message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param detected_first_usec [us] Time target was first detected (UNIX epoch, microseconds UTC).
 * @param valid_until_usec [us] Handover data validity expiry (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED).
 * @param vy [m/s] Velocity east component (NED).
 * @param vz [m/s] Velocity down component (NED).
 * @param cov_pos_x  Position covariance, north axis (m^2).
 * @param cov_pos_y  Position covariance, east axis (m^2).
 * @param cov_pos_z  Position covariance, down axis (m^2).
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2).
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2).
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param match_media_url  Short URL referencing matching media asset (null-terminated).
 * @param confidence_score  Confidence score of identification [0.0-1.0].
 * @param authorization  Opaque authorization token.
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @param match_media_type  Type of matching media referenced by match_media_url.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this handover transfers. The authoritative correlation handle across aircraft; target_name is a human label only. All-zero if not associated with a track.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_handover_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint64_t detected_first_usec, uint64_t valid_until_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, uint32_t target_set_id, const char *target_name, const char *match_media_url, float confidence_score, const uint8_t *authorization, uint8_t target_class, uint8_t target_force, uint8_t match_media_type, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_HANDOVER_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, detected_first_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_int32_t(buf, 24, lat);
    _mav_put_int32_t(buf, 28, lon);
    _mav_put_float(buf, 32, alt);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, vz);
    _mav_put_float(buf, 48, cov_pos_x);
    _mav_put_float(buf, 52, cov_pos_y);
    _mav_put_float(buf, 56, cov_pos_z);
    _mav_put_float(buf, 60, cov_vel_x);
    _mav_put_float(buf, 64, cov_vel_y);
    _mav_put_float(buf, 68, cov_vel_z);
    _mav_put_uint32_t(buf, 72, target_set_id);
    _mav_put_float(buf, 76, confidence_score);
    _mav_put_uint8_t(buf, 188, target_class);
    _mav_put_uint8_t(buf, 189, target_force);
    _mav_put_uint8_t(buf, 190, match_media_type);
    _mav_put_char_array(buf, 80, target_name, 50);
    _mav_put_char_array(buf, 130, match_media_url, 50);
    _mav_put_uint8_t_array(buf, 180, authorization, 8);
    _mav_put_uint8_t_array(buf, 191, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN);
#else
    mavlink_target_handover_t packet;
    packet.time_usec = time_usec;
    packet.detected_first_usec = detected_first_usec;
    packet.valid_until_usec = valid_until_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.cov_pos_x = cov_pos_x;
    packet.cov_pos_y = cov_pos_y;
    packet.cov_pos_z = cov_pos_z;
    packet.cov_vel_x = cov_vel_x;
    packet.cov_vel_y = cov_vel_y;
    packet.cov_vel_z = cov_vel_z;
    packet.target_set_id = target_set_id;
    packet.confidence_score = confidence_score;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.match_media_type = match_media_type;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet.match_media_url, match_media_url, sizeof(char)*50);
    mav_array_memcpy(packet.authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_HANDOVER;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN);
#endif
}

/**
 * @brief Pack a target_handover message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param detected_first_usec [us] Time target was first detected (UNIX epoch, microseconds UTC).
 * @param valid_until_usec [us] Handover data validity expiry (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED).
 * @param vy [m/s] Velocity east component (NED).
 * @param vz [m/s] Velocity down component (NED).
 * @param cov_pos_x  Position covariance, north axis (m^2).
 * @param cov_pos_y  Position covariance, east axis (m^2).
 * @param cov_pos_z  Position covariance, down axis (m^2).
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2).
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2).
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param match_media_url  Short URL referencing matching media asset (null-terminated).
 * @param confidence_score  Confidence score of identification [0.0-1.0].
 * @param authorization  Opaque authorization token.
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @param match_media_type  Type of matching media referenced by match_media_url.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this handover transfers. The authoritative correlation handle across aircraft; target_name is a human label only. All-zero if not associated with a track.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_handover_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint64_t detected_first_usec,uint64_t valid_until_usec,int32_t lat,int32_t lon,float alt,float vx,float vy,float vz,float cov_pos_x,float cov_pos_y,float cov_pos_z,float cov_vel_x,float cov_vel_y,float cov_vel_z,uint32_t target_set_id,const char *target_name,const char *match_media_url,float confidence_score,const uint8_t *authorization,uint8_t target_class,uint8_t target_force,uint8_t match_media_type,const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_HANDOVER_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, detected_first_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_int32_t(buf, 24, lat);
    _mav_put_int32_t(buf, 28, lon);
    _mav_put_float(buf, 32, alt);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, vz);
    _mav_put_float(buf, 48, cov_pos_x);
    _mav_put_float(buf, 52, cov_pos_y);
    _mav_put_float(buf, 56, cov_pos_z);
    _mav_put_float(buf, 60, cov_vel_x);
    _mav_put_float(buf, 64, cov_vel_y);
    _mav_put_float(buf, 68, cov_vel_z);
    _mav_put_uint32_t(buf, 72, target_set_id);
    _mav_put_float(buf, 76, confidence_score);
    _mav_put_uint8_t(buf, 188, target_class);
    _mav_put_uint8_t(buf, 189, target_force);
    _mav_put_uint8_t(buf, 190, match_media_type);
    _mav_put_char_array(buf, 80, target_name, 50);
    _mav_put_char_array(buf, 130, match_media_url, 50);
    _mav_put_uint8_t_array(buf, 180, authorization, 8);
    _mav_put_uint8_t_array(buf, 191, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN);
#else
    mavlink_target_handover_t packet;
    packet.time_usec = time_usec;
    packet.detected_first_usec = detected_first_usec;
    packet.valid_until_usec = valid_until_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.cov_pos_x = cov_pos_x;
    packet.cov_pos_y = cov_pos_y;
    packet.cov_pos_z = cov_pos_z;
    packet.cov_vel_x = cov_vel_x;
    packet.cov_vel_y = cov_vel_y;
    packet.cov_vel_z = cov_vel_z;
    packet.target_set_id = target_set_id;
    packet.confidence_score = confidence_score;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.match_media_type = match_media_type;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet.match_media_url, match_media_url, sizeof(char)*50);
    mav_array_memcpy(packet.authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_HANDOVER;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_CRC);
}

/**
 * @brief Encode a target_handover struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param target_handover C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_handover_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_target_handover_t* target_handover)
{
    return mavlink_msg_target_handover_pack(system_id, component_id, msg, target_handover->time_usec, target_handover->detected_first_usec, target_handover->valid_until_usec, target_handover->lat, target_handover->lon, target_handover->alt, target_handover->vx, target_handover->vy, target_handover->vz, target_handover->cov_pos_x, target_handover->cov_pos_y, target_handover->cov_pos_z, target_handover->cov_vel_x, target_handover->cov_vel_y, target_handover->cov_vel_z, target_handover->target_set_id, target_handover->target_name, target_handover->match_media_url, target_handover->confidence_score, target_handover->authorization, target_handover->target_class, target_handover->target_force, target_handover->match_media_type, target_handover->track_uid);
}

/**
 * @brief Encode a target_handover struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_handover C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_handover_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_target_handover_t* target_handover)
{
    return mavlink_msg_target_handover_pack_chan(system_id, component_id, chan, msg, target_handover->time_usec, target_handover->detected_first_usec, target_handover->valid_until_usec, target_handover->lat, target_handover->lon, target_handover->alt, target_handover->vx, target_handover->vy, target_handover->vz, target_handover->cov_pos_x, target_handover->cov_pos_y, target_handover->cov_pos_z, target_handover->cov_vel_x, target_handover->cov_vel_y, target_handover->cov_vel_z, target_handover->target_set_id, target_handover->target_name, target_handover->match_media_url, target_handover->confidence_score, target_handover->authorization, target_handover->target_class, target_handover->target_force, target_handover->match_media_type, target_handover->track_uid);
}

/**
 * @brief Encode a target_handover struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param target_handover C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_handover_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_target_handover_t* target_handover)
{
    return mavlink_msg_target_handover_pack_status(system_id, component_id, _status, msg,  target_handover->time_usec, target_handover->detected_first_usec, target_handover->valid_until_usec, target_handover->lat, target_handover->lon, target_handover->alt, target_handover->vx, target_handover->vy, target_handover->vz, target_handover->cov_pos_x, target_handover->cov_pos_y, target_handover->cov_pos_z, target_handover->cov_vel_x, target_handover->cov_vel_y, target_handover->cov_vel_z, target_handover->target_set_id, target_handover->target_name, target_handover->match_media_url, target_handover->confidence_score, target_handover->authorization, target_handover->target_class, target_handover->target_force, target_handover->match_media_type, target_handover->track_uid);
}

/**
 * @brief Send a target_handover message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param detected_first_usec [us] Time target was first detected (UNIX epoch, microseconds UTC).
 * @param valid_until_usec [us] Handover data validity expiry (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED).
 * @param vy [m/s] Velocity east component (NED).
 * @param vz [m/s] Velocity down component (NED).
 * @param cov_pos_x  Position covariance, north axis (m^2).
 * @param cov_pos_y  Position covariance, east axis (m^2).
 * @param cov_pos_z  Position covariance, down axis (m^2).
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2).
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2).
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param match_media_url  Short URL referencing matching media asset (null-terminated).
 * @param confidence_score  Confidence score of identification [0.0-1.0].
 * @param authorization  Opaque authorization token.
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @param match_media_type  Type of matching media referenced by match_media_url.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this handover transfers. The authoritative correlation handle across aircraft; target_name is a human label only. All-zero if not associated with a track.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_target_handover_send(mavlink_channel_t chan, uint64_t time_usec, uint64_t detected_first_usec, uint64_t valid_until_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, uint32_t target_set_id, const char *target_name, const char *match_media_url, float confidence_score, const uint8_t *authorization, uint8_t target_class, uint8_t target_force, uint8_t match_media_type, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_HANDOVER_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, detected_first_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_int32_t(buf, 24, lat);
    _mav_put_int32_t(buf, 28, lon);
    _mav_put_float(buf, 32, alt);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, vz);
    _mav_put_float(buf, 48, cov_pos_x);
    _mav_put_float(buf, 52, cov_pos_y);
    _mav_put_float(buf, 56, cov_pos_z);
    _mav_put_float(buf, 60, cov_vel_x);
    _mav_put_float(buf, 64, cov_vel_y);
    _mav_put_float(buf, 68, cov_vel_z);
    _mav_put_uint32_t(buf, 72, target_set_id);
    _mav_put_float(buf, 76, confidence_score);
    _mav_put_uint8_t(buf, 188, target_class);
    _mav_put_uint8_t(buf, 189, target_force);
    _mav_put_uint8_t(buf, 190, match_media_type);
    _mav_put_char_array(buf, 80, target_name, 50);
    _mav_put_char_array(buf, 130, match_media_url, 50);
    _mav_put_uint8_t_array(buf, 180, authorization, 8);
    _mav_put_uint8_t_array(buf, 191, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_HANDOVER, buf, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_CRC);
#else
    mavlink_target_handover_t packet;
    packet.time_usec = time_usec;
    packet.detected_first_usec = detected_first_usec;
    packet.valid_until_usec = valid_until_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.cov_pos_x = cov_pos_x;
    packet.cov_pos_y = cov_pos_y;
    packet.cov_pos_z = cov_pos_z;
    packet.cov_vel_x = cov_vel_x;
    packet.cov_vel_y = cov_vel_y;
    packet.cov_vel_z = cov_vel_z;
    packet.target_set_id = target_set_id;
    packet.confidence_score = confidence_score;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.match_media_type = match_media_type;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet.match_media_url, match_media_url, sizeof(char)*50);
    mav_array_memcpy(packet.authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_HANDOVER, (const char *)&packet, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_CRC);
#endif
}

/**
 * @brief Send a target_handover message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_target_handover_send_struct(mavlink_channel_t chan, const mavlink_target_handover_t* target_handover)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_target_handover_send(chan, target_handover->time_usec, target_handover->detected_first_usec, target_handover->valid_until_usec, target_handover->lat, target_handover->lon, target_handover->alt, target_handover->vx, target_handover->vy, target_handover->vz, target_handover->cov_pos_x, target_handover->cov_pos_y, target_handover->cov_pos_z, target_handover->cov_vel_x, target_handover->cov_vel_y, target_handover->cov_vel_z, target_handover->target_set_id, target_handover->target_name, target_handover->match_media_url, target_handover->confidence_score, target_handover->authorization, target_handover->target_class, target_handover->target_force, target_handover->match_media_type, target_handover->track_uid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_HANDOVER, (const char *)target_handover, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_CRC);
#endif
}

#if MAVLINK_MSG_ID_TARGET_HANDOVER_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_target_handover_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint64_t detected_first_usec, uint64_t valid_until_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, uint32_t target_set_id, const char *target_name, const char *match_media_url, float confidence_score, const uint8_t *authorization, uint8_t target_class, uint8_t target_force, uint8_t match_media_type, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, detected_first_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_int32_t(buf, 24, lat);
    _mav_put_int32_t(buf, 28, lon);
    _mav_put_float(buf, 32, alt);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, vz);
    _mav_put_float(buf, 48, cov_pos_x);
    _mav_put_float(buf, 52, cov_pos_y);
    _mav_put_float(buf, 56, cov_pos_z);
    _mav_put_float(buf, 60, cov_vel_x);
    _mav_put_float(buf, 64, cov_vel_y);
    _mav_put_float(buf, 68, cov_vel_z);
    _mav_put_uint32_t(buf, 72, target_set_id);
    _mav_put_float(buf, 76, confidence_score);
    _mav_put_uint8_t(buf, 188, target_class);
    _mav_put_uint8_t(buf, 189, target_force);
    _mav_put_uint8_t(buf, 190, match_media_type);
    _mav_put_char_array(buf, 80, target_name, 50);
    _mav_put_char_array(buf, 130, match_media_url, 50);
    _mav_put_uint8_t_array(buf, 180, authorization, 8);
    _mav_put_uint8_t_array(buf, 191, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_HANDOVER, buf, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_CRC);
#else
    mavlink_target_handover_t *packet = (mavlink_target_handover_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->detected_first_usec = detected_first_usec;
    packet->valid_until_usec = valid_until_usec;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->vx = vx;
    packet->vy = vy;
    packet->vz = vz;
    packet->cov_pos_x = cov_pos_x;
    packet->cov_pos_y = cov_pos_y;
    packet->cov_pos_z = cov_pos_z;
    packet->cov_vel_x = cov_vel_x;
    packet->cov_vel_y = cov_vel_y;
    packet->cov_vel_z = cov_vel_z;
    packet->target_set_id = target_set_id;
    packet->confidence_score = confidence_score;
    packet->target_class = target_class;
    packet->target_force = target_force;
    packet->match_media_type = match_media_type;
    mav_array_memcpy(packet->target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet->match_media_url, match_media_url, sizeof(char)*50);
    mav_array_memcpy(packet->authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_HANDOVER, (const char *)packet, MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN, MAVLINK_MSG_ID_TARGET_HANDOVER_CRC);
#endif
}
#endif

#endif

// MESSAGE TARGET_HANDOVER UNPACKING


/**
 * @brief Get field time_usec from target_handover message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_handover_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field detected_first_usec from target_handover message
 *
 * @return [us] Time target was first detected (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_handover_get_detected_first_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field valid_until_usec from target_handover message
 *
 * @return [us] Handover data validity expiry (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_handover_get_valid_until_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Get field lat from target_handover message
 *
 * @return [degE7] Target latitude, WGS84.
 */
static inline int32_t mavlink_msg_target_handover_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  24);
}

/**
 * @brief Get field lon from target_handover message
 *
 * @return [degE7] Target longitude, WGS84.
 */
static inline int32_t mavlink_msg_target_handover_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  28);
}

/**
 * @brief Get field alt from target_handover message
 *
 * @return [m] Target altitude, MSL.
 */
static inline float mavlink_msg_target_handover_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field vx from target_handover message
 *
 * @return [m/s] Velocity north component (NED).
 */
static inline float mavlink_msg_target_handover_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field vy from target_handover message
 *
 * @return [m/s] Velocity east component (NED).
 */
static inline float mavlink_msg_target_handover_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field vz from target_handover message
 *
 * @return [m/s] Velocity down component (NED).
 */
static inline float mavlink_msg_target_handover_get_vz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field cov_pos_x from target_handover message
 *
 * @return  Position covariance, north axis (m^2).
 */
static inline float mavlink_msg_target_handover_get_cov_pos_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field cov_pos_y from target_handover message
 *
 * @return  Position covariance, east axis (m^2).
 */
static inline float mavlink_msg_target_handover_get_cov_pos_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field cov_pos_z from target_handover message
 *
 * @return  Position covariance, down axis (m^2).
 */
static inline float mavlink_msg_target_handover_get_cov_pos_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field cov_vel_x from target_handover message
 *
 * @return  Velocity covariance, north axis (m^2/s^2).
 */
static inline float mavlink_msg_target_handover_get_cov_vel_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field cov_vel_y from target_handover message
 *
 * @return  Velocity covariance, east axis (m^2/s^2).
 */
static inline float mavlink_msg_target_handover_get_cov_vel_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field cov_vel_z from target_handover message
 *
 * @return  Velocity covariance, down axis (m^2/s^2).
 */
static inline float mavlink_msg_target_handover_get_cov_vel_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field target_set_id from target_handover message
 *
 * @return  Parent target set identifier.
 */
static inline uint32_t mavlink_msg_target_handover_get_target_set_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  72);
}

/**
 * @brief Get field target_name from target_handover message
 *
 * @return  Human-readable target name (null-terminated).
 */
static inline uint16_t mavlink_msg_target_handover_get_target_name(const mavlink_message_t* msg, char *target_name)
{
    return _MAV_RETURN_char_array(msg, target_name, 50,  80);
}

/**
 * @brief Get field match_media_url from target_handover message
 *
 * @return  Short URL referencing matching media asset (null-terminated).
 */
static inline uint16_t mavlink_msg_target_handover_get_match_media_url(const mavlink_message_t* msg, char *match_media_url)
{
    return _MAV_RETURN_char_array(msg, match_media_url, 50,  130);
}

/**
 * @brief Get field confidence_score from target_handover message
 *
 * @return  Confidence score of identification [0.0-1.0].
 */
static inline float mavlink_msg_target_handover_get_confidence_score(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field authorization from target_handover message
 *
 * @return  Opaque authorization token.
 */
static inline uint16_t mavlink_msg_target_handover_get_authorization(const mavlink_message_t* msg, uint8_t *authorization)
{
    return _MAV_RETURN_uint8_t_array(msg, authorization, 8,  180);
}

/**
 * @brief Get field target_class from target_handover message
 *
 * @return  Target classification.
 */
static inline uint8_t mavlink_msg_target_handover_get_target_class(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  188);
}

/**
 * @brief Get field target_force from target_handover message
 *
 * @return  Force affiliation.
 */
static inline uint8_t mavlink_msg_target_handover_get_target_force(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  189);
}

/**
 * @brief Get field match_media_type from target_handover message
 *
 * @return  Type of matching media referenced by match_media_url.
 */
static inline uint8_t mavlink_msg_target_handover_get_match_media_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  190);
}

/**
 * @brief Get field track_uid from target_handover message
 *
 * @return  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this handover transfers. The authoritative correlation handle across aircraft; target_name is a human label only. All-zero if not associated with a track.
 */
static inline uint16_t mavlink_msg_target_handover_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  191);
}

/**
 * @brief Decode a target_handover message into a struct
 *
 * @param msg The message to decode
 * @param target_handover C-struct to decode the message contents into
 */
static inline void mavlink_msg_target_handover_decode(const mavlink_message_t* msg, mavlink_target_handover_t* target_handover)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    target_handover->time_usec = mavlink_msg_target_handover_get_time_usec(msg);
    target_handover->detected_first_usec = mavlink_msg_target_handover_get_detected_first_usec(msg);
    target_handover->valid_until_usec = mavlink_msg_target_handover_get_valid_until_usec(msg);
    target_handover->lat = mavlink_msg_target_handover_get_lat(msg);
    target_handover->lon = mavlink_msg_target_handover_get_lon(msg);
    target_handover->alt = mavlink_msg_target_handover_get_alt(msg);
    target_handover->vx = mavlink_msg_target_handover_get_vx(msg);
    target_handover->vy = mavlink_msg_target_handover_get_vy(msg);
    target_handover->vz = mavlink_msg_target_handover_get_vz(msg);
    target_handover->cov_pos_x = mavlink_msg_target_handover_get_cov_pos_x(msg);
    target_handover->cov_pos_y = mavlink_msg_target_handover_get_cov_pos_y(msg);
    target_handover->cov_pos_z = mavlink_msg_target_handover_get_cov_pos_z(msg);
    target_handover->cov_vel_x = mavlink_msg_target_handover_get_cov_vel_x(msg);
    target_handover->cov_vel_y = mavlink_msg_target_handover_get_cov_vel_y(msg);
    target_handover->cov_vel_z = mavlink_msg_target_handover_get_cov_vel_z(msg);
    target_handover->target_set_id = mavlink_msg_target_handover_get_target_set_id(msg);
    target_handover->confidence_score = mavlink_msg_target_handover_get_confidence_score(msg);
    mavlink_msg_target_handover_get_target_name(msg, target_handover->target_name);
    mavlink_msg_target_handover_get_match_media_url(msg, target_handover->match_media_url);
    mavlink_msg_target_handover_get_authorization(msg, target_handover->authorization);
    target_handover->target_class = mavlink_msg_target_handover_get_target_class(msg);
    target_handover->target_force = mavlink_msg_target_handover_get_target_force(msg);
    target_handover->match_media_type = mavlink_msg_target_handover_get_match_media_type(msg);
    mavlink_msg_target_handover_get_track_uid(msg, target_handover->track_uid);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TARGET_HANDOVER_LEN? msg->len : MAVLINK_MSG_ID_TARGET_HANDOVER_LEN;
        memset(target_handover, 0, MAVLINK_MSG_ID_TARGET_HANDOVER_LEN);
    memcpy(target_handover, _MAV_PAYLOAD(msg), len);
#endif
}
