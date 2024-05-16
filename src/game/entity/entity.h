#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include <stdlib.h>

typedef enum entitytype { PLAYER, ENEMY } entitytype;

typedef struct {
    f32 speed, scale, lifetime, rotation;
    entitytype type;
    vec3f position, direction;
    vec2f tex;
} Entity;

Entity* entity_create(entitytype type);
void entity_push_data(Entity* entity, f32* buffer, u32 offset);
void entity_update_position(Entity* entity, f32 dt);
void entity_destroy(Entity* entity);

#endif