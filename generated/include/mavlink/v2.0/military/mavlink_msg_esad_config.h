#pragma once
// MESSAGE ESAD_CONFIG PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_ESAD_CONFIG 53032


typedef struct __mavlink_esad_config_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint32_t arming_challenge_hash; /*<  Challenge hash matching the active ESAD_STATE hash for the target store.*/
 uint8_t esad_id; /*<  Vehicle-local ESAD instance identifier to configure. 0 = all ESAD instances selected by store_id, 1-254 = specific ESAD instance, 255 = reserved.*/
 uint8_t store_id; /*<  Target store instance identifier. 0 = all stores / broadcast.*/
 uint8_t trigger_distance_mode; /*<  Requested coarse trigger-distance standoff mode. Coarse selection only.*/
} mavlink_esad_config_t;

#define MAVLINK_MSG_ID_ESAD_CONFIG_LEN 15
#define MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN 15
#define MAVLINK_MSG_ID_53032_LEN 15
#define MAVLINK_MSG_ID_53032_MIN_LEN 15

#define MAVLINK_MSG_ID_ESAD_CONFIG_CRC 216
#define MAVLINK_MSG_ID_53032_CRC 216



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ESAD_CONFIG { \
    53032, \
    "ESAD_CONFIG", \
    5, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_esad_config_t, time_usec) }, \
         { "arming_challenge_hash", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_esad_config_t, arming_challenge_hash) }, \
         { "esad_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_esad_config_t, esad_id) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_esad_config_t, store_id) }, \
         { "trigger_distance_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_esad_config_t, trigger_distance_mode) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ESAD_CONFIG { \
    "ESAD_CONFIG", \
    5, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_esad_config_t, time_usec) }, \
         { "arming_challenge_hash", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_esad_config_t, arming_challenge_hash) }, \
         { "esad_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_esad_config_t, esad_id) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_esad_config_t, store_id) }, \
         { "trigger_distance_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_esad_config_t, trigger_distance_mode) }, \
         } \
}
#endif

