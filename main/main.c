#include <stdbool.h>

#include "attribute.h"
#include "defines_cdfj.h"
#include "defines_from_dasm_for_c.h"

#include "defines.h"

#include "main.h"

#include "animations.h"
#include "atarivox.h"
#include "bitpatterns.h"
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

#if WORST_TIMING
int worstEver = 0;
int worstEverCreature = -1;
#endif

int togt;
int cpulse;
int wyrmNum;

int conveyorDirection;

////////////////////////////////////////////////////////////////////////////////
// CONFIGURABLE UX

#define DEAD_RESTART \
    1 // 20     /* # frames to hold trigger after loss of life, to start next
      // life
      // */
// #define MAX_PEBBLES        400     /* # random pebbles to put in dirt */

// Delays on RESET and SELECT are to allow non-ambiguous press of SELECT+RESET
// for suicide

#define RESET_DELAY 20  /* # frames to hold RESET before it is detected */
#define SELECT_DELAY 10 /* # frames to hold SELECT before it is detected */

////////////////////////////////////////////////////////////////////////////////

const int dir[] = {1, -1, -40, 40, 0};
const signed char xdir[] = {1, -1, 0, 0};
const signed char ydir[] = {0, 0, -1, 1};
const unsigned char merge[] = {2, 8, 1, 4};

const signed char dirOffset[] = {-1, 1, -40, 40};

int lavaSurface;
bool showWater;
bool showLava;

static int boardRow;
int boardCol;

int gravity;
int nextGravity;

int canPlay[5];

int explodeCount;

#if ENABLE_RAINBOW
bool rainbow;
#endif

bool showTool;

bool lockDisplay;
bool rageQuit;
unsigned char *thiss;
unsigned char inpt4;
unsigned char swcha;
int millingTime; // negative = expired
int doges;
int time;
int level;

bool waitRelease;
bool switchOn;

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

unsigned char enableParallax;

unsigned int availableIdleTime;
unsigned int uncoverCount;
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

int dogeBlockCount;
int cumulativeBlockCount;

int lives;
// int selectResetDelay;;
int resetDelay;

#if ENABLE_DEBUG
static int selectDelay;
#endif

unsigned int currentPalette;

int cave;
bool caveCompleted;
unsigned char bufferedSWCHA;
unsigned int usableSWCHA;
unsigned int inhibitSWCHA;

signed char wyrmX[WYRM_POP][WYRM_MAX];
signed char wyrmY[WYRM_POP][WYRM_MAX];
int wyrmHead[WYRM_POP]; // = -1;
int wyrmDir[WYRM_POP];

#if __FADE
unsigned int fade = 0;
#endif

#if __ENABLE_WATER
int water unsigned char *lastWater;
#endif

#if __ENABLE_LAVA
int lava;
#endif

#if ENABLE_SHAKE
int shakeX, shakeY;
int shakeTime;
#endif

