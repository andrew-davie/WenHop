#include <stdbool.h>

#include "defines.h"
#include "defines_cdfj.h"
// #include "defines_from_dasm_for_c.h"

#include "main.h"

#include "animations.h"
#include "atarivox.h"
#include "attribute.h"
#include "cavedata.h"
#include "characterset.h"
#include "colour.h"
#include "decodecaves.h"
#include "drawplayer.h"
#include "drawscreen.h"
#include "joystick.h"
#include "mellon.h"
#include "menu.h"
#include "player.h"
#include "random.h"
#include "score.h"
#include "scroll.h"
#include "sound.h"
#include "swipeCircle.h"
#include "tools.h"
#include "wyrm.h"

#if WORST_TIMING
int worstEver = 0;
int worstEverCreature = -1;
#endif

int togt;
int pulsePlayerColour;
int waterDir = 0;
int conveyorDirection;

unsigned char creature;
unsigned int type;

// static int destroy = 0;
// int destroyInc = 10;

////////////////////////////////////////////////////////////////////////////////
// CONFIGURABLE UX

#define DEAD_RESTART                                                                               \
    1 // 20     /* # frames to hold trigger after loss of life, to start next
      // life
      // */
// #define MAX_PEBBLES        400     /* # random pebbles to put in dirt */

// Delays on RESET and SELECT are to allow non-ambiguous press of SELECT+RESET
// for suicide

#define RESET_DELAY 20  /* # frames to hold RESET before it is detected */
#define SELECT_DELAY 10 /* # frames to hold SELECT before it is detected */

////////////////////////////////////////////////////////////////////////////////

const signed char dirOffset[] = {-_1ROW, 1, _1ROW, -1, 0};
const signed char xdir[] = {0, 1, 0, -1, 0};
const signed char ydir[] = {-1, 0, 1, 0, 0};

int lavaSurfaceTrixel;
bool showWater;
bool showLava;

int boardRow;
int boardCol;

int gravity;
int nextGravity;

int canPlay[5];

int explodeCount;

bool showTool;

bool lockDisplay;
bool rageQuit;
unsigned char *me;
unsigned char inpt4;
unsigned char swcha;
int millingTime; // negative = expired
int doges;
int time;
int level;

bool waitRelease;

#ifdef ENABLE_SWITCH
bool switchOn;
#endif

unsigned char mm_tv_type; // 0 = NTSC, 1 = PAL, 2 = PAL-60, 3 = SECAM... start @
                          // NTSC always
// unsigned char autoTVType;
bool exitTrigger;
unsigned int idleTimer;
unsigned int sparkleTimer;
bool showingWords;

int exitMode;
int frameCounter;
int selectorCounter;
int activated;

static const int isActive[] = {

    ATT_PHASE1 | ATT_PHASE2, // 0
    ATT_PHASE1 | ATT_PHASE4, // 1
    ATT_PHASE1 | ATT_PHASE2, // 2
    ATT_PHASE1,              // 3
};

unsigned int availableIdleTime;

bool invincible;

int wordColour;
int spacing;
int perfectTimer;

int gameFrame;
int gameSpeed;
// enum DisplayMode displayMode;
// enum DisplayMode lastDisplayMode;
unsigned int triggerPressCounter;
static unsigned int triggerOffCounter;

// int dogeBlockCount;
// int cumulativeBlockCount;

int lives;
// int selectResetDelay;;
int resetDelay;

#if ENABLE_DEBUG
static int selectDelay;
#endif

unsigned int currentPalette;

unsigned int cave;
bool caveCompleted;
unsigned char bufferedSWCHA;
unsigned int usableSWCHA;
unsigned int inhibitSWCHA;

#if ENABLE_SHAKE
int shakeX, shakeY;
int shakeTime;
#endif

// COMPILE-TIME REVERSE BITS IN BYTE
#define RVS(a)                                                                                     \
    (((((a) >> 0) & 1) << 7) | ((((a) >> 1) & 1) << 6) | ((((a) >> 2) & 1) << 5) |                 \
     ((((a) >> 3) & 1) << 4) | ((((a) >> 4) & 1) << 3) | ((((a) >> 5) & 1) << 2) |                 \
     ((((a) >> 6) & 1) << 1) | ((((a) >> 7) & 1) << 0))

#define P0(a) RVS(a)
#define P1(a) P0(a), P0(a + 1)
#define P2(a) P1(a), P1(a + 2)
#define P3(a) P2(a), P2(a + 4)
#define P4(a) P3(a), P3(a + 8)
#define P5(a) P4(a), P4(a + 16)
#define P6(a) P5(a), P5(a + 32)
#define P7(a) P6(a), P6(a + 64)
#define P8(a) P7(a), P7(a + 128)

// Want to call RVS(n) for 0-255 values. The weird #defines above allows a
// single-call It's effectively a recursive power-of-two call of the base RVS
// macro

const unsigned char reverseBits[] = {
    P8(0),
};

// TODO: cater for gravity in flag setting
unsigned char thisFrame[] = {0, FLAG_THISFRAME, FLAG_THISFRAME, 0};

enum SCHEDULE gameSchedule;

// Function Prototypes

void GameOverscan();
void GameVerticalBlank();
void initNextLife();
void SystemReset();
void setupBoard();
void processCharAnimations();

void (*const runFunc[])() = {

    SystemReset,       // _FN_SYSTEM_RESET
    MenuOverscan,      // _FN_MENU_OS
    MenuVerticalBlank, // _FN_MENU_VB
    SchedulerMenu,     // _FN_MENU_IDLE
    initNextLife,      // _FN_INIT_GAME_KERNEL
    GameOverscan,      // _FN_GAME_OS
    GameVerticalBlank, // _FN_GAME_VB
    Scheduler,         // _FN_GAME_IDLE
};

int main() { // <-- 6507/ARM interfaced here!

    (*runFunc[RUN_FUNC])();
    return 0;
}

#if WORST_TIMING
int worst[TYPE_MAX];
#endif

void SystemReset() {

    initRandom();
    initAudio();
    initMenuDatastreams();
    initCharVector();

    for (int i = 0; i <= 34; i++)
        QINC[i] = 0x100; // data stream increments -> 1.0

    initKernel(KERNEL_COPYRIGHT);

    rageQuit = false;
    ARENA_COLOUR = 0;

    enableICC = LEFT_DIFFICULTY_A;

    for (int i = 0; i < 5; i++)

#if ENABLE_DEBUG
        canPlay[i] = 0xFFFFFFFF;
#else
        canPlay[i] = 0b00010001000100010001000100010001;
#endif
}

bool visible(int col, int row) {

    int y = (scrollY /* + shakeY*/) >> 16;
    int deltaY = row * TRILINES - y;

    if (deltaY <= -TRILINES || deltaY >= _ARENA_SCANLINES / 3)
        return false;

    int x = ((scrollX /* + shakeX*/) * 5) >> 16;
    int deltaX = col * 5 - x;
    if ((unsigned int)/*deltaX < -4 ||*/ deltaX >= 40)
        return false;

    return true;
}

