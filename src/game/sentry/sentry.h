
#ifndef SENTRY_H
#define SENTRY_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../projectile/projectile.h"
#include "../aoe/aoe.h"

typedef struct {
    vec3f position;
    u32 id;
    f32 timer;
} Sentry;

Sentry* sentry_create(u32 id);
void sentry_update(Sentry* sentry, f32 dt);
void sentroy_destroy(Sentry* sentry, u32 idx);
void destroy_all_sentries(void);

_ARRAY_DECLARE(Sentry, sentry)
extern SentryArray global_sentries;

#define MAX_SENTRY_ID 1
#define SHAITAN_SENTRY 0

#define _SENTRY_INIT(_type) \
    void _type##_create(Sentry* sentry); \
    void _type##_update(Sentry* sentry, f32 dt);

_SENTRY_INIT(shaitan_sentry)

#endif