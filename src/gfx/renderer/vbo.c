#include "vbo.h"
#include <stdlib.h>

VBO vbo_create(GLenum type)
{
    VBO vbo;
    glGenBuffers(1, &vbo.ID);
    vbo.type = type;
    vbo.size = 0;
    vbo.data = malloc(0);
    return vbo;
}

void vbo_update(VBO* vbo, u32 size, void* data)
{
    vbo->size = size;
    free(vbo->data);
    vbo->data = data;
    glBindBuffer(vbo->type, vbo->ID);
    glBufferData(vbo->type, vbo->size, vbo->data, GL_STATIC_DRAW);
}

void vbo_bind(VBO vbo)
{
    glBindBuffer(vbo.type, vbo.ID);
}

void vbo_buffer(VBO vbo)
{
    glBufferData(vbo.type, vbo.size, vbo.data, GL_STATIC_DRAW);
}

void vbo_destroy(VBO vbo)
{
    free(vbo.data);
}
