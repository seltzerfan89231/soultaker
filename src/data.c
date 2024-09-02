#include "data.h"
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 50000000

Data data;
static u32 offset;

static void data_update_tiles(void);
static void data_update_walls(void);
static void data_update_entities(void);
static void data_update_projectiles(void);
static void data_update_parjicles(void);
static void data_update_particles(void);
static void data_update_parstacles(void);
static void data_update_obstacles(void);

static void wall_push_data(Wall* wall)
{
    if (wall->id == INVISIBLE_WALL)
        return;
    assert(data.vbo_length + 5 * 4 * 8 < BUFFER_SIZE);
    static u8 dx[] = {0, 0, 0, 0, 1, 1, 1, 1};
    static u8 dy[] = {0, 0, 1, 1, 0, 0, 1, 1};
    static u8 dz[] = {0, 1, 0, 1, 0, 1, 0, 1};
    static u8 tx[] = {0, 1, 1, 0};
    static u8 ty[] = {0, 0, 1, 1};
    static u8 winding[] = {0, 1, 2, 0, 2, 3};
    static u8 side_ids[] = {RIGHT, UP, TOP, LEFT, DOWN}; 
    static u8 sides[][4] = {
        {4, 5, 7, 6}, // +x
        {5, 1, 3, 7}, // +z
        {2, 6, 7, 3}, // +y
        {1, 0, 2, 3}, // -x
        {0, 4, 6, 2}  // -z
    };
    for (i32 side = 0; side < 5; side++) {
        if (wall_get_blocked(wall, side_ids[side]))
            continue;
        u32 idx = data.vbo_length / 8;
        for (i32 i = 0; i < 4; i++) {
            data.vbo_buffer[data.vbo_length++] = wall->dimensions.w * dx[sides[side][i]] + wall->position.x;
            data.vbo_buffer[data.vbo_length++] = wall->dimensions.h * dy[sides[side][i]];
            data.vbo_buffer[data.vbo_length++] = wall->dimensions.l * dz[sides[side][i]] + wall->position.z;
            data.vbo_buffer[data.vbo_length++] = wall->position.x + wall->dimensions.w / 2;
            data.vbo_buffer[data.vbo_length++] = wall->position.z + wall->dimensions.l / 2;
            data.vbo_buffer[data.vbo_length++] = tx[i];
            data.vbo_buffer[data.vbo_length++] = ty[i];
            switch (side % 3) {
                case 0:
                    data.vbo_buffer[data.vbo_length++] = wall->side1_tex; break;
                case 1:
                    data.vbo_buffer[data.vbo_length++] = wall->side2_tex; break;
                case 2:
                    data.vbo_buffer[data.vbo_length++] = wall->top_tex; break;
            }
            
        }
        for (i32 i = 0; i < 3 * 2; i++)
            data.ebo_buffer[data.ebo_length++] = idx + winding[i];
    }
}

static void tile_push_data(Tile* tile, i32 vbo_offset, i32 ebo_offset)
{
    assert(vbo_offset + 10 * 4 < BUFFER_SIZE);
    static u32 dx[] = {0, 1, 1, 0};
    static u32 dy[] = {0, 0, 1, 1};
    static u32 winding[] = {0, 1, 2, 0, 2, 3};
    u32 idx = vbo_offset / 10;
    f32 xoff, yoff;
    for (i32 i = 0; i < 4; i++) {
        data.vbo_buffer[vbo_offset++] = tile->position.x + tile->dimensions.w * dx[i];
        data.vbo_buffer[vbo_offset++] = tile->position.z + tile->dimensions.l * dy[i];
        data.vbo_buffer[vbo_offset++] = dx[i];
        data.vbo_buffer[vbo_offset++] = dy[i];
        data.vbo_buffer[vbo_offset++] = dx[i] + tile->offset.x;
        data.vbo_buffer[vbo_offset++] = dy[i] + tile->offset.y;
        data.vbo_buffer[vbo_offset++] = (dx[i] == 1) ? 0.25 : -0.25;
        data.vbo_buffer[vbo_offset++] = (dy[i] == 1) ? 0.25 : -0.25;
        data.vbo_buffer[vbo_offset++] = tile->shadow;
        data.vbo_buffer[vbo_offset++] = tile->tex;
    }
    for (i32 i = 0; i < 3 * 2; i++)
        data.ebo_buffer[ebo_offset++] = idx + winding[i];
}

