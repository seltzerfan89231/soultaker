#include "vao.h"

VAO vao_create(GLenum usage, GLenum mode, u32 length, bool use_ebo)
{
    VAO vao;
    glGenVertexArrays(1, &vao.id);
    glBindVertexArray(vao.id);
    vao.vbo = vbo_create();
    vao.ebo = use_ebo ? ebo_create() : NULL;
    vao.length = length;
    vao.usage = usage;
    vao.mode = mode;
    return vao;
}

void vao_attr(VAO vao, u32 index, u32 length, u32 offset)
{
    glBindVertexArray(vao.id);
    vbo_bind(vao.vbo);
    glVertexAttribPointer(index, length, GL_FLOAT, GL_FALSE, vao.length * sizeof(f32), (void*)(offset * sizeof(f32)));
    glEnableVertexAttribArray(index);
}

void vao_update(VAO vao, u32 vbo_offset, u32 vbo_length, f32* vbo_buffer, u32 ebo_offset, u32 ebo_length, u32* ebo_buffer)
{
    glBindVertexArray(vao.id);
    vbo_update(vao.vbo, vbo_offset, vbo_length, vbo_buffer);
    if (vao.ebo != NULL)
        ebo_update(vao.ebo, ebo_offset, ebo_length, ebo_buffer);
}

void vao_malloc(VAO vao, u32 vbo_length, u32 ebo_length)
{
    glBindVertexArray(vao.id);
    vbo_malloc(vao.vbo, vbo_length, vao.usage);
    if (vao.ebo != NULL)
        ebo_malloc(vao.ebo, ebo_length, vao.usage);
}

void vao_draw(VAO vao)
{
    glBindVertexArray(vao.id);
    if (vao.ebo == NULL)
        glDrawArrays(vao.mode, 0, vao.vbo->length / vao.length);
    else
        glDrawElements(vao.mode, vao.ebo->length, GL_UNSIGNED_INT, 0);
}

void vao_destroy(VAO vao)
{
    vbo_destroy(vao.vbo);
    if (vao.ebo != NULL)
        ebo_destroy(vao.ebo);
    glDeleteVertexArrays(1, &vao.id);
}
