#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../../util/indices.h"

#include "knight.h"

#define MAX_ENTITY_ID 2

typedef enum {
    KNIGHT = 0,
    ENEMY = 1
} EntityID;

typedef struct {
    f32 speed, scale, hitbox_radius, health, max_health;
    u8 friendly, frame;
    EntityID id;
    vec3f position, direction;
    vec2f facing;
} Entity;

extern u32 **frames;

Entity* entity_create(EntityID id, u8 friendly);
void entity_update(Entity* entity, f32 dt);
void entity_set_direction(Entity *entity, vec3f direction);
void entity_destroy(Entity* entity);
void entity_frames_init(void);
void entity_frames_destroy(void);

#endif