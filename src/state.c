#include "state.h"

State state;

void state_init(void) 
{
    window_init();
    renderer_init();
    
    state.renderer = &renderer;
    state.window = &window;
    state.camera = &camera;
}

void state_loop(void)
{
    while (!window_closed())
    {
        window_process_input();
        renderer_render();
        window_poll_events();
        window_swap_buffers();
    }
}