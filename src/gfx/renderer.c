#include "renderer.h"

Renderer renderer;

void renderer_init() 
{
    
}

void renderer_render()
{
    glClearColor(0.6f, 0.7f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}