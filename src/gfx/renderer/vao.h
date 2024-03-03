#ifndef VAO_H
#define VAO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>
#include "vbo.h"

typedef struct VAO {
    u32 ID;
    VBO vbo, ebo;
} VAO;

VAO vao_create(void);
void vao_bind(VAO vao);
void vao_update(VAO vao, GLenum type, u32 size, void* data);
void vao_attr(u8 index, u8 count, u32 size, void* offset);
void vao_destroy(VAO vao);

#endif