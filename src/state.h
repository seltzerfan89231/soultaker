#ifndef STATE_H
#define STATE_H

#include "game/game.h"
#include "window/window.h"
#include "renderer/renderer.h"
#include "camera/camera.h"
#include "gui/gui.h"

void state_init(void);
void state_loop(void);
void state_exit(void);

#endif
