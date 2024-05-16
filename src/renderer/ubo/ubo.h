#ifndef UBO_H
#define UBO_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

typedef struct {
    u32 id;
} UBO;

UBO ubo_create(size_t size);

#endif