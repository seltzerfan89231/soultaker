#include "parstacle.h"
#include <stdlib.h>
#include <assert.h>

ParstacleArray parstacles;

Parstacle* parstacle_create(void)
{
    Parstacle *parstacle = malloc(sizeof(Parstacle));
    parstacle->scale = 1.0f;
    parstacle->tex = BUSH_TEX;
    parstacle_array_push(&parstacles, parstacle);
    return parstacle;
}

void parstacle_destroy(Parstacle* parstacle, u32 idx)
{
    assert(parstacle == parstacles.buffer[idx]);
    parstacle_array_cut(&parstacles, idx);
    free(parstacle);
}

void destroy_all_parstacles(void)
{
    for (i32 i = 0; i < parstacles.length; i++)
        free(parstacles.buffer[i]);
    parstacle_array_destroy(&parstacles);
}

_ARRAY_DEFINE(Parstacle, parstacle)