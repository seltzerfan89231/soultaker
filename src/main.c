#include "state.h"
#include "audio/audio.h"

int main()
{
    srand(0);
    audio_test();
    state_init();
    state_loop();
    state_exit();
    return 0;
}
