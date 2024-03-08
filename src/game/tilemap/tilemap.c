#include "tilemap.h"
#include <gvec.h>
#include <stdlib.h>

#define NUM_WALL_SIDES 5
#define NUM_TILE_SIDES 1
#define VERTEX_COUNT 6
#define FIELD_COUNT 6

TileMap tilemap;

void tilemap_init(void) 
{
    tilemap.tile_count = 0;
    tilemap.deque = deque_create();
    for (i32 i = 0; i < TILEMAP_WIDTH * TILEMAP_WIDTH; i++) {
        if (i % 7 == 0) {
            Tile* tile = tile_create(i / TILEMAP_WIDTH, 3, i % TILEMAP_WIDTH, 0.5f, 0.5f, 0.5f);
            tilemap.tile_count++;
            tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] = tile;
            deque_insert(&tilemap.deque, tile->node);
        }
        else
            tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] = NULL;
    }
    tilemap.data_size = NUM_WALL_SIDES * VERTEX_COUNT * FIELD_COUNT * tilemap.tile_count * sizeof(f32);
}

void tilemap_clear(void)
{
    
}

void tilemap_vertex_data(f32* data, i32* offset) 
{
    Node* cur = tilemap.deque.head;
    while (cur != NULL)
        tile_vertex_data(data, cur->data, offset), cur = cur->next;
}