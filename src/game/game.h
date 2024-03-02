#ifndef GAME_H
#define GAME_H

#include "player/player.h"
#include "tilemap/tilemap.h"

typedef struct Game {
    Player* player;
} Game;

extern Game game;

void game_init(void);

#endif