#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

#include "main.h"

extern const unsigned int Attribute[];
extern const unsigned char CharToType[];

enum ObjectType {

    // update Attribute[] in attribute.c
    // update AnimateBase[] in animations.c
    // update processVec[] in main.c

    TYPE_SPACE,                 // 00      ASSUMED == 0 in code
    TYPE_DIRT,                  // 01
    TYPE_BRICKWALL,             // 02
    TYPE_OUTBOX_PRE,            // 03
    TYPE_OUTBOX,                // 04
    TYPE_STEELWALL,             // 05
    TYPE_ROCK,                  // 06
    TYPE_DOGE,                  // 07
    TYPE_MELLON_HUSK_PRE,       // 08
    TYPE_MELLON_HUSK,           // 09
    TYPE_PEBBLE1,               // 10
    TYPE_GRAB,                  // 11
    TYPE_DUST_0,                // 12
    TYPE_DOGE_FALLING,          // 13
    TYPE_ROCK_FALLING,          // 14
    TYPE_DUST_ROCK,             // 15
    TYPE_CONVERT_GEODE_TO_DOGE, // 16
    TYPE_SWITCH,                // 17
    TYPE_PUSHER,                // 18
    TYPE_PUSHER_VERT,           // 19
    TYPE_WYRM,                  // 20
    TYPE_GEODOGE,               // 21
    TYPE_GEODOGE_FALLING,       // 22
    TYPE_GEODOGE_CRITICAL,      // 23 depreacted
    TYPE_LAVA,                  // 24
    TYPE_PEBBLE_ROCK,           // 25
    TYPE_FLIP_GRAVITY,          // 26
    TYPE_BLOCK,                 // 27
    TYPE_GRINDER,               // 28
    TYPE_HUB,                   // 29
    TYPE_WATER,                 // 30
    TYPE_WATERFLOW_0,           // 31
    TYPE_WATERFLOW_1,           // 32
    TYPE_WATERFLOW_2,           // 33
    TYPE_WATERFLOW_3,           // 34
    TYPE_WATERFLOW_4,           // 35
    TYPE_TAP,                   // 36
    TYPE_OUTLET,                // 37
    TYPE_GRINDER_1,             // 38
    TYPE_BELT,                  // 39
    TYPE_BELT_1,                // 40
    TYPE_CONVERT_PIPE,          // 41

    TYPE_MAX
};

enum ChName {

    // see charSet[] @ characterset.c
    // Objects numbered > 63 cannot be generated by cave data (6 bits)
    // see CharToType[] in attribute.c

