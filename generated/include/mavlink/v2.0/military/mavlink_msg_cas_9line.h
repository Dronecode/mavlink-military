#pragma once
// MESSAGE CAS_9LINE PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_CAS_9LINE 53060


typedef struct __mavlink_cas_9line_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 int32_t ip_lat; /*< [degE7] Line 1: initial point / battle position latitude, WGS84.*/
 int32_t ip_lon; /*< [degE7] Line 1: initial point / battle position longitude, WGS84.*/
 uint32_t distance_m; /*< [m] Line 3: distance IP to target.*/
 int32_t tgt_elev_m; /*< [m] Line 4: target elevation, MSL.*/
 int32_t tgt_lat; /*< [degE7] Line 6: target latitude, WGS84.*/
 int32_t tgt_lon; /*< [degE7] Line 6: target longitude, WGS84.*/
 int32_t friendlies_lat; /*< [degE7] Line 8: friendlies latitude, WGS84.*/
 int32_t friendlies_lon; /*< [degE7] Line 8: friendlies longitude, WGS84.*/
 uint16_t heading_deg; /*< [deg] Line 2: heading (IP to target).*/
 int16_t offset_deg; /*< [deg] Line 2: offset (L/R); sign indicates side.*/
 uint16_t egress_deg; /*< [deg] Line 9: egress heading.*/
 uint16_t final_attack_heading_deg; /*< [deg] Remarks: final attack heading (FAH). 0xFFFF if unspecified.*/
 uint8_t mark_type; /*<  Line 7: type of mark / terminal guidance.*/
 uint8_t laser_code_slot; /*<  Line 7: 1 = a laser code is assigned (slot); 0 = none. Never the numeric code.*/
 uint8_t danger_close; /*<  Remarks: 1 = danger close / troops in contact; 0 = not.*/
 uint8_t delivery; /*<  Bomb-on-coordinate vs bomb-on-target.*/
} mavlink_cas_9line_t;

#define MAVLINK_MSG_ID_CAS_9LINE_LEN 52
#define MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN 52
#define MAVLINK_MSG_ID_53060_LEN 52
#define MAVLINK_MSG_ID_53060_MIN_LEN 52

