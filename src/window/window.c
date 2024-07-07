#include "window.h"
#include <stdio.h>

Window window;

static void cursor_pos_callback();
static void error_callback();

extern void mouse_button_callback();
extern void key_callback();
extern void framebuffer_size_callback();

void window_init(void) 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window.size = vec2f_create(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    window.cursor.position = vec2f_create(window.size.x / 2, window.size.y / 2);
    window.handle = glfwCreateWindow(window.size.x, window.size.y, "soultaker", NULL, NULL);
    glfwMakeContextCurrent(window.handle);

    glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window.handle, mouse_button_callback);
    glfwSetCursorPosCallback(window.handle, cursor_pos_callback);
    glfwSetKeyCallback(window.handle, key_callback);
    glfwSetErrorCallback(error_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, window.size.x, window.size.y);

    window.aspect_ratio = (f32)window.size.x / window.size.y;
    window.last_frame = glfwGetTime();
    window.dt = 0;
    window.fps = 0;
}

void window_update(void)
{
    glfwPollEvents();
    glfwSwapBuffers(window.handle);
    f32 cur_frame = glfwGetTime();
    window.dt = cur_frame - window.last_frame;
    if (window.dt != 0)
        window.fps = 1 / window.dt;
    window.last_frame = cur_frame;
}

void cursor_pos_callback(GLFWwindow* handle, double xpos, double ypos)
{
    window.cursor.position.x = xpos / window.size.x;
    window.cursor.position.y = ypos / window.size.y;
}

void error_callback(int x, const char *message)
{
    printf("%d\n%s\n", x, message);
}

bool window_closed(void) { return glfwWindowShouldClose(window.handle); }
void window_close(void) { glfwSetWindowShouldClose(window.handle, 1); }
bool window_key_pressed(GLenum key) { return glfwGetKey(window.handle, key) == GLFW_PRESS; }
bool window_mouse_button_pressed(GLenum button) { return glfwGetMouseButton(window.handle, button) == GLFW_PRESS; }
