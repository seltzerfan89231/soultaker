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

    window.size.x = DEFAULT_WINDOW_WIDTH;
    window.size.y = DEFAULT_WINDOW_HEIGHT;
    window.handle = glfwCreateWindow(window.size.x, window.size.y, "untitled", NULL, NULL);

    window.mouse.pos.x = DEFAULT_WINDOW_WIDTH / 2;
    window.mouse.pos.y = DEFAULT_WINDOW_HEIGHT / 2;

    glfwMakeContextCurrent(window.handle);
    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window.handle, mouse_button_callback);
    glfwSetCursorPosCallback(window.handle, mouse_callback);

    gladLoadGL(glfwGetProcAddress);
    glViewport(0, 0, window.size.x, window.size.y);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_FRONT); 
}

void window_process_input(void)
{
    if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.handle, true);
}

void framebuffer_size_callback() {}
void mouse_button_callback() {}
void mouse_callback() {}

/* glfw abstractions */
int window_closed(void) { return glfwWindowShouldClose(window.handle); }
void window_poll_events(void) { glfwPollEvents(); }
void window_swap_buffers(void) { glfwSwapBuffers(window.handle); }
