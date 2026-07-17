#pragma once
// MESSAGE RWS_POSE PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_RWS_POSE 53040


typedef struct __mavlink_rws_pose_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 int32_t lat; /*< [degE7] RWS latitude, WGS84. INT32_MAX if unknown.*/
 int32_t lon; /*< [degE7] RWS longitude, WGS84. INT32_MAX if unknown.*/
 float alt; /*< [m] RWS altitude, MSL. NaN if unknown.*/
 float vx; /*< [m/s] Velocity north component (NED). NaN if unknown.*/
 float vy; /*< [m/s] Velocity east component (NED). NaN if unknown.*/
 float vz; /*< [m/s] Velocity down component (NED). NaN if unknown.*/
 float cov_pos_x; /*<  Position covariance, north axis (m^2). NaN if unknown.*/
 float cov_pos_y; /*<  Position covariance, east axis (m^2). NaN if unknown.*/
 float cov_pos_z; /*<  Position covariance, down axis (m^2). NaN if unknown.*/
 float cov_vel_x; /*<  Velocity covariance, north axis (m^2/s^2). NaN if unknown.*/
 float cov_vel_y; /*<  Velocity covariance, east axis (m^2/s^2). NaN if unknown.*/
 float cov_vel_z; /*<  Velocity covariance, down axis (m^2/s^2). NaN if unknown.*/
 float offset_x; /*< [m] Mounting offset X from vehicle reference point in coordinate_frame.*/
 float offset_y; /*< [m] Mounting offset Y from vehicle reference point in coordinate_frame.*/
 float offset_z; /*< [m] Mounting offset Z from vehicle reference point in coordinate_frame.*/
 float q[4]; /*<  RWS orientation quaternion [w, x, y, z] relative to coordinate_frame.*/
 float accuracy_roll; /*< [rad] Roll orientation accuracy (1-sigma).*/
 float accuracy_pitch; /*< [rad] Pitch orientation accuracy (1-sigma).*/
 float accuracy_yaw; /*< [rad] Yaw orientation accuracy (1-sigma).*/
 uint8_t coordinate_frame; /*<  Coordinate frame for offset and orientation. See MAV_FRAME.*/
} mavlink_rws_pose_t;

#define MAVLINK_MSG_ID_RWS_POSE_LEN 97
#define MAVLINK_MSG_ID_RWS_POSE_MIN_LEN 97
#define MAVLINK_MSG_ID_53040_LEN 97
#define MAVLINK_MSG_ID_53040_MIN_LEN 97

#define MAVLINK_MSG_ID_RWS_POSE_CRC 107
#define MAVLINK_MSG_ID_53040_CRC 107

