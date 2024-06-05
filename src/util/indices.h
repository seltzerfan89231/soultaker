#ifndef INDICES_H
#define INDICES_H

#pragma region UBOS
#define NUM_UBOS         6
#define MATRICES_UBO     0
#define ZOOM_UBO         1
#define ASPECT_RATIO_UBO 2
#define ROTATION_UBO     3
#define TILT_UBO         4
#define CONSTANTS_UBO    5
#pragma endregion

#pragma region SSBOS
#define NUM_SSBOS    1
#define TEXTURE_SSBO 0
#pragma endregion

#pragma region SHADERS
#define NUM_SHADERS       11
#define TILE_SHADER       0
#define WALL_SHADER       1
#define ENTITY_SHADER     2
#define PROJECTILE_SHADER 3
#define GUI_SHADER        4
#define SHADOW_SHADER     5
#define HEALTHBAR_SHADER  6
#define PARTICLE_SHADER   7
#define OBSTACLE_SHADER   8
#define PARJICLE_SHADER   9
#define PARSTACLE_SHADER  10
#pragma endregion

#pragma region VAOS
#define NUM_VAOS       9
#define TILE_VAO       0
#define WALL_VAO       1
#define ENTITY_VAO     2
#define PROJECTILE_VAO 3
#define GUI_VAO        4
#define PARTICLE_VAO   5
#define OBSTACLE_VAO   6
#define PARJICLE_VAO   7
#define PARSTACLE_VAO  8
#pragma endregion

#pragma region TEXTURES
#define NUM_TEXTURES 5
#define KNIGHT_TEX   0
#define BULLET_TEX   1
#define TILE_TEX     2
#define WALL_TOP_TEX 3
#define WALL_TEX     4
#pragma endregion

#endif