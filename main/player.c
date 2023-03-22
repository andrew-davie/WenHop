#include <stdbool.h>
#include "defines_from_dasm_for_c.h"

#include "main.h"
#include "player.h"

#include "atarivox.h"
#include "bitpatterns.h"
#include "colour.h"
#include "rockford.h"
#include "sound.h"


int autoMoveX;
int autoMoveY;
int autoMoveDeltaX;
int autoMoveDeltaY;
int autoMoveFrameCount;


const signed char AnimationDefault[] = {
    FRAME_STAND, 255,
};

const signed char AnimationStandUp[] = {

    FRAME_WALKUP0,20,
    FRAME_WALK3, 6,
    FRAME_STAND, 255,
};

const signed char AnimationStandLR[] = {
    FRAME_WALK3, 20,
    FRAME_STAND, 255,
};


const signed char AnimationPush[] = {

    FRAME_PUSH2, 2,
    ACTION_SFX, SFX_PICKAXE,
    ACTION_DOT, 3,4,
    FRAME_PUSH, 6,
    FRAME_PUSH2, 5,
    //FRAME_HUNCH, 2,
    FRAME_STAND, 1,
    ACTION_STOP,
};

const signed char AnimationLocked[] = {
    FRAME_HUNCH, 12,
    ACTION_STOP,
};

// const signed char AnimationEndPush2[] = {
// //    ACTION_POSITION, 4,0,
// //    FRAME_PUSH2, 15,
// //    ACTION_POSITION, 2,0,
//     FRAME_HUNCH, 5,
//     ACTION_STOP,
// };

// #if ENABLE_SHAKE
// const signed char AnimationShake[] = {
//     ACTION_POSITION, 0,0,
//     FRAME_SHAKE,10,
//     FRAME_SHAKE2,10,
//     FRAME_SHAKE3,10,
//     ACTION_LOOP,
//     ACTION_STOP,
// };
// #endif

// const signed char AnimationWipeHair[] = {
// //    FRAME_WIPE_HAIR, 22,
// //    FRAME_HAIR, 64,
//     FRAME_HAIR2, 4,
//     FRAME_HAIR, 4,
//     FRAME_HAIR2, 4,
//     FRAME_HAIR, 4,
//     ACTION_STOP,
// };

// const signed char AnimationHoldBoulder[] = {
//     FRAME_ARMS_IN_AIR, 10,
//     ACTION_LOOP,
//     FRAME_HOLD_BOULDER_1, 5,
//     ACTION_STOP,
// };

// const signed char AnimationStoop[] = { //=jump
//     ACTION_POSITION, 0,0,
//     FRAME_HUNCH, 1,
//     ACTION_LOOP,
//     ACTION_STOP,
// };

// const signed char AnimationImpatient[] = {
//     FRAME_ARMSCROSSED, 50,
//     FRAME_IMPATIENT, 10,
//     FRAME_IMPATIENT2, 10,
//     FRAME_IMPATIENT, 10,
//     FRAME_IMPATIENT2, 10,
//     FRAME_IMPATIENT, 10,
//     FRAME_IMPATIENT2, 10,
//     // FRAME_IMPATIENT, 10,
//     // FRAME_IMPATIENT2, 10,
//     ACTION_STOP,
// };


// const signed char AnimationLook[] = {
//     ACTION_POSITION, -1,0,
//     FRAME_LOOK1, 5,
//     ACTION_POSITION, -1,0,
//     FRAME_LOOK2, 20,
//     ACTION_POSITION, -1,0,
//     FRAME_LOOK1, 10,
//     FRAME_MOON,10,
//     ACTION_FLIP,
//     FRAME_MOON,10,
//     ACTION_FLIP,
//     FRAME_MOON,10,
//     ACTION_FLIP,
//     FRAME_MOON,10,
//     ACTION_FLIP,
//     FRAME_MOON,10,
//     ACTION_FLIP,
//     FRAME_MOON,10,
//     ACTION_FLIP,
//     FRAME_MOON,10,
//     ACTION_FLIP,
//     FRAME_LOOK1, 10,
//     ACTION_STOP,
// };

// const signed char AnimationBlink[] = {
//     FRAME_BLINK, 6,
//     ACTION_STOP,
// };

const signed char AnimationTurn[] = {
    FRAME_LOOK1, 4,
    FRAME_LOOK2, 4,
    ACTION_FLIP,
    ACTION_STOP,
};

// const signed char AnimationShades[] = {
//     FRAME_STAND, 50,
//     FRAME_SHADES_ARM, 20,
//     FRAME_SHADES, 125,
//     FRAME_SHADES_ARM, 25,
//     ACTION_STOP,
// };

const signed char AnimationDie[] = {
// #if ENABLE_SHAKE
//     FRAME_SHAKE,6,
// #endif

//    FRAME_ARMS_IN_AIR,10,
    //FRAME_HUNCH,100,
    ACTION_STOP,
};

const signed char AnimationWalk[] = {

    FRAME_WALK1, 6,
    FRAME_WALK2, 6,
    FRAME_WALK3, 6,
    FRAME_WALK4, 6,
    ACTION_LOOP,
//    ACTION_STOP,
};

const signed char AnimationWalkUp[] = {

    FRAME_WALKUP0, 6,
    FRAME_WALKUP1, 6,
    FRAME_WALKUP2, 6,
    FRAME_WALKUP3, 6,
    ACTION_LOOP,
//    ACTION_STOP,
};

const signed char AnimationWalkDown[] = {

    FRAME_WALKDOWN0, 6,
    FRAME_WALKDOWN1, 6,
    FRAME_WALKDOWN2, 6,
    FRAME_WALKDOWN3, 6,
    ACTION_LOOP,
//    ACTION_STOP,
};



// const signed char AnimationSnatch[] = {
//     ACTION_POSITION, 5,0,
//     FRAME_PUSH, 10,
//     ACTION_POSITION, 0,0,
// //    FRAME_IMPATIENT, 15,
//     FRAME_WALK4,15,
//     ACTION_STOP,
// };

// const signed char AnimationSnatchDown[] = {
//     ACTION_POSITION, 0,-4,
//     FRAME_SNATCH_DOWN, 10,
//     ACTION_POSITION, 0,0,
//     FRAME_IMPATIENT, 15,
//     ACTION_STOP,
// };

// const signed char AnimationSnatchUp[] = {
//     ACTION_POSITION, 0,4,
//     FRAME_ARMS_IN_AIR, 10,
//     ACTION_POSITION, 0,0,
//     FRAME_IMPATIENT, 15,
//     ACTION_STOP,
// };


// const signed char AnimationSkeleton2[] = {
//     FRAME_SKELETON4, 8,
//     FRAME_SKELETON, 8,
//     ACTION_LOOP,
//     ACTION_STOP,
// };

const signed char AnimationSkeleton[] = {

    FRAME_SKELETON1, 8,
    FRAME_SKELETON2, 8,
    FRAME_SKELETON3, 8,
    FRAME_SKELETON4, 8,
    FRAME_SKELETON5, 8,

    FRAME_BLANK, 255,
//    ACTION_LOOP,
//    ACTION_STOP,
};

//const signed char AnimationStartup[] = {
//     FRAME_SKELETON5, 8,
//     FRAME_SKELETON2, 8,
//     FRAME_SKELETON3, 8,
//     FRAME_SKELETON, 15,

//#define DX 4

//     FRAME_STAND,DX,
//     FRAME_SKELETON, DX,
//     FRAME_STAND,DX,
//     FRAME_SKELETON, DX,
//     FRAME_STAND,DX,
//     FRAME_SKELETON, DX,
//     FRAME_STAND,DX,
//     FRAME_SKELETON, DX,

    // FRAME_BLANK, 90,
    // FRAME_STAND, DX,
    // FRAME_BLANK, DX,
    // FRAME_STAND, DX,
    // FRAME_BLANK, DX,
    // FRAME_STAND, DX,
    // FRAME_BLANK, DX,
    // FRAME_STAND, DX,
    // FRAME_BLANK, DX,

    // FRAME_STAND, 1,
    // ACTION_STOP



    // FRAME_STAND,10,

    // ACTION_POSITION, -1,0,
    // FRAME_LOOK1, 5,
    // ACTION_POSITION, -1,0,
    // FRAME_LOOK2, 20,
    // ACTION_POSITION, -1,0,
    // FRAME_LOOK1, 5,
    // ACTION_POSITION, 0,0,
//    FRAME_STAND, 255,
//    ACTION_STOP,
// };

const signed char AnimationArmsCrossed[] = {
    FRAME_ARMSCROSSED, 80,
    ACTION_STOP,
};

// const signed char AnimationTalk[] = {
// #if __ENABLE_ATARIVOX
//     ACTION_SAY, __WORD_DOSOMETHING,
//     FRAME_TALK,10, //FRAMEDELAY_RANDOM,
//     FRAME_STAND,3, //FRAMEDELAY_RANDOM,
//     FRAME_TALK,6, //FRAMEDELAY_RANDOM,
//     FRAME_STAND,4, //FRAMEDELAY_RANDOM,
//     FRAME_TALK,10, //FRAMEDELAY_RANDOM,
// #endif
//     FRAME_STAND,10, //FRAMEDELAY_RANDOM,
//     FRAME_BLINK, 6,
//     ACTION_STOP,
// };

