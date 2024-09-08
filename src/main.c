#include "state.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    srand(0);
    atexit(state_exit);
    state_init();
    state_loop();
    return 0;
}
