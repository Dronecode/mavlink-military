#pragma once
// MESSAGE STORE_STATUS PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_STORE_STATUS 53033


typedef struct __mavlink_store_status_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint32_t sensor_fault_mask; /*<  Bitmask of MAVLINK_M_STORE_SENSOR_TYPE values currently NOT healthy (bit = 1<<sensor_type).*/
 uint8_t store_id; /*<  Store instance identifier.*/
 uint8_t store_count; /*<  Total number of stores on the carrier (lets the GCS know how many to expect). 0 if unknown.*/
 uint8_t readiness; /*<  Roll-up release-readiness state.*/
 uint8_t arming_status; /*<  ESAD arming state of this store (mirrored for convenience).*/
 uint8_t sensors_healthy; /*<  Count of sensors reporting OK.*/
 uint8_t sensors_total; /*<  Total count of sensors on this store.*/
} mavlink_store_status_t;

#define MAVLINK_MSG_ID_STORE_STATUS_LEN 18
#define MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN 18
#define MAVLINK_MSG_ID_53033_LEN 18
#define MAVLINK_MSG_ID_53033_MIN_LEN 18

#define MAVLINK_MSG_ID_STORE_STATUS_CRC 75
#define MAVLINK_MSG_ID_53033_CRC 75



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_STORE_STATUS { \
    53033, \
    "STORE_STATUS", \
    8, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_store_status_t, time_usec) }, \
         { "sensor_fault_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_store_status_t, sensor_fault_mask) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_store_status_t, store_id) }, \
         { "store_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_store_status_t, store_count) }, \
         { "readiness", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_store_status_t, readiness) }, \
         { "arming_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 15, offsetof(mavlink_store_status_t, arming_status) }, \
         { "sensors_healthy", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_store_status_t, sensors_healthy) }, \
         { "sensors_total", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_store_status_t, sensors_total) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_STORE_STATUS { \
    "STORE_STATUS", \
    8, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_store_status_t, time_usec) }, \
         { "sensor_fault_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_store_status_t, sensor_fault_mask) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_store_status_t, store_id) }, \
         { "store_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_store_status_t, store_count) }, \
         { "readiness", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_store_status_t, readiness) }, \
         { "arming_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 15, offsetof(mavlink_store_status_t, arming_status) }, \
         { "sensors_healthy", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_store_status_t, sensors_healthy) }, \
         { "sensors_total", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_store_status_t, sensors_total) }, \
         } \
}
#endif

