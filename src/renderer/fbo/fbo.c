#include "fbo.h"

FBO fbo_create(void)
{
    FBO fbo;
    glGenFramebuffers(1, &fbo.id);
}

void fbo_bind(FBO fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo.id);
}

void fbo_destroy(FBO fbo)
{
    glDeleteBuffers(1, &fbo.id);
}