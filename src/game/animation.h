#ifndef ANIMATION_H
#define ANIMATION_H

#include "entity/entity.h"
#include "projectile/projectile.h"
#include "particle/particle.h"
#include "obstacle/obstacle.h"
#include "parjicle/parjicle.h"
#include "parstacle/parstacle.h"
#include "tile/tile.h"
#include "wall/wall.h"
#include "../util/type.h"
#include "../util/indices.h"

#define DOWN  0
#define RIGHT 1
#define UP    2
#define LEFT  3

#define KNIGHT_FRAMES 2
#define KNIGHT_IDLE   0
#define KNIGHT_SHOOT  1

typedef struct {
    u32 ***frames;
} Animation;

extern Animation animation;

void animation_init(void);
void animation_destroy(void);

#endif