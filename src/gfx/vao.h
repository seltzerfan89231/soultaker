#ifndef VAO_H
#define VAO_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>

typedef struct VAO {
    u32 ID;
} VAO;

VAO vao_create(void);
void vao_bind(VAO vao);
void vao_attr(u8 index, u8 count, u32 size, void* offset);

#endif