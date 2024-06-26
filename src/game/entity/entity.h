#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../../util/indices.h"

#define MAX_ENTITY_ID 2
#define KNIGHT 0
#define ENEMY  1

#define ENEMY_IDLE  0
#define ENEMY_SHOOT 1

typedef struct {
    f32 speed, scale, hitbox_radius, health, max_health;
    u8 friendly, state;
    u32 id;
    vec3f position, direction;
    vec2f facing;
} Entity;

Entity* entity_create(u32 id, u8 friendly);
void entity_update(Entity* entity, f32 dt);
void entity_set_direction(Entity *entity, vec3f direction);
void entity_destroy(Entity* entity);

#endif