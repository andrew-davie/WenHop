#include "defines.h"
#include "defines_cdfj.h"

#include "main.h"

#include "cavedata.h"
#include "colour.h"
#include "decodecaves.h"
#include "player.h"
#include "random.h"
#include "score.h"
#include "scroll.h"


unsigned char bgPalette[22];
unsigned char fgPalette[2];
static int flashTime;

#if ENABLE_RAINBOW
static int lastRainbowIndex;
#endif
static int lastBgCol;
static int lastPfCharLine;
static int lastBgCharLine;

int roller;


void initColours() {
#if ENABLE_RAINBOW
    lastRainbowIndex = -1;
#endif
    lastBgCol = 0xFF;
    lastPfCharLine = -1;
//    lastDisplayMode = DISPLAY_NONE;
    roller = 0;
}



bool interleavedColour = false;
void interleaveColour() {

    interleavedColour = (enableICC == LEFT_DIFFICULTY_A);

    if (++roller > 2 || !interleavedColour)
        roller = 0;
}



static const unsigned char xlate[] = {
    0x00, 0x20, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0,
    0xD0, 0xB0, 0x90, 0x70, 0x50, 0x30, 0x20, 0x40
};

static const unsigned char xlateSecam[] = {
       0,  0xC,  0xC,    4,    4,    6,    6,    2,
       2,    2,    8,    8,    8,    8,  0xC,  0xC
};



int secamConvert(int col) {

    int c = xlateSecam[col >> 4];

    if ((col & 0xF) >= 4) {
        if (!c)
            c = 0xE;
        else if (c == 2)
            c = 0xA;
    }
    return c;
}



int convertColour(int colour) {

     switch (mm_tv_type) {
     case NTSC:
        break;

     case SECAM: {
         colour = secamConvert(colour);
         break;
     }

     case PAL:
     case PAL_60:
         colour = xlate[colour >> 4] | (colour & 0xF);
         break;
     }

    return colour;
}



void setFlash2(unsigned char col, int time) {
    ARENA_COLOUR = convertColour(col);
    flashTime = time;
}



void doFlash() {

    if (flashTime) {
        if (!--flashTime)
            if (mm_tv_type == SECAM || (flashTime = --ARENA_COLOUR & 0xF) == 0)
                ARENA_COLOUR = 0;
    }

}


#define FRANGE (0x100/22)
void setBackgroundPalette(unsigned char *c) {

    if (mm_tv_type == SECAM) {
        int colour = convertColour(c[2]);
        for (int bgLine = 0; bgLine < 22; bgLine++)
            bgPalette[bgLine] = colour;
    }

    else {


        int c1 = c[2] & 0xF0;
        int c2 = c[3] & 0xF0;
        int i1 = c[2] & 0xF;
        int i2 = c[3] & 0xF;

        int cStep = (c2 - c1) * FRANGE;
        int iStep = (i2 - i1) * FRANGE;

        i1 = i1 << 8;
        c1 = c1 << 8;

        for (int bgLine = 0; bgLine < 22; bgLine++) {

            bgPalette[bgLine] = convertColour(((c1 >> 8) & 0xF0) | (i1 >> 8));

            i1 += iStep;
            c1 += cStep;
        }
    }


    fgPalette[0] = convertColour(c[0]);
    fgPalette[1] = convertColour(c[1]);
}



#if ENABLE_RAINBOW

int rainbowIndex;

void doRainbowBackground() {

    if (rainbow) {

        if (rainbowIndex != lastRainbowIndex) {

            int rbi = rainbowIndex;
            for (int col = 0; col < 22; col++) {
                if (rbi >= 16)
                    rbi = 2;
                if (mm_tv_type == NTSC)
                    bgPalette[col] = (rbi << 4) | 4;
                else
                    bgPalette[col] = xlate[rbi] | 4;
                rbi++;
            }
        }

        lastRainbowIndex = rainbowIndex;
    }
}



void rollRainbow() {

    static int slower;
    if (++slower > 5) {
        slower = 0;
        if (++rainbowIndex >= 16)
            rainbowIndex = 2;
    }

}

#endif


