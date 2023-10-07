#include "defines.h"
#include "defines_cdfj.h"
// #include "defines_from_dasm_for_c.h"

#include "main.h"

#include "mellon.h"

#include "animations.h"
#include "atarivox.h"
#include "attribute.h"
#include "colour.h"
#include "decodecaves.h"
#include "joystick.h"
#include "player.h"
#include "random.h"
#include "score.h"
#include "scroll.h"
#include "sound.h"

int playerX; // char pos 0-39 (use *5 for pixel)
int playerY; // char pos 0-21 (use *10 for pixel and then *3 for scanline)

int frameAdjustX;
int frameAdjustY;
unsigned int pushCounter;
enum FaceDirectionX faceDirection;
bool playerDead;
int waitForNothing;
bool handled;

enum JOYSTICK_DIRECTION {
    JOYSTICK_UP = 1,
    JOYSTICK_DOWN = 2,
    JOYSTICK_LEFT = 4,
    JOYSTICK_RIGHT = 8,
};

const unsigned char joyDirectBit[] = {
    JOYSTICK_UP,
    JOYSTICK_RIGHT,
    JOYSTICK_DOWN,
    JOYSTICK_LEFT,
};

const signed char faceDirectionDef[] = {
    FACE_UP,
    FACE_RIGHT,
    FACE_DOWN,
    FACE_LEFT,
};

const signed char animDeltaX[] = {
    0,
    -20,
    0,
    -20,
};

const unsigned char mineAnimation[] = {
    ID_MineUp,
    ID_Push,
    ID_MineDown,
    ID_Push,
};

const unsigned char tapAnimation[] = {
    ID_TapUp,
    ID_TapPush,
    ID_TapDown,
    ID_TapPush,
};

const unsigned char WalkAnimation[] = {
    ID_WalkUp,   // U
    ID_Walk,     // R
    ID_WalkDown, // D
    ID_Walk,     // L
};

void initPlayer() {

    pushCounter = 0;
    playerDead = false;

    faceDirection = FACE_RIGHT;

    startPlayerAnimation(ID_Stand);
}

// void chooseIdleAnimation() {
//  return;

// #if ENABLE_IDLE_ANIMATION
// #define ANIM_COUNT (sizeof(animID)/2)

//     static const char animID[] = {
//         // ID_Blink,       200,
// //        ID_WipeHair,    120,
// //        ID_Impatient,   112,
//         ID_Turn,        117,
// //        ID_Look,        130,
//         // ID_Shades,      125,
//         // ID_ArmsCrossed, 113,
//     };

//     // suicide skeleton
// //     if (selectResetDelay > DEAD_RESTART_COUCH * 3 / 5) {
// //         if (playerAnimationID != ID_Skeleton2) {
// //             startPlayerAnimation(ID_Skeleton2);
// // //            ADDAUDIO(SFX_DRIP);
// //             SAY(__WORD_GOODBYE);
// //         }
// //     }

// //    else
//      {

//         // choose an idle animation
//         if ((inpt4 & 0x80) && usableSWCHA == 0xFF) {

//             if (playerAnimationID == ID_Skeleton2)
//                 startPlayerAnimation(ID_Stand);             // abort from
//                 suicide

//             else if (playerAnimationID == ID_Stand) {

//                 if (getRandom32() < 0x700000) {
//                     int idle = rangeRandom(ANIM_COUNT) << 1;
//                     if ((rndX & 0xFFF) < animID[idle + 1])
//                         startPlayerAnimation(animID[idle]);
//                 }
//             }
//         }
//     }

// #endif
// }

void grabDoge() {

    totalDogePossible--;

    // if (doges > 0)
    addScore(100); // theCave->dogeValue);

    if (!--doges) {
        exitTrigger = true;
        //        FLASH(0x08, 8);     //open door
        ADDAUDIO(SFX_EXIT);
    } else
        ADDAUDIO(SFX_DOGE2);
}

int playerSlow = 0;
int tapDelay = 0;

