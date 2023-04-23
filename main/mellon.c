#include "defines.h"
#include "defines_cdfj.h"
#include "main.h"

#include "animations.h"
#include "atarivox.h"
#include "attribute.h"
#include "colour.h"
#include "decodecaves.h"
#include "joystick.h"
#include "mellon.h"
#include "player.h"
#include "random.h"
#include "score.h"
#include "scroll.h"
#include "sound.h"

// #define PLAYER_BORED        100

int playerX;
int playerY;
int frameAdjustX;
int frameAdjustY;
unsigned int pushCounter;
enum FaceDirectionX faceDirection;
bool playerDead;
// bool playerDeadRelease;

static bool handled;

enum DIR {
    DIR_UP = 1,
    DIR_DOWN = 2,
    DIR_LEFT = 4,
    DIR_RIGHT = 8,
};

const int off[] = {-40, 1, 40, -1};

const signed char xInc[] = {

    // RLDU
    0,  // 0000
    0,  // 0001
    0,  // 0010
    0,  // 0011
    -1, // 0100
    -1, // 0101
    -1, // 0110
    0,  // 0111
    1,  // 1000
    1,  // 1001
    1,  // 1010
    0,  // 1011
    0,  // 1100
    0,  // 1101
    0,  // 1110
    0,  // 1111
};

const signed char yInc[] = {

    // RLDU
    0,  // 0000
    -1, // 0001
    1,  // 0010
    0,  // 0011
    0,  // 0100
    -1, // 0101
    1,  // 0110
    0,  // 0111
    0,  // 1000
    -1, // 1001
    1,  // 1010
    0,  // 1011
    0,  // 1100
    0,  // 1101
    0,  // 1110
    0,  // 1111
};

const unsigned char joyDirectBit[] = {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
};

const signed char faceDirectionDef[] = {
    FACE_LEFT,
    FACE_RIGHT,
    FACE_UP,
    FACE_DOWN,
};

const signed char animDeltaX[] = {
    -20,
    -20,
    0,
    0,
};

const signed char animDeltaY[] = {
    0,
    0,
    PIECE_DEPTH,
    -PIECE_DEPTH,
};

// const char newSnatch[] = {
//     ID_Snatch,
//     ID_Snatch,
//     ID_SnatchUp,
//     ID_SnatchDown,
// };

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

