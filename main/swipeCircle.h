#ifndef __SWIPECIRCLE_H
#define __SWIPECIRCLE_H

#define CIRCLE_RESOLUTION 4
#define CIRCLE_ZOOM_ZERO (1 << CIRCLE_RESOLUTION)

void swipeCircle();
bool checkSwipeFinished();
void initSwipeCircle(int zoom);
// bool checkInCircle(int x, int y);

#endif
//EOF
