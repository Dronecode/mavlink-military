#pragma once
// MESSAGE TARGET_BOX_COORD PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_TARGET_BOX_COORD 53012


typedef struct __mavlink_target_box_coord_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint64_t time_start; /*< [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.*/
 uint64_t time_end; /*< [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.*/
 uint32_t target_set_id; /*<  Unique identifier of the target set.*/
 int32_t lat[4]; /*< [degE7] Corner latitudes, WGS84, clockwise order.*/
 int32_t lon[4]; /*< [degE7] Corner longitudes, WGS84, clockwise order.*/
 float alt[4]; /*< [m] Corner altitudes, MSL.*/
 char target_set_name[50]; /*<  Human-readable name of the target set (null-terminated).*/
} mavlink_target_box_coord_t;

#define MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN 126
#define MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN 126
#define MAVLINK_MSG_ID_53012_LEN 126
#define MAVLINK_MSG_ID_53012_MIN_LEN 126

#define MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC 60
#define MAVLINK_MSG_ID_53012_CRC 60

#define MAVLINK_MSG_TARGET_BOX_COORD_FIELD_LAT_LEN 4
#define MAVLINK_MSG_TARGET_BOX_COORD_FIELD_LON_LEN 4
#define MAVLINK_MSG_TARGET_BOX_COORD_FIELD_ALT_LEN 4
#define MAVLINK_MSG_TARGET_BOX_COORD_FIELD_TARGET_SET_NAME_LEN 50

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TARGET_BOX_COORD { \
    53012, \
    "TARGET_BOX_COORD", \
    8, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_box_coord_t, time_usec) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_target_box_coord_t, target_set_id) }, \
         { "target_set_name", NULL, MAVLINK_TYPE_CHAR, 50, 76, offsetof(mavlink_target_box_coord_t, target_set_name) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 4, 28, offsetof(mavlink_target_box_coord_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 4, 44, offsetof(mavlink_target_box_coord_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 4, 60, offsetof(mavlink_target_box_coord_t, alt) }, \
         { "time_start", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_target_box_coord_t, time_start) }, \
         { "time_end", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_target_box_coord_t, time_end) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TARGET_BOX_COORD { \
    "TARGET_BOX_COORD", \
    8, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_box_coord_t, time_usec) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_target_box_coord_t, target_set_id) }, \
         { "target_set_name", NULL, MAVLINK_TYPE_CHAR, 50, 76, offsetof(mavlink_target_box_coord_t, target_set_name) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 4, 28, offsetof(mavlink_target_box_coord_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 4, 44, offsetof(mavlink_target_box_coord_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 4, 60, offsetof(mavlink_target_box_coord_t, alt) }, \
         { "time_start", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_target_box_coord_t, time_start) }, \
         { "time_end", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_target_box_coord_t, time_end) }, \
         } \
}
#endif

