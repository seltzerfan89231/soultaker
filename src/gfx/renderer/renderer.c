#include "renderer.h"

#define INDEX_COUNT 2
#define FIELD_COUNT 6

Renderer renderer;

void renderer_init(void) 
{
    u32 fields[] = {3, 3};
    renderer.shader = shader_create("src/shaders/vert.sl", "src/shaders/frag.sl");
    renderer.vao = vao_create(INDEX_COUNT, FIELD_COUNT, fields);
    shader_use(renderer.shader);
}

void renderer_update(u32 offset, size_t buffer_size, f32* buffer)
{
    vao_update(&renderer.vao, offset, buffer_size, buffer);
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
    shader_destroy(renderer.shader);
}

/* abstractions */
u32 renderer_uniform_location(char* identifier) { return glGetUniformLocation(renderer.shader.ID, identifier); }