int sphereDot(int dotX, int dotY, int type, int age, int speed) {

    int whichDrop = -1;

    int col = dotX - ((scrollX * 5) >> 16);
    if (col >= 0 && col < 40 /*pixels*/) {

        int line = dotY - (scrollY >> 16);
        if (line >= 0 && line < (_ARENA_SCANLINES / 3 - 1)) {

            int oldest = 0;
            while (++whichDrop < PARTICLE_COUNT && particleAge[whichDrop])
                if (particleAge[whichDrop] < particleAge[oldest])
                    oldest = whichDrop;

            if (whichDrop == PARTICLE_COUNT)
                whichDrop = oldest;

            particleType[whichDrop] = type;
            particleX[whichDrop] = dotX << 8;

            particleY[whichDrop] = dotY << 16;
            particleSpeedX[whichDrop] = ((int)((rangeRandom(128) - 64)) * speed) >> 16;
            particleSpeedY[whichDrop] = ((int)((rangeRandom(128) - 64)) * speed * 3 * 4) >> 11;

            particleAge[whichDrop] = age;
        }
    }

    return whichDrop;
}

void nDots(int count, int dripX, int dripY, int type, int age, int offsetX, int offsetY,
           int speed) {

    if (gravity < 0)
        offsetY = TRILINES - offsetY;

    for (int i = 0; i < count; i++)
        sphereDot(dripX * 5 + offsetX, dripY * TRILINES + offsetY, type, age, speed);
}

void nDotsBackwards(int count, int dripX, int dripY, int type, int age, int offsetX, int offsetY,
                    int speed) {

    if (gravity < 0)
        offsetY = TRILINES - offsetY;

    for (int i = 0; i < count; i++) {
        int idx = sphereDot(dripX * 5 + offsetX, dripY * TRILINES + offsetY, type, age, speed);

        particleX[idx] += particleAge[idx] * particleSpeedX[idx];
        particleY[idx] += particleAge[idx] * particleSpeedY[idx];

        particleSpeedX[idx] = -particleSpeedX[idx];
        particleSpeedY[idx] = -particleSpeedY[idx];
    }
}

void nDotsAtTrixel(int count, int dripX, int dripY, int age, int speed) {

    for (int i = 0; i < count; i++) {
        int idx = sphereDot(dripX, dripY, 2, age, speed);
        if (idx >= 0)
            particleSpeedY[idx] = -((((int)(rangeRandom(0x10000 >> 1))) * speed) >> 16);
    }
}

void setJumpVectors(int midKernel, int exitKernel) {

    for (int i = 0; i < _ARENA_SCANLINES; i++)
        RAM_SINT[(_BUF_JUMP1 / 2) + i] = midKernel;
    RAM_SINT[_BUF_JUMP1_EXIT / 2] = exitKernel;
}

int dirFromCoords(int x, int y, int prevX, int prevY) {

    int dir = 0;
    if (x < prevX)
        dir |= DIR_L;
    if (x > prevX)
        dir |= DIR_R;

    if (y < prevY)
        dir |= DIR_U;
    if (y > prevY)
        dir |= DIR_D;

    return dir;
}

void initNewGame() {

    actualScore = 0;
    partialScore = 0;
    lives = 3;
    invincible = false;
    pulsePlayerColour = 0;
}

void initNextLife() {

    //    KERNEL = KERNEL_GAME;

    setJumpVectors(_NORMAL_KERNEL, _EXIT_KERNEL);

#if __ENABLE_WATER
    //    water = 0;
    //    lava = 0;
    lastWater = 0;
#endif

#if ENABLE_SHAKE
    shakeTime = 0;
    // shakeX = 0;
    // shakeY = 0;
#endif

    bufferedSWCHA = 0xFF;

    caveCompleted = false;
    exitTrigger = false;

    perfectTimer = 80;

    exitMode = 0;
    idleTimer = 0;
    sparkleTimer = 0;
    gameFrame = 0;
    triggerPressCounter = 0;
    triggerOffCounter = 0;
    // expandSpeed = 0;
    nextGravity = 1;

    // dogeBlockCount = 0;
    // cumulativeBlockCount = 0;
    explodeCount = 0;

    resetDelay = 0;
    // selectResetDelay = 0;

    showTool = false;

#if ENABLE_DEBUG
    selectDelay = 0;
#endif

    lavaSurfaceTrixel = 10000; // 0x1C2/3; //22 * PIECE_DEPTH - 1;
    showLava = false;
    showWater = false;

    // lastDisplayMode = DISPLAY_NONE;

#ifdef ENABLE_SWITCH
    switchOn = true;
#endif

    // #define SPEED_INCREMENT (0xC000)
    // #define SPEED_INCREMENT_60 (SPEED_INCREMENT)
    // #define SPEED_INCREMENT_50 (SPEED_INCREMENT * 50 / 60)

    // static const unsigned int speedo[] = {

    //     SPEED_INCREMENT_60,
    //     SPEED_INCREMENT_50,
    //     SPEED_INCREMENT_60,
    //     SPEED_INCREMENT_50,
    // };

#if SCHEDULER == 0
    gameSpeed = 4;
#else
    gamespeed = 6;
#endif

    frameCounter = gameSpeed; // force initial
    selectorCounter = 0;

    initWyrms();
    initPlayer();
    initSprites();

    for (int i = 0; i < PARTICLE_COUNT; i++)
        particleAge[i] = -1;

#if CIRCLE
    initSwipeCircle(CIRCLE_ZOOM_ZERO + 1);
#endif

    initCharAnimations();

    spacing = 0;

    decodeCave(cave);
    // if (lockDisplay)
    //     displayMode = DISPLAY_HALF;

    gameSchedule = SCHEDULE_UNPACK_CAVE;
    setScoreCycle(SCORELINE_CAVELEVEL);
}

void scheduleUnpackCave() {

    while (T1TC < 20000)
        if (!decodeExplicitData(false)) {

            if (!totalDogePossible)
                totalDogePossible = -1; // indicates "perfect" not possible

            gameSchedule = SCHEDULE_START;
            break;
        }
}

void Scheduler() {

    static void (*const scheduleFunc[])() = {

        setupBoard,          // SCHEDULE_START
        processBoardSquares, // SCHEDULE_PROCESSBOARD
        scheduleUnpackCave,  // SCHEDULE_UNPACK_CAVE
    };

    (*scheduleFunc[gameSchedule])();
}

const unsigned char sinoid[] = {0, 1, 1, 3, 5, 6, 6, 7, 7, 6, 6, 5, 3, 1, 1, 0};

