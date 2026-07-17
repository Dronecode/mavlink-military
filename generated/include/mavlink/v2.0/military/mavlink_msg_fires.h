#pragma once
// MESSAGE FIRES PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FIRES 53020


typedef struct __mavlink_fires_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint64_t time_impact_usec; /*< [us] Expected time of impact (UNIX epoch, microseconds UTC).*/
 int32_t lat; /*< [degE7] Target latitude, WGS84.*/
 int32_t lon; /*< [degE7] Target longitude, WGS84.*/
 float alt; /*< [m] Target altitude, MSL.*/
 uint32_t effector_id; /*<  Identifier of the assigned effector.*/
 float cep_expected; /*< [m] Expected circular error probable at impact.*/
 uint16_t sequence; /*<  Fire mission sequence number.*/
 uint16_t prf_code; /*<  Laser designator PRF code for SAL weapons (e.g. 1111-1788). 0 = no laser code assigned.*/
 uint8_t store_id; /*<  Target store/bay on a multi-store carrier. 0 = system default / vehicle itself (e.g. OWA).*/
 uint8_t requested_effect; /*<  Coarse requested effect (intent), for non-artillery/OWA effectors. For call-for-fire missions use munition_class + fuze_action instead.*/
 uint8_t munition_class; /*<  Call-for-fire projectile/shell class (method of engagement). UNKNOWN if N/A.*/
 uint8_t fuze_mode; /*<  Call-for-fire requested fuze mode (method of engagement). UNKNOWN if N/A.*/
 uint8_t hob_intent; /*<  Airburst height-of-burst intent for proximity/time modes (descriptive selector, not a value).*/
 uint8_t fuze_mofa_capable; /*<  1 if the fielded fuze is multi-option (e.g. M782 MOFA) and settable to any mode; 0 otherwise. Capability flag, not a mode.*/
 uint8_t track_uid[16]; /*<  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.*/
} mavlink_fires_t;

#define MAVLINK_MSG_ID_FIRES_LEN 62
#define MAVLINK_MSG_ID_FIRES_MIN_LEN 62
#define MAVLINK_MSG_ID_53020_LEN 62
#define MAVLINK_MSG_ID_53020_MIN_LEN 62

#define MAVLINK_MSG_ID_FIRES_CRC 16
#define MAVLINK_MSG_ID_53020_CRC 16

#define MAVLINK_MSG_FIRES_FIELD_TRACK_UID_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FIRES { \
    53020, \
    "FIRES", \
    16, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fires_t, time_usec) }, \
         { "time_impact_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fires_t, time_impact_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_fires_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_fires_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_fires_t, alt) }, \
         { "effector_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_fires_t, effector_id) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 36, offsetof(mavlink_fires_t, sequence) }, \
         { "cep_expected", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_fires_t, cep_expected) }, \
         { "prf_code", NULL, MAVLINK_TYPE_UINT16_T, 0, 38, offsetof(mavlink_fires_t, prf_code) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_fires_t, store_id) }, \
         { "requested_effect", NULL, MAVLINK_TYPE_UINT8_T, 0, 41, offsetof(mavlink_fires_t, requested_effect) }, \
         { "munition_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_fires_t, munition_class) }, \
         { "fuze_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 43, offsetof(mavlink_fires_t, fuze_mode) }, \
         { "hob_intent", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_fires_t, hob_intent) }, \
         { "fuze_mofa_capable", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_fires_t, fuze_mofa_capable) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 46, offsetof(mavlink_fires_t, track_uid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FIRES { \
    "FIRES", \
    16, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fires_t, time_usec) }, \
         { "time_impact_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fires_t, time_impact_usec) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_fires_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_fires_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_fires_t, alt) }, \
         { "effector_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_fires_t, effector_id) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 36, offsetof(mavlink_fires_t, sequence) }, \
         { "cep_expected", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_fires_t, cep_expected) }, \
         { "prf_code", NULL, MAVLINK_TYPE_UINT16_T, 0, 38, offsetof(mavlink_fires_t, prf_code) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_fires_t, store_id) }, \
         { "requested_effect", NULL, MAVLINK_TYPE_UINT8_T, 0, 41, offsetof(mavlink_fires_t, requested_effect) }, \
         { "munition_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_fires_t, munition_class) }, \
         { "fuze_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 43, offsetof(mavlink_fires_t, fuze_mode) }, \
         { "hob_intent", NULL, MAVLINK_TYPE_UINT8_T, 0, 44, offsetof(mavlink_fires_t, hob_intent) }, \
         { "fuze_mofa_capable", NULL, MAVLINK_TYPE_UINT8_T, 0, 45, offsetof(mavlink_fires_t, fuze_mofa_capable) }, \
         { "track_uid", NULL, MAVLINK_TYPE_UINT8_T, 16, 46, offsetof(mavlink_fires_t, track_uid) }, \
         } \
}
#endif

