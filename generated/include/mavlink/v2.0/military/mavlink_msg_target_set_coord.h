#pragma once
// MESSAGE TARGET_SET_COORD PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_TARGET_SET_COORD 53011


typedef struct __mavlink_target_set_coord_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint64_t time_start; /*< [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.*/
 uint64_t time_end; /*< [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.*/
 uint32_t target_set_id; /*<  Unique identifier of the target set.*/
 int32_t lat; /*< [degE7] Centroid latitude, WGS84.*/
 int32_t lon; /*< [degE7] Centroid longitude, WGS84.*/
 float alt; /*< [m] Centroid altitude, MSL.*/
 float radius; /*< [m] Radius of the circular target set area.*/
 char target_set_name[50]; /*<  Human-readable name of the target set (null-terminated).*/
} mavlink_target_set_coord_t;

#define MAVLINK_MSG_ID_TARGET_SET_COORD_LEN 94
#define MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN 94
#define MAVLINK_MSG_ID_53011_LEN 94
#define MAVLINK_MSG_ID_53011_MIN_LEN 94

#define MAVLINK_MSG_ID_TARGET_SET_COORD_CRC 77
#define MAVLINK_MSG_ID_53011_CRC 77

#define MAVLINK_MSG_TARGET_SET_COORD_FIELD_TARGET_SET_NAME_LEN 50

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TARGET_SET_COORD { \
    53011, \
    "TARGET_SET_COORD", \
    9, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_set_coord_t, time_usec) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_target_set_coord_t, target_set_id) }, \
         { "target_set_name", NULL, MAVLINK_TYPE_CHAR, 50, 44, offsetof(mavlink_target_set_coord_t, target_set_name) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_target_set_coord_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 32, offsetof(mavlink_target_set_coord_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_set_coord_t, alt) }, \
         { "radius", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_target_set_coord_t, radius) }, \
         { "time_start", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_target_set_coord_t, time_start) }, \
         { "time_end", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_target_set_coord_t, time_end) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TARGET_SET_COORD { \
    "TARGET_SET_COORD", \
    9, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_set_coord_t, time_usec) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_target_set_coord_t, target_set_id) }, \
         { "target_set_name", NULL, MAVLINK_TYPE_CHAR, 50, 44, offsetof(mavlink_target_set_coord_t, target_set_name) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_target_set_coord_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 32, offsetof(mavlink_target_set_coord_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_set_coord_t, alt) }, \
         { "radius", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_target_set_coord_t, radius) }, \
         { "time_start", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_target_set_coord_t, time_start) }, \
         { "time_end", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_target_set_coord_t, time_end) }, \
         } \
}
#endif

