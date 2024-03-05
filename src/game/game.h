#ifndef GAME_H
#define GAME_H

#include "player/player.h"
#include "tilemap/tilemap.h"

inline static void game_init(void)
{
    tilemap_init();
}

inline static void** game_vertex_data(void)
{
    void** tilemap_data = tilemap_vertex_data();
    return tilemap_data;
}

#endif