#define MAVLINK_MSG_RWS_POSE_FIELD_Q_LEN 4

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_RWS_POSE { \
    53040, \
    "RWS_POSE", \
    21, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rws_pose_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_rws_pose_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_rws_pose_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_rws_pose_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_rws_pose_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_rws_pose_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_rws_pose_t, vz) }, \
         { "cov_pos_x", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_rws_pose_t, cov_pos_x) }, \
         { "cov_pos_y", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_rws_pose_t, cov_pos_y) }, \
         { "cov_pos_z", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_rws_pose_t, cov_pos_z) }, \
         { "cov_vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_rws_pose_t, cov_vel_x) }, \
         { "cov_vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_rws_pose_t, cov_vel_y) }, \
         { "cov_vel_z", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_rws_pose_t, cov_vel_z) }, \
         { "offset_x", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_rws_pose_t, offset_x) }, \
         { "offset_y", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_rws_pose_t, offset_y) }, \
         { "offset_z", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_rws_pose_t, offset_z) }, \
         { "q", NULL, MAVLINK_TYPE_FLOAT, 4, 68, offsetof(mavlink_rws_pose_t, q) }, \
         { "accuracy_roll", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_rws_pose_t, accuracy_roll) }, \
         { "accuracy_pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_rws_pose_t, accuracy_pitch) }, \
         { "accuracy_yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 92, offsetof(mavlink_rws_pose_t, accuracy_yaw) }, \
         { "coordinate_frame", NULL, MAVLINK_TYPE_UINT8_T, 0, 96, offsetof(mavlink_rws_pose_t, coordinate_frame) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_RWS_POSE { \
    "RWS_POSE", \
    21, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rws_pose_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_rws_pose_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_rws_pose_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_rws_pose_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_rws_pose_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_rws_pose_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_rws_pose_t, vz) }, \
         { "cov_pos_x", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_rws_pose_t, cov_pos_x) }, \
         { "cov_pos_y", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_rws_pose_t, cov_pos_y) }, \
         { "cov_pos_z", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_rws_pose_t, cov_pos_z) }, \
         { "cov_vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_rws_pose_t, cov_vel_x) }, \
         { "cov_vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_rws_pose_t, cov_vel_y) }, \
         { "cov_vel_z", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_rws_pose_t, cov_vel_z) }, \
         { "offset_x", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_rws_pose_t, offset_x) }, \
         { "offset_y", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_rws_pose_t, offset_y) }, \
         { "offset_z", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_rws_pose_t, offset_z) }, \
         { "q", NULL, MAVLINK_TYPE_FLOAT, 4, 68, offsetof(mavlink_rws_pose_t, q) }, \
         { "accuracy_roll", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_rws_pose_t, accuracy_roll) }, \
         { "accuracy_pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_rws_pose_t, accuracy_pitch) }, \
         { "accuracy_yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 92, offsetof(mavlink_rws_pose_t, accuracy_yaw) }, \
         { "coordinate_frame", NULL, MAVLINK_TYPE_UINT8_T, 0, 96, offsetof(mavlink_rws_pose_t, coordinate_frame) }, \
         } \
}
#endif

