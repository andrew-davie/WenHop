// Object attributes

    #include "attribute.h"

const unsigned char CharToType[]= {

    // see ChName for corresponding character name/number
    // may need to update worstRequiredTime if that's in use

     TYPE_SPACE,                  // CH_BLANK,                   // 0
     TYPE_DIRT,                   // CH_DIRT,                    // 1
     TYPE_BRICKWALL,              // CH_BRICKWALL,               // 2
     TYPE_MAGICWALL,              // CH_MAGICWALL,               // 3
     TYPE_OUTBOX_PRE,             // CH_STEELWALL,               // 4 exit door closed
     TYPE_OUTBOX,                 // CH_DOOROPEN_0,              // 5 exit door (open)
     TYPE_STEELWALL,              // CH_EXITBLANK,               // 6 blank exit after player walks through
     TYPE_STEELWALL,              // CH_STEELWALL,               // 7
     TYPE_FIREFLY,                // CH_FIREFLY_0,               // 8
     TYPE_FIREFLY,                // CH_FIREFLY_1,               // 9
     TYPE_FIREFLY,                // CH_FIREFLY_2,               // 10
     TYPE_FIREFLY,                // CH_FIREFLY_3,               // 11
     TYPE_PEBBLE1,                // CH_PEBBLE1,                 // 12
     TYPE_PEBBLE2,                // CH_PEBBLE2,                 // 13
     TYPE_EASTEREGG,              // CH_EASTEREGG                // 14
     TYPE_BOULDER,                // CH_BOULDER,                 // 15
     TYPE_BOULDER_FALLING,        // CH_BOULDER_FALLING,         // 16
     TYPE_DOGE,                   // CH_DOGE_00,                 // 17
     TYPE_DOGE_FALLING,           // CH_DOGE_FALLING,            // 18
     TYPE_EXPLODE_DIAMOND_0,      // CH_EXPLODETODIAMOND1,       // 19
     TYPE_EXPLODE_DIAMOND_1,      // CH_EXPLODETODIAMOND2,       // 20
     TYPE_EXPLODE_DIAMOND_2,      // CH_EXPLODETODIAMOND3,       // 21
     TYPE_EXPLODE_DIAMOND_3,      // CH_EXPLODETODIAMOND4,       // 22
     TYPE_EXPLODE_DIAMOND_4,      // CH_EXPLODETODIAMOND5,       // 23
     TYPE_ROCKFORD_PRE,           // CH_ROCKFORD_BIRTH,          // 24
     TYPE_MAGICWALL,              // CH_MAGICWALL_1              // 25
     TYPE_MAGICWALL,              // CH_MAGICWALL_2              // 26
     TYPE_MAGICWALL,              // CH_MAGICWALL_3              // 27
     TYPE_BUTTERFLY,              // CH_BUTTERFLY_0,             // 28
     TYPE_BUTTERFLY,              // CH_BUTTERFLY_1,             // 29
     TYPE_BUTTERFLY,              // CH_BUTTERFLY_2,             // 30
     TYPE_BUTTERFLY,              // CH_BUTTERFLY_2,             // 31
     TYPE_AMOEBA,                 // CH_AMOEBA0,                 // 32
     TYPE_AMOEBA,                 // CH_AMOEBA1,                 // 33
     TYPE_AMOEBA,                 // CH_AMOEBA2,                 // 34
     TYPE_AMOEBA,                 // CH_AMOEBA3,                 // 35
     TYPE_ROCKFORD,               // CH_ROCKFORD                 // 36
     TYPE_DIAMOND_PULSE_0,        // CH_DIAMOND_PULSE_0,         // 37
     TYPE_DIAMOND_PULSE_1,        // CH_DIAMOND_PULSE_1,         // 38
     TYPE_DIAMOND_PULSE_2,        // CH_DIAMOND_PULSE_2,         // 39
     TYPE_DIAMOND_PULSE_3,        // CH_DIAMOND_PULSE_3,         // 40
     TYPE_DIAMOND_PULSE_4,        // CH_DIAMOND_PULSE_4,         // 41
     TYPE_DIAMOND_PULSE_5,        // CH_DIAMOND_PULSE_5,         // 42
     TYPE_DIAMOND_PULSE_6,        // CH_DIAMOND_PULSE_6,         // 43
     TYPE_DIAMOND_STATIC,         // CH_DIAMOND_STATIC,          // 44
     TYPE_LADDER,                                                // 45
     TYPE_LADDER,                                                // 46
     TYPE_LADDER,                                                // 47
     TYPE_SPACE,                  // CH_SPARKLE_3                // 48
     TYPE_EXPLODE_BLANK_0,        // CH_EXPLODETOBLANK_0,        // 49
     TYPE_EXPLODE_BLANK_1,        // CH_EXPLODETOBLANK_1,        // 50
     TYPE_EXPLODE_BLANK_2,        // CH_EXPLODETOBLANK_2,        // 51
     TYPE_EXPLODE_BLANK_3,        // CH_EXPLODETOBLANK_3,        // 52
     TYPE_EXPLODE_BLANK_4,        // CH_EXPLODETOBLANK_4,        // 53
     TYPE_GRAB,                   // CH_DOGE_GRAB,               // 54
     TYPE_DIAMOND_WITHOUT_DIRT,   // CH_DIAMOND_WITHOUT_DIRT,    // 55
     TYPE_DUST_0,                 // CH_DUST_0,                  // 56
     TYPE_DUST_1,                 // CH_DUST_1,                  // 57
     TYPE_DUST_2,                 // CH_DUST_2,                  // 58
     TYPE_BOULDER_SHAKE,          // CH_BOULDER_SHAKE            // 59
     TYPE_DUST_LEFT,              // CH_DUST_LEFT_0              // 60
     TYPE_DUST_LEFT,              // CH_DUST_LEFT_1              // 61
     TYPE_DUST_RIGHT,             // CH_DUST_RIGHT_0             // 62
     TYPE_DUST_RIGHT,             // CH_DUST_RIGHT_1             // 63

     TYPE_BOULDER_DOGE,                                          // 64     conglomerate 0
     TYPE_BOULDER_DOGE,                                          // 65     conglomerate 1
     TYPE_BOULDER_DOGE,                                          // 66     conglomerate 2
     TYPE_BOULDER_DOGE,                                          // 67     conglomerate 3
     TYPE_BOULDER_DOGE,                                          // 68     conglomerate 4
     TYPE_BOULDER_DOGE,                                          // 69     conglomerate 5
     TYPE_BOULDER_DOGE,                                          // 70     conglomerate 6
     TYPE_BOULDER_DOGE,                                          // 71     conglomerate 7
     TYPE_BOULDER_DOGE,                                          // 72     conglomerate 8
     TYPE_BOULDER_DOGE,                                          // 73     conglomerate 9
     TYPE_BOULDER_DOGE,                                          // 74     conglomerate 10
     TYPE_BOULDER_DOGE,                                          // 75     conglomerate 11
     TYPE_BOULDER_DOGE,                                          // 76     conglomerate 12
     TYPE_BOULDER_DOGE,                                          // 77     conglomerate 13
     TYPE_BOULDER_DOGE,                                          // 78     conglomerate 14
     TYPE_BOULDER_DOGE_CRITICAL,                                 // 79     conglomerate 15

     TYPE_BOULDER_FALLING,                                       // 80     broken
     TYPE_BOULDER_FALLING,                                       // 81     broken2

     TYPE_DUST_ROCK,                 // CH_DUST_ROCK_0,          // 82
     TYPE_DUST_ROCK,                 // CH_DUST_ROCK_1,          // 83
     TYPE_DUST_ROCK,                 // CH_DUST_ROCK_2,          // 84

     TYPE_DOGE_CONVERT,              // CH_DOGE_CONVERT,         // 85

     TYPE_SWITCH,                    // CH_SWITCH_LEFT_OFF       // 86
     TYPE_SWITCH,                    // CH_SWITCH_LEFT_ON        // 87
     TYPE_PUSHER,                    // CH_PUSH_LEFT             // 88
     TYPE_PUSHER,                    // CH_HORIZONTAL_BAR        // 89
     TYPE_PUSHER,                    // CH_PUSH_RIGHT            // 90
     TYPE_PUSHER,                    // CH_PUSH_LEFT_REVERSE     // 91
     TYPE_PUSHER,                    // CH_PUSH_RIGHT_REVERSE    // 92

     TYPE_PUSHER_VERT,               // CH_PUSH_UP               // 93
     TYPE_PUSHER_VERT,               // CH_VERTICAL_BAR          // 94
     TYPE_PUSHER_VERT,               // CH_PUSH_DOWN             // 95
     TYPE_PUSHER_VERT,               // CH_PUSH_UP_REVERSE       // 96
     TYPE_PUSHER_VERT,               // CH_PUSH_DOWN_REVERSE     // 97

     TYPE_WYRM,                      // CH_WYRM_HEAD             // 98
     TYPE_WYRM,                      // CH_WYRM_BODY             // 99
     TYPE_WYRM,                      // CH_WYRM_VERT_BODY        // 100

     TYPE_WYRM,                      // CH_WYRM_CORNER_LD        // 101
     TYPE_WYRM,                      // CH_WYRM_CORNER_RD        // 102
     TYPE_WYRM,                      // CH_WYRM_CORNER_LU        // 103
     TYPE_WYRM,                      // CH_WYRM_CORNER_RU        // 104

     TYPE_WYRM,                      // CH_WYRM_HEAD_U           // 105
     TYPE_WYRM,                      // CH_WYRM_HEAD_R           // 106
     TYPE_WYRM,                      // CH_WYRM_HEAD_D           // 107
     TYPE_WYRM,                      // CH_WYRM_HEAD_L           // 108

     TYPE_SPACE,                      // CH_CORNER_00                  // 109
     TYPE_SPACE,                      // CH_CORNER_01                  // 110
     TYPE_SPACE,                      // CH_CORNER_02                  // 111
     TYPE_SPACE,                      // CH_CORNER_03                  // 112
     TYPE_SPACE,                      // CH_CORNER_04                  // 113
     TYPE_SPACE,                      // CH_CORNER_05                  // 114
     TYPE_SPACE,                      // CH_CORNER_06                  // 115
     TYPE_SPACE,                      // CH_CORNER_07                  // 116
     TYPE_SPACE,                      // CH_CORNER_08                  // 117
     TYPE_SPACE,                      // CH_CORNER_09                  // 118
     TYPE_SPACE,                      // CH_CORNER_10                  // 119
     TYPE_SPACE,                      // CH_CORNER_11                  // 120
     TYPE_SPACE,                      // CH_CORNER_12                  // 121
     TYPE_SPACE,                      // CH_CORNER_13                  // 122
     TYPE_SPACE,                      // CH_CORNER_14                  // 123
     TYPE_SPACE,                      // CH_CORNER_15                  // 124

     TYPE_BOULDER,                  // CH_BOULDER_UDLR2

     TYPE_BOULDER_DOGE,                  // CH_BOULDER_DOGE                 // 126
     TYPE_BOULDER_DOGE_FALLING,          // CH_BOULDER_DOGE_FALLING         // 127


// #if __ENABLE_WATER
// TYPE_WATER,                  // CH_WATER                    // 73
// TYPE_WATER,                  // CH_WATER1                   // 74
// TYPE_WATER,                  // CH_WATER2                   // 75
// TYPE_WATER,                  // CH_WATER3                   // 76
// #endif

};


