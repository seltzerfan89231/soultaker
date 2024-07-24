#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../util/type.h"
#include "../../util/indices.h"

typedef struct {
    u32 tex;
    u8 width, height, bearingX, bearingY;
} Character;

extern Character char_map[128];

void char_map_init(void);

#endif