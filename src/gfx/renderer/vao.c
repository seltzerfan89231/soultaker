#include "vao.h"
#include <stdlib.h>
#include <stdio.h>

VAO vao_create(buffertype type)
{
    VAO vao;
    glGenVertexArrays(1, &vao.ID);
    glBindVertexArray(vao.ID);
    vao.vbo = vbo_create(type);
    if (type == DRAWABLE) {
        vao.vertex_length = 5;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(0));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
    } else if (type == GUI) {
        vao.vertex_length = 5;
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(0));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(2 * sizeof(f32)));
    }
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    return vao;
}

void vao_update(VAO* vao, u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length)
{
    vbo_update(&vao->vbo, offset, subdata_size, subdata, buffer_length);
}

void vao_draw(VAO vao)
{
    glDrawArrays(GL_TRIANGLES, 0, vao.vbo.buffer_length / vao.vertex_length);
}

void vao_bind(VAO vao)
{
    glBindVertexArray(vao.ID);
}

void vao_destroy(VAO vao)
{
    vbo_destroy(vao.vbo);
    glDeleteVertexArrays(1, &vao.ID);
}
