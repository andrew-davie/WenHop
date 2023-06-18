#include <limits.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#include "defines_from_dasm_for_c.h"
#define CDFJ_NO_MUSIC #must be before defines_cdfjplus.h
#define CDFJ_NO_PITCH_TABLE #must be before defines_cdfjplus.h
#define CDFJ_NO_MEMCOPY_INT #must be before defines_cdfjplus.h
#include "defines.h"
#include "defines_cdfjplus.h"

#pragma GCC diagnostic pop

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
#include "player.h"
#include "random.h"
#include "score.h"
#include "sound.h"

#define setPointer(fetcher, offset) _QPTR[fetcher] = (offset) << 20;

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
static int frame = 0;
static int base2;
static int pushCount;
static unsigned int menuLine;
static int caveUnpackComplete;
int detectedPeriod;

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

        detectedPeriod = T1TC;

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

    return; // tmp
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

#if ENABLE_ANIMATING_MAN
const unsigned short toolIcon[][127] = {

    {
        126,

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
    },
    // {
    //     126,

    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000111110000,
    //     0b0000000111100000,
    //     0b0000000111100000,
    //     0b0000000111100000,
    //     0b0000001111111000,
    //     0b0000001111110000,
    //     0b0000001111110000,
    //     0b0000001111110000,
    //     0b0000011111111100,
    //     0b0000011111111000,
    //     0b0000011000111000,
    //     0b0000011000111000,
    //     0b0000011111111100,
    //     0b0000011000011000,
    //     0b0000010111101000,
    //     0b0000010000001000,
    //     0b0000111111111110,
    //     0b0000110000011100,
    //     0b0000111111101100,
    //     0b0000110000001100,
    //     0b0000111111111110,
    //     0b0000110000011100,
    //     0b0000101100000100,
    //     0b0000100000000100,
    //     0b0000111111111110,
    //     0b0000110011111100,
    //     0b0000101100000100,
    //     0b0000100000000100,
    //     0b0001111111111111,
    //     0b0001110011111110,
    //     0b0001100100000110,
    //     0b0001100000000110,
    //     0b0001111111111111,
    //     0b0001110000011110,
    //     0b0001001100000010,
    //     0b0001000000000010,
    //     0b0001111111111111,
    //     0b0001110000111110,
    //     0b0001000111000010,
    //     0b0001000011000010,
    //     0b0001111111111111,
    //     0b0001110000111110,
    //     0b0001001111000010,
    //     0b0001000011000010,
    //     0b0001111111111111,
    //     0b0001100000111110,
    //     0b0001011111000010,
    //     0b0001011111000010,
    //     0b0001111111111111,
    //     0b0001100000111110,
    //     0b0001010011000010,
    //     0b0001011111000010,
    //     0b0001111111111111,
    //     0b0001100000111110,
    //     0b0001010011000010,
    //     0b0001011111000010,
    //     0b0001111111111111,
    //     0b0001100000111110,
    //     0b0001011111000010,
    //     0b0001011111000010,
    //     0b0001111111111111,
    //     0b0001110000111110,
    //     0b0001000111000010,
    //     0b0001000011000010,
    //     0b0001111111111111,
    //     0b0001110000111110,
    //     0b0001001111000010,
    //     0b0001000011000010,
    //     0b0001111111111111,
    //     0b0001110000111110,
    //     0b0001000111000010,
    //     0b0001000011000010,
    //     0b0001111111111111,
    //     0b0001110000111110,
    //     0b0001101111000110,
    //     0b0001100011000110,
    //     0b0000111111111110,
    //     0b0000111100111100,
    //     0b0000100011000100,
    //     0b0000100011000100,
    //     0b0000111111111110,
    //     0b0000111100111100,
    //     0b0000100011000100,
    //     0b0000100011001100,
    //     0b0000111111111110,
    //     0b0000111100111100,
    //     0b0000110011001100,
    //     0b0000110011001100,
    //     0b0000011111111100,
    //     0b0000011100111000,
    //     0b0000010011001000,
    //     0b0000011011011000,
    //     0b0000011111111100,
    //     0b0000011100111000,
    //     0b0000011011011000,
    //     0b0000011111111000,
    //     0b0000001111111000,
    //     0b0000001100110000,
    //     0b0000001111110000,
    //     0b0000001111110000,
    //     0b0000000111110000,
    //     0b0000000100100000,
    //     0b0000000111100000,
    //     0b0000000111100000,
    //     0b0000000011000000,
    //     0b0000000000000000,ccd
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    //     0b0000000000000000,
    // },
};
#endif

