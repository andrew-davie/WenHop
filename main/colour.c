#include "defines.h"
#include "defines_cdfj.h"
// #include "defines_from_dasm_for_c.h"

#include "colour.h"
#include "main.h"
#include "scroll.h"

unsigned char bgPalette[_BOARD_ROWS];
unsigned char fgPalette[2];
static int flashTime;

static int lastBgCol;
static int lastPfCharLine;
static int lastBgCharLine;

int roller;

void initColours() {

    lastBgCol = 0xFF;
    lastPfCharLine = -1;
    roller = 0;
}

int interleavedColour = false;
void interleaveColour() {

    interleavedColour = (enableICC == LEFT_DIFFICULTY_A);

    if (++roller > 2 || !interleavedColour)
        roller = 0;
}

const unsigned char xlate[] = {0x00, 0x20, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0,
                               0xD0, 0xB0, 0x90, 0x70, 0x50, 0x30, 0x20, 0x40};

const unsigned char xlateSecam[] = {0, 0xC, 0xC, 4, 4, 6, 6, 2, 2, 2, 8, 8, 8, 8, 0xC, 0xC};

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

#define FRANGE (0x100 / _BOARD_ROWS)
void setBackgroundPalette(unsigned char *c) {

    if (mm_tv_type == SECAM) {
        int colour = convertColour(c[2]);
        for (int bgLine = 0; bgLine < _BOARD_ROWS; bgLine++)
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

        for (int bgLine = 0; bgLine < _BOARD_ROWS; bgLine++) {

            bgPalette[bgLine] = convertColour(((c1 >> 8) & 0xF0) | (i1 >> 8));

            i1 += iStep;
            c1 += cStep;
        }
    }

    fgPalette[0] = convertColour(c[0]);
    fgPalette[1] = convertColour(c[1]);
}

void setPalette() {

    int shift = 16;

    interleaveColour();

    unsigned char bgCol = flashTime ? ARENA_COLOUR : 0;

    int i = 0;
    unsigned char *pfCol = RAM + _BUF_COLUPF;
    unsigned char *bkCol = RAM + _BUF_COLUBK;

    int bgCharLine = (scrollY >> shift) * 3;
    int pfCharLine = 0;

    while (bgCharLine >= PIECE_DEPTH) {
        bgCharLine -= PIECE_DEPTH;
        pfCharLine++;
    }

    lastBgCharLine = bgCharLine;
    lastPfCharLine = pfCharLine;

    unsigned char rollColour[5];

    rollColour[0] = rollColour[3] = fgPalette[1];
    rollColour[1] = rollColour[4] = bgPalette[pfCharLine];
    rollColour[2] = fgPalette[0];

    int roll = roller;
    if (interleavedColour && --roll < 0)
        roll = 2;

    static unsigned char lavaColour[] = {0x24, 0x36, 0x46, 0x24};
    static const unsigned char waterColour[] = {0x88, 0x78, 0xC8, 0x88};

    static const unsigned char wbg[] = {0x96, 0x96, 0x96, 0x94, 0x94, 0x94,
                                        0x92, 0x92, 0x90, 0x90, 0x90};

    static const unsigned char lbg[] = {0x46, 0x46, 0x46, 0x44, 0x44, 0x44,
                                        0x42, 0x42, 0x40, 0x40, 0x40};

    int lavaLine = (lavaSurfaceTrixel - (scrollY >> shift)) * 3;
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
        if (bgCharLine >= PIECE_DEPTH) {
            bgCharLine = 0;
            rollColour[1] = rollColour[4] = bgPalette[++pfCharLine];
        }

        i += 3;
    }

    const unsigned char *cl = showLava ? &lbg[0] : &wbg[0];
    const unsigned char *clava = showLava ? &lavaColour[0] : &waterColour[0];

    while (i < _ARENA_SCANLINES) {

        unsigned char lbgCol = cl[(lavab >> 2)];

        if (lavab < (10 << 2))
            lavab += 3;

        pfCol[0] = clava[roll];
        pfCol[1] = clava[roll + 1];
        pfCol[2] = clava[roll + 2];

        bkCol[0] = lbgCol;
        bkCol[1] = lbgCol;
        bkCol[2] = lbgCol;

        pfCol += 3;
        bkCol += 3;

        i += 3;
    }
}

void loadPalette() {

    unsigned char *c = (unsigned char *)_COLOUR_POOL;

    c += ((currentPalette & 15) << 2);
    setBackgroundPalette(c);
}

// EOF