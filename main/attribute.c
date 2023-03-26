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
};


const int Attribute[TYPE_MAX] = {

// see attribute.h "ObjectType"

#define _ 0

#define RKF ATT_ROCKFORDYBLANK
#define PSH ATT_PUSH
#define WTR 0 /*ATT_WATER*/
#define LAV 0 /*ATT_LAVA*/
#define QUI ATT_NOROCKNOISE
#define XIT ATT_EXIT
#define HRD ATT_HARD
#define SQB ATT_SQUASHABLE_TO_BLANKS
#define ACT ATT_ACTIVE
#define BNG ATT_EXPLODES
#define GRB ATT_GRAB
#define SPC ATT_BLANK
#define PER ATT_PERMEABLE
#define XPD ATT_EXPLODABLE
#define FLY ATT_KILLS_FLY
#define ROL ATT_ROLL
#define DRP ATT_DRIP
#define DRT ATT_DIRT
#define CNR ATT_CORNER
#define PAD ATT_PAD
#define SHV ATT_SHOVE
#define BOU ATT_BOULDER
#define DGE ATT_BOULDER_DOGE
#define MLT ATT_MELTS
#define DIS ATT_DISSOLVES

//  LAV =   Object immediately turns into lava bubbles when below lava line
//  QUI =   Quiet object. No noise genrate when things fall onto it
//  HRD =   Hard. Boulders create dust when falling onto
//  ACT =   Active object that must be processed every frame
//  BNG     Explodes in lava

//  CNR =   surrounding space fills in corner
//  PAD =   do the corner padding for this creature type
//  SHV =   the pushers can push this object if next square blank
//  MLT =   melts when in lava -> CH_LAVA_00
//                                                                                                                          e           k
//                                                                                                                         s           n                       e
//                                                                                                    y       k           i           a                   e   l
//                                                                                                   d       n           o           l       s           l   b   y
//                                                                                                  r       a           n           B       e           b   a   l
//                                                                                                 o       l           k           h   e   d           a   d   F
//                                                                                                f       b   r       c           s   v   o       k   e   o   s
//                                                                                       T   p   k   h   i   e   a   o   t   d   a   i   l   b   n   m   l   l   1
//                                                                                      R   i   c   s   m   t   v   R   i   r   u   t   p   a   a   r   p   l   l
//                                                                                     I   r   o   u   e   a   a   o   x   a   q   c   x   r   l   e   x   i   o
//                                                                                    D   D   R   P   S   W   L   N   E   H   S   A   E   G   B   P   E   K   R
//                                                                                    |   |   |   |   |x  |x  |x  |   |   |   |   |   |   |   |   |   |   |   |
// CNR PAD SHV BOU DGE MLT DIS                                                       --- DRP RKF PSH SSP WTR LAV QUI XIT HRD SQB ACT BNG GRB SPC PER XPD FLY ROL

    _ |PAD| _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ |WTR|LAV|QUI| _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 00 TYPE_SPACE,
   CNR| _ | _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |   DRT|DRP| _ | _ | _ |WTR|LAV| _ | _ | _ | _ | _ | _ | _ | _ |PER|XPD| _ | _  , // 01 TYPE_DIRT,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ |DRP| _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ |XPD| _ |ROL , // 02 TYPE_BRICKWALL,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 03 TYPE_OUTBOX_PRE,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ |XIT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 04 TYPE_OUTBOX,
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ |DRP| _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _  , // 05 TYPE_STEELWALL,
    _ |PAD|SHV|BOU| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ |PSH| _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 06 TYPE_BOULDER,
    _ |PAD|SHV| _ | _ |MLT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 07 TYPE_DOGE,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 08 TYPE_ROCKFORD_PRE,
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ |SQB|ACT| _ | _ | _ | _ |XPD|FLY| _  , // 09 TYPE_ROCKFORD,
   CNR| _ | _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |   DRT|DRP| _ | _ | _ |WTR|LAV| _ | _ | _ | _ |ACT| _ | _ | _ |PER|XPD| _ | _  , // 10 TYPE_PEBBLE1,
   CNR| _ | _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |   DRT|DRP| _ | _ | _ |WTR|LAV| _ | _ | _ | _ |ACT| _ | _ | _ |PER|XPD| _ | _  , // 11 TYPE_PEBBLE2,
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ |WTR|LAV|QUI| _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 12 TYPE_GRAB,
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 13 TYPE_DUST_0,
    // _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 14 TYPE_DUST_1,
    // _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 15 TYPE_DUST_2,
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 16 TYPE_DUST_LEFT,
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 17 TYPE_DUST_RIGHT,
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 18 TYPE_DOGE_FALLING,
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ | _  , // 19 TYPE_BOULDER_FALLING,
    _ |PAD| _ | _ | _ |MLT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG| _ | _ | _ |XPD| _ | _  , // 20 TYPE_DUST_ROCK,
    _ |PAD| _ | _ | _ |MLT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 21 TYPE_DOGE_CONVERT,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ |GRB| _ | _ | _ | _ | _  , // 22 TYPE_SWITCH,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ |ROL , // 23 TYPE_PUSHER,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 24 TYPE_PUSHER_VERT,
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 25 TYPE_WYRM,
    _ |PAD|SHV|BOU|DGE|MLT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ |PSH| _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 26 TYPE_BOULDER_DOGE,
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ | _  , // 27 TYPE_BOULDER_DOGE_FALLING,
    _ |PAD|SHV|BOU|DGE| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ |PSH| _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 28 TYPE_BOULDER_DOGE_CRITICAL,
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ |SPC| _ |XPD| _ | _  , // 29 TYPE_LAVA,
    _ | _ | _ | _ | _ | _ |DIS| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG| _ | _ |PER|XPD| _ | _  , // 30 TYPE_PEBBLE_BOULDER,




#if __ENABLE_LAVA
     , // 47 LAVA
#endif

#if __ENABLE_WATER
     _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 48 WATER
#endif

//  --- DRP RKF PSH SSP WTR LAV QUI XIT HRD SQB ACT BNG GRB SPC PER XPD FLY ROL
//   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
//   D   D   R   P   S   W   L   N   E   H   S   A   E   G   B   P   E   K   R
//    I   r   o   u   e   a   a   o   x   a   q   c   x   r   l   e   x   i   o
//     R   i   c   s   m   t   v   R   i   r   u   t   p   a   a   r   p   l   l
//      T   p   k   h   i   e   a   o   t   d   a   i   l   b   n   m   l   l   1
//               f       b   r       c           s   v   o       k   e   o   s
//                o       l           k           h   e   d               a   d   F
//                 r       a           n           B       e               b   a   l
//                  d       n           o           l       s               l   b   y
//                   y       k           i           a                       e   l
//                                        s           n                           e
//                                         e           k

};


// const unsigned short worstRequiredTime[] = {
// };