// COMPILE-TIME REVERSE BITS IN BYTE
#define RVS(a)                                           \
    (((((a) >> 0) & 1) << 7) | ((((a) >> 1) & 1) << 6) | \
     ((((a) >> 2) & 1) << 5) | ((((a) >> 3) & 1) << 4) | \
     ((((a) >> 4) & 1) << 3) | ((((a) >> 5) & 1) << 2) | \
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

const unsigned char BitRev[] = {
    P8(0),
};

enum SCHEDULE gameSchedule;

// Function Prototypes

void GameOverscan();
void GameVerticalBlank();
void initNextLife();
void SystemReset();
void setupBoard();
void processCharAnimations();

#if ENABLE_OVERLAY
void GameScheduleDrawOverlay();
#endif

static void (*const runFunc[])() = {

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

    for (int i = 0; i <= 34; i++)
        QINC[i] = 0x100; // data stream increments -> 1.0

    initKernel(KERNEL_COPYRIGHT);

    rageQuit = false;
    ARENA_COLOUR = 0;

    enableParallax = RIGHT_DIFFICULTY_A;
    enableICC = LEFT_DIFFICULTY_A;

    for (int i = 0; i < 5; i++)

#if ENABLE_DEBUG
        canPlay[i] = 0xFFFFFFFF;
#else
        canPlay[i] = 0b00010001000100010001000100010001;
#endif

#if WORST_TIMING
    for (int i = 0; i < TYPE_MAX; i++)
        worst[i] = 0;
#endif

    // #if __ENABLE_ATARIVOX
    // RAM[_BUF_SPEECH] = 0xFF;
    // #endif
}

int sphereDot(int dripX, int dripY, int type, int age, int speed) {

    int idx = -1;

    int line = ((dripY >> 16) - ((scrollY) >> 16)) * 3;
    if (line < 0 || line >= _ARENA_SCANLINES - 3)
        return idx;

    int col = (dripX >> 8) - ((scrollX * 5) >> 16);
    if (col < 0 || col > 39)
        return idx;

    int whichDrop = -1;
    while (++whichDrop < RAINHAILSHINE)
        if (rainX[whichDrop] == -1)
            break;

    if (whichDrop == RAINHAILSHINE)
        whichDrop = rangeRandom(RAINHAILSHINE);

    rainType[whichDrop] = type;
    rainX[whichDrop] = dripX;
    //    rainRow[whichDrop] = dripY;

#define DOTY 0x10000

    rainY[whichDrop] = dripY;
    rainSpeedX[whichDrop] =
        (((int)(((rangeRandom(64) - 32) << 1))) * speed) >> 16;
    rainSpeedY[whichDrop] =
        (((int)(rangeRandom(DOTY) - (DOTY >> 1))) * speed) >> 16;

    rainAge[whichDrop] =
        age < 0 ? -age : age; // rangeRandom(-age>>1) + (age >>1) : age;

    return whichDrop;
}

void nDots(int count, int dripX, int dripY, int type, int age, int offsetX,
           int offsetY, int speed) {

    int y = offsetY;
    if (gravity < 0) {
        y = TRILINES - y;
    }
    for (int i = 0; i < count; i++)
        sphereDot((dripX * 5 + offsetX) << 8,
                  (dripY * TRILINES + y) << 16, type, age, speed);
}

void nDotsAtPixel(int count, int dripX, int dripY, int age, int speed) {

    return; // tmp

    for (int i = 0; i < count; i++) {
        int idx = sphereDot(dripX << 8, dripY << 16, 2, age, speed);
        if (idx >= 0)
            rainSpeedY[idx] =
                -((((int)(rangeRandom(DOTY >> 1))) * speed) >> 16);
    }
}

void setJumpVectors(int midKernel, int exitKernel) {

    for (int i = 0; i < _ARENA_SCANLINES; i++)
        RAM_SINT[(_BUF_JUMP1 / 2) + i] = midKernel;
    RAM_SINT[_BUF_JUMP1_EXIT / 2] = exitKernel;
}

#define DIR_U 1
#define DIR_R 2
#define DIR_D 4
#define DIR_L 8

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

// void randomPebble() {
//     unsigned char *p = RAM + _BOARD + rangeRandom(880);
//     if (*p == CH_DIRT)
//         *p = CH_PEBBLE1 + rangeRandom(2);
// }

void newWyrm(int x, int y) {

    if (wyrmNum < WYRM_POP) {
        wyrmHead[wyrmNum] = 0;
        wyrmDir[wyrmNum] = getRandom32() & 3;
        wyrmX[wyrmNum][0] = x;
        wyrmY[wyrmNum][0] = y;
        wyrmNum++;
    }
}

void awyrm() {

    for (int wyrm = 0; wyrm < WYRM_POP; wyrm++) {

        int headPos = wyrmHead[wyrm];

        if (headPos < 0 /*|| (gameFrame & 31)*/)
            continue;

        int x, y;

        x = wyrmX[wyrm][headPos];
        y = wyrmY[wyrm][headPos];

        if (gameFrame & 1)
            return;

        int offsetX[] = {0, 1, 0, -1, 0};
        int offsetY[] = {-1, 0, 1, 0, 0};

        int candidateX = x + offsetX[wyrmDir[wyrm]];
        int candidateY = y + offsetY[wyrmDir[wyrm]];

        unsigned char *newHead = RAM + _BOARD + y * 40 + x;

        int mask = ATT_BLANK | ATT_GRAB;
        if (!rangeRandom(4) || wyrmHead[wyrm] < 2)
            mask |= ATT_DIRT;

        int whatsThere = CharToType[GET(*newHead)];
        bool moveable = Attribute[whatsThere] & mask;

        if (!moveable || !(getRandom32() & 63)) {

            int rdir = wyrmDir[wyrm];

            if (getRandom32() & 1)
                rdir = getRandom32() & 3;

            for (int dir = 0; dir < 4; dir++) {

                candidateX = x + offsetX[rdir];
                candidateY = y + offsetY[rdir];

                newHead = RAM + _BOARD + candidateY * 40 + candidateX;
                whatsThere = CharToType[GET(*newHead)];
                if (Attribute[whatsThere] & mask) {
                    wyrmDir[wyrm] = rdir;
                    moveable = true;

                    break;
                }

                rdir = (rdir + 1) & 3;
            }

            if (!moveable) {

                // reverse wyrm

                int tempX[WYRM_MAX], tempY[WYRM_MAX];
                for (int i = 0; i <= wyrmHead[wyrm]; i++) {
                    tempX[wyrmHead[wyrm] - i] = wyrmX[wyrm][i];
                    tempY[wyrmHead[wyrm] - i] = wyrmY[wyrm][i];
                }

                for (int i = 0; i <= wyrmHead[wyrm]; i++) {
                    wyrmX[wyrm][i] = tempX[i];
                    wyrmY[wyrm][i] = tempY[i];
                }
            }
        }

        if (moveable) {

            static const unsigned char wyrmChar[] = {
                0,                 // 0
                CH_WYRM_VERT_BODY, // 1   U
                CH_WYRM_BODY,      // 2   R
                CH_WYRM_CORNER_RU, // 3   RU
                CH_WYRM_VERT_BODY, // 4   D
                CH_WYRM_VERT_BODY, // 5   UD
                CH_WYRM_CORNER_RD, // 6   RD
                0,                 // 7
                CH_WYRM_BODY,      // 8   L
                CH_WYRM_CORNER_LU, // 9   LU
                CH_WYRM_BODY,      // 10  LR
                0,                 // 11
                CH_WYRM_CORNER_LD, // 12  LD
                0,                 // 13
                0,                 // 14
                0,                 // 15
            };

            // candidateX, candidateY --> new head position
            // wyrmX[wyrmHead], wyrmY[wyrmHead] --> old head position (new neck)
            // wyrmX[wyrmHead -1], wyrmY[wyrmHead - 1] -> previous neck

            unsigned char *segment;
            if (headPos > 0) {
                int dir =
                    dirFromCoords(candidateX, candidateY, wyrmX[wyrm][headPos],
                                  wyrmY[wyrm][headPos]) |
                    dirFromCoords(wyrmX[wyrm][headPos - 1],
                                  wyrmY[wyrm][headPos - 1],
                                  wyrmX[wyrm][headPos], wyrmY[wyrm][headPos]);
                segment = RAM + _BOARD + wyrmY[wyrm][headPos] * 40 +
                          wyrmX[wyrm][headPos];
                *segment = wyrmChar[dir];
            }

            wyrmX[wyrm][++headPos] = candidateX;
            wyrmY[wyrm][headPos] = candidateY;

            wyrmHead[wyrm] = headPos;

            segment = RAM + _BOARD + candidateY * 40 + candidateX;

            if (TYPEOF(*segment) == TYPE_DOGE)
                nDots(8, candidateX, candidateY, 2, -50, 3, 0, 0x10000);

            const unsigned char headCharacter[] = {
                CH_WYRM_HEAD_U,
                CH_WYRM_HEAD_R,
                CH_WYRM_HEAD_D,
                CH_WYRM_HEAD_L,
            };

            *segment = headCharacter[wyrmDir[wyrm]];
        }

        if (wyrmHead[wyrm] == WYRM_MAX - 1) {
            unsigned char *tailPos =
                RAM + _BOARD + wyrmY[wyrm][0] * 40 + wyrmX[wyrm][0];

            *tailPos = CH_DUST_0; //
            //   (Attribute[whatsThere] & ATT_DIRT)
            //                  ? /CH_DUST_0
            //              : (getRandom32() & 63) ? CH_DUST_0
            //                                     : CH_DOGE_00;

            if (wyrmY[wyrm][0] * TRILINES > lavaSurface) {
                if (!rangeRandom(50)) {
                    newWyrm(wyrmX[wyrm][0], wyrmY[wyrm][0]);
                }
            }

            for (int i = 0; i < WYRM_MAX - 1; i++) {
                wyrmX[wyrm][i] = wyrmX[wyrm][i + 1];
                wyrmY[wyrm][i] = wyrmY[wyrm][i + 1];
            }

            // tailPos = RAM + _BOARD + wyrmY[wyrm][0] * 40 + wyrmX[wyrm][0];
            // if (*tailPos == CH_WYRM_BODY)
            //     *tailPos = CH_WYRM_CORNER_LD;

            wyrmHead[wyrm]--;
        }
    }
}

void initNewGame() {

    actualScore = 0;
    partialScore = 0;
    lives = 3;
    invincible = false;
    cpulse = 0;
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

    dogeBlockCount = 0;
    cumulativeBlockCount = 0;
    explodeCount = 0;

    resetDelay = 0;
    // selectResetDelay = 0;

    showTool = false;

#if ENABLE_DEBUG
    selectDelay = 0;
#endif

    lavaSurface = 10000; // 0x1C2/3; //22 * PIECE_DEPTH - 1;
    showLava = false;
    showWater = false;

#if __FADE
    fade = 0;
#endif

    // lastDisplayMode = DISPLAY_NONE;
    switchOn = true;

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

    for (int wyrm = 0; wyrm < WYRM_POP; wyrm++) {
        wyrmHead[wyrm] = -1;
        wyrmDir[wyrm] = 0;
        for (int i = 0; i < WYRM_MAX; i++) {
            wyrmX[wyrm][i] = -1;
            wyrmY[wyrm][i] = -1;
        }
    }

    initPlayer();
    initSprites();

    for (int i = 0; i < RAINHAILSHINE; i++)
        rainX[i] = -1;

#if CIRCLE
    initSwipeCircle(CIRCLE_ZOOM_ZERO + 1);
#endif

    initCharAnimations();

#if COLSELECT
    extern unsigned char colr[5];
    colr[4] = currentPalette; //(cave + level) & 0xF;
#endif

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

    // FIXES PAL long-word display?
    availableIdleTime -= 30000;
    if (availableIdleTime > 0)
        availableIdleTime = 0;

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

                drawBigDigit(ch, x, y + sinoid[(x + (togt >> 2) + base) & 15],
                             colour, true);
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

// void add1PixObject(int x, int y, int pix) {

//     for (int whichDrop = 0; whichDrop < RAINHAILSHINE; whichDrop++) {
//         if (rainX[whichDrop] == -1) {

//             int dripX = x;
//             int dripY = y;

//             unsigned char *dripPos = RAM + _BOARD + (dripY * 40) + dripX;

//             rainType[whichDrop] = 2;
//             rainX[whichDrop] = ((dripX << 2) + pix ) << 8;
//             rainRow[whichDrop] = dripY;
//             rainY[whichDrop] = 0x6FFFF;
//             rainSpeedX[whichDrop] = ((((rangeRandom(8))<< 1) + 2) << 1) *
//             FaceDirection; rainSpeedY[whichDrop] = -0x2300 +
//             (rangeRandom(12000));

//             rainAge[whichDrop] = 32;

//             break;
//         }
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
    drawScreen(0);
    drawScreen(1);
    drawScore();

    drawPlayerSprite();

    // static int whichDrop = 0;
    if (!showingWords) {

        // bullets

        // static int whichDrop = 0;
        // if (!playerDead && JOY0_FIRE)
        //     sphereDot(playerX, playerY, 2, -130, 2, 5);

        // if (++whichDrop >= theCave->weather)
        //     whichDrop = 0;

        // real rain

        // if (theCave->weather && rainX[whichDrop] == 255) {

        //     rndX = getRandom32();

        //     int dripX = playerX + ((((rndX >> 12) & 0xFF) * 9) >> 8) - 4;
        //     int dripY = playerY + ((((rndX >> 7) & 0xFF) * 9) >> 8) - 4;

        //     if (dripX >= 1 && dripX <= 39 && dripY >= 1 && dripY <= 19) {

        //         unsigned char *dripPos = RAM + _BOARD + (dripY * 40) + dripX;
        //         if ((Attribute[CharToType[GET(*(dripPos - 40))]] & ATT_DRIP)
        //             && (Attribute[CharToType[GET(*dripPos)]] & ATT_BLANK)) {

        //             rainX[whichDrop] = (dripX << 2) + (rndX & 3);
        //             rainRow[whichDrop] = dripY;
        //             rainY[whichDrop] = -1;                  // embed in upper
        //             char rainSpeed[whichDrop] = RAIN_FORMING_DRIP;

        //             if (++whichDrop >= theCave->weather)
        //                 whichDrop = 0;
        //         }
        //     }
        // }
    }
    // }
    // }

    //    lastDisplayMode = displayMode;
}

void initGameDataStreams() {

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
                'P',
                'E',
                'R',
                'F',
                'E',
                'C',
                'T',
                END_STRING,
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
                        'D',
                        'O',
                        'G',
                        'E',
                        END_STRING,
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
                        'T',
                        'I',
                        'M',
                        'E',
                        END_STRING,
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

    availableIdleTime = 99000 - 1000;

#if __ENABLE_ATARIVOX
    if (RAM[_BUF_SPEECH] != 0xFF)
        availableIdleTime = 30000;
#endif

    if (!(SWCHA & 0xF0)) // UDLR at same time!
        invincible = true;

#if ENABLE_SHAKE

    if (shakeTime) {

        shakeTime--;

        shakeX = (rangeRandom(3) - 1) << 13;
        shakeY = (rangeRandom(6) - 3) << 15;
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

    // handleCaveCompletion();

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

#if ENABLE_OVERLAY
                overlayWord = 0;
#endif
                return;
            }
        }
    }

