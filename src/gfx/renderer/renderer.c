#include "renderer.h"

Renderer renderer;

void renderer_init(void) 
{
    u32 test[2] = {3, 3};
    renderer.shader = shader_create("src/shaders/vert.sl", "src/shaders/frag.sl");
    renderer.vao = vao_create(2, 6, test);
    shader_use(renderer.shader);
    //vao_update(renderer.vao, GL_ARRAY_BUFFER, sizeof(vertices), vertices);
}

void renderer_update(size_t data_size, void* data)
{
    vao_update(&renderer.vao, GL_ARRAY_BUFFER, data_size, data);
}

void renderer_render(void)
{
    glClearColor(0.6f, 0.7f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vao_draw(renderer.vao);
}

void renderer_destroy(void)
{
    vao_destroy(renderer.vao);
}

/* abstractions */
u32 renderer_uniform_location(char* identifier) { return glGetUniformLocation(renderer.shader.ID, identifier); }