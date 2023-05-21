#ifndef __SOUND_H
#define __SOUND_H

#define AUDIO_LOCKED 0x80
#define AUDIO_SINGLETON 0x40
#define AUDIO_KILL 0x20

#define ADDAUDIO(id) audioRequest[id] = true

struct AudioTable {
    const unsigned char *sample;
    const unsigned char priority;
    unsigned char flags; // locked;
};

enum AudioCommand {
    CMD_LOOP = 254,
    CMD_STOP = 255,
};

enum AudioID {

    // Ordered by priority; see AudioSamples[]

    SFX_NULL,          // 00
    SFX_UNCOVERED,     // 01
    SFX_COUNTDOWN2,    // 02  time expiring
    SFX_PICKAXE,       // 03
    SFX_DOGE2,         // 04
    SFX_WHOOSH,        // 05
    SFX_BLIP,          // 06
    SFX_EXTRA,         // 07
    SFX_EXIT,          // 08
    SFX_EXPLODE,       // 09
    SFX_EXPLODE_QUIET, // 10
    SFX_MAGIC,         // 11
    SFX_MAGIC2,        // 12
    SFX_ROCK,          // 13
    SFX_ROCK2,         // 14
    SFX_SCORE,         // 15
    SFX_DOGE,          // 16
    SFX_DOGE3,         // 17
    SFX_DIRT,          // 18
    SFX_PUSH,          // 19
    SFX_SPACE,         // 20
    SFX_DRIP,          // 21
    SFX_BUBBLER,       // 22
    SFX_DRIP2,         // 23
    SFX_UNCOVER,       // 24

#if __ENABLE_LAVA2
    SFX_LAVA, // 25
#endif

    SFX_MAX, // size only; not a sound
};

extern bool audioRequest[SFX_MAX];

struct Audio {
    unsigned char id;
    unsigned char delay;
    bool handled;
    unsigned int index;
};

#define MAX_TRACKS 4

struct trackInfo {

    const unsigned char *tune;
    int index;
    int progress;
    unsigned char instrument;
    unsigned char frequency;
    int volume;
    int noteDurationMultiplier;
    // int speed;
};

#define TRACK_MAX 2
#define VOLUME_NONPLAYING 312
#define VOLUME_PLAYING 384
#define VOLUME_MAX 1024

extern struct trackInfo track[TRACK_MAX];

extern int sound_volume;
extern int sound_max_volume;

void playAudio();
bool addAudio(enum AudioID id);
void killAudio(enum AudioID id);
void killRepeatingAudio();
void initAudio();

#endif
// EOF