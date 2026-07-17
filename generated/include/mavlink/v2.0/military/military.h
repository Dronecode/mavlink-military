/** @file
 *  @brief MAVLink comm protocol generated from military.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_MILITARY_H
#define MAVLINK_MILITARY_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_MILITARY.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_MILITARY_XML_HASH -2798040742744071622

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 50, 9, 9, 0, 0, 0}, {1, 124, 31, 43, 0, 0, 0}, {2, 137, 12, 12, 0, 0, 0}, {4, 237, 14, 14, 3, 12, 13}, {5, 217, 28, 28, 1, 0, 0}, {6, 104, 3, 3, 0, 0, 0}, {7, 119, 32, 32, 0, 0, 0}, {8, 117, 36, 36, 0, 0, 0}, {11, 89, 6, 6, 1, 4, 0}, {20, 214, 20, 20, 3, 2, 3}, {21, 159, 2, 2, 3, 0, 1}, {22, 220, 25, 25, 0, 0, 0}, {23, 168, 23, 23, 3, 4, 5}, {24, 24, 30, 52, 0, 0, 0}, {25, 23, 101, 101, 0, 0, 0}, {26, 170, 22, 24, 0, 0, 0}, {27, 144, 26, 29, 0, 0, 0}, {28, 67, 16, 16, 0, 0, 0}, {29, 115, 14, 16, 0, 0, 0}, {30, 39, 28, 28, 0, 0, 0}, {31, 246, 32, 48, 0, 0, 0}, {32, 185, 28, 28, 0, 0, 0}, {33, 104, 28, 28, 0, 0, 0}, {34, 237, 22, 22, 0, 0, 0}, {35, 244, 22, 22, 0, 0, 0}, {36, 222, 21, 37, 0, 0, 0}, {37, 212, 6, 7, 3, 4, 5}, {38, 9, 6, 7, 3, 4, 5}, {39, 254, 37, 38, 3, 32, 33}, {40, 230, 4, 5, 3, 2, 3}, {41, 28, 4, 4, 3, 2, 3}, {42, 28, 2, 18, 0, 0, 0}, {43, 132, 2, 3, 3, 0, 1}, {44, 221, 4, 9, 3, 2, 3}, {45, 232, 2, 3, 3, 0, 1}, {46, 11, 2, 2, 0, 0, 0}, {47, 153, 3, 8, 3, 0, 1}, {48, 41, 13, 21, 1, 12, 0}, {49, 39, 12, 20, 0, 0, 0}, {50, 78, 37, 37, 3, 18, 19}, {51, 196, 4, 5, 3, 2, 3}, {54, 15, 27, 27, 3, 24, 25}, {55, 3, 25, 25, 0, 0, 0}, {61, 167, 72, 72, 0, 0, 0}, {62, 183, 26, 26, 0, 0, 0}, {63, 119, 181, 181, 0, 0, 0}, {64, 191, 225, 225, 0, 0, 0}, {65, 118, 42, 42, 0, 0, 0}, {66, 148, 6, 6, 3, 2, 3}, {67, 21, 4, 4, 0, 0, 0}, {69, 243, 11, 30, 1, 10, 0}, {70, 124, 18, 38, 3, 16, 17}, {73, 38, 37, 38, 3, 32, 33}, {74, 20, 20, 20, 0, 0, 0}, {75, 158, 35, 35, 3, 30, 31}, {76, 152, 33, 33, 3, 30, 31}, {77, 143, 3, 10, 3, 8, 9}, {80, 14, 4, 4, 3, 2, 3}, {81, 106, 22, 22, 0, 0, 0}, {82, 49, 39, 51, 3, 36, 37}, {83, 22, 37, 37, 0, 0, 0}, {84, 143, 53, 53, 3, 50, 51}, {85, 140, 51, 51, 0, 0, 0}, {86, 5, 53, 53, 3, 50, 51}, {87, 150, 51, 51, 0, 0, 0}, {89, 231, 28, 28, 0, 0, 0}, {90, 183, 56, 56, 0, 0, 0}, {91, 63, 42, 42, 0, 0, 0}, {92, 54, 33, 33, 0, 0, 0}, {93, 47, 81, 81, 0, 0, 0}, {100, 175, 26, 34, 0, 0, 0}, {101, 102, 32, 117, 0, 0, 0}, {102, 158, 32, 117, 0, 0, 0}, {103, 208, 20, 57, 0, 0, 0}, {104, 56, 32, 116, 0, 0, 0}, {105, 93, 62, 63, 0, 0, 0}, {106, 138, 44, 44, 0, 0, 0}, {107, 108, 64, 65, 0, 0, 0}, {108, 32, 84, 92, 0, 0, 0}, {109, 185, 9, 9, 0, 0, 0}, {110, 84, 254, 254, 3, 1, 2}, {111, 34, 16, 18, 3, 16, 17}, {112, 174, 12, 12, 0, 0, 0}, {113, 124, 36, 39, 0, 0, 0}, {114, 237, 44, 44, 0, 0, 0}, {115, 4, 64, 64, 0, 0, 0}, {116, 76, 22, 24, 0, 0, 0}, {117, 128, 6, 6, 3, 4, 5}, {118, 56, 14, 14, 0, 0, 0}, {119, 116, 12, 12, 3, 10, 11}, {120, 134, 97, 97, 0, 0, 0}, {121, 237, 2, 2, 3, 0, 1}, {122, 203, 2, 2, 3, 0, 1}, {123, 250, 113, 113, 3, 0, 1}, {124, 87, 35, 57, 0, 0, 0}, {125, 203, 6, 6, 0, 0, 0}, {126, 220, 79, 81, 3, 79, 80}, {127, 25, 35, 35, 0, 0, 0}, {128, 226, 35, 35, 0, 0, 0}, {129, 46, 22, 24, 0, 0, 0}, {130, 29, 13, 13, 0, 0, 0}, {131, 223, 255, 255, 0, 0, 0}, {132, 85, 14, 39, 0, 0, 0}, {133, 6, 18, 18, 0, 0, 0}, {134, 229, 43, 43, 0, 0, 0}, {135, 203, 8, 8, 0, 0, 0}, {136, 1, 22, 22, 0, 0, 0}, {137, 195, 14, 16, 0, 0, 0}, {138, 109, 36, 120, 0, 0, 0}, {139, 168, 43, 43, 3, 41, 42}, {140, 181, 41, 41, 0, 0, 0}, {141, 47, 32, 32, 0, 0, 0}, {142, 72, 243, 243, 0, 0, 0}, {143, 131, 14, 16, 0, 0, 0}, {144, 127, 93, 93, 0, 0, 0}, {146, 103, 100, 100, 0, 0, 0}, {147, 154, 36, 54, 0, 0, 0}, {148, 178, 60, 78, 0, 0, 0}, {149, 200, 30, 60, 0, 0, 0}, {162, 189, 8, 9, 0, 0, 0}, {192, 36, 44, 54, 0, 0, 0}, {225, 208, 65, 73, 0, 0, 0}, {230, 163, 42, 42, 0, 0, 0}, {231, 105, 40, 40, 0, 0, 0}, {232, 151, 63, 65, 0, 0, 0}, {233, 35, 182, 182, 0, 0, 0}, {234, 150, 40, 40, 0, 0, 0}, {235, 179, 42, 42, 0, 0, 0}, {241, 90, 32, 32, 0, 0, 0}, {242, 104, 52, 60, 0, 0, 0}, {243, 85, 53, 61, 1, 52, 0}, {244, 95, 6, 6, 0, 0, 0}, {245, 130, 2, 2, 0, 0, 0}, {246, 184, 38, 38, 0, 0, 0}, {247, 81, 19, 19, 0, 0, 0}, {248, 8, 254, 254, 3, 3, 4}, {249, 204, 36, 36, 0, 0, 0}, {250, 49, 30, 30, 0, 0, 0}, {251, 170, 18, 18, 0, 0, 0}, {252, 44, 18, 18, 0, 0, 0}, {253, 83, 51, 54, 0, 0, 0}, {254, 46, 9, 9, 0, 0, 0}, {256, 71, 42, 42, 3, 8, 9}, {257, 131, 9, 9, 0, 0, 0}, {258, 187, 32, 232, 3, 0, 1}, {259, 92, 235, 237, 0, 0, 0}, {260, 146, 5, 14, 0, 0, 0}, {261, 179, 27, 61, 0, 0, 0}, {262, 12, 18, 23, 0, 0, 0}, {263, 133, 255, 255, 0, 0, 0}, {264, 49, 28, 32, 0, 0, 0}, {265, 26, 16, 20, 0, 0, 0}, {266, 193, 255, 255, 3, 2, 3}, {267, 35, 255, 255, 3, 2, 3}, {268, 14, 4, 4, 3, 2, 3}, {269, 109, 213, 215, 0, 0, 0}, {270, 59, 19, 20, 0, 0, 0}, {271, 22, 52, 53, 0, 0, 0}, {275, 126, 31, 32, 0, 0, 0}, {276, 18, 49, 50, 0, 0, 0}, {277, 62, 30, 30, 0, 0, 0}, {280, 70, 33, 33, 0, 0, 0}, {281, 48, 13, 13, 0, 0, 0}, {282, 123, 35, 35, 3, 32, 33}, {283, 74, 144, 149, 0, 0, 0}, {284, 99, 32, 32, 3, 30, 31}, {285, 137, 40, 49, 3, 38, 39}, {286, 210, 53, 57, 3, 50, 51}, {287, 1, 23, 23, 3, 20, 21}, {288, 20, 23, 23, 3, 20, 21}, {290, 251, 46, 46, 0, 0, 0}, {291, 10, 57, 57, 0, 0, 0}, {295, 234, 12, 12, 0, 0, 0}, {296, 158, 41, 41, 3, 36, 37}, {299, 19, 96, 98, 0, 0, 0}, {300, 217, 22, 22, 0, 0, 0}, {301, 243, 58, 58, 0, 0, 0}, {310, 28, 17, 17, 0, 0, 0}, {311, 95, 116, 116, 0, 0, 0}, {320, 243, 20, 20, 3, 2, 3}, {321, 88, 2, 2, 3, 0, 1}, {322, 243, 149, 149, 0, 0, 0}, {323, 78, 147, 147, 3, 0, 1}, {324, 132, 146, 146, 0, 0, 0}, {330, 23, 158, 167, 0, 0, 0}, {331, 91, 230, 233, 0, 0, 0}, {332, 236, 239, 239, 0, 0, 0}, {333, 231, 109, 109, 0, 0, 0}, {334, 72, 10, 53, 0, 0, 0}, {335, 225, 24, 24, 0, 0, 0}, {336, 245, 84, 84, 0, 0, 0}, {339, 199, 5, 5, 0, 0, 0}, {340, 99, 70, 70, 0, 0, 0}, {345, 209, 21, 21, 3, 2, 3}, {350, 232, 20, 252, 0, 0, 0}, {360, 11, 25, 25, 0, 0, 0}, {361, 93, 33, 33, 0, 0, 0}, {370, 75, 87, 109, 0, 0, 0}, {371, 10, 26, 26, 0, 0, 0}, {372, 26, 140, 140, 0, 0, 0}, {373, 117, 42, 42, 0, 0, 0}, {375, 251, 140, 140, 0, 0, 0}, {376, 199, 8, 8, 0, 0, 0}, {380, 232, 20, 20, 0, 0, 0}, {385, 147, 133, 133, 3, 2, 3}, {386, 132, 16, 16, 3, 4, 5}, {387, 4, 72, 72, 3, 4, 5}, {388, 8, 37, 37, 3, 32, 33}, {390, 156, 238, 240, 0, 0, 0}, {395, 0, 212, 212, 0, 0, 0}, {396, 50, 160, 160, 0, 0, 0}, {397, 182, 108, 108, 0, 0, 0}, {400, 110, 254, 254, 3, 4, 5}, {401, 183, 6, 6, 3, 4, 5}, {410, 160, 53, 53, 0, 0, 0}, {411, 106, 3, 3, 0, 0, 0}, {412, 33, 6, 6, 3, 4, 5}, {413, 77, 7, 7, 3, 4, 5}, {435, 134, 46, 46, 0, 0, 0}, {436, 193, 9, 9, 0, 0, 0}, {437, 30, 1, 1, 0, 0, 0}, {440, 66, 35, 35, 0, 0, 0}, {9000, 113, 137, 137, 0, 0, 0}, {9005, 117, 34, 34, 0, 0, 0}, {12900, 114, 44, 44, 3, 0, 1}, {12901, 254, 59, 59, 3, 30, 31}, {12902, 140, 53, 53, 3, 4, 5}, {12903, 249, 46, 46, 3, 0, 1}, {12904, 77, 54, 54, 3, 28, 29}, {12905, 49, 43, 43, 3, 0, 1}, {12915, 94, 249, 249, 3, 0, 1}, {12918, 139, 51, 51, 0, 0, 0}, {12919, 7, 18, 18, 3, 16, 17}, {12920, 20, 5, 5, 0, 0, 0}, {53000, 21, 141, 141, 0, 0, 0}, {53001, 11, 68, 68, 0, 0, 0}, {53002, 253, 207, 207, 0, 0, 0}, {53003, 126, 110, 110, 0, 0, 0}, {53004, 47, 69, 69, 0, 0, 0}, {53010, 71, 245, 245, 0, 0, 0}, {53011, 77, 94, 94, 0, 0, 0}, {53012, 60, 126, 126, 0, 0, 0}, {53013, 14, 126, 126, 0, 0, 0}, {53020, 16, 62, 62, 0, 0, 0}, {53021, 94, 49, 49, 0, 0, 0}, {53022, 167, 141, 141, 0, 0, 0}, {53023, 45, 44, 44, 0, 0, 0}, {53024, 236, 50, 50, 0, 0, 0}, {53030, 81, 59, 59, 0, 0, 0}, {53031, 153, 15, 15, 0, 0, 0}, {53032, 216, 15, 15, 0, 0, 0}, {53033, 75, 18, 18, 0, 0, 0}, {53034, 19, 24, 24, 0, 0, 0}, {53035, 156, 75, 75, 0, 0, 0}, {53036, 83, 38, 38, 0, 0, 0}, {53040, 107, 97, 97, 0, 0, 0}, {53041, 175, 60, 60, 0, 0, 0}, {53050, 244, 24, 24, 0, 0, 0}, {53060, 199, 52, 52, 0, 0, 0}, {53061, 114, 14, 14, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_MILITARY

// ENUM DEFINITIONS


/** @brief Classification of a target across physical and non-physical domains. */
#ifndef HAVE_ENUM_MAVLINK_M_TARGET_CLASS
#define HAVE_ENUM_MAVLINK_M_TARGET_CLASS
typedef enum MAVLINK_M_TARGET_CLASS
{
   MAVLINK_M_TARGET_CLASS_UNKNOWN=0, /* Unknown target class. | */
   MAVLINK_M_TARGET_CLASS_GROUND_VEHICLE_UNKNOWN=1, /* Unknown ground vehicle. | */
   MAVLINK_M_TARGET_CLASS_MAIN_BATTLE_TANK=2, /* Main battle tank. | */
   MAVLINK_M_TARGET_CLASS_INFANTRY_FIGHTING_VEHICLE=3, /* Infantry fighting vehicle. | */
   MAVLINK_M_TARGET_CLASS_ARMORED_PERSONNEL_CARRIER=4, /* Armored personnel carrier. | */
   MAVLINK_M_TARGET_CLASS_LIGHT_TACTICAL_VEHICLE=5, /* Light tactical vehicle. | */
   MAVLINK_M_TARGET_CLASS_LOGISTICS_VEHICLE=6, /* Logistics, cargo, or supply vehicle. | */
   MAVLINK_M_TARGET_CLASS_ARTILLERY_TOWED=7, /* Towed artillery system. | */
   MAVLINK_M_TARGET_CLASS_ARTILLERY_SELF_PROPELLED=8, /* Self-propelled artillery system. | */
   MAVLINK_M_TARGET_CLASS_MLRS=9, /* Multiple launch rocket system. | */
   MAVLINK_M_TARGET_CLASS_AIR_DEFENSE_SYSTEM=10, /* Ground-based air defense system. | */
   MAVLINK_M_TARGET_CLASS_RADAR_VEHICLE=11, /* Vehicle-mounted radar system. | */
   MAVLINK_M_TARGET_CLASS_EW_VEHICLE=12, /* Electronic warfare vehicle. | */
   MAVLINK_M_TARGET_CLASS_COMMAND_POST_VEHICLE=13, /* Command post or command vehicle. | */
   MAVLINK_M_TARGET_CLASS_ENGINEERING_VEHICLE=14, /* Combat engineering or breaching vehicle. | */
   MAVLINK_M_TARGET_CLASS_UNMANNED_GROUND_VEHICLE=15, /* Unmanned ground vehicle. | */
   MAVLINK_M_TARGET_CLASS_PERSONNEL_UNKNOWN=50, /* Unknown personnel target. | */
   MAVLINK_M_TARGET_CLASS_PERSONNEL_SINGLE=51, /* Single person. | */
   MAVLINK_M_TARGET_CLASS_PERSONNEL_GROUP=52, /* Group of people. | */
   MAVLINK_M_TARGET_CLASS_WEAPON_CREW=53, /* Weapon crew. | */
   MAVLINK_M_TARGET_CLASS_AIRCRAFT_UNKNOWN=80, /* Unknown aircraft. | */
   MAVLINK_M_TARGET_CLASS_FIXED_WING_AIRCRAFT=81, /* Fixed-wing aircraft. | */
   MAVLINK_M_TARGET_CLASS_ROTARY_WING_AIRCRAFT=82, /* Rotary-wing aircraft. | */
   MAVLINK_M_TARGET_CLASS_UAS_FIXED_WING=83, /* Fixed-wing unmanned aircraft. | */
   MAVLINK_M_TARGET_CLASS_UAS_MULTIROTOR=84, /* Multirotor unmanned aircraft. | */
   MAVLINK_M_TARGET_CLASS_LOITERING_MUNITION=85, /* Loitering munition. | */
   MAVLINK_M_TARGET_CLASS_MISSILE=86, /* Missile or rocket in flight. | */
   MAVLINK_M_TARGET_CLASS_PROJECTILE=87, /* Projectile or shell in flight. | */
   MAVLINK_M_TARGET_CLASS_VESSEL_UNKNOWN=120, /* Unknown surface vessel. | */
   MAVLINK_M_TARGET_CLASS_WARSHIP=121, /* Military surface vessel. | */
   MAVLINK_M_TARGET_CLASS_PATROL_BOAT=122, /* Patrol boat or small combatant. | */
   MAVLINK_M_TARGET_CLASS_LANDING_CRAFT=123, /* Landing craft. | */
   MAVLINK_M_TARGET_CLASS_LOGISTICS_VESSEL=124, /* Logistics or support vessel. | */
   MAVLINK_M_TARGET_CLASS_CIVILIAN_VESSEL=125, /* Civilian surface vessel. | */
   MAVLINK_M_TARGET_CLASS_UNMANNED_SURFACE_VESSEL=126, /* Unmanned surface vessel. | */
   MAVLINK_M_TARGET_CLASS_SUBSURFACE_UNKNOWN=160, /* Unknown subsurface target. | */
   MAVLINK_M_TARGET_CLASS_SUBMARINE=161, /* Submarine. | */
   MAVLINK_M_TARGET_CLASS_UNMANNED_UNDERWATER_VEHICLE=162, /* Unmanned underwater vehicle. | */
   MAVLINK_M_TARGET_CLASS_MINE=163, /* Naval mine or underwater explosive hazard. | */
   MAVLINK_M_TARGET_CLASS_ROAD=190, /* Road or linear infrastructure. | */
   MAVLINK_M_TARGET_CLASS_BRIDGE=191, /* Bridge. | */
   MAVLINK_M_TARGET_CLASS_RAIL=192, /* Railway or rail infrastructure. | */
   MAVLINK_M_TARGET_CLASS_RUNWAY=193, /* Runway or airfield surface. | */
   MAVLINK_M_TARGET_CLASS_BUILDING=194, /* Building or structure. | */
   MAVLINK_M_TARGET_CLASS_DEPOT=195, /* Depot, storage site, or logistics node. | */
   MAVLINK_M_TARGET_CLASS_POWER_INFRASTRUCTURE=196, /* Power generation or distribution infrastructure. | */
   MAVLINK_M_TARGET_CLASS_COMMUNICATIONS_INFRASTRUCTURE=197, /* Communications infrastructure. | */
   MAVLINK_M_TARGET_CLASS_EMITTER_UNKNOWN=220, /* Unknown electromagnetic emitter. | */
   MAVLINK_M_TARGET_CLASS_RADAR_EMITTER=221, /* Radar emitter. | */
   MAVLINK_M_TARGET_CLASS_JAMMER=222, /* Jammer or interference source. | */
   MAVLINK_M_TARGET_CLASS_COMMUNICATIONS_NODE=223, /* Communications node. | */
   MAVLINK_M_TARGET_CLASS_NETWORK_NODE=224, /* Network or cyber node. | */
   MAVLINK_M_TARGET_CLASS_SPACE_OBJECT_UNKNOWN=240, /* Unknown space object. | */
   MAVLINK_M_TARGET_CLASS_SATELLITE=241, /* Satellite. | */
   MAVLINK_M_TARGET_CLASS_ORBITAL_DEBRIS=242, /* Orbital debris. | */
   MAVLINK_M_TARGET_CLASS_SPACE_LAUNCH_OBJECT=243, /* Launch vehicle or space launch object. | */
   MAVLINK_M_TARGET_CLASS_OTHER=254, /* Other target class not covered by a more specific entry. | */
   MAVLINK_M_TARGET_CLASS_ENUM_END=255, /*  | */
} MAVLINK_M_TARGET_CLASS;
#endif

/** @brief Primary operating domain of the target. */
#ifndef HAVE_ENUM_MAVLINK_M_TARGET_DOMAIN
#define HAVE_ENUM_MAVLINK_M_TARGET_DOMAIN
typedef enum MAVLINK_M_TARGET_DOMAIN
{
   MAVLINK_M_TARGET_DOMAIN_UNKNOWN=0, /* Unknown target domain. | */
   MAVLINK_M_TARGET_DOMAIN_GROUND=1, /* Ground or land surface target. | */
   MAVLINK_M_TARGET_DOMAIN_AIR=2, /* Airborne target. | */
   MAVLINK_M_TARGET_DOMAIN_MARITIME_SURFACE=3, /* Maritime surface target. | */
   MAVLINK_M_TARGET_DOMAIN_SUBSURFACE=4, /* Submerged or underwater target. | */
   MAVLINK_M_TARGET_DOMAIN_SPACE=5, /* Space target or orbital object. | */
   MAVLINK_M_TARGET_DOMAIN_CYBER=6, /* Cyber, network, or digital infrastructure target. | */
   MAVLINK_M_TARGET_DOMAIN_ELECTROMAGNETIC=7, /* Electromagnetic emitter, jammer, radar, or spectrum target. | */
   MAVLINK_M_TARGET_DOMAIN_INFRASTRUCTURE=8, /* Fixed infrastructure target spanning one or more physical domains. | */
   MAVLINK_M_TARGET_DOMAIN_ENUM_END=9, /*  | */
} MAVLINK_M_TARGET_DOMAIN;
#endif

/** @brief 
        Target entity class, representative subset of the MIL-STD-2525D
        (Distribution A) land entity library. Note 2525D has no separate IFV
        entity; an IFV renders as ARMORED_FIGHTING_VEHICLE. Pin the 2525D version
        to the target 6017 baseline for lossless round-trip.
       */
#ifndef HAVE_ENUM_MAVLINK_M_TARGET_ENTITY_2525D
#define HAVE_ENUM_MAVLINK_M_TARGET_ENTITY_2525D
typedef enum MAVLINK_M_TARGET_ENTITY_2525D
{
   MAVLINK_M_ENT_UNKNOWN=0, /* Unknown entity. | */
   MAVLINK_M_ENT_TANK_LIGHT=1, /* Tank (light). | */
   MAVLINK_M_ENT_TANK_MEDIUM=2, /* Tank (medium). | */
   MAVLINK_M_ENT_TANK_HEAVY=3, /* Tank (heavy); MBT maps here. | */
   MAVLINK_M_ENT_ARMORED_FIGHTING_VEHICLE=4, /* Armored fighting vehicle; IFV renders here. | */
   MAVLINK_M_ENT_APC=5, /* Armored personnel carrier. | */
   MAVLINK_M_ENT_HOWITZER=6, /* Howitzer. | */
   MAVLINK_M_ENT_MRL=7, /* Multiple rocket launcher. | */
   MAVLINK_M_ENT_MORTAR=8, /* Mortar. | */
   MAVLINK_M_ENT_ADA_GUN=9, /* Air-defense gun (AAA). | */
   MAVLINK_M_ENT_ADA_MISSILE=10, /* Air-defense missile launcher (SAM; TLAR/TELAR). | */
   MAVLINK_M_ENT_ANTITANK=11, /* Antitank gun or missile launcher. | */
   MAVLINK_M_ENT_SSM_LAUNCHER=12, /* Surface-to-surface missile launcher. | */
   MAVLINK_M_ENT_RADAR=13, /* Radar (sensor entity). | */
   MAVLINK_M_ENT_C2_NODE=14, /* Command-and-control node or command post. | */
   MAVLINK_M_ENT_ENGINEER_VEHICLE=15, /* Engineer vehicle. | */
   MAVLINK_M_ENT_POL=16, /* Petroleum/oil/lubricant site (logistics). | */
   MAVLINK_M_ENT_AMMO=17, /* Ammunition site (logistics). | */
   MAVLINK_M_ENT_BRIDGE=18, /* Bridge. | */
   MAVLINK_M_ENT_ROUTE=19, /* Road or route. | */
   MAVLINK_M_ENT_INFANTRY=20, /* Infantry unit. | */
   MAVLINK_M_ENT_FIELD_ARTILLERY=21, /* Field artillery unit. | */
   MAVLINK_M_ENT_EW_MI=22, /* Electronic warfare or military intelligence unit. | */
   MAVLINK_M_ENT_LAND_MINE_IED=23, /* Land mine or IED. | */
   MAVLINK_M_TARGET_ENTITY_2525D_ENUM_END=24, /*  | */
} MAVLINK_M_TARGET_ENTITY_2525D;
#endif

/** @brief Force affiliation of a target. */
#ifndef HAVE_ENUM_MAVLINK_M_TARGET_FORCE
#define HAVE_ENUM_MAVLINK_M_TARGET_FORCE
typedef enum MAVLINK_M_TARGET_FORCE
{
   MAVLINK_M_TARGET_FORCE_UNKNOWN=0, /* Force affiliation unknown. | */
   MAVLINK_M_TARGET_FORCE_NEUTRAL=10, /* Neutral force. | */
   MAVLINK_M_TARGET_FORCE_FRIENDLY=20, /* Friendly force. | */
   MAVLINK_M_TARGET_FORCE_FOE=30, /* Enemy force. | */
   MAVLINK_M_TARGET_FORCE_EXTRATERRESTRIAL=250, /* Extraterrestrial / non-human origin. | */
   MAVLINK_M_TARGET_FORCE_ENUM_END=251, /*  | */
} MAVLINK_M_TARGET_FORCE;
#endif

