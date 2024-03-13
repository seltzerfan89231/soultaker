#include "drawable.h"
#include <stdlib.h>
#include <math.h>

#define NUM_WALL_SIDES 5
#define NUM_FLOOR_SIDES 1
#define VERTEX_COUNT 6
#define FIELD_COUNT 6

static f32 vertices[] = {
    0, 0, 0,
    1, 0, 0,
    1, 1, 0,
    0, 1, 0,
    0, 0, 1,
    1, 0, 1,
    1, 1, 1,
    0, 1, 1
};

static u32 sides[] = {
    2, 1, 0, 3, //-z
    7, 4, 5, 6, //+z
    6, 5, 1, 2, //+x
    3, 0, 4, 7, //-x
    2, 3, 7, 6, //+y
    0, 4, 5, 1  //-y
};

static u32 vertex_order[] = {
    0, 1, 2, 0, 2, 3
};

static void tile_vertex_data(f32* buffer, Drawable* drawable, i32 offset)
{
    i32 start, end;
    Tile* tile = drawable->obj;
    start = tile->type == WALL ? 0 : NUM_WALL_SIDES;
    end   = tile->type == WALL ? NUM_WALL_SIDES : NUM_WALL_SIDES + NUM_FLOOR_SIDES;
    for (i32 s = start; s < end; s++) {
        for (i32 v = 0; v < VERTEX_COUNT; v++) {
            buffer[offset++] = vertices[3*sides[4*s+vertex_order[v]]]   + drawable->position.x;
            buffer[offset++] = vertices[3*sides[4*s+vertex_order[v]]+1] * drawable->position.y;
            buffer[offset++] = vertices[3*sides[4*s+vertex_order[v]]+2] + drawable->position.z;
            buffer[offset++] = drawable->color.x + s * 0.1;
            buffer[offset++] = drawable->color.y + s * 0.1;
            buffer[offset++] = drawable->color.z + s * 0.1;
        }
    }
}

static void entity_vertex_data(f32* buffer, Drawable* drawable, i32 offset, f32 rotation)
{
    for (i32 v = 0; v < VERTEX_COUNT; v++) {
        buffer[offset++] = (vertices[3*sides[4*5+vertex_order[v]]]   + drawable->position.x) * cos(rotation);
        buffer[offset++] = vertices[3*sides[4*5+vertex_order[v]]+1] + drawable->position.y;
        buffer[offset++] = (vertices[3*sides[4*5+vertex_order[v]]+2] + drawable->position.z) * sin(rotation);
        buffer[offset++] = drawable->color.x;
        buffer[offset++] = drawable->color.y;
        buffer[offset++] = drawable->color.z;
    }
}

Drawable* drawable_create(vec3f position, vec3f color, void* obj, objtype type)
{
    Drawable* drawable = malloc(sizeof(Drawable));
    drawable->position = position;
    drawable->color = color;
    drawable->obj = obj;
    drawable->type = type;
    return drawable;
}

void drawable_vertex_data(f32* buffer, Drawable* drawable, i32 offset, f32 rotation)
{
    switch(drawable->type)
    {
        case TILE:
            tile_vertex_data(buffer, drawable, offset);
            break;
        case ENTITY:
            entity_vertex_data(buffer, drawable, offset, rotation);
            break;
    }
}

void drawable_destroy(Drawable* drawable)
{
    switch(drawable->type)
    {
        case TILE:
            tile_destroy(drawable->obj);
            break;
        case ENTITY:
            entity_destroy(drawable->obj);
            break;
    }
    free(drawable);
}