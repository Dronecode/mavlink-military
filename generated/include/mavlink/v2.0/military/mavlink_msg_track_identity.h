#pragma once
// MESSAGE TRACK_IDENTITY PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_TRACK_IDENTITY 53000


typedef struct __mavlink_track_identity_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint64_t first_detected_usec; /*< [us] Time the object was first detected (UNIX epoch, microseconds UTC).*/
 uint32_t target_set_id; /*<  Associated target set identifier, if any. 0 = none.*/
 float id_confidence; /*<  Confidence of identification [0.0-1.0]. NaN if not provided.*/
 uint16_t atr_model_id; /*<  Identifier of the ATR model/version that produced atr_confidence_pct. 0 = unspecified.*/
 uint8_t track_uid[16]; /*<  Globally-unique track identifier (UUID). Stable across the whole chain.*/
 uint8_t parent_track_uid[16]; /*<  Parent track UID for split/merge/re-id lineage. All-zero if none.*/
 uint8_t origin_sysid; /*<  System ID of the platform that originated/owns this track.*/
 uint8_t origin_sensor; /*<  Sensor/method underlying the current identification.*/
 uint8_t id_method; /*<  Method by which identification was reached.*/
 uint8_t pid_status; /*<  Positive identification status (descriptive).*/
 uint8_t track_rel; /*<  Relationship to parent track (split/merge/re-id).*/
 uint8_t target_class; /*<  Classification (what it is), distinct from id_method (how it was identified).*/
 uint8_t target_force; /*<  Force affiliation.*/
 char id_basis[50]; /*<  Optional free-text basis/notes for the identification (null-terminated).*/
 char external_track_number[20]; /*<  External/joint track number (e.g. Link 16 track number or VMF URN), as text for gateway round-trip. Empty if none. Encoding per external_track_type.*/
 uint8_t external_track_type; /*<  Namespace of external_track_number.*/
 uint8_t stanag_identity; /*<  STANAG/APP-6 standard identity (richer than target_force).*/
 uint8_t environment; /*<  STANAG/APP-6 battle dimension / environment.*/
 uint8_t atr_confidence_pct; /*< [%] ATR model confidence [0-100]. 255 = N/A. Raw score; the C2 node owns any ROE threshold.*/
 uint8_t atr_conf_tier; /*<  OPTIONAL advisory display tier derived from atr_confidence_pct. Not for automated ROE.*/
 uint8_t sidc_context; /*<  Reality context (MIL-STD-2525D SIDC digit 3): real-world vs exercise vs simulation. Prevents a live track and an exercise/simulated track from being indistinguishable on a joint net.*/
} mavlink_track_identity_t;

#define MAVLINK_MSG_ID_TRACK_IDENTITY_LEN 141
#define MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN 141
#define MAVLINK_MSG_ID_53000_LEN 141
#define MAVLINK_MSG_ID_53000_MIN_LEN 141

#define MAVLINK_MSG_ID_TRACK_IDENTITY_CRC 21
#define MAVLINK_MSG_ID_53000_CRC 21

