#include "ssbo.h"

SSBO ssbo_create(size_t size)
{
    SSBO ssbo;
    glGenBuffers(1, &ssbo.id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo.id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_STATIC_DRAW);
    return ssbo;
}

void ssbo_destroy(SSBO ssbo)
{
    glDeleteBuffers(1, &ssbo.id);
}