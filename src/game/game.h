#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include "data_structures/dll.h"
#include "drawable/drawable.h"

#define MAP_WIDTH 100

typedef struct Game {
    f32* buffer;
    u32 buffer_length;
    DLL objects;
    DLL tiles;
    DLL entities;
    f32 rotation, tilt;
} Game;

extern Game game;

void game_init(void);
void game_setup(void);
void game_update(void);
void game_clear(void);
void game_remove(Data* data);
void game_insert(Data* data);
void game_set_target(vec3f target);
void game_set_rotation(f32 rotation);
void game_set_tilt(f32 tilt);
void game_destroy(void);

void game_shoot(void);

#endif