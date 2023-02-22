#include <stdbool.h>

#include "attribute.h"
#include "defines_cdfj.h"
#include "defines_from_dasm_for_c.h"

#include "defines.h"

#include "main.h"

#include "amoeba.h"
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
#include "menu.h"
#include "overlay.h"
#include "player.h"
#include "random.h"
#include "rockford.h"
#include "score.h"
#include "scroll.h"
#include "sound.h"
#include "swipeCircle.h"


#if WORST_TIMING
        int worstEver = 0;
        int worstEverCreature = -1;
#endif

int togt;

////////////////////////////////////////////////////////////////////////////////
// CONFIGURABLE UX

#define DEAD_RESTART        20     /* # frames to hold trigger after loss of life, to start next life */
#define MAX_PEBBLES        100     /* # random pebbles to put in dirt */

    // Delays on RESET and SELECT are to allow non-ambiguous press of SELECT+RESET for suicide

#define RESET_DELAY         20     /* # frames to hold RESET before it is detected */
#define SELECT_DELAY        10     /* # frames to hold SELECT before it is detected */



////////////////////////////////////////////////////////////////////////////////


static int boardRow;
int boardCol;

static bool magicWallActive;

int canPlay[5];


#if ENABLE_RAINBOW
bool rainbow;
#endif

bool lockDisplay;
bool rageQuit;
unsigned char *this;
unsigned char inpt4;
unsigned char swcha;
int millingTime;                // negative = expired
int diamonds;
int time;
int level;

bool waitRelease;

unsigned char mm_tv_type;  // 0 = NTSC, 1 = PAL, 2 = PAL-60, 3 = SECAM... start @ NTSC always
//unsigned char autoTVType;
bool exitTrigger;
unsigned int idleTimer;
unsigned int sparkleTimer;
bool showingWords;

int exitMode;
static int frameCounter;

unsigned char enableParallax;

unsigned int availableIdleTime;
int uncoverTimer;
unsigned int uncoverCount;
bool invincible;

int wordColour;
int spacing;
int perfectTimer;

int gameFrame;
int gameSpeed;
enum DisplayMode displayMode;
enum DisplayMode lastDisplayMode;
unsigned int triggerPressCounter;
static unsigned int triggerOffCounter;



int lives;
int selectResetDelay;;
int resetDelay;

#if ENABLE_DEBUG
static int selectDelay;
#endif

unsigned int currentPalette;

// int diamondValue;
//int extraDiamondValue;
int cave;
bool caveCompleted;
unsigned char bufferedSWCHA;
unsigned int usableSWCHA;
unsigned int inhibitSWCHA;

#if __FADE
unsigned int fade = 0;
#endif

#if __ENABLE_WATER
int water
unsigned char *lastWater;
#endif

#if __ENABLE_LAVA
int lava;
#endif


#if ENABLE_SHAKE
int shakeX, shakeY;
int shakeTime;
#endif



// COMPILE-TIME REVERSE BITS IN BYTE
#define RVS(a) ( \
      ((((a) >> 0) & 1) << 7) \
    | ((((a) >> 1) & 1) << 6) \
    | ((((a) >> 2) & 1) << 5) \
    | ((((a) >> 3) & 1) << 4) \
    | ((((a) >> 4) & 1) << 3) \
    | ((((a) >> 5) & 1) << 2) \
    | ((((a) >> 6) & 1) << 1) \
    | ((((a) >> 7) & 1) << 0) \
    )

#define P0(a) RVS(a)
#define P1(a) P0(a), P0(a+1)
#define P2(a) P1(a), P1(a+2)
#define P3(a) P2(a), P2(a+4)
#define P4(a) P3(a), P3(a+8)
#define P5(a) P4(a), P4(a+16)
#define P6(a) P5(a), P5(a+32)
#define P7(a) P6(a), P6(a+64)
#define P8(a) P7(a), P7(a+128)

// Want to call RVS(n) for 0-255 values. The weird #defines above allows a single-call
// It's effectively a recursive power-of-two call of the base RVS macro

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

    SystemReset,                // _FN_SYSTEM_RESET

    MenuOverscan,               // _FN_MENU_OS
    MenuVerticalBlank,          // _FN_MENU_VB
    SchedulerMenu,              // _FN_MENU_IDLE

    initNextLife,               // _FN_INIT_GAME_KERNEL
    GameOverscan,               // _FN_GAME_OS
    GameVerticalBlank,          // _FN_GAME_VB
    Scheduler,                  // _FN_GAME_IDLE
};