#define DOUBLE_TAP 8
#define TOOLONG 30

    if (!waitRelease && !(inpt4 & 0x80)) { // JOY0_FIRE)

        if (showTool)
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

        if (!exitMode && triggerPressCounter &&
            triggerOffCounter >= DOUBLE_TAP) {

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

#if __FADE
    if (fade < 0x10x) {

        fade += 1536;
        loadPalette();
    }
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

    showingWords = false;
    availableIdleTime = 120000 - 1000;

#if __ENABLE_ATARIVOX
    processSpeech();
#endif

    if (sparkleTimer)
        --sparkleTimer;

#if COLSELECT
    extern void colourAdjust();
    if (LEFT_DIFFICULTY_A)
        colourAdjust();
#endif

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

#if !COLSELECT

            time--;

            if ((time & 0xFF) == 0xFF) {

                time -= 0xC4; // magic!  - (-256+60)
                if (time < 0xA00) {
                    setScoreCycle(SCORELINE_TIME);
                    ADDAUDIO(SFX_COUNTDOWN2);
                }
            }
#endif
        }

        drawScore();
        rain();

        extern const unsigned short manPushing[][73];

        if (showTool)
            doDrawBitmap(manPushing[0], 90);

#if CIRCLE
        swipeCircle();
#endif

        setPalette();
        processCharAnimations();
    }

    // drawOverlayWords();
}

void conglomerate(unsigned char *thiss, int att) {

    int chr = GET(*thiss);
    int type = CharToType[chr];
    if ((Attribute[type] & att)) {

        unsigned char cong = CH_CONGLOMERATE;

        for (int i = 0; i < 4; i++) {
            int ch = *(thiss + dir[i]);
            if (Attribute[CharToType[GET(ch)]] & ATT_ROCK_DOGE)
                cong += merge[i];
        }

        *thiss = cong;
    }
}