#define MAVLINK_MSG_ID_CAS_9LINE_CRC 199
#define MAVLINK_MSG_ID_53060_CRC 199



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CAS_9LINE { \
    53060, \
    "CAS_9LINE", \
    17, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_cas_9line_t, time_usec) }, \
         { "ip_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_cas_9line_t, ip_lat) }, \
         { "ip_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_cas_9line_t, ip_lon) }, \
         { "heading_deg", NULL, MAVLINK_TYPE_UINT16_T, 0, 40, offsetof(mavlink_cas_9line_t, heading_deg) }, \
         { "offset_deg", NULL, MAVLINK_TYPE_INT16_T, 0, 42, offsetof(mavlink_cas_9line_t, offset_deg) }, \
         { "distance_m", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_cas_9line_t, distance_m) }, \
         { "tgt_elev_m", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_cas_9line_t, tgt_elev_m) }, \
         { "tgt_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_cas_9line_t, tgt_lat) }, \
         { "tgt_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_cas_9line_t, tgt_lon) }, \
         { "mark_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 48, offsetof(mavlink_cas_9line_t, mark_type) }, \
         { "laser_code_slot", NULL, MAVLINK_TYPE_UINT8_T, 0, 49, offsetof(mavlink_cas_9line_t, laser_code_slot) }, \
         { "friendlies_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 32, offsetof(mavlink_cas_9line_t, friendlies_lat) }, \
         { "friendlies_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 36, offsetof(mavlink_cas_9line_t, friendlies_lon) }, \
         { "egress_deg", NULL, MAVLINK_TYPE_UINT16_T, 0, 44, offsetof(mavlink_cas_9line_t, egress_deg) }, \
         { "final_attack_heading_deg", NULL, MAVLINK_TYPE_UINT16_T, 0, 46, offsetof(mavlink_cas_9line_t, final_attack_heading_deg) }, \
         { "danger_close", NULL, MAVLINK_TYPE_UINT8_T, 0, 50, offsetof(mavlink_cas_9line_t, danger_close) }, \
         { "delivery", NULL, MAVLINK_TYPE_UINT8_T, 0, 51, offsetof(mavlink_cas_9line_t, delivery) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CAS_9LINE { \
    "CAS_9LINE", \
    17, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_cas_9line_t, time_usec) }, \
         { "ip_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_cas_9line_t, ip_lat) }, \
         { "ip_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_cas_9line_t, ip_lon) }, \
         { "heading_deg", NULL, MAVLINK_TYPE_UINT16_T, 0, 40, offsetof(mavlink_cas_9line_t, heading_deg) }, \
         { "offset_deg", NULL, MAVLINK_TYPE_INT16_T, 0, 42, offsetof(mavlink_cas_9line_t, offset_deg) }, \
         { "distance_m", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_cas_9line_t, distance_m) }, \
         { "tgt_elev_m", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_cas_9line_t, tgt_elev_m) }, \
         { "tgt_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_cas_9line_t, tgt_lat) }, \
         { "tgt_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_cas_9line_t, tgt_lon) }, \
         { "mark_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 48, offsetof(mavlink_cas_9line_t, mark_type) }, \
         { "laser_code_slot", NULL, MAVLINK_TYPE_UINT8_T, 0, 49, offsetof(mavlink_cas_9line_t, laser_code_slot) }, \
         { "friendlies_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 32, offsetof(mavlink_cas_9line_t, friendlies_lat) }, \
         { "friendlies_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 36, offsetof(mavlink_cas_9line_t, friendlies_lon) }, \
         { "egress_deg", NULL, MAVLINK_TYPE_UINT16_T, 0, 44, offsetof(mavlink_cas_9line_t, egress_deg) }, \
         { "final_attack_heading_deg", NULL, MAVLINK_TYPE_UINT16_T, 0, 46, offsetof(mavlink_cas_9line_t, final_attack_heading_deg) }, \
         { "danger_close", NULL, MAVLINK_TYPE_UINT8_T, 0, 50, offsetof(mavlink_cas_9line_t, danger_close) }, \
         { "delivery", NULL, MAVLINK_TYPE_UINT8_T, 0, 51, offsetof(mavlink_cas_9line_t, delivery) }, \
         } \
}
#endif

