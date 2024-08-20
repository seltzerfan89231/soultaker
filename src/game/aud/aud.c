#include "aud.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_AUDS 2

Aud *auds;
i32 num_auds;
static pthread_t thread_id;
static bool kill_thread;
static sem_t mutex;

// singleplayer doesnt need this thread

static void *aud_update(void *vargp)
{
    while (TRUE) {
        if (kill_thread)
            pthread_exit(NULL);

        sem_wait(&mutex);
        for (i32 i = 0; i < num_auds; i++) {
            Aud aud = auds[i];
            if (aud.playing) {
                auds[i] = auds[num_auds-1];
                num_auds--;
            }
        }
        sem_post(&mutex);
    }
}

void aud_init()
{
    auds = malloc(MAX_NUM_AUDS * sizeof(Aud));
    kill_thread = FALSE;
    sem_init(&mutex, 0, 1);
    pthread_create(&thread_id, NULL, aud_update, NULL);
}

void aud_destroy()
{
    kill_thread = TRUE;
    pthread_join(thread_id, NULL);
    free(auds);
    sem_destroy(&mutex);
}

void aud_clear()
{
    sem_wait(&mutex);
    num_auds = 0;
    sem_post(&mutex);
}

void aud_play(u32 id)
{
    if (num_auds >= MAX_NUM_AUDS)
        return;
    sem_wait(&mutex);
    Aud aud = { .id = id, .playing = FALSE };
    auds[num_auds++] = aud;
    sem_post(&mutex);
}

void aud_wait()
{
    sem_wait(&mutex);
}

void aud_post()
{
    sem_post(&mutex);
}
