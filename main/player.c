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

const signed char AnimationPush[] = {

    FRAME_PUSH2, 3,
    ACTION_SFX, SFX_PICKAXE,
    FRAME_PUSH, 10,
    FRAME_PUSH2, 3,
    FRAME_HUNCH, 3,
    FRAME_STAND, 2,
    ACTION_STOP,
};

const signed char AnimationLocked[] = {
    FRAME_HUNCH, 12,
    ACTION_STOP,
};

const signed char AnimationEndPush2[] = {
//    ACTION_POSITION, 4,0,
//    FRAME_PUSH2, 15,
//    ACTION_POSITION, 2,0,
    FRAME_HUNCH, 5,
    ACTION_STOP,
};

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

const signed char AnimationWipeHair[] = {
//    FRAME_WIPE_HAIR, 22,
//    FRAME_HAIR, 64,
    FRAME_HAIR2, 4,
    FRAME_HAIR, 4,
    FRAME_HAIR2, 4,
    FRAME_HAIR, 4,
    ACTION_STOP,
};

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

const signed char AnimationImpatient[] = {
    FRAME_ARMSCROSSED, 50,
    FRAME_IMPATIENT, 10,
    FRAME_IMPATIENT2, 10,
    FRAME_IMPATIENT, 10,
    FRAME_IMPATIENT2, 10,
    FRAME_IMPATIENT, 10,
    FRAME_IMPATIENT2, 10,
    // FRAME_IMPATIENT, 10,
    // FRAME_IMPATIENT2, 10,
    ACTION_STOP,
};


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

const signed char AnimationBlink[] = {
    FRAME_BLINK, 6,
    ACTION_STOP,
};

const signed char AnimationTurn[] = {
    FRAME_LOOK1, 4,
    FRAME_LOOK2, 4,
    ACTION_FLIP,
    ACTION_STOP,
};

const signed char AnimationShades[] = {
    FRAME_STAND, 50,
    FRAME_SHADES_ARM, 20,
    FRAME_SHADES, 125,
    FRAME_SHADES_ARM, 25,
    ACTION_STOP,
};

const signed char AnimationDie[] = {
// #if ENABLE_SHAKE
//     FRAME_SHAKE,6,
// #endif

    FRAME_ARMS_IN_AIR,10,
    //FRAME_HUNCH,100,
    ACTION_STOP,
};

const signed char AnimationWalk[] = {

    FRAME_WALK1, 3,
    FRAME_WALK2, 3,
    FRAME_WALK3, 3,
    FRAME_WALK4, 3,
    ACTION_LOOP,
    ACTION_STOP,
};



const signed char AnimationSnatch[] = {
    ACTION_POSITION, 5,0,
    FRAME_PUSH, 10,
    ACTION_POSITION, 0,0,
    FRAME_IMPATIENT, 15,
    ACTION_STOP,
};

const signed char AnimationSnatchDown[] = {
    ACTION_POSITION, 0,-4,
    FRAME_SNATCH_DOWN, 10,
    ACTION_POSITION, 0,0,
    FRAME_IMPATIENT, 15,
    ACTION_STOP,
};

const signed char AnimationSnatchUp[] = {
    ACTION_POSITION, 0,4,
    FRAME_ARMS_IN_AIR, 10,
    ACTION_POSITION, 0,0,
    FRAME_IMPATIENT, 15,
    ACTION_STOP,
};


const signed char AnimationSkeleton2[] = {
    FRAME_SKELETON4, 8,
    FRAME_SKELETON, 8,
    ACTION_LOOP,
    ACTION_STOP,
};

