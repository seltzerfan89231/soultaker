#include "vbo.h"
#include <stdlib.h>

VBO vbo_create(GLenum type)
{
    VBO vbo;
    glGenBuffers(1, &vbo.ID);
    vbo.type = type;
    vbo.data_size = 0;
    vbo.data = malloc(0);
    return vbo;
}

void vbo_update(VBO* vbo, size_t data_size, void* data)
{
    free(vbo->data);
    vbo->data_size = data_size;
    vbo->data = data;
    glBindBuffer(vbo->type, vbo->ID);
    glBufferData(vbo->type, vbo->data_size, vbo->data, GL_STATIC_DRAW);
}

void vbo_destroy(VBO vbo)
{
    free(vbo.data);
}
