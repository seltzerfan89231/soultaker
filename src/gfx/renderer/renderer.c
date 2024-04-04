#include "renderer.h"

Renderer renderer;

void renderer_init(void) 
{
    renderer.shaders[DRAWABLE] = shader_create("src/shaders/drawable_vertex.sl", "src/shaders/drawable_fragment.sl");
    renderer.shaders[GUI] = shader_create("src/shaders/gui_vertex.sl", "src/shaders/gui_fragment.sl");
    renderer.vaos[DRAWABLE] = vao_create(DRAWABLE);
    renderer.vaos[GUI] = vao_create(GUI);
}

void renderer_update(u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length, buffertype type)
{
    vao_update(&renderer.vaos[type], offset, subdata_size, subdata, buffer_length);
}

void renderer_render(void)
{
    glClearColor(0.6f, 0.7f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader_use(renderer.shaders[DRAWABLE]);
    glEnable(GL_DEPTH_TEST);
    vao_bind(renderer.vaos[DRAWABLE]);
    vao_draw(renderer.vaos[DRAWABLE]);
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUI]);
    vao_bind(renderer.vaos[GUI]);
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