/** @brief Transport protocol used to retrieve an externally hosted target package. */
#ifndef HAVE_ENUM_MAVLINK_M_TARGET_PACKAGE_TRANSPORT
#define HAVE_ENUM_MAVLINK_M_TARGET_PACKAGE_TRANSPORT
typedef enum MAVLINK_M_TARGET_PACKAGE_TRANSPORT
{
   MAVLINK_M_TARGET_PACKAGE_TRANSPORT_UNKNOWN=0, /* Unknown or no target package transport. | */
   MAVLINK_M_TARGET_PACKAGE_TRANSPORT_HTTP=1, /* HTTP target package transport. | */
   MAVLINK_M_TARGET_PACKAGE_TRANSPORT_HTTPS=2, /* HTTPS target package transport. | */
   MAVLINK_M_TARGET_PACKAGE_TRANSPORT_ENUM_END=3, /*  | */
} MAVLINK_M_TARGET_PACKAGE_TRANSPORT;
#endif

/** @brief Target warning and status flags. */
#ifndef HAVE_ENUM_MAVLINK_M_TARGET_FLAGS
#define HAVE_ENUM_MAVLINK_M_TARGET_FLAGS
typedef enum MAVLINK_M_TARGET_FLAGS
{
   MAVLINK_M_TARGET_FLAG_AUTHORIZATION_REQUIRED=1, /* Authorization is required before action can be taken. | */
   MAVLINK_M_TARGET_FLAG_GNSS_DEGRADED=2, /* GNSS quality was degraded when the target was generated. | */
   MAVLINK_M_TARGET_FLAG_LINK_DEGRADED=4, /* Link quality was degraded when the target was generated. | */
   MAVLINK_M_TARGET_FLAG_LOW_CONFIDENCE=8, /* Target confidence is low. | */
   MAVLINK_M_TARGET_FLAG_LOW_IMAGE_QUALITY=16, /* Associated imagery quality is low. | */
   MAVLINK_M_TARGET_FLAG_MOVING=32, /* Target is assessed to be moving. | */
   MAVLINK_M_TARGET_FLAG_STALE=64, /* Target data may be stale. | */
   MAVLINK_M_TARGET_FLAG_INTEGRITY_PRESENT=128, /* Associated target package contains integrity material. | */
   MAVLINK_M_TARGET_FLAG_MANUAL_DESIGNATION=256, /* Target was designated manually by an operator. | */
   MAVLINK_M_TARGET_FLAG_AUTONOMOUS_DETECTION=512, /* Target was detected or designated autonomously. | */
   MAVLINK_M_TARGET_FLAGS_ENUM_END=513, /*  | */
} MAVLINK_M_TARGET_FLAGS;
#endif

/** @brief Primary sensor source used for target identification. */
#ifndef HAVE_ENUM_MAVLINK_M_TARGET_SENSOR_TYPE
#define HAVE_ENUM_MAVLINK_M_TARGET_SENSOR_TYPE
typedef enum MAVLINK_M_TARGET_SENSOR_TYPE
{
   MAVLINK_M_TARGET_SENSOR_TYPE_UNKNOWN=0, /* Unknown or unspecified target identification sensor. | */
   MAVLINK_M_TARGET_SENSOR_TYPE_EO=1, /* Electro-optical sensor. | */
   MAVLINK_M_TARGET_SENSOR_TYPE_IR=2, /* Infrared sensor. | */
   MAVLINK_M_TARGET_SENSOR_TYPE_ACOUSTIC=3, /* Acoustic sensor. | */
   MAVLINK_M_TARGET_SENSOR_TYPE_RADAR=4, /* Radar sensor. | */
   MAVLINK_M_TARGET_SENSOR_TYPE_RF=5, /* RF sensor. | */
   MAVLINK_M_TARGET_SENSOR_TYPE_FUSED=6, /* Multiple sensor sources were fused for target identification. | */
   MAVLINK_M_TARGET_SENSOR_TYPE_ENUM_END=7, /*  | */
} MAVLINK_M_TARGET_SENSOR_TYPE;
#endif

/** @brief 
        Type of terminal attack control, a defined construct in JP 3-09.3 (Close
        Air Support). The three types are distinguished by what the terminal
        controller can visually acquire before granting clearance.
       */
#ifndef HAVE_ENUM_MAVLINK_M_TAC_TYPE
#define HAVE_ENUM_MAVLINK_M_TAC_TYPE
typedef enum MAVLINK_M_TAC_TYPE
{
   MAVLINK_M_TAC_TYPE_NONE=0, /* Not under terminal attack control. | */
   MAVLINK_M_TAC_TYPE_1=1, /* Type 1: controller must visually acquire both the attacking aircraft and the target before clearance. | */
   MAVLINK_M_TAC_TYPE_2=2, /* Type 2: controller clears an individual attack without visually acquiring the aircraft and/or target at release. | */
   MAVLINK_M_TAC_TYPE_3=3, /* Type 3: controller grants clearance for multiple attacks within a defined engagement/period under stated restrictions. | */
   MAVLINK_M_TAC_TYPE_ENUM_END=4, /*  | */
} MAVLINK_M_TAC_TYPE;
#endif

/** @brief CAS clearance / abort handshake verbs (JP 3-09.3). Human-authority instruments. */
#ifndef HAVE_ENUM_MAVLINK_M_CAS_CLEARANCE
#define HAVE_ENUM_MAVLINK_M_CAS_CLEARANCE
typedef enum MAVLINK_M_CAS_CLEARANCE
{
   MAVLINK_M_CAS_NONE=0, /* No clearance state. | */
   MAVLINK_M_CAS_CONTINUE=1, /* Continue. | */
   MAVLINK_M_CAS_CLEARED_HOT=2, /* Cleared hot. | */
   MAVLINK_M_CAS_ABORT=3, /* Abort. | */
   MAVLINK_M_CAS_CEASE_FIRE=4, /* Cease fire. | */
   MAVLINK_M_CAS_CLEARANCE_ENUM_END=5, /*  | */
} MAVLINK_M_CAS_CLEARANCE;
#endif

/** @brief Attacking-aircraft status calls (JFIRE 9-line flow). */
#ifndef HAVE_ENUM_MAVLINK_M_AIRCRAFT_CALL
#define HAVE_ENUM_MAVLINK_M_AIRCRAFT_CALL
typedef enum MAVLINK_M_AIRCRAFT_CALL
{
   MAVLINK_M_ACFT_CALL_NONE=0, /* No call. | */
   MAVLINK_M_ACFT_CALL_IN=1, /* IN (commencing attack run). | */
   MAVLINK_M_ACFT_CALL_OFF=2, /* OFF (off target). | */
   MAVLINK_M_ACFT_CALL_VISUAL=3, /* VISUAL (sees friendlies). | */
   MAVLINK_M_ACFT_CALL_TALLY=4, /* TALLY (sees target). | */
   MAVLINK_M_AIRCRAFT_CALL_ENUM_END=5, /*  | */
} MAVLINK_M_AIRCRAFT_CALL;
#endif

/** @brief Type of target mark / terminal guidance (9-line line 7). */
#ifndef HAVE_ENUM_MAVLINK_M_MARK_TYPE
#define HAVE_ENUM_MAVLINK_M_MARK_TYPE
typedef enum MAVLINK_M_MARK_TYPE
{
   MAVLINK_M_MARK_NONE=0, /* No mark. | */
   MAVLINK_M_MARK_WP=1, /* White phosphorus mark. | */
   MAVLINK_M_MARK_ILLUM=2, /* Illumination mark. | */
   MAVLINK_M_MARK_LASER=3, /* Laser designation (code carried as slot, not value). | */
   MAVLINK_M_MARK_IR=4, /* IR pointer. | */
   MAVLINK_M_MARK_TYPE_ENUM_END=5, /*  | */
} MAVLINK_M_MARK_TYPE;
#endif

/** @brief Bomb-on-coordinate vs bomb-on-target delivery intent. */
#ifndef HAVE_ENUM_MAVLINK_M_ORDNANCE_DELIVERY
#define HAVE_ENUM_MAVLINK_M_ORDNANCE_DELIVERY
typedef enum MAVLINK_M_ORDNANCE_DELIVERY
{
   MAVLINK_M_DELIVERY_UNSPECIFIED=0, /* Unspecified. | */
   MAVLINK_M_DELIVERY_BOC=1, /* Bomb on coordinate. | */
   MAVLINK_M_DELIVERY_BOT=2, /* Bomb on target. | */
   MAVLINK_M_ORDNANCE_DELIVERY_ENUM_END=3, /*  | */
} MAVLINK_M_ORDNANCE_DELIVERY;
#endif

/** @brief ESAD arming state. */
#ifndef HAVE_ENUM_MAVLINK_M_ESAD_ARMING_STATUS
#define HAVE_ENUM_MAVLINK_M_ESAD_ARMING_STATUS
typedef enum MAVLINK_M_ESAD_ARMING_STATUS
{
   MAVLINK_M_ESAD_ARMING_DISARMED=0, /* System is disarmed. | */
   MAVLINK_M_ESAD_ARMING_ARMED=1, /* System is armed. | */
   MAVLINK_M_ESAD_ARMING_FAULT=2, /* Arming fault detected. | */
   MAVLINK_M_ESAD_ARMING_STATUS_ENUM_END=3, /*  | */
} MAVLINK_M_ESAD_ARMING_STATUS;
#endif

/** @brief ESAD munition readiness state. */
#ifndef HAVE_ENUM_MAVLINK_M_ESAD_MUNITION_STATUS
#define HAVE_ENUM_MAVLINK_M_ESAD_MUNITION_STATUS
typedef enum MAVLINK_M_ESAD_MUNITION_STATUS
{
   MAVLINK_M_ESAD_MUNITION_NOT_PRESENT=0, /* No munition present. | */
   MAVLINK_M_ESAD_MUNITION_PRESENT=1, /* Munition present and not ready. | */
   MAVLINK_M_ESAD_MUNITION_READY=2, /* Munition present and ready. | */
   MAVLINK_M_ESAD_MUNITION_FAULT=3, /* Munition fault detected. | */
   MAVLINK_M_ESAD_MUNITION_STATUS_ENUM_END=4, /*  | */
} MAVLINK_M_ESAD_MUNITION_STATUS;
#endif

/** @brief ESAD ignition circuit state. */
#ifndef HAVE_ENUM_MAVLINK_M_ESAD_IGNITION_STATUS
#define HAVE_ENUM_MAVLINK_M_ESAD_IGNITION_STATUS
typedef enum MAVLINK_M_ESAD_IGNITION_STATUS
{
   MAVLINK_M_ESAD_IGNITION_OPEN=0, /* Ignition circuit open. | */
   MAVLINK_M_ESAD_IGNITION_CLOSED=1, /* Ignition circuit closed. | */
   MAVLINK_M_ESAD_IGNITION_FIRED=2, /* Ignition has fired. | */
   MAVLINK_M_ESAD_IGNITION_FAULT=3, /* Ignition circuit fault. | */
   MAVLINK_M_ESAD_IGNITION_STATUS_ENUM_END=4, /*  | */
} MAVLINK_M_ESAD_IGNITION_STATUS;
#endif

/** @brief 
        ESAD fault flag bitmask. Scope is ESAD-internal faults only.
        Deceleration/landing sensor health is reported separately via
        STORE_SENSOR_STATUS and is not represented here.
       */
#ifndef HAVE_ENUM_MAVLINK_M_ESAD_FAULT_FLAGS
#define HAVE_ENUM_MAVLINK_M_ESAD_FAULT_FLAGS
typedef enum MAVLINK_M_ESAD_FAULT_FLAGS
{
   MAVLINK_M_ESAD_FAULT_WIRING=1, /* Wiring fault detected. | */
   MAVLINK_M_ESAD_FAULT_POWER_GLITCH=2, /* Power supply glitch detected. | */
   MAVLINK_M_ESAD_FAULT_SIGNAL_INTEGRITY=4, /* Signal integrity fault detected. | */
   MAVLINK_M_ESAD_FAULT_FLAGS_ENUM_END=5, /*  | */
} MAVLINK_M_ESAD_FAULT_FLAGS;
#endif

/** @brief ESAD arming command. */
#ifndef HAVE_ENUM_MAVLINK_M_ESAD_ARMING_REQUEST
#define HAVE_ENUM_MAVLINK_M_ESAD_ARMING_REQUEST
typedef enum MAVLINK_M_ESAD_ARMING_REQUEST
{
   MAVLINK_M_ESAD_REQUEST_DISARM=0, /* Request disarm. | */
   MAVLINK_M_ESAD_REQUEST_ARM=1, /* Request arm. | */
   MAVLINK_M_ESAD_ARMING_REQUEST_ENUM_END=2, /*  | */
} MAVLINK_M_ESAD_ARMING_REQUEST;
#endif

/** @brief State of the physical safety pull-pin on an ESAD. Read-only status. */
#ifndef HAVE_ENUM_MAVLINK_M_ESAD_PIN_STATE
#define HAVE_ENUM_MAVLINK_M_ESAD_PIN_STATE
typedef enum MAVLINK_M_ESAD_PIN_STATE
{
   MAVLINK_M_ESAD_PIN_UNKNOWN=0, /* Pin state not determined. | */
   MAVLINK_M_ESAD_PIN_PRESENT=1, /* Pin present (device mechanically safed). | */
   MAVLINK_M_ESAD_PIN_REMOVED=2, /* Pin removed (mechanical safety released). | */
   MAVLINK_M_ESAD_PIN_STATE_ENUM_END=3, /*  | */
} MAVLINK_M_ESAD_PIN_STATE;
#endif

/** @brief 
        Selected arming-delay setting: how long after the in-flight-event signal
        the ESAD will PERMIT arming. Reports the physical switch detent position.
        This is a safety timer setting, not a fuze timing value.
       */
#ifndef HAVE_ENUM_MAVLINK_M_ESAD_ARM_DELAY_SETTING
#define HAVE_ENUM_MAVLINK_M_ESAD_ARM_DELAY_SETTING
typedef enum MAVLINK_M_ESAD_ARM_DELAY_SETTING
{
   MAVLINK_M_ESAD_ARM_DELAY_UNKNOWN=0, /* Setting not determined. | */
   MAVLINK_M_ESAD_ARM_DELAY_90S=1, /* 90 second arming delay. | */
   MAVLINK_M_ESAD_ARM_DELAY_60S=2, /* 60 second arming delay. | */
   MAVLINK_M_ESAD_ARM_DELAY_30S=3, /* 30 second arming delay. | */
   MAVLINK_M_ESAD_ARM_DELAY_SETTING_ENUM_END=4, /*  | */
} MAVLINK_M_ESAD_ARM_DELAY_SETTING;
#endif

/** @brief 
        Selected trigger-distance MODE for a proximity (TOF or equivalent) safe/arm
        device: the coarse standoff detent at which the device is permitted to
        function. This is a SAFE/ARM standoff SELECTION among the device's defined
        modes, NOT a settable continuous distance and NOT a fuze height-of-burst
        configuration. It must remain a coarse enum; it must never be widened to a
        free continuous distance value on the wire, which would turn the bus into a
        fuze-configuration channel. On devices with a physical switch this reports
        the switch position; on devices that accept ESAD_CONFIG it reports the mode
        currently in effect.
       */
#ifndef HAVE_ENUM_MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE
#define HAVE_ENUM_MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE
typedef enum MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE
{
   MAVLINK_M_ESAD_TRIG_DIST_UNKNOWN=0, /* Mode not determined. | */
   MAVLINK_M_ESAD_TRIG_DIST_2M=1, /* 2 metre standoff mode. | */
   MAVLINK_M_ESAD_TRIG_DIST_4M=2, /* 4 metre standoff mode. | */
   MAVLINK_M_ESAD_TRIG_DIST_MANUAL=3, /* Manual mode (standoff governed by the platform/operator, not an auto standoff). | */
   MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE_ENUM_END=4, /*  | */
} MAVLINK_M_ESAD_TRIGGER_DISTANCE_MODE;
#endif

/** @brief Remote weapon system arming state. */
#ifndef HAVE_ENUM_MAVLINK_M_RWS_ARMING_STATE
#define HAVE_ENUM_MAVLINK_M_RWS_ARMING_STATE
typedef enum MAVLINK_M_RWS_ARMING_STATE
{
   MAVLINK_M_RWS_ARMING_SAFE=0, /* Weapon system safe. | */
   MAVLINK_M_RWS_ARMING_ARMED=1, /* Weapon system armed. | */
   MAVLINK_M_RWS_ARMING_FAULT=2, /* Weapon system fault. | */
   MAVLINK_M_RWS_ARMING_STATE_ENUM_END=3, /*  | */
} MAVLINK_M_RWS_ARMING_STATE;
#endif

/** @brief Media type used for target matching. */
#ifndef HAVE_ENUM_MAVLINK_M_MATCH_MEDIA_TYPE
#define HAVE_ENUM_MAVLINK_M_MATCH_MEDIA_TYPE
typedef enum MAVLINK_M_MATCH_MEDIA_TYPE
{
   MAVLINK_M_MATCH_MEDIA_NONE=0, /* No matching media. | */
   MAVLINK_M_MATCH_MEDIA_IMAGE=1, /* Still image. | */
   MAVLINK_M_MATCH_MEDIA_VIDEO_CLIP=2, /* Video clip. | */
   MAVLINK_M_MATCH_MEDIA_IR_IMAGE=3, /* Infrared image. | */
   MAVLINK_M_MATCH_MEDIA_SAR_IMAGE=4, /* SAR image. | */
   MAVLINK_M_MATCH_MEDIA_TYPE_ENUM_END=5, /*  | */
} MAVLINK_M_MATCH_MEDIA_TYPE;
#endif

/** @brief Deviation spotting relative to the observer-target (OT) line (ATP 3-09.30 / VMF K02.22). */
#ifndef HAVE_ENUM_MAVLINK_M_SPLASH_DEVIATION
#define HAVE_ENUM_MAVLINK_M_SPLASH_DEVIATION
typedef enum MAVLINK_M_SPLASH_DEVIATION
{
   MAVLINK_M_SPLASH_DEVIATION_UNKNOWN=0, /* Deviation not determined. | */
   MAVLINK_M_SPLASH_DEVIATION_LINE=1, /* Impact on the OT line; zero lateral deviation. | */
   MAVLINK_M_SPLASH_DEVIATION_LEFT=2, /* Impact left of the OT line (correction: shift right). | */
   MAVLINK_M_SPLASH_DEVIATION_RIGHT=3, /* Impact right of the OT line (correction: shift left). | */
   MAVLINK_M_SPLASH_DEVIATION_ENUM_END=4, /*  | */
} MAVLINK_M_SPLASH_DEVIATION;
#endif

/** @brief Range spotting along the observer-target line (ATP 3-09.30 / STANAG 1034 / VMF K02.22). */
#ifndef HAVE_ENUM_MAVLINK_M_SPLASH_RANGE
#define HAVE_ENUM_MAVLINK_M_SPLASH_RANGE
typedef enum MAVLINK_M_SPLASH_RANGE
{
   MAVLINK_M_SPLASH_RANGE_UNKNOWN=0, /* Range relationship not determined. | */
   MAVLINK_M_SPLASH_RANGE_OVER=1, /* Impact beyond the target (range too long; decrease range). | */
   MAVLINK_M_SPLASH_RANGE_SHORT=2, /* Impact between observer and target (range too short; increase range). | */
   MAVLINK_M_SPLASH_RANGE_TARGET=3, /* Direct hit at target range (precision/registration); enter fire for effect. | */
   MAVLINK_M_SPLASH_RANGE_RANGE_CORRECT=4, /* Impact at correct range along the OT line. | */
   MAVLINK_M_SPLASH_RANGE_STRADDLE=5, /* Multi-gun salvo: rounds fell both over and short; MPI correct, enter FFE. | */
   MAVLINK_M_SPLASH_RANGE_DOUBTFUL=6, /* Impact seen but cannot be called over/short. | */
   MAVLINK_M_SPLASH_RANGE_LOST=7, /* Round neither seen nor heard. | */
   MAVLINK_M_SPLASH_RANGE_UNOBSERVED=8, /* Heard/seen but cannot determine over/short (distinct from LOST). | */
   MAVLINK_M_SPLASH_RANGE_NEGLECT=9, /* Naval (NSFS): last salvo fired on incorrect data; disregard spotting. | */
   MAVLINK_M_SPLASH_RANGE_ENUM_END=10, /*  | */
} MAVLINK_M_SPLASH_RANGE;
#endif

/** @brief 
        Height-of-burst spotting (ATP 3-09.30). An OBSERVATION of where the round
        detonated vertically, NOT a munition property or a fuze setting. Drives
        the doctrinal vertical correction (e.g. graze on an intended airburst =>
        "Up 40").
       */
#ifndef HAVE_ENUM_MAVLINK_M_SPLASH_HOB
#define HAVE_ENUM_MAVLINK_M_SPLASH_HOB
typedef enum MAVLINK_M_SPLASH_HOB
{
   MAVLINK_M_SPLASH_HOB_NA=0, /* Not applicable / not observed. | */
   MAVLINK_M_SPLASH_HOB_AIR=1, /* Detonated in the air as intended. | */
   MAVLINK_M_SPLASH_HOB_GRAZE=2, /* Detonated on contact with the ground (ground-burst). | */
   MAVLINK_M_SPLASH_HOB_MIXED=3, /* Salvo: air and graze bursts, no clear majority. | */
   MAVLINK_M_SPLASH_HOB_MIXED_AIR=4, /* Salvo: mixed, majority air. | */
   MAVLINK_M_SPLASH_HOB_MIXED_GRAZE=5, /* Salvo: mixed, majority graze. | */
   MAVLINK_M_SPLASH_HOB_RIPPED_CHUTE=6, /* Illumination parachute ripped/separated on deployment; repeat illum. | */
   MAVLINK_M_SPLASH_HOB_DARK_STAR=7, /* Illumination round failed to deploy or properly ignite (ATP 3-09.32). | */
   MAVLINK_M_SPLASH_HOB_ENUM_END=8, /*  | */
} MAVLINK_M_SPLASH_HOB;
#endif

/** @brief Supplementary: what the round struck / what the splash was observed in/on. Sensor context, not part of the doctrinal spotting set. */
#ifndef HAVE_ENUM_MAVLINK_M_SPLASH_SURFACE
#define HAVE_ENUM_MAVLINK_M_SPLASH_SURFACE
typedef enum MAVLINK_M_SPLASH_SURFACE
{
   MAVLINK_M_SPLASH_SURFACE_UNKNOWN=0, /* Surface not determined. | */
   MAVLINK_M_SPLASH_SURFACE_GROUND=1, /* Bare land / terrain. | */
   MAVLINK_M_SPLASH_SURFACE_WATER=2, /* Water surface. A near-miss beside a vessel reports this. | */
   MAVLINK_M_SPLASH_SURFACE_STRUCTURE=3, /* Building or fixed structure. | */
   MAVLINK_M_SPLASH_SURFACE_VEHICLE=4, /* Land vehicle (tank, IFV, truck). Mobile; may have moved by next correction. | */
   MAVLINK_M_SPLASH_SURFACE_SURFACE_VESSEL=5, /* Ship or boat. Distinct from WATER so hit-vs-near-miss on a vessel is unambiguous. | */
   MAVLINK_M_SPLASH_SURFACE_FOLIAGE=6, /* Tree canopy / vegetation; may cause early function or masking. | */
   MAVLINK_M_SPLASH_SURFACE_ENUM_END=7, /*  | */
} MAVLINK_M_SPLASH_SURFACE;
#endif

/** @brief Supplementary: why the observer could not fully resolve the impact. Relates to RANGE_DOUBTFUL / RANGE_LOST. */
#ifndef HAVE_ENUM_MAVLINK_M_SPLASH_OBSCURATION
#define HAVE_ENUM_MAVLINK_M_SPLASH_OBSCURATION
typedef enum MAVLINK_M_SPLASH_OBSCURATION
{
   MAVLINK_M_SPLASH_OBSCURATION_NONE=0, /* Clear observation, no obscuration. | */
   MAVLINK_M_SPLASH_OBSCURATION_TERRAIN=1, /* Masked by terrain / defilade. | */
   MAVLINK_M_SPLASH_OBSCURATION_SMOKE=2, /* Masked by smoke or dust (own or battlefield). | */
   MAVLINK_M_SPLASH_OBSCURATION_WEATHER=3, /* Masked by cloud, fog, or precipitation. | */
   MAVLINK_M_SPLASH_OBSCURATION_VEGETATION=4, /* Masked by foliage / canopy. | */
   MAVLINK_M_SPLASH_OBSCURATION_SENSOR_LIMIT=5, /* Sensor resolution / range / angle limit, not an external mask. | */
   MAVLINK_M_SPLASH_OBSCURATION_ENUM_END=6, /*  | */
} MAVLINK_M_SPLASH_OBSCURATION;
#endif

/** @brief 
        Procedural fire-mission control commands exchanged in the observer/FDC
        digital handshake (ATP 3-09.30; map to VMF K02.16 End of Mission and
        K02.22 Subsequent Adjust flows). These are control verbs, not spotting.
       */
#ifndef HAVE_ENUM_MAVLINK_M_FIRE_MISSION_COMMAND
#define HAVE_ENUM_MAVLINK_M_FIRE_MISSION_COMMAND
typedef enum MAVLINK_M_FIRE_MISSION_COMMAND
{
   MAVLINK_M_FMC_NONE=0, /* No command. | */
   MAVLINK_M_FMC_FIRE_FOR_EFFECT=1, /* Enter fire for effect. | */
   MAVLINK_M_FMC_END_OF_MISSION=2, /* End of mission (EOM). | */
   MAVLINK_M_FMC_RECORD_AS_TARGET=3, /* Record the current data as a target. | */
   MAVLINK_M_FMC_REPEAT=4, /* Repeat the last fire. | */
   MAVLINK_M_FMC_CHECK_FIRING=5, /* Check firing (temporary halt). | */
   MAVLINK_M_FMC_CANCEL_CHECK_FIRING=6, /* Cancel check firing / resume. | */
   MAVLINK_M_FMC_CEASE_LOADING=7, /* Cease loading. | */
   MAVLINK_M_FMC_CANCEL_AT_MY_COMMAND=8, /* Cancel At My Command. | */
   MAVLINK_M_FMC_CANCEL_HIGH_ANGLE=9, /* Cancel high angle. | */
   MAVLINK_M_FMC_CHECK_SOLUTION=10, /* Check fire-control solution (NSFS). | */
   MAVLINK_M_FMC_FRESH_TARGET=11, /* Fresh target: interrupt current mission for higher-priority target (NSFS). | */
   MAVLINK_M_FMC_NEW_TARGET=12, /* New target: engage additional non-priority target, continue original (NSFS). | */
   MAVLINK_M_FIRE_MISSION_COMMAND_ENUM_END=13, /*  | */
} MAVLINK_M_FIRE_MISSION_COMMAND;
#endif

