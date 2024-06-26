#ifndef ANIMATION_H
#define ANIMATION_H

#include "../../util/type.h"
#include "../../util/indices.h"
#include "entities/entities.h"

typedef struct {
    u32 ***frames;
} Animation;

void animation_init_entities(Animation *animation);
void animation_destroy_entities(Animation *animation);

#endif