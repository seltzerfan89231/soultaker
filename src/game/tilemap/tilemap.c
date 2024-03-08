#include "tilemap.h"
#include <gvec.h>
#include <stdlib.h>

TileMap tilemap;

void tilemap_init(void) 
{
    tilemap.faces = 0;
    tilemap.deque = deque_create();
    for (i32 i = 0; i < TILEMAP_WIDTH * TILEMAP_WIDTH; i++) {
        if (i % 7 == 0) {
            Tile* tile = tile_create(i / TILEMAP_WIDTH, 3, i % TILEMAP_WIDTH, 0.5f, 0.5f, 0.5f, WALL);
            tilemap.faces += NUM_WALL_SIDES;
            tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] = tile;
            deque_insert(&tilemap.deque, tile->node);
        }
        else {
            Tile* tile = tile_create(i / TILEMAP_WIDTH, 0, i % TILEMAP_WIDTH, 0.7f, 0.3f, 0.2f, FLOOR);
            tilemap.faces += NUM_FLOOR_SIDES;
            tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] = tile;
            deque_insert(&tilemap.deque, tile->node);
        }
    }
    tilemap.data_size = tilemap.faces * VERTEX_COUNT * FIELD_COUNT * sizeof(f32);
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