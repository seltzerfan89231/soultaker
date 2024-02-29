#ifndef STATE_H
#define STATE_H

#include <glad.h>
#include "game/game.h"
#include "gfx/gfx.h"

typedef struct State {
    Renderer* renderer;
    Window* window;
    Camera* camera;
} State;

void state_init(void);
void state_loop(void);

#endif
