#pragma once
// MESSAGE SENSOR_TASKING PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_SENSOR_TASKING 53050


typedef struct __mavlink_sensor_tasking_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 int32_t poi_lat; /*< [degE7] Point-of-interest latitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).*/
 int32_t poi_lon; /*< [degE7] Point-of-interest longitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).*/
 float poi_alt; /*< [m] Point-of-interest altitude, MSL. NaN = not provided.*/
 uint16_t task_id; /*<  Tasking correlation id (echoed in the status response).*/
 uint8_t sensor_mode; /*<  Commanded sensor/payload mode.*/
 uint8_t status; /*<  Tasking-status response (ACK/REJECTED/COMPLETE/ACTIVE).*/
} mavlink_sensor_tasking_t;

#define MAVLINK_MSG_ID_SENSOR_TASKING_LEN 24
#define MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN 24
#define MAVLINK_MSG_ID_53050_LEN 24
#define MAVLINK_MSG_ID_53050_MIN_LEN 24

#define MAVLINK_MSG_ID_SENSOR_TASKING_CRC 244
#define MAVLINK_MSG_ID_53050_CRC 244



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SENSOR_TASKING { \
    53050, \
    "SENSOR_TASKING", \
    7, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_sensor_tasking_t, time_usec) }, \
         { "task_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_sensor_tasking_t, task_id) }, \
         { "sensor_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_sensor_tasking_t, sensor_mode) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 23, offsetof(mavlink_sensor_tasking_t, status) }, \
         { "poi_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_sensor_tasking_t, poi_lat) }, \
         { "poi_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_sensor_tasking_t, poi_lon) }, \
         { "poi_alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_sensor_tasking_t, poi_alt) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SENSOR_TASKING { \
    "SENSOR_TASKING", \
    7, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_sensor_tasking_t, time_usec) }, \
         { "task_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_sensor_tasking_t, task_id) }, \
         { "sensor_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_sensor_tasking_t, sensor_mode) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 23, offsetof(mavlink_sensor_tasking_t, status) }, \
         { "poi_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_sensor_tasking_t, poi_lat) }, \
         { "poi_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_sensor_tasking_t, poi_lon) }, \
         { "poi_alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_sensor_tasking_t, poi_alt) }, \
         } \
}
#endif

