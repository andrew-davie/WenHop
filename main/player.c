#include "defines_from_dasm_for_c.h"
#include <stdbool.h>

#include "main.h"
#include "player.h"

#include "atarivox.h"
#include "bitpatterns.h"
#include "colour.h"
#include "mellon.h"
#include "sound.h"

int autoMoveX;
int autoMoveY;
int autoMoveDeltaX;
int autoMoveDeltaY;
int autoMoveFrameCount;

const signed char AnimationDefault[] = {

    FRAME_STAND,
    255,
};

const signed char AnimationStandUp[] = {

    FRAME_WALKUP0,
    20,
    FRAME_WALK3,
    6,
    FRAME_STAND,
    255,
};

const signed char AnimationStandLR[] = {
    //    FRAME_WALK3, ,
    FRAME_STAND,
    255,
};

const signed char AnimationPush[] = {

    ACTION_SFX,
    SFX_PICKAXE,
    ACTION_DOT,
    4,
    4,
    FRAME_PUSH,
    8,
    FRAME_PUSH2,
    5,
    FRAME_STAND,
    5,
    ACTION_LOOP,
};

const signed char AnimationMineUp[] = {

    ACTION_SFX,
    SFX_PICKAXE,
    ACTION_DOT,
    0,
    0,
    FRAME_MINE_UP_1,
    12,
    FRAME_MINE_UP_0,
    8,
    ACTION_LOOP,
};

const signed char AnimationMineDown[] = {

    //    FRAME_MINE_DOWN_0, 2,
    ACTION_SFX,
    SFX_PICKAXE,
    ACTION_DOT,
    1,
    12,
    FRAME_MINE_DOWN_1,
    8,
    FRAME_MINE_DOWN_0,
    5,
    FRAME_STAND,
    5,
    ACTION_LOOP,
};

