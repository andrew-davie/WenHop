#ifndef __BITSHAPES_H
#define __BITSHAPES_H

#define SMALL_SPRITE_OFFSET 94
#define FRAMEDELAY_RANDOM 254


enum FRAME {
    FRAME_BLANK,            // 21
    FRAME_STAND,            // 0
    FRAME_ARMS_IN_AIR,      // 1
    FRAME_HUNCH,            // 2
    FRAME_HAIR,             // 3
    FRAME_PUSH,             // 4
    FRAME_PUSH2,            // 5
    FRAME_HAIR2,            // 6
    FRAME_IMPATIENT,        // 7
    FRAME_IMPATIENT2,       // 8
    FRAME_LOOK1,            // 9
    FRAME_LOOK2,            // 10
    FRAME_SHADES,           // 11
    FRAME_SHADES_ARM,       // 12
    FRAME_BLINK,            // 13
    FRAME_WALK1,            // 14
    FRAME_WALK2,            // 15
    FRAME_WALK3,            // 16
    FRAME_WALK4,            // 17
    FRAME_SNATCH_DOWN,      // 18
    FRAME_SKELETON,         // 19
    FRAME_SKELETON2,        // 20
    FRAME_SKELETON3,        // 22
    FRAME_SKELETON4,        // 23
    FRAME_SKELETON5,        // 24

    FRAME_ARMSCROSSED,      // 25

//#if ENABLE_SHAKE    
//    FRAME_SHAKE,            // 28
//    FRAME_SHAKE2,           // 29
//    FRAME_SHAKE3,           // 30
//#endif

    FRAME_TALK,             // 26



    // actions start after frames

    ACTION_SFX,
    ACTION_SAY,
    ACTION_POSITION,
    ACTION_FLIP,
    ACTION_LOOP,
    ACTION_STOP,
};


enum AnimationIdent {

    ID_Stand,
    ID_Push,
//#if ENABLE_SHAKE
//    ID_Shake,
//#endif
    ID_WipeHair,
    ID_Impatient,
    ID_Turn,
    ID_Blink,
    ID_Shades,
    ID_Die,
    ID_Walk,
    ID_Snatch,
    ID_SnatchDown,
    ID_SnatchUp,
    ID_Skeleton,
    ID_Skeleton2,
//    ID_Startup,
    ID_ArmsCrossed,
    ID_Talk,
    ID_EndPush2,
    
//#if __ENABLE_DRIP
    ID_Drip,
    ID_Talk2,
//    ID_Drip2,
//#endif

    ID_Locked,

};

extern int autoMoveX;
extern int autoMoveY;
extern int autoMoveDeltaX;
extern int autoMoveDeltaY;
extern int autoMoveFrameCount;

extern const signed char *const AnimationVector[]; //animJames[];
extern const int AnimationIndex[];

extern enum AnimationIdent playerAnimationID;
extern const signed char *playerAnimation;
extern const signed char *playerAnimationLoop;
extern unsigned int playerAnimationCount;

extern const signed char playerBigSprite[][2 + 23 * 3];

//#define ZEROBLOCK playerBigSprite

extern const unsigned short reciprocal[];

void processAnimationCommand();
void updateAnimation();
void startPlayerAnimation(enum AnimationIdent animID);

extern const unsigned char redirect[];

#endif
//EOF