// const signed char AnimationTalk2[] = {
//     FRAME_TALK,10,
//     FRAME_BLINK, 10,
//     ACTION_STOP,
// };



//#if __ENABLE_DRIP

// const signed char AnimationDrip[] = {
//     FRAME_IMPATIENT,25,
//     FRAME_STAND,10,
//     FRAME_HAIR2, 6,
//     FRAME_HAIR, 6,
//     FRAME_HAIR2, 6,
//     FRAME_HAIR, 6,
//     ACTION_STOP,
// };

// const signed char AnimationDrip2[] = {
// //    FRAME_IMPATIENT,25,
// //    FRAME_STAND,10,
//     ACTION_POSITION, -1,0,
//     FRAME_LOOK1, 5,
//     ACTION_POSITION, -1,0,
//     FRAME_LOOK2, 15,
//     ACTION_POSITION, -1,0,
//     FRAME_LOOK1, 5,
// //    ACTION_POSITION, 0,0,
// //    FRAME_ARMSCROSSED, 90,
//     ACTION_STOP,
// };

//#endif // ENABLE_DRIP


const signed char *const AnimationVector[] = {

    // see (player.h) AnimationIdent

    AnimationDefault,       // 00 
    AnimationStandUp,       // 01
    AnimationStandLR,       // 02
    AnimationPush,          // 03
    AnimationTurn,          // 04
    AnimationDie,           // 05
    AnimationWalk,          // 06
    AnimationSkeleton,      // 07
    AnimationLocked,        // 08
    AnimationWalkUp,        // 09
    AnimationWalkDown,      // 10
};



enum AnimationIdent playerAnimationID = ID_Stand;
const signed char *playerAnimation = AnimationDefault;
const signed char *playerAnimationLoop = AnimationDefault;
unsigned int playerAnimationCount = 0;



// #define HAIR 0x28
// #define SKIN 0x46
// #define TOP1 0x58
// #define TOP2 0x54
// #define BOOT 0x24
// #define PANT 0x06
// #define BELT 0x98
// #define SOLE 0x08
// #define BONE 0x08

#define HAIR 0
#define SKIN 1
#define TOP1 2
#define TOP2 3
#define BOOT 4
#define PANT 5
#define BELT 6
#define SOLE 7
#define BONE 8

#define HMT0 9
#define HMT1 10
#define HMT2 11
#define HMT3 12

#define BDY0 13
#define BDY1 14
#define BDY2 15


const unsigned char redirect[] = { 0, 1, 1, 2};
const unsigned char playerColour[] = {

    //NTSC  PAL  PAL_60 SECAM

    0x28,   // 0 HAIR
    0x34,   // 1 SKIN
    0x06,   // 2 TOP1
    0x06,   // 3 TOP 2
    0x44,   // 4 BOOT
    0x44,   // 5 PANT
    0x58,   // 6 BELT
    0x08,   // 5 SOLE
    0x08,   // 8 BONE    

    0x2C,   // 9  HMT0
    0x28,   // 10 HMT1
    0x26,   // 11 HMT2
    0x22,   // 12 HMT3

    0x4A,   // 13  BDY0
    0x46,   // 14 BDY1
    0x44,   // 15 BDY2

};




#define SP(a,b,c,d) \
    a, b, (c << 4) + d

#define SP2(a,b) \
    a, (b << 4)

//#define PNT2 0x04


