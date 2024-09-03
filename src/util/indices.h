#ifndef INDICES_H
#define INDICES_H

#define DOWN   0
#define RIGHT  1
#define UP     2
#define LEFT   3
#define TOP    4
#define BOTTOM 5

#pragma region UBOS
#define NUM_UBOS         8
#define MATRICES_UBO     0
#define ZOOM_UBO         1
#define ASPECT_RATIO_UBO 2
#define ROTATION_UBO     3
#define TILT_UBO         4
#define CONSTANTS_UBO    5
#define OUTLINE_UBO      6
#define GAME_TIME_UBO    7
#pragma endregion





#pragma region SSBOS
#define NUM_SSBOS 2
#define GAME_SSBO 0
#define GUI_SSBO  1
#pragma endregion





#pragma region SHADERS
#define NUM_SHADERS         13
#define TILE_SHADER         0 
#define WALL_SHADER         1
#define ENTITY_SHADER       2
#define PROJECTILE_SHADER   3
#define GUI_SHADER          4 
#define SHADOW_SHADER       5
#define HEALTHBAR_SHADER    6
#define PARTICLE_SHADER     7
#define OBSTACLE_SHADER     8
#define PARJICLE_SHADER     9
#define PARSTACLE_SHADER    10
#define TILE_SHADOW_SHADER  11
#define SCREEN_SHADER       12
#pragma endregion





#pragma region VAOS
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
#pragma endregion





#pragma region GAME_TEXTURES
#define NUM_GAME_TEXTURES 41
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
#define TRAINING_DUMMY_TEX 31
#define SHAITAN_LAVA_TEX 32
#define SHAITAN_FLOOR_1_TEX 33
#define SHAITAN_FLOOR_2_TEX 34
#define SHAITAN_WALL_SIDE_TEX 35
#define SHAITAN_WALL_TOP_TEX 36
#define SHAITAN_BARS_SIDE_TEX 37
#define SHAITAN_BARS_TOP_TEX 38
#define SHAITAN_HELLSTONE_TEX 39
#define GAME_NO_TEX 40
#pragma endregion





#pragma region GUI_TEXTURES
#define NUM_GUI_TEXTURES 100
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
#define FORWARDSLASH_TEX 42
#define LOWER_A_TEX 43
#define LOWER_B_TEX 44
#define LOWER_C_TEX 45
#define LOWER_D_TEX 46
#define LOWER_E_TEX 47
#define LOWER_F_TEX 48
#define LOWER_G_TEX 49
#define LOWER_H_TEX 50
#define LOWER_I_TEX 51
#define LOWER_J_TEX 52
#define LOWER_K_TEX 53
#define LOWER_L_TEX 54
#define LOWER_M_TEX 55
#define LOWER_N_TEX 56
#define LOWER_O_TEX 57
#define LOWER_P_TEX 58
#define LOWER_Q_TEX 59
#define LOWER_R_TEX 60
#define LOWER_S_TEX 61
#define LOWER_T_TEX 62
#define LOWER_U_TEX 63
#define LOWER_V_TEX 64
#define LOWER_W_TEX 65
#define LOWER_X_TEX 66
#define LOWER_Y_TEX 67
#define LOWER_Z_TEX 68
#define AMPERSAND_TEX 69
#define APOSTROPHE_TEX 70
#define ASTERISK_TEX 71
#define AT_TEX 72
#define BACKSLASH_TEX 73
#define COLON_TEX 74
#define COMMA_TEX 75
#define DOLLAR_TEX 76
#define EQUALS_TEX 77
#define EXCLAMATIONMARK_TEX 78
#define GREATERTHAN_TEX 79
#define HASH_TEX 80
#define LEFTCURLYBRACKET_TEX 81
#define LEFTPARENTHESES_TEX 82
#define LEFTSQUAREBRACKET_TEX 83
#define LESSTHAN_TEX 84
#define MINUS_TEX 85
#define PERCENT_TEX 86
#define PERIOD_TEX 87
#define PIPE_TEX 88
#define PLUS_TEX 89
#define QUESTIONMARK_TEX 90
#define QUOTE_TEX 91
#define RIGHTCURLYBRACKET_TEX 92
#define RIGHTPARENTHESES_TEX 93
#define RIGHTSQUAREBRACKET_TEX 94
#define SEMICOLON_TEX 95
#define UNDERSCORE_TEX 96
#define BACKTICK_TEX 97
#define CARROT_TEX 98
#define TILDE_TEX 99
#pragma endregion





#pragma region AUDIO_BUFFERS
#define NUM_BUFFERS 2
#define GUI_CLICK_AUD 0

#endif