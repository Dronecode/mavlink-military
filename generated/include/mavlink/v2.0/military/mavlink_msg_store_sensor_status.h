#pragma once
// MESSAGE STORE_SENSOR_STATUS PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_STORE_SENSOR_STATUS 53034


typedef struct __mavlink_store_sensor_status_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 float value; /*<  Current sensor reading in the sensor's native units. NaN if invalid.*/
 float value_min; /*<  Lower bound of the valid operating range, native units. NaN if unspecified.*/
 float value_max; /*<  Upper bound of the valid operating range, native units. NaN if unspecified.*/
 uint8_t store_id; /*<  Store instance identifier this sensor belongs to.*/
 uint8_t sensor_type; /*<  Type of sensor.*/
 uint8_t sensor_index; /*<  Index when multiple sensors of the same type exist on a store (0-based).*/
 uint8_t health; /*<  Health state of this sensor.*/
} mavlink_store_sensor_status_t;

#define MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN 24
#define MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN 24
#define MAVLINK_MSG_ID_53034_LEN 24
#define MAVLINK_MSG_ID_53034_MIN_LEN 24

#define MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC 19
#define MAVLINK_MSG_ID_53034_CRC 19



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_STORE_SENSOR_STATUS { \
    53034, \
    "STORE_SENSOR_STATUS", \
    8, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_store_sensor_status_t, time_usec) }, \
         { "value", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_store_sensor_status_t, value) }, \
         { "value_min", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_store_sensor_status_t, value_min) }, \
         { "value_max", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_store_sensor_status_t, value_max) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_store_sensor_status_t, store_id) }, \
         { "sensor_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_store_sensor_status_t, sensor_type) }, \
         { "sensor_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_store_sensor_status_t, sensor_index) }, \
         { "health", NULL, MAVLINK_TYPE_UINT8_T, 0, 23, offsetof(mavlink_store_sensor_status_t, health) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_STORE_SENSOR_STATUS { \
    "STORE_SENSOR_STATUS", \
    8, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_store_sensor_status_t, time_usec) }, \
         { "value", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_store_sensor_status_t, value) }, \
         { "value_min", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_store_sensor_status_t, value_min) }, \
         { "value_max", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_store_sensor_status_t, value_max) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_store_sensor_status_t, store_id) }, \
         { "sensor_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_store_sensor_status_t, sensor_type) }, \
         { "sensor_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_store_sensor_status_t, sensor_index) }, \
         { "health", NULL, MAVLINK_TYPE_UINT8_T, 0, 23, offsetof(mavlink_store_sensor_status_t, health) }, \
         } \
}
#endif

