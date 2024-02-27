#ifndef WINDOW_H
#define WINDOW_H

#include <glad.h>
#include <glfw.h>
#include <gtype.h>
#include <gvec.h>

#define DEFAULT_WINDOW_WIDTH 1920 / 2
#define DEFAULT_WINDOW_HEIGHT 1080 / 2

typedef struct Mouse {
    vec2u pos;
} Mouse;

typedef struct Window {
    GLFWwindow *handle;
    vec2u size;
    Mouse mouse;
} Window;

void window_init();
void window_process_input();

/* glfw abstractions */
int window_closed();
void window_poll_events();
void window_swap_buffers();

extern Window window;

#endif