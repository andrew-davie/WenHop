/* decodeCaves.c
   Original program written by:
       Jeff Bevis <bevis@ecn.purdue.edu>
       Peter Broadribb <peterb@perth.dialix.oz.au>
   28 Aug 1995
   
   01 Oct 1995: Fixed bug in NextRandom(); I have now checked the output
   of NextRandom() against the output of the original 6510 code, and they
   appear to be generating the same numbers. However, the cave data,
   although _almost_ correct, doesn't seem exactly right. I'm puzzled. [PB]
   
   */

#include "defines_cdfj.h"

#include "main.h"
#include "decodecaves.h"
#include "cavedata.h"
#include "colour.h"
#include "amoeba.h"
#include "attribute.h"
#include "characterset.h"
#include "random.h"
#include "rockford.h"
#include "scroll.h"
#include "sound.h"

#define DRAW_LINE 0b01000000
#define DRAW_RECT 0b11000000
#define DRAW_FILLED_RECT 0b10000000


/* **************************************** */
/* Types */
//typedef const unsigned char UBYTE;
typedef unsigned char objectType;


/* DrawLine data */
/* When drawing lines, you can draw in all eight directions. This table gives
   the offsets needed to move in each of the 8 directions. */

const signed char ldxy[]={ -1, -1, 0, 1, 1, 1, 0, -1, -1, -1 };


/* **************************************** */
/* Prototypes */
void decodeCave(int cave);
void StoreObject(int x, int y, objectType anObject);
void DrawLine(objectType anObject, int x, int y, int aLength, int aDirection);
void DrawFilledRect(objectType anObject, int x, int y, int aWidth, int aHeight, objectType aFillObject);
void DrawRect(objectType anObject, int x, int y, int aWidth, int aHeight);
//void DrawHorizontalLine(objectType anObject, int x, int y, int aLength);

#if 0
void NextRandom(int *RandSeed1, int *RandSeed2);
int RandSeed1, RandSeed2;
#endif

const unsigned char *theCaveData;
//int caveFlags;
int decodingRow;
unsigned char caveMirrorXY;
static int doorX, doorY;
bool processedLevel;
extern int thumbnailSpeed;
int totalDiamondsPossible;

enum DECODE_STATE decodeState;

struct CAVE_DEFINITION *theCave;


static int decodeFlasher;

// int last_prng_a;
// int last_prng_b;

int wyrmNum;

void decodeCave(int cave) {

    wyrmNum = 0;

    theCave = (struct CAVE_DEFINITION *) (((int)caveList[cave]) & 0xFFFF);

    decodeState = DECODE_NONE;

    cave_random_a = theCave->randomInit[level];
    cave_random_b = cave_random_a++;  // ensure one is non-zero!

#if ENABLE_RAINBOW
    rainbow = theCave->flags & CAVEDEF_RAINBOW;
#endif
    lockDisplay = theCave->flags & CAVEDEF_OVERVIEW;
    displayMode = lockDisplay ? DISPLAY_HALF : DISPLAY_NORMAL;


    diamonds = theCave->diamondsRequired[level]; 
    time = (theCave->timeToComplete[level] << 8) + 60;
    millingTime = theCave->millingTime * 60;

    int *s = (int *) (RAM + _BOARD);
    for (int i = 0; i < 880/4; i++)
        *(s+i) = 0; //(FLAG_UNCOVER << 24) | (FLAG_UNCOVER << 16) | (FLAG_UNCOVER << 8) | FLAG_UNCOVER;

    decodingRow = -1;
    decodeFlasher = 21;
    totalDiamondsPossible = 0;

    theCaveData = (&(theCave->objectData)) + theCave->objectCount * 6;


    decodeState = DECODE_START;
}


unsigned char cmd;
unsigned char a, b, c, d, e, f;
unsigned char theCode;
unsigned char theObject;

// unsigned int restore_prng_a, restore_prng_b;

