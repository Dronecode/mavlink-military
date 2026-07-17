#pragma once
// MESSAGE SPLASH_CORRECTION PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_SPLASH_CORRECTION 53021


typedef struct __mavlink_splash_correction_t {
 uint64_t time_usec; /*< [us] Timestamp of observation (UNIX epoch, microseconds UTC).*/
 int32_t lat; /*< [degE7] Observed splash latitude, WGS84.*/
 int32_t lon; /*< [degE7] Observed splash longitude, WGS84.*/
 float alt; /*< [m] Observed splash altitude, MSL.*/
 float cep_expected; /*< [m] Estimated CEP of the observed splash.*/
 uint16_t sequence; /*<  Fire mission sequence number this correction applies to.*/
 uint8_t type_detected; /*<  Coarse splash detector cue (implementation-defined; e.g. 0=unknown, 1=smoke, 2=explosion). Doctrinal observed-fire adjustment is carried by deviation, range_spot, hob, impact_surface, and obscuration.*/
 uint8_t deviation; /*<  Deviation spotting relative to the observer-target line.*/
 uint8_t range_spot; /*<  Range spotting along the observer-target line.*/
 uint8_t hob; /*<  Height-of-burst spotting (observation, not munition/fuze setting).*/
 uint8_t impact_surface; /*<  Supplementary: what was struck / what the splash landed in/on.*/
 uint8_t obscuration; /*<  Supplementary: cause of obscuration, if observation was masked.*/
 uint8_t command; /*<  Procedural fire-mission command accompanying this spotting (NONE if pure spotting).*/
 uint8_t track_uid[16]; /*<  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.*/
} mavlink_splash_correction_t;

#define MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN 49
#define MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN 49
#define MAVLINK_MSG_ID_53021_LEN 49
#define MAVLINK_MSG_ID_53021_MIN_LEN 49

#define MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC 94
#define MAVLINK_MSG_ID_53021_CRC 94

#define MAVLINK_MSG_SPLASH_CORRECTION_FIELD_TRACK_UID_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SPLASH_CORRECTION { \
    53021, \
    "SPLASH_CORRECTION", \
    14, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_splash_correction_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_splash_correction_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_splash_correction_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_splash_correction_t, alt) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_splash_correction_t, sequence) }, \
         { "type_detected", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_splash_correction_t, type_detected) }, \
         { "cep_expected", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_splash_correction_t, cep_expected) }, \
         { "deviation", NULL, MAVLINK_TYPE_UINT8_T, 0, 27, offsetof(mavlink_splash_correction_t, deviation) }, \
         { "range_spot", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_splash_correction_t, range_spot) }, \
         { "hob", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_splash_correction_t, hob) }, \
         { "impact_surface", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_splash_correction_t, impact_surface) }, \
         { "obscuration", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_splash_correction_t, obscuration) }, \
         { "command", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_splash_correction_t, command) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 33, offsetof(mavlink_splash_correction_t, track_uid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SPLASH_CORRECTION { \
    "SPLASH_CORRECTION", \
    14, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_splash_correction_t, time_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_splash_correction_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_splash_correction_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_splash_correction_t, alt) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_splash_correction_t, sequence) }, \
         { "type_detected", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_splash_correction_t, type_detected) }, \
         { "cep_expected", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_splash_correction_t, cep_expected) }, \
         { "deviation", NULL, MAVLINK_TYPE_UINT8_T, 0, 27, offsetof(mavlink_splash_correction_t, deviation) }, \
         { "range_spot", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_splash_correction_t, range_spot) }, \
         { "hob", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_splash_correction_t, hob) }, \
         { "impact_surface", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_splash_correction_t, impact_surface) }, \
         { "obscuration", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_splash_correction_t, obscuration) }, \
         { "command", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_splash_correction_t, command) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 33, offsetof(mavlink_splash_correction_t, track_uid) }, \
         } \
}
#endif