void drawWord(const unsigned char *string, int y) {

    showingWords = true;

    FLASH(0x42, 2);

    // FIXES PAL long-word display?
    // availableIdleTime -= 30000;
    // if (availableIdleTime > 0)
    //     availableIdleTime = 0;

    if (spacing < 56)
        spacing++;

    wordColour -= 5;
    int col = wordColour;

    int base = 0;
    while (*string != NEW_LINE) {

        const unsigned char *width = string;
        while (*++width != NEW_LINE)
            ;

        int x = (8 + width - string) >> 1;

        int ch;
        while ((ch = *string++) != NEW_LINE) {

            col += 20;
            int colour = (col >> 6) & 7;
            if (colour < 1)
                colour = 7;

            if (ch != ' ') {
                if (ch >= 'A')
                    ch = LETTER(ch);

                drawBigDigit(ch, x, y + sinoid[(x + (togt >> 2) + base) & 15], colour, true);
            }
            x--;
        }

        y += spacing >> 1;
        base += 3;
    }
}

// void drawOverlayWords() {
//  return; //tmp

//     togt++;

//     if (
// #if __ENABLE_DEMO
//         !demoMode &&
// #endif
//         displayMode != DISPLAY_OVERVIEW && uncoverTimer > 1 && uncoverTimer <
//         20) drawWord(theCaveData, 70);

//     else if (!lives && *playerAnimation == FRAME_BLANK) {
//         static const unsigned char gameOver[] = {
//         'G','A','M','E',NEW_LINE,'O','V','E','R',END_STRING };
//         drawWord(gameOver, 70);
//     }
// }

void drawOverscanThings() {

    doFlash();

    updateAnimation();

    // zap sprite buffers (expensive!)
    unsigned int *p = (unsigned int *)(RAM + _BUF_GRP0A);
    for (int i = 0; i < _ARENA_SCANLINES / 2; i++)
        p[i] = 0;

    // if (exitMode)
    //     displayMode = DISPLAY_NORMAL;

    // if (displayMode == DISPLAY_OVERVIEW) {

    //     drawOverviewScreen(0, 11);
    //     drawPlayerSmallSprite();
    // }

    // else {

    // if (displayMode == DISPLAY_HALF) {
    //     // createParallaxCharset();
    //     drawHalfSprite();
    // }

    // if (lastDisplayMode == DISPLAY_OVERVIEW) {
    //     unsigned char *p = RAM + _BUF_PF0_LEFT + DIGIT_SIZE;
    //     for (int i = 0; i < 3; i++)
    //         for (int j = 0; j < _ARENA_SCANLINES * 6; j += _ARENA_SCANLINES)
    //             *(p + i + j) = 0;
    // }

    // if (lastDisplayMode != displayMode)
    //     resetTracking();

    Scroll();
    //        drawScore();

    // if (displayMode == DISPLAY_NORMAL) {

    // createParallaxCharset();
    drawScreen();
    drawScore();

    drawPlayerSprite();
}

struct ptrs {
    unsigned char dataStream;
    unsigned short buffer;
};

static const struct ptrs streamInits[] = {

    {_DS_PF0_LEFT, _BUF_PF0_LEFT},
    {_DS_PF1_LEFT, _BUF_PF1_LEFT},
    {_DS_PF2_LEFT, _BUF_PF2_LEFT},
    {_DS_PF0_RIGHT, _BUF_PF0_RIGHT},
    {_DS_PF1_RIGHT, _BUF_PF1_RIGHT},
    {_DS_PF2_RIGHT, _BUF_PF2_RIGHT},
    {_DS_AUDV0, _BUF_AUDV},
    {_DS_AUDC0, _BUF_AUDC},
    {_DS_AUDF0, _BUF_AUDF},
    {_DS_COLUPF, _BUF_COLUPF},
    {_DS_COLUBK, _BUF_COLUBK},
    {_DS_COLUP0, _BUF_COLUP0},
    {_DS_COLUP1, _BUF_COLUP1},
    {_DS_GRP0a, _BUF_GRP0A},
    {_DS_GRP1a, _BUF_GRP1A},
#if __ENABLE_ATARIVOX
    {_DS_SPEECH, _BUF_SPEECH},
#endif
    {0x21, _BUF_JUMP1},
};

void initGameDataStreams() {

    for (unsigned int i = 0; i < sizeof(streamInits) / sizeof(struct ptrs); i++)
        setPointer(streamInits[i].dataStream, streamInits[i].buffer);

    // QINC[_DS_SPEECH] = 0;
}

void bigStuff(int amount) {

    unsigned char timeString[6];
    *drawDecimal2(timeString, 0, 0, amount) = 0xFF;

    int digitPos = amount >= 10 ? amount >= 100 ? 6 : 5 : 4;

    for (int digit = 0; timeString[digit] <= 9; digit++, digitPos -= 2)
        doubleSizeScore(digitPos, 85, timeString[digit], 6);
}

void handleCaveCompletion() {

    if (exitMode) {

        if (waitRelease) {
            if ((inpt4 & 0x80) && (swcha == 0xFF))
                waitRelease = false;
        }

        if (!waitRelease && (JOY0_FIRE || (swcha != 0xFF))) {
            addScore(theCave->extraDogeValue * -doges);
            addScore(2 * (time >> 8));
            exitMode = 0;
            caveCompleted = true;
            return;
        }

        // if (playerAnimationID != ID_Shades && !autoMoveFrameCount && exitMode
        // > 150)
        //     startPlayerAnimation(ID_Shades);

        static int slowDown = 0;

        if (perfectTimer && !totalDogePossible) { // got 'em all!
            static const unsigned char perfect[] = {
                'P', 'E', 'R', 'F', 'E', 'C', 'T', END_STRING,
            };
            drawWord(perfect, 60);
            perfectTimer--;
        }

        else {

#if __ENABLE_DEMO
            if (!demoMode) {
#endif
                if (doges < 0) {

                    static const unsigned char extraBonus[] = {
                        'D', 'O', 'G', 'E', END_STRING,
                    };

                    if (exitMode == 51)
                        ADDAUDIO(SFX_UNCOVER);

                    if (exitMode < 50 && --slowDown < 0) {

                        ++doges;
                        addScore(theCave->extraDogeValue);
                        slowDown = 5;
                        exitMode = doges ? 50 : 80;

                        if (!doges) {
                            ADDAUDIO(SFX_BLIP);
                            killAudio(SFX_UNCOVER);
                        }
                    }

                    drawWord(extraBonus, 40);
                    bigStuff(-doges);
                }

                else if (exitMode < 50 && time > 0) {

                    if (exitMode == 7)
                        ADDAUDIO(SFX_UNCOVER);

                    static const unsigned char extraBonus[] = {
                        'T', 'I', 'M', 'E', END_STRING,
                    };

                    setScoreCycle(SCORELINE_SCORE);

                    if (exitMode < 7 && --slowDown < 0) {
                        time -= 256;
                        addScore(2);
                        slowDown = 5;
                        exitMode = 7;
                    }

                    if (time <= 0) {
                        time = 0;
                        ADDAUDIO(SFX_BLIP);
                        killAudio(SFX_UNCOVER);
                        exitMode = 80;
                    }

                    drawWord(extraBonus, 40);
                    bigStuff(time >> 8);
                }

                if (!--exitMode)
                    caveCompleted = true;
#if __ENABLE_DEMO
            }
#endif
        }

        setScoreCycle(SCORELINE_SCORE);
    }
}

