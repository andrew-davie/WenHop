#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

    #include "main.h"
        
extern const short Attribute[];
extern const unsigned char CharToType[];

enum ObjectType {


    // update Attribute[] in animations.c if changing this

    TYPE_SPACE,                 // 0       ASSUMED == 0 in code
    TYPE_DIRT,                  // 1
    TYPE_BRICKWALL,             // 2
    TYPE_MAGICWALL,             // 3
    TYPE_OUTBOX_PRE,            // 4
    TYPE_OUTBOX,                // 5
    TYPE_STEELWALL,             // 6
    TYPE_FIREFLY,               // 7
    TYPE_BOULDER,               // 8
    TYPE_DIAMOND,               // 9
    TYPE_EASTEREGG,             // 10
    TYPE_EXPLODE_DIAMOND_0,     // 11
    TYPE_EXPLODE_DIAMOND_1,     // 12
    TYPE_EXPLODE_DIAMOND_2,     // 13
    TYPE_EXPLODE_DIAMOND_3,     // 14
    TYPE_EXPLODE_DIAMOND_4,     // 15
    TYPE_ROCKFORD_PRE,          // 16
    TYPE_BUTTERFLY,             // 17
    TYPE_ROCKFORD,              // 18
    TYPE_AMOEBA,                // 19
    TYPE_DIAMOND_PULSE_0,       // 20
    TYPE_DIAMOND_PULSE_1,       // 21
    TYPE_DIAMOND_PULSE_2,       // 22
    TYPE_DIAMOND_PULSE_3,       // 23
    TYPE_DIAMOND_PULSE_4,       // 24
    TYPE_DIAMOND_PULSE_5,       // 25
    TYPE_DIAMOND_PULSE_6,       // 26
    TYPE_DIAMOND_STATIC,        // 27
    TYPE_PEBBLE1,               // 28
    TYPE_PEBBLE2,               // 29
    TYPE_EXPLODE_BLANK_0,       // 30
    TYPE_EXPLODE_BLANK_1,       // 31
    TYPE_EXPLODE_BLANK_2,       // 32
    TYPE_EXPLODE_BLANK_3,       // 33
    TYPE_EXPLODE_BLANK_4,       // 34
    TYPE_DIAMOND_GRAB,          // 35
    TYPE_DUST_0,                // 36
    TYPE_DUST_1,                // 37
    TYPE_DUST_2,                // 38
    TYPE_BOULDER_SHAKE,         // 39
    TYPE_DUST_LEFT,             // 40
    TYPE_DUST_RIGHT,            // 41
    TYPE_DIAMOND_FALLING,       // 42
    TYPE_DIAMOND_WITHOUT_DIRT,  // 43

#if __ENABLE_LAVA    
    TYPE_LAVA,                  // 47
#endif

#if __ENABLE_WATER
    TYPE_WATER,                 // 48
#endif

    TYPE_MAX
};




//extern const unsigned short worstRequiredTime[TYPE_MAX];


enum ChName {

    // see charSet @ characterset.c
    // Objects numbered > 63 cannot be generated by cave data (6 bits)

