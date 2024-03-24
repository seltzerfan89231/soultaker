#include "vbo.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

VBO vbo_create(void)
{
    VBO vbo;
    glGenBuffers(1, &vbo.ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
    vbo.buffer_length = 0;
    vbo.buffer = malloc(MAX_BUFFER_LENGTH * sizeof(f32));
    glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_LENGTH * sizeof(f32), vbo.buffer, GL_DYNAMIC_DRAW);
    return vbo;
}

void vbo_update(VBO* vbo, u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length)
{
    assert(buffer_length < MAX_BUFFER_LENGTH);
    vbo->buffer_length = buffer_length;
    glBufferSubData(GL_ARRAY_BUFFER, offset, subdata_size, subdata);
}

void vbo_destroy(VBO vbo)
{
    glDeleteBuffers(1, &vbo.ID);
}