#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include "player/player.h"
#include "tile/tile.h"

#define MAP_WIDTH 100

typedef enum objtype {
    TILE
} objtype;

typedef struct Game {
    f32* buffer;
    u32 buffer_length;
    DLL objects;
} Game;

extern Game game;

void game_init(void);
void game_clear(void);
void game_remove(Data* data);
void game_insert(Data* data);
void game_destroy(void);

#endif