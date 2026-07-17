#pragma once
// MESSAGE LOITER_MUNITION_CONTROL PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL 53036


typedef struct __mavlink_loiter_munition_control_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 int32_t loiter_lat; /*< [degE7] Loiter/orbit station latitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).*/
 int32_t loiter_lon; /*< [degE7] Loiter/orbit station longitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).*/
 uint8_t track_uid[16]; /*<  128-bit track UID of the engaged object (see TRACK_IDENTITY).*/
 uint8_t consent_state; /*<  Man-in-the-loop consent-to-strike state (recorded human decision, not a trigger).*/
 uint8_t terminate; /*<  Abort / wave-off / self-destruct action.*/
 uint8_t tst_status; /*<  Time-sensitive-target prosecution status.*/
 uint8_t pid_status; /*<  Positive-identification status gate (from TRACK_IDENTITY set).*/
 uint8_t cde_level; /*<  Collateral-damage-estimate level gate (number only).*/
 uint8_t dmpi_kind; /*<  How the desired point of impact is referenced (no mensurated coordinate).*/
} mavlink_loiter_munition_control_t;

#define MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN 38
#define MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN 38
#define MAVLINK_MSG_ID_53036_LEN 38
#define MAVLINK_MSG_ID_53036_MIN_LEN 38

#define MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC 83
#define MAVLINK_MSG_ID_53036_CRC 83

#define MAVLINK_MSG_LOITER_MUNITION_CONTROL_FIELD_TRACK_UID_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LOITER_MUNITION_CONTROL { \
    53036, \
    "LOITER_MUNITION_CONTROL", \
    10, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_loiter_munition_control_t, time_usec) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 16, offsetof(mavlink_loiter_munition_control_t, track_uid) }, \
         { "consent_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_loiter_munition_control_t, consent_state) }, \
         { "terminate", NULL, MAVLINK_TYPE_UINT8_T, 0, 33, offsetof(mavlink_loiter_munition_control_t, terminate) }, \
         { "tst_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 34, offsetof(mavlink_loiter_munition_control_t, tst_status) }, \
         { "pid_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 35, offsetof(mavlink_loiter_munition_control_t, pid_status) }, \
         { "cde_level", NULL, MAVLINK_TYPE_UINT8_T, 0, 36, offsetof(mavlink_loiter_munition_control_t, cde_level) }, \
         { "loiter_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_loiter_munition_control_t, loiter_lat) }, \
         { "loiter_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_loiter_munition_control_t, loiter_lon) }, \
         { "dmpi_kind", NULL, MAVLINK_TYPE_UINT8_T, 0, 37, offsetof(mavlink_loiter_munition_control_t, dmpi_kind) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LOITER_MUNITION_CONTROL { \
    "LOITER_MUNITION_CONTROL", \
    10, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_loiter_munition_control_t, time_usec) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 16, offsetof(mavlink_loiter_munition_control_t, track_uid) }, \
         { "consent_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_loiter_munition_control_t, consent_state) }, \
         { "terminate", NULL, MAVLINK_TYPE_UINT8_T, 0, 33, offsetof(mavlink_loiter_munition_control_t, terminate) }, \
         { "tst_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 34, offsetof(mavlink_loiter_munition_control_t, tst_status) }, \
         { "pid_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 35, offsetof(mavlink_loiter_munition_control_t, pid_status) }, \
         { "cde_level", NULL, MAVLINK_TYPE_UINT8_T, 0, 36, offsetof(mavlink_loiter_munition_control_t, cde_level) }, \
         { "loiter_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_loiter_munition_control_t, loiter_lat) }, \
         { "loiter_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_loiter_munition_control_t, loiter_lon) }, \
         { "dmpi_kind", NULL, MAVLINK_TYPE_UINT8_T, 0, 37, offsetof(mavlink_loiter_munition_control_t, dmpi_kind) }, \
         } \
}
#endif

