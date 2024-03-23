#include "vbo.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

VBO vbo_create(void)
{
    VBO vbo;
    glGenBuffers(1, &vbo.ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
    vbo.buffer_size = 0;
    vbo.buffer = malloc(10000000 * sizeof(f32));
    glBufferData(GL_ARRAY_BUFFER, 10000000 * sizeof(f32), vbo.buffer, GL_DYNAMIC_DRAW);
    return vbo;
}

void vbo_update(VBO* vbo, u32 offset, size_t buffer_size, f32* buffer)
{
    vbo->buffer_size = buffer_size;
    glBufferSubData(GL_ARRAY_BUFFER, offset, buffer_size, buffer);
}

void vbo_destroy(VBO vbo)
{
    glDeleteBuffers(1, &vbo.ID);
}