void setupBoard() {

    // #if SCHEDULER==0
    if (frameCounter >= gameSpeed) {
        // #endif

        selectorCounter++;
        selectorCounter &= 3;

        // if (++frameCounter >= gameSpeed)
        frameCounter = 0;

        if (showLava) {

            if (lavaSurface && !(gameFrame & 15))
                lavaSurface -= gravity;

            if (!rangeRandom(3)) {
                int posX = ((scrollX * 5) >> 16) + rangeRandom(40);
                nDotsAtPixel(4, posX, lavaSurface + 1, 40, 0x10000);
            }
        }

        if (showWater) {

            extern void bubbles(int count, int dripX, int dripY, int age,
                                int speed);

            for (int i = 0; i < 4; i++) {
                int posX = ((scrollX * 5) >> 16) + rangeRandom(40);
                int deep =
                    lavaSurface + rangeRandom(21 * PIECE_DEPTH - lavaSurface);
                if (deep > 0 && deep < _ARENA_SCANLINES)
                    bubbles(1, posX, deep, 2240, 0x8000);
            }
        }

        gameFrame++;
        gravity = nextGravity;

        usableSWCHA = bufferedSWCHA;
        bufferedSWCHA = 0xFF;

        if (boardRow < 0) {
            boardRow = 21;
            boardCol = 39;
        }

        else {
            boardCol = -1;
            boardRow = 0;
        }

        gameSchedule = SCHEDULE_PROCESSBOARD;

        // if (theCave->flags & CAVEDEF_ROCK_GENERATE) {
        //     unsigned char *const generator = RAM + _BOARD + 40 + 19;
        //     if (Attribute[CharToType[GET(*generator)]] & ATT_BLANK)
        //         *generator = CH_ROCK_FALLING;
        // }

        processBoardSquares();

        // #if SCHEDULER==0
    }
    // #endif
}

void Explode(unsigned char *where, unsigned char explosionShape) {

    ADDAUDIO(SFX_EXPLODE);

    // bool player = false;

    for (int x = -1; x < 2; x++)
        for (int y = -40; y < 80; y += 40) {
            unsigned char *cell = where + y + x;
            unsigned char type = CharToType[GET(*cell)];
            if (Attribute[type] & ATT_EXPLODABLE) {
                *cell = explosionShape;
                if (explosionShape == CH_DOGE_00)
                    totalDogePossible++;
            }
            // if (type == TYPE_mellon_husk)
            //     player = true;
        }

    // if (player) {
    //     FLASH(0x44, 8);
    //     #if ENABLE_SHAKE
    //         shakeTime += 50;
    //     #endif
    // }
    // else
    FLASH(4, 4);
}

// 00 = facing left
// 01 = facing up
// 10 = facing right
// 11 = facing down

// turn right = -1
// turn left = +1

// CH_FIREFLY_0 --> facing LEFT
// CH_FIREFLY_1 --> FACING UP
// CH_FIREFLY_2 --> FACING RIGHT
// CH_FIREFLY_3 --> FACING DOWN

// Note: firefly init facing left (00), butterfly init facing down (11)
// fireflies turn to LEFT, butterflies turn to RIGHT

// void handleFly(unsigned char *thiss, int base, int turn, unsigned char
// explode) {

//     static const signed char move[] = {
//         -1, -40, +1, +40,
//     };

//     // turn = -1 (firefly) and +1 (butterfly)

//     // any killables?
//     for (int dir = 0; dir < 4; dir++)
//         if (Attribute[CharToType[GET(*(thiss + move[dir]))]] & ATT_KILLS_FLY)
//         {
//             Explode(this, explode);
//             return;
//         }

//     unsigned char replace = CH_BLANK | FLAG_THISFRAME;

//     // turn preferred direction
//     int dir = (*thiss) - base;                   // facing direction

//     unsigned char newdir = (dir + turn) & 3;
//     unsigned char *newpos = thiss + move[newdir];

//     if (Attribute[CharToType[GET(*newpos)]] & ATT_BLANK) {
//         *newpos = (base + newdir) | FLAG_THISFRAME;
//         *thiss = replace;
//         return;
//     }

//     // straight ahead
//     newpos = thiss + move[dir];

//     if (Attribute[CharToType[GET(*newpos)]] & ATT_BLANK) {
//         *newpos = (base + dir) | FLAG_THISFRAME;
//         *thiss = replace;
//         return;
//     }

//     // turn non-preferred direction
//     *thiss = base + ((dir - turn) & 3);
// }

void doRoll(unsigned char *thiss, unsigned char creature) {

    if (rangeRandom(50) || !(TYPEOF(*(thiss + 40)) == TYPE_GRINDER ||
                             CharToType[GET(*(thiss + 40))] == TYPE_GRINDER_1))
        return;

    // if (!((CharToType[GET(*(thiss + 40))] == TYPE_GRINDER)
    //     || (CharToType[GET(*(this+ 40))] == TYPE_GRINDER_1))
    //     && (!shakeTime || rangeRandom(50)))
    //     return;

    for (int offset = -1; offset < 2; offset += 2) {

        unsigned char *side = thiss + offset;
        if (!(*side & FLAG_THISFRAME)) {

            unsigned char sideType = CharToType[GET(*side)];
            if (Attribute[sideType] & ATT_BLANK) {

                unsigned char sideDownType = CharToType[GET(*(side + 40))];
                if (Attribute[sideDownType] & ATT_BLANK) {

                    int creatureType = CharToType[GET(creature)];
                    unsigned replacement = (Attribute[creatureType] &
                                            (ATT_ROCK | ATT_ROCK_DOGE))
                                               ? CH_DUST_0
                                               : CH_BLANK;
                    *thiss = replacement | FLAG_THISFRAME;
                    *(thiss + offset) = creature | FLAG_THISFRAME;

                    for (int i = 0; i < 4; i++)
                        conglomerate(thiss + dir[i],
                                     (ATT_ROCK_DOGE | ATT_GRAB));

                    return;
                }
            }
        }
    }
}

void chainReactDoge() {

    for (int i = 0; i < 4; i++) {

        int chr = *(thiss + dir[i]);
        if (!(chr & FLAG_THISFRAME)) {
            int type = CharToType[chr];

            if (Attribute[type] & ATT_ROCK_DOGE) {

                *(thiss + dir[i]) =
                    CH_DOGE_CONVERT |
                    FLAG_THISFRAME; //((dir[i] > 0) ? FLAG_THISFRAME : 0);
                ADDAUDIO(SFX_UNCOVER);
                dogeBlockCount++;
                cumulativeBlockCount++;

                for (int j = 0; j < 4; j++)
                    conglomerate(thiss + dir[i] + dir[j],
                                 (ATT_ROCK_DOGE | ATT_GRAB));
            }
        }
    }
}

