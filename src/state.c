#include "state.h"

State state;

static void link_camera(void) 
{
    state.camera->aspect_ratio = (float) state.window->size.x / state.window->size.y;
    state.camera->viewID = glGetUniformLocation(state.renderer->shader.ID, "view");
    state.camera->projID = glGetUniformLocation(state.renderer->shader.ID, "proj");
    camera_update_view();
    camera_update_proj();
}

void state_init(void) 
{
    window_init();
    renderer_init();
    camera_init();

    state.renderer = &renderer;
    state.window = &window;
    state.camera = &camera;

    link_camera();
}

void state_loop(void)
{
    while (!window_closed())
    {
        camera_rotate(0.0008);
        window_process_input();
        renderer_render();
        window_poll_events();
        window_swap_buffers();
    }
}