#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include "data_structures/dll.h"
#include "drawable/drawable.h"
#include "../gfx/renderer/renderer.h"

#define MAP_WIDTH 100

typedef struct Game {
    f32* buffer;
    u32 buffer_length;
    DLL tiles;
    DLL entities;
} Game;

extern Game game;

void game_init(void);
void game_setup(void);
void game_update(void);
void game_clear(void);
void game_remove(Data* data);
void game_insert(Drawable* drawable);
void game_set_target(vec3f target);
void game_update_rotation(f32 rotation);
void game_update_tilt(f32 tilt);
void game_destroy(void);

void game_shoot(void);

#endif