#define MAVLINK_MSG_TRACK_IDENTITY_FIELD_TRACK_UID_LEN 16
#define MAVLINK_MSG_TRACK_IDENTITY_FIELD_PARENT_TRACK_UID_LEN 16
#define MAVLINK_MSG_TRACK_IDENTITY_FIELD_ID_BASIS_LEN 50
#define MAVLINK_MSG_TRACK_IDENTITY_FIELD_EXTERNAL_TRACK_NUMBER_LEN 20

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TRACK_IDENTITY { \
    53000, \
    "TRACK_IDENTITY", \
    22, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_track_identity_t, time_usec) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 26, offsetof(mavlink_track_identity_t, track_uid) }, \
         { "parent_track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 42, offsetof(mavlink_track_identity_t, parent_track_uid) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_track_identity_t, target_set_id) }, \
         { "first_detected_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_track_identity_t, first_detected_usec) }, \
         { "id_confidence", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_track_identity_t, id_confidence) }, \
         { "origin_sysid", NULL, MAVLINK_TYPE_UINT8_T, 0, 58, offsetof(mavlink_track_identity_t, origin_sysid) }, \
         { "origin_sensor", NULL, MAVLINK_TYPE_UINT8_T, 0, 59, offsetof(mavlink_track_identity_t, origin_sensor) }, \
         { "id_method", NULL, MAVLINK_TYPE_UINT8_T, 0, 60, offsetof(mavlink_track_identity_t, id_method) }, \
         { "pid_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 61, offsetof(mavlink_track_identity_t, pid_status) }, \
         { "track_rel", NULL, MAVLINK_TYPE_UINT8_T, 0, 62, offsetof(mavlink_track_identity_t, track_rel) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 63, offsetof(mavlink_track_identity_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 64, offsetof(mavlink_track_identity_t, target_force) }, \
         { "id_basis", NULL, MAVLINK_TYPE_CHAR, 50, 65, offsetof(mavlink_track_identity_t, id_basis) }, \
         { "external_track_number", NULL, MAVLINK_TYPE_CHAR, 20, 115, offsetof(mavlink_track_identity_t, external_track_number) }, \
         { "external_track_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 135, offsetof(mavlink_track_identity_t, external_track_type) }, \
         { "stanag_identity", NULL, MAVLINK_TYPE_UINT8_T, 0, 136, offsetof(mavlink_track_identity_t, stanag_identity) }, \
         { "environment", NULL, MAVLINK_TYPE_UINT8_T, 0, 137, offsetof(mavlink_track_identity_t, environment) }, \
         { "atr_confidence_pct", NULL, MAVLINK_TYPE_UINT8_T, 0, 138, offsetof(mavlink_track_identity_t, atr_confidence_pct) }, \
         { "atr_model_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_track_identity_t, atr_model_id) }, \
         { "atr_conf_tier", NULL, MAVLINK_TYPE_UINT8_T, 0, 139, offsetof(mavlink_track_identity_t, atr_conf_tier) }, \
         { "sidc_context", NULL, MAVLINK_TYPE_UINT8_T, 0, 140, offsetof(mavlink_track_identity_t, sidc_context) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TRACK_IDENTITY { \
    "TRACK_IDENTITY", \
    22, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_track_identity_t, time_usec) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 26, offsetof(mavlink_track_identity_t, track_uid) }, \
         { "parent_track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 42, offsetof(mavlink_track_identity_t, parent_track_uid) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_track_identity_t, target_set_id) }, \
         { "first_detected_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_track_identity_t, first_detected_usec) }, \
         { "id_confidence", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_track_identity_t, id_confidence) }, \
         { "origin_sysid", NULL, MAVLINK_TYPE_UINT8_T, 0, 58, offsetof(mavlink_track_identity_t, origin_sysid) }, \
         { "origin_sensor", NULL, MAVLINK_TYPE_UINT8_T, 0, 59, offsetof(mavlink_track_identity_t, origin_sensor) }, \
         { "id_method", NULL, MAVLINK_TYPE_UINT8_T, 0, 60, offsetof(mavlink_track_identity_t, id_method) }, \
         { "pid_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 61, offsetof(mavlink_track_identity_t, pid_status) }, \
         { "track_rel", NULL, MAVLINK_TYPE_UINT8_T, 0, 62, offsetof(mavlink_track_identity_t, track_rel) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 63, offsetof(mavlink_track_identity_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 64, offsetof(mavlink_track_identity_t, target_force) }, \
         { "id_basis", NULL, MAVLINK_TYPE_CHAR, 50, 65, offsetof(mavlink_track_identity_t, id_basis) }, \
         { "external_track_number", NULL, MAVLINK_TYPE_CHAR, 20, 115, offsetof(mavlink_track_identity_t, external_track_number) }, \
         { "external_track_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 135, offsetof(mavlink_track_identity_t, external_track_type) }, \
         { "stanag_identity", NULL, MAVLINK_TYPE_UINT8_T, 0, 136, offsetof(mavlink_track_identity_t, stanag_identity) }, \
         { "environment", NULL, MAVLINK_TYPE_UINT8_T, 0, 137, offsetof(mavlink_track_identity_t, environment) }, \
         { "atr_confidence_pct", NULL, MAVLINK_TYPE_UINT8_T, 0, 138, offsetof(mavlink_track_identity_t, atr_confidence_pct) }, \
         { "atr_model_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_track_identity_t, atr_model_id) }, \
         { "atr_conf_tier", NULL, MAVLINK_TYPE_UINT8_T, 0, 139, offsetof(mavlink_track_identity_t, atr_conf_tier) }, \
         { "sidc_context", NULL, MAVLINK_TYPE_UINT8_T, 0, 140, offsetof(mavlink_track_identity_t, sidc_context) }, \
         } \
}
#endif