const signed char AnimationLocked[] = {
    FRAME_HUNCH,
    12,
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
    FRAME_LOOK1,
    4,
    FRAME_LOOK2,
    4,
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
    // FRAME_HUNCH,100,
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

// const signed char AnimationStartup[] = {
//      FRAME_SKELETON5, 8,
//      FRAME_SKELETON2, 8,
//      FRAME_SKELETON3, 8,
//      FRAME_SKELETON, 15,

// #define DX 4

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
    FRAME_ARMSCROSSED,
    80,
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

// #if __ENABLE_DRIP

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

// #endif // ENABLE_DRIP

const signed char *const AnimationVector[] = {

    // see (player.h) AnimationIdent

    AnimationDefault,  // 00
    AnimationStandUp,  // 01
    AnimationStandLR,  // 02
    AnimationPush,     // 03
    AnimationTurn,     // 04
    AnimationDie,      // 05
    AnimationWalk,     // 06
    AnimationSkeleton, // 07
    AnimationLocked,   // 08
    AnimationWalkUp,   // 09
    AnimationWalkDown, // 10
    AnimationMineUp,   // 11
    AnimationMineDown, // 12
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

// #define HAIR 0
// #define SKIN 1
// #define TOP1 2
// #define TOP2 3
// #define BOOT 4
// #define PANT 5
// #define BELT 6
// #define SOLE 7
#define BONE 8

#define HMT0 9
#define HMT1 10
#define HMT2 11
#define HMT3 12

#define BDY0 13
#define BDY1 14
#define BDY2 15

const unsigned char redirect[] = {0, 1, 1, 2};
const unsigned char playerColour[] = {

    // NTSC  PAL  PAL_60 SECAM

    0x28, // 0 HAIR
    0x34, // 1 SKIN
    0x06, // 2 TOP1
    0x06, // 3 TOP 2
    0x44, // 4 BOOT
    0x44, // 5 PANT
    0x58, // 6 BELT
    0x08, // 5 SOLE
    0x08, // 8 BONE

    0x2C, // 9  HMT0
    0x28, // 10 HMT1
    0x26, // 11 HMT2
    0x22, // 12 HMT3

    0x4A, // 13  BDY0
    0x46, // 14 BDY1
    0x44, // 15 BDY2

};

#define SP(a, b, c, d) \
    a, b, (c << 4) + d

#define SP2(a, b) \
    a, (b << 4)

// #define PNT2 0x04

/* V6

* Area (0,0):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________

*Area (0,1):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_XXXX_X, ________
X_XXXX_X, ________
XXXXXXXX, ________
XXXXXXXX, ________
_XXXXXX_, ________
_X____X_, ________
__XXXX__, ________
__XXXX__, ________
_X____X_, ________
X_XXXX_X, ________
XXXXXXXX, ________
XX____XX, ________
X_XXXX_X, ________
X_XXXX_X, ________
X______X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________

*Area (1,1):
________, ________
________, ________
________, ________
___XXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
_XXXX_XX, ________
_XXXX_XX, ________
_XXXX_XX, ________
XXXXXXXX, ________
XXXXXXXX, ________
_____XXX, ________
_XXXX_X_, ________
_XXXXX__, ________
X____X__, ________
XXXXX___, ________
XXXXX_X_, ________
______X_, ________
_XXXX_X_, ________
_XXXXX__, ________
___X____, ________
__X_X___, ________
_XXX_X__, ________
_XX__X__, ________
_XX_____, ________
__X_____, ________
________, ________
________, ________

*Area (2,1):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_XXXX_X, ________
X_XXXX_X, ________
XXXXXXXX, ________
XXXXXXXX, ________
_XXXXXX_, ________
_X____X_, ________
__XXXX__, ________
__XXXX__, ________
_X____X_, ________
X_XXXX_X, ________
XXXXXXXX, ________
XX____XX, ________
X_XXXX_X, ________
X_XXXX_X, ________
X______X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________

*Area (3,1):
________, ________
________, ________
________, ________
__XXX___, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_XXXX_, ________
XX_XXXX_, ________
XX_XXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XXX_____, ________
_X_XXXX_, ________
__XXXXX_, ________
__X____X, ________
___XXXXX, ________
_X_XXXXX, ________
_X______, ________
_X_XXXX_, ________
__XXXXX_, ________
____X___, ________
___X_X__, ________
__X_XXX_, ________
__X__XX_, ________
_____XX_, ________
_____X__, ________
________, ________
________, ________

*Area (0,2):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXX_XX, ________
XXXX___X, ________
XX_X_X_X, ________
XX_X_X_X, ________
XX_X___X, ________
XXXX___X, ________
XXXX___X, ________
_XXXX_X_, ________
_XXXX_X_, ________
X_XXXX__, ________
XX______, ________
X_XX_X__, ________
X_XX_X__, ________
XXXX_X__, ________
X_XX____, ________
X_XX_X__, ________
X_XX_X__, ________
X_X_X___, ________
___XX___, ________
___XX___, ________
__XX____, ________
__XX____, ________
__XXX___, ________

*Area (1,2):
________, ________
________, ________
________, ________
___XXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXX_XX, ________
XXXXX__X, ________
XXX_X_XX, ________
XXX_X_XX, ________
XXX_X__X, ________
XXXXX__X, ________
XXXXX__X, ________
_XXXX_X_, ________
_XXXX_X_, ________
__X_XX__, ________
XX___XX_, ________
XX_XXXX_, ________
XX_XXXX_, ________
XXX_XX__, ________
X_XX____, ________
_X______, ________
_X_XXX_X, ________
XXXX_XXX, ________
XXX__XXX, ________
X_X___X_, ________
______X_, ________
________, ________
________, ________
________, ________

*Area (2,2):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXX_XX, ________
XXXX___X, ________
XX_X_X_X, ________
XX_X_X_X, ________
XX_X___X, ________
XXXX___X, ________
XXXX___X, ________
_XXXX_X_, ________
_XXXX_X_, ________
X_XXXX__, ________
XX______, ________
X_XX_X__, ________
X_XX_X__, ________
XXXX_X__, ________
X_XX____, ________
X_XX_X__, ________
X_XX_X__, ________
X_X_X___, ________
___XX___, ________
___XX___, ________
__XX____, ________
__XX____, ________
__XXX___, ________

*Area (3,2):
________, ________
________, ________
________, ________
___XXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXX__XX, ________
XXX__X_X, ________
X_X_X__X, ________
X_X_X__X, ________
X_X____X, ________
XXX____X, ________
XXX____X, ________
_XXX__X_, ________
_XXX__X_, ________
X_XXXX__, ________
XX_____X, ________
_XXX_X_X, ________
XXXX_X_X, ________
XXXX_X__, ________
_XX_____, ________
_____X__, ________
_X_X_X_X, ________
XXXXXXXX, ________
XXXX_XXX, ________
X_X___X_, ________
______X_, ________
________, ________
________, ________
________, ________

*Area (0,3):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________

*Area (1,3):
________, ________
________, ________
________, ________
__XXX___, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX___XXX, ________
X_X__XXX, ________
X_X___XX, ________
X_____XX, ________
X_____XX, ________
_X___XX_, ________
_X___XX_, ________
__XXXX__, ________
______X_, ________
_XXXXXXX, ________
XX_XX_XX, ________
XX_X_X_X, ________
X_XX_XXX, ________
__XX_XX_, ________
___X_XX_, ________
__X_X___, ________
_XXX_X__, ________
_XX__X__, ________
_XX_____, ________
__X_____, ________
________, ________
________, ________

*Area (2,3):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________

*Area (3,3):
________, ________
________, ________
________, ________
___XXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XXX___XX, ________
XXXX___X, ________
XX_X___X, ________
XX_____X, ________
XX_____X, ________
_XX___X_, ________
_XX___X_, ________
__XXXX__, ________
_X______, ________
XXXXXXX_, ________
XX_XX_XX, ________
X_X_X_XX, ________
XXX_XX_X, ________
_XX_XX__, ________
_XX_X___, ________
___X_X__, ________
__X_XXX_, ________
__X__XX_, ________
_____XX_, ________
_____X__, ________
________, ________
________, ________

*Area (0,4):
________, ________
________, ________
________, ________
________, ________
________, _XX_____
_______X, X_______
__XXXX_X, ________
_XXXXXX_, X_______
_XXXXXX_, X_______
XXXX__X_, X_______
XXX__X_X, _X______
X_X_X__X, _X______
X_X_X__X, _X______
X_X____X, _X______
XXX____X, ________
XXX____X, _X______
_XXX__X_, _X______
_XXX_X_X, ________
X_XXXXXX, ________
XX____XX, ________
X_XX_XX_, ________
X_XX_XX_, ________
_XXXX___, ________
_X_XX_X_, ________
_X_XX_X_, ________
_X__XX__, ________
____XX__, ________
____XX__, ________
___XX___, ________
___XXX__, ________

*Area (1,4):
________, ________
________, ________
________, ________
________, ________
________, ________
___XXXX_, ________
__XXXXXX, ___XX___
__XXXXXX, _____X__
_XXXXX_X, X_____X_
_XXXX___, X____XX_
_XX_X_X_, X____X_X
_XX_X_X_, X___X__X
_XX_X___, X___X__X
_XXXX___, X__X____
_XXXX___, X__X____
__XXXX_X, __X__X__
__XXXX_X, __X_____
_X_XXXX_, _______X
_XX____X, X______X
_X_XX_XX, X_______
_X_XX_XX, ________
_XXXX_X_, ________
_X_XXX__, _____X__
_X_XX_X_, _____X__
_X__XX__, ________
____XX__, ________
____XX__, ________
___XX___, ________
___XX___, ________
____XX__, ________

*Area (0,5):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
___X__XX, XX______
__X__XXX, XXX_____
_X___XXX, XXX_____
_XX_XXXX, XXXX____
X_X_XXXX, XXXX____
X__XXX_X, XXX_____
X__XXX_X, XXX_____
X___XX_X, XXX_____
____XXXX, XXXX____
____XXXX, XXXX____
____XXX_, ________
_____X_X, XXX_____
____X_XX, XXX_____
____X_X_, ___X____
____XX_X, XXXX____
_____X_X, XXXX____
_____X__, ________
_______X, XXX_____
_______X, XXX_____
______X_, _X______
_____XXX, XX______
_____X_X, XX______
_____X__, _X______
________, _X______
*Area (1,5):
________, XX______
______XX, X____X__
_____X_X, X____X__
________, X__X____
________, X_______
______XX, XX______
_____XXX, XXX____X
_____XXX, XXX____X
____XXXX, XXXX____
____XXXX, XXXX____
____X_XX, XX_X____
____X_XX, XX_X____
____X_XX, XX_X____
____XXXX, XXXX____
____XXXX, XXXX____
_____XXX, XXX_____
____XX__, __X_____
____XXXX, X_______
____XXXX, X_______
____X___, __X_____
____XXXX, X_______
_____XXX, X_X_____
________, __X_____
_____XXX, X_______
________, ________
______XX, XX______
_______X, X_______
______X_, _X______
______X_, _X______
______X_, _X______

*Area (0,6):
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XXX___XX, ________
XXXX___X, ________
XX_X___X, ________
XX_____X, ________
XX_____X, ________
_XX___X_, ________
_XX___X_, ________
__XXXX__, ________
______X_, ________
_XXXXXX_, ________
_XXX__XX, ________
_X_XX__X, ________
__X_XXXX, ________
___X_XX_, ________
__X____X, ___X____
_XXXXXXX, X__XX___
XX_XXX_X, X__XX___
_X______, _X_X____
________, _XX_____
________, __X_____
________, _X____X_
________, X_____X_
________, ________
*Area (1,6):
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
________, ________
_XXXXXX_, ________
_XX___X_, ________
__XX_XX_, ________
__XX_XX_, ________
___X_X__, ________
__X_X_X_, ________
_XXX_XXX, ________
XX_X_X_X, X_______
_X_____X, ________
____X___, ________
____X___, ________
X___X___, ________
____XX_X, ________
____XXX_, ________
___XX___, ________

Area (0,7):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
Area (1,7):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_X_, ________
XX_XX_X_, ________
XXXXXXX_, ________
X_XXX_X_, ________
X_X___X_, ________
X__XX_X_, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
Area (2,7):
________, ________
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
XXXXX_X_, ________
XX_XX_X_, ________
XX____X_, ________
X_X_XXX_, ________
X_X_XX__, ________
___X____, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
Area (3,7):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_X_, ________
XX_XX_X_, ________
XXXXXXX_, ________
X_XXX_X_, ________
X_X___X_, ________
X__XX_X_, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________

Area (0,8):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
Area (1,8):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XX_XX_XX, ________
X_XXXX_X, ________
__X__X__, ________
___XX___, ________
__XXXX__, ________
__X__X__, ________
__X__X__, ________
Area (2,8):
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
________, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
________, ________
________, ________
Area (3,8):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XX_XX_XX, ________
X_XXXX_X, ________
__X__X__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________

Area (0,9):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__XX_, ________
Area (1,9):
________, ________
________, ________
________, ________
________, ________
___XXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXX__XX, ________
XXX__X_X, ________
X_X_X__X, ________
X_X_X__X, ________
X_X____X, ________
XXX____X, ________
XXX____X, ________
_XXX__X_, ________
_XXX__X_, ________
__XXXX__, ________
_X____X_, ________
XXXXXXXX, ________
XX_XX_XX, ________
X_XXXX_X, ________
X_XXXX_X, ________
_X_XX_X_, ________
_X____X_, ________
___XX___, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__XX_, ________
__X__X__, ________
Area (2,9):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, ________
_X____X_, ________
XXXXXXXX, ________
XX_XX_XX, ________
X_XXXX_X, ________
X_XXXX_X, ________
_X_XX_X_, ________
_X____X_, ________
___XX___, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__XX_, ________
Area (3,9):
________, ________
________, ________
________, ________
________, ________
__XXX___, ________
_XXXXXX_, ________
_XXXXXX_, ________
XX__XXXX, ________
X__X_XXX, ________
X_X__X_X, ________
X_X__X_X, ________
X____X_X, ________
X____XXX, ________
X____XXX, ________
_X__XXX_, ________
_X__XXX_, ________
__XXXX__, ________
_X____X_, ________
XXXXXXXX, ________
XX_XX_XX, ________
X_XXXX_X, ________
X_XXXX_X, ________
_X_XX_X_, ________
_X____X_, ________
___XX___, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__XX_, ________
__X__X__, ________

Area (0,10):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, _______X
__XXXX__, ______XX
_X____X_, ______XX
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
Area (1,10):
________, ________
________, ________
________, ________
__XXXX__, _______X
_XXXXXX_, _______X
_XXXXXX_, _______X
XXX__XXX, _______X
XX_X__XX, _______X
XXX___XX, _______X
X_X____X, _______X
X______X, _______X
X______X, _______X
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, X_______
XX____XX, XX______
XXXXXXXX, XX______
XX_XX_XX, ________
_X_XX_X_, ________
_XXXXXX_, ________
__XXXX__, ________
__X__X__, ________
___XX___, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
________, ________
Area (2,10):
________, ________
X______X, ________
X_XXXX_X, ________
_XXXXXX_, X_______
_X____X_, X_______
XX_X__XX, X_______
X_X____X, X_______
X_X____X, X_______
X______X, X_______
X______X, X_______
XX____XX, X_______
X_XXXX_X, X_______
X_XXXX_X, ________
XX____XX, ________
XXXXXXXX, ________
XX_XX_X_, _______X
_X_XX_X_, ______XX
__XXXX__, ______XX
__XXXX__, ________
___XX___, ________
__X__X__, ________
_XXXXXX_, ________
_X_XX_X_, ________
_X____X_, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
Area (3,10):
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, X_______
XX____XX, XX______
XXXXXXXX, XX______
XX_XX_XX, ________
_X_XX_X_, ________
_XXXXXX_, ________
__XXXX__, ________
__X__X__, ________
___XX___, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
_X____X_, ________
_X____X_, ________
________, ________

Area (0,11):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XXX__XXX, ________
X_X__X_X, ________
_X_XX_X_, ________
_X_XX_X_, ________
_XX__XX_, ________
Area (1,11):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
__X__X__, ________
_X____X_, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XXX__XXX, ________
X_X__X_X, ________
_X_XX_X_, ________
_X_XX_X_, ________
_XX__XX_, ________
Area (2,11):
________, ________
________, ________
________, ________
________, ________
X______X, _______X
X______X, ________
_X____X_, ________
________, ________
X______X, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XXX__XXX, ________
X_X__X_X, ________
_X_XX_X_, ________
_X_XX_X_, ________
_XX__XX_, ________
Area (3,11):
________, ________
________, ________
________, ________
________, ________
________, X_______
________, ________
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
_X____X_, ________
_X____X_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XXX__XXX, ________
X_X__X_X, ________
_X_XX_X_, ________
_X_XX_X_, ________
_XX__XX_, ________

*Area (0,12):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, ________
_X____X_, ________
_XXXXXX_, ________
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
*Area (1,12):
________, ________
________, ________
________, ________
________, ________
__XXX___, ________
_XXXXXX_, ________
_XXXXXX_, ________
XX__XXXX, ________
X__X_XXX, ________
X_X__X_X, ________
X_X__X_X, ________
X____X_X, ________
X____XXX, ________
X____XXX, ________
_X__XXX_, ________
_X__XXX_, ________
__XXXX_X, ________
______XX, ________
__XXXX_X, ________
_X_X_XX_, ________
_X_X_XX_, ________
_XXX_XX_, ________
_XXX_XX_, ________
_X___XX_, ________
___X_X__, ________
___XX___, ________
_____X__, ________
___X_X__, ________
___X____, ________
___X____, ________
*Area (2,12):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XX_XXXXX, ________
X___XXXX, ________
X_X_X_XX, ________
X_X_X_XX, ________
X___X_XX, ________
X___XXXX, ________
X___XXXX, ________
_X_XXXX_, ________
_X_XXXX_, ________
__XXXX_X, ________
______XX, ________
__X_XX_X, ________
__X_XX_X, ________
__X_XXXX, ________
____XX_X, ________
__X_XX_X, ________
__X_XX_X, ________
___X_X_X, ________
___XX___, ________
___XX___, ________
____XX__, ________
____XX__, ________
___XXX__, ________
*Area (3,12):
________, ________
________, ________
________, ________
________, ________
__XXX___, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
XX_XXXX_, ________
XX_XXXX_, ________
XX_XXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
_XXXXXX_, ________
_XXX____, ________
__X_XXX_, ________
____XXX_, ________
__X_X___, ________
__X_XXX_, ________
_XX_XXX_, ________
_XX_X___, ________
_XX_XXX_, ________
_X__XXX_, ________
__X_X___, ________
___XXX__, ________
__X_____, ________
__X_X___, ________
____X___, ________
____X___, ________
*Area (4,12):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_XXXX_X, ________
X_XXXX_X, ________
XXXXXXXX, ________
XXXXXXXX, ________
_XXXXXX_, ________
_X____X_, ________
__XXXX__, ________
__XXXX__, ________
_X____X_, ________
X_XXXX_X, ________
XXXXXXXX, ________
XX____XX, ________
X_XXXX_X, ________
X_XXXX_X, ________
X______X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
*Area (5,12):
________, ________
________, ________
________, ________
________, ________
___XXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXXXXX, ________
XXXXXXXX, ________
_XXXX_XX, ________
_XXXX_XX, ________
_XXXX_XX, ________
XXXXXXXX, ________
XXXXXXXX, ________
_XXXXXX_, ________
____XXX_, ________
_XXX_X__, ________
_XXX____, ________
___X_X__, ________
_XXX_X__, ________
_XXX_XX_, ________
___X_XX_, ________
_XXX_XX_, ________
_XXX__X_, ________
___X_X__, ________
__XXX___, ________
_____X__, ________
___X_X__, ________
___X____, ________
___X____, ________
*Area (6,12):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXXXX_XX, ________
XXXX___X, ________
XX_X_X_X, ________
XX_X_X_X, ________
XX_X___X, ________
XXXX___X, ________
XXXX___X, ________
_XXXX_X_, ________
_XXXX_X_, ________
X_XXXX__, ________
XX______, ________
X_XX_X__, ________
X_XX_X__, ________
XXXX_X__, ________
X_XX____, ________
X_XX_X__, ________
X_XX_X__, ________
X_X_X___, ________
___XX___, ________
___XX___, ________
__XX____, ________
__XX____, ________
__XXX___, ________
Area (0,13):
________, ________
________, ________
________, ________
________, ________
__XXXX__, ________
_XXXXXX_, ________
_XXXXXX_, ________
XXX__XXX, ________
XX_X__XX, ________
XXX___XX, ________
X_X____X, ________
X______X, ________
X______X, ________
X______X, ________
_X____X_, ________
_XX__XX_, ________
__XXXX__, _______X
_X____X_, ______XX
_XXXXXX_, ______XX
XX_XX_XX, ________
XX_XX_XX, ________
XXXXXXXX, ________
X_XXXX_X, ________
X_X__X_X, ________
X__XX__X, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
Area (1,13):
________, ________
________, ________
________, ________
________, ________
__XXXX__, _______X
_XXXXXX_, ________
_XX__XX_, ________
XX_X__XX, _______X
XXX___XX, _______X
X_X____X, ______XX
X______X, _______X
X______X, _______X
X______X, _______X
XX____XX, _______X
_XX__XX_, _______X
_XXXXXX_, _______X
__XXXX__, X_______
XX____XX, XX______
XXXXXXXX, XX______
XX_XX_XX, ________
_X_XX_X_, ________
_XXXXXX_, ________
__XXXX__, ________
__X__X__, ________
___XX___, ________
__XXXX__, ________
___XX___, ________
__X__X__, ________
__X__X__, ________
__X__X__, ________
Area (2,13):
________, ________
________, ________
________, ________
________, ________
________, X_______
XX____XX, ________
X______X, ________
__XXXX__, X______X
_X____X_, X___X___
_X_X__X_, XX__X___
X_X____X, X____X__
X_X____X, X______X
X______X, X______X
X______X, X____X_X
XX____XX, X______X
XXXXXXXX, X______X
X_XXXX_X, _______X
X_XXXX_X, _______X
XX____XX, _______X
XXXXXXX_, _______X
_X_XX_X_, ________
_X_XX_X_, ________
__XXXX__, ________
__XXXX__, ________
__X__X__, ________
_X_XX_X_, ________
_XXXXXX_, ________
_X_XX_X_, ________
_X____X_, ________
_X____X_, ________
Area (3,13):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, X_______
XX____XX, ___X____
X______X, ___X____
X______X, __X_____
__XXXX__, X_______
_XXXXXX_, X_______
_X____X_, X_X_____
XX_X__XX, X___X__X
X_X____X, X______X
X_X____X, X______X
X______X, X_____XX
X______X, X_____X_
X______X, X_____X_
XX____XX, ______X_
X_XXXX_X, ______XX
XX____XX, _______X
_XXXXXX_, _______X
_X_XX_X_, ________
__XXXX__, ________
_X_XX_X_, ________
X_X__X_X, _______X
X__XX__X, _______X
_X____X_, ________
Area (4,13):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, X__X____
X______X, X_______
__XXXX__, X_______
_XXXXXX_, XX_____X
_X____X_, _X___X_X
XXX___XX, _X_____X
X__X___X, _X____XX
X___X__X, XX____X_
X__X_X_X, X_____X_
X______X, X_____X_
X______X, _______X
XX____XX, _______X
XXXXXXXX, _______X
_X____X_, X____X_X
__XXXX__, X____X__
X______X, ______X_
Area (5,13):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, X_______
X______X, X_X_____
__XXXX__, X_______
_XXXXXX_, XX______
_X____X_, _X______
X__X_X_X, _X______
X___X__X, _X______
___X_X__, X_______
__X___X_, X_______
__X_____, X_______
X______X, X_X_____
XXXXXXXX, __X_____
_XXXXXX_, _X______
Area (6,13):
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
________, ________
__X__X__, ________
___XX___, ________
_X_XX_X_, _______X
_X_XX_X_, _______X
___XX___, ________
__X__X__, ________
________, ________
________, ________


*/

const unsigned char shape_FRAME_BLANK[] = {
    // 00

    0,
    0, 0,

    SP2(________, ____), // 00
    SP2(________, ____), // 01
    SP2(________, ____), // 02
    SP2(________, ____), // 03
    SP2(________, ____), // 04
    SP2(________, ____), // 05
    SP2(________, ____), // 06
    SP2(________, ____), // 07
    SP2(________, ____), // 08
    SP2(________, ____), // 09
    SP2(________, ____), // 10
    SP2(________, ____), // 11
    SP2(________, ____), // 12
    SP2(________, ____), // 13
    SP2(________, ____), // 14
    SP2(________, ____), // 15
    SP2(________, ____), // 16
    SP2(________, ____), // 17
    SP2(________, ____), // 18
    SP2(________, ____), // 19
    SP2(________, ____), // 20
    SP2(________, ____), // 21
    SP2(________, ____), // 22
    SP2(________, ____), // 23
    SP2(________, ____), // 24
    SP2(________, ____), // 25
    SP2(________, ____), // 26
    SP2(________, ____), // 27
    SP2(________, ____), // 28
    SP2(________, ____), // 29
};

const unsigned char shape_FRAME_STAND[] = {

    26,
    4 + 0, 0,

    SP2(__XXXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXX__XXX, HMT1), // 03
    SP2(XX_X__XX, HMT1), // 04
    SP2(XXX___XX, HMT1), // 05
    SP2(X_X____X, HMT1), // 06
    SP2(X______X, HMT2), // 07
    SP2(X______X, HMT2), // 08
    SP2(X______X, HMT2), // 09
    SP2(_X____X_, HMT3), // 10
    SP2(_XX__XX_, HMT3), // 11
    SP2(__XXXX__, HMT3), // 12
    SP2(_X____X_, BDY1), // 13
    SP2(_XXXXXX_, BDY0), // 14
    SP2(XX_XX_XX, BDY1), // 15
    SP2(XX_XX_XX, BDY1), // 16
    SP2(XXXXXXXX, BDY2), // 17
    SP2(X_XXXX_X, BDY2), // 18
    SP2(X_X__X_X, BDY2), // 19
    SP2(X__XX__X, HMT1), // 20
    SP2(__XXXX__, HMT1), // 21
    SP2(___XX___, HMT1), // 22
    SP2(__X__X__, HMT1), // 23
    SP2(__X__X__, HMT2), // 24
    SP2(__X__X__, HMT0), // 25

};

const unsigned char shape_FRAME_ARMS_IN_AIR[] = {
    // 02

    SPRITE_DOUBLE | 24,
    2, 5,

    SP(__X_____, _X______, HMT0, BONE), // 00
    SP(__X_XXXX, _X______, HMT0, BONE), // 01
    SP(_X_XXXXX, X_X_____, HMT0, BONE), // 02
    SP(_X_X____, X_X_____, HMT1, BONE), // 03
    SP(_XXX_X__, XXX_____, HMT1, BONE), // 04
    SP(_XX_X___, _XX_____, HMT1, BONE), // 05
    SP(_XX_X___, _XX_____, HMT1, BONE), // 06
    SP(_XX_____, _XX_____, HMT2, BONE), // 07
    SP(_XX_____, _XX_____, HMT2, BONE), // 08
    SP(_XXX____, XXX_____, HMT2, BONE), // 09
    SP(_XX_XXXX, _XX_____, HMT3, BONE), // 10
    SP(__X_XXXX, _X______, HMT3, BONE), // 11
    SP(__XX____, XX______, HMT3, BONE), // 12
    SP(__XXXXXX, XX______, BDY1, BONE), // 13
    SP(__XX_XX_, X_______, BDY0, BONE), // 14
    SP(___X_XX_, X_______, BDY1, BONE), // 15
    SP(____XXXX, ________, BDY2, BONE), // 16
    SP(____XXXX, ________, BDY2, BONE), // 17
    SP(_____XX_, ________, BDY2, BONE), // 18
    SP(____X__X, ________, BDY2, BONE), // 19
    SP(___XXXXX, X_______, HMT1, BONE), // 20
    SP(___X_XX_, X_______, HMT1, BONE), // 21
    SP(__XX____, XX______, HMT2, BONE), // 22
    SP(__X_____, _X______, HMT0, BONE), // 23
};

const unsigned char shape_FRAME_HUNCH[] = {
    // 03

    26,
    4 + 0, 0,

    SP2(___XXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXX__XX, HMT1), // 03
    SP2(XXX__X_X, HMT1), // 04
    SP2(X_X_X__X, HMT1), // 05
    SP2(X_X_X__X, HMT1), // 06
    SP2(X_X____X, HMT2), // 07
    SP2(XXX____X, HMT2), // 08
    SP2(XXX____X, HMT2), // 09
    SP2(_XXX__X_, HMT3), // 10
    SP2(_XXX__X_, HMT3), // 11
    SP2(__XXXX__, HMT3), // 12
    SP2(_X____X_, BDY1), // 13
    SP2(XXXXXXXX, BDY0), // 14
    SP2(XX_XX_XX, BDY1), // 15
    SP2(X_XXXX_X, BDY2), // 16
    SP2(X_XXXX_X, BDY2), // 17
    SP2(_X_XX_X_, BDY2), // 18
    SP2(_X____X_, BDY2), // 19
    SP2(___XX___, HMT1), // 20
    SP2(__XXXX__, HMT2), // 21
    SP2(___XX___, HMT2), // 22
    SP2(__X__X__, HMT2), // 23
    SP2(__X__XX_, HMT2), // 24
    SP2(__X__X__, HMT0), // 25

};

const unsigned char shape_FRAME_PUSH[] = {
    // 04

    SPRITE_DOUBLE | 25,
    4, 0,

    SP(___XXXX_, ________, HMT0, BONE), // 00
    SP(__XXXXXX, ___XX___, HMT0, BONE), // 01
    SP(__XXXXXX, _____X__, HMT0, BONE), // 02
    SP(_XXXXX_X, X_____X_, HMT1, BONE), // 03
    SP(_XXXX___, X____XX_, HMT1, BONE), // 04
    SP(_XX_X_X_, X____X_X, HMT1, BONE), // 05
    SP(_XX_X_X_, X___X__X, HMT1, BONE), // 06
    SP(_XX_X___, X___X__X, HMT2, BONE), // 07
    SP(_XXXX___, X__X____, HMT2, BONE), // 08
    SP(_XXXX___, X__X____, HMT2, BONE), // 09
    SP(__XXXX_X, __X_____, HMT3, BONE), // 10
    SP(__XXXX_X, __X_____, HMT3, BONE), // 11
    SP(_X_XXXX_, ________, HMT3, BONE), // 12
    SP(_XX____X, X_______, BDY1, BONE), // 13
    SP(_X_XX_XX, X_______, BDY0, BONE), // 14
    SP(_X_XX_XX, ________, BDY1, BONE), // 15
    SP(_XXXX_X_, ________, BDY2, BONE), // 16
    SP(_X_XXX__, ________, BDY2, BONE), // 17
    SP(_X_XX_X_, ________, BDY2, BONE), // 18
    SP(_X__XX__, ________, HMT1, BONE), // 19
    SP(____XX__, ________, HMT2, BONE), // 20
    SP(____XX__, ________, HMT2, BONE), // 21
    SP(___XX___, ________, HMT2, BONE), // 22
    SP(___XX___, ________, HMT2, BONE), // 23
    SP(____XX__, ________, HMT0, BONE), // 24
};

const unsigned char shape_FRAME_PUSH2[] = {
    // 05

    SPRITE_DOUBLE | 26,
    4, 0,

    SP(________, _XX_____, BONE, BONE), // 00
    SP(_______X, X_______, BONE, BONE), // 01
    SP(__XXXX_X, ________, HMT0, BONE), // 02
    SP(_XXXXXX_, X_______, HMT0, BONE), // 03
    SP(_XXXXXX_, X_______, HMT0, BONE), // 04
    SP(XXXX__X_, X_______, HMT1, BONE), // 05
    SP(XXX__X_X, _X______, HMT1, BONE), // 06
    SP(X_X_X__X, _X______, HMT1, BONE), // 07
    SP(X_X_X__X, _X______, HMT1, BONE), // 08
    SP(X_X____X, _X______, HMT2, BONE), // 09
    SP(XXX____X, ________, HMT2, BONE), // 10
    SP(XXX____X, _X______, HMT2, BONE), // 11
    SP(_XXX__X_, _X______, HMT3, BONE), // 12
    SP(_XXX_X_X, ________, HMT3, BONE), // 13
    SP(X_XXXXXX, ________, HMT3, BONE), // 14
    SP(XX____XX, ________, BDY1, BONE), // 15
    SP(X_XX_XX_, ________, BDY0, BONE), // 16
    SP(X_XX_XX_, ________, BDY1, BONE), // 17
    SP(_XXXX___, ________, BDY2, BONE), // 18
    SP(_X_XX_X_, ________, BDY2, BONE), // 19
    SP(_X_XX_X_, ________, HMT1, BONE), // 20
    SP(_X__XX__, ________, HMT2, BONE), // 21
    SP(____XX__, ________, HMT2, BONE), // 22
    SP(____XX__, ________, HMT2, BONE), // 23
    SP(___XX___, ________, HMT2, BONE), // 24
    SP(___XXX__, ________, HMT0, BONE), // 25
};

const unsigned char shape_FRAME_IMPATIENT[] = {
    // 06
};

const unsigned char shape_FRAME_IMPATIENT2[] = {
    // 07
};

const unsigned char shape_FRAME_LOOK1[] = {
    // 08
};

const unsigned char shape_FRAME_LOOK2[] = {
    // 09
};

const unsigned char shape_FRAME_SHADES[] = {
    // 10
};

const unsigned char shape_FRAME_SHADES_ARM[] = {
    // 11
};

const unsigned char shape_FRAME_BLINK[] = {
    // 12
};

const unsigned char shape_FRAME_WALK1[] = {
    // 13

    26,
    5, 0,

    SP2(__XXXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXX_XX, HMT1), // 03
    SP2(XXXX___X, HMT1), // 04
    SP2(XX_X_X_X, HMT1), // 05
    SP2(XX_X_X_X, HMT1), // 06
    SP2(XX_X___X, HMT2), // 07
    SP2(XXXX___X, HMT2), // 08
    SP2(XXXX___X, HMT2), // 09
    SP2(_XXXX_X_, HMT3), // 10
    SP2(_XXXX_X_, HMT3), // 11
    SP2(X_XXXX__, HMT3), // 12
    SP2(XX______, BDY0), // 13
    SP2(X_XX_X__, BDY1), // 14
    SP2(X_XX_X__, BDY2), // 15
    SP2(XXXX_X__, BDY2), // 16
    SP2(X_XX____, BDY2), // 17
    SP2(X_XX_X__, BDY2), // 18
    SP2(X_XX_X__, HMT2), // 19
    SP2(X_X_X___, HMT2), // 20
    SP2(___XX___, HMT2), // 21
    SP2(___XX___, HMT2), // 22
    SP2(__XX____, HMT2), // 23
    SP2(__XX____, HMT2), // 24
    SP2(__XXX___, HMT0), // 25
};

const unsigned char shape_FRAME_WALK2[] = {
    // 14

    24,
    3, 3,

    SP2(___XXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXX_XX, HMT1), // 03
    SP2(XXXXX__X, HMT1), // 04
    SP2(XXX_X_XX, HMT1), // 05
    SP2(XXX_X_XX, HMT1), // 06
    SP2(XXX_X__X, HMT2), // 07
    SP2(XXXXX__X, HMT2), // 08
    SP2(XXXXX__X, HMT2), // 09
    SP2(_XXXX_X_, HMT3), // 10
    SP2(_XXXX_X_, HMT3), // 11
    SP2(__X_XX__, HMT3), // 12
    SP2(XX___XX_, BDY1), // 13
    SP2(XX_XXXX_, BDY0), // 14
    SP2(XX_XXXX_, BDY1), // 15
    SP2(XXX_XX__, BDY2), // 16
    SP2(X_XX____, BDY2), // 17
    SP2(_X______, BDY2), // 18
    SP2(_X_XXX_X, HMT1), // 19
    SP2(XXXX_XXX, HMT2), // 20
    SP2(XXX__XXX, HMT2), // 21
    SP2(X_X___X_, HMT2), // 22
    SP2(______X_, HMT0), // 23
};

const unsigned char shape_FRAME_WALK3[] = {
    // 15

    26,
    4, 0,

    SP2(__XXXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXX_XX, HMT1), // 03
    SP2(XXXX___X, HMT1), // 04
    SP2(XX_X_X_X, HMT1), // 05
    SP2(XX_X_X_X, HMT1), // 06
    SP2(XX_X___X, HMT2), // 07
    SP2(XXXX___X, HMT2), // 08
    SP2(XXXX___X, HMT2), // 09
    SP2(_XXXX_X_, HMT3), // 10
    SP2(_XXXX_X_, HMT3), // 11
    SP2(X_XXXX__, HMT3), // 12
    SP2(XX______, BDY1), // 13
    SP2(X_XX_X__, BDY0), // 14
    SP2(X_XX_X__, BDY1), // 15
    SP2(XXXX_X__, BDY2), // 16
    SP2(X_XX____, BDY2), // 17
    SP2(X_XX_X__, BDY2), // 18
    SP2(X_XX_X__, BDY2), // 19
    SP2(X_X_X___, HMT1), // 20
    SP2(___XX___, HMT2), // 21
    SP2(___XX___, HMT2), // 22
    SP2(__XX____, HMT2), // 23
    SP2(__XX____, HMT2), // 24
    SP2(__XXX___, HMT0), // 25
};

const unsigned char shape_FRAME_WALK4[] = {
    // 16

    24,
    3, 3,

    SP2(___XXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXX__XX, HMT1), // 03
    SP2(XXX__X_X, HMT1), // 04
    SP2(X_X_X__X, HMT1), // 05
    SP2(X_X_X__X, HMT1), // 06
    SP2(X_X____X, HMT2), // 07
    SP2(XXX____X, HMT2), // 08
    SP2(XXX____X, HMT2), // 09
    SP2(_XXX__X_, HMT3), // 10
    SP2(_XXX__X_, HMT3), // 11
    SP2(X_XXXX__, HMT3), // 12
    SP2(XX_____X, BDY1), // 13
    SP2(_XXX_X_X, BDY0), // 14
    SP2(XXXX_X_X, BDY1), // 15
    SP2(XXXX_X__, BDY2), // 16
    SP2(_XX_____, BDY2), // 17
    SP2(_____X__, HMT1), // 18
    SP2(_X_X_X_X, HMT2), // 19
    SP2(XXXXXXXX, HMT2), // 20
    SP2(XXXX_XXX, HMT2), // 21
    SP2(X_X___X_, HMT2), // 22
    SP2(______X_, HMT0), // 23

};

const unsigned char shape_FRAME_SNATCH_DOWN[] = {
    // 17
};

const unsigned char shape_FRAME_SKELETON1[] = {
    // 18

    SPRITE_DOUBLE | SPRITE_ABSCOLOUR | 20,
    0, 0,

    SP(_____XXX, X_______, BONE, BONE), // 00
    SP(____XXXX, XX______, BONE, BONE), // 01
    SP(____X__X, __X_____, BONE, BONE), // 02
    SP(____X__X, __X_____, BONE, BONE), // 03
    SP(____XXXX, XX______, BONE, BONE), // 04
    SP(_____X_X, _X______, BONE, BONE), // 05
    SP(______X_, X_______, BONE, BONE), // 06
    SP(_______X, ________, BONE, BONE), // 07
    SP(____XXXX, XX______, BONE, BONE), // 08
    SP(___X___X, __X_____, BONE, BONE), // 09
    SP(__XX_XXX, X_XX____, BONE, BONE), // 10
    SP(__X____X, ___X____, BONE, BONE), // 11
    SP(_____XXX, XX______, BONE, BONE), // 12
    SP(__XX__XX, X_XX____, BONE, BONE), // 13
    SP(_X___X_X, _X__X___, BONE, BONE), // 14
    SP(_____X__, _X______, BONE, BONE), // 15
    SP(____XX__, _XX_____, BONE, BONE), // 16
    SP(_____X__, _X______, BONE, BONE), // 17
    SP(________, ________, BONE, BONE), // 18
    SP(____XXX_, XXX_____, BONE, BONE), // 19
};

const unsigned char shape_FRAME_SKELETON2[] = {
    // 21

    SPRITE_DOUBLE | SPRITE_ABSCOLOUR | 20,
    1, 0,

    SP(____XXXX, ________, BONE, BONE), // 00
    SP(___XXXXX, X_______, BONE, BONE), // 01
    SP(__X__X__, X_______, BONE, BONE), // 02
    SP(__X__X__, X_______, BONE, BONE), // 03
    SP(__XXXXXX, X_______, BONE, BONE), // 04
    SP(___X_X_X, ________, BONE, BONE), // 05
    SP(____X_X_, ________, BONE, BONE), // 06
    SP(_______X, ________, BONE, BONE), // 07
    SP(___XXXXX, X_______, BONE, BONE), // 08
    SP(__X___X_, _X______, BONE, BONE), // 09
    SP(_XX_XXXX, _XX_____, BONE, BONE), // 10
    SP(_X____X_, __X_____, BONE, BONE), // 11
    SP(____XXXX, X_______, BONE, BONE), // 12
    SP(_XX__XXX, _XX_____, BONE, BONE), // 13
    SP(X___X_X_, X__X____, BONE, BONE), // 14
    SP(____X___, X_______, BONE, BONE), // 15
    SP(___XX___, XX______, BONE, BONE), // 16
    SP(____X___, X_______, BONE, BONE), // 17
    SP(________, ________, BONE, BONE), // 18
    SP(___XXX_X, XX______, BONE, BONE), // 19

};

const unsigned char shape_FRAME_SKELETON3[] = {
    // 20

    SPRITE_DOUBLE | SPRITE_ABSCOLOUR | 16,
    0, 0,

    SP(_______X, XXX_____, BONE, BONE), // 00
    SP(______XX, XXXX____, BONE, BONE), // 01
    SP(______X_, _X__X___, BONE, BONE), // 02
    SP(______X_, _X__X___, BONE, BONE), // 03
    SP(______XX, XXXX____, BONE, BONE), // 04
    SP(_______X, _X_X____, BONE, BONE), // 05
    SP(________, X_X_____, BONE, BONE), // 06
    SP(__X_XXX_, XXX_____, BONE, BONE), // 07
    SP(_X____X_, ________, BONE, BONE), // 08
    SP(_X__XXXX, ___X____, BONE, BONE), // 09
    SP(______XX, __XX____, BONE, BONE), // 10
    SP(_X__X_X_, X_______, BONE, BONE), // 11
    SP(_X__X___, X___XX__, BONE, BONE), // 12
    SP(_X__X___, X___X___, BONE, BONE), // 13
    SP(X_______, ________, BONE, BONE), // 14
    SP(___XXX_X, XX______, BONE, BONE), // 15
};

const unsigned char shape_FRAME_SKELETON4[] = {
    // 19

    SPRITE_DOUBLE | SPRITE_ABSCOLOUR | 12,
    -1, 0,

    SP(________, XXXX____, BONE, BONE), // 00
    SP(_______X, XXXXX___, BONE, BONE), // 01
    SP(_______X, __X__X__, BONE, BONE), // 02
    SP(_______X, __X__X__, BONE, BONE), // 03
    SP(_______X, XXXXX___, BONE, BONE), // 04
    SP(________, X_X_X___, BONE, BONE), // 05
    SP(________, _X_X____, BONE, BONE), // 06
    SP(_____X__, XXXX____, BONE, BONE), // 07
    SP(___X___X, ________, BONE, BONE), // 08
    SP(_______X, XX______, BONE, BONE), // 09
    SP(___X__X_, ______X_, BONE, BONE), // 10
    SP(__XX__XX, X_XXX__X, BONE, BONE), // 11
};

const unsigned char shape_FRAME_SKELETON5[] = {
    // 22

    3,
    6, 0,

    SP2(_XXXXXX_, BONE), // 00
    SP2(X__X__XX, BONE), // 01
    SP2(XX_XX__X, BONE), // 02
};

const unsigned char shape_FRAME_ARMSCROSSED[] = {
    // 23
};

const unsigned char shape_FRAME_TALK[] = {
    // 24
};

const unsigned char shape_FRAME_WALKUP0[] = {
    // 25

    26,
    3, 0,

    SP2(__XXXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXXXXX, HMT1), // 03
    SP2(XXXXXXXX, HMT1), // 04
    SP2(X_XXXX_X, HMT1), // 05
    SP2(X_XXXX_X, HMT1), // 06
    SP2(X_XXXX_X, HMT2), // 07
    SP2(XXXXXXXX, HMT2), // 08
    SP2(XXXXXXXX, HMT2), // 09
    SP2(_XXXXXX_, HMT3), // 10
    SP2(_X____X_, HMT3), // 11
    SP2(__XXXX__, HMT3), // 12
    SP2(__XXXX__, BDY1), // 13
    SP2(_X____X_, BDY0), // 14
    SP2(X_XXXX_X, BDY1), // 15
    SP2(XXXXXXXX, BDY2), // 16
    SP2(XX____XX, BDY2), // 17
    SP2(X_XXXX_X, BDY2), // 18
    SP2(X_XXXX_X, BDY2), // 19
    SP2(X______X, BDY2), // 20
    SP2(__XXXX__, HMT1), // 21
    SP2(___XX___, HMT2), // 22
    SP2(__X__X__, HMT2), // 23
    SP2(__X__X__, HMT2), // 24
    SP2(__X__X__, HMT0), // 25
};

const unsigned char shape_FRAME_WALKUP1[] = {
    // 26

    25,
    3, 2,

    SP2(___XXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXXXXX, HMT1), // 03
    SP2(XXXXXXXX, HMT1), // 04
    SP2(_XXXX_XX, HMT1), // 05
    SP2(_XXXX_XX, HMT1), // 06
    SP2(_XXXX_XX, HMT2), // 07
    SP2(XXXXXXXX, HMT2), // 08
    SP2(XXXXXXXX, HMT2), // 09
    SP2(_____XXX, HMT3), // 10
    SP2(_XXXX_X_, HMT3), // 11
    SP2(_XXXXX__, HMT3), // 12
    SP2(X____X__, BDY1), // 13
    SP2(XXXXX___, BDY0), // 14
    SP2(XXXXX_X_, BDY1), // 15
    SP2(______X_, BDY2), // 16
    SP2(_XXXX_X_, BDY2), // 17
    SP2(_XXXXX__, BDY2), // 18
    SP2(___X____, BDY2), // 19
    SP2(__X_X___, HMT1), // 20
    SP2(_XXX_X__, HMT2), // 21
    SP2(_XX__X__, HMT2), // 22
    SP2(_XX_____, HMT2), // 23
    SP2(__X_____, HMT0), // 24
};

const unsigned char shape_FRAME_WALKUP2[] = {
    // 27

    26,
    3, 0,

    SP2(__XXXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXXXXX, HMT1), // 03
    SP2(XXXXXXXX, HMT1), // 04
    SP2(X_XXXX_X, HMT1), // 05
    SP2(X_XXXX_X, HMT1), // 06
    SP2(X_XXXX_X, HMT2), // 07
    SP2(XXXXXXXX, HMT2), // 08
    SP2(XXXXXXXX, HMT2), // 09
    SP2(_XXXXXX_, HMT3), // 10
    SP2(_X____X_, HMT3), // 11
    SP2(__XXXX__, HMT3), // 12
    SP2(__XXXX__, BDY1), // 13
    SP2(_X____X_, BDY0), // 14
    SP2(X_XXXX_X, BDY1), // 15
    SP2(XXXXXXXX, BDY2), // 16
    SP2(XX____XX, BDY2), // 17
    SP2(X_XXXX_X, BDY2), // 18
    SP2(X_XXXX_X, BDY2), // 19
    SP2(X______X, BDY2), // 20
    SP2(__XXXX__, HMT1), // 21
    SP2(___XX___, HMT2), // 22
    SP2(__X__X__, HMT2), // 23
    SP2(__X__X__, HMT2), // 24
    SP2(__X__X__, HMT0), // 25
};

const unsigned char shape_FRAME_WALKUP3[] = {
    // 28

    25,
    3, 2,

    SP2(__XXX___, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXXXXX, HMT1), // 03
    SP2(XXXXXXXX, HMT1), // 04
    SP2(XX_XXXX_, HMT1), // 05
    SP2(XX_XXXX_, HMT1), // 06
    SP2(XX_XXXX_, HMT2), // 07
    SP2(XXXXXXXX, HMT2), // 08
    SP2(XXXXXXXX, HMT2), // 09
    SP2(XXX_____, HMT3), // 10
    SP2(_X_XXXX_, HMT3), // 11
    SP2(__XXXXX_, HMT3), // 12
    SP2(__X____X, BDY1), // 13
    SP2(___XXXXX, BDY0), // 14
    SP2(_X_XXXXX, BDY1), // 15
    SP2(_X______, BDY2), // 16
    SP2(_X_XXXX_, BDY2), // 17
    SP2(__XXXXX_, BDY2), // 18
    SP2(____X___, BDY2), // 19
    SP2(___X_X__, HMT1), // 20
    SP2(__X_XXX_, HMT2), // 21
    SP2(__X__XX_, HMT2), // 22
    SP2(_____XX_, HMT2), // 23
    SP2(_____X__, HMT0), // 24
};

const unsigned char shape_FRAME_WALKDOWN0[] = {
    // 29

    26,
    3, 0,

    SP2(__XXXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXXXXX, HMT1), // 03
    SP2(XXXXXXXX, HMT1), // 04
    SP2(XX_X__XX, HMT1), // 05
    SP2(XXX___XX, HMT1), // 06
    SP2(X_X____X, HMT2), // 07
    SP2(X______X, HMT2), // 08
    SP2(X______X, HMT2), // 09
    SP2(_X____X_, HMT3), // 10
    SP2(_X____X_, HMT3), // 11
    SP2(__XXXX__, HMT3), // 12
    SP2(_X____X_, BDY1), // 13
    SP2(_XXXXXX_, BDY0), // 14
    SP2(XX_XX_XX, BDY2), // 15
    SP2(XX_XX_XX, BDY2), // 16
    SP2(XXXXXXXX, BDY2), // 17
    SP2(X_XXXX_X, BDY2), // 18
    SP2(X_X__X_X, BDY2), // 19
    SP2(X__XX__X, BDY2), // 20
    SP2(__XXXX__, BDY2), // 21
    SP2(___XX___, BDY2), // 22
    SP2(__X__X__, HMT1), // 23
    SP2(__X__X__, HMT2), // 24
    SP2(__X__X__, HMT0), // 25
};

const unsigned char shape_FRAME_WALKDOWN1[] = {
    // 30

    25,
    3, 3,

    SP2(__XXX___, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXXXXX, HMT1), // 03
    SP2(XXXXXXXX, HMT1), // 04
    SP2(XX___XXX, HMT1), // 05
    SP2(X_X__XXX, HMT1), // 06
    SP2(X_X___XX, HMT2), // 07
    SP2(X_____XX, HMT2), // 08
    SP2(X_____XX, HMT2), // 09
    SP2(_X___XX_, HMT3), // 10
    SP2(_X___XX_, HMT3), // 11
    SP2(__XXXX__, HMT3), // 12
    SP2(______X_, BDY1), // 13
    SP2(_XXXXXXX, BDY1), // 14
    SP2(XX_XX_XX, BDY0), // 15
    SP2(XX_X_X_X, BDY1), // 16
    SP2(X_XX_XXX, BDY2), // 17
    SP2(__XX_XX_, BDY2), // 18
    SP2(___X_XX_, BDY2), // 19
    SP2(__X_X___, BDY2), // 20
    SP2(_XXX_X__, HMT1), // 21
    SP2(_XX__X__, HMT2), // 22
    SP2(_XX_____, HMT2), // 23
    SP2(__X_____, HMT0), // 24
};

const unsigned char shape_FRAME_WALKDOWN2[] = {
    // 31

    26,
    3, 3,

    SP2(__XXXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXXXXX, HMT1), // 03
    SP2(XXXXXXXX, HMT1), // 04
    SP2(XX_X__XX, HMT1), // 05
    SP2(XXX___XX, HMT1), // 06
    SP2(X_X____X, HMT2), // 07
    SP2(X______X, HMT2), // 08
    SP2(X______X, HMT2), // 09
    SP2(_X____X_, HMT3), // 10
    SP2(_X____X_, HMT3), // 11
    SP2(__XXXX__, HMT3), // 12
    SP2(_X____X_, BDY1), // 13
    SP2(_XXXXXX_, BDY0), // 14
    SP2(XX_XX_XX, BDY1), // 15
    SP2(XX_XX_XX, BDY2), // 16
    SP2(XXXXXXXX, BDY2), // 17
    SP2(X_XXXX_X, BDY2), // 18
    SP2(X_X__X_X, BDY2), // 19
    SP2(X__XX__X, BDY2), // 20
    SP2(__XXXX__, BDY2), // 21
    SP2(___XX___, BDY2), // 22
    SP2(__X__X__, HMT1), // 23
    SP2(__X__X__, HMT2), // 24
    SP2(__X__X__, HMT0), // 25
};

const unsigned char shape_FRAME_WALKDOWN3[] = {
    // 32

    25,
    3, 3,

    SP2(___XXX__, HMT0), // 00
    SP2(_XXXXXX_, HMT0), // 01
    SP2(_XXXXXX_, HMT0), // 02
    SP2(XXXXXXXX, HMT1), // 03
    SP2(XXXXXXXX, HMT1), // 04
    SP2(XXX___XX, HMT1), // 05
    SP2(XXXX___X, HMT1), // 06
    SP2(XX_X___X, HMT2), // 07
    SP2(XX_____X, HMT2), // 08
    SP2(XX_____X, HMT2), // 09
    SP2(_XX___X_, HMT3), // 10
    SP2(_XX___X_, HMT3), // 11
    SP2(__XXXX__, HMT3), // 12
    SP2(_X______, BDY1), // 13
    SP2(XXXXXXX_, BDY0), // 14
    SP2(XX_XX_XX, BDY1), // 15
    SP2(X_X_X_XX, BDY2), // 16
    SP2(XXX_XX_X, BDY2), // 17
    SP2(_XX_XX__, BDY2), // 18
    SP2(_XX_X___, BDY2), // 19
    SP2(___X_X__, BDY2), // 20
    SP2(__X_XXX_, HMT1), // 21
    SP2(__X__XX_, HMT2), // 22
    SP2(_____XX_, HMT2), // 23
    SP2(_____X__, HMT0), // 24
};

const unsigned char shape_FRAME_MINE_UP_0[] = {
    // 31

    SPRITE_DOUBLE | 31,
    0, 0,

    SP(________, XX______, BONE, BONE), // 00
    SP(_______X, X_______, BONE, BONE), // 00
    SP(______XX, X_______, BONE, BONE), // 01
    SP(_____X_X, X_______, BONE, BONE), // 02
    SP(________, X_______, BONE, BONE), // 03
    SP(________, X_______, BONE, BONE), // 04
    SP(______XX, XX______, HMT0, HMT0), // 05
    SP(_____XXX, XXX_____, HMT0, HMT0), // 06
    SP(_____XXX, XXX_____, HMT0, HMT0), // 07
    SP(____XXXX, XXXX____, HMT1, HMT1), // 08
    SP(____XXXX, XXXX____, HMT1, HMT1), // 09
    SP(____X_XX, XX_X____, HMT1, HMT1), // 10
    SP(____X_XX, XX_X____, HMT2, HMT2), // 11
    SP(____X_XX, XX_X____, HMT2, HMT2), // 12
    SP(____XXXX, XXXX____, HMT2, HMT2), // 13
    SP(____XXXX, XXXX____, HMT3, HMT3), // 14
    SP(_____XXX, XXX_____, HMT3, HMT3), // 15
    SP(____XX__, __X_____, BDY0, BDY1), // 16
    SP(____XXXX, X_______, BDY0, BDY1), // 17
    SP(____XXXX, X_______, BDY1, BDY1), // 18
    SP(____X___, __X_____, BDY1, BDY1), // 19
    SP(____XXXX, X_______, BDY2, BDY2), // 20
    SP(_____XXX, X_X_____, BDY2, BDY2), // 21
    SP(________, __X_____, BDY2, BDY2), // 22
    SP(_____XXX, X_______, HMT1, HMT1), // 23
    SP(________, ________, HMT2, HMT2), // 24
    SP(______XX, XX______, HMT0, HMT0), // 25
    SP(_______X, X_______, HMT0, HMT0), // 26
    SP(______X_, _X______, HMT0, HMT0), // 27
    SP(______X_, _X______, HMT0, HMT0), // 28
    SP(______X_, _X______, HMT0, HMT0), // 29
};

const unsigned char shape_FRAME_MINE_UP_1[] = {
    // 32

    SPRITE_DOUBLE | 24,
    -5, 0,

    SP(_______X, __XXXX__, BONE, HMT0), // 00
    SP(______X_, _XXXXXX_, BONE, HMT0), // 01
    SP(_____X__, _XXXXXX_, BONE, HMT0), // 02
    SP(_____XX_, XXXXXXXX, BONE, HMT1), // 03
    SP(____X_X_, XXXXXXXX, BONE, HMT1), // 04
    SP(____X__X, XX_XXXX_, BONE, HMT1), // 05
    SP(____X__X, XX_XXXX_, BONE, HMT1), // 06
    SP(____X___, XX_XXXX_, BONE, HMT2), // 07
    SP(________, XXXXXXXX, HMT2, HMT2), // 08
    SP(________, XXXXXXXX, HMT2, HMT2), // 09
    SP(________, XXX_____, BDY0, BDY1), // 10
    SP(________, _X_XXXX_, BDY0, BDY1), // 11
    SP(________, X_XXXXX_, BDY1, BDY1), // 12
    SP(________, X_X____X, BDY1, BDY1), // 13
    SP(________, XX_XXXXX, BDY0, BDY2), // 14
    SP(________, _X_XXXXX, BDY1, BDY2), // 15
    SP(________, _X______, BDY2, BDY2), // 16
    SP(________, ___XXXX_, BDY2, BDY2), // 17
    SP(________, ___XXXX_, BDY2, BDY2), // 18
    SP(________, __X__X__, BDY2, BDY2), // 19
    SP(________, _XXXXX__, BDY2, BDY2), // 20
    SP(________, _X_XXX__, HMT1, HMT1), // 21
    SP(________, _X___X__, HMT2, HMT2), // 22
    SP(________, _____X__, HMT2, HMT2), // 23
};

/*

*Area (0,6):
________, ________
*Area (1,6):
________, ________






























*/

const unsigned char shape_FRAME_MINE_DOWN_0[] = {
    // 31

    SPRITE_DOUBLE | 27,
    3, -4,

    SP(__XXXX__, ________, HMT0, BONE), // 00
    SP(_XXXXXX_, ________, HMT0, BONE), // 01
    SP(_XXXXXX_, ________, HMT0, BONE), // 02
    SP(XXXXXXXX, ________, HMT0, BONE), // 03
    SP(XXXXXXXX, ________, HMT1, BONE), // 04
    SP(XXX___XX, ________, HMT1, BONE), // 05
    SP(XXXX___X, ________, HMT1, HMT0), // 06
    SP(XX_X___X, ________, HMT1, HMT0), // 07
    SP(XX_____X, ________, HMT2, HMT0), // 08
    SP(XX_____X, ________, HMT2, HMT1), // 09
    SP(_XX___X_, ________, HMT2, HMT1), // 10
    SP(_XX___X_, ________, HMT3, HMT1), // 11
    SP(__XXXX__, ________, HMT3, HMT2), // 12
    SP(______X_, ________, BDY0, HMT2), // 13
    SP(_XXXXXX_, ________, BDY0, HMT2), // 14
    SP(_XXX__XX, ________, BDY1, HMT3), // 15
    SP(_X_XX__X, ________, BDY1, HMT3), // 16
    SP(__X_XXXX, ________, BDY1, BDY1), // 17
    SP(___X_XX_, ________, BDY2, BDY1), // 18
    SP(__X____X, ___X____, HMT1, BONE), // 19
    SP(_XXXXXXX, X__XX___, HMT1, BONE), // 20
    SP(XX_XXX_X, X__XX___, HMT2, BONE), // 21
    SP(_X______, _X_X____, HMT2, BONE), // 22
    SP(________, _XX_____, BDY2, BONE), // 23
    SP(________, __X_____, HMT1, BONE), // 24
    SP(________, _X______, HMT2, BONE), // 25
    SP(________, X_______, HMT0, BONE), // 26
};

const unsigned char shape_FRAME_MINE_DOWN_1[] = {
    // 32

    SPRITE_DOUBLE | 29,
    3, 0,

    SP(__XXXX__, ________, HMT0, HMT0), // 00
    SP(_XXXXXX_, ________, HMT0, HMT0), // 01
    SP(_XXXXXX_, ________, HMT0, HMT0), // 02
    SP(_XXXXXX_, ________, HMT1, HMT1), // 03
    SP(XXXXXXXX, ________, HMT1, HMT1), // 04
    SP(XX_X__XX, ________, HMT1, HMT1), // 05
    SP(XXX___XX, ________, HMT1, HMT1), // 06
    SP(X_X____X, ________, HMT1, HMT2), // 07
    SP(X______X, ________, HMT1, HMT2), // 08
    SP(X______X, ________, HMT2, HMT2), // 09
    SP(_X____X_, ________, HMT2, BDY1), // 10
    SP(_X____X_, ________, HMT2, BDY1), // 11
    SP(__XXXX__, ________, HMT2, BDY1), // 12
    SP(________, ________, BDY1, BDY1), // 13
    SP(_XXXXXX_, ________, BDY0, BDY2), // 14
    SP(_XX___X_, ________, BDY1, BDY2), // 15
    SP(__XX_XX_, ________, BDY2, BDY2), // 16
    SP(__XX_XX_, ________, BDY2, BDY2), // 17
    SP(___X_X__, ________, BDY2, BDY2), // 18
    SP(__X_X_X_, ________, BDY2, BDY2), // 19
    SP(_XXX_XXX, ________, BDY2, BDY2), // 20
    SP(XX_X_X_X, X_______, HMT1, HMT1), // 21
    SP(_X_____X, ________, HMT2, HMT2), // 22
    SP(____X___, ________, BONE, BONE), // 23
    SP(____X___, ________, BONE, BONE), // 24
    SP(____X___, ________, BONE, BONE), // 25
    SP(____XX_X, ________, BONE, BONE), // 26
    SP(____XXX_, ________, BONE, BONE), // 27
    SP(___XX___, ________, BONE, BONE), // 28
};

const unsigned char *const spriteShape[] = {

    shape_FRAME_BLANK,       // 00
    shape_FRAME_STAND,       // 01
    0,                       // shape_FRAME_ARMS_IN_AIR,       // 02
    shape_FRAME_HUNCH,       // 03
    shape_FRAME_PUSH,        // 04
    shape_FRAME_PUSH2,       // 05
    0,                       // shape_FRAME_IMPATIENT,         // 06
    0,                       // shape_FRAME_IMPATIENT2,        // 07
    0,                       // shape_FRAME_LOOK1,             // 08
    0,                       // shape_FRAME_LOOK2,             // 09
    0,                       // shape_FRAME_SHADES,            // 10
    0,                       // shape_FRAME_SHADES_ARM,        // 11
    0,                       // shape_FRAME_BLINK,             // 12
    shape_FRAME_WALK1,       // 13
    shape_FRAME_WALK2,       // 14
    shape_FRAME_WALK3,       // 15
    shape_FRAME_WALK4,       // 16
    0,                       // shape_FRAME_SNATCH_DOWN,       // 17
    shape_FRAME_SKELETON1,   // 18
    shape_FRAME_SKELETON2,   // 19
    shape_FRAME_SKELETON3,   // 20
    shape_FRAME_SKELETON4,   // 21
    shape_FRAME_SKELETON5,   // 22
    0,                       // shape_FRAME_ARMSCROSSED,       // 23
    0,                       // shape_FRAME_TALK,              // 24
    shape_FRAME_WALKUP0,     // 25
    shape_FRAME_WALKUP1,     // 26
    shape_FRAME_WALKUP2,     // 27
    shape_FRAME_WALKUP3,     // 28
    shape_FRAME_WALKDOWN0,   // 29
    shape_FRAME_WALKDOWN1,   // 30
    shape_FRAME_WALKDOWN2,   // 31
    shape_FRAME_WALKDOWN3,   // 32
    shape_FRAME_MINE_UP_0,   // 33
    shape_FRAME_MINE_UP_1,   // 34
    shape_FRAME_MINE_DOWN_0, // 35
    shape_FRAME_MINE_DOWN_1, // 36
};

void processAnimationCommand() {

    while (!playerAnimationCount)
        switch (*playerAnimation) {

        case ACTION_SFX:
            ADDAUDIO(*++playerAnimation);
            playerAnimation++;
            break;

        case ACTION_FLIP:
            faceDirection = -faceDirection;
            playerAnimation++;
            break;

        case ACTION_LOOP:
            if (playerDead)
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
            startPlayerAnimation(playerDead ? ID_Skeleton : ID_Stand);
            break;

        case ACTION_POSITION: {
            frameAdjustX = *++playerAnimation;
            frameAdjustY = *++playerAnimation;
            playerAnimation++;
            break;
        }

        case ACTION_DOT: {

            int dotX = 2 + (*++playerAnimation) * faceDirection;
            int dotY = *++playerAnimation;
            nDots(4, playerX, playerY, 2, -30, dotX, dotY, 0x10000);
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
    0x10000 / 3,
#endif

#if SPEED_BASE == 3
    0x10000 / 4,
#endif

#if SPEED_BASE == 4
    0x10000 / 5,
#endif

#if SPEED_BASE == 5
    0x10000 / 6,
#endif

#if SCHEDULER == 1
    0x10000 / 3,
#endif

    //    0x10000/5,
    //    0x10000/6,
    //    0x10000/7,
    0x10000 / 7,
// 0x10000/9,
// 0x10000/10,
// 0x10000/11,
// 0x10000/12,
// 0x10000/13,

#if SPEED_BASE == 6
    0x10000 / 11,
#endif
};

void updateAnimation() {

    if (autoMoveFrameCount)
        autoMoveFrameCount--;

    autoMoveX = ((autoMoveFrameCount * autoMoveDeltaX * (int)reciprocal[0]) >> 16);
    autoMoveY = ((autoMoveFrameCount * autoMoveDeltaY * (int)reciprocal[0]) >> 16);

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

// EOF