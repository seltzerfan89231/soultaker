#include <stdio.h>
#include <stdlib.h>
#include <al.h>
#include <alc.h>
#include <sndfile.h>

#define BUFFER_SIZE 4096

void checkError(const char* msg) {
    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        fprintf(stderr, "OpenAL Error: %s\n", msg);
        fprintf(stderr, "Error code: %d\n", error);
        exit(EXIT_FAILURE);
    }
}

int audio_test() {
    ALCdevice* device;
    ALCcontext* context;
    ALuint source;
    ALuint buffer;
    SNDFILE* file;
    SF_INFO sfinfo;
    ALshort* samples;
    ALsizei numSamples;
    ALsizei size;
    ALenum format;

    // Initialize OpenAL
    device = alcOpenDevice(NULL);  // Open default device
    if (!device) {
        fprintf(stderr, "Failed to open OpenAL device.\n");
        return EXIT_FAILURE;
    }

    context = alcCreateContext(device, NULL);
    if (!context) {
        fprintf(stderr, "Failed to create OpenAL context.\n");
        alcCloseDevice(device);
        return EXIT_FAILURE;
    }
    alcMakeContextCurrent(context);

    // Load the sound file
    file = sf_open("test.wav", SFM_READ, &sfinfo);
    if (!file) {
        fprintf(stderr, "Failed to open sound file.\n");
        alcDestroyContext(context);
        alcCloseDevice(device);
        return EXIT_FAILURE;
    }

    // Determine the audio format
    if (sfinfo.channels == 1) {
        format = AL_FORMAT_MONO16;
    } else if (sfinfo.channels == 2) {
        format = AL_FORMAT_STEREO16;
    } else {
        fprintf(stderr, "Unsupported number of channels.\n");
        sf_close(file);
        alcDestroyContext(context);
        alcCloseDevice(device);
        return EXIT_FAILURE;
    }

    // Allocate and fill the buffer with sound data
    size = sfinfo.frames * sfinfo.channels * sizeof(ALshort);
    samples = (ALshort*)malloc(size);
    if (!samples) {
        fprintf(stderr, "Failed to allocate memory for audio samples.\n");
        sf_close(file);
        alcDestroyContext(context);
        alcCloseDevice(device);
        return EXIT_FAILURE;
    }

    numSamples = sf_read_short(file, samples, sfinfo.frames * sfinfo.channels);
    if (numSamples != sfinfo.frames * sfinfo.channels) {
        fprintf(stderr, "Failed to read all samples from file.\n");
        free(samples);
        sf_close(file);
        alcDestroyContext(context);
        alcCloseDevice(device);
        return EXIT_FAILURE;
    }
    sf_close(file);

    // Generate a buffer and source
    alGenBuffers(1, &buffer);
    checkError("Failed to generate buffer.");
    alBufferData(buffer, format, samples, size, sfinfo.samplerate);
    checkError("Failed to fill buffer with data.");

    alGenSources(1, &source);
    checkError("Failed to generate source.");
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    checkError("Failed to play source.");

    printf("Playing audio. Press Enter to stop...\n");
    getchar();

    // Clean up
    alSourceStop(source);
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    free(samples);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return EXIT_SUCCESS;
}