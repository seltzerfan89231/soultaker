#ifndef WINDOW_H
#define WINDOW_H

#include <glad.h>
#include <glfw.h>
#include "../util/type.h"
#include "../util/vec.h"

#define DEFAULT_WINDOW_WIDTH 1920/2
#define DEFAULT_WINDOW_HEIGHT 1080/2

typedef struct {
    GLFWwindow *handle;
    struct {
        vec2f position;
    } cursor;
    f32 aspect_ratio, last_frame, dt, fps;
    i32 xpos, ypos, width, height;
} Window;

extern Window window;

void window_init(void);
void window_toggle_fullscreen(void);
void window_update(void);
void window_calc_dt(void);
bool window_closed(void);
void window_close(void);
bool window_mouse_button_pressed(GLenum button);
bool window_key_pressed(GLenum key);

#endif