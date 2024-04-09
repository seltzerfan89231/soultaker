#ifndef VAO_H
#define VAO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>
#include "vbo.h"

typedef struct VAO {
    u32 id, length;
    VBO vbo;
} VAO;

VAO vao_create(void);
void vao_attr(VAO* vao, u32 index, u32 length, u32 stride, u32 offset);
void vao_update(VAO* vao, u32 offset, u32 length, f32* buffer);
void vao_malloc(VAO* vao, u32 length, GLenum usage);
void vao_destroy(VAO vao);
void vao_bind(VAO vao);
void vao_draw(VAO vao);

#endif