#include "state.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern Window window;
extern Renderer renderer;
extern Camera camera;
extern GUI gui;

static f32 minimap_zoom;

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
    update_view_matrix();
    update_proj_matrix();
}

static void state_update(void)
{
    if (game_paused)
        return;
    if (player.entity != NULL)
        camera_set_target(game_get_player_position());
    renderer_uniform_update_minimap(camera.target.x, camera.target.z, 1 / minimap_zoom);
    renderer_uniform_update_game_time(game_time);
    data_update();
    update_view_matrix();
}

void framebuffer_size_callback(GLFWwindow* handle, i32 width, i32 height)
{
    glfwGetWindowSize(window.handle, &window.width, &window.height);
    window.aspect_ratio = (f32)window.width / window.height;
    glViewport(0, 0, window.width, window.height);
    renderer_update_framebuffers();
    renderer_uniform_update_aspect_ratio(1 / window.aspect_ratio);
    camera_update_proj_matrix(window.aspect_ratio);
    update_proj_matrix();
    gui_update();
}

void mouse_button_callback(GLFWwindow* handle, i32 button, i32 action)
{
    gui_mouse_button_callback(button, action);
}

void key_callback(GLFWwindow* handle, i32 key, i32 scancode, i32 action, i32 mods)
{
    gui_key_callback(key, scancode, action, mods);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        window_close();
    if (gui_input_paused())
        return;
    if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
        window_toggle_fullscreen();
    if (key == GLFW_KEY_H && action == GLFW_PRESS)
        game_pause();
    if (key == GLFW_KEY_V && action == GLFW_PRESS)
        game_switch_weapon();
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
        game_heal();
    if (key == GLFW_KEY_J && action == GLFW_PRESS)
        game_setup(4);
    if (key == GLFW_KEY_K && action == GLFW_PRESS)
        game_setup(1);
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
        audio_play_sound(GUI_CLICK_AUD);
    if (key == GLFW_KEY_U && action == GLFW_PRESS)
        chat_send_message("Hello World");
}

static void process_input(void)
{
    i32 rotation_magnitude = 0;
    i32 tilt_magnitude = 0;
    i32 zoom_magnitude = 0;
    vec2i move_direction = vec2i_create(0, 0);
    bool hovered = 0;

    if (game_paused || gui_input_paused())
        return;

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

    if (window_key_pressed(GLFW_KEY_EQUAL)) {
        minimap_zoom += 5 * window.dt;
        if (minimap_zoom > MAX_ZOOM)
            minimap_zoom = MAX_ZOOM;
    }
        
    if (window_key_pressed(GLFW_KEY_MINUS)) {
        minimap_zoom -= 5 * window.dt;
        if (minimap_zoom < MIN_ZOOM)
            minimap_zoom = MIN_ZOOM;
    }

    if (window_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
        if (!hovered)
            game_shoot(window.cursor.position, camera.yaw, camera.pitch, camera.zoom, window.aspect_ratio);
    
    if (window_mouse_button_pressed(GLFW_MOUSE_BUTTON_RIGHT))
        if (!hovered)
            game_spellcast(window.cursor.position, camera.yaw, camera.pitch, camera.zoom, window.aspect_ratio);

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
    audio_init();
    camera_init(window.aspect_ratio);
    game_init();
    gui_init();
    data_init();
    minimap_zoom = camera.zoom;
}

#include <sys/time.h>
void state_loop(void)
{
    struct timeval times[6] = { 0 };
    i64 seconds, microseconds;
    state_setup();
    while (!window_closed()) {
        gettimeofday(&times[0], NULL);
        gui_update();
        gettimeofday(&times[1], NULL);
        window_update();
        gettimeofday(&times[2], NULL);
        process_input();
        gettimeofday(&times[3], NULL);
        state_update();
        gettimeofday(&times[4], NULL);
        renderer_render();
        gettimeofday(&times[5], NULL);

        for (i32 i = 0; i < 5; i++) {
            seconds = times[i+1].tv_sec - times[i].tv_sec;
            microseconds = times[i+1].tv_usec - times[i].tv_usec;
            //printf("%f\n", (f32)seconds + microseconds*1e-6);
        }
        //printf("\n\n");
    }
}

void state_exit(void)
{
    networking_destroy();
    audio_destroy();
    renderer_destroy();
    game_destroy();
    data_destroy();
    gui_destroy();
}
