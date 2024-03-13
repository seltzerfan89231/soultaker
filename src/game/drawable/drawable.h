#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "entity/entity.h"
#include "tile/tile.h"

typedef enum objtype { ENTITY, TILE } objtype;

typedef struct Drawable {
    vec3f position;
    vec3f color;
    void* obj;
    objtype type;
} Drawable;

Drawable* drawable_create(vec3f position, vec3f color, void* obj, objtype type);
void drawable_vertex_data(f32* buffer, Drawable* drawable, i32 offset, f32 rotation);
void drawable_destroy(Drawable* drawable);

#endif