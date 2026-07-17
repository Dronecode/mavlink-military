#pragma once
// MESSAGE TERMINAL_CONTROL PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_TERMINAL_CONTROL 53061


typedef struct __mavlink_terminal_control_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint16_t sequence; /*<  Engagement sequence this handshake applies to.*/
 uint8_t tac_type; /*<  Type of terminal attack control (1/2/3).*/
 uint8_t clearance; /*<  Clearance / abort verb (human authority).*/
 uint8_t aircraft_call; /*<  Attacking-aircraft status call.*/
 uint8_t abort_authority_present; /*<  1 = a valid abort authority is established for this engagement; 0 = not.*/
} mavlink_terminal_control_t;

#define MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN 14
#define MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN 14
#define MAVLINK_MSG_ID_53061_LEN 14
#define MAVLINK_MSG_ID_53061_MIN_LEN 14

#define MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC 114
#define MAVLINK_MSG_ID_53061_CRC 114



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TERMINAL_CONTROL { \
    53061, \
    "TERMINAL_CONTROL", \
    6, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_terminal_control_t, time_usec) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_terminal_control_t, sequence) }, \
         { "tac_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_terminal_control_t, tac_type) }, \
         { "clearance", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_terminal_control_t, clearance) }, \
         { "aircraft_call", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_terminal_control_t, aircraft_call) }, \
         { "abort_authority_present", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_terminal_control_t, abort_authority_present) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TERMINAL_CONTROL { \
    "TERMINAL_CONTROL", \
    6, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_terminal_control_t, time_usec) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_terminal_control_t, sequence) }, \
         { "tac_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_terminal_control_t, tac_type) }, \
         { "clearance", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_terminal_control_t, clearance) }, \
         { "aircraft_call", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_terminal_control_t, aircraft_call) }, \
         { "abort_authority_present", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_terminal_control_t, abort_authority_present) }, \
         } \
}
#endif

