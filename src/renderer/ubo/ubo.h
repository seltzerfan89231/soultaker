#ifndef UBO_H
#define UBO_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

typedef struct {
    u32 id;
} UBO;

UBO ubo_create(size_t size);
void ubo_bind_buffer_base(UBO ubo, u32 index);
void ubo_bind(UBO ubo);
void ubo_update(UBO ubo, size_t offset, size_t size, f32 *data);
void ubo_destroy(UBO ubo);

#endif