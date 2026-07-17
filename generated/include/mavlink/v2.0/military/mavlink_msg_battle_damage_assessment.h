#pragma once
// MESSAGE BATTLE_DAMAGE_ASSESSMENT PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT 53022


typedef struct __mavlink_battle_damage_assessment_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 int32_t lat; /*< [degE7] Assessed target latitude, WGS84.*/
 int32_t lon; /*< [degE7] Assessed target longitude, WGS84.*/
 float alt; /*< [m] Assessed target altitude, MSL.*/
 float vx; /*< [m/s] Velocity north component (NED). 0 if target is static.*/
 float vy; /*< [m/s] Velocity east component (NED). 0 if target is static.*/
 float vz; /*< [m/s] Velocity down component (NED). 0 if target is static.*/
 float cov_pos_x; /*<  Position covariance, north axis (m^2).*/
 float cov_pos_y; /*<  Position covariance, east axis (m^2).*/
 float cov_pos_z; /*<  Position covariance, down axis (m^2).*/
 float cov_vel_x; /*<  Velocity covariance, north axis (m^2/s^2).*/
 float cov_vel_y; /*<  Velocity covariance, east axis (m^2/s^2).*/
 float cov_vel_z; /*<  Velocity covariance, down axis (m^2/s^2).*/
 uint32_t target_set_id; /*<  Parent target set identifier.*/
 char target_name[50]; /*<  Human-readable target name (null-terminated).*/
 uint8_t authorization[8]; /*<  Opaque authorization token.*/
 uint8_t destruction_pct; /*< [%] Assessed target destruction level [0-100].*/
 uint8_t confidence_pct; /*< [%] Confidence of assessment [0-100].*/
 uint8_t target_class; /*<  Target classification.*/
 uint8_t target_force; /*<  Force affiliation.*/
 uint8_t functional_damage; /*<  Discrete functional damage state (joint-aligned), carried alongside destruction_pct.*/
 uint8_t physical_damage; /*<  Discrete physical damage state (combat-assessment layer).*/
 uint8_t reattack_recommended; /*<  Reattack recommendation: 1 = yes, 0 = no. Operational output of BDA.*/
 uint8_t track_uid[16]; /*<  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.*/
} mavlink_battle_damage_assessment_t;

#define MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN 141
#define MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN 141
#define MAVLINK_MSG_ID_53022_LEN 141
#define MAVLINK_MSG_ID_53022_MIN_LEN 141

#define MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC 167
#define MAVLINK_MSG_ID_53022_CRC 167

