#ifndef STATE_H
#define STATE_H

#include "game/game.h"
#include "gfx/gfx.h"

typedef struct State {
    Renderer* renderer;
    Window* window;
    Camera* camera;
    Game* game;
} State;

void state_init(void);
void state_loop(void);

#endif
