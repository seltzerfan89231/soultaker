#include "state.h"

State state;

static void link_camera(void) 
{
    state.camera->aspect_ratio = (float) state.window->size.x / state.window->size.y;
    state.camera->viewID = renderer_uniform_location("view");
    state.camera->projID = renderer_uniform_location("proj");
    camera_update_view();
    camera_update_proj();
}

static void process_input(void)
{
    vec2i move_offset = vec2i_create(0, 0);
    if (window_key_pressed(GLFW_KEY_ESCAPE))
        window_close();
    if (window_key_pressed(GLFW_KEY_Q))
        camera_rotate(0.0008);
    if (window_key_pressed(GLFW_KEY_E))
        camera_rotate(-0.0008);
    if (window_key_pressed(GLFW_KEY_W))
        move_offset.x++;
    if (window_key_pressed(GLFW_KEY_S))
        move_offset.x--;
    if (window_key_pressed(GLFW_KEY_A))
        move_offset.y--;
    if (window_key_pressed(GLFW_KEY_D))
        move_offset.y++;
    camera_move(move_offset);
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
        process_input();
        renderer_render();
        window_poll_events();
        window_swap_buffers();
    }
}