void convertDogeToATT_ROCK() {

    //    int neighbours = 0;
    for (int i = 0; i < 4; i++) {

        int chr = GET(*(thiss + dir[i]));
        int type = CharToType[chr];

        if (Attribute[type] & ATT_ROCK_DOGE) {
            // neighbours++;
            *thiss = CH_ROCK_DOGE | FLAG_THISFRAME;

            //      conglomerate(this, (ATT_ROCK_DOGE | ATT_GRAB));
            return;
        }
    }

    // if (neighbours > 0)
    //     *thiss = CH_ROCK_DOGE | FLAG_THISFRAME;
}

void genericPush(int offsetX, int offsetY) {

    if (switchOn) {

        int adjustOffset = offsetY * 40 + offsetX;

        unsigned char *playerPos = RAM + _BOARD + playerY * 40 + playerX;
        unsigned char *pushPos = thiss + adjustOffset;

        if (playerPos == pushPos && (!(*playerPos & FLAG_THISFRAME))) {

            cpulse = 20;
            shakeTime = 3;
            ADDAUDIO(SFX_EXPLODE_QUIET);

            unsigned char *pushPosFurther = pushPos + adjustOffset;

            if (ATTRIBUTE_BIT(*pushPosFurther, ATT_BLANK | ATT_GRAB)) {

                // Note we may have a lagging flag clear until next frame but
                // who cares
                *pushPosFurther = *pushPos | FLAG_THISFRAME;
                *pushPos = CH_BLANK | FLAG_THISFRAME;

                autoMoveY = 0;
                autoMoveY = 0;
                autoMoveFrameCount = 0;
                playerX += offsetX;
                playerY += offsetY;

                nDots(RAINHAILSHINE / 2, boardCol + offsetX, boardRow + offsetY,
                      2, -150, 3, 4, 0x10000);
            }
        }

        int att = ATTRIBUTE(*pushPos);
        if ((GET(*pushPos) == CH_DOGE_CONVERT) ||
            att & (ATT_PERMEABLE | ATT_GRAB | ATT_ROCK_DOGE | ATT_ROCK)) {

            // dots for the disappearing object
            if (!(att & ATT_BLANK)) {

                if (rangeRandom(15)) {
                    *pushPos |= FLAG_THISFRAME;
                    //          shakeTime = 2;
                    return;
                }

                FLASH(0x32, 4);

                nDots(10, boardCol + offsetX, boardRow + offsetY, 2, 150, 3, 5,
                      0x10000);

                if (att & ATT_ROCK_DOGE) {
                    nDots(10, boardCol + offsetX, boardRow + offsetY, 2, 150, 3,
                          5, 0x10000);

                    *pushPos = CH_BLANK;

                    for (int i = 0; i < 4; i++)
                        conglomerate(pushPos + dir[i],
                                     (ATT_ROCK_DOGE | ATT_GRAB));

                    *pushPos = CH_DOGE_CONVERT | FLAG_THISFRAME;

                    return;
                }
            }

            *pushPos = *thiss | FLAG_THISFRAME;
            *thiss = offsetX ? CH_HORIZONTAL_BAR : CH_VERTICAL_BAR;

            // dots for a solid impact on NEXT move
            att = Attribute[CharToType[GET(*(pushPos + adjustOffset))]];
            if (!(att & ATT_BLANK)) {

                // int x[] = {4, 3, 0};
                // int y[] = {8, 4, 0};

                // nDots(3, boardCol + offsetX * 2, boardRow + offsetY * 2, 2,
                // 50,
                //     x[offsetX + 1], y[offsetY + 1], 0x10000);
            }
        }

        else
            *thiss = (*thiss) + 1; // reverse
    }
}

void genericPushReverse(int offsetX, int offsetY) {

    if (switchOn) {

        unsigned char *pushPos = thiss + offsetY * 40 + offsetX;
        int type = CharToType[GET(*pushPos)];

        if (type == TYPE_PUSHER) {
            *pushPos = *thiss | FLAG_THISFRAME;
            *thiss = CH_BLANK;
        } else
            *thiss = (*thiss) - 1;
    }
}

