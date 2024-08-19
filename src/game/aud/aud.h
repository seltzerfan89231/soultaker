#ifndef AUD_H
#define AUD_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/indices.h"
#include <al.h>
#include <alc.h>

typedef struct {
    ALuint id;
    bool playing;
} Aud;

extern Aud *auds;
extern i32 num_auds;

void aud_init();
void aud_destroy();
void aud_clear();
void aud_push(u32 id);
void aud_wait();
void aud_post();
i32 get_num_auds();

#endif