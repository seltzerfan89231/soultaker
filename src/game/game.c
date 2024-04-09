#include "game.h"
#include <stdio.h>
#include <assert.h>
#include <glfw.h>

Game game;

static void game_push_tile(Tile* tile);
static void game_remove_tile(Tile* tile);

void game_init(void)
{
    game.tile_buffer = game.entity_buffer = game.gui_buffer = NULL;
    game.tile_length = game.entity_length = game.gui_length = 0;
    game.tiles = dll_create();
    game.entities = dll_create();
    game.rotation = game.tilt = 0;
}

void game_setup(void)
{
    game.tile_buffer = malloc(MAX_BUFFER_LENGTH * sizeof(f32));
    Tile* tile = tile_create(FLOOR);
    tile->position = vec2f_create(0.0f, 1.0f);
    game_push_tile(tile);
    tile = tile_create(WALL);
    tile->position = vec2f_create(1.0f, 0.0f);
    game_push_tile(tile);
}

void game_update(f32 dt)
{

}

void game_set_target(vec3f target)
{

}

void game_destroy(void)
{
    free(game.tile_buffer);
    free(game.entity_buffer);
    free(game.gui_buffer);
}

void game_shoot(vec2f dir)
{
    /* static f32 cooldown;
    if (glfwGetTime() - cooldown < 0.05)
        return;
    cooldown = glfwGetTime();
    assert(player != NULL);
    Entity* proj = entity_create(PROJECTILE, 0.5);
    proj->speed = 4;
    f32 dirx, dirz, a, b, c;
    a = atan(-dir.y/dir.x);
    b = PI/2 + game.tilt;
    c = tan(a) * tan(a) / cos(b) / cos(b) + 1;
    dir.x =  dir.x > 0 ? 1 / sqrt(c) : -1 / sqrt(c);
    dir.y = -dir.y > 0 ? sqrt(1 - 1 / c) : -sqrt(1 - 1 / c);
    dirx = dir.x * cos(game.rotation - HALFPI) - dir.y * sin(game.rotation - HALFPI);
    dirz = dir.x * sin(game.rotation - HALFPI) + dir.y * cos(game.rotation - HALFPI);
    proj->direction = vec3f_normalize(vec3f_create(dirx, 0, dirz));
    vec3f start = player->position;
    start.y = 0.0;
    game_insert(drawable_create(start, vec2f_create(0.5, 0), proj, ENTITY)); */
}

void game_push_tile(Tile* tile)
{
    tile_vertex_data(tile, game.tile_buffer, &game.tile_length);
}