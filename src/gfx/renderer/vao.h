#ifndef VAO_H
#define VAO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>
#include "vbo.h"

typedef struct VAO {
    u32 ID;
    VBO vbo;
    u32 index_count, index_size;
    u32* indices;
} VAO;

VAO vao_create(u32 index_count, u32 index_size, u32* indices);
void vao_update(VAO* vao, u32 offset, size_t buffer_size, f32* buffer);
void vao_destroy(VAO vao);
void vao_draw(VAO vao);

#endif