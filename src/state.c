#include "state.h"

State state;

void state_init(void) 
{
    renderer_init();
    window_init();

    state.renderer = &renderer;
    state.window = &window;
    state.camera = &camera;
}