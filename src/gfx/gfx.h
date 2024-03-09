#ifndef GFX_H
#define GFX_H

#include "renderer/renderer.h"
#include "window/window.h"

inline static void gfx_init(void)
{
    window_init();
    renderer_init();
}

#endif