/**
 * @brief Pack a loiter_munition_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param track_uid  128-bit track UID of the engaged object (see TRACK_IDENTITY).
 * @param consent_state  Man-in-the-loop consent-to-strike state (recorded human decision, not a trigger).
 * @param terminate  Abort / wave-off / self-destruct action.
 * @param tst_status  Time-sensitive-target prosecution status.
 * @param pid_status  Positive-identification status gate (from TRACK_IDENTITY set).
 * @param cde_level  Collateral-damage-estimate level gate (number only).
 * @param loiter_lat [degE7] Loiter/orbit station latitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param loiter_lon [degE7] Loiter/orbit station longitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param dmpi_kind  How the desired point of impact is referenced (no mensurated coordinate).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loiter_munition_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, const uint8_t *track_uid, uint8_t consent_state, uint8_t terminate, uint8_t tst_status, uint8_t pid_status, uint8_t cde_level, int32_t loiter_lat, int32_t loiter_lon, uint8_t dmpi_kind)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, loiter_lat);
    _mav_put_int32_t(buf, 12, loiter_lon);
    _mav_put_uint8_t(buf, 32, consent_state);
    _mav_put_uint8_t(buf, 33, terminate);
    _mav_put_uint8_t(buf, 34, tst_status);
    _mav_put_uint8_t(buf, 35, pid_status);
    _mav_put_uint8_t(buf, 36, cde_level);
    _mav_put_uint8_t(buf, 37, dmpi_kind);
    _mav_put_uint8_t_array(buf, 16, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN);
#else
    mavlink_loiter_munition_control_t packet;
    packet.time_usec = time_usec;
    packet.loiter_lat = loiter_lat;
    packet.loiter_lon = loiter_lon;
    packet.consent_state = consent_state;
    packet.terminate = terminate;
    packet.tst_status = tst_status;
    packet.pid_status = pid_status;
    packet.cde_level = cde_level;
    packet.dmpi_kind = dmpi_kind;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC);
}

/**
 * @brief Pack a loiter_munition_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param track_uid  128-bit track UID of the engaged object (see TRACK_IDENTITY).
 * @param consent_state  Man-in-the-loop consent-to-strike state (recorded human decision, not a trigger).
 * @param terminate  Abort / wave-off / self-destruct action.
 * @param tst_status  Time-sensitive-target prosecution status.
 * @param pid_status  Positive-identification status gate (from TRACK_IDENTITY set).
 * @param cde_level  Collateral-damage-estimate level gate (number only).
 * @param loiter_lat [degE7] Loiter/orbit station latitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param loiter_lon [degE7] Loiter/orbit station longitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param dmpi_kind  How the desired point of impact is referenced (no mensurated coordinate).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loiter_munition_control_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, const uint8_t *track_uid, uint8_t consent_state, uint8_t terminate, uint8_t tst_status, uint8_t pid_status, uint8_t cde_level, int32_t loiter_lat, int32_t loiter_lon, uint8_t dmpi_kind)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, loiter_lat);
    _mav_put_int32_t(buf, 12, loiter_lon);
    _mav_put_uint8_t(buf, 32, consent_state);
    _mav_put_uint8_t(buf, 33, terminate);
    _mav_put_uint8_t(buf, 34, tst_status);
    _mav_put_uint8_t(buf, 35, pid_status);
    _mav_put_uint8_t(buf, 36, cde_level);
    _mav_put_uint8_t(buf, 37, dmpi_kind);
    _mav_put_uint8_t_array(buf, 16, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN);
#else
    mavlink_loiter_munition_control_t packet;
    packet.time_usec = time_usec;
    packet.loiter_lat = loiter_lat;
    packet.loiter_lon = loiter_lon;
    packet.consent_state = consent_state;
    packet.terminate = terminate;
    packet.tst_status = tst_status;
    packet.pid_status = pid_status;
    packet.cde_level = cde_level;
    packet.dmpi_kind = dmpi_kind;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN);
#endif
}

/**
 * @brief Pack a loiter_munition_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param track_uid  128-bit track UID of the engaged object (see TRACK_IDENTITY).
 * @param consent_state  Man-in-the-loop consent-to-strike state (recorded human decision, not a trigger).
 * @param terminate  Abort / wave-off / self-destruct action.
 * @param tst_status  Time-sensitive-target prosecution status.
 * @param pid_status  Positive-identification status gate (from TRACK_IDENTITY set).
 * @param cde_level  Collateral-damage-estimate level gate (number only).
 * @param loiter_lat [degE7] Loiter/orbit station latitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param loiter_lon [degE7] Loiter/orbit station longitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param dmpi_kind  How the desired point of impact is referenced (no mensurated coordinate).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_loiter_munition_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,const uint8_t *track_uid,uint8_t consent_state,uint8_t terminate,uint8_t tst_status,uint8_t pid_status,uint8_t cde_level,int32_t loiter_lat,int32_t loiter_lon,uint8_t dmpi_kind)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, loiter_lat);
    _mav_put_int32_t(buf, 12, loiter_lon);
    _mav_put_uint8_t(buf, 32, consent_state);
    _mav_put_uint8_t(buf, 33, terminate);
    _mav_put_uint8_t(buf, 34, tst_status);
    _mav_put_uint8_t(buf, 35, pid_status);
    _mav_put_uint8_t(buf, 36, cde_level);
    _mav_put_uint8_t(buf, 37, dmpi_kind);
    _mav_put_uint8_t_array(buf, 16, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN);
#else
    mavlink_loiter_munition_control_t packet;
    packet.time_usec = time_usec;
    packet.loiter_lat = loiter_lat;
    packet.loiter_lon = loiter_lon;
    packet.consent_state = consent_state;
    packet.terminate = terminate;
    packet.tst_status = tst_status;
    packet.pid_status = pid_status;
    packet.cde_level = cde_level;
    packet.dmpi_kind = dmpi_kind;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC);
}

/**
 * @brief Encode a loiter_munition_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param loiter_munition_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loiter_munition_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_loiter_munition_control_t* loiter_munition_control)
{
    return mavlink_msg_loiter_munition_control_pack(system_id, component_id, msg, loiter_munition_control->time_usec, loiter_munition_control->track_uid, loiter_munition_control->consent_state, loiter_munition_control->terminate, loiter_munition_control->tst_status, loiter_munition_control->pid_status, loiter_munition_control->cde_level, loiter_munition_control->loiter_lat, loiter_munition_control->loiter_lon, loiter_munition_control->dmpi_kind);
}

/**
 * @brief Encode a loiter_munition_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param loiter_munition_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loiter_munition_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_loiter_munition_control_t* loiter_munition_control)
{
    return mavlink_msg_loiter_munition_control_pack_chan(system_id, component_id, chan, msg, loiter_munition_control->time_usec, loiter_munition_control->track_uid, loiter_munition_control->consent_state, loiter_munition_control->terminate, loiter_munition_control->tst_status, loiter_munition_control->pid_status, loiter_munition_control->cde_level, loiter_munition_control->loiter_lat, loiter_munition_control->loiter_lon, loiter_munition_control->dmpi_kind);
}

/**
 * @brief Encode a loiter_munition_control struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param loiter_munition_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_loiter_munition_control_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_loiter_munition_control_t* loiter_munition_control)
{
    return mavlink_msg_loiter_munition_control_pack_status(system_id, component_id, _status, msg,  loiter_munition_control->time_usec, loiter_munition_control->track_uid, loiter_munition_control->consent_state, loiter_munition_control->terminate, loiter_munition_control->tst_status, loiter_munition_control->pid_status, loiter_munition_control->cde_level, loiter_munition_control->loiter_lat, loiter_munition_control->loiter_lon, loiter_munition_control->dmpi_kind);
}

/**
 * @brief Send a loiter_munition_control message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param track_uid  128-bit track UID of the engaged object (see TRACK_IDENTITY).
 * @param consent_state  Man-in-the-loop consent-to-strike state (recorded human decision, not a trigger).
 * @param terminate  Abort / wave-off / self-destruct action.
 * @param tst_status  Time-sensitive-target prosecution status.
 * @param pid_status  Positive-identification status gate (from TRACK_IDENTITY set).
 * @param cde_level  Collateral-damage-estimate level gate (number only).
 * @param loiter_lat [degE7] Loiter/orbit station latitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param loiter_lon [degE7] Loiter/orbit station longitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 * @param dmpi_kind  How the desired point of impact is referenced (no mensurated coordinate).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_loiter_munition_control_send(mavlink_channel_t chan, uint64_t time_usec, const uint8_t *track_uid, uint8_t consent_state, uint8_t terminate, uint8_t tst_status, uint8_t pid_status, uint8_t cde_level, int32_t loiter_lat, int32_t loiter_lon, uint8_t dmpi_kind)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, loiter_lat);
    _mav_put_int32_t(buf, 12, loiter_lon);
    _mav_put_uint8_t(buf, 32, consent_state);
    _mav_put_uint8_t(buf, 33, terminate);
    _mav_put_uint8_t(buf, 34, tst_status);
    _mav_put_uint8_t(buf, 35, pid_status);
    _mav_put_uint8_t(buf, 36, cde_level);
    _mav_put_uint8_t(buf, 37, dmpi_kind);
    _mav_put_uint8_t_array(buf, 16, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL, buf, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC);
#else
    mavlink_loiter_munition_control_t packet;
    packet.time_usec = time_usec;
    packet.loiter_lat = loiter_lat;
    packet.loiter_lon = loiter_lon;
    packet.consent_state = consent_state;
    packet.terminate = terminate;
    packet.tst_status = tst_status;
    packet.pid_status = pid_status;
    packet.cde_level = cde_level;
    packet.dmpi_kind = dmpi_kind;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC);
#endif
}

/**
 * @brief Send a loiter_munition_control message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_loiter_munition_control_send_struct(mavlink_channel_t chan, const mavlink_loiter_munition_control_t* loiter_munition_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_loiter_munition_control_send(chan, loiter_munition_control->time_usec, loiter_munition_control->track_uid, loiter_munition_control->consent_state, loiter_munition_control->terminate, loiter_munition_control->tst_status, loiter_munition_control->pid_status, loiter_munition_control->cde_level, loiter_munition_control->loiter_lat, loiter_munition_control->loiter_lon, loiter_munition_control->dmpi_kind);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL, (const char *)loiter_munition_control, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC);
#endif
}

#if MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_loiter_munition_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, const uint8_t *track_uid, uint8_t consent_state, uint8_t terminate, uint8_t tst_status, uint8_t pid_status, uint8_t cde_level, int32_t loiter_lat, int32_t loiter_lon, uint8_t dmpi_kind)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, loiter_lat);
    _mav_put_int32_t(buf, 12, loiter_lon);
    _mav_put_uint8_t(buf, 32, consent_state);
    _mav_put_uint8_t(buf, 33, terminate);
    _mav_put_uint8_t(buf, 34, tst_status);
    _mav_put_uint8_t(buf, 35, pid_status);
    _mav_put_uint8_t(buf, 36, cde_level);
    _mav_put_uint8_t(buf, 37, dmpi_kind);
    _mav_put_uint8_t_array(buf, 16, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL, buf, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC);
#else
    mavlink_loiter_munition_control_t *packet = (mavlink_loiter_munition_control_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->loiter_lat = loiter_lat;
    packet->loiter_lon = loiter_lon;
    packet->consent_state = consent_state;
    packet->terminate = terminate;
    packet->tst_status = tst_status;
    packet->pid_status = pid_status;
    packet->cde_level = cde_level;
    packet->dmpi_kind = dmpi_kind;
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL, (const char *)packet, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_CRC);
#endif
}
#endif

#endif

// MESSAGE LOITER_MUNITION_CONTROL UNPACKING


/**
 * @brief Get field time_usec from loiter_munition_control message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_loiter_munition_control_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field track_uid from loiter_munition_control message
 *
 * @return  128-bit track UID of the engaged object (see TRACK_IDENTITY).
 */
