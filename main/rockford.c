#include "defines_cdfj.h"
#include "defines.h"
#include "main.h"

#include "amoeba.h"
#include "animations.h"
#include "atarivox.h"
#include "attribute.h"
#include "colour.h"
#include "decodecaves.h"
#include "joystick.h"
#include "player.h"
#include "rockford.h"
#include "random.h"
#include "score.h"
#include "sound.h"


#define PLAYER_BORED        100


int rockfordX;
int rockfordY;
int frameAdjustX;
int frameAdjustY;
unsigned int pushCounter;
enum FaceDirection rockfordFaceDirection;
bool rockfordDead;
// bool rockfordDeadRelease;

static bool handled;
static unsigned int playerIdleTime;


enum DIR {
    DIR_UP = 1,
    DIR_DOWN = 2,
    DIR_LEFT = 4,
    DIR_RIGHT = 8,
};

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

const signed char faceDirection[] = {
    FACE_LEFT,
    FACE_RIGHT,
    0,
    0,
};

const signed char animDeltaX[] = {
    -20,-20,0,0,
};

const signed char animDeltaY[] = {
    0,0,PIECE_DEPTH,-PIECE_DEPTH,
};

const char newSnatch[] = {
    ID_Snatch,
    ID_Snatch,
    ID_SnatchUp,
    ID_SnatchDown,
};



void initRockford() {

    pushCounter =
    playerIdleTime = 0;

    rockfordDead = false;

    rockfordFaceDirection = FACE_RIGHT;

    startPlayerAnimation(ID_Stand);

}



void chooseIdleAnimation() {
 return;

#if ENABLE_IDLE_ANIMATION
#define ANIM_COUNT (sizeof(animID)/2)

    static const char animID[] = {
        ID_Blink,       200, 
        ID_WipeHair,    120,
        ID_Impatient,   112, 
        ID_Turn,        117, 
//        ID_Look,        130, 
        ID_Shades,      125, 
        ID_ArmsCrossed, 113,
    };

    // suicide skeleton
//     if (selectResetDelay > DEAD_RESTART_COUCH * 3 / 5) {
//         if (playerAnimationID != ID_Skeleton2) {
//             startPlayerAnimation(ID_Skeleton2);
// //            ADDAUDIO(SFX_DRIP);
//             SAY(__WORD_GOODBYE);
//         }
//     }

//    else
     {

        // choose an idle animation
        if ((inpt4 & 0x80) && usableSWCHA == 0xFF) {

            if (playerAnimationID == ID_Skeleton2)
                startPlayerAnimation(ID_Stand);             // abort from suicide

            if (playerAnimationID == ID_Stand) {

                if (playerIdleTime++ > PLAYER_BORED) {
                    startPlayerAnimation(ID_Talk);   
                    playerIdleTime = 0;
                }

                else if (getRandom32() < 0x700000) {
                    int idle = rangeRandom(ANIM_COUNT) << 1;
                    if ((rndX & 0xFFF) < animID[idle + 1])
                        startPlayerAnimation(animID[idle]);   
                }
            }
        }
    }

#endif
}



void grabDoge(unsigned char *where) {

    // TODO
    *where = CH_DOGE_GRAB | FLAG_THISFRAME;

    startCharAnimation(TYPE_GRAB, AnimateBase[TYPE_GRAB]);

    totalDiamondsPossible--;

    // if (diamonds > 0)
        addScore(theCave->diamondValue);

    if (!--diamonds) {
        exitTrigger = true;
//        FLASH(0x08, 8);     //open door
        ADDAUDIO(SFX_EXIT);
    }
    else
        ADDAUDIO(SFX_DIAMOND2);
}



