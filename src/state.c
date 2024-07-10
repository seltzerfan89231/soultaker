#include "state.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern Window window;
extern Renderer renderer;
extern Camera camera;
extern GUI gui;

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

static void state_setup(void)
{
    renderer_uniform_update_aspect_ratio(1 / window.aspect_ratio);
    game_setup();
    camera_set_target(game_get_player_position());
    update_view_matrix();
    update_proj_matrix();
    data_setup();
}

static void state_update(void)
{
    game_update(window.dt > 0.01 ? 0.01 : window.dt);
    camera_set_target(game_get_player_position());
    update_view_matrix();
    data_update_entities();
    data_update_projectiles();
    data_update_particles();
    data_update_parjicles();
}

void framebuffer_size_callback(GLFWwindow* handle, i32 width, i32 height)
{
    window.size.x = width;
    window.size.y = height;
    window.aspect_ratio = (f32)window.size.x / window.size.y;
    glViewport(0, 0, window.size.x, window.size.y);
    renderer_uniform_update_aspect_ratio(1 / window.aspect_ratio);
    camera_update_proj_matrix(window.aspect_ratio);
    update_proj_matrix();
    gui_update_data();
    renderer_update(GUI_VAO, 0, gui.length, gui.buffer);
}

void mouse_button_callback(GLFWwindow* handle, i32 button, i32 action)
{
    gui_mouse_button_callback(button, action);
}

void key_callback(GLFWwindow* handle, i32 key, i32 scancode, i32 action, i32 mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        window_close();
    if (key == GLFW_KEY_H && action == GLFW_PRESS)
        game_pause();
    if (key == GLFW_KEY_V && action == GLFW_PRESS)
        game_switch_weapon();
    //gui_key_callback(key, scancode, action, mods);
}

static void process_input(void)
{
    i32 rotation_magnitude = 0;
    i32 tilt_magnitude = 0;
    i32 zoom_magnitude = 0;
    vec2i move_direction = vec2i_create(0, 0);
    bool hovered = 0;

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

    if (window_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
        if (!hovered)
            game_shoot(window.cursor.position, camera.yaw, camera.pitch, camera.zoom, window.aspect_ratio);

    game_set_direction(camera_get_direction(move_direction));
    if (rotation_magnitude != 0)
        camera_rotate(rotation_magnitude, window.dt);
    if (tilt_magnitude != 0)
        camera_tilt(tilt_magnitude, window.dt);
    if (zoom_magnitude != 0)
        camera_zoom(zoom_magnitude, window.dt, window.aspect_ratio);
    if (zoom_magnitude != 0)
        update_proj_matrix();
}
void state_init(void) 
{
    window_init();
    renderer_init();
    camera_init(window.aspect_ratio);
    game_init();
    gui_init();
    data_init();
    state_setup();
}

void state_loop(void)
{
    f32 t = glfwGetTime();
    while (!window_closed()) {
        gui_update();
        window_update();
        process_input();
        state_update();
        renderer_render();
        if (glfwGetTime() - t > 1) {
            t = glfwGetTime();
            printf("%.0f\n", window.fps);
        }
    }
}

void state_exit(void)
{
    renderer_destroy();
    game_destroy();
    data_destroy();
    gui_destroy();
}
