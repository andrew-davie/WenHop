#include "defines_cdfj.h"
#include "main.h"
#include <stdbool.h>
// #include "amoeba.h"
#include "colour.h"
#include "joystick.h"
#include "random.h"
#include "sound.h"

void loadTrack(int t, const unsigned char *tune);
void processTracks();

static const unsigned char trackSimple[];
// static const unsigned char trackSimple2[];

int sound_volume = 128;
int sound_max_volume = 1024;
int volume[2];

struct Audio Track[MAX_TRACKS];

const unsigned char sampleTick[] = {
    0xF,
    0x1F,
    1,
    2,
    0,
    0,
    0,
    6,
    0xF,
    0x1F,
    1,
    1,
    0,
    0,
    0,
    40,
    CMD_LOOP,
};

const unsigned char sampleDrip[] = {
    12,
    12,
    4,
    1,
    CMD_STOP,
};

const unsigned char sampleUncover[] = {
    12,
    6,
    3,
    1,
    12,
    4,
    3,
    2,
    0,
    0,
    0,
    1,
    CMD_LOOP,
};

const unsigned char sampleDrip2[] = {
    12,
    6,
    4,
    1,
    12,
    4,
    4,
    1,
    CMD_STOP,
};

const unsigned char sampleMagic[] = {
    0xC,
    0x8,
    3,
    2,
    CMD_LOOP,
};

const unsigned char sampleMagic2[] = {
    0x5,
    0x8,
    5,
    15,
    CMD_STOP,
};

const unsigned char samplePick[] = {
    9,
    12,
    8,
    1,
    9,
    20,
    15,
    1,
    9,
    31,
    12,
    1,
    // 8, 18, 9, 1,
    // 8, 18, 6, 1,
    CMD_STOP,
};

const unsigned char sampleRock[] = {
    8,
    18,
    5,
    4,
    8,
    18,
    5,
    3,
    8,
    18,
    4,
    2,
    8,
    18,
    3,
    1,
    CMD_STOP,
};

const unsigned char sampleRock2[] = {
    8,
    18,
    4,
    4,
    8,
    18,
    3,
    3,
    8,
    18,
    2,
    3,
    CMD_STOP,
};

const unsigned char sampleDirt[] = {
    8,
    31,
    3,
    10,
    CMD_STOP,
};

const unsigned char sampleSpace[] = {
    8,
    2,
    2,
    4,
    CMD_STOP,
};

const unsigned char sampleBlip[] = {
    4,
    18,
    5,
    1,
    4,
    18,
    4,
    2,
    4,
    18,
    3,
    4,
    CMD_STOP,
};

const unsigned char sampleAmoeba[] = {
    0xE, 0x8, 5, 30,
    CMD_STOP,
    //    CMD_LOOP,
    // 12,10,2,1,
    // CMD_LOOP,
};

#if __ENABLE_LAVA
const unsigned char sampleLava[] = {
    3,
    10,
    2,
    2,
    CMD_LOOP,
};
#endif

const unsigned char sampleExxtra[] = {
    12,
    5,
    4,
    10,
    12,
    7,
    4,
    10,
    12,
    5,
    4,
    10,
    12,
    7,
    4,
    10,
    12,
    5,
    4,
    10,
    12,
    7,
    4,
    10,
    CMD_STOP,
};

const unsigned char sampleUncovered[] = {
    12,
    5,
    4,
    3,
    12,
    7,
    4,
    3,
    12,
    5,
    4,
    3,
    12,
    7,
    4,
    3,
    CMD_STOP,
};

const unsigned char samplePush[] = {
    8,
    4,
    4,
    12,
    CMD_STOP,
};

const unsigned char sampleExplode[] = {
    8,
    7,
    9,
    2,
    8,
    10,
    8,
    2,
    8,
    13,
    7,
    2,
    8,
    16,
    7,
    3,
    8,
    19,
    6,
    4,
    8,
    22,
    5,
    5,
    8,
    25,
    4,
    6,
    8,
    28,
    3,
    10,
    8,
    29,
    2,
    15,
    8,
    31,
    1,
    15,
    CMD_STOP,
};

const unsigned char sampleExplodeQuiet[] = {
    8,
    7,
    7,
    2,
    //    8, 10, 8, 2,
    8,
    13,
    5,
    2,
    //   8, 16, 7, 3,
    8,
    19,
    4,
    4,
    //   8, 22, 5, 5,
    8,
    25,
    2,
    6,
    //   8, 28, 3,10,
    8,
    29,
    1,
    15,
    //  8, 31, 1, 15,
    CMD_STOP,
};

