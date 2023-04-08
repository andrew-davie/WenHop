// Object attributes

    #include "attribute.h"

const unsigned char CharToType[CH_MAX]= {

    // see ChName for corresponding character name/number
    // may need to update worstRequiredTime if that's in use

    TYPE_SPACE,                     // 000 CH_BLANK,
    TYPE_DIRT,                      // 001 CH_DIRT,
    TYPE_BRICKWALL,                 // 002 CH_BRICKWALL,
    TYPE_OUTBOX_PRE,                // 003 CH_DOORCLOSED,
    TYPE_OUTBOX,                    // 004 CH_DOOROPEN_0,
    TYPE_STEELWALL,                 // 005 CH_EXITBLANK,
    TYPE_STEELWALL,                 // 006 CH_STEELWALL,
    TYPE_PEBBLE1,                   // 007 CH_PEBBLE1,
    TYPE_PEBBLE2,                   // 008 CH_PEBBLE2,
    TYPE_BOULDER,                   // 009 CH_BOULDER,
    TYPE_BOULDER_FALLING,           // 010 CH_BOULDER_FALLING,
    TYPE_DOGE,                      // 011 CH_DOGE_00,
    TYPE_DOGE_FALLING,              // 012 CH_DOGE_FALLING,
    TYPE_ROCKFORD_PRE,              // 013 CH_ROCKFORD_BIRTH,
    TYPE_LAVA,                      // 014 CH_LAVA_0,
    TYPE_LAVA,                      // 015 CH_LAVA_1,
    TYPE_LAVA,                      // 016 CH_LAVA_2,
    TYPE_LAVA,                      // 017 CH_LAVA_3,
    TYPE_ROCKFORD,                  // 018 CH_ROCKFORD,
    TYPE_DOGE,                      // 019 CH_DOGE_01,
    TYPE_DOGE,                      // 020 CH_DOGE_02,
    TYPE_DOGE,                      // 021 CH_DOGE_03,
    TYPE_DOGE,                      // 022 CH_DOGE_04,
    TYPE_DOGE,                      // 023 CH_DOGE_05,
    TYPE_DOGE,                      // 024 CH_DOGE_STATIC,
    TYPE_PEBBLE_BOULDER,            // 025 CH_PEBBLE_BOULDER,
    TYPE_SPACE,                     // 026 CH_EXPLODETOBLANK_0,
    TYPE_SPACE,                     // 027 CH_EXPLODETOBLANK_1,
    TYPE_SPACE,                     // 028 CH_EXPLODETOBLANK_2,
    TYPE_SPACE,                     // 029 CH_EXPLODETOBLANK_3,
    TYPE_SPACE,                     // 030 CH_EXPLODETOBLANK_4,
    TYPE_GRAB,                      // 031 CH_DOGE_GRAB,
    TYPE_DUST_0,                    // 032 CH_DUST_0,
    TYPE_DUST_0,                    // 033 CH_DUST_1,
    TYPE_DUST_0,                    // 034 CH_DUST_2,
    TYPE_BOULDER_DOGE,              // 035 CH_CONGLOMERATE,
    TYPE_BOULDER_DOGE,              // 036 CH_CONGLOMERATE_1,
    TYPE_BOULDER_DOGE,              // 037 CH_CONGLOMERATE_2,
    TYPE_BOULDER_DOGE,              // 038 CH_CONGLOMERATE_3,
    TYPE_BOULDER_DOGE,              // 039 CH_CONGLOMERATE_4,
    TYPE_BOULDER_DOGE,              // 040 CH_CONGLOMERATE_5,
    TYPE_BOULDER_DOGE,              // 041 CH_CONGLOMERATE_6,
    TYPE_BOULDER_DOGE,              // 042 CH_CONGLOMERATE_7,
    TYPE_BOULDER_DOGE,              // 043 CH_CONGLOMERATE_8,
    TYPE_BOULDER_DOGE,              // 044 CH_CONGLOMERATE_9,
    TYPE_BOULDER_DOGE,              // 045 CH_CONGLOMERATE_10,
    TYPE_BOULDER_DOGE,              // 046 CH_CONGLOMERATE_11,
    TYPE_BOULDER_DOGE,              // 047 CH_CONGLOMERATE_12,
    TYPE_BOULDER_DOGE,              // 048 CH_CONGLOMERATE_13,
    TYPE_BOULDER_DOGE,              // 049 CH_CONGLOMERATE_14,
    TYPE_BOULDER_DOGE_CRITICAL,     // 050 CH_CONGLOMERATE_15,
    TYPE_DUST_ROCK,                 // 051 CH_DUST_ROCK_0,
    TYPE_DUST_ROCK,                 // 052 CH_DUST_ROCK_1,
    TYPE_DUST_ROCK,                 // 053 CH_DUST_ROCK_2,
    TYPE_DOGE_CONVERT,              // 054 CH_DOGE_CONVERT,
    TYPE_SWITCH,                    // 055 CH_SWITCH_LEFT_OFF,
    TYPE_SWITCH,                    // 056 CH_SWITCH_LEFT_ON,
    TYPE_PUSHER,                    // 057 CH_HORIZONTAL_BAR,
    TYPE_PUSHER,                    // 058 CH_PUSH_LEFT,
    TYPE_PUSHER,                    // 059 CH_PUSH_LEFT_REVERSE,
    TYPE_PUSHER,                    // 060 CH_PUSH_RIGHT,
    TYPE_PUSHER,                    // 061 CH_PUSH_RIGHT_REVERSE,
    TYPE_PUSHER,                    // 062 CH_VERTICAL_BAR,
    TYPE_PUSHER,                    // 063 CH_PUSH_UP,
    TYPE_PUSHER,                    // 064 CH_PUSH_UP_REVERSE,
    TYPE_PUSHER,                    // 065 CH_PUSH_DOWN,
    TYPE_PUSHER,                    // 066 CH_PUSH_DOWN_REVERSE,
    TYPE_WYRM,                      // 067 CH_WYRM_BODY,
    TYPE_WYRM,                      // 068 CH_WYRM_VERT_BODY,
    TYPE_WYRM,                      // 069 CH_WYRM_CORNER_LD,
    TYPE_WYRM,                      // 070 CH_WYRM_CORNER_RD,
    TYPE_WYRM,                      // 071 CH_WYRM_CORNER_LU,
    TYPE_WYRM,                      // 072 CH_WYRM_CORNER_RU,
    TYPE_WYRM,                      // 073 CH_WYRM_HEAD_U,
    TYPE_WYRM,                      // 074 CH_WYRM_HEAD_R,
    TYPE_WYRM,                      // 075 CH_WYRM_HEAD_D,
    TYPE_WYRM,                      // 076 CH_WYRM_HEAD_L,
    TYPE_SPACE,                     // 077 CH_CORNER_0,
    TYPE_SPACE,                     // 078 CH_CORNER_1,
    TYPE_SPACE,                     // 079 CH_CORNER_2,
    TYPE_SPACE,                     // 080 CH_CORNER_3,
    TYPE_SPACE,                     // 081 CH_CORNER_4,
    TYPE_SPACE,                     // 082 CH_CORNER_5,
    TYPE_SPACE,                     // 083 CH_CORNER_6,
    TYPE_SPACE,                     // 084 CH_CORNER_7,
    TYPE_SPACE,                     // 085 CH_CORNER_8,
    TYPE_SPACE,                     // 086 CH_CORNER_9,
    TYPE_SPACE,                     // 087 CH_CORNER_10,
    TYPE_SPACE,                     // 088 CH_CORNER_11,
    TYPE_SPACE,                     // 089 CH_CORNER_12,
    TYPE_SPACE,                     // 090 CH_CORNER_13,
    TYPE_SPACE,                     // 091 CH_CORNER_14,
    TYPE_SPACE,                     // 092 CH_CORNER_15,
    TYPE_BOULDER,                   // 093 CH_CONGLOMERATE_MID,
    TYPE_BOULDER_DOGE,              // 094 CH_BOULDER_DOGE,
    TYPE_BOULDER_DOGE_FALLING,      // 095 CH_BOULDER_DOGE_FALLING,
    TYPE_FLIP_GRAVITY,              // 096 CH_FLIP_GRAVITY_0,
    TYPE_FLIP_GRAVITY,              // 097 CH_FLIP_GRAVITY_1,
    TYPE_FLIP_GRAVITY,              // 098 CH_FLIP_GRAVITY_2,
    TYPE_ZAP,                       // 099 CH_HORIZ_ZAP_0,
    TYPE_ZAP,                       // 100 CH_HORIZ_ZAP_1,
    TYPE_ZAP,                       // 101 CH_HORIZ_ZAP_2,
    TYPE_BLOCK,                     // 102 CH_BLOCK,
    TYPE_PACMAN_DOT,                // 103 CH_PACMAN_DOT,
    TYPE_AIRHOSE,                   // 104 CH_HORIZ_ZAP_3,
    TYPE_HUB,                       // 105 CH_HUB,
    TYPE_WATER,                     // 106 CH_WATER_0
    TYPE_WATER,                     // 107 CH_WATER_1
    TYPE_WATER,                     // 108 CH_WATER_2
    TYPE_WATER,                     // 109 CH_WATER_3
};