/**
 * @brief Pack a rws_pose message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] RWS latitude, WGS84. INT32_MAX if unknown.
 * @param lon [degE7] RWS longitude, WGS84. INT32_MAX if unknown.
 * @param alt [m] RWS altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north component (NED). NaN if unknown.
 * @param vy [m/s] Velocity east component (NED). NaN if unknown.
 * @param vz [m/s] Velocity down component (NED). NaN if unknown.
 * @param cov_pos_x  Position covariance, north axis (m^2). NaN if unknown.
 * @param cov_pos_y  Position covariance, east axis (m^2). NaN if unknown.
 * @param cov_pos_z  Position covariance, down axis (m^2). NaN if unknown.
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2). NaN if unknown.
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2). NaN if unknown.
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2). NaN if unknown.
 * @param offset_x [m] Mounting offset X from vehicle reference point in coordinate_frame.
 * @param offset_y [m] Mounting offset Y from vehicle reference point in coordinate_frame.
 * @param offset_z [m] Mounting offset Z from vehicle reference point in coordinate_frame.
 * @param q  RWS orientation quaternion [w, x, y, z] relative to coordinate_frame.
 * @param accuracy_roll [rad] Roll orientation accuracy (1-sigma).
 * @param accuracy_pitch [rad] Pitch orientation accuracy (1-sigma).
 * @param accuracy_yaw [rad] Yaw orientation accuracy (1-sigma).
 * @param coordinate_frame  Coordinate frame for offset and orientation. See MAV_FRAME.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rws_pose_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, float offset_x, float offset_y, float offset_z, const float *q, float accuracy_roll, float accuracy_pitch, float accuracy_yaw, uint8_t coordinate_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RWS_POSE_LEN];
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
    _mav_put_float(buf, 56, offset_x);
    _mav_put_float(buf, 60, offset_y);
    _mav_put_float(buf, 64, offset_z);
    _mav_put_float(buf, 84, accuracy_roll);
    _mav_put_float(buf, 88, accuracy_pitch);
    _mav_put_float(buf, 92, accuracy_yaw);
    _mav_put_uint8_t(buf, 96, coordinate_frame);
    _mav_put_float_array(buf, 68, q, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RWS_POSE_LEN);
#else
    mavlink_rws_pose_t packet;
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
    packet.offset_x = offset_x;
    packet.offset_y = offset_y;
    packet.offset_z = offset_z;
    packet.accuracy_roll = accuracy_roll;
    packet.accuracy_pitch = accuracy_pitch;
    packet.accuracy_yaw = accuracy_yaw;
    packet.coordinate_frame = coordinate_frame;
    mav_array_memcpy(packet.q, q, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RWS_POSE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RWS_POSE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN, MAVLINK_MSG_ID_RWS_POSE_CRC);
}

/**
 * @brief Pack a rws_pose message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] RWS latitude, WGS84. INT32_MAX if unknown.
 * @param lon [degE7] RWS longitude, WGS84. INT32_MAX if unknown.
 * @param alt [m] RWS altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north component (NED). NaN if unknown.
 * @param vy [m/s] Velocity east component (NED). NaN if unknown.
 * @param vz [m/s] Velocity down component (NED). NaN if unknown.
 * @param cov_pos_x  Position covariance, north axis (m^2). NaN if unknown.
 * @param cov_pos_y  Position covariance, east axis (m^2). NaN if unknown.
 * @param cov_pos_z  Position covariance, down axis (m^2). NaN if unknown.
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2). NaN if unknown.
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2). NaN if unknown.
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2). NaN if unknown.
 * @param offset_x [m] Mounting offset X from vehicle reference point in coordinate_frame.
 * @param offset_y [m] Mounting offset Y from vehicle reference point in coordinate_frame.
 * @param offset_z [m] Mounting offset Z from vehicle reference point in coordinate_frame.
 * @param q  RWS orientation quaternion [w, x, y, z] relative to coordinate_frame.
 * @param accuracy_roll [rad] Roll orientation accuracy (1-sigma).
 * @param accuracy_pitch [rad] Pitch orientation accuracy (1-sigma).
 * @param accuracy_yaw [rad] Yaw orientation accuracy (1-sigma).
 * @param coordinate_frame  Coordinate frame for offset and orientation. See MAV_FRAME.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rws_pose_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, float offset_x, float offset_y, float offset_z, const float *q, float accuracy_roll, float accuracy_pitch, float accuracy_yaw, uint8_t coordinate_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RWS_POSE_LEN];
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
    _mav_put_float(buf, 56, offset_x);
    _mav_put_float(buf, 60, offset_y);
    _mav_put_float(buf, 64, offset_z);
    _mav_put_float(buf, 84, accuracy_roll);
    _mav_put_float(buf, 88, accuracy_pitch);
    _mav_put_float(buf, 92, accuracy_yaw);
    _mav_put_uint8_t(buf, 96, coordinate_frame);
    _mav_put_float_array(buf, 68, q, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RWS_POSE_LEN);
#else
    mavlink_rws_pose_t packet;
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
    packet.offset_x = offset_x;
    packet.offset_y = offset_y;
    packet.offset_z = offset_z;
    packet.accuracy_roll = accuracy_roll;
    packet.accuracy_pitch = accuracy_pitch;
    packet.accuracy_yaw = accuracy_yaw;
    packet.coordinate_frame = coordinate_frame;
    mav_array_memcpy(packet.q, q, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RWS_POSE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RWS_POSE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN, MAVLINK_MSG_ID_RWS_POSE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN);
#endif
}

/**
 * @brief Pack a rws_pose message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] RWS latitude, WGS84. INT32_MAX if unknown.
 * @param lon [degE7] RWS longitude, WGS84. INT32_MAX if unknown.
 * @param alt [m] RWS altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north component (NED). NaN if unknown.
 * @param vy [m/s] Velocity east component (NED). NaN if unknown.
 * @param vz [m/s] Velocity down component (NED). NaN if unknown.
 * @param cov_pos_x  Position covariance, north axis (m^2). NaN if unknown.
 * @param cov_pos_y  Position covariance, east axis (m^2). NaN if unknown.
 * @param cov_pos_z  Position covariance, down axis (m^2). NaN if unknown.
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2). NaN if unknown.
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2). NaN if unknown.
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2). NaN if unknown.
 * @param offset_x [m] Mounting offset X from vehicle reference point in coordinate_frame.
 * @param offset_y [m] Mounting offset Y from vehicle reference point in coordinate_frame.
 * @param offset_z [m] Mounting offset Z from vehicle reference point in coordinate_frame.
 * @param q  RWS orientation quaternion [w, x, y, z] relative to coordinate_frame.
 * @param accuracy_roll [rad] Roll orientation accuracy (1-sigma).
 * @param accuracy_pitch [rad] Pitch orientation accuracy (1-sigma).
 * @param accuracy_yaw [rad] Yaw orientation accuracy (1-sigma).
 * @param coordinate_frame  Coordinate frame for offset and orientation. See MAV_FRAME.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rws_pose_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,int32_t lat,int32_t lon,float alt,float vx,float vy,float vz,float cov_pos_x,float cov_pos_y,float cov_pos_z,float cov_vel_x,float cov_vel_y,float cov_vel_z,float offset_x,float offset_y,float offset_z,const float *q,float accuracy_roll,float accuracy_pitch,float accuracy_yaw,uint8_t coordinate_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RWS_POSE_LEN];
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
    _mav_put_float(buf, 56, offset_x);
    _mav_put_float(buf, 60, offset_y);
    _mav_put_float(buf, 64, offset_z);
    _mav_put_float(buf, 84, accuracy_roll);
    _mav_put_float(buf, 88, accuracy_pitch);
    _mav_put_float(buf, 92, accuracy_yaw);
    _mav_put_uint8_t(buf, 96, coordinate_frame);
    _mav_put_float_array(buf, 68, q, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RWS_POSE_LEN);
#else
    mavlink_rws_pose_t packet;
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
    packet.offset_x = offset_x;
    packet.offset_y = offset_y;
    packet.offset_z = offset_z;
    packet.accuracy_roll = accuracy_roll;
    packet.accuracy_pitch = accuracy_pitch;
    packet.accuracy_yaw = accuracy_yaw;
    packet.coordinate_frame = coordinate_frame;
    mav_array_memcpy(packet.q, q, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RWS_POSE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RWS_POSE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN, MAVLINK_MSG_ID_RWS_POSE_CRC);
}

/**
 * @brief Encode a rws_pose struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rws_pose C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rws_pose_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rws_pose_t* rws_pose)
{
    return mavlink_msg_rws_pose_pack(system_id, component_id, msg, rws_pose->time_usec, rws_pose->lat, rws_pose->lon, rws_pose->alt, rws_pose->vx, rws_pose->vy, rws_pose->vz, rws_pose->cov_pos_x, rws_pose->cov_pos_y, rws_pose->cov_pos_z, rws_pose->cov_vel_x, rws_pose->cov_vel_y, rws_pose->cov_vel_z, rws_pose->offset_x, rws_pose->offset_y, rws_pose->offset_z, rws_pose->q, rws_pose->accuracy_roll, rws_pose->accuracy_pitch, rws_pose->accuracy_yaw, rws_pose->coordinate_frame);
}

/**
 * @brief Encode a rws_pose struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rws_pose C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rws_pose_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_rws_pose_t* rws_pose)
{
    return mavlink_msg_rws_pose_pack_chan(system_id, component_id, chan, msg, rws_pose->time_usec, rws_pose->lat, rws_pose->lon, rws_pose->alt, rws_pose->vx, rws_pose->vy, rws_pose->vz, rws_pose->cov_pos_x, rws_pose->cov_pos_y, rws_pose->cov_pos_z, rws_pose->cov_vel_x, rws_pose->cov_vel_y, rws_pose->cov_vel_z, rws_pose->offset_x, rws_pose->offset_y, rws_pose->offset_z, rws_pose->q, rws_pose->accuracy_roll, rws_pose->accuracy_pitch, rws_pose->accuracy_yaw, rws_pose->coordinate_frame);
}

/**
 * @brief Encode a rws_pose struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param rws_pose C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rws_pose_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_rws_pose_t* rws_pose)
{
    return mavlink_msg_rws_pose_pack_status(system_id, component_id, _status, msg,  rws_pose->time_usec, rws_pose->lat, rws_pose->lon, rws_pose->alt, rws_pose->vx, rws_pose->vy, rws_pose->vz, rws_pose->cov_pos_x, rws_pose->cov_pos_y, rws_pose->cov_pos_z, rws_pose->cov_vel_x, rws_pose->cov_vel_y, rws_pose->cov_vel_z, rws_pose->offset_x, rws_pose->offset_y, rws_pose->offset_z, rws_pose->q, rws_pose->accuracy_roll, rws_pose->accuracy_pitch, rws_pose->accuracy_yaw, rws_pose->coordinate_frame);
}

/**
 * @brief Send a rws_pose message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param lat [degE7] RWS latitude, WGS84. INT32_MAX if unknown.
 * @param lon [degE7] RWS longitude, WGS84. INT32_MAX if unknown.
 * @param alt [m] RWS altitude, MSL. NaN if unknown.
 * @param vx [m/s] Velocity north component (NED). NaN if unknown.
 * @param vy [m/s] Velocity east component (NED). NaN if unknown.
 * @param vz [m/s] Velocity down component (NED). NaN if unknown.
 * @param cov_pos_x  Position covariance, north axis (m^2). NaN if unknown.
 * @param cov_pos_y  Position covariance, east axis (m^2). NaN if unknown.
 * @param cov_pos_z  Position covariance, down axis (m^2). NaN if unknown.
 * @param cov_vel_x  Velocity covariance, north axis (m^2/s^2). NaN if unknown.
 * @param cov_vel_y  Velocity covariance, east axis (m^2/s^2). NaN if unknown.
 * @param cov_vel_z  Velocity covariance, down axis (m^2/s^2). NaN if unknown.
 * @param offset_x [m] Mounting offset X from vehicle reference point in coordinate_frame.
 * @param offset_y [m] Mounting offset Y from vehicle reference point in coordinate_frame.
 * @param offset_z [m] Mounting offset Z from vehicle reference point in coordinate_frame.
 * @param q  RWS orientation quaternion [w, x, y, z] relative to coordinate_frame.
 * @param accuracy_roll [rad] Roll orientation accuracy (1-sigma).
 * @param accuracy_pitch [rad] Pitch orientation accuracy (1-sigma).
 * @param accuracy_yaw [rad] Yaw orientation accuracy (1-sigma).
 * @param coordinate_frame  Coordinate frame for offset and orientation. See MAV_FRAME.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rws_pose_send(mavlink_channel_t chan, uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, float offset_x, float offset_y, float offset_z, const float *q, float accuracy_roll, float accuracy_pitch, float accuracy_yaw, uint8_t coordinate_frame)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RWS_POSE_LEN];
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
    _mav_put_float(buf, 56, offset_x);
    _mav_put_float(buf, 60, offset_y);
    _mav_put_float(buf, 64, offset_z);
    _mav_put_float(buf, 84, accuracy_roll);
    _mav_put_float(buf, 88, accuracy_pitch);
    _mav_put_float(buf, 92, accuracy_yaw);
    _mav_put_uint8_t(buf, 96, coordinate_frame);
    _mav_put_float_array(buf, 68, q, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_POSE, buf, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN, MAVLINK_MSG_ID_RWS_POSE_CRC);
#else
    mavlink_rws_pose_t packet;
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
    packet.offset_x = offset_x;
    packet.offset_y = offset_y;
    packet.offset_z = offset_z;
    packet.accuracy_roll = accuracy_roll;
    packet.accuracy_pitch = accuracy_pitch;
    packet.accuracy_yaw = accuracy_yaw;
    packet.coordinate_frame = coordinate_frame;
    mav_array_memcpy(packet.q, q, sizeof(float)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_POSE, (const char *)&packet, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN, MAVLINK_MSG_ID_RWS_POSE_CRC);
#endif
}

/**
 * @brief Send a rws_pose message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_rws_pose_send_struct(mavlink_channel_t chan, const mavlink_rws_pose_t* rws_pose)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_rws_pose_send(chan, rws_pose->time_usec, rws_pose->lat, rws_pose->lon, rws_pose->alt, rws_pose->vx, rws_pose->vy, rws_pose->vz, rws_pose->cov_pos_x, rws_pose->cov_pos_y, rws_pose->cov_pos_z, rws_pose->cov_vel_x, rws_pose->cov_vel_y, rws_pose->cov_vel_z, rws_pose->offset_x, rws_pose->offset_y, rws_pose->offset_z, rws_pose->q, rws_pose->accuracy_roll, rws_pose->accuracy_pitch, rws_pose->accuracy_yaw, rws_pose->coordinate_frame);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_POSE, (const char *)rws_pose, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN, MAVLINK_MSG_ID_RWS_POSE_CRC);
#endif
}

#if MAVLINK_MSG_ID_RWS_POSE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_rws_pose_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, float offset_x, float offset_y, float offset_z, const float *q, float accuracy_roll, float accuracy_pitch, float accuracy_yaw, uint8_t coordinate_frame)
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
    _mav_put_float(buf, 56, offset_x);
    _mav_put_float(buf, 60, offset_y);
    _mav_put_float(buf, 64, offset_z);
    _mav_put_float(buf, 84, accuracy_roll);
    _mav_put_float(buf, 88, accuracy_pitch);
    _mav_put_float(buf, 92, accuracy_yaw);
    _mav_put_uint8_t(buf, 96, coordinate_frame);
    _mav_put_float_array(buf, 68, q, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_POSE, buf, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN, MAVLINK_MSG_ID_RWS_POSE_CRC);
#else
    mavlink_rws_pose_t *packet = (mavlink_rws_pose_t *)msgbuf;
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
    packet->offset_x = offset_x;
    packet->offset_y = offset_y;
    packet->offset_z = offset_z;
    packet->accuracy_roll = accuracy_roll;
    packet->accuracy_pitch = accuracy_pitch;
    packet->accuracy_yaw = accuracy_yaw;
    packet->coordinate_frame = coordinate_frame;
    mav_array_memcpy(packet->q, q, sizeof(float)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_POSE, (const char *)packet, MAVLINK_MSG_ID_RWS_POSE_MIN_LEN, MAVLINK_MSG_ID_RWS_POSE_LEN, MAVLINK_MSG_ID_RWS_POSE_CRC);
#endif
}
#endif

#endif

// MESSAGE RWS_POSE UNPACKING


/**
 * @brief Get field time_usec from rws_pose message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_rws_pose_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field lat from rws_pose message
 *
 * @return [degE7] RWS latitude, WGS84. INT32_MAX if unknown.
 */