#define MAVLINK_MSG_BATTLE_DAMAGE_ASSESSMENT_FIELD_TARGET_NAME_LEN 50
#define MAVLINK_MSG_BATTLE_DAMAGE_ASSESSMENT_FIELD_AUTHORIZATION_LEN 8
#define MAVLINK_MSG_BATTLE_DAMAGE_ASSESSMENT_FIELD_TRACK_UID_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_BATTLE_DAMAGE_ASSESSMENT { \
    53022, \
    "BATTLE_DAMAGE_ASSESSMENT", \
    24, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_battle_damage_assessment_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_battle_damage_assessment_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_battle_damage_assessment_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_battle_damage_assessment_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_battle_damage_assessment_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_battle_damage_assessment_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_battle_damage_assessment_t, vz) }, \
         { "cov_pos_x", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_battle_damage_assessment_t, cov_pos_x) }, \
         { "cov_pos_y", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_battle_damage_assessment_t, cov_pos_y) }, \
         { "cov_pos_z", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_battle_damage_assessment_t, cov_pos_z) }, \
         { "cov_vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_battle_damage_assessment_t, cov_vel_x) }, \
         { "cov_vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_battle_damage_assessment_t, cov_vel_y) }, \
         { "cov_vel_z", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_battle_damage_assessment_t, cov_vel_z) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 56, offsetof(mavlink_battle_damage_assessment_t, target_set_id) }, \
         { "target_name", NULL, MAVLINK_TYPE_CHAR, 50, 60, offsetof(mavlink_battle_damage_assessment_t, target_name) }, \
         { "authorization", NULL, MAVLINK_TYPE_UINT8_T, 8, 110, offsetof(mavlink_battle_damage_assessment_t, authorization) }, \
         { "destruction_pct", NULL, MAVLINK_TYPE_UINT8_T, 0, 118, offsetof(mavlink_battle_damage_assessment_t, destruction_pct) }, \
         { "confidence_pct", NULL, MAVLINK_TYPE_UINT8_T, 0, 119, offsetof(mavlink_battle_damage_assessment_t, confidence_pct) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 120, offsetof(mavlink_battle_damage_assessment_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 121, offsetof(mavlink_battle_damage_assessment_t, target_force) }, \
         { "functional_damage", NULL, MAVLINK_TYPE_UINT8_T, 0, 122, offsetof(mavlink_battle_damage_assessment_t, functional_damage) }, \
         { "physical_damage", NULL, MAVLINK_TYPE_UINT8_T, 0, 123, offsetof(mavlink_battle_damage_assessment_t, physical_damage) }, \
         { "reattack_recommended", NULL, MAVLINK_TYPE_UINT8_T, 0, 124, offsetof(mavlink_battle_damage_assessment_t, reattack_recommended) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 125, offsetof(mavlink_battle_damage_assessment_t, track_uid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_BATTLE_DAMAGE_ASSESSMENT { \
    "BATTLE_DAMAGE_ASSESSMENT", \
    24, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_battle_damage_assessment_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_battle_damage_assessment_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_battle_damage_assessment_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_battle_damage_assessment_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_battle_damage_assessment_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_battle_damage_assessment_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_battle_damage_assessment_t, vz) }, \
         { "cov_pos_x", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_battle_damage_assessment_t, cov_pos_x) }, \
         { "cov_pos_y", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_battle_damage_assessment_t, cov_pos_y) }, \
         { "cov_pos_z", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_battle_damage_assessment_t, cov_pos_z) }, \
         { "cov_vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_battle_damage_assessment_t, cov_vel_x) }, \
         { "cov_vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_battle_damage_assessment_t, cov_vel_y) }, \
         { "cov_vel_z", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_battle_damage_assessment_t, cov_vel_z) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 56, offsetof(mavlink_battle_damage_assessment_t, target_set_id) }, \
         { "target_name", NULL, MAVLINK_TYPE_CHAR, 50, 60, offsetof(mavlink_battle_damage_assessment_t, target_name) }, \
         { "authorization", NULL, MAVLINK_TYPE_UINT8_T, 8, 110, offsetof(mavlink_battle_damage_assessment_t, authorization) }, \
         { "destruction_pct", NULL, MAVLINK_TYPE_UINT8_T, 0, 118, offsetof(mavlink_battle_damage_assessment_t, destruction_pct) }, \
         { "confidence_pct", NULL, MAVLINK_TYPE_UINT8_T, 0, 119, offsetof(mavlink_battle_damage_assessment_t, confidence_pct) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 120, offsetof(mavlink_battle_damage_assessment_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 121, offsetof(mavlink_battle_damage_assessment_t, target_force) }, \
         { "functional_damage", NULL, MAVLINK_TYPE_UINT8_T, 0, 122, offsetof(mavlink_battle_damage_assessment_t, functional_damage) }, \
         { "physical_damage", NULL, MAVLINK_TYPE_UINT8_T, 0, 123, offsetof(mavlink_battle_damage_assessment_t, physical_damage) }, \
         { "reattack_recommended", NULL, MAVLINK_TYPE_UINT8_T, 0, 124, offsetof(mavlink_battle_damage_assessment_t, reattack_recommended) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 125, offsetof(mavlink_battle_damage_assessment_t, track_uid) }, \
         } \
}
#endif