const int Attribute[TYPE_MAX] = {

// see attribute.h "ObjectType"

#define _ 0


//  LAV =   Object immediately turns into lava bubbles when below lava line
//  QUI =   Quiet object. No noise genrate when things fall onto it
//  HRD =   Hard. Boulders create dust when falling onto
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
//                                    21
//                                   22
//  31  30  29  28  27  26  25  24  23  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0
// CNR PAD SHV BOU DGE MLT DIS PUL PH*                 MIN DRP RKF LAV QUI XIT HRD SQB     BNG GRB DRT SPC PER XPD     ROL
// ---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    _ |PAD| _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ | _ |RKF|LAV|QUI| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 00 TYPE_SPACE,
   CNR| _ | _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ |DRP| _ |LAV| _ | _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD| _ | _  , // 01 TYPE_DIRT,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |DRP| _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 02 TYPE_BRICKWALL,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 03 TYPE_OUTBOX_PRE,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |XIT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 04 TYPE_OUTBOX,
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |DRP| _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 05 TYPE_STEELWALL,
    _ |PAD|SHV|BOU| _ | _ | _ |PUL|PH2| _ | _ | _ | _ |MIN| _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 06 TYPE_BOULDER,
    _ |PAD|SHV| _ | _ |MLT| _ |PUL|PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |BNG|GRB| _ | _ | _ |XPD| _ |ROL , // 07 TYPE_DOGE,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 08 TYPE_ROCKFORD_PRE,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ |QUI| _ | _ |SQB| _ | _ | _ | _ | _ | _ |XPD| _ | _  , // 09 TYPE_ROCKFORD,
   CNR| _ | _ | _ | _ | _ |DIS| _ |PH4| _ | _ | _ | _ | _ |DRP| _ |LAV| _ | _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD| _ | _  , // 10 TYPE_PEBBLE1,
   CNR| _ | _ | _ | _ | _ |DIS| _ |PH4| _ | _ | _ | _ | _ |DRP| _ |LAV| _ | _ | _ | _ | _ | _ | _ |DRT| _ |PER|XPD| _ | _  , // 11 TYPE_PEBBLE2,
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |RKF|LAV|QUI| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 12 TYPE_GRAB,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ |QUI| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 13 TYPE_DUST_0,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 14 TYPE_DOGE_FALLING,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ | _  , // 15 TYPE_BOULDER_FALLING,
    _ |PAD| _ | _ | _ |MLT| _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |BNG| _ | _ | _ | _ |XPD| _ | _  , // 16 TYPE_DUST_ROCK,
    _ |PAD| _ | _ | _ |MLT| _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 17 TYPE_DOGE_CONVERT,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |GRB| _ | _ | _ | _ | _ | _  , // 18 TYPE_SWITCH,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ROL , // 19 TYPE_PUSHER,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 20 TYPE_PUSHER_VERT,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 21 TYPE_WYRM,
    _ |PAD|SHV|BOU|DGE|MLT| _ |PUL|PH2| _ | _ | _ | _ |MIN| _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 22 TYPE_BOULDER_DOGE,
    _ |PAD| _ | _ | _ | _ | _ | _ |PH2| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ | _  , // 23 TYPE_BOULDER_DOGE_FALLING,
    _ |PAD|SHV|BOU|DGE| _ | _ | _ |PH2| _ | _ | _ | _ |MIN| _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ | _ |XPD| _ |ROL , // 24 TYPE_BOULDER_DOGE_CRITICAL,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ | _ |SPC| _ |XPD| _ | _  , // 25 TYPE_LAVA,
    _ |PAD| _ | _ | _ | _ |DIS| _ |PH4| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ |BNG| _ | _ | _ |PER|XPD| _ | _  , // 26 TYPE_PEBBLE_BOULDER,
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ |BNG| _ |DRT| _ |PER|XPD| _ | _  , // 27 TYPE_FLIP_GRAVITY
    _ |PAD| _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ |DRP| _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 28 TYPE_ZAP
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 29 TYPE_BLOCK
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 30 TYPE_BLOCK
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |RKF| _ |QUI| _ | _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 31 TYPE_AIRHOSE
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |DRP| _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 32 TYPE_HUB
    _ | _ | _ | _ | _ | _ | _ | _ |PH1| _ | _ | _ | _ | _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ | _ |SPC| _ |XPD| _ | _  , // 33 TYPE_WATER
// ---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+


};


// const unsigned short worstRequiredTime[] = {
// };


