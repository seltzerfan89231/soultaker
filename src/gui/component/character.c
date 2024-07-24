#include "character.h"

Character char_map[128];

void char_map_init(void)
{
    for (i32 i = 0; i < 128; i++) {
        char_map[i].tex = EMPTY_TEX;
        char_map[i].width = 5;
        char_map[i].height = 5;
    }
    char_map[' '].tex = NO_TEX;
    char_map['0'].tex = NUM_0_TEX;
    char_map['1'].tex = NUM_1_TEX;
    char_map['2'].tex = NUM_2_TEX;
    char_map['3'].tex = NUM_3_TEX;
    char_map['4'].tex = NUM_4_TEX;
    char_map['5'].tex = NUM_5_TEX;
    char_map['6'].tex = NUM_6_TEX;
    char_map['7'].tex = NUM_7_TEX;
    char_map['8'].tex = NUM_8_TEX;
    char_map['9'].tex = NUM_9_TEX;
    char_map['A'].tex = A_TEX;
    char_map['B'].tex = B_TEX;
    char_map['C'].tex = C_TEX;
    char_map['D'].tex = D_TEX;
    char_map['E'].tex = E_TEX;
    char_map['F'].tex = F_TEX;
    char_map['G'].tex = G_TEX;
    char_map['H'].tex = H_TEX;
    char_map['I'].tex = I_TEX;
    char_map['J'].tex = J_TEX;
    char_map['K'].tex = K_TEX;
    char_map['L'].tex = L_TEX;
    char_map['M'].tex = M_TEX;
    char_map['N'].tex = N_TEX;
    char_map['O'].tex = O_TEX;
    char_map['P'].tex = P_TEX;
    char_map['P'].width = 4;
    char_map['Q'].tex = Q_TEX;
    char_map['R'].tex = R_TEX;
    char_map['S'].tex = S_TEX;
    char_map['T'].tex = T_TEX;
    char_map['U'].tex = U_TEX;
    char_map['V'].tex = V_TEX;
    char_map['W'].tex = W_TEX;
    char_map['X'].tex = X_TEX;
    char_map['Y'].tex = Y_TEX;
    char_map['Z'].tex = Z_TEX;
    for (i32 i = 0; i < 128; i++)
        char_map[i].tex = F_TEX;
    char_map['P'].tex = P_TEX;
    char_map['P'].width = 4;
    char_map['P'].bearingX = 2;
    char_map['P'].bearingY = 2;
}