/**
 * @brief Pack a cas_9line message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param ip_lat [degE7] Line 1: initial point / battle position latitude, WGS84.
 * @param ip_lon [degE7] Line 1: initial point / battle position longitude, WGS84.
 * @param heading_deg [deg] Line 2: heading (IP to target).
 * @param offset_deg [deg] Line 2: offset (L/R); sign indicates side.
 * @param distance_m [m] Line 3: distance IP to target.
 * @param tgt_elev_m [m] Line 4: target elevation, MSL.
 * @param tgt_lat [degE7] Line 6: target latitude, WGS84.
 * @param tgt_lon [degE7] Line 6: target longitude, WGS84.
 * @param mark_type  Line 7: type of mark / terminal guidance.
 * @param laser_code_slot  Line 7: 1 = a laser code is assigned (slot); 0 = none. Never the numeric code.
 * @param friendlies_lat [degE7] Line 8: friendlies latitude, WGS84.
 * @param friendlies_lon [degE7] Line 8: friendlies longitude, WGS84.
 * @param egress_deg [deg] Line 9: egress heading.
 * @param final_attack_heading_deg [deg] Remarks: final attack heading (FAH). 0xFFFF if unspecified.
 * @param danger_close  Remarks: 1 = danger close / troops in contact; 0 = not.
 * @param delivery  Bomb-on-coordinate vs bomb-on-target.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cas_9line_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t ip_lat, int32_t ip_lon, uint16_t heading_deg, int16_t offset_deg, uint32_t distance_m, int32_t tgt_elev_m, int32_t tgt_lat, int32_t tgt_lon, uint8_t mark_type, uint8_t laser_code_slot, int32_t friendlies_lat, int32_t friendlies_lon, uint16_t egress_deg, uint16_t final_attack_heading_deg, uint8_t danger_close, uint8_t delivery)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CAS_9LINE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, ip_lat);
    _mav_put_int32_t(buf, 12, ip_lon);
    _mav_put_uint32_t(buf, 16, distance_m);
    _mav_put_int32_t(buf, 20, tgt_elev_m);
    _mav_put_int32_t(buf, 24, tgt_lat);
    _mav_put_int32_t(buf, 28, tgt_lon);
    _mav_put_int32_t(buf, 32, friendlies_lat);
    _mav_put_int32_t(buf, 36, friendlies_lon);
    _mav_put_uint16_t(buf, 40, heading_deg);
    _mav_put_int16_t(buf, 42, offset_deg);
    _mav_put_uint16_t(buf, 44, egress_deg);
    _mav_put_uint16_t(buf, 46, final_attack_heading_deg);
    _mav_put_uint8_t(buf, 48, mark_type);
    _mav_put_uint8_t(buf, 49, laser_code_slot);
    _mav_put_uint8_t(buf, 50, danger_close);
    _mav_put_uint8_t(buf, 51, delivery);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CAS_9LINE_LEN);
#else
    mavlink_cas_9line_t packet;
    packet.time_usec = time_usec;
    packet.ip_lat = ip_lat;
    packet.ip_lon = ip_lon;
    packet.distance_m = distance_m;
    packet.tgt_elev_m = tgt_elev_m;
    packet.tgt_lat = tgt_lat;
    packet.tgt_lon = tgt_lon;
    packet.friendlies_lat = friendlies_lat;
    packet.friendlies_lon = friendlies_lon;
    packet.heading_deg = heading_deg;
    packet.offset_deg = offset_deg;
    packet.egress_deg = egress_deg;
    packet.final_attack_heading_deg = final_attack_heading_deg;
    packet.mark_type = mark_type;
    packet.laser_code_slot = laser_code_slot;
    packet.danger_close = danger_close;
    packet.delivery = delivery;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CAS_9LINE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CAS_9LINE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN, MAVLINK_MSG_ID_CAS_9LINE_CRC);
}

/**
 * @brief Pack a cas_9line message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param ip_lat [degE7] Line 1: initial point / battle position latitude, WGS84.
 * @param ip_lon [degE7] Line 1: initial point / battle position longitude, WGS84.
 * @param heading_deg [deg] Line 2: heading (IP to target).
 * @param offset_deg [deg] Line 2: offset (L/R); sign indicates side.
 * @param distance_m [m] Line 3: distance IP to target.
 * @param tgt_elev_m [m] Line 4: target elevation, MSL.
 * @param tgt_lat [degE7] Line 6: target latitude, WGS84.
 * @param tgt_lon [degE7] Line 6: target longitude, WGS84.
 * @param mark_type  Line 7: type of mark / terminal guidance.
 * @param laser_code_slot  Line 7: 1 = a laser code is assigned (slot); 0 = none. Never the numeric code.
 * @param friendlies_lat [degE7] Line 8: friendlies latitude, WGS84.
 * @param friendlies_lon [degE7] Line 8: friendlies longitude, WGS84.
 * @param egress_deg [deg] Line 9: egress heading.
 * @param final_attack_heading_deg [deg] Remarks: final attack heading (FAH). 0xFFFF if unspecified.
 * @param danger_close  Remarks: 1 = danger close / troops in contact; 0 = not.
 * @param delivery  Bomb-on-coordinate vs bomb-on-target.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cas_9line_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, int32_t ip_lat, int32_t ip_lon, uint16_t heading_deg, int16_t offset_deg, uint32_t distance_m, int32_t tgt_elev_m, int32_t tgt_lat, int32_t tgt_lon, uint8_t mark_type, uint8_t laser_code_slot, int32_t friendlies_lat, int32_t friendlies_lon, uint16_t egress_deg, uint16_t final_attack_heading_deg, uint8_t danger_close, uint8_t delivery)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CAS_9LINE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, ip_lat);
    _mav_put_int32_t(buf, 12, ip_lon);
    _mav_put_uint32_t(buf, 16, distance_m);
    _mav_put_int32_t(buf, 20, tgt_elev_m);
    _mav_put_int32_t(buf, 24, tgt_lat);
    _mav_put_int32_t(buf, 28, tgt_lon);
    _mav_put_int32_t(buf, 32, friendlies_lat);
    _mav_put_int32_t(buf, 36, friendlies_lon);
    _mav_put_uint16_t(buf, 40, heading_deg);
    _mav_put_int16_t(buf, 42, offset_deg);
    _mav_put_uint16_t(buf, 44, egress_deg);
    _mav_put_uint16_t(buf, 46, final_attack_heading_deg);
    _mav_put_uint8_t(buf, 48, mark_type);
    _mav_put_uint8_t(buf, 49, laser_code_slot);
    _mav_put_uint8_t(buf, 50, danger_close);
    _mav_put_uint8_t(buf, 51, delivery);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CAS_9LINE_LEN);
#else
    mavlink_cas_9line_t packet;
    packet.time_usec = time_usec;
    packet.ip_lat = ip_lat;
    packet.ip_lon = ip_lon;
    packet.distance_m = distance_m;
    packet.tgt_elev_m = tgt_elev_m;
    packet.tgt_lat = tgt_lat;
    packet.tgt_lon = tgt_lon;
    packet.friendlies_lat = friendlies_lat;
    packet.friendlies_lon = friendlies_lon;
    packet.heading_deg = heading_deg;
    packet.offset_deg = offset_deg;
    packet.egress_deg = egress_deg;
    packet.final_attack_heading_deg = final_attack_heading_deg;
    packet.mark_type = mark_type;
    packet.laser_code_slot = laser_code_slot;
    packet.danger_close = danger_close;
    packet.delivery = delivery;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CAS_9LINE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CAS_9LINE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN, MAVLINK_MSG_ID_CAS_9LINE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN);
#endif
}

/**
 * @brief Pack a cas_9line message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param ip_lat [degE7] Line 1: initial point / battle position latitude, WGS84.
 * @param ip_lon [degE7] Line 1: initial point / battle position longitude, WGS84.
 * @param heading_deg [deg] Line 2: heading (IP to target).
 * @param offset_deg [deg] Line 2: offset (L/R); sign indicates side.
 * @param distance_m [m] Line 3: distance IP to target.
 * @param tgt_elev_m [m] Line 4: target elevation, MSL.
 * @param tgt_lat [degE7] Line 6: target latitude, WGS84.
 * @param tgt_lon [degE7] Line 6: target longitude, WGS84.
 * @param mark_type  Line 7: type of mark / terminal guidance.
 * @param laser_code_slot  Line 7: 1 = a laser code is assigned (slot); 0 = none. Never the numeric code.
 * @param friendlies_lat [degE7] Line 8: friendlies latitude, WGS84.
 * @param friendlies_lon [degE7] Line 8: friendlies longitude, WGS84.
 * @param egress_deg [deg] Line 9: egress heading.
 * @param final_attack_heading_deg [deg] Remarks: final attack heading (FAH). 0xFFFF if unspecified.
 * @param danger_close  Remarks: 1 = danger close / troops in contact; 0 = not.
 * @param delivery  Bomb-on-coordinate vs bomb-on-target.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_cas_9line_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,int32_t ip_lat,int32_t ip_lon,uint16_t heading_deg,int16_t offset_deg,uint32_t distance_m,int32_t tgt_elev_m,int32_t tgt_lat,int32_t tgt_lon,uint8_t mark_type,uint8_t laser_code_slot,int32_t friendlies_lat,int32_t friendlies_lon,uint16_t egress_deg,uint16_t final_attack_heading_deg,uint8_t danger_close,uint8_t delivery)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CAS_9LINE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, ip_lat);
    _mav_put_int32_t(buf, 12, ip_lon);
    _mav_put_uint32_t(buf, 16, distance_m);
    _mav_put_int32_t(buf, 20, tgt_elev_m);
    _mav_put_int32_t(buf, 24, tgt_lat);
    _mav_put_int32_t(buf, 28, tgt_lon);
    _mav_put_int32_t(buf, 32, friendlies_lat);
    _mav_put_int32_t(buf, 36, friendlies_lon);
    _mav_put_uint16_t(buf, 40, heading_deg);
    _mav_put_int16_t(buf, 42, offset_deg);
    _mav_put_uint16_t(buf, 44, egress_deg);
    _mav_put_uint16_t(buf, 46, final_attack_heading_deg);
    _mav_put_uint8_t(buf, 48, mark_type);
    _mav_put_uint8_t(buf, 49, laser_code_slot);
    _mav_put_uint8_t(buf, 50, danger_close);
    _mav_put_uint8_t(buf, 51, delivery);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CAS_9LINE_LEN);
#else
    mavlink_cas_9line_t packet;
    packet.time_usec = time_usec;
    packet.ip_lat = ip_lat;
    packet.ip_lon = ip_lon;
    packet.distance_m = distance_m;
    packet.tgt_elev_m = tgt_elev_m;
    packet.tgt_lat = tgt_lat;
    packet.tgt_lon = tgt_lon;
    packet.friendlies_lat = friendlies_lat;
    packet.friendlies_lon = friendlies_lon;
    packet.heading_deg = heading_deg;
    packet.offset_deg = offset_deg;
    packet.egress_deg = egress_deg;
    packet.final_attack_heading_deg = final_attack_heading_deg;
    packet.mark_type = mark_type;
    packet.laser_code_slot = laser_code_slot;
    packet.danger_close = danger_close;
    packet.delivery = delivery;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CAS_9LINE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CAS_9LINE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN, MAVLINK_MSG_ID_CAS_9LINE_CRC);
}

/**
 * @brief Encode a cas_9line struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param cas_9line C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cas_9line_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_cas_9line_t* cas_9line)
{
    return mavlink_msg_cas_9line_pack(system_id, component_id, msg, cas_9line->time_usec, cas_9line->ip_lat, cas_9line->ip_lon, cas_9line->heading_deg, cas_9line->offset_deg, cas_9line->distance_m, cas_9line->tgt_elev_m, cas_9line->tgt_lat, cas_9line->tgt_lon, cas_9line->mark_type, cas_9line->laser_code_slot, cas_9line->friendlies_lat, cas_9line->friendlies_lon, cas_9line->egress_deg, cas_9line->final_attack_heading_deg, cas_9line->danger_close, cas_9line->delivery);
}

/**
 * @brief Encode a cas_9line struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cas_9line C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cas_9line_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_cas_9line_t* cas_9line)
{
    return mavlink_msg_cas_9line_pack_chan(system_id, component_id, chan, msg, cas_9line->time_usec, cas_9line->ip_lat, cas_9line->ip_lon, cas_9line->heading_deg, cas_9line->offset_deg, cas_9line->distance_m, cas_9line->tgt_elev_m, cas_9line->tgt_lat, cas_9line->tgt_lon, cas_9line->mark_type, cas_9line->laser_code_slot, cas_9line->friendlies_lat, cas_9line->friendlies_lon, cas_9line->egress_deg, cas_9line->final_attack_heading_deg, cas_9line->danger_close, cas_9line->delivery);
}

/**
 * @brief Encode a cas_9line struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param cas_9line C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_cas_9line_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_cas_9line_t* cas_9line)
{
    return mavlink_msg_cas_9line_pack_status(system_id, component_id, _status, msg,  cas_9line->time_usec, cas_9line->ip_lat, cas_9line->ip_lon, cas_9line->heading_deg, cas_9line->offset_deg, cas_9line->distance_m, cas_9line->tgt_elev_m, cas_9line->tgt_lat, cas_9line->tgt_lon, cas_9line->mark_type, cas_9line->laser_code_slot, cas_9line->friendlies_lat, cas_9line->friendlies_lon, cas_9line->egress_deg, cas_9line->final_attack_heading_deg, cas_9line->danger_close, cas_9line->delivery);
}

/**
 * @brief Send a cas_9line message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param ip_lat [degE7] Line 1: initial point / battle position latitude, WGS84.
 * @param ip_lon [degE7] Line 1: initial point / battle position longitude, WGS84.
 * @param heading_deg [deg] Line 2: heading (IP to target).
 * @param offset_deg [deg] Line 2: offset (L/R); sign indicates side.
 * @param distance_m [m] Line 3: distance IP to target.
 * @param tgt_elev_m [m] Line 4: target elevation, MSL.
 * @param tgt_lat [degE7] Line 6: target latitude, WGS84.
 * @param tgt_lon [degE7] Line 6: target longitude, WGS84.
 * @param mark_type  Line 7: type of mark / terminal guidance.
 * @param laser_code_slot  Line 7: 1 = a laser code is assigned (slot); 0 = none. Never the numeric code.
 * @param friendlies_lat [degE7] Line 8: friendlies latitude, WGS84.
 * @param friendlies_lon [degE7] Line 8: friendlies longitude, WGS84.
 * @param egress_deg [deg] Line 9: egress heading.
 * @param final_attack_heading_deg [deg] Remarks: final attack heading (FAH). 0xFFFF if unspecified.
 * @param danger_close  Remarks: 1 = danger close / troops in contact; 0 = not.
 * @param delivery  Bomb-on-coordinate vs bomb-on-target.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_cas_9line_send(mavlink_channel_t chan, uint64_t time_usec, int32_t ip_lat, int32_t ip_lon, uint16_t heading_deg, int16_t offset_deg, uint32_t distance_m, int32_t tgt_elev_m, int32_t tgt_lat, int32_t tgt_lon, uint8_t mark_type, uint8_t laser_code_slot, int32_t friendlies_lat, int32_t friendlies_lon, uint16_t egress_deg, uint16_t final_attack_heading_deg, uint8_t danger_close, uint8_t delivery)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CAS_9LINE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, ip_lat);
    _mav_put_int32_t(buf, 12, ip_lon);
    _mav_put_uint32_t(buf, 16, distance_m);
    _mav_put_int32_t(buf, 20, tgt_elev_m);
    _mav_put_int32_t(buf, 24, tgt_lat);
    _mav_put_int32_t(buf, 28, tgt_lon);
    _mav_put_int32_t(buf, 32, friendlies_lat);
    _mav_put_int32_t(buf, 36, friendlies_lon);
    _mav_put_uint16_t(buf, 40, heading_deg);
    _mav_put_int16_t(buf, 42, offset_deg);
    _mav_put_uint16_t(buf, 44, egress_deg);
    _mav_put_uint16_t(buf, 46, final_attack_heading_deg);
    _mav_put_uint8_t(buf, 48, mark_type);
    _mav_put_uint8_t(buf, 49, laser_code_slot);
    _mav_put_uint8_t(buf, 50, danger_close);
    _mav_put_uint8_t(buf, 51, delivery);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAS_9LINE, buf, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN, MAVLINK_MSG_ID_CAS_9LINE_CRC);
#else
    mavlink_cas_9line_t packet;
    packet.time_usec = time_usec;
    packet.ip_lat = ip_lat;
    packet.ip_lon = ip_lon;
    packet.distance_m = distance_m;
    packet.tgt_elev_m = tgt_elev_m;
    packet.tgt_lat = tgt_lat;
    packet.tgt_lon = tgt_lon;
    packet.friendlies_lat = friendlies_lat;
    packet.friendlies_lon = friendlies_lon;
    packet.heading_deg = heading_deg;
    packet.offset_deg = offset_deg;
    packet.egress_deg = egress_deg;
    packet.final_attack_heading_deg = final_attack_heading_deg;
    packet.mark_type = mark_type;
    packet.laser_code_slot = laser_code_slot;
    packet.danger_close = danger_close;
    packet.delivery = delivery;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAS_9LINE, (const char *)&packet, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN, MAVLINK_MSG_ID_CAS_9LINE_CRC);
#endif
}

/**
 * @brief Send a cas_9line message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_cas_9line_send_struct(mavlink_channel_t chan, const mavlink_cas_9line_t* cas_9line)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_cas_9line_send(chan, cas_9line->time_usec, cas_9line->ip_lat, cas_9line->ip_lon, cas_9line->heading_deg, cas_9line->offset_deg, cas_9line->distance_m, cas_9line->tgt_elev_m, cas_9line->tgt_lat, cas_9line->tgt_lon, cas_9line->mark_type, cas_9line->laser_code_slot, cas_9line->friendlies_lat, cas_9line->friendlies_lon, cas_9line->egress_deg, cas_9line->final_attack_heading_deg, cas_9line->danger_close, cas_9line->delivery);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAS_9LINE, (const char *)cas_9line, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN, MAVLINK_MSG_ID_CAS_9LINE_CRC);
#endif
}

#if MAVLINK_MSG_ID_CAS_9LINE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_cas_9line_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, int32_t ip_lat, int32_t ip_lon, uint16_t heading_deg, int16_t offset_deg, uint32_t distance_m, int32_t tgt_elev_m, int32_t tgt_lat, int32_t tgt_lon, uint8_t mark_type, uint8_t laser_code_slot, int32_t friendlies_lat, int32_t friendlies_lon, uint16_t egress_deg, uint16_t final_attack_heading_deg, uint8_t danger_close, uint8_t delivery)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, ip_lat);
    _mav_put_int32_t(buf, 12, ip_lon);
    _mav_put_uint32_t(buf, 16, distance_m);
    _mav_put_int32_t(buf, 20, tgt_elev_m);
    _mav_put_int32_t(buf, 24, tgt_lat);
    _mav_put_int32_t(buf, 28, tgt_lon);
    _mav_put_int32_t(buf, 32, friendlies_lat);
    _mav_put_int32_t(buf, 36, friendlies_lon);
    _mav_put_uint16_t(buf, 40, heading_deg);
    _mav_put_int16_t(buf, 42, offset_deg);
    _mav_put_uint16_t(buf, 44, egress_deg);
    _mav_put_uint16_t(buf, 46, final_attack_heading_deg);
    _mav_put_uint8_t(buf, 48, mark_type);
    _mav_put_uint8_t(buf, 49, laser_code_slot);
    _mav_put_uint8_t(buf, 50, danger_close);
    _mav_put_uint8_t(buf, 51, delivery);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAS_9LINE, buf, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN, MAVLINK_MSG_ID_CAS_9LINE_CRC);
#else
    mavlink_cas_9line_t *packet = (mavlink_cas_9line_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->ip_lat = ip_lat;
    packet->ip_lon = ip_lon;
    packet->distance_m = distance_m;
    packet->tgt_elev_m = tgt_elev_m;
    packet->tgt_lat = tgt_lat;
    packet->tgt_lon = tgt_lon;
    packet->friendlies_lat = friendlies_lat;
    packet->friendlies_lon = friendlies_lon;
    packet->heading_deg = heading_deg;
    packet->offset_deg = offset_deg;
    packet->egress_deg = egress_deg;
    packet->final_attack_heading_deg = final_attack_heading_deg;
    packet->mark_type = mark_type;
    packet->laser_code_slot = laser_code_slot;
    packet->danger_close = danger_close;
    packet->delivery = delivery;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CAS_9LINE, (const char *)packet, MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN, MAVLINK_MSG_ID_CAS_9LINE_LEN, MAVLINK_MSG_ID_CAS_9LINE_CRC);
#endif
}
#endif

#endif

// MESSAGE CAS_9LINE UNPACKING


/**
 * @brief Get field time_usec from cas_9line message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_cas_9line_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field ip_lat from cas_9line message
 *
 * @return [degE7] Line 1: initial point / battle position latitude, WGS84.
 */