static inline uint16_t mavlink_msg_loiter_munition_control_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  16);
}

/**
 * @brief Get field consent_state from loiter_munition_control message
 *
 * @return  Man-in-the-loop consent-to-strike state (recorded human decision, not a trigger).
 */
static inline uint8_t mavlink_msg_loiter_munition_control_get_consent_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  32);
}

/**
 * @brief Get field terminate from loiter_munition_control message
 *
 * @return  Abort / wave-off / self-destruct action.
 */
static inline uint8_t mavlink_msg_loiter_munition_control_get_terminate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  33);
}

/**
 * @brief Get field tst_status from loiter_munition_control message
 *
 * @return  Time-sensitive-target prosecution status.
 */
static inline uint8_t mavlink_msg_loiter_munition_control_get_tst_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  34);
}

/**
 * @brief Get field pid_status from loiter_munition_control message
 *
 * @return  Positive-identification status gate (from TRACK_IDENTITY set).
 */
static inline uint8_t mavlink_msg_loiter_munition_control_get_pid_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  35);
}

/**
 * @brief Get field cde_level from loiter_munition_control message
 *
 * @return  Collateral-damage-estimate level gate (number only).
 */
static inline uint8_t mavlink_msg_loiter_munition_control_get_cde_level(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  36);
}

