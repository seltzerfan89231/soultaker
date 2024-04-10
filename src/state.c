#include "state.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern Window window;
extern Renderer renderer;
extern Camera camera;
extern Game game;

static void state_setup(void)
{
    game_setup();
    renderer_malloc(TILE, game.tile_length);
    renderer_update(TILE, 0, game.tile_length, game.tile_buffer);
    renderer_malloc(ENTITY, MAX_BUFFER_LENGTH);
    renderer_update(ENTITY, 0, game.entity_length, game.entity_buffer);
    renderer_malloc(GUI, game.gui_length);
    renderer_update(GUI, 0, game.gui_length, game.gui_buffer);
}

static void state_update(void)
{
    game_update(window.dt);
    renderer_update(ENTITY, 0, game.entity_length, game.entity_buffer);
}

static void update_proj_matrix(void)
{
    renderer_uniform_update_matrix(TILE, "proj", camera.proj);
    renderer_uniform_update_matrix(ENTITY, "proj", camera.proj);
}

static void update_view_matrix(void)
{
    renderer_uniform_update_matrix(TILE, "view", camera.view);
    renderer_uniform_update_matrix(ENTITY, "view", camera.view);
}

static void process_input(void)
{
    i32 rotation_magnitude = 0;
    i32 tilt_magnitude = 0;
    i32 zoom_magnitude = 0;
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
    if (window_key_pressed(GLFW_KEY_T))
        tilt_magnitude++;
    if (window_key_pressed(GLFW_KEY_Y))
        tilt_magnitude--;
    if (window_key_pressed(GLFW_KEY_O))
        zoom_magnitude++;
    if (window_key_pressed(GLFW_KEY_P))
        zoom_magnitude--;
    if (window_mouse_button_pressed(MOUSE_LEFT))
        game_shoot(window_mouse_direction());

    if (move_direction.x != 0 || move_direction.y != 0)
        game_set_target(camera_move(move_direction, window.dt));
    if (rotation_magnitude != 0)
        game_set_rotation(camera_rotate(rotation_magnitude, window.dt));
    if (tilt_magnitude != 0)
        game_set_tilt(camera_tilt(tilt_magnitude, window.dt));
    if (zoom_magnitude != 0)
        camera_zoom(zoom_magnitude, window.dt);

    if (move_direction.x != 0 || move_direction.y != 0 || rotation_magnitude != 0 || tilt_magnitude != 0)
        update_view_matrix();
    if (zoom_magnitude != 0)
        update_proj_matrix();
}

void state_init(void) 
{
    window_init();
    renderer_init();
    camera_init();
    game_init();

    game_set_rotation(camera.yaw);
    game_set_tilt(camera.pitch);
    camera_aspect_ratio(window.size.x / window.size.y);
    update_view_matrix();
    update_proj_matrix();
}

void state_loop(void)
{
    state_setup();
    f32 time = glfwGetTime();
    while (!window_closed()) {
        process_input();
        state_update();
        renderer_render();
        window_poll_events();
        window_swap_buffers();
        window_calc_dt();
        if (glfwGetTime() - time > 1)
            printf("%d, %.0f\n", window.mouse.left, window.fps), time = glfwGetTime();
    }
}

void state_exit(void)
{
    renderer_destroy();
    game_destroy();
}