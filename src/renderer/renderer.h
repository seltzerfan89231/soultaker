#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>
#include "../util/indices.h"
#include "../util/vec.h"
#include "../util/constants.h"
#include "vao/vao.h"
#include "shader/shader.h"
#include "texture/texture.h"
#include "ubo/ubo.h"
#include "ssbo/ssbo.h"
#include "fbo/fbo.h"

#define MAX_BUFFER_LENGTH 1000000

typedef struct {
    VAO *vaos;
    Shader *shaders;
    UBO *ubos;
    SSBO *ssbos;
    FBO fbo;
    Texture *textures;
} Renderer;

extern Renderer renderer;

void renderer_init(void);
void renderer_malloc(u32 vao_index, u32 length);
void renderer_update(u32 vao_index, u32 offset, u32 length, f32* buffer);
void renderer_render(void);
void renderer_destroy(void);

void renderer_uniform_update_view(f32 *mat);
void renderer_uniform_update_proj(f32 *mat);
void renderer_uniform_update_zoom(f32 zoom);
void renderer_uniform_update_rotation(f32 rotation);
void renderer_uniform_update_tilt(f32 tilt);
void renderer_uniform_update_aspect_ratio(f32 ar);

#endif