bool checkHighPriorityMove(int dir) {

    unsigned char joyBit = joyDirectBit[dir] << 4;
    if (usableSWCHA & joyBit)
        return false;

    if (faceDirectionDef[dir] && faceDirection != faceDirectionDef[dir]) {
        pushCounter = 0; // so we get an animation during turn
        faceDirection = faceDirectionDef[dir];
    }

    unsigned char *meOffset = me + dirOffset[dir];
    unsigned char destType = CharToType[GET(*meOffset)];

    { // no fire button

        //        bool grabbed = false;
        int type = CharToType[GET(*meOffset)];

        if (tapDelay)
            tapDelay--;

        // turn on/off a tap
        if (!tapDelay && type == TYPE_TAP) {
            *meOffset = *meOffset ^ (CH_TAP_1 ^ CH_TAP_0);
            if (*meOffset == CH_TAP_1) {
                // showWater = true;
                // showLava = false;
                if (21 * TRILINES < lavaSurfaceTrixel)
                    lavaSurfaceTrixel = 21 * TRILINES;
            }

            *(meOffset + _1ROW) = (GET(*(meOffset + _1ROW)) == CH_HUB) ? CH_HUB_1 : CH_HUB;

            startPlayerAnimation(tapAnimation[dir]);
            tapDelay = 10;

            waitForNothing = 6;
            //            startPlayerAnimation(ID_Stand);
            handled = true;
        }

        else if (type == TYPE_GRINDER || type == TYPE_GRINDER_1) {
            ADDAUDIO(SFX_EXPLODE_QUIET);
            shakeTime = 5;
        }

        else if (Attribute[destType] & (ATT_BLANK | ATT_PERMEABLE | ATT_GRAB | ATT_EXIT)) {

            // startCharAnimation(TYPE_MELLON_HUSK,
            // AnimateBase[TYPE_MELLON_HUSK]);

            pushCounter = 0;

            if (Attribute[destType] & ATT_BLANK)
                ADDAUDIO(SFX_SPACE);

            else if (destType == TYPE_OUTBOX) {
                *meOffset = CH_EXITBLANK;
                ADDAUDIO(SFX_WHOOSH);
                exitMode = 151;
                waitRelease = true;
            }

#ifdef ENABLE_SWITCH
            else if (destType == TYPE_SWITCH) {
                switchOn = !switchOn;
            }
#endif

            else if (destType == TYPE_FLIP_GRAVITY) {
                nextGravity = -gravity;
                FLASH(0xC5, 3);
                shakeTime = 20;
                ADDAUDIO(SFX_SCORE);
            }

            // else if (destType == TYPE_EASTEREGG) {
            //     FLASH(0x8, 10);
            //     time += 50 << 8;
            //     lockDisplay = false;
            // }

            else if (Attribute[destType] & ATT_GRAB) {
                grabDoge(/* meOffset */);
                //     grabbed = true;
                // if (grabbed)
                nDots(4, playerX, playerY, PARTICLETYPE_SPIRAL, 25, 3, 4, 0x10000);
            }

            playerX += xdir[dir];
            playerY += ydir[dir];

            frameAdjustX = frameAdjustY = 0;

            if (!exitMode) {
                *meOffset = FLAG(CH_MELLON_HUSK);

                if (Attribute[destType] & ATT_DIRT)
                    startCharAnimation(TYPE_MELLON_HUSK, AnimateBase[TYPE_MELLON_HUSK]);
                else
                    startCharAnimation(TYPE_MELLON_HUSK, AnimateBase[TYPE_MELLON_HUSK] + 6);
            }

            // Fix bar stuff

            if (!(inpt4 & 0x80)) {

                int udlr = 0;

                static const unsigned char udlrChar[] = {

                    // 1 = up
                    // 2 = right
                    // 4 = down
                    // 8 = left

                    CH_HORIZONTAL_BAR, // 00
                    CH_VERTICAL_BAR,   // 01 U
                    CH_HORIZONTAL_BAR, // 02 R
                    CH_HUB_1,          // 03 UR
                    CH_VERTICAL_BAR,   // 04 D
                    CH_VERTICAL_BAR,   // 05 UD
                    CH_HUB_1,          // 06 RD
                    CH_HUB_1,          // 07 URD
                    CH_HORIZONTAL_BAR, // 08 L
                    CH_HUB_1,          // 09 UL
                    CH_HORIZONTAL_BAR, // 10 RL
                    CH_HUB_1,          // 11 URL
                    CH_HUB_1,          // 12 LD
                    CH_HUB_1,          // 13 UDL
                    CH_HUB_1,          // 14 RDL
                    CH_HUB_1,          // 15 URDL
                };

                for (int d = 0; d < 4; d++) {
                    if ((ATTRIBUTE_BIT(*(me + dirOffset[d]), ATT_PIPE)) ||
                        GET(*(me + dirOffset[d])) == CH_MELLON_HUSK)
                        udlr |= 1 << d;
                }

                *me = udlrChar[udlr];

                // if (*me == CH_HUB_1 && Attribute[CharToType[GET(*(me - _BOARD_COLS))]] &
                // ATT_BLANK)
                //     *(me - _BOARD_COLS) = CH_TAP_0;

                showTool = true;
            }

            else
                *me = FLAG(CH_DUST_ROCK_0);

            playerSlow = 0;
            if (!autoMoveFrameCount &&
                ((Attribute[destType] & (ATT_DIRT | ATT_WATERFLOW)) || destType == TYPE_LAVA)) {

                playerSlow = ((Attribute[destType] & ATT_WATERFLOW)) ? 2 : 1;

                ADDAUDIO(SFX_DIRT);
                // dirtFlag = true;
                startCharAnimation(TYPE_MELLON_HUSK, AnimateBase[TYPE_MELLON_HUSK]);

                nDots(6, playerX, playerY, 2, 25, 2, 5, 0x10000);
            }

            int dir2 = (gravity < 0) ? dir ^ 2 : dir;

            if (playerAnimationID != WalkAnimation[dir2])
                startPlayerAnimation(WalkAnimation[dir2]);

            if (!autoMoveFrameCount) {

                autoMoveFrameCount = ((gameSpeed * 2) << playerSlow);

                autoMoveX = autoMoveDeltaX = animDeltaX[dir] >> playerSlow;
                autoMoveY = autoMoveDeltaY = -(ydir[dir] * PIECE_DEPTH) >> playerSlow;
            }

            handled = true;
        }
    }

    if (handled) {
        bufferedSWCHA |= joyBit;
        usableSWCHA |= joyBit;
        inhibitSWCHA = joyBit;
    }

    return handled;
}

