#include "entity.h"
#include <stdlib.h>

Entity* entity_create(entitytype type, f32 scale)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->type = type;
    entity->scale = scale;
    entity->speed = 1;
    entity->lifetime = 5;
    entity->direction = vec3f_create(0, 0, 0);
    return entity;
}

void entity_destroy(Entity* entity)
{
    free(entity);
}