#include "random.h"

unsigned int prng_b;
unsigned int prng_a;

unsigned int cave_random_a, cave_random_b;

unsigned int rndX;

void initRandom() {

    prng_a = *(unsigned int *)(0x40001FB4);
    prng_b = prng_a ^ 0xBABEACED;

    cave_random_a = prng_a;
    cave_random_b = prng_b;
}

unsigned int getRandom32() {
    prng_b = 36969 * (prng_b & 65535) + (prng_b >> 16);
    prng_a = 18000 * (prng_a & 65535) + (prng_a >> 16);
    return (prng_b << 16) + prng_a;
}

unsigned int getCaveRandom32() {
    cave_random_b = 36969 * (cave_random_b & 65535) + (cave_random_b >> 16);
    cave_random_a = 18000 * (cave_random_a & 65535) + (cave_random_a >> 16);
    return (cave_random_b << 16) + cave_random_a;
}

unsigned int rangeRandom(int range) {
    return ((getRandom32() >> 16) * range) >> 16;
}

// EOF