int main() {                    // <-- 6507/ARM interfaced here!

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

    for(int i = 0; i <= 34; i++)
        QINC[i] = 0x100;              // data stream increments -> 1.0

    initKernel(KERNEL_COPYRIGHT);

    // needed in case startup screen is mid-view
    //createParallaxCharset();

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




void setJumpVectors(int midKernel, int exitKernel) {

    for (int i=0; i < _ARENA_SCANLINES; i++)
        RAM_SINT[(_BUF_JUMP1 / 2) + i] = midKernel;
    RAM_SINT[ _BUF_JUMP1_EXIT / 2 ] = exitKernel;
}


void initNewGame() {

    actualScore = 0;
    partialScore = 0;
    lives = 3;
    invincible = false;
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
    magicWallActive = false;

    perfectTimer = 80;

    exitMode = 0;
    idleTimer = 0;
    sparkleTimer = 0;
    gameFrame = 0;
    triggerPressCounter = 0;
    triggerOffCounter = 0;
    // expandSpeed = 0;

    resetDelay = 0;
    selectResetDelay = 0;

    #if ENABLE_DEBUG
    selectDelay = 0;
    #endif

#if __FADE
    fade = 0;
#endif
    
    uncoverTimer = 25;
//    ADDAUDIO(SFX_UNCOVER);

    uncoverCount = 880;

    lastDisplayMode = DISPLAY_NONE;

    #define SPEED_INCREMENT (0xC000)
    #define SPEED_INCREMENT_60 (SPEED_INCREMENT)
    #define SPEED_INCREMENT_50 (SPEED_INCREMENT * 50 / 60)

    static const unsigned int speedo[] = {

        SPEED_INCREMENT_60,
        SPEED_INCREMENT_50,
        SPEED_INCREMENT_60,
        SPEED_INCREMENT_50,
    };


    gameSpeed = SPEED_BASE + (((5 - level) * speedo[mm_tv_type]) >> 17);


    frameCounter = gameSpeed;               // force initial 

    initRockford();
    initSprites();

    for (int i = 0; i < RAINHAILSHINE; i++)
        rainX[i] = 255;

    initAmoeba();

#if CIRCLE
    initSwipeCircle(CIRCLE_ZOOM_ZERO + 1);
#endif

    initCharAnimations();
    AnimCount[TYPE_MAGICWALL] = 0;


#if ENABLE_OVERLAY

extern int fSpeed;

    if (overlayWord != overlayBoulderDash) {
        overlayWord = overlayBoulderDash;

        fSpeed = 0x120;
        fIndex = 0;
        rotateOffset = 0;
    }
 #endif

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

            // add pebbles
            for (int pebble = 0; pebble < MAX_PEBBLES; pebble++) {
                unsigned char *idx = RAM + _BOARD + rangeRandom(840);
                if (GET(*idx) == CH_DIRT)
                    *idx = (CH_PEBBLE1 /*| FLAG_UNCOVER*/) + (getRandom32() & 1);
            }
            
            if (!totalDiamondsPossible)
                totalDiamondsPossible = -1;     // indicates "perfect" not possible

    #if __ENABLE_LAVA
            if (lava)
                ADDAUDIO(SFX_LAVA);
    #endif

            gameSchedule = SCHEDULE_START;
            break;
        }
}



void Scheduler() {

    static void (*const scheduleFunc[])() = {

        setupBoard,                 // SCHEDULE_START
        processBoardSquares,        // SCHEDULE_PROCESSBOARD
        scheduleUnpackCave,         // SCHEDULE_UNPACK_CAVE
    };

    (*scheduleFunc[gameSchedule])();

    // if (gameSchedule == SCHEDULE_PROCESSBOARD && T1TC > availableIdleTime) {
    //     unsigned char *c = RAM + _BOARD + (boardRow * 40) + boardCol;
    //     worstEverCreature = GET(*c);
    //     worstEver = GET(*c);
    //     setScore(worstEverCreature);
    // }
}


const unsigned char sinoid[] = { 0,1,1,3,5,6,6,7, 7,6,6,5,3,1,1,0};



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
        while (*++width != NEW_LINE);

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

                drawBigDigit(
                    ch,
                    x,
                    y + sinoid[(x + (togt>>2) + base) & 15],
                    colour,
                    true);
            }
            x--;
        }

        y += spacing >> 1;
        base += 3;
    }
}



void drawOverlayWords() {
 return; //tmp

    togt++;

    if (
#if __ENABLE_DEMO
        !demoMode && 
#endif
        displayMode != DISPLAY_OVERVIEW && uncoverTimer > 1 && uncoverTimer < 20)
        drawWord(theCaveData, 70);

    else if (!lives && *playerAnimation == FRAME_BLANK) {
        static const unsigned char gameOver[] = { 'G','A','M','E',NEW_LINE,'O','V','E','R',END_STRING };
        drawWord(gameOver, 70);
    }
}



