#ifndef STATE_H
#define STATE_H

#include "audio/audio.h"
#include "game/game.h"
#include "window/window.h"
#include "renderer/renderer.h"
#include "camera/camera.h"
#include "networking/networking.h"
#include "gui/gui.h"
#include "chat/chat.h"
#include "data.h"

void state_init(void);
void state_loop(void);
void state_exit(void);

#endif