/**
 * @brief Pack a sensor_tasking message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param task_id  Tasking correlation id (echoed in the status response).
 * @param sensor_mode  Commanded sensor/payload mode.
 * @param status  Tasking-status response (ACK/REJECTED/COMPLETE/ACTIVE).
 * @param poi_lat [degE7] Point-of-interest latitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param poi_lon [degE7] Point-of-interest longitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param poi_alt [m] Point-of-interest altitude, MSL. NaN = not provided.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_tasking_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint16_t task_id, uint8_t sensor_mode, uint8_t status, int32_t poi_lat, int32_t poi_lon, float poi_alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_TASKING_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, poi_lat);
    _mav_put_int32_t(buf, 12, poi_lon);
    _mav_put_float(buf, 16, poi_alt);
    _mav_put_uint16_t(buf, 20, task_id);
    _mav_put_uint8_t(buf, 22, sensor_mode);
    _mav_put_uint8_t(buf, 23, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_TASKING_LEN);
#else
    mavlink_sensor_tasking_t packet;
    packet.time_usec = time_usec;
    packet.poi_lat = poi_lat;
    packet.poi_lon = poi_lon;
    packet.poi_alt = poi_alt;
    packet.task_id = task_id;
    packet.sensor_mode = sensor_mode;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_TASKING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_TASKING;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_CRC);
}

/**
 * @brief Pack a sensor_tasking message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param task_id  Tasking correlation id (echoed in the status response).
 * @param sensor_mode  Commanded sensor/payload mode.
 * @param status  Tasking-status response (ACK/REJECTED/COMPLETE/ACTIVE).
 * @param poi_lat [degE7] Point-of-interest latitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param poi_lon [degE7] Point-of-interest longitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param poi_alt [m] Point-of-interest altitude, MSL. NaN = not provided.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_tasking_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint16_t task_id, uint8_t sensor_mode, uint8_t status, int32_t poi_lat, int32_t poi_lon, float poi_alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_TASKING_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, poi_lat);
    _mav_put_int32_t(buf, 12, poi_lon);
    _mav_put_float(buf, 16, poi_alt);
    _mav_put_uint16_t(buf, 20, task_id);
    _mav_put_uint8_t(buf, 22, sensor_mode);
    _mav_put_uint8_t(buf, 23, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_TASKING_LEN);
#else
    mavlink_sensor_tasking_t packet;
    packet.time_usec = time_usec;
    packet.poi_lat = poi_lat;
    packet.poi_lon = poi_lon;
    packet.poi_alt = poi_alt;
    packet.task_id = task_id;
    packet.sensor_mode = sensor_mode;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_TASKING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_TASKING;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN);
#endif
}

/**
 * @brief Pack a sensor_tasking message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param task_id  Tasking correlation id (echoed in the status response).
 * @param sensor_mode  Commanded sensor/payload mode.
 * @param status  Tasking-status response (ACK/REJECTED/COMPLETE/ACTIVE).
 * @param poi_lat [degE7] Point-of-interest latitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param poi_lon [degE7] Point-of-interest longitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param poi_alt [m] Point-of-interest altitude, MSL. NaN = not provided.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_tasking_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint16_t task_id,uint8_t sensor_mode,uint8_t status,int32_t poi_lat,int32_t poi_lon,float poi_alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_TASKING_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, poi_lat);
    _mav_put_int32_t(buf, 12, poi_lon);
    _mav_put_float(buf, 16, poi_alt);
    _mav_put_uint16_t(buf, 20, task_id);
    _mav_put_uint8_t(buf, 22, sensor_mode);
    _mav_put_uint8_t(buf, 23, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_TASKING_LEN);
#else
    mavlink_sensor_tasking_t packet;
    packet.time_usec = time_usec;
    packet.poi_lat = poi_lat;
    packet.poi_lon = poi_lon;
    packet.poi_alt = poi_alt;
    packet.task_id = task_id;
    packet.sensor_mode = sensor_mode;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_TASKING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_TASKING;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_CRC);
}

/**
 * @brief Encode a sensor_tasking struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param sensor_tasking C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_tasking_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_sensor_tasking_t* sensor_tasking)
{
    return mavlink_msg_sensor_tasking_pack(system_id, component_id, msg, sensor_tasking->time_usec, sensor_tasking->task_id, sensor_tasking->sensor_mode, sensor_tasking->status, sensor_tasking->poi_lat, sensor_tasking->poi_lon, sensor_tasking->poi_alt);
}

/**
 * @brief Encode a sensor_tasking struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sensor_tasking C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_tasking_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_sensor_tasking_t* sensor_tasking)
{
    return mavlink_msg_sensor_tasking_pack_chan(system_id, component_id, chan, msg, sensor_tasking->time_usec, sensor_tasking->task_id, sensor_tasking->sensor_mode, sensor_tasking->status, sensor_tasking->poi_lat, sensor_tasking->poi_lon, sensor_tasking->poi_alt);
}

/**
 * @brief Encode a sensor_tasking struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param sensor_tasking C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_tasking_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_sensor_tasking_t* sensor_tasking)
{
    return mavlink_msg_sensor_tasking_pack_status(system_id, component_id, _status, msg,  sensor_tasking->time_usec, sensor_tasking->task_id, sensor_tasking->sensor_mode, sensor_tasking->status, sensor_tasking->poi_lat, sensor_tasking->poi_lon, sensor_tasking->poi_alt);
}

/**
 * @brief Send a sensor_tasking message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param task_id  Tasking correlation id (echoed in the status response).
 * @param sensor_mode  Commanded sensor/payload mode.
 * @param status  Tasking-status response (ACK/REJECTED/COMPLETE/ACTIVE).
 * @param poi_lat [degE7] Point-of-interest latitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param poi_lon [degE7] Point-of-interest longitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param poi_alt [m] Point-of-interest altitude, MSL. NaN = not provided.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_sensor_tasking_send(mavlink_channel_t chan, uint64_t time_usec, uint16_t task_id, uint8_t sensor_mode, uint8_t status, int32_t poi_lat, int32_t poi_lon, float poi_alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_TASKING_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, poi_lat);
    _mav_put_int32_t(buf, 12, poi_lon);
    _mav_put_float(buf, 16, poi_alt);
    _mav_put_uint16_t(buf, 20, task_id);
    _mav_put_uint8_t(buf, 22, sensor_mode);
    _mav_put_uint8_t(buf, 23, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_TASKING, buf, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_CRC);
#else
    mavlink_sensor_tasking_t packet;
    packet.time_usec = time_usec;
    packet.poi_lat = poi_lat;
    packet.poi_lon = poi_lon;
    packet.poi_alt = poi_alt;
    packet.task_id = task_id;
    packet.sensor_mode = sensor_mode;
    packet.status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_TASKING, (const char *)&packet, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_CRC);
#endif
}

/**
 * @brief Send a sensor_tasking message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_sensor_tasking_send_struct(mavlink_channel_t chan, const mavlink_sensor_tasking_t* sensor_tasking)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_sensor_tasking_send(chan, sensor_tasking->time_usec, sensor_tasking->task_id, sensor_tasking->sensor_mode, sensor_tasking->status, sensor_tasking->poi_lat, sensor_tasking->poi_lon, sensor_tasking->poi_alt);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_TASKING, (const char *)sensor_tasking, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_CRC);
#endif
}

#if MAVLINK_MSG_ID_SENSOR_TASKING_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_sensor_tasking_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint16_t task_id, uint8_t sensor_mode, uint8_t status, int32_t poi_lat, int32_t poi_lon, float poi_alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, poi_lat);
    _mav_put_int32_t(buf, 12, poi_lon);
    _mav_put_float(buf, 16, poi_alt);
    _mav_put_uint16_t(buf, 20, task_id);
    _mav_put_uint8_t(buf, 22, sensor_mode);
    _mav_put_uint8_t(buf, 23, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_TASKING, buf, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_CRC);
#else
    mavlink_sensor_tasking_t *packet = (mavlink_sensor_tasking_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->poi_lat = poi_lat;
    packet->poi_lon = poi_lon;
    packet->poi_alt = poi_alt;
    packet->task_id = task_id;
    packet->sensor_mode = sensor_mode;
    packet->status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_TASKING, (const char *)packet, MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_LEN, MAVLINK_MSG_ID_SENSOR_TASKING_CRC);
#endif
}
#endif

#endif

// MESSAGE SENSOR_TASKING UNPACKING


/**
 * @brief Get field time_usec from sensor_tasking message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_sensor_tasking_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field task_id from sensor_tasking message
 *
 * @return  Tasking correlation id (echoed in the status response).
 */
