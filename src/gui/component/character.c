#include "character.h"

char char_map[128];

void char_map_init(void)
{
    for (i32 i = 0; i < 128; i++)
        char_map[i] = EMPTY_TEX;
    char_map[' '] = NO_TEX;
    char_map['0'] = NUM_0_TEX;
    char_map['1'] = NUM_1_TEX;
    char_map['2'] = NUM_2_TEX;
    char_map['3'] = NUM_3_TEX;
    char_map['4'] = NUM_4_TEX;
    char_map['5'] = NUM_5_TEX;
    char_map['6'] = NUM_6_TEX;
    char_map['7'] = NUM_7_TEX;
    char_map['8'] = NUM_8_TEX;
    char_map['9'] = NUM_9_TEX;
    char_map['A'] = A_TEX;
    char_map['B'] = B_TEX;
    char_map['C'] = C_TEX;
    char_map['D'] = D_TEX;
    char_map['E'] = E_TEX;
    char_map['F'] = F_TEX;
    char_map['G'] = G_TEX;
    char_map['H'] = H_TEX;
    char_map['I'] = I_TEX;
    char_map['J'] = J_TEX;
    char_map['K'] = K_TEX;
    char_map['L'] = L_TEX;
    char_map['M'] = M_TEX;
    char_map['N'] = N_TEX;
    char_map['O'] = O_TEX;
    char_map['P'] = P_TEX;
    char_map['Q'] = Q_TEX;
    char_map['R'] = R_TEX;
    char_map['S'] = S_TEX;
    char_map['T'] = T_TEX;
    char_map['U'] = U_TEX;
    char_map['V'] = V_TEX;
    char_map['W'] = W_TEX;
    char_map['X'] = X_TEX;
    char_map['Y'] = Y_TEX;
    char_map['Z'] = Z_TEX;
}