/**
 * @brief Pack a track_identity message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param track_uid  Globally-unique track identifier (UUID). Stable across the whole chain.
 * @param parent_track_uid  Parent track UID for split/merge/re-id lineage. All-zero if none.
 * @param target_set_id  Associated target set identifier, if any. 0 = none.
 * @param first_detected_usec [us] Time the object was first detected (UNIX epoch, microseconds UTC).
 * @param id_confidence  Confidence of identification [0.0-1.0]. NaN if not provided.
 * @param origin_sysid  System ID of the platform that originated/owns this track.
 * @param origin_sensor  Sensor/method underlying the current identification.
 * @param id_method  Method by which identification was reached.
 * @param pid_status  Positive identification status (descriptive).
 * @param track_rel  Relationship to parent track (split/merge/re-id).
 * @param target_class  Classification (what it is), distinct from id_method (how it was identified).
 * @param target_force  Force affiliation.
 * @param id_basis  Optional free-text basis/notes for the identification (null-terminated).
 * @param external_track_number  External/joint track number (e.g. Link 16 track number or VMF URN), as text for gateway round-trip. Empty if none. Encoding per external_track_type.
 * @param external_track_type  Namespace of external_track_number.
 * @param stanag_identity  STANAG/APP-6 standard identity (richer than target_force).
 * @param environment  STANAG/APP-6 battle dimension / environment.
 * @param atr_confidence_pct [%] ATR model confidence [0-100]. 255 = N/A. Raw score; the C2 node owns any ROE threshold.
 * @param atr_model_id  Identifier of the ATR model/version that produced atr_confidence_pct. 0 = unspecified.
 * @param atr_conf_tier  OPTIONAL advisory display tier derived from atr_confidence_pct. Not for automated ROE.
 * @param sidc_context  Reality context (MIL-STD-2525D SIDC digit 3): real-world vs exercise vs simulation. Prevents a live track and an exercise/simulated track from being indistinguishable on a joint net.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_track_identity_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, const uint8_t *track_uid, const uint8_t *parent_track_uid, uint32_t target_set_id, uint64_t first_detected_usec, float id_confidence, uint8_t origin_sysid, uint8_t origin_sensor, uint8_t id_method, uint8_t pid_status, uint8_t track_rel, uint8_t target_class, uint8_t target_force, const char *id_basis, const char *external_track_number, uint8_t external_track_type, uint8_t stanag_identity, uint8_t environment, uint8_t atr_confidence_pct, uint16_t atr_model_id, uint8_t atr_conf_tier, uint8_t sidc_context)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TRACK_IDENTITY_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, first_detected_usec);
    _mav_put_uint32_t(buf, 16, target_set_id);
    _mav_put_float(buf, 20, id_confidence);
    _mav_put_uint16_t(buf, 24, atr_model_id);
    _mav_put_uint8_t(buf, 58, origin_sysid);
    _mav_put_uint8_t(buf, 59, origin_sensor);
    _mav_put_uint8_t(buf, 60, id_method);
    _mav_put_uint8_t(buf, 61, pid_status);
    _mav_put_uint8_t(buf, 62, track_rel);
    _mav_put_uint8_t(buf, 63, target_class);
    _mav_put_uint8_t(buf, 64, target_force);
    _mav_put_uint8_t(buf, 135, external_track_type);
    _mav_put_uint8_t(buf, 136, stanag_identity);
    _mav_put_uint8_t(buf, 137, environment);
    _mav_put_uint8_t(buf, 138, atr_confidence_pct);
    _mav_put_uint8_t(buf, 139, atr_conf_tier);
    _mav_put_uint8_t(buf, 140, sidc_context);
    _mav_put_uint8_t_array(buf, 26, track_uid, 16);
    _mav_put_uint8_t_array(buf, 42, parent_track_uid, 16);
    _mav_put_char_array(buf, 65, id_basis, 50);
    _mav_put_char_array(buf, 115, external_track_number, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN);
#else
    mavlink_track_identity_t packet;
    packet.time_usec = time_usec;
    packet.first_detected_usec = first_detected_usec;
    packet.target_set_id = target_set_id;
    packet.id_confidence = id_confidence;
    packet.atr_model_id = atr_model_id;
    packet.origin_sysid = origin_sysid;
    packet.origin_sensor = origin_sensor;
    packet.id_method = id_method;
    packet.pid_status = pid_status;
    packet.track_rel = track_rel;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.external_track_type = external_track_type;
    packet.stanag_identity = stanag_identity;
    packet.environment = environment;
    packet.atr_confidence_pct = atr_confidence_pct;
    packet.atr_conf_tier = atr_conf_tier;
    packet.sidc_context = sidc_context;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.parent_track_uid, parent_track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.id_basis, id_basis, sizeof(char)*50);
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TRACK_IDENTITY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_CRC);
}

/**
 * @brief Pack a track_identity message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param track_uid  Globally-unique track identifier (UUID). Stable across the whole chain.
 * @param parent_track_uid  Parent track UID for split/merge/re-id lineage. All-zero if none.
 * @param target_set_id  Associated target set identifier, if any. 0 = none.
 * @param first_detected_usec [us] Time the object was first detected (UNIX epoch, microseconds UTC).
 * @param id_confidence  Confidence of identification [0.0-1.0]. NaN if not provided.
 * @param origin_sysid  System ID of the platform that originated/owns this track.
 * @param origin_sensor  Sensor/method underlying the current identification.
 * @param id_method  Method by which identification was reached.
 * @param pid_status  Positive identification status (descriptive).
 * @param track_rel  Relationship to parent track (split/merge/re-id).
 * @param target_class  Classification (what it is), distinct from id_method (how it was identified).
 * @param target_force  Force affiliation.
 * @param id_basis  Optional free-text basis/notes for the identification (null-terminated).
 * @param external_track_number  External/joint track number (e.g. Link 16 track number or VMF URN), as text for gateway round-trip. Empty if none. Encoding per external_track_type.
 * @param external_track_type  Namespace of external_track_number.
 * @param stanag_identity  STANAG/APP-6 standard identity (richer than target_force).
 * @param environment  STANAG/APP-6 battle dimension / environment.
 * @param atr_confidence_pct [%] ATR model confidence [0-100]. 255 = N/A. Raw score; the C2 node owns any ROE threshold.
 * @param atr_model_id  Identifier of the ATR model/version that produced atr_confidence_pct. 0 = unspecified.
 * @param atr_conf_tier  OPTIONAL advisory display tier derived from atr_confidence_pct. Not for automated ROE.
 * @param sidc_context  Reality context (MIL-STD-2525D SIDC digit 3): real-world vs exercise vs simulation. Prevents a live track and an exercise/simulated track from being indistinguishable on a joint net.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_track_identity_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, const uint8_t *track_uid, const uint8_t *parent_track_uid, uint32_t target_set_id, uint64_t first_detected_usec, float id_confidence, uint8_t origin_sysid, uint8_t origin_sensor, uint8_t id_method, uint8_t pid_status, uint8_t track_rel, uint8_t target_class, uint8_t target_force, const char *id_basis, const char *external_track_number, uint8_t external_track_type, uint8_t stanag_identity, uint8_t environment, uint8_t atr_confidence_pct, uint16_t atr_model_id, uint8_t atr_conf_tier, uint8_t sidc_context)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TRACK_IDENTITY_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, first_detected_usec);
    _mav_put_uint32_t(buf, 16, target_set_id);
    _mav_put_float(buf, 20, id_confidence);
    _mav_put_uint16_t(buf, 24, atr_model_id);
    _mav_put_uint8_t(buf, 58, origin_sysid);
    _mav_put_uint8_t(buf, 59, origin_sensor);
    _mav_put_uint8_t(buf, 60, id_method);
    _mav_put_uint8_t(buf, 61, pid_status);
    _mav_put_uint8_t(buf, 62, track_rel);
    _mav_put_uint8_t(buf, 63, target_class);
    _mav_put_uint8_t(buf, 64, target_force);
    _mav_put_uint8_t(buf, 135, external_track_type);
    _mav_put_uint8_t(buf, 136, stanag_identity);
    _mav_put_uint8_t(buf, 137, environment);
    _mav_put_uint8_t(buf, 138, atr_confidence_pct);
    _mav_put_uint8_t(buf, 139, atr_conf_tier);
    _mav_put_uint8_t(buf, 140, sidc_context);
    _mav_put_uint8_t_array(buf, 26, track_uid, 16);
    _mav_put_uint8_t_array(buf, 42, parent_track_uid, 16);
    _mav_put_char_array(buf, 65, id_basis, 50);
    _mav_put_char_array(buf, 115, external_track_number, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN);
#else
    mavlink_track_identity_t packet;
    packet.time_usec = time_usec;
    packet.first_detected_usec = first_detected_usec;
    packet.target_set_id = target_set_id;
    packet.id_confidence = id_confidence;
    packet.atr_model_id = atr_model_id;
    packet.origin_sysid = origin_sysid;
    packet.origin_sensor = origin_sensor;
    packet.id_method = id_method;
    packet.pid_status = pid_status;
    packet.track_rel = track_rel;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.external_track_type = external_track_type;
    packet.stanag_identity = stanag_identity;
    packet.environment = environment;
    packet.atr_confidence_pct = atr_confidence_pct;
    packet.atr_conf_tier = atr_conf_tier;
    packet.sidc_context = sidc_context;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.parent_track_uid, parent_track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.id_basis, id_basis, sizeof(char)*50);
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TRACK_IDENTITY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN);
#endif
}

/**
 * @brief Pack a track_identity message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param track_uid  Globally-unique track identifier (UUID). Stable across the whole chain.
 * @param parent_track_uid  Parent track UID for split/merge/re-id lineage. All-zero if none.
 * @param target_set_id  Associated target set identifier, if any. 0 = none.
 * @param first_detected_usec [us] Time the object was first detected (UNIX epoch, microseconds UTC).
 * @param id_confidence  Confidence of identification [0.0-1.0]. NaN if not provided.
 * @param origin_sysid  System ID of the platform that originated/owns this track.
 * @param origin_sensor  Sensor/method underlying the current identification.
 * @param id_method  Method by which identification was reached.
 * @param pid_status  Positive identification status (descriptive).
 * @param track_rel  Relationship to parent track (split/merge/re-id).
 * @param target_class  Classification (what it is), distinct from id_method (how it was identified).
 * @param target_force  Force affiliation.
 * @param id_basis  Optional free-text basis/notes for the identification (null-terminated).
 * @param external_track_number  External/joint track number (e.g. Link 16 track number or VMF URN), as text for gateway round-trip. Empty if none. Encoding per external_track_type.
 * @param external_track_type  Namespace of external_track_number.
 * @param stanag_identity  STANAG/APP-6 standard identity (richer than target_force).
 * @param environment  STANAG/APP-6 battle dimension / environment.
 * @param atr_confidence_pct [%] ATR model confidence [0-100]. 255 = N/A. Raw score; the C2 node owns any ROE threshold.
 * @param atr_model_id  Identifier of the ATR model/version that produced atr_confidence_pct. 0 = unspecified.
 * @param atr_conf_tier  OPTIONAL advisory display tier derived from atr_confidence_pct. Not for automated ROE.
 * @param sidc_context  Reality context (MIL-STD-2525D SIDC digit 3): real-world vs exercise vs simulation. Prevents a live track and an exercise/simulated track from being indistinguishable on a joint net.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_track_identity_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,const uint8_t *track_uid,const uint8_t *parent_track_uid,uint32_t target_set_id,uint64_t first_detected_usec,float id_confidence,uint8_t origin_sysid,uint8_t origin_sensor,uint8_t id_method,uint8_t pid_status,uint8_t track_rel,uint8_t target_class,uint8_t target_force,const char *id_basis,const char *external_track_number,uint8_t external_track_type,uint8_t stanag_identity,uint8_t environment,uint8_t atr_confidence_pct,uint16_t atr_model_id,uint8_t atr_conf_tier,uint8_t sidc_context)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TRACK_IDENTITY_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, first_detected_usec);
    _mav_put_uint32_t(buf, 16, target_set_id);
    _mav_put_float(buf, 20, id_confidence);
    _mav_put_uint16_t(buf, 24, atr_model_id);
    _mav_put_uint8_t(buf, 58, origin_sysid);
    _mav_put_uint8_t(buf, 59, origin_sensor);
    _mav_put_uint8_t(buf, 60, id_method);
    _mav_put_uint8_t(buf, 61, pid_status);
    _mav_put_uint8_t(buf, 62, track_rel);
    _mav_put_uint8_t(buf, 63, target_class);
    _mav_put_uint8_t(buf, 64, target_force);
    _mav_put_uint8_t(buf, 135, external_track_type);
    _mav_put_uint8_t(buf, 136, stanag_identity);
    _mav_put_uint8_t(buf, 137, environment);
    _mav_put_uint8_t(buf, 138, atr_confidence_pct);
    _mav_put_uint8_t(buf, 139, atr_conf_tier);
    _mav_put_uint8_t(buf, 140, sidc_context);
    _mav_put_uint8_t_array(buf, 26, track_uid, 16);
    _mav_put_uint8_t_array(buf, 42, parent_track_uid, 16);
    _mav_put_char_array(buf, 65, id_basis, 50);
    _mav_put_char_array(buf, 115, external_track_number, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN);
#else
    mavlink_track_identity_t packet;
    packet.time_usec = time_usec;
    packet.first_detected_usec = first_detected_usec;
    packet.target_set_id = target_set_id;
    packet.id_confidence = id_confidence;
    packet.atr_model_id = atr_model_id;
    packet.origin_sysid = origin_sysid;
    packet.origin_sensor = origin_sensor;
    packet.id_method = id_method;
    packet.pid_status = pid_status;
    packet.track_rel = track_rel;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.external_track_type = external_track_type;
    packet.stanag_identity = stanag_identity;
    packet.environment = environment;
    packet.atr_confidence_pct = atr_confidence_pct;
    packet.atr_conf_tier = atr_conf_tier;
    packet.sidc_context = sidc_context;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.parent_track_uid, parent_track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.id_basis, id_basis, sizeof(char)*50);
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TRACK_IDENTITY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_CRC);
}

/**
 * @brief Encode a track_identity struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param track_identity C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_track_identity_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_track_identity_t* track_identity)
{
    return mavlink_msg_track_identity_pack(system_id, component_id, msg, track_identity->time_usec, track_identity->track_uid, track_identity->parent_track_uid, track_identity->target_set_id, track_identity->first_detected_usec, track_identity->id_confidence, track_identity->origin_sysid, track_identity->origin_sensor, track_identity->id_method, track_identity->pid_status, track_identity->track_rel, track_identity->target_class, track_identity->target_force, track_identity->id_basis, track_identity->external_track_number, track_identity->external_track_type, track_identity->stanag_identity, track_identity->environment, track_identity->atr_confidence_pct, track_identity->atr_model_id, track_identity->atr_conf_tier, track_identity->sidc_context);
}

/**
 * @brief Encode a track_identity struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param track_identity C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_track_identity_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_track_identity_t* track_identity)
{
    return mavlink_msg_track_identity_pack_chan(system_id, component_id, chan, msg, track_identity->time_usec, track_identity->track_uid, track_identity->parent_track_uid, track_identity->target_set_id, track_identity->first_detected_usec, track_identity->id_confidence, track_identity->origin_sysid, track_identity->origin_sensor, track_identity->id_method, track_identity->pid_status, track_identity->track_rel, track_identity->target_class, track_identity->target_force, track_identity->id_basis, track_identity->external_track_number, track_identity->external_track_type, track_identity->stanag_identity, track_identity->environment, track_identity->atr_confidence_pct, track_identity->atr_model_id, track_identity->atr_conf_tier, track_identity->sidc_context);
}

/**
 * @brief Encode a track_identity struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param track_identity C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_track_identity_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_track_identity_t* track_identity)
{
    return mavlink_msg_track_identity_pack_status(system_id, component_id, _status, msg,  track_identity->time_usec, track_identity->track_uid, track_identity->parent_track_uid, track_identity->target_set_id, track_identity->first_detected_usec, track_identity->id_confidence, track_identity->origin_sysid, track_identity->origin_sensor, track_identity->id_method, track_identity->pid_status, track_identity->track_rel, track_identity->target_class, track_identity->target_force, track_identity->id_basis, track_identity->external_track_number, track_identity->external_track_type, track_identity->stanag_identity, track_identity->environment, track_identity->atr_confidence_pct, track_identity->atr_model_id, track_identity->atr_conf_tier, track_identity->sidc_context);
}

/**
 * @brief Send a track_identity message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param track_uid  Globally-unique track identifier (UUID). Stable across the whole chain.
 * @param parent_track_uid  Parent track UID for split/merge/re-id lineage. All-zero if none.
 * @param target_set_id  Associated target set identifier, if any. 0 = none.
 * @param first_detected_usec [us] Time the object was first detected (UNIX epoch, microseconds UTC).
 * @param id_confidence  Confidence of identification [0.0-1.0]. NaN if not provided.
 * @param origin_sysid  System ID of the platform that originated/owns this track.
 * @param origin_sensor  Sensor/method underlying the current identification.
 * @param id_method  Method by which identification was reached.
 * @param pid_status  Positive identification status (descriptive).
 * @param track_rel  Relationship to parent track (split/merge/re-id).
 * @param target_class  Classification (what it is), distinct from id_method (how it was identified).
 * @param target_force  Force affiliation.
 * @param id_basis  Optional free-text basis/notes for the identification (null-terminated).
 * @param external_track_number  External/joint track number (e.g. Link 16 track number or VMF URN), as text for gateway round-trip. Empty if none. Encoding per external_track_type.
 * @param external_track_type  Namespace of external_track_number.
 * @param stanag_identity  STANAG/APP-6 standard identity (richer than target_force).
 * @param environment  STANAG/APP-6 battle dimension / environment.
 * @param atr_confidence_pct [%] ATR model confidence [0-100]. 255 = N/A. Raw score; the C2 node owns any ROE threshold.
 * @param atr_model_id  Identifier of the ATR model/version that produced atr_confidence_pct. 0 = unspecified.
 * @param atr_conf_tier  OPTIONAL advisory display tier derived from atr_confidence_pct. Not for automated ROE.
 * @param sidc_context  Reality context (MIL-STD-2525D SIDC digit 3): real-world vs exercise vs simulation. Prevents a live track and an exercise/simulated track from being indistinguishable on a joint net.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_track_identity_send(mavlink_channel_t chan, uint64_t time_usec, const uint8_t *track_uid, const uint8_t *parent_track_uid, uint32_t target_set_id, uint64_t first_detected_usec, float id_confidence, uint8_t origin_sysid, uint8_t origin_sensor, uint8_t id_method, uint8_t pid_status, uint8_t track_rel, uint8_t target_class, uint8_t target_force, const char *id_basis, const char *external_track_number, uint8_t external_track_type, uint8_t stanag_identity, uint8_t environment, uint8_t atr_confidence_pct, uint16_t atr_model_id, uint8_t atr_conf_tier, uint8_t sidc_context)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TRACK_IDENTITY_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, first_detected_usec);
    _mav_put_uint32_t(buf, 16, target_set_id);
    _mav_put_float(buf, 20, id_confidence);
    _mav_put_uint16_t(buf, 24, atr_model_id);
    _mav_put_uint8_t(buf, 58, origin_sysid);
    _mav_put_uint8_t(buf, 59, origin_sensor);
    _mav_put_uint8_t(buf, 60, id_method);
    _mav_put_uint8_t(buf, 61, pid_status);
    _mav_put_uint8_t(buf, 62, track_rel);
    _mav_put_uint8_t(buf, 63, target_class);
    _mav_put_uint8_t(buf, 64, target_force);
    _mav_put_uint8_t(buf, 135, external_track_type);
    _mav_put_uint8_t(buf, 136, stanag_identity);
    _mav_put_uint8_t(buf, 137, environment);
    _mav_put_uint8_t(buf, 138, atr_confidence_pct);
    _mav_put_uint8_t(buf, 139, atr_conf_tier);
    _mav_put_uint8_t(buf, 140, sidc_context);
    _mav_put_uint8_t_array(buf, 26, track_uid, 16);
    _mav_put_uint8_t_array(buf, 42, parent_track_uid, 16);
    _mav_put_char_array(buf, 65, id_basis, 50);
    _mav_put_char_array(buf, 115, external_track_number, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRACK_IDENTITY, buf, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_CRC);
#else
    mavlink_track_identity_t packet;
    packet.time_usec = time_usec;
    packet.first_detected_usec = first_detected_usec;
    packet.target_set_id = target_set_id;
    packet.id_confidence = id_confidence;
    packet.atr_model_id = atr_model_id;
    packet.origin_sysid = origin_sysid;
    packet.origin_sensor = origin_sensor;
    packet.id_method = id_method;
    packet.pid_status = pid_status;
    packet.track_rel = track_rel;
    packet.target_class = target_class;
    packet.target_force = target_force;
    packet.external_track_type = external_track_type;
    packet.stanag_identity = stanag_identity;
    packet.environment = environment;
    packet.atr_confidence_pct = atr_confidence_pct;
    packet.atr_conf_tier = atr_conf_tier;
    packet.sidc_context = sidc_context;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.parent_track_uid, parent_track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet.id_basis, id_basis, sizeof(char)*50);
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRACK_IDENTITY, (const char *)&packet, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_CRC);
#endif
}

/**
 * @brief Send a track_identity message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_track_identity_send_struct(mavlink_channel_t chan, const mavlink_track_identity_t* track_identity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_track_identity_send(chan, track_identity->time_usec, track_identity->track_uid, track_identity->parent_track_uid, track_identity->target_set_id, track_identity->first_detected_usec, track_identity->id_confidence, track_identity->origin_sysid, track_identity->origin_sensor, track_identity->id_method, track_identity->pid_status, track_identity->track_rel, track_identity->target_class, track_identity->target_force, track_identity->id_basis, track_identity->external_track_number, track_identity->external_track_type, track_identity->stanag_identity, track_identity->environment, track_identity->atr_confidence_pct, track_identity->atr_model_id, track_identity->atr_conf_tier, track_identity->sidc_context);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRACK_IDENTITY, (const char *)track_identity, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_CRC);
#endif
}

#if MAVLINK_MSG_ID_TRACK_IDENTITY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_track_identity_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, const uint8_t *track_uid, const uint8_t *parent_track_uid, uint32_t target_set_id, uint64_t first_detected_usec, float id_confidence, uint8_t origin_sysid, uint8_t origin_sensor, uint8_t id_method, uint8_t pid_status, uint8_t track_rel, uint8_t target_class, uint8_t target_force, const char *id_basis, const char *external_track_number, uint8_t external_track_type, uint8_t stanag_identity, uint8_t environment, uint8_t atr_confidence_pct, uint16_t atr_model_id, uint8_t atr_conf_tier, uint8_t sidc_context)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, first_detected_usec);
    _mav_put_uint32_t(buf, 16, target_set_id);
    _mav_put_float(buf, 20, id_confidence);
    _mav_put_uint16_t(buf, 24, atr_model_id);
    _mav_put_uint8_t(buf, 58, origin_sysid);
    _mav_put_uint8_t(buf, 59, origin_sensor);
    _mav_put_uint8_t(buf, 60, id_method);
    _mav_put_uint8_t(buf, 61, pid_status);
    _mav_put_uint8_t(buf, 62, track_rel);
    _mav_put_uint8_t(buf, 63, target_class);
    _mav_put_uint8_t(buf, 64, target_force);
    _mav_put_uint8_t(buf, 135, external_track_type);
    _mav_put_uint8_t(buf, 136, stanag_identity);
    _mav_put_uint8_t(buf, 137, environment);
    _mav_put_uint8_t(buf, 138, atr_confidence_pct);
    _mav_put_uint8_t(buf, 139, atr_conf_tier);
    _mav_put_uint8_t(buf, 140, sidc_context);
    _mav_put_uint8_t_array(buf, 26, track_uid, 16);
    _mav_put_uint8_t_array(buf, 42, parent_track_uid, 16);
    _mav_put_char_array(buf, 65, id_basis, 50);
    _mav_put_char_array(buf, 115, external_track_number, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRACK_IDENTITY, buf, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_CRC);
#else
    mavlink_track_identity_t *packet = (mavlink_track_identity_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->first_detected_usec = first_detected_usec;
    packet->target_set_id = target_set_id;
    packet->id_confidence = id_confidence;
    packet->atr_model_id = atr_model_id;
    packet->origin_sysid = origin_sysid;
    packet->origin_sensor = origin_sensor;
    packet->id_method = id_method;
    packet->pid_status = pid_status;
    packet->track_rel = track_rel;
    packet->target_class = target_class;
    packet->target_force = target_force;
    packet->external_track_type = external_track_type;
    packet->stanag_identity = stanag_identity;
    packet->environment = environment;
    packet->atr_confidence_pct = atr_confidence_pct;
    packet->atr_conf_tier = atr_conf_tier;
    packet->sidc_context = sidc_context;
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet->parent_track_uid, parent_track_uid, sizeof(uint8_t)*16);
    mav_array_memcpy(packet->id_basis, id_basis, sizeof(char)*50);
    mav_array_memcpy(packet->external_track_number, external_track_number, sizeof(char)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRACK_IDENTITY, (const char *)packet, MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN, MAVLINK_MSG_ID_TRACK_IDENTITY_CRC);
#endif
}
#endif

#endif

// MESSAGE TRACK_IDENTITY UNPACKING


/**
 * @brief Get field time_usec from track_identity message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_track_identity_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field track_uid from track_identity message
 *
 * @return  Globally-unique track identifier (UUID). Stable across the whole chain.
 */