bool checkLowPriorityMove(int dir) {

    unsigned char joyBit = joyDirectBit[dir] << 4;
    if (usableSWCHA & joyBit) {
        return false;
    }

    int offset = dirOffset[dir];
    unsigned char *meOffset = me + offset;
    unsigned char destType = CharToType[GET(*meOffset)];

#if 1 // disable push
    if (/*faceDirectionDef[dir] && */ (Attribute[destType] & (ATT_MINE | ATT_PIPE))) {

        if (++pushCounter > 1) {

            int anim = mineAnimation[dir];
            if (!(dir & 1) && gravity < 0)
                anim ^= ID_MineDown ^ ID_MineUp;

            if (playerAnimationID != anim)
                startPlayerAnimation(anim);
        } else {
            ADDAUDIO(SFX_SPACE);
            //            startPlayerAnimation(ID_Locked);          // works
            //            nicely as start of push
        }

        if (pushCounter > 10) {

            if (Attribute[destType] & ATT_MINE) {
                addScore(VALUE_BREAK_GEODE);

                //            pushCounter = 2;
                *meOffset = ATTRIBUTE_BIT(*meOffset, ATT_GEODOGE) ? FLAG(CH_CONVERT_GEODE_TO_DOGE)
                                                                  : CH_DUST_0;

                surroundingConglomerate(playerX + xdir[dir], playerY + ydir[dir]);
            }

            else {
                *meOffset = FLAG(CH_CONVERT_PIPE);
            }

            // fixSurroundingConglomerates(meOffset);

            waitForNothing = 6;
            startPlayerAnimation(ID_Stand);

            pushCounter = 0;

            // extern int dogeBlockCount;
            // extern int cumulativeBlockCount;
            // dogeBlockCount++;
            // cumulativeBlockCount++;

            if (faceDirection > 0) {
                me += 2;
                boardCol += 2; // SKIP processing it!
            }

            ADDAUDIO(SFX_PUSH);
        }

        handled = true;
    }

    else

#endif
        startPlayerAnimation(ID_Locked);

    return handled;
}

void bubbles(int count, int dripX, int dripY, int age, int speed) {
    for (int i = 0; i < count; i++) {
        int idx = sphereDot(dripX, dripY, PARTICLETYPE_BUBBLE, age);
        if (idx >= 0) {
            // particleSpeedY[idx] = -0x2800 - rangeRandom(0x2800);
            // particleSpeedX[idx] >>= 4;

            particleDirection[idx] = 128 + rangeRandom(64) - 32;
        }
    }
}

void movePlayer(unsigned char *me) {

    handled = false;

    // breath bubbles
    static int breath;
    if (showWater && playerY * TRILINES > lavaSurfaceTrixel) {

        breath++;
        if (!(breath & 35) && (breath & 63) < 21) {
            int x = (playerX * 5) + 3;
            int y = (playerY * TRILINES) + 4;
            bubbles(1, x - 1, y - 2, 400, 0x1000);
            ADDAUDIO(SFX_BUBBLER);
        }
    }

    else
        killAudio(SFX_BUBBLER);

    static unsigned char lastUsableSWCHA = 0;

    if (usableSWCHA != lastUsableSWCHA) {
        waitForNothing = 0;
        // tapDelay = 0;
    }

    if (waitForNothing) {
        --waitForNothing;
        usableSWCHA = 0xFF;
        return;
    }

    if (autoMoveFrameCount)
        return;

    lastUsableSWCHA = usableSWCHA;

    for (int dir = 0; dir < 4; dir++)
        if (checkHighPriorityMove(dir))
            return;

    for (int dir = 0; dir < 4 && !handled; dir++)
        if (checkLowPriorityMove(dir))
            return;

    // switch back to standing facing forward, turning if required

    if (!autoMoveFrameCount) {

        if (playerAnimationID == ID_WalkUp || playerAnimationID == ID_MineUp)
            startPlayerAnimation(ID_StandUp);

        else if (playerAnimationID == ID_Walk || playerAnimationID == ID_Push)
            startPlayerAnimation(ID_StandLR);

        else if (playerAnimationID == ID_WalkDown || playerAnimationID == ID_MineDown)
            startPlayerAnimation(ID_Stand);
    }

    // after all movement checked, anything falling on player?
    // potential bug - if you're pushing and something falls on you

    if (Attribute[CharToType[*(me - _1ROW * gravity)]] & ATT_CRUSHES) {
        //        SAY(__WORD_WATCHOUT);
        startPlayerAnimation(ID_Die);
        return;
    }

    pushCounter = 0;
    idleTimer++;

    // if (!autoMoveFrameCount)
    //     chooseIdleAnimation();
}

// EOF