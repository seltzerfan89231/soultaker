#include "renderer.h"

Renderer renderer;

static void renderer_settings(void)
{
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); 
    glEnable(GL_MULTISAMPLE);
    glCullFace(GL_FRONT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwWindowHint(GLFW_SAMPLES, NUM_SAMPLES);
}

void renderer_init(void) 
{
    renderer.shaders[DRAWABLE] = shader_create("src/shaders/drawable_vertex.sl", "src/shaders/drawable_fragment.sl");
    renderer.usage[DRAWABLE] = GL_DYNAMIC_DRAW;
    renderer.vaos[DRAWABLE] = vao_create();
    vao_attr(&renderer.vaos[DRAWABLE], 0, 3, 5, 0);
    vao_attr(&renderer.vaos[DRAWABLE], 1, 2, 5, 3);

    renderer.shaders[GUI] = shader_create("src/shaders/gui_vertex.sl", "src/shaders/gui_fragment.sl");
    renderer.usage[GUI] = GL_STATIC_DRAW;
    renderer.vaos[GUI] = vao_create();
    vao_attr(&renderer.vaos[GUI], 0, 2, 5, 0);
    vao_attr(&renderer.vaos[GUI], 1, 3, 5, 2);

    renderer.spritesheet = texture_create("assets/spritesheet.png");
    glUniform1i(renderer_uniform_location("tex", DRAWABLE), renderer.spritesheet.ID);
    texture_bind(renderer.spritesheet);
    renderer_settings();
}

void renderer_malloc(buffertype type, u32 length)
{
    vao_malloc(&renderer.vaos[type], length, renderer.usage[type]);
}

void renderer_update(buffertype type, u32 length, f32* buffer)
{
    vao_update(&renderer.vaos[type], length, buffer);
}

void renderer_render(void)
{
    glClearColor(0.6f, 0.7f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader_use(renderer.shaders[DRAWABLE]);
    glEnable(GL_DEPTH_TEST);
    vao_draw(renderer.vaos[DRAWABLE]);
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUI]);
    vao_draw(renderer.vaos[GUI]);
    shader_use(renderer.shaders[DRAWABLE]);
}

void renderer_destroy(void)
{
    vao_destroy(renderer.vaos[DRAWABLE]);
    vao_destroy(renderer.vaos[GUI]);
    shader_destroy(renderer.shaders[DRAWABLE]);
    shader_destroy(renderer.shaders[GUI]);
}

u32 renderer_uniform_location(char* identifier, buffertype type) {
    shader_use(renderer.shaders[DRAWABLE]);
    return glGetUniformLocation(renderer.shaders[type].ID, identifier); 
}