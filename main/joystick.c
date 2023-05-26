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

#include "joystick.h"

#include "colour.h"
#include "menu.h"
#include "random.h"
#include "swipeCircle.h"

void getJoystick() {
    swcha = SWCHA;
    inpt4 = INPT4;
}

// EOF
