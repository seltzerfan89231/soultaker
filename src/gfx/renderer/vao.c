#include "vao.h"
#include <stdlib.h>
#include <stdio.h>

VAO vao_create(u32 index_count, u32 index_size, u32* indices)
{
    VAO vao;
    glGenVertexArrays(1, &vao.ID);
    glBindVertexArray(vao.ID);
    vao.vbo = vbo_create();
    for (u32 c = 0, i = 0; i < index_count; c += indices[i], i++) {
        glVertexAttribPointer(i, indices[i], GL_FLOAT, GL_FALSE, index_size * sizeof(f32), (void*)(c * sizeof(f32)));
        glEnableVertexAttribArray(i);
    }
    return vao;
}

void vao_update(VAO* vao, u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length)
{
    vbo_update(&vao->vbo, offset, subdata_size, subdata, buffer_length);
    
}

void vao_draw(VAO vao)
{
    glDrawArrays(GL_TRIANGLES, 0, vao.vbo.buffer_length / 6);
}

void vao_destroy(VAO vao)
{
    vbo_destroy(vao.vbo);
    glDeleteVertexArrays(1, &vao.ID);
}