/**
 * @brief Pack a fires message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param time_impact_usec [us] Expected time of impact (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param effector_id  Identifier of the assigned effector.
 * @param sequence  Fire mission sequence number.
 * @param cep_expected [m] Expected circular error probable at impact.
 * @param prf_code  Laser designator PRF code for SAL weapons (e.g. 1111-1788). 0 = no laser code assigned.
 * @param store_id  Target store/bay on a multi-store carrier. 0 = system default / vehicle itself (e.g. OWA).
 * @param requested_effect  Coarse requested effect (intent), for non-artillery/OWA effectors. For call-for-fire missions use munition_class + fuze_action instead.
 * @param munition_class  Call-for-fire projectile/shell class (method of engagement). UNKNOWN if N/A.
 * @param fuze_mode  Call-for-fire requested fuze mode (method of engagement). UNKNOWN if N/A.
 * @param hob_intent  Airburst height-of-burst intent for proximity/time modes (descriptive selector, not a value).
 * @param fuze_mofa_capable  1 if the fielded fuze is multi-option (e.g. M782 MOFA) and settable to any mode; 0 otherwise. Capability flag, not a mode.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fires_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint64_t time_impact_usec, int32_t lat, int32_t lon, float alt, uint32_t effector_id, uint16_t sequence, float cep_expected, uint16_t prf_code, uint8_t store_id, uint8_t requested_effect, uint8_t munition_class, uint8_t fuze_mode, uint8_t hob_intent, uint8_t fuze_mofa_capable, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FIRES_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_impact_usec);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_uint32_t(buf, 28, effector_id);
    _mav_put_float(buf, 32, cep_expected);
    _mav_put_uint16_t(buf, 36, sequence);
    _mav_put_uint16_t(buf, 38, prf_code);
    _mav_put_uint8_t(buf, 40, store_id);
    _mav_put_uint8_t(buf, 41, requested_effect);
    _mav_put_uint8_t(buf, 42, munition_class);
    _mav_put_uint8_t(buf, 43, fuze_mode);
    _mav_put_uint8_t(buf, 44, hob_intent);
    _mav_put_uint8_t(buf, 45, fuze_mofa_capable);
    _mav_put_uint8_t_array(buf, 46, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FIRES_LEN);
#else
    mavlink_fires_t packet;
    packet.time_usec = time_usec;
    packet.time_impact_usec = time_impact_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.effector_id = effector_id;
    packet.cep_expected = cep_expected;
    packet.sequence = sequence;
    packet.prf_code = prf_code;
    packet.store_id = store_id;
    packet.requested_effect = requested_effect;
    packet.munition_class = munition_class;
    packet.fuze_mode = fuze_mode;
    packet.hob_intent = hob_intent;
    packet.fuze_mofa_capable = fuze_mofa_capable;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FIRES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FIRES;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN, MAVLINK_MSG_ID_FIRES_CRC);
}

/**
 * @brief Pack a fires message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param time_impact_usec [us] Expected time of impact (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param effector_id  Identifier of the assigned effector.
 * @param sequence  Fire mission sequence number.
 * @param cep_expected [m] Expected circular error probable at impact.
 * @param prf_code  Laser designator PRF code for SAL weapons (e.g. 1111-1788). 0 = no laser code assigned.
 * @param store_id  Target store/bay on a multi-store carrier. 0 = system default / vehicle itself (e.g. OWA).
 * @param requested_effect  Coarse requested effect (intent), for non-artillery/OWA effectors. For call-for-fire missions use munition_class + fuze_action instead.
 * @param munition_class  Call-for-fire projectile/shell class (method of engagement). UNKNOWN if N/A.
 * @param fuze_mode  Call-for-fire requested fuze mode (method of engagement). UNKNOWN if N/A.
 * @param hob_intent  Airburst height-of-burst intent for proximity/time modes (descriptive selector, not a value).
 * @param fuze_mofa_capable  1 if the fielded fuze is multi-option (e.g. M782 MOFA) and settable to any mode; 0 otherwise. Capability flag, not a mode.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fires_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint64_t time_impact_usec, int32_t lat, int32_t lon, float alt, uint32_t effector_id, uint16_t sequence, float cep_expected, uint16_t prf_code, uint8_t store_id, uint8_t requested_effect, uint8_t munition_class, uint8_t fuze_mode, uint8_t hob_intent, uint8_t fuze_mofa_capable, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FIRES_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_impact_usec);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_uint32_t(buf, 28, effector_id);
    _mav_put_float(buf, 32, cep_expected);
    _mav_put_uint16_t(buf, 36, sequence);
    _mav_put_uint16_t(buf, 38, prf_code);
    _mav_put_uint8_t(buf, 40, store_id);
    _mav_put_uint8_t(buf, 41, requested_effect);
    _mav_put_uint8_t(buf, 42, munition_class);
    _mav_put_uint8_t(buf, 43, fuze_mode);
    _mav_put_uint8_t(buf, 44, hob_intent);
    _mav_put_uint8_t(buf, 45, fuze_mofa_capable);
    _mav_put_uint8_t_array(buf, 46, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FIRES_LEN);
#else
    mavlink_fires_t packet;
    packet.time_usec = time_usec;
    packet.time_impact_usec = time_impact_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.effector_id = effector_id;
    packet.cep_expected = cep_expected;
    packet.sequence = sequence;
    packet.prf_code = prf_code;
    packet.store_id = store_id;
    packet.requested_effect = requested_effect;
    packet.munition_class = munition_class;
    packet.fuze_mode = fuze_mode;
    packet.hob_intent = hob_intent;
    packet.fuze_mofa_capable = fuze_mofa_capable;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FIRES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FIRES;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN, MAVLINK_MSG_ID_FIRES_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN);
#endif
}

/**
 * @brief Pack a fires message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param time_impact_usec [us] Expected time of impact (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param effector_id  Identifier of the assigned effector.
 * @param sequence  Fire mission sequence number.
 * @param cep_expected [m] Expected circular error probable at impact.
 * @param prf_code  Laser designator PRF code for SAL weapons (e.g. 1111-1788). 0 = no laser code assigned.
 * @param store_id  Target store/bay on a multi-store carrier. 0 = system default / vehicle itself (e.g. OWA).
 * @param requested_effect  Coarse requested effect (intent), for non-artillery/OWA effectors. For call-for-fire missions use munition_class + fuze_action instead.
 * @param munition_class  Call-for-fire projectile/shell class (method of engagement). UNKNOWN if N/A.
 * @param fuze_mode  Call-for-fire requested fuze mode (method of engagement). UNKNOWN if N/A.
 * @param hob_intent  Airburst height-of-burst intent for proximity/time modes (descriptive selector, not a value).
 * @param fuze_mofa_capable  1 if the fielded fuze is multi-option (e.g. M782 MOFA) and settable to any mode; 0 otherwise. Capability flag, not a mode.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fires_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint64_t time_impact_usec,int32_t lat,int32_t lon,float alt,uint32_t effector_id,uint16_t sequence,float cep_expected,uint16_t prf_code,uint8_t store_id,uint8_t requested_effect,uint8_t munition_class,uint8_t fuze_mode,uint8_t hob_intent,uint8_t fuze_mofa_capable,const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FIRES_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_impact_usec);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_uint32_t(buf, 28, effector_id);
    _mav_put_float(buf, 32, cep_expected);
    _mav_put_uint16_t(buf, 36, sequence);
    _mav_put_uint16_t(buf, 38, prf_code);
    _mav_put_uint8_t(buf, 40, store_id);
    _mav_put_uint8_t(buf, 41, requested_effect);
    _mav_put_uint8_t(buf, 42, munition_class);
    _mav_put_uint8_t(buf, 43, fuze_mode);
    _mav_put_uint8_t(buf, 44, hob_intent);
    _mav_put_uint8_t(buf, 45, fuze_mofa_capable);
    _mav_put_uint8_t_array(buf, 46, track_uid, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FIRES_LEN);
#else
    mavlink_fires_t packet;
    packet.time_usec = time_usec;
    packet.time_impact_usec = time_impact_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.effector_id = effector_id;
    packet.cep_expected = cep_expected;
    packet.sequence = sequence;
    packet.prf_code = prf_code;
    packet.store_id = store_id;
    packet.requested_effect = requested_effect;
    packet.munition_class = munition_class;
    packet.fuze_mode = fuze_mode;
    packet.hob_intent = hob_intent;
    packet.fuze_mofa_capable = fuze_mofa_capable;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FIRES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FIRES;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN, MAVLINK_MSG_ID_FIRES_CRC);
}

/**
 * @brief Encode a fires struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fires C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fires_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fires_t* fires)
{
    return mavlink_msg_fires_pack(system_id, component_id, msg, fires->time_usec, fires->time_impact_usec, fires->lat, fires->lon, fires->alt, fires->effector_id, fires->sequence, fires->cep_expected, fires->prf_code, fires->store_id, fires->requested_effect, fires->munition_class, fires->fuze_mode, fires->hob_intent, fires->fuze_mofa_capable, fires->track_uid);
}

/**
 * @brief Encode a fires struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fires C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fires_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fires_t* fires)
{
    return mavlink_msg_fires_pack_chan(system_id, component_id, chan, msg, fires->time_usec, fires->time_impact_usec, fires->lat, fires->lon, fires->alt, fires->effector_id, fires->sequence, fires->cep_expected, fires->prf_code, fires->store_id, fires->requested_effect, fires->munition_class, fires->fuze_mode, fires->hob_intent, fires->fuze_mofa_capable, fires->track_uid);
}

/**
 * @brief Encode a fires struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fires C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fires_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fires_t* fires)
{
    return mavlink_msg_fires_pack_status(system_id, component_id, _status, msg,  fires->time_usec, fires->time_impact_usec, fires->lat, fires->lon, fires->alt, fires->effector_id, fires->sequence, fires->cep_expected, fires->prf_code, fires->store_id, fires->requested_effect, fires->munition_class, fires->fuze_mode, fires->hob_intent, fires->fuze_mofa_capable, fires->track_uid);
}

/**
 * @brief Send a fires message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param time_impact_usec [us] Expected time of impact (UNIX epoch, microseconds UTC).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param effector_id  Identifier of the assigned effector.
 * @param sequence  Fire mission sequence number.
 * @param cep_expected [m] Expected circular error probable at impact.
 * @param prf_code  Laser designator PRF code for SAL weapons (e.g. 1111-1788). 0 = no laser code assigned.
 * @param store_id  Target store/bay on a multi-store carrier. 0 = system default / vehicle itself (e.g. OWA).
 * @param requested_effect  Coarse requested effect (intent), for non-artillery/OWA effectors. For call-for-fire missions use munition_class + fuze_action instead.
 * @param munition_class  Call-for-fire projectile/shell class (method of engagement). UNKNOWN if N/A.
 * @param fuze_mode  Call-for-fire requested fuze mode (method of engagement). UNKNOWN if N/A.
 * @param hob_intent  Airburst height-of-burst intent for proximity/time modes (descriptive selector, not a value).
 * @param fuze_mofa_capable  1 if the fielded fuze is multi-option (e.g. M782 MOFA) and settable to any mode; 0 otherwise. Capability flag, not a mode.
 * @param track_uid  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fires_send(mavlink_channel_t chan, uint64_t time_usec, uint64_t time_impact_usec, int32_t lat, int32_t lon, float alt, uint32_t effector_id, uint16_t sequence, float cep_expected, uint16_t prf_code, uint8_t store_id, uint8_t requested_effect, uint8_t munition_class, uint8_t fuze_mode, uint8_t hob_intent, uint8_t fuze_mofa_capable, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FIRES_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_impact_usec);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_uint32_t(buf, 28, effector_id);
    _mav_put_float(buf, 32, cep_expected);
    _mav_put_uint16_t(buf, 36, sequence);
    _mav_put_uint16_t(buf, 38, prf_code);
    _mav_put_uint8_t(buf, 40, store_id);
    _mav_put_uint8_t(buf, 41, requested_effect);
    _mav_put_uint8_t(buf, 42, munition_class);
    _mav_put_uint8_t(buf, 43, fuze_mode);
    _mav_put_uint8_t(buf, 44, hob_intent);
    _mav_put_uint8_t(buf, 45, fuze_mofa_capable);
    _mav_put_uint8_t_array(buf, 46, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FIRES, buf, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN, MAVLINK_MSG_ID_FIRES_CRC);
#else
    mavlink_fires_t packet;
    packet.time_usec = time_usec;
    packet.time_impact_usec = time_impact_usec;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.effector_id = effector_id;
    packet.cep_expected = cep_expected;
    packet.sequence = sequence;
    packet.prf_code = prf_code;
    packet.store_id = store_id;
    packet.requested_effect = requested_effect;
    packet.munition_class = munition_class;
    packet.fuze_mode = fuze_mode;
    packet.hob_intent = hob_intent;
    packet.fuze_mofa_capable = fuze_mofa_capable;
    mav_array_memcpy(packet.track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FIRES, (const char *)&packet, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN, MAVLINK_MSG_ID_FIRES_CRC);
#endif
}

/**
 * @brief Send a fires message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fires_send_struct(mavlink_channel_t chan, const mavlink_fires_t* fires)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fires_send(chan, fires->time_usec, fires->time_impact_usec, fires->lat, fires->lon, fires->alt, fires->effector_id, fires->sequence, fires->cep_expected, fires->prf_code, fires->store_id, fires->requested_effect, fires->munition_class, fires->fuze_mode, fires->hob_intent, fires->fuze_mofa_capable, fires->track_uid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FIRES, (const char *)fires, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN, MAVLINK_MSG_ID_FIRES_CRC);
#endif
}

#if MAVLINK_MSG_ID_FIRES_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fires_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint64_t time_impact_usec, int32_t lat, int32_t lon, float alt, uint32_t effector_id, uint16_t sequence, float cep_expected, uint16_t prf_code, uint8_t store_id, uint8_t requested_effect, uint8_t munition_class, uint8_t fuze_mode, uint8_t hob_intent, uint8_t fuze_mofa_capable, const uint8_t *track_uid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_impact_usec);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_float(buf, 24, alt);
    _mav_put_uint32_t(buf, 28, effector_id);
    _mav_put_float(buf, 32, cep_expected);
    _mav_put_uint16_t(buf, 36, sequence);
    _mav_put_uint16_t(buf, 38, prf_code);
    _mav_put_uint8_t(buf, 40, store_id);
    _mav_put_uint8_t(buf, 41, requested_effect);
    _mav_put_uint8_t(buf, 42, munition_class);
    _mav_put_uint8_t(buf, 43, fuze_mode);
    _mav_put_uint8_t(buf, 44, hob_intent);
    _mav_put_uint8_t(buf, 45, fuze_mofa_capable);
    _mav_put_uint8_t_array(buf, 46, track_uid, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FIRES, buf, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN, MAVLINK_MSG_ID_FIRES_CRC);
#else
    mavlink_fires_t *packet = (mavlink_fires_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->time_impact_usec = time_impact_usec;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->effector_id = effector_id;
    packet->cep_expected = cep_expected;
    packet->sequence = sequence;
    packet->prf_code = prf_code;
    packet->store_id = store_id;
    packet->requested_effect = requested_effect;
    packet->munition_class = munition_class;
    packet->fuze_mode = fuze_mode;
    packet->hob_intent = hob_intent;
    packet->fuze_mofa_capable = fuze_mofa_capable;
    mav_array_memcpy(packet->track_uid, track_uid, sizeof(uint8_t)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FIRES, (const char *)packet, MAVLINK_MSG_ID_FIRES_MIN_LEN, MAVLINK_MSG_ID_FIRES_LEN, MAVLINK_MSG_ID_FIRES_CRC);
#endif
}
#endif

#endif

// MESSAGE FIRES UNPACKING


/**
 * @brief Get field time_usec from fires message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_fires_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field time_impact_usec from fires message
 *
 * @return [us] Expected time of impact (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_fires_get_time_impact_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field lat from fires message
 *
 * @return [degE7] Target latitude, WGS84.
 */
