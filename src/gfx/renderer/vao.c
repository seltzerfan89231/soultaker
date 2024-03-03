#include "vao.h"

VAO vao_create(void)
{
    VAO vao;
    glGenVertexArrays(1, &vao.ID);
    vao.vbo = vbo_create(GL_ARRAY_BUFFER);
    vao.ebo = vbo_create(GL_ELEMENT_ARRAY_BUFFER);
    return vao;
}

void vao_bind(VAO vao)
{
    glBindVertexArray(vao.ID);
}

void vao_update(VAO vao, GLenum type, u32 size, void* data)
{
    if (type == GL_ARRAY_BUFFER)
        vbo_update(&vao.vbo, size, data);
    else if (type == GL_ELEMENT_ARRAY_BUFFER)
        vbo_update(&vao.ebo, size, data);
}

void vao_attr(u8 index, u8 count, u32 size, void* offset)
{
    glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, size, offset);
    glEnableVertexAttribArray(index);
}

void vao_destroy(VAO vao)
{
    vbo_destroy(vao.vbo);
    vbo_destroy(vao.ebo);
}