#if ENABLE_TITLE_PULSE
#define LUMINANCE_TITLE 6
#else
#define LUMINANCE_TITLE 0x6
#endif

// #define LUMINANCE 2

char RGB[6];

const unsigned char titleScreenImagePalette[] = {
    0xB6, 0xF8, 0x46 // + LUMINANCE, 0x24 + LUMINANCE, 0x24 + LUMINANCE, // NTSC
};

void doDrawBitmap(const unsigned short *shape, int y) {

    unsigned char *pf1R = RAM + _BUF_PF1_RIGHT;
    unsigned char *pf2R = RAM + _BUF_PF2_RIGHT;

    int size = shape[0];

    // const unsigned short *bf = shape + 1;

    int baseRoll = roller;

    union g {
        int bGraphic;
        unsigned char g[4];
    } gfx;

    for (int i = 1; i < size + 1; i += 4) {

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

    doDrawBitmap(toolIcon[pushFrame], 120 + jiggle);
}
#endif

// clang-format off

const unsigned char charAtoZ[] = {

    // XX__XX_X,
    // XX__XX_X,
    // XXX_XX_X,
    // XXXXXX_X,
    // XXXXXX_X,
    // XXXXXX_X,
    // XXXXXX_X,
    // XX_XXX_X,
    // XX__XX_X,
    // XX__XX_X,

    // XXXX_XXX,
    // XXXX_XXX,
    // XX___XXX,
    // XXX__XXX,
    // XXX__XXX,
    // XX___XXX,
    // XX___XXX,
    // XXXX_XXX,
    // XXXX_XXX,
    // XXXX_XXX,

    // XX__XXXX,
    // XXX_XXXX,
    // __XX__XX,
    // __XX__XX,
    // __XX__XX,
    // XXXX__XX,
    // XXX___XX,
    // ______XX,
    // ______XX,
    // ______XX,

    // XXX_XXX_,
    // XXX_XXX_,
    // X___XXX_,
    // X___XXX_,
    // X___XXX_,
    // X___XXX_,
    // X___XXX_,
    // X___XXXX,
    // X____XXX,
    // X_____XX,

    // _XX_XX__,
    // _XX_XX__,
    // _XX_XXX_,
    // _XX_XXXX,
    // _XX_XXXX,
    // _XX_XXXX,
    // _XX_XXXX,
    // XXX_XX_X,
    // XXX_XX__,
    // XX__XX__,

    // XX_XXXXX,
    // XX_XXXXX,
    // XX_XXX__,
    // XX_XXXX_,
    // XX_XXXX_,
    // XX_XXX__,
    // XX_XXX__,
    // XX_XXXXX,
    // XX_XXXXX,
    // XX_XXXXX,


    // XXXXXXX_,
    // XXXXXXX_,
    // __XXX___,
    // __XXX___,
    // __XXX___,
    // __XXX___,
    // __XXX___,
    // __XXX___,
    // __XXX___,
    // __XXX___,

    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXXXXXX_,
    // _XXXXXX_,
    // __XXXX__,

    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // _XXXXX__,
    // _XXXXX__,
    // _XXXXX__,
    // __XXX___,
    // __XXX___,

    // XXXXXX_X,
    // XXXXXX_X,
    // XXX____X,
    // XXXXX__X,
    // XXXXX__X,
    // XXX____X,
    // XXX____X,
    // XXXXXX_X,
    // XXXXXX_X,
    // XXXXXX_X,

    // X___XX_X,
    // XX__XX_X,
    // XXX_XX_X,
    // XXXXXX_X,
    // XXXXXX_X,
    // XXXXXX_X,
    // X_XXXX_X,
    // XX_XXX_X,
    // XX__XX_X,
    // XX__XX__,

    // X__XX___,
    // X__XX__X,
    // X__XX_XX,
    // X__XX_XX,
    // X__XX_XX,
    // X__XX__X,
    // X__XX___,
    // XXXXX_XX,
    // XXXXX_XX,
    // XXXX__XX,

    // XXXX____,
    // XXXX____,
    // X_______,
    // X_______,
    // XXX_____,
    // XXXX____,
    // _XXX____,
    // XXXX____,
    // XXXX____,
    // XXX_____,

    // XX___XX_,
    // XXX_XXX_,
    // XXXXXXX_,
    // XXXXXXX_,
    // XX_X_XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,
    // XXX__XX_,

    // XXXXXX_X,
    // XXXXXX_X,
    // XXX____X,
    // XXXXX__X,
    // XXXXX__X,
    // XXX____X,
    // XXX____X,
    // XXXXXX_X,
    // XXXXXX_X,
    // XXXXXX_X,

    // XXX_____,
    // XXXX___X,
    // X__XX_XX,
    // X__XX_XX,
    // XXXXX_XX,
    // XXXX__XX,
    // XXX___XX,
    // XXXX__XX,
    // X_XXX__X,
    // X__XX___,

    // XXX_XX__,
    // XXX_XX__,
    // X___XX__,
    // ____XX__,
    // ____XX__,
    // ____XX__,
    // X___XX__,
    // XXX_XXXX,
    // XXX__XXX,
    // XXX___XX,

    // XX_XXXX_,
    // XX_XXXXX,
    // XX_XX__X,
    // XX_XX__X,
    // XX_XXXXX,
    // XX_XXXXX,
    // XX_XXXX_,
    // XX_XXXXX,
    // XX_XX_XX,
    // X__XX__X,

    // __XX__XX,
    // __XX__XX,
    // X_XX__XX,
    // X_XX__XX,
    // X_XXXXXX,
    // __XXXXX_,
    // ___XXX__,
    // ___XXX__,
    // X__XXX__,
    // X__XXX__,



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

    ___XX___,
    ___XX___,
    __XX_X__,
    __XXXX__,
    __XXXX__,
    __XXXX__,
    ___XX___,
    __XXXX__,
    __XX_X__,
    __X__X__,

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
    ________, XXXXXX__, _X___XXX, X___X_XX, XXXXXXXX, XX_X___X,
    ________, XXXX_XX_, XX__XX__, XX_XXXX_, _XXXX_XX, XX_XX_XX,
    ________, __X___X_, X____XXX, _XXX__XX, X__X__X_, ___XXXXX,
    ________, __X___XX, X______X, X_X_____, XX_X__XX, X__X_X_X,
    ________, __X____X, ____XXXX, X_X__XXX, XX_X__X_, ___X___X,
    ________, __X____X, ____XXXX, __X__XXX, X__X__XX, XX_X___X,
};

const char wordStartAt[] = {
    ________, ________, ___XXX__, X____XX_, _X__X_XX, XX_XXXXX,
    ________, ________, ___X__X_, X___XXXX, _XX_X_X_, ___XXXXX,
    ________, ________, ___X__X_, X___X__X, _XX_X_XX, X____X__,
    ________, ________, ___XXX__, X___XXXX, _X_XX_X_, _____X__,
    ________, ________, ___X____, X___X__X, _X_XX_XX, XX___X__,
    ________, ________, ___X____, XXX_X__X, _X__X_XX, XX___X__,
};

const char wordDifficulty[] = {

    ________, _____XXX, ___XXX__, _XX__X__, X__XX__X, X____XX_,
    ________, _____X__, XX_XX_X_, XXXX_X__, X_XXXX_X, _X__X__X,
    ________, _____XXX, ___X__X_, X__X_X__, X_X__X_X, __X_X__X,
    ________, _____X__, XX_XXX__, XXXX_X__, X_XXXX_X, __X_X__X,
    ________, _____XXX, XX_X_X__, X__X_XXX, __X__X_X, XXX_XXXX,
    ________, _____XXX, X__X__X_, X__X__X_, __X__X_X, XX___XX_,
};


const char wordProto2[] = {
    XXX___XX, __XXX__X, XX______, XX__XXXX, ____XXX_, _X______,
    __XX_X__, X___XX__, _XX____X, __X_X___, ______XX, _X__X___,
    __X__X__, X___X___, XX_____X, __X_XXX_, ______X_, _X__X___,
    _X___X__, X__X____, _XX____X, __X____X, _____X__, _XXXX___,
    XXXX_XXX, X_XXXX_X, XXX_XX_X, XXX_XXXX, _XX_XXXX, ___XX___,
    XXXX__XX, __XXXX_X, XX__XX__, XX__XXX_, _XX_XXXX, ___XX___,
};


const char wordProto[] = {
    XXX__XXX, ___XX__X, XXXX__XX, ____X__X, ________, __X_____,
    XXXX_XX_, X_X__X_X, XXXX_X__, X___XX_X, ________, _XX_____,
    X__X_X__, X_X__X__, _X___X__, X___XX_X, __XX____, _XX_____,
    XXX__XXX, __X__X__, _X___X__, X___X_XX, _X__X___, __X_____,
    X____X_X, __XXXX__, _X___XXX, X___X_XX, _XXXX_XX, _XXX____,
    X____X__, X__XX___, _X____XX, ____X__X, __XX__XX, _XXX____,
};

// clang-format on

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

    while (*text && x < 6)
        drawCharacter(x++, y, *text++);

    for (int i = 0; i < LETTER_HEIGHT; i++)
        RAM[_BUF_MENU_COLUP0 + i + y - 1] = convertColour(colour);
}