/**
 * @brief Pack a store_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sensor_fault_mask  Bitmask of MAVLINK_M_STORE_SENSOR_TYPE values currently NOT healthy (bit = 1<<sensor_type).
 * @param store_id  Store instance identifier.
 * @param store_count  Total number of stores on the carrier (lets the GCS know how many to expect). 0 if unknown.
 * @param readiness  Roll-up release-readiness state.
 * @param arming_status  ESAD arming state of this store (mirrored for convenience).
 * @param sensors_healthy  Count of sensors reporting OK.
 * @param sensors_total  Total count of sensors on this store.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t sensor_fault_mask, uint8_t store_id, uint8_t store_count, uint8_t readiness, uint8_t arming_status, uint8_t sensors_healthy, uint8_t sensors_total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, sensor_fault_mask);
    _mav_put_uint8_t(buf, 12, store_id);
    _mav_put_uint8_t(buf, 13, store_count);
    _mav_put_uint8_t(buf, 14, readiness);
    _mav_put_uint8_t(buf, 15, arming_status);
    _mav_put_uint8_t(buf, 16, sensors_healthy);
    _mav_put_uint8_t(buf, 17, sensors_total);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_STATUS_LEN);
#else
    mavlink_store_status_t packet;
    packet.time_usec = time_usec;
    packet.sensor_fault_mask = sensor_fault_mask;
    packet.store_id = store_id;
    packet.store_count = store_count;
    packet.readiness = readiness;
    packet.arming_status = arming_status;
    packet.sensors_healthy = sensors_healthy;
    packet.sensors_total = sensors_total;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN, MAVLINK_MSG_ID_STORE_STATUS_CRC);
}

/**
 * @brief Pack a store_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sensor_fault_mask  Bitmask of MAVLINK_M_STORE_SENSOR_TYPE values currently NOT healthy (bit = 1<<sensor_type).
 * @param store_id  Store instance identifier.
 * @param store_count  Total number of stores on the carrier (lets the GCS know how many to expect). 0 if unknown.
 * @param readiness  Roll-up release-readiness state.
 * @param arming_status  ESAD arming state of this store (mirrored for convenience).
 * @param sensors_healthy  Count of sensors reporting OK.
 * @param sensors_total  Total count of sensors on this store.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t sensor_fault_mask, uint8_t store_id, uint8_t store_count, uint8_t readiness, uint8_t arming_status, uint8_t sensors_healthy, uint8_t sensors_total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, sensor_fault_mask);
    _mav_put_uint8_t(buf, 12, store_id);
    _mav_put_uint8_t(buf, 13, store_count);
    _mav_put_uint8_t(buf, 14, readiness);
    _mav_put_uint8_t(buf, 15, arming_status);
    _mav_put_uint8_t(buf, 16, sensors_healthy);
    _mav_put_uint8_t(buf, 17, sensors_total);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_STATUS_LEN);
#else
    mavlink_store_status_t packet;
    packet.time_usec = time_usec;
    packet.sensor_fault_mask = sensor_fault_mask;
    packet.store_id = store_id;
    packet.store_count = store_count;
    packet.readiness = readiness;
    packet.arming_status = arming_status;
    packet.sensors_healthy = sensors_healthy;
    packet.sensors_total = sensors_total;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN, MAVLINK_MSG_ID_STORE_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN);
#endif
}

/**
 * @brief Pack a store_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sensor_fault_mask  Bitmask of MAVLINK_M_STORE_SENSOR_TYPE values currently NOT healthy (bit = 1<<sensor_type).
 * @param store_id  Store instance identifier.
 * @param store_count  Total number of stores on the carrier (lets the GCS know how many to expect). 0 if unknown.
 * @param readiness  Roll-up release-readiness state.
 * @param arming_status  ESAD arming state of this store (mirrored for convenience).
 * @param sensors_healthy  Count of sensors reporting OK.
 * @param sensors_total  Total count of sensors on this store.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t sensor_fault_mask,uint8_t store_id,uint8_t store_count,uint8_t readiness,uint8_t arming_status,uint8_t sensors_healthy,uint8_t sensors_total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, sensor_fault_mask);
    _mav_put_uint8_t(buf, 12, store_id);
    _mav_put_uint8_t(buf, 13, store_count);
    _mav_put_uint8_t(buf, 14, readiness);
    _mav_put_uint8_t(buf, 15, arming_status);
    _mav_put_uint8_t(buf, 16, sensors_healthy);
    _mav_put_uint8_t(buf, 17, sensors_total);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_STATUS_LEN);
#else
    mavlink_store_status_t packet;
    packet.time_usec = time_usec;
    packet.sensor_fault_mask = sensor_fault_mask;
    packet.store_id = store_id;
    packet.store_count = store_count;
    packet.readiness = readiness;
    packet.arming_status = arming_status;
    packet.sensors_healthy = sensors_healthy;
    packet.sensors_total = sensors_total;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN, MAVLINK_MSG_ID_STORE_STATUS_CRC);
}

/**
 * @brief Encode a store_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param store_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_store_status_t* store_status)
{
    return mavlink_msg_store_status_pack(system_id, component_id, msg, store_status->time_usec, store_status->sensor_fault_mask, store_status->store_id, store_status->store_count, store_status->readiness, store_status->arming_status, store_status->sensors_healthy, store_status->sensors_total);
}

/**
 * @brief Encode a store_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param store_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_store_status_t* store_status)
{
    return mavlink_msg_store_status_pack_chan(system_id, component_id, chan, msg, store_status->time_usec, store_status->sensor_fault_mask, store_status->store_id, store_status->store_count, store_status->readiness, store_status->arming_status, store_status->sensors_healthy, store_status->sensors_total);
}

/**
 * @brief Encode a store_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param store_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_store_status_t* store_status)
{
    return mavlink_msg_store_status_pack_status(system_id, component_id, _status, msg,  store_status->time_usec, store_status->sensor_fault_mask, store_status->store_id, store_status->store_count, store_status->readiness, store_status->arming_status, store_status->sensors_healthy, store_status->sensors_total);
}

/**
 * @brief Send a store_status message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sensor_fault_mask  Bitmask of MAVLINK_M_STORE_SENSOR_TYPE values currently NOT healthy (bit = 1<<sensor_type).
 * @param store_id  Store instance identifier.
 * @param store_count  Total number of stores on the carrier (lets the GCS know how many to expect). 0 if unknown.
 * @param readiness  Roll-up release-readiness state.
 * @param arming_status  ESAD arming state of this store (mirrored for convenience).
 * @param sensors_healthy  Count of sensors reporting OK.
 * @param sensors_total  Total count of sensors on this store.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_store_status_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t sensor_fault_mask, uint8_t store_id, uint8_t store_count, uint8_t readiness, uint8_t arming_status, uint8_t sensors_healthy, uint8_t sensors_total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, sensor_fault_mask);
    _mav_put_uint8_t(buf, 12, store_id);
    _mav_put_uint8_t(buf, 13, store_count);
    _mav_put_uint8_t(buf, 14, readiness);
    _mav_put_uint8_t(buf, 15, arming_status);
    _mav_put_uint8_t(buf, 16, sensors_healthy);
    _mav_put_uint8_t(buf, 17, sensors_total);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_STATUS, buf, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN, MAVLINK_MSG_ID_STORE_STATUS_CRC);
#else
    mavlink_store_status_t packet;
    packet.time_usec = time_usec;
    packet.sensor_fault_mask = sensor_fault_mask;
    packet.store_id = store_id;
    packet.store_count = store_count;
    packet.readiness = readiness;
    packet.arming_status = arming_status;
    packet.sensors_healthy = sensors_healthy;
    packet.sensors_total = sensors_total;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_STATUS, (const char *)&packet, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN, MAVLINK_MSG_ID_STORE_STATUS_CRC);
#endif
}

/**
 * @brief Send a store_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_store_status_send_struct(mavlink_channel_t chan, const mavlink_store_status_t* store_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_store_status_send(chan, store_status->time_usec, store_status->sensor_fault_mask, store_status->store_id, store_status->store_count, store_status->readiness, store_status->arming_status, store_status->sensors_healthy, store_status->sensors_total);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_STATUS, (const char *)store_status, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN, MAVLINK_MSG_ID_STORE_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_STORE_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_store_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t sensor_fault_mask, uint8_t store_id, uint8_t store_count, uint8_t readiness, uint8_t arming_status, uint8_t sensors_healthy, uint8_t sensors_total)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, sensor_fault_mask);
    _mav_put_uint8_t(buf, 12, store_id);
    _mav_put_uint8_t(buf, 13, store_count);
    _mav_put_uint8_t(buf, 14, readiness);
    _mav_put_uint8_t(buf, 15, arming_status);
    _mav_put_uint8_t(buf, 16, sensors_healthy);
    _mav_put_uint8_t(buf, 17, sensors_total);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_STATUS, buf, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN, MAVLINK_MSG_ID_STORE_STATUS_CRC);
#else
    mavlink_store_status_t *packet = (mavlink_store_status_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->sensor_fault_mask = sensor_fault_mask;
    packet->store_id = store_id;
    packet->store_count = store_count;
    packet->readiness = readiness;
    packet->arming_status = arming_status;
    packet->sensors_healthy = sensors_healthy;
    packet->sensors_total = sensors_total;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_STATUS, (const char *)packet, MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN, MAVLINK_MSG_ID_STORE_STATUS_LEN, MAVLINK_MSG_ID_STORE_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE STORE_STATUS UNPACKING


/**
 * @brief Get field time_usec from store_status message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_store_status_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field sensor_fault_mask from store_status message
 *
 * @return  Bitmask of MAVLINK_M_STORE_SENSOR_TYPE values currently NOT healthy (bit = 1<<sensor_type).
 */
