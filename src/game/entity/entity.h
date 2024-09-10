#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../../util/indices.h"
#include "../../util/framedata.h"
#include "../particle/particle.h"
#include "../parstacle/parstacle.h"

#define FRIENDLY_BIT 1
#define FACE_DIR_BIT 2
#define FLAG_BIT     3

typedef struct {
    f32 speed, scale, hitbox_radius, health, max_health;
    // state for textures, phase for behavior
    u8 state, phase;
    bool friendly, face_dir, flag, ground_level, invisible;
    u32 id;
    vec3f position, direction;
    vec2f facing;
    // entity dependent data
    void* data;
} Entity;

Entity* entity_create(u32 id, u8 friendly);
void entity_update(Entity* entity, f32 dt);
void entity_damage(Entity *entity, f32 damage);
void entity_set_direction(Entity *entity, vec3f direction);
void entity_destroy(Entity* entity, u32 idx);
void destroy_all_entities(void);

_ARRAY_DECLARE(Entity, entity)
extern EntityArray global_entities;

#define MAX_ENTITY_ID 6
#define KNIGHT 0
#define ENEMY  1
#define SLIME  2
#define TRAINING_DUMMY 3
#define SHAITAN_THE_ADVISOR 4
#define SHAITAN_HAND 5

#define _ENTITY_INIT(_type) \
    void _type##_init_frame_data(FrameData ***frame_data); \
    void _type##_destroy_frame_data(FrameData ***frame_data); \
    void _type##_create(Entity *entity); \
    void _type##_update(Entity *entity, f32 dt); \
    void _type##_damage(Entity *entity, f32 damage); \
    void _type##_die(Entity *entity);

_ENTITY_INIT(knight)
_ENTITY_INIT(enemy)
_ENTITY_INIT(slime)
_ENTITY_INIT(training_dummy)
_ENTITY_INIT(shaitan_the_advisor)
_ENTITY_INIT(shaitan_hand)

#endif