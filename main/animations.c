#include "attribute.h"
#include "main.h"
#include "animations.h"
#include "random.h"


const char *Animate[TYPE_MAX];
char AnimCount[TYPE_MAX];

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


static const char AnimRockford[] = {


    // CH_BLANK, 50,
    // CH_DUST_2, 8,
    // CH_DUST_1, 8,
    // CH_DUST_0, 8,
    // CH_DUST_2, 8,
    // CH_DUST_1, 8,
    // CH_DUST_0, 8,
    // CH_DUST_1, 8,
    //CH_BLANK, 1,
    CH_ROCKFORD, ANIM_HALT,

    // @20...   see grab in rockford.c

//    CH_DIAMOND_WITHOUT_DIRT, 3,
    CH_DOGE_GRAB,8,

    CH_ROCKFORD, ANIM_HALT,

    CH_DUST_0, 6,
    CH_DUST_1, 6,
    CH_DUST_2, 6,

    CH_ROCKFORD, ANIM_HALT,

};


const char *const AnimateBase[TYPE_MAX] = {

    // indexed by object TYPE (def: ObjectType in attribute.h)
    // =0 if object does not auto-animate

    // Note that the type number is an ID, not ordinal. That's because the continuity may
    // be compromised by the conditional compilation. Beware.

    0,                          // 00 TYPE_SPACE,
    0,                          // 01 TYPE_DIRT,
    0,                          // 02 TYPE_BRICKWALL,
    0,                          // 03 TYPE_OUTBOX_PRE,
    AnimFlashOut,               // 04 TYPE_OUTBOX,
    0,                          // 05 TYPE_STEELWALL,
    0,                          // 06 TYPE_BOULDER,
    AnimPulseDoge,              // 07 TYPE_DOGE,
    0,                          // 08 TYPE_ROCKFORD_PRE,
    AnimRockford,               // 09 TYPE_ROCKFORD,
    0,                          // 10 TYPE_PEBBLE1,
    0,                          // 11 TYPE_PEBBLE2,
    AnimGrab,                   // 12 TYPE_GRAB,
    0,                          // 13 TYPE_DUST_0,
    // 0,                          // 14 TYPE_DUST_1,
    // 0,                          // 15 TYPE_DUST_2,
    0,                          // 16 TYPE_DUST_LEFT,
    0,                          // 17 TYPE_DUST_RIGHT,
    0,                          // 18 TYPE_DOGE_FALLING,
    0,                          // 19 TYPE_BOULDER_FALLING,
    0,                          // 20 TYPE_DUST_ROCK,
    0,                          // 21 TYPE_DOGE_CONVERT,
    AnimSwitch,                 // 22 TYPE_SWITCH,
    0,                          // 23 TYPE_PUSHER,
    0,                          // 24 TYPE_PUSHER_VERT,
    0,                          // 25 TYPE_WYRM,
    0,                          // 26 TYPE_BOULDER_DOGE,
    0,                          // 27 TYPE_BOULDER_DOGE_FALLING,
    AnimConglomerateMid,        // 28 TYPE_BOULDER_DOGE_CRITICAL,
    0,                          // 29 TYPE_LAVA,
    0,                          // 30 TYPE_PEBBLE_BOULDER,
};



void initCharAnimations() {

    for (int type = 0; type < TYPE_MAX; type++)
        startCharAnimation(type, AnimateBase[type]);
}



void startCharAnimation(int type, const char *idx) {

    if (idx) {

        if ((*idx)  == ANIM_LOOP)
            idx = AnimateBase[type];

        Animate[type] = idx++;

        int count = *idx;
        if (count == ANIM_RNDSPEED)
            count = (getRandom32() >> 25) | 7;

        AnimCount[type] = count;
    }
}



void processCharAnimations() {

    for (int type = 0; type < TYPE_MAX; type++)
        if (AnimateBase[type] && AnimCount[type] != ANIM_HALT)
            if (!--AnimCount[type])
                startCharAnimation(type, Animate[type] + 2);
}

//EOF