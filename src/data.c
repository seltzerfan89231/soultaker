#include "data.h"
#include <stdlib.h>

Data data;
i32 i;

static void wall_push_data(Wall* wall, u32 offset)
{
    offset *= 5;
    data.buffer[offset++] = wall->position.x;
    data.buffer[offset++] = wall->height;
    data.buffer[offset++] = wall->position.z;
    data.buffer[offset++] = WALL_TOP_TEX;
    data.buffer[offset++] = WALL_TEX;
}

static void tile_push_data(Tile* tile, u32 offset)
{
    offset *= 3;
    data.buffer[offset++] = tile->position.x;
    data.buffer[offset++] = tile->position.z;
    data.buffer[offset++] = TILE_TEX;
}

static void projectile_push_data(Projectile* projectile, u32 offset)
{
    offset *= 6;
    data.buffer[offset++] = projectile->position.x;
    data.buffer[offset++] = projectile->position.y;
    data.buffer[offset++] = projectile->position.z;
    data.buffer[offset++] = projectile->scale;
    data.buffer[offset++] = projectile->rotation;
    data.buffer[offset++] = BULLET_TEX;
}

static void entity_push_data(Entity* entity, u32 offset)
{
    offset *= 10;
    data.buffer[offset++] = entity->position.x;
    data.buffer[offset++] = entity->position.y;
    data.buffer[offset++] = entity->position.z;
    data.buffer[offset++] = entity->scale;
    data.buffer[offset++] = entity->health / entity->max_health;
    f32 theta = atan(entity->facing.y / entity->facing.x) + (entity->facing.x >= 0 ? 0 : PI);
    f32 dif = theta + PI - camera.yaw;
    u8 dir;
    if (dif > 2 * PI) dif -= 2 * PI;
    if (dif < 0) dif += 2 * PI;

    if      (dif < PI / 4 - 0.01)     dir = DOWN;
    else if (dif < 3 * PI / 4 + 0.01) dir = RIGHT;
    else if (dif < 5 * PI / 4 - 0.01) dir = UP;
    else if (dif < 7 * PI / 4 + 0.01) dir = LEFT;
    else                              dir = DOWN;
    data.buffer[offset++] = data.frame_data[entity->id][dir][entity->state].frame;
    data.buffer[offset++] = data.frame_data[entity->id][dir][entity->state].x;
    data.buffer[offset++] = data.frame_data[entity->id][dir][entity->state].y;
    data.buffer[offset++] = data.frame_data[entity->id][dir][entity->state].w;
    data.buffer[offset++] = data.frame_data[entity->id][dir][entity->state].h;  
}

static void particle_push_data(Particle *particle, u32 offset)
{
    offset *= 4;
    data.buffer[offset++] = particle->position.x;
    data.buffer[offset++] = particle->position.y;
    data.buffer[offset++] = particle->position.z;
    data.buffer[offset++] = particle->scale;
}

static void parstacle_push_data(Parstacle *parstacle, u32 offset)
{
    offset *= 5;
    data.buffer[offset++] = parstacle->position.x;
    data.buffer[offset++] = parstacle->position.y;
    data.buffer[offset++] = parstacle->position.z;
    data.buffer[offset++] = parstacle->scale;
    data.buffer[offset++] = BUSH_TEX;
}

static void parjicle_push_data(Parjicle *parjicle, u32 offset)
{
    offset *= 5;
    data.buffer[offset++] = parjicle->position.x;
    data.buffer[offset++] = parjicle->position.y;
    data.buffer[offset++] = parjicle->position.z;
    data.buffer[offset++] = parjicle->scale;
    data.buffer[offset++] = parjicle->rotation;
}


static void obstacle_push_data(Obstacle *obstacle, u32 offset)
{
    offset *= 5;
    data.buffer[offset++] = obstacle->position.x;
    data.buffer[offset++] = obstacle->position.y;
    data.buffer[offset++] = obstacle->position.z;
    data.buffer[offset++] = obstacle->scale;
    data.buffer[offset++] = ROCK_TEX;
}

void data_init(void)
{
    data.buffer = malloc(50000000 * sizeof(f32));
    data.frame_data = malloc(MAX_ENTITY_ID * sizeof(FrameData**));
    knight_init_frame_data(data.frame_data);
    enemy_init_frame_data(data.frame_data);
}

void data_destroy(void)
{
    knight_destroy_frame_data(data.frame_data);
    enemy_destroy_frame_data(data.frame_data);
    free(data.frame_data);
    free(data.buffer);
}

void data_setup(void)
{
    renderer_malloc(TILE_VAO, tiles.max_length);
    renderer_malloc(WALL_VAO, walls.max_length);
    renderer_malloc(ENTITY_VAO, entities.max_length);
    renderer_malloc(PROJECTILE_VAO, projectiles.max_length);
    renderer_malloc(PARTICLE_VAO, particles.max_length);
    renderer_malloc(OBSTACLE_VAO, obstacles.max_length);
    renderer_malloc(PARSTACLE_VAO, parstacles.max_length);
    renderer_malloc(PARJICLE_VAO, parjicles.max_length);
    gui_push_data();
    renderer_malloc(GUI_VAO, gui.max_length);
    data_update_tiles();
    data_update_walls();
    data_update_entities();
    data_update_projectiles();
    data_update_parjicles();
    data_update_particles();
    data_update_parstacles();
    data_update_obstacles();
    renderer_update(GUI_VAO, 0, gui.length, gui.buffer);
}

void data_update_tiles(void)
{
    for (i = 0; i < tiles.length; i++)
        tile_push_data(tiles.buffer[i], i);
    renderer_update(TILE_VAO, 0, i, data.buffer);
}

void data_update_walls(void)
{
    for (i = 0; i < walls.length; i++)
        wall_push_data(walls.buffer[i], i);
    renderer_update(WALL_VAO, 0, i, data.buffer);
}

void data_update_entities(void)
{
    for (i = 0; i < entities.length; i++)
        entity_push_data(entities.buffer[i], i);
    renderer_update(ENTITY_VAO, 0, i, data.buffer);
}

void data_update_projectiles(void)
{
    for (i = 0; i < projectiles.length; i++)
        projectile_push_data(projectiles.buffer[i], i);
    renderer_update(PROJECTILE_VAO, 0, i, data.buffer);
}

void data_update_parjicles(void)
{
    for (i = 0; i < parjicles.length; i++)
        parjicle_push_data(parjicles.buffer[i], i);
    renderer_update(PARJICLE_VAO, 0, i, data.buffer);
}

void data_update_particles(void)
{
    for (i = 0; i < particles.length; i++)
        particle_push_data(particles.buffer[i], i);
    renderer_update(PARTICLE_VAO, 0, i, data.buffer);
}

void data_update_parstacles(void)
{
    for (i = 0; i < parstacles.length; i++)
        parstacle_push_data(parstacles.buffer[i], i);
    renderer_update(PARSTACLE_VAO, 0, i, data.buffer);
}

void data_update_obstacles(void)
{
    for (i = 0; i < obstacles.length; i++)
        obstacle_push_data(obstacles.buffer[i], i);
    renderer_update(OBSTACLE_VAO, 0, i, data.buffer);
}
