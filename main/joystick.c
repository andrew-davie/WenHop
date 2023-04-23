#include "defines_cdfj.h"

#include "colour.h"
#include "defines.h"
#include "joystick.h"
#include "main.h"
#include "menu.h"
#include "random.h"
#include "swipeCircle.h"

#if __ENABLE_DEMO
bool demoMode = true;
static int demoJoy;

#if CIRCLE
static bool demoCircleTriggered;
#endif

const unsigned char *joyRecording = (const unsigned char *)__DEMO_JOYSTICK;

static int demoFrameBase;
#endif

// void initDemoMode(bool mode) {

//     cave = 0;
//     level = 0;

//     #if __ENABLE_DEMO
//     demoMode = mode;
//     demoJoy = 0;
//     demoFrameBase = 0;
//     #endif

//     #if CIRCLE
//     #if __ENABLE_DEMO
//     demoCircleTriggered = false;
//     #endif
//     #endif
// }

void getJoystick() {

#if __ENABLE_DEMO
    if (!demoMode) {
#endif

#if COLSELECT
        if (!LEFT_DIFFICULTY_A)
#endif
        {
            swcha = SWCHA;
            inpt4 = INPT4;
        }

        // if (swcha == 0xFF && !(getRandom32() & 0x3))
        //     swcha = getRandom32() & 0xF0;
#if __ENABLE_DEMO
    }
#endif

#if __ENABLE_DEMO
    else {

        static const unsigned char rework[] = {

            (255 - 0x80),
            (255 - 0x40),
            (255 - 0x10),
            (255 - 0x20),
            255,
        };

        if (!joyRecording[demoJoy] || SWCHA != 0xFF || !(INPT4 & 0x80)
#if CIRCLE
            || demoCircleTriggered
#endif
        ) {

            swcha = 0xFF;

#if CIRCLE
            if (!demoCircleTriggered) {
                demoCircleTriggered = true;
                initSwipeCircle(CIRCLE_ZOOM_ZERO - 1);
            }
#endif

            caveCompleted = true;
        } else {

            if (uncoverTimer < 0)
                while (joyRecording[demoJoy] && gameFrame > demoFrameBase + (joyRecording[demoJoy] & 0x0F))
                    demoFrameBase += joyRecording[demoJoy++] & 0x0F;

            swcha = rework[(joyRecording[demoJoy] >> 4) & 7];
            inpt4 = joyRecording[demoJoy] ^ 0x80;
        }
    }
#endif
}

#if __ENABLE_DEMO
void checkDemoFinished() {

#if CIRCLE
    if (demoCircleTriggered && checkSwipeFinished())
#endif
        initKernel(KERNEL_MENU);
}
#endif
// EOF
