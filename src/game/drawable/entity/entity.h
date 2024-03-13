#ifndef ENTITY_H
#define ENTITY_H

typedef enum entitytype { PLAYER } entitytype;

typedef struct Entity {
    entitytype type;
} Entity;

Entity* entity_create(entitytype type);
void entity_destroy(Entity* entity);

#endif