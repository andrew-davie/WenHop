#include <limits.h>

#include "defines.h"
#include "defines_cdfj.h"

#include "main.h"
#include "menu.h"

#include "animations.h"
#include "atarivox.h"
#include "bitpatterns.h"
#include "cavedata.h"
#include "characterset.h"
#include "colour.h"
#include "decodecaves.h"
#include "drawscreen.h"
#include "joystick.h"
#include "mellon.h"
#include "overlay.h"
#include "player.h"
#include "random.h"
#include "score.h"
#include "sound.h"

#if DEBUG_TIMER
unsigned int debugDelay = 0;
#endif

#define LETTER_HEIGHT 10

#define OPTION_SYSTEM 2

void doubleSize(int x, int y, int letter);

unsigned char enableICC;
int menuLineTVType;

static int mustWatchDelay;
static int pushFrame;
static int frame;
static int base2;
static int pushCount;
static unsigned int menuLine;
static int caveUnpackComplete;

int thumbnailSpeed;

unsigned int sline = 0;

#define DETECT_FRAME_COUNT 10

void detectConsoleType() {

    switch (frame) {

    case 0:

        mm_tv_type = TV_TYPE = 0; // force NTSC frame

        T1TC = 0;
        T1TCR = 1;
        break;

    case DETECT_FRAME_COUNT: {

        int detectedPeriod = T1TC;

        static const struct fmt {

            int frequency;
            unsigned char format;

        } mapTimeToFormat[] = {

        // Timings from Gopher, 20220827

#define NTSC_70MHZ (0xB25FCD * DETECT_FRAME_COUNT / 10)
#define PAL_70MHZ (0xB3856E * DETECT_FRAME_COUNT / 10)
#define SECAM_70MHZ (((PAL_70MHZ - NTSC_70MHZ) / 2 + NTSC_70MHZ) * DETECT_FRAME_COUNT / 10)

            {
                NTSC_70MHZ,
                NTSC,
            },
            {
                SECAM_70MHZ,
                SECAM,
            },
            {
                PAL_70MHZ,
                PAL_60,
            },

#if ENABLE_60MHZ_AUTODETECT

#define NTSC_60MHZ (0x98EB2F * DETECT_FRAME_COUNT / 10)
#define PAL_60MHZ (0x9A0EEF * DETECT_FRAME_COUNT / 10)
#define SECAM_60MHZ (((PAL_60MHZ - NTSC_60MHZ) / 2 + NTSC_60MHZ) * DETECT_FRAME_COUNT / 10)

            {
                NTSC_60MHZ,
                NTSC,
            },
            {
                SECAM_60MHZ,
                SECAM,
            },
            {
                PAL_60MHZ,
                PAL_60,
            },
#endif
        };

        int delta = INT_MAX;
        for (unsigned int i = 0; i < sizeof(mapTimeToFormat) / sizeof(struct fmt); i++) {

            int dist = detectedPeriod - mapTimeToFormat[i].frequency;
            if (dist < 0)
                dist = -dist;

            if (dist < delta) {
                delta = dist;
                mm_tv_type = mapTimeToFormat[i].format;
            }
        }

        menuLineTVType = TV_TYPE = mm_tv_type;
        break;
    }

    default:
        break;
    }

    frame++;
}

void clearBuffer(int *buffer, int size) {

    for (int i = 0; i < size; i++)
        buffer[i] = 0;
}

void initMenuDatastreams() {

    static const struct ptrs {

        unsigned char dataStream;
        unsigned short buffer;

    } streamInits[] = {

        {_DS_PF1_LEFT, _BUF_MENU_PF1_LEFT},
        {_DS_PF2_LEFT, _BUF_MENU_PF2_LEFT},
        {_DS_PF1_RIGHT, _BUF_MENU_PF1_RIGHT},
        {_DS_PF2_RIGHT, _BUF_MENU_PF2_RIGHT},
        {_DS_AUDV0, _BUF_AUDV},
        {_DS_AUDC0, _BUF_AUDC},
        {_DS_AUDF0, _BUF_AUDF},
#if __ENABLE_ATARIVOX
        {_DS_SPEECH, _BUF_SPEECH},
#endif
        {_DS_COLUPF, _BUF_MENU_COLUPF},
        {_DS_COLUP0, _BUF_MENU_COLUP0},
        {_DS_GRP0a, _BUF_MENU_GRP0A},
        {_DS_GRP1a, _BUF_MENU_GRP1A},
        {_DS_GRP0b, _BUF_MENU_GRP0B},
        {_DS_GRP1b, _BUF_MENU_GRP1B},
        {_DS_GRP0c, _BUF_MENU_GRP0C},
        {_DS_GRP1c, _BUF_MENU_GRP1C},
        {0x21, _BUF_JUMP1},

    };

    for (unsigned int i = 0; i < sizeof(streamInits) / sizeof(struct ptrs); i++)
        setPointer(streamInits[i].dataStream, streamInits[i].buffer);

    // QINC[_DS_SPEECH] = 0;
}

