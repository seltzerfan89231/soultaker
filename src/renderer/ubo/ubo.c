#include "ubo.h"
#include <stdio.h>

UBO ubo_create(size_t size)
{
    UBO ubo;
    glGenBuffers(1, &ubo.id);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo.id);
    glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
    return ubo;
}