static inline uint16_t mavlink_msg_track_identity_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  26);
}

/**
 * @brief Get field parent_track_uid from track_identity message
 *
 * @return  Parent track UID for split/merge/re-id lineage. All-zero if none.
 */
static inline uint16_t mavlink_msg_track_identity_get_parent_track_uid(const mavlink_message_t* msg, uint8_t *parent_track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, parent_track_uid, 16,  42);
}

/**
 * @brief Get field target_set_id from track_identity message
 *
 * @return  Associated target set identifier, if any. 0 = none.
 */
static inline uint32_t mavlink_msg_track_identity_get_target_set_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field first_detected_usec from track_identity message
 *
 * @return [us] Time the object was first detected (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_track_identity_get_first_detected_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field id_confidence from track_identity message
 *
 * @return  Confidence of identification [0.0-1.0]. NaN if not provided.
 */
static inline float mavlink_msg_track_identity_get_id_confidence(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field origin_sysid from track_identity message
 *
 * @return  System ID of the platform that originated/owns this track.
 */
static inline uint8_t mavlink_msg_track_identity_get_origin_sysid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  58);
}

/**
 * @brief Get field origin_sensor from track_identity message
 *
 * @return  Sensor/method underlying the current identification.
 */
static inline uint8_t mavlink_msg_track_identity_get_origin_sensor(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  59);
}