static inline int32_t mavlink_msg_fires_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field lon from fires message
 *
 * @return [degE7] Target longitude, WGS84.
 */
static inline int32_t mavlink_msg_fires_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field alt from fires message
 *
 * @return [m] Target altitude, MSL.
 */
static inline float mavlink_msg_fires_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field effector_id from fires message
 *
 * @return  Identifier of the assigned effector.
 */
static inline uint32_t mavlink_msg_fires_get_effector_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  28);
}

/**
 * @brief Get field sequence from fires message
 *
 * @return  Fire mission sequence number.
 */
static inline uint16_t mavlink_msg_fires_get_sequence(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  36);
}

/**
 * @brief Get field cep_expected from fires message
 *
 * @return [m] Expected circular error probable at impact.
 */
static inline float mavlink_msg_fires_get_cep_expected(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field prf_code from fires message
 *
 * @return  Laser designator PRF code for SAL weapons (e.g. 1111-1788). 0 = no laser code assigned.
 */
static inline uint16_t mavlink_msg_fires_get_prf_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  38);
}

/**
 * @brief Get field store_id from fires message
 *
 * @return  Target store/bay on a multi-store carrier. 0 = system default / vehicle itself (e.g. OWA).
 */
static inline uint8_t mavlink_msg_fires_get_store_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  40);
}