int butterflyOffset[] = {
    0, 37, 68, 96};

const unsigned char butterfly[] = {

    36,

    _XX____X,
    _XX____X,
    ________,
    _XXX_XXX,
    _XX___XX,
    ________,
    _XXX_XXX,
    _XX___XX,
    __XX_XX_,
    _XXXXXXX,
    _XXXXXXX,
    __XX__X_,
    __XXXXXX,
    __XX_XXX,
    __X___X_,
    __XXXXX_,
    __XX_XX_,
    ________,
    __XXXX__,
    __XX_X__,
    ________,
    _XXXXX__,
    _XX_XX__,
    ________,
    _XXXXX__,
    _XX_XX__,
    __X__X__,
    _XXXXX__,
    _XX_XX__,
    __X__X__,
    _XX_XX__,
    _XX_XX__,
    ________,
    _XX_XX__,
    _XX_XX__,
    ________,

    30,
    ___X_XX_,
    ___X_XX_,
    ________,
    ___X_XX_,
    ___X_XX_,
    ___X_X__,
    ___XXXX_,
    ___XXXX_,
    ___X_X__,
    ___XXXX_,
    ___X_XX_,
    ___X_X__,
    ___XXX__,
    ___X_X__,
    ________,
    ___XXX__,
    ___X_X__,
    ________,
    __XXXX__,
    __X_XX__,
    ________,
    __XXXX__,
    __X_XX__,
    __X_X___,
    __XXX___,
    __X_X___,
    __X_X___,
    __X_X___,
    __X_X___,
    ________,

    27,

    __XXX___,
    __XXX___,
    ________,
    _XXXXX__,
    _XX_XX__,
    ___X____,
    _XXXXX__,
    _X___X__,
    __XXX___,
    _XXXXX__,
    _X___X__,
    __XXX___,
    _XXXXX__,
    _X___X__,
    __XXX___,
    _XXXXX__,
    _X___X__,
    __XXX___,
    _XXXXX__,
    _X___X__,
    __XXX___,
    _XXXXX__,
    _XX_XX__,
    ___X____,
    __XXX___,
    __XXX___,
    ________,

    21,
    ________,
    ________,
    ________,
    ___X____,
    ___X____,
    ________,
    __XXX___,
    __XXX___,
    ________,
    __X_X___,
    __XXX___,
    ________,
    __X_X___,
    __XXX___,
    ________,
    __XXX___,
    __XXX___,
    ________,
    ___X____,
    ___X____,
    ________,
};

#if ENABLE_ANIMATING_MAN
const unsigned short manPushing[][129] = {

    {
        128,

        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000111110000,
        0b0000000111100000,
        0b0000000111100000,
        0b0000000111100000,
        0b0000001111111000,
        0b0000001111110000,
        0b0000001111110000,
        0b0000001111110000,
        0b0000011111111100,
        0b0000011111111000,
        0b0000011000111000,
        0b0000011000111000,
        0b0000011111111100,
        0b0000011000011000,
        0b0000010111101000,
        0b0000010000001000,
        0b0000111111111110,
        0b0000110000011100,
        0b0000111111101100,
        0b0000110000001100,
        0b0000111111111110,
        0b0000110000011100,
        0b0000101100000100,
        0b0000100000000100,
        0b0000111111111110,
        0b0000110011111100,
        0b0000101100000100,
        0b0000100000000100,
        0b0001111111111111,
        0b0001110011111110,
        0b0001100100000110,
        0b0001100000000110,
        0b0001111111111111,
        0b0001110000011110,
        0b0001001100000010,
        0b0001000000000010,
        0b0001111111111111,
        0b0001110000111110,
        0b0001000111000010,
        0b0001000011000010,
        0b0001111111111111,
        0b0001110000111110,
        0b0001001111000010,
        0b0001000011000010,
        0b0001111111111111,
        0b0001100000111110,
        0b0001011111000010,
        0b0001011111000010,
        0b0001111111111111,
        0b0001100000111110,
        0b0001010011000010,
        0b0001011111000010,
        0b0001111111111111,
        0b0001100000111110,
        0b0001010011000010,
        0b0001011111000010,
        0b0001111111111111,
        0b0001100000111110,
        0b0001011111000010,
        0b0001011111000010,
        0b0001111111111111,
        0b0001110000111110,
        0b0001000111000010,
        0b0001000011000010,
        0b0001111111111111,
        0b0001110000111110,
        0b0001001111000010,
        0b0001000011000010,
        0b0001111111111111,
        0b0001110000111110,
        0b0001000111000010,
        0b0001000011000010,
        0b0001111111111111,
        0b0001110000111110,
        0b0001101111000110,
        0b0001100011000110,
        0b0000111111111110,
        0b0000111100111100,
        0b0000100011000100,
        0b0000100011000100,
        0b0000111111111110,
        0b0000111100111100,
        0b0000100011000100,
        0b0000100011001100,
        0b0000111111111110,
        0b0000111100111100,
        0b0000110011001100,
        0b0000110011001100,
        0b0000011111111100,
        0b0000011100111000,
        0b0000010011001000,
        0b0000011011011000,
        0b0000011111111100,
        0b0000011100111000,
        0b0000011011011000,
        0b0000011111111000,
        0b0000001111111000,
        0b0000001100110000,
        0b0000001111110000,
        0b0000001111110000,
        0b0000000111110000,
        0b0000000100100000,
        0b0000000111100000,
        0b0000000111100000,
        0b0000000011000000,
        0b0000000000000000,
        0b0000000011000000,
        0b0000000011000000,
        0b0000000011000000,
        0b0000000000000000,
        0b0000000011000000,
        0b0000000011000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
        0b0000000000000000,
    },
};
#endif

