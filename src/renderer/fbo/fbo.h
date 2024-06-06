#ifndef FBO_H
#define FBO_H

#include <glad.h>
#include "../../util/type.h"

typedef struct {
    u32 id;
} FBO;

FBO fbo_create(void);
void fbo_destroy(FBO fbo);

#endif