void drawSmallString(int y, const char *smallText) {
    static const unsigned char smallColour[] = {0x98, 0xB8, 0xB8, 0x0A};
    int colour = smallColour[mm_tv_type];

    for (int line = 0; line < 6; line++) {
        RAM[_BUF_MENU_COLUP0 + y + line - 1] = colour;
        for (int i = 0; i < 6; i++)
            RAM[_BUF_MENU_GRP0A + _ARENA_SCANLINES * i + y + line] = *smallText++;
    }
}

int flashTime2 = 0;

// clang-format off

const char showCave[][6] = {
    {";;MARS"}, {"URANUS"}, {"SATURN"}, {"FOUR  "}, {"FIVE  "},
    {"SIX   "}, {"SEVEN "}, {"EIGHT "}, {"NINE  "}, {"X     "},
};

const char TV[][6] = {

    {";;NTSC"},
    {";;;PAL"},
    {";PAL60"},
    {";SECAM"},
};

const char Level[][6] = {

    {";;WIMP"}, {";;BOZO"}, {";;HERO"}, {"TRAGIC"}, {"MANIAC"},
};

// clang-format on

const char *smallWord[] = {
    wordStartAt,
    wordDifficulty,
    wordTvType0,
};

void SchedulerMenu() {}

#if ENABLE_TITLE_PULSE
extern const unsigned char sinoid[];
#endif

