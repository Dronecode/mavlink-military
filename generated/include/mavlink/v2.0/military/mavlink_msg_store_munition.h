#pragma once
// MESSAGE STORE_MUNITION PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_STORE_MUNITION 53035


typedef struct __mavlink_store_munition_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 float mass; /*< [kg] Munition mass. NaN if unknown.*/
 uint16_t quantity_remaining; /*<  Count of this munition remaining available on the store/carrier.*/
 char external_track_number[20]; /*<  External/joint track or store reference for gateway correlation. Empty if none.*/
 char nomenclature[30]; /*<  Munition nomenclature/designation (null-terminated).*/
 uint8_t store_id; /*<  Store instance identifier.*/
 uint8_t munition_type; /*<  Munition type code (implementation-defined; consistent with ESAD_STATE.munition_type).*/
 uint8_t guidance; /*<  Coarse guidance category.*/
 uint8_t warhead; /*<  Coarse warhead category.*/
 uint8_t arming_status; /*<  Safe/armed state (mirrored from ESAD for convenience).*/
 uint8_t fuze_health; /*<  Coarse fuze HEALTH (functioning/fault), not fuze configuration.*/
 uint8_t external_track_type; /*<  Namespace of external_track_number.*/
 uint8_t munition_family; /*<  Composite-munition family (finer than the warhead/guidance pair). Descriptive.*/
 uint8_t munition_payload; /*<  Composite-munition payload category. Descriptive.*/
 uint8_t warhead_mode; /*<  Coarse selectable warhead MODE currently set for a selectable/multi-mode warhead (e.g. surface vs penetrate on a multi-drop magazine store). Reports the mode only. It is a COARSE enum and MUST NOT be widened to carry a fuze timing / inter-stage delay value; the actual timing is device-internal and configured on the component bus (e.g. DroneCAN) below the FMU.*/
 uint8_t sd_duration; /*<  Scatterable-mine self-destruct duration CATEGORY (not exact seconds), for mine payloads.*/
} mavlink_store_munition_t;

#define MAVLINK_MSG_ID_STORE_MUNITION_LEN 75
#define MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN 75
#define MAVLINK_MSG_ID_53035_LEN 75
#define MAVLINK_MSG_ID_53035_MIN_LEN 75

#define MAVLINK_MSG_ID_STORE_MUNITION_CRC 156
#define MAVLINK_MSG_ID_53035_CRC 156