void GameOverscan() {

    T1TC = 0;
    T1TCR = 1;

    // destroy += destroyInc;
    // actualScore = destroy;

    availableIdleTime = 90000; // + destroy; // 99000 - 1000;

#if __ENABLE_ATARIVOX
    if (RAM[_BUF_SPEECH] != 0xFF)
        availableIdleTime = 30000;
#endif

    if (!(SWCHA & 0xF0)) // UDLR at same time!
        invincible = true;

#if ENABLE_SHAKE

    if (shakeTime) {

        shakeTime--;

#define X_SHAKE 0x3FFF
#define Y_SHAKE 0x20000

        shakeX = ((int)rangeRandom(X_SHAKE)) - X_SHAKE / 2;
        shakeY = rangeRandom(Y_SHAKE) - Y_SHAKE / 2;
    } else
        shakeY = shakeX = 0;

#endif

    initGameDataStreams();
    playAudio();

    if (gameSchedule == SCHEDULE_UNPACK_CAVE)
        return;

    getJoystick();
    bufferedSWCHA &= swcha; // | inhibitSWCHA;

    if (frameCounter > ((gameSpeed * 5) >> 3)) {
        bufferedSWCHA |= inhibitSWCHA;
        inhibitSWCHA = 0;
    }

    if (waitRelease) {
        if ((inpt4 & 0x80) && (swcha == 0xFF))
            waitRelease = false;
    } else {

        // if (!(SWCHB & 0b11)    // select+reset
        //     || (swcha == 0xFF && !(inpt4 & 0x80))) {
        //         selectResetDelay++;
        // }

        // else
        {

            //            selectResetDelay = 0;

            if (!GAME_RESET_PRESSED)
                resetDelay = 0;

            else if (++resetDelay == RESET_DELAY) {

                rageQuit = true;
                initKernel(KERNEL_MENU);
                //                ADDAUDIO(SFX_BLIP);
                return;
            }
        }
    }

#define DOUBLE_TAP 8
#define TOOLONG 30

    if (!waitRelease && !(inpt4 & 0x80)) { // JOY0_FIRE)

        showTool = false;

        if (!exitMode && triggerOffCounter && triggerOffCounter < DOUBLE_TAP &&
            triggerPressCounter < TOOLONG) {

            // Handle double-click view mode switching

            showTool = true;

            //            ADDAUDIO(SFX_BLIP);

            //             switch (displayMode) {
            //             case DISPLAY_NORMAL:
            //             case DISPLAY_HALF :
            // //                displayMode = DISPLAY_OVERVIEW;
            //                 break;
            //             default:
            //                 displayMode = DISPLAY_NORMAL;
            //                 break;
            //             }

            triggerPressCounter = 0;
            waitRelease = true;
        } else {
            triggerPressCounter++;
            triggerOffCounter = 0;
        }

        // Long-press after death will restart
        if (playerDead && triggerPressCounter == DEAD_RESTART) {

            waitRelease = true;
            //            ADDAUDIO(SFX_BLIP);

            if (lives) {
                initKernel(KERNEL_STATS);
            } else
                initKernel(KERNEL_MENU);

            return;
        }

    } else {

        if (!exitMode && triggerPressCounter && triggerOffCounter >= DOUBLE_TAP) {

            //             if (triggerPressCounter < TOOLONG) {
            //                 // if (displayMode == DISPLAY_NORMAL)
            //                 //     displayMode = DISPLAY_HALF;
            //                 // else
            //                     // displayMode = DISPLAY_NORMAL;

            // //                ADDAUDIO(SFX_BLIP);

            //             }
            triggerPressCounter = 0;
            triggerOffCounter = 0;
        }

        triggerOffCounter++;
    }

    drawOverscanThings();

#if __ENABLE_DEMO
//    checkDemoFinished();
#endif

    handleSelectReset();
}

void handleSelectReset() {

#if ENABLE_DEBUG

    if (!GAME_SELECT_PRESSED)
        selectDelay = 0;

    // (DEBUG) "next level" SELECT press
    else if (!GAME_RESET_PRESSED && ++selectDelay == SELECT_DELAY)
        caveCompleted = true;

#endif

    if (caveCompleted) {

        caveCompleted = false;

#if __ENABLE_DEMO
        if (demoMode)
            initKernel(KERNEL_MENU);
        else {
#endif

            if (++cave >= caveCount) {
#if !__ENABLE_TRAINER
                if (level < 4)
                    ++level;
#endif
                cave = 0;
            }

            initKernel(KERNEL_STATS);
#if __ENABLE_DEMO
        }
#endif
    }
}

void GameVerticalBlank() {

    T1TC = 0;
    T1TCR = 1;

    // destroy += destroyInc;

    showingWords = false;
    availableIdleTime = 90000; // + destroy; // 120000 - 1000;

#if __ENABLE_ATARIVOX
    processSpeech();
#endif

    if (sparkleTimer)
        --sparkleTimer;

#if SCHEDULER == 0
    frameCounter++;
#endif

    if (gameSchedule != SCHEDULE_UNPACK_CAVE) {

        handleCaveCompletion();

        if (
#if CIRCLE
            checkSwipeFinished() &&
#endif
            time && !playerDead && !exitMode) {

            time--;

            if ((time & 0xFF) == 0xFF) {

                time -= 0xC4; // magic!  - (-256+60)
                if (time < 0xA00) {
                    setScoreCycle(SCORELINE_TIME);
                    ADDAUDIO(SFX_COUNTDOWN2);
                }
            }
        }

        drawScore();
        drawParticles();

        if (showTool) {

            static int pulseTool = 0;
            pulseTool++;

            doDrawBitmap(toolIcon[0 /*(pulseTool >> 4) & 1*/], 90);
        }
#if CIRCLE
        swipeCircle();
#endif

        setPalette();
        processCharAnimations();
    }
}

void surroundingConglomerate(int col, int row) {

    if (visible(col, row)) {

        unsigned char *pos = RAM + _BOARD + row * _1ROW + col;
        for (int i = 0; i < 5; i++) {

            unsigned char *offsetPos = pos + dirOffset[i];
            if (Attribute[CharToType[GET(*offsetPos)]] & ATT_GEODOGE) {

                int cong = CH_GEODOGE;

                for (int j = 0; j < 4; j++)
                    if (Attribute[CharToType[GET(*(offsetPos + dirOffset[j]))]] & ATT_GEODOGE)
                        cong += 1 << j;

                *offsetPos = cong;
            }
        }
    }
}