static inline int32_t mavlink_msg_rws_pose_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field lon from rws_pose message
 *
 * @return [degE7] RWS longitude, WGS84. INT32_MAX if unknown.
 */
static inline int32_t mavlink_msg_rws_pose_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field alt from rws_pose message
 *
 * @return [m] RWS altitude, MSL. NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field vx from rws_pose message
 *
 * @return [m/s] Velocity north component (NED). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field vy from rws_pose message
 *
 * @return [m/s] Velocity east component (NED). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field vz from rws_pose message
 *
 * @return [m/s] Velocity down component (NED). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_vz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field cov_pos_x from rws_pose message
 *
 * @return  Position covariance, north axis (m^2). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_cov_pos_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field cov_pos_y from rws_pose message
 *
 * @return  Position covariance, east axis (m^2). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_cov_pos_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field cov_pos_z from rws_pose message
 *
 * @return  Position covariance, down axis (m^2). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_cov_pos_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field cov_vel_x from rws_pose message
 *
 * @return  Velocity covariance, north axis (m^2/s^2). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_cov_vel_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field cov_vel_y from rws_pose message
 *
 * @return  Velocity covariance, east axis (m^2/s^2). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_cov_vel_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field cov_vel_z from rws_pose message
 *
 * @return  Velocity covariance, down axis (m^2/s^2). NaN if unknown.
 */
