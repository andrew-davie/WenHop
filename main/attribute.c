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
    TYPE_PEBBLE1,               // 008 CH_PEBBLE2,
    TYPE_ROCK,                  // 009 CH_ROCK,
    TYPE_ROCK_FALLING,          // 010 CH_ROCK_FALLING,
    TYPE_DOGE,                  // 011 CH_DOGE_00,
    TYPE_DOGE_FALLING,          // 012 CH_DOGE_FALLING,
    TYPE_MELLON_HUSK_PRE,       // 013 CH_MELLON_HUSK_BIRTH,
    TYPE_LAVA,                  // 014 CH_LAVA_BLANK,
    TYPE_LAVA,                  // 015 CH_LAVA_SMALL,
    TYPE_LAVA,                  // 016 CH_LAVA_MEDIUM,
    TYPE_LAVA,                  // 017 CH_LAVA_LARGE,
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
    TYPE_DUST_0,                // 031 CH_DUST_0,
    TYPE_DUST_0,                // 032 CH_DUST_1,
    TYPE_DUST_0,                // 033 CH_DUST_2,
    TYPE_GEODOGE,               // 034 CH_CONGLOMERATE,
    TYPE_GEODOGE,               // 035 CH_CONGLOMERATE_1,
    TYPE_GEODOGE,               // 036 CH_CONGLOMERATE_2,
    TYPE_GEODOGE,               // 037 CH_CONGLOMERATE_3,
    TYPE_GEODOGE,               // 038 CH_CONGLOMERATE_4,
    TYPE_GEODOGE,               // 039 CH_CONGLOMERATE_5,
    TYPE_GEODOGE,               // 040 CH_CONGLOMERATE_6,
    TYPE_GEODOGE,               // 041 CH_CONGLOMERATE_7,
    TYPE_GEODOGE,               // 042 CH_CONGLOMERATE_8,
    TYPE_GEODOGE,               // 043 CH_CONGLOMERATE_9,
    TYPE_GEODOGE,               // 044 CH_CONGLOMERATE_10,
    TYPE_GEODOGE,               // 045 CH_CONGLOMERATE_11,
    TYPE_GEODOGE,               // 046 CH_CONGLOMERATE_12,
    TYPE_GEODOGE,               // 047 CH_CONGLOMERATE_13,
    TYPE_GEODOGE,               // 048 CH_CONGLOMERATE_14,
    TYPE_GEODOGE,               // 049 CH_CONGLOMERATE_15,
    TYPE_DUST_ROCK,             // 050 CH_DUST_ROCK_0,
    TYPE_DUST_ROCK,             // 051 CH_DUST_ROCK_1,
    TYPE_DUST_ROCK,             // 052 CH_DUST_ROCK_2,
    TYPE_CONVERT_GEODE_TO_DOGE, // 053 CH_CONVERT_GEODE_TO_DOGE,
    TYPE_SWITCH,                // 054 CH_SWITCH_LEFT_OFF,
    TYPE_SWITCH,                // 055 CH_SWITCH_LEFT_ON,
    TYPE_PUSHER,                // 056 CH_HORIZONTAL_BAR,
    TYPE_PUSHER,                // 057 CH_PUSH_LEFT,
    TYPE_PUSHER,                // 058 CH_PUSH_LEFT_REVERSE,
    TYPE_PUSHER,                // 059 CH_PUSH_RIGHT,
    TYPE_PUSHER,                // 060 CH_PUSH_RIGHT_REVERSE,
    TYPE_PUSHER,                // 061 CH_VERTICAL_BAR,
    TYPE_PUSHER,                // 062 CH_PUSH_UP,
    TYPE_PUSHER,                // 063 CH_PUSH_UP_REVERSE,
    TYPE_PUSHER,                // 064 CH_PUSH_DOWN,
    TYPE_PUSHER,                // 065 CH_PUSH_DOWN_REVERSE,
    TYPE_WYRM,                  // 066 CH_WYRM_BODY,
    TYPE_WYRM,                  // 067 CH_WYRM_VERT_BODY,
    TYPE_WYRM,                  // 068 CH_WYRM_CORNER_LD,
    TYPE_WYRM,                  // 069 CH_WYRM_CORNER_RD,
    TYPE_WYRM,                  // 070 CH_WYRM_CORNER_LU,
    TYPE_WYRM,                  // 071 CH_WYRM_CORNER_RU,
    TYPE_WYRM,                  // 072 CH_WYRM_HEAD_U,
    TYPE_WYRM,                  // 073 CH_WYRM_HEAD_R,
    TYPE_WYRM,                  // 074 CH_WYRM_HEAD_D,
    TYPE_WYRM,                  // 075 CH_WYRM_HEAD_L,
    TYPE_ROCK,                  // 076 CH_CONGLOMERATE_MID,
    TYPE_GEODOGE_FALLING,       // 077 CH_GEODOGE_FALLING,
    TYPE_FLIP_GRAVITY,          // 078 CH_FLIP_GRAVITY_0,
    TYPE_FLIP_GRAVITY,          // 079 CH_FLIP_GRAVITY_1,
    TYPE_FLIP_GRAVITY,          // 080 CH_FLIP_GRAVITY_2,
    TYPE_BLOCK,                 // 081 CH_BLOCK,
    TYPE_GRINDER,               // 082 CH_GRINDER_0,
    TYPE_GRINDER_1,             // 083 CH_GRINDER_1
    TYPE_HUB,                   // 084 CH_HUB,
    TYPE_WATER,                 // 085 CH_WATER_0
    TYPE_WATERFLOW_0,           // 086 CH_WATERFLOW_0
    TYPE_WATERFLOW_1,           // 087 CH_WATERFLOW_1
    TYPE_WATERFLOW_2,           // 088 CH_WATERFLOW_2
    TYPE_WATERFLOW_3,           // 089 CH_WATERFLOW_3
    TYPE_WATERFLOW_4,           // 090 CH_WATERFLOW_4
    TYPE_TAP,                   // 091 CH_TAP_0
    TYPE_HUB,                   // 092 CH_HUB_1
    TYPE_OUTLET,                // 093 CH_OUTLET
    TYPE_TAP,                   // 094 CH_TAP_1
    TYPE_BELT,                  // 095 CH_BELT_0
    TYPE_BELT_1,                // 096 CH_BELT_1
    TYPE_PUSHER,                // 097 CH_PUSH_DOWN2
    TYPE_CONVERT_GEODE_TO_DOGE, // 098 CH_GEODOGE_CONVERT  (deprecated)
    TYPE_CONVERT_PIPE,          // 099 CH_CONVERT_PIPE
    TYPE_WYRM,                  // 100 CH_WYRM_TAIL_U,
    TYPE_WYRM,                  // 101 CH_WYRM_HEAD_R,
    TYPE_WYRM,                  // 102 CH_WYRM_HEAD_D,
    TYPE_WYRM,                  // 103 CH_WYRM_HEAD_L,
    TYPE_DOGE_FALLING,          // 104 CH_DOGE_FALLING_TOP,
    TYPE_DOGE_FALLING,          // 105 CH_DOGE_FALLING_BOTTOM,
    TYPE_ROCK_FALLING,          // 106 CH_ROCK_FALLING_TOP,
    TYPE_ROCK_FALLING,          // 107 CH_ROCK_FALLING_BOTTOM,
    TYPE_GEODOGE_FALLING,       // 108 CH_GEODOGE_FALLING_TOP,
    TYPE_GEODOGE_FALLING,       // 109 CH_GEODOGE_FALLING_BOTTOM,
    TYPE_DOGE_FALLING2,         // 110 CH_DOGE_FALLING_TOP2,
    TYPE_DOGE_FALLING2,         // 111 CH_DOGE_FALLING_BOTTOM2,
    TYPE_DOGE_FALLING2,         // 112 CH_DOGE_SIDE_1
    TYPE_DOGE_FALLING2,         // 113 CH_DOGE_SIDE_3
    TYPE_DOGE_FALLING2,         // 114 CH_DOGE_SIDE_2
    TYPE_DOGE_FALLING2,         // 115 CH_DOGE_SIDE_4
};

