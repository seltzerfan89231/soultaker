#ifndef AOE_H
#define AOE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../particle/particle.h"
#include "../entity/entity.h"

typedef struct {
    struct {
        f32 x, z;
    } position;
    f32 radius;
    f32 timer;
} AOE;

AOE* aoe_create(f32 x, f32 z);
void aoe_update_timer(AOE* aoe, f32 dt);
void aoe_update(AOE* aoe);
void aoe_hit(AOE* aoe, Entity* entity);
void aoe_destroy(AOE* aoe, u32 idx);
void destroy_all_aoes(void);

_ARRAY_DECLARE(AOE, aoe)
extern AOEArray global_aoes;

#endif