/**
 * @brief Pack a splash_correction message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp of observation (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Observed splash latitude, WGS84.
 * @param lon [degE7] Observed splash longitude, WGS84.
 * @param alt [m] Observed splash altitude, MSL.
 * @param sequence  Fire mission sequence number this correction applies to.
 * @param type_detected  Coarse splash detector cue (implementation-defined; e.g. 0=unknown, 1=smoke, 2=explosion). Doctrinal observed-fire adjustment is carried by deviation, range_spot, hob, impact_surface, and obscuration.
 * @param cep_expected [m] Estimated CEP of the observed splash.
 * @param deviation  Deviation spotting relative to the observer-target line.
 * @param range_spot  Range spotting along the observer-target line.
 * @param hob  Height-of-burst spotting (observation, not munition/fuze setting).
 * @param impact_surface  Supplementary: what was struck / what the splash landed in/on.
 * @param obscuration  Supplementary: cause of obscuration, if observation was masked.
 * @param command  Procedural fire-mission command accompanying this spotting (NONE if pure spotting).
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_splash_correction_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t lat, int32_t lon, float alt, uint16_t sequence, uint8_t type_detected, float cep_expected, uint8_t deviation, uint8_t range_spot, uint8_t hob, uint8_t impact_surface, uint8_t obscuration, uint8_t command, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, cep_expected);
    _mav_put_uint16_t(buf, 24, sequence);
    _mav_put_uint8_t(buf, 26, type_detected);
    _mav_put_uint8_t(buf, 27, deviation);
    _mav_put_uint8_t(buf, 28, range_spot);
    _mav_put_uint8_t(buf, 29, hob);
    _mav_put_uint8_t(buf, 30, impact_surface);
    _mav_put_uint8_t(buf, 31, obscuration);
    _mav_put_uint8_t(buf, 32, command);
    _mav_put_uint8_t_array(buf, 33, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN);
#else
    mavlink_splash_correction_t packet;
    packet.time_usec = time_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.cep_expected = cep_expected;
    packet.sequence = sequence;
    packet.type_detected = type_detected;
    packet.deviation = deviation;
    packet.range_spot = range_spot;
    packet.hob = hob;
    packet.impact_surface = impact_surface;
    packet.obscuration = obscuration;
    packet.command = command;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SPLASH_CORRECTION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC);
}

/**
 * @brief Pack a splash_correction message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp of observation (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Observed splash latitude, WGS84.
 * @param lon [degE7] Observed splash longitude, WGS84.
 * @param alt [m] Observed splash altitude, MSL.
 * @param sequence  Fire mission sequence number this correction applies to.
 * @param type_detected  Coarse splash detector cue (implementation-defined; e.g. 0=unknown, 1=smoke, 2=explosion). Doctrinal observed-fire adjustment is carried by deviation, range_spot, hob, impact_surface, and obscuration.
 * @param cep_expected [m] Estimated CEP of the observed splash.
 * @param deviation  Deviation spotting relative to the observer-target line.
 * @param range_spot  Range spotting along the observer-target line.
 * @param hob  Height-of-burst spotting (observation, not munition/fuze setting).
 * @param impact_surface  Supplementary: what was struck / what the splash landed in/on.
 * @param obscuration  Supplementary: cause of obscuration, if observation was masked.
 * @param command  Procedural fire-mission command accompanying this spotting (NONE if pure spotting).
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_splash_correction_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t lat, int32_t lon, float alt, uint16_t sequence, uint8_t type_detected, float cep_expected, uint8_t deviation, uint8_t range_spot, uint8_t hob, uint8_t impact_surface, uint8_t obscuration, uint8_t command, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, cep_expected);
    _mav_put_uint16_t(buf, 24, sequence);
    _mav_put_uint8_t(buf, 26, type_detected);
    _mav_put_uint8_t(buf, 27, deviation);
    _mav_put_uint8_t(buf, 28, range_spot);
    _mav_put_uint8_t(buf, 29, hob);
    _mav_put_uint8_t(buf, 30, impact_surface);
    _mav_put_uint8_t(buf, 31, obscuration);
    _mav_put_uint8_t(buf, 32, command);
    _mav_put_uint8_t_array(buf, 33, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN);
#else
    mavlink_splash_correction_t packet;
    packet.time_usec = time_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.cep_expected = cep_expected;
    packet.sequence = sequence;
    packet.type_detected = type_detected;
    packet.deviation = deviation;
    packet.range_spot = range_spot;
    packet.hob = hob;
    packet.impact_surface = impact_surface;
    packet.obscuration = obscuration;
    packet.command = command;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SPLASH_CORRECTION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN);
#endif
}

/**
 * @brief Pack a splash_correction message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp of observation (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Observed splash latitude, WGS84.
 * @param lon [degE7] Observed splash longitude, WGS84.
 * @param alt [m] Observed splash altitude, MSL.
 * @param sequence  Fire mission sequence number this correction applies to.
 * @param type_detected  Coarse splash detector cue (implementation-defined; e.g. 0=unknown, 1=smoke, 2=explosion). Doctrinal observed-fire adjustment is carried by deviation, range_spot, hob, impact_surface, and obscuration.
 * @param cep_expected [m] Estimated CEP of the observed splash.
 * @param deviation  Deviation spotting relative to the observer-target line.
 * @param range_spot  Range spotting along the observer-target line.
 * @param hob  Height-of-burst spotting (observation, not munition/fuze setting).
 * @param impact_surface  Supplementary: what was struck / what the splash landed in/on.
 * @param obscuration  Supplementary: cause of obscuration, if observation was masked.
 * @param command  Procedural fire-mission command accompanying this spotting (NONE if pure spotting).
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_splash_correction_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,int32_t lat,int32_t lon,float alt,uint16_t sequence,uint8_t type_detected,float cep_expected,uint8_t deviation,uint8_t range_spot,uint8_t hob,uint8_t impact_surface,uint8_t obscuration,uint8_t command,const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, cep_expected);
    _mav_put_uint16_t(buf, 24, sequence);
    _mav_put_uint8_t(buf, 26, type_detected);
    _mav_put_uint8_t(buf, 27, deviation);
    _mav_put_uint8_t(buf, 28, range_spot);
    _mav_put_uint8_t(buf, 29, hob);
    _mav_put_uint8_t(buf, 30, impact_surface);
    _mav_put_uint8_t(buf, 31, obscuration);
    _mav_put_uint8_t(buf, 32, command);
    _mav_put_uint8_t_array(buf, 33, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN);
#else
    mavlink_splash_correction_t packet;
    packet.time_usec = time_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.cep_expected = cep_expected;
    packet.sequence = sequence;
    packet.type_detected = type_detected;
    packet.deviation = deviation;
    packet.range_spot = range_spot;
    packet.hob = hob;
    packet.impact_surface = impact_surface;
    packet.obscuration = obscuration;
    packet.command = command;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SPLASH_CORRECTION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC);
}

/**
 * @brief Encode a splash_correction struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param splash_correction C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_splash_correction_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_splash_correction_t* splash_correction)
{
    return mavlink_msg_splash_correction_pack(system_id, component_id, msg, splash_correction->time_usec, splash_correction->lat, splash_correction->lon, splash_correction->alt, splash_correction->sequence, splash_correction->type_detected, splash_correction->cep_expected, splash_correction->deviation, splash_correction->range_spot, splash_correction->hob, splash_correction->impact_surface, splash_correction->obscuration, splash_correction->command, splash_correction->track_uid);
}

/**
 * @brief Encode a splash_correction struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param splash_correction C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_splash_correction_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_splash_correction_t* splash_correction)
{
    return mavlink_msg_splash_correction_pack_chan(system_id, component_id, chan, msg, splash_correction->time_usec, splash_correction->lat, splash_correction->lon, splash_correction->alt, splash_correction->sequence, splash_correction->type_detected, splash_correction->cep_expected, splash_correction->deviation, splash_correction->range_spot, splash_correction->hob, splash_correction->impact_surface, splash_correction->obscuration, splash_correction->command, splash_correction->track_uid);
}

/**
 * @brief Encode a splash_correction struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param splash_correction C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_splash_correction_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_splash_correction_t* splash_correction)
{
    return mavlink_msg_splash_correction_pack_status(system_id, component_id, _status, msg,  splash_correction->time_usec, splash_correction->lat, splash_correction->lon, splash_correction->alt, splash_correction->sequence, splash_correction->type_detected, splash_correction->cep_expected, splash_correction->deviation, splash_correction->range_spot, splash_correction->hob, splash_correction->impact_surface, splash_correction->obscuration, splash_correction->command, splash_correction->track_uid);
}

/**
 * @brief Send a splash_correction message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp of observation (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Observed splash latitude, WGS84.
 * @param lon [degE7] Observed splash longitude, WGS84.
 * @param alt [m] Observed splash altitude, MSL.
 * @param sequence  Fire mission sequence number this correction applies to.
 * @param type_detected  Coarse splash detector cue (implementation-defined; e.g. 0=unknown, 1=smoke, 2=explosion). Doctrinal observed-fire adjustment is carried by deviation, range_spot, hob, impact_surface, and obscuration.
 * @param cep_expected [m] Estimated CEP of the observed splash.
 * @param deviation  Deviation spotting relative to the observer-target line.
 * @param range_spot  Range spotting along the observer-target line.
 * @param hob  Height-of-burst spotting (observation, not munition/fuze setting).
 * @param impact_surface  Supplementary: what was struck / what the splash landed in/on.
 * @param obscuration  Supplementary: cause of obscuration, if observation was masked.
 * @param command  Procedural fire-mission command accompanying this spotting (NONE if pure spotting).
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_splash_correction_send(mavlink_channel_t chan, uint64_t time_usec, int32_t lat, int32_t lon, float alt, uint16_t sequence, uint8_t type_detected, float cep_expected, uint8_t deviation, uint8_t range_spot, uint8_t hob, uint8_t impact_surface, uint8_t obscuration, uint8_t command, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, cep_expected);
    _mav_put_uint16_t(buf, 24, sequence);
    _mav_put_uint8_t(buf, 26, type_detected);
    _mav_put_uint8_t(buf, 27, deviation);
    _mav_put_uint8_t(buf, 28, range_spot);
    _mav_put_uint8_t(buf, 29, hob);
    _mav_put_uint8_t(buf, 30, impact_surface);
    _mav_put_uint8_t(buf, 31, obscuration);
    _mav_put_uint8_t(buf, 32, command);
    _mav_put_uint8_t_array(buf, 33, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPLASH_CORRECTION, buf, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC);
#else
    mavlink_splash_correction_t packet;
    packet.time_usec = time_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.cep_expected = cep_expected;
    packet.sequence = sequence;
    packet.type_detected = type_detected;
    packet.deviation = deviation;
    packet.range_spot = range_spot;
    packet.hob = hob;
    packet.impact_surface = impact_surface;
    packet.obscuration = obscuration;
    packet.command = command;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPLASH_CORRECTION, (const char *)&packet, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC);
#endif
}

/**
 * @brief Send a splash_correction message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_splash_correction_send_struct(mavlink_channel_t chan, const mavlink_splash_correction_t* splash_correction)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_splash_correction_send(chan, splash_correction->time_usec, splash_correction->lat, splash_correction->lon, splash_correction->alt, splash_correction->sequence, splash_correction->type_detected, splash_correction->cep_expected, splash_correction->deviation, splash_correction->range_spot, splash_correction->hob, splash_correction->impact_surface, splash_correction->obscuration, splash_correction->command, splash_correction->track_uid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPLASH_CORRECTION, (const char *)splash_correction, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC);
#endif
}

#if MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_splash_correction_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, int32_t lat, int32_t lon, float alt, uint16_t sequence, uint8_t type_detected, float cep_expected, uint8_t deviation, uint8_t range_spot, uint8_t hob, uint8_t impact_surface, uint8_t obscuration, uint8_t command, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, lat);
    _mav_put_int32_t(buf, 12, lon);
    _mav_put_float(buf, 16, alt);
    _mav_put_float(buf, 20, cep_expected);
    _mav_put_uint16_t(buf, 24, sequence);
    _mav_put_uint8_t(buf, 26, type_detected);
    _mav_put_uint8_t(buf, 27, deviation);
    _mav_put_uint8_t(buf, 28, range_spot);
    _mav_put_uint8_t(buf, 29, hob);
    _mav_put_uint8_t(buf, 30, impact_surface);
    _mav_put_uint8_t(buf, 31, obscuration);
    _mav_put_uint8_t(buf, 32, command);
    _mav_put_uint8_t_array(buf, 33, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPLASH_CORRECTION, buf, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC);
#else
    mavlink_splash_correction_t *packet = (mavlink_splash_correction_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->cep_expected = cep_expected;
    packet->sequence = sequence;
    packet->type_detected = type_detected;
    packet->deviation = deviation;
    packet->range_spot = range_spot;
    packet->hob = hob;
    packet->impact_surface = impact_surface;
    packet->obscuration = obscuration;
    packet->command = command;
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SPLASH_CORRECTION, (const char *)packet, MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN, MAVLINK_MSG_ID_SPLASH_CORRECTION_CRC);
#endif
}
#endif

#endif

// MESSAGE SPLASH_CORRECTION UNPACKING


/**
 * @brief Get field time_usec from splash_correction message
 *
 * @return [us] Timestamp of observation (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_splash_correction_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field lat from splash_correction message
 *
 * @return [degE7] Observed splash latitude, WGS84.
 */
