#ifndef GAME_H
#define GAME_H

#include "player/player.h"
#include "tilemap/tilemap.h"

inline static void game_init(void)
{
    tilemap_init();
}

inline static f32* game_vertex_data(void)
{
    f32* tilemap_data = tilemap_vertex_data();
    return tilemap_data;
}

#endif