/**
 * @brief Pack a target_set_coord message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Unique identifier of the target set.
 * @param target_set_name  Human-readable name of the target set (null-terminated).
 * @param lat [degE7] Centroid latitude, WGS84.
 * @param lon [degE7] Centroid longitude, WGS84.
 * @param alt [m] Centroid altitude, MSL.
 * @param radius [m] Radius of the circular target set area.
 * @param time_start [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 * @param time_end [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_set_coord_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t target_set_id, const char *target_set_name, int32_t lat, int32_t lon, float alt, float radius, uint64_t time_start, uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_SET_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t(buf, 28, lat);
    _mav_put_int32_t(buf, 32, lon);
    _mav_put_float(buf, 36, alt);
    _mav_put_float(buf, 40, radius);
    _mav_put_char_array(buf, 44, target_set_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN);
#else
    mavlink_target_set_coord_t packet;
    packet.time_usec = time_usec;
    packet.time_start = time_start;
    packet.time_end = time_end;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.radius = radius;
    mav_array_memcpy(packet.target_set_name, target_set_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_SET_COORD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_CRC);
}

/**
 * @brief Pack a target_set_coord message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Unique identifier of the target set.
 * @param target_set_name  Human-readable name of the target set (null-terminated).
 * @param lat [degE7] Centroid latitude, WGS84.
 * @param lon [degE7] Centroid longitude, WGS84.
 * @param alt [m] Centroid altitude, MSL.
 * @param radius [m] Radius of the circular target set area.
 * @param time_start [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 * @param time_end [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_set_coord_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t target_set_id, const char *target_set_name, int32_t lat, int32_t lon, float alt, float radius, uint64_t time_start, uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_SET_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t(buf, 28, lat);
    _mav_put_int32_t(buf, 32, lon);
    _mav_put_float(buf, 36, alt);
    _mav_put_float(buf, 40, radius);
    _mav_put_char_array(buf, 44, target_set_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN);
#else
    mavlink_target_set_coord_t packet;
    packet.time_usec = time_usec;
    packet.time_start = time_start;
    packet.time_end = time_end;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.radius = radius;
    mav_array_memcpy(packet.target_set_name, target_set_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_SET_COORD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN);
#endif
}

/**
 * @brief Pack a target_set_coord message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Unique identifier of the target set.
 * @param target_set_name  Human-readable name of the target set (null-terminated).
 * @param lat [degE7] Centroid latitude, WGS84.
 * @param lon [degE7] Centroid longitude, WGS84.
 * @param alt [m] Centroid altitude, MSL.
 * @param radius [m] Radius of the circular target set area.
 * @param time_start [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 * @param time_end [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_set_coord_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t target_set_id,const char *target_set_name,int32_t lat,int32_t lon,float alt,float radius,uint64_t time_start,uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_SET_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t(buf, 28, lat);
    _mav_put_int32_t(buf, 32, lon);
    _mav_put_float(buf, 36, alt);
    _mav_put_float(buf, 40, radius);
    _mav_put_char_array(buf, 44, target_set_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN);
#else
    mavlink_target_set_coord_t packet;
    packet.time_usec = time_usec;
    packet.time_start = time_start;
    packet.time_end = time_end;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.radius = radius;
    mav_array_memcpy(packet.target_set_name, target_set_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_SET_COORD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_CRC);
}

/**
 * @brief Encode a target_set_coord struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param target_set_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_set_coord_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_target_set_coord_t* target_set_coord)
{
    return mavlink_msg_target_set_coord_pack(system_id, component_id, msg, target_set_coord->time_usec, target_set_coord->target_set_id, target_set_coord->target_set_name, target_set_coord->lat, target_set_coord->lon, target_set_coord->alt, target_set_coord->radius, target_set_coord->time_start, target_set_coord->time_end);
}

/**
 * @brief Encode a target_set_coord struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_set_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_set_coord_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_target_set_coord_t* target_set_coord)
{
    return mavlink_msg_target_set_coord_pack_chan(system_id, component_id, chan, msg, target_set_coord->time_usec, target_set_coord->target_set_id, target_set_coord->target_set_name, target_set_coord->lat, target_set_coord->lon, target_set_coord->alt, target_set_coord->radius, target_set_coord->time_start, target_set_coord->time_end);
}

/**
 * @brief Encode a target_set_coord struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param target_set_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_set_coord_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_target_set_coord_t* target_set_coord)
{
    return mavlink_msg_target_set_coord_pack_status(system_id, component_id, _status, msg,  target_set_coord->time_usec, target_set_coord->target_set_id, target_set_coord->target_set_name, target_set_coord->lat, target_set_coord->lon, target_set_coord->alt, target_set_coord->radius, target_set_coord->time_start, target_set_coord->time_end);
}

/**
 * @brief Send a target_set_coord message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Unique identifier of the target set.
 * @param target_set_name  Human-readable name of the target set (null-terminated).
 * @param lat [degE7] Centroid latitude, WGS84.
 * @param lon [degE7] Centroid longitude, WGS84.
 * @param alt [m] Centroid altitude, MSL.
 * @param radius [m] Radius of the circular target set area.
 * @param time_start [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 * @param time_end [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_target_set_coord_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t target_set_id, const char *target_set_name, int32_t lat, int32_t lon, float alt, float radius, uint64_t time_start, uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_SET_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t(buf, 28, lat);
    _mav_put_int32_t(buf, 32, lon);
    _mav_put_float(buf, 36, alt);
    _mav_put_float(buf, 40, radius);
    _mav_put_char_array(buf, 44, target_set_name, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_SET_COORD, buf, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_CRC);
#else
    mavlink_target_set_coord_t packet;
    packet.time_usec = time_usec;
    packet.time_start = time_start;
    packet.time_end = time_end;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.radius = radius;
    mav_array_memcpy(packet.target_set_name, target_set_name, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_SET_COORD, (const char *)&packet, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_CRC);
#endif
}

/**
 * @brief Send a target_set_coord message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_target_set_coord_send_struct(mavlink_channel_t chan, const mavlink_target_set_coord_t* target_set_coord)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_target_set_coord_send(chan, target_set_coord->time_usec, target_set_coord->target_set_id, target_set_coord->target_set_name, target_set_coord->lat, target_set_coord->lon, target_set_coord->alt, target_set_coord->radius, target_set_coord->time_start, target_set_coord->time_end);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_SET_COORD, (const char *)target_set_coord, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_CRC);
#endif
}

#if MAVLINK_MSG_ID_TARGET_SET_COORD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_target_set_coord_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t target_set_id, const char *target_set_name, int32_t lat, int32_t lon, float alt, float radius, uint64_t time_start, uint64_t time_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_start);
    _mav_put_uint64_t(buf, 16, time_end);
    _mav_put_uint32_t(buf, 24, target_set_id);
    _mav_put_int32_t(buf, 28, lat);
    _mav_put_int32_t(buf, 32, lon);
    _mav_put_float(buf, 36, alt);
    _mav_put_float(buf, 40, radius);
    _mav_put_char_array(buf, 44, target_set_name, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_SET_COORD, buf, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_CRC);
#else
    mavlink_target_set_coord_t *packet = (mavlink_target_set_coord_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->time_start = time_start;
    packet->time_end = time_end;
    packet->target_set_id = target_set_id;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->radius = radius;
    mav_array_memcpy(packet->target_set_name, target_set_name, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_SET_COORD, (const char *)packet, MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN, MAVLINK_MSG_ID_TARGET_SET_COORD_CRC);
#endif
}
#endif

#endif

// MESSAGE TARGET_SET_COORD UNPACKING


/**
 * @brief Get field time_usec from target_set_coord message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_set_coord_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field target_set_id from target_set_coord message
 *
 * @return  Unique identifier of the target set.
 */
