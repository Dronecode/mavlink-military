#pragma once
// MESSAGE RWS_STATE PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_RWS_STATE 53041


typedef struct __mavlink_rws_state_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 char weapon_string[50]; /*<  Human-readable weapon description or designation (null-terminated).*/
 uint8_t arming_state; /*<  Current arming state of the weapon system.*/
 uint8_t weapon_type; /*<  Weapon type identifier (implementation-defined).*/
} mavlink_rws_state_t;

#define MAVLINK_MSG_ID_RWS_STATE_LEN 60
#define MAVLINK_MSG_ID_RWS_STATE_MIN_LEN 60
#define MAVLINK_MSG_ID_53041_LEN 60
#define MAVLINK_MSG_ID_53041_MIN_LEN 60

#define MAVLINK_MSG_ID_RWS_STATE_CRC 175
#define MAVLINK_MSG_ID_53041_CRC 175

#define MAVLINK_MSG_RWS_STATE_FIELD_WEAPON_STRING_LEN 50

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_RWS_STATE { \
    53041, \
    "RWS_STATE", \
    4, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rws_state_t, time_usec) }, \
         { "weapon_string", NULL, MAVLINK_TYPE_CHAR, 50, 8, offsetof(mavlink_rws_state_t, weapon_string) }, \
         { "arming_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 58, offsetof(mavlink_rws_state_t, arming_state) }, \
         { "weapon_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 59, offsetof(mavlink_rws_state_t, weapon_type) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_RWS_STATE { \
    "RWS_STATE", \
    4, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rws_state_t, time_usec) }, \
         { "weapon_string", NULL, MAVLINK_TYPE_CHAR, 50, 8, offsetof(mavlink_rws_state_t, weapon_string) }, \
         { "arming_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 58, offsetof(mavlink_rws_state_t, arming_state) }, \
         { "weapon_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 59, offsetof(mavlink_rws_state_t, weapon_type) }, \
         } \
}
#endif

