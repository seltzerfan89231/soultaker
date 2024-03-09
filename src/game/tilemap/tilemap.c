#include "tilemap.h"
#include <gvec.h>
#include <assert.h>

TileMap tilemap;

void tilemap_init(void) 
{
    tilemap.faces = 0;
    tilemap.dll = dll_create();
    for (i32 i = 0; i < TILEMAP_WIDTH * TILEMAP_WIDTH; i++) {
        if (i % 7 == 0) 
            tilemap_insert(tile_create(i / TILEMAP_WIDTH, 3, i % TILEMAP_WIDTH, 0.5f, 0.5f, 0.5f, WALL));
        else
            tilemap_insert(tile_create(i / TILEMAP_WIDTH, 0, i % TILEMAP_WIDTH, 0.7f, 0.3f, 0.2f, FLOOR));
    }
}

void tilemap_clear(void)
{
    while (!dll_empty(&tilemap.dll))
        tilemap_remove(tilemap.dll.head->data);
}

void tilemap_remove(Tile* tile)
{
    tilemap.faces -= tile->type == WALL ? NUM_WALL_SIDES : NUM_FLOOR_SIDES;
    tilemap.map[tile->pos.x][tile->pos.z] = NULL;
    dll_remove(&tilemap.dll, tile->node);
    tile_destroy(tile);
}

void tilemap_insert(Tile* tile)
{
    assert(tilemap.map[tile->pos.x][tile->pos.z] == NULL);
    tilemap.faces += tile->type == WALL ? NUM_WALL_SIDES : NUM_FLOOR_SIDES;
    tilemap.map[tile->pos.x][tile->pos.z] = tile;
    dll_append(&tilemap.dll, tile->node);
}

void tilemap_vertex_data(f32* data, i32* offset) 
{
    Node* cur = tilemap.dll.head;
    while (cur != NULL)
        tile_vertex_data(data, cur->data, offset), cur = cur->next;
}

size_t tilemap_data_size(void)
{
    assert(tilemap.faces >= 0);
    return tilemap.faces * VERTEX_COUNT * FIELD_COUNT * sizeof(f32);
}