/** @brief 
        Projectile / shell class for the call-for-fire method of engagement
        (ATP 3-09.30 element 5). The projectile is a distinct component from the
        fuze; the two are specified separately. This is requester intent, not
        weaponeering configuration.
       */
#ifndef HAVE_ENUM_MAVLINK_M_MUNITION_CLASS
#define HAVE_ENUM_MAVLINK_M_MUNITION_CLASS
typedef enum MAVLINK_M_MUNITION_CLASS
{
   MAVLINK_M_MUNITION_CLASS_UNKNOWN=0, /* Unspecified. | */
   MAVLINK_M_MUNITION_CLASS_HE=1, /* High explosive. | */
   MAVLINK_M_MUNITION_CLASS_WP=2, /* White phosphorus (incendiary / marking / obscuration). | */
   MAVLINK_M_MUNITION_CLASS_ILLUM=3, /* Illumination. | */
   MAVLINK_M_MUNITION_CLASS_SMOKE=4, /* Smoke (e.g. HC base-ejection). | */
   MAVLINK_M_MUNITION_CLASS_DPICM=5, /* Dual-purpose improved conventional munition. | */
   MAVLINK_M_MUNITION_CLASS_PGM=6, /* Precision guided munition (e.g. Excalibur, APMI). | */
   MAVLINK_M_MUNITION_CLASS_ENUM_END=7, /*  | */
} MAVLINK_M_MUNITION_CLASS;
#endif

/** @brief 
        Requested fuze MODE for the call-for-fire method of engagement
        (ATP 3-09.30). Product-independent: selects the standard fuze behavior
        category (the observer's intent), NOT internal fuze timing or
        height-of-burst settings, which remain device-internal and out of scope.
        Whether the fielded fuze is multi-option (e.g. M782 MOFA) is carried
        separately as the fuze_mofa_capable flag on FIRES, since MOFA is a
        capability, not a mode.
       */
#ifndef HAVE_ENUM_MAVLINK_M_FUZE_MODE
#define HAVE_ENUM_MAVLINK_M_FUZE_MODE
typedef enum MAVLINK_M_FUZE_MODE
{
   MAVLINK_M_FUZE_MODE_UNKNOWN=0, /* Unspecified. | */
   MAVLINK_M_FUZE_MODE_PD=1, /* Point-detonating; detonate on contact. | */
   MAVLINK_M_FUZE_MODE_PD_SQ=2, /* Point-detonating superquick. | */
   MAVLINK_M_FUZE_MODE_DELAY=3, /* Delay; detonate after impact for penetration. | */
   MAVLINK_M_FUZE_MODE_TIME=4, /* Mechanical/electronic time; burst at a set point in trajectory. | */
   MAVLINK_M_FUZE_MODE_ET=5, /* Electronic time. | */
   MAVLINK_M_FUZE_MODE_MTSQ=6, /* Mechanical time superquick. | */
   MAVLINK_M_FUZE_MODE_VT=7, /* Variable time / proximity; burst at a preset height above ground. | */
   MAVLINK_M_FUZE_MODE_CVT=8, /* Controlled variable time. | */
   MAVLINK_M_FUZE_MODE_ENUM_END=9, /*  | */
} MAVLINK_M_FUZE_MODE;
#endif

/** @brief Descriptive airburst height-of-burst intent for proximity/time modes. A selector, NOT a millisecond or metric value. */
#ifndef HAVE_ENUM_MAVLINK_M_HOB_INTENT
#define HAVE_ENUM_MAVLINK_M_HOB_INTENT
typedef enum MAVLINK_M_HOB_INTENT
{
   MAVLINK_M_HOB_INTENT_NA=0, /* Not applicable (non-airburst mode). | */
   MAVLINK_M_HOB_INTENT_LOW=1, /* Low airburst intent. | */
   MAVLINK_M_HOB_INTENT_HIGH=2, /* High airburst intent. | */
   MAVLINK_M_HOB_INTENT_ENUM_END=3, /*  | */
} MAVLINK_M_HOB_INTENT;
#endif

/** @brief 
        Intent of a non-kinetic point-of-interest cue. These values explicitly
        denote observation/investigation tasking and carry NO engagement
        semantics. A consumer must not interpret a TARGET_CUE as a fires order.
       */
#ifndef HAVE_ENUM_MAVLINK_M_CUE_TYPE
#define HAVE_ENUM_MAVLINK_M_CUE_TYPE
typedef enum MAVLINK_M_CUE_TYPE
{
   MAVLINK_M_CUE_TYPE_UNSPECIFIED=0, /* Not specified (default for an unset field). A consumer must not act on an unspecified cue type. | */
   MAVLINK_M_CUE_TYPE_INVESTIGATE=1, /* Proceed to the point and gather further information. Non-kinetic. | */
   MAVLINK_M_CUE_TYPE_OBSERVE=2, /* Maintain standoff observation of the point. Non-kinetic. | */
   MAVLINK_M_CUE_TYPE_MARK=3, /* Record/mark the point as a reference of interest. No tasking implied. | */
   MAVLINK_M_CUE_TYPE_ENUM_END=4, /*  | */
} MAVLINK_M_CUE_TYPE;
#endif

/** @brief 
        Result of receiving/processing a MAVLink-M message, reported via
        MAVLINK_M_ACK. Distinguishes "received" from "accepted" so a sender
        can tell delivery from agreement.
       */
#ifndef HAVE_ENUM_MAVLINK_M_ACK_RESULT
#define HAVE_ENUM_MAVLINK_M_ACK_RESULT
typedef enum MAVLINK_M_ACK_RESULT
{
   MAVLINK_M_ACK_RECEIVED=0, /* Message was received and parsed. No acceptance implied. | */
   MAVLINK_M_ACK_ACCEPTED=1, /* Message was received and accepted/actioned by the recipient. | */
   MAVLINK_M_ACK_REJECTED=2, /* Message was received but rejected (e.g. operator declined the cue). | */
   MAVLINK_M_ACK_UNSUPPORTED=3, /* Message type or requested action is not supported by the recipient. | */
   MAVLINK_M_ACK_FAILED=4, /* Message was received but processing failed (e.g. malformed or stale). | */
   MAVLINK_M_ACK_EXPIRED=5, /* Message was received after its validity window had passed. | */
   MAVLINK_M_ACK_RESULT_ENUM_END=6, /*  | */
} MAVLINK_M_ACK_RESULT;
#endif

/** @brief Type of sensor feeding a store's deceleration/landing-trigger system. */
#ifndef HAVE_ENUM_MAVLINK_M_STORE_SENSOR_TYPE
#define HAVE_ENUM_MAVLINK_M_STORE_SENSOR_TYPE
typedef enum MAVLINK_M_STORE_SENSOR_TYPE
{
   MAVLINK_M_STORE_SENSOR_UNKNOWN=0, /* Unknown / unspecified sensor. | */
   MAVLINK_M_STORE_SENSOR_BARO=1, /* Barometric altimeter. | */
   MAVLINK_M_STORE_SENSOR_MMWAVE_RADAR=2, /* Millimeter-wave radar altimeter/ranger. | */
   MAVLINK_M_STORE_SENSOR_AIRSPEED=3, /* Airspeed sensor. | */
   MAVLINK_M_STORE_SENSOR_LIDAR=4, /* LIDAR rangefinder. | */
   MAVLINK_M_STORE_SENSOR_TOF=5, /* Time-of-flight rangefinder (generic, non-LIDAR). | */
   MAVLINK_M_STORE_SENSOR_IMU=6, /* Inertial measurement unit (accel/gyro). | */
   MAVLINK_M_STORE_SENSOR_GNSS=7, /* GNSS receiver. | */
   MAVLINK_M_STORE_SENSOR_TYPE_ENUM_END=8, /*  | */
} MAVLINK_M_STORE_SENSOR_TYPE;
#endif

/** @brief Health state of an individual store sensor. */
#ifndef HAVE_ENUM_MAVLINK_M_SENSOR_HEALTH
#define HAVE_ENUM_MAVLINK_M_SENSOR_HEALTH
typedef enum MAVLINK_M_SENSOR_HEALTH
{
   MAVLINK_M_SENSOR_HEALTH_NOT_PRESENT=0, /* Sensor not installed / not detected. | */
   MAVLINK_M_SENSOR_HEALTH_OK=1, /* Sensor present and healthy. | */
   MAVLINK_M_SENSOR_HEALTH_DEGRADED=2, /* Sensor functional but degraded (e.g. noisy, low confidence). | */
   MAVLINK_M_SENSOR_HEALTH_FAULT=3, /* Sensor faulted / no valid data. | */
   MAVLINK_M_SENSOR_HEALTH_CALIBRATING=4, /* Sensor initializing or calibrating; not yet usable. | */
   MAVLINK_M_SENSOR_HEALTH_OUT_OF_RANGE=5, /* Sensor reading outside valid operating range. | */
   MAVLINK_M_SENSOR_HEALTH_ENUM_END=6, /*  | */
} MAVLINK_M_SENSOR_HEALTH;
#endif

/** @brief Roll-up release-readiness state of a store. */
#ifndef HAVE_ENUM_MAVLINK_M_STORE_READINESS
#define HAVE_ENUM_MAVLINK_M_STORE_READINESS
typedef enum MAVLINK_M_STORE_READINESS
{
   MAVLINK_M_STORE_READINESS_UNKNOWN=0, /* Readiness not yet determined. | */
   MAVLINK_M_STORE_READINESS_NOT_READY=1, /* Not ready to release (one or more blocking conditions). | */
   MAVLINK_M_STORE_READINESS_READY=2, /* All checks passed; cleared for release. | */
   MAVLINK_M_STORE_READINESS_FAULT=3, /* Store in fault state; must not be released. | */
   MAVLINK_M_STORE_READINESS_RELEASED=4, /* Store has been released from the carrier. | */
   MAVLINK_M_STORE_READINESS_ENUM_END=5, /*  | */
} MAVLINK_M_STORE_READINESS;
#endif

/** @brief Relationship of a track to its parent, used when tracks split, merge, or are re-identified. */
#ifndef HAVE_ENUM_MAVLINK_M_TRACK_REL
#define HAVE_ENUM_MAVLINK_M_TRACK_REL
typedef enum MAVLINK_M_TRACK_REL
{
   MAVLINK_M_TRACK_REL_NONE=0, /* No parent; this is an originating track. | */
   MAVLINK_M_TRACK_REL_CHILD=1, /* Derived from a single parent track (e.g. a split). | */
   MAVLINK_M_TRACK_REL_MERGED=2, /* Result of merging two or more parent tracks. | */
   MAVLINK_M_TRACK_REL_REID=3, /* Re-identification of a previously dropped track. | */
   MAVLINK_M_TRACK_REL_ENUM_END=4, /*  | */
} MAVLINK_M_TRACK_REL;
#endif

/** @brief Method by which a target identification was reached. Records the basis of ID, separate from classification. */
#ifndef HAVE_ENUM_MAVLINK_M_ID_METHOD
#define HAVE_ENUM_MAVLINK_M_ID_METHOD
typedef enum MAVLINK_M_ID_METHOD
{
   MAVLINK_M_ID_METHOD_UNKNOWN=0, /* Method not recorded. | */
   MAVLINK_M_ID_METHOD_VISUAL_EO=1, /* Electro-optical (visual) identification. | */
   MAVLINK_M_ID_METHOD_IR=2, /* Infrared / thermal identification. | */
   MAVLINK_M_ID_METHOD_SAR=3, /* Synthetic-aperture radar identification. | */
   MAVLINK_M_ID_METHOD_RADAR=4, /* Radar (non-SAR) identification. | */
   MAVLINK_M_ID_METHOD_SIGINT=5, /* Signals-intelligence-derived identification. | */
   MAVLINK_M_ID_METHOD_AUTOMATED_ATR=6, /* Automated target recognition (machine). | */
   MAVLINK_M_ID_METHOD_HUMAN_CONFIRM=7, /* Human-confirmed identification. | */
   MAVLINK_M_ID_METHOD_MULTI_SOURCE=8, /* Correlated from multiple sources. | */
   MAVLINK_M_ID_METHOD_GMTI=9, /* Ground moving target indicator. Distinct from generic RADAR because it drives specific track-correlation handling in Link 16. | */
   MAVLINK_M_ID_METHOD_ENUM_END=10, /*  | */
} MAVLINK_M_ID_METHOD;
#endif

/** @brief Positive identification (PID) status of a target. Descriptive record, not a release authority. */
#ifndef HAVE_ENUM_MAVLINK_M_PID_STATUS
#define HAVE_ENUM_MAVLINK_M_PID_STATUS
typedef enum MAVLINK_M_PID_STATUS
{
   MAVLINK_M_PID_STATUS_NONE=0, /* No PID established. | */
   MAVLINK_M_PID_STATUS_TENTATIVE=1, /* Tentative ID; PID not yet established. | */
   MAVLINK_M_PID_STATUS_POSITIVE=2, /* Positive identification established. | */
   MAVLINK_M_PID_STATUS_LOST=3, /* PID previously held but since lost. | */
   MAVLINK_M_PID_STATUS_ENUM_END=4, /*  | */
} MAVLINK_M_PID_STATUS;
#endif

/** @brief Rules-of-engagement / clearance state asserted for a target. Descriptive attestation carried for audit; does NOT gate weapon release. */
#ifndef HAVE_ENUM_MAVLINK_M_ROE_STATE
#define HAVE_ENUM_MAVLINK_M_ROE_STATE
typedef enum MAVLINK_M_ROE_STATE
{
   MAVLINK_M_ROE_STATE_UNKNOWN=0, /* ROE state not recorded. | */
   MAVLINK_M_ROE_STATE_HOLD=1, /* Hold / do not engage. | */
   MAVLINK_M_ROE_STATE_INVESTIGATE=2, /* Investigate further before any decision. | */
   MAVLINK_M_ROE_STATE_CLEARED=3, /* Engagement cleared by competent authority (attested, not commanded). | */
   MAVLINK_M_ROE_STATE_RESTRICTED=4, /* Restricted: constraints apply (see no-strike / collateral context). | */
   MAVLINK_M_ROE_STATE_ENUM_END=5, /*  | */
} MAVLINK_M_ROE_STATE;
#endif

/** @brief No-strike / restricted-target context for a coordinate or target. */
#ifndef HAVE_ENUM_MAVLINK_M_NOSTRIKE_STATUS
#define HAVE_ENUM_MAVLINK_M_NOSTRIKE_STATUS
typedef enum MAVLINK_M_NOSTRIKE_STATUS
{
   MAVLINK_M_NOSTRIKE_STATUS_UNKNOWN=0, /* No-strike status not evaluated. | */
   MAVLINK_M_NOSTRIKE_STATUS_CLEAR=1, /* Not on any no-strike or restricted list. | */
   MAVLINK_M_NOSTRIKE_STATUS_NEAR=2, /* Within proximity of a no-strike / protected entity. | */
   MAVLINK_M_NOSTRIKE_STATUS_ON_LIST=3, /* On a no-strike or restricted-target list. | */
   MAVLINK_M_NOSTRIKE_STATUS_ENUM_END=4, /*  | */
} MAVLINK_M_NOSTRIKE_STATUS;
#endif

/** @brief Engagement-control directive type. Provides abort / check-fire / re-target as first-class protocol actions alongside FIRES. */
#ifndef HAVE_ENUM_MAVLINK_M_ENGAGEMENT_DIRECTIVE
#define HAVE_ENUM_MAVLINK_M_ENGAGEMENT_DIRECTIVE
typedef enum MAVLINK_M_ENGAGEMENT_DIRECTIVE
{
   MAVLINK_M_ENGAGEMENT_DIRECTIVE_ABORT=0, /* Abort the referenced fire mission. | */
   MAVLINK_M_ENGAGEMENT_DIRECTIVE_CHECK_FIRE=1, /* Temporary check-fire; hold without cancelling. | */
   MAVLINK_M_ENGAGEMENT_DIRECTIVE_RESUME=2, /* Resume after a check-fire. | */
   MAVLINK_M_ENGAGEMENT_DIRECTIVE_RETARGET=3, /* Re-target the referenced fire mission to a new track/coordinate. | */
   MAVLINK_M_ENGAGEMENT_DIRECTIVE_ENUM_END=4, /*  | */
} MAVLINK_M_ENGAGEMENT_DIRECTIVE;
#endif

/** @brief 
        Coarse requested weapon effect, expressing requester INTENT (as in a
        call-for-fire method of engagement). The store controller translates this
        to device-internal fuze timing locally; this enum carries NO timing,
        height-of-burst, or arming-delay values and must not be extended to.
       */
#ifndef HAVE_ENUM_MAVLINK_M_REQUESTED_EFFECT
#define HAVE_ENUM_MAVLINK_M_REQUESTED_EFFECT
typedef enum MAVLINK_M_REQUESTED_EFFECT
{
   MAVLINK_M_REQUESTED_EFFECT_UNSPECIFIED=0, /* No specific effect requested; store default. | */
   MAVLINK_M_REQUESTED_EFFECT_PROXIMITY=1, /* Proximity / airburst effect requested. | */
   MAVLINK_M_REQUESTED_EFFECT_IMPACT=2, /* Point-detonate / impact effect requested. | */
   MAVLINK_M_REQUESTED_EFFECT_DELAY=3, /* Delayed / penetration effect requested. | */
   MAVLINK_M_REQUESTED_EFFECT_ENUM_END=4, /*  | */
} MAVLINK_M_REQUESTED_EFFECT;
#endif

/** @brief 
        Discrete functional damage state for BDA (functional damage assessment
        layer, per CJCSI 3162.02 / JP 3-09), mirroring joint reporting. Carried
        alongside destruction_pct and the physical damage state, not replacing them.
       */
#ifndef HAVE_ENUM_MAVLINK_M_FUNCTIONAL_DAMAGE
#define HAVE_ENUM_MAVLINK_M_FUNCTIONAL_DAMAGE
typedef enum MAVLINK_M_FUNCTIONAL_DAMAGE
{
   MAVLINK_M_FUNCTIONAL_DAMAGE_UNKNOWN=0, /* Damage state not determined. | */
   MAVLINK_M_FUNCTIONAL_DAMAGE_NONE=1, /* No functional damage assessed. | */
   MAVLINK_M_FUNCTIONAL_DAMAGE_MOBILITY=2, /* Mobility kill (target immobilized). | */
   MAVLINK_M_FUNCTIONAL_DAMAGE_FIREPOWER=3, /* Firepower kill (target's weapons disabled). | */
   MAVLINK_M_FUNCTIONAL_DAMAGE_COMMS=4, /* Communications / C2 kill. | */
   MAVLINK_M_FUNCTIONAL_DAMAGE_MISSION=5, /* Mission kill (cannot perform role short of total destruction). | */
   MAVLINK_M_FUNCTIONAL_DAMAGE_CATASTROPHIC=6, /* Catastrophic kill (target destroyed). | */
   MAVLINK_M_FUNCTIONAL_DAMAGE_ENUM_END=7, /*  | */
} MAVLINK_M_FUNCTIONAL_DAMAGE;
#endif

/** @brief 
        Discrete physical damage state for BDA (physical damage assessment layer,
        per CJCSI 3162.02A Methodology for Combat Assessment). Distinct from the
        functional-kill layer.
       */
#ifndef HAVE_ENUM_MAVLINK_M_PHYSICAL_DAMAGE
#define HAVE_ENUM_MAVLINK_M_PHYSICAL_DAMAGE
typedef enum MAVLINK_M_PHYSICAL_DAMAGE
{
   MAVLINK_M_PHYSICAL_DAMAGE_NO_ASSESSMENT=0, /* No assessment / unknown. | */
   MAVLINK_M_PHYSICAL_DAMAGE_NONE=1, /* No damage. | */
   MAVLINK_M_PHYSICAL_DAMAGE_LIGHT=2, /* Light damage. | */
   MAVLINK_M_PHYSICAL_DAMAGE_MODERATE=3, /* Moderate damage. | */
   MAVLINK_M_PHYSICAL_DAMAGE_SEVERE=4, /* Severe damage. | */
   MAVLINK_M_PHYSICAL_DAMAGE_DESTROYED=5, /* Destroyed. | */
   MAVLINK_M_PHYSICAL_DAMAGE_ENUM_END=6, /*  | */
} MAVLINK_M_PHYSICAL_DAMAGE;
#endif

/** @brief 
        Standard identity of a track, aligned to MIL-STD-2525D / APP-6D standard
        identity (SIDC digit 4). MIL-STD-2525D is Distribution A, making it a
        public authoritative source. Richer than MAVLINK_M_TARGET_FORCE:
        preserves PENDING / ASSUMED_FRIEND / SUSPECT distinctions that carry ROE
        meaning and are lost if collapsed to FRIENDLY/FOE. Values follow the
        2525D digit-4 code so a gateway can populate a SIDC directly.
       */
#ifndef HAVE_ENUM_MAVLINK_M_STANAG_IDENTITY
#define HAVE_ENUM_MAVLINK_M_STANAG_IDENTITY
typedef enum MAVLINK_M_STANAG_IDENTITY
{
   MAVLINK_M_STANAG_IDENTITY_PENDING=0, /* Pending: identity not yet evaluated (SIDC 0). | */
   MAVLINK_M_STANAG_IDENTITY_UNKNOWN=1, /* Unknown: evaluated but not established (SIDC 1). | */
   MAVLINK_M_STANAG_IDENTITY_ASSUMED_FRIEND=2, /* Assumed friend (SIDC 2). | */
   MAVLINK_M_STANAG_IDENTITY_FRIEND=3, /* Friend (SIDC 3). | */
   MAVLINK_M_STANAG_IDENTITY_NEUTRAL=4, /* Neutral (SIDC 4). | */
   MAVLINK_M_STANAG_IDENTITY_SUSPECT=5, /* Suspect / joker (SIDC 5). | */
   MAVLINK_M_STANAG_IDENTITY_HOSTILE=6, /* Hostile / faker (SIDC 6). | */
   MAVLINK_M_STANAG_IDENTITY_ENUM_END=7, /*  | */
} MAVLINK_M_STANAG_IDENTITY;
#endif

/** @brief Reality context of a track, per MIL-STD-2525D SIDC digit 3. Lets exercise/simulation tracks be distinguished from real ones. */
#ifndef HAVE_ENUM_MAVLINK_M_SIDC_CONTEXT
#define HAVE_ENUM_MAVLINK_M_SIDC_CONTEXT
typedef enum MAVLINK_M_SIDC_CONTEXT
{
   MAVLINK_M_SIDC_CONTEXT_REALITY=0, /* Reality (SIDC 0). | */
   MAVLINK_M_SIDC_CONTEXT_EXERCISE=1, /* Exercise (SIDC 1). | */
   MAVLINK_M_SIDC_CONTEXT_SIMULATION=2, /* Simulation (SIDC 2). | */
   MAVLINK_M_SIDC_CONTEXT_ENUM_END=3, /*  | */
} MAVLINK_M_SIDC_CONTEXT;
#endif

/** @brief 
        Track environment / dimension, aligned to the STANAG 5516 / APP-6 battle
        dimension. Pairs with MAVLINK_M_STANAG_IDENTITY to make a track mappable
        to joint symbology. Value numbering to be confirmed against spec.
       */
#ifndef HAVE_ENUM_MAVLINK_M_ENVIRONMENT
#define HAVE_ENUM_MAVLINK_M_ENVIRONMENT
typedef enum MAVLINK_M_ENVIRONMENT
{
   MAVLINK_M_ENVIRONMENT_UNKNOWN=0, /* Environment not determined. | */
   MAVLINK_M_ENVIRONMENT_SPACE=1, /* Space. | */
   MAVLINK_M_ENVIRONMENT_AIR=2, /* Air. | */
   MAVLINK_M_ENVIRONMENT_SURFACE=3, /* Surface (land or sea surface). | */
   MAVLINK_M_ENVIRONMENT_SUBSURFACE=4, /* Subsurface. | */
   MAVLINK_M_ENVIRONMENT_LAND=5, /* Land. | */
   MAVLINK_M_ENVIRONMENT_ENUM_END=6, /*  | */
} MAVLINK_M_ENVIRONMENT;
#endif

/** @brief 
        Type/namespace of the external track number carried alongside the native
        track_uid, so a gateway knows how to interpret it. Encodings per the
        respective standard; do not assume a format from this enum alone.
       */
#ifndef HAVE_ENUM_MAVLINK_M_TRACK_NUMBER_TYPE
#define HAVE_ENUM_MAVLINK_M_TRACK_NUMBER_TYPE
typedef enum MAVLINK_M_TRACK_NUMBER_TYPE
{
   MAVLINK_M_TRACK_NUMBER_TYPE_NONE=0, /* No external track number present. | */
   MAVLINK_M_TRACK_NUMBER_TYPE_LINK16=1, /* Link 16 track number (STANAG 5516 J-series). | */
   MAVLINK_M_TRACK_NUMBER_TYPE_VMF_URN=2, /* VMF unit reference number (MIL-STD-6017). | */
   MAVLINK_M_TRACK_NUMBER_TYPE_OTHER=3, /* Other/national namespace (implementation-defined). | */
   MAVLINK_M_TRACK_NUMBER_TYPE_ENUM_END=4, /*  | */
} MAVLINK_M_TRACK_NUMBER_TYPE;
#endif

/** @brief Nature of a participant reporting its own position/identity (PPLI-style). Value numbering to be confirmed against spec. */
#ifndef HAVE_ENUM_MAVLINK_M_PPLI_TYPE
#define HAVE_ENUM_MAVLINK_M_PPLI_TYPE
typedef enum MAVLINK_M_PPLI_TYPE
{
   MAVLINK_M_PPLI_TYPE_UNKNOWN=0, /* Unspecified participant. | */
   MAVLINK_M_PPLI_TYPE_AIR=1, /* Air participant. | */
   MAVLINK_M_PPLI_TYPE_LAND=2, /* Land participant. | */
   MAVLINK_M_PPLI_TYPE_SURFACE=3, /* Surface (maritime) participant. | */
   MAVLINK_M_PPLI_TYPE_SUBSURFACE=4, /* Subsurface participant. | */
   MAVLINK_M_PPLI_TYPE_ENUM_END=5, /*  | */
} MAVLINK_M_PPLI_TYPE;
#endif

