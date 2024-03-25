#include "drawable.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.141592653589
#define HALFPI 1.57079632679
#define BOTRIGHTDIS 0.5
#define SQRT2 1.41421356237

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

static f32 trig[10];

static void tile_vertex_data(f32* buffer, Drawable* drawable, i32 offset)
{
    i32 start, end;
    Tile* tile = drawable->obj;
    start = tile->type == WALL ? 0 : NUM_WALL_SIDES;
    end   = tile->type == WALL ? NUM_WALL_SIDES : NUM_WALL_SIDES + NUM_FLOOR_SIDES;
    for (i32 s = start; s < end; s++) {
        for (i32 v = 0; v < VERTEX_COUNT; v++) {
            buffer[offset++] = drawable->position.x + vertices[3*sides[4*s+vertex_order[v]]];
            buffer[offset++] = drawable->position.y * vertices[3*sides[4*s+vertex_order[v]]+1];
            buffer[offset++] = drawable->position.z + vertices[3*sides[4*s+vertex_order[v]]+2];
            buffer[offset++] = drawable->color.x + s * 0.1;
            buffer[offset++] = drawable->color.y + s * 0.1;
            buffer[offset++] = drawable->color.z + s * 0.1;
        }
    }
}

static void entity_vertex_data(f32* buffer, Drawable* drawable, i32 offset)
{
    f32 var = ((Entity*)drawable->obj)->scale / 2;
    f32 var2 = var * SQRT2;
    for (i32 v = 0; v < VERTEX_COUNT; v++) {
        f32 y_offset = (2 - trig[0]) / trig[1] * var;
        switch (vertex_order[v]) {
            case 0:
                buffer[offset++] = drawable->position.x + trig[2] * var;
                buffer[offset++] = drawable->position.y;
                buffer[offset++] = drawable->position.z + trig[3] * var;
                break;
            case 1:
                buffer[offset++] = drawable->position.x + trig[4] * var2;
                buffer[offset++] = drawable->position.y + y_offset;
                buffer[offset++] = drawable->position.z + trig[5] * var2;
                break;
            case 2:
                buffer[offset++] = drawable->position.x + trig[6] * var2;
                buffer[offset++] = drawable->position.y + y_offset;
                buffer[offset++] = drawable->position.z + trig[7] * var2;
                break;
            case 3:
                buffer[offset++] = drawable->position.x + trig[8] * var;
                buffer[offset++] = drawable->position.y;
                buffer[offset++] = drawable->position.z + trig[9] * var;
                break;
        }
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

void drawable_update_tilt(f32 tilt)
{
    trig[0] = cos(tilt + HALFPI);
    trig[1] = sin(tilt + HALFPI);
}

void drawable_update_rotation(f32 rotation)
{
    trig[2] = cos(rotation + HALFPI);
    trig[3] = sin(rotation + HALFPI);
    trig[4] = cos(rotation + 3 * PI / 4);
    trig[5] = sin(rotation + 3 * PI / 4);
    trig[6] = cos(rotation + 5 * PI / 4);
    trig[7] = sin(rotation + 5 * PI / 4);
    trig[8] = cos(rotation - HALFPI);
    trig[9] = sin(rotation - HALFPI);
}

void drawable_vertex_data(f32* buffer, Drawable* drawable, i32 offset)
{
    switch(drawable->type)
    {
        case TILE:
            tile_vertex_data(buffer, drawable, offset);
            break;
        case ENTITY:
            entity_vertex_data(buffer, drawable, offset);
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