/**
 * @brief Pack a store_sensor_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param value  Current sensor reading in the sensor's native units. NaN if invalid.
 * @param value_min  Lower bound of the valid operating range, native units. NaN if unspecified.
 * @param value_max  Upper bound of the valid operating range, native units. NaN if unspecified.
 * @param store_id  Store instance identifier this sensor belongs to.
 * @param sensor_type  Type of sensor.
 * @param sensor_index  Index when multiple sensors of the same type exist on a store (0-based).
 * @param health  Health state of this sensor.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_sensor_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, float value, float value_min, float value_max, uint8_t store_id, uint8_t sensor_type, uint8_t sensor_index, uint8_t health)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, value);
    _mav_put_float(buf, 12, value_min);
    _mav_put_float(buf, 16, value_max);
    _mav_put_uint8_t(buf, 20, store_id);
    _mav_put_uint8_t(buf, 21, sensor_type);
    _mav_put_uint8_t(buf, 22, sensor_index);
    _mav_put_uint8_t(buf, 23, health);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN);
#else
    mavlink_store_sensor_status_t packet;
    packet.time_usec = time_usec;
    packet.value = value;
    packet.value_min = value_min;
    packet.value_max = value_max;
    packet.store_id = store_id;
    packet.sensor_type = sensor_type;
    packet.sensor_index = sensor_index;
    packet.health = health;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_SENSOR_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC);
}

/**
 * @brief Pack a store_sensor_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param value  Current sensor reading in the sensor's native units. NaN if invalid.
 * @param value_min  Lower bound of the valid operating range, native units. NaN if unspecified.
 * @param value_max  Upper bound of the valid operating range, native units. NaN if unspecified.
 * @param store_id  Store instance identifier this sensor belongs to.
 * @param sensor_type  Type of sensor.
 * @param sensor_index  Index when multiple sensors of the same type exist on a store (0-based).
 * @param health  Health state of this sensor.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_sensor_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, float value, float value_min, float value_max, uint8_t store_id, uint8_t sensor_type, uint8_t sensor_index, uint8_t health)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, value);
    _mav_put_float(buf, 12, value_min);
    _mav_put_float(buf, 16, value_max);
    _mav_put_uint8_t(buf, 20, store_id);
    _mav_put_uint8_t(buf, 21, sensor_type);
    _mav_put_uint8_t(buf, 22, sensor_index);
    _mav_put_uint8_t(buf, 23, health);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN);
#else
    mavlink_store_sensor_status_t packet;
    packet.time_usec = time_usec;
    packet.value = value;
    packet.value_min = value_min;
    packet.value_max = value_max;
    packet.store_id = store_id;
    packet.sensor_type = sensor_type;
    packet.sensor_index = sensor_index;
    packet.health = health;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_SENSOR_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN);
#endif
}

/**
 * @brief Pack a store_sensor_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param value  Current sensor reading in the sensor's native units. NaN if invalid.
 * @param value_min  Lower bound of the valid operating range, native units. NaN if unspecified.
 * @param value_max  Upper bound of the valid operating range, native units. NaN if unspecified.
 * @param store_id  Store instance identifier this sensor belongs to.
 * @param sensor_type  Type of sensor.
 * @param sensor_index  Index when multiple sensors of the same type exist on a store (0-based).
 * @param health  Health state of this sensor.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_sensor_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,float value,float value_min,float value_max,uint8_t store_id,uint8_t sensor_type,uint8_t sensor_index,uint8_t health)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, value);
    _mav_put_float(buf, 12, value_min);
    _mav_put_float(buf, 16, value_max);
    _mav_put_uint8_t(buf, 20, store_id);
    _mav_put_uint8_t(buf, 21, sensor_type);
    _mav_put_uint8_t(buf, 22, sensor_index);
    _mav_put_uint8_t(buf, 23, health);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN);
#else
    mavlink_store_sensor_status_t packet;
    packet.time_usec = time_usec;
    packet.value = value;
    packet.value_min = value_min;
    packet.value_max = value_max;
    packet.store_id = store_id;
    packet.sensor_type = sensor_type;
    packet.sensor_index = sensor_index;
    packet.health = health;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_SENSOR_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC);
}

/**
 * @brief Encode a store_sensor_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param store_sensor_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_sensor_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_store_sensor_status_t* store_sensor_status)
{
    return mavlink_msg_store_sensor_status_pack(system_id, component_id, msg, store_sensor_status->time_usec, store_sensor_status->value, store_sensor_status->value_min, store_sensor_status->value_max, store_sensor_status->store_id, store_sensor_status->sensor_type, store_sensor_status->sensor_index, store_sensor_status->health);
}

/**
 * @brief Encode a store_sensor_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param store_sensor_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_sensor_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_store_sensor_status_t* store_sensor_status)
{
    return mavlink_msg_store_sensor_status_pack_chan(system_id, component_id, chan, msg, store_sensor_status->time_usec, store_sensor_status->value, store_sensor_status->value_min, store_sensor_status->value_max, store_sensor_status->store_id, store_sensor_status->sensor_type, store_sensor_status->sensor_index, store_sensor_status->health);
}

/**
 * @brief Encode a store_sensor_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param store_sensor_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_sensor_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_store_sensor_status_t* store_sensor_status)
{
    return mavlink_msg_store_sensor_status_pack_status(system_id, component_id, _status, msg,  store_sensor_status->time_usec, store_sensor_status->value, store_sensor_status->value_min, store_sensor_status->value_max, store_sensor_status->store_id, store_sensor_status->sensor_type, store_sensor_status->sensor_index, store_sensor_status->health);
}

/**
 * @brief Send a store_sensor_status message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param value  Current sensor reading in the sensor's native units. NaN if invalid.
 * @param value_min  Lower bound of the valid operating range, native units. NaN if unspecified.
 * @param value_max  Upper bound of the valid operating range, native units. NaN if unspecified.
 * @param store_id  Store instance identifier this sensor belongs to.
 * @param sensor_type  Type of sensor.
 * @param sensor_index  Index when multiple sensors of the same type exist on a store (0-based).
 * @param health  Health state of this sensor.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_store_sensor_status_send(mavlink_channel_t chan, uint64_t time_usec, float value, float value_min, float value_max, uint8_t store_id, uint8_t sensor_type, uint8_t sensor_index, uint8_t health)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, value);
    _mav_put_float(buf, 12, value_min);
    _mav_put_float(buf, 16, value_max);
    _mav_put_uint8_t(buf, 20, store_id);
    _mav_put_uint8_t(buf, 21, sensor_type);
    _mav_put_uint8_t(buf, 22, sensor_index);
    _mav_put_uint8_t(buf, 23, health);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_SENSOR_STATUS, buf, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC);
#else
    mavlink_store_sensor_status_t packet;
    packet.time_usec = time_usec;
    packet.value = value;
    packet.value_min = value_min;
    packet.value_max = value_max;
    packet.store_id = store_id;
    packet.sensor_type = sensor_type;
    packet.sensor_index = sensor_index;
    packet.health = health;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_SENSOR_STATUS, (const char *)&packet, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC);
#endif
}

/**
 * @brief Send a store_sensor_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_store_sensor_status_send_struct(mavlink_channel_t chan, const mavlink_store_sensor_status_t* store_sensor_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_store_sensor_status_send(chan, store_sensor_status->time_usec, store_sensor_status->value, store_sensor_status->value_min, store_sensor_status->value_max, store_sensor_status->store_id, store_sensor_status->sensor_type, store_sensor_status->sensor_index, store_sensor_status->health);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_SENSOR_STATUS, (const char *)store_sensor_status, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_store_sensor_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, float value, float value_min, float value_max, uint8_t store_id, uint8_t sensor_type, uint8_t sensor_index, uint8_t health)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, value);
    _mav_put_float(buf, 12, value_min);
    _mav_put_float(buf, 16, value_max);
    _mav_put_uint8_t(buf, 20, store_id);
    _mav_put_uint8_t(buf, 21, sensor_type);
    _mav_put_uint8_t(buf, 22, sensor_index);
    _mav_put_uint8_t(buf, 23, health);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_SENSOR_STATUS, buf, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC);
#else
    mavlink_store_sensor_status_t *packet = (mavlink_store_sensor_status_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->value = value;
    packet->value_min = value_min;
    packet->value_max = value_max;
    packet->store_id = store_id;
    packet->sensor_type = sensor_type;
    packet->sensor_index = sensor_index;
    packet->health = health;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_SENSOR_STATUS, (const char *)packet, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE STORE_SENSOR_STATUS UNPACKING


/**
 * @brief Get field time_usec from store_sensor_status message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_store_sensor_status_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field value from store_sensor_status message
 *
 * @return  Current sensor reading in the sensor's native units. NaN if invalid.
 */
