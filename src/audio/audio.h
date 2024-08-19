#ifndef AUDIO_H
#define AUDIO_H

#include <al.h>
#include <alc.h>
#include <sndfile.h>

typedef struct {
    ALuint buffer;
    ALenum format;
    ALshort *samples;
    ALsizei size;
    ALsizei freq;
} SoundInfo;

typedef struct {
    ALCdevice *device;
    ALCcontext *context;
    SoundInfo sound1;
} Audio;

extern Audio audio;

int audio_init();
void audio_play_sound();
void audio_destroy();

#endif