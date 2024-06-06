#include "fbo.h"

FBO fbo_create(void)
{
    FBO fbo;
    glGenFramebuffers(1, &fbo.id);
    return fbo;
}

void fbo_destroy(FBO fbo)
{
    glDeleteFramebuffers(1, &fbo.id);
}