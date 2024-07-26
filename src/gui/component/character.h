#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../util/type.h"
#include "../../util/indices.h"

typedef struct {
    u32 tex;
    struct { u8 x, y; } size;
    struct { u8 x, y; } bearing;
    u8 advance;
} Character;

extern Character char_map[128];

void char_map_init(void);

#endif