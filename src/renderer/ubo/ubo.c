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

void ubo_bind_buffer_base(UBO ubo, u32 index)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, index, ubo.id);
}

void ubo_bind(UBO ubo)
{
    glBindBuffer(GL_UNIFORM_BUFFER, ubo.id);
}

void ubo_update(UBO ubo, size_t offset, size_t size, f32 *data)
{
    ubo_bind(ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void ubo_destroy(UBO ubo)
{
    glDeleteBuffers(1, &ubo.id);
}