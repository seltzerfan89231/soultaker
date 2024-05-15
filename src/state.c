#include "state.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern Window window;
extern Renderer renderer;
extern Camera camera;
extern Game game;
extern GUI gui;

static void state_setup(void)
{
    game_setup();
    renderer_malloc(TILE, MAX_BUFFER_LENGTH);
    renderer_update(TILE, 0, game.tile_length * 3, game.tile_buffer);
    renderer_malloc(ENTITY, MAX_BUFFER_LENGTH);
    renderer_update(ENTITY, 0, game.entity_length * 3, game.entity_buffer);
    renderer_malloc(PROJECTILE, MAX_BUFFER_LENGTH);
    renderer_update(PROJECTILE, 0, game.projectile_length * 4, game.projectile_buffer);
    renderer_malloc(GUIB, MAX_BUFFER_LENGTH);
    renderer_update(GUIB, 0, gui.length, gui.buffer);
}

static void state_update(void)
{
    game_update(window.dt);
    renderer_update(ENTITY, 0, game.entity_length * 3, game.entity_buffer);
    renderer_update(PROJECTILE, 0, game.projectile_length * 4, game.projectile_buffer);
}

static void update_proj_matrix(void)
{
    renderer_uniform_update_proj(camera.proj);
    renderer_uniform_update_zoom(1 / camera.zoom);
}

static void update_view_matrix(void)
{
    renderer_uniform_update_view(camera.view);
    renderer_uniform_update_rotation(camera.yaw);
    renderer_uniform_update_tilt(-camera.pitch);
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
        game_shoot(window.mouse.position, camera.yaw, camera.pitch, camera.zoom, window.aspect_ratio);

    if (move_direction.x != 0 || move_direction.y != 0)
        game_set_target(camera_move(move_direction, window.dt));
    if (rotation_magnitude != 0)
        camera_rotate(rotation_magnitude, window.dt);
    if (tilt_magnitude != 0)
        camera_tilt(tilt_magnitude, window.dt);
    if (zoom_magnitude != 0)
        camera_zoom(zoom_magnitude, window.dt, window.aspect_ratio);

    if (move_direction.x != 0 || move_direction.y != 0 || rotation_magnitude != 0 || tilt_magnitude != 0)
        update_view_matrix();
    if (zoom_magnitude != 0)
        update_proj_matrix();
}

void state_init(void) 
{
    window_init();
    renderer_init();
    camera_init(vec3f_create(0.0f, 0.0f, 0.0f), window.aspect_ratio);
    game_init();
    gui_init();

    renderer_uniform_update_aspect_ratio(1 / window.aspect_ratio);
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
        window_update();
        if (glfwGetTime() - time > 1)
            printf("%d, %.0f, %f\n", window.mouse.left, window.fps, camera.yaw), time = glfwGetTime();
    }
}

void state_exit(void)
{
    renderer_destroy();
    game_destroy();
    gui_destroy();
}