#include "window.h"
#include <stdio.h>
#include <stb_image.h>

Window window;

static void cursor_pos_callback();
static void error_callback();
static void load_images();
extern void mouse_button_callback();
extern void key_callback();
extern void framebuffer_size_callback();

void window_init(void) 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window.handle = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "soultaker", NULL, NULL);
    glfwGetWindowSize(window.handle, &window.width, &window.height);
    glfwSetWindowAspectRatio(window.handle, 16, 9);
    window.aspect_ratio = (f32)window.width / window.height;
    window.last_frame = glfwGetTime();
    window.dt = 0;
    window.fps = 0;

    glfwMakeContextCurrent(window.handle);
    load_images();
    glfwSetFramebufferSizeCallback(window.handle, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window.handle, mouse_button_callback);
    glfwSetCursorPosCallback(window.handle, cursor_pos_callback);
    glfwSetKeyCallback(window.handle, key_callback);
    glfwSetErrorCallback(error_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, window.width, window.height);
    glfwSwapInterval(0);
}

void window_toggle_fullscreen(void)
{
    GLFWmonitor* monitor = glfwGetWindowMonitor(window.handle);
    const GLFWvidmode* mode;
    if (monitor != NULL)
        glfwSetWindowMonitor(window.handle, NULL, window.xpos, window.ypos, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0);
    else {
        glfwGetWindowPos(window.handle, &window.xpos, &window.ypos);
        glfwGetWindowSize(window.handle, &window.width, &window.height);
        GLFWmonitor* full_monitor = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(full_monitor);
        glfwSetWindowMonitor(window.handle, full_monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    window.cursor.position = vec2f_create(window.width / 2, window.height / 2);
    window.aspect_ratio = (f32)window.width / window.height;
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
    window.cursor.position.x = xpos / window.width;
    window.cursor.position.y = ypos / window.height;
}

void error_callback(int x, const char *message)
{
    printf("%d\n%s\n", x, message);
}

void window_close(void) 
{
    glfwDestroyCursor(window.cursor.handle);
    glfwSetWindowShouldClose(window.handle, 1); 
}

bool window_closed(void) { return glfwWindowShouldClose(window.handle); }
bool window_key_pressed(GLenum key) { return glfwGetKey(window.handle, key) == GLFW_PRESS; }
bool window_mouse_button_pressed(GLenum button) { return glfwGetMouseButton(window.handle, button) == GLFW_PRESS; }

static void load_images()
{
    GLFWimage images[2], cursor_image;

    images[0].pixels = stbi_load("assets/textures/my_icon.png", &images[0].width, &images[0].height, 0, 4);
    images[1].pixels = stbi_load("assets/textures/my_icon_small.png", &images[1].width, &images[1].height, 0, 4);
    glfwSetWindowIcon(window.handle, 2, images);

    cursor_image.pixels = stbi_load("assets/textures/cursor.png", &cursor_image.width, &cursor_image.height, 0, 4);
    window.cursor.handle = glfwCreateCursor(&cursor_image, 8, 8);
    glfwSetCursor(window.handle, window.cursor.handle);

    stbi_image_free(images[0].pixels);
    stbi_image_free(images[1].pixels);
    stbi_image_free(cursor_image.pixels);
}