static inline int32_t mavlink_msg_cas_9line_get_ip_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field ip_lon from cas_9line message
 *
 * @return [degE7] Line 1: initial point / battle position longitude, WGS84.
 */
static inline int32_t mavlink_msg_cas_9line_get_ip_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field heading_deg from cas_9line message
 *
 * @return [deg] Line 2: heading (IP to target).
 */
static inline uint16_t mavlink_msg_cas_9line_get_heading_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  40);
}

/**
 * @brief Get field offset_deg from cas_9line message
 *
 * @return [deg] Line 2: offset (L/R); sign indicates side.
 */
static inline int16_t mavlink_msg_cas_9line_get_offset_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  42);
}

/**
 * @brief Get field distance_m from cas_9line message
 *
 * @return [m] Line 3: distance IP to target.
 */
static inline uint32_t mavlink_msg_cas_9line_get_distance_m(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field tgt_elev_m from cas_9line message
 *
 * @return [m] Line 4: target elevation, MSL.
 */
static inline int32_t mavlink_msg_cas_9line_get_tgt_elev_m(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field tgt_lat from cas_9line message
 *
 * @return [degE7] Line 6: target latitude, WGS84.
 */
static inline int32_t mavlink_msg_cas_9line_get_tgt_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  24);
}

/**
 * @brief Get field tgt_lon from cas_9line message
 *
 * @return [degE7] Line 6: target longitude, WGS84.
 */