#if ENABLE_TITLE_PULSE
#define LUMINANCE_TITLE 6
#else
#define LUMINANCE_TITLE 0x6
#endif

#define LUMINANCE 4

char RGB[6];

const unsigned char titleScreenImagePalette[] = {
    0x24 + LUMINANCE, 0x40 + LUMINANCE, 0xD4 + LUMINANCE, // NTSC
};

#define BUT 4

static int butterflyX[BUT];
static int butterflyY[BUT];
// static int bdirX[BUT];
// static int bdirY[BUT];
static char bBase[BUT];

void doDrawBitmap(const unsigned short *shape, int y) {

    // unsigned char *pf1L = RAM + _BUF_PF1_LEFT;
    // unsigned char *pf2L = RAM + _BUF_PF2_LEFT;
    unsigned char *pf1R = RAM + _BUF_PF1_RIGHT;
    unsigned char *pf2R = RAM + _BUF_PF2_RIGHT;

    int size = shape[0];

    // const unsigned short *bf = shape + 1;

    int baseRoll = roller;

    union g {
        int bGraphic;
        unsigned char g[4];
    } gfx;

    for (int i = 1; i <= size; i += 4) {

        if (y >= _ARENA_SCANLINES - 3)
            return;

        static union masker {
            int mask;
            unsigned char mask2[4];
        } mask;

        mask.mask = shape[i] ^ 0xFFFFFFFF;

        for (int line = 0; line < 3; line++) {

            gfx.bGraphic = shape[i + baseRoll + 1];

            // pf1L[y] = (pf1L[y] & mask.mask2[3]) | gfx.g[3];
            pf1R[y] = (pf1R[y] & mask.mask2[1]) | gfx.g[1];
            pf2R[y] = (pf2R[y] & BitRev[mask.mask2[0]]) | BitRev[gfx.g[0]];
            // pf2L[y] = (pf2L[y] & BitRev[mask.mask2[2]]) | BitRev[gfx.g[2]];

            if (++baseRoll > 2)
                baseRoll = 0;

            y++;
        }
    }
}

#if ENABLE_ANIMATING_MAN
void doPlayer() {
    return;

    if (pushCount > 0) {
        pushCount--;
        pushFrame = 0;
    } else
        pushFrame = 1;

    if (!pushCount && !(rndX & 0xFF)) {
        pushFrame = 0; // ^= 1;
        pushCount = ((rndX >> 8) & 31) | 32;
    }

    int jiggle = 0;
    if (!pushFrame)
        jiggle = -((base2 >> 2) & 1) * 3;

    doDrawBitmap(manPushing[pushFrame], 120 + jiggle);
}
#endif

#if ENABLE_SNOW
void doSnow() {

    static const unsigned char snowbase[] = {26, 16, 0, 0, 16, 26};
    static const unsigned char snow[] = {

        15,
        _X_X____,
        _X_X____,
        _X_X____,
        __X_____,
        __X_____,
        __X_____,
        XXXXX___,
        XXXXX___,
        XXXXX___,
        __X_____,
        __X_____,
        __X_____,
        _X_X____,
        _X_X____,
        _X_X____,

        9,
        __X_____,
        __X_____,
        __X_____,
        _XXX____,
        _XXX____,
        _XXX____,
        __X_____,
        __X_____,
        __X_____,

        6,
        ________,
        ________,
        ________,
        __X_____,
        __X_____,
        __X_____,
    };

#define SNOW_SPEED 60

    // static int snowX = 20;
    static int snowY = 0;
    static int snowFrame = 0;
    int snowSpeed;
    int yrange;

    if (KERNEL != KERNEL_MENU) {
        snowSpeed = 80;
        yrange = 150;
    } else {
        snowSpeed = SNOW_SPEED;
        yrange = 50;
    }

    if (getRandom32() < 0x10000000 || snowFrame < 0) {

        if (KERNEL != KERNEL_MENU || !(getRandom32() & 63)) {

            if (KERNEL == KERNEL_MENU)
                ADDAUDIO(SFX_MAGIC2);

            snowFrame = 0x5FF;

            snowY = rangeRandom(yrange);
            if (KERNEL == KERNEL_MENU && snowY > 27) {
                snowY += 7;
                // snowX = rangeRandom(20) + 2;
            }
            // else
            //     snowX = rangeRandom(36);
        }

    } else {

        int base = snowbase[snowFrame >> 8];
        doDrawBitmap(snow + base, snowY + ((base + 6) >> 4));
        snowFrame -= snowSpeed;
    }
}
#endif

