#include "vao.h"

VAO vao_create(void)
{
    VAO vao;
    glGenVertexArrays(1, &vao.ID);
    return vao;
}

void vao_bind(VAO vao)
{
    glBindVertexArray(vao.ID);
}

void vao_attr(u8 index, u8 count, u32 size, void* offset)
{
    glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, size, offset);
    glEnableVertexAttribArray(index);
}