    CH_BLANK,                 // 000
    CH_DIRT,                  // 001
    CH_BRICKWALL,             // 002
    CH_DOORCLOSED,            // 003
    CH_DOOROPEN_0,            // 004
    CH_EXITBLANK,             // 005
    CH_STEELWALL,             // 006
    CH_PEBBLE1,               // 007
    CH_PEBBLE2,               // 008
    CH_ROCK,                  // 009
    CH_ROCK_FALLING,          // 010          +2 offset assumed by code
    CH_DOGE_00,               // 011
    CH_DOGE_FALLING,          // 012          +2 offset assumed by code
    CH_MELLON_HUSK_BIRTH,     // 013
    CH_LAVA_BLANK,            // 014
    CH_LAVA_SMALL,            // 015
    CH_LAVA_MEDIUM,           // 016
    CH_LAVA_LARGE,            // 017
    CH_MELLON_HUSK,           // 018
    CH_DOGE_01,               // 019
    CH_DOGE_02,               // 020
    CH_DOGE_03,               // 021
    CH_DOGE_04,               // 022
    CH_DOGE_05,               // 023
    CH_DOGE_STATIC,           // 024 (CAN SWITCH ANIMATIONS ON THIS!)
    CH_PEBBLE_ROCK,           // 025
    CH_EXPLODETOBLANK_0,      // 026
    CH_EXPLODETOBLANK_1,      // 027
    CH_EXPLODETOBLANK_2,      // 028
    CH_EXPLODETOBLANK_3,      // 029
    CH_EXPLODETOBLANK_4,      // 030
    CH_DOGE_GRAB,             // 031
    CH_DUST_0,                // 032
    CH_DUST_1,                // 033
    CH_DUST_2,                // 034
    CH_GEODOGE,               // 035
    CH_CONGLOMERATE_1,        // 036
    CH_CONGLOMERATE_2,        // 037
    CH_CONGLOMERATE_3,        // 038
    CH_CONGLOMERATE_4,        // 039
    CH_CONGLOMERATE_5,        // 040
    CH_CONGLOMERATE_6,        // 041
    CH_CONGLOMERATE_7,        // 042
    CH_CONGLOMERATE_8,        // 043
    CH_CONGLOMERATE_9,        // 044
    CH_CONGLOMERATE_10,       // 045
    CH_CONGLOMERATE_11,       // 046
    CH_CONGLOMERATE_12,       // 047
    CH_CONGLOMERATE_13,       // 048
    CH_CONGLOMERATE_14,       // 049
    CH_CONGLOMERATE_15,       // 050
    CH_DUST_ROCK_0,           // 051
    CH_DUST_ROCK_1,           // 052
    CH_DUST_ROCK_2,           // 053
    CH_CONVERT_GEODE_TO_DOGE, // 054
    CH_SWITCH_LEFT_OFF,       // 055
    CH_SWITCH_LEFT_ON,        // 056
    CH_HORIZONTAL_BAR,        // 057
    CH_PUSH_LEFT,             // 058       reverse must be +1
    CH_PUSH_LEFT_REVERSE,     // 059
    CH_PUSH_RIGHT,            // 060
    CH_PUSH_RIGHT_REVERSE,    // 061
    CH_VERTICAL_BAR,          // 062
    CH_PUSH_UP,               // 063
    CH_PUSH_UP_REVERSE,       // 064
    CH_PUSH_DOWN,             // 065
    CH_PUSH_DOWN_REVERSE,     // 066
    CH_WYRM_BODY,             // 067
    CH_WYRM_VERT_BODY,        // 068
    CH_WYRM_CORNER_LD,        // 069
    CH_WYRM_CORNER_RD,        // 070
    CH_WYRM_CORNER_LU,        // 071
    CH_WYRM_CORNER_RU,        // 072
    CH_WYRM_HEAD_U,           // 073
    CH_WYRM_HEAD_R,           // 074
    CH_WYRM_HEAD_D,           // 075
    CH_WYRM_HEAD_L,           // 076
    CH_CONGLOMERATE_MID,      // 077
    CH_GEODOGE_FALLING,       // 078
    CH_FLIP_GRAVITY_0,        // 079
    CH_FLIP_GRAVITY_1,        // 080
    CH_FLIP_GRAVITY_2,        // 081
    CH_BLOCK,                 // 082
    CH_GRINDER_0,             // 083
    CH_GRINDER_1,             // 084
    CH_HUB,                   // 085
    CH_WATER,                 // 086
    CH_WATERFLOW_0,           // 087 must be grouped
    CH_WATERFLOW_1,           // 088 .
    CH_WATERFLOW_2,           // 089 .
    CH_WATERFLOW_3,           // 090 .
    CH_WATERFLOW_4,           // 091 /
    CH_TAP_0,                 // 092
    CH_HUB_1,                 // 093
    CH_OUTLET,                // 094
    CH_TAP_1,                 // 095
    CH_BELT_0,                // 096
    CH_BELT_1,                // 097
    CH_PUSH_DOWN2,            // 098
    CH_GEODOGE_CONVERT,       // 099
    CH_CONVERT_PIPE,          // 100
    CH_WYRM_TAIL_U,           // 101
    CH_WYRM_TAIL_R,           // 102
    CH_WYRM_TAIL_D,           // 103
    CH_WYRM_TAIL_L,           // 104

    // 127 is limit

    CH_MAX
};

// clang-format off

#define ATT_ROLL                    (1 <<  0)
#define ATT_CONVERT                 (1 <<  1)
#define ATT_EXPLODABLE              (1 <<  2)
#define ATT_PERMEABLE               (1 <<  3)
#define ATT_BLANK                   (1 <<  4)
#define ATT_DIRT                    (1 <<  5)
#define ATT_GRAB                    (1 <<  6)
#define ATT_EXPLODES                (1 <<  7)
#define ATT_PUSH                    (1 <<  8)
#define ATT_SQUASHABLE_TO_BLANKS    (1 <<  9)
#define ATT_HARD                    (1 << 10)
#define ATT_EXIT                    (1 << 11)
#define ATT_NOROCKNOISE             (1 << 12)
//13
#define ATT_BLANKISH                (1 << 14)
#define ATT_DRIP                    (1 << 15)
#define ATT_MINE                    (1 << 16)
#define ATT_WATERFLOW               (1 << 17)
#define ATT_CONVEYOR                (1 << 18)
#define ATT_GRIND                   (1 << 19)
#define ATT_PIPE                    (1 << 20)
#define ATT_PHASE4                  (1 << 21)
#define ATT_PHASE2                  (1 << 22)
#define ATT_PHASE1                  (1 << 23)
#define ATT_PULL                    (1 << 24)
#define ATT_DISSOLVES               (1 << 25)
#define ATT_MELTS                   (1 << 26)
#define ATT_GEODOGE                 (1 << 27)
#define ATT_ROCK                    (1 << 28)
#define ATT_SHOVE                   (1 << 29)
#define ATT_PAD                     (1 << 30)
#define ATT_CORNER                  (1 << 31)

// clang-format on

#define RKF ATT_BLANKISH
#define MIN ATT_MINE
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
#define BOU ATT_ROCK
#define DGE ATT_GEODOGE
#define MLT ATT_MELTS
#define DIS ATT_DISSOLVES
#define PUL ATT_PULL
#define PSH ATT_PUSH
#define PIP ATT_PIPE
#define GND ATT_GRIND
#define CVY ATT_CONVEYOR
#define WTF ATT_WATERFLOW
#define CVT ATT_CONVERT

#define PH1 ATT_PHASE1
#define PH2 ATT_PHASE2
#define PH4 ATT_PHASE4

#define VALUE_BREAK_GEODE 25

#endif
