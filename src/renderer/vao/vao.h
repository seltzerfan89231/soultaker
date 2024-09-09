#ifndef VAO_H
#define VAO_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"
#include "../vbo/vbo.h"
#include "../ebo/ebo.h"

#define NUM_VAOS       10
#define TILE_VAO       0
#define WALL_VAO       1
#define ENTITY_VAO     2
#define PROJECTILE_VAO 3
#define GUI_VAO        4
#define PARTICLE_VAO   5
#define OBSTACLE_VAO   6
#define PARJICLE_VAO   7
#define PARSTACLE_VAO  8
#define QUAD_VAO       9

typedef struct {
    u32 id, length;
    GLenum usage, mode;
    VBO *vbo;
    EBO *ebo;
} VAO;

VAO vao_create(GLenum usage, GLenum mode, u32 length, bool use_ebo);
void vao_attr(VAO vao, u32 index, u32 length, u32 offset);
void vao_update(VAO vao, u32 vbo_offset, u32 vbo_length, f32* vbo_buffer, u32 ebo_offset, u32 ebo_length, u32* ebo_buffer);
void vao_malloc(VAO vao, u32 vbo_length, u32 ebo_length);
void vao_draw(VAO vao);
void vao_destroy(VAO vao);

#endif