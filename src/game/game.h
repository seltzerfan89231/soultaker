#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include "player/player.h"
#include "tilemap/tilemap.h"

typedef struct VertexData {
    size_t data_size;
    f32* data;
} VertexData;

void game_init(void);
VertexData game_vertex_data(void);

#endif