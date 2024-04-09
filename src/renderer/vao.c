#include "vao.h"

VAO vao_create(void)
{
    VAO vao;
    glGenVertexArrays(1, &vao.id);
    vao_bind(vao);
    vao.vbo = vbo_create();
    vao.length = 0;
    return vao;
}

void vao_attr(VAO* vao, u32 index, u32 length, u32 stride, u32 offset)
{
    vao_bind(*vao);
    vao->length = stride;
    glVertexAttribPointer(index, length, GL_FLOAT, GL_FALSE, stride * sizeof(f32), (void*)(offset * sizeof(f32)));
    glEnableVertexAttribArray(index);
}

void vao_update(VAO* vao, u32 length, f32* buffer)
{
    vao_bind(*vao);
    vbo_update(&vao->vbo, length, buffer);
}

void vao_malloc(VAO* vao, u32 length, GLenum usage)
{
    vao_bind(*vao);
    vbo_malloc(&vao->vbo, length, usage);
}

void vao_draw(VAO vao)
{
    vao_bind(vao);
    glDrawArrays(GL_TRIANGLES, 0, vao.vbo.length / vao.length);
}

void vao_bind(VAO vao)
{
    glBindVertexArray(vao.id);
}

void vao_destroy(VAO vao)
{
    vbo_destroy(vao.vbo);
    glDeleteVertexArrays(1, &vao.id);
}