#define MAVLINK_MSG_STORE_MUNITION_FIELD_EXTERNAL_TRACK_NUMBER_LEN 20
#define MAVLINK_MSG_STORE_MUNITION_FIELD_NOMENCLATURE_LEN 30

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_STORE_MUNITION { \
    53035, \
    "STORE_MUNITION", \
    16, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_store_munition_t, time_usec) }, \
         { "mass", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_store_munition_t, mass) }, \
         { "external_track_number", NULL, MAVLINK_TYPE_CHAR, 20, 14, offsetof(mavlink_store_munition_t, external_track_number) }, \
         { "nomenclature", NULL, MAVLINK_TYPE_CHAR, 30, 34, offsetof(mavlink_store_munition_t, nomenclature) }, \
         { "quantity_remaining", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_store_munition_t, quantity_remaining) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 64, offsetof(mavlink_store_munition_t, store_id) }, \
         { "munition_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 65, offsetof(mavlink_store_munition_t, munition_type) }, \
         { "guidance", NULL, MAVLINK_TYPE_UINT8_T, 0, 66, offsetof(mavlink_store_munition_t, guidance) }, \
         { "warhead", NULL, MAVLINK_TYPE_UINT8_T, 0, 67, offsetof(mavlink_store_munition_t, warhead) }, \
         { "arming_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 68, offsetof(mavlink_store_munition_t, arming_status) }, \
         { "fuze_health", NULL, MAVLINK_TYPE_UINT8_T, 0, 69, offsetof(mavlink_store_munition_t, fuze_health) }, \
         { "external_track_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 70, offsetof(mavlink_store_munition_t, external_track_type) }, \
         { "munition_family", NULL, MAVLINK_TYPE_UINT8_T, 0, 71, offsetof(mavlink_store_munition_t, munition_family) }, \
         { "munition_payload", NULL, MAVLINK_TYPE_UINT8_T, 0, 72, offsetof(mavlink_store_munition_t, munition_payload) }, \
         { "warhead_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 73, offsetof(mavlink_store_munition_t, warhead_mode) }, \
         { "sd_duration", NULL, MAVLINK_TYPE_UINT8_T, 0, 74, offsetof(mavlink_store_munition_t, sd_duration) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_STORE_MUNITION { \
    "STORE_MUNITION", \
    16, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_store_munition_t, time_usec) }, \
         { "mass", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_store_munition_t, mass) }, \
         { "external_track_number", NULL, MAVLINK_TYPE_CHAR, 20, 14, offsetof(mavlink_store_munition_t, external_track_number) }, \
         { "nomenclature", NULL, MAVLINK_TYPE_CHAR, 30, 34, offsetof(mavlink_store_munition_t, nomenclature) }, \
         { "quantity_remaining", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_store_munition_t, quantity_remaining) }, \
         { "store_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 64, offsetof(mavlink_store_munition_t, store_id) }, \
         { "munition_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 65, offsetof(mavlink_store_munition_t, munition_type) }, \
         { "guidance", NULL, MAVLINK_TYPE_UINT8_T, 0, 66, offsetof(mavlink_store_munition_t, guidance) }, \
         { "warhead", NULL, MAVLINK_TYPE_UINT8_T, 0, 67, offsetof(mavlink_store_munition_t, warhead) }, \
         { "arming_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 68, offsetof(mavlink_store_munition_t, arming_status) }, \
         { "fuze_health", NULL, MAVLINK_TYPE_UINT8_T, 0, 69, offsetof(mavlink_store_munition_t, fuze_health) }, \
         { "external_track_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 70, offsetof(mavlink_store_munition_t, external_track_type) }, \
         { "munition_family", NULL, MAVLINK_TYPE_UINT8_T, 0, 71, offsetof(mavlink_store_munition_t, munition_family) }, \
         { "munition_payload", NULL, MAVLINK_TYPE_UINT8_T, 0, 72, offsetof(mavlink_store_munition_t, munition_payload) }, \
         { "warhead_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 73, offsetof(mavlink_store_munition_t, warhead_mode) }, \
         { "sd_duration", NULL, MAVLINK_TYPE_UINT8_T, 0, 74, offsetof(mavlink_store_munition_t, sd_duration) }, \
         } \
}
#endif

/**
 * @brief Pack a store_munition message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param mass [kg] Munition mass. NaN if unknown.
 * @param external_track_number  External/joint track or store reference for gateway correlation. Empty if none.
 * @param nomenclature  Munition nomenclature/designation (null-terminated).
 * @param quantity_remaining  Count of this munition remaining available on the store/carrier.
 * @param store_id  Store instance identifier.
 * @param munition_type  Munition type code (implementation-defined; consistent with ESAD_STATE.munition_type).
 * @param guidance  Coarse guidance category.
 * @param warhead  Coarse warhead category.
 * @param arming_status  Safe/armed state (mirrored from ESAD for convenience).
 * @param fuze_health  Coarse fuze HEALTH (functioning/fault), not fuze configuration.
 * @param external_track_type  Namespace of external_track_number.
 * @param munition_family  Composite-munition family (finer than the warhead/guidance pair). Descriptive.
 * @param munition_payload  Composite-munition payload category. Descriptive.
 * @param warhead_mode  Coarse selectable warhead MODE currently set for a selectable/multi-mode warhead (e.g. surface vs penetrate on a multi-drop magazine store). Reports the mode only. It is a COARSE enum and MUST NOT be widened to carry a fuze timing / inter-stage delay value; the actual timing is device-internal and configured on the component bus (e.g. DroneCAN) below the FMU.
 * @param sd_duration  Scatterable-mine self-destruct duration CATEGORY (not exact seconds), for mine payloads.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_munition_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, float mass, const char *external_track_number, const char *nomenclature, uint16_t quantity_remaining, uint8_t store_id, uint8_t munition_type, uint8_t guidance, uint8_t warhead, uint8_t arming_status, uint8_t fuze_health, uint8_t external_track_type, uint8_t munition_family, uint8_t munition_payload, uint8_t warhead_mode, uint8_t sd_duration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_MUNITION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mass);
    _mav_put_uint16_t(buf, 12, quantity_remaining);
    _mav_put_uint8_t(buf, 64, store_id);
    _mav_put_uint8_t(buf, 65, munition_type);
    _mav_put_uint8_t(buf, 66, guidance);
    _mav_put_uint8_t(buf, 67, warhead);
    _mav_put_uint8_t(buf, 68, arming_status);
    _mav_put_uint8_t(buf, 69, fuze_health);
    _mav_put_uint8_t(buf, 70, external_track_type);
    _mav_put_uint8_t(buf, 71, munition_family);
    _mav_put_uint8_t(buf, 72, munition_payload);
    _mav_put_uint8_t(buf, 73, warhead_mode);
    _mav_put_uint8_t(buf, 74, sd_duration);
    _mav_put_char_array(buf, 14, external_track_number, 20);
    _mav_put_char_array(buf, 34, nomenclature, 30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_MUNITION_LEN);
#else
    mavlink_store_munition_t packet;
    packet.time_usec = time_usec;
    packet.mass = mass;
    packet.quantity_remaining = quantity_remaining;
    packet.store_id = store_id;
    packet.munition_type = munition_type;
    packet.guidance = guidance;
    packet.warhead = warhead;
    packet.arming_status = arming_status;
    packet.fuze_health = fuze_health;
    packet.external_track_type = external_track_type;
    packet.munition_family = munition_family;
    packet.munition_payload = munition_payload;
    packet.warhead_mode = warhead_mode;
    packet.sd_duration = sd_duration;
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet.nomenclature, nomenclature, sizeof(char)*30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_MUNITION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_MUNITION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN, MAVLINK_MSG_ID_STORE_MUNITION_CRC);
}

/**
 * @brief Pack a store_munition message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param mass [kg] Munition mass. NaN if unknown.
 * @param external_track_number  External/joint track or store reference for gateway correlation. Empty if none.
 * @param nomenclature  Munition nomenclature/designation (null-terminated).
 * @param quantity_remaining  Count of this munition remaining available on the store/carrier.
 * @param store_id  Store instance identifier.
 * @param munition_type  Munition type code (implementation-defined; consistent with ESAD_STATE.munition_type).
 * @param guidance  Coarse guidance category.
 * @param warhead  Coarse warhead category.
 * @param arming_status  Safe/armed state (mirrored from ESAD for convenience).
 * @param fuze_health  Coarse fuze HEALTH (functioning/fault), not fuze configuration.
 * @param external_track_type  Namespace of external_track_number.
 * @param munition_family  Composite-munition family (finer than the warhead/guidance pair). Descriptive.
 * @param munition_payload  Composite-munition payload category. Descriptive.
 * @param warhead_mode  Coarse selectable warhead MODE currently set for a selectable/multi-mode warhead (e.g. surface vs penetrate on a multi-drop magazine store). Reports the mode only. It is a COARSE enum and MUST NOT be widened to carry a fuze timing / inter-stage delay value; the actual timing is device-internal and configured on the component bus (e.g. DroneCAN) below the FMU.
 * @param sd_duration  Scatterable-mine self-destruct duration CATEGORY (not exact seconds), for mine payloads.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_munition_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, float mass, const char *external_track_number, const char *nomenclature, uint16_t quantity_remaining, uint8_t store_id, uint8_t munition_type, uint8_t guidance, uint8_t warhead, uint8_t arming_status, uint8_t fuze_health, uint8_t external_track_type, uint8_t munition_family, uint8_t munition_payload, uint8_t warhead_mode, uint8_t sd_duration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_MUNITION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mass);
    _mav_put_uint16_t(buf, 12, quantity_remaining);
    _mav_put_uint8_t(buf, 64, store_id);
    _mav_put_uint8_t(buf, 65, munition_type);
    _mav_put_uint8_t(buf, 66, guidance);
    _mav_put_uint8_t(buf, 67, warhead);
    _mav_put_uint8_t(buf, 68, arming_status);
    _mav_put_uint8_t(buf, 69, fuze_health);
    _mav_put_uint8_t(buf, 70, external_track_type);
    _mav_put_uint8_t(buf, 71, munition_family);
    _mav_put_uint8_t(buf, 72, munition_payload);
    _mav_put_uint8_t(buf, 73, warhead_mode);
    _mav_put_uint8_t(buf, 74, sd_duration);
    _mav_put_char_array(buf, 14, external_track_number, 20);
    _mav_put_char_array(buf, 34, nomenclature, 30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_MUNITION_LEN);
#else
    mavlink_store_munition_t packet;
    packet.time_usec = time_usec;
    packet.mass = mass;
    packet.quantity_remaining = quantity_remaining;
    packet.store_id = store_id;
    packet.munition_type = munition_type;
    packet.guidance = guidance;
    packet.warhead = warhead;
    packet.arming_status = arming_status;
    packet.fuze_health = fuze_health;
    packet.external_track_type = external_track_type;
    packet.munition_family = munition_family;
    packet.munition_payload = munition_payload;
    packet.warhead_mode = warhead_mode;
    packet.sd_duration = sd_duration;
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet.nomenclature, nomenclature, sizeof(char)*30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_MUNITION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_MUNITION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN, MAVLINK_MSG_ID_STORE_MUNITION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN);
#endif
}

/**
 * @brief Pack a store_munition message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param mass [kg] Munition mass. NaN if unknown.
 * @param external_track_number  External/joint track or store reference for gateway correlation. Empty if none.
 * @param nomenclature  Munition nomenclature/designation (null-terminated).
 * @param quantity_remaining  Count of this munition remaining available on the store/carrier.
 * @param store_id  Store instance identifier.
 * @param munition_type  Munition type code (implementation-defined; consistent with ESAD_STATE.munition_type).
 * @param guidance  Coarse guidance category.
 * @param warhead  Coarse warhead category.
 * @param arming_status  Safe/armed state (mirrored from ESAD for convenience).
 * @param fuze_health  Coarse fuze HEALTH (functioning/fault), not fuze configuration.
 * @param external_track_type  Namespace of external_track_number.
 * @param munition_family  Composite-munition family (finer than the warhead/guidance pair). Descriptive.
 * @param munition_payload  Composite-munition payload category. Descriptive.
 * @param warhead_mode  Coarse selectable warhead MODE currently set for a selectable/multi-mode warhead (e.g. surface vs penetrate on a multi-drop magazine store). Reports the mode only. It is a COARSE enum and MUST NOT be widened to carry a fuze timing / inter-stage delay value; the actual timing is device-internal and configured on the component bus (e.g. DroneCAN) below the FMU.
 * @param sd_duration  Scatterable-mine self-destruct duration CATEGORY (not exact seconds), for mine payloads.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_store_munition_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,float mass,const char *external_track_number,const char *nomenclature,uint16_t quantity_remaining,uint8_t store_id,uint8_t munition_type,uint8_t guidance,uint8_t warhead,uint8_t arming_status,uint8_t fuze_health,uint8_t external_track_type,uint8_t munition_family,uint8_t munition_payload,uint8_t warhead_mode,uint8_t sd_duration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_MUNITION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mass);
    _mav_put_uint16_t(buf, 12, quantity_remaining);
    _mav_put_uint8_t(buf, 64, store_id);
    _mav_put_uint8_t(buf, 65, munition_type);
    _mav_put_uint8_t(buf, 66, guidance);
    _mav_put_uint8_t(buf, 67, warhead);
    _mav_put_uint8_t(buf, 68, arming_status);
    _mav_put_uint8_t(buf, 69, fuze_health);
    _mav_put_uint8_t(buf, 70, external_track_type);
    _mav_put_uint8_t(buf, 71, munition_family);
    _mav_put_uint8_t(buf, 72, munition_payload);
    _mav_put_uint8_t(buf, 73, warhead_mode);
    _mav_put_uint8_t(buf, 74, sd_duration);
    _mav_put_char_array(buf, 14, external_track_number, 20);
    _mav_put_char_array(buf, 34, nomenclature, 30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STORE_MUNITION_LEN);
#else
    mavlink_store_munition_t packet;
    packet.time_usec = time_usec;
    packet.mass = mass;
    packet.quantity_remaining = quantity_remaining;
    packet.store_id = store_id;
    packet.munition_type = munition_type;
    packet.guidance = guidance;
    packet.warhead = warhead;
    packet.arming_status = arming_status;
    packet.fuze_health = fuze_health;
    packet.external_track_type = external_track_type;
    packet.munition_family = munition_family;
    packet.munition_payload = munition_payload;
    packet.warhead_mode = warhead_mode;
    packet.sd_duration = sd_duration;
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet.nomenclature, nomenclature, sizeof(char)*30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STORE_MUNITION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STORE_MUNITION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN, MAVLINK_MSG_ID_STORE_MUNITION_CRC);
}

/**
 * @brief Encode a store_munition struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param store_munition C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_munition_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_store_munition_t* store_munition)
{
    return mavlink_msg_store_munition_pack(system_id, component_id, msg, store_munition->time_usec, store_munition->mass, store_munition->external_track_number, store_munition->nomenclature, store_munition->quantity_remaining, store_munition->store_id, store_munition->munition_type, store_munition->guidance, store_munition->warhead, store_munition->arming_status, store_munition->fuze_health, store_munition->external_track_type, store_munition->munition_family, store_munition->munition_payload, store_munition->warhead_mode, store_munition->sd_duration);
}

/**
 * @brief Encode a store_munition struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param store_munition C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_munition_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_store_munition_t* store_munition)
{
    return mavlink_msg_store_munition_pack_chan(system_id, component_id, chan, msg, store_munition->time_usec, store_munition->mass, store_munition->external_track_number, store_munition->nomenclature, store_munition->quantity_remaining, store_munition->store_id, store_munition->munition_type, store_munition->guidance, store_munition->warhead, store_munition->arming_status, store_munition->fuze_health, store_munition->external_track_type, store_munition->munition_family, store_munition->munition_payload, store_munition->warhead_mode, store_munition->sd_duration);
}

/**
 * @brief Encode a store_munition struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param store_munition C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_store_munition_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_store_munition_t* store_munition)
{
    return mavlink_msg_store_munition_pack_status(system_id, component_id, _status, msg,  store_munition->time_usec, store_munition->mass, store_munition->external_track_number, store_munition->nomenclature, store_munition->quantity_remaining, store_munition->store_id, store_munition->munition_type, store_munition->guidance, store_munition->warhead, store_munition->arming_status, store_munition->fuze_health, store_munition->external_track_type, store_munition->munition_family, store_munition->munition_payload, store_munition->warhead_mode, store_munition->sd_duration);
}

/**
 * @brief Send a store_munition message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param mass [kg] Munition mass. NaN if unknown.
 * @param external_track_number  External/joint track or store reference for gateway correlation. Empty if none.
 * @param nomenclature  Munition nomenclature/designation (null-terminated).
 * @param quantity_remaining  Count of this munition remaining available on the store/carrier.
 * @param store_id  Store instance identifier.
 * @param munition_type  Munition type code (implementation-defined; consistent with ESAD_STATE.munition_type).
 * @param guidance  Coarse guidance category.
 * @param warhead  Coarse warhead category.
 * @param arming_status  Safe/armed state (mirrored from ESAD for convenience).
 * @param fuze_health  Coarse fuze HEALTH (functioning/fault), not fuze configuration.
 * @param external_track_type  Namespace of external_track_number.
 * @param munition_family  Composite-munition family (finer than the warhead/guidance pair). Descriptive.
 * @param munition_payload  Composite-munition payload category. Descriptive.
 * @param warhead_mode  Coarse selectable warhead MODE currently set for a selectable/multi-mode warhead (e.g. surface vs penetrate on a multi-drop magazine store). Reports the mode only. It is a COARSE enum and MUST NOT be widened to carry a fuze timing / inter-stage delay value; the actual timing is device-internal and configured on the component bus (e.g. DroneCAN) below the FMU.
 * @param sd_duration  Scatterable-mine self-destruct duration CATEGORY (not exact seconds), for mine payloads.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_store_munition_send(mavlink_channel_t chan, uint64_t time_usec, float mass, const char *external_track_number, const char *nomenclature, uint16_t quantity_remaining, uint8_t store_id, uint8_t munition_type, uint8_t guidance, uint8_t warhead, uint8_t arming_status, uint8_t fuze_health, uint8_t external_track_type, uint8_t munition_family, uint8_t munition_payload, uint8_t warhead_mode, uint8_t sd_duration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STORE_MUNITION_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mass);
    _mav_put_uint16_t(buf, 12, quantity_remaining);
    _mav_put_uint8_t(buf, 64, store_id);
    _mav_put_uint8_t(buf, 65, munition_type);
    _mav_put_uint8_t(buf, 66, guidance);
    _mav_put_uint8_t(buf, 67, warhead);
    _mav_put_uint8_t(buf, 68, arming_status);
    _mav_put_uint8_t(buf, 69, fuze_health);
    _mav_put_uint8_t(buf, 70, external_track_type);
    _mav_put_uint8_t(buf, 71, munition_family);
    _mav_put_uint8_t(buf, 72, munition_payload);
    _mav_put_uint8_t(buf, 73, warhead_mode);
    _mav_put_uint8_t(buf, 74, sd_duration);
    _mav_put_char_array(buf, 14, external_track_number, 20);
    _mav_put_char_array(buf, 34, nomenclature, 30);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_MUNITION, buf, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN, MAVLINK_MSG_ID_STORE_MUNITION_CRC);
#else
    mavlink_store_munition_t packet;
    packet.time_usec = time_usec;
    packet.mass = mass;
    packet.quantity_remaining = quantity_remaining;
    packet.store_id = store_id;
    packet.munition_type = munition_type;
    packet.guidance = guidance;
    packet.warhead = warhead;
    packet.arming_status = arming_status;
    packet.fuze_health = fuze_health;
    packet.external_track_type = external_track_type;
    packet.munition_family = munition_family;
    packet.munition_payload = munition_payload;
    packet.warhead_mode = warhead_mode;
    packet.sd_duration = sd_duration;
    mav_array_memcpy(packet.external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet.nomenclature, nomenclature, sizeof(char)*30);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_MUNITION, (const char *)&packet, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN, MAVLINK_MSG_ID_STORE_MUNITION_CRC);
#endif
}

/**
 * @brief Send a store_munition message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_store_munition_send_struct(mavlink_channel_t chan, const mavlink_store_munition_t* store_munition)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_store_munition_send(chan, store_munition->time_usec, store_munition->mass, store_munition->external_track_number, store_munition->nomenclature, store_munition->quantity_remaining, store_munition->store_id, store_munition->munition_type, store_munition->guidance, store_munition->warhead, store_munition->arming_status, store_munition->fuze_health, store_munition->external_track_type, store_munition->munition_family, store_munition->munition_payload, store_munition->warhead_mode, store_munition->sd_duration);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_MUNITION, (const char *)store_munition, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN, MAVLINK_MSG_ID_STORE_MUNITION_CRC);
#endif
}

#if MAVLINK_MSG_ID_STORE_MUNITION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_store_munition_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, float mass, const char *external_track_number, const char *nomenclature, uint16_t quantity_remaining, uint8_t store_id, uint8_t munition_type, uint8_t guidance, uint8_t warhead, uint8_t arming_status, uint8_t fuze_health, uint8_t external_track_type, uint8_t munition_family, uint8_t munition_payload, uint8_t warhead_mode, uint8_t sd_duration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, mass);
    _mav_put_uint16_t(buf, 12, quantity_remaining);
    _mav_put_uint8_t(buf, 64, store_id);
    _mav_put_uint8_t(buf, 65, munition_type);
    _mav_put_uint8_t(buf, 66, guidance);
    _mav_put_uint8_t(buf, 67, warhead);
    _mav_put_uint8_t(buf, 68, arming_status);
    _mav_put_uint8_t(buf, 69, fuze_health);
    _mav_put_uint8_t(buf, 70, external_track_type);
    _mav_put_uint8_t(buf, 71, munition_family);
    _mav_put_uint8_t(buf, 72, munition_payload);
    _mav_put_uint8_t(buf, 73, warhead_mode);
    _mav_put_uint8_t(buf, 74, sd_duration);
    _mav_put_char_array(buf, 14, external_track_number, 20);
    _mav_put_char_array(buf, 34, nomenclature, 30);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_MUNITION, buf, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN, MAVLINK_MSG_ID_STORE_MUNITION_CRC);
#else
    mavlink_store_munition_t *packet = (mavlink_store_munition_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->mass = mass;
    packet->quantity_remaining = quantity_remaining;
    packet->store_id = store_id;
    packet->munition_type = munition_type;
    packet->guidance = guidance;
    packet->warhead = warhead;
    packet->arming_status = arming_status;
    packet->fuze_health = fuze_health;
    packet->external_track_type = external_track_type;
    packet->munition_family = munition_family;
    packet->munition_payload = munition_payload;
    packet->warhead_mode = warhead_mode;
    packet->sd_duration = sd_duration;
    mav_array_memcpy(packet->external_track_number, external_track_number, sizeof(char)*20);
    mav_array_memcpy(packet->nomenclature, nomenclature, sizeof(char)*30);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STORE_MUNITION, (const char *)packet, MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN, MAVLINK_MSG_ID_STORE_MUNITION_LEN, MAVLINK_MSG_ID_STORE_MUNITION_CRC);
#endif
}
#endif

#endif

// MESSAGE STORE_MUNITION UNPACKING


/**
 * @brief Get field time_usec from store_munition message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_store_munition_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field mass from store_munition message
 *
 * @return [kg] Munition mass. NaN if unknown.
 */
static inline float mavlink_msg_store_munition_get_mass(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field external_track_number from store_munition message
 *
 * @return  External/joint track or store reference for gateway correlation. Empty if none.
 */
static inline uint16_t mavlink_msg_store_munition_get_external_track_number(const mavlink_message_t* msg, char *external_track_number)
{
    return _MAV_RETURN_char_array(msg, external_track_number, 20,  14);
}

/**
 * @brief Get field nomenclature from store_munition message
 *
 * @return  Munition nomenclature/designation (null-terminated).
 */
static inline uint16_t mavlink_msg_store_munition_get_nomenclature(const mavlink_message_t* msg, char *nomenclature)
{
    return _MAV_RETURN_char_array(msg, nomenclature, 30,  34);
}

/**
 * @brief Get field quantity_remaining from store_munition message
 *
 * @return  Count of this munition remaining available on the store/carrier.
 */
static inline uint16_t mavlink_msg_store_munition_get_quantity_remaining(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field store_id from store_munition message
 *
 * @return  Store instance identifier.
 */
static inline uint8_t mavlink_msg_store_munition_get_store_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  64);
}

/**
 * @brief Get field munition_type from store_munition message
 *
 * @return  Munition type code (implementation-defined; consistent with ESAD_STATE.munition_type).
 */
static inline uint8_t mavlink_msg_store_munition_get_munition_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  65);
}

