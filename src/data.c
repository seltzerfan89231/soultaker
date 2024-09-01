#include "data.h"
#include <stdlib.h>

#define BUFFER_SIZE 50000000

Data data;
i32 i;

static u32 offset;

static void wall_push_data(Wall* wall)
{
    if (wall->id == INVISIBLE_WALL)
        return;
    assert((data.vbo_index+1)*8 < BUFFER_SIZE);
    offset = data.vbo_index * 8;
    data.vbo_index++;
    data.vbo_buffer[offset++] = wall->position.x;
    data.vbo_buffer[offset++] = wall->position.z;
    data.vbo_buffer[offset++] = wall->dimensions.w;
    data.vbo_buffer[offset++] = wall->dimensions.h;
    data.vbo_buffer[offset++] = wall->dimensions.l;
    data.vbo_buffer[offset++] = wall->top_tex;
    data.vbo_buffer[offset++] = wall->side1_tex;
    data.vbo_buffer[offset++] = wall->side2_tex;
}

static void tile_push_data(Tile* tile)
{
    assert((data.vbo_index+1)*8 < BUFFER_SIZE);
    offset = data.vbo_index * 8;
    data.vbo_index++;
    data.vbo_buffer[offset++] = tile->position.x;
    data.vbo_buffer[offset++] = tile->position.z;
    data.vbo_buffer[offset++] = tile->dimensions.w;
    data.vbo_buffer[offset++] = tile->dimensions.l;
    data.vbo_buffer[offset++] = tile->offset.x;
    data.vbo_buffer[offset++] = tile->offset.y;
    data.vbo_buffer[offset++] = tile->shadow;
    data.vbo_buffer[offset++] = tile->tex;
}

static void projectile_push_data(Projectile* projectile)
{
    assert((data.vbo_index+1)*6 < BUFFER_SIZE);
    offset = data.vbo_index * 6;
    data.vbo_index++;
    data.vbo_buffer[offset++] = projectile->position.x;
    data.vbo_buffer[offset++] = projectile->position.y;
    data.vbo_buffer[offset++] = projectile->position.z;
    data.vbo_buffer[offset++] = projectile->scale;
    data.vbo_buffer[offset++] = projectile->rotation;
    data.vbo_buffer[offset++] = projectile->tex;
}

static void entity_push_data(Entity* entity)
{
    assert((data.vbo_index+1)*10 < BUFFER_SIZE);
    offset = data.vbo_index * 10;
    data.vbo_index++;
    data.vbo_buffer[offset++] = entity->position.x;
    data.vbo_buffer[offset++] = entity->position.y;
    data.vbo_buffer[offset++] = entity->position.z;
    data.vbo_buffer[offset++] = entity->scale;
    data.vbo_buffer[offset++] = entity->health / entity->max_health;
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
    
    data.vbo_buffer[offset++] = data.frame_data[entity->id][dir][entity->state].frame;
    data.vbo_buffer[offset++] = data.frame_data[entity->id][dir][entity->state].x;
    data.vbo_buffer[offset++] = data.frame_data[entity->id][dir][entity->state].y;
    data.vbo_buffer[offset++] = data.frame_data[entity->id][dir][entity->state].w;
    data.vbo_buffer[offset++] = data.frame_data[entity->id][dir][entity->state].h;
}

static void particle_push_data(Particle *particle)
{
    assert((data.vbo_index+1)*7 < BUFFER_SIZE);
    offset = data.vbo_index * 7;
    data.vbo_index++;
    data.vbo_buffer[offset++] = particle->position.x;
    data.vbo_buffer[offset++] = particle->position.y;
    data.vbo_buffer[offset++] = particle->position.z;
    data.vbo_buffer[offset++] = particle->scale;
    data.vbo_buffer[offset++] = particle->color.r;
    data.vbo_buffer[offset++] = particle->color.g;
    data.vbo_buffer[offset++] = particle->color.b;
}

static void parstacle_push_data(Parstacle *parstacle)
{
    assert((data.vbo_index+1)*5 < BUFFER_SIZE);
    offset = data.vbo_index * 5;
    data.vbo_index++;
    data.vbo_buffer[offset++] = parstacle->position.x;
    data.vbo_buffer[offset++] = parstacle->position.y;
    data.vbo_buffer[offset++] = parstacle->position.z;
    data.vbo_buffer[offset++] = parstacle->scale;
    data.vbo_buffer[offset++] = parstacle->tex;
}

static void parjicle_push_data(Parjicle *parjicle)
{
    assert((data.vbo_index+1)*8 < BUFFER_SIZE);
    offset = data.vbo_index * 8;
    data.vbo_index++;
    data.vbo_buffer[offset++] = parjicle->position.x;
    data.vbo_buffer[offset++] = parjicle->position.y;
    data.vbo_buffer[offset++] = parjicle->position.z;
    data.vbo_buffer[offset++] = parjicle->scale;
    data.vbo_buffer[offset++] = parjicle->rotation;
    data.vbo_buffer[offset++] = parjicle->color.r;
    data.vbo_buffer[offset++] = parjicle->color.g;
    data.vbo_buffer[offset++] = parjicle->color.b;
}


static void obstacle_push_data(Obstacle *obstacle)
{
    assert((data.vbo_index+1)*5 < BUFFER_SIZE);
    offset = data.vbo_index * 5;
    data.vbo_index++;
    data.vbo_buffer[offset++] = obstacle->position.x;
    data.vbo_buffer[offset++] = obstacle->position.y;
    data.vbo_buffer[offset++] = obstacle->position.z;
    data.vbo_buffer[offset++] = obstacle->scale;
    data.vbo_buffer[offset++] = obstacle->tex;
}

void data_init(void)
{
    data.vbo_buffer = malloc(BUFFER_SIZE * sizeof(f32));
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
    free(data.vbo_buffer);
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
        data.vbo_index = 0; \
        for (i = 0; i < global_##_ltypes.length; i++) \
            _ltype##_push_data(global_##_ltypes.buffer[i]); \
        if (_ltype##_array_changed_size(&global_##_ltypes)) \
            renderer_malloc(_utype##_VAO, global_##_ltypes.max_length); \
        renderer_update(_utype##_VAO, 0, data.vbo_index, data.vbo_buffer); \
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