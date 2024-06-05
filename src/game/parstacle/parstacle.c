#include "parstacle.h"
#include <stdlib.h>

Parstacle* parstacle_create(void)
{
    Parstacle *parstacle = malloc(sizeof(Parstacle));
    parstacle->scale = 1.0f;
    return parstacle;
}

void parstacle_destroy(Parstacle* parstacle)
{
    free(parstacle);
}