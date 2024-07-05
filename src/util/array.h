#ifndef ARRAY_H
#define ARRAY_H

#include "type.h"
#include <stdlib.h>

#define _ARRAY_DECLARE(_type, _ltype) \
    typedef struct { \
        u32 length, max_length; \
        u8 changed_size; \
        _type **buffer; \
    } _type##Array; \
    _type##Array _ltype##_array_create(u32 max_length); \
    void _ltype##_array_push(_type##Array *array, _type *_ltype); \
    void _ltype##_array_cut(_type##Array *array, u32 idx); \
    bool _ltype##_array_empty(_type##Array *array); \
    void _ltype##_array_destroy(_type##Array *array);

#define _ARRAY_DEFINE(_type, _ltype) \
    _type##Array _ltype##_array_create(u32 max_length) { \
        _type##Array array; \
        array.length = 0; \
        array.max_length = max_length; \
        array.changed_size = 1; \
        array.buffer = malloc(max_length * sizeof(_type*)); \
        return array; \
    } \
    void _ltype##_array_push(_type##Array *array, _type *_ltype) { \
        if (array->length >= array->max_length) { \
            array->buffer = realloc(array->buffer, (array->max_length += 100) * sizeof(_type*)); \
            array->changed_size = 1; \
        } \
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

#endif