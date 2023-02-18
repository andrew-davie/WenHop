#ifndef __DEMO_H
#define __DEMO_H

void getJoystick();

#if __ENABLE_DEMO
void initDemoMode(bool mode);
void checkDemoFinished();

extern bool demoMode;
#endif

#endif