/**
 * @brief Pack a rws_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param weapon_string  Human-readable weapon description or designation (null-terminated).
 * @param arming_state  Current arming state of the weapon system.
 * @param weapon_type  Weapon type identifier (implementation-defined).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rws_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, const char *weapon_string, uint8_t arming_state, uint8_t weapon_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RWS_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint8_t(buf, 58, arming_state);
    _mav_put_uint8_t(buf, 59, weapon_type);
    _mav_put_char_array(buf, 8, weapon_string, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RWS_STATE_LEN);
#else
    mavlink_rws_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_state = arming_state;
    packet.weapon_type = weapon_type;
    mav_array_memcpy(packet.weapon_string, weapon_string, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RWS_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RWS_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN, MAVLINK_MSG_ID_RWS_STATE_CRC);
}

/**
 * @brief Pack a rws_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param weapon_string  Human-readable weapon description or designation (null-terminated).
 * @param arming_state  Current arming state of the weapon system.
 * @param weapon_type  Weapon type identifier (implementation-defined).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rws_state_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, const char *weapon_string, uint8_t arming_state, uint8_t weapon_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RWS_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint8_t(buf, 58, arming_state);
    _mav_put_uint8_t(buf, 59, weapon_type);
    _mav_put_char_array(buf, 8, weapon_string, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RWS_STATE_LEN);
#else
    mavlink_rws_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_state = arming_state;
    packet.weapon_type = weapon_type;
    mav_array_memcpy(packet.weapon_string, weapon_string, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RWS_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RWS_STATE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN, MAVLINK_MSG_ID_RWS_STATE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN);
#endif
}

/**
 * @brief Pack a rws_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param weapon_string  Human-readable weapon description or designation (null-terminated).
 * @param arming_state  Current arming state of the weapon system.
 * @param weapon_type  Weapon type identifier (implementation-defined).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rws_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,const char *weapon_string,uint8_t arming_state,uint8_t weapon_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RWS_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint8_t(buf, 58, arming_state);
    _mav_put_uint8_t(buf, 59, weapon_type);
    _mav_put_char_array(buf, 8, weapon_string, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RWS_STATE_LEN);
#else
    mavlink_rws_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_state = arming_state;
    packet.weapon_type = weapon_type;
    mav_array_memcpy(packet.weapon_string, weapon_string, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RWS_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RWS_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN, MAVLINK_MSG_ID_RWS_STATE_CRC);
}

/**
 * @brief Encode a rws_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rws_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rws_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rws_state_t* rws_state)
{
    return mavlink_msg_rws_state_pack(system_id, component_id, msg, rws_state->time_usec, rws_state->weapon_string, rws_state->arming_state, rws_state->weapon_type);
}

/**
 * @brief Encode a rws_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rws_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rws_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_rws_state_t* rws_state)
{
    return mavlink_msg_rws_state_pack_chan(system_id, component_id, chan, msg, rws_state->time_usec, rws_state->weapon_string, rws_state->arming_state, rws_state->weapon_type);
}

/**
 * @brief Encode a rws_state struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param rws_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rws_state_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_rws_state_t* rws_state)
{
    return mavlink_msg_rws_state_pack_status(system_id, component_id, _status, msg,  rws_state->time_usec, rws_state->weapon_string, rws_state->arming_state, rws_state->weapon_type);
}

/**
 * @brief Send a rws_state message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param weapon_string  Human-readable weapon description or designation (null-terminated).
 * @param arming_state  Current arming state of the weapon system.
 * @param weapon_type  Weapon type identifier (implementation-defined).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rws_state_send(mavlink_channel_t chan, uint64_t time_usec, const char *weapon_string, uint8_t arming_state, uint8_t weapon_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RWS_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint8_t(buf, 58, arming_state);
    _mav_put_uint8_t(buf, 59, weapon_type);
    _mav_put_char_array(buf, 8, weapon_string, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_STATE, buf, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN, MAVLINK_MSG_ID_RWS_STATE_CRC);
#else
    mavlink_rws_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_state = arming_state;
    packet.weapon_type = weapon_type;
    mav_array_memcpy(packet.weapon_string, weapon_string, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_STATE, (const char *)&packet, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN, MAVLINK_MSG_ID_RWS_STATE_CRC);
#endif
}

/**
 * @brief Send a rws_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_rws_state_send_struct(mavlink_channel_t chan, const mavlink_rws_state_t* rws_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_rws_state_send(chan, rws_state->time_usec, rws_state->weapon_string, rws_state->arming_state, rws_state->weapon_type);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_STATE, (const char *)rws_state, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN, MAVLINK_MSG_ID_RWS_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_RWS_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_rws_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, const char *weapon_string, uint8_t arming_state, uint8_t weapon_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint8_t(buf, 58, arming_state);
    _mav_put_uint8_t(buf, 59, weapon_type);
    _mav_put_char_array(buf, 8, weapon_string, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_STATE, buf, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN, MAVLINK_MSG_ID_RWS_STATE_CRC);
#else
    mavlink_rws_state_t *packet = (mavlink_rws_state_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->arming_state = arming_state;
    packet->weapon_type = weapon_type;
    mav_array_memcpy(packet->weapon_string, weapon_string, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RWS_STATE, (const char *)packet, MAVLINK_MSG_ID_RWS_STATE_MIN_LEN, MAVLINK_MSG_ID_RWS_STATE_LEN, MAVLINK_MSG_ID_RWS_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE RWS_STATE UNPACKING


/**
 * @brief Get field time_usec from rws_state message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_rws_state_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field weapon_string from rws_state message
 *
 * @return  Human-readable weapon description or designation (null-terminated).
 */
static inline uint16_t mavlink_msg_rws_state_get_weapon_string(const mavlink_message_t* msg, char *weapon_string)
{
    return _MAV_RETURN_char_array(msg, weapon_string, 50,  8);
}

/**
 * @brief Get field arming_state from rws_state message
 *
 * @return  Current arming state of the weapon system.
 */
static inline uint8_t mavlink_msg_rws_state_get_arming_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  58);
}

/**
 * @brief Get field weapon_type from rws_state message
 *
 * @return  Weapon type identifier (implementation-defined).
 */
static inline uint8_t mavlink_msg_rws_state_get_weapon_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  59);
}

/**
 * @brief Decode a rws_state message into a struct
 *
 * @param msg The message to decode
 * @param rws_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_rws_state_decode(const mavlink_message_t* msg, mavlink_rws_state_t* rws_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    rws_state->time_usec = mavlink_msg_rws_state_get_time_usec(msg);
    mavlink_msg_rws_state_get_weapon_string(msg, rws_state->weapon_string);
    rws_state->arming_state = mavlink_msg_rws_state_get_arming_state(msg);
    rws_state->weapon_type = mavlink_msg_rws_state_get_weapon_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_RWS_STATE_LEN? msg->len : MAVLINK_MSG_ID_RWS_STATE_LEN;
        memset(rws_state, 0, MAVLINK_MSG_ID_RWS_STATE_LEN);
    memcpy(rws_state, _MAV_PAYLOAD(msg), len);
#endif
}
