#include "vao.h"
#include <stdlib.h>
#include <stdio.h>

VAO vao_create(u32 index_count, u32 index_size, u32* indices)
{
    VAO vao;
    glGenVertexArrays(1, &vao.ID);
    glBindVertexArray(vao.ID);
    vao.vbo = vbo_create();
    vao.index_count = index_count;
    vao.index_size = index_size;
    vao.indices = malloc(index_count * sizeof(u32));
    for (u32 i = 0; i < index_count; i++)
        vao.indices[i] = indices[i];
    return vao;
}

void vao_update(VAO* vao, size_t buffer_size)
{
    vbo_update(&vao->vbo, buffer_size);
    for (u32 c = 0, i = 0; i < vao->index_count; c += vao->indices[i], i++) {
        glVertexAttribPointer(i, vao->indices[i], GL_FLOAT, GL_FALSE, vao->index_size * sizeof(f32), (void*)(c * sizeof(f32)));
        glEnableVertexAttribArray(i);
    }
}

void vao_draw(VAO vao)
{
    glDrawArrays(GL_TRIANGLES, 0, vao.vbo.buffer_size);
}

void vao_destroy(VAO vao)
{
    free(vao.indices);
}