void setupBoard() {

    if (frameCounter >= gameSpeed) {

        frameCounter = 0;

        activated = isActive[++selectorCounter & 3];

        if (showLava) {

            if (gravity > 0 && lavaSurfaceTrixel && !(gameFrame & 15))
                lavaSurfaceTrixel -= gravity;

            // Surface lava "bubbles"
            int posX = ((scrollX * 5) >> 16) + rangeRandom(_BOARD_COLS);
            nDotsAtTrixel(1, posX, lavaSurfaceTrixel + 1, 20, 0x10000);
        }

        if (showWater) {
            static const unsigned char sinus[] = {0, 1, 1, 2, 2, 2, 3, 3, 4, 3, 3, 2, 2, 2, 1, 1};
            static int waves = 0;

            if (lavaSurfaceTrixel) {

                lavaSurfaceTrixel -= sinus[(waves >> 0) & 15];

                if (((sinus[(waves >> 0) & 15] & 3) != 0) || (gameFrame & 31) == 0) {
                    ++waves;

                    if (!(gameFrame & 31))
                        lavaSurfaceTrixel--;
                }

                lavaSurfaceTrixel += sinus[(waves >> 0) & 15];
            }

            for (int i = 0; i < 4; i++) {
                int posX = ((scrollX * 5) >> 16) + rangeRandom(_BOARD_COLS);
                int deep = lavaSurfaceTrixel + rangeRandom(21 * PIECE_DEPTH - lavaSurfaceTrixel);
                if (deep > 0 && deep < _ARENA_SCANLINES)
                    bubbles(1, posX, deep, 2240, 0x8000);
            }
        }

        gameFrame++;
        gravity = nextGravity;

        usableSWCHA = bufferedSWCHA;
        bufferedSWCHA = 0xFF;

        if (boardRow < 0) {
            boardRow = _BOARD_ROWS - 1;
            boardCol = _BOARD_COLS - 1;
        } else {
            boardCol = 0;
            boardRow = 0;
        }

        gameSchedule = SCHEDULE_PROCESSBOARD;

        // if (theCave->flags & CAVEDEF_ROCK_GENERATE) {
        //     unsigned char *const generator = RAM + _BOARD + 40 + 19;
        //     if (Attribute[CharToType[GET(*generator)]] & ATT_BLANK)
        //         *generator = CH_ROCK_FALLING;
        // }

        processBoardSquares();
    }
}

void Explode(unsigned char *where, unsigned char explosionShape) {

    ADDAUDIO(SFX_EXPLODE);

    int offset[] = {-_BOARD_COLS - 1, -_BOARD_COLS, -_BOARD_COLS + 1, -1, 1,
                    _BOARD_COLS - 1,  _BOARD_COLS,  _BOARD_COLS + 1};

    for (int i = 0; i < 8; i++) {
        unsigned char *cell = where + offset[i];
        unsigned char type = CharToType[GET(*cell)];
        if (Attribute[type] & ATT_EXPLODABLE) {
            *cell = explosionShape;
            if (explosionShape == CH_DOGE_00)
                totalDogePossible++;
        }
    }

    FLASH(4, 4);
}

void doRoll() {

    for (int offset = -1; offset < 2; offset += 2) {

        unsigned char *side = me + offset;
        if (!(*side & FLAG_THISFRAME)) {

            unsigned char sideType = CharToType[GET(*side)];
            if (Attribute[sideType] & ATT_BLANK) {

                unsigned char sideDownType = CharToType[GET(*(side + _1ROW))];
                if (Attribute[sideDownType] & ATT_BLANK) {

                    if (offset > 0) {
                        *me = FLAG(CH_DOGE_SIDE_1);
                        *(me + offset) = FLAG(CH_DOGE_SIDE_3);

                    } else {
                        *me = FLAG(CH_DOGE_SIDE_2);
                        *(me + offset) = FLAG(CH_DOGE_SIDE_4);
                    }

                    int off = offset < 0 ? 4 : 0;

                    nDots(1, boardCol, boardRow, 2, 15, offset * 2 + off, 4 * gravity, 0);
                    nDots(1, boardCol, boardRow, 2, 20, offset * 4 + off, 4 * gravity, 0);
                    nDots(1, boardCol, boardRow, 2, 25, offset * 6 + off, 7 * gravity, 0);
                    nDots(1, boardCol, boardRow, 2, 30, offset * 7 + off, 10 * gravity, 0);

                    surroundingConglomerate(boardCol, boardRow);
                    return;
                }
            }
        }
    }
}

void chainReact_GeoDogeToDoge() {

    bool ongoing = false;
    *me = FLAG(CH_DOGE_00);

    for (int i = 0; i < 4; i++) {

        unsigned char *newDogeCandidate = me + dirOffset[i];

        if (Attribute[CharToType[GET(*newDogeCandidate)]] & ATT_GEODOGE) {

            *newDogeCandidate = CH_CONVERT_GEODE_TO_DOGE | thisFrame[i];
            ADDAUDIO(SFX_UNCOVER);
            ongoing = true;

            surroundingConglomerate(boardCol + xdir[i], boardRow + ydir[i]);
        }
    }

    surroundingConglomerate(boardCol, boardRow);

    if (!ongoing)
        killAudio(SFX_UNCOVER);
}

void chainReact_Pipe() {

    bool ongoing = false;
    *me = FLAG(CH_DUST_0);

    for (int i = 0; i < 4; i++) {

        unsigned char *newDogeCandidate = me + dirOffset[i];

        if (ATTRIBUTE_BIT(*newDogeCandidate, ATT_PIPE)) {

            *newDogeCandidate = CH_CONVERT_PIPE | thisFrame[i];
            ADDAUDIO(SFX_UNCOVER);
            ongoing = true;
        }
    }

    if (!ongoing)
        killAudio(SFX_UNCOVER);
}

void genericPush(int offsetX, int offsetY) {

#ifdef ENABLE_SWITCH
    if (switchOn) {
#endif
        bool atEdge = (boardCol < 3) || (boardCol > 36) || (boardRow < 3) || (boardRow > 18);
        unsigned char *playerPos = RAM + _BOARD + playerY * _1ROW + playerX;

        int adjustOffset = offsetY * _1ROW + offsetX;
        unsigned char *pushPos = me + adjustOffset;

        unsigned char alternate = CH_STEELWALL;
        unsigned char *pushPosFurther = atEdge ? &alternate : pushPos + adjustOffset;
        int attPushPosFurther = Attribute[CharToType[GET(*pushPosFurther)]];

        if (playerPos == pushPos && (atEdge || !(attPushPosFurther & ATT_PERMEABLE))) {
            // shakeTime = 20;
            FLASH(0x42, 8);
            startPlayerAnimation(ID_Xray);
            nDots(6, boardCol + offsetX, boardRow + offsetY, 2, 50, 3, 4, 0x18000);
        }

        int attPushPos = Attribute[CharToType[GET(*pushPos)]];

        if (!(GET(*pushPos) & FLAG_THISFRAME)) {
            if ((attPushPos & ATT_PERMEABLE) ||
                ((attPushPos & ATT_PUSH) && (attPushPosFurther & ATT_PERMEABLE))) {

                // Note we may have a lagging flag clear until next frame but who cares

                if (attPushPosFurther & ATT_PERMEABLE)
                    *pushPosFurther = FLAG(*pushPos);

                *pushPos = FLAG(*me);
                *me = offsetX ? CH_HORIZONTAL_BAR : CH_VERTICAL_BAR;

                if (playerPos == pushPos) {

                    pulsePlayerColour = 20;
                    ADDAUDIO(SFX_EXPLODE_QUIET);

                    if (attPushPosFurther & ATT_BLANK) {

                        autoMoveY = 0;
                        autoMoveY = 0;
                        autoMoveFrameCount = 0;
                        playerX += offsetX;
                        playerY += offsetY;
                    }
                }

                surroundingConglomerate(boardCol, boardRow);
                surroundingConglomerate(boardCol + offsetX, boardRow + offsetY);

                if (!(attPushPos & ATT_PERMEABLE))
                    nDots(6, boardCol + offsetX, boardRow + offsetY, 2, 150, 3, 4, 0x10000);
                return;
            }
        }

        *me = (*me) + 1; // reverse
#ifdef ENABLE_SWITCH
    }
#endif
}

