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

#define DETECT_FRAME_COUNT 10

static int frame;

void initAutoDetect() { frame = 0; }

int detectConsoleType() {

    switch (frame) {

    case 0:

        mm_tv_type = TV_TYPE = -1;

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

        TV_TYPE = mm_tv_type;
        break;
    }

    default:
        break;
    }

    frame++;

    return TV_TYPE;
}
