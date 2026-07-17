#pragma once
// MESSAGE TARGET_AUTHORIZATION PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_TARGET_AUTHORIZATION 53013


typedef struct __mavlink_target_authorization_t {
 uint64_t time_usec; /*< [us] Timestamp this attestation was recorded (UNIX epoch, microseconds UTC).*/
 uint64_t decision_usec; /*< [us] Time the authority made the decision (UNIX epoch, microseconds UTC).*/
 uint64_t valid_until_usec; /*< [us] Expiry of this attestation (UNIX epoch, microseconds UTC). 0 = unspecified.*/
 uint32_t auth_nonce; /*<  Freshness nonce bound into the authorization token by the C2 node. A verifier caches seen nonces within the validity window to reject replays. Anti-replay input only; not itself a secret.*/
 float collateral_estimate; /*<  Collateral-damage estimate context [0.0-1.0 normalized], if assessed. NaN if not.*/
 uint8_t track_uid[16]; /*<  Track UID this authorization record applies to.*/
 uint8_t authority_id[16]; /*<  Opaque identifier of the authorizing authority/operator (for audit).*/
 uint8_t authorization_token[8]; /*<  Opaque authorization token (carried for record; not a release key).*/
 uint8_t pid_status; /*<  PID status asserted by the authority.*/
 uint8_t roe_state; /*<  ROE/clearance state asserted (attested, not commanded).*/
 uint8_t nostrike_status; /*<  No-strike / restricted-target context.*/
 char authority_role[50]; /*<  Human-readable role of the authority (e.g. designation), null-terminated.*/
 uint8_t cde_level; /*<  Collateral-damage-estimation LEVEL number only (CJCSI 3160.01). Never the underlying computation or population data.*/
} mavlink_target_authorization_t;

#define MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN 126
#define MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN 126
#define MAVLINK_MSG_ID_53013_LEN 126
#define MAVLINK_MSG_ID_53013_MIN_LEN 126

#define MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC 14
#define MAVLINK_MSG_ID_53013_CRC 14

#define MAVLINK_MSG_TARGET_AUTHORIZATION_FIELD_TRACK_UID_LEN 16
#define MAVLINK_MSG_TARGET_AUTHORIZATION_FIELD_AUTHORITY_ID_LEN 16
#define MAVLINK_MSG_TARGET_AUTHORIZATION_FIELD_AUTHORIZATION_TOKEN_LEN 8
#define MAVLINK_MSG_TARGET_AUTHORIZATION_FIELD_AUTHORITY_ROLE_LEN 50

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TARGET_AUTHORIZATION { \
    53013, \
    "TARGET_AUTHORIZATION", \
    13, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_authorization_t, time_usec) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 32, offsetof(mavlink_target_authorization_t, track_uid) }, \
         { "decision_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_target_authorization_t, decision_usec) }, \
         { "valid_until_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_target_authorization_t, valid_until_usec) }, \
         { "auth_nonce", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_target_authorization_t, auth_nonce) }, \
         { "collateral_estimate", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_authorization_t, collateral_estimate) }, \
         { "authority_id", NULL, MAVLINK_TYPE_UINT8_T, 16, 48, offsetof(mavlink_target_authorization_t, authority_id) }, \
         { "authorization_token", NULL, MAVLINK_TYPE_UINT8_T, 8, 64, offsetof(mavlink_target_authorization_t, authorization_token) }, \
         { "pid_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 72, offsetof(mavlink_target_authorization_t, pid_status) }, \
         { "roe_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 73, offsetof(mavlink_target_authorization_t, roe_state) }, \
         { "nostrike_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 74, offsetof(mavlink_target_authorization_t, nostrike_status) }, \
         { "authority_role", NULL, MAVLINK_TYPE_CHAR, 50, 75, offsetof(mavlink_target_authorization_t, authority_role) }, \
         { "cde_level", NULL, MAVLINK_TYPE_UINT8_T, 0, 125, offsetof(mavlink_target_authorization_t, cde_level) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TARGET_AUTHORIZATION { \
    "TARGET_AUTHORIZATION", \
    13, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_authorization_t, time_usec) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 32, offsetof(mavlink_target_authorization_t, track_uid) }, \
         { "decision_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_target_authorization_t, decision_usec) }, \
         { "valid_until_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_target_authorization_t, valid_until_usec) }, \
         { "auth_nonce", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_target_authorization_t, auth_nonce) }, \
         { "collateral_estimate", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_authorization_t, collateral_estimate) }, \
         { "authority_id", NULL, MAVLINK_TYPE_UINT8_T, 16, 48, offsetof(mavlink_target_authorization_t, authority_id) }, \
         { "authorization_token", NULL, MAVLINK_TYPE_UINT8_T, 8, 64, offsetof(mavlink_target_authorization_t, authorization_token) }, \
         { "pid_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 72, offsetof(mavlink_target_authorization_t, pid_status) }, \
         { "roe_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 73, offsetof(mavlink_target_authorization_t, roe_state) }, \
         { "nostrike_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 74, offsetof(mavlink_target_authorization_t, nostrike_status) }, \
         { "authority_role", NULL, MAVLINK_TYPE_CHAR, 50, 75, offsetof(mavlink_target_authorization_t, authority_role) }, \
         { "cde_level", NULL, MAVLINK_TYPE_UINT8_T, 0, 125, offsetof(mavlink_target_authorization_t, cde_level) }, \
         } \
}
#endif