/**
 * @brief Pack a terminal_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sequence  Engagement sequence this handshake applies to.
 * @param tac_type  Type of terminal attack control (1/2/3).
 * @param clearance  Clearance / abort verb (human authority).
 * @param aircraft_call  Attacking-aircraft status call.
 * @param abort_authority_present  1 = a valid abort authority is established for this engagement; 0 = not.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_terminal_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint16_t sequence, uint8_t tac_type, uint8_t clearance, uint8_t aircraft_call, uint8_t abort_authority_present)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint8_t(buf, 10, tac_type);
    _mav_put_uint8_t(buf, 11, clearance);
    _mav_put_uint8_t(buf, 12, aircraft_call);
    _mav_put_uint8_t(buf, 13, abort_authority_present);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN);
#else
    mavlink_terminal_control_t packet;
    packet.time_usec = time_usec;
    packet.sequence = sequence;
    packet.tac_type = tac_type;
    packet.clearance = clearance;
    packet.aircraft_call = aircraft_call;
    packet.abort_authority_present = abort_authority_present;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TERMINAL_CONTROL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC);
}

/**
 * @brief Pack a terminal_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sequence  Engagement sequence this handshake applies to.
 * @param tac_type  Type of terminal attack control (1/2/3).
 * @param clearance  Clearance / abort verb (human authority).
 * @param aircraft_call  Attacking-aircraft status call.
 * @param abort_authority_present  1 = a valid abort authority is established for this engagement; 0 = not.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_terminal_control_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint16_t sequence, uint8_t tac_type, uint8_t clearance, uint8_t aircraft_call, uint8_t abort_authority_present)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint8_t(buf, 10, tac_type);
    _mav_put_uint8_t(buf, 11, clearance);
    _mav_put_uint8_t(buf, 12, aircraft_call);
    _mav_put_uint8_t(buf, 13, abort_authority_present);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN);
#else
    mavlink_terminal_control_t packet;
    packet.time_usec = time_usec;
    packet.sequence = sequence;
    packet.tac_type = tac_type;
    packet.clearance = clearance;
    packet.aircraft_call = aircraft_call;
    packet.abort_authority_present = abort_authority_present;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TERMINAL_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN);
#endif
}

/**
 * @brief Pack a terminal_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sequence  Engagement sequence this handshake applies to.
 * @param tac_type  Type of terminal attack control (1/2/3).
 * @param clearance  Clearance / abort verb (human authority).
 * @param aircraft_call  Attacking-aircraft status call.
 * @param abort_authority_present  1 = a valid abort authority is established for this engagement; 0 = not.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_terminal_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint16_t sequence,uint8_t tac_type,uint8_t clearance,uint8_t aircraft_call,uint8_t abort_authority_present)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint8_t(buf, 10, tac_type);
    _mav_put_uint8_t(buf, 11, clearance);
    _mav_put_uint8_t(buf, 12, aircraft_call);
    _mav_put_uint8_t(buf, 13, abort_authority_present);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN);
#else
    mavlink_terminal_control_t packet;
    packet.time_usec = time_usec;
    packet.sequence = sequence;
    packet.tac_type = tac_type;
    packet.clearance = clearance;
    packet.aircraft_call = aircraft_call;
    packet.abort_authority_present = abort_authority_present;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TERMINAL_CONTROL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC);
}

/**
 * @brief Encode a terminal_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param terminal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_terminal_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_terminal_control_t* terminal_control)
{
    return mavlink_msg_terminal_control_pack(system_id, component_id, msg, terminal_control->time_usec, terminal_control->sequence, terminal_control->tac_type, terminal_control->clearance, terminal_control->aircraft_call, terminal_control->abort_authority_present);
}

/**
 * @brief Encode a terminal_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param terminal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_terminal_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_terminal_control_t* terminal_control)
{
    return mavlink_msg_terminal_control_pack_chan(system_id, component_id, chan, msg, terminal_control->time_usec, terminal_control->sequence, terminal_control->tac_type, terminal_control->clearance, terminal_control->aircraft_call, terminal_control->abort_authority_present);
}

/**
 * @brief Encode a terminal_control struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param terminal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_terminal_control_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_terminal_control_t* terminal_control)
{
    return mavlink_msg_terminal_control_pack_status(system_id, component_id, _status, msg,  terminal_control->time_usec, terminal_control->sequence, terminal_control->tac_type, terminal_control->clearance, terminal_control->aircraft_call, terminal_control->abort_authority_present);
}

/**
 * @brief Send a terminal_control message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param sequence  Engagement sequence this handshake applies to.
 * @param tac_type  Type of terminal attack control (1/2/3).
 * @param clearance  Clearance / abort verb (human authority).
 * @param aircraft_call  Attacking-aircraft status call.
 * @param abort_authority_present  1 = a valid abort authority is established for this engagement; 0 = not.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_terminal_control_send(mavlink_channel_t chan, uint64_t time_usec, uint16_t sequence, uint8_t tac_type, uint8_t clearance, uint8_t aircraft_call, uint8_t abort_authority_present)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint8_t(buf, 10, tac_type);
    _mav_put_uint8_t(buf, 11, clearance);
    _mav_put_uint8_t(buf, 12, aircraft_call);
    _mav_put_uint8_t(buf, 13, abort_authority_present);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TERMINAL_CONTROL, buf, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC);
#else
    mavlink_terminal_control_t packet;
    packet.time_usec = time_usec;
    packet.sequence = sequence;
    packet.tac_type = tac_type;
    packet.clearance = clearance;
    packet.aircraft_call = aircraft_call;
    packet.abort_authority_present = abort_authority_present;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TERMINAL_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC);
#endif
}

/**
 * @brief Send a terminal_control message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_terminal_control_send_struct(mavlink_channel_t chan, const mavlink_terminal_control_t* terminal_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_terminal_control_send(chan, terminal_control->time_usec, terminal_control->sequence, terminal_control->tac_type, terminal_control->clearance, terminal_control->aircraft_call, terminal_control->abort_authority_present);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TERMINAL_CONTROL, (const char *)terminal_control, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC);
#endif
}

#if MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_terminal_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint16_t sequence, uint8_t tac_type, uint8_t clearance, uint8_t aircraft_call, uint8_t abort_authority_present)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint16_t(buf, 8, sequence);
    _mav_put_uint8_t(buf, 10, tac_type);
    _mav_put_uint8_t(buf, 11, clearance);
    _mav_put_uint8_t(buf, 12, aircraft_call);
    _mav_put_uint8_t(buf, 13, abort_authority_present);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TERMINAL_CONTROL, buf, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC);
#else
    mavlink_terminal_control_t *packet = (mavlink_terminal_control_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->sequence = sequence;
    packet->tac_type = tac_type;
    packet->clearance = clearance;
    packet->aircraft_call = aircraft_call;
    packet->abort_authority_present = abort_authority_present;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TERMINAL_CONTROL, (const char *)packet, MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN, MAVLINK_MSG_ID_TERMINAL_CONTROL_CRC);
#endif
}
#endif

#endif

// MESSAGE TERMINAL_CONTROL UNPACKING


/**
 * @brief Get field time_usec from terminal_control message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_terminal_control_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field sequence from terminal_control message
 *
 * @return  Engagement sequence this handshake applies to.
 */
static inline uint16_t mavlink_msg_terminal_control_get_sequence(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field tac_type from terminal_control message
 *
 * @return  Type of terminal attack control (1/2/3).
 */
static inline uint8_t mavlink_msg_terminal_control_get_tac_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field clearance from terminal_control message
 *
 * @return  Clearance / abort verb (human authority).
 */
static inline uint8_t mavlink_msg_terminal_control_get_clearance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  11);
}

/**
 * @brief Get field aircraft_call from terminal_control message
 *
 * @return  Attacking-aircraft status call.
 */
static inline uint8_t mavlink_msg_terminal_control_get_aircraft_call(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field abort_authority_present from terminal_control message
 *
 * @return  1 = a valid abort authority is established for this engagement; 0 = not.
 */
static inline uint8_t mavlink_msg_terminal_control_get_abort_authority_present(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Decode a terminal_control message into a struct
 *
 * @param msg The message to decode
 * @param terminal_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_terminal_control_decode(const mavlink_message_t* msg, mavlink_terminal_control_t* terminal_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    terminal_control->time_usec = mavlink_msg_terminal_control_get_time_usec(msg);
    terminal_control->sequence = mavlink_msg_terminal_control_get_sequence(msg);
    terminal_control->tac_type = mavlink_msg_terminal_control_get_tac_type(msg);
    terminal_control->clearance = mavlink_msg_terminal_control_get_clearance(msg);
    terminal_control->aircraft_call = mavlink_msg_terminal_control_get_aircraft_call(msg);
    terminal_control->abort_authority_present = mavlink_msg_terminal_control_get_abort_authority_present(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN? msg->len : MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN;
        memset(terminal_control, 0, MAVLINK_MSG_ID_TERMINAL_CONTROL_LEN);
    memcpy(terminal_control, _MAV_PAYLOAD(msg), len);
#endif
}
