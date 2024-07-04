#include "state.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern Window window;
extern Renderer renderer;
extern Camera camera;
extern Game game;
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
    camera_set_target(game.entities.buffer[0]->position);
    update_view_matrix();
    update_proj_matrix();
    data_setup();
}

static void state_update(void)
{
    game_update(window.dt > 0.01 ? 0.01 : window.dt);
    camera_set_target(game.entities.buffer[0]->position);
    update_view_matrix();
    data_update_entities();
    data_update_projectiles();
    data_update_particles();
    data_update_parjicles();
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
    if (window_key_pressed(GLFW_KEY_G))
        renderer_reload_textures();

    if (window_mouse_button_pressed(MOUSE_LEFT))
        if (!gui_interact())
            game_shoot(window.mouse.position, camera.yaw, camera.pitch, camera.zoom, window.aspect_ratio);

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

void framebuffer_size_callback(GLFWwindow* handle, i32 width, i32 height)
{
    window.size.x = width;
    window.size.y = height;
    window.aspect_ratio = (f32)window.size.x / window.size.y;
    glViewport(0, 0, window.size.x, window.size.y);
    renderer_uniform_update_aspect_ratio(1 / window.aspect_ratio);
    camera_update_proj_matrix(window.aspect_ratio);
    update_proj_matrix();
    gui_push_data();
    renderer_update(GUI_VAO, 0, gui.length, gui.buffer);
}