static inline int32_t mavlink_msg_splash_correction_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field lon from splash_correction message
 *
 * @return [degE7] Observed splash longitude, WGS84.
 */
static inline int32_t mavlink_msg_splash_correction_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field alt from splash_correction message
 *
 * @return [m] Observed splash altitude, MSL.
 */
static inline float mavlink_msg_splash_correction_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field sequence from splash_correction message
 *
 * @return  Fire mission sequence number this correction applies to.
 */
static inline uint16_t mavlink_msg_splash_correction_get_sequence(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field type_detected from splash_correction message
 *
 * @return  Coarse splash detector cue (implementation-defined; e.g. 0=unknown, 1=smoke, 2=explosion). Doctrinal observed-fire adjustment is carried by deviation, range_spot, hob, impact_surface, and obscuration.
 */
static inline uint8_t mavlink_msg_splash_correction_get_type_detected(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  26);
}

/**
 * @brief Get field cep_expected from splash_correction message
 *
 * @return [m] Estimated CEP of the observed splash.
 */
static inline float mavlink_msg_splash_correction_get_cep_expected(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field deviation from splash_correction message
 *
 * @return  Deviation spotting relative to the observer-target line.
 */
static inline uint8_t mavlink_msg_splash_correction_get_deviation(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  27);
}

