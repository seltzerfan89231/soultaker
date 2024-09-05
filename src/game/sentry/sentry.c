#include "sentry.h"
#include <stdlib.h>

SentryArray global_sentries;

#define _SENTRY_CREATE(_id, _lid) \
    case _id : _lid##_create(sentry); break;

Sentry* sentry_create(u32 id)
{
    Sentry* sentry = malloc(sizeof(Sentry));
    sentry->id = id;
    sentry->timer = 0;
    switch (sentry->id) {
        _SENTRY_CREATE(SHAITAN_SENTRY, shaitan_sentry)
    }
    sentry_array_push(&global_sentries, sentry);
    return sentry;
}

#define _SENTRY_UPDATE(_id, _lid) \
    case _id : _lid##_update(sentry, dt); break;

void sentry_update(Sentry* sentry, f32 dt)
{
    switch (sentry->id) {
        _SENTRY_UPDATE(SHAITAN_SENTRY, shaitan_sentry)
    }
    sentry->timer -= dt;
}

void sentroy_destroy(Sentry* sentry, u32 idx)
{
    assert(sentry == global_sentries.buffer[idx]);
    sentry_array_cut(&global_sentries, idx);
    free(sentry);
}

void destroy_all_sentries(void)
{
    for (i32 i = 0; i < global_sentries.length; i++)
        free(global_sentries.buffer[i]);
    sentry_array_destroy(&global_sentries);
}


_ARRAY_DEFINE(Sentry, sentry)