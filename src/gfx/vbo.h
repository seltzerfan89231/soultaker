#ifndef VBO_H
#define VBO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>

typedef struct VBO {
    u32 ID;
    GLenum type;
} VBO;

VBO vbo_create(GLenum type);
void vbo_bind(VBO vbo);
void vbo_buffer(VBO vbo, u32 size, void *data);

#endif