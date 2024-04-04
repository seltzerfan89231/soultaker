#ifndef VAO_H
#define VAO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>
#include "vbo.h"

typedef enum buffertype { DRAWABLE = 0, GUI = 1 } buffertype;

typedef struct VAO {
    u32 ID, vertex_length;
    VBO vbo;
} VAO;

VAO vao_create(buffertype type);
void vao_update(VAO* vao, u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length);
void vao_destroy(VAO vao);
void vao_bind(VAO vao);
void vao_draw(VAO vao);

#endif