static inline uint32_t mavlink_msg_store_status_get_sensor_fault_mask(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field store_id from store_status message
 *
 * @return  Store instance identifier.
 */
static inline uint8_t mavlink_msg_store_status_get_store_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field store_count from store_status message
 *
 * @return  Total number of stores on the carrier (lets the GCS know how many to expect). 0 if unknown.
 */
static inline uint8_t mavlink_msg_store_status_get_store_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field readiness from store_status message
 *
 * @return  Roll-up release-readiness state.
 */
static inline uint8_t mavlink_msg_store_status_get_readiness(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field arming_status from store_status message
 *
 * @return  ESAD arming state of this store (mirrored for convenience).
 */
static inline uint8_t mavlink_msg_store_status_get_arming_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  15);
}

/**
 * @brief Get field sensors_healthy from store_status message
 *
 * @return  Count of sensors reporting OK.
 */
static inline uint8_t mavlink_msg_store_status_get_sensors_healthy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field sensors_total from store_status message
 *
 * @return  Total count of sensors on this store.
 */
static inline uint8_t mavlink_msg_store_status_get_sensors_total(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Decode a store_status message into a struct
 *
 * @param msg The message to decode
 * @param store_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_store_status_decode(const mavlink_message_t* msg, mavlink_store_status_t* store_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    store_status->time_usec = mavlink_msg_store_status_get_time_usec(msg);
    store_status->sensor_fault_mask = mavlink_msg_store_status_get_sensor_fault_mask(msg);
    store_status->store_id = mavlink_msg_store_status_get_store_id(msg);
    store_status->store_count = mavlink_msg_store_status_get_store_count(msg);
    store_status->readiness = mavlink_msg_store_status_get_readiness(msg);
    store_status->arming_status = mavlink_msg_store_status_get_arming_status(msg);
    store_status->sensors_healthy = mavlink_msg_store_status_get_sensors_healthy(msg);
    store_status->sensors_total = mavlink_msg_store_status_get_sensors_total(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_STORE_STATUS_LEN? msg->len : MAVLINK_MSG_ID_STORE_STATUS_LEN;
        memset(store_status, 0, MAVLINK_MSG_ID_STORE_STATUS_LEN);
    memcpy(store_status, _MAV_PAYLOAD(msg), len);
#endif
}
