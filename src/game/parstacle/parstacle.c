#include "parstacle.h"
#include <stdlib.h>
#include <assert.h>

ParstacleArray global_parstacles;

Parstacle* parstacle_create(void)
{
    Parstacle *parstacle = malloc(sizeof(Parstacle));
    parstacle->scale = 1.0f;
    parstacle->tex = BUSH_TEX;
    parstacle_array_push(&global_parstacles, parstacle);
    return parstacle;
}

void parstacle_destroy(Parstacle* parstacle, u32 idx)
{
    assert(parstacle == global_parstacles.buffer[idx]);
    parstacle_array_cut(&global_parstacles, idx);
    free(parstacle);
}

void destroy_all_parstacles(void)
{
    for (i32 i = 0; i < global_parstacles.length; i++)
        free(global_parstacles.buffer[i]);
    parstacle_array_destroy(&global_parstacles);
}

_ARRAY_DEFINE(Parstacle, parstacle)