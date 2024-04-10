#include "entity.h"
#include "../../util/vertex_data.h"
#include "../../util/buffertype.h"

static f32 trig[10];

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
    f32 var = entity->scale / 2;
    f32 var2 = var * SQRT2;
    for (i32 v = 0; v < QUAD_VERTEX_COUNT; v++) {
        f32 y_offset = (2 - trig[0]) / trig[1] * var;
        switch (vertex_order[v]) {
            case 0:
                buffer[(*length)++] = entity->position.x + trig[2] * var;
                buffer[(*length)++] = entity->position.y;
                buffer[(*length)++] = entity->position.z + trig[3] * var;
                break;
            case 1:
                buffer[(*length)++] = entity->position.x + trig[4] * var2;
                buffer[(*length)++] = entity->position.y + y_offset;
                buffer[(*length)++] = entity->position.z + trig[5] * var2;
                break;
            case 2:
                buffer[(*length)++] = entity->position.x + trig[6] * var2;
                buffer[(*length)++] = entity->position.y + y_offset;
                buffer[(*length)++] = entity->position.z + trig[7] * var2;
                break;
            case 3:
                buffer[(*length)++] = entity->position.x + trig[8] * var;
                buffer[(*length)++] = entity->position.y;
                buffer[(*length)++] = entity->position.z + trig[9] * var;
                break;
        }
        buffer[(*length)++] = entity->tex.x + tex[2*vertex_order[v]] * 0.25;
        buffer[(*length)++] = entity->tex.y + tex[2*vertex_order[v]+1] * 0.25;
    }
}

void entity_update_data(Entity* entity, f32* buffer, u32 offset)
{
    entity_push_data(entity, buffer, &offset);
}

void entity_update_position(Entity* entity)
{
    entity->position = vec3f_add(entity->position, entity->direction);
}

void entity_update_tilt(f32 tilt)
{
    trig[0] = cos(tilt + HALFPI);
    trig[1] = sin(tilt + HALFPI);
}

void entity_update_rotation(f32 rotation)
{
    trig[2] = cos(rotation + HALFPI);
    trig[3] = sin(rotation + HALFPI);
    trig[4] = cos(rotation + 3 * PI / 4);
    trig[5] = sin(rotation + 3 * PI / 4);
    trig[6] = cos(rotation - 3 * PI / 4);
    trig[7] = sin(rotation - 3 * PI / 4);
    trig[8] = cos(rotation - HALFPI);
    trig[9] = sin(rotation - HALFPI);
}

void entity_destroy(Entity* entity)
{
    free(entity);
}