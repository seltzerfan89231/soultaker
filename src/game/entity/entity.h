#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../../util/indices.h"
#include "../../util/framedata.h"
#include "../projectile/projectile.h"

extern f64 game_time;

#define FRIENDLY_BIT 1
#define FACE_DIR_BIT 2
#define FLAG_BIT     3

typedef struct {
    f32 speed, scale, hitbox_radius, health, max_health, timer, timer2;
    u8 friendly, face_dir, state, flag;
    u32 id;
    vec3f position, direction;
    vec2f facing;
} Entity;

Entity* entity_create(u32 id, u8 friendly);
void entity_update(Entity* entity, f32 dt);
void entity_damage(Entity *entity, u32 damage);
void entity_set_direction(Entity *entity, vec3f direction);
void entity_destroy(Entity* entity, u32 idx);

_ARRAY_DECLARE(Entity, entity)
extern EntityArray entities;

#define MAX_ENTITY_ID 3
#define KNIGHT 0
#define ENEMY  1
#define SLIME  2

#define _ENTITY_INIT(_type) \
    void _type##_init_frame_data(FrameData ***frame_data); \
    void _type##_destroy_frame_data(FrameData ***frame_data); \
    void _type##_update(Entity *entity);

_ENTITY_INIT(knight)
_ENTITY_INIT(enemy)
_ENTITY_INIT(slime)

#endif