const unsigned char sampleWhoosh[] = {
    15,
    31,
    1,
    2,
    15,
    31,
    2,
    2,
    15,
    28,
    3,
    2,
    15,
    25,
    4,
    3,
    15,
    22,
    5,
    4,
    15,
    19,
    6,
    5,
    15,
    16,
    7,
    6,
    15,
    13,
    7,
    10,
    15,
    10,
    4,
    2,
    15,
    7,
    2,
    2,
    CMD_STOP,
};

// const unsigned char sampleSpin[] = {
//     15, 31, 1, 1,
//     15, 31, 2, 2,
//     15, 28, 3, 3,
//     15, 25, 4, 5,
//     15, 22, 5, 6,
//     15, 19, 6, 6,
//     15, 16, 5, 6,
//     15, 13, 4, 5,
//     15, 10, 3, 3,
//     15, 7,  2, 2,
//     15, 7,  2, 1,
//     CMD_STOP,
// };

const unsigned char sample10987654321[] = {

    4,
    10,
    1,
    1,
    4,
    10,
    3,
    1,
    4,
    10,
    5,
    1,
    4,
    10,
    6,
    1,
    4,
    10,
    5,
    15,
    4,
    10,
    3,
    3,
    4,
    10,
    2,
    3,
    4,
    10,
    1,
    3,
    CMD_STOP,
};

const unsigned char sampleNone[] = {
    CMD_STOP,
};

const unsigned char sampleSFX[] = {
    // C,F,V,LEN
    5,
    14,
    4,
    1,
    5,
    12,
    6,
    1,
    5,
    11,
    7,
    1,
    5,
    3,
    10,
    2,
    5,
    4,
    8,
    1,
    5,
    5,
    6,
    1,
    5,
    6,
    4,
    1,
    5,
    7,
    1,
    1,
    CMD_STOP,
};

const unsigned char sampleDiamond2[] = {
    // C,F,V,LEN
    5,
    14,
    1,
    1,
    5,
    12,
    2,
    1,
    5,
    11,
    3,
    1,
    5,
    3,
    4,
    2,
    5,
    3,
    4,
    2,
    5,
    4,
    3,
    1,
    5,
    5,
    1,
    1,
    5,
    4,
    3,
    1,
    5,
    5,
    1,
    1,
    CMD_STOP,
};

const unsigned char sampleDiamond3[] = {
    // C,F,V,LEN
    5,
    14,
    1,
    1,
    5,
    11,
    3,
    1,
    5,
    3,
    4,
    1,
    5,
    4,
    3,
    1,
    5,
    5,
    1,
    1,
    CMD_STOP,
};

const unsigned char sampleExit[] = {
    12,
    16,
    1,
    1,
    12,
    16,
    4,
    1,
    12,
    16,
    10,
    1,
    12,
    16,
    8,
    4,
    12,
    16,
    6,
    1,
    12,
    16,
    4,
    1,
    12,
    16,
    2,
    1,
    CMD_STOP,
};

// const unsigned char sampleBirth[] = {

// //    8,4,1,1,
// //    8,4,4,1,
// //    8,4,8,1,
//     8,4,14,8,
//     8,4,10,4,
//     8,4,8,4,
//     8,4,6,4,
//     8,4,4,4,
//     8,4,2,4,
//     CMD_STOP,
// };

