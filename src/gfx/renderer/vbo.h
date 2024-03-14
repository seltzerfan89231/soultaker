#ifndef VBO_H
#define VBO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>

typedef struct VBO {
    u32 ID;
    void* buffer;
    size_t buffer_size;
} VBO;

VBO vbo_create(void);
void vbo_update(VBO* vbo, size_t buffer_size, f32* buffer);

#endif