static void projectile_push_data(Projectile* projectile)
{
    assert((data.vbo_length+1)*6 < BUFFER_SIZE);
    offset = data.vbo_length * 6;
    data.vbo_length++;
    data.vbo_buffer[offset++] = projectile->position.x;
    data.vbo_buffer[offset++] = projectile->position.y;
    data.vbo_buffer[offset++] = projectile->position.z;
    data.vbo_buffer[offset++] = projectile->scale;
    data.vbo_buffer[offset++] = projectile->rotation;
    data.vbo_buffer[offset++] = projectile->tex;
}

static void entity_push_data(Entity* entity)
{
    assert((data.vbo_length+1)*10 < BUFFER_SIZE);
    offset = data.vbo_length * 10;
    data.vbo_length++;
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
    assert((data.vbo_length+1)*7 < BUFFER_SIZE);
    offset = data.vbo_length * 7;
    data.vbo_length++;
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
    assert((data.vbo_length+1)*5 < BUFFER_SIZE);
    offset = data.vbo_length * 5;
    data.vbo_length++;
    data.vbo_buffer[offset++] = parstacle->position.x;
    data.vbo_buffer[offset++] = parstacle->position.y;
    data.vbo_buffer[offset++] = parstacle->position.z;
    data.vbo_buffer[offset++] = parstacle->scale;
    data.vbo_buffer[offset++] = parstacle->tex;
}

static void parjicle_push_data(Parjicle *parjicle)
{
    assert((data.vbo_length+1)*8 < BUFFER_SIZE);
    offset = data.vbo_length * 8;
    data.vbo_length++;
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
    assert((data.vbo_length+1)*5 < BUFFER_SIZE);
    offset = data.vbo_length * 5;
    data.vbo_length++;
    data.vbo_buffer[offset++] = obstacle->position.x;
    data.vbo_buffer[offset++] = obstacle->position.y;
    data.vbo_buffer[offset++] = obstacle->position.z;
    data.vbo_buffer[offset++] = obstacle->scale;
    data.vbo_buffer[offset++] = obstacle->tex;
}

void data_init(void)
{
    data.vbo_buffer = malloc(BUFFER_SIZE * sizeof(f32));
    data.ebo_buffer = malloc(BUFFER_SIZE * sizeof(u32));
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
    free(data.ebo_buffer);
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
        data.vbo_length = data.ebo_length = 0; \
        for (i32 i = 0; i < global_##_ltypes.length; i++) \
            _ltype##_push_data(global_##_ltypes.buffer[i]); \
        if (_ltype##_array_changed_size(&global_##_ltypes)) \
            renderer_malloc(_utype##_VAO, global_##_ltypes.max_length, 0); \
        renderer_update(_utype##_VAO, 0, data.vbo_length, data.vbo_buffer, 0, 0, NULL); \
        global_##_ltypes.updated = 0; \
    }

_DATA_UPDATE(PARJICLE, parjicle, parjicles)
_DATA_UPDATE(PARTICLE, particle, particles)
_DATA_UPDATE(PROJECTILE, projectile, projectiles)
_DATA_UPDATE(ENTITY, entity, entities)
_DATA_UPDATE(PARSTACLE, parstacle, parstacles)
_DATA_UPDATE(OBSTACLE, obstacle, obstacles)

void data_update_tiles(void)
{
    if (!tile_array_updated(&global_tiles))
        return;
    data.vbo_length = data.ebo_length = 0;
    for (i32 i = 0; i < global_tiles.length; i++)
        tile_push_data(global_tiles.buffer[i]);
    if (tile_array_changed_size(&global_tiles))
        renderer_malloc(TILE_VAO, global_tiles.max_length * 4 * 10, global_tiles.max_length * 6);
    renderer_update(TILE_VAO, 0, data.vbo_length, data.vbo_buffer, 0, data.ebo_length, data.ebo_buffer);
    global_tiles.updated = 0;
}

void data_update_walls(void)
{
    if (!wall_array_updated(&global_walls))
        return;
    data.vbo_length = data.ebo_length = 0;
    for (i32 i = 0; i < global_walls.length; i++)
        wall_push_data(global_walls.buffer[i]);
    if (wall_array_changed_size(&global_walls))
        renderer_malloc(WALL_VAO, global_walls.max_length * 5 * 4 * 8, global_walls.max_length * 5 * 6);
    renderer_update(WALL_VAO, 0, data.vbo_length, data.vbo_buffer, 0, data.ebo_length, data.ebo_buffer);
    global_walls.updated = 0;
}