static inline int32_t mavlink_msg_cas_9line_get_tgt_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  28);
}

/**
 * @brief Get field mark_type from cas_9line message
 *
 * @return  Line 7: type of mark / terminal guidance.
 */
static inline uint8_t mavlink_msg_cas_9line_get_mark_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  48);
}

/**
 * @brief Get field laser_code_slot from cas_9line message
 *
 * @return  Line 7: 1 = a laser code is assigned (slot); 0 = none. Never the numeric code.
 */
static inline uint8_t mavlink_msg_cas_9line_get_laser_code_slot(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  49);
}

/**
 * @brief Get field friendlies_lat from cas_9line message
 *
 * @return [degE7] Line 8: friendlies latitude, WGS84.
 */
static inline int32_t mavlink_msg_cas_9line_get_friendlies_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  32);
}

/**
 * @brief Get field friendlies_lon from cas_9line message
 *
 * @return [degE7] Line 8: friendlies longitude, WGS84.
 */
static inline int32_t mavlink_msg_cas_9line_get_friendlies_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  36);
}

/**
 * @brief Get field egress_deg from cas_9line message
 *
 * @return [deg] Line 9: egress heading.
 */
static inline uint16_t mavlink_msg_cas_9line_get_egress_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  44);
}

/**
 * @brief Get field final_attack_heading_deg from cas_9line message
 *
 * @return [deg] Remarks: final attack heading (FAH). 0xFFFF if unspecified.
 */