void genericPushReverse(int offsetX, int offsetY) {

#ifdef ENABLE_SWITCH
    if (switchOn) {
#endif
        unsigned char *pushPos = me + offsetY * _BOARD_COLS + offsetX;
        int type = CharToType[GET(*pushPos)];

        if (type == TYPE_PUSHER) {
            *pushPos = FLAG(*me);
            *me = CH_BLANK;
        } else
            *me = (*me) - 1;
#ifdef ENABLE_SWITCH
    }
#endif
}

void processDoge() {

    unsigned char *next = me + _1ROW * gravity;
    int attrNext = Attribute[CharToType[GET(*next)]];

    if (attrNext & ATT_BLANK) {
        *me = FLAG(CH_DOGE_FALLING_TOP);
        *next = FLAG(CH_DOGE_FALLING_BOTTOM);
    }

    else if (attrNext & ATT_ROLL)
        doRoll();
}

void processPebble() {

    // don't form way above player
    if (boardCol == playerX && boardRow < playerY)
        return;

    int chance = 50;

    for (int i = 0; i < 4; i++)
        if (TYPEOF(*(me + dirOffset[i])) == TYPE_MELLON_HUSK) {
            chance = 5;
            break;
        }

    if (!rangeRandom((chance))) {
        *me = FLAG(CH_PEBBLE_ROCK);
        nDots(10, boardCol, boardRow, 2, 20, 2, 5, 0x10000);
    }
}

void processWater() {

    if ((boardRow - 1) * TRILINES >= lavaSurfaceTrixel) {
        unsigned char *neighbour = me + dirOffset[waterDir & 3];
        if (Attribute[CharToType[GET(*neighbour)]] & ATT_DISSOLVES) {
            // FLASH(0x44, 2);
            *neighbour = CH_DUST_0;
        }
    }
}

void processLava() {

    if (visible(boardCol, boardRow)) {

        int rand = getRandom32();
        if ((boardRow - 1) * TRILINES >= lavaSurfaceTrixel) {

            int i = waterDir & 3;

            unsigned char *neighbour = me + dirOffset[i];
            int att = Attribute[CharToType[GET(*neighbour)]];

            if (att & ATT_DISSOLVES) {
                *neighbour = CH_LAVA_BLANK;
            }

            else if (att & ATT_MELTS && !(rand & 63)) {

                *neighbour = FLAG((att & ATT_GEODOGE) ? CH_DOGE_00 : CH_DUST_0);
                nDots(8, boardCol + xdir[i], boardRow + ydir[i], 2, 50, 3, 4, 0x10000);
            }
        }

        // Animate lava bubble
        switch (*me) {
        case CH_LAVA_BLANK: {
            if (!(rand & (15 << 7))) {
                (*me)++;
                nDots(3, boardCol, boardRow, 2, 30, 2, 5, 0xC000);
            }
            break;
        case CH_LAVA_SMALL:
            *me = CH_LAVA_MEDIUM;
            break;
        case CH_LAVA_MEDIUM:
            *me = CH_LAVA_BLANK;
            break;
        case CH_LAVA_LARGE:
            *me = CH_LAVA_BLANK;
            break;
        }
        }
    }
}

void processWaterFlow() {

    // Lag the interruption of water flowing downwards
    unsigned char above = *(me - _1ROW);
    if (!(above & FLAG_THISFRAME) && !(Attribute[CharToType[GET(above)]] & ATT_WATERFLOW)) {
        *me = FLAG(CH_BLANK);
        return;
    }

    int line = (boardRow + 1) * TRILINES;
    if (line < lavaSurfaceTrixel) {
        if (boardRow < 20) {

            unsigned char *next = me + _1ROW * gravity;
            int att = Attribute[CharToType[GET(*next)]];
            if (!(att & ATT_WATERFLOW)) {

                if (att & (ATT_DISSOLVES | ATT_BLANK)) {

                    unsigned char rollWater = *me - 1;

                    if (rollWater < CH_WATERFLOW_0)
                        rollWater = CH_WATERFLOW_4;

                    // flag enables slow leading edge
                    *next = FLAG(rollWater);

                } else

                    // Water has hit something below
                    nDots(3, boardCol, boardRow, 2 + PARTICLE_GRAVITY_FLAG, 40, 2 + rangeRandom(3),
                          11, 0x10000);

                shakeTime = 20;
            }
        }
    }
}

void processCharBeltAndGrinder() {

    if (creature == CH_GRINDER_1)
        conveyorDirection = 1;
    else if (creature == CH_GRINDER_0)
        conveyorDirection = -1;

    unsigned char *up = me - _1ROW;
    unsigned char *up2 = me - _1ROW + conveyorDirection;

    if (ATTRIBUTE_BIT(*up, ATT_CONVEYOR) && (ATTRIBUTE_BIT(*up2, ATT_BLANK | ATT_DISSOLVES)) &&
        !(*up & FLAG_THISFRAME)) {
        *up2 = FLAG(*up);
        *up = CH_DUST_0;
    }
}

void processOutlet() {

    if ((boardRow + 2) * TRILINES <= lavaSurfaceTrixel) {

        if (GET(*(me - _1ROW * 2)) == CH_TAP_0) {

            unsigned char under = GET(*(me + _1ROW));

            if (!(Attribute[CharToType[under]] & ATT_WATERFLOW)) {

                if (Attribute[CharToType[under]] & ATT_PERMEABLE)
                    *(me + _1ROW) = CH_WATERFLOW_0 + (getRandom32() & 3);

                else
                    nDots(1, boardCol, boardRow, 2, 30, rangeRandom(3) + 2, 10, 0x8000);
            }
        }

        else if (GET(*(me - _1ROW * 2)) == CH_TAP_1) {
            if (Attribute[CharToType[GET(*(me + _1ROW))]] & ATT_BLANK)
                *(me + _1ROW) = CH_BLANK;
        }
    }
}

