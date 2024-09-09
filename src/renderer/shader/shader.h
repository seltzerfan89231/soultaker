#ifndef SHADER_H
#define SHADER_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

#define NUM_SHADERS           16
#define TILE_SHADER           0 
#define WALL_SHADER           1
#define ENTITY_SHADER         2
#define PROJECTILE_SHADER     3
#define GUI_SHADER            4 
#define SHADOW_SHADER         5
#define HEALTHBAR_SHADER      6
#define PARTICLE_SHADER       7
#define OBSTACLE_SHADER       8
#define PARJICLE_SHADER       9
#define PARSTACLE_SHADER      10
#define TILE_SHADOW_SHADER    11
#define SCREEN_SHADER         12
#define MINIMAP_ENTITY_SHADER 13
#define MINIMAP_TILE_SHADER   14
#define MINIMAP_WALL_SHADER   15

typedef struct {
    u32 id;
} Shader;

Shader shader_create(char* vs_path, char* fs_path, char* gs_path);
void shader_bind_uniform_block(Shader shader, u32 index, char* identifier);
void shader_use(Shader shader);
void shader_destroy(Shader shader);

#endif