    CH_BLANK,                   // 0
    CH_DIRT,                    // 1
    CH_BRICKWALL,               // 2
    CH_MAGICWALL,               // 3
    CH_DOORCLOSED,              // 4
    CH_DOOROPEN_0,              // 5
    CH_EXITBLANK,               // 6
    CH_STEELWALL,               // 7
    CH_FIREFLY_0,               // 8    \       x4 for directions
    CH_FIREFLY_1,               // 9    |
    CH_FIREFLY_2,               // 10   |
    CH_FIREFLY_3,               // 11   /
    CH_PEBBLE1,                 // 12
    CH_PEBBLE2,                 // 13
    CH_EASTEREGG,               // 14
    CH_BOULDER,                 // 15
    CH_BOULDER_FALLING,         // 16          +2 offset assumed by code
    CH_DIAMOND,                 // 17
    CH_DIAMOND_FALLING,         // 18          +2 offset assumed by code
    CH_EXPLODETODIAMOND_0,      // 19
    CH_EXPLODETODIAMOND_1,      // 20
    CH_EXPLODETODIAMOND_2,      // 21
    CH_EXPLODETODIAMOND_3,      // 22
    CH_EXPLODETODIAMOND_4,      // 23
    CH_ROCKFORD_BIRTH,          // 24
    CH_MAGICWALL_1,             // 25
    CH_MAGICWALL_2,             // 26
    CH_MAGICWALL_3,             // 27
    CH_BUTTERFLY_0,             // 28   \       x4 for directions
    CH_BUTTERFLY_1,             // 29   |
    CH_BUTTERFLY_2,             // 30   |
    CH_BUTTERFLY_3,             // 31   /
    CH_AMOEBA_0,                // 32
    CH_AMOEBA_1,                // 33
    CH_AMOEBA_2,                // 34
    CH_AMOEBA_3,                // 35
    CH_ROCKFORD,                // 36 rockford
    CH_DIAMOND_PULSE_0,         // 37
    CH_DIAMOND_PULSE_1,         // 38
    CH_DIAMOND_PULSE_2,         // 39
    CH_DIAMOND_PULSE_3,         // 40
    CH_DIAMOND_PULSE_4,         // 41
    CH_DIAMOND_PULSE_5,         // 42
    CH_DIAMOND_PULSE_6,         // 43
    CH_DIAMOND_STATIC,          // 44 (CAN SWITCH ANIMATIONS ON THIS!)
    CH_SPARKLE_0,               // 45
    CH_SPARKLE_1,               // 46
    CH_SPARKLE_2,               // 47
    CH_SPARKLE_3,               // 48
    CH_EXPLODETOBLANK_0,        // 49
    CH_EXPLODETOBLANK_1,        // 50
    CH_EXPLODETOBLANK_2,        // 51
    CH_EXPLODETOBLANK_3,        // 52
    CH_EXPLODETOBLANK_4,        // 53
    CH_DIAMOND_GRAB,            // 54
    CH_DIAMOND_WITHOUT_DIRT,    // 55
    CH_DUST_0,                  // 56
    CH_DUST_1,                  // 57
    CH_DUST_2,                  // 58
    CH_BOULDER_SHAKE,           // 59
    CH_DUST_LEFT_0,             // 60
    CH_DUST_LEFT_1,             // 61
    CH_DUST_RIGHT_0,            // 62
    CH_DUST_RIGHT_1,            // 63

    CH_CONGLOMERATE,            // 64
    CH_CONGLOMERATE_1,          // 64
    CH_CONGLOMERATE_2,          // 64
    CH_CONGLOMERATE_3,          // 64
    CH_CONGLOMERATE_4,          // 64
    CH_CONGLOMERATE_5,          // 64
    CH_CONGLOMERATE_6,          // 64
    CH_CONGLOMERATE_7,          // 64
    CH_CONGLOMERATE_8,          // 64
    CH_CONGLOMERATE_9,          // 64
    CH_CONGLOMERATE_10,         // 64
    CH_CONGLOMERATE_11,         // 64
    CH_CONGLOMERATE_12,         // 64
    CH_CONGLOMERATE_13,         // 64
    CH_CONGLOMERATE_14,         // 64
    CH_CONGLOMERATE_15,         // 64

#if __ENABLE_LAVA
    CH_LAVA_0,                  // 69
    CH_LAVA_1,                  // 70
    CH_LAVA_2,                  // 71
    CH_LAVA_3,                  // 72
#endif

#if __ENABLE_WATER
    CH_WATER,                   // 73
    CH_WATER1,                  // 74
    CH_WATER2,                  // 75
    CH_WATER3,                  // 76
#endif    

    CH_MAX
};



#define ATT_ROLL                    1  /*  falling objects roll off this object */
#define ATT_KILLS_FLY               2  /*  firefly/butterfly object touching this is deadly */
#define ATT_EXPLODABLE              4  /*  object can be destroyed by explosion */
#define ATT_PERMEABLE               8  /*  amoeba can grow here */
#define ATT_BLANK                  16  /*  blank square */
#define ATT_DIRT                   32
#define ATT_GRAB                   64  /*  grabbable object */
#define ATT_EXPLODES              128  /*  object explodes if killed */
#define ATT_ACTIVE                256  /*  object requires checking/AI DISABLED!!!*/
#define ATT_SQUASHABLE_TO_BLANKS  512
#define ATT_HARD                 1024
#define ATT_EXIT                 2048
#define ATT_NOROCKNOISE          4096
#define ATT_PUSH                 8192
#define ATT_ROCKFORDYBLANK      16384
#define ATT_DRIP                32768

#endif