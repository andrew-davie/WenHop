#include <stdbool.h>
#include "defines.h"
#include "defines_cdfj.h"
#include "main.h"

#include "amoeba.h"
#include "bitpatterns.h"
#include "cavedata.h"
#include "colour.h"
#include "decodecaves.h"

#include "menu.h"
#include "player.h"
#include "random.h"
#include "rockford.h"
#include "score.h"
#include "sound.h"
#include "swipeCircle.h"


//#define RGB_BLACK       0
#define RGB_RED         1
#define RGB_BLUE        2
//#define RGB_PURPLE      3
#define RGB_GREEN       4
#define RGB_YELLOW      5
#define RGB_AQUA        6
//#define RGB_WHITE       7


#define SPARKLE            180     /* # frames to sparkle BG on extra life */

int actualScore;
int partialScore;
static int forceScoreDraw;

enum SCORE_MODE scoreCycle;

static unsigned char scoreLineNew[10];
static unsigned char scoreLineColour[10];

static int toggle = 0;



void addScore(int score) {

    actualScore += score;

    ADDAUDIO(SFX_SCORE);

    partialScore += score;

    while (partialScore >= 500) {
        partialScore -= 500;
        lives++;
        FLASH(0x86,6);
        sparkleTimer = SPARKLE;
        ADDAUDIO(SFX_EXTRA);
        setScoreCycle(SCORELINE_LIVES);
    }
}


const int pwr[] = {
    1,10,100,1000,10000,100000,
};

// right-to-left, least-significant first digit position
const unsigned char mask[] = {
    0x0F, 0xF0, 0xF0, 0x0F, 0x0F,
    0x0F, 0xF0, 0xF0, 0x0F, 0x0F,
};

const bool mirror[] = {
    1,1,0,0,1,
    1,1,0,0,1,
};

const int base[] = {
    _BUF_PF2_RIGHT,
    _BUF_PF2_RIGHT,
    _BUF_PF1_RIGHT,
    _BUF_PF1_RIGHT,
    _BUF_PF0_RIGHT,
    _BUF_PF2_LEFT,
    _BUF_PF2_LEFT,
    _BUF_PF1_LEFT,
    _BUF_PF1_LEFT,
    _BUF_PF0_LEFT,
};


void setScoreCycle(enum SCORE_MODE cycle) {
    scoreCycle = cycle;
    forceScoreDraw = SCOREVISIBLETIME;
}


static unsigned char bigDigitBuffer[DIGIT_SIZE];


void drawBigDigit(int digit, int pos, int offset, int colour, bool blackBackground) {

    // colour 0x80 --> don't draw bottom blacknmess
    // colour 0x40 --> don't draw top blackness

    if (digit == DIGIT_SPACE)
        return;

    unsigned char pmask = mask[pos];
    unsigned char *p = RAM + base[pos] + offset;

    // if (digit == DIGIT_SPACE) {
    //     for (int line = 0; line < DIGIT_SIZE; line++)
    //         p[line] &= pmask;
    //     return;
    // }

    int shift2 = pmask == 0x0F ? 0 : 4;

    //pmask = ~pmask;
    //if (blackBackground) {
        // if (mirror[pos])
        //     pmask = (pmask >> 1);
        // else
        //     pmask |= (pmask << 1);
    //}
    //pmask = ~pmask;

    // if (digit & 0x80)
    //     pmask = 0xFF;



    if (colour && enableICC == LEFT_DIFFICULTY_A)
        colour |= 7;

    int shift = (digit & 1) << 2;
    digit >>= 1;

    if (!mirror[pos])
        shift2 ^= 4;

    int dbase = offset + roller;
    while (dbase > 2)
        dbase -= 3;

    dbase = 1 << dbase;

    if (offset && blackBackground && !(colour & 0x40)) { //offset && (!digit & 0x40)) {
        p[0] &= pmask;
        p[1] &= pmask;
        p[2] &= pmask;
        p += 3;
    }


    unsigned char *dig;
    if (!(digit & 0x40))
        dig = (unsigned char *)(__DIGIT_SHAPE + digit * DIGIT_SIZE);
    else
        dig = bigDigitBuffer;

    unsigned char rdl, rdl2;
    if (mirror[pos]) {
        for (int line = 0; line < DIGIT_SIZE; line++) {

            rdl2 = ((dig[line] >> shift) & 0xF) << shift2;
            rdl = ~rdl2;
            if (!(colour & 7 & dbase))
                rdl2 = 0;
            if (blackBackground)
                rdl = ~pmask;
            dbase = (dbase << 1) | (dbase >> 2);
            p[line] = (p[line] & BitRev[rdl]) | BitRev[rdl2];
        }
    }
    else {
        for (int line = 0; line < DIGIT_SIZE; line++) {

            rdl2 = ((dig[line] >> shift) & 0xF) << shift2;
            rdl = ~rdl2;
            if (!(colour & 7 & dbase))
                rdl2 = 0;
            if (blackBackground)
                rdl = pmask;
            dbase = (dbase << 1) | (dbase >> 2);
            p[line] = (p[line] & rdl) | rdl2;
        }
    }


    if (offset && blackBackground  && !(colour & 0x80)) { //offset && !(digit & 0x40)) {
        p += DIGIT_SIZE;
        p[0] &= pmask;
        p[1] &= pmask;
        p[2] &= pmask;
    }
}



