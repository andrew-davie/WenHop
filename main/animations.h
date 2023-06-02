#ifndef __ANIMATIONS_H
#define __ANIMATIONS_H

#define ANIM_HALT 0
#define ANIM_LOOP 255
#define ANIM_WATER 254
// #define ANIM_RNDSPEED 254

extern const char *const AnimateBase[];
extern const char *Animate[];
extern char AnimCount[];

extern void initCharAnimations();
extern void startCharAnimation(int type, const char *idx);
extern void processCharAnimations();

#endif