const struct AudioTable AudioSamples[] = {

    {sampleNone, 0, 0}, // 0  PLACEHOLDER - NOT USED AS SOUND

    // MUST correspond to AudioID enum ordering/number
    // MUST be in priority order!

    {sampleUncovered, 201, 0},                                      // SFX_UNCOVERED,          // 0
    {sample10987654321, 200, AUDIO_LOCKED},                         // SFX_COUNTDOWN2,         // 1
    {samplePick, 200, 0},                                           // SFX_PICKAXE,           // 2
    {sampleSFX, 200, 0},                                            // SFX_DIAMOND2,           // 2
    {sampleWhoosh, 127, 0},                                         // SFX_WHOOSH,             // 3
    {sampleBlip, 125, 0},                                           // SFX_BLIP,               // 4
    {sampleExxtra, 110, 0},                                         // SFX_EXTRA,              // 5
    {sampleExit, 99, 0},                                            // SFX_EXIT,               // 6
    {sampleExplode, 99, 0},                                         // SFX_EXPLODE,            // 7
    {sampleExplodeQuiet, 99, 0},                                    // SFX_EXPLODE_QUIET,            // 7
    {sampleMagic, 50, AUDIO_KILL},                                  // SFX_MAGIC,              // 8
    {sampleMagic2, 50, 0},                                          // SFX_MAGIC2,             // 9
    {sampleRock, 11, 0},                                            // SFX_ROCK,               // 10
    {sampleRock2, 10, 0},                                           // SFX_ROCK2,              // 11
    {sampleDrip2, 10, 0},                                           // SFX_SCORE,              // 12
    {sampleDiamond2, 9, 0},                                         // SFX_DIAMOND,            // 13
    {sampleDiamond3, 9, 0},                                         // SFX_DIAMOND3,           // 14
    {sampleDirt, 9, 0},                                             // SFX_DIRT,               // 15
    {samplePush, 8, 0},                                             // SFX_PUSH,               // 16
    {sampleSpace, 8, 0},                                            // SFX_SPACE,              // 17
    {sampleDrip2, 8, 0},                                            // SFX_DRIP,               // 18
    {sampleAmoeba, 7, AUDIO_LOCKED | AUDIO_SINGLETON | AUDIO_KILL}, // SFX_AMOEBA,             // 18
    {sampleDrip, 5, 0},                                             // SFX_DRIP2,              // 19
    {sampleUncover, 2, AUDIO_LOCKED | AUDIO_KILL},                  // SFX_UNCOVER,            // 20
// { sampleTick,           0, AUDIO_LOCKED | AUDIO_KILL          }, // SFX_TICK,               // 22

#if __ENABLE_LAVA
    {sampleLava, 2, true}, // 20
#endif
};

bool audioRequest[SFX_MAX];

void initAudio() {

    // #if __ENABLE_ATARIVOX
    // RAM[_BUF_SPEECH] = 0xFF;
    // #endif

    // for (int i = 0; i < MAX_TRACKS; i++)
    //     Track[i].id = 0;

    // RAM[_BUF_AUDV] =
    // RAM[_BUF_AUDV + 1] = 0;

    for (int i = 0; i < SFX_MAX; i++)
        audioRequest[i] = false;

    loadTrack(1, trackSimple);
    loadTrack(0, trackSimple);
}

void killAudio(enum AudioID id) {

    audioRequest[id] = false;
    for (int i = 0; i < MAX_TRACKS; i++)
        if (Track[i].id == id)
            Track[i].id = 0;
}

void killRepeatingAudio() {

    for (int i = 0; i < MAX_TRACKS; i++)
        if (AudioSamples[Track[i].id].flags & AUDIO_KILL)
            Track[i].id = 0;

    for (int i = 0; i < SFX_MAX; i++)
        if (AudioSamples[i].flags & AUDIO_KILL)
            audioRequest[i] = false;
}