/**
 * @brief Get field id_method from track_identity message
 *
 * @return  Method by which identification was reached.
 */
static inline uint8_t mavlink_msg_track_identity_get_id_method(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  60);
}

/**
 * @brief Get field pid_status from track_identity message
 *
 * @return  Positive identification status (descriptive).
 */
static inline uint8_t mavlink_msg_track_identity_get_pid_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  61);
}

/**
 * @brief Get field track_rel from track_identity message
 *
 * @return  Relationship to parent track (split/merge/re-id).
 */
static inline uint8_t mavlink_msg_track_identity_get_track_rel(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  62);
}

/**
 * @brief Get field target_class from track_identity message
 *
 * @return  Classification (what it is), distinct from id_method (how it was identified).
 */
static inline uint8_t mavlink_msg_track_identity_get_target_class(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  63);
}

/**
 * @brief Get field target_force from track_identity message
 *
 * @return  Force affiliation.
 */
static inline uint8_t mavlink_msg_track_identity_get_target_force(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  64);
}

/**
 * @brief Get field id_basis from track_identity message
 *
 * @return  Optional free-text basis/notes for the identification (null-terminated).
 */
static inline uint16_t mavlink_msg_track_identity_get_id_basis(const mavlink_message_t* msg, char *id_basis)
{
    return _MAV_RETURN_char_array(msg, id_basis, 50,  65);
}