int decodeExplicitData(bool sfx) {

    // restore_prng_a = prng_a;
    // restore_prng_b = prng_b;

    // prng_a = last_prng_a;
    // prng_b = last_prng_b;

    switch (decodeState) {
    case DECODE_START:

        if (sfx)
            ADDAUDIO(SFX_SCORE);

        if (decodingRow < 22) {

            DrawLine(theCave->borderCharacter, 0, decodingRow + 1, 40, 2);

            if (decodingRow > 0 && decodingRow < 21) {

                DrawLine(theCave->interiorCharacter /*| FLAG_UNCOVER*/, 1, decodingRow, 38, 2);

                for (int x = 1; x < 39; x++)
                    for (int object = 0; object < theCave->objectCount; object++) {
                        unsigned char *p = (&(theCave->objectData)) + object * 6;
                        
                        // unsigned char *this = RAM + _BOARD + x + decodingRow * 40;
                        // if (GET(*this) == 0)
                            if ((getCaveRandom32() >> 24) < p[level + 1])
                                StoreObject(x, decodingRow, p[0]);
                    }
            }

            decodingRow++;
        }

        else {

            d = e = 0;
            //theCaveData = caveList[cave].cavePtr + sizeof(struct CAVE_DEFINITION);
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
                        while (*theCaveData++ != 0xFF);
                    processedLevel = true;
                    break;
                }

                for (int skipBotBlock = level; skipBotBlock < 4; skipBotBlock++)
                    while (*theCaveData++ != 0xFF);

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

                // if (theObject == CH_DIAMOND)
                //     theObject = CH_DIAMOND_PULSE_0 + rangeRandom(7);

                StoreObject(a, b, theObject);


                if (theObject == CH_DOORCLOSED) {
                    doorX = a;
                    doorY = b;
                }

                else if (theObject == CH_ROCKFORD_BIRTH) {

                    rockfordX = a;
                    rockfordY = b;

                    if (displayMode == DISPLAY_NORMAL)
                        scrollX = (rockfordX - (HALFWAYX /5)) << 16;

                    else if (displayMode == DISPLAY_HALF)
                        scrollX = (rockfordX - (HALFWAYX >> 1)) << 16;

                    scrollY = (( 6 * PIECE_DEPTH / 3 - 3) << 16);
                }


                thumbnailSpeed = -1;
            }

            else {

                d = 0;

                c = *theCaveData++;
                e = *theCaveData++;

                if (cmd == DRAW_FILLED_RECT) {
                    f = *theCaveData++;
                    if (e & 0x80) {     // instant
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

        DrawRect(theCave->borderCharacter & ((decodeFlasher & 4) ? 0 : 0xFF), 0, 0, 40, 22);

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

    unsigned char *this = RAM + _BOARD + x + y * 40;

    if (CharToType[GET(*this)] == TYPE_DOGE)
        totalDiamondsPossible--;

    else if (CharToType[anObject] == TYPE_WYRM) {
        wyrmHead[wyrmNum] = 0;
        wyrmDir[wyrmNum] = 0;
        wyrmX[wyrmNum][0] = x;
        wyrmY[wyrmNum][0] = y;
        wyrmNum++;
    }


    *this = anObject; // | FLAG_UNCOVER;

    if (CharToType[GET(anObject)] == TYPE_DOGE)
        totalDiamondsPossible++;
}
 

void DrawLine(objectType anObject, int x, int y, int aLength, int aDirection) {

    for (int counter = 0; counter < aLength; counter++) {
        StoreObject(x, y, anObject);
        x += ldxy[aDirection+2];
        y += ldxy[aDirection];     
    }
}


void DrawRect(objectType anObject, int x, int y, int aWidth, int aHeight) {

    DrawLine(anObject, x, y, aWidth, 2);
    DrawLine(anObject, x, y + aHeight - 1, aWidth, 2);
    DrawLine(anObject, x, y, aHeight, 4);
    DrawLine(anObject, x + aWidth - 1, y, aHeight, 4);
}


void DrawFilledRect(objectType anObject, int x, int y, int aWidth, int aHeight, objectType aFillObject) {

    for (int counter1 = aHeight - 2; counter1 > 0; counter1--)
        DrawLine(aFillObject, x + 1, y + counter1, aWidth - 2, 2);
    DrawRect(anObject, x, y, aWidth, aHeight);
}


//EOF