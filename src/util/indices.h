#ifndef INDICES_H
#define INDICES_H

#define NUM_UBOS         6
#define MATRICES_UBO     0
#define ZOOM_UBO         1
#define ASPECT_RATIO_UBO 2
#define ROTATION_UBO     3
#define TILT_UBO         4
#define CONSTANTS_UBO    5

#define NUM_SSBOS    1
#define TEXTURE_SSBO 0

#define NUM_SHADERS       7
#define TILE_SHADER       0
#define WALL_SHADER       1
#define ENTITY_SHADER     2
#define PROJECTILE_SHADER 3
#define GUI_SHADER        4
#define SHADOW_SHADER     5
#define HEALTHBAR_SHADER  6

#define NUM_VAOS       5
#define TILE_VAO       0
#define WALL_VAO       1
#define ENTITY_VAO     2
#define PROJECTILE_VAO 3
#define GUI_VAO        4

#define NUM_TEXTURES 5
#define KNIGHT_TEX   0
#define BULLET_TEX   1
#define TILE_TEX     2
#define WALL_TOP_TEX 3
#define WALL_TEX     4

#endif