// clang-format off

enum AttributeAlias {

    ROL = ATT_ROLL,                     // doge should roll off this object
    CVT = ATT_CONVERT,                  // iff below surface, object converts to lava or water
    XPD = ATT_EXPLODABLE,               // object is destroyed in explosions
    PER = ATT_PERMEABLE,                // square is 'permeable' (not solid/not blank)
    SPC = ATT_BLANK,                    // object is blank
    DRT = ATT_DIRT,                     // object is dirt
    GRB = ATT_GRAB,                     // doge
    PSH = ATT_PUSH,
    SQB = ATT_SQUASHABLE_TO_BLANKS,
    HRD = ATT_HARD,                     // Hard. rocks create dust when falling onto
    XIT = ATT_EXIT,
    QUI = ATT_NOROCKNOISE,
    RKF = ATT_BLANKISH,
    MIN = ATT_MINE,
    WTF = ATT_WATERFLOW,
    CVY = ATT_CONVEYOR,
    GND = ATT_GRIND,
    PIP = ATT_PIPE,
    PH4 = ATT_PHASE4,                   // processed every 4 frames
    PH2 = ATT_PHASE2,                   // processed every 2 frames
    PH1 = ATT_PHASE1,                   // processed every 1 frame
    DIS = ATT_DISSOLVES,
    MLT = ATT_MELTS,
    DGE = ATT_GEODOGE,                  // a geodoge
    PAD = ATT_PAD,                      // add dirt corners to this object square
    CNR = ATT_CORNER,                   // this object contributes to making a dirt corner
};


