#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>
#include "../util/vec.h"
#include "vao/vao.h"
#include "shader/shader.h"
#include "texture/texture.h"
#include "ubo/ubo.h"

#define NUM_SAMPLES 4
#define MAX_BUFFER_LENGTH 1000000
#define NUM_BUFFER_TYPES 5
#define NUM_UBO_TYPES 6

typedef enum ubotype { MATRICES, ZOOM, ASPECT_RATIO, ROTATION, TILT, CONSTANTS } ubotype;
typedef enum buffertype { TILE, ENTITY, PROJECTILE, GUIB } buffertype;

typedef struct {
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
void renderer_uniform_update_view(f32 *mat);
void renderer_uniform_update_proj(f32 *mat);
void renderer_uniform_update_zoom(f32 zoom);
void renderer_uniform_update_rotation(f32 rotation);
void renderer_uniform_update_tilt(f32 tilt);
void renderer_uniform_update_aspect_ratio(f32 ar);

#endif