static inline uint32_t mavlink_msg_target_set_coord_get_target_set_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field target_set_name from target_set_coord message
 *
 * @return  Human-readable name of the target set (null-terminated).
 */
static inline uint16_t mavlink_msg_target_set_coord_get_target_set_name(const mavlink_message_t* msg, char *target_set_name)
{
    return _MAV_RETURN_char_array(msg, target_set_name, 50,  44);
}

/**
 * @brief Get field lat from target_set_coord message
 *
 * @return [degE7] Centroid latitude, WGS84.
 */
static inline int32_t mavlink_msg_target_set_coord_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  28);
}

/**
 * @brief Get field lon from target_set_coord message
 *
 * @return [degE7] Centroid longitude, WGS84.
 */
static inline int32_t mavlink_msg_target_set_coord_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  32);
}

/**
 * @brief Get field alt from target_set_coord message
 *
 * @return [m] Centroid altitude, MSL.
 */
static inline float mavlink_msg_target_set_coord_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field radius from target_set_coord message
 *
 * @return [m] Radius of the circular target set area.
 */
static inline float mavlink_msg_target_set_coord_get_radius(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field time_start from target_set_coord message
 *
 * @return [us] Area validity start time (UNIX epoch, microseconds UTC). 0 = immediate.
 */
static inline uint64_t mavlink_msg_target_set_coord_get_time_start(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field time_end from target_set_coord message
 *
 * @return [us] Area validity end time (UNIX epoch, microseconds UTC). 0 = indefinite.
 */
static inline uint64_t mavlink_msg_target_set_coord_get_time_end(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Decode a target_set_coord message into a struct
 *
 * @param msg The message to decode
 * @param target_set_coord C-struct to decode the message contents into
 */
static inline void mavlink_msg_target_set_coord_decode(const mavlink_message_t* msg, mavlink_target_set_coord_t* target_set_coord)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    target_set_coord->time_usec = mavlink_msg_target_set_coord_get_time_usec(msg);
    target_set_coord->time_start = mavlink_msg_target_set_coord_get_time_start(msg);
    target_set_coord->time_end = mavlink_msg_target_set_coord_get_time_end(msg);
    target_set_coord->target_set_id = mavlink_msg_target_set_coord_get_target_set_id(msg);
    target_set_coord->lat = mavlink_msg_target_set_coord_get_lat(msg);
    target_set_coord->lon = mavlink_msg_target_set_coord_get_lon(msg);
    target_set_coord->alt = mavlink_msg_target_set_coord_get_alt(msg);
    target_set_coord->radius = mavlink_msg_target_set_coord_get_radius(msg);
    mavlink_msg_target_set_coord_get_target_set_name(msg, target_set_coord->target_set_name);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TARGET_SET_COORD_LEN? msg->len : MAVLINK_MSG_ID_TARGET_SET_COORD_LEN;
        memset(target_set_coord, 0, MAVLINK_MSG_ID_TARGET_SET_COORD_LEN);
    memcpy(target_set_coord, _MAV_PAYLOAD(msg), len);
#endif
}
