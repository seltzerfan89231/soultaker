#ifndef WINDOW_H
#define WINDOW_H

#include <glad.h>
#include <glfw.h>
#include "../util/type.h"
#include "../util/vec.h"

#define DEFAULT_WINDOW_WIDTH 1920/2
#define DEFAULT_WINDOW_HEIGHT 1080/2

typedef enum mousebutton { MOUSE_LEFT, MOUSE_MIDDLE, MOUSE_RIGHT } mousebutton;
typedef enum mbstate { UP, DOWN } mbstate;

typedef struct Mouse {
    vec2f position;
    mbstate left;
    mbstate middle;
    mbstate right;
} Mouse;

typedef struct Window {
    GLFWwindow* handle;
    vec2f size;
    Mouse mouse;
    f32 aspect_ratio, last_frame, dt, fps;
} Window;

extern Window window;

void window_init(void);
void window_update(void);
void window_calc_dt(void);
i2 window_mouse_button_pressed(mousebutton mb);
i2 window_closed(void);
void window_close(void);
i2 window_key_pressed(GLenum key);

#endif