/*

// Area 0,5:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(__XXXX__,________, BONE, BONE), // 4
 SP(_XXXXXX_,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(XXX__XXX,________, BONE, BONE), // 7
 SP(XX_X__XX,________, BONE, BONE), // 8
 SP(XXX___XX,________, BONE, BONE), // 9
 SP(X_X____X,________, BONE, BONE), // 10
 SP(X______X,________, BONE, BONE), // 11
 SP(X______X,________, BONE, BONE), // 12
 SP(X______X,________, BONE, BONE), // 13
 SP(_X____X_,________, BONE, BONE), // 14
 SP(_XX__XX_,________, BONE, BONE), // 15
 SP(__XXXX__,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(_XXXXXX_,________, BONE, BONE), // 18
 SP(XX_XX_XX,________, BONE, BONE), // 19
 SP(XX_XX_XX,________, BONE, BONE), // 20
 SP(XXXXXXXX,________, BONE, BONE), // 21
 SP(X_XXXX_X,________, BONE, BONE), // 22
 SP(X_X__X_X,________, BONE, BONE), // 23
 SP(X__XX__X,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 1,5:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(__XXXX__,________, BONE, BONE), // 4
 SP(_XXXXXX_,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(XXXXXXXX,________, BONE, BONE), // 7
 SP(XXX__XXX,________, BONE, BONE), // 8
 SP(XX_X__XX,________, BONE, BONE), // 9
 SP(XXX___XX,________, BONE, BONE), // 10
 SP(X_X____X,________, BONE, BONE), // 11
 SP(X______X,________, BONE, BONE), // 12
 SP(X______X,________, BONE, BONE), // 13
 SP(_X____X_,________, BONE, BONE), // 14
 SP(_X____X_,________, BONE, BONE), // 15
 SP(__XXXX__,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(_XXXXXX_,________, BONE, BONE), // 18
 SP(XX_XX_X_,________, BONE, BONE), // 19
 SP(XX_XX_X_,________, BONE, BONE), // 20
 SP(XXXXXXX_,________, BONE, BONE), // 21
 SP(X_XXX_X_,________, BONE, BONE), // 22
 SP(X_X___X_,________, BONE, BONE), // 23
 SP(X__XX_X_,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 2,5:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(________,________, BONE, BONE), // 4
 SP(__XXXX__,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(_XXXXXX_,________, BONE, BONE), // 7
 SP(XXXXXXXX,________, BONE, BONE), // 8
 SP(XXXXXXXX,________, BONE, BONE), // 9
 SP(XX_X__XX,________, BONE, BONE), // 10
 SP(XXX___XX,________, BONE, BONE), // 11
 SP(X_X____X,________, BONE, BONE), // 12
 SP(X______X,________, BONE, BONE), // 13
 SP(X______X,________, BONE, BONE), // 14
 SP(_X____X_,________, BONE, BONE), // 15
 SP(_X____X_,________, BONE, BONE), // 16
 SP(__XXXX__,________, BONE, BONE), // 17
 SP(_X____X_,________, BONE, BONE), // 18
 SP(XXXXX_X_,________, BONE, BONE), // 19
 SP(XX_XX_X_,________, BONE, BONE), // 20
 SP(XX____X_,________, BONE, BONE), // 21
 SP(X_X_XXX_,________, BONE, BONE), // 22
 SP(X_X_XX__,________, BONE, BONE), // 23
 SP(___X____,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 3,5:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(__XXXX__,________, BONE, BONE), // 4
 SP(_XXXXXX_,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(XXXXXXXX,________, BONE, BONE), // 7
 SP(XXX__XXX,________, BONE, BONE), // 8
 SP(XX_X__XX,________, BONE, BONE), // 9
 SP(XXX___XX,________, BONE, BONE), // 10
 SP(X_X____X,________, BONE, BONE), // 11
 SP(X______X,________, BONE, BONE), // 12
 SP(X______X,________, BONE, BONE), // 13
 SP(_X____X_,________, BONE, BONE), // 14
 SP(_X____X_,________, BONE, BONE), // 15
 SP(__XXXX__,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(_XXXXXX_,________, BONE, BONE), // 18
 SP(XX_XX_X_,________, BONE, BONE), // 19
 SP(XX_XX_X_,________, BONE, BONE), // 20
 SP(XXXXXXX_,________, BONE, BONE), // 21
 SP(X_XXX_X_,________, BONE, BONE), // 22
 SP(X_X___X_,________, BONE, BONE), // 23
 SP(X__XX_X_,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 0,6:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(__XXXX__,________, BONE, BONE), // 4
 SP(_XXXXXX_,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(XXX__XXX,________, BONE, BONE), // 7
 SP(XX_X__XX,________, BONE, BONE), // 8
 SP(XXX___XX,________, BONE, BONE), // 9
 SP(X_X____X,________, BONE, BONE), // 10
 SP(X______X,________, BONE, BONE), // 11
 SP(X______X,________, BONE, BONE), // 12
 SP(X______X,________, BONE, BONE), // 13
 SP(_X____X_,________, BONE, BONE), // 14
 SP(_XX__XX_,________, BONE, BONE), // 15
 SP(__XXXX__,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(_XXXXXX_,________, BONE, BONE), // 18
 SP(XX_XX_XX,________, BONE, BONE), // 19
 SP(XX_XX_XX,________, BONE, BONE), // 20
 SP(XXXXXXXX,________, BONE, BONE), // 21
 SP(X_XXXX_X,________, BONE, BONE), // 22
 SP(X_X__X_X,________, BONE, BONE), // 23
 SP(X__XX__X,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 1,6:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(________,________, BONE, BONE), // 4
 SP(________,________, BONE, BONE), // 5
 SP(__XXXX__,________, BONE, BONE), // 6
 SP(_XXXXXX_,________, BONE, BONE), // 7
 SP(_XXXXXX_,________, BONE, BONE), // 8
 SP(XXXXXXXX,________, BONE, BONE), // 9
 SP(XXXXXXXX,________, BONE, BONE), // 10
 SP(XX_X__XX,________, BONE, BONE), // 11
 SP(XXX___XX,________, BONE, BONE), // 12
 SP(X_X____X,________, BONE, BONE), // 13
 SP(X______X,________, BONE, BONE), // 14
 SP(X______X,________, BONE, BONE), // 15
 SP(_X____X_,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(__XXXX__,________, BONE, BONE), // 18
 SP(_X____X_,________, BONE, BONE), // 19
 SP(_XXXXXX_,________, BONE, BONE), // 20
 SP(XX_XX_XX,________, BONE, BONE), // 21
 SP(XX_XX_XX,________, BONE, BONE), // 22
 SP(XX_XX_XX,________, BONE, BONE), // 23
 SP(X_XXXX_X,________, BONE, BONE), // 24
 SP(__X__X__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__XXXX__,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 2,6:
 SP(__XXXX__,________, BONE, BONE), // 0
 SP(_XXXXXX_,________, BONE, BONE), // 1
 SP(_XXXXXX_,________, BONE, BONE), // 2
 SP(XXX__XXX,________, BONE, BONE), // 3
 SP(XX_X__XX,________, BONE, BONE), // 4
 SP(XXX___XX,________, BONE, BONE), // 5
 SP(X_X____X,________, BONE, BONE), // 6
 SP(X______X,________, BONE, BONE), // 7
 SP(X______X,________, BONE, BONE), // 8
 SP(X______X,________, BONE, BONE), // 9
 SP(_X____X_,________, BONE, BONE), // 10
 SP(_XX__XX_,________, BONE, BONE), // 11
 SP(__XXXX__,________, BONE, BONE), // 12
 SP(_X____X_,________, BONE, BONE), // 13
 SP(_XXXXXX_,________, BONE, BONE), // 14
 SP(XX_XX_XX,________, BONE, BONE), // 15
 SP(XX_XX_XX,________, BONE, BONE), // 16
 SP(XXXXXXXX,________, BONE, BONE), // 17
 SP(X_XXXX_X,________, BONE, BONE), // 18
 SP(X_X__X_X,________, BONE, BONE), // 19
 SP(X__XX__X,________, BONE, BONE), // 20
 SP(__XXXX__,________, BONE, BONE), // 21
 SP(___XX___,________, BONE, BONE), // 22
 SP(________,________, BONE, BONE), // 23
 SP(__X__X__,________, BONE, BONE), // 24
 SP(__X__X__,________, BONE, BONE), // 25
 SP(__X__X__,________, BONE, BONE), // 26
 SP(________,________, BONE, BONE), // 27
 SP(________,________, BONE, BONE), // 28
 SP(________,________, BONE, BONE), // 29

// Area 3,6:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(________,________, BONE, BONE), // 4
 SP(________,________, BONE, BONE), // 5
 SP(________,________, BONE, BONE), // 6
 SP(__XXXX__,________, BONE, BONE), // 7
 SP(_XXXXXX_,________, BONE, BONE), // 8
 SP(_XXXXXX_,________, BONE, BONE), // 9
 SP(XXXXXXXX,________, BONE, BONE), // 10
 SP(XXXXXXXX,________, BONE, BONE), // 11
 SP(XX_X__XX,________, BONE, BONE), // 12
 SP(XXX___XX,________, BONE, BONE), // 13
 SP(X_X____X,________, BONE, BONE), // 14
 SP(X______X,________, BONE, BONE), // 15
 SP(X______X,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(_X____X_,________, BONE, BONE), // 18
 SP(__XXXX__,________, BONE, BONE), // 19
 SP(_X____X_,________, BONE, BONE), // 20
 SP(_XXXXXX_,________, BONE, BONE), // 21
 SP(XX_XX_XX,________, BONE, BONE), // 22
 SP(XX_XX_XX,________, BONE, BONE), // 23
 SP(XX_XX_XX,________, BONE, BONE), // 24
 SP(X_XXXX_X,________, BONE, BONE), // 25
 SP(__X__X__,________, BONE, BONE), // 26
 SP(___XX___,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 0,7:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(__XXXX__,________, BONE, BONE), // 4
 SP(_XXXXXX_,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(XXX__XXX,________, BONE, BONE), // 7
 SP(XX_X__XX,________, BONE, BONE), // 8
 SP(XXX___XX,________, BONE, BONE), // 9
 SP(X_X____X,________, BONE, BONE), // 10
 SP(X______X,________, BONE, BONE), // 11
 SP(X______X,________, BONE, BONE), // 12
 SP(X______X,________, BONE, BONE), // 13
 SP(_X____X_,________, BONE, BONE), // 14
 SP(_XX__XX_,________, BONE, BONE), // 15
 SP(__XXXX__,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(_XXXXXX_,________, BONE, BONE), // 18
 SP(XX_XX_XX,________, BONE, BONE), // 19
 SP(XX_XX_XX,________, BONE, BONE), // 20
 SP(XXXXXXXX,________, BONE, BONE), // 21
 SP(X_XXXX_X,________, BONE, BONE), // 22
 SP(X_X__X_X,________, BONE, BONE), // 23
 SP(X__XX__X,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__XX_,________, BONE, BONE), // 29

// Area 1,7:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(___XXX__,________, BONE, BONE), // 4
 SP(_XXXXXX_,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(XXXX__XX,________, BONE, BONE), // 7
 SP(XXX__X_X,________, BONE, BONE), // 8
 SP(X_X_X__X,________, BONE, BONE), // 9
 SP(X_X_X__X,________, BONE, BONE), // 10
 SP(X_X____X,________, BONE, BONE), // 11
 SP(XXX____X,________, BONE, BONE), // 12
 SP(XXX____X,________, BONE, BONE), // 13
 SP(_XXX__X_,________, BONE, BONE), // 14
 SP(_XXX__X_,________, BONE, BONE), // 15
 SP(__XXXX__,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(XXXXXXXX,________, BONE, BONE), // 18
 SP(XX_XX_XX,________, BONE, BONE), // 19
 SP(X_XXXX_X,________, BONE, BONE), // 20
 SP(X_XXXX_X,________, BONE, BONE), // 21
 SP(_X_XX_X_,________, BONE, BONE), // 22
 SP(_X____X_,________, BONE, BONE), // 23
 SP(___XX___,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__XX_,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 2,7:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(__XXXX__,________, BONE, BONE), // 4
 SP(_XXXXXX_,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(XXX__XXX,________, BONE, BONE), // 7
 SP(XX_X__XX,________, BONE, BONE), // 8
 SP(XXX___XX,________, BONE, BONE), // 9
 SP(X_X____X,________, BONE, BONE), // 10
 SP(X______X,________, BONE, BONE), // 11
 SP(X______X,________, BONE, BONE), // 12
 SP(X______X,________, BONE, BONE), // 13
 SP(_X____X_,________, BONE, BONE), // 14
 SP(_XX__XX_,________, BONE, BONE), // 15
 SP(__XXXX__,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(XXXXXXXX,________, BONE, BONE), // 18
 SP(XX_XX_XX,________, BONE, BONE), // 19
 SP(X_XXXX_X,________, BONE, BONE), // 20
 SP(X_XXXX_X,________, BONE, BONE), // 21
 SP(_X_XX_X_,________, BONE, BONE), // 22
 SP(_X____X_,________, BONE, BONE), // 23
 SP(___XX___,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__X__,________, BONE, BONE), // 28
 SP(__X__XX_,________, BONE, BONE), // 29

// Area 3,7:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(__XXX___,________, BONE, BONE), // 4
 SP(_XXXXXX_,________, BONE, BONE), // 5
 SP(_XXXXXX_,________, BONE, BONE), // 6
 SP(XX__XXXX,________, BONE, BONE), // 7
 SP(X__X_XXX,________, BONE, BONE), // 8
 SP(X_X__X_X,________, BONE, BONE), // 9
 SP(X_X__X_X,________, BONE, BONE), // 10
 SP(X____X_X,________, BONE, BONE), // 11
 SP(X____XXX,________, BONE, BONE), // 12
 SP(X____XXX,________, BONE, BONE), // 13
 SP(_X__XXX_,________, BONE, BONE), // 14
 SP(_X__XXX_,________, BONE, BONE), // 15
 SP(__XXXX__,________, BONE, BONE), // 16
 SP(_X____X_,________, BONE, BONE), // 17
 SP(XXXXXXXX,________, BONE, BONE), // 18
 SP(XX_XX_XX,________, BONE, BONE), // 19
 SP(X_XXXX_X,________, BONE, BONE), // 20
 SP(X_XXXX_X,________, BONE, BONE), // 21
 SP(_X_XX_X_,________, BONE, BONE), // 22
 SP(_X____X_,________, BONE, BONE), // 23
 SP(___XX___,________, BONE, BONE), // 24
 SP(__XXXX__,________, BONE, BONE), // 25
 SP(___XX___,________, BONE, BONE), // 26
 SP(__X__X__,________, BONE, BONE), // 27
 SP(__X__XX_,________, BONE, BONE), // 28
 SP(__X__X__,________, BONE, BONE), // 29

// Area 0,8:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(________,________, BONE, BONE), // 3
 SP(____XXXX,________, BONE, BONE), // 4
 SP(___XXXXX,X_______, BONE, BONE), // 5
 SP(___XXXXX,X_______, BONE, BONE), // 6
 SP(__XXX__X,XX______, BONE, BONE), // 7
 SP(__XX_X__,XX______, BONE, BONE), // 8
 SP(__XXX___,XX______, BONE, BONE), // 9
 SP(__X_X___,_X______, BONE, BONE), // 10
 SP(__X_____,_X______, BONE, BONE), // 11
 SP(__X_____,_X______, BONE, BONE), // 12
 SP(__X_____,_X______, BONE, BONE), // 13
 SP(___X____,X_______, BONE, BONE), // 14
 SP(___XX__X,X_______, BONE, BONE), // 15
 SP(____XXXX,________, BONE, BONE), // 16
 SP(___X____,X_______, BONE, BONE), // 17
 SP(___XXXXX,X_______, BONE, BONE), // 18
 SP(__XX_XX_,XX______, BONE, BONE), // 19
 SP(__XX_XX_,XX______, BONE, BONE), // 20
 SP(__XXXXXX,XX______, BONE, BONE), // 21
 SP(__X_XXXX,_X______, BONE, BONE), // 22
 SP(__X_X__X,_X______, BONE, BONE), // 23
 SP(__X__XX_,_X______, BONE, BONE), // 24
 SP(____XXXX,________, BONE, BONE), // 25
 SP(_____XX_,________, BONE, BONE), // 26
 SP(____X__X,________, BONE, BONE), // 27
 SP(____X__X,________, BONE, BONE), // 28
 SP(____X__X,________, BONE, BONE), // 29

// Area 1,8:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(____XXXX,________, BONE, BONE), // 3
 SP(___XXXXX,X_______, BONE, BONE), // 4
 SP(___XXXXX,X_______, BONE, BONE), // 5
 SP(__XXX__X,XX______, BONE, BONE), // 6
 SP(__XX_X__,XX______, BONE, BONE), // 7
 SP(__XXX___,XX______, BONE, BONE), // 8
 SP(__X_X___,_X______, BONE, BONE), // 9
 SP(__X_____,_X______, BONE, BONE), // 10
 SP(__X_____,_X______, BONE, BONE), // 11
 SP(__X_____,_X______, BONE, BONE), // 12
 SP(___X____,X_______, BONE, BONE), // 13
 SP(___XX__X,X_______, BONE, BONE), // 14
 SP(_X__XXXX,__X_____, BONE, BONE), // 15
 SP(XXXX____,XXXX____, BONE, BONE), // 16
 SP(XXXXXXXX,XXXX____, BONE, BONE), // 17
 SP(__XX_XX_,XX______, BONE, BONE), // 18
 SP(___X_XX_,X_______, BONE, BONE), // 19
 SP(___XXXXX,X_______, BONE, BONE), // 20
 SP(____XXXX,________, BONE, BONE), // 21
 SP(____X__X,________, BONE, BONE), // 22
 SP(_____XX_,________, BONE, BONE), // 23
 SP(____XXXX,________, BONE, BONE), // 24
 SP(_____XX_,________, BONE, BONE), // 25
 SP(____X__X,________, BONE, BONE), // 26
 SP(____X__X,________, BONE, BONE), // 27
 SP(____X__X,________, BONE, BONE), // 28
 SP(________,________, BONE, BONE), // 29

// Area 2,8:
 SP(________,________, BONE, BONE), // 0
 SP(__X_____,_X______, BONE, BONE), // 1
 SP(__X_XXXX,_X______, BONE, BONE), // 2
 SP(_X_XXXXX,X_X_____, BONE, BONE), // 3
 SP(_X_X____,X_X_____, BONE, BONE), // 4
 SP(_XXX_X__,XXX_____, BONE, BONE), // 5
 SP(_XX_X___,_XX_____, BONE, BONE), // 6
 SP(_XX_X___,_XX_____, BONE, BONE), // 7
 SP(_XX_____,_XX_____, BONE, BONE), // 8
 SP(_XX_____,_XX_____, BONE, BONE), // 9
 SP(_XXX____,XXX_____, BONE, BONE), // 10
 SP(_XX_XXXX,_XX_____, BONE, BONE), // 11
 SP(__X_XXXX,_X______, BONE, BONE), // 12
 SP(__XX____,XX______, BONE, BONE), // 13
 SP(__XXXXXX,XX______, BONE, BONE), // 14
 SP(__XX_XX_,X_______, BONE, BONE), // 15
 SP(___X_XX_,X_______, BONE, BONE), // 16
 SP(____XXXX,________, BONE, BONE), // 17
 SP(____XXXX,________, BONE, BONE), // 18
 SP(_____XX_,________, BONE, BONE), // 19
 SP(____X__X,________, BONE, BONE), // 20
 SP(___XXXXX,X_______, BONE, BONE), // 21
 SP(___X_XX_,X_______, BONE, BONE), // 22
 SP(__XX____,XX______, BONE, BONE), // 23
 SP(__X_____,_X______, BONE, BONE), // 24
 SP(________,________, BONE, BONE), // 25
 SP(________,________, BONE, BONE), // 26
 SP(________,________, BONE, BONE), // 27
 SP(________,________, BONE, BONE), // 28
 SP(________,________, BONE, BONE), // 29

// Area 3,8:
 SP(________,________, BONE, BONE), // 0
 SP(________,________, BONE, BONE), // 1
 SP(________,________, BONE, BONE), // 2
 SP(____XXXX,________, BONE, BONE), // 3
 SP(___XXXXX,X_______, BONE, BONE), // 4
 SP(___XXXXX,X_______, BONE, BONE), // 5
 SP(__XXX__X,XX______, BONE, BONE), // 6
 SP(__XX_X__,XX______, BONE, BONE), // 7
 SP(__XXX___,XX______, BONE, BONE), // 8
 SP(__X_X___,_X______, BONE, BONE), // 9
 SP(__X_____,_X______, BONE, BONE), // 10
 SP(__X_____,_X______, BONE, BONE), // 11
 SP(__X_____,_X______, BONE, BONE), // 12
 SP(___X____,X_______, BONE, BONE), // 13
 SP(___XX__X,X_______, BONE, BONE), // 14
 SP(_X__XXXX,__X_____, BONE, BONE), // 15
 SP(XXXX____,XXXX____, BONE, BONE), // 16
 SP(XXXXXXXX,XXXX____, BONE, BONE), // 17
 SP(__XX_XX_,XX______, BONE, BONE), // 18
 SP(___X_XX_,X_______, BONE, BONE), // 19
 SP(___XXXXX,X_______, BONE, BONE), // 20
 SP(____XXXX,________, BONE, BONE), // 21
 SP(____X__X,________, BONE, BONE), // 22
 SP(_____XX_,________, BONE, BONE), // 23
 SP(____XXXX,________, BONE, BONE), // 24
 SP(_____XX_,________, BONE, BONE), // 25
 SP(____X__X,________, BONE, BONE), // 26
 SP(____X__X,________, BONE, BONE), // 27
 SP(____X__X,________, BONE, BONE), // 28
 SP(________,________, BONE, BONE), // 29
*/