const unsigned char charAtoZ[] = {

    __XXX___,
    _XXXXX__,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,

    XXXXXX__,
    XXXXXXX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXX__,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXX__,

    __XXXXX_,
    _XXXXXX_,
    XXXX____,
    XXX_____,
    XXX_____,
    XXX_____,
    XXXX____,
    XXXXXXX_,
    _XXXXXX_,
    __XXXXX_,

    XXXXX___,
    XXXXXX__,
    XXX_XXX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXX__,

    XXXXXXX_,
    XXXXXXX_,
    XXX_____,
    XXXXX___,
    XXXXX___,
    XXX_____,
    XXX_____,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,

    XXXXXXX_,
    XXXXXXX_,
    XXX_____,
    XXX_____,
    XXXXX___,
    XXXXX___,
    XXXXX___,
    XXX_____,
    XXX_____,
    XXX_____,

    __XXXXX_,
    _XXXXXX_,
    XXXX____,
    XXX_XXX_,
    XXX_XXX_,
    XXX__XX_,
    XXXX_XX_,
    XXXXXXX_,
    _XXXXXX_,
    __XXXXX_,

    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,

    _XXXXX__,
    _XXXXX__,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,
    _XXXXX__,
    _XXXXX__,
    _XXXXX__,

    ____XXX_,
    ____XXX_,
    ____XXX_,
    ____XXX_,
    ____XXX_,
    ____XXX_,
    XXX_XXX_,
    XXXXXXX_,
    XXXXXXX_,
    _XXXXX__,

    XXX___X_,
    XXX__XX_,
    XXX_XXX_,
    XXXXXX__,
    XXXXX___,
    XXXXX___,
    XXXXXX__,
    XXXXXXX_,
    XXX_XXX_,
    XXX__XX_,

    XXX_____,
    XXX_____,
    XXX_____,
    XXX_____,
    XXX_____,
    XXX_____,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,

    XX___XX_,
    XXX_XXX_,
    XXXXXXX_,
    XXXXXXX_,
    XX_X_XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,

    XX___XX_,
    XXX__XX_,
    XXXX_XX_,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,
    XX_XXXX_,
    XXX_XXX_,
    XXX__XX_,
    XXX__XX_,

    _XXXXX__,
    XXXXXXX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    _XXXXX__,

    XXXXX___,
    XXXXXX__,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXX__,
    XXX_____,
    XXX_____,
    XXX_____,

    _XXXXX__,
    XXXXXXX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX_XXX_,
    XXXXXX__,
    XXXXXXXX,
    _XXX_XXX,

    XXXXX___,
    XXXXXX__,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXX__,
    XXXXX___,
    XXXXXX__,
    XXX_XXX_,
    XXX__XX_,

    __XXXXX_,
    _XXXXXX_,
    XXXX____,
    XXXX____,
    XXXXXX__,
    _XXXXXX_,
    ___XXXX_,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXX__,

    XXXXXXX_,
    XXXXXXX_,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,

    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    _XXXXXX_,
    __XXXX__,

    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    _XXXXX__,
    _XXXXX__,
    _XXXXX__,
    __XXX___,
    __XXX___,

    XXX___XX,
    XXX___XX,
    XXX___XX,
    XXX___XX,
    XXX___XX,
    XXX_X_XX,
    XXXXXXXX,
    XXXXXXXX,
    XXXX_XXX,
    XXX___XX,

    XXX__XX_,
    XXX__XX_,
    XXX_XXX_,
    XXXXXX__,
    _XXXX___,
    __XXXX__,
    _XXXXXX_,
    XXX_XXX_,
    XX__XXX_,
    XX__XXX_,

    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    _XXXXX__,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,

    XXXXXXX_,
    XXXXXXX_,
    ____XXX_,
    ___XXXX_,
    __XXXX__,
    _XXXX___,
    XXXX____,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,

    _XXXXX__,
    XXXXXXX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    _XXXXX__,

    ___XX___,
    __XXX___,
    __XXX___,
    __XXX___,
    ___XX___,
    ___XX___,
    ___XX___,
    __XXXX__,
    __XXXX__,
    __XXXX__,

    _XXXXX__,
    XXXXXXX_,
    XXX_XXX_,
    ____XXX_,
    ___XXX__,
    __XXX___,
    _XXX____,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,

    XXXXXXX_,
    XXXXXXX_,
    ____XXX_,
    ___XXX__,
    __XXXX__,
    ____XXX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    _XXXXX__,

    ___XXX__,
    __XXXX__,
    _XXXXX__,
    XXX_XX__,
    XX__XX__,
    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,
    ____XX__,
    ____XX__,

    XXXXXXX_,
    XXXXXXX_,
    XXX_____,
    XXXXXX__,
    XXXXXXX_,
    _____XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    _XXXXX__,

    _XXXXX__,
    XXXXXX__,
    XXX_____,
    XXX_____,
    XXXXXX__,
    XXXXXXX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    _XXXXX__,

    XXXXXXX_,
    XXXXXXX_,
    XXXXXXX_,
    ____XXX_,
    ___XXX__,
    ___XXX__,
    __XXX___,
    __XXX___,
    __XXX___,
    __XXX___,

    _XXXXX__,
    XXXXXXX_,
    XXX__XX_,
    _XXXXX__,
    XXXXXXX_,
    XXX__XX_,
    XXX__XX_,
    XXXXXXX_,
    XXXXXXX_,
    _XXXXX__,

    _XXXXX__,
    XXXXXXX_,
    XX__XXX_,
    XX__XXX_,
    XX__XXX_,
    XXXXXXX_,
    _XXXXXX_,
    ____XXX_,
    _XXXXX__,
    _XXXX___,

    __XXXX__,
    _X____X_,
    X_XXX__X,
    X_X__X_X,
    X_X__X_X,
    X_XXX__X,
    X_X_X__X,
    X_X__X_X,
    _X____X_,
    __XXXX__,

    ________,
    ________,
    ________,
    ________,
    ________,
    ________,
    ________,
    ________,
    ________,
    ________,

};

