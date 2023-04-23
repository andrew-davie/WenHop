#include "main.h"

// #include "amoeba.h"
#include "atarivox.h"
#include "attribute.h"
#include "colour.h"
#include "decodecaves.h"
#include "random.h"
#include "sound.h"

// static int amoebaCounter;
#if 0

static bool amoebaCanGrow;
static bool amoebaGrew;

bool lastAmoebaCanGrow;
unsigned int expandSpeed;
static unsigned int changeAmoebaToBoulder;



void initAmoeba() {

    amoebaCounter = 0;
    amoebaCanGrow = true;
    lastAmoebaCanGrow = true;


}



void handleAmoeba() {

    if (!lastAmoebaCanGrow) {
        *thiss = CH_DOGE_00;
        totalDiamondsPossible++;
        return;
    }

    if (changeAmoebaToBoulder > MAXIMUM_AMOEBA_SIZE) {
        *thiss = CH_BOULDER;
        return;
    }

    amoebaCounter++;


    if (!(rndX & 0x10))
        *thiss = (rndX & 3) + CH_AMOEBA_0;

    // if (amoebaGrew)
    //     return;

    // MUST do *up to* 4 directions to get amoebaCanGrow correct

    int base = rndX;
    for (int i = 0; i < 4; i++) {

        unsigned char *where = thiss + dirOffset[(i + base) & 3];
        if (Attribute[CharToType[GET(*where)]] & ATT_PERMEABLE) {

            rndX = /*(rndX >> 30) | (rndX << 1); //*/getRandom32();
            amoebaCanGrow = true;

            if (!amoebaGrew && (rndX >> 18) < expandSpeed) {
                *where = CH_AMOEBA_0 | FLAG_THISFRAME;
                amoebaGrew = true;
                return;
            }
        }
    }

    // expandSpeed++;
}



void checkAmoeba() {

    if (amoebaCounter && lastAmoebaCanGrow && !amoebaCanGrow) {
        FLASH(0xDA, 8);
        ADDAUDIO(SFX_WHOOSH);
    }

    lastAmoebaCanGrow = amoebaCanGrow;
    amoebaCanGrow = false;
    amoebaGrew = false;

    changeAmoebaToBoulder = amoebaCounter;
    if (changeAmoebaToBoulder > MAXIMUM_AMOEBA_SIZE) {
        FLASH(0x2A, 8);
        SAY(__WORD_TOO_LATE);
    }

    if (amoebaCounter) {
        ADDAUDIO(SFX_AMOEBA);
        amoebaCounter = 0;
    }
    else {
 //       FLASH(0x92, 8);
        killAudio(SFX_AMOEBA);
    }
}

#endif

// EOF