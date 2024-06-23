#ifndef KNIGHT_H
#define KNIGHT_H

#include "../../util/type.h"
#include "../../util/indices.h"

#define KNIGHT_FRAMES 8

typedef enum {
    IDLE, SHOOT
} KnightFrames;

void knight_init(u32 *buf);

#endif