/** @brief Coarse guidance category of a loaded munition. Descriptive inventory data, not employment configuration. */
#ifndef HAVE_ENUM_MAVLINK_M_MUNITION_GUIDANCE
#define HAVE_ENUM_MAVLINK_M_MUNITION_GUIDANCE
typedef enum MAVLINK_M_MUNITION_GUIDANCE
{
   MAVLINK_M_MUNITION_GUIDANCE_UNKNOWN=0, /* Guidance category not specified. | */
   MAVLINK_M_MUNITION_GUIDANCE_UNGUIDED=1, /* Unguided. | */
   MAVLINK_M_MUNITION_GUIDANCE_GPS_INS=2, /* GPS/INS-guided. | */
   MAVLINK_M_MUNITION_GUIDANCE_LASER=3, /* Semi-active laser-guided. | */
   MAVLINK_M_MUNITION_GUIDANCE_IR=4, /* Infrared / imaging-IR seeker. | */
   MAVLINK_M_MUNITION_GUIDANCE_RADAR=5, /* Radar-guided. | */
   MAVLINK_M_MUNITION_GUIDANCE_EO=6, /* Electro-optical / visual seeker. | */
   MAVLINK_M_MUNITION_GUIDANCE_MULTI=7, /* Multi-mode seeker. | */
   MAVLINK_M_MUNITION_GUIDANCE_ENUM_END=8, /*  | */
} MAVLINK_M_MUNITION_GUIDANCE;
#endif

/** @brief Coarse warhead category of a loaded munition. Descriptive inventory data; mirrors the effect families used by MAVLINK_M_SPLASH_FUNCTION. Not employment configuration. */
#ifndef HAVE_ENUM_MAVLINK_M_MUNITION_WARHEAD
#define HAVE_ENUM_MAVLINK_M_MUNITION_WARHEAD
typedef enum MAVLINK_M_MUNITION_WARHEAD
{
   MAVLINK_M_MUNITION_WARHEAD_UNKNOWN=0, /* Warhead category not specified. | */
   MAVLINK_M_MUNITION_WARHEAD_INERT=1, /* Inert / training. | */
   MAVLINK_M_MUNITION_WARHEAD_HE=2, /* High explosive. | */
   MAVLINK_M_MUNITION_WARHEAD_FRAG=3, /* Fragmentation. | */
   MAVLINK_M_MUNITION_WARHEAD_SHAPED=4, /* Shaped charge / anti-armor. | */
   MAVLINK_M_MUNITION_WARHEAD_THERMOBARIC=5, /* Thermobaric. | */
   MAVLINK_M_MUNITION_WARHEAD_SMOKE=6, /* Smoke. | */
   MAVLINK_M_MUNITION_WARHEAD_ILLUM=7, /* Illumination. | */
   MAVLINK_M_MUNITION_WARHEAD_ENUM_END=8, /*  | */
} MAVLINK_M_MUNITION_WARHEAD;
#endif

/** @brief 
        Coarse HEALTH of the fuze subsystem. This reports whether the fuze is
        functioning, NOT how it is configured. Fuze mode/timing/height-of-burst
        configuration is intentionally out of scope for this dialect and is
        device-internal.
       */
#ifndef HAVE_ENUM_MAVLINK_M_FUZE_HEALTH
#define HAVE_ENUM_MAVLINK_M_FUZE_HEALTH
typedef enum MAVLINK_M_FUZE_HEALTH
{
   MAVLINK_M_FUZE_HEALTH_UNKNOWN=0, /* Fuze health not reported. | */
   MAVLINK_M_FUZE_HEALTH_NOMINAL=1, /* Fuze subsystem nominal. | */
   MAVLINK_M_FUZE_HEALTH_FAULT=2, /* Fuze subsystem fault. | */
   MAVLINK_M_FUZE_HEALTH_NOT_PRESENT=3, /* No fuze present. | */
   MAVLINK_M_FUZE_HEALTH_ENUM_END=4, /*  | */
} MAVLINK_M_FUZE_HEALTH;
#endif

