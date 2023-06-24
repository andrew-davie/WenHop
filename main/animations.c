#include "animations.h"
#include "attribute.h"
#include "random.h"

const unsigned char *Animate[TYPE_MAX];
char AnimCount[TYPE_MAX];

// clang-format off

const unsigned char AnimateBelt[] = {
    CH_BELT_0, 12,
    CH_BELT_1, 12,
    ANIM_LOOP,
};

const unsigned char AnimateBelt1[] = {
    CH_BELT_1, 12,
    CH_BELT_0, 12,
    ANIM_LOOP,
};


#define TRICKLE 5

const unsigned char AnimateWaterFlow0[] = {

    CH_WATERFLOW_4, TRICKLE,
    CH_WATERFLOW_3, TRICKLE,
    CH_WATERFLOW_2, TRICKLE,
    CH_WATERFLOW_1, TRICKLE,
    CH_WATERFLOW_0, TRICKLE,
    ANIM_LOOP,
};

const unsigned char AnimateWaterFlow1[] = {

    CH_WATERFLOW_3, TRICKLE,
    CH_WATERFLOW_2, TRICKLE,
    CH_WATERFLOW_1, TRICKLE,
    CH_WATERFLOW_0, TRICKLE,
    CH_WATERFLOW_4, TRICKLE,
    ANIM_LOOP,
};

const unsigned char AnimateWaterFlow2[] = {

    CH_WATERFLOW_2, TRICKLE,
    CH_WATERFLOW_1, TRICKLE,
    CH_WATERFLOW_0, TRICKLE,
    CH_WATERFLOW_4, TRICKLE,
    CH_WATERFLOW_3, TRICKLE,
    ANIM_LOOP,
};

const unsigned char AnimateWaterFlow3[] = {

    CH_WATERFLOW_1, TRICKLE,
    CH_WATERFLOW_0, TRICKLE,
    CH_WATERFLOW_4, TRICKLE,
    CH_WATERFLOW_3, TRICKLE,
    CH_WATERFLOW_2, TRICKLE,
    ANIM_LOOP,
};

const unsigned char AnimateWaterFlow4[] = {

    CH_WATERFLOW_0, TRICKLE,
    CH_WATERFLOW_4, TRICKLE,
    CH_WATERFLOW_3, TRICKLE,
    CH_WATERFLOW_2, TRICKLE,
    CH_WATERFLOW_1, TRICKLE,
    ANIM_LOOP,
};


const unsigned char AnimateGrinder[] = {

    CH_GRINDER_0, 12,
    CH_GRINDER_1, 12,
    ANIM_LOOP,
};

const unsigned char AnimateGrinder1[] = {

    CH_GRINDER_1, 12,
    CH_GRINDER_0, 12,
    ANIM_LOOP,
};


const unsigned char AnimateGravity[] = {

    CH_FLIP_GRAVITY_2, 30,
    CH_FLIP_GRAVITY_1, 4,
    CH_FLIP_GRAVITY_0, 4,
    CH_FLIP_GRAVITY_1, 4,
    ANIM_LOOP,
};

// const unsigned char AnimGrab[] = {

//     CH_DOGE_GRAB,8,
//     CH_DUST_2, 6,
//     CH_DUST_1, 6,
//     CH_DUST_0, 6,
//     CH_BLANK, ANIM_HALT,
// };

const unsigned char AnimConglomerateMid[] = {

    CH_CONGLOMERATE_15, SPEED_BASE * 2,
    CH_CONGLOMERATE_MID, SPEED_BASE,
    ANIM_LOOP,

};


const unsigned char AnimSwitch[] = {
    CH_SWITCH_LEFT_OFF, 20,
    CH_SWITCH_LEFT_ON, 20,
    ANIM_LOOP
};


const unsigned char AnimFlashOut[] = {

    CH_DOOROPEN_0,20,
    CH_BLANK,20,
    ANIM_LOOP
};

const unsigned char AnimPulseDoge[] = {

    CH_DOGE_00, 12, //ANIM_RNDSPEED,
    CH_DOGE_01, 8,
    CH_DOGE_02, 5,
    CH_DOGE_03, 4,
    CH_DOGE_04, 5,
    CH_DOGE_05, 8,

    CH_DOGE_04, 5,
    CH_DOGE_03, 4,
    CH_DOGE_02, 5,
    CH_DOGE_01, 8,

    ANIM_LOOP
};