static inline float mavlink_msg_rws_pose_get_cov_vel_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field offset_x from rws_pose message
 *
 * @return [m] Mounting offset X from vehicle reference point in coordinate_frame.
 */
static inline float mavlink_msg_rws_pose_get_offset_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field offset_y from rws_pose message
 *
 * @return [m] Mounting offset Y from vehicle reference point in coordinate_frame.
 */
static inline float mavlink_msg_rws_pose_get_offset_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field offset_z from rws_pose message
 *
 * @return [m] Mounting offset Z from vehicle reference point in coordinate_frame.
 */
static inline float mavlink_msg_rws_pose_get_offset_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field q from rws_pose message
 *
 * @return  RWS orientation quaternion [w, x, y, z] relative to coordinate_frame.
 */
static inline uint16_t mavlink_msg_rws_pose_get_q(const mavlink_message_t* msg, float *q)
{
    return _MAV_RETURN_float_array(msg, q, 4,  68);
}

/**
 * @brief Get field accuracy_roll from rws_pose message
 *
 * @return [rad] Roll orientation accuracy (1-sigma).
 */
static inline float mavlink_msg_rws_pose_get_accuracy_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  84);
}

/**
 * @brief Get field accuracy_pitch from rws_pose message
 *
 * @return [rad] Pitch orientation accuracy (1-sigma).
 */
