#include "knight.h"
#include <stdlib.h>

void knight_init(u32 *buf)
{
    buf[0] = KNIGHT_DOWN_TEX;
    buf[1] = KNIGHT_RIGHT_TEX;
    buf[2] = KNIGHT_UP_TEX;
    buf[3] = KNIGHT_LEFT_TEX;
    
    buf[4] = KNIGHT_SHOOT_DOWN_TEX;
    buf[5] = KNIGHT_SHOOT_RIGHT_TEX;
    buf[6] = KNIGHT_SHOOT_UP_TEX;
    buf[7] = KNIGHT_SHOOT_LEFT_TEX;
}