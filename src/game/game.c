#include "game.h"

Game game;

void game_init(void)
{
    tilemap_init();
    game.player = &player;
}