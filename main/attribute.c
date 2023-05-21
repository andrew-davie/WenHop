// Object attributes

#include "attribute.h"

const unsigned char CharToType[CH_MAX] = {

    // see ChName for corresponding character name/number
    // may need to update worstRequiredTime if that's in use

    TYPE_SPACE,                 // 000 CH_BLANK,
    TYPE_DIRT,                  // 001 CH_DIRT,
    TYPE_BRICKWALL,             // 002 CH_BRICKWALL,
    TYPE_OUTBOX_PRE,            // 003 CH_DOORCLOSED,
    TYPE_OUTBOX,                // 004 CH_DOOROPEN_0,
    TYPE_STEELWALL,             // 005 CH_EXITBLANK,
    TYPE_STEELWALL,             // 006 CH_STEELWALL,
    TYPE_PEBBLE1,               // 007 CH_PEBBLE1,
    TYPE_PEBBLE2,               // 008 CH_PEBBLE2,
    TYPE_ROCK,                  // 009 CH_ROCK,
    TYPE_ROCK_FALLING,          // 010 CH_ROCK_FALLING,
    TYPE_DOGE,                  // 011 CH_DOGE_00,
    TYPE_DOGE_FALLING,          // 012 CH_DOGE_FALLING,
    TYPE_MELLON_HUSK_PRE,       // 013 CH_MELLON_HUSK_BIRTH,
    TYPE_LAVA,                  // 014 CH_LAVA_0,
    TYPE_LAVA,                  // 015 CH_LAVA_1,
    TYPE_LAVA,                  // 016 CH_LAVA_2,
    TYPE_LAVA,                  // 017 CH_LAVA_3,
    TYPE_MELLON_HUSK,           // 018 CH_MELLON_HUSK,
    TYPE_DOGE,                  // 019 CH_DOGE_01,
    TYPE_DOGE,                  // 020 CH_DOGE_02,
    TYPE_DOGE,                  // 021 CH_DOGE_03,
    TYPE_DOGE,                  // 022 CH_DOGE_04,
    TYPE_DOGE,                  // 023 CH_DOGE_05,
    TYPE_DOGE,                  // 024 CH_DOGE_STATIC,
    TYPE_PEBBLE_ROCK,           // 025 CH_PEBBLE_ROCK,
    TYPE_SPACE,                 // 026 CH_EXPLODETOBLANK_0,
    TYPE_SPACE,                 // 027 CH_EXPLODETOBLANK_1,
    TYPE_SPACE,                 // 028 CH_EXPLODETOBLANK_2,
    TYPE_SPACE,                 // 029 CH_EXPLODETOBLANK_3,
    TYPE_SPACE,                 // 030 CH_EXPLODETOBLANK_4,
    TYPE_GRAB,                  // 031 CH_DOGE_GRAB,
    TYPE_DUST_0,                // 032 CH_DUST_0,
    TYPE_DUST_0,                // 033 CH_DUST_1,
    TYPE_DUST_0,                // 034 CH_DUST_2,
    TYPE_GEODOGE,               // 035 CH_CONGLOMERATE,
    TYPE_GEODOGE,               // 036 CH_CONGLOMERATE_1,
    TYPE_GEODOGE,               // 037 CH_CONGLOMERATE_2,
    TYPE_GEODOGE,               // 038 CH_CONGLOMERATE_3,
    TYPE_GEODOGE,               // 039 CH_CONGLOMERATE_4,
    TYPE_GEODOGE,               // 040 CH_CONGLOMERATE_5,
    TYPE_GEODOGE,               // 041 CH_CONGLOMERATE_6,
    TYPE_GEODOGE,               // 042 CH_CONGLOMERATE_7,
    TYPE_GEODOGE,               // 043 CH_CONGLOMERATE_8,
    TYPE_GEODOGE,               // 044 CH_CONGLOMERATE_9,
    TYPE_GEODOGE,               // 045 CH_CONGLOMERATE_10,
    TYPE_GEODOGE,               // 046 CH_CONGLOMERATE_11,
    TYPE_GEODOGE,               // 047 CH_CONGLOMERATE_12,
    TYPE_GEODOGE,               // 048 CH_CONGLOMERATE_13,
    TYPE_GEODOGE,               // 049 CH_CONGLOMERATE_14,
    TYPE_GEODOGE,               // 050 CH_CONGLOMERATE_15,
    TYPE_DUST_ROCK,             // 051 CH_DUST_ROCK_0,
    TYPE_DUST_ROCK,             // 052 CH_DUST_ROCK_1,
    TYPE_DUST_ROCK,             // 053 CH_DUST_ROCK_2,
    TYPE_DOGE,                  // 054 CH_CONVERT_GEODE_TO_DOGE,
    TYPE_SWITCH,                // 055 CH_SWITCH_LEFT_OFF,
    TYPE_SWITCH,                // 056 CH_SWITCH_LEFT_ON,
    TYPE_PUSHER,                // 057 CH_HORIZONTAL_BAR,
    TYPE_PUSHER,                // 058 CH_PUSH_LEFT,
    TYPE_PUSHER,                // 059 CH_PUSH_LEFT_REVERSE,
    TYPE_PUSHER,                // 060 CH_PUSH_RIGHT,
    TYPE_PUSHER,                // 061 CH_PUSH_RIGHT_REVERSE,
    TYPE_PUSHER,                // 062 CH_VERTICAL_BAR,
    TYPE_PUSHER,                // 063 CH_PUSH_UP,
    TYPE_PUSHER,                // 064 CH_PUSH_UP_REVERSE,
    TYPE_PUSHER,                // 065 CH_PUSH_DOWN,
    TYPE_PUSHER,                // 066 CH_PUSH_DOWN_REVERSE,
    TYPE_WYRM,                  // 067 CH_WYRM_BODY,
    TYPE_WYRM,                  // 068 CH_WYRM_VERT_BODY,
    TYPE_WYRM,                  // 069 CH_WYRM_CORNER_LD,
    TYPE_WYRM,                  // 070 CH_WYRM_CORNER_RD,
    TYPE_WYRM,                  // 071 CH_WYRM_CORNER_LU,
    TYPE_WYRM,                  // 072 CH_WYRM_CORNER_RU,
    TYPE_WYRM,                  // 073 CH_WYRM_HEAD_U,
    TYPE_WYRM,                  // 074 CH_WYRM_HEAD_R,
    TYPE_WYRM,                  // 075 CH_WYRM_HEAD_D,
    TYPE_WYRM,                  // 076 CH_WYRM_HEAD_L,
    TYPE_SPACE,                 // 077 CH_CORNER_0,
    TYPE_SPACE,                 // 078 CH_CORNER_1,
    TYPE_SPACE,                 // 079 CH_CORNER_2,
    TYPE_SPACE,                 // 080 CH_CORNER_3,
    TYPE_SPACE,                 // 081 CH_CORNER_4,
    TYPE_SPACE,                 // 082 CH_CORNER_5,
    TYPE_SPACE,                 // 083 CH_CORNER_6,
    TYPE_SPACE,                 // 084 CH_CORNER_7,
    TYPE_SPACE,                 // 085 CH_CORNER_8,
    TYPE_SPACE,                 // 086 CH_CORNER_9,
    TYPE_SPACE,                 // 087 CH_CORNER_10,
    TYPE_SPACE,                 // 088 CH_CORNER_11,
    TYPE_SPACE,                 // 089 CH_CORNER_12,
    TYPE_SPACE,                 // 090 CH_CORNER_13,
    TYPE_SPACE,                 // 091 CH_CORNER_14,
    TYPE_SPACE,                 // 092 CH_CORNER_15,
    TYPE_ROCK,                  // 093 CH_CONGLOMERATE_MID,
    TYPE_GEODOGE_FALLING,       // 094 CH_GEODOGE_FALLING,
    TYPE_FLIP_GRAVITY,          // 095 CH_FLIP_GRAVITY_0,
    TYPE_FLIP_GRAVITY,          // 096 CH_FLIP_GRAVITY_1,
    TYPE_FLIP_GRAVITY,          // 097 CH_FLIP_GRAVITY_2,
    TYPE_BLOCK,                 // 098 CH_BLOCK,
    TYPE_PACMAN_DOT,            // 099 CH_PACMAN_DOT,
    TYPE_GRINDER,               // 100 CH_GRINDER_0,
    TYPE_HUB,                   // 101 CH_HUB,
    TYPE_WATER,                 // 102 CH_WATER_0
    TYPE_WATER,                 // 103 CH_WATER_1
    TYPE_WATER,                 // 104 CH_WATER_2
    TYPE_WATER,                 // 105 CH_WATER_3
    TYPE_WATERFLOW,             // 106 CH_WATERFLOW_0
    TYPE_WATERFLOW,             // 107 CH_WATERFLOW_1
    TYPE_WATERFLOW,             // 108 CH_WATERFLOW_2
    TYPE_WATERFLOW,             // 109 CH_WATERFLOW_3
    TYPE_WATERFLOW,             // 110 CH_WATERFLOW_4
    TYPE_TAP,                   // 111 CH_TAP_0
    TYPE_HUB,                   // 112 CH_HUB_1
    TYPE_OUTLET,                // 113 CH_OUTLET
    TYPE_TAP,                   // 114 CH_TAP_1
    TYPE_GRINDER_1,             // 115 CH_GRINDER_1
    TYPE_BELT,                  // 116 CH_BELT_0
    TYPE_BELT_1,                // 117 CH_BELT_1
    TYPE_PUSHER,                // 118 CH_PUSH_DOWN2
    TYPE_CONVERT_GEODE_TO_DOGE, // 119 CH_GEODOGE_CONVERT  (deprecated)
};