const char wordTvType0[] = {
    XXXXXX__,
    _X___XXX,
    X___X_XX,
    XXXXXXXX,
    XX_X___X,
    ________,
    XXXX_XX_,
    XX__XX__,
    XX_XXXX_,
    _XXXX_XX,
    XX_XX_XX,
    ________,
    __X___X_,
    X____XXX,
    _XXX__XX,
    X__X__X_,
    ___XXXXX,
    ________,
    __X___XX,
    X______X,
    X_X_____,
    XX_X__XX,
    X__X_X_X,
    ________,
    __X____X,
    ____XXXX,
    X_X__XXX,
    XX_X__X_,
    ___X___X,
    ________,
    __X____X,
    ____XXXX,
    __X__XXX,
    X__X__XX,
    XX_X___X,
    ________,
};

const char wordStartAt[] = {
    _XXXXXXX,
    X_XX__XX,
    X_XXXXX_,
    __XX_XXX,
    XX______,
    ________,
    XX__XXXX,
    XXXXX_XX,
    XXXXXXX_,
    _XXXXXXX,
    XX______,
    ________,
    XXXX__X_,
    _X__X_X_,
    _X__X___,
    _X__X__X,
    ________,
    ________,
    ___XX_X_,
    _XXXX_XX,
    XX__X___,
    _XXXX__X,
    ________,
    ________,
    XXXXX_X_,
    _X__X_XX,
    X___X___,
    _X__X__X,
    ________,
    ________,
    XXXX__X_,
    _X__X_X_,
    _X__X___,
    _X__X__X,
    ________,
    ________,
};

const char wordDifficulty[] = {

    XXX__XXX,
    _XXXX_XX,
    XX_XXX__,
    XXX_X__X,
    _X__XXXX,
    XX___X__,
    X__X_XXX,
    _XXX__XX,
    X__XXX_X,
    X___X__X,
    _X__XXXX,
    XXX_XX__,
    X__XX_X_,
    _X____X_,
    ____X__X,
    ____X__X,
    _X____X_,
    __XXX___,
    X__XX_X_,
    _XXX__XX,
    X___X__X,
    X___X__X,
    _X____X_,
    ___X____,
    XXXXX_X_,
    _X____X_,
    ____X__X,
    XXX_XXXX,
    _XXXX_X_,
    ___X____,
    XXXX_XXX,
    _X____X_,
    ___XXX__,
    XXX__XX_,
    _XXXX_X_,
    ___X____,
};

#if ENABLE_EASTER_MYNAME
const char andrewDavie[] = {
    _XX_____,
    ___XX___,
    X_XX_X__,
    X__XXX__,
    __XX__X_,
    X_X__XX_,
    XX_X____,
    ___XX___,
    XXXX_X__,
    X__XXXX_,
    ___XX_X_,
    X_X_XXX_,
    XX_X_XX_,
    _XXXX__X,
    _X_X_X__,
    X__XX_XX,
    __XXX_X_,
    X___X_X_,
    XXXX_XXX,
    XX__X_XX,
    _XX__XXX,
    X__XX__X,
    _XX_X_X_,
    X_X_XX__,
    XXXX_X_X,
    XXXXX_X_,
    _XXX_XXX,
    X__XXXXX,
    _XXXX_XX,
    X_X_XXX_,
    XX_X_X_X,
    _XXXX_X_,
    __XX_X__,
    X__XXXX_,
    __XXX_XX,
    __X__XX_,
};
#endif

void drawCharacter(int x, int y, int ch) {

    if (ch == ' ')
        ch = '0' + 11;

    ch -= 'A';
    if (ch < 0)
        ch += 43;
    const unsigned char *p = charAtoZ + ch * 10;
    unsigned char *col = RAM + _BUF_MENU_GRP0A + _ARENA_SCANLINES * x + y;

    for (int i = 0; i < LETTER_HEIGHT; i++)
        *col++ = *p++;
}

