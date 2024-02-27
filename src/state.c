#include "state.h"
#include <stdio.h>

State state;

void state_init() 
{
    renderer_init();
    window_init();

    state.renderer = &renderer;
    state.window = &window;
    state.camera = &camera;
}

void state_loop()
{
    while (!window_closed())
    {
        window_process_input();
        renderer_render();
        window_poll_events();
        window_swap_buffers();
    }
}