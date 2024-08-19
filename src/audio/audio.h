#ifndef AUDIO_H
#define AUDIO_H

#include <al.h>
#include <alc.h>
#include <sndfile.h>
#include "../game/aud/aud.h"
#include "../util/indices.h"
#include "../util/type.h"

#define MAX_NUM_SOURCES 100

typedef struct {
    ALCdevice *device;
    ALCcontext *context;
    ALuint *buffers;
    ALuint *sources;
    ALuint num_sources;
} Audio;

extern Audio audio;

int audio_init();
void audio_play_sound(ALint id);
void audio_destroy();

#endif