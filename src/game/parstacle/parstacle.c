#include "parstacle.h"
#include <stdlib.h>

ParstacleArray parstacles;

Parstacle* parstacle_create(void)
{
    Parstacle *parstacle = malloc(sizeof(Parstacle));
    parstacle->scale = 1.0f;
    parstacle->tex = BUSH_TEX;
    parstacle_array_push(&parstacles, parstacle);
    return parstacle;
}

void parstacle_destroy(Parstacle* parstacle)
{
    free(parstacle);
}

_ARRAY_DEFINE(Parstacle, parstacle)