const int Attribute[] = {

// index via ObjectType value

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


//  LAV =   Object immediately turns into lava bubbles when below lava line
//  QUI =   Quiet object. No noise genrate when things fall onto it
//  HRD =   Hard. Boulders create dust when falling onto
//  ACT =   Active object that must be processed every frame
//  BNG     Explodes in lava

//  CNR =   surrounding space fills in corner
//  PAD =   do the corner padding for this creature type
//  SHV =   the pushers can push this object if next square blank

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
// CNR                                                                               --- DRP RKF PSH SSP WTR LAV QUI XIT HRD SQB ACT BNG GRB SPC PER XPD FLY ROL

    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ |WTR|LAV|QUI| _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 0 TYPE_SPACE
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |   DRT|DRP| _ | _ | _ |WTR|LAV| _ | _ | _ | _ | _ | _ | _ | _ |PER|XPD| _ | _  , // 1 TYPE_DIRT
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ |DRP| _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ |BNG| _ | _ | _ |XPD| _ |ROL , // 2 TYPE_BRICKWALL
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ |DRP| _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 3 TYPE_MAGICWALL
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 4 TYPE_OUTBOX_PRE
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ |XIT| _ | _ | _ | _ | _ | _ | _ | _ | _ | _  , // 5 TYPE_OUTBOX
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ |DRP| _ | _ | _ | _ | _ | _ | _ |HRD| _ | _ | _ | _ | _ | _ | _ | _ | _  , // 6 TYPE_STEELWALL
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ |WTR|LAV| _ | _ | _ |SQB|ACT| _ | _ | _ | _ |XPD| _ | _  , // 7 TYPE_FIREFLY
    _ |PAD|SHV|BOU| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ |PSH| _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 8 TYPE_BOULDER
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 9 TYPE_DOGE
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ |DRP| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |PER| _ | _ | _  , // 10 TYPE_EASTEREGG
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 11 TYPE_EXPLODE_DIAMOND_0
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 12 TYPE_EXPLODE_DIAMOND_1
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 13 TYPE_EXPLODE_DIAMOND_2
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 14 TYPE_EXPLODE_DIAMOND_3
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 15 TYPE_EXPLODE_DIAMOND_4
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 16 TYPE_ROCKFORD_PRE
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ |WTR| _ |LAV| _ | _ | _ | _ |ACT| _ | _ | _ | _ |XPD| _ | _  , // 17 TYPE_BUTTERFLY
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ |SQB|ACT| _ | _ | _ | _ |XPD|FLY| _  , // 18 TYPE_ROCKFORD
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ |WTR|LAV| _ | _ | _ | _ |ACT| _ | _ | _ | _ |XPD|FLY| _  , // 19 TYPE_AMOEBA
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 20 TYPE_DIAMOND_PULSE_0
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 21 TYPE_DIAMOND_PULSE_1
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 22 TYPE_DIAMOND_PULSE_2
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 23 TYPE_DIAMOND_PULSE_3
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 24 TYPE_DIAMOND_PULSE_4
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 25 TYPE_DIAMOND_PULSE_5
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 26 TYPE_DIAMOND_PULSE_6
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 27 TYPE_DIAMOND_STATIC
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |   DRT|DRP| _ | _ | _ |WTR|LAV| _ | _ | _ | _ | _ | _ | _ | _ |PER|XPD| _ | _  , // 28 TYPE_PEBBLE1
   CNR| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |   DRT|DRP| _ | _ | _ |WTR|LAV| _ | _ | _ | _ | _ | _ | _ | _ |PER|XPD| _ | _  , // 29 TYPE_PEBBLE2
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 30 TYPE_EXPLODE_BLANK_0
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 31 TYPE_EXPLODE_BLANK_1
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 32 TYPE_EXPLODE_BLANK_2
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 33 TYPE_EXPLODE_BLANK_3
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 34 TYPE_EXPLODE_BLANK_4
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ |WTR|LAV|QUI| _ | _ | _ | _ | _ | _ |SPC|PER|XPD| _ | _  , // 35 TYPE_GRAB
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 36 TYPE_DUST_0
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 37 TYPE_DUST_1
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 38 TYPE_DUST_2
    _ | _ | _ |BOU| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ |PSH| _ | _ | _ | _ | _ |HRD| _ |ACT| _ | _ | _ | _ |XPD| _ |ROL , // 39 TYPE_BOULDER_SHAKE
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 40 TYPE_DUST_LEFT
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ |RKF| _ | _ | _ | _ |QUI| _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 41 TYPE_DUST_RIGHT
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 42 TYPE_DOGE_FALLING
    _ |PAD|SHV| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG|GRB| _ | _ |XPD| _ |ROL , // 43 TYPE_DIAMOND2
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ | _  , // 44 TYPE_BOULDER_FALLING
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG| _ | _ | _ |XPD| _ | _  , // 45 TYPE_LADDER
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG| _ | _ | _ |XPD| _ | _  , // 46 TYPE_DUST_ROCK
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 47 TYPE_DOGE_CONVERT
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ |GRB| _ | _ | _ | _ | _  , // 48 TYPE_SWITCH
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ |ROL , // 49 TYPE_PUSHER
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 50 TYPE_PUSHER_VERT
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 51 TYPE_WYRM
    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ | _ | _ | _ | _ | _  , // 52 TYPE_LIFE
    _ |PAD|SHV|BOU|DGE| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ |PSH| _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 53 TYPE_BOULDER_DOGE
    _ |PAD| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ | _ | _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ | _  , // 54 TYPE_BOULDER_DOGE_FALLING
    _ |PAD|SHV|BOU|DGE| _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _ | _    |    _ | _ | _ |PSH| _ | _ | _ | _ | _ |HRD| _ |ACT|BNG| _ | _ | _ |XPD| _ |ROL , // 53 TYPE_BOULDER_DOGE_CRITICAL

#if __ENABLE_LAVA
     _ | _ |RKF| _ | _ | _ | _ | _ | _ | _ | _ |ACT| _ | _ |SPC|PER|XPD| _ | _  , // 47 LAVA
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

// 100 + 0x00bb, //0
// 100 + 0x00bb, //1
// 100 + 0x00bb, //2
// 100 + 0x0250, //3
// 100 + 0x0115, //4
// 100 + 0x0250, //5
// 100 + 0x00bb, //6
// 100 + 0x0282, //7
// 100 + 0x0294, //8
// 100 + 0x0283, //9
// 100 + 0x0250, //10
// 100 + 0x0114, //11
// 100 + 0x0114, //12
// 100 + 0x00cc, //13
// 100 + 0x0114, //14
// 100 + 0x01db, //15
// 100 + 0x01b9, //16
// 100 + 0x02f8, //17
// 100 + 0x0896, //18
// 100 + 0x01fe, //19
// 100 + 0x0283, //20
// 100 + 0x0283, //21
// 100 + 0x0283, //22
// 100 + 0x0283, //23
// 100 + 0x0283, //24
// 100 + 0x0283, //25
// 100 + 0x0283, //26
// 100 + 0x0283, //27
// 100 + 0x00bb, //28
// 100 + 0x00bb, //29
// 100 + 0x0112, //30
// 100 + 0x00ca, //31
// 100 + 0x00ca, //32
// 100 + 0x0112, //33
// 100 + 0x011a, //34
// 100 + 0x0250, //35
// 100 + 0x0250, //36
// 100 + 0x0250, //37
// 100 + 0x0250, //38
// 100 + 0x0250, //39
// 100 + 0x0350, //40
// 100 + 0x0250, //41
// 100 + 0x0250, //42
// 100 + 0x0283, //43

// };


