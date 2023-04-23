#include "defines_cdfj.h"
#include "main.h"
#include <stdbool.h>

#include "bitpatterns.h"
#include "defines.h"
#include "overlay.h"
#include "player.h"
#include "sound.h"

#if ENABLE_OVERLAY

const unsigned char (*overlayWord)[5];

int overlayStep = 64; // 1 << 8;
int sIndex = 0;
int rotateOffset = 0;
int fIndex = 0;
int fSpeed = 0x305;

const unsigned char overlayATT_ROCKDash[][5] = {

    {
        X___X___,
        XX___XX_,
        XX_X_XX_,
        XX__XXXX,
        ____XXX_,
    },
    {
        X___X___,
        X_X_XX_X,
        XX_X_XX_,
        X_X_XX__,
        ___X_XX_,
    },
    {
        X___X___,
        X_X_XX_X,
        XX_X_XX_,
        X_X_XX__,
        ___X_XX_,
    },
    {
        X___X___,
        XX__XX_X,
        XX_X_XX_,
        X_X_XXXX,
        ___X_XX_,
    },
    {
        X___X___,
        X_X_XX_X,
        XX_X_XX_,
        X_X_XX__,
        ____XXX_,
    },
    {
        X___X___,
        X_X_XX_X,
        XX_X_XX_,
        X_X_XX__,
        ___X_XX_,
    },
    {
        X___X_XX,
        XXX_XXXX,
        XX_X_XX_,
        XXX_XXXX,
        ___X_XX_,
    },
    {
        X___X_XX,
        XX___XX_,
        XX_XXX__,
        XX__XXXX,
        ___X_XX_,
    },
    {
        ________,
        ________,
        ________,
        ________,
        ________,
    },
    {
        ____XX__,
        _______X,
        _XX___XX,
        X_XX_X__,
        ________,
    },
    {
        _____XX_,
        _______X,
        X_XX_X_X,
        __XX_X__,
        ________,
    },
    {
        _____XX_,
        _______X,
        X_XX_X_X,
        __XX_X__,
        ________,
    },
    {
        ____XX__,
        _______X,
        XXXX_X_X,
        __XXXX__,
        ________,
    },
    {
        ____X___,
        _______X,
        X_XX_X_X,
        X_XX_X__,
        ________,
    },
    {
        ________,
        _______X,
        X_XX_X_X,
        X_XX_X__,
        ________,
    },
    {
        ____XXX_,
        _______X,
        X_XX_XXX,
        X_XX_X__,
        ________,
    },
    {
        ____XXX_,
        _______X,
        X_XX__XX,
        __XX_X__,
        ________,
    },

    // ________ ________ ________ ________ ________
    // ________ ______X_ ________ _X______ ________
    // ________ _____XX_ ________ _XX_____ ________
    // ________ ______XX ________ XX______ ________
    // ________ _______X X_XXXX__ X_______ ________
    // ________ ________ _XXXXXX_ ________ ________
    // ________ ________ XXXXXXXX ________ ________
    // ________ ________ X__XX__X ________ ________
    // ________ ________ X__XX__X ________ ________
    // ________ ________ XXXX_XXX ________ ________
    // ________ ________ _XX__XX_ ________ ________
    // ________ ________ __XXXX_X ________ ________
    // ________ ________ X__X_X_X X_______ ________
    // ________ _______X X_______ X_______ ________
    // ________ _______X __X_X___ XX______ ________
    // ________ _____XX_ __XXXX__ _XX_____ ________
    // ________ ______X_ __XXXX__ _X______ ________

};

//

const unsigned char overlayGameOver[][5] = {

    {
        ____X_XX,
        ______XX,
        X__XX__X,
        __XXXX__,
        ________,
    },
    {
        ____XXXX,
        _____XX_,
        X_X_XX__,
        X_XX____,
        ________,
    },
    {
        ____XXXX,
        _____XX_,
        X_X_XX__,
        X_XX____,
        ________,
    },
    {
        _____X_X,
        _____XX_,
        X_X_XX_X,
        X_XXXX__,
        ________,
    },
    {
        _____X_X,
        _____XX_,
        X_XXXX_X,
        X_XX____,
        ________,
    },
    {
        _____X_X,
        _____XX_,
        X_XXXX_X,
        X_XX____,
        ________,
    },
    {
        _____X_X,
        _____XX_,
        X_X_XX_X,
        X_XXXX__,
        ________,
    },
    {
        _____X_X,
        ______XX,
        X_X_XX_X,
        X_XXXX__,
        ________,
    },

    {
        ________,
        ________,
        ________,
        ________,
        ________,
    },

    {
        ____XXXX,
        _______X,
        _X_XX__X,
        _XXX____,
        ________,
    },
    {
        ______XX,
        ______XX,
        _X_XX_X_,
        _XX_X___,
        ________,
    },
    {
        ______XX,
        ______XX,
        _X_XX_X_,
        _XX_X___,
        ________,
    },
    {
        ____XXXX,
        ______XX,
        _X_XX_X_,
        _XX_X___,
        ________,
    },
    {
        ______XX,
        ______XX,
        _X_XX_X_,
        _XXX____,
        ________,
    },
    {
        ______XX,
        ______XX,
        _XXXX_X_,
        _XXXX___,
        ________,
    },
    {
        ____XXXX,
        ______XX,
        __XX__XX,
        _XX_X___,
        ________,
    },
    {
        ____XXXX,
        _______X,
        __X____X,
        _XX_X___,
        ________,
    },
};