void processCharGeoDogeAndRock() {

    unsigned char *next = me + _1ROW * gravity;
    unsigned char typeDown = CharToType[GET(*next)];
    // int typeofMe = CharToType[GET(*me)];

    if (Attribute[typeDown] & ATT_BLANK) {

        if (ATTRIBUTE_BIT(*me, ATT_GEODOGE)) {
            *next = FLAG(CH_GEODOGE_FALLING_BOTTOM);
            *me = FLAG(CH_GEODOGE_FALLING_TOP);
        } else {
            *next = FLAG(CH_ROCK_FALLING_BOTTOM);
            *me = FLAG(CH_ROCK_FALLING_TOP);
        }

        surroundingConglomerate(boardCol, boardRow);
    }

    else if (Attribute[typeDown] & ATT_ROLL) {

        // TODO: allow rock to roll in earthquake or on gear

        // if (ATTRIBUTE_BIT(*me, ATT_GEODOGE))
        //     doRoll(me, CH_GEODOGE_FALLING);
        // else {

        //     doRoll(me, CH_ROCK_FALLING);
        // }
    }
}

void processCharFallingThings() {

    unsigned char *next = me + _1ROW * gravity;
    unsigned char typeDown = CharToType[GET(*next)];
    if (Attribute[typeDown] & ATT_BLANK) {

        switch (creature) {

        case CH_GEODOGE_FALLING:
            *me = FLAG(CH_GEODOGE_FALLING_TOP);
            *next = FLAG(CH_GEODOGE_FALLING_BOTTOM);
            break;

        case CH_DOGE_FALLING:
            *me = FLAG(CH_DOGE_FALLING_TOP);
            *next = FLAG(CH_DOGE_FALLING_BOTTOM);
            break;

        case CH_ROCK_FALLING:
            *me = FLAG(CH_ROCK_FALLING_TOP);
            *next = FLAG(CH_ROCK_FALLING_BOTTOM);
            break;
        }

        unsigned char *nextNext = next + _1ROW * gravity;
        unsigned char downCh = GET(*nextNext);
        typeDown = CharToType[downCh];
        int attNextNext = Attribute[typeDown];

        if (downCh != CH_ROCK_FALLING && downCh != CH_DOGE_FALLING &&
            downCh != CH_GEODOGE_FALLING) {

            int sfx = 0;

            // if (!(attNextNext & ATT_NOROCKNOISE)) {

            //     if (creature == CH_ROCK_FALLING)
            //         sfx = attNextNext & ATT_HARD ? SFX_ROCK :
            //         SFX_ROCK2;
            //     else
            //         sfx = SFX_DOGE;
            // }

            if (attNextNext & ATT_HARD) {
                if (creature == CH_ROCK_FALLING || creature == CH_GEODOGE_FALLING) {

                    sfx = SFX_ROCK;

                    unsigned char *dL = me + _1ROW - 1;
                    unsigned char *dR = dL + 2;

                    if (!CharToType[GET(*dR)]) {
                        nDots(4, boardCol, boardRow + 1, 2, 10, 3, 7, 0x10000);
                    }

                    if (!CharToType[GET(*dL)]) {
                        nDots(4, boardCol, boardRow + 1, 2, 10, 3, 7, 0x10000);
                    }
                }
                // else
                //     sfx = SFX_DOGE;
            }

            if (sfx)
                ADDAUDIO(sfx);
        }
    }

    else if (Attribute[typeDown] & ATT_SQUASHABLE_TO_BLANKS) {

        if (creature == CH_DOGE_FALLING) {
            *me = FLAG(CH_BLANK);
            pulsePlayerColour = 5;
            grabDoge();
            nDots(6, boardCol, boardRow + 1, 2, 40, 3, 1, 0x10000);
        }

        else
            Explode(next, FLAG(CH_DUST_0));

    } else {

        // stop falling
        unsigned char sfx = 0;
        int att = ATTRIBUTE(*next);

        switch (creature) {

        case CH_ROCK_FALLING: {
            *me = CH_ROCK;
            sfx = att & ATT_HARD ? SFX_ROCK : SFX_ROCK2;
            break;
        }

        case CH_GEODOGE_FALLING: {
            *me = CH_GEODOGE;
            surroundingConglomerate(boardCol, boardRow);
            break;
        }

        case CH_DOGE_FALLING: {
            *me = CH_DOGE_00;
            sfx = SFX_DOGE;
            break;
        }
        }

        if (creature != CH_DOGE_FALLING)
            nDots(4, boardCol, boardRow, 2, 40, getRandom32() & 3, 10, 0x10000);

        // if (att & ATT_ROLL && creature == CH_DOGE_FALLING)
        //     doRoll(me, creature);

        if (sfx && !(att & ATT_NOROCKNOISE))
            ADDAUDIO(sfx);
    }
}

void convertWaterAndLavaObjects() {

    // Any blanks/dissolves underwater/lava gets transformed to water/lava chars

    if (boardRow * TRILINES >= lavaSurfaceTrixel && Attribute[type] & ATT_CONVERT)
        *me = showLava ? CH_LAVA_BLANK : CH_WATER;
}

void restartBoardScan() {

    waterDir++;

    processWyrms();

    gameSchedule = SCHEDULE_START;

    if (!autoMoveFrameCount) { // delay until fully in new square

        // // randomly place a new pebble
        // int *sq = RAM + _BOARD + rangeRandom(_BOARD_COLS * _BOARD_ROWS);
        // if (GET(*sq) == CH_DIRT)
        //     *sq = FLAG(CH_PEBBLE1 + (getRandom32() & 1));

        //                    chooseIdleAnimation();

        bool oldDead = playerDead;

        unsigned char *man = RAM + _BOARD + playerY * _1ROW + playerX;

        int what = GET(*man);

        if (invincible)
            what = *man = CH_MELLON_HUSK;

        int type = CharToType[what];
        playerDead = (type != TYPE_MELLON_HUSK && type != TYPE_MELLON_HUSK_PRE && !exitMode);

        if (explodeCount > 0) {
            nDots(2, playerX, playerY, 1, 1, 2, 0, 0x10000);
            --explodeCount;
        }

        if (oldDead != playerDead) {
            //                        sphereDot(playerX, playerY, 1,
            //                        -100, 2, 0);
            explodeCount = 4;
            startPlayerAnimation(ID_Die);
            waitRelease = true;
            lives--;
            lockDisplay = false;

            sound_max_volume = VOLUME_NONPLAYING;
            // killAudio(SFX_TICK);            // no heartbeat
            // playerDeadRelease = false;
        }

        if (playerDead && *playerAnimation)
            nDots(4, playerX, playerY, 1, 100, 2, 8, 0x10000);
    }
}

