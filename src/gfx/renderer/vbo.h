#ifndef VBO_H
#define VBO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>
#include <constants.h>

typedef struct VBO {
    u32 ID;
    u32 buffer_length;
} VBO;

VBO vbo_create(void);
void vbo_update(VBO* vbo, u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length);
void vbo_destroy(VBO vbo);

#endif