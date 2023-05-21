#include "defines_cdfj.h"

#include "decodecaves.h"

#include "attribute.h"
#include "cavedata.h"
#include "characterset.h"
#include "colour.h"
#include "main.h"
#include "mellon.h"
#include "random.h"
#include "scroll.h"
#include "sound.h"
#include "wyrm.h"

#define DRAW_LINE 0b01000000
#define DRAW_RECT 0b11000000
#define DRAW_FILLED_RECT 0b10000000

/* **************************************** */
/* Types */
// typedef const unsigned char UBYTE;
typedef unsigned char objectType;

/* DrawLine data */
/* When drawing lines, you can draw in all eight directions. This table gives
   the offsets needed to move in each of the 8 directions. */

const signed char ldxy[] = {-1, -1, 0, 1, 1, 1, 0, -1, -1, -1};

/* **************************************** */
/* Prototypes */
void decodeCave(int cave);
void StoreObject(int x, int y, objectType anObject);
void DrawLine(objectType anObject, int x, int y, int aLength, int aDirection);
void DrawFilledRect(objectType anObject, int x, int y, int aWidth, int aHeight,
                    objectType aFillObject);
void DrawRect(objectType anObject, int x, int y, int aWidth, int aHeight);
// void DrawHorizontalLine(objectType anObject, int x, int y, int aLength);

#if 0
void NextRandom(int *RandSeed1, int *RandSeed2);
int RandSeed1, RandSeed2;
#endif

const unsigned char *theCaveData;
// int caveFlags;
int decodingRow;
unsigned char caveMirrorXY;
static int doorX, doorY;
int processedLevel;
extern int thumbnailSpeed;
int totalDogePossible;

enum DECODE_STATE decodeState;

struct CAVE_DEFINITION *theCave;

static int decodeFlasher;

// int last_prng_a;
// int last_prng_b;

void decodeCave(int cave) {

    wyrmNum = 0;

    theCave = (struct CAVE_DEFINITION *)(((int)caveList[cave]) & 0xFFFF);

    decodeState = DECODE_NONE;

    cave_random_a = theCave->randomInit[level];
    cave_random_b = cave_random_a++; // ensure one is non-zero!

    lockDisplay = theCave->flags & CAVEDEF_OVERVIEW;
    // displayMode = lockDisplay ? DISPLAY_HALF : DISPLAY_NORMAL;

    doges = theCave->dogeRequired[level];
    time = (theCave->timeToComplete[level] << 8) + 60;
    millingTime = theCave->millingTime * 60;

    int *s = (int *)(RAM + _BOARD);
    for (int i = 0; i < (_BOARD_ROWS * _BOARD_COLS) / 4; i++)
        *(s + i) =
            0; //(FLAG_UNCOVER << 24) | (FLAG_UNCOVER << 16) | (FLAG_UNCOVER << 8) | FLAG_UNCOVER;

    decodingRow = -1;
    decodeFlasher = 21;
    totalDogePossible = 0;

    theCaveData = (&(theCave->objectData)) + theCave->objectCount * 6;

    decodeState = DECODE_START;
}

unsigned char cmd;
unsigned char a, b, c, d, e, f;
unsigned char theCode;
unsigned char theObject;

// unsigned int restore_prng_a, restore_prng_b;

