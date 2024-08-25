#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

static pthread_t thread_id;
static bool kill_thread;
static sem_t mutex;

Audio audio;

static void checkError(const char* msg) {
    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        fprintf(stderr, "OpenAL Error: %s\n", msg);
        fprintf(stderr, "Error code: %X\n", error);
        exit(EXIT_FAILURE);
    }
}

static void *audio_update(void *vargp)
{
    while (!kill_thread) {
        aud_wait();
        for (ALint i = 0; i < num_auds; i++) {
            Aud *aud = &auds[i];
            if (!aud->playing) {
                audio_play_sound(aud->id);
                aud->playing = TRUE;
            }
        }
        aud_post();

        sem_wait(&mutex);
        for (ALint i = 0; i < audio.num_sources; i++) {
            ALuint source_state, source, tmp;
            source = audio.sources[i];
            alGetSourcei(source, AL_SOURCE_STATE, &source_state);
            if (source_state == AL_STOPPED) {
                tmp = audio.sources[i];
                audio.sources[i] = audio.sources[audio.num_sources-1];
                audio.sources[audio.num_sources-1] = tmp;
                audio.num_sources--;
                i--;
            }
        }
        sem_post(&mutex);
    }
}

static int load_sounds(void);

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

    audio.buffers = malloc(sizeof(ALuint));
    alGenBuffers(1, audio.buffers);
    checkError("Failed to generate buffers.");

    audio.sources = malloc(MAX_NUM_SOURCES * sizeof(ALuint));
    alGenSources(MAX_NUM_SOURCES, audio.sources);
    checkError("Failed to generate sources.");
    audio.num_sources = 0;

    load_sounds();

    kill_thread = FALSE;
    sem_init(&mutex, 0, 1);
    pthread_create(&thread_id, NULL, audio_update, NULL);

    return EXIT_SUCCESS;
}

void audio_play_sound(ALint id)
{
    if (audio.num_sources >= MAX_NUM_SOURCES)
        return;
    sem_wait(&mutex);
    ALuint source = audio.sources[audio.num_sources];
    alSourcei(source, AL_BUFFER, audio.buffers[id]);
    alSourcePlay(source);
    checkError("Failed to play source.");
    audio.num_sources++;
    sem_post(&mutex);
}

void audio_destroy()
{
    kill_thread = TRUE;
    pthread_join(thread_id, NULL);
    sem_destroy(&mutex);

    for (ALint i = 0; i < MAX_NUM_SOURCES; i++) {
        alSourceStop(audio.sources[i]);
        checkError("Failed to stop source.");
    }

    alDeleteSources(MAX_NUM_SOURCES, audio.sources);
    checkError("Failed to delete source.");
    free(audio.sources);

    alDeleteBuffers(1, audio.buffers);
    checkError("Failed to delete buffers.");
    free(audio.buffers);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(audio.context);
    alcCloseDevice(audio.device);
}

static int load_sound(ALuint id, char *path)
{
    SNDFILE *file;
    SF_INFO sfinfo;
    ALenum format;
    ALshort *samples;
    ALsizei numSamples;
    ALsizei size;
    ALsizei freq;
    
    file = sf_open(path, SFM_READ, &sfinfo);
    if (!file) {
        fprintf(stderr, "Failed to open sound file: %s.\n", path);
        return EXIT_FAILURE;
    }

    if (sfinfo.channels == 1) {
        format = AL_FORMAT_MONO16;
    } else if (sfinfo.channels == 2) {
        format = AL_FORMAT_STEREO16;
    } else {
        fprintf(stderr, "Unsupported number of channels: %s.\n", path);
        sf_close(file);
        return EXIT_FAILURE;
    }

    size = sfinfo.frames * sfinfo.channels * sizeof(ALshort);
    samples = malloc(size);
    if (!samples) {
        fprintf(stderr, "Failed to allocate memory for audio samples: %s.\n", path);
        sf_close(file);
        return EXIT_FAILURE;
    }

    numSamples = sf_read_short(file, samples, sfinfo.frames * sfinfo.channels);
    if (numSamples != sfinfo.frames * sfinfo.channels) {
        fprintf(stderr, "Failed to read all samples from file: %s.\n", path);
        free(samples);
        sf_close(file);
        return EXIT_FAILURE;
    }
    freq = sfinfo.samplerate;
    sf_close(file);
    
    alBufferData(audio.buffers[id], format, samples, size, freq);
    checkError("Failed to fill buffer with data.");

    free(samples);
}

static int load_sounds(void)
{
    load_sound(GUI_CLICK_AUD, "assets/audio/hit.wav");
}