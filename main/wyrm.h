#ifndef __WYRM_H
#define __WYRM_H

#define WYRM_POP 8
#define WYRM_MAX 4


struct wyrmDetails {
    signed char x[WYRM_MAX];
    signed char y[WYRM_MAX];
    signed char head;
    unsigned char dir;
    unsigned char length;
};

extern struct wyrmDetails wyrms[WYRM_POP];

void initWyrms();
void newWyrm(int x, int y);
void processWyrms();

#endif