/**
 * @brief Get field requested_effect from fires message
 *
 * @return  Coarse requested effect (intent), for non-artillery/OWA effectors. For call-for-fire missions use munition_class + fuze_action instead.
 */
static inline uint8_t mavlink_msg_fires_get_requested_effect(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  41);
}

/**
 * @brief Get field munition_class from fires message
 *
 * @return  Call-for-fire projectile/shell class (method of engagement). UNKNOWN if N/A.
 */
static inline uint8_t mavlink_msg_fires_get_munition_class(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  42);
}

/**
 * @brief Get field fuze_mode from fires message
 *
 * @return  Call-for-fire requested fuze mode (method of engagement). UNKNOWN if N/A.
 */
static inline uint8_t mavlink_msg_fires_get_fuze_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  43);
}

/**
 * @brief Get field hob_intent from fires message
 *
 * @return  Airburst height-of-burst intent for proximity/time modes (descriptive selector, not a value).
 */
static inline uint8_t mavlink_msg_fires_get_hob_intent(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  44);
}

/**
 * @brief Get field fuze_mofa_capable from fires message
 *
 * @return  1 if the fielded fuze is multi-option (e.g. M782 MOFA) and settable to any mode; 0 otherwise. Capability flag, not a mode.
 */
static inline uint8_t mavlink_msg_fires_get_fuze_mofa_capable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  45);
}