void setPalette() {

//    static const int shiftMode[] = { 16, 17, 31 };
//    static const int rowSize[] = { PIECE_DEPTH, 15, 9 };

    int size = PIECE_DEPTH; //rowSize[displayMode];

    int shift = 16; //shiftMode[displayMode];


#if ENABLE_RAINBOW
    rollRainbow();
#endif

    interleaveColour();

    unsigned char bgCol = flashTime ? ARENA_COLOUR : 0;

    int i = 0;
    unsigned char *pfCol = RAM + _BUF_COLUPF;
    unsigned char *bkCol = RAM + _BUF_COLUBK;


    int bgCharLine = (scrollY >> shift) * 3;
    int pfCharLine = 0;


    while (bgCharLine >= PIECE_DEPTH) { //rowSize[displayMode]) {
        bgCharLine -= size;
        pfCharLine++;
    }


    // if (bgCol != lastBgCol) {
    //     lastBgCol = bgCol;
    //     for (int j = i; j < _ARENA_SCANLINES; j++)
    //         bkCol[j] = bgCol;
    // }


//     if (
// #if COLSELECT
//          LEFT_DIFFICULTY_A
//         ||
// #endif
// //tmp    true
// #if ENABLE_RAINBOW
//         || lastRainbowIndex != rainbowIndex
// #endif
//          lastPfCharLine != pfCharLine
//         || lastBgCharLine != bgCharLine
//         || lastDisplayMode != displayMode

// #if ENABLE_RAINBOW
// //        || rainbow //tmp
// #endif
//         ) {


        lastBgCharLine = bgCharLine;
        lastPfCharLine = pfCharLine;
//        lastDisplayMode = displayMode;


#if ENABLE_RAINBOW
        doRainbowBackground();
#endif
        unsigned char rollColour[5];

        rollColour[0] = rollColour[3] = fgPalette[1];
        rollColour[1] = rollColour[4] = bgPalette[pfCharLine];
        rollColour[2] = fgPalette[0];

        int roll = roller;
        if (interleavedColour && --roll < 0)
            roll = 2;


        static const int lavaColour[] = { 0x24, 0x34, 0x26, 0x24, 0x34 };
        static const unsigned char lbg[] = { 0x2A, 0x46, 0x46, 0x44,
            0x44, 0x44, 0x42,
            0x42, 0x42, 0x42, 0x40
        };

        int lavaLine = (lavaSurface - (scrollY >> shift)) * 3;
        int lavab = 0;
        if (lavaLine < 0)
            lavab = -lavaLine;
        if (lavab >= (10 << 2))
            lavab = (10 << 2);


        while (i < lavaLine && i < _ARENA_SCANLINES) {

            pfCol[0] = rollColour[roll];
            pfCol[1] = rollColour[roll + 1];
            pfCol[2] = rollColour[roll + 2];

            bkCol[0] = bgCol;
            bkCol[1] = bgCol;
            bkCol[2] = bgCol;

            pfCol += 3;
            bkCol += 3;

            bgCharLine += 3;
            if (bgCharLine >= size) {
                bgCharLine = 0;
                rollColour[1] = rollColour[4] = bgPalette[++pfCharLine];
            }

            i += 3;
        }


        while (i < _ARENA_SCANLINES) {


            unsigned char lbgCol = lbg[(lavab >> 2)];

            if (lavab < (10 << 2))
                lavab += 3;

            pfCol[0] = lavaColour[roll];
            pfCol[1] = lavaColour[roll + 1];
            pfCol[2] = lavaColour[roll + 2];

            bkCol[0] = lbgCol;
            bkCol[1] = lbgCol;
            bkCol[2] = lbgCol;

            pfCol += 3;
            bkCol += 3;

            i += 3;
        }


        // if (displayMode != DISPLAY_OVERVIEW) {

        //     int rollx = roll;
        //     static const unsigned char scoreColour[] = { 0x46, 0x98, 0xD8, 0x46, 0x98, 0x28, 0x28, 0x28 };

        //     if (enableICC != LEFT_DIFFICULTY_A)
        //         rollx = 5;

        //     unsigned char cc0 = convertColour(scoreColour[rollx]);
        //     unsigned char cc1 = convertColour(scoreColour[rollx + 1]);
        //     unsigned char cc2 = convertColour(scoreColour[rollx + 2]);

        //      while (i < _ARENA_SCANLINES/*SCORE_SCANLINES*/) {

        //          pfCol[0] = cc0;
        //          pfCol[1] = cc1;
        //          pfCol[2] = cc2;

        //          pfCol += 3;
        //          i += 3;
        //    }
        // }
    // }
}


void loadPalette() {


    unsigned char *c = (unsigned char *) __COLOUR_POOL;
//    currentPalette = getRandom32() & 15; //(cave ^ prng_a) & 15; // ^ prng_b; //rangeRandom(__PALETTE_COUNT);


    // if (((int)caveList[cave]) & CAVE_REQUIRES_AMOEBA_PALETTE)
    //     while (!(c[currentPalette << 2] & __COMPATIBLE_AMOEBA_PALETTE))
    //         currentPalette = rangeRandom(__PALETTE_COUNT);

    c += ((currentPalette & 15) << 2);
    setBackgroundPalette(c);

    // ICC Colour Usage / Palette by line in char definition

    // 0        the soil - varies in colour down the screen ("background")
    // 1        amoeba
    // 2        the brickwork "mortar"


    //--------------
    // format...
    // charline colour line 1
    // charline colour line 2
    // charline colour line 0 (bg, 2 definitions)


// #if ENABLE_RAINBOW
//     if (rainbow)
//         doRainbowBackground();
// #endif


    #if COLSELECT
        extern unsigned char colr[5];
        colr[0] = c[0];
        colr[1] = c[1];
        colr[2] = c[2];
        colr[3] = c[3];
        // colr[4] = rndX & 0xF;     // which palette #
    #endif
}


//EOF