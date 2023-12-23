#ifndef __MAIN_H
#define __MAIN_H

#include "defines_from_dasm_for_c.h"
#include <stdbool.h>

#define ENABLE_SOUND 1
#define ENABLE_SHAKE 1
#define ENABLE_IDLE_ANIMATION 0
#define ENABLE_TITLE_PULSE 0      /* 80 bytes */
#define ENABLE_60MHZ_AUTODETECT 0 /* 16 bytes */
#define ENABLE_ANIMATING_MAN 1    /* 244 bytes but man disappears */
#define WORST_TIMING 0

#define ENABLE_DEBUG 1

// Old/uncertiain flags that may not work

#define CIRCLE 0
#define FLAG(a) ((a) | FLAG_THISFRAME)

#define PIECE_DEPTH 30
#define SPRITE_DEPTH 30
#define HALF_DEPTH (PIECE_DEPTH / 2)

#define SPEED_BASE 8

#define PIXELS_PER_CHAR 5
#define HALFWAYX 20
#define HALFWAYY 32
#define TRILINES (PIECE_DEPTH / 3)

#define SCORE_SCANLINES 21
#define SCANLINES (_ARENA_SCANLINES)

#define TYPEOF(x) (CharToType[GET(x)])
#define ATTRIBUTE(x) (Attribute[TYPEOF(x)])
#define ATTRIBUTE_BIT(x, y) (ATTRIBUTE(x) & (y))

#define DIR_U 1
#define DIR_R 2
#define DIR_D 4
#define DIR_L 8

#define PARTICLE_GRAVITY_FLAG 0x80
#define RAINTYPE_BUBBLE 1

extern bool showTool;

void setJumpVectors(int midKernel, int exitKernel);
void InitializeNewGame();
void updateAnimation();
void pulseDoges(unsigned char *me);
void drawWord(const unsigned char *string, int y);
void conglomerate(int col, int row);
void bubbles(int count, int dripX, int dripY, int age, int speed);
int dirFromCoords(int x, int y, int prevX, int prevY);
void surroundingConglomerate(int col, int row);

extern const unsigned char reverseBits[];

struct Animation {
    signed char index;
    signed char count;
};

#define setPointer(fetcher, offset) QPTR[fetcher] = (offset) << 20;

#define FLAG_THISFRAME 0x80

#define DEAD_RESTART_COUCH 200

extern const unsigned char joyDirectBit[4];
extern unsigned char mm_tv_type;

extern int level;
extern unsigned int cave;
extern int gravity;
extern int nextGravity;
extern unsigned char *playerLocation;

enum SCHEDULE {
    SCHEDULE_START,
    SCHEDULE_PROCESSBOARD,
    SCHEDULE_UNPACK_CAVE,
};

extern enum SCHEDULE gameSchedule;
extern int gameSpeed;
extern int gameFrame;

#ifdef ENABLE_SWITCH
extern bool switchOn;
#endif

enum KERNEL_TYPE {
    KERNEL_COPYRIGHT,
    KERNEL_MENU,
    KERNEL_GAME,
    KERNEL_STATS,
};

extern unsigned char inpt4;
extern unsigned char swcha;
extern unsigned char bufferedSWCHA;
extern unsigned int usableSWCHA;
extern unsigned int inhibitSWCHA;

extern int doges;
extern int lives;
extern int time;
extern bool waitRelease;
extern bool rageQuit;
extern unsigned int sparkleTimer;

extern int exitMode;
extern unsigned int idleTimer;
extern int millingTime;
extern bool exitTrigger;

extern unsigned char *me;

extern int boardCol;

extern bool lockDisplay;

extern unsigned int triggerPressCounter;
extern unsigned char enableICC;

extern bool caveCompleted;
extern int lavaSurfaceTrixel;
extern bool showLava, showWater;

extern const signed char dirOffset[];
extern const signed char xdir[];
extern const signed char ydir[];

// extern int canPlay[5];
extern int shakeTime;

// extern const signed char dirOffset[];

extern unsigned int currentPalette;

extern unsigned int availableIdleTime;
extern int pulsePlayerColour;

void Scheduler();
void processBoardSquares();
void reanimateDoges(unsigned char *me);
void handleSelectReset();
void initNewGame();

void nDots(int count, int dripX, int dripY, int type, unsigned char age, int offsetX, int offsetY,
           int speed);
int sphereDot(int dripX, int dripY, int type, unsigned char age);
void nDotsAtTrixel(int count, int dripX, int dripY, unsigned char age, int speed);

// extern int actualScore;

/*
#define START_TIMER \
    T1TC = 0; \
    T1TCR = 1;                  // ensure timer starts @ 0

#define END_TIMER { \
    T1TCR = 0; \
    int time = T1TC; \
    if (time > max_timer) \
        max_timer = time; \
    setScore(max_timer); \
    }

#define PROFILE(a) \
    static int max_timer = 0; \
    START_TIMER \
    a \
    END_TIMER
*/

#define GET(a) (((unsigned char)((a) << 1)) >> 1)
#define GET2(a) (((unsigned char)((a) << 1)) >> 1)

#define NEW_LINE 0xFF
#define END_STRING NEW_LINE, NEW_LINE

#endif