void playAudio() {

#if 1
    processTracks();
#endif

    for (unsigned int id = 0; id < SFX_MAX; id++) {

        if (audioRequest[id]) {

#if ENABLE_SOUND

            if (AudioSamples[id].flags & AUDIO_SINGLETON) {
                bool dup = false;
                for (int i = 0; i < MAX_TRACKS; i++)
                    if (Track[i].id == id) {
                        dup = true;
                        break;
                    }
                if (dup)
                    continue;
            }

            int lowest = -1;
            for (int i = 0; i < MAX_TRACKS; i++) {

                int idx = Track[i].id;

                if (!idx) { // empty slot
                    lowest = i;
                    break;
                }

                if ((

                        !(AudioSamples[idx].flags & AUDIO_LOCKED) && // not locked, and...
                        (lowest < 0                                  // either we haven't found a lowest yet
                         || AudioSamples[Track[i].id].priority < AudioSamples[Track[lowest].id].priority)

                        // or the priority of this track is lower than the lowest found so far...

                        ))

                    lowest = i;
            }

            // we've now found the lowest priority sound in our current batch...
            // if the lowest slot is lower priority than new sound, replace it
            if (lowest >= 0 && (!Track[lowest].id || AudioSamples[id].priority >= AudioSamples[Track[lowest].id].priority)) {

                Track[lowest].index = 0;
                Track[lowest].id = id;
                Track[lowest].delay = AudioSamples[id].sample[3];

                audioRequest[id] = false;
            }

            else
                break; // sounds full or higher priority, ignore any more lower priority sounds

#endif
        }
    }

    // playAudio()

    for (int i = 0; i < MAX_TRACKS; i++) {
        struct Audio *track = &Track[i];
        track->handled = false;

        if (track->id && !--track->delay) {
            const struct AudioTable *s = &AudioSamples[track->id];
            track->index += 4;
            unsigned char cmd = s->sample[track->index];

            if (cmd == CMD_STOP)
                track->id = 0;

            else {
                if (cmd == CMD_LOOP)
                    track->index = 0;

                track->delay = s->sample[track->index + 3];
            }
        }
    }

    for (int channel = 0; channel < 2; channel++) {

        unsigned char audC = 0;
        unsigned char audV = 0;
        unsigned char audF = 0;

        struct Audio *best = 0;
        for (int i = 0; i < MAX_TRACKS; i++)
            if (Track[i].id && !Track[i].handled)
                if (!best || AudioSamples[best->id].priority < AudioSamples[Track[i].id].priority)
                    best = &Track[i];

        if (best) {

            best->handled = true;

            audC = AudioSamples[best->id].sample[best->index];
            audF = AudioSamples[best->id].sample[(best->index) + 1];
            audV = AudioSamples[best->id].sample[(best->index) + 2];

            switch (best->id) {

            case SFX_MAGIC2:
            case SFX_MAGIC:
                audF = getRandom32() & 0xF;
                break;

            case SFX_COUNTDOWN2:
                audF = (time >> 8) + 16;
                break;

            case SFX_AMOEBA: {
                // static unsigned char amoebaF;
                // if (!best->index && best->delay == AudioSamples[best->id].sample[3])
                //     amoebaF = (getRandom32() & 0xF) | 8;
                // audF = amoebaF;

                static int amFreq = 0;
                // if (!rangeRandom(4))
                amFreq = getRandom32() & 0x3;
                audF = amFreq;
                break;
            }

#if __ENABLE_LAVA
            case SFX_LAVA: {

                static unsigned char lavaF;
                static unsigned char lavaV;

                if (!best->index && best->delay == AudioSamples[best->id].sample[3] - 1) {
                    if ((getRandom32() & 0xFF) < 3) {

                        lavaF = (unsigned char)((getRandom32() & 0x3) + 12);
                        lavaV = getRandom32() & 3;

                        if (lavaV) {
                            FLASH(0x20, 10);
                            flashTime += lavaV;
#if ENABLE_SHAKE
                            extern int shakeTime;
                            shakeTime += 15; //(lavaV * 6);
#endif
                        }

                    }

                    else
                        lavaV = 0;
                }

                audV = lavaV;
                audF = lavaF;
            } break;
#endif // ENABLE_LAVA

                // case SFX_DEADBEAT: {

                //         static int f;
                //         if (!best->index && best->delay == AudioSamples[best->id].sample[3] - 1) {

                //             tuneIndex++;
                //             if (beat2[tuneIndex] == 0)
                //                 tuneIndex = 0;

                //             f = getRandom32();
                //         }

                //         audF = f; //getRandom32(); //beat2[tuneIndex];
                //     }
                //     break;

                // case SFX_DEADBEAT2: {

                //         if (!best->index && best->delay == AudioSamples[best->id].sample[3] - 1) {

                //             tuneIndex++;
                //             if (beat[tuneIndex] == 0)
                //                 tuneIndex = 0;
                //         }

                //         audF = beat[tuneIndex];
                //     }
                //     break;
            }
        }

#if ENABLE_SOUND

        if (audC && audV >= volume[channel]) {
            RAM[_BUF_AUDC + channel] = audC;
            RAM[_BUF_AUDF + channel] = audF;
            RAM[_BUF_AUDV + channel] = audV;

#if __ENABLE_DEMO
            if (!demoMode) {
#endif
                sound_volume -= 5;
                if (sound_volume < 0)
                    sound_volume = 0;
#if __ENABLE_DEMO
            }
#endif
        }
#endif
    }
}

#if 1

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-macros"

#define X(audc, audf) (((audc) << 6) | audf)
#define DUR(note) X(note, 0)

#define FULLNOTE 0b01000000,
#define HALFNOTE 0b10000000,
#define QUARTERNOTE 0b11000000,

#define C1 (0)
#define C4 (1)
#define C6 (2)
#define C12 (3)