void drawString(int x, int y, const char *text, int colour) {
    return; // tmp
    while (*text && x < 6)
        drawCharacter(x++, y, *text++);

    for (int i = 0; i < LETTER_HEIGHT; i++)
        RAM[_BUF_MENU_COLUP0 + i + y - 1] = convertColour(colour);
}

void drawSmallProxy(unsigned char colour, int y, const char *smallText) {

    for (int line = 0; line < 6; line++) {
        RAM[_BUF_MENU_COLUP0 + y + line - 1] = colour;
        for (int i = 0; i < 6; i++)
            RAM[_BUF_MENU_GRP0A + _ARENA_SCANLINES * i + y + line] = *smallText++;
    }
}

void drawSmallString(int y, const char *smallText) {
    static const unsigned char smallColour[] = {0x98, 0xB8, 0xB8, 0x0A};
    int colour = smallColour[mm_tv_type];
    drawSmallProxy(colour, y, smallText);
}

int flashTime2 = 0;

char showCave[] = {"CAVE;;"};

const char TV[][6] = {

    {"NTSC;;"},
    {"PAL;;;"},
    {"PAL60;"},
    {"SECAM;"},
};

const char Level[][6] = {

    {"NORMAL"},
    {"MEDIUM"},
    {"HARD;;"},
    {"EXPERT"},
    {"SUPER;"},
};

const char *smallWord[] = {
    wordStartAt,
    wordDifficulty,
    wordTvType0,
};

void SchedulerMenu() {
}

#if ENABLE_TITLE_PULSE
extern const unsigned char sinoid[];
#endif

void setTitleMarqueeColours(int a, int b) {

    unsigned char *p = RAM + _BUF_MENU_COLUPF;

    int baseRoller = roller + 1;

#if ENABLE_TITLE_PULSE

    static unsigned int flashc = 0;
    flashc += 0x2000000;

    // Note: low bit unused/superfluous
    static const unsigned char sinus[] = {2, 2, 4, 4, 6, 6, 8, 8, 8, 8, 6, 6, 4, 4, 2, 2};

    int flash = sinus[flashc >> 28];
    int flash2 = sinus[(flashc ^ 0x80000000) >> 28];

#endif

    for (int i = 0; i < _ARENA_SCANLINES; i++) {

        if (++baseRoller > 2)
            baseRoller -= 3;

        int offset = i < a ? 0 : 3;

        if (i < b) {
            p[i] = RGB[baseRoller + offset];

#if ENABLE_TITLE_PULSE
            if (mm_tv_type != SECAM) {
                if (i < a)
                    p[i] |= flash;
                else
                    p[i] |= flash2;
            }
#endif
        } else
            p[i] = convertColour(titleScreenImagePalette[baseRoller]);
    }
}

void handleMenuScreen() {

    if (!(SWCHA & 0xF0)) // UDLR at same time!
        drawString(0, 182, "ZPH001", 0);
    else
        drawString(0, 182, "      ", 0);

    // getRandom32();

    sline++;
    if (sline >= sizeof(smallWord) / sizeof(smallWord[0]))
        sline = 0;

    int y = sline * 24 + 93;

    if (flashTime2)
        --flashTime2;

    const char *dLine = 0;

    switch (sline) {

    case 0:
        showCave[5] = 'A' + cave;
        dLine = showCave;
        break;

    case 1:
        dLine = Level[level];
        break;

    case OPTION_SYSTEM:
        dLine = TV[menuLineTVType];
        break;
    }

    // tmp    drawSmallString(y, smallWord[sline]);

#if ENABLE_EASTER_MYNAME
    if (!(SWCHB & 3) && JOY0_DOWN)
        drawSmallProxy(0, 184, andrewDavie);
    else
        drawSmallProxy(0, 184, (const char *)playerBigSprite);
#endif

    int colour = sline == menuLine ? (flashTime2 & 4) ? 0x0A : ((base2 << 2) & 0xF0) | 0x16 : 0x26;

    drawString(0, y + 8, dLine, colour);

    // Draw ICC menu PF background

    interleaveColour();
    setTitleMarqueeColours(41, 78);

    const unsigned char *logo0a = (const unsigned char *)__TITLE_SCREEN;
    unsigned char *pf1L = RAM + _BUF_MENU_PF1_LEFT;
    for (int i = 0; i < _ARENA_SCANLINES * 4; i += 3) {
        for (int icc = 0; icc < 3; icc++) {
            pf1L[icc] = 0; // logo0a[roller];
            if (++roller > 2)
                roller = 0;
        }
        pf1L += 3;
        logo0a += 3;
    }

    static const char *registered = ":";
    drawString(5, 45, registered, 0x2); //(R)
}