const int sinStep[][2] = {
    {
        0,
        0,
    },
    {
        9,
        499,
    },
    {
        17,
        250,
    },
    {
        26,
        168,
    },
    {
        34,
        127,
    },
    {
        42,
        102,
    },
    {
        50,
        87,
    },
    {
        57,
        75,
    },
    {
        64,
        67,
    },
    {
        71,
        61,
    },
    {
        77,
        56,
    },
    {
        82,
        53,
    },
    {
        87,
        50,
    },
    {
        91,
        48,
    },
    {
        94,
        46,
    },
    {
        97,
        45,
    },
    {
        98,
        44,
    },
    {
        100,
        43,
    },
    {
        100,
        43,
    },
};

void Overlay(const unsigned char word[][5]) {

    sIndex = fIndex >> 8;

    if (fSpeed < 120) {
        if (rotateOffset) {
            if (sIndex == 0) {
                fSpeed = -1;
                return;
            }
        }
    } else {

        fSpeed -= 2;
    }

    // if (sIndex == 0)
    //     addAudio(SFX_SPIN);

    if (sIndex > 35) {
        sIndex = 0;
        fIndex = 0;
        rotateOffset = rotateOffset ? 0 : 17;
    }

    if (fSpeed > 0)
        fIndex += fSpeed;

    if (sIndex > 18)
        sIndex = 18 - (sIndex - 18);

    int totalHeight = sinStep[sIndex][0];
    if (!totalHeight)
        return;

    overlayStep = sinStep[sIndex][1];

    unsigned char *base = RAM + 100 - sinStep[sIndex][0] / 2;
    int row = 0;

    int phase = 0;
    for (int i = 0; i < sinStep[sIndex][0] / 2; i++) {
        phase--;
        if (phase < 0)
            phase = 2;
    }

    unsigned char *pf0l = _BUF_PF0_LEFT + base;
    unsigned char *pf1l = _BUF_PF1_LEFT + base;
    unsigned char *pf2l = _BUF_PF2_LEFT + base;

    unsigned char *pf0r = _BUF_PF0_RIGHT + base;
    unsigned char *pf1r = _BUF_PF1_RIGHT + base;
    unsigned char *pf2r = _BUF_PF2_RIGHT + base;

    for (int scanline = 0; scanline < totalHeight; scanline++) {

        int rowIndex = (row >> 8);

        if (rotateOffset) {

            rowIndex = 16 - rowIndex;

            if (phase) {
                *pf0l &= ~word[rowIndex][0];
                *pf1l &= ~word[rowIndex][1];
                *pf2l &= ~word[rowIndex][2];
            }
        }

        if (!rotateOffset || phase == 0) {
            *pf0l |= word[rowIndex][0];
            *pf1l |= word[rowIndex][1];
            *pf2l |= word[rowIndex][2];
        }

        pf0l++;
        pf1l++;
        pf2l++;

        if (rotateOffset && phase) {
            *pf0r &= ~word[rowIndex][0] << 4;
            *pf1r &= ~word[rowIndex][3];
            *pf2r &= ~word[rowIndex][4];
        }
        if (!rotateOffset || !phase) {
            *pf0r |= word[rowIndex][0] << 4;
            *pf1r |= word[rowIndex][3];
            *pf2r |= word[rowIndex][4];
        }

        pf0r++;
        pf1r++;
        pf2r++;

        row += overlayStep;

        phase++;
        if (phase > 2)
            phase = 0;
    }
}

void GameScheduleDrawOverlay() {

    // Handle "GAME OVER" display
    // ... if the square doesn't contain player

    //    int what = RAM[_BOARD + playerY * 40 + playerX] & 0x7F;
    //    char type = CharToType[what];

    if (playerDead && !flashTime) {

        if (!lives) {

            if (overlayWord != overlayGameOver) {

                overlayWord = overlayGameOver;
                fIndex = 0;
                rotateOffset = 0;
                fSpeed = 0x120;
            }

            if (JOY0_FIRE) {

                if (fSpeed < 0)
                    rotateOffset = 0;

                if (fSpeed < 0x400)
                    fSpeed += 28;

                idleTimer = 0;

            }

            else {

                if (idleTimer++ > IDLE_TIME) {

                    displayMode ^= 1;
                    idleTimer = 0;
                    if (fSpeed < 0)
                        rotateOffset = 0;

                    if (fSpeed < 0x400)
                        fSpeed += 250;
                }
            }
        }

#if ENABLE_TOGGLE_DISPLAY_ON_DEATH

        else {

            // loss of a life -- switch display occasionally

            if (idleTimer++ > IDLE_TIME) {
                displayMode ^= 1;
                idleTimer = 0;
            }
        }
#endif
    }

    Overlay(overlayWord);
}

#endif
