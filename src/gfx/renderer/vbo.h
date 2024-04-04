#ifndef VBO_H
#define VBO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>
#include <constants.h>

typedef enum buffertype { DRAWABLE = 0, GUI = 1 } buffertype;

typedef struct VBO {
    u32 ID;
    u32 buffer_length;
} VBO;

VBO vbo_create(buffertype type);
void vbo_update(VBO* vbo, u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length);
void vbo_destroy(VBO vbo);

#endif