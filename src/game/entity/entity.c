#include "entity.h"
#include "../../util/vertex_data.h"
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
    buffer[(*length)++] = entity->position.z;
}

void entity_destroy(Entity* entity)
{
    free(entity);
}