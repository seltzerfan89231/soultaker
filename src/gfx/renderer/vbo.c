#include "vbo.h"
#include <stdlib.h>

VBO vbo_create(void)
{
    VBO vbo;
    glGenBuffers(1, &vbo.ID);
    vbo.data_size = 0;
    vbo.data = malloc(0);
    return vbo;
}

void vbo_update(VBO* vbo, size_t data_size, f32* data)
{
    free(vbo->data);
    vbo->data_size = data_size;
    vbo->data = data;
    glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
    glBufferData(GL_ARRAY_BUFFER, vbo->data_size, vbo->data, GL_STATIC_DRAW);
}

void vbo_destroy(VBO vbo)
{
    free(vbo.data);
}
