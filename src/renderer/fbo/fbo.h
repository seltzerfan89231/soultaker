#ifndef FBO_H
#define FBO_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

typedef struct {
    u32 id;
} FBO;

FBO fbo_create(void);
void fbo_bind(FBO fbo);
void fbo_destroy(FBO fbo);

#endif