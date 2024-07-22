#ifndef ARRAY_H
#define ARRAY_H

#include "type.h"
#include <stdlib.h>

#define _ARRAY_DECLARE(_type, _ltype) \
    typedef struct { \
        u32 length, max_length; \
        u8 updated; \
        _type **buffer; \
    } _type##Array; \
    _type##Array _ltype##_array_create(u32 max_length); \
    void _ltype##_array_push(_type##Array *array, _type *_ltype); \
    void _ltype##_array_cut(_type##Array *array, u32 idx); \
    bool _ltype##_array_empty(_type##Array *array); \
    void _ltype##_array_change_size(_type##Array *array); \
    bool _ltype##_array_changed_size(_type##Array *array); \
    void _ltype##_array_update(_type##Array *array); \
    bool _ltype##_array_updated(_type##Array *array); \
    void _ltype##_array_destroy(_type##Array *array);

#define CHANGED_SIZE_BIT 0
#define UPDATE_BIT 1

#define _ARRAY_DEFINE(_type, _ltype) \
    _type##Array _ltype##_array_create(u32 max_length) { \
        _type##Array array; \
        array.length = 0; \
        array.max_length = max_length; \
        array.updated = ~0; \
        array.buffer = malloc(max_length * sizeof(_type*)); \
        return array; \
    } \
    void _ltype##_array_push(_type##Array *array, _type *_ltype) { \
        _ltype##_array_update(array); \
        if (array->length >= array->max_length) { \
            array->buffer = realloc(array->buffer, (array->max_length += 100) * sizeof(_type*)); \
            _ltype##_array_change_size(array); \
        } \
        array->buffer[array->length++] = _ltype; \
    } \
    void _ltype##_array_cut(_type##Array *array, u32 idx) { \
        _ltype##_array_update(array); \
        array->buffer[idx] = array->buffer[--array->length];\
    } \
    bool _ltype##_array_empty(_type##Array *array) { \
        return array->length == 0; \
    } \
    void _ltype##_array_change_size(_type##Array *array) { \
        array->updated |= (1 << CHANGED_SIZE_BIT); \
    } \
    bool _ltype##_array_changed_size(_type##Array *array) { \
        return (array->updated >> CHANGED_SIZE_BIT) & 1; \
    } \
    void _ltype##_array_update(_type##Array *array) { \
        array->updated |= (1 << UPDATE_BIT); \
    } \
    bool _ltype##_array_updated(_type##Array *array) { \
        return (array->updated >> UPDATE_BIT) & 1; \
    } \
    void _ltype##_array_destroy(_type##Array *array) { \
        _ltype##_array_update(array); \
        while (!_ltype##_array_empty(array)) \
            _ltype##_destroy(array->buffer[0], 0); \
        array->length = 0; \
        free(array->buffer); \
    }

#endif