/** @brief MAVLink-M store-handling commands. Sent via COMMAND_LONG/COMMAND_INT; responses via COMMAND_ACK. */
#ifndef HAVE_ENUM_MAV_CMD
#define HAVE_ENUM_MAV_CMD
typedef enum MAV_CMD
{
   MAV_CMD_NAV_WAYPOINT=16, /* Navigate to waypoint. This is intended for use in missions (for guided commands outside of missions use MAV_CMD_DO_REPOSITION). |Hold time. (ignored by fixed wing, time to stay at waypoint for rotary wing)| Acceptance radius (if the sphere with this radius is hit, the waypoint counts as reached)| 0 to pass through the WP, if > 0 radius to pass by WP. Positive value for clockwise orbit, negative value for counter-clockwise orbit. Allows trajectory control.| Desired yaw angle at waypoint (rotary wing). NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.).| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_LOITER_UNLIM=17, /* Loiter around this waypoint an unlimited amount of time |Empty| Empty| Loiter radius around waypoint for forward-only moving vehicles (not multicopters). If positive loiter clockwise, else counter-clockwise| Desired yaw angle. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.).| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_LOITER_TURNS=18, /* Loiter around this waypoint for X turns |Number of turns.| Leave loiter circle only when track heads towards the next waypoint (MAV_BOOL_FALSE: Leave when turns complete). Values not equal to 0 or 1 are invalid.| Loiter radius around waypoint for forward-only moving vehicles (not multicopters). If positive loiter clockwise, else counter-clockwise| Loiter circle exit location and/or path to next waypoint ("xtrack") for forward-only moving vehicles (not multicopters). 0 for the vehicle to converge towards the center xtrack when it leaves the loiter (the line between the centers of the current and next waypoint), 1 to converge to the direct line between the location that the vehicle exits the loiter radius and the next waypoint. NaN to use the current system default xtrack behaviour.| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_LOITER_TIME=19, /* Loiter at the specified latitude, longitude and altitude for a certain amount of time. Multicopter vehicles stop at the point (within a vehicle-specific acceptance radius). Forward-only moving vehicles (e.g. fixed-wing) circle the point with the specified radius/direction. If the Heading Required parameter (2) is non-zero forward moving aircraft will only leave the loiter circle once heading towards the next waypoint. |Loiter time (only starts once Lat, Lon and Alt is reached).| Leave loiter circle only when track heading towards the next waypoint (MAV_BOOL_FALSE: Leave on time expiry). Values not equal to 0 or 1 are invalid.| Loiter radius around waypoint for forward-only moving vehicles (not multicopters). If positive loiter clockwise, else counter-clockwise.| Loiter circle exit location and/or path to next waypoint ("xtrack") for forward-only moving vehicles (not multicopters). 0 for the vehicle to converge towards the center xtrack when it leaves the loiter (the line between the centers of the current and next waypoint), 1 to converge to the direct line between the location that the vehicle exits the loiter radius and the next waypoint. NaN to use the current system default xtrack behaviour.| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_RETURN_TO_LAUNCH=20, /* Return to launch location |Empty| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_NAV_LAND=21, /* Land at location. |Minimum target altitude if landing is aborted (0 = undefined/use system default).| Precision land mode.| Empty.| Desired yaw angle. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.).| Latitude.| Longitude.| Landing altitude (ground level in current frame).|  */
   MAV_CMD_NAV_TAKEOFF=22, /* Takeoff from ground / hand. Vehicles that support multiple takeoff modes (e.g. VTOL quadplane) should take off using the currently configured mode. |Minimum pitch (if airspeed sensor present), desired pitch without sensor| Empty| Bitmask of options flags.| Yaw angle (if magnetometer present), ignored without magnetometer. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.).| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_LAND_LOCAL=23, /* Land at local position (local frame only) |Landing target number (if available)| Maximum accepted offset from desired landing position - computed magnitude from spherical coordinates: d = sqrt(x^2 + y^2 + z^2), which gives the maximum accepted distance between the desired landing position and the position where the vehicle is about to land| Landing descend rate| Desired yaw angle| Y-axis position| X-axis position| Z-axis / ground level position|  */
   MAV_CMD_NAV_TAKEOFF_LOCAL=24, /* Takeoff from local position (local frame only) |Minimum pitch (if airspeed sensor present), desired pitch without sensor| Empty| Takeoff ascend rate| Yaw angle (if magnetometer or another yaw estimation source present), ignored without one of these| Y-axis position| X-axis position| Z-axis position|  */
   MAV_CMD_NAV_FOLLOW=25, /* Vehicle following, i.e. this waypoint represents the position of a moving vehicle |Following logic to use (e.g. loitering or sinusoidal following) - depends on specific autopilot implementation| Ground speed of vehicle to be followed| Radius around waypoint. If positive loiter clockwise, else counter-clockwise| Desired yaw angle.| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT=30, /* Continue on the current course and climb/descend to specified altitude.  When the altitude is reached continue to the next command (i.e., don't proceed to the next command until the desired altitude is reached. |Climb or Descend (0 = Neutral, command completes when within 5m of this command's altitude, 1 = Climbing, command completes when at or above this command's altitude, 2 = Descending, command completes when at or below this command's altitude.| Empty| Empty| Empty| Empty| Empty| Desired altitude|  */
   MAV_CMD_NAV_LOITER_TO_ALT=31, /* Begin loiter at the specified Latitude and Longitude.  If Lat=Lon=0, then loiter at the current position.  Don't consider the navigation command complete (don't leave loiter) until the altitude has been reached. Additionally, if the Heading Required parameter is non-zero the aircraft will not leave the loiter until heading toward the next waypoint. |Leave loiter circle only when track heading towards the next waypoint (MAV_BOOL_FALSE: Leave when altitude reached). Values not equal to 0 or 1 are invalid.| Loiter radius around waypoint for forward-only moving vehicles (not multicopters). If positive loiter clockwise, negative counter-clockwise, 0 means no change to standard loiter.| Empty| Loiter circle exit location and/or path to next waypoint ("xtrack") for forward-only moving vehicles (not multicopters). 0 for the vehicle to converge towards the center xtrack when it leaves the loiter (the line between the centers of the current and next waypoint), 1 to converge to the direct line between the location that the vehicle exits the loiter radius and the next waypoint. NaN to use the current system default xtrack behaviour.| Latitude| Longitude| Altitude|  */
   MAV_CMD_DO_FOLLOW=32, /* Begin following a target |System ID (of the FOLLOW_TARGET beacon). Send 0 to disable follow-me and return to the default position hold mode.| Reserved| Reserved| Altitude mode: 0: Keep current altitude, 1: keep altitude difference to target, 2: go to a fixed altitude above home.| Altitude above home. (used if mode=2)| Reserved| Time to land in which the MAV should go to the default position hold mode after a message RX timeout.|  */
   MAV_CMD_DO_FOLLOW_REPOSITION=33, /* Reposition the MAV after a follow target command has been sent |Camera q1 (where 0 is on the ray from the camera to the tracking device)| Camera q2| Camera q3| Camera q4| altitude offset from target| X offset from target| Y offset from target|  */
   MAV_CMD_DO_ORBIT=34, /* Start orbiting on the circumference of a circle defined by the parameters. Setting values to NaN/INT32_MAX (as appropriate) results in using defaults. |Radius of the circle. Positive: orbit clockwise. Negative: orbit counter-clockwise. NaN: Use vehicle default radius, or current radius if already orbiting.| Tangential Velocity. NaN: Use vehicle default velocity, or current velocity if already orbiting.| Yaw behavior of the vehicle.| Orbit around the centre point for this many radians (i.e. for a three-quarter orbit set 270*Pi/180). 0: Orbit forever. NaN: Use vehicle default, or current value if already orbiting.| Center point latitude (if no MAV_FRAME specified) / X coordinate according to MAV_FRAME. INT32_MAX (or NaN if sent in COMMAND_LONG): Use current vehicle position, or current center if already orbiting.| Center point longitude (if no MAV_FRAME specified) / Y coordinate according to MAV_FRAME. INT32_MAX (or NaN if sent in COMMAND_LONG): Use current vehicle position, or current center if already orbiting.| Center point altitude (MSL) (if no MAV_FRAME specified) / Z coordinate according to MAV_FRAME. NaN: Use current vehicle altitude.|  */
   MAV_CMD_DO_FIGURE_EIGHT=35, /* Fly a figure eight path as defined by the parameters.
          Set parameters to NaN/INT32_MAX (as appropriate) to use system-default values.
          The command is intended for fixed wing vehicles (and VTOL hybrids flying in fixed-wing mode), allowing POI tracking for gimbals that don't support infinite rotation.
          This command only defines the flight path. Speed should be set independently (use e.g. MAV_CMD_DO_CHANGE_SPEED).
          Yaw and other degrees of freedom are not specified, and will be flight-stack specific (on vehicles where they can be controlled independent of the heading).
         |Major axis radius of the figure eight. Positive: orbit the north circle clockwise. Negative: orbit the north circle counter-clockwise.
        NaN: The radius will be set to 2.5 times the minor radius and direction is clockwise.
        Must be greater or equal to two times the minor radius for feasible values.| Minor axis radius of the figure eight. Defines the radius of the two circles that make up the figure. Negative value has no effect.
        NaN: The radius will be set to the default loiter radius.| Reserved (default:NaN)| Orientation of the figure eight major axis with respect to true north (range: [-pi,pi]). NaN: use default orientation aligned to true north.| Center point latitude/X coordinate according to MAV_FRAME. If no MAV_FRAME specified, MAV_FRAME_GLOBAL is assumed.
        INT32_MAX or NaN: Use current vehicle position, or current center if already loitering.| Center point longitude/Y coordinate according to MAV_FRAME. If no MAV_FRAME specified, MAV_FRAME_GLOBAL is assumed.
        INT32_MAX or NaN: Use current vehicle position, or current center if already loitering.| Center point altitude MSL/Z coordinate according to MAV_FRAME. If no MAV_FRAME specified, MAV_FRAME_GLOBAL is assumed.
        INT32_MAX or NaN: Use current vehicle altitude.|  */
   MAV_CMD_NAV_ARC_WAYPOINT=36, /* Circular arc path waypoint.
          This defines the end/exit point and angle (param1) of an arc path from the previous waypoint. A position is required before this command to define the start of the arc (e.g. current position, a MAV_CMD_NAV_WAYPOINT, or a MAV_CMD_NAV_ARC_WAYPOINT).
          The resulting path is a circular arc in the NE frame, with the difference in height being defined by the difference in waypoint altitudes.
         |The angle in degrees from the starting position to the exit position of the arc in the NE frame. Positive values are CW arcs and negative values are CCW arcs.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_ROI=80, /* Sets the region of interest (ROI) for a sensor set or the vehicle itself. This can then be used by the vehicle's control system to control the vehicle attitude and the attitude of various sensors such as cameras. |Region of interest mode.| Waypoint index/ target ID. (see MAV_ROI enum)| ROI index (allows a vehicle to manage multiple ROI's)| Empty| x the location of the fixed ROI (see MAV_FRAME)| y| z|  */
   MAV_CMD_NAV_PATHPLANNING=81, /* Control autonomous path planning on the MAV. |0: Disable local obstacle avoidance / local path planning (without resetting map), 1: Enable local path planning, 2: Enable and reset local path planning| 0: Disable full path planning (without resetting map), 1: Enable, 2: Enable and reset map/occupancy grid, 3: Enable and reset planned route, but not occupancy grid| Empty| Yaw angle at goal| Latitude/X of goal| Longitude/Y of goal| Altitude/Z of goal|  */
   MAV_CMD_NAV_SPLINE_WAYPOINT=82, /* Navigate to waypoint using a spline path. |Hold time. (ignored by fixed wing, time to stay at waypoint for rotary wing)| Empty| Empty| Empty| Latitude/X of goal| Longitude/Y of goal| Altitude/Z of goal|  */
   MAV_CMD_NAV_VTOL_TAKEOFF=84, /* Takeoff from ground using VTOL mode, and transition to forward flight with specified heading. The command should be ignored by vehicles that dont support both VTOL and fixed-wing flight (multicopters, boats,etc.). |Empty| Front transition heading.| Empty| Yaw angle. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.).| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_VTOL_LAND=85, /* Land using VTOL mode |Landing behaviour.| Empty| Approach altitude (with the same reference as the Altitude field). NaN if unspecified.| Yaw angle. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.).| Latitude| Longitude| Altitude (ground level) relative to the current coordinate frame. NaN to use system default landing altitude (ignore value).|  */
   MAV_CMD_NAV_GUIDED_ENABLE=92, /* Hand control over to an external controller |Guided mode on (MAV_BOOL_FALSE: Off). Values not equal to 0 or 1 are invalid.| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_NAV_DELAY=93, /* Delay the next navigation command a number of seconds or until a specified time |Delay (-1 to enable time-of-day fields)| hour (24h format, UTC, -1 to ignore)| minute (24h format, UTC, -1 to ignore)| second (24h format, UTC, -1 to ignore)| Empty| Empty| Empty|  */
   MAV_CMD_NAV_PAYLOAD_PLACE=94, /* Descend and place payload. Vehicle moves to specified location, descends until it detects a hanging payload has reached the ground, and then releases the payload. If ground is not detected before the reaching the maximum descent value (param1), the command will complete without releasing the payload. |Maximum distance to descend.| Empty| Empty| Empty| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_LAST=95, /* NOP - This command is only used to mark the upper limit of the NAV/ACTION commands in the enumeration |Empty| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_CONDITION_DELAY=112, /* Delay mission state machine. |Delay| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_CONDITION_CHANGE_ALT=113, /* Ascend/descend to target altitude at specified rate. Delay mission state machine until desired altitude reached. |Descent / Ascend rate.| Empty| Empty| Empty| Empty| Empty| Target Altitude|  */
   MAV_CMD_CONDITION_DISTANCE=114, /* Delay mission state machine until within desired distance of next NAV point. |Distance.| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_CONDITION_YAW=115, /* Reach a certain target angle. |target angle [0-360]. Absolute angles: 0 is north. Relative angle: 0 is initial yaw. Direction set by param3.| angular speed| direction: -1: counter clockwise, 0: shortest direction, 1: clockwise| Relative offset (MAV_BOOL_FALSE: absolute angle). Values not equal to 0 or 1 are invalid.| Empty| Empty| Empty|  */
   MAV_CMD_CONDITION_LAST=159, /* NOP - This command is only used to mark the upper limit of the CONDITION commands in the enumeration |Empty| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_MODE=176, /* Set system mode. |Mode flags. MAV_MODE values can be used to set some mode flag combinations.| Custom system-specific mode (see target autopilot specifications for mode information). If MAV_MODE_FLAG_CUSTOM_MODE_ENABLED is set in param1 (mode) this mode is used: otherwise the field is ignored.| Custom sub mode - this is system specific, please refer to the individual autopilot specifications for details.| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_JUMP=177, /* Jump to the desired command in the mission list.  Repeat this action only the specified number of times |Sequence number| Repeat count| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_CHANGE_SPEED=178, /* Change speed and/or throttle set points. The value persists until it is overridden or there is a mode change |Speed type of value set in param2 (such as airspeed, ground speed, and so on)| Speed (-1 indicates no change, -2 indicates return to default vehicle speed)| Throttle (-1 indicates no change, -2 indicates return to default vehicle throttle value)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_DO_SET_HOME=179, /* 
          Sets the home position to either to the current position or a specified position.
          The home position is the default position that the system will return to and land on.
          The position is set automatically by the system during the takeoff (and may also be set using this command).
          Note: the current home position may be emitted in a HOME_POSITION message on request (using MAV_CMD_REQUEST_MESSAGE with param1=242).
         |Use current location (MAV_BOOL_FALSE: use specified location). Values not equal to 0 or 1 are invalid.| Roll angle (of surface). Range: -180..180 degrees. NAN or 0 means value not set. 0.01 indicates zero roll.| Pitch angle (of surface). Range: -90..90 degrees. NAN or 0 means value not set. 0.01 means zero pitch.| Yaw angle. NaN to use default heading. Range: -180..180 degrees.| Latitude| Longitude| Altitude|  */
   MAV_CMD_DO_SET_PARAMETER=180, /* Set a system parameter.  Caution!  Use of this command requires knowledge of the numeric enumeration value of the parameter. |Parameter number| Parameter value| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_RELAY=181, /* Set a relay to a condition. The current value may optionally be reported using RELAY_STATUS. |Relay instance number.| Setting. (1=on, 0=off, others possible depending on system hardware)| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_REPEAT_RELAY=182, /* Cycle a relay on and off for a desired number of cycles with a desired period. |Relay instance number.| Cycle count.| Cycle time.| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_SERVO=183, /* Set a servo to a desired PWM value. |Servo instance number.| Pulse Width Modulation.| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_REPEAT_SERVO=184, /* Cycle a between its nominal setting and a desired PWM for a desired number of cycles with a desired period. |Servo instance number.| Pulse Width Modulation.| Cycle count.| Cycle time.| Empty| Empty| Empty|  */
   MAV_CMD_DO_FLIGHTTERMINATION=185, /* Terminate flight immediately.
          Flight termination immediately and irreversibly terminates the current flight, returning the vehicle to ground.
          The vehicle will ignore RC or other input until it has been power-cycled.
          Termination may trigger safety measures, including: disabling motors and deployment of parachute on multicopters, and setting flight surfaces to initiate a landing pattern on fixed-wing).
          On multicopters without a parachute it may trigger a crash landing.
          Support for this command can be tested using the protocol bit: MAV_PROTOCOL_CAPABILITY_FLIGHT_TERMINATION.
          Support for this command can also be tested by sending the command with param1=0 (< 0.5); the ACK should be either MAV_RESULT_FAILED or MAV_RESULT_UNSUPPORTED.
         |Flight termination activated if > 0.5. Otherwise not activated and ACK with MAV_RESULT_FAILED.| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_CHANGE_ALTITUDE=186, /* Change altitude set point. |Altitude.| Frame of new altitude.| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_ACTUATOR=187, /* Sets actuators (e.g. servos) to a desired value. The actuator numbers are mapped to specific outputs (e.g. on any MAIN or AUX PWM or UAVCAN) using a flight-stack specific mechanism (i.e. a parameter). |Actuator 1 value, scaled from [-1 to 1]. NaN to ignore.| Actuator 2 value, scaled from [-1 to 1]. NaN to ignore.| Actuator 3 value, scaled from [-1 to 1]. NaN to ignore.| Actuator 4 value, scaled from [-1 to 1]. NaN to ignore.| Actuator 5 value.
          If sent in COMMAND_LONG: value is scaled from [-1 to 1]. NaN to ignore.
          If sent in COMMAND_INT or MISSION_ITEM_INT: value is scaled by 1e7. INT32_MAX to ignore.| Actuator 6 value.
          If sent in COMMAND_LONG: value is scaled from [-1 to 1]. NaN to ignore.
          If sent in COMMAND_INT or MISSION_ITEM_INT: value is scaled by 1e7. INT32_MAX to ignore.| Index of actuator set (i.e if set to 1, Actuator 1 becomes Actuator 7)|  */
   MAV_CMD_DO_RETURN_PATH_START=188, /* Mission item to specify the start of a failsafe/landing return-path segment (the end of the segment is the next MAV_CMD_DO_LAND_START item).
          A vehicle that is using missions for landing (e.g. in a return mode) will join the mission on the closest path of the return-path segment (instead of MAV_CMD_DO_LAND_START or the nearest waypoint).
          The main use case is to minimize the failsafe flight path in corridor missions, where the inbound/outbound paths are constrained (by geofences) to the same particular path.
          The MAV_CMD_NAV_RETURN_PATH_START would be placed at the start of the return path.
          If a failsafe occurs on the outbound path the vehicle will move to the nearest point on the return path (which is parallel for this kind of mission), effectively turning round and following the shortest path to landing.
          If a failsafe occurs on the inbound path the vehicle is already on the return segment and will continue to landing.
          The Latitude/Longitude/Altitude are optional, and may be set to 0 if not needed.
          If specified, the item defines the waypoint at which the return segment starts.
          If sent using as a command, the vehicle will perform a mission landing (using the land segment if defined) or reject the command if mission landings are not supported, or no mission landing is defined. When used as a command any position information in the command is ignored.
         |Empty| Empty| Empty| Empty| Latitudee. 0: not used.| Longitudee. 0: not used.| Altitudee. 0: not used.|  */
   MAV_CMD_DO_LAND_START=189, /* Mission item to mark the start of a mission landing pattern, or a command to land with a mission landing pattern.

        When used in a mission, this is a marker for the start of a sequence of mission items that represent a landing pattern.
        It should be followed by a navigation item that defines the first waypoint of the landing sequence.
        The start marker positional params are used only for selecting what landing pattern to use if several are defined in the mission (the selected pattern will be the one with the marker position that is closest to the vehicle when a landing is commanded).
        If the marker item position has zero-values for latitude, longitude, and altitude, then landing pattern selection is instead based on the position of the first waypoint in the landing sequence.

	      When sent as a command it triggers a landing using a mission landing pattern.
	      The location parameters are not used in this case, and should be set to 0.
	 |Empty| Empty| Empty| Empty| Latitude for landing sequence selection, or 0 (see description). Ignored in commands (set 0).| Longitude for landing sequence selection, or 0 (see description). Ignored in commands (set 0).| Altitude for landing sequence selection, or 0 (see description). Ignored in commands (set 0).|  */
   MAV_CMD_DO_RALLY_LAND=190, /* Mission command to perform a landing from a rally point. |Break altitude| Landing speed| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_GO_AROUND=191, /* Mission command to safely abort an autonomous landing. |Altitude| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_REPOSITION=192, /* Reposition the vehicle to a specific WGS84 global position. This command is intended for guided commands (for missions use MAV_CMD_NAV_WAYPOINT instead). |Ground speed, less than 0 (-1) for default| Bitmask of option flags.| Loiter radius for planes. Positive values only, direction is controlled by Yaw value. A value of zero or NaN is ignored. | Yaw heading (heading reference defined in Bitmask field). NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.). For planes indicates loiter direction (0: clockwise, 1: counter clockwise)| Latitude| Longitude| Altitude|  */
   MAV_CMD_DO_PAUSE_CONTINUE=193, /* If in a GPS controlled position mode, hold the current position or continue. |Continue mission (MAV_BOOL_TRUE), Pause current mission or reposition command, hold current position (MAV_BOOL_FALSE). Values not equal to 0 or 1 are invalid. A VTOL capable vehicle should enter hover mode (multicopter and VTOL planes). A plane should loiter with the default loiter radius.| Reserved| Reserved| Reserved| Reserved| Reserved| Reserved|  */
   MAV_CMD_DO_SET_REVERSE=194, /* Set moving direction to forward or reverse. |Reverse direction (MAV_BOOL_FALSE: Forward direction). Values not equal to 0 or 1 are invalid.| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_ROI_LOCATION=195, /* Sets the region of interest (ROI) to a location. This can then be used by the vehicle's control system to control the vehicle attitude and the attitude of various sensors such as cameras. This command can be sent to a gimbal manager but not to a gimbal device. A gimbal is not to react to this message. |Component ID of gimbal device to address (or 1-6 for non-MAVLink gimbal), 0 for all gimbal device components. Send command multiple times for more than one gimbal (but not all gimbals).| Empty| Empty| Empty| Latitude of ROI location| Longitude of ROI location| Altitude of ROI location|  */
   MAV_CMD_DO_SET_ROI_WPNEXT_OFFSET=196, /* Sets the region of interest (ROI) to be toward next waypoint, with optional pitch/roll/yaw offset. This can then be used by the vehicle's control system to control the vehicle attitude and the attitude of various sensors such as cameras. This command can be sent to a gimbal manager but not to a gimbal device. A gimbal device is not to react to this message. |Component ID of gimbal device to address (or 1-6 for non-MAVLink gimbal), 0 for all gimbal device components. Send command multiple times for more than one gimbal (but not all gimbals).| Empty| Empty| Empty| Pitch offset from next waypoint, positive pitching up| Roll offset from next waypoint, positive rolling to the right| Yaw offset from next waypoint, positive yawing to the right|  */
   MAV_CMD_DO_SET_ROI_NONE=197, /* Cancels any previous ROI command returning the vehicle/sensors to default flight characteristics. This can then be used by the vehicle's control system to control the vehicle attitude and the attitude of various sensors such as cameras. This command can be sent to a gimbal manager but not to a gimbal device. A gimbal device is not to react to this message. After this command the gimbal manager should go back to manual input if available, and otherwise assume a neutral position. |Component ID of gimbal device to address (or 1-6 for non-MAVLink gimbal), 0 for all gimbal device components. Send command multiple times for more than one gimbal (but not all gimbals).| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_ROI_SYSID=198, /* Mount tracks system with specified system ID. Determination of target vehicle position may be done with GLOBAL_POSITION_INT or any other means. This command can be sent to a gimbal manager but not to a gimbal device. A gimbal device is not to react to this message. |System ID| Component ID of gimbal device to address (or 1-6 for non-MAVLink gimbal), 0 for all gimbal device components. Send command multiple times for more than one gimbal (but not all gimbals).| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_DO_CONTROL_VIDEO=200, /* Control onboard camera system. |Camera ID (-1 for all)| Transmission: 0: disabled, 1: enabled compressed, 2: enabled raw| Transmission mode: 0: video stream, >0: single images every n seconds| Recording: 0: disabled, 1: enabled compressed, 2: enabled raw| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_ROI=201, /* Sets the region of interest (ROI) for a sensor set or the vehicle itself. This can then be used by the vehicle's control system to control the vehicle attitude and the attitude of various sensors such as cameras. |Region of interest mode.| Waypoint index/ target ID (depends on param 1).| Region of interest index. (allows a vehicle to manage multiple ROI's)| Empty| MAV_ROI_WPNEXT: pitch offset from next waypoint, MAV_ROI_LOCATION: latitude| MAV_ROI_WPNEXT: roll offset from next waypoint, MAV_ROI_LOCATION: longitude| MAV_ROI_WPNEXT: yaw offset from next waypoint, MAV_ROI_LOCATION: altitude|  */
   MAV_CMD_DO_DIGICAM_CONFIGURE=202, /* Configure digital camera. This is a fallback message for systems that have not yet implemented PARAM_EXT_XXX messages and camera definition files (see https://mavlink.io/en/services/camera_def.html ). |Modes: P, TV, AV, M, Etc.| Shutter speed: Divisor number for one second.| Aperture: F stop number.| ISO number e.g. 80, 100, 200, Etc.| Exposure type enumerator.| Command Identity.| Main engine cut-off time before camera trigger. (0 means no cut-off)|  */
   MAV_CMD_DO_DIGICAM_CONTROL=203, /* Control digital camera. This is a fallback message for systems that have not yet implemented PARAM_EXT_XXX messages and camera definition files (see https://mavlink.io/en/services/camera_def.html ). |Session control e.g. show/hide lens| Zoom's absolute position| Zooming step value to offset zoom from the current position| Focus Locking, Unlocking or Re-locking| Shooting Command| Command Identity| Test shot identifier. If set to 1, image will only be captured, but not counted towards internal frame count.|  */
   MAV_CMD_DO_MOUNT_CONFIGURE=204, /* Mission command to configure a camera or antenna mount |Mount operation mode| Stabilize roll (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Stabilize pitch (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Stabilize yaw (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Roll input (0 = angle body frame, 1 = angular rate, 2 = angle absolute frame)| Pitch input (0 = angle body frame, 1 = angular rate, 2 = angle absolute frame)| Yaw input (0 = angle body frame, 1 = angular rate, 2 = angle absolute frame)|  */
   MAV_CMD_DO_MOUNT_CONTROL=205, /* Mission command to control a camera or antenna mount |pitch depending on mount mode (degrees or degrees/second depending on pitch input).| roll depending on mount mode (degrees or degrees/second depending on roll input).| yaw depending on mount mode (degrees or degrees/second depending on yaw input).| altitude depending on mount mode.| latitude, set if appropriate mount mode.| longitude, set if appropriate mount mode.| Mount mode.|  */
   MAV_CMD_DO_SET_CAM_TRIGG_DIST=206, /* Mission command to set camera trigger distance for this flight. The camera is triggered each time this distance is exceeded. This command can also be used to set the shutter integration time for the camera. |Camera trigger distance. 0 to stop triggering.| Camera shutter integration time. -1 or 0 to ignore| Trigger camera once, immediately (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Empty| Empty| Empty|  */
   MAV_CMD_DO_FENCE_ENABLE=207, /* 
          Enable the geofence.
          This can be used in a mission or via the command protocol.
          The persistence/lifetime of the setting is undefined.
          Depending on flight stack implementation it may persist until superseded, or it may revert to a system default at the end of a mission.
          Flight stacks typically reset the setting to system defaults on reboot.
	 |enable? (0=disable, 1=enable, 2=disable_floor_only)| Fence types to enable or disable as a bitmask. 0: field is unused/all fences should be enabled or disabled (for compatibility reasons). Parameter is ignored if param1=2.| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_PARACHUTE=208, /* Mission item/command to release a parachute or enable/disable auto release. |Action| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_MOTOR_TEST=209, /* Command to perform motor test. |Motor instance number (from 1 to max number of motors on the vehicle).| Throttle type (whether the Throttle Value in param3 is a percentage, PWM value, etc.)| Throttle value.| Timeout between tests that are run in sequence.| Motor count. Number of motors to test in sequence: 0/1=one motor, 2= two motors, etc. The Timeout (param4) is used between tests.| Motor test order.| Empty|  */
   MAV_CMD_DO_INVERTED_FLIGHT=210, /* Change to/from inverted flight. |Inverted flight (MAV_BOOL_False: normal flight). Values not equal to 0 or 1 are invalid.| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_GRIPPER=211, /* Mission command to operate a gripper. |Gripper ID. 1-6 for an autopilot connected gripper. In missions this may be set to 1-6 for an autopilot gripper, or the gripper component id for a MAVLink gripper. 0 targets all grippers.| Gripper action to perform.| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_AUTOTUNE_ENABLE=212, /* Enable/disable autotune. |Enable autotune (MAV_BOOL_FALSE: disable autotune). Values not equal to 0 or 1 are invalid.| Specify axes for which autotuning is enabled/disabled. 0 indicates the field is unused (for compatibility reasons). If 0 the autopilot will follow its default behaviour, which is usually to tune all axes.| Empty.| Empty.| Empty.| Empty.| Empty.|  */
   MAV_CMD_NAV_SET_YAW_SPEED=213, /* Sets a desired vehicle turn angle and speed change. |Yaw angle to adjust steering by.| Speed.| Relative final angle (MAV_BOOL_FALSE: Absolute angle). Values not equal to 0 or 1 are invalid.| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_CAM_TRIGG_INTERVAL=214, /* Mission command to set camera trigger interval for this flight. If triggering is enabled, the camera is triggered each time this interval expires. This command can also be used to set the shutter integration time for the camera. |Camera trigger cycle time. -1 or 0 to ignore.| Camera shutter integration time. Should be less than trigger cycle time. -1 or 0 to ignore.| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_MOUNT_CONTROL_QUAT=220, /* Mission command to control a camera or antenna mount, using a quaternion as reference. |quaternion param q1, w (1 in null-rotation)| quaternion param q2, x (0 in null-rotation)| quaternion param q3, y (0 in null-rotation)| quaternion param q4, z (0 in null-rotation)| Empty| Empty| Empty|  */
   MAV_CMD_DO_GUIDED_MASTER=221, /* set id of master controller |System ID| Component ID| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_GUIDED_LIMITS=222, /* Set limits for external control |Timeout - maximum time that external controller will be allowed to control vehicle. 0 means no timeout.| Altitude (MSL) min - if vehicle moves below this alt, the command will be aborted and the mission will continue. 0 means no lower altitude limit.| Altitude (MSL) max - if vehicle moves above this alt, the command will be aborted and the mission will continue. 0 means no upper altitude limit.| Horizontal move limit - if vehicle moves more than this distance from its location at the moment the command was executed, the command will be aborted and the mission will continue. 0 means no horizontal move limit.| Empty| Empty| Empty|  */
   MAV_CMD_DO_ENGINE_CONTROL=223, /* Control vehicle engine. This is interpreted by the vehicles engine controller to change the target engine state. It is intended for vehicles with internal combustion engines |Start engine (MAV_BOOL_False: Stop engine). Values not equal to 0 or 1 are invalid.| Cold start engine (MAV_BOOL_FALSE: Warm start). Values not equal to 0 or 1 are invalid. Controls use of choke where applicable| Height delay. This is for commanding engine start only after the vehicle has gained the specified height. Used in VTOL vehicles during takeoff to start engine after the aircraft is off the ground. Zero for no delay.| A bitmask of options for engine control| Empty| Empty| Empty|  */
   MAV_CMD_DO_SET_MISSION_CURRENT=224, /* 
          Set the mission item with sequence number seq as the current item and emit MISSION_CURRENT (whether or not the mission number changed).
          If a mission is currently being executed, the system will continue to this new mission item on the shortest path, skipping any intermediate mission items.
	  Note that mission jump repeat counters are not reset unless param2 is set (see MAV_CMD_DO_JUMP param2).

          This command may trigger a mission state-machine change on some systems: for example from MISSION_STATE_NOT_STARTED or MISSION_STATE_PAUSED to MISSION_STATE_ACTIVE.
          If the system is in mission mode, on those systems this command might therefore start, restart or resume the mission.
          If the system is not in mission mode this command must not trigger a switch to mission mode.

          The mission may be "reset" using param2.
          Resetting sets jump counters to initial values (to reset counters without changing the current mission item set the param1 to `-1`).
          Resetting also explicitly changes a mission state of MISSION_STATE_COMPLETE to MISSION_STATE_PAUSED or MISSION_STATE_ACTIVE, potentially allowing it to resume when it is (next) in a mission mode.

	  The command will ACK with MAV_RESULT_FAILED if the sequence number is out of range (including if there is no mission item).
         |Mission sequence value to set. -1 for the current mission item (use to reset mission without changing current mission item).| Reset mission (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid. Resets jump counters to initial values and changes mission state "completed" to be "active" or "paused".| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_DO_LAST=240, /* NOP - This command is only used to mark the upper limit of the DO commands in the enumeration |Empty| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_PREFLIGHT_CALIBRATION=241, /* Trigger calibration. This command will be only accepted if in pre-flight mode. Except for Temperature Calibration, only one sensor should be set in a single message and all others should be zero. |1: gyro calibration, 3: gyro temperature calibration| Magnetometer calibration action.| Ground pressure calibration. Values not equal to 0 or 1 are invalid.| 1: radio RC calibration, 2: RC trim calibration| Accelerometer calibration action.| 1: APM: compass/motor interference calibration (PX4: airspeed calibration, deprecated), 2: airspeed calibration| 1: ESC calibration, 3: barometer temperature calibration|  */
   MAV_CMD_PREFLIGHT_SET_SENSOR_OFFSETS=242, /* Set sensor offsets. This command will be only accepted if in pre-flight mode. |Sensor to adjust the offsets for: 0: gyros, 1: accelerometer, 2: magnetometer, 3: barometer, 4: optical flow, 5: second magnetometer, 6: third magnetometer| X axis offset (or generic dimension 1), in the sensor's raw units| Y axis offset (or generic dimension 2), in the sensor's raw units| Z axis offset (or generic dimension 3), in the sensor's raw units| Generic dimension 4, in the sensor's raw units| Generic dimension 5, in the sensor's raw units| Generic dimension 6, in the sensor's raw units|  */
   MAV_CMD_PREFLIGHT_UAVCAN=243, /* Trigger UAVCAN configuration (actuator ID assignment and direction mapping). Note that this maps to the legacy UAVCAN v0 function UAVCAN_ENUMERATE, which is intended to be executed just once during initial vehicle configuration (it is not a normal pre-flight command and has been poorly named). |1: Trigger actuator ID assignment and direction mapping. 0: Cancel command.| Reserved| Reserved| Reserved| Reserved| Reserved| Reserved|  */
   MAV_CMD_PREFLIGHT_STORAGE=245, /* Request storage of different parameter values and logs. This command will be only accepted if in pre-flight mode. |Action to perform on the persistent parameter storage| Action to perform on the persistent mission storage| Onboard logging: 0: Ignore, 1: Start default rate logging, -1: Stop logging, > 1: logging rate (e.g. set to 1000 for 1000 Hz logging)| Reserved| Empty| Empty| Empty|  */
   MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN=246, /* Request the reboot or shutdown of system components. |Action to take for autopilot.| Action to take for onboard computer.| Action to take for component specified in param4.| MAVLink Component ID targeted in param3 (0 for all components).| Reserved (set to 0)| Conditions under which reboot/shutdown is allowed.| WIP: ID (e.g. camera ID -1 for all IDs)|  */
   MAV_CMD_OVERRIDE_GOTO=252, /* Override current mission with command to pause mission, pause mission and move to position, continue/resume mission. When param 1 indicates that the mission is paused (MAV_GOTO_DO_HOLD), param 2 defines whether it holds in place or moves to another position. |MAV_GOTO_DO_HOLD: pause mission and either hold or move to specified position (depending on param2), MAV_GOTO_DO_CONTINUE: resume mission.| MAV_GOTO_HOLD_AT_CURRENT_POSITION: hold at current position, MAV_GOTO_HOLD_AT_SPECIFIED_POSITION: hold at specified position.| Coordinate frame of hold point.| Desired yaw angle.| Latitude/X position.| Longitude/Y position.| Altitude/Z position.|  */
   MAV_CMD_OBLIQUE_SURVEY=260, /* Mission command to set a Camera Auto Mount Pivoting Oblique Survey (Replaces CAM_TRIGG_DIST for this purpose). The camera is triggered each time this distance is exceeded, then the mount moves to the next position. Params 4~6 set-up the angle limits and number of positions for oblique survey, where mount-enabled vehicles automatically roll the camera between shots to emulate an oblique camera setup (providing an increased HFOV). This command can also be used to set the shutter integration time for the camera. |Camera trigger distance. 0 to stop triggering.| Camera shutter integration time. 0 to ignore| The minimum interval in which the camera is capable of taking subsequent pictures repeatedly. 0 to ignore.| Total number of roll positions at which the camera will capture photos (images captures spread evenly across the limits defined by param5).| Angle limits that the camera can be rolled to left and right of center.| Fixed pitch angle that the camera will hold in oblique mode if the mount is actuated in the pitch axis.| Empty|  */
   MAV_CMD_DO_SET_STANDARD_MODE=262, /* Enable the specified standard MAVLink mode.
          If the specified mode is not supported, the vehicle should ACK with MAV_RESULT_FAILED.
          See https://mavlink.io/en/services/standard_modes.html
         |The mode to set.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:NaN)|  */
   MAV_CMD_MISSION_START=300, /* start running a mission |first_item: the first mission item to run| last_item:  the last mission item to run (after this item is run, the mission ends)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_ACTUATOR_TEST=310, /* Actuator testing command. This is similar to MAV_CMD_DO_MOTOR_TEST but operates on the level of output functions, i.e. it is possible to test Motor1 independent from which output it is configured on. Autopilots must NACK this command with MAV_RESULT_TEMPORARILY_REJECTED while armed. |Output value: 1 means maximum positive output, 0 to center servos or minimum motor thrust (expected to spin), -1 for maximum negative (if not supported by the motors, i.e. motor is not reversible, smaller than 0 maps to NaN). And NaN maps to disarmed (stop the motors).| Timeout after which the test command expires and the output is restored to the previous value. A timeout has to be set for safety reasons. A timeout of 0 means to restore the previous value immediately.| Reserved (default:0)| Reserved (default:0)| Actuator Output function| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_CONFIGURE_ACTUATOR=311, /* Actuator configuration command. |Actuator configuration action| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Actuator Output function| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_COMPONENT_ARM_DISARM=400, /* Arms / Disarms a component |Arm (MAV_BOOL_FALSE: disarm). Values not equal to 0 or 1 are invalid.| 0: arm-disarm unless prevented by safety checks (i.e. when landed), 21196: force arming/disarming (e.g. allow arming to override preflight checks and disarming in flight)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_RUN_PREARM_CHECKS=401, /* Instructs a target system to run pre-arm checks.
          This allows preflight checks to be run on demand, which may be useful on systems that normally run them at low rate, or which do not trigger checks when the armable state might have changed.
          This command should return MAV_RESULT_ACCEPTED if it will run the checks.
          The results of the checks are usually then reported in SYS_STATUS messages (this is system-specific).
          The command should return MAV_RESULT_TEMPORARILY_REJECTED if the system is already armed.
         |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_ILLUMINATOR_ON_OFF=405, /* Turns illuminators ON/OFF. An illuminator is a light source that is used for lighting up dark areas external to the system: e.g. a torch or searchlight (as opposed to a light source for illuminating the system itself, e.g. an indicator light). |Illuminators on/off (MAV_BOOL_TRUE: illuminators on). Values not equal to 0 or 1 are invalid.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_DO_ILLUMINATOR_CONFIGURE=406, /* Configures illuminator settings. An illuminator is a light source that is used for lighting up dark areas external to the system: e.g. a torch or searchlight (as opposed to a light source for illuminating the system itself, e.g. an indicator light). |Mode| 0%: Off, 100%: Max Brightness| Strobe period in seconds where 0 means strobing is not used| Strobe duty cycle where 100% means it is on constantly and 0 means strobing is not used| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_GET_HOME_POSITION=410, /* Request the home position from the vehicle.
          The vehicle will ACK the command and emit the HOME_POSITION message. |Reserved| Reserved| Reserved| Reserved| Reserved| Reserved| Reserved|  */
   MAV_CMD_INJECT_FAILURE=420, /* Inject artificial failure for testing purposes. Note that autopilots should implement an additional protection before accepting this command such as a specific param setting. |The unit which is affected by the failure.| The type how the failure manifests itself.| Instance affected by failure (0 to signal all). Takes precedence over Instance bitmask (param4) when not NaN. Set to NaN to use Instance bitmask instead.| Bitmask of instances affected by the failure (bit 0 = first instance, bit 1 = second instance, etc.). Used only when Instance (param3) is NaN.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_START_RX_PAIR=500, /* Starts receiver pairing. |RC type.| RC sub type.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_GET_MESSAGE_INTERVAL=510, /* 
          Request the interval between messages for a particular MAVLink message ID.
          The receiver should ACK the command and then emit its response in a MESSAGE_INTERVAL message.
         |The MAVLink message ID| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SET_MESSAGE_INTERVAL=511, /* Set the interval between messages for a particular MAVLink message ID. This interface replaces REQUEST_DATA_STREAM. |The MAVLink message ID| The interval between two messages. -1: disable. 0: request default rate (which may be zero).| Use for index ID, if required. Otherwise, the use of this parameter (if any) must be defined in the requested message. By default assumed not used (0).  When used as an index ID, 0 means "all instances", "1" means the first instance in the sequence (the emitted message will have an id of 0 if message ids are 0-indexed, or 1 if index numbers start from one).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0/NaN).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0/NaN).| Target address of message stream (if message has target address fields). 0: Flight-stack default (recommended), 1: address of requester, 2: broadcast.|  */
   MAV_CMD_REQUEST_MESSAGE=512, /* Request the target system(s) emit a single instance of a specified message (i.e. a "one-shot" version of MAV_CMD_SET_MESSAGE_INTERVAL). |The MAVLink message ID of the requested message.| Use for index ID, if required. Otherwise, the use of this parameter (if any) must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| Target address for requested message (if message has target address fields). 0: Flight-stack default, 1: address of requester, 2: broadcast.|  */
   MAV_CMD_REQUEST_PROTOCOL_VERSION=519, /* Request MAVLink protocol version compatibility. All receivers should ACK the command and then emit their capabilities in an PROTOCOL_VERSION message |Request supported protocol versions by all nodes on the network (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Reserved (all remaining params)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES=520, /* Request autopilot capabilities. The receiver should ACK the command and then emit its capabilities in an AUTOPILOT_VERSION message |Request autopilot version (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Reserved (all remaining params)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_REQUEST_CAMERA_INFORMATION=521, /* Request camera information (CAMERA_INFORMATION). |Request camera capabilities (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Reserved (all remaining params)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_REQUEST_CAMERA_SETTINGS=522, /* Request camera settings (CAMERA_SETTINGS). |Request camera settings (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Reserved (all remaining params)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_REQUEST_STORAGE_INFORMATION=525, /* Request storage information (STORAGE_INFORMATION). Use the command's target_component to target a specific component's storage. |Storage ID (0 for all, 1 for first, 2 for second, etc.)| Request storage information (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Reserved (all remaining params)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_STORAGE_FORMAT=526, /* Format a storage medium. Once format is complete, a STORAGE_INFORMATION message is sent. Use the command's target_component to target a specific component's storage. |Storage ID (1 for first, 2 for second, etc.)| Format storage (and reset image log). Values not equal to 0 or 1 are invalid.| Reset Image Log (without formatting storage medium). This will reset CAMERA_CAPTURE_STATUS.image_count and CAMERA_IMAGE_CAPTURED.image_index. Values not equal to 0 or 1 are invalid.| Reserved (all remaining params)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_REQUEST_CAMERA_CAPTURE_STATUS=527, /* Request camera capture status (CAMERA_CAPTURE_STATUS) |Request camera capture status (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Reserved (all remaining params)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_REQUEST_FLIGHT_INFORMATION=528, /* Request flight information (FLIGHT_INFORMATION) |Request flight information (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Reserved (all remaining params)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_RESET_CAMERA_SETTINGS=529, /* Reset all camera settings to Factory Default |Reset all settings (MAV_BOOL_TRUE). Values not equal to 0 or 1 are invalid.| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SET_CAMERA_MODE=530, /* Set camera running mode. Use NaN for reserved values. GCS will send a MAV_CMD_REQUEST_VIDEO_STREAM_STATUS command after a mode change if the camera supports video streaming. |Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Camera mode| Reserved (default:NaN)| Reserved (default:NaN)| Reserved (default:0)| Reserved (default:0)| Reserved (default:NaN)|  */
   MAV_CMD_SET_CAMERA_ZOOM=531, /* Set camera zoom. Camera must respond with a CAMERA_SETTINGS message (on success). |Zoom type| Zoom value. The range of valid values depend on the zoom type.| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:NaN)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SET_CAMERA_FOCUS=532, /* Set camera focus. Camera must respond with a CAMERA_SETTINGS message (on success). |Focus type| Focus value| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:NaN)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SET_STORAGE_USAGE=533, /* Set that a particular storage is the preferred location for saving photos, videos, and/or other media (e.g. to set that an SD card is used for storing videos).
          There can only be one preferred save location for each particular media type: setting a media usage flag will clear/reset that same flag if set on any other storage.
          If no flag is set the system should use its default storage.
          A target system can choose to always use default storage, in which case it should ACK the command with MAV_RESULT_UNSUPPORTED.
          A target system can choose to not allow a particular storage to be set as preferred storage, in which case it should ACK the command with MAV_RESULT_DENIED. |Storage ID (1 for first, 2 for second, etc.)| Usage flags| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SET_CAMERA_SOURCE=534, /* Set camera source. Changes the camera's active sources on cameras with multiple image sensors. |Component Id of camera to address or 1-6 for non-MAVLink cameras, 0 for all cameras.| Primary Source| Secondary Source. If non-zero the second source will be displayed as picture-in-picture.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_JUMP_TAG=600, /* Tagged jump target. Can be jumped to with MAV_CMD_DO_JUMP_TAG. |Tag.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_DO_JUMP_TAG=601, /* Jump to the matching tag in the mission list. Repeat this action for the specified number of times. A mission should contain a single matching tag for each jump. If this is not the case then a jump to a missing tag should complete the mission, and a jump where there are multiple matching tags should always select the one with the lowest mission sequence number. |Target tag to jump to.| Repeat count.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_DO_SET_GLOBAL_ORIGIN=611, /* Sets the GNSS coordinates of the vehicle local origin (0,0,0) position.
          Vehicle should emit GPS_GLOBAL_ORIGIN irrespective of whether the origin is changed.
          This enables transform between the local coordinate frame and the global (GNSS) coordinate frame, which may be necessary when (for example) indoor and outdoor settings are connected and the MAV should move from in- to outdoor.
          This command supersedes SET_GPS_GLOBAL_ORIGIN.
          Should be sent in a COMMAND_INT (Expected frame is MAV_FRAME_GLOBAL, and this should be assumed when sent in COMMAND_LONG).
         |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Latitude| Longitude| Altitude|  */
   MAV_CMD_DO_GIMBAL_MANAGER_PITCHYAW=1000, /* Set gimbal manager pitch/yaw setpoints (low rate command). It is possible to set combinations of the values below. E.g. an angle as well as a desired angular rate can be used to get to this angle at a certain angular rate, or an angular rate only will result in continuous turning. NaN is to be used to signal unset. Note: only the gimbal manager will react to this command - it will be ignored by a gimbal device. Use GIMBAL_MANAGER_SET_PITCHYAW if you need to stream pitch/yaw setpoints at higher rate.  |Pitch angle (positive to pitch up, relative to vehicle for FOLLOW mode, relative to world horizon for LOCK mode).| Yaw angle (positive to yaw to the right, relative to vehicle for FOLLOW mode, absolute to North for LOCK mode).| Pitch rate (positive to pitch up).| Yaw rate (positive to yaw to the right).| Gimbal manager flags to use.| Reserved (default:0)| Component ID of gimbal device to address (or 1-6 for non-MAVLink gimbal), 0 for all gimbal device components. Send command multiple times for more than one gimbal (but not all gimbals).|  */
   MAV_CMD_DO_GIMBAL_MANAGER_CONFIGURE=1001, /* Gimbal configuration to set which sysid/compid is in primary and secondary control. |Sysid for primary control (0: no one in control, -1: leave unchanged, -2: set itself in control (for missions where the own sysid is still unknown), -3: remove control if currently in control).| Compid for primary control (0: no one in control, -1: leave unchanged, -2: set itself in control (for missions where the own sysid is still unknown), -3: remove control if currently in control).| Sysid for secondary control (0: no one in control, -1: leave unchanged, -2: set itself in control (for missions where the own sysid is still unknown), -3: remove control if currently in control).| Compid for secondary control (0: no one in control, -1: leave unchanged, -2: set itself in control (for missions where the own sysid is still unknown), -3: remove control if currently in control).| Reserved (default:0)| Reserved (default:0)| Component ID of gimbal device to address (or 1-6 for non-MAVLink gimbal), 0 for all gimbal device components. Send command multiple times for more than one gimbal (but not all gimbals).|  */
   MAV_CMD_IMAGE_START_CAPTURE=2000, /* Start image capture sequence. CAMERA_IMAGE_CAPTURED must be emitted after each capture.

          Param1 (id) may be used to specify the target camera: 0: all cameras, 1 to 6: autopilot-connected cameras, 7-255: MAVLink camera component ID.
          It is needed in order to target specific cameras connected to the autopilot, or specific sensors in a multi-sensor camera (neither of which have a distinct MAVLink component ID).
          It is also needed to specify the target camera in missions.

          When used in a mission, an autopilot should execute the MAV_CMD for a specified local camera (param1 = 1-6), or resend it as a command if it is intended for a MAVLink camera (param1 = 7 - 255), setting the command's target_component as the param1 value (and setting param1 in the command to zero).
          If the param1 is 0 the autopilot should do both.

          When sent in a command the target MAVLink address is set using target_component.
          If addressed specifically to an autopilot: param1 should be used in the same way as it is for missions (though command should NACK with MAV_RESULT_DENIED if a specified local camera does not exist).
          If addressed to a MAVLink camera, param 1 can be used to address all cameras (0), or to separately address 1 to 7 individual sensors. Other values should be NACKed with MAV_RESULT_DENIED.
          If the command is broadcast (target_component is 0) then param 1 should be set to 0 (any other value should be NACKED with MAV_RESULT_DENIED). An autopilot would trigger any local cameras and forward the command to all channels.
         |Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Desired elapsed time between two consecutive pictures (in seconds). Minimum values depend on hardware (typically greater than 2 seconds).| Total number of images to capture. 0 to capture forever/until MAV_CMD_IMAGE_STOP_CAPTURE.| Capture sequence number starting from 1. This is only valid for single-capture (param3 == 1), otherwise set to 0. Increment the capture ID for each capture command to prevent double captures when a command is re-transmitted.| Reserved (default:0)| Reserved (default:0)| Reserved (default:NaN)|  */
   MAV_CMD_IMAGE_STOP_CAPTURE=2001, /* Stop image capture sequence.

          Param1 (id) may be used to specify the target camera: 0: all cameras, 1 to 6: autopilot-connected cameras, 7-255: MAVLink camera component ID.
          It is needed in order to target specific cameras connected to the autopilot, or specific sensors in a multi-sensor camera (neither of which have a distinct MAVLink component ID).
          It is also needed to specify the target camera in missions.

          When used in a mission, an autopilot should execute the MAV_CMD for a specified local camera (param1 = 1-6), or resend it as a command if it is intended for a MAVLink camera (param1 = 7 - 255), setting the command's target_component as the param1 value (and setting param1 in the command to zero).
          If the param1 is 0 the autopilot should do both.

          When sent in a command the target MAVLink address is set using target_component.
          If addressed specifically to an autopilot: param1 should be used in the same way as it is for missions (though command should NACK with MAV_RESULT_DENIED if a specified local camera does not exist).
          If addressed to a MAVLink camera, param1 can be used to address all cameras (0), or to separately address 1 to 7 individual sensors. Other values should be NACKed with MAV_RESULT_DENIED.
          If the command is broadcast (target_component is 0) then param 1 should be set to 0 (any other value should be NACKED with MAV_RESULT_DENIED). An autopilot would trigger any local cameras and forward the command to all channels.
         |Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:NaN)| Reserved (default:NaN)| Reserved (default:NaN)| Reserved (default:0)| Reserved (default:0)| Reserved (default:NaN)|  */
   MAV_CMD_REQUEST_CAMERA_IMAGE_CAPTURE=2002, /* Re-request a CAMERA_IMAGE_CAPTURED message. |Sequence number for missing CAMERA_IMAGE_CAPTURED message| Reserved (default:NaN)| Reserved (default:NaN)| Reserved (default:NaN)| Reserved (default:0)| Reserved (default:0)| Reserved (default:NaN)|  */
   MAV_CMD_DO_TRIGGER_CONTROL=2003, /* Enable or disable on-board camera triggering system. |Trigger enable/disable (0 for disable, 1 for start), -1 to ignore| 1 to reset the trigger sequence, -1 or 0 to ignore| 1 to pause triggering, but without switching the camera off or retracting it. -1 to ignore| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_CAMERA_TRACK_POINT=2004, /* If the camera supports point visual tracking (CAMERA_CAP_FLAGS_HAS_TRACKING_POINT is set), this command allows to initiate the tracking. |Point to track x value (normalized 0..1, 0 is left, 1 is right).| Point to track y value (normalized 0..1, 0 is top, 1 is bottom).| Point radius (normalized 0..1, 0 is one pixel, 1 is full image width).| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_CAMERA_TRACK_RECTANGLE=2005, /* If the camera supports rectangle visual tracking (CAMERA_CAP_FLAGS_HAS_TRACKING_RECTANGLE is set), this command allows to initiate the tracking. |Top left corner of rectangle x value (normalized 0..1, 0 is left, 1 is right).| Top left corner of rectangle y value (normalized 0..1, 0 is top, 1 is bottom).| Bottom right corner of rectangle x value (normalized 0..1, 0 is left, 1 is right).| Bottom right corner of rectangle y value (normalized 0..1, 0 is top, 1 is bottom).| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_CAMERA_STOP_TRACKING=2010, /* Stops ongoing tracking. |Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_VIDEO_START_CAPTURE=2500, /* Starts video capture (recording). |Video Stream ID (0 for all streams)| Frequency CAMERA_CAPTURE_STATUS messages should be sent while recording (0 for no messages, otherwise frequency)| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:NaN)| Reserved (default:0)| Reserved (default:0)| Reserved (default:NaN)|  */
   MAV_CMD_VIDEO_STOP_CAPTURE=2501, /* Stop the current video capture (recording). |Video Stream ID (0 for all streams)| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:NaN)| Reserved (default:NaN)| Reserved (default:0)| Reserved (default:0)| Reserved (default:NaN)|  */
   MAV_CMD_VIDEO_START_STREAMING=2502, /* Start video streaming |Video Stream ID (0 for all streams, 1 for first, 2 for second, etc.)| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_VIDEO_STOP_STREAMING=2503, /* Stop the given video stream |Video Stream ID (0 for all streams, 1 for first, 2 for second, etc.)| Target camera ID. 7 to 255: MAVLink camera component id. 1 to 6 for cameras attached to the autopilot, which don't have a distinct component id. 0: all cameras. This is used to target specific autopilot-connected cameras. It is also used to target specific cameras when the MAV_CMD is used in a mission.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_REQUEST_VIDEO_STREAM_INFORMATION=2504, /* Request video stream information (VIDEO_STREAM_INFORMATION) |Video Stream ID (0 for all streams, 1 for first, 2 for second, etc.)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_REQUEST_VIDEO_STREAM_STATUS=2505, /* Request video stream status (VIDEO_STREAM_STATUS) |Video Stream ID (0 for all streams, 1 for first, 2 for second, etc.)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_LOGGING_START=2510, /* Request to start streaming logging data over MAVLink (see also LOGGING_DATA message) |Format: 0: ULog| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)|  */
   MAV_CMD_LOGGING_STOP=2511, /* Request to stop streaming log data over MAVLink |Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)|  */
   MAV_CMD_AIRFRAME_CONFIGURATION=2520, /*  |Landing gear ID (default: 0, -1 for all)| Landing gear position (Down: 0, Up: 1, NaN for no change)| Reserved (default:NaN)| Reserved (default:NaN)| Reserved (default:0)| Reserved (default:0)| Reserved (default:NaN)|  */
   MAV_CMD_CONTROL_HIGH_LATENCY=2600, /* Request to start/stop transmitting over the high latency telemetry |Start transmission over high latency telemetry (MAV_BOOL_FALSE: stop transmission). Values not equal to 0 or 1 are invalid.| Empty| Empty| Empty| Empty| Empty| Empty|  */
   MAV_CMD_PANORAMA_CREATE=2800, /* Create a panorama at the current position |Viewing angle horizontal of the panorama (+- 0.5 the total angle)| Viewing angle vertical of panorama.| Speed of the horizontal rotation.| Speed of the vertical rotation.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_DO_VTOL_TRANSITION=3000, /* Request VTOL transition |The target VTOL state. For normal transitions, only MAV_VTOL_STATE_MC and MAV_VTOL_STATE_FW can be used.| Force immediate transition to the specified MAV_VTOL_STATE. 1: Force immediate, 0: normal transition. Can be used, for example, to trigger an emergency "Quadchute". Caution: Can be dangerous/damage vehicle, depending on autopilot implementation of this command.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_ARM_AUTHORIZATION_REQUEST=3001, /* Request authorization to arm the vehicle to a external entity, the arm authorizer is responsible to request all data that is needs from the vehicle before authorize or deny the request.
		If approved the COMMAND_ACK message progress field should be set with period of time that this authorization is valid in seconds.
		If the authorization is denied COMMAND_ACK.result_param2 should be set with one of the reasons in MAV_ARM_AUTH_DENIED_REASON.
         |Vehicle system id, this way ground station can request arm authorization on behalf of any vehicle| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SET_GUIDED_SUBMODE_STANDARD=4000, /* This command sets the submode to standard guided when vehicle is in guided mode. The vehicle holds position and altitude and the user can input the desired velocities along all three axes.
                   |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SET_GUIDED_SUBMODE_CIRCLE=4001, /* This command sets submode circle when vehicle is in guided mode. Vehicle flies along a circle facing the center of the circle. The user can input the velocity along the circle and change the radius. If no input is given the vehicle will hold position.
                   |Radius of desired circle in CIRCLE_MODE| User defined| User defined| User defined| Target latitude of center of circle in CIRCLE_MODE| Target longitude of center of circle in CIRCLE_MODE| Reserved (default:0)|  */
   MAV_CMD_CONDITION_GATE=4501, /* Delay mission state machine until gate has been reached. |Geometry: 0: orthogonal to path between previous and next waypoint.| Use altitude (MAV_BOOL_FALSE: ignore altitude). Values not equal to 0 or 1 are invalid.| Empty| Empty| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_FENCE_RETURN_POINT=5000, /* Fence return point (there can only be one such point in a geofence definition). If rally points are supported they should be used instead. |Reserved| Reserved| Reserved| Reserved| Latitude| Longitude| Altitude|  */
   MAV_CMD_NAV_FENCE_POLYGON_VERTEX_INCLUSION=5001, /* Fence vertex for an inclusion polygon (the polygon must not be self-intersecting). The vehicle must stay within this area. Minimum of 3 vertices required.
          The vertices for a polygon must be sent sequentially, each with param1 set to the total number of vertices in the polygon.
         |Polygon vertex count. This is the number of vertices in the current polygon (all vertices will have the same number).| Vehicle must be inside ALL inclusion zones in a single group, vehicle must be inside at least one group, must be the same for all points in each polygon| Reserved| Reserved| Latitude| Longitude| Reserved|  */
   MAV_CMD_NAV_FENCE_POLYGON_VERTEX_EXCLUSION=5002, /* Fence vertex for an exclusion polygon (the polygon must not be self-intersecting). The vehicle must stay outside this area. Minimum of 3 vertices required.
          The vertices for a polygon must be sent sequentially, each with param1 set to the total number of vertices in the polygon.
         |Polygon vertex count. This is the number of vertices in the current polygon (all vertices will have the same number).| Reserved| Reserved| Reserved| Latitude| Longitude| Reserved|  */
   MAV_CMD_NAV_FENCE_CIRCLE_INCLUSION=5003, /* Circular fence area. The vehicle must stay inside this area.
         |Radius.| Vehicle must be inside ALL inclusion zones in a single group, vehicle must be inside at least one group| Reserved| Reserved| Latitude| Longitude| Reserved|  */
   MAV_CMD_NAV_FENCE_CIRCLE_EXCLUSION=5004, /* Circular fence area. The vehicle must stay outside this area.
         |Radius.| Reserved| Reserved| Reserved| Latitude| Longitude| Reserved|  */
   MAV_CMD_NAV_RALLY_POINT=5100, /* Rally point. You can have multiple rally points defined.
         |Reserved| Reserved| Reserved| Reserved| Latitude| Longitude| Altitude|  */
   MAV_CMD_UAVCAN_GET_NODE_INFO=5200, /* Commands the vehicle to respond with a sequence of messages UAVCAN_NODE_INFO, one message per every UAVCAN node that is online. Note that some of the response messages can be lost, which the receiver can detect easily by checking whether every received UAVCAN_NODE_STATUS has a matching message UAVCAN_NODE_INFO received earlier; if not, this command should be sent again in order to request re-transmission of the node information messages. |Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)|  */
   MAV_CMD_DO_SET_SAFETY_SWITCH_STATE=5300, /* Change state of safety switch. |New safety switch state.| Empty.| Empty.| Empty| Empty.| Empty.| Empty.|  */
   MAV_CMD_DO_ADSB_OUT_IDENT=10001, /* Trigger the start of an ADSB-out IDENT. This should only be used when requested to do so by an Air Traffic Controller in controlled airspace. This starts the IDENT which is then typically held for 18 seconds by the hardware per the Mode A, C, and S transponder spec. |Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)| Reserved (set to 0)|  */
   MAV_CMD_PAYLOAD_PREPARE_DEPLOY=30001, /* Deploy payload on a Lat / Lon / Alt position. This includes the navigation to reach the required release position and velocity. |Operation mode. 0: prepare single payload deploy (overwriting previous requests), but do not execute it. 1: execute payload deploy immediately (rejecting further deploy commands during execution, but allowing abort). 2: add payload deploy to existing deployment list.| Desired approach vector in compass heading. A negative value indicates the system can define the approach vector at will.| Desired ground speed at release time. This can be overridden by the airframe in case it needs to meet minimum airspeed. A negative value indicates the system can define the ground speed at will.| Minimum altitude clearance to the release position. A negative value indicates the system can define the clearance at will.| Latitude.| Longitude.| Altitude (MSL)|  */
   MAV_CMD_PAYLOAD_CONTROL_DEPLOY=30002, /* Control the payload deployment. |Operation mode. 0: Abort deployment, continue normal mission. 1: switch to payload deployment mode. 100: delete first payload deployment request. 101: delete all payload deployment requests.| Reserved| Reserved| Reserved| Reserved| Reserved| Reserved|  */
   MAV_CMD_WAYPOINT_USER_1=31000, /* User defined waypoint item. Ground Station will show the Vehicle as flying through this item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_WAYPOINT_USER_2=31001, /* User defined waypoint item. Ground Station will show the Vehicle as flying through this item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_WAYPOINT_USER_3=31002, /* User defined waypoint item. Ground Station will show the Vehicle as flying through this item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_WAYPOINT_USER_4=31003, /* User defined waypoint item. Ground Station will show the Vehicle as flying through this item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_WAYPOINT_USER_5=31004, /* User defined waypoint item. Ground Station will show the Vehicle as flying through this item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_SPATIAL_USER_1=31005, /* User defined spatial item. Ground Station will not show the Vehicle as flying through this item. Example: ROI item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_SPATIAL_USER_2=31006, /* User defined spatial item. Ground Station will not show the Vehicle as flying through this item. Example: ROI item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_SPATIAL_USER_3=31007, /* User defined spatial item. Ground Station will not show the Vehicle as flying through this item. Example: ROI item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_SPATIAL_USER_4=31008, /* User defined spatial item. Ground Station will not show the Vehicle as flying through this item. Example: ROI item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_SPATIAL_USER_5=31009, /* User defined spatial item. Ground Station will not show the Vehicle as flying through this item. Example: ROI item. |User defined| User defined| User defined| User defined| Latitude unscaled| Longitude unscaled| Altitude (MSL)|  */
   MAV_CMD_USER_1=31010, /* User defined command. Ground Station will not show the Vehicle as flying through this item. Example: MAV_CMD_DO_SET_PARAMETER item. |User defined| User defined| User defined| User defined| User defined| User defined| User defined|  */
   MAV_CMD_USER_2=31011, /* User defined command. Ground Station will not show the Vehicle as flying through this item. Example: MAV_CMD_DO_SET_PARAMETER item. |User defined| User defined| User defined| User defined| User defined| User defined| User defined|  */
   MAV_CMD_USER_3=31012, /* User defined command. Ground Station will not show the Vehicle as flying through this item. Example: MAV_CMD_DO_SET_PARAMETER item. |User defined| User defined| User defined| User defined| User defined| User defined| User defined|  */
   MAV_CMD_USER_4=31013, /* User defined command. Ground Station will not show the Vehicle as flying through this item. Example: MAV_CMD_DO_SET_PARAMETER item. |User defined| User defined| User defined| User defined| User defined| User defined| User defined|  */
   MAV_CMD_USER_5=31014, /* User defined command. Ground Station will not show the Vehicle as flying through this item. Example: MAV_CMD_DO_SET_PARAMETER item. |User defined| User defined| User defined| User defined| User defined| User defined| User defined|  */
   MAV_CMD_CAN_FORWARD=32000, /* Request forwarding of CAN packets from the given CAN bus to this component via this MAVLink channel. CAN Frames are sent using CAN_FRAME and CANFD_FRAME messages |Bus number (0 to disable forwarding, 1 for first bus, 2 for 2nd bus, 3 for 3rd bus).| Empty.| Empty.| Empty.| Empty.| Empty.| Empty.|  */
   MAV_CMD_FIXED_MAG_CAL_YAW=42006, /* Magnetometer calibration based on provided known yaw. This allows for fast calibration using WMM field tables in the vehicle, given only the known yaw of the vehicle. If Latitude and longitude are both zero then use the current vehicle location. |Yaw of vehicle in earth frame.| CompassMask, 0 for all.| Latitude.| Longitude.| Empty.| Empty.| Empty.|  */
   MAV_CMD_DO_WINCH=42600, /* Command to operate winch. |Winch instance number.| Action to perform.| Length of line to release (negative to wind).| Release rate (negative to wind).| Empty.| Empty.| Empty.|  */
   MAV_CMD_GUIDED_CHANGE_SPEED=43000, /* Change flight speed at a given rate. This slews the vehicle at a controllable rate between it's previous speed and the new one. |Airspeed or groundspeed.| Target Speed| Acceleration rate, 0 to take effect instantly| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_GUIDED_CHANGE_ALTITUDE=43001, /* Change target altitude at a given rate. This slews the vehicle at a controllable rate between it's previous altitude and the new one. |Reserved (default:0)| Reserved (default:0)| Rate of change, toward new altitude. 0 for maximum rate change. Positive numbers only, as negative numbers will not converge on the new target alt.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Target Altitude|  */
   MAV_CMD_GUIDED_CHANGE_HEADING=43002, /* Change to target direction at a given rate, overriding previous heading/s. This slews the vehicle at a controllable rate between its previous heading and the new one. |Course-over-ground or raw vehicle heading.| Target heading.| Maximum centripetal acceleration, i.e. rate of change toward new heading.| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_EXTERNAL_POSITION_ESTIMATE=43003, /* Provide an external position estimate for use when dead-reckoning. This is meant to be used for occasional position resets that may be provided by a external system such as a remote pilot using landmarks over a video link. |Timestamp that this message was sent as a time in the transmitters time domain. The sender should wrap this time back to zero based on required timing accuracy for the application and the limitations of a 32 bit float. For example, wrapping at 10 hours would give approximately 1ms accuracy. Recipient must handle time wrap in any timing jitter correction applied to this field. Wrap rollover time should not be at not more than 250 seconds, which would give approximately 10 microsecond accuracy.| The time spent in processing the sensor data that is the basis for this position. The recipient can use this to improve time alignment of the data. Set to zero if not known.| estimated one standard deviation accuracy of the measurement. Set to NaN if not known.| Empty| Latitude| Longitude| Altitude, not used. Should be sent as NaN. May be supported in a future version of this message.|  */
   MAV_CMD_MAVLINK_M_STORE_ARM=53090, /* Arm or safe a store's ESAD. |Target store instance (0 = all stores / broadcast).| 0 = safe/disarm, 1 = arm.| Arming challenge hash; must match the store's last ESAD_STATE hash.| Reserved (0).| Reserved (0).| Reserved (0).| Reserved (0).|  */
   MAV_CMD_MAVLINK_M_STORE_RUN_BIT=53091, /* Run a built-in self-test (BIT) on a store. |Target store instance (0 = all stores / broadcast).| 0 = full BIT, 1 = sensors only, 2 = ESAD only.| Reserved (0).| Reserved (0).| Reserved (0).| Reserved (0).| Reserved (0).|  */
   MAV_CMD_MAVLINK_M_STORE_REQUEST_STATUS=53092, /* Request status push from a store. |Target store instance (0 = all stores / broadcast).| 0 = STORE_STATUS only, 1 = all STORE_SENSOR_STATUS, 2 = both.| Reserved (0).| Reserved (0).| Reserved (0).| Reserved (0).| Reserved (0).|  */
   MAV_CMD_MAVLINK_M_STORE_SET_DECEL_THRESHOLD=53093, /* Set the deceleration/landing-system trigger threshold for a store. |Target store instance (0 = all stores / broadcast).| Sensor (MAVLINK_M_STORE_SENSOR_TYPE) that gates deployment.| Threshold value in the sensor's native units.| 0 = trigger when reading falls below threshold, 1 = trigger when reading rises above threshold.| Reserved (0).| Reserved (0).| Reserved (0).|  */
   MAV_CMD_ENUM_END=53094, /*  | */
} MAV_CMD;
#endif

