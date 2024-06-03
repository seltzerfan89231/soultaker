#ifndef PARJICLE_H
#define PARJICLE_H

#include "../../util/type.h"
#include "../../util/vec.h"

typedef struct {
    f32 scale, rotation;
} Parjicle;

Parjicle *parjicle_create(void);
void parjicle_destroy(Parjicle *parj);

#endif