static inline uint16_t mavlink_msg_sensor_tasking_get_task_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field sensor_mode from sensor_tasking message
 *
 * @return  Commanded sensor/payload mode.
 */
static inline uint8_t mavlink_msg_sensor_tasking_get_sensor_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  22);
}

/**
 * @brief Get field status from sensor_tasking message
 *
 * @return  Tasking-status response (ACK/REJECTED/COMPLETE/ACTIVE).
 */
static inline uint8_t mavlink_msg_sensor_tasking_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  23);
}

/**
 * @brief Get field poi_lat from sensor_tasking message
 *
 * @return [degE7] Point-of-interest latitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 */
static inline int32_t mavlink_msg_sensor_tasking_get_poi_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field poi_lon from sensor_tasking message
 *
 * @return [degE7] Point-of-interest longitude to slew to, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 */
static inline int32_t mavlink_msg_sensor_tasking_get_poi_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field poi_alt from sensor_tasking message
 *
 * @return [m] Point-of-interest altitude, MSL. NaN = not provided.
 */
static inline float mavlink_msg_sensor_tasking_get_poi_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a sensor_tasking message into a struct
 *
 * @param msg The message to decode
 * @param sensor_tasking C-struct to decode the message contents into
 */
static inline void mavlink_msg_sensor_tasking_decode(const mavlink_message_t* msg, mavlink_sensor_tasking_t* sensor_tasking)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    sensor_tasking->time_usec = mavlink_msg_sensor_tasking_get_time_usec(msg);
    sensor_tasking->poi_lat = mavlink_msg_sensor_tasking_get_poi_lat(msg);
    sensor_tasking->poi_lon = mavlink_msg_sensor_tasking_get_poi_lon(msg);
    sensor_tasking->poi_alt = mavlink_msg_sensor_tasking_get_poi_alt(msg);
    sensor_tasking->task_id = mavlink_msg_sensor_tasking_get_task_id(msg);
    sensor_tasking->sensor_mode = mavlink_msg_sensor_tasking_get_sensor_mode(msg);
    sensor_tasking->status = mavlink_msg_sensor_tasking_get_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SENSOR_TASKING_LEN? msg->len : MAVLINK_MSG_ID_SENSOR_TASKING_LEN;
        memset(sensor_tasking, 0, MAVLINK_MSG_ID_SENSOR_TASKING_LEN);
    memcpy(sensor_tasking, _MAV_PAYLOAD(msg), len);
#endif
}
