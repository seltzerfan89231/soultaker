#include "window.h"

Window window;

static void framebuffer_size_callback();
static void mouse_button_callback();
static void mouse_callback();

void window_init(void) 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window.size = vec2f_create(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    window.mouse.position = vec2f_create(window.size.x / 2, window.size.y / 2);
    window.handle = glfwCreateWindow(window.size.x, window.size.y, "untitled", NULL, NULL);
    glfwMakeContextCurrent(window.handle);

    window.mouse.left = UP;
    window.mouse.middle = UP;
    window.mouse.right = UP;

    glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window.handle, mouse_button_callback);
    glfwSetCursorPosCallback(window.handle, mouse_callback);

    gladLoadGL(glfwGetProcAddress);
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

void framebuffer_size_callback() {}

void mouse_button_callback(GLFWwindow* handle, int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        window.mouse.left = DOWN;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        window.mouse.left = UP;
}

void mouse_callback(GLFWwindow* handle, double xpos, double ypos)
{
    window.mouse.position.x = xpos / window.size.x;
    window.mouse.position.y = ypos / window.size.y;
}

i2 window_mouse_button_pressed(mousebutton mb)
{
    switch (mb) 
    {
        case MOUSE_LEFT:
            return window.mouse.left == DOWN;
        case MOUSE_MIDDLE:
            return window.mouse.middle == DOWN;
        case MOUSE_RIGHT:
            return window.mouse.right == DOWN;
    }
    return UP;
}

i2 window_closed(void) { return glfwWindowShouldClose(window.handle); }
void window_close(void) { glfwSetWindowShouldClose(window.handle, 1); }
i2 window_key_pressed(GLenum key) { return glfwGetKey(window.handle, key) == GLFW_PRESS; }