#include "drawable.h"
#include <stdlib.h>
#include <math.h>

#define NUM_WALL_SIDES 5
#define NUM_FLOOR_SIDES 1
#define VERTEX_COUNT 6
#define FIELD_COUNT 6

#define PI 3.141592653589
#define HALFPI 1.57079632679
#define BOTRIGHTDIS 0.5
#define TOPRIGHTDIS 1.11803398875
#define ATAN2 1.10714872

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
            buffer[offset++] = drawable->position.x + vertices[3*sides[4*s+vertex_order[v]]];
            buffer[offset++] = drawable->position.y * vertices[3*sides[4*s+vertex_order[v]]+1];
            buffer[offset++] = drawable->position.z + vertices[3*sides[4*s+vertex_order[v]]+2];
            buffer[offset++] = drawable->color.x + s * 0.1;
            buffer[offset++] = drawable->color.y + s * 0.1;
            buffer[offset++] = drawable->color.z + s * 0.1;
        }
    }
}

static void entity_vertex_data(f32* buffer, Drawable* drawable, i32 offset, f32 rotation, f32 view_angle)
{
    for (i32 v = 0; v < VERTEX_COUNT; v++) {
        f32 y_offset = (1-0.5*cos(-view_angle + HALFPI))/sin(-view_angle + HALFPI);
        switch (vertex_order[v]) {
            case 0:
                buffer[offset++] = drawable->position.x + cos(rotation + HALFPI) * BOTRIGHTDIS;
                buffer[offset++] = drawable->position.y;
                buffer[offset++] = drawable->position.z + sin(rotation + HALFPI) * BOTRIGHTDIS;
                break;
            case 1:
                buffer[offset++] = drawable->position.x + cos(rotation + 3 * PI / 4) * sqrt(2) * 0.5;
                buffer[offset++] = drawable->position.y + y_offset;
                buffer[offset++] = drawable->position.z + sin(rotation + 3 * PI / 4) * sqrt(2) * 0.5;
                break;
            case 2:
                buffer[offset++] = drawable->position.x + cos(rotation + 5 * PI / 4) * sqrt(2) * 0.5;
                buffer[offset++] = drawable->position.y + y_offset;
                buffer[offset++] = drawable->position.z + sin(rotation + 5 * PI / 4) * sqrt(2) * 0.5;
                break;
            case 3:
                buffer[offset++] = drawable->position.x + cos(rotation - HALFPI) * BOTRIGHTDIS;
                buffer[offset++] = drawable->position.y;
                buffer[offset++] = drawable->position.z + sin(rotation - HALFPI) * BOTRIGHTDIS;
                break;
        }
        buffer[offset++] = vertex_order[v] / 3.0f;
        buffer[offset++] = 0;
        buffer[offset++] = 0;
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

void drawable_vertex_data(f32* buffer, Drawable* drawable, i32 offset, f32 rotation, f32 view_angle)
{
    switch(drawable->type)
    {
        case TILE:
            tile_vertex_data(buffer, drawable, offset);
            break;
        case ENTITY:
            entity_vertex_data(buffer, drawable, offset, rotation, view_angle);
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