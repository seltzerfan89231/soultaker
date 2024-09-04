#include "fbo.h"
#include <stdio.h>

FBO fbo_create(u32 width, u32 height)
{
    FBO fbo;
    glGenFramebuffers(1, &fbo.id);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo.id);
    glGenTextures(1, &fbo.color_buffer_id);
    glBindTexture(GL_TEXTURE_2D, fbo.color_buffer_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo.color_buffer_id, 0);
    return fbo;
}

void fbo_bind(FBO fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo.id);
}

void fbo_bind_color_buffer(FBO fbo)
{
    glBindTexture(GL_TEXTURE_2D, fbo.color_buffer_id);
}

void fbo_bind_default(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void fbo_attach_rbo(FBO fbo, RBO rbo)
{
    fbo_bind(fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo.id);
}

bool fbo_check_status(FBO fbo)
{
    fbo_bind(fbo);
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void fbo_destroy(FBO fbo)
{
    glDeleteTextures(1, &fbo.color_buffer_id);
    glDeleteFramebuffers(1, &fbo.id);
}