/**
 * @brief Pack a battle_damage_assessment message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Assessed target latitude, WGS84.
 * @param lon [degE7] Assessed target longitude, WGS84.
 * @param alt [m] Assessed target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED). 0 if target is static.
 * @param vy [m/s] Velocity east component (NED). 0 if target is static.
 * @param vz [m/s] Velocity down component (NED). 0 if target is static.
 * @param cov_pos_x  Position covariance, north axis (m^2).
 * @param cov_pos_y  Position covariance, east axis (m^2).
 * @param cov_pos_z  Position covariance, down axis (m^2).
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2).
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2).
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param authorization  Opaque authorization token.
 * @param destruction_pct [%] Assessed target destruction level [0-100].
 * @param confidence_pct [%] Confidence of assessment [0-100].
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @param functional_damage  Discrete functional damage state (joint-aligned), carried alongside destruction_pct.
 * @param physical_damage  Discrete physical damage state (combat-assessment layer).
 * @param reattack_recommended  Reattack recommendation: 1 = yes, 0 = no. Operational output of BDA.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, uint32_t target_set_id, const char *target_name, const uint8_t *authorization, uint8_t destruction_pct, uint8_t confidence_pct, uint8_t target_class, uint8_t target_force, uint8_t functional_damage, uint8_t physical_damage, uint8_t reattack_recommended, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, cov_pos_x);
    _mav_put_float(buf, 36, cov_pos_y);
    _mav_put_float(buf, 40, cov_pos_z);
    _mav_put_float(buf, 44, cov_vel_x);
    _mav_put_float(buf, 48, cov_vel_y);
    _mav_put_float(buf, 52, cov_vel_z);
    _mav_put_uint32_t(buf, 56, target_set_id);
    _mav_put_uint8_t(buf, 118, destruction_pct);
    _mav_put_uint8_t(buf, 119, confidence_pct);
    _mav_put_uint8_t(buf, 120, target_class);
    _mav_put_uint8_t(buf, 121, target_force);
    _mav_put_uint8_t(buf, 122, functional_damage);
    _mav_put_uint8_t(buf, 123, physical_damage);
    _mav_put_uint8_t(buf, 124, reattack_recommended);
    _mav_put_char_array(buf, 60, target_name, 50);
    _mav_put_uint8_t_array(buf, 110, authorization, 8);
    _mav_put_uint8_t_array(buf, 125, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN);
#else
    mavlink_battle_damage_assessment_t packet;
    packet.time_usec = time_usec;
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
    packet.destruction_pct = destruction_pct;
    packet.confidence_pct = confidence_pct;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.functional_damage = functional_damage;
    packet.physical_damage = physical_damage;
    packet.reattack_recommended = reattack_recommended;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet.authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC);
}

/**
 * @brief Pack a battle_damage_assessment message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Assessed target latitude, WGS84.
 * @param lon [degE7] Assessed target longitude, WGS84.
 * @param alt [m] Assessed target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED). 0 if target is static.
 * @param vy [m/s] Velocity east component (NED). 0 if target is static.
 * @param vz [m/s] Velocity down component (NED). 0 if target is static.
 * @param cov_pos_x  Position covariance, north axis (m^2).
 * @param cov_pos_y  Position covariance, east axis (m^2).
 * @param cov_pos_z  Position covariance, down axis (m^2).
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2).
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2).
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param authorization  Opaque authorization token.
 * @param destruction_pct [%] Assessed target destruction level [0-100].
 * @param confidence_pct [%] Confidence of assessment [0-100].
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @param functional_damage  Discrete functional damage state (joint-aligned), carried alongside destruction_pct.
 * @param physical_damage  Discrete physical damage state (combat-assessment layer).
 * @param reattack_recommended  Reattack recommendation: 1 = yes, 0 = no. Operational output of BDA.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, uint32_t target_set_id, const char *target_name, const uint8_t *authorization, uint8_t destruction_pct, uint8_t confidence_pct, uint8_t target_class, uint8_t target_force, uint8_t functional_damage, uint8_t physical_damage, uint8_t reattack_recommended, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, cov_pos_x);
    _mav_put_float(buf, 36, cov_pos_y);
    _mav_put_float(buf, 40, cov_pos_z);
    _mav_put_float(buf, 44, cov_vel_x);
    _mav_put_float(buf, 48, cov_vel_y);
    _mav_put_float(buf, 52, cov_vel_z);
    _mav_put_uint32_t(buf, 56, target_set_id);
    _mav_put_uint8_t(buf, 118, destruction_pct);
    _mav_put_uint8_t(buf, 119, confidence_pct);
    _mav_put_uint8_t(buf, 120, target_class);
    _mav_put_uint8_t(buf, 121, target_force);
    _mav_put_uint8_t(buf, 122, functional_damage);
    _mav_put_uint8_t(buf, 123, physical_damage);
    _mav_put_uint8_t(buf, 124, reattack_recommended);
    _mav_put_char_array(buf, 60, target_name, 50);
    _mav_put_uint8_t_array(buf, 110, authorization, 8);
    _mav_put_uint8_t_array(buf, 125, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN);
#else
    mavlink_battle_damage_assessment_t packet;
    packet.time_usec = time_usec;
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
    packet.destruction_pct = destruction_pct;
    packet.confidence_pct = confidence_pct;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.functional_damage = functional_damage;
    packet.physical_damage = physical_damage;
    packet.reattack_recommended = reattack_recommended;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet.authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN);
#endif
}

/**
 * @brief Pack a battle_damage_assessment message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Assessed target latitude, WGS84.
 * @param lon [degE7] Assessed target longitude, WGS84.
 * @param alt [m] Assessed target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED). 0 if target is static.
 * @param vy [m/s] Velocity east component (NED). 0 if target is static.
 * @param vz [m/s] Velocity down component (NED). 0 if target is static.
 * @param cov_pos_x  Position covariance, north axis (m^2).
 * @param cov_pos_y  Position covariance, east axis (m^2).
 * @param cov_pos_z  Position covariance, down axis (m^2).
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2).
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2).
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param authorization  Opaque authorization token.
 * @param destruction_pct [%] Assessed target destruction level [0-100].
 * @param confidence_pct [%] Confidence of assessment [0-100].
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @param functional_damage  Discrete functional damage state (joint-aligned), carried alongside destruction_pct.
 * @param physical_damage  Discrete physical damage state (combat-assessment layer).
 * @param reattack_recommended  Reattack recommendation: 1 = yes, 0 = no. Operational output of BDA.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,int32_t lat,int32_t lon,float alt,float vx,float vy,float vz,float cov_pos_x,float cov_pos_y,float cov_pos_z,float cov_vel_x,float cov_vel_y,float cov_vel_z,uint32_t target_set_id,const char *target_name,const uint8_t *authorization,uint8_t destruction_pct,uint8_t confidence_pct,uint8_t target_class,uint8_t target_force,uint8_t functional_damage,uint8_t physical_damage,uint8_t reattack_recommended,const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, cov_pos_x);
    _mav_put_float(buf, 36, cov_pos_y);
    _mav_put_float(buf, 40, cov_pos_z);
    _mav_put_float(buf, 44, cov_vel_x);
    _mav_put_float(buf, 48, cov_vel_y);
    _mav_put_float(buf, 52, cov_vel_z);
    _mav_put_uint32_t(buf, 56, target_set_id);
    _mav_put_uint8_t(buf, 118, destruction_pct);
    _mav_put_uint8_t(buf, 119, confidence_pct);
    _mav_put_uint8_t(buf, 120, target_class);
    _mav_put_uint8_t(buf, 121, target_force);
    _mav_put_uint8_t(buf, 122, functional_damage);
    _mav_put_uint8_t(buf, 123, physical_damage);
    _mav_put_uint8_t(buf, 124, reattack_recommended);
    _mav_put_char_array(buf, 60, target_name, 50);
    _mav_put_uint8_t_array(buf, 110, authorization, 8);
    _mav_put_uint8_t_array(buf, 125, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN);
#else
    mavlink_battle_damage_assessment_t packet;
    packet.time_usec = time_usec;
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
    packet.destruction_pct = destruction_pct;
    packet.confidence_pct = confidence_pct;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.functional_damage = functional_damage;
    packet.physical_damage = physical_damage;
    packet.reattack_recommended = reattack_recommended;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet.authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC);
}

/**
 * @brief Encode a battle_damage_assessment struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param battle_damage_assessment C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_battle_damage_assessment_t* battle_damage_assessment)
{
    return mavlink_msg_battle_damage_assessment_pack(system_id, component_id, msg, battle_damage_assessment->time_usec, battle_damage_assessment->lat, battle_damage_assessment->lon, battle_damage_assessment->alt, battle_damage_assessment->vx, battle_damage_assessment->vy, battle_damage_assessment->vz, battle_damage_assessment->cov_pos_x, battle_damage_assessment->cov_pos_y, battle_damage_assessment->cov_pos_z, battle_damage_assessment->cov_vel_x, battle_damage_assessment->cov_vel_y, battle_damage_assessment->cov_vel_z, battle_damage_assessment->target_set_id, battle_damage_assessment->target_name, battle_damage_assessment->authorization, battle_damage_assessment->destruction_pct, battle_damage_assessment->confidence_pct, battle_damage_assessment->target_class, battle_damage_assessment->target_force, battle_damage_assessment->functional_damage, battle_damage_assessment->physical_damage, battle_damage_assessment->reattack_recommended, battle_damage_assessment->track_uid);
}

/**
 * @brief Encode a battle_damage_assessment struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param battle_damage_assessment C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_battle_damage_assessment_t* battle_damage_assessment)
{
    return mavlink_msg_battle_damage_assessment_pack_chan(system_id, component_id, chan, msg, battle_damage_assessment->time_usec, battle_damage_assessment->lat, battle_damage_assessment->lon, battle_damage_assessment->alt, battle_damage_assessment->vx, battle_damage_assessment->vy, battle_damage_assessment->vz, battle_damage_assessment->cov_pos_x, battle_damage_assessment->cov_pos_y, battle_damage_assessment->cov_pos_z, battle_damage_assessment->cov_vel_x, battle_damage_assessment->cov_vel_y, battle_damage_assessment->cov_vel_z, battle_damage_assessment->target_set_id, battle_damage_assessment->target_name, battle_damage_assessment->authorization, battle_damage_assessment->destruction_pct, battle_damage_assessment->confidence_pct, battle_damage_assessment->target_class, battle_damage_assessment->target_force, battle_damage_assessment->functional_damage, battle_damage_assessment->physical_damage, battle_damage_assessment->reattack_recommended, battle_damage_assessment->track_uid);
}

/**
 * @brief Encode a battle_damage_assessment struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param battle_damage_assessment C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_battle_damage_assessment_t* battle_damage_assessment)
{
    return mavlink_msg_battle_damage_assessment_pack_status(system_id, component_id, _status, msg,  battle_damage_assessment->time_usec, battle_damage_assessment->lat, battle_damage_assessment->lon, battle_damage_assessment->alt, battle_damage_assessment->vx, battle_damage_assessment->vy, battle_damage_assessment->vz, battle_damage_assessment->cov_pos_x, battle_damage_assessment->cov_pos_y, battle_damage_assessment->cov_pos_z, battle_damage_assessment->cov_vel_x, battle_damage_assessment->cov_vel_y, battle_damage_assessment->cov_vel_z, battle_damage_assessment->target_set_id, battle_damage_assessment->target_name, battle_damage_assessment->authorization, battle_damage_assessment->destruction_pct, battle_damage_assessment->confidence_pct, battle_damage_assessment->target_class, battle_damage_assessment->target_force, battle_damage_assessment->functional_damage, battle_damage_assessment->physical_damage, battle_damage_assessment->reattack_recommended, battle_damage_assessment->track_uid);
}

/**
 * @brief Send a battle_damage_assessment message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Assessed target latitude, WGS84.
 * @param lon [degE7] Assessed target longitude, WGS84.
 * @param alt [m] Assessed target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED). 0 if target is static.
 * @param vy [m/s] Velocity east component (NED). 0 if target is static.
 * @param vz [m/s] Velocity down component (NED). 0 if target is static.
 * @param cov_pos_x  Position covariance, north axis (m^2).
 * @param cov_pos_y  Position covariance, east axis (m^2).
 * @param cov_pos_z  Position covariance, down axis (m^2).
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2).
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2).
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param authorization  Opaque authorization token.
 * @param destruction_pct [%] Assessed target destruction level [0-100].
 * @param confidence_pct [%] Confidence of assessment [0-100].
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @param functional_damage  Discrete functional damage state (joint-aligned), carried alongside destruction_pct.
 * @param physical_damage  Discrete physical damage state (combat-assessment layer).
 * @param reattack_recommended  Reattack recommendation: 1 = yes, 0 = no. Operational output of BDA.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_battle_damage_assessment_send(mavlink_channel_t chan, uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, uint32_t target_set_id, const char *target_name, const uint8_t *authorization, uint8_t destruction_pct, uint8_t confidence_pct, uint8_t target_class, uint8_t target_force, uint8_t functional_damage, uint8_t physical_damage, uint8_t reattack_recommended, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, vx);
    _mav_put_float(buf, 24, vy);
    _mav_put_float(buf, 28, vz);
    _mav_put_float(buf, 32, cov_pos_x);
    _mav_put_float(buf, 36, cov_pos_y);
    _mav_put_float(buf, 40, cov_pos_z);
    _mav_put_float(buf, 44, cov_vel_x);
    _mav_put_float(buf, 48, cov_vel_y);
    _mav_put_float(buf, 52, cov_vel_z);
    _mav_put_uint32_t(buf, 56, target_set_id);
    _mav_put_uint8_t(buf, 118, destruction_pct);
    _mav_put_uint8_t(buf, 119, confidence_pct);
    _mav_put_uint8_t(buf, 120, target_class);
    _mav_put_uint8_t(buf, 121, target_force);
    _mav_put_uint8_t(buf, 122, functional_damage);
    _mav_put_uint8_t(buf, 123, physical_damage);
    _mav_put_uint8_t(buf, 124, reattack_recommended);
    _mav_put_char_array(buf, 60, target_name, 50);
    _mav_put_uint8_t_array(buf, 110, authorization, 8);
    _mav_put_uint8_t_array(buf, 125, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT, buf, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC);
#else
    mavlink_battle_damage_assessment_t packet;
    packet.time_usec = time_usec;
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
    packet.destruction_pct = destruction_pct;
    packet.confidence_pct = confidence_pct;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.functional_damage = functional_damage;
    packet.physical_damage = physical_damage;
    packet.reattack_recommended = reattack_recommended;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet.authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT, (const char *)&packet, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC);
#endif
}

/**
 * @brief Send a battle_damage_assessment message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_battle_damage_assessment_send_struct(mavlink_channel_t chan, const mavlink_battle_damage_assessment_t* battle_damage_assessment)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_battle_damage_assessment_send(chan, battle_damage_assessment->time_usec, battle_damage_assessment->lat, battle_damage_assessment->lon, battle_damage_assessment->alt, battle_damage_assessment->vx, battle_damage_assessment->vy, battle_damage_assessment->vz, battle_damage_assessment->cov_pos_x, battle_damage_assessment->cov_pos_y, battle_damage_assessment->cov_pos_z, battle_damage_assessment->cov_vel_x, battle_damage_assessment->cov_vel_y, battle_damage_assessment->cov_vel_z, battle_damage_assessment->target_set_id, battle_damage_assessment->target_name, battle_damage_assessment->authorization, battle_damage_assessment->destruction_pct, battle_damage_assessment->confidence_pct, battle_damage_assessment->target_class, battle_damage_assessment->target_force, battle_damage_assessment->functional_damage, battle_damage_assessment->physical_damage, battle_damage_assessment->reattack_recommended, battle_damage_assessment->track_uid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT, (const char *)battle_damage_assessment, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC);
#endif
}

#if MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_battle_damage_assessment_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, uint32_t target_set_id, const char *target_name, const uint8_t *authorization, uint8_t destruction_pct, uint8_t confidence_pct, uint8_t target_class, uint8_t target_force, uint8_t functional_damage, uint8_t physical_damage, uint8_t reattack_recommended, const uint8_t *track_uid)
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
    _mav_put_float(buf, 32, cov_pos_x);
    _mav_put_float(buf, 36, cov_pos_y);
    _mav_put_float(buf, 40, cov_pos_z);
    _mav_put_float(buf, 44, cov_vel_x);
    _mav_put_float(buf, 48, cov_vel_y);
    _mav_put_float(buf, 52, cov_vel_z);
    _mav_put_uint32_t(buf, 56, target_set_id);
    _mav_put_uint8_t(buf, 118, destruction_pct);
    _mav_put_uint8_t(buf, 119, confidence_pct);
    _mav_put_uint8_t(buf, 120, target_class);
    _mav_put_uint8_t(buf, 121, target_force);
    _mav_put_uint8_t(buf, 122, functional_damage);
    _mav_put_uint8_t(buf, 123, physical_damage);
    _mav_put_uint8_t(buf, 124, reattack_recommended);
    _mav_put_char_array(buf, 60, target_name, 50);
    _mav_put_uint8_t_array(buf, 110, authorization, 8);
    _mav_put_uint8_t_array(buf, 125, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT, buf, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC);
#else
    mavlink_battle_damage_assessment_t *packet = (mavlink_battle_damage_assessment_t *)msgbuf;
    packet->time_usec = time_usec;
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
    packet->destruction_pct = destruction_pct;
    packet->confidence_pct = confidence_pct;
    packet->target_class = target_class;
    packet->target_force = target_force;
    packet->functional_damage = functional_damage;
    packet->physical_damage = physical_damage;
    packet->reattack_recommended = reattack_recommended;
    mav_array_memcpy(packet->target_name, target_name, sizeof(char)*50);
    mav_array_memcpy(packet->authorization, authorization, sizeof(uint8_t)*8);
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT, (const char *)packet, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_CRC);
#endif
}
#endif

#endif

// MESSAGE BATTLE_DAMAGE_ASSESSMENT UNPACKING


/**
 * @brief Get field time_usec from battle_damage_assessment message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_battle_damage_assessment_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field lat from battle_damage_assessment message
 *
 * @return [degE7] Assessed target latitude, WGS84.
 */