void initCopyrightScreen() {

    unsigned char *p = (unsigned char *)__COPYRIGHT_START;
    unsigned char *r = RAM + _BUF_MENU_GRP0A;

    int rStart = (_ARENA_SCANLINES - __COPYRIGHT_ROWS) / 2;
    int rEnd = (_ARENA_SCANLINES + __COPYRIGHT_ROWS) / 2;

    for (int col = 0; col < 6; col++) {
        for (int row = rStart; row < rEnd; row++) {
            RAM[_BUF_MENU_COLUP0 + row - 1] = convertColour(row < 52 ? 0x2C : 0x46);
            r[row] = *p++;
        }
        r += _ARENA_SCANLINES;
    }
}

void chooseColourScheme() {
    unsigned char *c = (unsigned char *)__COLOUR_POOL;
    //    do {
    currentPalette = rangeRandom(__PALETTE_COUNT);
    // } while (((int)caveList[cave]) & CAVE_REQUIRES_AMOEBA_PALETTE &&
    //     (!(c[currentPalette << 2] & __COMPATIBLE_AMOEBA_PALETTE)));
}

void initKernel(int kernel) {

    KERNEL = kernel;
    setJumpVectors(_MENU_KERNEL, _EXIT_MENU_KERNEL);

    killRepeatingAudio();
    gameSchedule = SCHEDULE_START;

    ARENA_COLOUR = 0;

    if (rageQuit) {
        rageQuit = false;
        SAY(__WORD_RAGEQUIT);
        FLASH(0x48, 8);
    }

    P0_X = 80;
    P1_X = 88;

    bufferedSWCHA = 0xFF;
    waitRelease = true;
    sound_max_volume = VOLUME_MAX;

    for (int but = 0; but < BUT; but++) {
        butterflyX[but] = 0x600;
        butterflyY[but] = 0x2200;
        bBase[but] = getRandom32() & 2;
    }

    // clearMenuPlayfield();
    // clearMenuSprites();
    clearBuffer((int *)(RAM + _BUF_MENU_PF1_LEFT), 10 * _ARENA_SCANLINES / 4);
    //    setCopyrightScreenPalette();

    switch (kernel) {

    case KERNEL_COPYRIGHT:

        frame = 0; // for auto-detect

        mustWatchDelay = MUSTWATCH_COPYRIGHT;
        SAY(__WORD_BOULDERDASH);
        break;

    case KERNEL_MENU:

        menuLine = 0;
        base2 = 0;
        pushCount = 0;

        // initDemoMode(false);

        chooseColourScheme();

        mustWatchDelay = MUSTWATCH_MENU;
        break;

    case KERNEL_STATS: {

        mustWatchDelay = MUSTWATCH_STATS;
        caveUnpackComplete = false;
        thumbnailSpeed = -10;

        chooseColourScheme();

#if __FADE
        fade = 0x10000;
#endif

        // initCharAnimations();

        decodeCave(cave);
        loadPalette();

        // static const char caveWord[] = "CAVE";
        // drawString(1, 35, caveWord, bgPalette[0] + 0x80);
        // doubleSize(2, 56, '1' + level);
        // doubleSize(0, 56, 'A' + cave);

        break;
    }

    case KERNEL_GAME:

        //        initNewGame();

#if __ENABLE_DEMO
        sound_max_volume = demoMode ? VOLUME_NONPLAYING : VOLUME_PLAYING;
#else
        sound_max_volume = VOLUME_PLAYING;
#endif

        break;
    }
}

void MenuOverscan() {

    initMenuDatastreams();

#if __ENABLE_ATARIVOX
    processSpeech();
#endif

    playAudio();

    clearBuffer((int *)(RAM + _BUF_MENU_PF1_LEFT), /*4 * */ _ARENA_SCANLINES /*/ 4*/);

    base2++;

    switch (KERNEL) {

    case KERNEL_COPYRIGHT:

        detectConsoleType();
        initCopyrightScreen();

        // if (enableParallax == 1) { // illegal, so a first-use/reboot
        //     enableParallax = RIGHT_DIFFICULTY_A;
        //     enableICC = LEFT_DIFFICULTY_A;
        // }

        // tmp        if (!--mustWatchDelay)
        initKernel(KERNEL_MENU);
        break;

    case KERNEL_MENU:
        handleMenuScreen();
        break;

    case KERNEL_STATS: // overscan

        interleaveColour();
        processCharAnimations();
        // tmp        initIconPalette();
        // tmp        drawIconScreen(0, 12);

        if (!caveUnpackComplete) {

            if (sound_volume > 5)
                sound_volume -= 6;

            if (++thumbnailSpeed > 1) {
                thumbnailSpeed = 0;
                caveUnpackComplete = !decodeExplicitData(true);
            }
        }

        break;

    default:
        break;
    }

#if ENABLE_SNOW
    doSnow();
#endif
}

void setStatusBackgroundPalette() {

    unsigned char *pal = (unsigned char *)(__COLOUR_POOL);
    pal += (currentPalette & 15) << 2;

    unsigned char *p = RAM + _BUF_MENU_COLUPF;

    int baseRoller = roller + 1;

    for (int i = 0; i < _ARENA_SCANLINES; i++) {
        if (++baseRoller > 2)
            baseRoller -= 3;

        p[i] = convertColour(pal[baseRoller]);
    }
}

