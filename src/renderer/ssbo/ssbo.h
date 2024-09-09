#ifndef SSBO_H
#define SSBO_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

#define NUM_SSBOS 2
#define GAME_SSBO 0
#define GUI_SSBO  1

typedef struct {
    u32 id;
} SSBO;

SSBO ssbo_create(size_t size);
void ssbo_bind(SSBO ssbo);
void ssbo_bind_buffer_base(SSBO ssbo, u32 index);
void ssbo_update(SSBO ssbo, size_t offset, size_t size, void *data);
void ssbo_destroy(SSBO ssbo);

#endif