static inline float mavlink_msg_store_sensor_status_get_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field value_min from store_sensor_status message
 *
 * @return  Lower bound of the valid operating range, native units. NaN if unspecified.
 */
static inline float mavlink_msg_store_sensor_status_get_value_min(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field value_max from store_sensor_status message
 *
 * @return  Upper bound of the valid operating range, native units. NaN if unspecified.
 */
static inline float mavlink_msg_store_sensor_status_get_value_max(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field store_id from store_sensor_status message
 *
 * @return  Store instance identifier this sensor belongs to.
 */
static inline uint8_t mavlink_msg_store_sensor_status_get_store_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Get field sensor_type from store_sensor_status message
 *
 * @return  Type of sensor.
 */
static inline uint8_t mavlink_msg_store_sensor_status_get_sensor_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  21);
}

/**
 * @brief Get field sensor_index from store_sensor_status message
 *
 * @return  Index when multiple sensors of the same type exist on a store (0-based).
 */
static inline uint8_t mavlink_msg_store_sensor_status_get_sensor_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  22);
}

/**
 * @brief Get field health from store_sensor_status message
 *
 * @return  Health state of this sensor.
 */
static inline uint8_t mavlink_msg_store_sensor_status_get_health(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  23);
}

/**
 * @brief Decode a store_sensor_status message into a struct
 *
 * @param msg The message to decode
 * @param store_sensor_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_store_sensor_status_decode(const mavlink_message_t* msg, mavlink_store_sensor_status_t* store_sensor_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    store_sensor_status->time_usec = mavlink_msg_store_sensor_status_get_time_usec(msg);
    store_sensor_status->value = mavlink_msg_store_sensor_status_get_value(msg);
    store_sensor_status->value_min = mavlink_msg_store_sensor_status_get_value_min(msg);
    store_sensor_status->value_max = mavlink_msg_store_sensor_status_get_value_max(msg);
    store_sensor_status->store_id = mavlink_msg_store_sensor_status_get_store_id(msg);
    store_sensor_status->sensor_type = mavlink_msg_store_sensor_status_get_sensor_type(msg);
    store_sensor_status->sensor_index = mavlink_msg_store_sensor_status_get_sensor_index(msg);
    store_sensor_status->health = mavlink_msg_store_sensor_status_get_health(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN? msg->len : MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN;
        memset(store_sensor_status, 0, MAVLINK_MSG_ID_STORE_SENSOR_STATUS_LEN);
    memcpy(store_sensor_status, _MAV_PAYLOAD(msg), len);
#endif
}
