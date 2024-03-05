#include "renderer.h"

Renderer renderer;

void renderer_init(u32 vao_index_count, u32 vao_field_count, u32* vao_fields) 
{
    renderer.shader = shader_create("src/shaders/vert.sl", "src/shaders/frag.sl");
    renderer.vao = vao_create(vao_index_count, vao_field_count, vao_fields);
    shader_use(renderer.shader);
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