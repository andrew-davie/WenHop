#ifndef __MENU_H
#define __MENU_H

#define MUSTWATCH_STATS 0x200

#if ENABLE_DEBUG
#define MUSTWATCH_COPYRIGHT 0x100
#define MUSTWATCH_MENU 0x800
#else
#define MUSTWATCH_COPYRIGHT 0x180
#define MUSTWATCH_MENU 0x400
#endif

void MenuOverscan();
void MenuVerticalBlank();
void SchedulerMenu();
void initKernel(int krn);
void clearBuffer(int *buffer, int size);
void initMenuDatastreams();

void doDrawBitmap(const unsigned short *shape, int y);

extern int menuLineTVType;
extern int mhz;

extern const unsigned char *menuCharSet[];

#define DEBUG_TIMER 0

#if DEBUG_TIMER
extern unsigned int debugDelay;
#endif

#endif