/** @brief Warning-order mission type for a call for fire (ATP 3-09.30 Ch.4). Descriptive intent. */
#ifndef HAVE_ENUM_MAVLINK_M_MISSION_TYPE
#define HAVE_ENUM_MAVLINK_M_MISSION_TYPE
typedef enum MAVLINK_M_MISSION_TYPE
{
   MAVLINK_M_MISSION_TYPE_UNSPECIFIED=0, /* Not specified (default for an unset field). | */
   MAVLINK_M_MISSION_TYPE_ADJUST_FIRE=1, /* Adjust fire. | */
   MAVLINK_M_MISSION_TYPE_FIRE_FOR_EFFECT=2, /* Fire for effect. | */
   MAVLINK_M_MISSION_TYPE_SUPPRESSION=3, /* Suppression. | */
   MAVLINK_M_MISSION_TYPE_IMMEDIATE_SUPPRESSION=4, /* Immediate suppression. | */
   MAVLINK_M_MISSION_TYPE_IMMEDIATE_SMOKE=5, /* Immediate smoke. | */
   MAVLINK_M_MISSION_TYPE_SEAD=6, /* Suppression of enemy air defenses. | */
   MAVLINK_M_MISSION_TYPE_REGISTRATION=7, /* Registration. | */
   MAVLINK_M_MISSION_TYPE_DESTRUCTION=8, /* Destruction. | */
   MAVLINK_M_MISSION_TYPE_ENUM_END=9, /*  | */
} MAVLINK_M_MISSION_TYPE;
#endif

/** @brief Method of target location for a call for fire (ATP 3-09.30 Ch.4). */
#ifndef HAVE_ENUM_MAVLINK_M_TARGET_LOCATION_METHOD
#define HAVE_ENUM_MAVLINK_M_TARGET_LOCATION_METHOD
typedef enum MAVLINK_M_TARGET_LOCATION_METHOD
{
   MAVLINK_M_TGT_LOC_UNSPECIFIED=0, /* Not specified (default for an unset field). | */
   MAVLINK_M_TGT_LOC_GRID=1, /* Grid. | */
   MAVLINK_M_TGT_LOC_POLAR=2, /* Polar (from observer). | */
   MAVLINK_M_TGT_LOC_SHIFT_KNOWN_POINT=3, /* Shift from a known point. | */
   MAVLINK_M_TGT_LOC_LASER_GRID=4, /* Laser-derived grid. | */
   MAVLINK_M_TGT_LOC_LASER_POLAR=5, /* Laser-derived polar. | */
   MAVLINK_M_TARGET_LOCATION_METHOD_ENUM_END=6, /*  | */
} MAVLINK_M_TARGET_LOCATION_METHOD;
#endif

/** @brief Type of adjustment (method of engagement). */
#ifndef HAVE_ENUM_MAVLINK_M_ADJUSTMENT_TYPE
#define HAVE_ENUM_MAVLINK_M_ADJUSTMENT_TYPE
typedef enum MAVLINK_M_ADJUSTMENT_TYPE
{
   MAVLINK_M_ADJUSTMENT_UNSPECIFIED=0, /* Not specified (default for an unset field). | */
   MAVLINK_M_ADJUSTMENT_AREA=1, /* Area adjustment. | */
   MAVLINK_M_ADJUSTMENT_PRECISION=2, /* Precision adjustment. | */
   MAVLINK_M_ADJUSTMENT_TYPE_ENUM_END=3, /*  | */
} MAVLINK_M_ADJUSTMENT_TYPE;
#endif

/** @brief Requested trajectory (method of engagement). */
#ifndef HAVE_ENUM_MAVLINK_M_TRAJECTORY
#define HAVE_ENUM_MAVLINK_M_TRAJECTORY
typedef enum MAVLINK_M_TRAJECTORY
{
   MAVLINK_M_TRAJECTORY_UNSPECIFIED=0, /* Not specified (default for an unset field). | */
   MAVLINK_M_TRAJECTORY_LOW_ANGLE=1, /* Low angle. | */
   MAVLINK_M_TRAJECTORY_HIGH_ANGLE=2, /* High angle. | */
   MAVLINK_M_TRAJECTORY_ENUM_END=3, /*  | */
} MAVLINK_M_TRAJECTORY;
#endif