void drawOverscanThings() {

    doFlash();

    updateAnimation();

    // zap sprite buffers (expensive!)
    unsigned int *p = (unsigned int *)(RAM + _BUF_GRP0A);
    for (int i = 0; i < _ARENA_SCANLINES / 2; i++)
        p[i] = 0;

    if (exitMode)
        displayMode = DISPLAY_NORMAL;

    if (displayMode == DISPLAY_OVERVIEW) {

        drawOverviewScreen(0, 11);
        drawPlayerSmallSprite();
    }

    else {

        if (displayMode == DISPLAY_HALF) {
            // createParallaxCharset();
            drawHalfSprite();
        }

        if (lastDisplayMode == DISPLAY_OVERVIEW) {
            unsigned char *p = RAM + _BUF_PF0_LEFT + DIGIT_SIZE;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < _ARENA_SCANLINES * 6; j += _ARENA_SCANLINES)
                    *(p + i + j) = 0;
        }

        if (lastDisplayMode != displayMode)
            resetTracking();
        
        Scroll();
//        drawScore();

        if (displayMode == DISPLAY_NORMAL) {

            createParallaxCharset();
            drawScreen();
        drawScore();

            drawPlayerSprite();

            static int whichDrop = 0;
            if (!showingWords && theCave->weather && rainX[whichDrop] == 255) {

                rndX = getRandom32();

                int dripX = rockfordX + ((((rndX >> 12) & 0xFF) * 9) >> 8) - 4;
                int dripY = rockfordY + ((((rndX >> 7) & 0xFF) * 9) >> 8) - 4;

                if (dripX >= 1 && dripX <= 39 && dripY >= 1 && dripY <= 19) {

                    unsigned char *dripPos = RAM + _BOARD + (dripY * 40) + dripX;
                    if ((Attribute[CharToType[GET(*(dripPos - 40))]] & ATT_DRIP)
                        && (Attribute[CharToType[GET(*dripPos)]] & ATT_BLANK)) {

                        rainX[whichDrop] = (dripX << 2) + (rndX & 3);
                        rainRow[whichDrop] = dripY;
                        rainY[whichDrop] = -1;                  // embed in upper char
                        rainSpeed[whichDrop] = RAIN_FORMING_DRIP;

                        if (++whichDrop >= theCave->weather)
                            whichDrop = 0;
                    }
                }
            }            
        }
    }
    
    lastDisplayMode = displayMode;
}