static inline float mavlink_msg_rws_pose_get_accuracy_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  88);
}

/**
 * @brief Get field accuracy_yaw from rws_pose message
 *
 * @return [rad] Yaw orientation accuracy (1-sigma).
 */
static inline float mavlink_msg_rws_pose_get_accuracy_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  92);
}

/**
 * @brief Get field coordinate_frame from rws_pose message
 *
 * @return  Coordinate frame for offset and orientation. See MAV_FRAME.
 */
static inline uint8_t mavlink_msg_rws_pose_get_coordinate_frame(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  96);
}

/**
 * @brief Decode a rws_pose message into a struct
 *
 * @param msg The message to decode
 * @param rws_pose C-struct to decode the message contents into
 */
static inline void mavlink_msg_rws_pose_decode(const mavlink_message_t* msg, mavlink_rws_pose_t* rws_pose)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    rws_pose->time_usec = mavlink_msg_rws_pose_get_time_usec(msg);
    rws_pose->lat = mavlink_msg_rws_pose_get_lat(msg);
    rws_pose->lon = mavlink_msg_rws_pose_get_lon(msg);
    rws_pose->alt = mavlink_msg_rws_pose_get_alt(msg);
    rws_pose->vx = mavlink_msg_rws_pose_get_vx(msg);
    rws_pose->vy = mavlink_msg_rws_pose_get_vy(msg);
    rws_pose->vz = mavlink_msg_rws_pose_get_vz(msg);
    rws_pose->cov_pos_x = mavlink_msg_rws_pose_get_cov_pos_x(msg);
    rws_pose->cov_pos_y = mavlink_msg_rws_pose_get_cov_pos_y(msg);
    rws_pose->cov_pos_z = mavlink_msg_rws_pose_get_cov_pos_z(msg);
    rws_pose->cov_vel_x = mavlink_msg_rws_pose_get_cov_vel_x(msg);
    rws_pose->cov_vel_y = mavlink_msg_rws_pose_get_cov_vel_y(msg);
    rws_pose->cov_vel_z = mavlink_msg_rws_pose_get_cov_vel_z(msg);
    rws_pose->offset_x = mavlink_msg_rws_pose_get_offset_x(msg);
    rws_pose->offset_y = mavlink_msg_rws_pose_get_offset_y(msg);
    rws_pose->offset_z = mavlink_msg_rws_pose_get_offset_z(msg);
    mavlink_msg_rws_pose_get_q(msg, rws_pose->q);
    rws_pose->accuracy_roll = mavlink_msg_rws_pose_get_accuracy_roll(msg);
    rws_pose->accuracy_pitch = mavlink_msg_rws_pose_get_accuracy_pitch(msg);
    rws_pose->accuracy_yaw = mavlink_msg_rws_pose_get_accuracy_yaw(msg);
    rws_pose->coordinate_frame = mavlink_msg_rws_pose_get_coordinate_frame(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_RWS_POSE_LEN? msg->len : MAVLINK_MSG_ID_RWS_POSE_LEN;
        memset(rws_pose, 0, MAVLINK_MSG_ID_RWS_POSE_LEN);
    memcpy(rws_pose, _MAV_PAYLOAD(msg), len);
#endif
}