static inline int32_t mavlink_msg_battle_damage_assessment_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field lon from battle_damage_assessment message
 *
 * @return [degE7] Assessed target longitude, WGS84.
 */
static inline int32_t mavlink_msg_battle_damage_assessment_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field alt from battle_damage_assessment message
 *
 * @return [m] Assessed target altitude, MSL.
 */
static inline float mavlink_msg_battle_damage_assessment_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field vx from battle_damage_assessment message
 *
 * @return [m/s] Velocity north component (NED). 0 if target is static.
 */
static inline float mavlink_msg_battle_damage_assessment_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field vy from battle_damage_assessment message
 *
 * @return [m/s] Velocity east component (NED). 0 if target is static.
 */
static inline float mavlink_msg_battle_damage_assessment_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field vz from battle_damage_assessment message
 *
 * @return [m/s] Velocity down component (NED). 0 if target is static.
 */
static inline float mavlink_msg_battle_damage_assessment_get_vz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field cov_pos_x from battle_damage_assessment message
 *
 * @return  Position covariance, north axis (m^2).
 */
static inline float mavlink_msg_battle_damage_assessment_get_cov_pos_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field cov_pos_y from battle_damage_assessment message
 *
 * @return  Position covariance, east axis (m^2).
 */
static inline float mavlink_msg_battle_damage_assessment_get_cov_pos_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field cov_pos_z from battle_damage_assessment message
 *
 * @return  Position covariance, down axis (m^2).
 */