/**
 * @brief Pack a target_box_coord message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Unique identifier of the target set.
 * @param target_set_name  Human-readable name of the target set (null-terminated).
 * @param lat [degE7] Corner latitudes, WGS84, clockwise order.
 * @param lon [degE7] Corner longitudes, WGS84, clockwise order.
 * @param alt [m] Corner altitudes, MSL.
 * @param time_start [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 * @param time_end [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_box_coord_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t target_set_id, const char *target_set_name, const int32_t *lat, const int32_t *lon, const float *alt, uint64_t time_start, uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t_array(buf, 28, lat, 4);
    _mav_put_int32_t_array(buf, 44, lon, 4);
    _mav_put_float_array(buf, 60, alt, 4);
    _mav_put_char_array(buf, 76, target_set_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN);
#else
    mavlink_target_box_coord_t packet;
    packet.time_usec = time_usec;
    packet.time_start = time_start;
    packet.time_end = time_end;
    packet.target_set_id = target_set_id;
    mav_array_memcpy(packet.lat, lat, sizeof(int32_t)*4);
    mav_array_memcpy(packet.lon, lon, sizeof(int32_t)*4);
    mav_array_memcpy(packet.alt, alt, sizeof(float)*4);
    mav_array_memcpy(packet.target_set_name, target_set_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_BOX_COORD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC);
}

/**
 * @brief Pack a target_box_coord message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Unique identifier of the target set.
 * @param target_set_name  Human-readable name of the target set (null-terminated).
 * @param lat [degE7] Corner latitudes, WGS84, clockwise order.
 * @param lon [degE7] Corner longitudes, WGS84, clockwise order.
 * @param alt [m] Corner altitudes, MSL.
 * @param time_start [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 * @param time_end [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_box_coord_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t target_set_id, const char *target_set_name, const int32_t *lat, const int32_t *lon, const float *alt, uint64_t time_start, uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t_array(buf, 28, lat, 4);
    _mav_put_int32_t_array(buf, 44, lon, 4);
    _mav_put_float_array(buf, 60, alt, 4);
    _mav_put_char_array(buf, 76, target_set_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN);
#else
    mavlink_target_box_coord_t packet;
    packet.time_usec = time_usec;
    packet.time_start = time_start;
    packet.time_end = time_end;
    packet.target_set_id = target_set_id;
    mav_array_memcpy(packet.lat, lat, sizeof(int32_t)*4);
    mav_array_memcpy(packet.lon, lon, sizeof(int32_t)*4);
    mav_array_memcpy(packet.alt, alt, sizeof(float)*4);
    mav_array_memcpy(packet.target_set_name, target_set_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_BOX_COORD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN);
#endif
}

/**
 * @brief Pack a target_box_coord message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Unique identifier of the target set.
 * @param target_set_name  Human-readable name of the target set (null-terminated).
 * @param lat [degE7] Corner latitudes, WGS84, clockwise order.
 * @param lon [degE7] Corner longitudes, WGS84, clockwise order.
 * @param alt [m] Corner altitudes, MSL.
 * @param time_start [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 * @param time_end [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_box_coord_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t target_set_id,const char *target_set_name,const int32_t *lat,const int32_t *lon,const float *alt,uint64_t time_start,uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t_array(buf, 28, lat, 4);
    _mav_put_int32_t_array(buf, 44, lon, 4);
    _mav_put_float_array(buf, 60, alt, 4);
    _mav_put_char_array(buf, 76, target_set_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN);
#else
    mavlink_target_box_coord_t packet;
    packet.time_usec = time_usec;
    packet.time_start = time_start;
    packet.time_end = time_end;
    packet.target_set_id = target_set_id;
    mav_array_memcpy(packet.lat, lat, sizeof(int32_t)*4);
    mav_array_memcpy(packet.lon, lon, sizeof(int32_t)*4);
    mav_array_memcpy(packet.alt, alt, sizeof(float)*4);
    mav_array_memcpy(packet.target_set_name, target_set_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_BOX_COORD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC);
}

/**
 * @brief Encode a target_box_coord struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param target_box_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_box_coord_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_target_box_coord_t* target_box_coord)
{
    return mavlink_msg_target_box_coord_pack(system_id, component_id, msg, target_box_coord->time_usec, target_box_coord->target_set_id, target_box_coord->target_set_name, target_box_coord->lat, target_box_coord->lon, target_box_coord->alt, target_box_coord->time_start, target_box_coord->time_end);
}

/**
 * @brief Encode a target_box_coord struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_box_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_box_coord_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_target_box_coord_t* target_box_coord)
{
    return mavlink_msg_target_box_coord_pack_chan(system_id, component_id, chan, msg, target_box_coord->time_usec, target_box_coord->target_set_id, target_box_coord->target_set_name, target_box_coord->lat, target_box_coord->lon, target_box_coord->alt, target_box_coord->time_start, target_box_coord->time_end);
}

/**
 * @brief Encode a target_box_coord struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param target_box_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_box_coord_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_target_box_coord_t* target_box_coord)
{
    return mavlink_msg_target_box_coord_pack_status(system_id, component_id, _status, msg,  target_box_coord->time_usec, target_box_coord->target_set_id, target_box_coord->target_set_name, target_box_coord->lat, target_box_coord->lon, target_box_coord->alt, target_box_coord->time_start, target_box_coord->time_end);
}

/**
 * @brief Send a target_box_coord message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Unique identifier of the target set.
 * @param target_set_name  Human-readable name of the target set (null-terminated).
 * @param lat [degE7] Corner latitudes, WGS84, clockwise order.
 * @param lon [degE7] Corner longitudes, WGS84, clockwise order.
 * @param alt [m] Corner altitudes, MSL.
 * @param time_start [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 * @param time_end [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_target_box_coord_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t target_set_id, const char *target_set_name, const int32_t *lat, const int32_t *lon, const float *alt, uint64_t time_start, uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t_array(buf, 28, lat, 4);
    _mav_put_int32_t_array(buf, 44, lon, 4);
    _mav_put_float_array(buf, 60, alt, 4);
    _mav_put_char_array(buf, 76, target_set_name, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_BOX_COORD, buf, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC);
#else
    mavlink_target_box_coord_t packet;
    packet.time_usec = time_usec;
    packet.time_start = time_start;
    packet.time_end = time_end;
    packet.target_set_id = target_set_id;
    mav_array_memcpy(packet.lat, lat, sizeof(int32_t)*4);
    mav_array_memcpy(packet.lon, lon, sizeof(int32_t)*4);
    mav_array_memcpy(packet.alt, alt, sizeof(float)*4);
    mav_array_memcpy(packet.target_set_name, target_set_name, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_BOX_COORD, (const char *)&packet, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC);
#endif
}

/**
 * @brief Send a target_box_coord message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_target_box_coord_send_struct(mavlink_channel_t chan, const mavlink_target_box_coord_t* target_box_coord)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_target_box_coord_send(chan, target_box_coord->time_usec, target_box_coord->target_set_id, target_box_coord->target_set_name, target_box_coord->lat, target_box_coord->lon, target_box_coord->alt, target_box_coord->time_start, target_box_coord->time_end);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_BOX_COORD, (const char *)target_box_coord, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC);
#endif
}

#if MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_target_box_coord_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t target_set_id, const char *target_set_name, const int32_t *lat, const int32_t *lon, const float *alt, uint64_t time_start, uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t_array(buf, 28, lat, 4);
    _mav_put_int32_t_array(buf, 44, lon, 4);
    _mav_put_float_array(buf, 60, alt, 4);
    _mav_put_char_array(buf, 76, target_set_name, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_BOX_COORD, buf, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC);
#else
    mavlink_target_box_coord_t *packet = (mavlink_target_box_coord_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->time_start = time_start;
    packet->time_end = time_end;
    packet->target_set_id = target_set_id;
    mav_array_memcpy(packet->lat, lat, sizeof(int32_t)*4);
    mav_array_memcpy(packet->lon, lon, sizeof(int32_t)*4);
    mav_array_memcpy(packet->alt, alt, sizeof(float)*4);
    mav_array_memcpy(packet->target_set_name, target_set_name, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_BOX_COORD, (const char *)packet, MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN, MAVLINK_MSG_ID_TARGET_BOX_COORD_CRC);
#endif
}
#endif

#endif

// MESSAGE TARGET_BOX_COORD UNPACKING


/**
 * @brief Get field time_usec from target_box_coord message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_box_coord_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field target_set_id from target_box_coord message
 *
 * @return  Unique identifier of the target set.
 */
