#include "animation.h"
#include <stdlib.h>

void animation_init_entities(Animation *animation)
{
    animation->frame_data = malloc(MAX_ENTITY_ID * sizeof(FrameData**));
    knight_init(animation->frame_data);
}

void animation_destroy_entities(Animation *animation)
{
    knight_destroy(animation->frame_data);
    free(animation->frame_data);
}