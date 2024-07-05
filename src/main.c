#include "state.h"

int main()
{
    srand(0);
    state_init();
    state_loop();
    state_exit();
    return 0;
}