void initGameDataStreams() {

    struct ptrs {
        unsigned char dataStream;
        unsigned short buffer;
    };

    static const struct ptrs streamInits[] = {

        {   _DS_PF0_LEFT,   _BUF_PF0_LEFT   },
        {   _DS_PF1_LEFT,   _BUF_PF1_LEFT   },
        {   _DS_PF2_LEFT,   _BUF_PF2_LEFT   },
        {   _DS_PF0_RIGHT,  _BUF_PF0_RIGHT  },
        {   _DS_PF1_RIGHT,  _BUF_PF1_RIGHT  },
        {   _DS_PF2_RIGHT,  _BUF_PF2_RIGHT  },
        {   _DS_AUDV0,      _BUF_AUDV       },
        {   _DS_AUDC0,      _BUF_AUDC       },
        {   _DS_AUDF0,      _BUF_AUDF       },
        {   _DS_COLUPF,     _BUF_COLUPF     },
        {   _DS_COLUBK,     _BUF_COLUBK     },
        {   _DS_COLUP0,     _BUF_COLUP0     },
        {   _DS_COLUP1,     _BUF_COLUP1     },
        {   _DS_GRP0a,      _BUF_GRP0A      },
        {   _DS_GRP1a,      _BUF_GRP1A      },
        #if __ENABLE_ATARIVOX
        {   _DS_SPEECH,     _BUF_SPEECH     },
        #endif
        {   0x21,           _BUF_JUMP1      },
    };

    for (unsigned int i = 0; i < sizeof(streamInits)/sizeof(struct ptrs); i++)
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
            addScore(theCave->extraDiamondValue * -diamonds);
            addScore(2 * (time >> 8));
            exitMode = 0;
            caveCompleted = true;
            return;
        }

        // if (playerAnimationID != ID_Shades && !autoMoveFrameCount && exitMode > 150)
        //     startPlayerAnimation(ID_Shades);

        static int slowDown = 0;

        if (perfectTimer && !totalDiamondsPossible) {   // got 'em all!
            static const unsigned char perfect[] = {
                'P','E','R','F','E','C','T',END_STRING,
            };
            drawWord(perfect, 60);
            perfectTimer--;
        }


        else {
            
#if __ENABLE_DEMO
            if (!demoMode) {
#endif                
                if (diamonds < 0) {

                    static const unsigned char extraBonus[] = {
                        'D','I','A','M','O','N','D','S',END_STRING,
                    };

                    if (exitMode == 51)
                        ADDAUDIO(SFX_UNCOVER);

                    if (exitMode < 50 && --slowDown < 0) {

                        ++diamonds;
                        addScore(theCave->extraDiamondValue);
                        slowDown = 5;
                        exitMode = diamonds ? 50 : 80;

                        if (!diamonds) {
                            ADDAUDIO(SFX_BLIP);
                            killAudio(SFX_UNCOVER);
                        }
                    }
                    
                    drawWord(extraBonus, 40);
                    bigStuff(-diamonds);
                }

                else if (exitMode < 50 && time > 0) {

                    if (exitMode == 7)
                        ADDAUDIO(SFX_UNCOVER);
                    
                    static const unsigned char extraBonus[] = {
                        'T','I','M','E',END_STRING,
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


    if (!(SWCHA & 0xF0))            // UDLR at same time!
        invincible = true;


#if ENABLE_SHAKE

    if (shakeTime) {

        shakeTime--;

        shakeX = (rangeRandom(3) - 1) << 13;
        shakeY = (rangeRandom(6) - 3) << 15;
    }
    else
        shakeY = shakeX = 0;

#endif

    initGameDataStreams();
    playAudio();

    if (gameSchedule == SCHEDULE_UNPACK_CAVE)
        return;


    getJoystick();
    bufferedSWCHA &= swcha | inhibitSWCHA;


    if (frameCounter > ((gameSpeed * 5) >> 3)) {
        bufferedSWCHA |= inhibitSWCHA;
        inhibitSWCHA = 0;
    }


#if __ENABLE_LAVA | ENABLE_WATER
    if ((rndX & 0x1ff) < 20) {
#endif

#if __ENABLE_LAVA
        if (lava > 1)
            lava--;
#endif

#if __ENABLE_WATER
        if (water > 1)
            water--;
#endif

#if __ENABLE_LAVA | ENABLE_WATER
        rndX >>= 1;
    }
#endif

    if (magicWallActive) {
        if (millingTime)
            millingTime--;
        if (!millingTime) {
            magicWallActive = false;
            Animate[TYPE_MAGICWALL] = AnimateBase[TYPE_MAGICWALL];
            AnimCount[TYPE_MAGICWALL] = 0;
            killAudio(SFX_MAGIC);
        }
    }


    if (lastAmoebaCanGrow && millingTime) {
        millingTime--;
        expandSpeed = millingTime ? EXPAND_SPEED  : EXPAND_SPEED * 10;
    }


    // handleCaveCompletion();

    if (waitRelease) {
        if ((inpt4 & 0x80) && (swcha == 0xFF))
            waitRelease = false;
    }
    else {

        if (!(SWCHB & 0b11)    // select+reset
            || (swcha == 0xFF && !(inpt4 & 0x80))) {
                selectResetDelay++;
        }

        else {

            selectResetDelay = 0;

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

    if (!waitRelease && !(inpt4 & 0x80)) { //JOY0_FIRE)

        if (!exitMode && triggerOffCounter && triggerOffCounter < DOUBLE_TAP && triggerPressCounter < TOOLONG) {

            // Handle double-click view mode switching

//            ADDAUDIO(SFX_BLIP);

            switch (displayMode) {
            case DISPLAY_NORMAL:
            case DISPLAY_HALF :
                displayMode = DISPLAY_OVERVIEW;
                break;
            default:
                displayMode = DISPLAY_NORMAL;
                break;
            }

            triggerPressCounter = 0;
            waitRelease = true;
        }
        else {
            triggerPressCounter++;
            triggerOffCounter = 0;
        }

        // Long-press after death will restart
        if (rockfordDead && triggerPressCounter == DEAD_RESTART) {

            waitRelease = true;
//            ADDAUDIO(SFX_BLIP);

            if (lives) {
                initKernel(KERNEL_STATS);
            }
            else
                initKernel(KERNEL_MENU);


            return;
        }

    }
    else {

        if (!exitMode && triggerPressCounter && triggerOffCounter >= DOUBLE_TAP) {
            
            if (triggerPressCounter < TOOLONG) {
                if (displayMode == DISPLAY_NORMAL)
                    displayMode = DISPLAY_HALF;
                else
                    displayMode = DISPLAY_NORMAL;

//                ADDAUDIO(SFX_BLIP);

            }
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

    frameCounter++;

    if (gameSchedule != SCHEDULE_UNPACK_CAVE) {

        // if (uncoverTimer > 0) {
        //     for (int i = 0; i < 6; i++)
        //         for (int scan = 0; scan < 10; scan++) {
        //             unsigned char *c = RAM + _BOARD + rangeRandom(880);
        //             if (*c & FLAG_UNCOVER) {
        //                 *c &= ~FLAG_UNCOVER;
        //                 uncoverCount--;
        //                 break;
        //             }
        //         }
        // }

        // else
            handleCaveCompletion();



        if (
#if CIRCLE            
            checkSwipeFinished() &&
#endif
            time && !rockfordDead && !exitMode) {

        #if !COLSELECT
        
            if (uncoverTimer <= 0)
                time--;

            if ((time & 0xFF) == 0xFF) {

                time -= 0xC4;           // magic!  - (-256+60)
                if (time < 0xA00) {
                    setScoreCycle(SCORELINE_TIME);
                    ADDAUDIO(SFX_COUNTDOWN2);
                }
            }
        #endif
        }

        if (displayMode == DISPLAY_OVERVIEW)
            drawOverviewScreen(11, 22);

        else if (displayMode == DISPLAY_HALF)
            drawHalfScreen();


#if CIRCLE
        swipeCircle();
#endif


        setPalette();
        processCharAnimations();

#if ENABLE_OVERLAY
        GameScheduleDrawOverlay();
#endif
    }


    drawOverlayWords();
}


void conglomerate() {

    int type = CharToType[GET(*this)];
    if (type == TYPE_BOULDER) {

        *this = CH_CONGLOMERATE;

        const int dir[] = { -40, 40, -1, 1 };
        const int merge[] = { 1, 4, 8, 2 };

        for (int i = 0; i < 4; i++) {

            int type = CharToType[GET(*(this + dir[i]))];
            if (Attribute[type] & ATT_PUSH) {
                *this |= merge[i];
            }
        }
    }
}



void setupBoard() {

    if (frameCounter > gameSpeed) {

        frameCounter = 0;
        gameFrame++;

        usableSWCHA = bufferedSWCHA;
        bufferedSWCHA = 0xFF;

        boardCol = -1;
        boardRow = 0;

        if (uncoverTimer <= 0)
            checkAmoeba();

        gameSchedule = SCHEDULE_PROCESSBOARD;


        if (theCave->flags & CAVEDEF_BOULDER_GENERATE) {
            unsigned char *const generator = RAM + _BOARD + 40 + 19;
            if (Attribute[CharToType[GET(*generator)]] & ATT_BLANK)
                *generator = CH_BOULDER_FALLING;
        }

        processBoardSquares();

    }
}



void Explode(unsigned char *where, unsigned char explosionShape) {


    ADDAUDIO(SFX_EXPLODE);

    bool player = false;

    for (int x = -1; x < 2; x++)
        for (int y = -40; y < 80; y += 40) {
            unsigned char *cell = where + y + x;
            unsigned char type = CharToType[GET(*cell)];
            if (Attribute[type] & ATT_EXPLODABLE) {
                *cell = explosionShape;
                if (explosionShape == CH_DOGE_00)
                    totalDiamondsPossible++;
            }
            if (type == TYPE_ROCKFORD)
                player = true;
        }


    if (player) {
        FLASH(0x44, 8);
        #if ENABLE_SHAKE
            shakeTime += 50;
        #endif
    }
    else
        FLASH(4, 4);
}


//00 = facing left
//01 = facing up
//10 = facing right
//11 = facing down

// turn right = -1
// turn left = +1


// CH_FIREFLY_0 --> facing LEFT
// CH_FIREFLY_1 --> FACING UP
// CH_FIREFLY_2 --> FACING RIGHT
// CH_FIREFLY_3 --> FACING DOWN

// Note: firefly init facing left (00), butterfly init facing down (11)
// fireflies turn to LEFT, butterflies turn to RIGHT


void handleFly(unsigned char *this, int base, int turn, unsigned char explode) {


    static const signed char move[] = {
        -1, -40, +1, +40,
    };


    // turn = -1 (firefly) and +1 (butterfly)

    // any killables?
    for (int dir = 0; dir < 4; dir++)
        if (Attribute[CharToType[GET(*(this + move[dir]))]] & ATT_KILLS_FLY) {
            Explode(this, explode);
            return;
        }

    unsigned char replace = CH_BLANK | FLAG_THISFRAME;

    // turn preferred direction
    int dir = (*this) - base;                   // facing direction

    unsigned char newdir = (dir + turn) & 3;
    unsigned char *newpos = this + move[newdir];

    if (Attribute[CharToType[GET(*newpos)]] & ATT_BLANK) {
        *newpos = (base + newdir) | FLAG_THISFRAME;
        *this = replace;
        return;
    }

    // straight ahead
    newpos = this + move[dir];

    if (Attribute[CharToType[GET(*newpos)]] & ATT_BLANK) {
        *newpos = (base + dir) | FLAG_THISFRAME;
        *this = replace;
        return;        
    }

    // turn non-preferred direction
    *this = base + ((dir - turn) & 3);
}



void doRoll(unsigned char *this, unsigned char creature) {

    for (int offset = -1; offset < 2; offset += 2) {

        unsigned char *side = this + offset;
        if (!(*side & FLAG_THISFRAME)) {

            unsigned char sideType = CharToType[GET(*side)];
            if (Attribute[sideType] & ATT_ROCKFORDYBLANK) {

                unsigned char sideDownType = CharToType[GET(*(side + 40))];
                if (Attribute[sideDownType] & ATT_ROCKFORDYBLANK) {

                    if (sideDownType == TYPE_ROCKFORD || sideType == TYPE_ROCKFORD) {
                        if (GET(*this) == CH_BOULDER)
                            *this = CH_BOULDER_SHAKE | FLAG_THISFRAME;
                    }
                    else {

                        unsigned replacement = CharToType[GET(creature)] == TYPE_BOULDER ? CH_DUST_0 : CH_BLANK;
                        *this = replacement | FLAG_THISFRAME;
                        *(this + offset) = creature | FLAG_THISFRAME;
                        return;
                    }
                }
            }
        }
    }
}



void chainReactDoge() {

    const int dir[] = { -40, 40, -1, 1 };
    for (int i = 0; i < 4; i++) {

        int type = CharToType[GET(*(this + dir[i]))];
        if (Attribute[type] & ATT_PUSH) {
            *(this + dir[i]) = CH_DUST_ROCK_2;

    static int audiox[] = { SFX_DIAMOND, SFX_DIAMOND2, SFX_DIAMOND3 };
    static int auds = 0;

            if (++auds > 2)
                auds = 0;

            ADDAUDIO(audiox[auds]);
        }
    }
}


void processBoardSquares() {

    #define blanker (CH_DUST_0 | FLAG_THISFRAME)

    // int lastCreature = 12345;
        if (!(getRandom32() & 0xFF)) {
         
            if (sound_max_volume)
                sound_max_volume = 0;
            else
                sound_max_volume = VOLUME_PLAYING;
        }


    while (true) {




//        if (T1TC >= availableIdleTime) {
//            setScore(lastCreature);
//            FLASH(0x42,4); 
//            return;
//        }

        //tmp??
        rndX = (rndX >> 1) | (rndX << 31);

        int lastBoardRow = boardRow;
        int lastBoardCol = boardCol;


        boardCol++;
        if (boardCol > 39) {

            // lastCreature = 0;

            boardCol = 0;
            boardRow++;



    #if __ENABLE_WATER
            // if (water && boardRowPD > water)
            //     blanker = CH_WATER | FLAG_THISFRAME;
    #endif

    #if __ENABLE_LAVA
            if (lava && boardRowPD > lava)
                blanker = CH_LAVA_0 | FLAG_THISFRAME;
    #endif
            


            if (boardRow > 21) {

                if (uncoverTimer >= 0)
                    uncoverTimer--;
                
                if (!uncoverTimer || uncoverCount < 30) {

                    uncoverCount = 9999;
                    killAudio(SFX_UNCOVER);
                    ADDAUDIO(SFX_UNCOVERED);
                }

                gameSchedule = SCHEDULE_START;

                if (!autoMoveFrameCount) {      // delay until fully in new square

//                    chooseIdleAnimation();

                    bool oldDead = rockfordDead;

                    unsigned char *man = RAM + _BOARD + (rockfordY << 5) + (rockfordY << 3) + rockfordX;

                    int what = GET(*man);

                    if (invincible)
                        what = *man = CH_ROCKFORD;

                    int type = CharToType[what];
                    rockfordDead = (type != TYPE_ROCKFORD && type != TYPE_ROCKFORD_PRE && !exitMode);

                    if (oldDead != rockfordDead) {
                        startPlayerAnimation(ID_Die);
                        waitRelease = true;
                        lives--;
                        lockDisplay = false;

                        sound_max_volume = VOLUME_NONPLAYING; 
                        // killAudio(SFX_TICK);            // no heartbeat
                        // rockfordDeadRelease = false;
                    }
                }
                
                return;
            }
        }

        this = RAM + _BOARD + (boardRow * 40) + boardCol;
        // lastCreature = GET(*this);


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
        int worstCreature = GET(*this);
#endif


        if (T1TC + 0x1000 /*worstRequiredTime[CharToType[GET(*this)]]*/ >= availableIdleTime) {

            boardRow = lastBoardRow;
            boardCol = lastBoardCol;
            return;

        }

        unsigned char creature = *this;

#if WORST_TIMING
//        worstEverCreature = creature;
#endif

        unsigned char *prev = this - 40;
        unsigned char *next = this + 40;


    #if __ENABLE_WATER
        if (water)
            if (Attribute[cType] & ATT_WATER)
                if (boardRowPD - 22  > water && boardRow > 2 && boardRow < 21) {
                    *this = CH_WATER | FLAG_THISFRAME;
                    continue;
                }
    #endif


    // #if ENABLE_SHAKE
    //     if (shakeTime)
    //         if (CharToType[GET(*this)] == TYPE_DIRT
    //             && (rndX & 0xFF) < 2) {
    //             *this = CH_DUST_0;
    //             rndX >>= 1;
    //             continue;
    //         }
    // #endif

    #if __ENABLE_LAVA
        if (lava)
            if (boardRowPD - 22 > lava) {
                if (cType != TYPE_LAVA) {
                    if (Attribute[cType] & ATT_EXPLODES) {
    //                  if (Attribute[cType] & ATT_EXPLODABLE)
                            if ((rndX & 0x1FF) < 3) {
                                Explode(this, CH_EXPLODETOBLANK_0 | FLAG_THISFRAME);
                                FLASH(0x42, 0x62, 0x04, 8);
                //                shakeTime += 100;
                        }
                    }

                    else if (!(Attribute[cType] & ATT_HARD))
                        *this = CH_LAVA_0 | FLAG_THISFRAME;

                }
            rndX >>= 1;
        }
    #endif // ENABLE_LAVA


//        if (uncoverTimer <= 0) {

//            *this &= ~FLAG_UNCOVER;

            if (!(creature & FLAG_THISFRAME)) {

                unsigned char type = CharToType[creature]; 
                
                if (Attribute[type] & ATT_ACTIVE) {
                    switch (type) {

                    case TYPE_AMOEBA:
                        handleAmoeba();
                        break;

        #if __ENABLE_LAVA
                    case TYPE_LAVA: {

                            if (!(rndX & 0x1100)) 
                                *this = (rndX & 3) + CH_LAVA_0;
                            rndX >>= 1;
                        }
                        break;
        #endif

        #if __ENABLE_WATER
                    case TYPE_WATER: {

                        // if ((toggler & 1) == 0) {

                            unsigned char *where = this-1;
                            unsigned char newCh = (rndX & 3) + CH_WATER;

                            // don't allow side-by-side sameness
                            if (!(rndX & 0x300) || *this == *where)
                                *this = newCh;

                            if (lastWater && CharToType[*lastWater & 0x7F] == TYPE_WATER)
                                *lastWater = *this;
                            lastWater = this;

                            rndX >>= 2;

                        // }

                    }
                    break;
        #endif

                    case TYPE_BUTTERFLY: {
                        handleFly(this, CH_BUTTERFLY_0, 1, CH_EXPLODETODIAMOND_0 | FLAG_THISFRAME);
                        break;
                    }

                    case TYPE_FIREFLY: {
                        handleFly(this, CH_FIREFLY_0, -1, CH_EXPLODETOBLANK_0 | FLAG_THISFRAME);
                        break;
                    }

                    case TYPE_ROCKFORD:
                        
                        if (!exitMode)
                            moveRockford(this, blanker);

                        if (selectResetDelay > DEAD_RESTART_COUCH
                            || (selectResetDelay > DEAD_RESTART && GAME_RESET_PRESSED && GAME_SELECT_PRESSED)
                            || ( (!time && !invincible)/*&& !terminalDelay*/)
        #if __ENABLE_LAVA
                            || (lava && boardRowPD + 10 > lava)
        #endif
                            ) {

                            Explode(this, CH_EXPLODETOBLANK_0 | FLAG_THISFRAME);
                            startPlayerAnimation(ID_Die);
//                            *this = CH_BLANK;
                        }

                        break;

                    default:
                        break;

                    }
                    
                    switch (creature) {

                    case CH_BOULDER_BROKEN:
                        if (*Animate[TYPE_BOULDER_FALLING] == CH_DUST_ROCK_2) {                         
                            *this = CH_DUST_ROCK_2;
                        }
                        break;


                    case CH_DUST_ROCK_2:
                        *this = CH_DOGE_00;
                        break;

                    case CH_DUST_0:
                    case CH_DUST_1:
                    case CH_DUST_RIGHT_0:
                    case CH_DUST_LEFT_0:
                    case CH_DUST_ROCK_0:
                    case CH_DUST_ROCK_1:
                        (*this)++;
                        break;

                    case CH_EXPLODETODIAMOND_0:
                    case CH_EXPLODETODIAMOND_1:
                    case CH_EXPLODETODIAMOND_2:
                    case CH_EXPLODETODIAMOND_3:
                    case CH_EXPLODETOBLANK_0:
                    case CH_EXPLODETOBLANK_1:
                    case CH_EXPLODETOBLANK_2:
                    case CH_EXPLODETOBLANK_3:
                        *this = (creature + 1) | FLAG_THISFRAME;
                        break;

                    case CH_EXPLODETOBLANK_4:
                        *this = CH_BLANK | FLAG_THISFRAME;
                        break;

                    case CH_EXPLODETODIAMOND_4:
                        *this = CH_DOGE_00; //CH_DIAMOND_WITHOUT_DIRT;

                        __attribute__ ((fallthrough));


//                    case CH_DIAMOND_WITHOUT_DIRT:


                    // case CH_DIAMOND:
                    // case CH_DIAMOND_STATIC:
                    // case CH_DIAMOND_PULSE_0:
                    // case CH_DIAMOND_PULSE_1:
                    // case CH_DIAMOND_PULSE_2:
                    // case CH_DIAMOND_PULSE_3:
                    // case CH_DIAMOND_PULSE_4:
                    // case CH_DIAMOND_PULSE_5:
                    // case CH_DIAMOND_PULSE_6: {

                    case CH_DOGE_00:
                    case CH_DOGE_01:
                    case CH_DOGE_02:
                    case CH_DOGE_03:
                    case CH_DOGE_04:
                    case CH_DOGE_05:
                    case CH_DOGE_06: {

                        chainReactDoge();

                        int attrNext = Attribute[CharToType[GET(*next)]]; 

                        if (attrNext & ATT_BLANK) {
                            *this = CH_DUST_0 | FLAG_THISFRAME;
                            *next = CH_DOGE_FALLING | FLAG_THISFRAME;
                            break;
                        }

                        if (attrNext & ATT_ROLL)
                            doRoll(this, CH_DOGE_FALLING);

                        break;
                    }


                    case CH_BOULDER_SHAKE:
                    case CH_BOULDER:
                    
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
                    {

                        unsigned char typeDown = CharToType[GET(*next)];
                        
                        if (Attribute[typeDown] & ATT_BLANK) {

                            *this = CH_DUST_0 | FLAG_THISFRAME;
                            *next = CH_BOULDER_FALLING | FLAG_THISFRAME;

                            // int att = Attribute[CharToType[GET(*(next + 40))]];
                            // if (!(att & ATT_NOROCKNOISE))
                            //     ADDAUDIO(att & ATT_HARD ? SFX_ROCK : SFX_ROCK2);
                        }

                        else if (typeDown == TYPE_ROCKFORD && creature == CH_BOULDER)
                            *this = CH_BOULDER_SHAKE | FLAG_THISFRAME;

                        else if (Attribute[typeDown] & ATT_ROLL)
                            doRoll(this, CH_BOULDER_FALLING);

                        if (*this == CH_BOULDER_SHAKE)
                            *this = CH_BOULDER;

                        conglomerate();
                        break;
                    }

                    case CH_DOGE_FALLING:
                    case CH_BOULDER_FALLING: {

                        // *this = CH_BOULDER_FALLING;
                        // break;

                        unsigned char typeDown = CharToType[GET(*next)];

                        if (Attribute[typeDown] & ATT_BLANK) {
                            
                            *this = blanker;
                            *next = creature | FLAG_THISFRAME;

                            unsigned char *nextNext = next + 40;
                            unsigned char downCh = GET(*nextNext);
                            typeDown = CharToType[downCh];
                            int attNextNext = Attribute[typeDown];

                            if (downCh != CH_BOULDER_FALLING && downCh != CH_DOGE_FALLING) {
                                
                                int sfx = 0;

                                // if (!(attNextNext & ATT_NOROCKNOISE)) {

                                //     if (creature == CH_BOULDER_FALLING)
                                //         sfx = attNextNext & ATT_HARD ? SFX_ROCK : SFX_ROCK2;
                                //     else
                                //         sfx = SFX_DIAMOND;
                                // }

                                if (attNextNext & ATT_HARD) {
                                    if (creature == CH_BOULDER_FALLING) {

                                        sfx = SFX_ROCK;

                                        // if (typeDown == TYPE_BOULDER)
                                        //     *nextNext = CH_BOULDER_SHAKE | FLAG_THISFRAME;

                                        *next = CH_BOULDER_SHAKE | FLAG_THISFRAME;
            
                                        unsigned char *dL = this + 40 - 1;
                                        unsigned char *dR = dL + 2;

                                        if (!CharToType[GET(*dR)])
                                            *dR = CH_DUST_RIGHT_0;

                                        if (!CharToType[GET(*dL)])
                                            *dL = CH_DUST_LEFT_0;
                                    }
                                    // else
                                    //     sfx = SFX_DIAMOND;
                                }


                                if (sfx)
                                    ADDAUDIO(sfx);
                            }
                        }

                        else if (Attribute[typeDown] & ATT_SQUASHABLE_TO_BLANKS)
                            Explode(next, CH_EXPLODETOBLANK_0 | FLAG_THISFRAME);

                        else if (typeDown == TYPE_BUTTERFLY)
                            Explode(next, CH_EXPLODETODIAMOND_0 | FLAG_THISFRAME);

                        else if (typeDown == TYPE_MAGICWALL) {

                            int sfx = SFX_ROCK;;
                            unsigned char trnsf = CH_DOGE_FALLING | FLAG_THISFRAME;

                            if (millingTime && !magicWallActive) {
                                magicWallActive = true;
                                startCharAnimation(TYPE_MAGICWALL, AnimateBase[TYPE_MAGICWALL]);
                                ADDAUDIO(SFX_MAGIC);
                            }

                            if (*this == CH_DOGE_FALLING) {
                                sfx = SFX_DIAMOND;
                                trnsf = CH_BOULDER_FALLING | FLAG_THISFRAME;
                            }

                            if (magicWallActive)
                                if (Attribute[CharToType[GET(*(this + 80))]] & ATT_BLANK)
                                    *(this + 80) = trnsf;

                            // active or not, anything falling into a magic wall blanks the square
                            *this = blanker;
                            ADDAUDIO(sfx);
                        }
                        else {                        

                            // stop falling
                            unsigned char sfx = 0;
                            int att = Attribute[CharToType[GET(*(next))]];

                            switch (creature) {
                            case CH_BOULDER_FALLING: {
                                *this = CH_BOULDER;
                                sfx = att & ATT_HARD ? SFX_ROCK : SFX_ROCK2;
                                break;
                            }

                            case CH_DOGE_FALLING: {
                                *this = CH_DOGE_00;
                                sfx = SFX_DIAMOND; //att & ATT_HARD ? SFX_DIAMOND : SFX_DIAMOND;
                                break;
                            }
                            }

                            if (att & ATT_ROLL) {
                                doRoll(this, creature);
                            }

                            if (sfx && !(att & ATT_NOROCKNOISE))
                                ADDAUDIO(sfx);
                        }


                        conglomerate();
                        break;
                    }

                    case CH_DOORCLOSED:
                        if (!diamonds)
                            *this = CH_DOOROPEN_0;
                        break;

                    case CH_ROCKFORD_BIRTH:

                        // rockfordX = boardCol;
                        // rockfordY = boardRow;

                        if (
    #if CIRCLE
                            checkSwipeFinished()
        #if ENABLE_OVERLAY
                            && fSpeed == -1
        #endif
        //                        && (displayMode == DISPLAY_OVERVIEW

                    ||
    #endif
                                (!isScrolling())) {

                            //SAY(__WORD_LETSGOBABY);

                            ADDAUDIO(SFX_PUSH);
                            startPlayerAnimation(ID_Shades); //(ID_Startup);
                            *this = CH_ROCKFORD; // | FLAG_THISFRAME;
                        }
                        break;


                    case CH_DOGE_GRAB:
                        if (*Animate[TYPE_DIAMOND_GRAB] == CH_BLANK)
                             *this = CH_BLANK;
                        break;

                    case CH_DUST_2:
                    case CH_DUST_LEFT_1:
                    case CH_DUST_RIGHT_1:
                        *this = CH_BLANK;
                        break;

                    default:
                        break;
                    }
            }
    }

    // Clear any "scanned this frame" objects on the previous line
    // note: we need to also do the last row ... or do we? if it's steel wall, no
    if (boardRow > 1)
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
            diamonds = worstEverCreature;
        }
    #endif

    }
}

// EOF