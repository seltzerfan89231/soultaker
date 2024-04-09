#ifndef BUFFERTYPE_H
#define BUFFERTYPE_H

#define MAX_BUFFER_LENGTH 1000000
#define QUAD_VERTEX_COUNT 6
#define TILE_VERTEX_LENGTH 5
#define ENTITY_VERTEX_LENGTH 2
#define GUI_VERTEX_LENGTH 5
#define NUM_BUFFER_TYPES 3

typedef enum buffertype { TILE, ENTITY, GUI } buffertype;

#endif