const unsigned char shape_FRAME_BLANK[] = {            // 00

    0,
    0,0,

    SP2( ________, ____  ),     //00
    SP2( ________, ____  ),     //01
    SP2( ________, ____  ),     //02
    SP2( ________, ____  ),     //03
    SP2( ________, ____  ),     //04
    SP2( ________, ____  ),     //05
    SP2( ________, ____  ),     //06
    SP2( ________, ____  ),     //07
    SP2( ________, ____  ),     //08
    SP2( ________, ____  ),     //09
    SP2( ________, ____  ),     //10
    SP2( ________, ____  ),     //11
    SP2( ________, ____  ),     //12
    SP2( ________, ____  ),     //13
    SP2( ________, ____  ),     //14
    SP2( ________, ____  ),     //15
    SP2( ________, ____  ),     //16
    SP2( ________, ____  ),     //17
    SP2( ________, ____  ),     //18
    SP2( ________, ____  ),     //19
    SP2( ________, ____  ),     //20
    SP2( ________, ____  ),     //21
    SP2( ________, ____  ),     //22
    SP2( ________, ____  ),     //23
    SP2( ________, ____  ),     //24
    SP2( ________, ____  ),     //25
    SP2( ________, ____  ),     //26
    SP2( ________, ____  ),     //27
    SP2( ________, ____  ),     //28
    SP2( ________, ____  ),     //29
};