void processBoardSquares() {

    // int lastCreature = 12345;
    // if (!(getRandom32() & 0xFF)) {

    //     if (sound_max_volume)
    //         sound_max_volume = 0;
    //     else
    //         sound_max_volume = VOLUME_PLAYING;
    // }

    while (true) {

        //        if (T1TC >= availableIdleTime) {
        //            setScore(lastCreature);
        //            FLASH(0x42,4);
        //            return;
        //        }

        // tmp??
        rndX = (rndX >> 1) | (rndX << 31);

        int lastBoardRow = boardRow;
        int lastBoardCol = boardCol;

        boardCol += gravity;
        if (boardCol > 39 || boardCol < 0) {

            // lastCreature = 0;

            if (boardCol < 0) {
                boardCol = 39;
                boardRow--;
            }

            else {
                boardCol = 0;
                boardRow++;
            }

            if (boardRow > 21 || boardRow < 0) {

                awyrm();
                //                randomPebble();

                int lastCumulative = cumulativeBlockCount;
                if (!dogeBlockCount && cumulativeBlockCount) {

                    int val = 0;

                    if (cumulativeBlockCount < 10)
                        val = cumulativeBlockCount;
                    else if (cumulativeBlockCount < 20)
                        val = cumulativeBlockCount * 10;
                    else
                        val = cumulativeBlockCount * 100;

                    addScore(val);

                    cumulativeBlockCount = 0;
                }
                dogeBlockCount = 0;

                if (!cumulativeBlockCount && lastCumulative) {
                    killAudio(SFX_UNCOVER);
                }

                gameSchedule = SCHEDULE_START;

                if (!autoMoveFrameCount) { // delay until fully in new square

                    //                    chooseIdleAnimation();

                    bool oldDead = playerDead;

                    unsigned char *man = RAM + _BOARD + (playerY << 5) +
                                         (playerY << 3) + playerX;

                    int what = GET(*man);

                    if (invincible)
                        what = *man = CH_MELLON_HUSK;

                    int type = CharToType[what];
                    playerDead = (type != TYPE_MELLON_HUSK &&
                                  type != TYPE_MELLON_HUSK_PRE && !exitMode);

                    if (explodeCount > 0) {
                        nDots(1, playerX, playerY, 1, -1, 3, 0, 0x10000);
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
                        nDots(4, playerX, playerY, 1, -100, 3, 8, 0x10000);
                }

                return;
            }
        }

        thiss = RAM + _BOARD + (boardRow * 40) + boardCol;
        // lastCreature = GET(*thiss);

        // pcount++;
        // if (displayMode == DISPLAY_OVERVIEW)
        //     setScore(pcount);

        // if (CharToType[lastCreature] >= TYPE_MAX) {
        //     setScore(lastCreature);
        //     FLASH(0xD2,20);
        //     boardRow = lastBoardRow;
        //     boardCol = lastBoardCol;
        //     return;
        // }

#if WORST_TIMING

        int startCreatureTime = T1TC;
        int worstCreature = GET(*thiss);
#endif

        if (T1TC + 0x1000 /*worstRequiredTime[CharToType[GET(*thiss)]]*/ >=
            availableIdleTime) {

            boardRow = lastBoardRow;
            boardCol = lastBoardCol;
            return;
        }

        unsigned char creature = *thiss;

#if WORST_TIMING
//        worstEverCreature = creature;
#endif

        unsigned char *prev = thiss - 40 * gravity;
        unsigned char *next = thiss + 40 * gravity;

        if (!(creature & FLAG_THISFRAME)) {

            int type = CharToType[creature];

            //    #if SCHEDULER==1

            static const int isActive[] = {

                PH1 | PH2, // 0
                PH1 | PH4, // 1
                PH1 | PH2, // 2
                PH1,       // 3
            };

            if (Attribute[type] & isActive[selectorCounter]) {
                switch (type) {

                case TYPE_PEBBLE1:
                case TYPE_PEBBLE2: {

                    // don't form above player
                    if (boardCol == playerX && boardRow < playerY)
                        break;

                    const int offset[] = {-40, 40, -1, 1};
                    static int chance;
                    bool nearPlayer = false;
                    for (int i = 0; i < 4; i++) {
                        if (TYPEOF(*(thiss + offset[i])) == TYPE_MELLON_HUSK) {
                            nearPlayer = true;
                            break;
                        }
                    }

#define DECHANCE 5

                    if (nearPlayer) {
                        if (chance >= DECHANCE)
                            chance -= DECHANCE;
                    } else {
                        chance = 50;
                    }

                    if (!rangeRandom((chance))) {
                        *thiss = CH_PEBBLE_ROCK;
                        nDots(10, boardCol, boardRow, 2, 50, 3, 5, 0x10000);
                    }

                    break;
                }

                case TYPE_WATER: {

                    if ((boardRow - 1) * TRILINES >= lavaSurface) {

                        for (int i = 0; i < 4; i++) {
                            unsigned char *neighbour = thiss + dir[i];

                            int type = CharToType[GET(*neighbour)];
                            int att = Attribute[type];

                            if (att & ATT_DISSOLVES) {
                                *neighbour = CH_DUST_0;
                                break;
                            }
                        }
                    }
                    break;
                }

                case TYPE_LAVA: {

                    if (*thiss == CH_LAVA_2) {
                        if (!rangeRandom(20))
                            *thiss = rangeRandom(4) + CH_LAVA_0;
                        ;
                    }

                    else {
                        *thiss = rangeRandom(4) + CH_LAVA_0;

                        if (!rangeRandom(105) && (*thiss == CH_LAVA_2))
                            nDots(rangeRandom(4) + 2, boardCol, boardRow, 2, 50,
                                  3, 4, 0x8000);
                    }

                    if ((boardRow - 1) * TRILINES >= lavaSurface) {

                        for (int i = 0; i < 4; i++) {
                            unsigned char *neighbour = thiss + dir[i];
                            if (!(*neighbour & FLAG_THISFRAME)) {

                                int type = CharToType[GET(*neighbour)];
                                int att = Attribute[type];

                                if (att & ATT_DISSOLVES) {
                                    *neighbour = CH_LAVA_0;
                                    break;
                                }

                                if (att & ATT_MELTS && !rangeRandom(50)) {
                                    *neighbour = CH_DUST_0;
                                    nDots(8, boardCol + xdir[i],
                                          boardRow + ydir[i], 2, 50, 3, 4,
                                          0x10000);
                                    break;
                                }
                            }
                        }
                    }

                    break;
                }

                case TYPE_MELLON_HUSK:

                    if (!exitMode)
                        movePlayer(thiss);
                    break;

                default:
                    break;
                }

                switch (creature) {

                case CH_BELT_0:
                case CH_BELT_1:
                case CH_GRINDER_0:
                case CH_GRINDER_1: {

                    if (creature == CH_GRINDER_1)
                        conveyorDirection = 1;
                    else if (creature == CH_GRINDER_0)
                        conveyorDirection = -1;

                    unsigned char *up = thiss - 40;
                    unsigned char *up2 = thiss - 40 + conveyorDirection;

                    if (ATTRIBUTE_BIT(*up, ATT_CONVEYOR) &&
                        (ATTRIBUTE_BIT(*up2, ATT_BLANK | ATT_DISSOLVES)) &&
                        !(*up & FLAG_THISFRAME)) {
                        *up2 = (*up) | FLAG_THISFRAME;
                        *up = CH_DUST_0;

                        for (int i = 0; i < 4; i++) {
                            conglomerate(up + dir[i],
                                         (ATT_ROCK_DOGE | ATT_GRAB));
                            conglomerate(up2 + dir[i],
                                         (ATT_ROCK_DOGE | ATT_GRAB));
                        }

                        conglomerate(up, (ATT_ROCK_DOGE | ATT_GRAB));
                        conglomerate(up2, (ATT_ROCK_DOGE | ATT_GRAB));
                    }

                    //     else {

                    //         if (creature == CH_BELT_0 || creature ==
                    //         CH_BELT_1 ||
                    //             GET(*(thiss + 1)) == CH_BELT_0 || GET(*(thiss +
                    //             1)) == CH_BELT_1) {

                    //             if (!(*(this - 40) & FLAG_THISFRAME)) {
                    //                 if (Attribute[CharToType[GET(*(this -
                    //                 39))]] & ATT_BLANK) {
                    //                     int type = CharToType[GET(*(this -
                    //                     40))]; if (type == TYPE_DOGE || type
                    //                     == TYPE_ROCK_DOGE ||
                    //                         type == TYPE_ROCK) {
                    //                     *(this - 39) = *(this - 40) |
                    //                     FLAG_THISFRAME;
                    //                     *(this - 40) = CH_DUST_0;
                    //                     }
                    //                 }
                    //             }
                    //         }

                    //         else {
                    //         int up = *(this - 40);
                    //         if (!(up & FLAG_THISFRAME))
                    //         if (Attribute[CharToType[up]] & ATT_GRIND) {
                    //             nDots(3, boardCol, boardRow - 1, 2, 50, 3, 7,
                    //             0x10000); if (!rangeRandom(10)) { FLASH(0x22,
                    //             1); ADDAUDIO(SFX_EXPLODE_QUIET); shakeTime =
                    //             5;

                    //             if (CharToType[up] == TYPE_ROCK_DOGE)
                    //                 *(this - 40) = CH_DOGE_CONVERT |
                    //                 FLAG_THISFRAME;
                    //             else
                    //                 *(this - 40) = CH_DUST_0 |
                    //                 FLAG_THISFRAME;
                    //             nDots(RAINHAILSHINE, boardCol, boardRow - 1,
                    //             2, 50, 3, 7,
                    //                     0x10000);
                    //             }
                    //             // else {
                    //             //     ADDAUDIO(SFX_DIRT);
                    //             // }
                    //         }
                    //     }
                    //   }
                    break;
                }

                case CH_HUB:

                    if ((boardRow + 2) * TRILINES <= lavaSurface) {

                        if (GET(*(thiss + 80)) != CH_WATERFLOW_0)
                            *(thiss + 80) = CH_WATERFLOW_0 | FLAG_THISFRAME;

                        nDots(4, boardCol, boardRow + 2, 2, 50,
                              rangeRandom(2) * 5, rangeRandom(7), 0x10000);
                    }
                    break;

                case CH_HUB_1:

                    if (GET(*(thiss + 80)) == CH_WATERFLOW_0)
                        *(thiss + 80) = CH_BLANK;
                    break;

                case CH_WATERFLOW_0: {

                    if (!(gameFrame & 7)) {

                        int line = (boardRow)*TRILINES;
                        if (boardRow < 20 && line < lavaSurface)
                            *(thiss + 40) = CH_WATERFLOW_0;

                        else
                            *thiss = CH_BLANK;
                    }

                    nDots(1, boardCol, boardRow, 2, 100, 5 * rangeRandom(2), 10,
                          0x10000);
                    break;
                }

                    // case CH_HORIZ_ZAP_0: {

                    //     int att = Attribute[CharToType[GET(*(thiss + 1))]];
                    //     if (/*!(gameFrame & 3) &&*/ att & ATT_BLANK) {
                    //         *(thiss + 1) = CH_HORIZ_ZAP_0 | FLAG_THISFRAME;
                    //         *(this) = CH_HORIZ_ZAP_1 | FLAG_THISFRAME;
                    //     }
                    //     else {
                    //         if (att & ATT_PULL) {
                    //             *thiss = *(thiss + 1) | FLAG_THISFRAME;
                    //             *(thiss + 1) = CH_BLANK | FLAG_THISFRAME;

                    //             if (CharToType[GET(*(this - 1))] == TYPE_ZAP)
                    //                 *(this - 1) = CH_HORIZ_ZAP_0 |
                    //                 FLAG_THISFRAME;
                    //         }
                    //         else {
                    //             *thiss = CH_HORIZ_ZAP_2 | FLAG_THISFRAME;
                    //         }
                    //     }
                    //     conglomerate();
                    //     break;
                    // }

                    // case CH_HORIZ_ZAP_2: {
                    //     *thiss = CH_BLANK | FLAG_THISFRAME;
                    //     if (CharToType[GET(*(this - 1))] == TYPE_ZAP)
                    //         *(this - 1) = CH_HORIZ_ZAP_2 | FLAG_THISFRAME;
                    //     break;
                    // }

                case CH_PEBBLE_ROCK:
                    *thiss = CH_ROCK_DOGE | FLAG_THISFRAME;
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
                    *thiss = CH_BLANK;
                    break;

                case CH_DUST_ROCK_2:
                    *thiss = CH_DOGE_00;
                    ADDAUDIO(SFX_UNCOVER);
                    break;

                case CH_DUST_0:
                case CH_DUST_1:
                case CH_DUST_ROCK_0:
                case CH_DUST_ROCK_1:
                    (*thiss)++;
                    break;

                case CH_EXPLODETOBLANK_0:
                case CH_EXPLODETOBLANK_1:
                case CH_EXPLODETOBLANK_2:
                case CH_EXPLODETOBLANK_3:
                    *thiss = (creature + 1) | FLAG_THISFRAME;
                    break;

                case CH_EXPLODETOBLANK_4:
                    *thiss = CH_BLANK | FLAG_THISFRAME;
                    break;

                case CH_DOGE_CONVERT:

                    chainReactDoge();
                    *thiss = CH_DOGE_00;
                    // fall through

                case CH_DOGE_00:
                case CH_DOGE_01:
                case CH_DOGE_02:
                case CH_DOGE_03:
                case CH_DOGE_04:
                case CH_DOGE_05: {

                    if (creature == CH_DOGE_00)
                        convertDogeToATT_ROCK();

                    // if (CharToType[GET(*(this - 40))] != TYPE_DOGE &&
                    // !(getRandom32() & 0xFFF)) {
                    //     *thiss = CH_DUST_0 | FLAG_THISFRAME;
                    //     nDots(8, boardCol, boardRow, 2, 50, 3, 0, 0x10000);
                    //     break;
                    // }

                    int attrNext = ATTRIBUTE(*next);

                    if (attrNext & ATT_BLANK) {
                        *thiss = CH_DUST_0 | FLAG_THISFRAME;
                        *next = CH_DOGE_FALLING | FLAG_THISFRAME;

                        for (int i = 0; i < 4; i++)
                            conglomerate(thiss + dir[i],
                                         (ATT_ROCK_DOGE | ATT_GRAB));
                        break;
                    }

                    if (attrNext & ATT_ROLL)
                        doRoll(thiss, CH_DOGE_FALLING);

                    // conglomerate();

                    break;
                }

                case CH_FLIP_GRAVITY_0:
                case CH_FLIP_GRAVITY_2:
                case CH_FLIP_GRAVITY_1:

                case CH_BLOCK: {

                    unsigned char typeDown = CharToType[GET(*next)];
                    if (Attribute[typeDown] & ATT_BLANK) {
                        *next = *thiss | FLAG_THISFRAME;
                        *thiss = CH_DUST_0 | FLAG_THISFRAME;
                    }
                    break;
                }

                case CH_CONGLOMERATE:
                case CH_CONGLOMERATE_1:
                case CH_CONGLOMERATE_2:
                case CH_CONGLOMERATE_3:
                case CH_CONGLOMERATE_4:
                case CH_CONGLOMERATE_5:
                case CH_CONGLOMERATE_6:
                case CH_CONGLOMERATE_7:
                case CH_CONGLOMERATE_8:
                case CH_CONGLOMERATE_9:
                case CH_CONGLOMERATE_10:
                case CH_CONGLOMERATE_11:
                case CH_CONGLOMERATE_12:
                case CH_CONGLOMERATE_13:
                case CH_CONGLOMERATE_14:
                case CH_CONGLOMERATE_15:

                case CH_ROCK:

                case CH_ROCK_DOGE: {

                    if (GET(*thiss) == CH_CONGLOMERATE_15 &&
                        *Animate[TYPE_ROCK_DOGE_CRITICAL] ==
                            CH_CONGLOMERATE_15 &&
                        !rangeRandom(4)) {

                        bool close =
                            ((boardCol - playerX) * (boardCol - playerX) +
                                 (boardRow - playerY) * (boardRow - playerY) <
                             7);

                        int pulse = 3 + rangeRandom(RAINHAILSHINE / 2);
                        if (pulse && close) {
                            cpulse += 32;
                            //                            FLASH(0x42, 10);
                        }

                        nDots(pulse, boardCol, boardRow, 2, 50, 3, 4, 0x30000);
                    }

                    unsigned char typeDown = CharToType[GET(*next)];

                    if (Attribute[typeDown] & ATT_BLANK) {

                        if (ATTRIBUTE_BIT(*thiss, ATT_ROCK_DOGE))
                            *next = CH_ROCK_DOGE_FALLING | FLAG_THISFRAME;
                        else
                            *next = CH_ROCK_FALLING | FLAG_THISFRAME;

                        *thiss = CH_DUST_0 | FLAG_THISFRAME;

                        // int att = Attribute[CharToType[GET(*(next + 40))]];
                        // if (!(att & ATT_NOROCKNOISE))
                        //     ADDAUDIO(att & ATT_HARD ? SFX_ROCK : SFX_ROCK2);
                    }

                    else if (Attribute[typeDown] & ATT_ROLL) {

                        if (ATTRIBUTE_BIT(*thiss, ATT_ROCK_DOGE))
                            doRoll(thiss, CH_ROCK_DOGE_FALLING);
                        else
                            doRoll(thiss, CH_ROCK_FALLING);
                    }

                    for (int i = 0; i < 4; i++)
                        conglomerate(thiss + dir[i],
                                     (ATT_ROCK_DOGE | ATT_GRAB));

                    break;
                }

                case CH_DOGE_FALLING:
                case CH_ROCK_FALLING:
                case CH_ROCK_DOGE_FALLING: {

                    unsigned char typeDown = CharToType[GET(*next)];
                    if (Attribute[typeDown] & ATT_BLANK) {

                        *thiss = CH_DUST_0 | FLAG_THISFRAME;

                        *next = creature | FLAG_THISFRAME;

                        unsigned char *nextNext = next + 40;
                        unsigned char downCh = GET(*nextNext);
                        typeDown = CharToType[downCh];
                        int attNextNext = Attribute[typeDown];

                        if (downCh != CH_ROCK_FALLING &&
                            downCh != CH_DOGE_FALLING &&
                            downCh != CH_ROCK_DOGE_FALLING) {

                            int sfx = 0;

                            // if (!(attNextNext & ATT_NOROCKNOISE)) {

                            //     if (creature == CH_ROCK_FALLING)
                            //         sfx = attNextNext & ATT_HARD ? SFX_ROCK :
                            //         SFX_ROCK2;
                            //     else
                            //         sfx = SFX_DOGE;
                            // }

                            if (attNextNext & ATT_HARD) {
                                if (creature == CH_ROCK_FALLING ||
                                    creature == CH_ROCK_DOGE_FALLING) {

                                    sfx = SFX_ROCK;

                                    unsigned char *dL = thiss + 40 - 1;
                                    unsigned char *dR = dL + 2;

                                    if (!CharToType[GET(*dR)]) {
                                        nDots(4, boardCol, boardRow + 1, 2, 10,
                                              3, 7, 0x10000);
                                    }

                                    if (!CharToType[GET(*dL)]) {
                                        nDots(4, boardCol, boardRow + 1, 2, 10,
                                              3, 7, 0x10000);
                                    }
                                }
                                // else
                                //     sfx = SFX_DOGE;
                            }

                            if (sfx)
                                ADDAUDIO(sfx);
                        }
                    }

                    else if (Attribute[typeDown] & ATT_SQUASHABLE_TO_BLANKS)
                        Explode(next, CH_DUST_0 | FLAG_THISFRAME);

                    // else if (typeDown == TYPE_BUTTERFLY)
                    //     Explode(next, CH_EXPLODETODOGE_0 |
                    //     FLAG_THISFRAME);

                    else {

                        // stop falling
                        unsigned char sfx = 0;
                        int att = ATTRIBUTE(*next);

                        switch (creature) {
                        case CH_ROCK_FALLING: {
                            *thiss = CH_ROCK;
                            sfx = att & ATT_HARD ? SFX_ROCK : SFX_ROCK2;
                            break;
                        }

                        case CH_ROCK_DOGE_FALLING: {
                            *thiss = CH_ROCK_DOGE;
                            break;
                        }

                        case CH_DOGE_FALLING: {
                            *thiss = CH_DOGE_00;
                            sfx = SFX_DOGE;
                            break;
                        }
                        }

                        if (creature != CH_DOGE_FALLING)
                            nDots(4, boardCol, boardRow, 2, 40,
                                  getRandom32() & 3, 10, 0x10000);

                        if (att & ATT_ROLL)
                            doRoll(thiss, creature);

                        if (sfx && !(att & ATT_NOROCKNOISE))
                            ADDAUDIO(sfx);
                    }

                    // conglomerate();
                    break;
                }

                case CH_DOORCLOSED:
                    if (!doges) {
                        *thiss = CH_DOOROPEN_0;
                        FLASH(0x28, 10);
                    }
                    break;

                case CH_MELLON_HUSK_BIRTH:

                    // playerX = boardCol;
                    // playerY = boardRow;

                    if (
#if CIRCLE
                        checkSwipeFinished()
#if ENABLE_OVERLAY
                            && fSpeed == -1
#endif
                        //                        && (displayMode ==
                        //                        DISPLAY_OVERVIEW

                        ||
#endif
                        (!isScrolling())) {

                        // SAY(__WORD_LETSGOBABY);

                        // ADDAUDIO(SFX_PUSH);
                        // startPlayerAnimation(ID_Shades); //(ID_Startup);
                        *thiss = CH_MELLON_HUSK; // | FLAG_THISFRAME;
                    }
                    break;

                case CH_DOGE_GRAB:
                    if (*Animate[TYPE_GRAB] == CH_BLANK)
                        *thiss = CH_BLANK;
                    break;

                default:
                    break;
                }
            }

            // Any blanks/dissolves underwater/lava gets transformed to
            // water/lava chars

            if (boardRow * TRILINES >= lavaSurface) {
                if (!(*thiss & FLAG_THISFRAME)) {
                    if (Attribute[type] & (ATT_BLANK | ATT_DISSOLVES)) {
                        if (!rangeRandom(4)) {
                            int rr = getRandom32() & 3;
                            *thiss = showLava ? CH_LAVA_2 : CH_WATER_0 + rr;
                        }
                    }
                }
            }
        }

        // Clear any "scanned this frame" objects on the previous line
        // note: we need to also do the last row ... or do we? if it's steel
        // wall, no
        if ((gravity > 0 && boardRow > 1) || (gravity < 0 && boardRow < _BOARD_ROWS - 1))
            *prev &= ~FLAG_THISFRAME;

#if WORST_TIMING

        //        setScore(worstEver);

        int timeDelta = T1TC - startCreatureTime;
        int type = CharToType[worstCreature];
        if (timeDelta > worst[type])
            worst[type] = timeDelta;

        if (timeDelta > worstEver) {
            worstEver = timeDelta;
            worstEverCreature = worstCreature;
            doges = worstEverCreature;
        }
#endif
    }
}

// EOF