#include "storage.h"
#include <stdlib.h>

#define _STORAGE_DEFINE(type, ltype) \
    void ltype##_storage_destroy(type##Storage storage) { \
        free(storage.vertex_buffer); \
        for (i32 i = 0; i < storage.length; i++) \
            ltype##_destroy(storage.obj_buffer[i]); \
        free(storage.obj_buffer); \
    }

_STORAGE_DEFINE(Tile, tile)
_STORAGE_DEFINE(Projectile, projectile)
_STORAGE_DEFINE(Entity, entity)