/**
 * @brief Get field range_spot from splash_correction message
 *
 * @return  Range spotting along the observer-target line.
 */
static inline uint8_t mavlink_msg_splash_correction_get_range_spot(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  28);
}

/**
 * @brief Get field hob from splash_correction message
 *
 * @return  Height-of-burst spotting (observation, not munition/fuze setting).
 */
static inline uint8_t mavlink_msg_splash_correction_get_hob(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  29);
}

/**
 * @brief Get field impact_surface from splash_correction message
 *
 * @return  Supplementary: what was struck / what the splash landed in/on.
 */
static inline uint8_t mavlink_msg_splash_correction_get_impact_surface(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  30);
}

/**
 * @brief Get field obscuration from splash_correction message
 *
 * @return  Supplementary: cause of obscuration, if observation was masked.
 */
static inline uint8_t mavlink_msg_splash_correction_get_obscuration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  31);
}

/**
 * @brief Get field command from splash_correction message
 *
 * @return  Procedural fire-mission command accompanying this spotting (NONE if pure spotting).
 */
static inline uint8_t mavlink_msg_splash_correction_get_command(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  32);
}

/**
 * @brief Get field track_uid from splash_correction message
 *
 * @return  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 */
static inline uint16_t mavlink_msg_splash_correction_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  33);
}

