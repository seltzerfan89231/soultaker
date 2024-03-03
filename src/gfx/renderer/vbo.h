#ifndef VBO_H
#define VBO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>

typedef struct VBO {
    u32 ID;
    GLenum type;
    void* data;
    size_t size;
} VBO;

VBO vbo_create(GLenum type);
void vbo_update(VBO* vbo, size_t size, void* data);
void vbo_bind(VBO vbo);
void vbo_buffer(VBO vbo);
void vbo_destroy(VBO vbo);

#endif