static inline uint32_t mavlink_msg_target_box_coord_get_target_set_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field target_set_name from target_box_coord message
 *
 * @return  Human-readable name of the target set (null-terminated).
 */
static inline uint16_t mavlink_msg_target_box_coord_get_target_set_name(const mavlink_message_t* msg, char *target_set_name)
{
    return _MAV_RETURN_char_array(msg, target_set_name, 50,  76);
}

/**
 * @brief Get field lat from target_box_coord message
 *
 * @return [degE7] Corner latitudes, WGS84, clockwise order.
 */
static inline uint16_t mavlink_msg_target_box_coord_get_lat(const mavlink_message_t* msg, int32_t *lat)
{
    return _MAV_RETURN_int32_t_array(msg, lat, 4,  28);
}

/**
 * @brief Get field lon from target_box_coord message
 *
 * @return [degE7] Corner longitudes, WGS84, clockwise order.
 */
static inline uint16_t mavlink_msg_target_box_coord_get_lon(const mavlink_message_t* msg, int32_t *lon)
{
    return _MAV_RETURN_int32_t_array(msg, lon, 4,  44);
}

/**
 * @brief Get field alt from target_box_coord message
 *
 * @return [m] Corner altitudes, MSL.
 */
static inline uint16_t mavlink_msg_target_box_coord_get_alt(const mavlink_message_t* msg, float *alt)
{
    return _MAV_RETURN_float_array(msg, alt, 4,  60);
}

/**
 * @brief Get field time_start from target_box_coord message
 *
 * @return [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 */
static inline uint64_t mavlink_msg_target_box_coord_get_time_start(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field time_end from target_box_coord message
 *
 * @return [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 */
static inline uint64_t mavlink_msg_target_box_coord_get_time_end(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Decode a target_box_coord message into a struct
 *
 * @param msg The message to decode
 * @param target_box_coord C-struct to decode the message contents into
 */
static inline void mavlink_msg_target_box_coord_decode(const mavlink_message_t* msg, mavlink_target_box_coord_t* target_box_coord)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    target_box_coord->time_usec = mavlink_msg_target_box_coord_get_time_usec(msg);
    target_box_coord->time_start = mavlink_msg_target_box_coord_get_time_start(msg);
    target_box_coord->time_end = mavlink_msg_target_box_coord_get_time_end(msg);
    target_box_coord->target_set_id = mavlink_msg_target_box_coord_get_target_set_id(msg);
    mavlink_msg_target_box_coord_get_lat(msg, target_box_coord->lat);
    mavlink_msg_target_box_coord_get_lon(msg, target_box_coord->lon);
    mavlink_msg_target_box_coord_get_alt(msg, target_box_coord->alt);
    mavlink_msg_target_box_coord_get_target_set_name(msg, target_box_coord->target_set_name);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN? msg->len : MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN;
        memset(target_box_coord, 0, MAVLINK_MSG_ID_TARGET_BOX_COORD_LEN);
    memcpy(target_box_coord, _MAV_PAYLOAD(msg), len);
#endif
}