static inline float mavlink_msg_battle_damage_assessment_get_cov_pos_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field cov_vel_x from battle_damage_assessment message
 *
 * @return  Velocity covariance, north axis (m^2/s^2).
 */
static inline float mavlink_msg_battle_damage_assessment_get_cov_vel_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field cov_vel_y from battle_damage_assessment message
 *
 * @return  Velocity covariance, east axis (m^2/s^2).
 */
static inline float mavlink_msg_battle_damage_assessment_get_cov_vel_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field cov_vel_z from battle_damage_assessment message
 *
 * @return  Velocity covariance, down axis (m^2/s^2).
 */
static inline float mavlink_msg_battle_damage_assessment_get_cov_vel_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field target_set_id from battle_damage_assessment message
 *
 * @return  Parent target set identifier.
 */
static inline uint32_t mavlink_msg_battle_damage_assessment_get_target_set_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  56);
}

/**
 * @brief Get field target_name from battle_damage_assessment message
 *
 * @return  Human-readable target name (null-terminated).
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_get_target_name(const mavlink_message_t* msg, char *target_name)
{
    return _MAV_RETURN_char_array(msg, target_name, 50,  60);
}

/**
 * @brief Get field authorization from battle_damage_assessment message
 *
 * @return  Opaque authorization token.
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_get_authorization(const mavlink_message_t* msg, uint8_t *authorization)
{
    return _MAV_RETURN_uint8_t_array(msg, authorization, 8,  110);
}

/**
 * @brief Get field destruction_pct from battle_damage_assessment message
 *
 * @return [%] Assessed target destruction level [0-100].
 */