#define a1_SHARP X(C6, 17),
#define a2_SHARP X(C1, 17),
#define a3 X(C12, 23),
#define a3_SHARP X(C1, 8),
#define a4 X(C12, 11),
#define a4_SHARP X(C12, 10),
#define b2 X(C6, 7),
#define b3 X(C6, 3),
#define c2 X(C1, 31),
#define c2_SHARP X(C1, 29),
#define c3 X(C1, 15),
#define c3_SHARP X(C1, 14),
#define c4 X(C12, 19),
#define c4_SHARP X(C12, 18),
#define c5 X(C4, 29),
#define d2_SHARP X(C6, 12),
#define d3 X(C1, 12),
#define d3_SHARP X(C1, 12),
#define d4_SHARP X(C12, 17),
#define d5 X(C4, 26),
#define d5_SHARP X(C4, 25),
#define e3 X(C12, 31),
#define e4 X(C12, 15),
#define f2 X(C1, 23),
#define f3 X(C12, 29),
#define f4 X(C12, 14),
#define f5 X(C4, 21),
#define g3 X(C12, 26),
#define g3_SHARP X(C12, 24),
#define g4 X(C12, 12),
#define g4_SHARP X(C1, 4),

#define b4 X(C4, 31),
#define c5_SHARP X(C4, 29),
#define g5_SHARP X(C4, 18),
#define f5_SHARP X(C4, 20),
#define d4 X(C12, 17),
#define b5 X(C4, 15),

#define e5 X(4, 23),
#define g5 X(4, 19),
#define a5 X(4, 17),
#define c6_SHARP X(12, 4),
#define d6 X(4, 12),
#define f4_SHARP X(12, 13),
#define e6 X(4, 11),
#define f6_SHARP X(4, 10),
#define g6 X(4, 9),
#define a6 X(4, 8),
#define b6 X(4, 7),
#define c7 X(1, 0),
#define f6 X(4, 10),
#define c6 X(4, 14),
#define f6_SHARP X(4, 10),
#define d6_SHARP X(4, 12),
#define e7 X(4, 5),

#pragma GCC diagnostic pop

// ref: http://www.retrointernals.org/boulder-dash/music.html
// ref: https://forums.atariage.com/topic/176497-atari-2600-frequency-and-tuning-chart-new-v11/#comment-2198932

