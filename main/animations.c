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



// static const char AnimLife[] = {
//     CH_LIFE_0, 15,
//     CH_LIFE_1, 15,
//     CH_LIFE_2, 15,
//     CH_LIFE_3, 15,
//     CH_LIFE_4, 15,
//     CH_LIFE_5, 15,
//     CH_LIFE_6, 15,
//     CH_LIFE_7, 15,
//     CH_LIFE_8, 15,
//     CH_LIFE_9, 15,
//     CH_LIFE_10, 15,
//     CH_LIFE_11, 15,
//     CH_LIFE_12, 15,
//     CH_LIFE_13, 15,
//     CH_LIFE_14, 15,
//     CH_LIFE_15, 15,
//     ANIM_LOOP,
// };


static const char AnimSwitch[] = {
    CH_SWITCH_LEFT_OFF, 20,
    CH_SWITCH_LEFT_ON, 20,
    ANIM_LOOP
};


// const char AnimBrokenBoulder[] = {
//     CH_BLANK,3,
//     CH_BOULDER,6,
//     CH_BLANK,3,
//     CH_BOULDER,6,
//     CH_DUST_ROCK_0, 9,
//     CH_DUST_ROCK_1, 9,
//     CH_DUST_ROCK_2, ANIM_HALT,
// };

static const char AnimMagicWall[] = {

    CH_BOULDER_DOGE, 3,
    CH_DUST_0, 3,
    ANIM_LOOP
};

static const char AnimFlashOut[] = {

    CH_DOOROPEN_0,20,
    CH_BLANK,20,
    ANIM_LOOP
};

static const char AnimFirefly[] = {

    CH_FIREFLY_0,2,
    CH_FIREFLY_1,4,
    CH_FIREFLY_2,5,
    CH_FIREFLY_0,6,
    CH_FIREFLY_2,4,
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

static const char AnimButterfly[] = {

    CH_BUTTERFLY_0,6,
    CH_BUTTERFLY_1,3,
    CH_BUTTERFLY_2,4,
    CH_BUTTERFLY_0,3,
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

    CH_DIAMOND_WITHOUT_DIRT, 3,
    CH_DOGE_GRAB,8,

    CH_ROCKFORD, ANIM_HALT,

    CH_DUST_0, 6,
    CH_DUST_1, 6,
    CH_DUST_2, 6,

    CH_ROCKFORD, ANIM_HALT,

};


const char *const AnimateBase[] = {

    // indexed by object TYPE (def: ObjectType in attribute.h)
    // =0 if object does not auto-animate

    // Note that the type number is an ID, not ordinal. That's because the continuity may
    // be compromised by the conditional compilation. Beware.

    0,                          // 00 TYPE_SPACE
    0,                          // 01 TYPE_DIRT
    0,                          // 02 TYPE_BRICKWALL
    AnimMagicWall,              // 03 TYPE_MAGICWALL
    0,                          // 04 TYPE_OUTBOX_PRE
    AnimFlashOut,               // 05 TYPE_OUTBOX
    0,                          // 06 TYPE_STEELWALL
    AnimFirefly,                // 07 TYPE_FIREFLY
    0,                          // 08 TYPE_BOULDER
    AnimPulseDoge,              // 09 TYPE_DOGE
    0,                          // 10 TYPE_EASTEREGG
    0,                          // 11 TYPE_EXPLODE_DIAMOND_0
    0,                          // 12 TYPE_EXPLODE_DIAMOND_1
    0,                          // 13 TYPE_EXPLODE_DIAMOND_2
    0,                          // 14 TYPE_EXPLODE_DIAMOND_3
    0,                          // 15 TYPE_EXPLODE_DIAMOND_4
    0,                          // 16 TYPE_ROCKFORD_PRE
    AnimButterfly,              // 17 TYPE_BUTTERFLY
    AnimRockford,               // 18 TYPE_ROCKFORD
    0,                          // 19 TYPE_AMOEBA
    AnimPulseDoge,              // 20 TYPE_DIAMOND_PULSE_0
    AnimPulseDoge,              // 21 TYPE_DIAMOND_PULSE_1
    AnimPulseDoge,              // 22 TYPE_DIAMOND_PULSE_2
    AnimPulseDoge,              // 23 TYPE_DIAMOND_PULSE_3
    AnimPulseDoge,              // 24 TYPE_DIAMOND_PULSE_4
    AnimPulseDoge,              // 25 TYPE_DIAMOND_PULSE_5
    AnimPulseDoge,              // 26 TYPE_DIAMOND_PULSE_6
    AnimPulseDoge,              // 27 TYPE_DIAMOND_STATIC
    0,                          // 28 TYPE_PEBBLE1
    0,                          // 29 TYPE_PEBBLE2
    0,                          // 30 TYPE_EXPLODE_BLANK_0
    0,                          // 31 TYPE_EXPLODE_BLANK_1
    0,                          // 32 TYPE_EXPLODE_BLANK_2
    0,                          // 33 TYPE_EXPLODE_BLANK_3
    0,                          // 34 TYPE_EXPLODE_BLANK_4
    AnimGrab,                   // 35 TYPE_GRAB
    0,                          // 36 TYPE_DUST_0
    0,                          // 37 TYPE_DUST_1
    0,                          // 38 TYPE_DUST_2
    0,                          // 39 TYPE_BOULDER_SHAKE
    0,                          // 40 TYPE_DUST_LEFT
    0,                          // 41 TYPE_DUST_RIGHT
    0,                          // 42 TYPE_DOGE_FALLING
    0,                          // 43 TYPE_DIAMOND_WITHOUT_DIRT
    0,                          // 44 TYPE_BOULDER_FALLING
    0,                          // 45 TYPE_LADDER

    0,                          // 46 TYPE_DUST_ROCK
    0,                          // 47 TYPE_DOGE_CONVERT
    AnimSwitch,                 // 48 TYPE_SWITCH
    0,                          // 49 TYPE_PUSHER

    0,                          // 50 TYPE_PUSHER_VERT
    0,                          // 51 TYPE_WYRM
    0,                          // 52 TYPE_LIFE
    0,                          // 53 TYPE_BOULDER_DOGE_FALLING
    0,                          // 53 TYPE_BOULDER_FALLING
    AnimConglomerateMid,        // 54 TYPE_BOULDER_DOGE_DRITICAL

#if __ENABLE_LAVA    
    0,                          // 47 TYPE_LAVA
#endif

#if __ENABLE_WATER    
    0,                          // 48 TYPE_WATER
#endif
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