/**
 * @brief Get field external_track_number from track_identity message
 *
 * @return  External/joint track number (e.g. Link 16 track number or VMF URN), as text for gateway round-trip. Empty if none. Encoding per external_track_type.
 */
static inline uint16_t mavlink_msg_track_identity_get_external_track_number(const mavlink_message_t* msg, char *external_track_number)
{
    return _MAV_RETURN_char_array(msg, external_track_number, 20,  115);
}

/**
 * @brief Get field external_track_type from track_identity message
 *
 * @return  Namespace of external_track_number.
 */
static inline uint8_t mavlink_msg_track_identity_get_external_track_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  135);
}

/**
 * @brief Get field stanag_identity from track_identity message
 *
 * @return  STANAG/APP-6 standard identity (richer than target_force).
 */
static inline uint8_t mavlink_msg_track_identity_get_stanag_identity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  136);
}

/**
 * @brief Get field environment from track_identity message
 *
 * @return  STANAG/APP-6 battle dimension / environment.
 */
static inline uint8_t mavlink_msg_track_identity_get_environment(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  137);
}

/**
 * @brief Get field atr_confidence_pct from track_identity message
 *
 * @return [%] ATR model confidence [0-100]. 255 = N/A. Raw score; the C2 node owns any ROE threshold.
 */