static const unsigned char trackSimple[] = {

    // a4 g4 f4 g4 a4 c5 a4 g4 f4 e4 f4 g4 e4 a3 g4 f4 g4 a4 c5 a4 g4 f4 e4 f4 g4 e4
    // e4 f4 g4 a4 b4 a4 g4 f4 e4 f4 g4 e4 f4 g4 e4 d4 e4 f4 g4 a4 b4 a4 g4 f4 e4
    // b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6 a6 b6 c5 b5 a5 g5 f5 e5 d5 c5 b4 a4 g4 f4 e4 d4 c4
    // d4 e4 f4 g4 a4 b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6 a6 b6 c5 b5 a5 g5 f5 e5 d5 c5 b4 a4
    // e4 d4 c4 b3 c4 d4 e4 d4 c4 b3 c4 d4 e4 f4 e4 d4 c4 b3 c4 d4 e4 f4 g4 a4 g4 f4 e4 f4 g4 e4 f4 g4 a4 g4 f4 e4
    // b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6

    /*

    Subject (A minor):
    a4 g4 f4 g4 a4 c5 a4 g4 f4 e4 f4 g4 e4 a3 g4 f4 g4 a4 c5 a4 g4 f4 e4 f4 g4 e4

    Counter-Subject:
    e4 f4 g4 a4 b4 a4 g4 f4 e4 f4 g4 e4 f4 g4 e4 d4 e4 f4 g4 a4 b4 a4 g4 f4 e4

    Episode 1:
    b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6 a6 b6 c7 d7 e7 f7 g7

    Subject (D minor):
    d4 e4 f4 g4 a4 b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6 a6 b6 c7 d7

    Counter-Subject:
    g4 f4 e4 d4 c4 d4 e4 f4 g4 a4 b4 c5 d5 e5 f5 g5 a5 b5 c6 d6

    Episode 2:
    f5 e5 d5 c5 b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6 a6 b6 c7 d7

    Subject (G major):
    g4 a4 b4 c5 d5 e5 f#5 g5 a5 b5 c6 d6 e6 f#6 g6 a6 b6 c7 d7 e7 f#7 g7

    Counter-Subject:
    d5 e5 f#5 g5 a5 b5 c6 d6 e6 f#6 g6 a6 b6 c7 d7 e7 f#7 g7 a7

    Episode 3:
    c6 d6 e6 f#6 g6 a6 b6 c7 d7 e7 f#7 g7 a7 b7 c8 d8 e8 f#8 g8 a8 b8 c9 d9


    */

    // a4 g4 f4 g4 a4 c5 a4 g4 f4 e4 f4 g4 e4 a3 g4 f4 g4 a4 c5 a4 g4 f4 e4 f4 g4 e4
    // e4 f4 g4 a4 b4 a4 g4 f4 e4 f4 g4 e4 f4 g4 e4 d4 e4 f4 g4 a4 b4 a4 g4 f4 e4
    // // b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6 a6 b6 c7 d7 e7 f7 g7
    // // d4 e4 f4 g4 a4 b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6 a6 b6 c7 d7
    // // g4 f4 e4 d4 c4 d4 e4 f4 g4 a4 b4 c5 d5 e5 f5 g5 a5 b5 c6 d6
    // // f5 e5 d5 c5 b4 c5 d5 e5 f5 g5 a5 b5 c6 d6 e6 f6 g6 a6 b6 c7 d7
    // // g4 a4 b4 c5 d5 e5 f#5 g5 a5 b5 c6 d6 e6 f#6 g6 a6 b6 c7 d7 e7 f#7 g7
    // // d5 e5 f#5 g5 a5 b5 c6 d6 e6 f#6 g6 a6 b6 c7 d7 e7 f#7 g7 a7
    // // c6 d6 e6 f#6 g6 a6 b6 c7 d7 e7 f#7 g7 a7 b7 c8 d8 e8 f#8 g8 a8 b8 c9 d9

    // d5 d5 d5 d5  e5 f5 g5 a5 b5 c6 d6  c6 b5 a5 g5 f5 e5 d5
    // d5 d5 d5 d5  e5 f5 g5 a5 b5 c6 d6  c6 b5 a5 g5 f5 e5 d5
    // d5 d5 d5 d5  c5_SHARP d5 e5 f5 g5 a5 b5 c6  b5 a5 g5 f5 e5 d5 c5_SHARP
    // d5 d5 d5 d5  c5_SHARP d5 e5 f5 g5 a5 b5 c6  b5 a5 g5 f5 e5 d5 c5_SHARP
    // d5 c5_SHARP c5 b4  a4 g4 f4_SHARP f4  e4 d4 c4_SHARP c4  b3 a3 c3_SHARP g3

    // music for a found harmonium
    /* the one in A major */

    //   FULLNOTE
    a4 b4
        c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
            c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                    b4 a4 g4_SHARP a4 c5_SHARP a4 a4 a4
                        c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                            c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                                c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                                    b4 a4 g4_SHARP a4 c5_SHARP a4 a4 a4

                                        b4 a4 g4_SHARP a4 b4 a4 g4_SHARP a4
                                            c5_SHARP a4 g4_SHARP a4 c5_SHARP a4 g4_SHARP a4
                                                d5 a4 b4 a4 g4_SHARP a4 d5 a4
                                                    c5_SHARP a4 a4 a4
                                                        // QUARTERNOTE
                                                        a4 a4
                                                            // FULLNOTE
                                                            /* previous 2 should be single quarter note */ a4 a4
                                                                b4 a4 g4_SHARP a4 b4 a4 g4_SHARP a4
                                                                    c5_SHARP a4 g4_SHARP a4 c5_SHARP a4 g4_SHARP a4
                                                                        d5 a4 b4 a4 g4_SHARP a4 d5 a4
                                                                            c5_SHARP a4 a4 a4
                                                                                // QUARTERNOTE
                                                                                a4 a4
                                                                                    // FULLNOTE
                                                                                    /* previous 2 should be single quarter note */ a4 c5

                                                                                        g5_SHARP c5_SHARP b4 c5_SHARP d5 c5_SHARP b4 c5_SHARP
                                                                                            g5_SHARP c5_SHARP b4 c5_SHARP b4
                                                                                                // QUARTERNOTE
                                                                                                b4 b4
                                                                                                    // FULLNOTE
                                                                                                    /* previous 2 should be single quarter note */ c5_SHARP
                                                                                                        g5_SHARP c5_SHARP b4 c5_SHARP d5 c5_SHARP b4 c5_SHARP
                                                                                                            g5_SHARP c5_SHARP b4 c5_SHARP b4
                                                                                                                // QUARTERNOTE
                                                                                                                b4 b4
                                                                                                                    // FULLNOTE
                                                                                                                    /* previous 2 should be single quarter note */ a4

                                                                                                                        f5_SHARP c5_SHARP a4 c5_SHARP d5 c5_SHARP a4 c5_SHARP
                                                                                                                            f5_SHARP c5_SHARP a4 c5_SHARP d5 c5_SHARP a4 c5_SHARP
                                                                                                                                f5_SHARP c5_SHARP b4 c5_SHARP d5 b4 b4 d5
                                                                                                                                    f5_SHARP c5_SHARP b4 c5_SHARP d5 b4 b4 d5

                                                                                                                                        g5_SHARP d5 b4 d5 g5_SHARP d4 d4 d4
                                                                                                                                            g5_SHARP d5 b4 d5 g5_SHARP d4 d4 d4
                                                                                                                                                g5_SHARP d5 b4 d5 g5_SHARP d4 d4 d4
                                                                                                                                                    g5_SHARP d5 b4 d5 g5_SHARP d4 d4 d4

                                                                                                                                                        c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                                                                                                                                                            c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                                                                                                                                                                c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                                                                                                                                                                    b4 a4 g4_SHARP a4 c5_SHARP a4 a4 a4
                                                                                                                                                                        c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                                                                                                                                                                            c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                                                                                                                                                                                c5_SHARP a4 d5 a4 c5_SHARP a4 a4 a4
                                                                                                                                                                                    b4 a4 g4_SHARP a4 c5_SHARP a4 a4 a4

                                                                                                                                                                                        b4 a4 g4_SHARP a4 b4 a4 g4_SHARP a4
                                                                                                                                                                                            c5_SHARP a4 g4 a4 c5_SHARP a4 g4 a4
                                                                                                                                                                                                d5 a4 b4 a4 g4_SHARP a4 b5 a4
                                                                                                                                                                                                    c5_SHARP a4 a4 a4
                                                                                                                                                                                                        // QUARTERNOTE
                                                                                                                                                                                                        a4 a4
                                                                                                                                                                                                            // FULLNOTE
                                                                                                                                                                                                            /* previous 2 should be single quarter note */ a4 a4
                                                                                                                                                                                                                b4 a4 g4_SHARP a4 b4 a4 g4_SHARP a4
                                                                                                                                                                                                                    c5_SHARP a4 g4 a4 c5_SHARP a4 g4 a4
                                                                                                                                                                                                                        d5 a4 b4 a4 g4_SHARP a4 b5 a4
                                                                                                                                                                                                                            c5_SHARP a4 a4 a4
                                                                                                                                                                                                                                // QUARTERNOTE
                                                                                                                                                                                                                                a4 a4 a4 a4 /* previous 4 should be single half note */

    0};

