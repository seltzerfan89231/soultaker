#include "window.h"
#include <stdio.h>

Window window;
Mouse mouse;

void window_init(void) 
{
    mouse.position.x = 0;
    mouse.position.y = 1;
    window.size.x = 1;
    window.size.y = 0;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /*
    window.size.x = DEFAULT_WINDOW_WIDTH;
    window.size.y = DEFAULT_WINDOW_HEIGHT;
    window.handle = glfwCreateWindow(window.size.x, window.size.y, "untitled", NULL, NULL);

    mouse.position.x = DEFAULT_WINDOW_WIDTH / 2;
    mouse.position.y = DEFAULT_WINDOW_HEIGHT / 2;

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
    */
}