const int Attribute[TYPE_MAX] = {

// see attribute.h "ObjectType"

#define _ 0

//  LAV =   Object immediately turns into lava bubbles when below lava line
//  QUI =   Quiet object. No noise genrate when things fall onto it
//  HRD =   Hard. rocks create dust when falling onto
//  ACT =   Active object that must be processed every frame
//  BNG     Explodes in lava

//  CNR =   surrounding space fills in corner
//  PAD =   do the corner padding for this creature type
//  SHV =   the pushers can push this object if next square blank
//  MLT =   melts when in lava -> CH_LAVA_00
//  PUL =   object pulled by lassoo
//
//  PH1     every nth frame processes...
//  PH2
//  PH4
//  GND     object can be "grinded"

#define PHC PH4 /* for conveyor */

    // clang-format off

//                                    21
//                                   22
//  31  30  29  28  27  26  25  24  23  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0
// CNR PAD SHV BOU DGE MLT DIS PUL PH*     GND CVY     MIN DRP RKF LAV QUI XIT HRD SQB     BNG GRB DRT SPC PER XPD     ROL
// ---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    _ |PAD| _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ | _ |RKF|LAV|QUI| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 00 TYPE_SPACE,
   CNR| _ | _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ |DRP| _ |LAV| _ | _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD| _ | _  , // 01 TYPE_DIRT,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |DRP| _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 02 TYPE_BRICKWALL,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 03 TYPE_OUTBOX_PRE,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |XIT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 04 TYPE_OUTBOX,
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |DRP| _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 05 TYPE_STEELWALL,
    _ |PAD|SHV|BOU| _ |MLT| _ |PUL|PH2| _ |GND|CVY| _ |MIN| _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 06 TYPE_ROCK,
    _ |PAD|SHV| _ | _ |MLT| _ |PUL|PH2| _ |GND|CVY| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |BNG|GRB| _ | _ | _ |XPD| _ |ROL , // 07 TYPE_DOGE,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 08 TYPE_MELLON_HUSK_PRE,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ |QUI| _ | _ |SQB| _ | _ | _ | _ | _ | _ |XPD| _ | _  , // 09 TYPE_MELLON_HUSK,
   CNR| _ | _ | _ | _ | _ |DIS| _ |PH4| _ | _ | _ | _ | _ |DRP| _ |LAV| _ | _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD| _ | _  , // 10 TYPE_PEBBLE1,
   CNR| _ | _ | _ | _ | _ |DIS| _ |PH4| _ | _ | _ | _ | _ |DRP| _ |LAV| _ | _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD| _ | _  , // 11 TYPE_PEBBLE2,
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |RKF|LAV|QUI| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 12 TYPE_GRAB,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ |RKF| _ |QUI| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 13 TYPE_DUST_0,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 14 TYPE_DOGE_FALLING,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ | _  , // 15 TYPE_ROCK_FALLING,
    _ |PAD| _ | _ | _ |MLT| _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |BNG| _ | _ | _ | _ |XPD| _ | _  , // 16 TYPE_DUST_ROCK,
    _ |PAD| _ | _ | _ |MLT| _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 17 TYPE_CONVERT_GEODE_TO_DOGE, (deprecated)
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |GRB| _ | _ | _ | _ | _ | _  , // 18 TYPE_SWITCH,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1|PIP| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 19 TYPE_PUSHER,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1|PIP| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 20 TYPE_PUSHER_VERT,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 21 TYPE_WYRM,
    _ |PAD|SHV|BOU|DGE|MLT| _ |PUL|PH2| _ |GND|CVY| _ |MIN| _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 22 TYPE_GEODOGE,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ | _  , // 23 TYPE_GEODOGE_FALLING,
    _ |PAD|SHV|BOU|DGE| _ | _ | _ |PH2| _ | _ | _ | _ |MIN| _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 24 TYPE_GEODOGE_CRITICAL (deprecated)
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ | _ |SPC| _ | _ | _ | _  , // 25 TYPE_LAVA,
    _ |PAD| _ | _ | _ | _ |DIS| _ |PH4| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ |BNG| _ | _ | _ |PER|XPD| _ | _  , // 26 TYPE_PEBBLE_ROCK,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ |BNG| _ |DRT| _ |PER|XPD| _ | _  , // 27 TYPE_FLIP_GRAVITY
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 28 TYPE_BLOCK
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 29 TYPE_BLOCK
    _ |PAD| _ | _ | _ | _ | _ | _ |PHC| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 30 TYPE_GRINDER
    _ | _ | _ | _ | _ | _ | _ | _ |PH4|PIP| _ | _ | _ | _ |DRP| _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 31 TYPE_HUB
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ | _ |SPC| _ |XPD| _ | _  , // 32 TYPE_WATER
    _ | _ | _ | _ | _ | _ |DIS| _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |XPD| _ | _  , // 33 TYPE_WATERFLOW
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 34 TYPE_TAP
    _ | _ | _ | _ | _ | _ | _ | _ |PH4|PIP| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 35 TYPE_OUTLET
    _ |PAD| _ | _ | _ | _ | _ | _ |PH4| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 36 TYPE_GRINDER1
    _ |PAD| _ | _ | _ | _ | _ | _ |PHC| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 37 TYPE_BELT
    _ |PAD| _ | _ | _ | _ | _ | _ |PHC| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 38 TYPE_BELT_1
// ---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

    // clang-format on

};

// EOF
