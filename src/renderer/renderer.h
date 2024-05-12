#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>
#include "../util/buffertype.h"
#include "../util/vec.h"
#include "vao/vao.h"
#include "shader/shader.h"
#include "texture/texture.h"
#include "ubo/ubo.h"

#define NUM_SAMPLES 4

typedef struct Renderer {
    VAO *vaos;
    Shader* shaders;
    UBO *ubos;
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
void renderer_uniform_update_vec3(buffertype type, char* identifier, vec3f vec);

void renderer_uniform_update_view(f32 *mat);
void renderer_uniform_update_proj(f32 *mat);

#endif