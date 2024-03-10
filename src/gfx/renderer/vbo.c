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
    vbo.buffer = NULL;
    return vbo;
}

void vbo_update(VBO* vbo, size_t buffer_size)
{
    vbo->buffer_size = buffer_size;
    glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
    glBufferData(GL_ARRAY_BUFFER, vbo->buffer_size, vbo->buffer, GL_STATIC_DRAW);
}
