#include "sll.h"
#include <stdlib.h>

SLL sll_create(void)
{
    SLL sll;
    sll.head = NULL;
    return sll;
}