const signed char AnimationSkeleton[] = {

    FRAME_SKELETON, 20,
    FRAME_SKELETON4, 20,
    FRAME_SKELETON3, 8,
    FRAME_SKELETON2, 8,
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

const signed char AnimationTalk[] = {
#if __ENABLE_ATARIVOX
    ACTION_SAY, __WORD_DOSOMETHING,
    FRAME_TALK,10, //FRAMEDELAY_RANDOM,
    FRAME_STAND,3, //FRAMEDELAY_RANDOM,
    FRAME_TALK,6, //FRAMEDELAY_RANDOM,
    FRAME_STAND,4, //FRAMEDELAY_RANDOM,
    FRAME_TALK,10, //FRAMEDELAY_RANDOM,
#endif
    FRAME_STAND,10, //FRAMEDELAY_RANDOM,
    FRAME_BLINK, 6,
    ACTION_STOP,
};

const signed char AnimationTalk2[] = {
    FRAME_TALK,10,
    FRAME_BLINK, 10,
    ACTION_STOP,
};



//#if __ENABLE_DRIP

const signed char AnimationDrip[] = {
    FRAME_IMPATIENT,25,
    FRAME_STAND,10,
    FRAME_HAIR2, 6,
    FRAME_HAIR, 6,
    FRAME_HAIR2, 6,
    FRAME_HAIR, 6,
    ACTION_STOP,
};

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

    AnimationDefault,
    AnimationPush,
// #if ENABLE_SHAKE
//     AnimationShake,
// #endif
    AnimationWipeHair,
    AnimationImpatient,
    AnimationTurn,
    AnimationBlink,
    AnimationShades,
    AnimationDie,
    AnimationWalk,
    AnimationSnatch,
    AnimationSnatchDown,
    AnimationSnatchUp,
    AnimationSkeleton,
    AnimationSkeleton2,
//    AnimationStartup,
    AnimationArmsCrossed,
    AnimationTalk,
    AnimationEndPush2,

//#if __ENABLE_DRIP
    AnimationDrip,
//    AnimationDrip2,
//#endif
    AnimationTalk2,

    AnimationLocked,
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


const unsigned char redirect[] = { 0, 1, 1, 2};
const unsigned char playerColour[][4] = {

    //NTSC  PAL  PAL_60 SECAM

    { 0x28, 0x98, 0x98, 0x0C },   // 0 HAIR
    { 0x34, 0x24, 0x24, 0x06 },   // 1 SKIN
    { 0x06, 0x26, 0x26, 0x0C },   // 2 TOP1
    { 0x06, 0x20, 0x20, 0x04 },   // 3 TOP 2
    { 0x24, 0x22, 0x22, 0x02 },   // 4 BOOT
    { 0x08, 0x04, 0x04, 0x0A },   // 5 PANT
    { 0x58, 0x96, 0x96, 0x0E },   // 6 BELT
    { 0x08, 0x06, 0x06, 0x0E },   // 5 SOLE
    { 0x0A, 0x0A, 0x0A, 0x0E },   // 8 BONE    
};




#define SP(a,b,c,d) \
    a, b, (c << 4) + d

//#define PNT2 0x04


const signed char playerBigSprite[][2 + SPRITE_DEPTH * 3] = {

// Format
// X, Y offsets
// [GRP0, GRP1, COLUP0, COLUP1,]      * (PIECE_DEPTH+0)

{   // FRAME_BLANK = 23

    0,0,

    SP( ________,________, ____, ____ ),     //00
    SP( ________,________, ____, ____ ),     //01
    SP( ________,________, ____, ____ ),     //02
    SP( ________,________, ____, ____ ),     //03
    SP( ________,________, ____, ____ ),     //04
    SP( ________,________, ____, ____ ),     //05
    SP( ________,________, ____, ____ ),     //06
    SP( ________,________, ____, ____ ),     //05
    SP( ________,________, ____, ____ ),     //08
    SP( ________,________, ____, ____ ),     //09
    SP( ________,________, ____, ____ ),     //10
    SP( ________,________, ____, ____ ),     //11
    SP( ________,________, ____, ____ ),     //12
    SP( ________,________, ____, ____ ),     //13
    SP( ________,________, ____, ____ ),     //14
    SP( ________,________, ____, ____ ),     //15
    SP( ________,________, ____, ____ ),     //16
    SP( ________,________, ____, ____ ),     //15
    SP( ________,________, ____, ____ ),     //18
    SP( ________,________, ____, ____ ),     //19
    SP( ________,________, ____, ____ ),     //20
    SP( ________,________, ____, ____ ),     //21
    SP( ________,________, ____, ____ ),     //22

},

{   // FRAME_STAND= 0

    2+0, 0,

    SP( ____X_X_,X_______, HAIR, HAIR ),     //00
    SP( __X_____,________, HAIR, HAIR ),     //00
    SP( _X_XXXX_,_X______, HAIR, HAIR ),     //01
    SP( __XXXXXX,X_______, HAIR, HAIR ),     //02
    SP( X_XXXXXX,_X______, SKIN, HAIR ),     //03
    SP( __XXXXXX,________, SKIN, HAIR ),     //04
    SP( X_XX_X_X,_X______, SKIN, HAIR ),     //05
    SP( __XXXXXX,________, SKIN, HAIR ),     //06
    SP( X_XXXXX_,X_______, SKIN, SKIN ),     //05
    SP( ___X____,________, SKIN, SKIN ),     //08
    SP( _X_XXXX_,X_______, SKIN, SKIN ),     //09
    SP( __XXXXXX,________, TOP1, TOP1 ),     //10
    SP( _XX_XX_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXX_X_X,X_______, TOP1, TOP1 ),     //12
    SP( XXXXX_XX,XX______, TOP2, TOP2 ),     //13
    SP( ___XX_X_,XX______, TOP2, SKIN ),     //15
    SP( XX_XX_X_,________, BELT, BELT ),     //16
    SP( XX_XXXXX,________, PANT, PANT ),     //15
    SP( ___XX_XX,________, PANT, PANT ),     //18
    SP( __XXX_XX,________, PANT, PANT ),     //19
    SP( __XX__XX,________, BOOT, BOOT ),     //20
    SP( __XXX_XX,X_______, BOOT, BOOT ),     //21
    SP( __XXX_XX,X_______, SOLE, SOLE ),     //22

    },



{   // FRAME_ARMS_IN_AIR = 1

    -3+0, 0,

    SP( ________,_X_X_X__, HAIR, HAIR ),     //00
    SP( _______X,_______X, HAIR, HAIR ),     //01
    SP( _____XX_,_XXXX___, SKIN, HAIR ),     //02
    SP( _____XX_,XXXXXXXX, SKIN, SKIN ),     //03
    SP( ____XX__,XXXXX_XX, TOP2, SKIN ),     //04
    SP( ____XX__,X_X_X_XX, TOP1, SKIN ),     //05
    SP( ____XX__,XXXXX_XX, TOP2, SKIN ),     //06
    SP( ____XX__,XX_XX_XX, TOP1, SKIN ),     //05
    SP( ____XXX_,XXXX__XX, TOP2, SKIN ),     //08
    SP( _____XXX,_XXX_XX_, TOP1, SKIN ),     //09
    SP( ______XX,_XXX_XX_, TOP1, TOP1 ),     //10
    SP( _______X,X_X_XXX_, TOP2, TOP2 ),     //11
    SP( _______X,XX_XXX__, TOP1, TOP1 ),     //12
    SP( ________,XX_XX___, TOP2, TOP2 ),     //13
    SP( ________,XX_X____, TOP1, TOP1 ),     //14
    SP( ________,XX_X____, TOP2, TOP2 ),     //15
    SP( ________,XXXX____, BELT, BELT ),     //16
    SP( _______X,XXXXX___, PANT, PANT ),     //15
    SP( _______X,XXXXX___, PANT, PANT ),     //18
    SP( _______X,X__XX___, PANT, PANT ),     //19
    SP( ______XX,X__XXX__, BOOT, BOOT ),     //20
    SP( ______XX,X___XX__, BOOT, BOOT ),     //21
    SP( ______XX,X___XXX_, SOLE, SOLE ),     //22

},


// {   // FRAME_HOLD_BOULDER_1 = 2

//     2+0, 0,   // X,Y OFFSET

//     _XX_XXXX,_XX_____, HAIR, BELT,     //00
//     _XX_XXXX,_XX_____, HAIR, BELT,     //01
//     ___XXXXX,________, HAIR, HAIR,     //02
//     XX_XXXXX,_XX_____, SKIN, SKIN,     //03
//     XX_X_X_X,_XX_____, SKIN, SKIN,     //04
//     XX_XXXXX,_XX_____, SKIN, SKIN,     //05
//     XX_XX_XX,_XX_____, SKIN, SKIN,     //06
//     XX_XXXXX,_XX_____, SKIN, SKIN,     //05
//     XXX_XXX_,_XX_____, SKIN, SKIN,     //08
//     _XXXXXXX,XX______, SKIN, SKIN,     //09
//     __XXXXXX,XX______, TOP1, TOP1,     //10
//     __XXXXXX,X_______, TOP2, TOP2,     //11
//     ___XXXXX,________, TOP1, ____,     //12
//     ___XXXX_,________, TOP2, ____,     //13
//     ___XXXX_,________, TOP1, ____,     //14
//     ___XXXX_,________, TOP2, ____,     //15
//     ___XXXX_,________, BELT, ____,     //16
//     ___XXXX_,________, PANT, ____,     //15
//     ___XXXXX,________, PANT, ____,     //18
//     __XXX_XX,________, PANT, ____,     //19
//     __XXX_XX,X_______, BOOT, BOOT,     //20
//     __XXX__X,X_______, BOOT, BOOT,     //21
//     __XXX__X,XX______, SOLE, SOLE,     //22

//     -4,0,    // x,y

//     _X_XX_X_, HAIR,    // 0
//     _X_X_X__, SKIN,    // 1
//     _X___X__, TOP2,    // 2
//     _XXXX___, TOP1,    // 3
//     __XXX___, TOP2,    // 4
//     __XX____, TOP1,    // 5
//     __XX____, TOP2,    // 6
//     __X_X___, PNT2,    // 5
//     _XX_X___, BOOT,    // 8

// },


// {   // FRAME_WIPE_HAIR = 3

//     2+0, 0,

//     ____XXX_,________, HAIR, ____,     //00
//     ___XXXX_,________, HAIR, ____,     //01
//     __XXXXXX,________, HAIR, ____,     //02
//     __XXXXXX,X_______, HAIR, HAIR,     //03
//     __XXXXXX,XX______, SKIN, HAIR,     //04
//     __X_X_X_,XX______, SKIN, SKIN,     //05
//     __XXXXX_,XX______, SKIN, TOP1,     //06
//     __XXXXX_,XX______, SKIN, TOP2,     //05
//     ___X_XX_,XX______, SKIN, TOP1,     //08
//     ___XXXX_,XX______, SKIN, TOP2,     //09
//     __XXXXXX,XX______, TOP1, TOP1,     //10
//     _XXXXXXX,X_______, TOP2, TOP2,     //11
//     _XXXXXXX,________, TOP1, ____,     //12
//     XX_XXXX_,________, TOP2, ____,     //13
//     XX_XXXX_,________, TOP1, ____,     //14
//     ___XXXX_,________, TOP2, ____,     //15
//     XX_XXXX_,________, BELT, ____,     //16
//     XX_XXXXX,________, PANT, ____,     //15
//     ___XX_XX,________, PANT, ____,     //18
//     __XXX_XX,________, PANT, ____,     //19
//     __XX__XX,________, BOOT, BOOT,     //20
//     __XXX_XX,X_______, BOOT, BOOT,     //21
//     __XXX_XX,X_______, SOLE, SOLE,     //22

// },

{   // FRAME_HUNCH = 4

    3+0, 0,

    SP( ___X_X_X,________, ____, ____ ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //00
    SP( ___XXXX_,________, HAIR, HAIR ),     //01
    SP( X_XXXXXX,_X______, HAIR, HAIR ),     //02
    SP( __XXXXXX,________, SKIN, HAIR ),     //03
    SP( X_XXXXXX,_X______, SKIN, HAIR ),     //04
    SP( __XX_X_X,________, SKIN, HAIR ),     //05
    SP( X_XXXXXX,_X______, SKIN, SKIN ),     //06
    SP( __XXXXX_,________, SKIN, SKIN ),     //05
    SP( _X_XX_X_,X_______, SKIN, SKIN ),     //08
    SP( __XXXXX_,________, TOP1, TOP1 ),     //10
    SP( _XX_XXX_,________, TOP2, TOP2 ),     //11
    SP( XXXX_X_X,________, TOP1, TOP1 ),     //12
    SP( XXXXX_XX,________, TOP2, TOP2 ),     //13
    SP( XXX_X_XX,________, TOP1, TOP1 ),     //14
    SP( XXX_XX_X,X_______, TOP2, SKIN ),     //15
    SP( _XXXXX_X,X_______, BELT, BELT ),     //16
    SP( __XXXXX_,X_______, PANT, SKIN ),     //15
    SP( _XXX_XX_,________, PANT, PANT ),     //18
    SP( _XXX_XX_,________, PANT, PANT ),     //19
    SP( _XX__XX_,________, BOOT, BOOT ),     //20
    SP( _XXX_XXX,________, BOOT, BOOT ),     //21
    SP( _XXX_XXX,________, SOLE, SOLE ),     //22

},


{   // FRAME_HAIR = 5

    2+0, 0,

    SP( ___X_X_X,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( ___XXXX_,________, HAIR, HAIR ),     //02
    SP( X_XXXXXX,_X______, SKIN, HAIR ),     //03
    SP( __XXXXXX,________, SKIN, SKIN ),     //04
    SP( X_XX_X_X,_X______, SKIN, SKIN ),     //05
    SP( __XXXXXX,________, SKIN, SKIN ),     //06
    SP( X_XXXXXX,_X______, SKIN, SKIN ),     //05
    SP( ___XX_X_,X_______, SKIN, SKIN ),     //08
    SP( _X__XXX_,________, SKIN, SKIN ),     //09
    SP( __X_XXXX,X_______, TOP1, TOP1 ),     //10
    SP( _XXX_X_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXXX_XX,XX______, TOP1, TOP1 ),     //12
    SP( XX_XX_X_,XX______, TOP2, TOP2 ),     //13
    SP( XX_XX_X_,XX______, TOP1, TOP1 ),     //14
    SP( ___XXXX_,XX______, TOP2, SKIN ),     //15
    SP( XX_XXXX_,________, BELT, BELT ),     //16
    SP( XX_XXXXX,________, PANT, PANT ),     //15
    SP( ___XX_XX,________, PANT, PANT ),     //18
    SP( __XXX_XX,________, PANT, PANT ),     //19
    SP( __XX__XX,________, BOOT, BOOT ),     //20
    SP( __XXX_XX,X_______, BOOT, BOOT ),     //21
    SP( __XXX_XX,X_______, SOLE, SOLE ),     //22

},

{   // FRAME_PUSH = 6

    4, 0,

    SP( ___X__X_,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( ____XXXX,_X______, HAIR, BOOT ),     //02
    SP( X_XXXXXX,___X____, HAIR, BOOT ),     //03
    SP( __XXXXXX,__XXXX__, SKIN, BOOT ),     //04
    SP( X_XXXXXX,_XXXXXXX, SKIN, BOOT ),     //05
    SP( __XX_X_X,_X_XXXXX, SKIN, BOOT ),     //06
    SP( X_XXXXXX,__XX_XX_, SKIN, BOOT ),     //05
    SP( __XXXXX_,X_XX____, SKIN, BOOT ),     //08
    SP( _X_XX_X_,_XX_____, TOP2, BOOT ),     //09
    SP( ___XXXX_,_XX_____, TOP1, BOOT ),     //10
    SP( _XXX_XX_,XX______, TOP2, BOOT ),     //11
    SP( XXXXX_XX,X_______, TOP1, BOOT ),     //12
    SP( XXXXXX_X,________, TOP2, TOP2 ),     //13
    SP( XXX_XXXX,________, TOP1, TOP1 ),     //14
    SP( XXX_XX_X,________, TOP2, TOP2 ),     //15
    SP( _XXXXX_X,________, BELT, BELT ),     //16
    SP( __XXXXX_,________, PANT, PANT ),     //15
    SP( _XXX_XX_,________, PANT, PANT ),     //18
    SP( _XXX_XX_,________, PANT, PANT ),     //19
    SP( _XX__XX_,________, BOOT, BOOT ),     //20
    SP( _XXX_XXX,________, BOOT, BOOT ),     //21
    SP( _XXX_XXX,________, SOLE, SOLE ),     //22

},


{   // FRAME_PUSH2 = 5

    3, 0,

    SP( ___X__X_,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( ____XXXX,_X______, HAIR, BOOT ),     //02
    SP( X_XXXXXX,________, HAIR, BOOT ),     //03
    SP( __XXXXXX,_X______, SKIN, BOOT ),     //04
    SP( X_XXXXXX,________, SKIN, BOOT ),     //05
    SP( __XX_X_X,_X______, SKIN, BOOT ),     //06
    SP( X_XXXXXX,________, SKIN, BOOT ),     //05
    SP( __XXXXX_,X_______, SKIN, BOOT ),     //08
    SP( _X_XX_X_,________, TOP2, BOOT ),     //09
    SP( ___XXXX_,________, TOP1, BOOT ),     //10
    SP( _XXX_XX_,_X______, TOP2, BOOT ),     //11
    SP( XXXXX_XX,XX______, TOP1, BOOT ),     //12
    SP( XXXXXX_X,X_______, TOP2, BOOT ),     //13
    SP( XXX_XXXX,X_______, TOP1, TOP1 ),     //14
    SP( XXX_XX_X,________, TOP2, TOP2 ),     //15
    SP( _XXXXX_X,________, BELT, BELT ),     //16
    SP( __XXXXX_,________, PANT, PANT ),     //15
    SP( _XXX_XX_,________, PANT, PANT ),     //18
    SP( _XXX_XX_,________, PANT, PANT ),     //19
    SP( _XX__XX_,________, BOOT, BOOT ),     //20
    SP( _XXX_XXX,________, BOOT, BOOT ),     //21
    SP( _XXX_XXX,________, SOLE, SOLE ),     //22

},

{   // FRAME_HAIR2 = 8

    2+0, 0,

    SP( ___X_X_X,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( ___XXXX_,________, HAIR, HAIR ),     //02
    SP( X_XXXXXX,_X______, SKIN, HAIR ),     //03
    SP( __XXXXXX,________, SKIN, SKIN ),     //04
    SP( X_X_X_XX,_X______, SKIN, SKIN ),     //05
    SP( __XXXXXX,________, SKIN, SKIN ),     //06
    SP( X__XXXXX,_X______, SKIN, SKIN ),     //05
    SP( ___X_XX_,X_______, SKIN, SKIN ),     //08
    SP( _X__XXX_,________, SKIN, SKIN ),     //09
    SP( __X_XXXX,X_______, TOP1, TOP1 ),     //10
    SP( _XXX_X_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXXX_XX,XX______, TOP1, TOP1 ),     //12
    SP( XX_XX_X_,XX______, TOP2, TOP2 ),     //13
    SP( XX_XX_X_,XX______, TOP1, TOP1 ),     //14
    SP( ___XXXX_,XX______, TOP2, SKIN ),     //15
    SP( XX_XXXX_,________, BELT, BELT ),     //16
    SP( XX_XXXXX,________, PANT, PANT ),     //15
    SP( ___XX_XX,________, PANT, PANT ),     //18
    SP( __XXX_XX,________, PANT, PANT ),     //19
    SP( __XX__XX,________, BOOT, BOOT ),     //20
    SP( __XXX_XX,X_______, BOOT, BOOT ),     //21
    SP( __XXX_XX,X_______, SOLE, SOLE ),     //22

},


{   // FRAME_IMPATIENT = 9

    0+1, 0,

    SP( __X_X_X_,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( ___XXXX_,_X______, HAIR, HAIR ),     //02
    SP( X_XXXXXX,________, SKIN, HAIR ),     //03
    SP( __XXXXXX,_X______, SKIN, SKIN ),     //04
    SP( X_XX_X_X,________, SKIN, SKIN ),     //05
    SP( __XXXXXX,_X______, SKIN, SKIN ),     //06
    SP( X_XXXXX_,________, SKIN, SKIN ),     //05
    SP( ___XX_X_,_X______, SKIN, SKIN ),     //08
    SP( __X_XXXX,________, SKIN, TOP2 ),     //09
    SP( ___X_XXX,X_______, TOP1, TOP1 ),     //10
    SP( ___XX_X_,XX______, TOP2, TOP2 ),     //11
    SP( __XXXX_X,XXX_____, TOP1, TOP1 ),     //12
    SP( _XXXXX_X,XXX_____, TOP2, TOP2 ),     //13
    SP( _XX_XX_X,_XX_____, TOP1, SKIN ),     //14
    SP( _XX_XXXX,X_______, TOP2, TOP2 ),     //15
    SP( ____XXXX,X_______, BELT, BELT ),     //16
    SP( _XX_XXXX,X_______, PANT, PANT ),     //15
    SP( _XX_XX_X,X_______, PANT, PANT ),     //18
    SP( ___XXX_X,XXX_____, PANT, BOOT ),     //19
    SP( ___XX__X,XXX_____, BOOT, BOOT ),     //20
    SP( ___XXX__,________, BOOT, SOLE ),     //21
    SP( ___XXX__,________, SOLE, SOLE ),     //22

    },


{   // FRAME_IMPATIENT2 = 10

    0+1, 0,

    SP( __X_X_X_,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( ___XXXX_,_X______, HAIR, HAIR ),     //02
    SP( X_XXXXXX,________, SKIN, HAIR ),     //03
    SP( __XXXXXX,_X______, SKIN, SKIN ),     //04
    SP( X_XX_X_X,________, SKIN, SKIN ),     //05
    SP( __XXXXXX,_X______, SKIN, SKIN ),     //06
    SP( X_XXXXX_,________, SKIN, SKIN ),     //05
    SP( ___XX_X_,_X______, SKIN, SKIN ),     //08
    SP( __X_XXXX,________, SKIN, TOP2 ),     //09
    SP( __X_XXX_,________, TOP1, TOP1 ),     //10
    SP( __XX_X_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXXX_XX,XX______, TOP1, TOP1 ),     //12
    SP( XXXXX_XX,XX______, TOP2, TOP2 ),     //13
    SP( XX_XX_X_,XX______, TOP1, SKIN ),     //14
    SP( XX_XXXX_,________, TOP2, TOP2 ),     //15
    SP( ___XXXXX,________, BELT, BELT ),     //16
    SP( XX_XXXXX,________, PANT, PANT ),     //15
    SP( XX_XX_XX,XX______, PANT, BOOT ),     //18
    SP( __XXX_XX,XX______, BOOT, BOOT ),     //19
    SP( __XX____,________, BOOT, BOOT ),     //20
    SP( __XXX___,________, BOOT, BOOT ),     //21
    SP( __XXX___,________, SOLE, SOLE ),     //22
    },

{   // FRAME_LOOK1 = 11

    3,0,

    SP( ___X_X_X,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( ___XXXX_,________, HAIR, HAIR ),     //02
    SP( X_XXXXXX,_X______, SKIN, HAIR ),     //03
    SP( __XXXXXX,________, SKIN, HAIR ),     //04
    SP( X_X_X_XX,_X______, SKIN, HAIR ),     //05
    SP( __XXXXXX,________, SKIN, SKIN ),     //06
    SP( X_XXXXXX,_X______, SKIN, SKIN ),     //05
    SP( ___X_XX_,________, SKIN, SKIN ),     //08
    SP( _X_XXXX_,X_______, SKIN, SKIN ),     //09
    SP( __X_XXXX,________, TOP1, TOP1 ),     //10
    SP( _XXX_X_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXXX_XX,XX______, TOP1, TOP1 ),     //12
    SP( _XX_X_XX,XX______, TOP2, TOP2 ),     //13
    SP( _XXXX_X_,XX______, TOP1, TOP1 ),     //14
    SP( ___XXXX_,XX______, TOP2, SKIN ),     //15
    SP( _XXXXXX_,________, BELT, BELT ),     //16
    SP( ___XXXX_,________, PANT, PANT ),     //15
    SP( ___XXXX_,________, PANT, PANT ),     //18
    SP( ___XXXXX,________, PANT, PANT ),     //19
    SP( ___XX_XX,________, BOOT, BOOT ),     //20
    SP( ___XX_XX,X_______, BOOT, BOOT ),     //21
    SP( ___XX_XX,X_______, SOLE, SOLE ),     //22

    },

{   // FRAME_LOOK2 = 12

    2,0,

    SP( ___X_X_X,________, HAIR, HAIR ),     //00
    SP( _X______,_X______, HAIR, HAIR ),     //01
    SP( ___XXXXX,__X_____, HAIR, HAIR ),     //02
    SP( X__XXXXX,X_______, SKIN, HAIR ),     //03
    SP( __XXXXXX,X_X_____, SKIN, HAIR ),     //04
    SP( X_X_X_XX,X_______, SKIN, HAIR ),     //05
    SP( __XXXXXX,X_X_____, SKIN, HAIR ),     //06
    SP( _X_XXXXX,_X______, SKIN, SKIN ),     //05
    SP( __X__XXX,________, SKIN, SKIN ),     //08
    SP( ____XXXX,________, SKIN, SKIN ),     //09
    SP( ___X_XXX,XX______, TOP1, TOP1 ),     //10
    SP( __XXX_X_,XXX_____, TOP2, TOP2 ),     //11
    SP( __XXXX_X,XXX_____, TOP1, TOP1 ),     //12
    SP( __XX_X_X,_XX_____, TOP2, TOP2 ),     //13
    SP( __XXXX_X,__XX____, TOP1, TOP1 ),     //14
    SP( ____XXXX,__XX____, TOP2, SKIN ),     //15
    SP( __XXXXXX,________, BELT, BELT ),     //16
    SP( ____XXXX,________, PANT, PANT ),     //15
    SP( ____XXXX,________, PANT, PANT ),     //18
    SP( ____XXXX,________, PANT, PANT ),     //19
    SP( ____XX_X,X_______, BOOT, BOOT ),     //20
    SP( ____XX_X,X_______, BOOT, BOOT ),     //21
    SP( ___XXX_X,X_______, SOLE, SOLE ),     //22
    },

{   // FRAME_SHADES = 13

    2+0,0,
    
    SP( ___X_X_X,________, HAIR, HAIR ),     //00
    SP( _X______,_X______, HAIR, HAIR ),     //01
    SP( ___XXXXX,________, HAIR, HAIR ),     //02
    SP( X_XXXXXX,_X______, SKIN, HAIR ),     //03
    SP( __XXXXXX,________, SKIN, HAIR ),     //04
    SP( X_______,_X______, SKIN, HAIR ),     //05
    SP( __XX_X_X,________, SKIN, HAIR ),     //06
    SP( X_XXXXX_,_X______, SKIN, SKIN ),     //05
    SP( ___XX_X_,X_______, SKIN, SKIN ),     //08
    SP( _X_XXXX_,________, SKIN, SKIN ),     //09
    SP( __X_XXXX,X_______, TOP1, TOP1 ),     //10
    SP( _XXX_X_X,XX______, TOP2, TOP2 ),     //11
    SP( _XXXX_XX,XX______, TOP1, TOP1 ),     //12
    SP( XX_XX_X_,XX______, TOP2, TOP2 ),     //13
    SP( XX_XX_X_,_XX_____, TOP1, TOP1 ),     //14
    SP( ___XXXX_,_XX_____, TOP2, SKIN ),     //15
    SP( XX_XXXX_,________, BELT, BELT ),     //16
    SP( XX_XXXXX,________, PANT, PANT ),     //15
    SP( ___XX_XX,________, PANT, PANT ),     //18
    SP( __XXX_XX,________, PANT, PANT ),     //19
    SP( __XX__XX,________, BOOT, BOOT ),     //20
    SP( __XXX_XX,X_______, BOOT, BOOT ),     //21
    SP( __XXX_XX,X_______, SOLE, SOLE ),     //22

    },

{   // FRAME_SHADES_ARM = 14

    2+0, 0,

    SP( ___X_X_X,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( __X_XXX_,________, HAIR, HAIR ),     //02
    SP( X_XXXXXX,_X______, HAIR, HAIR ),     //03
    SP( __XXXXXX,________, SKIN, HAIR ),     //04
    SP( X_______,XX______, SKIN, SKIN ),     //05
    SP( __XX_X_X,XX______, SKIN, SKIN ),     //06
    SP( X_XXXXX_,XX______, SKIN, TOP2 ),     //05
    SP( ___XX_X_,XX______, SKIN, TOP1 ),     //08
    SP( _X_XXXX_,XX______, SKIN, TOP2 ),     //09
    SP( ___XXXXX,XX______, TOP1, TOP1 ),     //10
    SP( _XXX_X_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXXX_XX,________, TOP1, TOP1 ),     //12
    SP( XX_XX_X_,________, TOP2, TOP2 ),     //13
    SP( XX_XX_X_,________, TOP1, TOP1 ),     //14
    SP( ___XXXX_,________, TOP2, TOP2 ),     //15
    SP( XX_XXXX_,________, BELT, BELT ),     //16
    SP( XX_XXXXX,________, PANT, PANT ),     //15
    SP( ___XX_XX,________, PANT, PANT ),     //18
    SP( __XXX_XX,________, PANT, PANT ),     //19
    SP( __XX__XX,________, BOOT, BOOT ),     //20
    SP( __XXX_XX,X_______, BOOT, BOOT ),     //21
    SP( __XXX_XX,X_______, SOLE, SOLE ),     //22

},


{   // FRAME_BLINK= 15

    2+0, 0,

    SP( ____X_X_,X_______, HAIR, HAIR ),     //00
    SP( __X_____,________, HAIR, HAIR ),     //00
    SP( _X_XXXX_,_X______, HAIR, HAIR ),     //01
    SP( __XXXXXX,X_______, HAIR, HAIR ),     //02
    SP( X_XXXXXX,_X______, SKIN, HAIR ),     //03
    SP( __XXXXXX,________, SKIN, HAIR ),     //04
    SP( X_XXXXXX,_X______, SKIN, HAIR ),     //05
    SP( __XXXXXX,________, SKIN, HAIR ),     //06
    SP( X_XXXXX_,X_______, SKIN, SKIN ),     //05
    SP( ___X____,________, SKIN, SKIN ),     //08
    SP( _X_XXXX_,X_______, SKIN, SKIN ),     //09
    SP( __XXXXXX,________, TOP1, TOP1 ),     //10
    SP( _XX_XX_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXX_X_X,X_______, TOP1, TOP1 ),     //12
    SP( XXXXX_XX,XX______, TOP2, TOP2 ),     //13
    SP( ___XX_X_,XX______, TOP2, SKIN ),     //15
    SP( XX_XX_X_,________, BELT, BELT ),     //16
    SP( XX_XXXXX,________, PANT, PANT ),     //15
    SP( ___XX_XX,________, PANT, PANT ),     //18
    SP( __XXX_XX,________, PANT, PANT ),     //19
    SP( __XX__XX,________, BOOT, BOOT ),     //20
    SP( __XXX_XX,X_______, BOOT, BOOT ),     //21
    SP( __XXX_XX,X_______, SOLE, SOLE ),     //22

    },

{   // FRAME_WALK1 = 16

    3, -2,

    SP( ____X_X_,X_______, HAIR, HAIR ),     //00
    SP( __X_____,_X______, HAIR, HAIR ),     //01
    SP( _X__XXXX,X_______, HAIR, HAIR ),     //02
    SP( ___XXXXX,X_X_____, SKIN, HAIR ),     //03
    SP( _X_XXXXX,X_______, SKIN, HAIR ),     //04
    SP( ___XX_X_,X_X_____, SKIN, HAIR ),     //05
    SP( _X_XXXXX,X_______, SKIN, HAIR ),     //06
    SP( ___XXXXX,__X_____, SKIN, SKIN ),     //05
    SP( __X_XX_X,X_______, SKIN, SKIN ),     //08
    SP( ____XXX_,________, SKIN, SKIN ),     //09
    SP( __XXX_XX,X_______, TOP1, TOP1 ),     //10
    SP( _XXXX_X_,XX______, TOP2, TOP2 ),     //11
    SP( XXXXXX_X,XX______, TOP1, TOP1 ),     //12
    SP( XX_XXXX_,XX______, TOP2, TOP2 ),     //13
    SP( XX_XXXX_,_XX_____, TOP1, TOP1 ),     //14
    SP( ___XXXXX,_XX_____, TOP2, SKIN ),     //15
    SP( XX_XXXXX,________, BELT, BELT ),     //16
    SP( __XXXXXX,________, PANT, PANT ),     //15
    SP( __XXX_XX,X_______, PANT, PANT ),     //18
    SP( _XXX___X,XX______, PANT, PANT ),     //19
    SP( XXX_____,XX______, BOOT, BOOT ),     //20
    SP( XX______,XX______, BOOT, BOOT ),     //21
    SP( XXX_____,XXX_____, SOLE, SOLE ),     //22

},



{   // FRAME_WALK2 = 15

    3, 0,

    SP( ____X_X_,X_______, HAIR, HAIR ),     //00
    SP( __X_____,_X______, HAIR, HAIR ),     //01
    SP( _X__XXXX,X_______, HAIR, HAIR ),     //02
    SP( ___XXXXX,X_X_____, SKIN, HAIR ),     //03
    SP( _X_XXXXX,X_______, SKIN, HAIR ),     //04
    SP( ___XX_X_,X_X_____, SKIN, HAIR ),     //05
    SP( _X_XXXXX,X_______, SKIN, HAIR ),     //06
    SP( ___XXXXX,__X_____, SKIN, SKIN ),     //05
    SP( __X_XX_X,X_______, SKIN, SKIN ),     //08
    SP( ____XXX_,________, SKIN, SKIN ),     //09
    SP( __XXX_XX,________, TOP1, TOP1 ),     //10
    SP( __XXXX_X,________, TOP2, TOP2 ),     //11
    SP( _XXXXX_X,X_______, TOP2, TOP2 ),     //12
    SP( __XXXXXX,X_______, TOP1, TOP1 ),     //13
    SP( ___XXXXX,X_______, TOP2, SKIN ),     //14
    SP( __X_XXX_,________, BELT, BELT ),     //15
    SP( __XXXXXX,________, PANT, PANT ),     //16
    SP( __XXXXXX,________, PANT, PANT ),     //15
    SP( __XXX_XX,X_______, PANT, PANT ),     //18
    SP( _XXX___X,XX______, BOOT, PANT ),     //19
    SP( XX______,XX______, BOOT, BOOT ),     //20
    SP( XXX_____,XX______, SOLE, BOOT ),     //21
    SP( ________,XXX_____, SOLE, SOLE ),     //22

    },


{   // FRAME_WALK3 = 18

    3, 1,

    SP( ____X_X_,X_______, HAIR, HAIR ),     //00
    SP( __X_____,_X______, HAIR, HAIR ),     //01
    SP( _X__XXXX,X_______, HAIR, HAIR ),     //02
    SP( ___XXXXX,X_X_____, SKIN, HAIR ),     //03
    SP( _X_XXXXX,X_______, SKIN, HAIR ),     //04
    SP( ___XX_X_,X_X_____, SKIN, HAIR ),     //05
    SP( _X_XXXXX,X_______, SKIN, HAIR ),     //06
    SP( ___XXXXX,__X_____, SKIN, SKIN ),     //05
    SP( __X_XX_X,X_______, SKIN, SKIN ),     //08
    SP( ____XXX_,________, SKIN, SKIN ),     //09
    SP( __XXX_XX,________, TOP1, TOP1 ),     //10
    SP( __XXXX_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXXXX_X,X_______, TOP1, TOP1 ),     //12
    SP( _XX_XXX_,X_______, TOP2, TOP1 ),     //13
    SP( _XX_XXX_,X_______, TOP1, TOP1 ),     //14
    SP( ____XXXX,X_______, TOP2, SKIN ),     //15
    SP( __XX_XX_,________, BELT, BELT ),     //16
    SP( ____XXXX,________, PANT, PANT ),     //15
    SP( ____XXXX,________, PANT, PANT ),     //18
    SP( __XX_XXX,________, PANT, PANT ),     //19
    SP( __XX_XXX,________, BOOT, BOOT ),     //20
    SP( _____XX_,________, BOOT, BOOT ),     //21
    SP( _____XXX,________, SOLE, SOLE ),     //22


},



{   // FRAME_WALK4 = 19

    3, 0,

    SP( ____X_X_,X_______, HAIR, HAIR ),     //00
    SP( __X_____,_X______, HAIR, HAIR ),     //01
    SP( _X__XXXX,X_______, HAIR, HAIR ),     //02
    SP( ___XXXXX,X_X_____, SKIN, HAIR ),     //03
    SP( _X_XXXXX,X_______, SKIN, HAIR ),     //04
    SP( ___XX_X_,X_X_____, SKIN, HAIR ),     //05
    SP( _X_XXXXX,X_______, SKIN, HAIR ),     //06
    SP( ___XXXXX,__X_____, SKIN, SKIN ),     //05
    SP( __X_XX_X,X_______, SKIN, SKIN ),     //08
    SP( ____XXX_,________, SKIN, SKIN ),     //09
    SP( __XXX_XX,X_______, TOP1, TOP1 ),     //10
    SP( _XXXXX_X,XX______, TOP2, TOP2 ),     //11
    SP( XXXXXX_X,XX______, TOP1, TOP1 ),     //12
    SP( XX_XXXX_,XX______, TOP2, TOP2 ),     //13
    SP( XX_XXXX_,_XX_____, TOP1, TOP1 ),     //14
    SP( ___XXXXX,_XX_____, TOP2, SKIN ),     //15
    SP( XX_XXXXX,________, BELT, BELT ),     //16
    SP( ____XXXX,________, PANT, PANT ),     //15
    SP( ____XXXX,________, PANT, PANT ),     //18
    SP( _____XXX,X_______, PANT, BOOT ),     //19
    SP( ____XXXX,X_______, BOOT, BOOT ),     //20
    SP( _____XX_,________, BOOT, BOOT ),     //21
    SP( _____XXX,________, SOLE, SOLE ),     //22

    },

{   // FRAME_SNATCH_DOWN = 20

    2+0, 0,

    SP( ________,________, ____, ____ ),     //00
    SP( ________,________, ____, ____ ),     //01
    SP( ________,________, ____, ____ ),     //02
    SP( ________,________, ____, ____ ),     //03
    SP( ________,________, ____, ____ ),     //04
    SP( ________,________, ____, ____ ),     //05
    SP( ____X_X_,X_______, ____, ____ ),     //06
    SP( __X_____,__X_____, HAIR, HAIR ),     //05
    SP( _X__XXXX,X_______, HAIR, HAIR ),     //08
    SP( ___XXXXX,X_X_____, SKIN, SKIN ),     //09
    SP( _X_XXXXX,X_______, SKIN, SKIN ),     //10
    SP( ___XX_X_,X_X_____, SKIN, SKIN ),     //11
    SP( _X_XXXXX,X_______, SKIN, SKIN ),     //12
    SP( ___XXXXX,_X______, SKIN, SKIN ),     //13
    SP( __X_XX_X,________, SKIN, SKIN ),     //14
    SP( __XX_XXX,X_______, TOP1, TOP1 ),     //15
    SP( __XXX_X_,X_______, TOP2, TOP2 ),     //16
    SP( __XXXX_X,X_______, TOP1, TOP1 ),     //15
    SP( __XX_XXX,X_______, TOP2, TOP2 ),     //18
    SP( ___XX_XX,X_______, TOP1, TOP1 ),     //19
    SP( ___XXXXX,X_______, TOP2, TOP2 ),     //20
    SP( __XXX_XX,X_______, BELT, SKIN ),     //21
    SP( __XXX_XX,X_______, SOLE, SKIN ),     //22

},

{   // FRAME_SKELETON = 21

    0,0,

    SP( ________,________, ____, ____ ),     //00
    SP( ________,________, ____, ____ ),     //01
    SP( _____XXX,X_______, BONE, BONE ),     //02
    SP( ____XXXX,XX______, BONE, BONE ),     //03
    SP( ____X__X,__X_____, BONE, BONE ),     //04
    SP( ____X__X,__X_____, BONE, BONE ),     //05
    SP( ____XXXX,XX______, BONE, BONE ),     //06
    SP( _____X_X,_X______, BONE, BONE ),     //05
    SP( ______X_,X_______, BONE, BONE ),     //08
    SP( _______X,________, BONE, BONE ),     //09
    SP( ____XXXX,XX______, BONE, BONE ),     //10
    SP( ___X___X,__X_____, BONE, BONE ),     //11
    SP( __XX_XXX,X_XX____, BONE, BONE ),     //12
    SP( __X____X,___X____, BONE, BONE ),     //13
    SP( _____XXX,XX______, BONE, BONE ),     //14
    SP( __XX__XX,X_XX____, BONE, BONE ),     //15
    SP( _X___X_X,_X__X___, BONE, BONE ),     //16
    SP( _____X__,_X______, BONE, BONE ),     //15
    SP( ____XX__,_XX_____, BONE, BONE ),     //18
    SP( _____X__,_X______, BONE, BONE ),     //19
    SP( ________,________, BONE, BONE ),     //20
    SP( ____XXX_,XXX_____, BONE, BONE ),     //21
    SP( ________,________, ____, ____ ),     //22

    },

{   // FRAME_SKELETON2 = 22

    -1,0,

    SP( ________,________, ____, ____ ),     //00
    SP( ________,________, ____, ____ ),     //01
    SP( ________,________, ____, ____ ),     //02
    SP( ________,________, ____, ____ ),     //03
    SP( ________,________, ____, ____ ),     //04
    SP( ________,________, ____, ____ ),     //05
    SP( ________,________, ____, ____ ),     //06
    SP( ________,________, ____, ____ ),     //05
    SP( ________,________, ____, ____ ),     //08
    SP( ________,________, ____, ____ ),     //09
    SP( ________,________, ____, ____ ),     //10
    SP( ________,XXXX____, BONE, BONE ),     //11
    SP( _______X,XXXXX___, BONE, BONE ),     //12
    SP( _______X,__X__X__, BONE, BONE ),     //13
    SP( _______X,__X__X__, BONE, BONE ),     //14
    SP( _______X,XXXXX___, BONE, BONE ),     //15
    SP( ________,X_X_X___, BONE, BONE ),     //16
    SP( ________,_X_X____, BONE, BONE ),     //15
    SP( _____X__,XXXX____, BONE, BONE ),     //18
    SP( ___X___X,________, BONE, BONE ),     //19
    SP( _______X,XX______, BONE, BONE ),     //20
    SP( ___X__X_,______X_, BONE, BONE ),     //21
    SP( __XX__XX,X_XXX__X, BONE, BONE ),     //22

    },




{   // FRAME_SKELETON3 = 24

    0,0,

    SP( ________,________, ____, ____ ),     //00
    SP( ________,________, ____, ____ ),     //01
    SP( ________,________, ____, ____ ),     //02
    SP( ________,________, ____, ____ ),     //03
    SP( ________,________, ____, ____ ),     //04
    SP( ________,________, ____, ____ ),     //05
    SP( _______X,XXX_____, BONE, BONE ),     //06
    SP( ______XX,XXXX____, BONE, BONE ),     //05
    SP( ______X_,_X__X___, BONE, BONE ),     //08
    SP( ______X_,_X__X___, BONE, BONE ),     //09
    SP( ______XX,XXXX____, BONE, BONE ),     //10
    SP( _______X,_X_X____, BONE, BONE ),     //11
    SP( ________,X_X_____, BONE, BONE ),     //12
    SP( __X_XXX_,XXX_____, BONE, BONE ),     //13
    SP( _X____X_,________, BONE, BONE ),     //14
    SP( _X__XXXX,___X____, BONE, BONE ),     //15
    SP( ______XX,__XX____, BONE, BONE ),     //16
    SP( _X__X_X_,X_______, BONE, BONE ),     //15
    SP( _X__X___,X___XX__, BONE, BONE ),     //18
    SP( _X__X___,X___X___, BONE, BONE ),     //19
    SP( X_______,________, BONE, BONE ),     //20
    SP( ___XXX_X,XX______, BONE, BONE ),     //21
    SP( ________,________, ____, ____ ),     //22

    },


{   // FRAME_SKELETON4 = 25

    1,0,

    SP( ________,________, ____, ____ ),     //00
    SP( ________,________, ____, ____ ),     //01
    SP( ____XXXX,________, BONE, BONE ),     //02
    SP( ___XXXXX,X_______, BONE, BONE ),     //03
    SP( __X__X__,X_______, BONE, BONE ),     //04
    SP( __X__X__,X_______, BONE, BONE ),     //05
    SP( __XXXXXX,X_______, BONE, BONE ),     //06
    SP( ___X_X_X,________, BONE, BONE ),     //05
    SP( ____X_X_,________, BONE, BONE ),     //08
    SP( _______X,________, BONE, BONE ),     //09
    SP( ___XXXXX,X_______, BONE, BONE ),     //10
    SP( __X___X_,_X______, BONE, BONE ),     //11
    SP( _XX_XXXX,_XX_____, BONE, BONE ),     //12
    SP( _X____X_,__X_____, BONE, BONE ),     //13
    SP( ____XXXX,X_______, BONE, BONE ),     //14
    SP( _XX__XXX,_XX_____, BONE, BONE ),     //15
    SP( X___X_X_,X__X____, BONE, BONE ),     //16
    SP( ____X___,X_______, BONE, BONE ),     //15
    SP( ___XX___,XX______, BONE, BONE ),     //18
    SP( ____X___,X_______, BONE, BONE ),     //19
    SP( ________,________, BONE, BONE ),     //20
    SP( ___XXX_X,XX______, BONE, BONE ),     //21
    SP( ________,________, ____, ____ ),     //22

    },


{   // FRAME_SKELETON5 = 26

    0,0,

    SP( ________,________, ____, ____ ),     //00
    SP( ________,________, ____, ____ ),     //01
    SP( ________,________, ____, ____ ),     //02
    SP( ________,________, ____, ____ ),     //03
    SP( ________,________, ____, ____ ),     //04
    SP( ________,________, ____, ____ ),     //05
    SP( ________,________, ____, ____ ),     //06
    SP( ________,________, ____, ____ ),     //05
    SP( ________,________, ____, ____ ),     //08
    SP( ________,________, ____, ____ ),     //09
    SP( ________,________, ____, ____ ),     //10
    SP( ________,________, ____, ____ ),     //11
    SP( ________,________, ____, ____ ),     //12
    SP( ________,________, ____, ____ ),     //13
    SP( ________,________, ____, ____ ),     //14
    SP( ________,________, ____, ____ ),     //15
    SP( ________,________, ____, ____ ),     //16
    SP( ________,________, ____, ____ ),     //15
    SP( ________,________, ____, ____ ),     //18
    SP( ________,________, ____, ____ ),     //19
    SP( _______X,XXXXX___, BONE, BONE ),     //20
    SP( ______X_,_X__XX__, BONE, BONE ),     //21
    SP( ______XX,_XX__X__, BONE, BONE ),     //22

    },


{   // FRAME_ARMSCROSSED = 25

    2+0, 0,



    SP( ___X_X_X,________, HAIR, HAIR ),     //00
    SP( _X______,X_______, HAIR, HAIR ),     //01
    SP( X__XXXXX,________, HAIR, HAIR ),     //02
    SP( __XXXXXX,_X______, HAIR, HAIR ),     //03
    SP( X_XXXXXX,________, SKIN, HAIR ),     //04
    SP( __XX_X_X,_X______, SKIN, HAIR ),     //05
    SP( X_XXXXXX,________, SKIN, HAIR ),     //06
    SP( __XXXXX_,_X______, SKIN, SKIN ),     //05
    SP( _X_XX_X_,X_______, SKIN, SKIN ),     //08
    SP( ___XXXX_,________, SKIN, SKIN ),     //09
    SP( __X_XXXX,________, TOP1, TOP1 ),     //10
    SP( _XXX_X_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXX__XX,X_______, TOP1, TOP1 ),     //12
    SP( _XXXXXXX,X_______, TOP2, BELT ),     //13
    SP( __XXXX_X,X_______, PANT, TOP1 ),     //14
    SP( ______XX,________, TOP2, TOP2 ),     //15
    SP( ___XXXX_,________, BELT, BELT ),     //16
    SP( ___XXXXX,________, PANT, PANT ),     //15
    SP( ___XXXXX,________, PANT, PANT ),     //18
    SP( ___XX_XX,________, PANT, PANT ),     //19
    SP( __XX__XX,________, BOOT, BOOT ),     //20
    SP( __XXX_XX,X_______, BOOT, BOOT ),     //21
    SP( __XXX_XX,X_______, SOLE, SOLE ),     //22

    },

// #if ENABLE_SHAKE

// {   // FRAME_SHAKE= 28

//     -1+0, 0,

//     ________,________, ____, ____,     //00
//     _______X,XXX_____, HAIR, HAIR,     //01
//     ______XX,XXX_____, HAIR, HAIR,     //02
//     _____XXX,XXXX____, HAIR, HAIR,     //03
//     _____XXX,XXXXXX__, HAIR, HAIR,     //04
//     _____XXX,XXXX____, SKIN, SKIN,     //05
//     _____XX_,X_X_____, SKIN, SKIN,     //06
//     _____XXX,XXX_____, SKIN, SKIN,     //05
//     _____XXX,XX______, SKIN, SKIN,     //08
//     __XX__XX,_X__XX__, SKIN, SKIN,     //09
//     ___X__XX,_X__X___, SKIN, SKIN,     //10
//     ____XXXX,XXXXX___, TOP1, TOP1,     //11
//     ___XXXXX,XXXXX___, TOP2, TOP2,     //12
//     ____XXXX,XXXX____, TOP1, TOP1,     //13
//     ______XX,XX______, TOP2, TOP2,     //14
//     ______XX,XX______, TOP1, TOP1,     //15
//     ______XX,XX______, TOP2, TOP2,     //16
//     ______XX,XX______, BELT, BELT,     //15
//     ______XX,XXX_____, PANT, PANT,     //18
//     ______XX,_XX_____, PANT, BOOT,     //19
//     _____XX_,_XX_____, BOOT, BOOT,     //20
//     _____XXX,_XXX____, BOOT, SOLE,     //21
//     _____XXX,________, SOLE, SOLE,     //22

//     },


// {   // FRAME_SHAKE = 29

//     0+0, 0,

//     ________,________, ____, ____,     //00
//     _______X,XXX_____, HAIR, HAIR,     //01
//     ______XX,XXX_____, HAIR, HAIR,     //02
//     _____XXX,XXXX____, HAIR, HAIR,     //03
//     _____XXX,XXXXXX__, HAIR, HAIR,     //04
//     _____XXX,XXXX____, SKIN, SKIN,     //05
//     _____XX_,X_X_____, SKIN, SKIN,     //06
//     _____XXX,XXX_____, SKIN, SKIN,     //05
//     _____XXX,XX______, SKIN, SKIN,     //08
//     ______XX,_X___XX_, SKIN, SKIN,     //09
//     ______XX,_X___X__, SKIN, SKIN,     //10
//     ____XXXX,XXXXXX__, TOP1, TOP1,     //11
//     ___XXXXX,XXXXXX__, TOP2, TOP2,     //12
//     __XXX_XX,XXXXX___, TOP1, TOP1,     //13
//     __XX__XX,XX______, TOP2, TOP2,     //14
//     __XX__XX,XX______, TOP1, TOP1,     //15
//     ______XX,XX______, TOP2, TOP2,     //16
//     __XX__XX,XX______, BELT, BELT,     //15
//     ______XX,XXX_____, PANT, PANT,     //18
//     ______XX,_XX_____, PANT, BOOT,     //19
//     _____XX_,_XX_____, BOOT, BOOT,     //20
//     _____XXX,_XXX____, BOOT, BOOT,     //21
//     _____XXX,________, SOLE, SOLE,     //22
    
//     },

// {   // FRAME_SHAKE= 30

//     -1+0, 0,

//     ________,________, ____, ____,     //00
//     _______X,XXX_____, HAIR, HAIR,     //01
//     ______XX,XXX_____, HAIR, HAIR,     //02
//     _____XXX,XXXX____, HAIR, HAIR,     //03
//     _____XXX,XXXXXX__, HAIR, HAIR,     //04
//     _____XXX,XXXX____, SKIN, SKIN,     //05
//     _____XX_,X_X_____, SKIN, SKIN,     //06
//     _____XXX,XXX_____, SKIN, SKIN,     //05
//     _____XXX,XX______, SKIN, SKIN,     //08
//     _XX___XX,_X______, SKIN, SKIN,     //09
//     __X___XX,_X______, SKIN, SKIN,     //10
//     __XXXXXX,XXX_____, TOP1, TOP1,     //11
//     __XXXXXX,XXXX____, TOP2, TOP2,     //12
//     ___XXXXX,XXXXX___, TOP1, TOP1,     //13
//     ______XX,XX_XX___, TOP2, TOP2,     //14
//     ______XX,XX__XX__, TOP1, TOP1,     //15
//     ______XX,XX______, TOP2, TOP2,     //16
//     ______XX,XX__XX__, BELT, BELT,     //15
//     ______XX,XXX_____, PANT, PANT,     //18
//     ______XX,_XX_____, PANT, BOOT,     //19
//     _____XX_,_XX_____, BOOT, BOOT,     //20
//     _____XXX,_XXX____, BOOT, SOLE,     //21
//     _____XXX,________, SOLE, SOLE,     //22

//     },

// #endif

{   // FRAME_TALK= 31

    2+0, 0,



    SP( ____X_X_,________, HAIR, HAIR ),     //00
    SP( __X_____,X_______, HAIR, HAIR ),     //01
    SP( _X_XXXXX,________, HAIR, HAIR ),     //02
    SP( __XXXXXX,_X______, HAIR, HAIR ),     //03
    SP( X_XXXXXX,________, SKIN, HAIR ),     //04
    SP( __XX_X_X,_X______, SKIN, HAIR ),     //05
    SP( X_XXXXXX,________, SKIN, HAIR ),     //06
    SP( __XXXXX_,_X______, SKIN, SKIN ),     //05
    SP( _X_XX_X_,X_______, SKIN, SKIN ),     //08
    SP( ___XXXX_,________, SKIN, SKIN ),     //09
    SP( __X_XXXX,________, TOP1, TOP1 ),     //10
    SP( _XXX_X_X,X_______, TOP2, TOP2 ),     //11
    SP( _XXXX_XX,X_______, TOP1, TOP1 ),     //12
    SP( XX_XX_X_,XX______, TOP2, TOP2 ),     //13
    SP( XX_XX_X_,XX______, TOP1, TOP1 ),     //14
    SP( ___XXXX_,XX______, TOP2, SKIN ),     //15
    SP( XX_XXXX_,________, BELT, BELT ),     //16
    SP( XX_XXXXX,________, PANT, PANT ),     //15
    SP( ___XX_XX,________, PANT, PANT ),     //18
    SP( __XXX_XX,________, PANT, PANT ),     //19
    SP( __XX__XX,________, BOOT, BOOT ),     //20
    SP( __XXX_XX,X_______, BOOT, BOOT ),     //21
    SP( __XXX_XX,X_______, SOLE, SOLE ),     //22

    },

// {   // FRAME_TALK= 31

//     3+0, 0,



//     ________,________, HAIR, ____ ),     //00
//     ________,________, HAIR, ____ ),     //01
//     ________,________, HAIR, HAIR ),     //02
//     ________,________, HAIR, HAIR ),     //03
//     ___XXXXX,________, SKIN, HAIR ),     //04
//     __XXXXXX,X_______, HAIR, HAIR ),     //05
//     __XXXXXX,________, HAIR, HAIR ),     //06
//     __XXXXXX,________, HAIR, ____ ),     //05
//     __XXXXX_,________, HAIR, ____ ),     //08
//     ___XXXX_,________, HAIR, ____ ),     //09
//     ___XXXXX,________, SKIN, TOP1 ),     //10
//     __XXXXXX,X_______, TOP2, TOP2 ),     //11
//     __XXXXXX,X_______, TOP1, TOP1 ),     //12
//     _XXXXXXX,XX______, TOP2, TOP2 ),     //13
//     XX_XXXX_,________, SKIN, SKIN ),     //14
//     XX_XXXX_,________, SKIN, ____ ),     //15
//     __XX_XXX,________, SKIN, BELT ),     //16
//     __XX_XXX,________, SKIN, PANT ),     //15
//     __X____X,________, SKIN, ____ ),     //18
//     ___XX_XX,________, SKIN, ____ ),     //19
//     ___XX_XX,________, SKIN, ____ ),     //20
//     __XX__XX,X_______, BOOT, BOOT ),     //21
//     __XXX_XX,X_______, SOLE, SOLE ),     //22


//     },
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

            else if (exitMode)
                startPlayerAnimation(ID_Shades);

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
        }
            break;

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


//ROF