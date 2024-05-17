#include "state.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern Window window;
extern Renderer renderer;
extern Camera camera;
extern Game game;
extern GUI gui;
f32 *buffer;
i32 i;

static void wall_push_data(Wall* wall, f32* buffer, u32 offset)
{
    offset *= 4;
    buffer[offset++] = wall->position.x;
    buffer[offset++] = wall->height;
    buffer[offset++] = wall->position.y;
    buffer[offset++] = 0;
}

static void tile_push_data(Tile* tile, f32* buffer, u32 offset)
{
    offset *= 2;
    buffer[offset++] = tile->position.x;
    buffer[offset++] = tile->position.y;
}

static void projectile_push_data(Projectile* projectile, f32* buffer, u32 offset)
{
    offset *= 4;
    buffer[offset++] = projectile->position.x;
    buffer[offset++] = projectile->position.y;
    buffer[offset++] = projectile->position.z;
    buffer[offset++] = projectile->rotation;
}

static void entity_push_data(Entity* entity, f32* buffer, u32 offset)
{
    offset *= 3;
    buffer[offset++] = entity->position.x;
    buffer[offset++] = entity->position.y;
    buffer[offset++] = entity->position.z;
}

static void state_setup(void)
{
    game_setup();

    renderer_malloc(TILE, game.tiles.max_length);
    for (i = 0; i < game.tiles.length; i++)
        tile_push_data(game.tiles.buffer[i], buffer, i);
    renderer_update(TILE, 0, i, buffer);

    renderer_malloc(WALL, game.walls.max_length);
    for (i = 0; i < game.walls.length; i++)
        wall_push_data(game.walls.buffer[i], buffer, i);
    renderer_update(WALL, 0, i, buffer);

    renderer_malloc(ENTITY, game.entities.max_length);
    for (i = 0; i < game.entities.length; i++)
        entity_push_data(game.entities.buffer[i], buffer, i);
    renderer_update(ENTITY, 0, i, buffer);
    
    renderer_malloc(PROJECTILE, game.projectiles.max_length);
    for (i = 0; i < game.projectiles.length; i++)
        projectile_push_data(game.projectiles.buffer[i], buffer, i);
    renderer_update(PROJECTILE, 0, i, buffer);
}

static void state_update(void)
{
    game_update(window.dt);

    for (i = 0; i < game.entities.length; i++)
        entity_push_data(game.entities.buffer[i], buffer, i);
    renderer_update(ENTITY, 0, i, buffer);

    for (i = 0; i < game.projectiles.length; i++)
        projectile_push_data(game.projectiles.buffer[i], buffer, i);
    renderer_update(PROJECTILE, 0, i, buffer);
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
    buffer = malloc(5000000 * sizeof(f32));
    window_init();
    renderer_init();
    camera_init(vec3f_create(0.0f, 0.0f, 0.0f), window.aspect_ratio);
    game_init();
    gui_init();
    renderer_uniform_update_aspect_ratio(1 / window.aspect_ratio);
    update_view_matrix();
    update_proj_matrix();
    state_setup();
}

void state_loop(void)
{
    f32 time = glfwGetTime();
    while (!window_closed()) {
        process_input();
        state_update();
        renderer_render();
        window_update();
        if (glfwGetTime() - time > 1)
            printf("%d, %.0f\n", window.mouse.left, window.fps), time = glfwGetTime();
    }
}

void state_exit(void)
{
    free(buffer);
    renderer_destroy();
    game_destroy();
    gui_destroy();
}