#include "array.h"
#include <stdlib.h>

#define _ARRAY_DEFINE(_type, _ltype) \
    _type##Array _ltype##_array_create(u32 max_length) { \
        _type##Array array; \
        array.length = 0; \
        array.max_length = max_length; \
        array.buffer = malloc(max_length * sizeof(_type*)); \
        return array; \
    } \
    void _ltype##_array_push(_type##Array *array, _type *_ltype) { \
        array->buffer[array->length++] = _ltype; \
    } \
    void _ltype##_array_cut(_type##Array *array, u32 idx) { \
        _ltype##_destroy(array->buffer[idx]); \
        array->buffer[idx] = array->buffer[--array->length];\
    } \
    bool _ltype##_array_empty(_type##Array *array) { \
        return array->length == 0; \
    } \
    void _ltype##_array_destroy(_type##Array *array) { \
        for (i32 i = 0; i < array->length; i++) \
            _ltype##_destroy(array->buffer[i]); \
        free(array->buffer); \
    }

_ARRAY_DEFINE(Tile, tile)
_ARRAY_DEFINE(Wall, wall)
_ARRAY_DEFINE(Projectile, projectile)
_ARRAY_DEFINE(Entity, entity)
_ARRAY_DEFINE(Particle, particle)
_ARRAY_DEFINE(Obstacle, obstacle)
_ARRAY_DEFINE(Parjicle, parjicle)
_ARRAY_DEFINE(Parstacle, parstacle)