/**
 * @brief Pack a target_authorization message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp this attestation was recorded (UNIX epoch, microseconds UTC).
 * @param track_uid  Track UID this authorization record applies to.
 * @param decision_usec [us] Time the authority made the decision (UNIX epoch, microseconds UTC).
 * @param valid_until_usec [us] Expiry of this attestation (UNIX epoch, microseconds UTC). 0 = unspecified.
 * @param auth_nonce  Freshness nonce bound into the authorization token by the C2 node. A verifier caches seen nonces within the validity window to reject replays. Anti-replay input only; not itself a secret.
 * @param collateral_estimate  Collateral-damage estimate context [0.0-1.0 normalized], if assessed. NaN if not.
 * @param authority_id  Opaque identifier of the authorizing authority/operator (for audit).
 * @param authorization_token  Opaque authorization token (carried for record; not a release key).
 * @param pid_status  PID status asserted by the authority.
 * @param roe_state  ROE/clearance state asserted (attested, not commanded).
 * @param nostrike_status  No-strike / restricted-target context.
 * @param authority_role  Human-readable role of the authority (e.g. designation), null-terminated.
 * @param cde_level  Collateral-damage-estimation LEVEL number only (CJCSI 3160.01). Never the underlying computation or population data.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_authorization_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, const uint8_t *track_uid, uint64_t decision_usec, uint64_t valid_until_usec, uint32_t auth_nonce, float collateral_estimate, const uint8_t *authority_id, const uint8_t *authorization_token, uint8_t pid_status, uint8_t roe_state, uint8_t nostrike_status, const char *authority_role, uint8_t cde_level)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, decision_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_uint32_t(buf, 24, auth_nonce);
    _mav_put_float(buf, 28, collateral_estimate);
    _mav_put_uint8_t(buf, 72, pid_status);
    _mav_put_uint8_t(buf, 73, roe_state);
    _mav_put_uint8_t(buf, 74, nostrike_status);
    _mav_put_uint8_t(buf, 125, cde_level);
    _mav_put_uint8_t_array(buf, 32, track_uid, 16);
    _mav_put_uint8_t_array(buf, 48, authority_id, 16);
    _mav_put_uint8_t_array(buf, 64, authorization_token, 8);
    _mav_put_char_array(buf, 75, authority_role, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN);
#else
    mavlink_target_authorization_t packet;
    packet.time_usec = time_usec;
    packet.decision_usec = decision_usec;
    packet.valid_until_usec = valid_until_usec;
    packet.auth_nonce = auth_nonce;
    packet.collateral_estimate = collateral_estimate;
    packet.pid_status = pid_status;
    packet.roe_state = roe_state;
    packet.nostrike_status = nostrike_status;
    packet.cde_level = cde_level;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.authority_id, authority_id, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.authorization_token, authorization_token, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.authority_role, authority_role, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_AUTHORIZATION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC);
}

/**
 * @brief Pack a target_authorization message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp this attestation was recorded (UNIX epoch, microseconds UTC).
 * @param track_uid  Track UID this authorization record applies to.
 * @param decision_usec [us] Time the authority made the decision (UNIX epoch, microseconds UTC).
 * @param valid_until_usec [us] Expiry of this attestation (UNIX epoch, microseconds UTC). 0 = unspecified.
 * @param auth_nonce  Freshness nonce bound into the authorization token by the C2 node. A verifier caches seen nonces within the validity window to reject replays. Anti-replay input only; not itself a secret.
 * @param collateral_estimate  Collateral-damage estimate context [0.0-1.0 normalized], if assessed. NaN if not.
 * @param authority_id  Opaque identifier of the authorizing authority/operator (for audit).
 * @param authorization_token  Opaque authorization token (carried for record; not a release key).
 * @param pid_status  PID status asserted by the authority.
 * @param roe_state  ROE/clearance state asserted (attested, not commanded).
 * @param nostrike_status  No-strike / restricted-target context.
 * @param authority_role  Human-readable role of the authority (e.g. designation), null-terminated.
 * @param cde_level  Collateral-damage-estimation LEVEL number only (CJCSI 3160.01). Never the underlying computation or population data.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_authorization_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, const uint8_t *track_uid, uint64_t decision_usec, uint64_t valid_until_usec, uint32_t auth_nonce, float collateral_estimate, const uint8_t *authority_id, const uint8_t *authorization_token, uint8_t pid_status, uint8_t roe_state, uint8_t nostrike_status, const char *authority_role, uint8_t cde_level)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, decision_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_uint32_t(buf, 24, auth_nonce);
    _mav_put_float(buf, 28, collateral_estimate);
    _mav_put_uint8_t(buf, 72, pid_status);
    _mav_put_uint8_t(buf, 73, roe_state);
    _mav_put_uint8_t(buf, 74, nostrike_status);
    _mav_put_uint8_t(buf, 125, cde_level);
    _mav_put_uint8_t_array(buf, 32, track_uid, 16);
    _mav_put_uint8_t_array(buf, 48, authority_id, 16);
    _mav_put_uint8_t_array(buf, 64, authorization_token, 8);
    _mav_put_char_array(buf, 75, authority_role, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN);
#else
    mavlink_target_authorization_t packet;
    packet.time_usec = time_usec;
    packet.decision_usec = decision_usec;
    packet.valid_until_usec = valid_until_usec;
    packet.auth_nonce = auth_nonce;
    packet.collateral_estimate = collateral_estimate;
    packet.pid_status = pid_status;
    packet.roe_state = roe_state;
    packet.nostrike_status = nostrike_status;
    packet.cde_level = cde_level;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.authority_id, authority_id, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.authorization_token, authorization_token, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.authority_role, authority_role, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_AUTHORIZATION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN);
#endif
}

/**
 * @brief Pack a target_authorization message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp this attestation was recorded (UNIX epoch, microseconds UTC).
 * @param track_uid  Track UID this authorization record applies to.
 * @param decision_usec [us] Time the authority made the decision (UNIX epoch, microseconds UTC).
 * @param valid_until_usec [us] Expiry of this attestation (UNIX epoch, microseconds UTC). 0 = unspecified.
 * @param auth_nonce  Freshness nonce bound into the authorization token by the C2 node. A verifier caches seen nonces within the validity window to reject replays. Anti-replay input only; not itself a secret.
 * @param collateral_estimate  Collateral-damage estimate context [0.0-1.0 normalized], if assessed. NaN if not.
 * @param authority_id  Opaque identifier of the authorizing authority/operator (for audit).
 * @param authorization_token  Opaque authorization token (carried for record; not a release key).
 * @param pid_status  PID status asserted by the authority.
 * @param roe_state  ROE/clearance state asserted (attested, not commanded).
 * @param nostrike_status  No-strike / restricted-target context.
 * @param authority_role  Human-readable role of the authority (e.g. designation), null-terminated.
 * @param cde_level  Collateral-damage-estimation LEVEL number only (CJCSI 3160.01). Never the underlying computation or population data.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_authorization_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,const uint8_t *track_uid,uint64_t decision_usec,uint64_t valid_until_usec,uint32_t auth_nonce,float collateral_estimate,const uint8_t *authority_id,const uint8_t *authorization_token,uint8_t pid_status,uint8_t roe_state,uint8_t nostrike_status,const char *authority_role,uint8_t cde_level)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, decision_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_uint32_t(buf, 24, auth_nonce);
    _mav_put_float(buf, 28, collateral_estimate);
    _mav_put_uint8_t(buf, 72, pid_status);
    _mav_put_uint8_t(buf, 73, roe_state);
    _mav_put_uint8_t(buf, 74, nostrike_status);
    _mav_put_uint8_t(buf, 125, cde_level);
    _mav_put_uint8_t_array(buf, 32, track_uid, 16);
    _mav_put_uint8_t_array(buf, 48, authority_id, 16);
    _mav_put_uint8_t_array(buf, 64, authorization_token, 8);
    _mav_put_char_array(buf, 75, authority_role, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN);
#else
    mavlink_target_authorization_t packet;
    packet.time_usec = time_usec;
    packet.decision_usec = decision_usec;
    packet.valid_until_usec = valid_until_usec;
    packet.auth_nonce = auth_nonce;
    packet.collateral_estimate = collateral_estimate;
    packet.pid_status = pid_status;
    packet.roe_state = roe_state;
    packet.nostrike_status = nostrike_status;
    packet.cde_level = cde_level;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.authority_id, authority_id, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.authorization_token, authorization_token, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.authority_role, authority_role, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_AUTHORIZATION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC);
}

/**
 * @brief Encode a target_authorization struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param target_authorization C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_authorization_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_target_authorization_t* target_authorization)
{
    return mavlink_msg_target_authorization_pack(system_id, component_id, msg, target_authorization->time_usec, target_authorization->track_uid, target_authorization->decision_usec, target_authorization->valid_until_usec, target_authorization->auth_nonce, target_authorization->collateral_estimate, target_authorization->authority_id, target_authorization->authorization_token, target_authorization->pid_status, target_authorization->roe_state, target_authorization->nostrike_status, target_authorization->authority_role, target_authorization->cde_level);
}

/**
 * @brief Encode a target_authorization struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_authorization C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_authorization_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_target_authorization_t* target_authorization)
{
    return mavlink_msg_target_authorization_pack_chan(system_id, component_id, chan, msg, target_authorization->time_usec, target_authorization->track_uid, target_authorization->decision_usec, target_authorization->valid_until_usec, target_authorization->auth_nonce, target_authorization->collateral_estimate, target_authorization->authority_id, target_authorization->authorization_token, target_authorization->pid_status, target_authorization->roe_state, target_authorization->nostrike_status, target_authorization->authority_role, target_authorization->cde_level);
}

/**
 * @brief Encode a target_authorization struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param target_authorization C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_authorization_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_target_authorization_t* target_authorization)
{
    return mavlink_msg_target_authorization_pack_status(system_id, component_id, _status, msg,  target_authorization->time_usec, target_authorization->track_uid, target_authorization->decision_usec, target_authorization->valid_until_usec, target_authorization->auth_nonce, target_authorization->collateral_estimate, target_authorization->authority_id, target_authorization->authorization_token, target_authorization->pid_status, target_authorization->roe_state, target_authorization->nostrike_status, target_authorization->authority_role, target_authorization->cde_level);
}

/**
 * @brief Send a target_authorization message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp this attestation was recorded (UNIX epoch, microseconds UTC).
 * @param track_uid  Track UID this authorization record applies to.
 * @param decision_usec [us] Time the authority made the decision (UNIX epoch, microseconds UTC).
 * @param valid_until_usec [us] Expiry of this attestation (UNIX epoch, microseconds UTC). 0 = unspecified.
 * @param auth_nonce  Freshness nonce bound into the authorization token by the C2 node. A verifier caches seen nonces within the validity window to reject replays. Anti-replay input only; not itself a secret.
 * @param collateral_estimate  Collateral-damage estimate context [0.0-1.0 normalized], if assessed. NaN if not.
 * @param authority_id  Opaque identifier of the authorizing authority/operator (for audit).
 * @param authorization_token  Opaque authorization token (carried for record; not a release key).
 * @param pid_status  PID status asserted by the authority.
 * @param roe_state  ROE/clearance state asserted (attested, not commanded).
 * @param nostrike_status  No-strike / restricted-target context.
 * @param authority_role  Human-readable role of the authority (e.g. designation), null-terminated.
 * @param cde_level  Collateral-damage-estimation LEVEL number only (CJCSI 3160.01). Never the underlying computation or population data.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_target_authorization_send(mavlink_channel_t chan, uint64_t time_usec, const uint8_t *track_uid, uint64_t decision_usec, uint64_t valid_until_usec, uint32_t auth_nonce, float collateral_estimate, const uint8_t *authority_id, const uint8_t *authorization_token, uint8_t pid_status, uint8_t roe_state, uint8_t nostrike_status, const char *authority_role, uint8_t cde_level)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, decision_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_uint32_t(buf, 24, auth_nonce);
    _mav_put_float(buf, 28, collateral_estimate);
    _mav_put_uint8_t(buf, 72, pid_status);
    _mav_put_uint8_t(buf, 73, roe_state);
    _mav_put_uint8_t(buf, 74, nostrike_status);
    _mav_put_uint8_t(buf, 125, cde_level);
    _mav_put_uint8_t_array(buf, 32, track_uid, 16);
    _mav_put_uint8_t_array(buf, 48, authority_id, 16);
    _mav_put_uint8_t_array(buf, 64, authorization_token, 8);
    _mav_put_char_array(buf, 75, authority_role, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_AUTHORIZATION, buf, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC);
#else
    mavlink_target_authorization_t packet;
    packet.time_usec = time_usec;
    packet.decision_usec = decision_usec;
    packet.valid_until_usec = valid_until_usec;
    packet.auth_nonce = auth_nonce;
    packet.collateral_estimate = collateral_estimate;
    packet.pid_status = pid_status;
    packet.roe_state = roe_state;
    packet.nostrike_status = nostrike_status;
    packet.cde_level = cde_level;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.authority_id, authority_id, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.authorization_token, authorization_token, sizeof(uint8_t)*8);
    mav_array_memcpy(packet.authority_role, authority_role, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_AUTHORIZATION, (const char *)&packet, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC);
#endif
}

/**
 * @brief Send a target_authorization message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_target_authorization_send_struct(mavlink_channel_t chan, const mavlink_target_authorization_t* target_authorization)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_target_authorization_send(chan, target_authorization->time_usec, target_authorization->track_uid, target_authorization->decision_usec, target_authorization->valid_until_usec, target_authorization->auth_nonce, target_authorization->collateral_estimate, target_authorization->authority_id, target_authorization->authorization_token, target_authorization->pid_status, target_authorization->roe_state, target_authorization->nostrike_status, target_authorization->authority_role, target_authorization->cde_level);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_AUTHORIZATION, (const char *)target_authorization, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC);
#endif
}

#if MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_target_authorization_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, const uint8_t *track_uid, uint64_t decision_usec, uint64_t valid_until_usec, uint32_t auth_nonce, float collateral_estimate, const uint8_t *authority_id, const uint8_t *authorization_token, uint8_t pid_status, uint8_t roe_state, uint8_t nostrike_status, const char *authority_role, uint8_t cde_level)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, decision_usec);
    _mav_put_uint64_t(buf, 16, valid_until_usec);
    _mav_put_uint32_t(buf, 24, auth_nonce);
    _mav_put_float(buf, 28, collateral_estimate);
    _mav_put_uint8_t(buf, 72, pid_status);
    _mav_put_uint8_t(buf, 73, roe_state);
    _mav_put_uint8_t(buf, 74, nostrike_status);
    _mav_put_uint8_t(buf, 125, cde_level);
    _mav_put_uint8_t_array(buf, 32, track_uid, 16);
    _mav_put_uint8_t_array(buf, 48, authority_id, 16);
    _mav_put_uint8_t_array(buf, 64, authorization_token, 8);
    _mav_put_char_array(buf, 75, authority_role, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_AUTHORIZATION, buf, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC);
#else
    mavlink_target_authorization_t *packet = (mavlink_target_authorization_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->decision_usec = decision_usec;
    packet->valid_until_usec = valid_until_usec;
    packet->auth_nonce = auth_nonce;
    packet->collateral_estimate = collateral_estimate;
    packet->pid_status = pid_status;
    packet->roe_state = roe_state;
    packet->nostrike_status = nostrike_status;
    packet->cde_level = cde_level;
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet->authority_id, authority_id, sizeof(uint8_t)*16);
    mav_array_memcpy(packet->authorization_token, authorization_token, sizeof(uint8_t)*8);
    mav_array_memcpy(packet->authority_role, authority_role, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_AUTHORIZATION, (const char *)packet, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_CRC);
#endif
}
#endif

#endif

// MESSAGE TARGET_AUTHORIZATION UNPACKING


/**
 * @brief Get field time_usec from target_authorization message
 *
 * @return [us] Timestamp this attestation was recorded (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_authorization_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field track_uid from target_authorization message
 *
 * @return  Track UID this authorization record applies to.
 */