static inline uint8_t mavlink_msg_battle_damage_assessment_get_destruction_pct(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  118);
}

/**
 * @brief Get field confidence_pct from battle_damage_assessment message
 *
 * @return [%] Confidence of assessment [0-100].
 */
static inline uint8_t mavlink_msg_battle_damage_assessment_get_confidence_pct(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  119);
}

/**
 * @brief Get field target_class from battle_damage_assessment message
 *
 * @return  Target classification.
 */
static inline uint8_t mavlink_msg_battle_damage_assessment_get_target_class(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  120);
}

/**
 * @brief Get field target_force from battle_damage_assessment message
 *
 * @return  Force affiliation.
 */
static inline uint8_t mavlink_msg_battle_damage_assessment_get_target_force(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  121);
}

/**
 * @brief Get field functional_damage from battle_damage_assessment message
 *
 * @return  Discrete functional damage state (joint-aligned), carried alongside destruction_pct.
 */
static inline uint8_t mavlink_msg_battle_damage_assessment_get_functional_damage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  122);
}

/**
 * @brief Get field physical_damage from battle_damage_assessment message
 *
 * @return  Discrete physical damage state (combat-assessment layer).
 */
static inline uint8_t mavlink_msg_battle_damage_assessment_get_physical_damage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  123);
}

