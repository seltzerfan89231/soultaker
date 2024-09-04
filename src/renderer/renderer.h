#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>
#include "../window/window.h"
#include "../util/indices.h"
#include "../util/vec.h"
#include "../util/constants.h"
#include "vao/vao.h"
#include "shader/shader.h"
#include "texture/texture.h"
#include "ubo/ubo.h"
#include "ssbo/ssbo.h"
#include "fbo/fbo.h"

typedef struct {
    VAO *vaos;
    Shader *shaders;
    UBO *ubos;
    SSBO *ssbos;
    Texture *game_textures;
    Texture *gui_textures;
    FBO fbo, fbo2, fbo3;
    RBO rbo;
} Renderer;

extern Renderer renderer;

void renderer_init(void);
void renderer_malloc(u32 vao_index, u32 vbo_length, u32 ebo_length);
void renderer_update(u32 vao_index, u32 vbo_offset, u32 vbo_length, f32* vbo_buffer, u32 ebo_offset, u32 ebo_length, u32* ebo_buffer);
void renderer_render(void);
void renderer_destroy(void);

void renderer_uniform_update_view(f32 *mat);
void renderer_uniform_update_proj(f32 *mat);
void renderer_uniform_update_zoom(f32 zoom);
void renderer_uniform_update_rotation(f32 rotation);
void renderer_uniform_update_tilt(f32 tilt);
void renderer_uniform_update_game_time(f32 game_time);
void renderer_uniform_update_aspect_ratio(f32 ar);
void renderer_uniform_update_minimap(f32 x, f32 z, f32 zoom);

#endif