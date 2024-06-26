#include "animation.h"
#include <stdlib.h>

void animation_init_entities(Animation *animation)
{
    animation->frames = malloc(MAX_ENTITY_ID * sizeof(u32**));
    knight_init(animation->frames);
}

void animation_destroy_entities(Animation *animation)
{
    knight_destroy(animation->frames);
    free(animation->frames);
}