static inline uint16_t mavlink_msg_target_authorization_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  32);
}

/**
 * @brief Get field decision_usec from target_authorization message
 *
 * @return [us] Time the authority made the decision (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_authorization_get_decision_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field valid_until_usec from target_authorization message
 *
 * @return [us] Expiry of this attestation (UNIX epoch, microseconds UTC). 0 = unspecified.
 */
static inline uint64_t mavlink_msg_target_authorization_get_valid_until_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Get field auth_nonce from target_authorization message
 *
 * @return  Freshness nonce bound into the authorization token by the C2 node. A verifier caches seen nonces within the validity window to reject replays. Anti-replay input only; not itself a secret.
 */
static inline uint32_t mavlink_msg_target_authorization_get_auth_nonce(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field collateral_estimate from target_authorization message
 *
 * @return  Collateral-damage estimate context [0.0-1.0 normalized], if assessed. NaN if not.
 */
static inline float mavlink_msg_target_authorization_get_collateral_estimate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field authority_id from target_authorization message
 *
 * @return  Opaque identifier of the authorizing authority/operator (for audit).
 */
static inline uint16_t mavlink_msg_target_authorization_get_authority_id(const mavlink_message_t* msg, uint8_t *authority_id)
{
    return _MAV_RETURN_uint8_t_array(msg, authority_id, 16,  48);
}

/**
 * @brief Get field authorization_token from target_authorization message
 *
 * @return  Opaque authorization token (carried for record; not a release key).
 */
static inline uint16_t mavlink_msg_target_authorization_get_authorization_token(const mavlink_message_t* msg, uint8_t *authorization_token)
{
    return _MAV_RETURN_uint8_t_array(msg, authorization_token, 8,  64);
}

/**
 * @brief Get field pid_status from target_authorization message
 *
 * @return  PID status asserted by the authority.
 */
static inline uint8_t mavlink_msg_target_authorization_get_pid_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  72);
}

