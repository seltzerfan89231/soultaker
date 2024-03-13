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
    f32 rotation;
} Game;

extern Game game;

void game_init(void);
void game_clear(void);
void game_remove(Data* data);
void game_insert(Data* data);
void game_set_target(vec3f target);
void game_set_rotation(f32 rotation);
void game_destroy(void);

#endif