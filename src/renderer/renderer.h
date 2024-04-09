#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>
#include "../util/vertex_data.h"
#include "vao/vao.h"
#include "shader/shader.h"
#include "texture/texture.h"

#define NUM_SAMPLES 4

typedef enum buffertype { TILE, GUI } buffertype;

typedef struct Renderer {
    VAO vaos[2];
    Shader shaders[2];
    GLenum usage[2];
    Texture spritesheet;
} Renderer;

extern Renderer renderer;

void renderer_init(void);
void renderer_malloc(buffertype type, u32 length);
void renderer_update(buffertype type, u32 offset, u32 length, f32* buffer);
void renderer_render(void);
void renderer_destroy(void);

u32 renderer_uniform_location(buffertype type, char* identifier);

#endif