void fillBit(int line, unsigned char b) {
    unsigned char *bdp = bigDigitBuffer + (line << 2);
    bdp[0] =
    bdp[1] =
    bdp[2] =
    bdp[3] = b;
}



void doubleSizeScore(int x, int y, int letter, int col) {

    extern unsigned char charAtoZ[];
    unsigned char *sample = charAtoZ + (letter + 26) * 10;

    for (int line = 0; line < 5; line++)
        fillBit(line, sample[line]);      

    drawBigDigit(0x80, x, y, 0x80 | col, false);
    drawBigDigit(0x81, x + 1, y, 0x80 | col, false);

    for (int line = 0; line < 5; line++)
        fillBit(line, sample[line + 5]);

    drawBigDigit(0x80, x, y + DIGIT_SIZE, 0x40 | col, false);
    drawBigDigit(0x81, x + 1, y + DIGIT_SIZE, 0x40 | col, false);
}



unsigned char *drawDecimal2(unsigned char *buffer, unsigned char *colour_buffer, unsigned int colour, int cvt) {

    int forced = 0;
    for (int digit = 2; digit >= 0; digit--) {

        int displayDigit = 0;
        while (cvt >= pwr[digit]) {
            displayDigit++;
            cvt -= pwr[digit];
        }

        forced |= displayDigit;

        if (forced || !digit) {
            *buffer++ = displayDigit;
            
            if (colour_buffer)
                *colour_buffer++ = colour;
        }
    }

    return buffer;
}



void drawCaveLevel(){

    scoreLineNew[2] = LETTER('C');
    scoreLineNew[3] = LETTER('A');
    scoreLineNew[4] = LETTER('V');
    scoreLineNew[5] = LETTER('E');

    scoreLineNew[7] = LETTER('A' + cave);
    scoreLineNew[8] = level + 1;

    scoreLineColour[2] =
    scoreLineColour[3] =
    scoreLineColour[4] =
    scoreLineColour[5] = RGB_YELLOW;

    scoreLineColour[7] =
    scoreLineColour[8] = RGB_AQUA;
}


void drawSpeedRun() {

    static int speedCycle;
    speedCycle -= 12;
    for (int i = 0; i < 8; i++) {    
        scoreLineNew[i + 1] = LETTER("SPEEDRUN"[i]);
        scoreLineColour[i + 1] = ((speedCycle + i * 0x30) >> 8) & 7;
    }
}


void drawDiamond() {

    scoreLineNew[1] = diamonds < 0 ? DIGIT_PLUS : DIGIT_DIAMOND;
    scoreLineColour[1] = RGB_GREEN;
    drawDecimal2(scoreLineNew + 2, scoreLineColour + 2, RGB_YELLOW, diamonds < 0 ? - diamonds : diamonds);
}


