#include "window.h"
#include <stdbool.h>

Window window;

static void framebuffer_size_callback();
static void mouse_button_callback();
static void mouse_callback();

void window_init(void) 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window.size = vec2u_create(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    window.mouse.position = vec2u_create(window.size.x / 2, window.size.y / 2);
    window.handle = glfwCreateWindow(window.size.x, window.size.y, "untitled", NULL, NULL);
    glfwMakeContextCurrent(window.handle);

    glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window.handle, mouse_button_callback);
    glfwSetCursorPosCallback(window.handle, mouse_callback);

    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, window.size.x, window.size.y);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_FRONT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    window.last_frame = glfwGetTime();
    window.dt = 0;
    window.fps = 0;
}

void window_calc_dt(void)
{
    f32 cur_frame = glfwGetTime();
    window.dt = cur_frame - window.last_frame;
    if (window.dt != 0)
        window.fps = 1 / window.dt;
    window.last_frame = cur_frame;
}

void framebuffer_size_callback() {}
void mouse_button_callback() {}
void mouse_callback() {}

/* abstractions */
i2 window_closed(void) { return glfwWindowShouldClose(window.handle); }
void window_close(void) { glfwSetWindowShouldClose(window.handle, true); }
void window_poll_events(void) { glfwPollEvents(); }
void window_swap_buffers(void) { glfwSwapBuffers(window.handle); }
i2 window_key_pressed(GLenum key) { return glfwGetKey(window.handle, key) == GLFW_PRESS; }