void grabDoge(unsigned char *where) {

    // TODO
    *where = CH_DOGE_GRAB | FLAG_THISFRAME;

    startCharAnimation(TYPE_GRAB, AnimateBase[TYPE_GRAB]);

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

bool checkHighPriorityMove(int dir) {

    unsigned char joyBit = joyDirectBit[dir] << 4;
    if (usableSWCHA & joyBit)
        return false;

    if (faceDirectionDef[dir] && faceDirection != faceDirectionDef[dir]) {
        pushCounter = 0; // so we get an animation during turn
        faceDirection = faceDirectionDef[dir];
    }

    unsigned char *thissOffset = thiss + dirOffset[dir];
    unsigned char destType = CharToType[GET(*thissOffset)];
    // bool dirtFlag = false;

    //    if (!waitRelease && !(inpt4 & 0x80)) {        // fire button

    // extern int shakeTime;
    //     shakeTime += 10;

    //        triggerPressCounter = 999;

    // if (destType == TYPE_DOGE_FALLING && dir < 2) {
    //     grabDoge(thisOffset);
    //     startPlayerAnimation(newSnatch[dir]);
    //     handled = true;
    // }
    // else

    // if (Attribute[destType] & (ATT_DIRT | ATT_GRAB)) {

    //     if (Attribute[destType] & ATT_GRAB)
    //         grabDoge(thisOffset);

    //     else {
    //         ADDAUDIO(SFX_DIRT);
    //         *thissOffset = CH_DUST_0 | FLAG_THISFRAME;
    //     }

    //     startPlayerAnimation(newSnatch[dir]);
    //     handled = true;
    // }
    // else
    //            startPlayerAnimation(ID_Locked);
    //   }

    //   else
    { // no fire button

        bool grabbed = false;
        int type = CharToType[GET(*thissOffset)];

        // turn on/off a tap
        if (type == TYPE_TAP) {
            *thissOffset = *thissOffset ^ (CH_TAP_1 ^ CH_TAP_0);
            if (*thissOffset == CH_TAP_1) {
                showWater = true;
                if (21 * PIECE_DEPTH / 3 < lavaSurface)
                    lavaSurface = 21 * PIECE_DEPTH / 3;
            }

            *(thissOffset + 40) =
                (GET(*(thissOffset + 40)) == CH_HUB) ? CH_HUB_1 : CH_HUB;
            startPlayerAnimation(ID_Push);
            handled = true;
        }

        else if (type == TYPE_GRINDER || type == TYPE_GRINDER_1) {
            ADDAUDIO(SFX_EXPLODE_QUIET);
            shakeTime = 5;
        }

        else if (Attribute[destType] &
                 (ATT_BLANK | ATT_PERMEABLE | ATT_GRAB | ATT_EXIT)) {

            // startCharAnimation(TYPE_MELLON_HUSK,
            // AnimateBase[TYPE_MELLON_HUSK]);

            pushCounter = 0;

            if (Attribute[destType] & ATT_BLANK)
                ADDAUDIO(SFX_SPACE);

            else if (destType == TYPE_OUTBOX) {
                *thissOffset = CH_EXITBLANK;
                ADDAUDIO(SFX_WHOOSH);
                exitMode = 151;
                waitRelease = true;
                canPlay[level] |= 1 << (cave + 1);
            }

            else if (destType == TYPE_SWITCH) {
                switchOn = !switchOn;
            }

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
                grabDoge(thissOffset);
                grabbed = true;
            }

            playerX += xInc[joyDirectBit[dir]];
            playerY += yInc[joyDirectBit[dir]];

            if (grabbed)
                nDots(4, playerX, playerY, 2, -50, 3, 4, 0x10000);

            frameAdjustX = frameAdjustY = 0;

            if (!exitMode) {
                *thissOffset = CH_MELLON_HUSK | FLAG_THISFRAME;

                if (Attribute[destType] & ATT_DIRT)
                    startCharAnimation(TYPE_MELLON_HUSK,
                                       AnimateBase[TYPE_MELLON_HUSK] + 8);

                else if (Attribute[destType] & ATT_GRAB)
                    startCharAnimation(TYPE_MELLON_HUSK,
                                       AnimateBase[TYPE_MELLON_HUSK] + 2);

                else
                    startCharAnimation(TYPE_MELLON_HUSK,
                                       AnimateBase[TYPE_MELLON_HUSK]);
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
                    if ((ATTRIBUTE_BIT(*(thiss + off[d]), ATT_PIPE)) ||
                        GET(*(thiss + off[d])) == CH_MELLON_HUSK)
                        udlr |= 1 << d;
                }

                *thiss = udlrChar[udlr];

                if (*thiss == CH_HUB_1 &&
                    Attribute[CharToType[GET(*(thiss - 40))]] & ATT_BLANK)
                    *(thiss - 40) = CH_TAP_0;

            }

            else
                *thiss = CH_DUST_0 | FLAG_THISFRAME;

            playerSlow = 0;
            if (!autoMoveFrameCount &&
                ((Attribute[destType] & ATT_DIRT) || destType == TYPE_LAVA)) {

                playerSlow = 1;
                ADDAUDIO(SFX_DIRT);
                // dirtFlag = true;
                startCharAnimation(TYPE_MELLON_HUSK,
                                   AnimateBase[TYPE_MELLON_HUSK]);

                nDots(6, playerX, playerY, 2, -50, 3, 4, 0x10000);
            }

            const int WalkAnimation[] = {
                ID_Walk,     // L
                ID_Walk,     // R
                ID_WalkUp,   // U
                ID_WalkDown, // D
            };

            int dir2 = dir;
            if (gravity < 0 && dir2 > 1)
                dir2 ^= 1;

            if (playerAnimationID != WalkAnimation[dir2])
                startPlayerAnimation(WalkAnimation[dir2]);

            if (!autoMoveFrameCount) {

                autoMoveFrameCount = ((gameSpeed * 2) << playerSlow);

                autoMoveX = autoMoveDeltaX = animDeltaX[dir] >> playerSlow;
                autoMoveY = autoMoveDeltaY = animDeltaY[dir] >> playerSlow;
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

int waitForNothing;

const unsigned char mineAnimation[4] = {
    ID_Push,
    ID_Push,
    ID_MineUp,
    ID_MineDown,
};

bool checkLowPriorityMove(int dir) {

    unsigned char joyBit = joyDirectBit[dir] << 4;
    if (usableSWCHA & joyBit) {
        return false;
    }

    int offset = dirOffset[dir];
    unsigned char *thissOffset = thiss + offset;
    unsigned char destType = CharToType[GET(*thissOffset)];

#if 1 // disable push
    if (faceDirectionDef[dir] && (Attribute[destType] & ATT_MINE)) {

        if (++pushCounter > 1) {
            int anim = mineAnimation[dir];
            if (dir > 1 && gravity < 0)
                anim ^= ID_MineDown ^ ID_MineUp;

            if (playerAnimationID != anim)
                startPlayerAnimation(anim);
        } else {
            ADDAUDIO(SFX_SPACE);
            //            startPlayerAnimation(ID_Locked);          // works
            //            nicely as start of push
        }

        if (pushCounter > 6) {
            //            pushCounter = 2;
            *thissOffset = ATTRIBUTE_BIT(*thissOffset, ATT_ROCK_DOGE)
                               ? CH_DOGE_CONVERT | FLAG_THISFRAME
                               : CH_DUST_0;

            waitForNothing = 2;
            pushCounter = 0;

            extern int dogeBlockCount;
            extern int cumulativeBlockCount;
            dogeBlockCount++;
            cumulativeBlockCount++;

            if (faceDirection > 0) {
                thiss += 2;
                boardCol += 2; // SKIP processing it!
            }

            ADDAUDIO(SFX_PUSH);

            for (int i = 0; i < 4; i++)
                conglomerate(thissOffset + dirOffset[i],
                             (ATT_ROCK_DOGE | ATT_GRAB));
        }

        handled = true;
    }

    else

#endif
        startPlayerAnimation(ID_Locked);

    return handled;
}

#if COLSELECT
int colourn = 0;
extern unsigned char colr[5];
static bool letgo = true;

void colourAdjust() {

    if (SWCHA != 0xFF && letgo)
        return;
    letgo = false;

    if (SWCHA != 0xFF)
        letgo = true;

    if (JOY0_RIGHT) {
        colourn = colourn + 1;
        if (colourn > 4)
            colourn = 0;
    }

    if (JOY0_LEFT) {
        colourn = colourn - 1;
        if (colourn < 0)
            colourn = 4;
    }

    if (JOY0_UP) {

        if (colourn == 4) {
            colr[4] = (colr[4] + 1) & 0xF;
            currentPalette = colr[4];
            loadPalette();
        }

        else {
            colr[colourn] += 2;
            if (mm_tv_type == SECAM)
                colr[colourn] &= 0xF;
            if (colourn == 2)
                colr[3] = colr[2];
        }
    }

    if (JOY0_DOWN) {

        if (colourn == 4) {
            colr[4] = (colr[4] - 1) & 0xF;
            currentPalette = colr[4];
            loadPalette();
        }

        else {
            colr[colourn] -= 2;
            if (mm_tv_type == SECAM)
                colr[colourn] &= 0xF;
            if (colourn == 2)
                colr[3] = colr[2];
        }
    }

#if ENABLE_RAINBOW
    rainbow = (!(colr[2] | colr[3]));

    if (!rainbow)
#endif
        setBackgroundPalette(colr);
}
#endif

// #define DOTY 0x10000

void bubbles(int count, int dripX, int dripY, int age, int speed) {
    for (int i = 0; i < count; i++) {
        int idx = sphereDot(dripX << 8, dripY << 16, 1, age, speed);
        if (idx >= 0) {
            rainSpeedY[idx] =
                -0x2800 -
                rangeRandom(0x2800); //- ((0x4000 + ((int)(rangeRandom(DOTY
                                     //>> 1))) * 0x8000) >> 16);
            rainSpeedX[idx] >>= 2;
            //            rainX[idx] += rangeRandom(3) - 1;
        }
    }
}

void movePlayer(unsigned char *thiss) {

    handled = false;

    // lasso
    // if (!(inpt4 & 0x80)) {        // fire button
    //     // shakeTime += 10;

    //     if (Attribute[CharToType[GET(*(thiss + 1))]] & ATT_BLANK)
    //         *(thiss + 1) = CH_HORIZ_ZAP_0 | FLAG_THISFRAME;

    // }

    // breath bubbles
    static int breath;
    if (showWater && playerY * PIECE_DEPTH / 3 > lavaSurface) {

        ADDAUDIO(SFX_BUBBLER);

        breath++;
        if (!(breath & 35) && (breath & 63) < 21) {
            int x = (playerX * 5) + 3;
            int y = (playerY * (PIECE_DEPTH / 3)) + 4;
            bubbles(4, x, y, 200, 0x80000);
        }
    }

    else
        killAudio(SFX_BUBBLER);

    static unsigned char lastUsableSWCHA = 0;

    if (usableSWCHA != lastUsableSWCHA)
        waitForNothing = 0;

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

        else if (playerAnimationID == ID_WalkDown ||
                 playerAnimationID == ID_MineDown)
            startPlayerAnimation(ID_Stand);
    }

    // after all movement checked, anything falling on player?
    // potential bug - if you're pushing and something falls on you

    if (*(thiss - 40) == (CH_DOGE_FALLING | FLAG_THISFRAME) ||
        *(thiss - 40) == (CH_ROCK_FALLING | FLAG_THISFRAME)) {
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