int decodeExplicitData(int sfx) {

    // restore_prng_a = prng_a;
    // restore_prng_b = prng_b;

    // prng_a = last_prng_a;
    // prng_b = last_prng_b;

    switch (decodeState) {
    case DECODE_START:

        if (sfx)
            ADDAUDIO(SFX_SCORE);

        if (decodingRow < _BOARD_ROWS) {

            DrawLine(theCave->borderCharacter, 0, decodingRow + 1, _BOARD_COLS, 2);

            if (decodingRow > 0 && decodingRow < _BOARD_ROWS - 1) {

                DrawLine(theCave->interiorCharacter /*| FLAG_UNCOVER*/, 1, decodingRow,
                         _BOARD_COLS - 2, 2);

                for (int x = 1; x < _BOARD_COLS - 1; x++)
                    for (int object = 0; object < theCave->objectCount; object++) {
                        unsigned char *p = (&(theCave->objectData)) + object * 6;

                        // unsigned char *me = RAM + _BOARD + x + decodingRow * _BOARD_COLS;
                        // if (GET(*me) == 0)
                        if ((getCaveRandom32() >> 24) < p[level + 1])
                            StoreObject(x, decodingRow, p[0]);
                    }
            }

            decodingRow++;
        }

        else {

            d = e = 0;
            // theCaveData = caveList[cave].cavePtr + sizeof(struct CAVE_DEFINITION);
            decodeState = DECODE_STOP;
            processedLevel = false;
        }

        break;

    case DECODE_STOP: {

        if (d == e) {

            theCode = *theCaveData++;

            if (theCode == 0xFF) {

                // Now handle the individual level additions
                // format <block> 0xFF... <block> 0xFF
                // so we want to get to the right block based on level

                if (!processedLevel) {
                    for (int skipToBlock = 0; skipToBlock < level; skipToBlock++)
                        while (*theCaveData++ != 0xFF)
                            ;
                    processedLevel = true;
                    break;
                }

                for (int skipBotBlock = level; skipBotBlock < 4; skipBotBlock++)
                    while (*theCaveData++ != 0xFF)
                        ;

                decodeState = DECODE_FLASH;
                break;
            }

            if (theCode == 0xFE) {
                theObject = *theCaveData++;
                cmd = 0;
            }

            else {
                cmd = theCode & 0b11000000;
                theObject = theCode & 0x3F;
            }

            a = *theCaveData++;
            b = *theCaveData++;

            if (!cmd) {

                // if (theObject == CH_DOGE)
                //     theObject = CH_DOGE_PULSE_0 + rangeRandom(7);

                StoreObject(a, b, theObject);

                if (theObject == CH_DOORCLOSED) {
                    doorX = a;
                    doorY = b;
                }

                else if (theObject == CH_MELLON_HUSK_BIRTH) {

                    playerX = a;
                    playerY = b;

                    //                    if (displayMode == DISPLAY_NORMAL)
                    scrollX = (playerX - (HALFWAYX / 5)) << 16;

                    // else if (displayMode == DISPLAY_HALF)
                    //     scrollX = (playerX - (HALFWAYX >> 1)) << 16;

                    scrollY = ((6 * TRILINES - 3) << 16);
                }

                thumbnailSpeed = -1;
            }

            else {

                d = 0;

                c = *theCaveData++;
                e = *theCaveData++;

                if (cmd == DRAW_FILLED_RECT) {
                    f = *theCaveData++;
                    if (e & 0x80) { // instant
                        e &= 0x7F;
                        d = e - 1;
                    }
                }
            }
        }

        else {

            d++;

            switch (cmd) {

            case DRAW_LINE:
                DrawLine(theObject, a, b, d, c);
                if (sfx)
                    ADDAUDIO(SFX_DRIP);
                break;

            case DRAW_FILLED_RECT:
                thumbnailSpeed = -2;
                DrawFilledRect(theObject, a, b, c, d, f);
                if (sfx)
                    ADDAUDIO(SFX_DIRT);
                break;

            case DRAW_RECT:
                d = e;
                DrawRect(theObject, a, b, c, d);
                if (sfx)
                    ADDAUDIO(SFX_BLIP);
                break;

            default:
                break;
            }

            if (d == e)
                thumbnailSpeed = -10;
        }

        break;
    }

    case DECODE_FLASH:

        DrawRect(theCave->borderCharacter & ((decodeFlasher & 4) ? 0 : 0xFF), 0, 0, _BOARD_COLS,
                 _BOARD_ROWS);

        if (!(decodeFlasher & 0b11))
            if (sfx)
                ADDAUDIO(SFX_DRIP);
        if (!--decodeFlasher)
            StoreObject(doorX, doorY, CH_DOORCLOSED);
        break;

    default:
        break;
    }

    // last_prng_a = prng_a;
    // last_prng_b = prng_b;

    // prng_a = restore_prng_a;
    // prng_b = restore_prng_b;

    return decodeFlasher;
}

void StoreObject(int x, int y, objectType anObject) {

    unsigned char *me = RAM + _BOARD + x + y * _BOARD_COLS;
    unsigned char type = TYPEOF(anObject);

    if (TYPEOF(*me) == TYPE_DOGE)
        totalDogePossible--;

    switch (type) {

    case TYPE_WYRM: {
        newWyrm(x, y);
        break;
    }

    case TYPE_LAVA: {

        showLava = true;
        int line = y * TRILINES;
        if (lavaSurface > 0 && line < lavaSurface)
            lavaSurface = line;

        break;
    }

    case TYPE_WATER: {

        showWater = true;
        int line = y * TRILINES;
        if (lavaSurface > 0 && line < lavaSurface)
            lavaSurface = line;

        break;
    }

    case TYPE_DOGE: {

        totalDogePossible++;
        break;
    }

    default:
        break;
    }

    *me = anObject;
}

void DrawLine(objectType anObject, int x, int y, int aLength, int aDirection) {

    for (int counter = 0; counter < aLength; counter++) {
        StoreObject(x, y, anObject);
        x += ldxy[aDirection + 2];
        y += ldxy[aDirection];
    }
}

void DrawRect(objectType anObject, int x, int y, int aWidth, int aHeight) {

    DrawLine(anObject, x, y, aWidth, 2);
    DrawLine(anObject, x, y + aHeight - 1, aWidth, 2);
    DrawLine(anObject, x, y, aHeight, 4);
    DrawLine(anObject, x + aWidth - 1, y, aHeight, 4);
}

void DrawFilledRect(objectType anObject, int x, int y, int aWidth, int aHeight,
                    objectType aFillObject) {

    for (int counter1 = aHeight - 2; counter1 > 0; counter1--)
        DrawLine(aFillObject, x + 1, y + counter1, aWidth - 2, 2);
    DrawRect(anObject, x, y, aWidth, aHeight);
}

// EOF