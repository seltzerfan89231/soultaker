#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad.h>
#include <glfw.h>
#include <stb_image.h>
#include "../../util/type.h"

#define NUM_SAMPLES 4

typedef struct {
    u32 id;
    u64 handle;
} Texture;

Texture texture_create(const char* image_path);
void texture_destroy(Texture texture);

#endif