/**
 * @brief Get field loiter_lat from loiter_munition_control message
 *
 * @return [degE7] Loiter/orbit station latitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 */
static inline int32_t mavlink_msg_loiter_munition_control_get_loiter_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field loiter_lon from loiter_munition_control message
 *
 * @return [degE7] Loiter/orbit station longitude, WGS84. INT32_MAX = not provided (0 is a valid coordinate).
 */
static inline int32_t mavlink_msg_loiter_munition_control_get_loiter_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field dmpi_kind from loiter_munition_control message
 *
 * @return  How the desired point of impact is referenced (no mensurated coordinate).
 */
static inline uint8_t mavlink_msg_loiter_munition_control_get_dmpi_kind(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  37);
}

/**
 * @brief Decode a loiter_munition_control message into a struct
 *
 * @param msg The message to decode
 * @param loiter_munition_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_loiter_munition_control_decode(const mavlink_message_t* msg, mavlink_loiter_munition_control_t* loiter_munition_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    loiter_munition_control->time_usec = mavlink_msg_loiter_munition_control_get_time_usec(msg);
    loiter_munition_control->loiter_lat = mavlink_msg_loiter_munition_control_get_loiter_lat(msg);
    loiter_munition_control->loiter_lon = mavlink_msg_loiter_munition_control_get_loiter_lon(msg);
    mavlink_msg_loiter_munition_control_get_track_uid(msg, loiter_munition_control->track_uid);
    loiter_munition_control->consent_state = mavlink_msg_loiter_munition_control_get_consent_state(msg);
    loiter_munition_control->terminate = mavlink_msg_loiter_munition_control_get_terminate(msg);
    loiter_munition_control->tst_status = mavlink_msg_loiter_munition_control_get_tst_status(msg);
    loiter_munition_control->pid_status = mavlink_msg_loiter_munition_control_get_pid_status(msg);
    loiter_munition_control->cde_level = mavlink_msg_loiter_munition_control_get_cde_level(msg);
    loiter_munition_control->dmpi_kind = mavlink_msg_loiter_munition_control_get_dmpi_kind(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN? msg->len : MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN;
        memset(loiter_munition_control, 0, MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_LEN);
    memcpy(loiter_munition_control, _MAV_PAYLOAD(msg), len);
#endif
}
