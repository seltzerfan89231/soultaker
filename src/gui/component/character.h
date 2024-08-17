#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../util/type.h"
#include "../../util/indices.h"

#define GLYPH_HEIGHT 7

typedef struct {
    u32 tex;
    struct { i8 x, y; } size;
    struct { i8 x, y; } bearing;
    i8 advance;
} Character;

extern Character char_map[128];

void char_map_init(void);

#endif