#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../../util/indices.h"

#include "entities/entities.h"

typedef struct {
    f32 speed, scale, hitbox_radius, health, max_health, timer;
    u8 friendly, face_dir, state;
    u32 id;
    vec3f position, direction;
    vec2f facing;
} Entity;

Entity* entity_create(u32 id, u8 friendly);
void entity_update(Entity* entity, f32 dt);
void entity_set_state(Entity *entity, u32 state);
void entity_set_direction(Entity *entity, vec3f direction);
void entity_destroy(Entity* entity);

_ARRAY_DECLARE(Entity, entity)

#endif