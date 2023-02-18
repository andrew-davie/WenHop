#include "main.h"

#include "amoeba.h"
#include "atarivox.h"
#include "attribute.h"
#include "colour.h"
#include "decodecaves.h"
#include "random.h"
#include "sound.h"

static int amoebaCounter;
const signed char dirOffset[] = { -1, 1, -40, 40 };

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
        *this = CH_DIAMOND;
        totalDiamondsPossible++;
        return;
    }

    if (changeAmoebaToBoulder > MAXIMUM_AMOEBA_SIZE) {
        *this = CH_BOULDER;
        return;
    }

    amoebaCounter++;


    if (!(rndX & 0x10))
        *this = (rndX & 3) + CH_AMOEBA_0;

    // if (amoebaGrew)
    //     return;

    // MUST do *up to* 4 directions to get amoebaCanGrow correct

    int base = rndX;
    for (int i = 0; i < 4; i++) {

        unsigned char *where = this + dirOffset[(i + base) & 3];
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

//EOF