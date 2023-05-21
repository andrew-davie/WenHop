#include "animations.h"
#include "attribute.h"

const char *Animate[TYPE_MAX];
char AnimCount[TYPE_MAX];

// clang-format off

static const char AnimateBelt[] = {
    CH_BELT_0, 12,
    CH_BELT_1, 12,
    ANIM_LOOP,
};

static const char AnimateBelt1[] = {
    CH_BELT_1, 12,
    CH_BELT_0, 12,
    ANIM_LOOP,
};

static const char AnimateWaterFlow[] = {

    CH_WATERFLOW_4, 3,
    CH_WATERFLOW_3, 3,
    CH_WATERFLOW_2, 3,
    CH_WATERFLOW_1, 3,
    CH_WATERFLOW_0, 3,
    ANIM_LOOP,
};

static const char AnimateGrinder[] = {

    CH_GRINDER_0, 12,
    CH_GRINDER_1, 12,
    ANIM_LOOP,
};

static const char AnimateGrinder1[] = {

    CH_GRINDER_1, 12,
    CH_GRINDER_0, 12,
    ANIM_LOOP,
};


static const char AnimateGravity[] = {

    CH_FLIP_GRAVITY_2, 30,
    CH_FLIP_GRAVITY_1, 4,
    CH_FLIP_GRAVITY_0, 4,
    CH_FLIP_GRAVITY_1, 4,
    ANIM_LOOP,
};

static const char AnimGrab[] = {

    CH_DOGE_GRAB,8,
    CH_DUST_2, 6,
    CH_DUST_1, 6,
    CH_DUST_0, 6,
    CH_BLANK, ANIM_HALT,
};

static const char AnimConglomerateMid[] = {

    CH_CONGLOMERATE_15, SPEED_BASE * 2,
    CH_CONGLOMERATE_MID, SPEED_BASE,
    ANIM_LOOP,

};


static const char AnimSwitch[] = {
    CH_SWITCH_LEFT_OFF, 20,
    CH_SWITCH_LEFT_ON, 20,
    ANIM_LOOP
};


static const char AnimFlashOut[] = {

    CH_DOOROPEN_0,20,
    CH_BLANK,20,
    ANIM_LOOP
};

static const char AnimPulseDoge[] = {

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


static const char AnimMellonHusk[] = {

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

const char *const AnimateBase[TYPE_MAX] = {

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
    0,                   // 11 TYPE_PEBBLE2
    AnimGrab,            // 12 TYPE_GRAB
    0,                   // 13 TYPE_DUST_0
    0,                   // 14 TYPE_DOGE_FALLING
    0,                   // 15 TYPE_ROCK_FALLING
    0,                   // 16 TYPE_DUST_ROCK
    0,                   // 17 TYPE_CONVERT_GEODE_TO_DOGE
    AnimSwitch,          // 18 TYPE_SWITCH
    0,                   // 19 TYPE_PUSHER
    0,                   // 20 TYPE_PUSHER_VERT
    0,                   // 21 TYPE_WYRM
    0,                   // 22 TYPE_GEODOGE
    0,                   // 23 TYPE_GEODOGE_FALLING
    AnimConglomerateMid, // 24 TYPE_GEODOGE_CRITICAL (deprecated)
    0,                   // 25 TYPE_LAVA
    0,                   // 26 TYPE_PEBBLE_ROCK
    AnimateGravity,      // 27 TYPE_FLIP_GRAVITY
    0,                   // 28 TYPE_BLOCK
    0,                   // 29 TYPE_PACMAN_DOT
    AnimateGrinder,      // 30 TYPE_GRINDER
    0,                   // 31 TYPE_HUB
    0,                   // 32 TYPE_WATER
    AnimateWaterFlow,    // 33 TYPE_WATERFLOW
    0,                   // 34 TYPE_TAP
    0,                   // 35 TYPE_OUTLET
    AnimateGrinder1,     // 36 TYPE_GRINDER1
    AnimateBelt,         // 37 TYPE_BELT
    AnimateBelt1,        // 38 TYPE_BELT1
};

void initCharAnimations() {

    for (int type = 0; type < TYPE_MAX; type++)
        startCharAnimation(type, AnimateBase[type]);
}

void startCharAnimation(int type, const char *idx) {

    if (idx) {

        if ((int)(*idx) == ANIM_LOOP)
            idx = AnimateBase[type];

        Animate[type] = idx++;

        int count = *idx;
        // if (count == ANIM_RNDSPEED)
        //     count = (getRandom32() >> 25) | 7;

        AnimCount[type] = count;
    }
}

void processCharAnimations() {

    for (int type = 0; type < TYPE_MAX; type++)
        if (AnimateBase[type] && AnimCount[type] != ANIM_HALT)
            if (!--AnimCount[type])
                startCharAnimation(type, Animate[type] + 2);
}

// EOF