const unsigned char shape_FRAME_STAND[] = {

    0x80 | 26,
    4+0, 0,

    SP2( __XXXX__, HMT0 ),     // 00
    SP2( _XXXXXX_, HMT0 ),     // 01
    SP2( _XXXXXX_, HMT0 ),     // 02
    SP2( XXX__XXX, HMT1 ),     // 03
    SP2( XX_X__XX, HMT1 ),     // 04
    SP2( XXX___XX, HMT1 ),     // 05
    SP2( X_X____X, HMT1 ),     // 06
    SP2( X______X, HMT2 ),     // 07
    SP2( X______X, HMT2 ),     // 08
    SP2( X______X, HMT2 ),     // 09
    SP2( _X____X_, HMT3 ),     // 10
    SP2( _XX__XX_, HMT3 ),     // 11
    SP2( __XXXX__, HMT3 ),     // 12
    SP2( _X____X_, BDY1 ),     // 13
    SP2( _XXXXXX_, BDY0 ),     // 14
    SP2( XX_XX_XX, BDY1 ),     // 15
    SP2( XX_XX_XX, BDY1 ),     // 16
    SP2( XXXXXXXX, BDY2 ),     // 17
    SP2( X_XXXX_X, BDY2 ),     // 18
    SP2( X_X__X_X, BDY2 ),     // 19
    SP2( X__XX__X, HMT1 ),     // 20
    SP2( __XXXX__, HMT1 ),     // 21
    SP2( ___XX___, HMT1 ),     // 22
    SP2( __X__X__, HMT1 ),     // 23
    SP2( __X__X__, HMT2 ),     // 24
    SP2( __X__X__, HMT0 ),     // 25
};

const unsigned char shape_FRAME_ARMS_IN_AIR[] = {      // 02

    24,
    2, 5,

    SP(__X_____,_X______, HMT0, BONE), // 00
    SP(__X_XXXX,_X______, HMT0, BONE), // 01
    SP(_X_XXXXX,X_X_____, HMT0, BONE), // 02
    SP(_X_X____,X_X_____, HMT1, BONE), // 03
    SP(_XXX_X__,XXX_____, HMT1, BONE), // 04
    SP(_XX_X___,_XX_____, HMT1, BONE), // 05
    SP(_XX_X___,_XX_____, HMT1, BONE), // 06
    SP(_XX_____,_XX_____, HMT2, BONE), // 07
    SP(_XX_____,_XX_____, HMT2, BONE), // 08
    SP(_XXX____,XXX_____, HMT2, BONE), // 09
    SP(_XX_XXXX,_XX_____, HMT3, BONE), // 10
    SP(__X_XXXX,_X______, HMT3, BONE), // 11
    SP(__XX____,XX______, HMT3, BONE), // 12
    SP(__XXXXXX,XX______, BDY1, BONE), // 13
    SP(__XX_XX_,X_______, BDY0, BONE), // 14
    SP(___X_XX_,X_______, BDY1, BONE), // 15
    SP(____XXXX,________, BDY2, BONE), // 16
    SP(____XXXX,________, BDY2, BONE), // 17
    SP(_____XX_,________, BDY2, BONE), // 18
    SP(____X__X,________, BDY2, BONE), // 19
    SP(___XXXXX,X_______, HMT1, BONE), // 20
    SP(___X_XX_,X_______, HMT1, BONE), // 21
    SP(__XX____,XX______, HMT2, BONE), // 22
    SP(__X_____,_X______, HMT0, BONE), // 23
};