void setTitleMarqueeColours() { // int a, int b) {

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

        //         int offset = 3; // i < a ? 0 : 3;

        //         if (i < b) {
        //             p[i] = RGB[baseRoller + offset];

        // #if ENABLE_TITLE_PULSE
        //             if (mm_tv_type != SECAM) {
        //                 if (i < a)
        //                     p[i] |= flash;
        //                 else
        //                     p[i] |= flash2;
        //             }
        // #endif
        //         } else
        p[i] = convertColour(titleScreenImagePalette[baseRoller]);
    }
}

void handleMenuScreen() {
    return; // tmp

    // if (!(SWCHA & 0xF0)) // UDLR at same time!
    //     drawString(0, 182, "ZPH001", 0);
    // else
    //     drawString(0, 182, "      ", 0);

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
        //        showCave[5] = 'A' + cave;
        dLine = showCave[cave];
        break;

    case 1:
        dLine = Level[level];
        break;

    case OPTION_SYSTEM:
        dLine = TV[menuLineTVType];
        break;
    }

    drawSmallString(y, smallWord[sline]);

    int colour = sline == menuLine ? (flashTime2 & 4) ? 0x0A : ((base2 << 2) & 0xF0) | 0x16 : 0x26;

    drawString(0, y + 8, dLine, colour);

    static int protoTime = 0;
    if (++protoTime < 200) {

        drawSmallString(180, wordProto);
        drawSmallString(188, wordProto2);

        for (int line = 179; line < 194; line++) {
            RAM[_BUF_MENU_COLUP0 + line] = 0x8;
        }
    }

    else {

        for (int line = 179; line < 194; line++)
            for (int i = 0; i < 6; i++)
                RAM[_BUF_MENU_GRP0A + _ARENA_SCANLINES * i + line] = 0;
    }

    // Draw ICC menu PF background

    interleaveColour();
    setTitleMarqueeColours(); // 41, 78);

    const unsigned char *logo0a = (const unsigned char *)__TITLE_SCREEN;
    unsigned char *pf1L = RAM + _BUF_MENU_PF1_LEFT;
    for (int i = 0; i < _ARENA_SCANLINES * 4; i += 3) {
        for (int icc = 0; icc < 3; icc++) {
            pf1L[icc] = logo0a[roller];
            if (++roller > 2)
                roller = 0;
        }
        pf1L += 3;
        logo0a += 3;
    }

    // static const char *registered = ":";
    //  static int landing = 62;
    //  drawString(5, landing, ";", 0x22); //(R)
    //  if (--landing < 0)
    //      landing = 62;
    drawString(5, 62, ":", 0x22); //(R)
}

