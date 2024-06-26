#include "data.h"

Data data;
i32 i;

static void wall_push_data(Wall* wall, u32 offset)
{
    offset *= 4;
    data.buffer[offset++] = wall->position.x;
    data.buffer[offset++] = wall->height;
    data.buffer[offset++] = wall->position.z;
    data.buffer[offset++] = 0;
}

static void tile_push_data(Tile* tile, u32 offset)
{
    offset *= 2;
    data.buffer[offset++] = tile->position.x;
    data.buffer[offset++] = tile->position.z;
}

static void projectile_push_data(Projectile* projectile, u32 offset)
{
    offset *= 5;
    data.buffer[offset++] = projectile->position.x;
    data.buffer[offset++] = projectile->position.y;
    data.buffer[offset++] = projectile->position.z;
    data.buffer[offset++] = projectile->scale;
    data.buffer[offset++] = projectile->rotation;
}

static void entity_push_data(Entity* entity, u32 offset)
{
    offset *= 6;
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
    data.buffer[offset++] = renderer.animations[ENTITY_ANIMATION].frames[entity->id][dir][entity->state];
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
    offset *= 4;
    data.buffer[offset++] = parstacle->position.x;
    data.buffer[offset++] = parstacle->position.y;
    data.buffer[offset++] = parstacle->position.z;
    data.buffer[offset++] = parstacle->scale;
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
    offset *= 4;
    data.buffer[offset++] = obstacle->position.x;
    data.buffer[offset++] = obstacle->position.y;
    data.buffer[offset++] = obstacle->position.z;
    data.buffer[offset++] = obstacle->scale;
}

void data_init(void)
{
    data.buffer = malloc(50000000 * sizeof(f32));
}

void data_setup(void)
{
    renderer_malloc(TILE_VAO, game.tiles.max_length);
    renderer_malloc(WALL_VAO, game.walls.max_length);
    renderer_malloc(ENTITY_VAO, game.entities.max_length);
    renderer_malloc(PROJECTILE_VAO, game.projectiles.max_length);
    renderer_malloc(PARTICLE_VAO, game.particles.max_length);
    renderer_malloc(OBSTACLE_VAO, game.obstacles.max_length);
    renderer_malloc(PARSTACLE_VAO, game.parstacles.max_length);
    renderer_malloc(PARJICLE_VAO, game.parjicles.max_length);
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
    for (i = 0; i < game.tiles.length; i++)
        tile_push_data(game.tiles.buffer[i], i);
    renderer_update(TILE_VAO, 0, i, data.buffer);
}

void data_update_walls(void)
{
    for (i = 0; i < game.walls.length; i++)
        wall_push_data(game.walls.buffer[i], i);
    renderer_update(WALL_VAO, 0, i, data.buffer);
}

void data_update_entities(void)
{
    for (i = 0; i < game.entities.length; i++)
        entity_push_data(game.entities.buffer[i], i);
    renderer_update(ENTITY_VAO, 0, i, data.buffer);
}

void data_update_projectiles(void)
{
    for (i = 0; i < game.projectiles.length; i++)
        projectile_push_data(game.projectiles.buffer[i], i);
    renderer_update(PROJECTILE_VAO, 0, i, data.buffer);
}

void data_update_parjicles(void)
{
    for (i = 0; i < game.parjicles.length; i++)
        parjicle_push_data(game.parjicles.buffer[i], i);
    renderer_update(PARJICLE_VAO, 0, i, data.buffer);
}

void data_update_particles(void)
{
    for (i = 0; i < game.particles.length; i++)
        particle_push_data(game.particles.buffer[i], i);
    renderer_update(PARTICLE_VAO, 0, i, data.buffer);
}

void data_update_parstacles(void)
{
    for (i = 0; i < game.parstacles.length; i++)
        parstacle_push_data(game.parstacles.buffer[i], i);
    renderer_update(PARSTACLE_VAO, 0, i, data.buffer);
}

void data_update_obstacles(void)
{
    for (i = 0; i < game.obstacles.length; i++)
        obstacle_push_data(game.obstacles.buffer[i], i);
    renderer_update(OBSTACLE_VAO, 0, i, data.buffer);
}

void data_destroy(void)
{
    free(data.buffer);
}