/**
 * @brief Get field guidance from store_munition message
 *
 * @return  Coarse guidance category.
 */
static inline uint8_t mavlink_msg_store_munition_get_guidance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  66);
}

/**
 * @brief Get field warhead from store_munition message
 *
 * @return  Coarse warhead category.
 */
static inline uint8_t mavlink_msg_store_munition_get_warhead(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  67);
}

/**
 * @brief Get field arming_status from store_munition message
 *
 * @return  Safe/armed state (mirrored from ESAD for convenience).
 */
static inline uint8_t mavlink_msg_store_munition_get_arming_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  68);
}

/**
 * @brief Get field fuze_health from store_munition message
 *
 * @return  Coarse fuze HEALTH (functioning/fault), not fuze configuration.
 */
static inline uint8_t mavlink_msg_store_munition_get_fuze_health(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  69);
}

/**
 * @brief Get field external_track_type from store_munition message
 *
 * @return  Namespace of external_track_number.
 */
static inline uint8_t mavlink_msg_store_munition_get_external_track_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  70);
}

/**
 * @brief Get field munition_family from store_munition message
 *
 * @return  Composite-munition family (finer than the warhead/guidance pair). Descriptive.
 */
static inline uint8_t mavlink_msg_store_munition_get_munition_family(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  71);
}

