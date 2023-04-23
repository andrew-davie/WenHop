#ifndef __SCROLL_H
#define __SCROLL_H

extern int scrollX;
extern int scrollY;

void Scroll();
void resetTracking();
int isScrolling();

#define SCROLLSPEED_MAXIMUM_X (256)
#define SCROLL_MAXIMUM_X ((32 << 16))
#define SCROLLSPEED_MAXIMUM_Y (SCROLLSPEED_MAXIMUM_X * 8)
#define SCROLL_MINIMUM 0

#define SCROLL_TRIGGEREDGE_HORIZONTAL 2
#define SCROLL_TRIGGEREDGE_VERTICAL 10

#endif
// EOF
