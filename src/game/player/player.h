#ifndef PLAYER_H
#define PLAYER_H

#include <gvec.h>

typedef struct Player {
    vec3f* position;
    f32* rotation;
} Player;

extern Player player;

void player_init(void);

#endif