int setBounds(int value, int max) {
    if (value < 0)
        value = max;
    if (value > max)
        value = 0;
    return value;
}

void resetMode() {

    flashTime2 = 16;
    ADDAUDIO(SFX_DRIP);

    mustWatchDelay = MUSTWATCH_MENU;
    waitRelease = true;

    pushFrame = 0;
    pushCount = (rndX & 31) | 32;
}

void handleMenuVB() {

    // #if __ENABLE_DEMO
    // if (!--mustWatchDelay) {

    //     initDemoMode(true);
    //     initNewGame();
    //     initKernel(KERNEL_GAME);
    //     loadPalette();
    //     return;
    // }
    // #endif

    doFlash();

#if ENABLE_ANIMATING_MAN
    doPlayer();
#endif

    for (int i = 0; i < 6; i++)
        if (!RGB[i] || !rangeRandom(64))
            RGB[i] = (mm_tv_type == SECAM) ? (rangeRandom(7) + 1) << 1
                                           : LUMINANCE_TITLE | (getRandom32() << 4);

    int negJoy = (SWCHA >> 4) ^ 0xF;

    if (!waitRelease) {

        if (true) { // tmp !(INPT4 & 0x80)) {

            initNewGame();
            initKernel(KERNEL_STATS);
            return;
        }

        int dir = yInc[negJoy];

        if (dir)
            menuLine = setBounds(menuLine + dir, 2);

        else {

            dir = xInc[negJoy];
            if (dir) {

                switch (menuLine) {
                case 0:
                    do
                        cave = setBounds(cave + dir, caveCount - 1);
                    while (!(canPlay[level] & (1 << cave)));
                    break;

                case 1:
#if !__ENABLE_TRAINER
                    level = setBounds(level + dir, 4);
                    while (!(canPlay[level] & (1 << cave)))
                        cave--;
#endif
                    break;

                case OPTION_SYSTEM:
                    menuLineTVType = setBounds(menuLineTVType + dir, 3);
                    mm_tv_type = TV_TYPE = menuLineTVType;
                    break;
                }
            }
        }

        if (dir) {
            resetMode();
            ADDAUDIO(SFX_BLIP);
        }
    }

    else if (!negJoy && (INPT4 & 0x80))
        waitRelease = false;

    // if (menuLineTVType)
    //     TV_TYPE = mm_tv_type;

    // #if ENABLE_SNOW
    //     doSnow();
    // #endif
}

void MenuVerticalBlank() {

#if __ENABLE_ATARIVOX
    processSpeech();
#endif

    switch (KERNEL) {

    case KERNEL_STATS: // VBlank

        // tmp        setStatusBackgroundPalette();
        // tmp        drawIconScreen(12, 22);

        if (sound_volume && !caveUnpackComplete)
            sound_volume--;

        /*tmp
                if (!JOY0_FIRE)
                    waitRelease = false;

                else if (!waitRelease) {
                    */
        waitRelease = true;
        initKernel(KERNEL_GAME);
        // tmop        }

        handleSelectReset();
        break;

    case KERNEL_COPYRIGHT: // VBlank

        interleaveColour();
        setStatusBackgroundPalette();
        break;

    case KERNEL_MENU: // VBlank
        handleMenuVB();
        // setStatusBackgroundPalette();
        break;
    }

    // doButterflies(0x0000, 0x1600, 0x1A00, 0x3000);

    if (KERNEL == KERNEL_STATS) {
        // clear behind the thumbnail
        unsigned char *gfx = RAM + _BUF_MENU_PF2_RIGHT;
        for (int line = 100; line < 100 + decodingRow * 3; line++) {
            gfx[line] = 0;
            gfx[line + (_BUF_MENU_PF1_RIGHT - _BUF_MENU_PF2_RIGHT)] &= 0xF0;
        }
    }
}

void doubleSize(int x, int y, int letter) {

    int colour = convertColour(fgPalette[0] + 0x80); // & 0xF0) | 4);

    letter -= 'A';
    if (letter < 0)
        letter += 43;
    const unsigned char *gfx = charAtoZ + letter * LETTER_HEIGHT;

    unsigned char *col0 = RAM + _BUF_MENU_GRP0A + _ARENA_SCANLINES * x + y + _ARENA_SCANLINES;
    unsigned char *p = RAM + _BUF_MENU_COLUP0 + y - 1;

    int pattern = 0;

    for (int line = 0; line < LETTER_HEIGHT; line++) {

        for (int bit = 0b10000000; bit; bit >>= 1) {
            pattern <<= 2;
            if (gfx[line] & bit)
                pattern |= 0b11;
        }

        for (int stretch = 0; stretch < 3; stretch++) {
            *col0 = pattern >> 8;
            *(col0++ + _ARENA_SCANLINES) = pattern;
            *p++ = colour;
        }
    }
}

// EOF