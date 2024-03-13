#include "drawable.h"
#include <stdlib.h>

Drawable* drawable_create(vec3f position, vec3f color, void* obj, objtype type)
{
    Drawable* drawable = malloc(sizeof(Drawable));
    drawable->position = position;
    drawable->color = color;
    drawable->obj = obj;
    drawable->type = type;
    return drawable;
}

void drawable_vertex_data(f32* buffer, Drawable* drawable, i32 offset)
{
    if (drawable->type == TILE)
        tile_vertex_data(drawable->position, drawable->color, buffer, drawable->obj, offset);
}

void drawable_destroy(Drawable* drawable)
{
    free(drawable->obj);
    free(drawable);
}