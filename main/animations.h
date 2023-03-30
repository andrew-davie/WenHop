#ifndef __ANIMATIONS_H
#define __ANIMATIONS_H

#include "attribute.h"

extern const char *const AnimateBase[TYPE_MAX];

#define ANIM_HALT 0
#define ANIM_LOOP 255
#define ANIM_RNDSPEED 254
#define ANIM_ZAP 253

#define DRIP_SPLASH 12
#define DRIP_FALL 10


extern const char *Animate[TYPE_MAX];
extern char AnimCount[TYPE_MAX];

extern void initCharAnimations();
extern void startCharAnimation(int type, const char *idx);
extern void processCharAnimations();

extern const char AnimBrokenBoulder[];

#endif
