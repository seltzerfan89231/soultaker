#include "entity.h"
#include <stdlib.h>

Entity* entity_create(entitytype type)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->type = type;
    return entity;
}

void entity_destroy(Entity* entity)
{
    free(entity);
}