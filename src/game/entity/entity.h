#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../../util/indices.h"
#include "../../util/framedata.h"
#include "../projectile/projectile.h"
#include "../parstacle/parstacle.h"

#define FRIENDLY_BIT 1
#define FACE_DIR_BIT 2
#define FLAG_BIT     3

typedef struct {
    f32 speed, scale, hitbox_radius, timer, timer2, health, max_health;
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
void destroy_all_entities(void);

_ARRAY_DECLARE(Entity, entity)
extern EntityArray global_entities;

#define MAX_ENTITY_ID 4
#define KNIGHT 0
#define ENEMY  1
#define SLIME  2
#define TRAINING_DUMMY 3

#define _ENTITY_INIT(_type) \
    void _type##_init_frame_data(FrameData ***frame_data); \
    void _type##_destroy_frame_data(FrameData ***frame_data); \
    void _type##_create(Entity *entity); \
    void _type##_update(Entity *entity); \
    void _type##_die(Entity *entity);

_ENTITY_INIT(knight)
_ENTITY_INIT(enemy)
_ENTITY_INIT(slime)
_ENTITY_INIT(training_dummy)

#endif