// static const unsigned char trackSimple2[] = {

// //    HALFNOTE

//     f2 c3 f3 g3_SHARP d2_SHARP d3 d3_SHARP a3_SHARP c2_SHARP c2_SHARP c3_SHARP c2_SHARP
//     d3_SHARP a4_SHARP e3 g4_SHARP f2 f2 f2 f2 d2_SHARP d2_SHARP d2_SHARP d2_SHARP f2 f2 f2 f2
//     c3_SHARP c3_SHARP c3_SHARP c3_SHARP d2_SHARP d2_SHARP d2_SHARP d2_SHARP b2 b2 b2 b2 c2 c4
//     c2 c4 a1_SHARP a1_SHARP f2 f2 f2 f2 f2 f2 f3 f3 f2 f2 d2_SHARP d2_SHARP d2_SHARP d2_SHARP
//     d3_SHARP d3_SHARP d2_SHARP d2_SHARP f2 a4 f2 a4_SHARP f3 a4 f2 a4_SHARP d2_SHARP a4
//     d2_SHARP a4_SHARP d3_SHARP g4 d2_SHARP g4_SHARP f2 f2 f2 c5 f3 f3 f2 g4_SHARP d2_SHARP
//     d2_SHARP d2_SHARP d2_SHARP d3_SHARP d3_SHARP d2_SHARP d2_SHARP f2 a4 f2 a4_SHARP f3 a4 f2
//     a4_SHARP d2_SHARP a4 d2_SHARP a4_SHARP d3_SHARP g4 d2_SHARP g4_SHARP f4 c4 a3 f3 d4_SHARP
//     a3_SHARP g3 d2_SHARP c5 a4 f4 c4 a3_SHARP g3 d3_SHARP d2_SHARP
//     0
// };

// Instrument envelopes have 16 bytes defining the volume multipliers for each "audio tick"

static const unsigned char adsr_Trombone[] = {

    50, 100, 150, 200, 200, 180, 200, 180, 200, 180, 200, 150, 100, 50, 0, 0,

    200, 180, 160, 140, 96, 95, 94, 93, 92, 91, 80, 60, 40, 20, 0, 0};

static const unsigned char adsr_Trombone2[] = {
    100, 200, 255, 255, 200, 150, 75, 75, 100, 100, 100, 100, 75, 75, 75, 75,
    // 10, 20, 25, 25, 20, 15, 7, 7, 10, 10, 10, 10, 7, 7, 7, 7,
    //    80, 80, 60, 250, 250, 160, 50, 40, 10, 0, 0, 0, 0, 0, 0, 0
};

