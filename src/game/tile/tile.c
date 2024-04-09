#include "tile.h"
#include <stdlib.h>

Tile* tile_create(tiletype type)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->type = type;
    tile->tex = vec2f_create(0.25f, 0.0f);
    tile->height = 3.0f;
    return tile;
}

void tile_vertex_data(Tile* tile, f32* buffer, u32* offset)
{
    i32 start, end;
    start = tile->type == WALL ? 0 : 5;
    end   = tile->type == WALL ? 5 : 6;
    for (i32 s = start; s < end; s++) {
        for (i32 v = 0; v < QUAD_VERTEX_COUNT; v++) {
            buffer[(*offset)++] = tile->position.x + vertices[3*sides[4*s+vertex_order[v]]];
            buffer[(*offset)++] = tile->height * vertices[3*sides[4*s+vertex_order[v]]+1];
            buffer[(*offset)++] = tile->position.y + vertices[3*sides[4*s+vertex_order[v]]+2];
            buffer[(*offset)++] = tile->tex.x + tex[2*vertex_order[v]] * 0.25;
            buffer[(*offset)++] = tile->tex.y + tex[2*vertex_order[v]+1] * 0.25;
        }
    }
}

void tile_destroy(Tile* tile)
{
    free(tile);
}