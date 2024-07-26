#include "character.h"

Character char_map[128];

#define _CHAR_INIT(_c, _tex, _w, _h, _bx, _by) \
    char_map[_c].tex = _tex; \
    char_map[_c].size.x = _w; \
    char_map[_c].size.y = _h; \
    char_map[_c].bearing.x = _bx; \
    char_map[_c].bearing.y = _by; \
    char_map[_c].advance = 1;

void char_map_init(void)
{
    for (i32 i = 0; i < 128; i++) {
        _CHAR_INIT(i, EMPTY_TEX, 5, 5, 0, 0);
    }
    _CHAR_INIT(' ', NO_TEX,      1, 1, 0, 0)
    _CHAR_INIT('0', NUM_0_TEX,   5, 7, 0, 0)
    _CHAR_INIT('1', NUM_1_TEX,   5, 7, 0, 0)
    _CHAR_INIT('2', NUM_2_TEX,   5, 7, 0, 0)
    _CHAR_INIT('3', NUM_3_TEX,   5, 7, 0, 0)
    _CHAR_INIT('4', NUM_4_TEX,   5, 7, 0, 0)
    _CHAR_INIT('5', NUM_5_TEX,   5, 7, 0, 0)
    _CHAR_INIT('6', NUM_6_TEX,   5, 7, 0, 0)
    _CHAR_INIT('7', NUM_7_TEX,   5, 7, 0, 0)
    _CHAR_INIT('8', NUM_8_TEX,   5, 7, 0, 0)
    _CHAR_INIT('9', NUM_9_TEX,   5, 7, 0, 0)
    _CHAR_INIT('A', UPPER_A_TEX, 5, 7, 0, 0)
    _CHAR_INIT('B', UPPER_B_TEX, 5, 7, 0, 0)
    _CHAR_INIT('C', UPPER_C_TEX, 5, 7, 0, 0)
    _CHAR_INIT('D', UPPER_D_TEX, 5, 7, 0, 0)
    _CHAR_INIT('E', UPPER_E_TEX, 5, 7, 0, 0)
    _CHAR_INIT('F', UPPER_F_TEX, 5, 7, 0, 0)
    _CHAR_INIT('G', UPPER_G_TEX, 5, 7, 0, 0)
    _CHAR_INIT('H', UPPER_H_TEX, 5, 7, 0, 0)
    _CHAR_INIT('I', UPPER_I_TEX, 5, 7, 0, 0)
    _CHAR_INIT('J', UPPER_J_TEX, 5, 7, 0, 0)
    _CHAR_INIT('K', UPPER_K_TEX, 5, 7, 0, 0)
    _CHAR_INIT('L', UPPER_L_TEX, 5, 7, 0, 0)
    _CHAR_INIT('M', UPPER_M_TEX, 5, 7, 0, 0)
    _CHAR_INIT('N', UPPER_N_TEX, 5, 7, 0, 0)
    _CHAR_INIT('O', UPPER_O_TEX, 5, 7, 0, 0)
    _CHAR_INIT('P', UPPER_P_TEX, 5, 7, 0, 0)
    _CHAR_INIT('Q', UPPER_Q_TEX, 5, 7, 0, 0)
    _CHAR_INIT('R', UPPER_R_TEX, 5, 7, 0, 0)
    _CHAR_INIT('S', UPPER_S_TEX, 5, 7, 0, 0)
    _CHAR_INIT('T', UPPER_T_TEX, 5, 7, 0, 0)
    _CHAR_INIT('U', UPPER_U_TEX, 5, 7, 0, 0)
    _CHAR_INIT('V', UPPER_V_TEX, 5, 7, 0, 0)
    _CHAR_INIT('W', UPPER_W_TEX, 5, 7, 0, 0)
    _CHAR_INIT('X', UPPER_X_TEX, 5, 7, 0, 0)
    _CHAR_INIT('Y', UPPER_Y_TEX, 5, 7, 0, 0)
    _CHAR_INIT('Z', UPPER_Z_TEX, 5, 7, 0, 0)
}