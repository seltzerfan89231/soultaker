#ifndef INDICES_H
#define INDICES_H

#define DOWN  0
#define RIGHT 1
#define UP    2
#define LEFT  3

#pragma region UBOS
#define NUM_UBOS         7
#define MATRICES_UBO     0
#define ZOOM_UBO         1
#define ASPECT_RATIO_UBO 2
#define ROTATION_UBO     3
#define TILT_UBO         4
#define CONSTANTS_UBO    5
#define OUTLINE_UBO      6
#pragma endregion





#pragma region SSBOS
#define NUM_SSBOS 2
#define GAME_SSBO 0
#define GUI_SSBO  1
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





#pragma region GAME_TEXTURES
#define NUM_GAME_TEXTURES 25
#define BULLET_TEX        0
#define TILE_TEX          1
#define WALL_TOP_TEX      2
#define WALL_SIDE_TEX     3
#define BUSH_TEX          4
#define ROCK_TEX          5
#define KNIGHT_IDLE_DOWN_TEX   6
#define KNIGHT_IDLE_RIGHT_TEX  7
#define KNIGHT_IDLE_UP_TEX     8
#define KNIGHT_IDLE_LEFT_TEX   9
#define KNIGHT_SHOOT_LEFT_1_TEX 10
#define KNIGHT_SHOOT_RIGHT_1_TEX 11
#define KNIGHT_SHOOT_DOWN_1_TEX 12
#define KNIGHT_SHOOT_UP_1_TEX 13
#define KNIGHT_WALK_DOWN_1_TEX 14
#define KNIGHT_WALK_RIGHT_TEX 15
#define KNIGHT_WALK_UP_1_TEX 16
#define KNIGHT_WALK_LEFT_TEX 17
#define KNIGHT_WALK_DOWN_2_TEX 18
#define KNIGHT_WALK_UP_2_TEX 19
#define KNIGHT_SHOOT_LEFT_2_TEX 20
#define KNIGHT_SHOOT_RIGHT_2_TEX 21
#define KNIGHT_SHOOT_DOWN_2_TEX 22
#define KNIGHT_SHOOT_UP_2_TEX 23
#define BULLET_2_TEX 24
#pragma endregion





#pragma region GUI_TEXTURES
#define NUM_GUI_TEXTURES 41
#define NO_TEX           0
#define EMPTY_TEX        1
#define BUTTON_TEX       2
#define SWORD_1_TEX 3
#define SWORD_2_TEX 4
#define A_TEX 5
#define B_TEX 6
#define C_TEX 7
#define D_TEX 8
#define E_TEX 9
#define F_TEX 10
#define G_TEX 11
#define H_TEX 12
#define I_TEX 13
#define J_TEX 14
#define K_TEX 15
#define L_TEX 16
#define M_TEX 17
#define N_TEX 18
#define O_TEX 19
#define P_TEX 20
#define Q_TEX 21
#define R_TEX 22
#define S_TEX 23
#define T_TEX 24
#define U_TEX 25
#define V_TEX 26
#define W_TEX 27
#define X_TEX 28
#define Y_TEX 29
#define Z_TEX 30
#define NUM_0_TEX 31
#define NUM_1_TEX 32
#define NUM_2_TEX 33
#define NUM_3_TEX 34
#define NUM_4_TEX 35
#define NUM_5_TEX 36
#define NUM_6_TEX 37
#define NUM_7_TEX 38
#define NUM_8_TEX 39
#define NUM_9_TEX 40
#pragma endregion

#endif