void processTypes() {

    switch (type) {

    case TYPE_DOGE:
        processDoge();
        break;

    case TYPE_PEBBLE1:
        processPebble();
        break;

    case TYPE_WATER:
        processWater();
        break;

    case TYPE_LAVA:
        processLava();
        break;

    case TYPE_MELLON_HUSK:

        if (!exitMode)
            movePlayer(me);
        break;

    case TYPE_WATERFLOW_0:
    case TYPE_WATERFLOW_1:
    case TYPE_WATERFLOW_2:
    case TYPE_WATERFLOW_3:
    case TYPE_WATERFLOW_4:
        processWaterFlow();
        break;

    case TYPE_BELT:
    case TYPE_BELT_1:
    case TYPE_GRINDER:
    case TYPE_GRINDER_1:
        processCharBeltAndGrinder();
        break;

    case TYPE_GEODOGE:

        if (!rangeRandom(50)) {
            *me = FLAG(CH_ROCK_PEBBLE_1);
            nDotsBackwards(10, boardCol, boardRow, 2, 25, 2, 5, 0x16000);
        }

        else
            processCharGeoDogeAndRock();

        surroundingConglomerate(boardCol, boardRow);
        break;

    default:
        break;
    }
}

void processCreatures() {

    switch (creature) {

    case CH_OUTLET:
        processOutlet();
        break;

    case CH_ROCK_PEBBLE_1:
        *me = FLAG(CH_ROCK_PEBBLE);
        // shakeTime += 5;
        break;

    case CH_ROCK_PEBBLE:
        *me = FLAG(CH_DUST_ROCK_0);
        break;

    case CH_PEBBLE_ROCK:
        *me = FLAG(CH_GEODOGE);
        surroundingConglomerate(boardCol, boardRow);
        break;

    case CH_PUSH_LEFT:
        genericPush(-1, 0);
        break;

    case CH_PUSH_LEFT_REVERSE:
        genericPushReverse(1, 0);
        break;

    case CH_PUSH_RIGHT:
        genericPush(1, 0);
        break;

    case CH_PUSH_RIGHT_REVERSE:
        genericPushReverse(-1, 0);
        break;

    case CH_PUSH_UP:
        genericPush(0, -1);
        break;

    case CH_PUSH_UP_REVERSE:
        genericPushReverse(0, 1);
        break;

    case CH_PUSH_DOWN:
        genericPush(0, 1);
        break;

    case CH_PUSH_DOWN_REVERSE:
        genericPushReverse(0, -1);
        break;

    case CH_DUST_2:
    case CH_DUST_ROCK_2:
        *me = CH_BLANK;
        break;

    case CH_DUST_0:
    case CH_DUST_1:
    case CH_DUST_ROCK_0:
    case CH_DUST_ROCK_1:
        (*me)++;
        break;

        // case CH_EXPLODETOBLANK_0:
        // case CH_EXPLODETOBLANK_1:
        // case CH_EXPLODETOBLANK_2:
        // case CH_EXPLODETOBLANK_3:
        //     *me = FLAG(creature + 1);
        //     break;

        // case CH_EXPLODETOBLANK_4:
        //     *me = FLAG(CH_BLANK);
        //     break;

    case CH_CONVERT_GEODE_TO_DOGE:
        *me = FLAG(CH_DOGE_00);
        chainReact_GeoDogeToDoge();
        break;

    case CH_CONVERT_PIPE:
        chainReact_Pipe();
        break;

    case CH_BLOCK: {

        unsigned char *next = me + _1ROW * gravity;
        unsigned char typeDown = CharToType[GET(*next)];
        if (Attribute[typeDown] & ATT_BLANK) {
            *next = FLAG(*me);
            *me = FLAG(CH_DUST_0);
        }
        break;
    }

    case CH_ROCK:
        processCharGeoDogeAndRock();
        break;

    case CH_ROCK_FALLING_TOP:
        *me = FLAG(CH_DUST_ROCK_0);
        break;

    case CH_GEODOGE_FALLING_TOP:
        *me = FLAG(CH_DUST_ROCK_0);
        break;

    case CH_DOGE_SIDE_1:
    case CH_DOGE_SIDE_2:
        *me = FLAG(CH_BLANK);
        break;

    case CH_DOGE_SIDE_3:
    case CH_DOGE_SIDE_4:
        *me = FLAG(CH_DOGE_FALLING_TOP);
        *(me + gravity * _1ROW) = FLAG(CH_DOGE_FALLING_BOTTOM);
        break;

    case CH_DOGE_FALLING_TOP2:
        *me = FLAG(CH_DOGE_FALLING_TOP);
        *(me + gravity * _1ROW) = FLAG(CH_DOGE_FALLING_BOTTOM);
        break;

    case CH_DOGE_FALLING_TOP:
        *me = FLAG(CH_BLANK);
        break;

    case CH_DOGE_FALLING_BOTTOM:
        *me = FLAG(CH_DOGE_FALLING);
        break;

    case CH_ROCK_FALLING_BOTTOM:
        *me = FLAG(CH_ROCK_FALLING);
        break;

    case CH_GEODOGE_FALLING_BOTTOM:
        *me = FLAG(CH_GEODOGE_FALLING);
        break;

    case CH_DOGE_FALLING:
    case CH_ROCK_FALLING:
    case CH_GEODOGE_FALLING: {

        processCharFallingThings();
        break;
    }

    case CH_DOORCLOSED:
        if (!doges) {
            *me = CH_DOOROPEN_0;
            FLASH(0x28, 10);
        }
        break;

    case CH_MELLON_HUSK_BIRTH:

        if (
#if CIRCLE
            checkSwipeFinished() &&
#endif
            (!isScrolling())) {
            *me = CH_MELLON_HUSK;
        }
        break;

    default:
        break;
    }
}

void processBoardSquares() {

    while (T1TC < availableIdleTime) {

        me = RAM + _BOARD + boardRow * _1ROW + boardCol;

        creature = *me;

        if (!(creature & FLAG_THISFRAME)) {

            type = CharToType[creature];

            if (visible(boardCol, boardRow))
                convertWaterAndLavaObjects();

            if (Attribute[type] & activated) {
                processTypes();
                processCreatures();
            }
        }

        // Clear any "scanned this frame" objects on the previous line
        // note: we need to also do the last row ... or do we? if it's steel wall, no

        if (gravity > 0) {
            if (boardRow > 1) {
                unsigned char *prev = me - _1ROW;
                *prev &= ~FLAG_THISFRAME;
            }
        }

        else {
            if (boardRow < _BOARD_ROWS - 1) {
                unsigned char *prev = me + _1ROW;
                *prev &= ~FLAG_THISFRAME;
            }
        }

        me += gravity;

        boardCol += gravity;

        if (gravity < 0) {
            if (boardCol < 0) {
                boardCol = _BOARD_COLS - 1;

                if (!--boardRow) {
                    restartBoardScan();
                    return;
                }
            }
        }

        else {
            if (boardCol > (_BOARD_COLS - 1)) {
                boardCol = 0;
                if (++boardRow > _BOARD_ROWS - 1) {
                    restartBoardScan();
                    return;
                }
            }
        }
    }
}

// EOF