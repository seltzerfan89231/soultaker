#include "entity.h"
#include <stdlib.h>

Entity* entity_create(entitytype type, f32 scale)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->type = type;
    entity->scale = scale;
    return entity;
}

void entity_destroy(Entity* entity)
{
    free(entity);
}