// static const unsigned char adsr_2[] = {
//     80, 80, 60, 250, 250, 160, 50, 40, 10, 0, 0, 0, 0, 0, 0, 0
// };

static const unsigned char *const instrument[] = {
    adsr_Trombone2,
    adsr_Trombone, // tmp2,
};

struct trackInfo track[TRACK_MAX];

void loadTrack(int t, const unsigned char *tune) {

    track[t].tune = tune;
    track[t].index = 0;
    track[t].progress = 0;
    track[t].instrument = t;
    track[t].volume = 256;
    track[t].noteDurationMultiplier = 0x100; // 0x80 = single note, 0x40 = half-note, etc
}

static const int systemSpeed[] = {

    0x11500 * 7 / 60,
    0x11500 * 7 / 50,
    0x11500 * 7 / 60,
    0x11500 * 7 / 50,
};

static const unsigned char renote[] = {
    1, 4, 6, 12};

const int multiplier[] = {
    0, 0x100, 0x200, 0x400};

void processTracks() {

    if (sound_volume < sound_max_volume)
        sound_volume += 2;

    else if (sound_volume > 2)
        sound_volume -= 3;

    for (int i = 0; i < 2; i++) {

        if (track[i].progress >= 0x10000) {

            unsigned char nextNote;
            bool done;

            do {
                done = true;
                nextNote = track[i].tune[track[i].index++];

                if (!nextNote)
                    track[i].index = 0;

                else if (!(nextNote & 0b00111111)) {
                    track[i].noteDurationMultiplier = multiplier[nextNote >> 6];
                    done = false;
                }

            } while (!done);

            track[i].progress -= 0x10000;
        }

        unsigned char note = track[i].tune[track[i].index];
        int envelope_ptr = (track[i].progress) >> (12);

        RAM[_BUF_AUDV + i] = volume[i] = (instrument[track[i].instrument][envelope_ptr] * sound_volume * track[i].volume) >> (4 + 10 + 8);
        RAM[_BUF_AUDF + i] = note;
        RAM[_BUF_AUDC + i] = renote[note >> 6];

        track[i].progress += (systemSpeed[mm_tv_type] * track[i].noteDurationMultiplier) >> 8;
    }
}

#endif

#if 0
Alternative...

[F4, F4, F4, F4,   F4, F4, F4, F4,   F4, F4, F4, F4,   F4, F4, F4, F4]
[F4, A4, F4,Bb4,   F4, A4, F4,Bb4,   F4, A4, F4,Bb4,  Eb4, G4,Eb4,Ab4]
[F4, F5, F4,Eb5,   F4, D5, F4, C5,  Eb4,Eb5,Eb4,Eb5,  Eb4,Bb4,Eb4,Eb5]
[F4, A4, F4,Bb4,   F4, A4, F4,Bb4,   F4, A4, F4,Bb4,  Eb4, G4,Eb4,Ab4]
[A4, F4, C4, A3,   G4,Eb4,Bb3,Eb3,   C5, A4, F4, C4,   G4,Eb4,Bb3,Eb3]

aud0=aud0.ring

[F2, C3, F3,Ab3,  Eb2, D3,Eb3,Bb3,  Db2,Db2,Db3,Db2,  Eb3,Bb4, E3, A4]
[F2, F2, F2, F2,  Eb2,Eb2,Eb2,Eb2,   F2, F2, F2, F2,  Db3,Db3,Db3,Db3]
[Eb2,Eb2,Eb2,Eb2,   B2, B2, B2, B2,   C2, C3, C2, C3,  Bb2,Bb2, F2, F2]
[F2, F2, F2, F2,   F3, F3, F2, F2,  Eb2,Eb2,Eb2,Eb2,  Eb3,Eb3,Eb2,Eb2]
[F2, F4, F2, F4,   F3, F4, F2, F4,  Eb2, F4,Eb2, F4,  Eb3,Eb4,Eb2,Eb4]
[F2, F2, F2, C5,   F3, F3, F2, C5,  Eb2,Eb2,Eb2,Eb2,  Eb3,Eb3,Eb2,Eb2]
[F2, F4, F2, F4,   F3, F4, F2, F4,  Eb2, F4,Eb2, F4,  Eb3,Eb4,Eb2,Eb4]
[F4, C4, A3, F3,  Eb4,Bb3, G3,Eb2,   A4, F4, C4, A3,  Bb3, G3,Eb3,Eb2]

#endif

// EOF