/** @brief Distribution / sheaf for the fire-for-effect pattern (method of engagement). */
#ifndef HAVE_ENUM_MAVLINK_M_SHEAF
#define HAVE_ENUM_MAVLINK_M_SHEAF
typedef enum MAVLINK_M_SHEAF
{
   MAVLINK_M_SHEAF_UNSPECIFIED=0, /* Not specified (default for an unset field). | */
   MAVLINK_M_SHEAF_CONVERGED=1, /* Converged sheaf. | */
   MAVLINK_M_SHEAF_OPEN=2, /* Open sheaf. | */
   MAVLINK_M_SHEAF_PARALLEL=3, /* Parallel sheaf. | */
   MAVLINK_M_SHEAF_SPECIAL=4, /* Special sheaf (linear target; length/width/attitude specified separately). | */
   MAVLINK_M_SHEAF_ENUM_END=5, /*  | */
} MAVLINK_M_SHEAF;
#endif

/** @brief Method of fire and control (ATP 3-09.30 Ch.4). */
#ifndef HAVE_ENUM_MAVLINK_M_FIRE_CONTROL_METHOD
#define HAVE_ENUM_MAVLINK_M_FIRE_CONTROL_METHOD
typedef enum MAVLINK_M_FIRE_CONTROL_METHOD
{
   MAVLINK_M_FCM_UNSPECIFIED=0, /* Not specified (default for an unset field). | */
   MAVLINK_M_FCM_WHEN_READY=1, /* When ready. | */
   MAVLINK_M_FCM_AT_MY_COMMAND=2, /* At my command (AMC). | */
   MAVLINK_M_FCM_TIME_ON_TARGET=3, /* Time on target (TOT). | */
   MAVLINK_M_FCM_CANNOT_OBSERVE=4, /* Cannot observe. | */
   MAVLINK_M_FCM_CONTINUOUS_ILLUM=5, /* Continuous illumination. | */
   MAVLINK_M_FCM_COORDINATED_ILLUM=6, /* Coordinated illumination. | */
   MAVLINK_M_FCM_CONTINUOUS_FIRE=7, /* Continuous fire. | */
   MAVLINK_M_FIRE_CONTROL_METHOD_ENUM_END=8, /*  | */
} MAVLINK_M_FIRE_CONTROL_METHOD;
#endif

/** @brief 
        Target-location-error CATEGORY LABEL only (ATP 3-09.30 Fig.3-14).
        The category band label is Distribution A; the underlying CEP/performance
        figure is NOT carried.
       */
#ifndef HAVE_ENUM_MAVLINK_M_TLE_CATEGORY
#define HAVE_ENUM_MAVLINK_M_TLE_CATEGORY
typedef enum MAVLINK_M_TLE_CATEGORY
{
   MAVLINK_M_TLE_UNKNOWN=0, /* TLE not established. | */
   MAVLINK_M_TLE_CAT_I=1, /* Category I (highest accuracy band). | */
   MAVLINK_M_TLE_CAT_II=2, /* Category II. | */
   MAVLINK_M_TLE_CAT_III=3, /* Category III. | */
   MAVLINK_M_TLE_CAT_IV=4, /* Category IV. | */
   MAVLINK_M_TLE_CATEGORY_ENUM_END=5, /*  | */
} MAVLINK_M_TLE_CATEGORY;
#endif

/** @brief 
        Collateral-damage-estimation LEVEL NUMBER only (CJCSI 3160.01 series).
        Carries the level as a status value; NEVER the underlying CDE computation
        or population data.
       */
#ifndef HAVE_ENUM_MAVLINK_M_CDE_LEVEL
#define HAVE_ENUM_MAVLINK_M_CDE_LEVEL
typedef enum MAVLINK_M_CDE_LEVEL
{
   MAVLINK_M_CDE_LEVEL_NONE=0, /* No CDE recorded. | */
   MAVLINK_M_CDE_LEVEL_1=1, /* Level 1 - target validation / initial assessment. | */
   MAVLINK_M_CDE_LEVEL_2=2, /* Level 2 - general / target-size assessment. | */
   MAVLINK_M_CDE_LEVEL_3=3, /* Level 3 - weaponeering assessment. | */
   MAVLINK_M_CDE_LEVEL_4=4, /* Level 4 - refined assessment. | */
   MAVLINK_M_CDE_LEVEL_5=5, /* Level 5 - casualty assessment. | */
   MAVLINK_M_CDE_LEVEL_ENUM_END=6, /*  | */
} MAVLINK_M_CDE_LEVEL;
#endif

/** @brief No-strike / restricted-target context flags. Status flags only. */
#ifndef HAVE_ENUM_MAVLINK_M_RESTRICTED_TARGET_FLAGS
#define HAVE_ENUM_MAVLINK_M_RESTRICTED_TARGET_FLAGS
typedef enum MAVLINK_M_RESTRICTED_TARGET_FLAGS
{
   MAVLINK_M_RTL_NO_STRIKE_LIST=1, /* On the No-Strike List. | */
   MAVLINK_M_RTL_RESTRICTED_TARGET=2, /* On the Restricted Target List. | */
   MAVLINK_M_RTL_NO_FIRE_AREA=4, /* Within a No-Fire Area. | */
   MAVLINK_M_RESTRICTED_TARGET_FLAGS_ENUM_END=5, /*  | */
} MAVLINK_M_RESTRICTED_TARGET_FLAGS;
#endif

/** @brief 
        How a desired-mean-point-of-impact reference is expressed. A precise
        mensurated DMPI tied to a weapon solution is treated as controlled and is
        NOT carried here; carry target location + TLE category instead.
       */
#ifndef HAVE_ENUM_MAVLINK_M_DMPI_REFERENCE_KIND
#define HAVE_ENUM_MAVLINK_M_DMPI_REFERENCE_KIND
typedef enum MAVLINK_M_DMPI_REFERENCE_KIND
{
   MAVLINK_M_DMPI_NONE=0, /* No DMPI reference. | */
   MAVLINK_M_DMPI_TARGET_LOCATION=1, /* DMPI = the target location already carried (with TLE category). | */
   MAVLINK_M_DMPI_OFFSET_REF=2, /* DMPI expressed as a labeled offset reference (not a mensurated coordinate). | */
   MAVLINK_M_DMPI_REFERENCE_KIND_ENUM_END=3, /*  | */
} MAVLINK_M_DMPI_REFERENCE_KIND;
#endif

/** @brief 
        OPTIONAL, ADVISORY coarse tier for human display only, derived from the
        raw atr_confidence_pct. It has NO protocol-defined probability band and
        MUST NOT be used as an automated rules-of-engagement input; the raw score
        + model id are the authoritative fields and the C2 node owns the
        threshold policy.
       */
#ifndef HAVE_ENUM_MAVLINK_M_ATR_CONFIDENCE
#define HAVE_ENUM_MAVLINK_M_ATR_CONFIDENCE
typedef enum MAVLINK_M_ATR_CONFIDENCE
{
   MAVLINK_M_ATR_CONF_NA=0, /* Not an ATR identification / not applicable. | */
   MAVLINK_M_ATR_CONF_LOW=1, /* Advisory display tier: low. No protocol-defined band. | */
   MAVLINK_M_ATR_CONF_MEDIUM=2, /* Advisory display tier: medium. No protocol-defined band. | */
   MAVLINK_M_ATR_CONF_HIGH=3, /* Advisory display tier: high. No protocol-defined band. | */
   MAVLINK_M_ATR_CONFIDENCE_ENUM_END=4, /*  | */
} MAVLINK_M_ATR_CONFIDENCE;
#endif

/** @brief 
        Man-in-the-loop consent-to-strike state for a loitering munition / OWA UAS.
        HUMAN-IN-THE-LOOP INSTRUMENT: this records a human consent decision and its
        withdrawal. It MUST NOT be used to construct an automated release path;
        release authority remains with the crewed C2 system, and consent is a
        precondition recorded for accountability, not a trigger.
       */
#ifndef HAVE_ENUM_MAVLINK_M_LM_CONSENT_STATE
#define HAVE_ENUM_MAVLINK_M_LM_CONSENT_STATE
typedef enum MAVLINK_M_LM_CONSENT_STATE
{
   MAVLINK_M_LM_CONSENT_NONE=0, /* No consent state. | */
   MAVLINK_M_LM_CONSENT_REQUESTED=1, /* Consent-to-strike requested from human authority. | */
   MAVLINK_M_LM_CONSENT_GRANTED=2, /* Consent granted by human authority (recorded). | */
   MAVLINK_M_LM_CONSENT_WITHHELD=3, /* Consent withheld. | */
   MAVLINK_M_LM_CONSENT_WITHDRAWN=4, /* Previously-granted consent withdrawn. | */
   MAVLINK_M_LM_CONSENT_STATE_ENUM_END=5, /*  | */
} MAVLINK_M_LM_CONSENT_STATE;
#endif

/** @brief Loitering-munition abort / terminate action. */
#ifndef HAVE_ENUM_MAVLINK_M_LM_TERMINATE
#define HAVE_ENUM_MAVLINK_M_LM_TERMINATE
typedef enum MAVLINK_M_LM_TERMINATE
{
   MAVLINK_M_LM_TERMINATE_NONE=0, /* No action. | */
   MAVLINK_M_LM_TERMINATE_WAVE_OFF=1, /* Wave off / break engagement, remain flyable. | */
   MAVLINK_M_LM_TERMINATE_ABORT=2, /* Abort current attack, return to loiter. | */
   MAVLINK_M_LM_TERMINATE_SELF_DESTRUCT=3, /* Self-destruct / render safe (per platform capability). | */
   MAVLINK_M_LM_TERMINATE_ENUM_END=4, /*  | */
} MAVLINK_M_LM_TERMINATE;
#endif

/** @brief Time-sensitive-target prosecution status. */
#ifndef HAVE_ENUM_MAVLINK_M_TST_STATUS
#define HAVE_ENUM_MAVLINK_M_TST_STATUS
typedef enum MAVLINK_M_TST_STATUS
{
   MAVLINK_M_TST_NONE=0, /* Not a TST / no status. | */
   MAVLINK_M_TST_NOMINATED=1, /* Nominated as TST. | */
   MAVLINK_M_TST_PROSECUTING=2, /* Under prosecution. | */
   MAVLINK_M_TST_COMPLETE=3, /* Prosecution complete. | */
   MAVLINK_M_TST_STATUS_ENUM_END=4, /*  | */
} MAVLINK_M_TST_STATUS;
#endif

/** @brief Munition family (composite munition, part 1 of 3). Descriptive class names, all Distribution-A doctrine. */
#ifndef HAVE_ENUM_MAVLINK_M_MUNITION_FAMILY
#define HAVE_ENUM_MAVLINK_M_MUNITION_FAMILY
typedef enum MAVLINK_M_MUNITION_FAMILY
{
   MAVLINK_M_MUN_FAM_UNKNOWN=0, /* Unspecified. | */
   MAVLINK_M_MUN_FAM_HE=1, /* High explosive. | */
   MAVLINK_M_MUN_FAM_DPICM=2, /* Dual-purpose ICM (e.g. M483A1). Distinct submunition/dispersion profile from APICM. | */
   MAVLINK_M_MUN_FAM_APICM=3, /* Antipersonnel ICM (e.g. M449 family). Distinct dispersion from DPICM. | */
   MAVLINK_M_MUN_FAM_SMOKE=4, /* Smoke (WP/HC/base-eject). | */
   MAVLINK_M_MUN_FAM_ILLUM=5, /* Illumination (visible/IR). | */
   MAVLINK_M_MUN_FAM_SCATTERABLE_MINE=6, /* Scatterable mine (RAAMS/ADAM); carries SD-duration enum, not exact seconds. | */
   MAVLINK_M_MUN_FAM_SENSOR_FUZED=7, /* Sensor-fused / top-attack (SADARM, BONUS). Requires aimpoint-offset footprint, not a point coordinate. | */
   MAVLINK_M_MUN_FAM_PRECISION=8, /* Precision/guided conventional (Excalibur). Requires 10-digit grid + TLE minimum. | */
   MAVLINK_M_MUN_FAM_PGK=9, /* Precision guidance kit / APMI. Hybrid HE/PGM; TLE minimum required or reverts ballistic. | */
   MAVLINK_M_MUN_FAM_THERMOBARIC=10, /* Thermobaric / fuel-air explosive. Overpressure-primary; hardened/subterranean targets. | */
   MAVLINK_M_MUN_FAM_ANTIPERSONNEL=11, /* Antipersonnel (APERS/flechette). | */
   MAVLINK_M_MUN_FAM_ROCKET_MISSILE=12, /* Rocket/missile (ATACMS, GMLRS, RAP). | */
   MAVLINK_M_MUN_FAM_LOITERING=13, /* Loitering munition / LMAMS. Platform becomes terminal-guidance/relay, not passive observer. | */
   MAVLINK_M_MUNITION_FAMILY_ENUM_END=14, /*  | */
} MAVLINK_M_MUNITION_FAMILY;
#endif

/** @brief Munition payload (composite munition, part 3 of 3). */
#ifndef HAVE_ENUM_MAVLINK_M_MUNITION_PAYLOAD
#define HAVE_ENUM_MAVLINK_M_MUNITION_PAYLOAD
typedef enum MAVLINK_M_MUNITION_PAYLOAD
{
   MAVLINK_M_MUN_PAY_UNKNOWN=0, /* Unspecified. | */
   MAVLINK_M_MUN_PAY_HE_FRAG=1, /* HE / fragmentation. | */
   MAVLINK_M_MUN_PAY_HEAT=2, /* Shaped charge / HEAT. | */
   MAVLINK_M_MUN_PAY_WP=3, /* White phosphorus. | */
   MAVLINK_M_MUN_PAY_HC_SMOKE=4, /* HC smoke. | */
   MAVLINK_M_MUN_PAY_ILLUM=5, /* Illuminant. | */
   MAVLINK_M_MUN_PAY_SUBMUNITION=6, /* Submunitions. | */
   MAVLINK_M_MUN_PAY_MINE=7, /* Mine payload. | */
   MAVLINK_M_MUNITION_PAYLOAD_ENUM_END=8, /*  | */
} MAVLINK_M_MUNITION_PAYLOAD;
#endif

/** @brief 
        Coarse selectable warhead MODE for a multi-mode / selectable warhead
        (e.g. a penetrating warhead with a surface-vs-penetrate selection on a
        multi-drop magazine). Reports/sets the coarse mode only. This is a
        SAFE/ARM-adjacent coarse selection, NOT a fuze timing channel: it must
        never be widened to carry an inter-stage delay or any timing value. The
        actual timing (e.g. secondary-charge delay) is device-internal and is
        configured on the component bus (DroneCAN or vendor structure) below the
        FMU, never on this dialect.
       */
#ifndef HAVE_ENUM_MAVLINK_M_WARHEAD_MODE
#define HAVE_ENUM_MAVLINK_M_WARHEAD_MODE
typedef enum MAVLINK_M_WARHEAD_MODE
{
   MAVLINK_M_WARHEAD_MODE_UNSPECIFIED=0, /* Not specified / not a selectable warhead. | */
   MAVLINK_M_WARHEAD_MODE_SURFACE=1, /* Surface / point-detonating effect selected. | */
   MAVLINK_M_WARHEAD_MODE_PENETRATE=2, /* Penetrating effect selected. | */
   MAVLINK_M_WARHEAD_MODE_AIRBURST=3, /* Airburst / height-of-burst effect selected (coarse selection; no HOB value carried). | */
   MAVLINK_M_WARHEAD_MODE_ENUM_END=4, /*  | */
} MAVLINK_M_WARHEAD_MODE;
#endif

/** @brief Scatterable-mine self-destruct duration CATEGORY (not exact seconds). */
#ifndef HAVE_ENUM_MAVLINK_M_SD_DURATION
#define HAVE_ENUM_MAVLINK_M_SD_DURATION
typedef enum MAVLINK_M_SD_DURATION
{
   MAVLINK_M_SD_NA=0, /* Not applicable. | */
   MAVLINK_M_SD_SHORT=1, /* Short self-destruct duration. | */
   MAVLINK_M_SD_LONG=2, /* Long self-destruct duration. | */
   MAVLINK_M_SD_DURATION_ENUM_END=3, /*  | */
} MAVLINK_M_SD_DURATION;
#endif

/** @brief 
        Mission-effect task verb (FM 3-09 / ATP 3-60), SEPARATE from burst geometry.
        The verb is descriptive tasking intent. The doctrinal casualty-percentage
        definitions are NOT carried on the wire (they drift from tasking intent to
        effects computation).
       */
#ifndef HAVE_ENUM_MAVLINK_M_EFFECT_VERB
#define HAVE_ENUM_MAVLINK_M_EFFECT_VERB
typedef enum MAVLINK_M_EFFECT_VERB
{
   MAVLINK_M_EFFECT_UNSPECIFIED=0, /* Unspecified. | */
   MAVLINK_M_EFFECT_SUPPRESS=1, /* Suppress. | */
   MAVLINK_M_EFFECT_NEUTRALIZE=2, /* Neutralize. | */
   MAVLINK_M_EFFECT_DESTROY=3, /* Destroy. | */
   MAVLINK_M_EFFECT_HARASS=4, /* Harass. | */
   MAVLINK_M_EFFECT_INTERDICT=5, /* Interdict. | */
   MAVLINK_M_EFFECT_OBSCURE=6, /* Obscure / screen. | */
   MAVLINK_M_EFFECT_ILLUMINATE=7, /* Illuminate. | */
   MAVLINK_M_EFFECT_MARK=8, /* Mark. | */
   MAVLINK_M_EFFECT_SEAD=9, /* Suppression of enemy air defenses. | */
   MAVLINK_M_EFFECT_VERB_ENUM_END=10, /*  | */
} MAVLINK_M_EFFECT_VERB;
#endif

/** @brief Commanded/reported sensor payload mode (UCI-style tasking). */
#ifndef HAVE_ENUM_MAVLINK_M_SENSOR_MODE
#define HAVE_ENUM_MAVLINK_M_SENSOR_MODE
typedef enum MAVLINK_M_SENSOR_MODE
{
   MAVLINK_M_SENSOR_MODE_UNKNOWN=0, /* Unspecified. | */
   MAVLINK_M_SENSOR_MODE_WIDE_AREA_SEARCH=1, /* Wide-area search. | */
   MAVLINK_M_SENSOR_MODE_POINT_TRACK=2, /* Point-target track. | */
   MAVLINK_M_SENSOR_MODE_LASER_DESIGNATE=3, /* Laser designation (code carried as slot elsewhere, not a value). | */
   MAVLINK_M_SENSOR_MODE_LASER_RANGE=4, /* Laser ranging. | */
   MAVLINK_M_SENSOR_MODE_IR_MARK=5, /* IR pointer / mark. | */
   MAVLINK_M_SENSOR_MODE_STANDBY=6, /* Sensor standby / caged. | */
   MAVLINK_M_SENSOR_MODE_ENUM_END=7, /*  | */
} MAVLINK_M_SENSOR_MODE;
#endif

/** @brief Response to an inbound tasking request (UCI publish/subscribe event). */
#ifndef HAVE_ENUM_MAVLINK_M_TASKING_STATUS
#define HAVE_ENUM_MAVLINK_M_TASKING_STATUS
typedef enum MAVLINK_M_TASKING_STATUS
{
   MAVLINK_M_TASKING_UNSPECIFIED=0, /* Not specified (default for an unset field). Not an acceptance. | */
   MAVLINK_M_TASKING_ACK=1, /* Tasking accepted. | */
   MAVLINK_M_TASKING_REJECTED=2, /* Tasking rejected (unable/ineligible). | */
   MAVLINK_M_TASKING_COMPLETE=3, /* Tasking complete. | */
   MAVLINK_M_TASKING_ACTIVE=4, /* Tasking in progress. | */
   MAVLINK_M_TASKING_STATUS_ENUM_END=5, /*  | */
} MAVLINK_M_TASKING_STATUS;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 1
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 1
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_target_set_coord.h"
#include "./mavlink_msg_target_box_coord.h"
#include "./mavlink_msg_target.h"
#include "./mavlink_msg_fires.h"
#include "./mavlink_msg_splash_correction.h"
#include "./mavlink_msg_target_handover.h"
#include "./mavlink_msg_battle_damage_assessment.h"
#include "./mavlink_msg_esad_state.h"
#include "./mavlink_msg_esad_arming.h"
#include "./mavlink_msg_esad_config.h"
#include "./mavlink_msg_rws_pose.h"
#include "./mavlink_msg_rws_state.h"
#include "./mavlink_msg_sensor_tasking.h"
#include "./mavlink_msg_cas_9line.h"
#include "./mavlink_msg_terminal_control.h"
#include "./mavlink_msg_target_cue.h"
#include "./mavlink_msg_mavlink_m_ack.h"
#include "./mavlink_msg_store_sensor_status.h"
#include "./mavlink_msg_store_status.h"
#include "./mavlink_msg_track_identity.h"
#include "./mavlink_msg_target_authorization.h"
#include "./mavlink_msg_engagement_directive.h"
#include "./mavlink_msg_call_for_fire.h"
#include "./mavlink_msg_participant_position.h"
#include "./mavlink_msg_store_munition.h"
#include "./mavlink_msg_loiter_munition_control.h"

// base include
#include "../common/common.h"


