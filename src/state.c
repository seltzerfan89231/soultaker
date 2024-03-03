#include "state.h"
#include <stdlib.h>

extern Window window;
extern Renderer renderer;
extern Camera camera;
extern TileMap tilemap;

static void link_camera(void) 
{
    camera.aspect_ratio = (float) window.size.x / window.size.y;
    camera.viewID = renderer_uniform_location("view");
    camera.projID = renderer_uniform_location("proj");
    camera_update_view();
    camera_update_proj();
}

static void process_input(void)
{
    i32 rotation_magnitude = 0;
    vec2i move_direction = vec2i_create(0, 0);
    if (window_key_pressed(GLFW_KEY_ESCAPE))
        window_close();
    if (window_key_pressed(GLFW_KEY_Q))
        rotation_magnitude++;
    if (window_key_pressed(GLFW_KEY_E))
        rotation_magnitude--;
    if (window_key_pressed(GLFW_KEY_W))
        move_direction.x++;
    if (window_key_pressed(GLFW_KEY_S))
        move_direction.x--;
    if (window_key_pressed(GLFW_KEY_A))
        move_direction.y--;
    if (window_key_pressed(GLFW_KEY_D))
        move_direction.y++;

    if (move_direction.x != 0 || move_direction.y != 0)
        camera_move(move_direction);
    if (rotation_magnitude != 0)
        camera_rotate(rotation_magnitude);
}

void state_init(void) 
{
    window_init();
    renderer_init();
    camera_init();
    tilemap_init();

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

void state_exit(void)
{
    renderer_destroy();
}