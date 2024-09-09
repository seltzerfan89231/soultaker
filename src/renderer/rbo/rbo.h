#ifndef RBO_H
#define RBO_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

#define NUM_RBOS 1
#define GAME_RBO 0

typedef struct {
    u32 id;
} RBO;

RBO rbo_create(u32 width, u32 height);
void rbo_bind(RBO rbo);
void rbo_bind_default(void);
void rbo_destroy(RBO rbo);

#endif