/**
 * @brief Get field roe_state from target_authorization message
 *
 * @return  ROE/clearance state asserted (attested, not commanded).
 */
static inline uint8_t mavlink_msg_target_authorization_get_roe_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  73);
}

/**
 * @brief Get field nostrike_status from target_authorization message
 *
 * @return  No-strike / restricted-target context.
 */
static inline uint8_t mavlink_msg_target_authorization_get_nostrike_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  74);
}

/**
 * @brief Get field authority_role from target_authorization message
 *
 * @return  Human-readable role of the authority (e.g. designation), null-terminated.
 */
static inline uint16_t mavlink_msg_target_authorization_get_authority_role(const mavlink_message_t* msg, char *authority_role)
{
    return _MAV_RETURN_char_array(msg, authority_role, 50,  75);
}

/**
 * @brief Get field cde_level from target_authorization message
 *
 * @return  Collateral-damage-estimation LEVEL number only (CJCSI 3160.01). Never the underlying computation or population data.
 */
static inline uint8_t mavlink_msg_target_authorization_get_cde_level(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  125);
}

/**
 * @brief Decode a target_authorization message into a struct
 *
 * @param msg The message to decode
 * @param target_authorization C-struct to decode the message contents into
 */
static inline void mavlink_msg_target_authorization_decode(const mavlink_message_t* msg, mavlink_target_authorization_t* target_authorization)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    target_authorization->time_usec = mavlink_msg_target_authorization_get_time_usec(msg);
    target_authorization->decision_usec = mavlink_msg_target_authorization_get_decision_usec(msg);
    target_authorization->valid_until_usec = mavlink_msg_target_authorization_get_valid_until_usec(msg);
    target_authorization->auth_nonce = mavlink_msg_target_authorization_get_auth_nonce(msg);
    target_authorization->collateral_estimate = mavlink_msg_target_authorization_get_collateral_estimate(msg);
    mavlink_msg_target_authorization_get_track_uid(msg, target_authorization->track_uid);
    mavlink_msg_target_authorization_get_authority_id(msg, target_authorization->authority_id);
    mavlink_msg_target_authorization_get_authorization_token(msg, target_authorization->authorization_token);
    target_authorization->pid_status = mavlink_msg_target_authorization_get_pid_status(msg);
    target_authorization->roe_state = mavlink_msg_target_authorization_get_roe_state(msg);
    target_authorization->nostrike_status = mavlink_msg_target_authorization_get_nostrike_status(msg);
    mavlink_msg_target_authorization_get_authority_role(msg, target_authorization->authority_role);
    target_authorization->cde_level = mavlink_msg_target_authorization_get_cde_level(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN? msg->len : MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN;
        memset(target_authorization, 0, MAVLINK_MSG_ID_TARGET_AUTHORIZATION_LEN);
    memcpy(target_authorization, _MAV_PAYLOAD(msg), len);
#endif
}
