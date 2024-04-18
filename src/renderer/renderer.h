#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>
#include "../util/buffertype.h"
#include "vao/vao.h"
#include "shader/shader.h"
#include "texture/texture.h"

#define NUM_SAMPLES 4

typedef struct Renderer {
    VAO *vaos;
    Shader *shaders;
    Texture atlas;
} Renderer;

extern Renderer renderer;

void renderer_init(void);
void renderer_malloc(buffertype type, u32 length);
void renderer_update(buffertype type, u32 offset, u32 length, f32* buffer);
void renderer_render(void);
void renderer_destroy(void);
void renderer_uniform_update_texture(buffertype type, char* identifier, Texture texture);
void renderer_uniform_update_matrix(buffertype type, char* identifier, f32* mat4);
void renderer_uniform_update_float(buffertype type, char* identifier, f32 flt);

#endif