#ifndef ARRAY_H
#define ARRAY_H

#include "entity/entity.h"
#include "projectile/projectile.h"
#include "particle/particle.h"
#include "obstacle/obstacle.h"
#include "parjicle/parjicle.h"
#include "tile/tile.h"
#include "wall/wall.h"
#include "../util/type.h"

#define _ARRAY_DECLARE(_type, _ltype) \
    typedef struct { \
        u32 length, max_length; \
        _type **buffer; \
    } _type##Array; \
    _type##Array _ltype##_array_create(u32 max_length); \
    void _ltype##_array_push(_type##Array *array, _type *_ltype); \
    void _ltype##_array_cut(_type##Array *array, u32 idx); \
    bool _ltype##_array_empty(_type##Array *array); \
    void _ltype##_array_destroy(_type##Array *array);

_ARRAY_DECLARE(Tile, tile)
_ARRAY_DECLARE(Wall, wall)
_ARRAY_DECLARE(Projectile, projectile)
_ARRAY_DECLARE(Entity, entity)
_ARRAY_DECLARE(Particle, particle)
_ARRAY_DECLARE(Obstacle, obstacle)
_ARRAY_DECLARE(Parjicle, parjicle)

#endif