/**
 * @brief Get field track_uid from fires message
 *
 * @return  Globally-unique track identifier (UUID) of the TRACK_IDENTITY this message correlates to. Ties the engagement/assessment to the authorized track. All-zero if not associated.
 */
static inline uint16_t mavlink_msg_fires_get_track_uid(const mavlink_message_t* msg, uint8_t *track_uid)
{
    return _MAV_RETURN_uint8_t_array(msg, track_uid, 16,  46);
}

/**
 * @brief Decode a fires message into a struct
 *
 * @param msg The message to decode
 * @param fires C-struct to decode the message contents into
 */
static inline void mavlink_msg_fires_decode(const mavlink_message_t* msg, mavlink_fires_t* fires)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fires->time_usec = mavlink_msg_fires_get_time_usec(msg);
    fires->time_impact_usec = mavlink_msg_fires_get_time_impact_usec(msg);
    fires->lat = mavlink_msg_fires_get_lat(msg);
    fires->lon = mavlink_msg_fires_get_lon(msg);
    fires->alt = mavlink_msg_fires_get_alt(msg);
    fires->effector_id = mavlink_msg_fires_get_effector_id(msg);
    fires->cep_expected = mavlink_msg_fires_get_cep_expected(msg);
    fires->sequence = mavlink_msg_fires_get_sequence(msg);
    fires->prf_code = mavlink_msg_fires_get_prf_code(msg);
    fires->store_id = mavlink_msg_fires_get_store_id(msg);
    fires->requested_effect = mavlink_msg_fires_get_requested_effect(msg);
    fires->munition_class = mavlink_msg_fires_get_munition_class(msg);
    fires->fuze_mode = mavlink_msg_fires_get_fuze_mode(msg);
    fires->hob_intent = mavlink_msg_fires_get_hob_intent(msg);
    fires->fuze_mofa_capable = mavlink_msg_fires_get_fuze_mofa_capable(msg);
    mavlink_msg_fires_get_track_uid(msg, fires->track_uid);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FIRES_LEN? msg->len : MAVLINK_MSG_ID_FIRES_LEN;
        memset(fires, 0, MAVLINK_MSG_ID_FIRES_LEN);
    memcpy(fires, _MAV_PAYLOAD(msg), len);
#endif
}
