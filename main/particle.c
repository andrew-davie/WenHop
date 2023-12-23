#include "defines.h"
#include "defines_cdfj.h"
#include "defines_from_dasm_for_c.h"

#include <stdbool.h>

#include "main.h"
#include "particle.h"

#include "attribute.h"
#include "colour.h"
#include "drawscreen.h"
#include "mellon.h"
#include "player.h"
#include "random.h"
#include "score.h"
#include "sound.h"

unsigned int ropeLength;
unsigned char ropeDirection[ROPE_PARTICLE_COUNT];

const int xsin[32] = {
    //    0, 97, 181, 236, 256, 236, 181, 97, 0, -97, -181, -236, -256, -236, -181, -97,
    0, 49,  97,  142,  181,  212,  236,  251,  256,  251,  236,  212,  181,  142,  97,  49,
    0, -49, -97, -142, -181, -212, -236, -251, -256, -251, -236, -212, -181, -142, -97, -49,
};

void modifyCharAtTip(int x, int y) {

    int xchar = (x * (256 / 5)) >> 16;
    int ychar = (y * (256 / 10)) >> 16;

    unsigned char *b = RAM + _BOARD + ychar * _BOARD_COLS + xchar;
    int ch = CharToType[GET(*b)];
    int audio = SFX_DRIP;

    if (ch == TYPE_ROCK) {
        *b = CH_GEODOGE | FLAG_THISFRAME;
        audio = SFX_ROCK;
    } else if (ch == TYPE_GEODOGE) {
        *b = CH_DOGE_00 | FLAG_THISFRAME;
        audio = SFX_DOGE3;
    } else if (ch == TYPE_DIRT) {
        *b = CH_DUST_0 | FLAG_THISFRAME;
        audio = SFX_DIRT;
    } else if (ch == TYPE_DOGE) {
        audio = SFX_BUBBLER;
        *b = CH_DOGE_00 | FLAG_THISFRAME;
    }

    if (*b & FLAG_THISFRAME) {

        if (audio != SFX_DRIP)
            ADDAUDIO(audio);
        nDotsAtTrixel(5, (x >> 8) + 2, (y >> 8) + 5, 30, 50);
    }
}

// bool ropeEnabled = false;
const int PIXEL_ASPECT = 181;

void drawRope() {

    if (--ropeLength > ROPE_PARTICLE_COUNT) // relies on unsigned int arithmetic
        ropeLength = ROPE_PARTICLE_COUNT;

    int baseX = (playerX * 5 + 2 + ((faceDirection * autoMoveX) >> 2)) << 8;
    int baseY = ((playerY * 10 + 6) << 8) + (autoMoveY * (256 / 3));

    int x = 0, y = 0;

    for (unsigned int i = 0; i < ropeLength; i++) {

        x += (xsin[(ropeDirection[i] >> 3) & 0x1F] * PIXEL_ASPECT) >> 8;
        y += (xsin[((ropeDirection[i] >> 3) + 4) & 0x1F] * 256) >> 8;

        drawBit((baseX + x) >> 8, (baseY + y) >> 8);
        drawBit((baseX - x) >> 8, (baseY - y) >> 8);
    }

    modifyCharAtTip(baseX + x, baseY + y);
    modifyCharAtTip(baseX - x, baseY - y);

    static int wantedDirection = 0;

    if (ropeDirection[0] == wantedDirection)
        wantedDirection = rangeRandom(256);

    else if (wantedDirection > ropeDirection[0])
        ropeDirection[0] += ((wantedDirection - ropeDirection[0]) >> 2) + 1;

    else
        ropeDirection[0] -= ((ropeDirection[0] - wantedDirection) >> 2) + 1;

    for (int i = ropeLength - 1; i > 0; i--)
        ropeDirection[i] = (ropeDirection[i] + ropeDirection[i - 1] * 3) >> 2;
}

struct Particle particle[PARTICLE_COUNT];

void drawParticles() {

    for (int i = 0; i < PARTICLE_COUNT; i++) {
        if (particle[i].age) {

            int xOffset = (xsin[particle[i].direction >> 3] * particle[i].distance) >> 8;
            int yOffset =
                (xsin[((particle[i].direction >> 3) + 8) & 0x1F] * particle[i].distance * 3) >> 8;

            int y = (particle[i].y + yOffset) >> 8;
            int x = (particle[i].x + xOffset) >> 8;

            switch (particle[i].type) {

            case PT_TWO: {

                break;
            }

            case PT_SPIRAL2:
            case PT_SPIRAL: {

                particle[i].direction += PARTICLE_SPIRAL_ANGULAR_SPEED;

                if (!rangeRandom(250))
                    nDotsAtTrixel(4, x, y, 30, 0x20);
                break;
            }

            case PT_BUBBLE: {

                // FLASH(0xD2, 4);

                if (y < lavaSurfaceTrixel) {
                    particle[i].age = 0;
                    continue;
                }

                particle[i].y -= particle[i].speed;
                x += rangeRandom(3) - 1; // wobble
                break;
            }

            default:
                break;
            }

            if (!drawBit(x, y))
                particle[i].age = 0;

            else {

                --particle[i].age;

                particle[i].distance += particle[i].speed;
            }
        }
    }
}

// EOF
