#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>
#include <stb_image.h>

typedef struct Texture {
    u32 ID;
} Texture;

Texture texture_create(const char* image_path);
void texture_bind(Texture texture);

#endif