static inline uint8_t mavlink_msg_track_identity_get_atr_confidence_pct(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  138);
}

/**
 * @brief Get field atr_model_id from track_identity message
 *
 * @return  Identifier of the ATR model/version that produced atr_confidence_pct. 0 = unspecified.
 */
static inline uint16_t mavlink_msg_track_identity_get_atr_model_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field atr_conf_tier from track_identity message
 *
 * @return  OPTIONAL advisory display tier derived from atr_confidence_pct. Not for automated ROE.
 */
static inline uint8_t mavlink_msg_track_identity_get_atr_conf_tier(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  139);
}

/**
 * @brief Get field sidc_context from track_identity message
 *
 * @return  Reality context (MIL-STD-2525D SIDC digit 3): real-world vs exercise vs simulation. Prevents a live track and an exercise/simulated track from being indistinguishable on a joint net.
 */
static inline uint8_t mavlink_msg_track_identity_get_sidc_context(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  140);
}

/**
 * @brief Decode a track_identity message into a struct
 *
 * @param msg The message to decode
 * @param track_identity C-struct to decode the message contents into
 */
static inline void mavlink_msg_track_identity_decode(const mavlink_message_t* msg, mavlink_track_identity_t* track_identity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    track_identity->time_usec = mavlink_msg_track_identity_get_time_usec(msg);
    track_identity->first_detected_usec = mavlink_msg_track_identity_get_first_detected_usec(msg);
    track_identity->target_set_id = mavlink_msg_track_identity_get_target_set_id(msg);
    track_identity->id_confidence = mavlink_msg_track_identity_get_id_confidence(msg);
    track_identity->atr_model_id = mavlink_msg_track_identity_get_atr_model_id(msg);
    mavlink_msg_track_identity_get_track_uid(msg, track_identity->track_uid);
    mavlink_msg_track_identity_get_parent_track_uid(msg, track_identity->parent_track_uid);
    track_identity->origin_sysid = mavlink_msg_track_identity_get_origin_sysid(msg);
    track_identity->origin_sensor = mavlink_msg_track_identity_get_origin_sensor(msg);
    track_identity->id_method = mavlink_msg_track_identity_get_id_method(msg);
    track_identity->pid_status = mavlink_msg_track_identity_get_pid_status(msg);
    track_identity->track_rel = mavlink_msg_track_identity_get_track_rel(msg);
    track_identity->target_class = mavlink_msg_track_identity_get_target_class(msg);
    track_identity->target_force = mavlink_msg_track_identity_get_target_force(msg);
    mavlink_msg_track_identity_get_id_basis(msg, track_identity->id_basis);
    mavlink_msg_track_identity_get_external_track_number(msg, track_identity->external_track_number);
    track_identity->external_track_type = mavlink_msg_track_identity_get_external_track_type(msg);
    track_identity->stanag_identity = mavlink_msg_track_identity_get_stanag_identity(msg);
    track_identity->environment = mavlink_msg_track_identity_get_environment(msg);
    track_identity->atr_confidence_pct = mavlink_msg_track_identity_get_atr_confidence_pct(msg);
    track_identity->atr_conf_tier = mavlink_msg_track_identity_get_atr_conf_tier(msg);
    track_identity->sidc_context = mavlink_msg_track_identity_get_sidc_context(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TRACK_IDENTITY_LEN? msg->len : MAVLINK_MSG_ID_TRACK_IDENTITY_LEN;
        memset(track_identity, 0, MAVLINK_MSG_ID_TRACK_IDENTITY_LEN);
    memcpy(track_identity, _MAV_PAYLOAD(msg), len);
#endif
}
