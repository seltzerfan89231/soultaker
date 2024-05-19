#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad.h>
#include <glfw.h>
#include <stb_image.h>
#include "../../util/type.h"

typedef struct {
    u32 id;
} Texture;

Texture texture_create(const char* image_path);
void texture_bind(Texture texture, u32 binding);
void texture_destroy(Texture texture);

#endif