#ifndef __BITSHAPES_H
#define __BITSHAPES_H

#define SMALL_SPRITE_OFFSET 94
#define FRAMEDELAY_RANDOM 254

#define SPRITE_DOUBLE 0x80
#define SPRITE_ABSCOLOUR 0x40

enum FRAME {

    // see (player.c) -> create a frame shape_* and add to spriteShape[] table

    FRAME_BLANK,       // 21
    FRAME_STAND,       // 0
    FRAME_ARMS_IN_AIR, // 1
    FRAME_HUNCH,       // 2
                       //    FRAME_HAIR,             // 3
    FRAME_PUSH,        // 4
    FRAME_PUSH2,       // 5
                       //    FRAME_HAIR2,            // 6
    FRAME_IMPATIENT,   // 7
    FRAME_IMPATIENT2,  // 8
    FRAME_LOOK1,       // 9
    FRAME_LOOK2,       // 10
    FRAME_SHADES,      // 11
    FRAME_SHADES_ARM,  // 12
    FRAME_BLINK,       // 13
    FRAME_WALK1,       // 14
    FRAME_WALK2,       // 15
    FRAME_WALK3,       // 16
    FRAME_WALK4,       // 17
    FRAME_SNATCH_DOWN, // 18
    FRAME_SKELETON1,   // 19
    FRAME_SKELETON2,   // 20
    FRAME_SKELETON3,   // 22
    FRAME_SKELETON4,   // 23
    FRAME_SKELETON5,   // 24

    FRAME_ARMSCROSSED, // 25

    // #if ENABLE_SHAKE
    //    FRAME_SHAKE,            // 28
    //    FRAME_SHAKE2,           // 29
    //    FRAME_SHAKE3,           // 30
    // #endif

    FRAME_TALK, // 26

    FRAME_WALKUP0,
    FRAME_WALKUP1,
    FRAME_WALKUP2,
    FRAME_WALKUP3,

    FRAME_WALKDOWN0,
    FRAME_WALKDOWN1,
    FRAME_WALKDOWN2,
    FRAME_WALKDOWN3,

    FRAME_MINE_UP_0,
    FRAME_MINE_UP_1,
    FRAME_MINE_DOWN_0,
    FRAME_MINE_DOWN_1,

    // actions start after frames

    ACTION_DOT,
    ACTION_SFX,
    ACTION_SAY,
    ACTION_POSITION,
    ACTION_FLIP,
    ACTION_LOOP,
    ACTION_STOP,

};

enum AnimationIdent {

    // see (player.c) AnimationVector[] -> animation program

    ID_Stand,    // 00
    ID_StandUp,  // 01
    ID_StandLR,  // 02
    ID_Push,     // 03
    ID_Turn,     // 04
    ID_Die,      // 05
    ID_Walk,     // 06
    ID_Skeleton, // 07
    ID_Locked,   // 08
    ID_WalkUp,   // 09
    ID_WalkDown, // 10
    ID_MineUp,   // 11
    ID_MineDown, // 12
};

extern int autoMoveX;
extern int autoMoveY;
extern int autoMoveDeltaX;
extern int autoMoveDeltaY;
extern int autoMoveFrameCount;

extern const signed char *const AnimationVector[]; // animJames[];
extern const int AnimationIndex[];

extern enum AnimationIdent playerAnimationID;
extern const signed char *playerAnimation;
extern const signed char *playerAnimationLoop;
extern unsigned int playerAnimationCount;

extern const unsigned short reciprocal[];

void processAnimationCommand();
void updateAnimation();
void startPlayerAnimation(enum AnimationIdent animID);

extern const unsigned char redirect[];
extern const unsigned char *const spriteShape[];

#endif
// EOF