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
    data.buffer[offset++] = wall->top_tex;
    data.buffer[offset++] = wall->side_tex;
}

static void tile_push_data(Tile* tile, u32 offset)
{
    offset *= 3;
    data.buffer[offset++] = tile->position.x;
    data.buffer[offset++] = tile->position.z;
    data.buffer[offset++] = tile->tex;
}

static void projectile_push_data(Projectile* projectile, u32 offset)
{
    offset *= 6;
    data.buffer[offset++] = projectile->position.x;
    data.buffer[offset++] = projectile->position.y;
    data.buffer[offset++] = projectile->position.z;
    data.buffer[offset++] = projectile->scale;
    data.buffer[offset++] = projectile->rotation;
    data.buffer[offset++] = projectile->tex;
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
    offset *= 7;
    data.buffer[offset++] = particle->position.x;
    data.buffer[offset++] = particle->position.y;
    data.buffer[offset++] = particle->position.z;
    data.buffer[offset++] = particle->scale;
    data.buffer[offset++] = particle->color.r;
    data.buffer[offset++] = particle->color.g;
    data.buffer[offset++] = particle->color.b;
}

static void parstacle_push_data(Parstacle *parstacle, u32 offset)
{
    offset *= 5;
    data.buffer[offset++] = parstacle->position.x;
    data.buffer[offset++] = parstacle->position.y;
    data.buffer[offset++] = parstacle->position.z;
    data.buffer[offset++] = parstacle->scale;
    data.buffer[offset++] = parstacle->tex;
}

static void parjicle_push_data(Parjicle *parjicle, u32 offset)
{
    offset *= 8;
    data.buffer[offset++] = parjicle->position.x;
    data.buffer[offset++] = parjicle->position.y;
    data.buffer[offset++] = parjicle->position.z;
    data.buffer[offset++] = parjicle->scale;
    data.buffer[offset++] = parjicle->rotation;
    data.buffer[offset++] = parjicle->color.r;
    data.buffer[offset++] = parjicle->color.g;
    data.buffer[offset++] = parjicle->color.b;
}


static void obstacle_push_data(Obstacle *obstacle, u32 offset)
{
    offset *= 5;
    data.buffer[offset++] = obstacle->position.x;
    data.buffer[offset++] = obstacle->position.y;
    data.buffer[offset++] = obstacle->position.z;
    data.buffer[offset++] = obstacle->scale;
    data.buffer[offset++] = obstacle->tex;
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
    data_update_tiles();
    data_update_walls();
    data_update_entities();
    data_update_projectiles();
    data_update_parjicles();
    data_update_particles();
    data_update_parstacles();
    data_update_obstacles();
}

#define _DATA_UPDATE(_utype, _ltype, _ltypes) \
    void data_update_##_ltypes(void) { \
        for (i = 0; i < _ltypes.length; i++) \
            _ltype##_push_data(_ltypes.buffer[i], i); \
        if (_ltypes.changed_size) { \
            renderer_malloc(_utype##_VAO, _ltypes.max_length); \
            _ltypes.changed_size = 0; \
        } \
        renderer_update(_utype##_VAO, 0, i, data.buffer); \
    }

_DATA_UPDATE(PARJICLE, parjicle, parjicles)
_DATA_UPDATE(PARTICLE, particle, particles)
_DATA_UPDATE(PROJECTILE, projectile, projectiles)
_DATA_UPDATE(ENTITY, entity, entities)
_DATA_UPDATE(TILE, tile, tiles)
_DATA_UPDATE(WALL, wall, walls)
_DATA_UPDATE(PARSTACLE, parstacle, parstacles)
_DATA_UPDATE(OBSTACLE, obstacle, obstacles)