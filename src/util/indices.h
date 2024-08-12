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
#define NUM_GAME_TEXTURES 31
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
#define GRASS_1_TEX 25
#define GRASS_2_TEX 26
#define GRASS_3_TEX 27
#define HELLSTONE_TEX 28
#define SLIME_TEX 29
#define GRAVESTONE_TEX 30
#pragma endregion





#pragma region GUI_TEXTURES
#define NUM_GUI_TEXTURES 42
#define NO_TEX           0
#define EMPTY_TEX        1
#define BUTTON_TEX       2
#define SWORD_1_TEX 3
#define SWORD_2_TEX 4
#define UPPER_A_TEX 5
#define UPPER_B_TEX 6
#define UPPER_C_TEX 7
#define UPPER_D_TEX 8
#define UPPER_E_TEX 9
#define UPPER_F_TEX 10
#define UPPER_G_TEX 11
#define UPPER_H_TEX 12
#define UPPER_I_TEX 13
#define UPPER_J_TEX 14
#define UPPER_K_TEX 15
#define UPPER_L_TEX 16
#define UPPER_M_TEX 17
#define UPPER_N_TEX 18
#define UPPER_O_TEX 19
#define UPPER_P_TEX 20
#define UPPER_Q_TEX 21
#define UPPER_R_TEX 22
#define UPPER_S_TEX 23
#define UPPER_T_TEX 24
#define UPPER_U_TEX 25
#define UPPER_V_TEX 26
#define UPPER_W_TEX 27
#define UPPER_X_TEX 28
#define UPPER_Y_TEX 29
#define UPPER_Z_TEX 30
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
#define SOULTAKER_LOGO_TEX 41
#pragma endregion

#endif