const unsigned int Attribute[TYPE_MAX] = {

// see attribute.h "ObjectType"

#define _ 0

    // clang-format off

// CNR PAD DGE MLT DIS PH* PIP GND CVY WTF MIN RKF QUI XIT HRD SQB PSH GRB DRT SPC PER XPD CVT ROL
// ---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ |RKF|QUI| _ | _ | _ | _ | _ | _ |SPC|PER|XPD|CVT| _  , // 00 TYPE_SPACE,
   CNR| _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD|CVT| _  , // 01 TYPE_DIRT,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ |XPD| _ |ROL , // 02 TYPE_BRICKWALL,
    _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _  , // 03 TYPE_OUTBOX_PRE,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |XIT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 04 TYPE_OUTBOX,
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _  , // 05 TYPE_STEELWALL,
    _ |PAD| _ |MLT| _ |PH1| _ |GND|CVY| _ |MIN| _ | _ | _ |HRD| _ |PSH| _ | _ | _ | _ |XPD| _ |ROL , // 06 TYPE_ROCK,
    _ |PAD| _ |MLT| _ |PH4| _ |GND|CVY| _ | _ | _ | _ | _ | _ | _ |PSH|GRB| _ | _ | _ |XPD| _ |ROL , // 07 TYPE_DOGE,
    _ |PAD| _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 08 TYPE_MELLON_HUSK_PRE,
    _ |PAD| _ | _ | _ |PH1| _ | _ | _ | _ | _ |RKF|QUI| _ | _ |SQB|PSH| _ | _ | _ | _ |XPD| _ | _  , // 09 TYPE_MELLON_HUSK,
   CNR| _ | _ | _ |DIS|PH4| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD| _ | _  , // 10 TYPE_PEBBLE1,
    _ |PAD| _ | _ | _ |PH2| _ | _ | _ | _ | _ |RKF|QUI| _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 11 TYPE_DUST_0,
    _ |PAD| _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |PSH| _ | _ | _ | _ |XPD| _ |ROL , // 12 TYPE_DOGE_FALLING,
    _ |PAD| _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |PSH| _ | _ | _ | _ |XPD| _ | _  , // 13 TYPE_ROCK_FALLING,
    _ |PAD| _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 14 TYPE_DUST_ROCK,
    _ |PAD| _ |MLT| _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |XPD| _ |ROL , // 15 TYPE_CONVERT_GEODE_TO_DOGE
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |GRB| _ | _ | _ | _ | _ | _  , // 16 TYPE_SWITCH,
    _ | _ | _ | _ | _ |PH1|PIP| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 17 TYPE_PUSHER,
    _ | _ | _ | _ | _ |PH1|PIP| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 18 TYPE_PUSHER_VERT,
    _ |PAD| _ | _ | _ |PH4| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 19 TYPE_WYRM,
    _ |PAD|DGE|MLT| _ |PH2| _ |GND|CVY| _ |MIN| _ | _ | _ |HRD| _ |PSH| _ | _ | _ | _ |XPD| _ |ROL , // 20 TYPE_GEODOGE,
    _ |PAD| _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |PSH| _ | _ | _ | _ |XPD| _ | _  , // 21 TYPE_GEODOGE_FALLING,
    _ |PAD|DGE| _ | _ |PH2| _ | _ | _ | _ |MIN| _ | _ | _ |HRD| _ |PSH| _ | _ | _ | _ |XPD| _ |ROL , // 22 TYPE_GEODOGE_CRITICAL
    _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ |SPC|PER| _ | _ | _  , // 23 TYPE_LAVA,
    _ |PAD| _ | _ |DIS|PH4| _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ |PER|XPD| _ | _  , // 24 TYPE_PEBBLE_ROCK,
    _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD| _ | _  , // 25 TYPE_FLIP_GRAVITY
    _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _  , // 26 TYPE_BLOCK
    _ |PAD| _ | _ | _ |PH4| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 27 TYPE_GRINDER
    _ | _ | _ | _ | _ |PH4|PIP| _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _  , // 28 TYPE_HUB
    _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 29 TYPE_WATER
    _ | _ | _ | _ |DIS|PH1| _ | _ | _ |WTF| _ |RKF| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD|CVT| _  , // 30 TYPE_WATERFLOW0
    _ | _ | _ | _ |DIS|PH1| _ | _ | _ |WTF| _ |RKF| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD|CVT| _  , // 31 TYPE_WATERFLOW1
    _ | _ | _ | _ |DIS|PH1| _ | _ | _ |WTF| _ |RKF| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD|CVT| _  , // 32 TYPE_WATERFLOW2
    _ | _ | _ | _ |DIS|PH1| _ | _ | _ |WTF| _ |RKF| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD|CVT| _  , // 33 TYPE_WATERFLOW3
    _ | _ | _ | _ |DIS|PH1| _ | _ | _ |WTF| _ |RKF| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD|CVT| _  , // 34 TYPE_WATERFLOW4
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 35 TYPE_TAP
    _ | _ | _ | _ | _ |PH1|PIP| _ | _ |WTF| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 36 TYPE_OUTLET
    _ |PAD| _ | _ | _ |PH4| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 37 TYPE_GRINDER1
    _ |PAD| _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 38 TYPE_BELT
    _ |PAD| _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 39 TYPE_BELT_1
    _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 40 TYPE_CONVERT_PIPE
    _ |PAD| _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |PSH| _ | _ | _ | _ |XPD| _ | _  , // 41 TYPE_DOGE_FALLING2
// ---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

    // clang-format on

};

// EOF
