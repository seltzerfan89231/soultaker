#ifndef AOE_H
#define AOE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../particle/particle.h"
#include "../parjicle/parjicle.h"
#include "../entity/entity.h"

typedef struct {
    struct {
        f32 x, z;
    } position;
    f32 radius;
    i32 damage;
    bool friendly;
} AOE;

AOE* aoe_create(f32 x, f32 z, bool friendly);
void aoe_destroy(AOE* aoe, u32 idx);
void destroy_all_aoes(void);

_ARRAY_DECLARE(AOE, aoe)
extern AOEArray global_aoes;

#endif