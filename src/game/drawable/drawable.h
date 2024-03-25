#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "entity/entity.h"
#include "tile/tile.h"

#define NUM_WALL_SIDES 5
#define NUM_FLOOR_SIDES 1
#define VERTEX_COUNT 6
#define FIELD_COUNT 6
#define QUAD_DATA_LENGTH VERTEX_COUNT * FIELD_COUNT

typedef enum objtype { ENTITY, TILE } objtype;

typedef struct Drawable {
    vec3f position;
    vec3f color;
    void* obj;
    objtype type;
} Drawable;

Drawable* drawable_create(vec3f position, vec3f color, void* obj, objtype type);
void drawable_update_tilt(f32 tilt);
void drawable_update_rotation(f32 rotation);
void drawable_vertex_data(f32* buffer, Drawable* drawable, i32 offset);
void drawable_destroy(Drawable* drawable);

#endif