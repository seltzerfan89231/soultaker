#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>

typedef struct Renderer {
    int x;
} Renderer;

void renderer_init();
void renderer_render();

extern Renderer renderer;

#endif