#ifndef STORAGE_H
#define STORAGE_H

#include "entity/entity.h"
#include "projectile/projectile.h"
#include "tile/tile.h"
#include "wall/wall.h"
#include "../util/type.h"

#define _STORAGE_DECLARE(type, ltype) \
    typedef struct { \
        u32 length; \
        f32 *vertex_buffer; \
        type **obj_buffer; \
    } type##Storage; \
    void ltype##_storage_destroy(type##Storage storage);

_STORAGE_DECLARE(Tile, tile)
_STORAGE_DECLARE(Wall, wall)
_STORAGE_DECLARE(Projectile, projectile)
_STORAGE_DECLARE(Entity, entity)


#endif