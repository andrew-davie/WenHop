#ifndef __RANDOM_H
#define __RANDOM_H

extern unsigned int rndX;
extern unsigned int prng_a, prng_b;
extern unsigned int cave_random_a, cave_random_b;

void initRandom();
unsigned int getRandom32();
unsigned int getCaveRandom32();
unsigned int rangeRandom(int range);

#endif
//EOF