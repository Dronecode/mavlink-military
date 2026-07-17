/** @file
 *    @brief MAVLink comm protocol testsuite generated from military.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef MILITARY_TESTSUITE_H
#define MILITARY_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_military(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_military(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_target_set_coord(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_SET_COORD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_set_coord_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,963498920,963499128,269.0,297.0,"STUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNO"
    };
    mavlink_target_set_coord_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_start = packet_in.time_start;
        packet1.time_end = packet_in.time_end;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.radius = packet_in.radius;
        
        mav_array_memcpy(packet1.target_set_name, packet_in.target_set_name, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_set_coord_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_set_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_set_coord_pack(system_id, component_id, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.radius , packet1.time_start , packet1.time_end );
    mavlink_msg_target_set_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_set_coord_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.radius , packet1.time_start , packet1.time_end );
    mavlink_msg_target_set_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_set_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_set_coord_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.radius , packet1.time_start , packet1.time_end );
    mavlink_msg_target_set_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_SET_COORD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_SET_COORD) != NULL);
#endif
}

static void mavlink_test_target_box_coord(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_BOX_COORD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_box_coord_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,{ 963498920, 963498921, 963498922, 963498923 },{ 963499752, 963499753, 963499754, 963499755 },{ 437.0, 438.0, 439.0, 440.0 },"YZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU"
    };
    mavlink_target_box_coord_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_start = packet_in.time_start;
        packet1.time_end = packet_in.time_end;
        packet1.target_set_id = packet_in.target_set_id;
        
        mav_array_memcpy(packet1.lat, packet_in.lat, sizeof(int32_t)*4);
        mav_array_memcpy(packet1.lon, packet_in.lon, sizeof(int32_t)*4);
        mav_array_memcpy(packet1.alt, packet_in.alt, sizeof(float)*4);
        mav_array_memcpy(packet1.target_set_name, packet_in.target_set_name, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_box_coord_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_box_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_box_coord_pack(system_id, component_id, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.time_start , packet1.time_end );
    mavlink_msg_target_box_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_box_coord_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.time_start , packet1.time_end );
    mavlink_msg_target_box_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_box_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_box_coord_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.time_start , packet1.time_end );
    mavlink_msg_target_box_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_BOX_COORD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_BOX_COORD) != NULL);
#endif
}

static void mavlink_test_target(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,963498712,963498920,963499128,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,493.0,521.0,549.0,577.0,963501832,963502040,963502248,963502456,22435,22539,22643,"CDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXY",217,28,95,162,229,40,"GHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFG",91,158,225
    };
    mavlink_target_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.target_time_usec = packet_in.target_time_usec;
        packet1.target_id = packet_in.target_id;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.package_id_hash = packet_in.package_id_hash;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.cov_pos_x = packet_in.cov_pos_x;
        packet1.cov_pos_y = packet_in.cov_pos_y;
        packet1.cov_pos_z = packet_in.cov_pos_z;
        packet1.cov_vel_x = packet_in.cov_vel_x;
        packet1.cov_vel_y = packet_in.cov_vel_y;
        packet1.cov_vel_z = packet_in.cov_vel_z;
        packet1.cep_desired = packet_in.cep_desired;
        packet1.cep_max = packet_in.cep_max;
        packet1.flags = packet_in.flags;
        packet1.package_endpoint_ip_1 = packet_in.package_endpoint_ip_1;
        packet1.package_endpoint_ip_2 = packet_in.package_endpoint_ip_2;
        packet1.package_endpoint_ip_3 = packet_in.package_endpoint_ip_3;
        packet1.confidence = packet_in.confidence;
        packet1.package_endpoint_port = packet_in.package_endpoint_port;
        packet1.prf_code = packet_in.prf_code;
        packet1.target_class = packet_in.target_class;
        packet1.target_domain = packet_in.target_domain;
        packet1.target_entity_2525d = packet_in.target_entity_2525d;
        packet1.target_force = packet_in.target_force;
        packet1.sensor_type = packet_in.sensor_type;
        packet1.package_transport = packet_in.package_transport;
        packet1.tle_category = packet_in.tle_category;
        packet1.dmpi_reference_kind = packet_in.dmpi_reference_kind;
        packet1.restricted_target_flags = packet_in.restricted_target_flags;
        
        mav_array_memcpy(packet1.target_name, packet_in.target_name, sizeof(char)*50);
        mav_array_memcpy(packet1.package_path, packet_in.package_path, sizeof(char)*80);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_pack(system_id, component_id, &msg , packet1.time_usec , packet1.target_time_usec , packet1.target_id , packet1.target_set_id , packet1.package_id_hash , packet1.target_name , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.cep_desired , packet1.cep_max , packet1.flags , packet1.package_endpoint_ip_1 , packet1.package_endpoint_ip_2 , packet1.package_endpoint_ip_3 , packet1.target_class , packet1.target_domain , packet1.target_entity_2525d , packet1.target_force , packet1.confidence , packet1.package_endpoint_port , packet1.sensor_type , packet1.package_transport , packet1.package_path , packet1.prf_code , packet1.tle_category , packet1.dmpi_reference_kind , packet1.restricted_target_flags );
    mavlink_msg_target_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.target_time_usec , packet1.target_id , packet1.target_set_id , packet1.package_id_hash , packet1.target_name , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.cep_desired , packet1.cep_max , packet1.flags , packet1.package_endpoint_ip_1 , packet1.package_endpoint_ip_2 , packet1.package_endpoint_ip_3 , packet1.target_class , packet1.target_domain , packet1.target_entity_2525d , packet1.target_force , packet1.confidence , packet1.package_endpoint_port , packet1.sensor_type , packet1.package_transport , packet1.package_path , packet1.prf_code , packet1.tle_category , packet1.dmpi_reference_kind , packet1.restricted_target_flags );
    mavlink_msg_target_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.target_time_usec , packet1.target_id , packet1.target_set_id , packet1.package_id_hash , packet1.target_name , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.cep_desired , packet1.cep_max , packet1.flags , packet1.package_endpoint_ip_1 , packet1.package_endpoint_ip_2 , packet1.package_endpoint_ip_3 , packet1.target_class , packet1.target_domain , packet1.target_entity_2525d , packet1.target_force , packet1.confidence , packet1.package_endpoint_port , packet1.sensor_type , packet1.package_transport , packet1.package_path , packet1.prf_code , packet1.tle_category , packet1.dmpi_reference_kind , packet1.restricted_target_flags );
    mavlink_msg_target_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET) != NULL);
#endif
}

static void mavlink_test_fires(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FIRES >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fires_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,185.0,963498920,241.0,19107,19211,125,192,3,70,137,204,{ 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 }
    };
    mavlink_fires_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_impact_usec = packet_in.time_impact_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.effector_id = packet_in.effector_id;
        packet1.cep_expected = packet_in.cep_expected;
        packet1.sequence = packet_in.sequence;
        packet1.prf_code = packet_in.prf_code;
        packet1.store_id = packet_in.store_id;
        packet1.requested_effect = packet_in.requested_effect;
        packet1.munition_class = packet_in.munition_class;
        packet1.fuze_mode = packet_in.fuze_mode;
        packet1.hob_intent = packet_in.hob_intent;
        packet1.fuze_mofa_capable = packet_in.fuze_mofa_capable;
        
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FIRES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FIRES_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fires_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fires_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fires_pack(system_id, component_id, &msg , packet1.time_usec , packet1.time_impact_usec , packet1.lat , packet1.lon , packet1.alt , packet1.effector_id , packet1.sequence , packet1.cep_expected , packet1.prf_code , packet1.store_id , packet1.requested_effect , packet1.munition_class , packet1.fuze_mode , packet1.hob_intent , packet1.fuze_mofa_capable , packet1.track_uid );
    mavlink_msg_fires_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fires_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.time_impact_usec , packet1.lat , packet1.lon , packet1.alt , packet1.effector_id , packet1.sequence , packet1.cep_expected , packet1.prf_code , packet1.store_id , packet1.requested_effect , packet1.munition_class , packet1.fuze_mode , packet1.hob_intent , packet1.fuze_mofa_capable , packet1.track_uid );
    mavlink_msg_fires_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fires_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fires_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.time_impact_usec , packet1.lat , packet1.lon , packet1.alt , packet1.effector_id , packet1.sequence , packet1.cep_expected , packet1.prf_code , packet1.store_id , packet1.requested_effect , packet1.munition_class , packet1.fuze_mode , packet1.hob_intent , packet1.fuze_mofa_capable , packet1.track_uid );
    mavlink_msg_fires_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FIRES") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FIRES) != NULL);
#endif
}

static void mavlink_test_splash_correction(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SPLASH_CORRECTION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_splash_correction_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,18483,211,22,89,156,223,34,101,{ 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183 }
    };
    mavlink_splash_correction_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.cep_expected = packet_in.cep_expected;
        packet1.sequence = packet_in.sequence;
        packet1.type_detected = packet_in.type_detected;
        packet1.deviation = packet_in.deviation;
        packet1.range_spot = packet_in.range_spot;
        packet1.hob = packet_in.hob;
        packet1.impact_surface = packet_in.impact_surface;
        packet1.obscuration = packet_in.obscuration;
        packet1.command = packet_in.command;
        
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_splash_correction_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_splash_correction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_splash_correction_pack(system_id, component_id, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.sequence , packet1.type_detected , packet1.cep_expected , packet1.deviation , packet1.range_spot , packet1.hob , packet1.impact_surface , packet1.obscuration , packet1.command , packet1.track_uid );
    mavlink_msg_splash_correction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_splash_correction_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.sequence , packet1.type_detected , packet1.cep_expected , packet1.deviation , packet1.range_spot , packet1.hob , packet1.impact_surface , packet1.obscuration , packet1.command , packet1.track_uid );
    mavlink_msg_splash_correction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_splash_correction_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_splash_correction_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.sequence , packet1.type_detected , packet1.cep_expected , packet1.deviation , packet1.range_spot , packet1.hob , packet1.impact_surface , packet1.obscuration , packet1.command , packet1.track_uid );
    mavlink_msg_splash_correction_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SPLASH_CORRECTION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SPLASH_CORRECTION) != NULL);
#endif
}

static void mavlink_test_target_handover(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_HANDOVER >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_handover_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,963498920,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,493.0,963501208,549.0,"CDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXY","ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVW",{ 33, 34, 35, 36, 37, 38, 39, 40 },57,124,191,{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 }
    };
    mavlink_target_handover_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.detected_first_usec = packet_in.detected_first_usec;
        packet1.valid_until_usec = packet_in.valid_until_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.cov_pos_x = packet_in.cov_pos_x;
        packet1.cov_pos_y = packet_in.cov_pos_y;
        packet1.cov_pos_z = packet_in.cov_pos_z;
        packet1.cov_vel_x = packet_in.cov_vel_x;
        packet1.cov_vel_y = packet_in.cov_vel_y;
        packet1.cov_vel_z = packet_in.cov_vel_z;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.confidence_score = packet_in.confidence_score;
        packet1.target_class = packet_in.target_class;
        packet1.target_force = packet_in.target_force;
        packet1.match_media_type = packet_in.match_media_type;
        
        mav_array_memcpy(packet1.target_name, packet_in.target_name, sizeof(char)*50);
        mav_array_memcpy(packet1.match_media_url, packet_in.match_media_url, sizeof(char)*50);
        mav_array_memcpy(packet1.authorization, packet_in.authorization, sizeof(uint8_t)*8);
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_handover_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_handover_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_handover_pack(system_id, component_id, &msg , packet1.time_usec , packet1.detected_first_usec , packet1.valid_until_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.match_media_url , packet1.confidence_score , packet1.authorization , packet1.target_class , packet1.target_force , packet1.match_media_type , packet1.track_uid );
    mavlink_msg_target_handover_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_handover_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.detected_first_usec , packet1.valid_until_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.match_media_url , packet1.confidence_score , packet1.authorization , packet1.target_class , packet1.target_force , packet1.match_media_type , packet1.track_uid );
    mavlink_msg_target_handover_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_handover_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_handover_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.detected_first_usec , packet1.valid_until_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.match_media_url , packet1.confidence_score , packet1.authorization , packet1.target_class , packet1.target_force , packet1.match_media_type , packet1.track_uid );
    mavlink_msg_target_handover_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_HANDOVER") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_HANDOVER) != NULL);
#endif
}

static void mavlink_test_battle_damage_assessment(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_battle_damage_assessment_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,963500376,"IJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDE",{ 207, 208, 209, 210, 211, 212, 213, 214 },231,42,109,176,243,54,121,{ 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203 }
    };
    mavlink_battle_damage_assessment_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.cov_pos_x = packet_in.cov_pos_x;
        packet1.cov_pos_y = packet_in.cov_pos_y;
        packet1.cov_pos_z = packet_in.cov_pos_z;
        packet1.cov_vel_x = packet_in.cov_vel_x;
        packet1.cov_vel_y = packet_in.cov_vel_y;
        packet1.cov_vel_z = packet_in.cov_vel_z;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.destruction_pct = packet_in.destruction_pct;
        packet1.confidence_pct = packet_in.confidence_pct;
        packet1.target_class = packet_in.target_class;
        packet1.target_force = packet_in.target_force;
        packet1.functional_damage = packet_in.functional_damage;
        packet1.physical_damage = packet_in.physical_damage;
        packet1.reattack_recommended = packet_in.reattack_recommended;
        
        mav_array_memcpy(packet1.target_name, packet_in.target_name, sizeof(char)*50);
        mav_array_memcpy(packet1.authorization, packet_in.authorization, sizeof(uint8_t)*8);
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battle_damage_assessment_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_battle_damage_assessment_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battle_damage_assessment_pack(system_id, component_id, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.authorization , packet1.destruction_pct , packet1.confidence_pct , packet1.target_class , packet1.target_force , packet1.functional_damage , packet1.physical_damage , packet1.reattack_recommended , packet1.track_uid );
    mavlink_msg_battle_damage_assessment_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battle_damage_assessment_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.authorization , packet1.destruction_pct , packet1.confidence_pct , packet1.target_class , packet1.target_force , packet1.functional_damage , packet1.physical_damage , packet1.reattack_recommended , packet1.track_uid );
    mavlink_msg_battle_damage_assessment_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_battle_damage_assessment_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battle_damage_assessment_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.authorization , packet1.destruction_pct , packet1.confidence_pct , packet1.target_class , packet1.target_force , packet1.functional_damage , packet1.physical_damage , packet1.reattack_recommended , packet1.track_uid );
    mavlink_msg_battle_damage_assessment_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("BATTLE_DAMAGE_ASSESSMENT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT) != NULL);
#endif
}

static void mavlink_test_esad_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ESAD_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_esad_state_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,18483,211,{ 22, 23, 24, 25, 26, 27, 28, 29 },46,113,180,247,58,125,192,3,{ 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85 }
    };
    mavlink_esad_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.arming_challenge_hash = packet_in.arming_challenge_hash;
        packet1.fault_flags = packet_in.fault_flags;
        packet1.input_1 = packet_in.input_1;
        packet1.input_2 = packet_in.input_2;
        packet1.arm_delay_remaining_s = packet_in.arm_delay_remaining_s;
        packet1.esad_id = packet_in.esad_id;
        packet1.arming_status = packet_in.arming_status;
        packet1.munition_status = packet_in.munition_status;
        packet1.ignition_status = packet_in.ignition_status;
        packet1.munition_type = packet_in.munition_type;
        packet1.store_id = packet_in.store_id;
        packet1.pin_state = packet_in.pin_state;
        packet1.arm_delay_setting = packet_in.arm_delay_setting;
        packet1.trigger_distance_mode = packet_in.trigger_distance_mode;
        
        mav_array_memcpy(packet1.sw_version_hash, packet_in.sw_version_hash, sizeof(uint8_t)*8);
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_esad_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_state_pack(system_id, component_id, &msg , packet1.time_usec , packet1.esad_id , packet1.arming_challenge_hash , packet1.fault_flags , packet1.input_1 , packet1.input_2 , packet1.sw_version_hash , packet1.arming_status , packet1.munition_status , packet1.ignition_status , packet1.munition_type , packet1.store_id , packet1.pin_state , packet1.arm_delay_setting , packet1.arm_delay_remaining_s , packet1.trigger_distance_mode , packet1.track_uid );
    mavlink_msg_esad_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.esad_id , packet1.arming_challenge_hash , packet1.fault_flags , packet1.input_1 , packet1.input_2 , packet1.sw_version_hash , packet1.arming_status , packet1.munition_status , packet1.ignition_status , packet1.munition_type , packet1.store_id , packet1.pin_state , packet1.arm_delay_setting , packet1.arm_delay_remaining_s , packet1.trigger_distance_mode , packet1.track_uid );
    mavlink_msg_esad_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_esad_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_state_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.esad_id , packet1.arming_challenge_hash , packet1.fault_flags , packet1.input_1 , packet1.input_2 , packet1.sw_version_hash , packet1.arming_status , packet1.munition_status , packet1.ignition_status , packet1.munition_type , packet1.store_id , packet1.pin_state , packet1.arm_delay_setting , packet1.arm_delay_remaining_s , packet1.trigger_distance_mode , packet1.track_uid );
    mavlink_msg_esad_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ESAD_STATE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ESAD_STATE) != NULL);
#endif
}

static void mavlink_test_esad_arming(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ESAD_ARMING >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_esad_arming_t packet_in = {
        93372036854775807ULL,963497880,41,108,175
    };
    mavlink_esad_arming_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.arming_challenge_hash = packet_in.arming_challenge_hash;
        packet1.esad_id = packet_in.esad_id;
        packet1.arming_request = packet_in.arming_request;
        packet1.store_id = packet_in.store_id;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_arming_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_esad_arming_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_arming_pack(system_id, component_id, &msg , packet1.time_usec , packet1.esad_id , packet1.arming_challenge_hash , packet1.arming_request , packet1.store_id );
    mavlink_msg_esad_arming_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_arming_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.esad_id , packet1.arming_challenge_hash , packet1.arming_request , packet1.store_id );
    mavlink_msg_esad_arming_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_esad_arming_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_arming_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.esad_id , packet1.arming_challenge_hash , packet1.arming_request , packet1.store_id );
    mavlink_msg_esad_arming_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ESAD_ARMING") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ESAD_ARMING) != NULL);
#endif
}

static void mavlink_test_esad_config(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ESAD_CONFIG >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_esad_config_t packet_in = {
        93372036854775807ULL,963497880,41,108,175
    };
    mavlink_esad_config_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.arming_challenge_hash = packet_in.arming_challenge_hash;
        packet1.esad_id = packet_in.esad_id;
        packet1.store_id = packet_in.store_id;
        packet1.trigger_distance_mode = packet_in.trigger_distance_mode;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ESAD_CONFIG_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_config_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_esad_config_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_config_pack(system_id, component_id, &msg , packet1.time_usec , packet1.arming_challenge_hash , packet1.esad_id , packet1.store_id , packet1.trigger_distance_mode );
    mavlink_msg_esad_config_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_config_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.arming_challenge_hash , packet1.esad_id , packet1.store_id , packet1.trigger_distance_mode );
    mavlink_msg_esad_config_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_esad_config_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_config_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.arming_challenge_hash , packet1.esad_id , packet1.store_id , packet1.trigger_distance_mode );
    mavlink_msg_esad_config_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ESAD_CONFIG") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ESAD_CONFIG) != NULL);
#endif
}

static void mavlink_test_rws_pose(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RWS_POSE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_rws_pose_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,{ 493.0, 494.0, 495.0, 496.0 },605.0,633.0,661.0,37
    };
    mavlink_rws_pose_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.cov_pos_x = packet_in.cov_pos_x;
        packet1.cov_pos_y = packet_in.cov_pos_y;
        packet1.cov_pos_z = packet_in.cov_pos_z;
        packet1.cov_vel_x = packet_in.cov_vel_x;
        packet1.cov_vel_y = packet_in.cov_vel_y;
        packet1.cov_vel_z = packet_in.cov_vel_z;
        packet1.offset_x = packet_in.offset_x;
        packet1.offset_y = packet_in.offset_y;
        packet1.offset_z = packet_in.offset_z;
        packet1.accuracy_roll = packet_in.accuracy_roll;
        packet1.accuracy_pitch = packet_in.accuracy_pitch;
        packet1.accuracy_yaw = packet_in.accuracy_yaw;
        packet1.coordinate_frame = packet_in.coordinate_frame;
        
        mav_array_memcpy(packet1.q, packet_in.q, sizeof(float)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RWS_POSE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RWS_POSE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_pose_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_rws_pose_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_pose_pack(system_id, component_id, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.offset_x , packet1.offset_y , packet1.offset_z , packet1.q , packet1.accuracy_roll , packet1.accuracy_pitch , packet1.accuracy_yaw , packet1.coordinate_frame );
    mavlink_msg_rws_pose_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_pose_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.offset_x , packet1.offset_y , packet1.offset_z , packet1.q , packet1.accuracy_roll , packet1.accuracy_pitch , packet1.accuracy_yaw , packet1.coordinate_frame );
    mavlink_msg_rws_pose_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_rws_pose_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_pose_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.offset_x , packet1.offset_y , packet1.offset_z , packet1.q , packet1.accuracy_roll , packet1.accuracy_pitch , packet1.accuracy_yaw , packet1.coordinate_frame );
    mavlink_msg_rws_pose_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("RWS_POSE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_RWS_POSE) != NULL);
#endif
}

static void mavlink_test_rws_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RWS_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_rws_state_t packet_in = {
        93372036854775807ULL,"IJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDE",51,118
    };
    mavlink_rws_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.arming_state = packet_in.arming_state;
        packet1.weapon_type = packet_in.weapon_type;
        
        mav_array_memcpy(packet1.weapon_string, packet_in.weapon_string, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RWS_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RWS_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_rws_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_state_pack(system_id, component_id, &msg , packet1.time_usec , packet1.weapon_string , packet1.arming_state , packet1.weapon_type );
    mavlink_msg_rws_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.weapon_string , packet1.arming_state , packet1.weapon_type );
    mavlink_msg_rws_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_rws_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_state_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.weapon_string , packet1.arming_state , packet1.weapon_type );
    mavlink_msg_rws_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("RWS_STATE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_RWS_STATE) != NULL);
#endif
}

static void mavlink_test_sensor_tasking(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SENSOR_TASKING >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_sensor_tasking_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,18275,199,10
    };
    mavlink_sensor_tasking_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.poi_lat = packet_in.poi_lat;
        packet1.poi_lon = packet_in.poi_lon;
        packet1.poi_alt = packet_in.poi_alt;
        packet1.task_id = packet_in.task_id;
        packet1.sensor_mode = packet_in.sensor_mode;
        packet1.status = packet_in.status;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SENSOR_TASKING_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_tasking_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_sensor_tasking_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_tasking_pack(system_id, component_id, &msg , packet1.time_usec , packet1.task_id , packet1.sensor_mode , packet1.status , packet1.poi_lat , packet1.poi_lon , packet1.poi_alt );
    mavlink_msg_sensor_tasking_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_tasking_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.task_id , packet1.sensor_mode , packet1.status , packet1.poi_lat , packet1.poi_lon , packet1.poi_alt );
    mavlink_msg_sensor_tasking_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_sensor_tasking_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sensor_tasking_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.task_id , packet1.sensor_mode , packet1.status , packet1.poi_lat , packet1.poi_lon , packet1.poi_alt );
    mavlink_msg_sensor_tasking_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SENSOR_TASKING") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SENSOR_TASKING) != NULL);
#endif
}

static void mavlink_test_cas_9line(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CAS_9LINE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_cas_9line_t packet_in = {
        93372036854775807ULL,963497880,963498088,963498296,963498504,963498712,963498920,963499128,963499336,19315,19419,19523,19627,149,216,27,94
    };
    mavlink_cas_9line_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.ip_lat = packet_in.ip_lat;
        packet1.ip_lon = packet_in.ip_lon;
        packet1.distance_m = packet_in.distance_m;
        packet1.tgt_elev_m = packet_in.tgt_elev_m;
        packet1.tgt_lat = packet_in.tgt_lat;
        packet1.tgt_lon = packet_in.tgt_lon;
        packet1.friendlies_lat = packet_in.friendlies_lat;
        packet1.friendlies_lon = packet_in.friendlies_lon;
        packet1.heading_deg = packet_in.heading_deg;
        packet1.offset_deg = packet_in.offset_deg;
        packet1.egress_deg = packet_in.egress_deg;
        packet1.final_attack_heading_deg = packet_in.final_attack_heading_deg;
        packet1.mark_type = packet_in.mark_type;
        packet1.laser_code_slot = packet_in.laser_code_slot;
        packet1.danger_close = packet_in.danger_close;
        packet1.delivery = packet_in.delivery;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CAS_9LINE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_cas_9line_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_cas_9line_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_cas_9line_pack(system_id, component_id, &msg , packet1.time_usec , packet1.ip_lat , packet1.ip_lon , packet1.heading_deg , packet1.offset_deg , packet1.distance_m , packet1.tgt_elev_m , packet1.tgt_lat , packet1.tgt_lon , packet1.mark_type , packet1.laser_code_slot , packet1.friendlies_lat , packet1.friendlies_lon , packet1.egress_deg , packet1.final_attack_heading_deg , packet1.danger_close , packet1.delivery );
    mavlink_msg_cas_9line_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_cas_9line_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.ip_lat , packet1.ip_lon , packet1.heading_deg , packet1.offset_deg , packet1.distance_m , packet1.tgt_elev_m , packet1.tgt_lat , packet1.tgt_lon , packet1.mark_type , packet1.laser_code_slot , packet1.friendlies_lat , packet1.friendlies_lon , packet1.egress_deg , packet1.final_attack_heading_deg , packet1.danger_close , packet1.delivery );
    mavlink_msg_cas_9line_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_cas_9line_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_cas_9line_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.ip_lat , packet1.ip_lon , packet1.heading_deg , packet1.offset_deg , packet1.distance_m , packet1.tgt_elev_m , packet1.tgt_lat , packet1.tgt_lon , packet1.mark_type , packet1.laser_code_slot , packet1.friendlies_lat , packet1.friendlies_lon , packet1.egress_deg , packet1.final_attack_heading_deg , packet1.danger_close , packet1.delivery );
    mavlink_msg_cas_9line_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CAS_9LINE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CAS_9LINE) != NULL);
#endif
}

static void mavlink_test_terminal_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TERMINAL_CONTROL >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_terminal_control_t packet_in = {
        93372036854775807ULL,17651,163,230,41,108
    };
    mavlink_terminal_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.sequence = packet_in.sequence;
        packet1.tac_type = packet_in.tac_type;
        packet1.clearance = packet_in.clearance;
        packet1.aircraft_call = packet_in.aircraft_call;
        packet1.abort_authority_present = packet_in.abort_authority_present;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TERMINAL_CONTROL_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_terminal_control_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_terminal_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_terminal_control_pack(system_id, component_id, &msg , packet1.time_usec , packet1.sequence , packet1.tac_type , packet1.clearance , packet1.aircraft_call , packet1.abort_authority_present );
    mavlink_msg_terminal_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_terminal_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.sequence , packet1.tac_type , packet1.clearance , packet1.aircraft_call , packet1.abort_authority_present );
    mavlink_msg_terminal_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_terminal_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_terminal_control_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.sequence , packet1.tac_type , packet1.clearance , packet1.aircraft_call , packet1.abort_authority_present );
    mavlink_msg_terminal_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TERMINAL_CONTROL") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TERMINAL_CONTROL) != NULL);
#endif
}

static void mavlink_test_target_cue(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_CUE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_cue_t packet_in = {
        93372036854775807ULL,963497880,963498088,963498296,963498504,185.0,213.0,241.0,269.0,297.0,137,204,15,82,"WXYZABCDEFGHIJKLMNO"
    };
    mavlink_target_cue_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.cue_id = packet_in.cue_id;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.confidence_score = packet_in.confidence_score;
        packet1.origin_sysid = packet_in.origin_sysid;
        packet1.cue_type = packet_in.cue_type;
        packet1.target_class = packet_in.target_class;
        packet1.target_force = packet_in.target_force;
        
        mav_array_memcpy(packet1.name, packet_in.name, sizeof(char)*20);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_CUE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_cue_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_cue_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_cue_pack(system_id, component_id, &msg , packet1.time_usec , packet1.cue_id , packet1.target_set_id , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.confidence_score , packet1.origin_sysid , packet1.cue_type , packet1.target_class , packet1.target_force , packet1.name );
    mavlink_msg_target_cue_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_cue_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.cue_id , packet1.target_set_id , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.confidence_score , packet1.origin_sysid , packet1.cue_type , packet1.target_class , packet1.target_force , packet1.name );
    mavlink_msg_target_cue_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_cue_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_cue_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.cue_id , packet1.target_set_id , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.confidence_score , packet1.origin_sysid , packet1.cue_type , packet1.target_class , packet1.target_force , packet1.name );
    mavlink_msg_target_cue_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_CUE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_CUE) != NULL);
#endif
}

static void mavlink_test_mavlink_m_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MAVLINK_M_ACK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mavlink_m_ack_t packet_in = {
        93372036854775807ULL,963497880,963498088,53,120,187,"TUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOP"
    };
    mavlink_mavlink_m_ack_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.ack_msgid = packet_in.ack_msgid;
        packet1.ack_instance = packet_in.ack_instance;
        packet1.origin_sysid = packet_in.origin_sysid;
        packet1.ack_sysid = packet_in.ack_sysid;
        packet1.result = packet_in.result;
        
        mav_array_memcpy(packet1.reason, packet_in.reason, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MAVLINK_M_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MAVLINK_M_ACK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mavlink_m_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mavlink_m_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mavlink_m_ack_pack(system_id, component_id, &msg , packet1.time_usec , packet1.ack_msgid , packet1.ack_instance , packet1.origin_sysid , packet1.ack_sysid , packet1.result , packet1.reason );
    mavlink_msg_mavlink_m_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mavlink_m_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.ack_msgid , packet1.ack_instance , packet1.origin_sysid , packet1.ack_sysid , packet1.result , packet1.reason );
    mavlink_msg_mavlink_m_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mavlink_m_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mavlink_m_ack_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.ack_msgid , packet1.ack_instance , packet1.origin_sysid , packet1.ack_sysid , packet1.result , packet1.reason );
    mavlink_msg_mavlink_m_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MAVLINK_M_ACK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MAVLINK_M_ACK) != NULL);
#endif
}

static void mavlink_test_store_sensor_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_STORE_SENSOR_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_store_sensor_status_t packet_in = {
        93372036854775807ULL,73.0,101.0,129.0,65,132,199,10
    };
    mavlink_store_sensor_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.value = packet_in.value;
        packet1.value_min = packet_in.value_min;
        packet1.value_max = packet_in.value_max;
        packet1.store_id = packet_in.store_id;
        packet1.sensor_type = packet_in.sensor_type;
        packet1.sensor_index = packet_in.sensor_index;
        packet1.health = packet_in.health;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_STORE_SENSOR_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_sensor_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_store_sensor_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_sensor_status_pack(system_id, component_id, &msg , packet1.time_usec , packet1.value , packet1.value_min , packet1.value_max , packet1.store_id , packet1.sensor_type , packet1.sensor_index , packet1.health );
    mavlink_msg_store_sensor_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_sensor_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.value , packet1.value_min , packet1.value_max , packet1.store_id , packet1.sensor_type , packet1.sensor_index , packet1.health );
    mavlink_msg_store_sensor_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_store_sensor_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_sensor_status_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.value , packet1.value_min , packet1.value_max , packet1.store_id , packet1.sensor_type , packet1.sensor_index , packet1.health );
    mavlink_msg_store_sensor_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("STORE_SENSOR_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_STORE_SENSOR_STATUS) != NULL);
#endif
}

static void mavlink_test_store_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_STORE_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_store_status_t packet_in = {
        93372036854775807ULL,963497880,41,108,175,242,53,120
    };
    mavlink_store_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.sensor_fault_mask = packet_in.sensor_fault_mask;
        packet1.store_id = packet_in.store_id;
        packet1.store_count = packet_in.store_count;
        packet1.readiness = packet_in.readiness;
        packet1.arming_status = packet_in.arming_status;
        packet1.sensors_healthy = packet_in.sensors_healthy;
        packet1.sensors_total = packet_in.sensors_total;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_STORE_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_store_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_status_pack(system_id, component_id, &msg , packet1.time_usec , packet1.sensor_fault_mask , packet1.store_id , packet1.store_count , packet1.readiness , packet1.arming_status , packet1.sensors_healthy , packet1.sensors_total );
    mavlink_msg_store_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.sensor_fault_mask , packet1.store_id , packet1.store_count , packet1.readiness , packet1.arming_status , packet1.sensors_healthy , packet1.sensors_total );
    mavlink_msg_store_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_store_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_status_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.sensor_fault_mask , packet1.store_id , packet1.store_count , packet1.readiness , packet1.arming_status , packet1.sensors_healthy , packet1.sensors_total );
    mavlink_msg_store_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("STORE_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_STORE_STATUS) != NULL);
#endif
}

static void mavlink_test_track_identity(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TRACK_IDENTITY >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_track_identity_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,157.0,18483,{ 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226 },{ 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 },51,118,185,252,63,130,197,"NOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJ","LMNOPQRSTUVWXYZABCD",90,157,224,35,102,169
    };
    mavlink_track_identity_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.first_detected_usec = packet_in.first_detected_usec;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.id_confidence = packet_in.id_confidence;
        packet1.atr_model_id = packet_in.atr_model_id;
        packet1.origin_sysid = packet_in.origin_sysid;
        packet1.origin_sensor = packet_in.origin_sensor;
        packet1.id_method = packet_in.id_method;
        packet1.pid_status = packet_in.pid_status;
        packet1.track_rel = packet_in.track_rel;
        packet1.target_class = packet_in.target_class;
        packet1.target_force = packet_in.target_force;
        packet1.external_track_type = packet_in.external_track_type;
        packet1.stanag_identity = packet_in.stanag_identity;
        packet1.environment = packet_in.environment;
        packet1.atr_confidence_pct = packet_in.atr_confidence_pct;
        packet1.atr_conf_tier = packet_in.atr_conf_tier;
        packet1.sidc_context = packet_in.sidc_context;
        
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        mav_array_memcpy(packet1.parent_track_uid, packet_in.parent_track_uid, sizeof(uint8_t)*16);
        mav_array_memcpy(packet1.id_basis, packet_in.id_basis, sizeof(char)*50);
        mav_array_memcpy(packet1.external_track_number, packet_in.external_track_number, sizeof(char)*20);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TRACK_IDENTITY_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_track_identity_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_track_identity_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_track_identity_pack(system_id, component_id, &msg , packet1.time_usec , packet1.track_uid , packet1.parent_track_uid , packet1.target_set_id , packet1.first_detected_usec , packet1.id_confidence , packet1.origin_sysid , packet1.origin_sensor , packet1.id_method , packet1.pid_status , packet1.track_rel , packet1.target_class , packet1.target_force , packet1.id_basis , packet1.external_track_number , packet1.external_track_type , packet1.stanag_identity , packet1.environment , packet1.atr_confidence_pct , packet1.atr_model_id , packet1.atr_conf_tier , packet1.sidc_context );
    mavlink_msg_track_identity_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_track_identity_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.track_uid , packet1.parent_track_uid , packet1.target_set_id , packet1.first_detected_usec , packet1.id_confidence , packet1.origin_sysid , packet1.origin_sensor , packet1.id_method , packet1.pid_status , packet1.track_rel , packet1.target_class , packet1.target_force , packet1.id_basis , packet1.external_track_number , packet1.external_track_type , packet1.stanag_identity , packet1.environment , packet1.atr_confidence_pct , packet1.atr_model_id , packet1.atr_conf_tier , packet1.sidc_context );
    mavlink_msg_track_identity_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_track_identity_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_track_identity_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.track_uid , packet1.parent_track_uid , packet1.target_set_id , packet1.first_detected_usec , packet1.id_confidence , packet1.origin_sysid , packet1.origin_sensor , packet1.id_method , packet1.pid_status , packet1.track_rel , packet1.target_class , packet1.target_force , packet1.id_basis , packet1.external_track_number , packet1.external_track_type , packet1.stanag_identity , packet1.environment , packet1.atr_confidence_pct , packet1.atr_model_id , packet1.atr_conf_tier , packet1.sidc_context );
    mavlink_msg_track_identity_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TRACK_IDENTITY") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TRACK_IDENTITY) != NULL);
#endif
}

static void mavlink_test_target_authorization(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_AUTHORIZATION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_authorization_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,213.0,{ 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116 },{ 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164 },{ 197, 198, 199, 200, 201, 202, 203, 204 },221,32,99,"XYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRST",188
    };
    mavlink_target_authorization_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.decision_usec = packet_in.decision_usec;
        packet1.valid_until_usec = packet_in.valid_until_usec;
        packet1.auth_nonce = packet_in.auth_nonce;
        packet1.collateral_estimate = packet_in.collateral_estimate;
        packet1.pid_status = packet_in.pid_status;
        packet1.roe_state = packet_in.roe_state;
        packet1.nostrike_status = packet_in.nostrike_status;
        packet1.cde_level = packet_in.cde_level;
        
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        mav_array_memcpy(packet1.authority_id, packet_in.authority_id, sizeof(uint8_t)*16);
        mav_array_memcpy(packet1.authorization_token, packet_in.authorization_token, sizeof(uint8_t)*8);
        mav_array_memcpy(packet1.authority_role, packet_in.authority_role, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_AUTHORIZATION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_authorization_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_authorization_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_authorization_pack(system_id, component_id, &msg , packet1.time_usec , packet1.track_uid , packet1.decision_usec , packet1.valid_until_usec , packet1.auth_nonce , packet1.collateral_estimate , packet1.authority_id , packet1.authorization_token , packet1.pid_status , packet1.roe_state , packet1.nostrike_status , packet1.authority_role , packet1.cde_level );
    mavlink_msg_target_authorization_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_authorization_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.track_uid , packet1.decision_usec , packet1.valid_until_usec , packet1.auth_nonce , packet1.collateral_estimate , packet1.authority_id , packet1.authorization_token , packet1.pid_status , packet1.roe_state , packet1.nostrike_status , packet1.authority_role , packet1.cde_level );
    mavlink_msg_target_authorization_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_authorization_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_authorization_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.track_uid , packet1.decision_usec , packet1.valid_until_usec , packet1.auth_nonce , packet1.collateral_estimate , packet1.authority_id , packet1.authorization_token , packet1.pid_status , packet1.roe_state , packet1.nostrike_status , packet1.authority_role , packet1.cde_level );
    mavlink_msg_target_authorization_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_AUTHORIZATION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_AUTHORIZATION) != NULL);
#endif
}

static void mavlink_test_engagement_directive(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ENGAGEMENT_DIRECTIVE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_engagement_directive_t packet_in = {
        93372036854775807ULL,963497880,963498088,963498296,157.0,18483,{ 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226 },3,70
    };
    mavlink_engagement_directive_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.effector_id = packet_in.effector_id;
        packet1.retarget_lat = packet_in.retarget_lat;
        packet1.retarget_lon = packet_in.retarget_lon;
        packet1.retarget_alt = packet_in.retarget_alt;
        packet1.sequence = packet_in.sequence;
        packet1.directive = packet_in.directive;
        packet1.origin_sysid = packet_in.origin_sysid;
        
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ENGAGEMENT_DIRECTIVE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ENGAGEMENT_DIRECTIVE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_engagement_directive_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_engagement_directive_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_engagement_directive_pack(system_id, component_id, &msg , packet1.time_usec , packet1.track_uid , packet1.sequence , packet1.effector_id , packet1.retarget_lat , packet1.retarget_lon , packet1.retarget_alt , packet1.directive , packet1.origin_sysid );
    mavlink_msg_engagement_directive_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_engagement_directive_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.track_uid , packet1.sequence , packet1.effector_id , packet1.retarget_lat , packet1.retarget_lon , packet1.retarget_alt , packet1.directive , packet1.origin_sysid );
    mavlink_msg_engagement_directive_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_engagement_directive_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_engagement_directive_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.track_uid , packet1.sequence , packet1.effector_id , packet1.retarget_lat , packet1.retarget_lon , packet1.retarget_alt , packet1.directive , packet1.origin_sysid );
    mavlink_msg_engagement_directive_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ENGAGEMENT_DIRECTIVE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ENGAGEMENT_DIRECTIVE) != NULL);
#endif
}

static void mavlink_test_call_for_fire(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CALL_FOR_FIRE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_call_for_fire_t packet_in = {
        93372036854775807ULL,17651,17755,17859,17963,18067,18171,18275,18379,77,144,211,22,89,156,223,34,101,168,{ 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250 }
    };
    mavlink_call_for_fire_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.sequence = packet_in.sequence;
        packet1.rounds = packet_in.rounds;
        packet1.duration_s = packet_in.duration_s;
        packet1.sheaf_length_m = packet_in.sheaf_length_m;
        packet1.sheaf_width_m = packet_in.sheaf_width_m;
        packet1.sheaf_attitude_cdeg = packet_in.sheaf_attitude_cdeg;
        packet1.ot_direction_cdeg = packet_in.ot_direction_cdeg;
        packet1.ot_factor_dm = packet_in.ot_factor_dm;
        packet1.mission_type = packet_in.mission_type;
        packet1.location_method = packet_in.location_method;
        packet1.adjustment_type = packet_in.adjustment_type;
        packet1.trajectory = packet_in.trajectory;
        packet1.sheaf = packet_in.sheaf;
        packet1.control_method = packet_in.control_method;
        packet1.danger_close = packet_in.danger_close;
        packet1.tle_category = packet_in.tle_category;
        packet1.mensurated = packet_in.mensurated;
        packet1.effect_verb = packet_in.effect_verb;
        
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CALL_FOR_FIRE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_call_for_fire_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_call_for_fire_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_call_for_fire_pack(system_id, component_id, &msg , packet1.time_usec , packet1.sequence , packet1.mission_type , packet1.location_method , packet1.adjustment_type , packet1.trajectory , packet1.sheaf , packet1.control_method , packet1.danger_close , packet1.rounds , packet1.duration_s , packet1.tle_category , packet1.mensurated , packet1.sheaf_length_m , packet1.sheaf_width_m , packet1.sheaf_attitude_cdeg , packet1.ot_direction_cdeg , packet1.ot_factor_dm , packet1.effect_verb , packet1.track_uid );
    mavlink_msg_call_for_fire_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_call_for_fire_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.sequence , packet1.mission_type , packet1.location_method , packet1.adjustment_type , packet1.trajectory , packet1.sheaf , packet1.control_method , packet1.danger_close , packet1.rounds , packet1.duration_s , packet1.tle_category , packet1.mensurated , packet1.sheaf_length_m , packet1.sheaf_width_m , packet1.sheaf_attitude_cdeg , packet1.ot_direction_cdeg , packet1.ot_factor_dm , packet1.effect_verb , packet1.track_uid );
    mavlink_msg_call_for_fire_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_call_for_fire_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_call_for_fire_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.sequence , packet1.mission_type , packet1.location_method , packet1.adjustment_type , packet1.trajectory , packet1.sheaf , packet1.control_method , packet1.danger_close , packet1.rounds , packet1.duration_s , packet1.tle_category , packet1.mensurated , packet1.sheaf_length_m , packet1.sheaf_width_m , packet1.sheaf_attitude_cdeg , packet1.ot_direction_cdeg , packet1.ot_factor_dm , packet1.effect_verb , packet1.track_uid );
    mavlink_msg_call_for_fire_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CALL_FOR_FIRE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CALL_FOR_FIRE) != NULL);
#endif
}

static void mavlink_test_participant_position(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PARTICIPANT_POSITION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_participant_position_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,185.0,213.0,241.0,"KLMNOPQRSTUVWXYZABC","EFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZA",195,6,73,140
    };
    mavlink_participant_position_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.course = packet_in.course;
        packet1.origin_sysid = packet_in.origin_sysid;
        packet1.external_track_type = packet_in.external_track_type;
        packet1.stanag_identity = packet_in.stanag_identity;
        packet1.ppli_type = packet_in.ppli_type;
        
        mav_array_memcpy(packet1.external_track_number, packet_in.external_track_number, sizeof(char)*20);
        mav_array_memcpy(packet1.callsign, packet_in.callsign, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PARTICIPANT_POSITION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_participant_position_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_participant_position_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_participant_position_pack(system_id, component_id, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.course , packet1.external_track_number , packet1.callsign , packet1.origin_sysid , packet1.external_track_type , packet1.stanag_identity , packet1.ppli_type );
    mavlink_msg_participant_position_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_participant_position_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.course , packet1.external_track_number , packet1.callsign , packet1.origin_sysid , packet1.external_track_type , packet1.stanag_identity , packet1.ppli_type );
    mavlink_msg_participant_position_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_participant_position_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_participant_position_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.course , packet1.external_track_number , packet1.callsign , packet1.origin_sysid , packet1.external_track_type , packet1.stanag_identity , packet1.ppli_type );
    mavlink_msg_participant_position_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PARTICIPANT_POSITION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PARTICIPANT_POSITION) != NULL);
#endif
}

static void mavlink_test_store_munition(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_STORE_MUNITION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_store_munition_t packet_in = {
        93372036854775807ULL,73.0,17859,"OPQRSTUVWXYZABCDEFG","IJKLMNOPQRSTUVWXYZABCDEFGHIJK",197,8,75,142,209,20,87,154,221,32,99
    };
    mavlink_store_munition_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.mass = packet_in.mass;
        packet1.quantity_remaining = packet_in.quantity_remaining;
        packet1.store_id = packet_in.store_id;
        packet1.munition_type = packet_in.munition_type;
        packet1.guidance = packet_in.guidance;
        packet1.warhead = packet_in.warhead;
        packet1.arming_status = packet_in.arming_status;
        packet1.fuze_health = packet_in.fuze_health;
        packet1.external_track_type = packet_in.external_track_type;
        packet1.munition_family = packet_in.munition_family;
        packet1.munition_payload = packet_in.munition_payload;
        packet1.warhead_mode = packet_in.warhead_mode;
        packet1.sd_duration = packet_in.sd_duration;
        
        mav_array_memcpy(packet1.external_track_number, packet_in.external_track_number, sizeof(char)*20);
        mav_array_memcpy(packet1.nomenclature, packet_in.nomenclature, sizeof(char)*30);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_STORE_MUNITION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_munition_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_store_munition_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_munition_pack(system_id, component_id, &msg , packet1.time_usec , packet1.mass , packet1.external_track_number , packet1.nomenclature , packet1.quantity_remaining , packet1.store_id , packet1.munition_type , packet1.guidance , packet1.warhead , packet1.arming_status , packet1.fuze_health , packet1.external_track_type , packet1.munition_family , packet1.munition_payload , packet1.warhead_mode , packet1.sd_duration );
    mavlink_msg_store_munition_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_munition_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.mass , packet1.external_track_number , packet1.nomenclature , packet1.quantity_remaining , packet1.store_id , packet1.munition_type , packet1.guidance , packet1.warhead , packet1.arming_status , packet1.fuze_health , packet1.external_track_type , packet1.munition_family , packet1.munition_payload , packet1.warhead_mode , packet1.sd_duration );
    mavlink_msg_store_munition_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_store_munition_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_store_munition_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.mass , packet1.external_track_number , packet1.nomenclature , packet1.quantity_remaining , packet1.store_id , packet1.munition_type , packet1.guidance , packet1.warhead , packet1.arming_status , packet1.fuze_health , packet1.external_track_type , packet1.munition_family , packet1.munition_payload , packet1.warhead_mode , packet1.sd_duration );
    mavlink_msg_store_munition_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("STORE_MUNITION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_STORE_MUNITION) != NULL);
#endif
}

static void mavlink_test_loiter_munition_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_loiter_munition_control_t packet_in = {
        93372036854775807ULL,963497880,963498088,{ 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 },101,168,235,46,113,180
    };
    mavlink_loiter_munition_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.loiter_lat = packet_in.loiter_lat;
        packet1.loiter_lon = packet_in.loiter_lon;
        packet1.consent_state = packet_in.consent_state;
        packet1.terminate = packet_in.terminate;
        packet1.tst_status = packet_in.tst_status;
        packet1.pid_status = packet_in.pid_status;
        packet1.cde_level = packet_in.cde_level;
        packet1.dmpi_kind = packet_in.dmpi_kind;
        
        mav_array_memcpy(packet1.track_uid, packet_in.track_uid, sizeof(uint8_t)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loiter_munition_control_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_loiter_munition_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loiter_munition_control_pack(system_id, component_id, &msg , packet1.time_usec , packet1.track_uid , packet1.consent_state , packet1.terminate , packet1.tst_status , packet1.pid_status , packet1.cde_level , packet1.loiter_lat , packet1.loiter_lon , packet1.dmpi_kind );
    mavlink_msg_loiter_munition_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loiter_munition_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.track_uid , packet1.consent_state , packet1.terminate , packet1.tst_status , packet1.pid_status , packet1.cde_level , packet1.loiter_lat , packet1.loiter_lon , packet1.dmpi_kind );
    mavlink_msg_loiter_munition_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_loiter_munition_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_loiter_munition_control_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.track_uid , packet1.consent_state , packet1.terminate , packet1.tst_status , packet1.pid_status , packet1.cde_level , packet1.loiter_lat , packet1.loiter_lon , packet1.dmpi_kind );
    mavlink_msg_loiter_munition_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LOITER_MUNITION_CONTROL") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LOITER_MUNITION_CONTROL) != NULL);
#endif
}

static void mavlink_test_military(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_target_set_coord(system_id, component_id, last_msg);
    mavlink_test_target_box_coord(system_id, component_id, last_msg);
    mavlink_test_target(system_id, component_id, last_msg);
    mavlink_test_fires(system_id, component_id, last_msg);
    mavlink_test_splash_correction(system_id, component_id, last_msg);
    mavlink_test_target_handover(system_id, component_id, last_msg);
    mavlink_test_battle_damage_assessment(system_id, component_id, last_msg);
    mavlink_test_esad_state(system_id, component_id, last_msg);
    mavlink_test_esad_arming(system_id, component_id, last_msg);
    mavlink_test_esad_config(system_id, component_id, last_msg);
    mavlink_test_rws_pose(system_id, component_id, last_msg);
    mavlink_test_rws_state(system_id, component_id, last_msg);
    mavlink_test_sensor_tasking(system_id, component_id, last_msg);
    mavlink_test_cas_9line(system_id, component_id, last_msg);
    mavlink_test_terminal_control(system_id, component_id, last_msg);
    mavlink_test_target_cue(system_id, component_id, last_msg);
    mavlink_test_mavlink_m_ack(system_id, component_id, last_msg);
    mavlink_test_store_sensor_status(system_id, component_id, last_msg);
    mavlink_test_store_status(system_id, component_id, last_msg);
    mavlink_test_track_identity(system_id, component_id, last_msg);
    mavlink_test_target_authorization(system_id, component_id, last_msg);
    mavlink_test_engagement_directive(system_id, component_id, last_msg);
    mavlink_test_call_for_fire(system_id, component_id, last_msg);
    mavlink_test_participant_position(system_id, component_id, last_msg);
    mavlink_test_store_munition(system_id, component_id, last_msg);
    mavlink_test_loiter_munition_control(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MILITARY_TESTSUITE_H