// void initCopyrightScreen() {

//     unsigned char *p = (unsigned char *)__COPYRIGHT_START;
//     unsigned char *r = RAM + _BUF_MENU_GRP0A;

//     int rStart = (_ARENA_SCANLINES - __COPYRIGHT_ROWS) / 2;
//     int rEnd = (_ARENA_SCANLINES + __COPYRIGHT_ROWS) / 2;

//     for (int col = 0; col < 6; col++) {
//         for (int row = rStart; row < rEnd; row++) {
//             RAM[_BUF_MENU_COLUP0 + row - 1] = convertColour(row < 52 ? 0x2C : 0x46);
//             r[row] = *p++;
//         }
//         r += _ARENA_SCANLINES;
//     }
// }

void chooseColourScheme() {
    //    unsigned char *c = (unsigned char *)__COLOUR_POOL;
    //    do {
    currentPalette = rangeRandom(__PALETTE_COUNT);
    // } while (((int)caveList[cave]) & CAVE_REQUIRES_COMPATIBLE_PALETTE &&
    //     (!(c[currentPalette << 2] & __COMPATIBLE_PALETTE)));
}

void initKernel(int kernel) {

    KERNEL = kernel;
    setJumpVectors(_MENU_KERNEL, _EXIT_MENU_KERNEL);

    // tmp    killRepeatingAudio();
    gameSchedule = SCHEDULE_START;

    ARENA_COLOUR = 0;

    // tmp...
    //  if (rageQuit) {
    //      rageQuit = false;
    //      SAY(__WORD_RAGEQUIT);
    //      FLASH(0x48, 8);
    //  }

    P0_X = 80;
    P1_X = 88;

    bufferedSWCHA = 0xFF;
    waitRelease = true;
    sound_max_volume = VOLUME_MAX;

    // clearMenuPlayfield();
    // clearMenuSprites();
    // tmp    clearBuffer((int *)(RAM + _BUF_MENU_PF1_LEFT), 10 * _ARENA_SCANLINES / 4);
    //     setCopyrightScreenPalette();

    switch (kernel) {

    case KERNEL_COPYRIGHT:

        frame = 0; // for auto-detect

        mustWatchDelay = MUSTWATCH_COPYRIGHT;
        SAY(__WORD_ATT_ROCKDASH);
        break;

    case KERNEL_MENU:

        menuLine = 0;
        base2 = 0;
        pushCount = 0;

        // initDemoMode(false);

        // tmp        chooseColourScheme();

        mustWatchDelay = MUSTWATCH_MENU;
        break;

    case KERNEL_STATS: {

        break; // tmp
        mustWatchDelay = MUSTWATCH_STATS;
        caveUnpackComplete = false;
        thumbnailSpeed = -10;

        chooseColourScheme();

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
    return; // tmp

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
        // initCopyrightScreen();

        // if (enableParallax == 1) { // illegal, so a first-use/reboot
        //     enableParallax = RIGHT_DIFFICULTY_A;
        //     enableICC = LEFT_DIFFICULTY_A;
        // }

        if (!--mustWatchDelay)
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

const signed char xInc[] = {

    // RLDU
    0,  // 0000
    0,  // 0001
    0,  // 0010
    0,  // 0011
    -1, // 0100
    -1, // 0101
    -1, // 0110
    0,  // 0111
    1,  // 1000
    1,  // 1001
    1,  // 1010
    0,  // 1011
    0,  // 1100
    0,  // 1101
    0,  // 1110
    0,  // 1111
};

const signed char yInc[] = {

    // RLDU
    0,  // 0000
    -1, // 0001
    1,  // 0010
    0,  // 0011
    0,  // 0100
    -1, // 0101
    1,  // 0110
    0,  // 0111
    0,  // 1000
    -1, // 1001
    1,  // 1010
    0,  // 1011
    0,  // 1100
    0,  // 1101
    0,  // 1110
    0,  // 1111
};

void handleMenuVB() {
    return; // tmp

    // #if __ENABLE_DEMO
    // if (!--mustWatchDelay) {

    //     initDemoMode(true);
    //     initNewGame();
    //     initKernel(KERNEL_GAME);
    //     loadPalette();
    //     return;
    // }
    // #endif

    // tmp    doFlash();

#if ENABLE_ANIMATING_MAN
// tmp    doPlayer();
#endif

    // tmp...
    //  for (int i = 0; i < 6; i++)
    //      if (!RGB[i] || !rangeRandom(64))
    //          RGB[i] = (mm_tv_type == SECAM) ? (rangeRandom(7) + 1) << 1
    //                                         : LUMINANCE_TITLE | (getRandom32() << 4);

    int negJoy = (SWCHA >> 4) ^ 0xF;

    if (!waitRelease) {

        if (!(INPT4 & 0x80)) {

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

        // tmp...
        //  if (dir) {
        //      resetMode();
        //      ADDAUDIO(SFX_BLIP);
        //  }
    }

    else if (!negJoy && (INPT4 & 0x80))
        waitRelease = false;

    if (menuLineTVType)
        TV_TYPE = mm_tv_type;
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
        // tmp        initKernel(KERNEL_GAME);
        //  tmop        }

        // tmp        handleSelectReset();
        break;

        // case KERNEL_COPYRIGHT: // VBlank

        //     interleaveColour();
        //     setStatusBackgroundPalette();
        //     break;

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