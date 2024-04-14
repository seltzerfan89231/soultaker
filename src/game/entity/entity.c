#include "entity.h"
#include "../../util/buffertype.h"

Entity* entity_create(entitytype type)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->type = type;
    entity->scale = 1;
    entity->speed = 1;
    entity->lifetime = 5;
    entity->direction = vec3f_create(0, 0, 0);
    return entity;
}

void entity_push_data(Entity* entity, f32* buffer, u32* length)
{
    buffer[(*length)++] = entity->position.x;
    buffer[(*length)++] = entity->position.y;
    buffer[(*length)++] = entity->position.z;
    return;
}

void entity_update_data(Entity* entity, f32* buffer, u32 offset)
{
    entity_push_data(entity, buffer, &offset);
}

void entity_update_position(Entity* entity, f32 dt)
{
    entity->position = vec3f_add(entity->position, vec3f_scale(dt * entity->speed, entity->direction));
}

void entity_destroy(Entity* entity)
{
    free(entity);
}