const unsigned char AnimMellonHusk[] = {

    // Note that mellon.c indexes into this with an offset so this must be kept synched

    CH_DUST_0, 6,
    CH_DUST_1, 6,
    CH_DUST_2, 6,

    CH_MELLON_HUSK, ANIM_HALT,

    // @+2
    // CH_DOGE_GRAB,8,
    // CH_MELLON_HUSK, ANIM_HALT,

    // @+2
};

// clang-format on

const unsigned char *const AnimateBase[TYPE_MAX] = {

    // indexed by object TYPE (def: ObjectType in attribute.h)
    // =0 if object does not auto-animate

    // Note that the type number is an ID, not ordinal. That's because the continuity may
    // be compromised by the conditional compilation. Beware.

    0,                   // 00 TYPE_SPACE
    0,                   // 01 TYPE_DIRT
    0,                   // 02 TYPE_BRICKWALL
    0,                   // 03 TYPE_OUTBOX_PRE
    AnimFlashOut,        // 04 TYPE_OUTBOX
    0,                   // 05 TYPE_STEELWALL
    0,                   // 06 TYPE_ROCK
    AnimPulseDoge,       // 07 TYPE_DOGE
    0,                   // 08 TYPE_MELLON_HUSK_PRE
    AnimMellonHusk,      // 09 TYPE_MELLON_HUSK
    0,                   // 10 TYPE_PEBBLE1
    0,                   // 11 TYPE_DUST_0
    0,                   // 12 TYPE_DOGE_FALLING
    0,                   // 13 TYPE_ROCK_FALLING
    0,                   // 14 TYPE_DUST_ROCK
    0,                   // 15 TYPE_CONVERT_GEODE_TO_DOGE
    AnimSwitch,          // 16 TYPE_SWITCH
    0,                   // 17 TYPE_PUSHER
    0,                   // 18 TYPE_PUSHER_VERT
    0,                   // 19 TYPE_WYRM
    0,                   // 20 TYPE_GEODOGE
    0,                   // 21 TYPE_GEODOGE_FALLING
    AnimConglomerateMid, // 22 TYPE_GEODOGE_CRITICAL (deprecated)
    0,                   // 23 TYPE_LAVA
    0,                   // 24 TYPE_PEBBLE_ROCK
    AnimateGravity,      // 25 TYPE_FLIP_GRAVITY
    0,                   // 26 TYPE_BLOCK
    AnimateGrinder,      // 27 TYPE_GRINDER
    0,                   // 28 TYPE_HUB
    0,                   // 29 TYPE_WATER
    AnimateWaterFlow0,   // 30 TYPE_WATERFLOW0
    AnimateWaterFlow1,   // 31 TYPE_WATERFLOW1
    AnimateWaterFlow2,   // 32 TYPE_WATERFLOW2
    AnimateWaterFlow3,   // 33 TYPE_WATERFLOW3
    AnimateWaterFlow4,   // 34 TYPE_WATERFLOW4
    0,                   // 35 TYPE_TAP
    0,                   // 36 TYPE_OUTLET
    AnimateGrinder1,     // 37 TYPE_GRINDER1
    AnimateBelt,         // 38 TYPE_BELT
    AnimateBelt1,        // 39 TYPE_BELT1
    0,                   // 40 TYPE_CONVERT_PIPE
    0,                   // 41 TYPE_DOGE_FALLING2
};

void initCharAnimations() {

    for (int type = 0; type < TYPE_MAX; type++)
        startCharAnimation(type, AnimateBase[type]);
}

void startCharAnimation(int type, const unsigned char *idx) {

    if (idx) {

        if ((int)*idx == ANIM_LOOP)
            idx = AnimateBase[type];

        Animate[type] = idx++;
        AnimCount[type] = *idx;
    }
}

void processCharAnimations() {

    for (int type = 0; type < TYPE_MAX; type++)
        if (AnimateBase[type] && AnimCount[type] != ANIM_HALT)
            if (!--AnimCount[type])
                startCharAnimation(type, Animate[type] + 2);
}

// EOF