#if MAVLINK_MILITARY_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_SYS_STATUS, MAVLINK_MESSAGE_INFO_SYSTEM_TIME, MAVLINK_MESSAGE_INFO_PING, MAVLINK_MESSAGE_INFO_CHANGE_OPERATOR_CONTROL, MAVLINK_MESSAGE_INFO_CHANGE_OPERATOR_CONTROL_ACK, MAVLINK_MESSAGE_INFO_AUTH_KEY, MAVLINK_MESSAGE_INFO_LINK_NODE_STATUS, MAVLINK_MESSAGE_INFO_SET_MODE, MAVLINK_MESSAGE_INFO_PARAM_REQUEST_READ, MAVLINK_MESSAGE_INFO_PARAM_REQUEST_LIST, MAVLINK_MESSAGE_INFO_PARAM_VALUE, MAVLINK_MESSAGE_INFO_PARAM_SET, MAVLINK_MESSAGE_INFO_GPS_RAW_INT, MAVLINK_MESSAGE_INFO_GPS_STATUS, MAVLINK_MESSAGE_INFO_SCALED_IMU, MAVLINK_MESSAGE_INFO_RAW_IMU, MAVLINK_MESSAGE_INFO_RAW_PRESSURE, MAVLINK_MESSAGE_INFO_SCALED_PRESSURE, MAVLINK_MESSAGE_INFO_ATTITUDE, MAVLINK_MESSAGE_INFO_ATTITUDE_QUATERNION, MAVLINK_MESSAGE_INFO_LOCAL_POSITION_NED, MAVLINK_MESSAGE_INFO_GLOBAL_POSITION_INT, MAVLINK_MESSAGE_INFO_RC_CHANNELS_SCALED, MAVLINK_MESSAGE_INFO_RC_CHANNELS_RAW, MAVLINK_MESSAGE_INFO_SERVO_OUTPUT_RAW, MAVLINK_MESSAGE_INFO_MISSION_REQUEST_PARTIAL_LIST, MAVLINK_MESSAGE_INFO_MISSION_WRITE_PARTIAL_LIST, MAVLINK_MESSAGE_INFO_MISSION_ITEM, MAVLINK_MESSAGE_INFO_MISSION_REQUEST, MAVLINK_MESSAGE_INFO_MISSION_SET_CURRENT, MAVLINK_MESSAGE_INFO_MISSION_CURRENT, MAVLINK_MESSAGE_INFO_MISSION_REQUEST_LIST, MAVLINK_MESSAGE_INFO_MISSION_COUNT, MAVLINK_MESSAGE_INFO_MISSION_CLEAR_ALL, MAVLINK_MESSAGE_INFO_MISSION_ITEM_REACHED, MAVLINK_MESSAGE_INFO_MISSION_ACK, MAVLINK_MESSAGE_INFO_SET_GPS_GLOBAL_ORIGIN, MAVLINK_MESSAGE_INFO_GPS_GLOBAL_ORIGIN, MAVLINK_MESSAGE_INFO_PARAM_MAP_RC, MAVLINK_MESSAGE_INFO_MISSION_REQUEST_INT, MAVLINK_MESSAGE_INFO_SAFETY_SET_ALLOWED_AREA, MAVLINK_MESSAGE_INFO_SAFETY_ALLOWED_AREA, MAVLINK_MESSAGE_INFO_ATTITUDE_QUATERNION_COV, MAVLINK_MESSAGE_INFO_NAV_CONTROLLER_OUTPUT, MAVLINK_MESSAGE_INFO_GLOBAL_POSITION_INT_COV, MAVLINK_MESSAGE_INFO_LOCAL_POSITION_NED_COV, MAVLINK_MESSAGE_INFO_RC_CHANNELS, MAVLINK_MESSAGE_INFO_REQUEST_DATA_STREAM, MAVLINK_MESSAGE_INFO_DATA_STREAM, MAVLINK_MESSAGE_INFO_MANUAL_CONTROL, MAVLINK_MESSAGE_INFO_RC_CHANNELS_OVERRIDE, MAVLINK_MESSAGE_INFO_MISSION_ITEM_INT, MAVLINK_MESSAGE_INFO_VFR_HUD, MAVLINK_MESSAGE_INFO_COMMAND_INT, MAVLINK_MESSAGE_INFO_COMMAND_LONG, MAVLINK_MESSAGE_INFO_COMMAND_ACK, MAVLINK_MESSAGE_INFO_COMMAND_CANCEL, MAVLINK_MESSAGE_INFO_MANUAL_SETPOINT, MAVLINK_MESSAGE_INFO_SET_ATTITUDE_TARGET, MAVLINK_MESSAGE_INFO_ATTITUDE_TARGET, MAVLINK_MESSAGE_INFO_SET_POSITION_TARGET_LOCAL_NED, MAVLINK_MESSAGE_INFO_POSITION_TARGET_LOCAL_NED, MAVLINK_MESSAGE_INFO_SET_POSITION_TARGET_GLOBAL_INT, MAVLINK_MESSAGE_INFO_POSITION_TARGET_GLOBAL_INT, MAVLINK_MESSAGE_INFO_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET, MAVLINK_MESSAGE_INFO_HIL_STATE, MAVLINK_MESSAGE_INFO_HIL_CONTROLS, MAVLINK_MESSAGE_INFO_HIL_RC_INPUTS_RAW, MAVLINK_MESSAGE_INFO_HIL_ACTUATOR_CONTROLS, MAVLINK_MESSAGE_INFO_OPTICAL_FLOW, MAVLINK_MESSAGE_INFO_GLOBAL_VISION_POSITION_ESTIMATE, MAVLINK_MESSAGE_INFO_VISION_POSITION_ESTIMATE, MAVLINK_MESSAGE_INFO_VISION_SPEED_ESTIMATE, MAVLINK_MESSAGE_INFO_VICON_POSITION_ESTIMATE, MAVLINK_MESSAGE_INFO_HIGHRES_IMU, MAVLINK_MESSAGE_INFO_OPTICAL_FLOW_RAD, MAVLINK_MESSAGE_INFO_HIL_SENSOR, MAVLINK_MESSAGE_INFO_SIM_STATE, MAVLINK_MESSAGE_INFO_RADIO_STATUS, MAVLINK_MESSAGE_INFO_FILE_TRANSFER_PROTOCOL, MAVLINK_MESSAGE_INFO_TIMESYNC, MAVLINK_MESSAGE_INFO_CAMERA_TRIGGER, MAVLINK_MESSAGE_INFO_HIL_GPS, MAVLINK_MESSAGE_INFO_HIL_OPTICAL_FLOW, MAVLINK_MESSAGE_INFO_HIL_STATE_QUATERNION, MAVLINK_MESSAGE_INFO_SCALED_IMU2, MAVLINK_MESSAGE_INFO_LOG_REQUEST_LIST, MAVLINK_MESSAGE_INFO_LOG_ENTRY, MAVLINK_MESSAGE_INFO_LOG_REQUEST_DATA, MAVLINK_MESSAGE_INFO_LOG_DATA, MAVLINK_MESSAGE_INFO_LOG_ERASE, MAVLINK_MESSAGE_INFO_LOG_REQUEST_END, MAVLINK_MESSAGE_INFO_GPS_INJECT_DATA, MAVLINK_MESSAGE_INFO_GPS2_RAW, MAVLINK_MESSAGE_INFO_POWER_STATUS, MAVLINK_MESSAGE_INFO_SERIAL_CONTROL, MAVLINK_MESSAGE_INFO_GPS_RTK, MAVLINK_MESSAGE_INFO_GPS2_RTK, MAVLINK_MESSAGE_INFO_SCALED_IMU3, MAVLINK_MESSAGE_INFO_DATA_TRANSMISSION_HANDSHAKE, MAVLINK_MESSAGE_INFO_ENCAPSULATED_DATA, MAVLINK_MESSAGE_INFO_DISTANCE_SENSOR, MAVLINK_MESSAGE_INFO_TERRAIN_REQUEST, MAVLINK_MESSAGE_INFO_TERRAIN_DATA, MAVLINK_MESSAGE_INFO_TERRAIN_CHECK, MAVLINK_MESSAGE_INFO_TERRAIN_REPORT, MAVLINK_MESSAGE_INFO_SCALED_PRESSURE2, MAVLINK_MESSAGE_INFO_ATT_POS_MOCAP, MAVLINK_MESSAGE_INFO_SET_ACTUATOR_CONTROL_TARGET, MAVLINK_MESSAGE_INFO_ACTUATOR_CONTROL_TARGET, MAVLINK_MESSAGE_INFO_ALTITUDE, MAVLINK_MESSAGE_INFO_RESOURCE_REQUEST, MAVLINK_MESSAGE_INFO_SCALED_PRESSURE3, MAVLINK_MESSAGE_INFO_FOLLOW_TARGET, MAVLINK_MESSAGE_INFO_CONTROL_SYSTEM_STATE, MAVLINK_MESSAGE_INFO_BATTERY_STATUS, MAVLINK_MESSAGE_INFO_AUTOPILOT_VERSION, MAVLINK_MESSAGE_INFO_LANDING_TARGET, MAVLINK_MESSAGE_INFO_FENCE_STATUS, MAVLINK_MESSAGE_INFO_MAG_CAL_REPORT, MAVLINK_MESSAGE_INFO_EFI_STATUS, MAVLINK_MESSAGE_INFO_ESTIMATOR_STATUS, MAVLINK_MESSAGE_INFO_WIND_COV, MAVLINK_MESSAGE_INFO_GPS_INPUT, MAVLINK_MESSAGE_INFO_GPS_RTCM_DATA, MAVLINK_MESSAGE_INFO_HIGH_LATENCY, MAVLINK_MESSAGE_INFO_HIGH_LATENCY2, MAVLINK_MESSAGE_INFO_VIBRATION, MAVLINK_MESSAGE_INFO_HOME_POSITION, MAVLINK_MESSAGE_INFO_SET_HOME_POSITION, MAVLINK_MESSAGE_INFO_MESSAGE_INTERVAL, MAVLINK_MESSAGE_INFO_EXTENDED_SYS_STATE, MAVLINK_MESSAGE_INFO_ADSB_VEHICLE, MAVLINK_MESSAGE_INFO_COLLISION, MAVLINK_MESSAGE_INFO_V2_EXTENSION, MAVLINK_MESSAGE_INFO_MEMORY_VECT, MAVLINK_MESSAGE_INFO_DEBUG_VECT, MAVLINK_MESSAGE_INFO_NAMED_VALUE_FLOAT, MAVLINK_MESSAGE_INFO_NAMED_VALUE_INT, MAVLINK_MESSAGE_INFO_STATUSTEXT, MAVLINK_MESSAGE_INFO_DEBUG, MAVLINK_MESSAGE_INFO_SETUP_SIGNING, MAVLINK_MESSAGE_INFO_BUTTON_CHANGE, MAVLINK_MESSAGE_INFO_PLAY_TUNE, MAVLINK_MESSAGE_INFO_CAMERA_INFORMATION, MAVLINK_MESSAGE_INFO_CAMERA_SETTINGS, MAVLINK_MESSAGE_INFO_STORAGE_INFORMATION, MAVLINK_MESSAGE_INFO_CAMERA_CAPTURE_STATUS, MAVLINK_MESSAGE_INFO_CAMERA_IMAGE_CAPTURED, MAVLINK_MESSAGE_INFO_FLIGHT_INFORMATION, MAVLINK_MESSAGE_INFO_MOUNT_ORIENTATION, MAVLINK_MESSAGE_INFO_LOGGING_DATA, MAVLINK_MESSAGE_INFO_LOGGING_DATA_ACKED, MAVLINK_MESSAGE_INFO_LOGGING_ACK, MAVLINK_MESSAGE_INFO_VIDEO_STREAM_INFORMATION, MAVLINK_MESSAGE_INFO_VIDEO_STREAM_STATUS, MAVLINK_MESSAGE_INFO_CAMERA_FOV_STATUS, MAVLINK_MESSAGE_INFO_CAMERA_TRACKING_IMAGE_STATUS, MAVLINK_MESSAGE_INFO_CAMERA_TRACKING_GEO_STATUS, MAVLINK_MESSAGE_INFO_CAMERA_THERMAL_RANGE, MAVLINK_MESSAGE_INFO_GIMBAL_MANAGER_INFORMATION, MAVLINK_MESSAGE_INFO_GIMBAL_MANAGER_STATUS, MAVLINK_MESSAGE_INFO_GIMBAL_MANAGER_SET_ATTITUDE, MAVLINK_MESSAGE_INFO_GIMBAL_DEVICE_INFORMATION, MAVLINK_MESSAGE_INFO_GIMBAL_DEVICE_SET_ATTITUDE, MAVLINK_MESSAGE_INFO_GIMBAL_DEVICE_ATTITUDE_STATUS, MAVLINK_MESSAGE_INFO_AUTOPILOT_STATE_FOR_GIMBAL_DEVICE, MAVLINK_MESSAGE_INFO_GIMBAL_MANAGER_SET_PITCHYAW, MAVLINK_MESSAGE_INFO_GIMBAL_MANAGER_SET_MANUAL_CONTROL, MAVLINK_MESSAGE_INFO_ESC_INFO, MAVLINK_MESSAGE_INFO_ESC_STATUS, MAVLINK_MESSAGE_INFO_AIRSPEED, MAVLINK_MESSAGE_INFO_GLOBAL_POSITION_SENSOR, MAVLINK_MESSAGE_INFO_WIFI_CONFIG_AP, MAVLINK_MESSAGE_INFO_PROTOCOL_VERSION, MAVLINK_MESSAGE_INFO_AIS_VESSEL, MAVLINK_MESSAGE_INFO_UAVCAN_NODE_STATUS, MAVLINK_MESSAGE_INFO_UAVCAN_NODE_INFO, MAVLINK_MESSAGE_INFO_PARAM_EXT_REQUEST_READ, MAVLINK_MESSAGE_INFO_PARAM_EXT_REQUEST_LIST, MAVLINK_MESSAGE_INFO_PARAM_EXT_VALUE, MAVLINK_MESSAGE_INFO_PARAM_EXT_SET, MAVLINK_MESSAGE_INFO_PARAM_EXT_ACK, MAVLINK_MESSAGE_INFO_OBSTACLE_DISTANCE, MAVLINK_MESSAGE_INFO_ODOMETRY, MAVLINK_MESSAGE_INFO_TRAJECTORY_REPRESENTATION_WAYPOINTS, MAVLINK_MESSAGE_INFO_TRAJECTORY_REPRESENTATION_BEZIER, MAVLINK_MESSAGE_INFO_CELLULAR_STATUS, MAVLINK_MESSAGE_INFO_ISBD_LINK_STATUS, MAVLINK_MESSAGE_INFO_CELLULAR_CONFIG, MAVLINK_MESSAGE_INFO_RAW_RPM, MAVLINK_MESSAGE_INFO_UTM_GLOBAL_POSITION, MAVLINK_MESSAGE_INFO_PARAM_ERROR, MAVLINK_MESSAGE_INFO_DEBUG_FLOAT_ARRAY, MAVLINK_MESSAGE_INFO_ORBIT_EXECUTION_STATUS, MAVLINK_MESSAGE_INFO_FIGURE_EIGHT_EXECUTION_STATUS, MAVLINK_MESSAGE_INFO_SMART_BATTERY_INFO, MAVLINK_MESSAGE_INFO_FUEL_STATUS, MAVLINK_MESSAGE_INFO_BATTERY_INFO, MAVLINK_MESSAGE_INFO_GENERATOR_STATUS, MAVLINK_MESSAGE_INFO_ACTUATOR_OUTPUT_STATUS, MAVLINK_MESSAGE_INFO_RELAY_STATUS, MAVLINK_MESSAGE_INFO_TIME_ESTIMATE_TO_TARGET, MAVLINK_MESSAGE_INFO_TUNNEL, MAVLINK_MESSAGE_INFO_CAN_FRAME, MAVLINK_MESSAGE_INFO_CANFD_FRAME, MAVLINK_MESSAGE_INFO_CAN_FILTER_MODIFY, MAVLINK_MESSAGE_INFO_ONBOARD_COMPUTER_STATUS, MAVLINK_MESSAGE_INFO_COMPONENT_INFORMATION, MAVLINK_MESSAGE_INFO_COMPONENT_INFORMATION_BASIC, MAVLINK_MESSAGE_INFO_COMPONENT_METADATA, MAVLINK_MESSAGE_INFO_PLAY_TUNE_V2, MAVLINK_MESSAGE_INFO_SUPPORTED_TUNES, MAVLINK_MESSAGE_INFO_EVENT, MAVLINK_MESSAGE_INFO_CURRENT_EVENT_SEQUENCE, MAVLINK_MESSAGE_INFO_REQUEST_EVENT, MAVLINK_MESSAGE_INFO_RESPONSE_EVENT_ERROR, MAVLINK_MESSAGE_INFO_AVAILABLE_MODES, MAVLINK_MESSAGE_INFO_CURRENT_MODE, MAVLINK_MESSAGE_INFO_AVAILABLE_MODES_MONITOR, MAVLINK_MESSAGE_INFO_ILLUMINATOR_STATUS, MAVLINK_MESSAGE_INFO_WHEEL_DISTANCE, MAVLINK_MESSAGE_INFO_WINCH_STATUS, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_BASIC_ID, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_LOCATION, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_AUTHENTICATION, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_SELF_ID, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_SYSTEM, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_OPERATOR_ID, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_MESSAGE_PACK, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_ARM_STATUS, MAVLINK_MESSAGE_INFO_OPEN_DRONE_ID_SYSTEM_UPDATE, MAVLINK_MESSAGE_INFO_HYGROMETER_SENSOR, MAVLINK_MESSAGE_INFO_TRACK_IDENTITY, MAVLINK_MESSAGE_INFO_TARGET_CUE, MAVLINK_MESSAGE_INFO_TARGET_HANDOVER, MAVLINK_MESSAGE_INFO_PARTICIPANT_POSITION, MAVLINK_MESSAGE_INFO_MAVLINK_M_ACK, MAVLINK_MESSAGE_INFO_TARGET, MAVLINK_MESSAGE_INFO_TARGET_SET_COORD, MAVLINK_MESSAGE_INFO_TARGET_BOX_COORD, MAVLINK_MESSAGE_INFO_TARGET_AUTHORIZATION, MAVLINK_MESSAGE_INFO_FIRES, MAVLINK_MESSAGE_INFO_SPLASH_CORRECTION, MAVLINK_MESSAGE_INFO_BATTLE_DAMAGE_ASSESSMENT, MAVLINK_MESSAGE_INFO_ENGAGEMENT_DIRECTIVE, MAVLINK_MESSAGE_INFO_CALL_FOR_FIRE, MAVLINK_MESSAGE_INFO_ESAD_STATE, MAVLINK_MESSAGE_INFO_ESAD_ARMING, MAVLINK_MESSAGE_INFO_ESAD_CONFIG, MAVLINK_MESSAGE_INFO_STORE_STATUS, MAVLINK_MESSAGE_INFO_STORE_SENSOR_STATUS, MAVLINK_MESSAGE_INFO_STORE_MUNITION, MAVLINK_MESSAGE_INFO_LOITER_MUNITION_CONTROL, MAVLINK_MESSAGE_INFO_RWS_POSE, MAVLINK_MESSAGE_INFO_RWS_STATE, MAVLINK_MESSAGE_INFO_SENSOR_TASKING, MAVLINK_MESSAGE_INFO_CAS_9LINE, MAVLINK_MESSAGE_INFO_TERMINAL_CONTROL}
# define MAVLINK_MESSAGE_NAMES {{ "ACTUATOR_CONTROL_TARGET", 140 }, { "ACTUATOR_OUTPUT_STATUS", 375 }, { "ADSB_VEHICLE", 246 }, { "AIRSPEED", 295 }, { "AIS_VESSEL", 301 }, { "ALTITUDE", 141 }, { "ATTITUDE", 30 }, { "ATTITUDE_QUATERNION", 31 }, { "ATTITUDE_QUATERNION_COV", 61 }, { "ATTITUDE_TARGET", 83 }, { "ATT_POS_MOCAP", 138 }, { "AUTH_KEY", 7 }, { "AUTOPILOT_STATE_FOR_GIMBAL_DEVICE", 286 }, { "AUTOPILOT_VERSION", 148 }, { "AVAILABLE_MODES", 435 }, { "AVAILABLE_MODES_MONITOR", 437 }, { "BATTERY_INFO", 372 }, { "BATTERY_STATUS", 147 }, { "BATTLE_DAMAGE_ASSESSMENT", 53022 }, { "BUTTON_CHANGE", 257 }, { "CALL_FOR_FIRE", 53024 }, { "CAMERA_CAPTURE_STATUS", 262 }, { "CAMERA_FOV_STATUS", 271 }, { "CAMERA_IMAGE_CAPTURED", 263 }, { "CAMERA_INFORMATION", 259 }, { "CAMERA_SETTINGS", 260 }, { "CAMERA_THERMAL_RANGE", 277 }, { "CAMERA_TRACKING_GEO_STATUS", 276 }, { "CAMERA_TRACKING_IMAGE_STATUS", 275 }, { "CAMERA_TRIGGER", 112 }, { "CANFD_FRAME", 387 }, { "CAN_FILTER_MODIFY", 388 }, { "CAN_FRAME", 386 }, { "CAS_9LINE", 53060 }, { "CELLULAR_CONFIG", 336 }, { "CELLULAR_STATUS", 334 }, { "CHANGE_OPERATOR_CONTROL", 5 }, { "CHANGE_OPERATOR_CONTROL_ACK", 6 }, { "COLLISION", 247 }, { "COMMAND_ACK", 77 }, { "COMMAND_CANCEL", 80 }, { "COMMAND_INT", 75 }, { "COMMAND_LONG", 76 }, { "COMPONENT_INFORMATION", 395 }, { "COMPONENT_INFORMATION_BASIC", 396 }, { "COMPONENT_METADATA", 397 }, { "CONTROL_SYSTEM_STATE", 146 }, { "CURRENT_EVENT_SEQUENCE", 411 }, { "CURRENT_MODE", 436 }, { "DATA_STREAM", 67 }, { "DATA_TRANSMISSION_HANDSHAKE", 130 }, { "DEBUG", 254 }, { "DEBUG_FLOAT_ARRAY", 350 }, { "DEBUG_VECT", 250 }, { "DISTANCE_SENSOR", 132 }, { "EFI_STATUS", 225 }, { "ENCAPSULATED_DATA", 131 }, { "ENGAGEMENT_DIRECTIVE", 53023 }, { "ESAD_ARMING", 53031 }, { "ESAD_CONFIG", 53032 }, { "ESAD_STATE", 53030 }, { "ESC_INFO", 290 }, { "ESC_STATUS", 291 }, { "ESTIMATOR_STATUS", 230 }, { "EVENT", 410 }, { "EXTENDED_SYS_STATE", 245 }, { "FENCE_STATUS", 162 }, { "FIGURE_EIGHT_EXECUTION_STATUS", 361 }, { "FILE_TRANSFER_PROTOCOL", 110 }, { "FIRES", 53020 }, { "FLIGHT_INFORMATION", 264 }, { "FOLLOW_TARGET", 144 }, { "FUEL_STATUS", 371 }, { "GENERATOR_STATUS", 373 }, { "GIMBAL_DEVICE_ATTITUDE_STATUS", 285 }, { "GIMBAL_DEVICE_INFORMATION", 283 }, { "GIMBAL_DEVICE_SET_ATTITUDE", 284 }, { "GIMBAL_MANAGER_INFORMATION", 280 }, { "GIMBAL_MANAGER_SET_ATTITUDE", 282 }, { "GIMBAL_MANAGER_SET_MANUAL_CONTROL", 288 }, { "GIMBAL_MANAGER_SET_PITCHYAW", 287 }, { "GIMBAL_MANAGER_STATUS", 281 }, { "GLOBAL_POSITION_INT", 33 }, { "GLOBAL_POSITION_INT_COV", 63 }, { "GLOBAL_POSITION_SENSOR", 296 }, { "GLOBAL_VISION_POSITION_ESTIMATE", 101 }, { "GPS2_RAW", 124 }, { "GPS2_RTK", 128 }, { "GPS_GLOBAL_ORIGIN", 49 }, { "GPS_INJECT_DATA", 123 }, { "GPS_INPUT", 232 }, { "GPS_RAW_INT", 24 }, { "GPS_RTCM_DATA", 233 }, { "GPS_RTK", 127 }, { "GPS_STATUS", 25 }, { "HEARTBEAT", 0 }, { "HIGHRES_IMU", 105 }, { "HIGH_LATENCY", 234 }, { "HIGH_LATENCY2", 235 }, { "HIL_ACTUATOR_CONTROLS", 93 }, { "HIL_CONTROLS", 91 }, { "HIL_GPS", 113 }, { "HIL_OPTICAL_FLOW", 114 }, { "HIL_RC_INPUTS_RAW", 92 }, { "HIL_SENSOR", 107 }, { "HIL_STATE", 90 }, { "HIL_STATE_QUATERNION", 115 }, { "HOME_POSITION", 242 }, { "HYGROMETER_SENSOR", 12920 }, { "ILLUMINATOR_STATUS", 440 }, { "ISBD_LINK_STATUS", 335 }, { "LANDING_TARGET", 149 }, { "LINK_NODE_STATUS", 8 }, { "LOCAL_POSITION_NED", 32 }, { "LOCAL_POSITION_NED_COV", 64 }, { "LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET", 89 }, { "LOGGING_ACK", 268 }, { "LOGGING_DATA", 266 }, { "LOGGING_DATA_ACKED", 267 }, { "LOG_DATA", 120 }, { "LOG_ENTRY", 118 }, { "LOG_ERASE", 121 }, { "LOG_REQUEST_DATA", 119 }, { "LOG_REQUEST_END", 122 }, { "LOG_REQUEST_LIST", 117 }, { "LOITER_MUNITION_CONTROL", 53036 }, { "MAG_CAL_REPORT", 192 }, { "MANUAL_CONTROL", 69 }, { "MANUAL_SETPOINT", 81 }, { "MAVLINK_M_ACK", 53004 }, { "MEMORY_VECT", 249 }, { "MESSAGE_INTERVAL", 244 }, { "MISSION_ACK", 47 }, { "MISSION_CLEAR_ALL", 45 }, { "MISSION_COUNT", 44 }, { "MISSION_CURRENT", 42 }, { "MISSION_ITEM", 39 }, { "MISSION_ITEM_INT", 73 }, { "MISSION_ITEM_REACHED", 46 }, { "MISSION_REQUEST", 40 }, { "MISSION_REQUEST_INT", 51 }, { "MISSION_REQUEST_LIST", 43 }, { "MISSION_REQUEST_PARTIAL_LIST", 37 }, { "MISSION_SET_CURRENT", 41 }, { "MISSION_WRITE_PARTIAL_LIST", 38 }, { "MOUNT_ORIENTATION", 265 }, { "NAMED_VALUE_FLOAT", 251 }, { "NAMED_VALUE_INT", 252 }, { "NAV_CONTROLLER_OUTPUT", 62 }, { "OBSTACLE_DISTANCE", 330 }, { "ODOMETRY", 331 }, { "ONBOARD_COMPUTER_STATUS", 390 }, { "OPEN_DRONE_ID_ARM_STATUS", 12918 }, { "OPEN_DRONE_ID_AUTHENTICATION", 12902 }, { "OPEN_DRONE_ID_BASIC_ID", 12900 }, { "OPEN_DRONE_ID_LOCATION", 12901 }, { "OPEN_DRONE_ID_MESSAGE_PACK", 12915 }, { "OPEN_DRONE_ID_OPERATOR_ID", 12905 }, { "OPEN_DRONE_ID_SELF_ID", 12903 }, { "OPEN_DRONE_ID_SYSTEM", 12904 }, { "OPEN_DRONE_ID_SYSTEM_UPDATE", 12919 }, { "OPTICAL_FLOW", 100 }, { "OPTICAL_FLOW_RAD", 106 }, { "ORBIT_EXECUTION_STATUS", 360 }, { "PARAM_ERROR", 345 }, { "PARAM_EXT_ACK", 324 }, { "PARAM_EXT_REQUEST_LIST", 321 }, { "PARAM_EXT_REQUEST_READ", 320 }, { "PARAM_EXT_SET", 323 }, { "PARAM_EXT_VALUE", 322 }, { "PARAM_MAP_RC", 50 }, { "PARAM_REQUEST_LIST", 21 }, { "PARAM_REQUEST_READ", 20 }, { "PARAM_SET", 23 }, { "PARAM_VALUE", 22 }, { "PARTICIPANT_POSITION", 53003 }, { "PING", 4 }, { "PLAY_TUNE", 258 }, { "PLAY_TUNE_V2", 400 }, { "POSITION_TARGET_GLOBAL_INT", 87 }, { "POSITION_TARGET_LOCAL_NED", 85 }, { "POWER_STATUS", 125 }, { "PROTOCOL_VERSION", 300 }, { "RADIO_STATUS", 109 }, { "RAW_IMU", 27 }, { "RAW_PRESSURE", 28 }, { "RAW_RPM", 339 }, { "RC_CHANNELS", 65 }, { "RC_CHANNELS_OVERRIDE", 70 }, { "RC_CHANNELS_RAW", 35 }, { "RC_CHANNELS_SCALED", 34 }, { "RELAY_STATUS", 376 }, { "REQUEST_DATA_STREAM", 66 }, { "REQUEST_EVENT", 412 }, { "RESOURCE_REQUEST", 142 }, { "RESPONSE_EVENT_ERROR", 413 }, { "RWS_POSE", 53040 }, { "RWS_STATE", 53041 }, { "SAFETY_ALLOWED_AREA", 55 }, { "SAFETY_SET_ALLOWED_AREA", 54 }, { "SCALED_IMU", 26 }, { "SCALED_IMU2", 116 }, { "SCALED_IMU3", 129 }, { "SCALED_PRESSURE", 29 }, { "SCALED_PRESSURE2", 137 }, { "SCALED_PRESSURE3", 143 }, { "SENSOR_TASKING", 53050 }, { "SERIAL_CONTROL", 126 }, { "SERVO_OUTPUT_RAW", 36 }, { "SETUP_SIGNING", 256 }, { "SET_ACTUATOR_CONTROL_TARGET", 139 }, { "SET_ATTITUDE_TARGET", 82 }, { "SET_GPS_GLOBAL_ORIGIN", 48 }, { "SET_HOME_POSITION", 243 }, { "SET_MODE", 11 }, { "SET_POSITION_TARGET_GLOBAL_INT", 86 }, { "SET_POSITION_TARGET_LOCAL_NED", 84 }, { "SIM_STATE", 108 }, { "SMART_BATTERY_INFO", 370 }, { "SPLASH_CORRECTION", 53021 }, { "STATUSTEXT", 253 }, { "STORAGE_INFORMATION", 261 }, { "STORE_MUNITION", 53035 }, { "STORE_SENSOR_STATUS", 53034 }, { "STORE_STATUS", 53033 }, { "SUPPORTED_TUNES", 401 }, { "SYSTEM_TIME", 2 }, { "SYS_STATUS", 1 }, { "TARGET", 53010 }, { "TARGET_AUTHORIZATION", 53013 }, { "TARGET_BOX_COORD", 53012 }, { "TARGET_CUE", 53001 }, { "TARGET_HANDOVER", 53002 }, { "TARGET_SET_COORD", 53011 }, { "TERMINAL_CONTROL", 53061 }, { "TERRAIN_CHECK", 135 }, { "TERRAIN_DATA", 134 }, { "TERRAIN_REPORT", 136 }, { "TERRAIN_REQUEST", 133 }, { "TIMESYNC", 111 }, { "TIME_ESTIMATE_TO_TARGET", 380 }, { "TRACK_IDENTITY", 53000 }, { "TRAJECTORY_REPRESENTATION_BEZIER", 333 }, { "TRAJECTORY_REPRESENTATION_WAYPOINTS", 332 }, { "TUNNEL", 385 }, { "UAVCAN_NODE_INFO", 311 }, { "UAVCAN_NODE_STATUS", 310 }, { "UTM_GLOBAL_POSITION", 340 }, { "V2_EXTENSION", 248 }, { "VFR_HUD", 74 }, { "VIBRATION", 241 }, { "VICON_POSITION_ESTIMATE", 104 }, { "VIDEO_STREAM_INFORMATION", 269 }, { "VIDEO_STREAM_STATUS", 270 }, { "VISION_POSITION_ESTIMATE", 102 }, { "VISION_SPEED_ESTIMATE", 103 }, { "WHEEL_DISTANCE", 9000 }, { "WIFI_CONFIG_AP", 299 }, { "WINCH_STATUS", 9005 }, { "WIND_COV", 231 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_MILITARY_H