bool checkHighPriorityMove(int dir, unsigned char blanker) {

    unsigned char joyBit = joyDirectBit[dir] << 4;
    if (usableSWCHA & joyBit)
        return false;

    if (faceDirection[dir] && rockfordFaceDirection != faceDirection[dir]) {
        pushCounter = 0;        // so we get an animation during turn
        rockfordFaceDirection = faceDirection[dir];
    }


    unsigned char *thisOffset = this + dirOffset[dir];
    unsigned char destType = CharToType[(*thisOffset) & 0x7F]; 
    bool dirtFlag = false;

    if (!(inpt4 & 0x80)) {        // fire button

        triggerPressCounter = 999;

        if (destType == TYPE_DOGE_FALLING && dir < 2) {
            grabDoge(thisOffset);
            startPlayerAnimation(newSnatch[dir]);
            handled = true;
        }

        else if (Attribute[destType] & (ATT_DIRT | ATT_GRAB)) {

            if (Attribute[destType] & ATT_GRAB)
                grabDoge(thisOffset);

            else {
                ADDAUDIO(SFX_DIRT);
                *thisOffset = CH_DUST_0 | FLAG_THISFRAME;
            }

            startPlayerAnimation(newSnatch[dir]);
            handled = true;
        }
        else
            startPlayerAnimation(ID_Locked);
    }

    else {        // no fire button

        bool grabbed = false;

        if (Attribute[destType] & (ATT_BLANK | ATT_PERMEABLE | ATT_GRAB | ATT_EXIT)) {
        
                //startCharAnimation(TYPE_ROCKFORD, AnimateBase[TYPE_ROCKFORD]);

            pushCounter = 0;

            if (Attribute[destType] & ATT_DIRT) {
                ADDAUDIO(SFX_DIRT);
                dirtFlag = true;
                startCharAnimation(TYPE_ROCKFORD, AnimateBase[TYPE_ROCKFORD]);
            }

            else if (Attribute[destType] & ATT_BLANK)
                ADDAUDIO(SFX_SPACE);

            else if (destType == TYPE_OUTBOX) {
                *thisOffset = CH_EXITBLANK;
                ADDAUDIO(SFX_WHOOSH);
                exitMode = 151;
                waitRelease = true;
                canPlay[level] |= 1 << (cave + 1);


            }

            else if (destType == TYPE_SWITCH) {
                switchOn = !switchOn;
            }

            // else if (destType == TYPE_EASTEREGG) {
            //     FLASH(0x8, 10);
            //     time += 50 << 8;
            //     lockDisplay = false;
            // }

            else if (Attribute[destType] & ATT_GRAB) {
                grabDoge(thisOffset);
                grabbed = true;

            }

            rockfordX += xInc[joyDirectBit[dir]];
            rockfordY += yInc[joyDirectBit[dir]];

            if (grabbed)
                for (int i = 0; i < 8; i++)
                    sphereDot(rockfordX, rockfordY, 2, -50, 2, 4);



            frameAdjustX = frameAdjustY = 0;

            if (!exitMode) {
                *thisOffset = CH_ROCKFORD | FLAG_THISFRAME;

                if (Attribute[destType] & ATT_DIRT)
                    startCharAnimation(TYPE_ROCKFORD, AnimateBase[TYPE_ROCKFORD] + 8);

                else if (Attribute[destType] & ATT_GRAB)
                    startCharAnimation(TYPE_ROCKFORD, AnimateBase[TYPE_ROCKFORD] + 2);

                else
                    startCharAnimation(TYPE_ROCKFORD, AnimateBase[TYPE_ROCKFORD]);
            }





            *this = dirtFlag ? CH_DUST_0 | FLAG_THISFRAME : blanker | FLAG_THISFRAME;


            const int WalkAnimation[] = {
                ID_Walk,        // L
                ID_Walk,        // R
                ID_WalkUp,      // U
                ID_WalkDown,    // D
            };

            if (playerAnimationID != WalkAnimation[dir])
                startPlayerAnimation(WalkAnimation[dir]);
            autoMoveFrameCount = gameSpeed;


            autoMoveX = autoMoveDeltaX = animDeltaX[dir];
            autoMoveY = autoMoveDeltaY = animDeltaY[dir];

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


bool checkLowPriorityMove(int dir, int blanker) {


    unsigned char joyBit = joyDirectBit[dir] << 4;
    if (usableSWCHA & joyBit) {
        return false;
    }


    int offset = dirOffset[dir];
    unsigned char *thisOffset = this + offset;
    unsigned char destType = CharToType[(*thisOffset) & 0x7F]; 

    #if 1  // disable push
    if (faceDirection[dir] && (Attribute[destType] & ATT_PUSH)
        && !(Attribute[CharToType[(*(thisOffset + 40)) & 0x7F]] & ATT_BLANK)) {

        
        if (++pushCounter > 1) {
//            *thisOffset = CH_BOULDER_SHAKE | FLAG_THISFRAME; //((rockfordFaceDirection > 0) ? FLAG_THISFRAME : 0);
            if (playerAnimationID != ID_Push)
                startPlayerAnimation(ID_Push);
        }
        else {
            ADDAUDIO(SFX_SPACE);    
//            startPlayerAnimation(ID_Locked);          // works nicely as start of push
        }

        if (pushCounter > 6) {
//            pushCounter = 2;
            *thisOffset = Attribute[CharToType[GET(*thisOffset)]] & ATT_BOULDER_DOGE ? CH_DOGE_CONVERT : CH_DUST_0;

            waitForNothing = 4;
            pushCounter = 0;

            extern int dogeBlockCount;
            extern int cumulativeBlockCount;
            dogeBlockCount++;
            cumulativeBlockCount++;

            if (rockfordFaceDirection > 0) {
                this += 2;
                boardCol += 2;                      // SKIP processing it!
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
        colourn = colourn+1;
        if (colourn > 4)
            colourn = 0;
    }

    if (JOY0_LEFT) {
        colourn = colourn-1;
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
    rainbow = (!(colr[2] |colr[3]));

    if (!rainbow)
#endif
        setBackgroundPalette(colr);
}
#endif



void moveRockford(unsigned char *this, unsigned char blanker) {

    handled = false;

    // if (SWCHA == 0xFF) {
    //     waitForNothing = 0;
    //     usableSWCHA = 0xFF;
    // }

    if (waitForNothing) {
        --waitForNothing;
        return;
    }
        
    
    for (int dir = 0; dir < 4; dir++ )
        if (checkHighPriorityMove(dir, blanker))
            return;

    for (int dir = 0; dir < 4 && !handled; dir++)
        if (checkLowPriorityMove(dir, blanker))
            return;


    // switch back to standing facing forward, turning if required

    if (!autoMoveFrameCount) {

        if (playerAnimationID == ID_WalkUp)
            startPlayerAnimation(ID_StandUp);

        else if (playerAnimationID == ID_Walk)
            startPlayerAnimation(ID_StandLR);
        
        else if (playerAnimationID == ID_WalkDown)
            startPlayerAnimation(ID_Stand);
    }


    // after all movement checked, anything falling on player?
    // potential bug - if you're pushing and something falls on you
    
    if (*(this - 40) == (CH_DOGE_FALLING | FLAG_THISFRAME)
        || *(this - 40) == (CH_BOULDER_FALLING | FLAG_THISFRAME)) {
//        SAY(__WORD_WATCHOUT);
        startPlayerAnimation(ID_Die);
        return;
    }

    pushCounter = 0;
    idleTimer++;

    if (!autoMoveFrameCount)
        chooseIdleAnimation();
}

//EOF