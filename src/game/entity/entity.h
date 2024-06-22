#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../../util/indices.h"

typedef enum { PLAYER, ENEMY } entitytype;

typedef struct {
    f32 speed, scale, lifetime, hitbox_radius, health, max_health;
    u8 friendly;
    entitytype type;
    vec3f position, direction, facing;
} Entity;

Entity* entity_create(entitytype type, u8 friendly);
void entity_update(Entity* entity, f32 dt);
void entity_set_direction(Entity *entity, vec3f direction);
void entity_destroy(Entity* entity);

#endif