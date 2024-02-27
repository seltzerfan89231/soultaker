#ifndef RENDERER_H
#define RENDERER_H

typedef struct Renderer {
    int x;
} Renderer;

void renderer_init(void);

extern Renderer renderer;

#endif