static inline uint16_t mavlink_msg_cas_9line_get_final_attack_heading_deg(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  46);
}

/**
 * @brief Get field danger_close from cas_9line message
 *
 * @return  Remarks: 1 = danger close / troops in contact; 0 = not.
 */
static inline uint8_t mavlink_msg_cas_9line_get_danger_close(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  50);
}

/**
 * @brief Get field delivery from cas_9line message
 *
 * @return  Bomb-on-coordinate vs bomb-on-target.
 */
static inline uint8_t mavlink_msg_cas_9line_get_delivery(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  51);
}

/**
 * @brief Decode a cas_9line message into a struct
 *
 * @param msg The message to decode
 * @param cas_9line C-struct to decode the message contents into
 */
static inline void mavlink_msg_cas_9line_decode(const mavlink_message_t* msg, mavlink_cas_9line_t* cas_9line)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    cas_9line->time_usec = mavlink_msg_cas_9line_get_time_usec(msg);
    cas_9line->ip_lat = mavlink_msg_cas_9line_get_ip_lat(msg);
    cas_9line->ip_lon = mavlink_msg_cas_9line_get_ip_lon(msg);
    cas_9line->distance_m = mavlink_msg_cas_9line_get_distance_m(msg);
    cas_9line->tgt_elev_m = mavlink_msg_cas_9line_get_tgt_elev_m(msg);
    cas_9line->tgt_lat = mavlink_msg_cas_9line_get_tgt_lat(msg);
    cas_9line->tgt_lon = mavlink_msg_cas_9line_get_tgt_lon(msg);
    cas_9line->friendlies_lat = mavlink_msg_cas_9line_get_friendlies_lat(msg);
    cas_9line->friendlies_lon = mavlink_msg_cas_9line_get_friendlies_lon(msg);
    cas_9line->heading_deg = mavlink_msg_cas_9line_get_heading_deg(msg);
    cas_9line->offset_deg = mavlink_msg_cas_9line_get_offset_deg(msg);
    cas_9line->egress_deg = mavlink_msg_cas_9line_get_egress_deg(msg);
    cas_9line->final_attack_heading_deg = mavlink_msg_cas_9line_get_final_attack_heading_deg(msg);
    cas_9line->mark_type = mavlink_msg_cas_9line_get_mark_type(msg);
    cas_9line->laser_code_slot = mavlink_msg_cas_9line_get_laser_code_slot(msg);
    cas_9line->danger_close = mavlink_msg_cas_9line_get_danger_close(msg);
    cas_9line->delivery = mavlink_msg_cas_9line_get_delivery(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CAS_9LINE_LEN? msg->len : MAVLINK_MSG_ID_CAS_9LINE_LEN;
        memset(cas_9line, 0, MAVLINK_MSG_ID_CAS_9LINE_LEN);
    memcpy(cas_9line, _MAV_PAYLOAD(msg), len);
#endif
}