/**
 * @brief Pack a esad_config message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash matching the active ESAD_STATE hash for the target store.
 * @param esad_id  Vehicle-local ESAD instance identifier to configure. 0 = all ESAD instances selected by store_id, 1-254 = specific ESAD instance, 255 = reserved.
 * @param store_id  Target store instance identifier. 0 = all stores / broadcast.
 * @param trigger_distance_mode  Requested coarse trigger-distance standoff mode. Coarse selection only.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_config_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t arming_challenge_hash, uint8_t esad_id, uint8_t store_id, uint8_t trigger_distance_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_CONFIG_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, esad_id);
    _mav_put_uint8_t(buf, 13, store_id);
    _mav_put_uint8_t(buf, 14, trigger_distance_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_CONFIG_LEN);
#else
    mavlink_esad_config_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.esad_id = esad_id;
    packet.store_id = store_id;
    packet.trigger_distance_mode = trigger_distance_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_CONFIG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_CONFIG;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_CRC);
}

/**
 * @brief Pack a esad_config message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash matching the active ESAD_STATE hash for the target store.
 * @param esad_id  Vehicle-local ESAD instance identifier to configure. 0 = all ESAD instances selected by store_id, 1-254 = specific ESAD instance, 255 = reserved.
 * @param store_id  Target store instance identifier. 0 = all stores / broadcast.
 * @param trigger_distance_mode  Requested coarse trigger-distance standoff mode. Coarse selection only.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_config_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t arming_challenge_hash, uint8_t esad_id, uint8_t store_id, uint8_t trigger_distance_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_CONFIG_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, esad_id);
    _mav_put_uint8_t(buf, 13, store_id);
    _mav_put_uint8_t(buf, 14, trigger_distance_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_CONFIG_LEN);
#else
    mavlink_esad_config_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.esad_id = esad_id;
    packet.store_id = store_id;
    packet.trigger_distance_mode = trigger_distance_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_CONFIG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_CONFIG;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN);
#endif
}

/**
 * @brief Pack a esad_config message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash matching the active ESAD_STATE hash for the target store.
 * @param esad_id  Vehicle-local ESAD instance identifier to configure. 0 = all ESAD instances selected by store_id, 1-254 = specific ESAD instance, 255 = reserved.
 * @param store_id  Target store instance identifier. 0 = all stores / broadcast.
 * @param trigger_distance_mode  Requested coarse trigger-distance standoff mode. Coarse selection only.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_config_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t arming_challenge_hash,uint8_t esad_id,uint8_t store_id,uint8_t trigger_distance_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_CONFIG_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, esad_id);
    _mav_put_uint8_t(buf, 13, store_id);
    _mav_put_uint8_t(buf, 14, trigger_distance_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_CONFIG_LEN);
#else
    mavlink_esad_config_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.esad_id = esad_id;
    packet.store_id = store_id;
    packet.trigger_distance_mode = trigger_distance_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_CONFIG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_CONFIG;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_CRC);
}

/**
 * @brief Encode a esad_config struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param esad_config C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_config_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_esad_config_t* esad_config)
{
    return mavlink_msg_esad_config_pack(system_id, component_id, msg, esad_config->time_usec, esad_config->arming_challenge_hash, esad_config->esad_id, esad_config->store_id, esad_config->trigger_distance_mode);
}

/**
 * @brief Encode a esad_config struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param esad_config C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_config_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_esad_config_t* esad_config)
{
    return mavlink_msg_esad_config_pack_chan(system_id, component_id, chan, msg, esad_config->time_usec, esad_config->arming_challenge_hash, esad_config->esad_id, esad_config->store_id, esad_config->trigger_distance_mode);
}

/**
 * @brief Encode a esad_config struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param esad_config C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_config_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_esad_config_t* esad_config)
{
    return mavlink_msg_esad_config_pack_status(system_id, component_id, _status, msg,  esad_config->time_usec, esad_config->arming_challenge_hash, esad_config->esad_id, esad_config->store_id, esad_config->trigger_distance_mode);
}

/**
 * @brief Send a esad_config message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash matching the active ESAD_STATE hash for the target store.
 * @param esad_id  Vehicle-local ESAD instance identifier to configure. 0 = all ESAD instances selected by store_id, 1-254 = specific ESAD instance, 255 = reserved.
 * @param store_id  Target store instance identifier. 0 = all stores / broadcast.
 * @param trigger_distance_mode  Requested coarse trigger-distance standoff mode. Coarse selection only.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_esad_config_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t arming_challenge_hash, uint8_t esad_id, uint8_t store_id, uint8_t trigger_distance_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_CONFIG_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, esad_id);
    _mav_put_uint8_t(buf, 13, store_id);
    _mav_put_uint8_t(buf, 14, trigger_distance_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_CONFIG, buf, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_CRC);
#else
    mavlink_esad_config_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.esad_id = esad_id;
    packet.store_id = store_id;
    packet.trigger_distance_mode = trigger_distance_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_CONFIG, (const char *)&packet, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_CRC);
#endif
}

/**
 * @brief Send a esad_config message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_esad_config_send_struct(mavlink_channel_t chan, const mavlink_esad_config_t* esad_config)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_esad_config_send(chan, esad_config->time_usec, esad_config->arming_challenge_hash, esad_config->esad_id, esad_config->store_id, esad_config->trigger_distance_mode);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_CONFIG, (const char *)esad_config, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_CRC);
#endif
}

#if MAVLINK_MSG_ID_ESAD_CONFIG_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_esad_config_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t arming_challenge_hash, uint8_t esad_id, uint8_t store_id, uint8_t trigger_distance_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, esad_id);
    _mav_put_uint8_t(buf, 13, store_id);
    _mav_put_uint8_t(buf, 14, trigger_distance_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_CONFIG, buf, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_CRC);
#else
    mavlink_esad_config_t *packet = (mavlink_esad_config_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->arming_challenge_hash = arming_challenge_hash;
    packet->esad_id = esad_id;
    packet->store_id = store_id;
    packet->trigger_distance_mode = trigger_distance_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_CONFIG, (const char *)packet, MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_LEN, MAVLINK_MSG_ID_ESAD_CONFIG_CRC);
#endif
}
#endif

#endif

// MESSAGE ESAD_CONFIG UNPACKING


/**
 * @brief Get field time_usec from esad_config message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_esad_config_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field arming_challenge_hash from esad_config message
 *
 * @return  Challenge hash matching the active ESAD_STATE hash for the target store.
 */
static inline uint32_t mavlink_msg_esad_config_get_arming_challenge_hash(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field esad_id from esad_config message
 *
 * @return  Vehicle-local ESAD instance identifier to configure. 0 = all ESAD instances selected by store_id, 1-254 = specific ESAD instance, 255 = reserved.
 */
static inline uint8_t mavlink_msg_esad_config_get_esad_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field store_id from esad_config message
 *
 * @return  Target store instance identifier. 0 = all stores / broadcast.
 */
static inline uint8_t mavlink_msg_esad_config_get_store_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field trigger_distance_mode from esad_config message
 *
 * @return  Requested coarse trigger-distance standoff mode. Coarse selection only.
 */
static inline uint8_t mavlink_msg_esad_config_get_trigger_distance_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Decode a esad_config message into a struct
 *
 * @param msg The message to decode
 * @param esad_config C-struct to decode the message contents into
 */
static inline void mavlink_msg_esad_config_decode(const mavlink_message_t* msg, mavlink_esad_config_t* esad_config)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    esad_config->time_usec = mavlink_msg_esad_config_get_time_usec(msg);
    esad_config->arming_challenge_hash = mavlink_msg_esad_config_get_arming_challenge_hash(msg);
    esad_config->esad_id = mavlink_msg_esad_config_get_esad_id(msg);
    esad_config->store_id = mavlink_msg_esad_config_get_store_id(msg);
    esad_config->trigger_distance_mode = mavlink_msg_esad_config_get_trigger_distance_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ESAD_CONFIG_LEN? msg->len : MAVLINK_MSG_ID_ESAD_CONFIG_LEN;
        memset(esad_config, 0, MAVLINK_MSG_ID_ESAD_CONFIG_LEN);
    memcpy(esad_config, _MAV_PAYLOAD(msg), len);
#endif
}