void drawTime() {

    int tPos = time >= 0xA00 ? time >= 0x6400 ? 5 : 6 : 7;

    scoreLineNew[tPos] = LETTER('T');
    scoreLineColour[tPos++] = RGB_BLUE;

    if (time > 0xA00 || ++toggle & 16)
        drawDecimal2(scoreLineNew + tPos, scoreLineColour + tPos, time < 0xA00 ? RGB_RED : RGB_AQUA, time >> 8);
}



void drawLives() {

    scoreLineNew[1] = LETTER('L');
    scoreLineColour[1] = RGB_BLUE;

    drawDecimal2(scoreLineNew + 2, scoreLineColour + 2, RGB_YELLOW, lives);
}



void drawTheScore(int score) {

    for (int digit = 5; digit >= 0; digit--) {

        int displayDigit = 0;
        while (score >= pwr[digit]) {
            displayDigit++;
            score -= pwr[digit];
        }

        scoreLineNew[7 - digit] = displayDigit;
        scoreLineColour[7 - digit] = RGB_YELLOW; // digit + 1;
    }
}



#if COLSELECT
extern int colourn;
unsigned char colr[5];
static int tog = 0;


void drawc(int start, int v) {

    scoreLineNew[start] = DIGIT_SPACE;
    scoreLineNew[start + 1] = DIGIT_SPACE;

    if (!(7- start == colourn * 2) ||  (tog & 0b1000)) {

        int d = (v >> 4) & 0xF;
        if (d >= 10)
            d += DIGIT_A - 10;

        scoreLineNew[start] = d;
        d = v & 0xF;
        if (d >= 10)
            d += DIGIT_A - 10;
        scoreLineNew[start+1] = d;
    }
}
 


void drawColours() {

    tog++;

    scoreLineNew[9] = DIGIT_SPACE;
    if (colourn != 4 || (tog & 0b1000))
        scoreLineNew[9] = colr[4] + ((colr[4] > 9) ? DIGIT_A - 10 : 0);


    drawc(7,colr[0]);
    drawc(5,colr[1]);
    drawc(3,colr[2]);
    drawc(1,colr[3]);

    short type = 0;
    switch (mm_tv_type) {
        case NTSC: 
            type = DIGIT_N;
            break;
        case PAL:
        case PAL_60:
            type = DIGIT_P;
            break;
    }

    scoreLineNew[0] = type;
}
#endif


void drawScore() {


    static int scc = 0;
    scc++;


    if (!--forceScoreDraw) {
        forceScoreDraw = SCOREVISIBLETIME;
        if (++scoreCycle >= SCORELINE_END)
            scoreCycle = rockfordDead ? SCORELINE_LIVES : SCORELINE_START;
    }

    if (!exitMode && !rockfordDead && time < 0xA00)
        setScoreCycle(SCORELINE_TIME);

    else {

        // occasionally show score when idle
        if (idleTimer > IDLE_TIME) {
            idleTimer = 0;
            setScoreCycle(SCORELINE_SCORE);
        }
    }

// #if COLSELECT > 0
//     displayedScoreCycle = SCORELINE_COLOUREDIT;
// #endif

    for (int i = 0; i < 10; i++)
        scoreLineNew[i] = DIGIT_SPACE;

#if COLSELECT
    if (LEFT_DIFFICULTY_A) {
        drawColours();
    } else
#endif


    switch (scoreCycle) {
    case SCORELINE_TIME:
        drawDiamond();
        drawTime();
        break;
    case SCORELINE_SCORE:
        drawTheScore(actualScore);
        break;
    case SCORELINE_LIVES:
        drawTime();
        drawLives();
        break;
    case SCORELINE_CAVELEVEL:
        drawCaveLevel();
        break;
    case SCORELINE_SPEEDRUN:
        if (!theCave->diamondsRequired[level] && !rockfordDead)
            drawSpeedRun();
        else
            setScoreCycle(SCORELINE_LIVES);
        break;

    default:
        break;
    }

    for (int i = 0; i < 10; i++)
        drawBigDigit(scoreLineNew[i], 9 - i, 9, 7 /*scoreLineColour[i]*/, false);

}



//EOF