/**
 * @brief Decode a splash_correction message into a struct
 *
 * @param msg The message to decode
 * @param splash_correction C-struct to decode the message contents into
 */
static inline void mavlink_msg_splash_correction_decode(const mavlink_message_t* msg, mavlink_splash_correction_t* splash_correction)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    splash_correction->time_usec = mavlink_msg_splash_correction_get_time_usec(msg);
    splash_correction->lat = mavlink_msg_splash_correction_get_lat(msg);
    splash_correction->lon = mavlink_msg_splash_correction_get_lon(msg);
    splash_correction->alt = mavlink_msg_splash_correction_get_alt(msg);
    splash_correction->cep_expected = mavlink_msg_splash_correction_get_cep_expected(msg);
    splash_correction->sequence = mavlink_msg_splash_correction_get_sequence(msg);
    splash_correction->type_detected = mavlink_msg_splash_correction_get_type_detected(msg);
    splash_correction->deviation = mavlink_msg_splash_correction_get_deviation(msg);
    splash_correction->range_spot = mavlink_msg_splash_correction_get_range_spot(msg);
    splash_correction->hob = mavlink_msg_splash_correction_get_hob(msg);
    splash_correction->impact_surface = mavlink_msg_splash_correction_get_impact_surface(msg);
    splash_correction->obscuration = mavlink_msg_splash_correction_get_obscuration(msg);
    splash_correction->command = mavlink_msg_splash_correction_get_command(msg);
    mavlink_msg_splash_correction_get_track_uid(msg, splash_correction->track_uid);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN? msg->len : MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN;
        memset(splash_correction, 0, MAVLINK_MSG_ID_SPLASH_CORRECTION_LEN);
    memcpy(splash_correction, _MAV_PAYLOAD(msg), len);
#endif
}
