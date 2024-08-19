#include "audio.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

Audio audio;

void checkError(const char* msg) {
    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        fprintf(stderr, "OpenAL Error: %s\n", msg);
        fprintf(stderr, "Error code: %d\n", error);
        exit(EXIT_FAILURE);
    }
}

int audio_init() {
    audio.device = alcOpenDevice(NULL);
    if (!audio.device) {
        fprintf(stderr, "Failed to open OpenAL device.\n");
        return EXIT_FAILURE;
    }
    audio.context = alcCreateContext(audio.device, NULL);
    if (!audio.context) {
        fprintf(stderr, "Failed to create OpenAL context.\n");
        alcCloseDevice(audio.device);
        return EXIT_FAILURE;
    }
    alcMakeContextCurrent(audio.context);

    /* ----------------------------- */

    SNDFILE *file;
    SF_INFO sfinfo;
    file = sf_open("assets/audio/nature.wav", SFM_READ, &sfinfo);
    if (!file) {
        fprintf(stderr, "Failed to open sound file.\n");
        return EXIT_FAILURE;
    }

    if (sfinfo.channels == 1) {
        audio.sound1.format = AL_FORMAT_MONO16;
    } else if (sfinfo.channels == 2) {
        audio.sound1.format = AL_FORMAT_STEREO16;
    } else {
        fprintf(stderr, "Unsupported number of channels.\n");
        sf_close(file);
        return EXIT_FAILURE;
    }

    audio.sound1.size = sfinfo.frames * sfinfo.channels * sizeof(ALshort);
    audio.sound1.samples = malloc(audio.sound1.size);
    if (!audio.sound1.samples) {
        fprintf(stderr, "Failed to allocate memory for audio samples.\n");
        sf_close(file);
        return EXIT_FAILURE;
    }

    ALsizei numSamples = sf_read_short(file, audio.sound1.samples, sfinfo.frames * sfinfo.channels);
    if (numSamples != sfinfo.frames * sfinfo.channels) {
        fprintf(stderr, "Failed to read all samples from file.\n");
        free(audio.sound1.samples);
        sf_close(file);
        return EXIT_FAILURE;
    }
    audio.sound1.freq = sfinfo.samplerate;
    sf_close(file);
    alGenBuffers(1, &audio.sound1.buffer);
    checkError("Failed to generate buffer.");
    alBufferData(audio.sound1.buffer, 
                 audio.sound1.format, 
                 audio.sound1.samples, 
                 audio.sound1.size, 
                 audio.sound1.freq);
    checkError("Failed to fill buffer with data.");

    return EXIT_SUCCESS;
}

void audio_play_sound()
{
    ALuint source;
    alGenSources(1, &source);
    checkError("Failed to generate source.");
    alSourcei(source, AL_BUFFER, audio.sound1.buffer);
    alSourcePlay(source);
    checkError("Failed to play source.");
}

void audio_destroy()
{
    free(audio.sound1.samples);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(audio.context);
    alcCloseDevice(audio.device);
}