/**
 * @brief Get field reattack_recommended from battle_damage_assessment message
 *
 * @return  Reattack recommendation: 1 = yes, 0 = no. Operational output of BDA.
 */
static inline uint8_t mavlink_msg_battle_damage_assessment_get_reattack_recommended(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  124);
}

/**
 * @brief Get field track_uid from battle_damage_assessment message
 *
 * @return  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 */
static inline uint16_t mavlink_msg_battle_damage_assessment_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  125);
}

/**
 * @brief Decode a battle_damage_assessment message into a struct
 *
 * @param msg The message to decode
 * @param battle_damage_assessment C-struct to decode the message contents into
 */
static inline void mavlink_msg_battle_damage_assessment_decode(const mavlink_message_t* msg, mavlink_battle_damage_assessment_t* battle_damage_assessment)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    battle_damage_assessment->time_usec = mavlink_msg_battle_damage_assessment_get_time_usec(msg);
    battle_damage_assessment->lat = mavlink_msg_battle_damage_assessment_get_lat(msg);
    battle_damage_assessment->lon = mavlink_msg_battle_damage_assessment_get_lon(msg);
    battle_damage_assessment->alt = mavlink_msg_battle_damage_assessment_get_alt(msg);
    battle_damage_assessment->vx = mavlink_msg_battle_damage_assessment_get_vx(msg);
    battle_damage_assessment->vy = mavlink_msg_battle_damage_assessment_get_vy(msg);
    battle_damage_assessment->vz = mavlink_msg_battle_damage_assessment_get_vz(msg);
    battle_damage_assessment->cov_pos_x = mavlink_msg_battle_damage_assessment_get_cov_pos_x(msg);
    battle_damage_assessment->cov_pos_y = mavlink_msg_battle_damage_assessment_get_cov_pos_y(msg);
    battle_damage_assessment->cov_pos_z = mavlink_msg_battle_damage_assessment_get_cov_pos_z(msg);
    battle_damage_assessment->cov_vel_x = mavlink_msg_battle_damage_assessment_get_cov_vel_x(msg);
    battle_damage_assessment->cov_vel_y = mavlink_msg_battle_damage_assessment_get_cov_vel_y(msg);
    battle_damage_assessment->cov_vel_z = mavlink_msg_battle_damage_assessment_get_cov_vel_z(msg);
    battle_damage_assessment->target_set_id = mavlink_msg_battle_damage_assessment_get_target_set_id(msg);
    mavlink_msg_battle_damage_assessment_get_target_name(msg, battle_damage_assessment->target_name);
    mavlink_msg_battle_damage_assessment_get_authorization(msg, battle_damage_assessment->authorization);
    battle_damage_assessment->destruction_pct = mavlink_msg_battle_damage_assessment_get_destruction_pct(msg);
    battle_damage_assessment->confidence_pct = mavlink_msg_battle_damage_assessment_get_confidence_pct(msg);
    battle_damage_assessment->target_class = mavlink_msg_battle_damage_assessment_get_target_class(msg);
    battle_damage_assessment->target_force = mavlink_msg_battle_damage_assessment_get_target_force(msg);
    battle_damage_assessment->functional_damage = mavlink_msg_battle_damage_assessment_get_functional_damage(msg);
    battle_damage_assessment->physical_damage = mavlink_msg_battle_damage_assessment_get_physical_damage(msg);
    battle_damage_assessment->reattack_recommended = mavlink_msg_battle_damage_assessment_get_reattack_recommended(msg);
    mavlink_msg_battle_damage_assessment_get_track_uid(msg, battle_damage_assessment->track_uid);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN? msg->len : MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN;
        memset(battle_damage_assessment, 0, MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_LEN);
    memcpy(battle_damage_assessment, _MAV_PAYLOAD(msg), len);
#endif
}
