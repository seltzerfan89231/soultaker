#include "vao.h"
#include <stdlib.h>
#include <stdio.h>

VAO vao_create(u32 index_count, u32 index_size, u32* indices)
{
    VAO vao;
    glGenVertexArrays(1, &vao.ID);
    vao.vbo = vbo_create(GL_ARRAY_BUFFER);
    vao.ebo = vbo_create(GL_ELEMENT_ARRAY_BUFFER);
    vao.index_count = index_count;
    vao.index_size = index_size;
    vao.indices = malloc(index_count * sizeof(int));
    for (u32 i = 0; i < index_count; i++)
        vao.indices[i] = indices[i]; 
    return vao;
}

void vao_bind(VAO vao)
{
    glBindVertexArray(vao.ID);
}

void vao_update(VAO vao, GLenum type, u32 size, void* data)
{
    vao_bind(vao);
    u32 type_size = type == GL_ARRAY_BUFFER ? sizeof(f32) : sizeof(u32);
    if (type == GL_ARRAY_BUFFER)
        vbo_update(&vao.vbo, size, data);
    else if (type == GL_ELEMENT_ARRAY_BUFFER)
        vbo_update(&vao.ebo, size, data);
    for (u32 c = 0, i = 0; i < vao.index_count; c += vao.indices[i], i++) {
        u32 offset = c * type_size;
        void* offset_ptr = &offset;
        printf("%d, %d, %d, %d\n", i, vao.indices[i], vao.index_size, c);
        glVertexAttribPointer(i, vao.indices[i], GL_FLOAT, GL_FALSE, vao.index_size * type_size, offset_ptr);
        glEnableVertexAttribArray(i);
    }
}

void vao_destroy(VAO vao)
{
    free(vao.indices);
    vbo_destroy(vao.vbo);
    vbo_destroy(vao.ebo);
}