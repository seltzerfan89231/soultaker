#ifndef STATE_H
#define STATE_H

#include "game/game.h"
#include "gfx/gfx.h"

typedef struct State {
    Renderer *renderer;
    Window *window;
    Camera *camera;
} State;

void state_init();
void state_loop();

#endif
