#ifndef __ROPE_H
#define __ROPE_H

#define PARTICLE_COUNT 24
#define ROPE_PARTICLE_COUNT 24
#define PARTICLE_SPIRAL_ANGULAR_SPEED 6

enum ParticleType {

    PT_ONE = 1,
    PT_TWO,
    PT_SPIRAL,
    PT_SPIRAL2,
    PT_BUBBLE,
    PT_STATIC,
};

struct Particle {

    unsigned char type;
    unsigned char age;
    unsigned char speed;
    int x;
    int y;
    unsigned char direction;
    unsigned short distance;
};

extern struct Particle particle[PARTICLE_COUNT];

void drawParticles();
// void drawRope();

#endif
// EOF