const unsigned char shape_FRAME_HUNCH[] = {            // 03

    0x80 | 26,
    4+0, 0,

    SP2( ___XXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXXX__XX, HMT1 ), // 03
    SP2( XXX__X_X, HMT1 ), // 04
    SP2( X_X_X__X, HMT1 ), // 05
    SP2( X_X_X__X, HMT1 ), // 06
    SP2( X_X____X, HMT2 ), // 07
    SP2( XXX____X, HMT2 ), // 08
    SP2( XXX____X, HMT2 ), // 09
    SP2( _XXX__X_, HMT3 ), // 10
    SP2( _XXX__X_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( _X____X_, BDY1 ), // 13
    SP2( XXXXXXXX, BDY0 ), // 14
    SP2( XX_XX_XX, BDY1 ), // 15
    SP2( X_XXXX_X, BDY2 ), // 16
    SP2( X_XXXX_X, BDY2 ), // 17
    SP2( _X_XX_X_, BDY2 ), // 18
    SP2( _X____X_, BDY2 ), // 19
    SP2( ___XX___, HMT1 ), // 20
    SP2( __XXXX__, HMT2 ), // 21
    SP2( ___XX___, HMT2 ), // 22
    SP2( __X__X__, HMT2 ), // 23
    SP2( __X__XX_, HMT2 ), // 24
    SP2( __X__X__, HMT0 ), // 25

};

const unsigned char shape_FRAME_PUSH[] = {             // 04

    25,
    4, 0,

    SP(____XXX_,______X_, HMT0, BONE), // 00
    SP(__XXXXXX,___XX___, HMT0, BONE), // 01
    SP(__XXXXXX,_____X__, HMT0, BONE), // 02
    SP(_XXXX__X,X_____X_, HMT1, BONE), // 03
    SP(_XXX__X_,X____XX_, HMT1, BONE), // 04
    SP(_X_X_X__,X____X_X, HMT1, BONE), // 05
    SP(_X_X_X__,X___X__X, HMT1, BONE), // 06
    SP(_X_X____,X___X__X, HMT2, BONE), // 07
    SP(_XXX____,X__X____, HMT2, BONE), // 08
    SP(_XXX____,X__X____, HMT2, BONE), // 09
    SP(__XXX__X,__X_____, HMT3, BONE), // 10
    SP(__XXX__X,__X__X__, HMT3, BONE), // 11
    SP(_X_XXXX_,________, HMT3, BONE), // 12
    SP(_XX____X,X_______, BDY1, BONE), // 13
    SP(_X_XX_XX,X_______, BDY0, BONE), // 14
    SP(_X_XX_XX,________, BDY1, BONE), // 15
    SP(_XXXX_X_,________, BDY2, BONE), // 16
    SP(_X_XXX__,________, BDY2, BONE), // 17
    SP(_X_XX_X_,________, BDY2, BONE), // 18
    SP(_X__XX__,________, HMT1, BONE), // 19
    SP(____XX__,________, HMT2, BONE), // 20
    SP(____XX__,________, HMT2, BONE), // 21
    SP(___XX___,________, HMT2, BONE), // 22
    SP(___XX___,________, HMT2, BONE), // 23
    SP(____XX__,________, HMT0, BONE), // 24
};

const unsigned char shape_FRAME_PUSH2[] = {            // 05

    26,
    4, 0,

    SP(________,_XX_____, BONE, BONE), // 00
    SP(________,X_______, BONE, BONE), // 01
    SP(__XXXX_X,________, HMT0, BONE), // 02
    SP(_XXXXXX_,X_______, HMT0, BONE), // 03
    SP(_XXXXXX_,X_______, HMT0, BONE), // 04
    SP(XXXX__X_,_X______, HMT1, BONE), // 05
    SP(XXX__X_X,_X______, HMT1, BONE), // 06
    SP(X_X_X__X,________, HMT1, BONE), // 07
    SP(X_X_X__X,_X______, HMT1, BONE), // 08
    SP(X_X____X,_X______, HMT2, BONE), // 09
    SP(XXX____X,_X______, HMT2, BONE), // 10
    SP(XXX____X,________, HMT2, BONE), // 11
    SP(_XXX__X_,________, HMT3, BONE), // 12
    SP(_XXX_X_X,________, HMT3, BONE), // 13
    SP(X_XXXXXX,________, HMT3, BONE), // 14
    SP(XX____XX,________, BDY1, BONE), // 15
    SP(X_XX_XX_,________, BDY0, BONE), // 16
    SP(X_XX_XX_,________, BDY1, BONE), // 17
    SP(_XXXX___,________, BDY2, BONE), // 18
    SP(_X_XX_X_,________, BDY2, BONE), // 19
    SP(_X_XX_X_,________, HMT1, BONE), // 20
    SP(_X__XX__,________, HMT2, BONE), // 21
    SP(____XX__,________, HMT2, BONE), // 22
    SP(____XX__,________, HMT2, BONE), // 23
    SP(___XX___,________, HMT2, BONE), // 24
    SP(___XXX__,________, HMT0, BONE), // 25
};

const unsigned char shape_FRAME_IMPATIENT[] = {        // 06
};

const unsigned char shape_FRAME_IMPATIENT2[] = {       // 07
};

const unsigned char shape_FRAME_LOOK1[] = {            // 08
};

const unsigned char shape_FRAME_LOOK2[] = {            // 09
};

const unsigned char shape_FRAME_SHADES[] = {           // 10
};

const unsigned char shape_FRAME_SHADES_ARM[] = {       // 11
};

const unsigned char shape_FRAME_BLINK[] = {            // 12
};

const unsigned char shape_FRAME_WALK1[] = {            // 13

    0x80 | 26,
    5, 0,

    SP2( ___XXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXXX__XX, HMT1 ), // 03
    SP2( XXX__X_X, HMT1 ), // 04
    SP2( X_X_X__X, HMT1 ), // 05
    SP2( X_X_X__X, HMT1 ), // 06
    SP2( X_X____X, HMT2 ), // 07
    SP2( XXX____X, HMT2 ), // 08
    SP2( XXX____X, HMT2 ), // 09
    SP2( _XXX__X_, HMT3 ), // 10
    SP2( _XXX__X_, HMT3 ), // 11
    SP2( X_XXXX__, HMT3 ), // 12
    SP2( XX______, BDY0 ), // 13
    SP2( X_XX_X__, BDY1 ), // 14
    SP2( X_XX_X__, BDY2 ), // 15
    SP2( XXXX_X__, BDY2 ), // 16
    SP2( X_XX____, BDY2 ), // 17
    SP2( X_XX_X__, BDY2 ), // 18
    SP2( X_X__X__, HMT2 ), // 19
    SP2( X__XX___, HMT2 ), // 20
    SP2( ___XX___, HMT2 ), // 21
    SP2( ___XX___, HMT2 ), // 22
    SP2( __XX____, HMT2 ), // 23
    SP2( __XX____, HMT2 ), // 24
    SP2( __XXX___, HMT0 ), // 25
};


const unsigned char shape_FRAME_WALK2[] = {            // 14

    0x80 | 24,
    3, 3,

    SP2( ___XXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXXX__XX, HMT1 ), // 03
    SP2( XXX__X_X, HMT1 ), // 04
    SP2( X_X_X__X, HMT1 ), // 05
    SP2( X_X_X__X, HMT1 ), // 06
    SP2( X_X____X, HMT2 ), // 07
    SP2( XXX____X, HMT2 ), // 08
    SP2( XXX____X, HMT2 ), // 09
    SP2( _XXX__X_, HMT3 ), // 10
    SP2( _XXX__X_, HMT3 ), // 11
    SP2( X_XXXX__, HMT3 ), // 12
    SP2( XX___XX_, BDY1 ), // 13
    SP2( XX_XXXX_, BDY0 ), // 14
    SP2( XX_XXXX_, BDY1 ), // 15
    SP2( XXX_XX__, BDY2 ), // 16
    SP2( X_XX____, BDY2 ), // 17
    SP2( _X______, BDY2 ), // 18
    SP2( _X_XXX_X, HMT1 ), // 19
    SP2( XXXX_XXX, HMT2 ), // 20
    SP2( XXX__XXX, HMT2 ), // 21
    SP2( X_X___X_, HMT2 ), // 22
    SP2( ______X_, HMT0 ), // 23
};


const unsigned char shape_FRAME_WALK3[] = {            // 15

    0x80 | 26,
    4, 0,

    SP2(___XXX__, HMT0 ), // 00
    SP2(_XXXXXX_, HMT0 ), // 01
    SP2(_XXXXXX_, HMT0 ), // 02
    SP2(XXXX__XX, HMT1 ), // 03
    SP2(XXX__X_X, HMT1 ), // 04
    SP2(X_X_X__X, HMT1 ), // 05
    SP2(X_X_X__X, HMT1 ), // 06
    SP2(X_X____X, HMT2 ), // 07
    SP2(XXX____X, HMT2 ), // 08
    SP2(XXX____X, HMT2 ), // 09
    SP2(_XXX__X_, HMT3 ), // 10
    SP2(_XXX__X_, HMT3 ), // 11
    SP2(X_XXXX__, HMT3 ), // 12
    SP2(XX______, BDY1 ), // 13
    SP2(X_XX_X__, BDY0 ), // 14
    SP2(X_XX_X__, BDY1 ), // 15
    SP2(XXXX_X__, BDY2 ), // 16
    SP2(X_XX____, BDY2 ), // 17
    SP2(X_XX_X__, BDY2 ), // 18
    SP2(X_X__X__, BDY2 ), // 19
    SP2(X__XX___, HMT1 ), // 20
    SP2(___XX___, HMT2 ), // 21
    SP2(___XX___, HMT2 ), // 22
    SP2(__XX____, HMT2 ), // 23
    SP2(__XX____, HMT2 ), // 24
    SP2(__XXX___, HMT0 ), // 25
};


const unsigned char shape_FRAME_WALK4[] = {            // 16

    0x80 | 24,
    3, 3,

    SP2(___XXX__, HMT0 ), // 00
    SP2(_XXXXXX_, HMT0 ), // 01
    SP2(_XXXXXX_, HMT0 ), // 02
    SP2(XXXX__XX, HMT1 ), // 03
    SP2(XXX__X_X, HMT1 ), // 04
    SP2(X_X_X__X, HMT1 ), // 05
    SP2(X_X_X__X, HMT1 ), // 06
    SP2(X_X____X, HMT2 ), // 07
    SP2(XXX____X, HMT2 ), // 08
    SP2(XXX____X, HMT2 ), // 09
    SP2(_XXX__X_, HMT3 ), // 10
    SP2(_XXX__X_, HMT3 ), // 11
    SP2(X_XXXX__, HMT3 ), // 12
    SP2(XX_____X, BDY1 ), // 13
    SP2(_XXX_X_X, BDY0 ), // 14
    SP2(XXXX_X_X, BDY1 ), // 15
    SP2(XXXX_X__, BDY2 ), // 16
    SP2(_XX_____, BDY2 ), // 17
    SP2(_____X__, HMT1 ), // 18
    SP2(_X_X_X_X, HMT2 ), // 19
    SP2(XXXXXXXX, HMT2 ), // 20
    SP2(XXXX_XXX, HMT2 ), // 21
    SP2(X_X___X_, HMT2 ), // 22
    SP2(______X_, HMT0 ), // 23
 
 };

const unsigned char shape_FRAME_SNATCH_DOWN[] = {      // 17
};

const unsigned char shape_FRAME_SKELETON1[] = {         // 18

    20,
    0,0,

    SP( _____XXX,X_______, BONE, BONE ),     // 00
    SP( ____XXXX,XX______, BONE, BONE ),     // 01
    SP( ____X__X,__X_____, BONE, BONE ),     // 02
    SP( ____X__X,__X_____, BONE, BONE ),     // 03
    SP( ____XXXX,XX______, BONE, BONE ),     // 04
    SP( _____X_X,_X______, BONE, BONE ),     // 05
    SP( ______X_,X_______, BONE, BONE ),     // 06
    SP( _______X,________, BONE, BONE ),     // 07
    SP( ____XXXX,XX______, BONE, BONE ),     // 08
    SP( ___X___X,__X_____, BONE, BONE ),     // 09
    SP( __XX_XXX,X_XX____, BONE, BONE ),     // 10
    SP( __X____X,___X____, BONE, BONE ),     // 11
    SP( _____XXX,XX______, BONE, BONE ),     // 12
    SP( __XX__XX,X_XX____, BONE, BONE ),     // 13
    SP( _X___X_X,_X__X___, BONE, BONE ),     // 14
    SP( _____X__,_X______, BONE, BONE ),     // 15
    SP( ____XX__,_XX_____, BONE, BONE ),     // 16
    SP( _____X__,_X______, BONE, BONE ),     // 17
    SP( ________,________, BONE, BONE ),     // 18
    SP( ____XXX_,XXX_____, BONE, BONE ),     // 19
};


const unsigned char shape_FRAME_SKELETON2[] = {        // 21

    20,
    1, 0,

    SP( ____XXXX,________, BONE, BONE ),     // 00
    SP( ___XXXXX,X_______, BONE, BONE ),     // 01
    SP( __X__X__,X_______, BONE, BONE ),     // 02
    SP( __X__X__,X_______, BONE, BONE ),     // 03
    SP( __XXXXXX,X_______, BONE, BONE ),     // 04
    SP( ___X_X_X,________, BONE, BONE ),     // 05
    SP( ____X_X_,________, BONE, BONE ),     // 06
    SP( _______X,________, BONE, BONE ),     // 07
    SP( ___XXXXX,X_______, BONE, BONE ),     // 08
    SP( __X___X_,_X______, BONE, BONE ),     // 09
    SP( _XX_XXXX,_XX_____, BONE, BONE ),     // 10
    SP( _X____X_,__X_____, BONE, BONE ),     // 11
    SP( ____XXXX,X_______, BONE, BONE ),     // 12
    SP( _XX__XXX,_XX_____, BONE, BONE ),     // 13
    SP( X___X_X_,X__X____, BONE, BONE ),     // 14
    SP( ____X___,X_______, BONE, BONE ),     // 15
    SP( ___XX___,XX______, BONE, BONE ),     // 16
    SP( ____X___,X_______, BONE, BONE ),     // 17
    SP( ________,________, BONE, BONE ),     // 18
    SP( ___XXX_X,XX______, BONE, BONE ),     // 19

};


const unsigned char shape_FRAME_SKELETON3[] = {        // 20

    16,
    0, 0,

    SP( _______X,XXX_____, BONE, BONE ),     // 00
    SP( ______XX,XXXX____, BONE, BONE ),     // 01
    SP( ______X_,_X__X___, BONE, BONE ),     // 02
    SP( ______X_,_X__X___, BONE, BONE ),     // 03
    SP( ______XX,XXXX____, BONE, BONE ),     // 04
    SP( _______X,_X_X____, BONE, BONE ),     // 05
    SP( ________,X_X_____, BONE, BONE ),     // 06
    SP( __X_XXX_,XXX_____, BONE, BONE ),     // 07
    SP( _X____X_,________, BONE, BONE ),     // 08
    SP( _X__XXXX,___X____, BONE, BONE ),     // 09
    SP( ______XX,__XX____, BONE, BONE ),     // 10
    SP( _X__X_X_,X_______, BONE, BONE ),     // 11
    SP( _X__X___,X___XX__, BONE, BONE ),     // 12
    SP( _X__X___,X___X___, BONE, BONE ),     // 13
    SP( X_______,________, BONE, BONE ),     // 14
    SP( ___XXX_X,XX______, BONE, BONE ),     // 15
};


const unsigned char shape_FRAME_SKELETON4[] = {        // 19

    12,
    -1,0,

    SP( ________,XXXX____, BONE, BONE ),     // 00
    SP( _______X,XXXXX___, BONE, BONE ),     // 01
    SP( _______X,__X__X__, BONE, BONE ),     // 02
    SP( _______X,__X__X__, BONE, BONE ),     // 03
    SP( _______X,XXXXX___, BONE, BONE ),     // 04
    SP( ________,X_X_X___, BONE, BONE ),     // 05
    SP( ________,_X_X____, BONE, BONE ),     // 06
    SP( _____X__,XXXX____, BONE, BONE ),     // 07
    SP( ___X___X,________, BONE, BONE ),     // 08
    SP( _______X,XX______, BONE, BONE ),     // 09
    SP( ___X__X_,______X_, BONE, BONE ),     // 10
    SP( __XX__XX,X_XXX__X, BONE, BONE ),     // 11
};


const unsigned char shape_FRAME_SKELETON5[] = {        // 22

    0x80 | 3,
    6, 0,

    SP2( _XXXXXX_, BONE ),     // 00
    SP2( X__X__XX, BONE ),     // 01
    SP2( XX_XX__X, BONE ),     // 02
};

const unsigned char shape_FRAME_ARMSCROSSED[] = {      // 23
};

const unsigned char shape_FRAME_TALK[] = {             // 24
};

const unsigned char shape_FRAME_WALKUP0[] = {          // 25

    0x80 | 26,
    3, 0,

    SP2( __XXXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXXXXXXX, HMT1 ), // 03
    SP2( XXXXXXXX, HMT1 ), // 04
    SP2( X_XXXX_X, HMT1 ), // 05
    SP2( X_XXXX_X, HMT1 ), // 06
    SP2( X_XXXX_X, HMT2 ), // 07
    SP2( XXXXXXXX, HMT2 ), // 08
    SP2( XXXXXXXX, HMT2 ), // 09
    SP2( _XXXXXX_, HMT3 ), // 10
    SP2( _XXXXXX_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( _X____X_, BDY1 ), // 13
    SP2( _X_XX_X_, BDY0 ), // 14
    SP2( XX____XX, BDY1 ), // 15
    SP2( XX_XX_XX, BDY2 ), // 16
    SP2( X_XXXX_X, BDY2 ), // 17
    SP2( X_XXXX_X, BDY2 ), // 18
    SP2( X_XXXX_X, BDY2 ), // 19
    SP2( X__XX__X, BDY2 ), // 20
    SP2( __X__X__, HMT1 ), // 21
    SP2( ___XX___, HMT2 ), // 22
    SP2( __X__X__, HMT2 ), // 23
    SP2( __X__X__, HMT2 ), // 24
    SP2( __X__X__, HMT0 ), // 25
};

const unsigned char shape_FRAME_WALKUP1[] = {          // 26

    0x80 | 25,
    3, 2,

    SP2( __XXXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXXXXXXX, HMT1 ), // 03
    SP2( XXXXXXXX, HMT1 ), // 04
    SP2( X_XXXX_X, HMT1 ), // 05
    SP2( X_XXXX_X, HMT1 ), // 06
    SP2( X_XXXX_X, HMT2 ), // 07
    SP2( XXXXXXXX, HMT2 ), // 08
    SP2( XXXXXXXX, HMT2 ), // 09
    SP2( _XXXXXX_, HMT3 ), // 10
    SP2( _XXXXXX_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( ______X_, BDY1 ), // 13
    SP2( _X__X_XX, BDY0 ), // 14
    SP2( XX_X__XX, BDY1 ), // 15
    SP2( XX__X_XX, BDY2 ), // 16
    SP2( X__XXXX_, BDY2 ), // 17
    SP2( __XXXX__, BDY2 ), // 18
    SP2( ___XXX__, BDY2 ), // 19
    SP2( __X_X___, HMT1 ), // 20
    SP2( _XXX_X__, HMT2 ), // 21
    SP2( _XX__X__, HMT2 ), // 22
    SP2( _XX_____, HMT2 ), // 23
    SP2( __X_____, HMT0 ), // 24
};

const unsigned char shape_FRAME_WALKUP2[] = {          // 27

    0x80 | 26,
    3, 0,

    SP2( __XXXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXXXXXXX, HMT1 ), // 03
    SP2( XXXXXXXX, HMT1 ), // 04
    SP2( X_XXXX_X, HMT1 ), // 05
    SP2( X_XXXX_X, HMT1 ), // 06
    SP2( X_XXXX_X, HMT2 ), // 07
    SP2( XXXXXXXX, HMT2 ), // 08
    SP2( XXXXXXXX, HMT2 ), // 09
    SP2( _XXXXXX_, HMT3 ), // 10
    SP2( _XXXXXX_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( _X____X_, BDY1 ), // 13
    SP2( _X_XX_X_, BDY0 ), // 14
    SP2( XX____XX, BDY1 ), // 15
    SP2( XX_XX_XX, BDY2 ), // 16
    SP2( X_XXXX_X, BDY2 ), // 17
    SP2( X_XXXX_X, BDY2 ), // 18
    SP2( X_XXXX_X, BDY2 ), // 19
    SP2( X__XX__X, BDY2 ), // 20
    SP2( __X__X__, HMT1 ), // 21
    SP2( ___XX___, HMT2 ), // 22
    SP2( __X__X__, HMT2 ), // 23
    SP2( __X__X__, HMT2 ), // 24
    SP2( __X__X__, HMT0 ), // 25
};

const unsigned char shape_FRAME_WALKUP3[] = {          // 28

    0x80 | 25,
    3, 2,

    SP2( __XXXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXXXXXXX, HMT1 ), // 03
    SP2( XXXXXXXX, HMT1 ), // 04
    SP2( X_XXXX_X, HMT1 ), // 05
    SP2( X_XXXX_X, HMT1 ), // 06
    SP2( X_XXXX_X, HMT2 ), // 07
    SP2( XXXXXXXX, HMT2 ), // 08
    SP2( XXXXXXXX, HMT2 ), // 09
    SP2( _XXXXXX_, HMT3 ), // 10
    SP2( _XXXXXX_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( _X______, BDY1 ), // 13
    SP2( XX_X__X_, BDY0 ), // 14
    SP2( XX__X_XX, BDY1 ), // 15
    SP2( XX_X__XX, BDY2 ), // 16
    SP2( _XXXX__X, BDY2 ), // 17
    SP2( __XXXX__, BDY2 ), // 18
    SP2( __XXX___, BDY2 ), // 19
    SP2( ___X_X__, HMT1 ), // 20
    SP2( __X_XXX_, HMT2 ), // 21
    SP2( __X__XX_, HMT2 ), // 22
    SP2( _____XX_, HMT2 ), // 23
    SP2( _____X__, HMT0 ), // 24
};

const unsigned char shape_FRAME_WALKDOWN0[] = {        // 29

    0x80 | 26,
    3, 0,

    SP2( __XXXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXX__XXX, HMT1 ), // 03
    SP2( XX_X__XX, HMT1 ), // 04
    SP2( XXX___XX, HMT1 ), // 05
    SP2( X_X____X, HMT1 ), // 06
    SP2( X______X, HMT2 ), // 07
    SP2( X______X, HMT2 ), // 08
    SP2( X______X, HMT2 ), // 09
    SP2( _X____X_, HMT3 ), // 10
    SP2( _XX__XX_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( _X____X_, BDY1 ), // 13
    SP2( _XXXXXX_, BDY0 ), // 14
    SP2( XX_XX_XX, BDY2 ), // 15
    SP2( XX_XX_XX, BDY2 ), // 16
    SP2( XXXXXXXX, BDY2 ), // 17
    SP2( X_XXXX_X, BDY2 ), // 18
    SP2( X_X__X_X, BDY2 ), // 19
    SP2( X__XX__X, BDY2 ), // 20
    SP2( __XXXX__, BDY2 ), // 21
    SP2( ___XX___, BDY2 ), // 22
    SP2( __X__X__, HMT1 ), // 23
    SP2( __X__X__, HMT2 ), // 24
    SP2( __X__X__, HMT0 ), // 25
};

const unsigned char shape_FRAME_WALKDOWN1[] = {        // 30

    0x80 | 25,
    3, 3,

    SP2( __XXXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXX__XXX, HMT1 ), // 03
    SP2( XX_X__XX, HMT1 ), // 04
    SP2( XXX___XX, HMT1 ), // 05
    SP2( X_X____X, HMT1 ), // 06
    SP2( X______X, HMT2 ), // 07
    SP2( X______X, HMT2 ), // 08
    SP2( X______X, HMT2 ), // 09
    SP2( _X____X_, HMT3 ), // 10
    SP2( _XX__XX_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( ______X_, BDY1 ), // 13
    SP2( _XXXXXXX, BDY1 ), // 14
    SP2( XX_XX_XX, BDY0 ), // 15
    SP2( XX_X_X_X, BDY1 ), // 16
    SP2( X_XX_XXX, BDY2 ), // 17
    SP2( __XX_XX_, BDY2 ), // 18
    SP2( ___X_XX_, BDY2 ), // 19
    SP2( __X_X___, BDY2 ), // 20
    SP2( _XXX_X__, HMT1 ), // 21
    SP2( _XX__X__, HMT2 ), // 22
    SP2( _XX_____, HMT2 ), // 23
    SP2( __X_____, HMT0 ), // 24
};

const unsigned char shape_FRAME_WALKDOWN2[] = {        // 31

    0x80 | 26,
    3, 3,

    SP2( __XXXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXX__XXX, HMT1 ), // 03
    SP2( XX_X__XX, HMT1 ), // 04
    SP2( XXX___XX, HMT1 ), // 05
    SP2( X_X____X, HMT1 ), // 06
    SP2( X______X, HMT2 ), // 07
    SP2( X______X, HMT2 ), // 08
    SP2( X______X, HMT2 ), // 09
    SP2( _X____X_, HMT3 ), // 10
    SP2( _XX__XX_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( _X____X_, BDY1 ), // 13
    SP2( _XXXXXX_, BDY0 ), // 14
    SP2( XX_XX_XX, BDY1 ), // 15
    SP2( XX_XX_XX, BDY2 ), // 16
    SP2( XXXXXXXX, BDY2 ), // 17
    SP2( X_XXXX_X, BDY2 ), // 18
    SP2( X_X__X_X, BDY2 ), // 19
    SP2( X__XX__X, BDY2 ), // 20
    SP2( __XXXX__, BDY2 ), // 21
    SP2( ___XX___, BDY2 ), // 22
    SP2( __X__X__, HMT1 ), // 23
    SP2( __X__X__, HMT2 ), // 24
    SP2( __X__X__, HMT0 ), // 25
};

const unsigned char shape_FRAME_WALKDOWN3[] = {        // 32

    0x80 | 25,
    3, 3,

    SP2( __XXXX__, HMT0 ), // 00
    SP2( _XXXXXX_, HMT0 ), // 01
    SP2( _XXXXXX_, HMT0 ), // 02
    SP2( XXX__XXX, HMT1 ), // 03
    SP2( XX_X__XX, HMT1 ), // 04
    SP2( XXX___XX, HMT1 ), // 05
    SP2( X_X____X, HMT1 ), // 06
    SP2( X______X, HMT2 ), // 07
    SP2( X______X, HMT2 ), // 08
    SP2( X______X, HMT2 ), // 09
    SP2( _X____X_, HMT3 ), // 10
    SP2( _XX__XX_, HMT3 ), // 11
    SP2( __XXXX__, HMT3 ), // 12
    SP2( _X______, BDY1 ), // 13
    SP2( XXXXXXX_, BDY0 ), // 14
    SP2( XX_XX_XX, BDY1 ), // 15
    SP2( X_X_X_XX, BDY2 ), // 16
    SP2( XXX_XX_X, BDY2 ), // 17
    SP2( _XX_XX__, BDY2 ), // 18
    SP2( _XX_X___, BDY2 ), // 19
    SP2( ___X_X__, BDY2 ), // 20
    SP2( __X_XXX_, HMT1 ), // 21
    SP2( __X__XX_, HMT2 ), // 22
    SP2( _____XX_, HMT2 ), // 23
    SP2( _____X__, HMT0 ), // 24
};




const unsigned char *const spriteShape[] = {

    shape_FRAME_BLANK,                 // 00
    shape_FRAME_STAND,                 // 01
    0, //shape_FRAME_ARMS_IN_AIR,      // 02
    shape_FRAME_HUNCH,                 // 03
    shape_FRAME_PUSH,                  // 04
    shape_FRAME_PUSH2,                 // 05
    0, //shape_FRAME_IMPATIENT,        // 06
    0, //shape_FRAME_IMPATIENT2,       // 07
    0, //shape_FRAME_LOOK1,            // 08
    0, //shape_FRAME_LOOK2,            // 09
    0, //shape_FRAME_SHADES,           // 10
    0, //shape_FRAME_SHADES_ARM,       // 11
    0, //shape_FRAME_BLINK,            // 12
    shape_FRAME_WALK1,                 // 13
    shape_FRAME_WALK2,                 // 14
    shape_FRAME_WALK3,                 // 15
    shape_FRAME_WALK4,                 // 16
    0, //shape_FRAME_SNATCH_DOWN,      // 17
    shape_FRAME_SKELETON1,             // 18
    shape_FRAME_SKELETON2,             // 19
    shape_FRAME_SKELETON3,             // 20
    shape_FRAME_SKELETON4,             // 21
    shape_FRAME_SKELETON5,             // 22
    0, //shape_FRAME_ARMSCROSSED,      // 23
    0, //shape_FRAME_TALK,             // 24
    shape_FRAME_WALKUP0,               // 25
    shape_FRAME_WALKUP1,               // 26
    shape_FRAME_WALKUP2,               // 27
    shape_FRAME_WALKUP3,               // 28
    shape_FRAME_WALKDOWN0,             // 29
    shape_FRAME_WALKDOWN1,             // 30
    shape_FRAME_WALKDOWN2,             // 31
    shape_FRAME_WALKDOWN3,             // 32
};



void processAnimationCommand() {

    while (!playerAnimationCount)
        switch (*playerAnimation) {

        case ACTION_SFX:
            ADDAUDIO(*++playerAnimation);
            playerAnimation++;
            break;

        case ACTION_FLIP:
            rockfordFaceDirection = -rockfordFaceDirection;
            playerAnimation++;
            break;

        case ACTION_LOOP:
            if (rockfordDead)
                startPlayerAnimation(ID_Skeleton);

            // else if (exitMode)
            //     startPlayerAnimation(ID_Shades);

            else {
                if (playerAnimationLoop)
                    playerAnimation = playerAnimationLoop;
                else
                    playerAnimation++;
            }
            break;

        case ACTION_STOP:
            startPlayerAnimation(rockfordDead? ID_Skeleton : ID_Stand);
            break;

        case ACTION_POSITION: {
            frameAdjustX = *++playerAnimation;
            frameAdjustY = *++playerAnimation;
            playerAnimation++;
            break;
        }

        case ACTION_DOT: {

            int dotX = 2 + (*++playerAnimation) * rockfordFaceDirection;
            int dotY = *++playerAnimation;
            for (int i = 0; i < 4; i++)
                sphereDot(rockfordX, rockfordY, 2, -30, dotX, dotY);
            playerAnimation++;
            break;
        }

        case ACTION_SAY:
#if __ENABLE_ATARIVOX
            sayWord(*++playerAnimation);
#endif
            playerAnimation++;
            break;

        default:
            playerAnimationCount = *(playerAnimation + 1);
            break;
        }
}



const unsigned short reciprocal[] = {        

#if SPEED_BASE == 2
    0x10000/3,
#endif

#if SPEED_BASE == 3
    0x10000/4,
#endif

#if SPEED_BASE == 4
    0x10000/5,
#endif

#if SPEED_BASE == 5
    0x10000/6,
#endif

    0x10000/7,
    0x10000/8,
    0x10000/9,
    0x10000/10,
    0x10000/11,
    0x10000/12,
    0x10000/13,

#if SPEED_BASE == 6
    0x10000/11,
#endif
};



void updateAnimation() {

    if (autoMoveFrameCount)
        autoMoveFrameCount--;

    autoMoveX = ((autoMoveFrameCount * autoMoveDeltaX * (int)reciprocal[gameSpeed - SPEED_BASE]) >> 16);
    autoMoveY = ((autoMoveFrameCount * autoMoveDeltaY * (int)reciprocal[gameSpeed - SPEED_BASE]) >> 16);

    if (playerAnimationCount != 255) {

        if (!playerAnimationCount) {
            playerAnimation += 2;
            processAnimationCommand();
        }

        playerAnimationCount--;
    }
}



void startPlayerAnimation(enum AnimationIdent animID) {

    playerAnimationID = animID;
    
    playerAnimation =
    playerAnimationLoop = AnimationVector[animID];

    playerAnimationCount =
    autoMoveDeltaX = 
    autoMoveDeltaY =
    frameAdjustX =
    frameAdjustY = 0;

    processAnimationCommand();
}


//EOF