/**
 * @brief Get field munition_payload from store_munition message
 *
 * @return  Composite-munition payload category. Descriptive.
 */
static inline uint8_t mavlink_msg_store_munition_get_munition_payload(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  72);
}

/**
 * @brief Get field warhead_mode from store_munition message
 *
 * @return  Coarse selectable warhead MODE currently set for a selectable/multi-mode warhead (e.g. surface vs penetrate on a multi-drop magazine store). Reports the mode only. It is a COARSE enum and MUST NOT be widened to carry a fuze timing / inter-stage delay value; the actual timing is device-internal and configured on the component bus (e.g. DroneCAN) below the FMU.
 */
static inline uint8_t mavlink_msg_store_munition_get_warhead_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  73);
}

/**
 * @brief Get field sd_duration from store_munition message
 *
 * @return  Scatterable-mine self-destruct duration CATEGORY (not exact seconds), for mine payloads.
 */
static inline uint8_t mavlink_msg_store_munition_get_sd_duration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  74);
}

/**
 * @brief Decode a store_munition message into a struct
 *
 * @param msg The message to decode
 * @param store_munition C-struct to decode the message contents into
 */
static inline void mavlink_msg_store_munition_decode(const mavlink_message_t* msg, mavlink_store_munition_t* store_munition)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    store_munition->time_usec = mavlink_msg_store_munition_get_time_usec(msg);
    store_munition->mass = mavlink_msg_store_munition_get_mass(msg);
    store_munition->quantity_remaining = mavlink_msg_store_munition_get_quantity_remaining(msg);
    mavlink_msg_store_munition_get_external_track_number(msg, store_munition->external_track_number);
    mavlink_msg_store_munition_get_nomenclature(msg, store_munition->nomenclature);
    store_munition->store_id = mavlink_msg_store_munition_get_store_id(msg);
    store_munition->munition_type = mavlink_msg_store_munition_get_munition_type(msg);
    store_munition->guidance = mavlink_msg_store_munition_get_guidance(msg);
    store_munition->warhead = mavlink_msg_store_munition_get_warhead(msg);
    store_munition->arming_status = mavlink_msg_store_munition_get_arming_status(msg);
    store_munition->fuze_health = mavlink_msg_store_munition_get_fuze_health(msg);
    store_munition->external_track_type = mavlink_msg_store_munition_get_external_track_type(msg);
    store_munition->munition_family = mavlink_msg_store_munition_get_munition_family(msg);
    store_munition->munition_payload = mavlink_msg_store_munition_get_munition_payload(msg);
    store_munition->warhead_mode = mavlink_msg_store_munition_get_warhead_mode(msg);
    store_munition->sd_duration = mavlink_msg_store_munition_get_sd_duration(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_STORE_MUNITION_LEN? msg->len : MAVLINK_MSG_ID_STORE_MUNITION_LEN;
        memset(store_munition, 0, MAVLINK_MSG_ID_STORE_MUNITION_LEN);
    memcpy(store_munition, _MAV_PAYLOAD(msg), len);
#endif
}
