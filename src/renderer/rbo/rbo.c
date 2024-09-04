#include "rbo.h"
#include <stdio.h>

RBO rbo_create(u32 width, u32 height)
{
    RBO rbo;
    glGenRenderbuffers(1, &rbo.id);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo.id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    return rbo;
}

void rbo_bind(RBO rbo)
{
    glBindRenderbuffer(GL_RENDERBUFFER, rbo.id);
}

void rbo_bind_default(void)
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void rbo_destroy(RBO rbo)
{
    glDeleteRenderbuffers(1, &rbo.id);
}