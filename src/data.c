#include "data.h"
#include <stdlib.h>

#define BUFFER_SIZE 50000000

Data data;
i32 i;

static void wall_push_data(Wall* wall, u32 offset)
{
    assert((offset+1)*5 < BUFFER_SIZE);
    offset *= 5;
    data.buffer[offset++] = wall->position.x;
    data.buffer[offset++] = wall->height;
    data.buffer[offset++] = wall->position.z;
    data.buffer[offset++] = wall->top_tex;
    data.buffer[offset++] = wall->side_tex;
}

static void tile_push_data(Tile* tile, u32 offset)
{
    assert((offset+1)*3 < BUFFER_SIZE);
    offset *= 3;
    data.buffer[offset++] = tile->position.x;
    data.buffer[offset++] = tile->position.z;
    data.buffer[offset++] = tile->tex;
}

static void projectile_push_data(Projectile* projectile, u32 offset)
{
    assert((offset+1)*6 < BUFFER_SIZE);
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
    assert((offset+1)*10 < BUFFER_SIZE);
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
    assert((offset+1)*7 < BUFFER_SIZE);
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
    assert((offset+1)*5 < BUFFER_SIZE);
    offset *= 5;
    data.buffer[offset++] = parstacle->position.x;
    data.buffer[offset++] = parstacle->position.y;
    data.buffer[offset++] = parstacle->position.z;
    data.buffer[offset++] = parstacle->scale;
    data.buffer[offset++] = parstacle->tex;
}

static void parjicle_push_data(Parjicle *parjicle, u32 offset)
{
    assert((offset+1)*8 < BUFFER_SIZE);
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
    assert((offset+1)*5 < BUFFER_SIZE);
    offset *= 5;
    data.buffer[offset++] = obstacle->position.x;
    data.buffer[offset++] = obstacle->position.y;
    data.buffer[offset++] = obstacle->position.z;
    data.buffer[offset++] = obstacle->scale;
    data.buffer[offset++] = obstacle->tex;
}

void data_init(void)
{
    data.buffer = malloc(BUFFER_SIZE * sizeof(f32));
    data.frame_data = malloc(MAX_ENTITY_ID * sizeof(FrameData**));
    knight_init_frame_data(data.frame_data);
    enemy_init_frame_data(data.frame_data);
    slime_init_frame_data(data.frame_data);
    training_dummy_init_frame_data(data.frame_data);
}

void data_destroy(void)
{
    knight_destroy_frame_data(data.frame_data);
    enemy_destroy_frame_data(data.frame_data);
    slime_destroy_frame_data(data.frame_data);
    training_dummy_destroy_frame_data(data.frame_data);
    free(data.frame_data);
    free(data.buffer);
}

void data_update(void)
{
    game_wait();
    data_update_entities();
    data_update_projectiles();
    data_update_parjicles();
    data_update_particles();
    data_update_tiles();
    data_update_walls();
    data_update_parstacles();
    data_update_obstacles();
    game_post();
}

#define _DATA_UPDATE(_utype, _ltype, _ltypes) \
    void data_update_##_ltypes(void) { \
        if (!_ltype##_array_updated(&global_##_ltypes)) \
            return; \
        for (i = 0; i < global_##_ltypes.length; i++) \
            _ltype##_push_data(global_##_ltypes.buffer[i], i); \
        if (_ltype##_array_changed_size(&global_##_ltypes)) \
            renderer_malloc(_utype##_VAO, global_##_ltypes.max_length); \
        renderer_update(_utype##_VAO, 0, i, data.buffer); \
        global_##_ltypes.updated = 0; \
    }

_DATA_UPDATE(PARJICLE, parjicle, parjicles)
_DATA_UPDATE(PARTICLE, particle, particles)
_DATA_UPDATE(PROJECTILE, projectile, projectiles)
_DATA_UPDATE(ENTITY, entity, entities)
_DATA_UPDATE(TILE, tile, tiles)
_DATA_UPDATE(WALL, wall, walls)
_DATA_UPDATE(PARSTACLE, parstacle, parstacles)
_DATA_UPDATE(OBSTACLE, obstacle, obstacles)