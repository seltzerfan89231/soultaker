#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include "../util/data_structures/dll.h"
#include "entity/entity.h"
#include "tile/tile.h"
#include "gui/gui.h"

typedef struct Game {
    f32 *tile_buffer, *entity_buffer, *gui_buffer;
    u32 tile_length, entity_length, gui_length;
    DLL tiles, entities;
    f32 rotation, tilt;
} Game;

extern Game game;

void game_init(void);
void game_setup(void);
void game_update(f32 dt);
void game_set_target(vec3f target);
void game_destroy(void);
void game_shoot(vec2f dir);

#endif