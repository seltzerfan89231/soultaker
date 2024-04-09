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
    renderer.shaders[TILE] = shader_create("src/renderer/shaders/tile.vert", "src/renderer/shaders/tile.frag");
    renderer.usage[TILE] = GL_DYNAMIC_DRAW;
    renderer.vaos[TILE] = vao_create();
    renderer.vaos[TILE].length = TILE_VERTEX_LENGTH;
    vao_attr(&renderer.vaos[TILE], 0, 3, TILE_VERTEX_LENGTH, 0);
    vao_attr(&renderer.vaos[TILE], 1, 2, TILE_VERTEX_LENGTH, 3);

    renderer.shaders[GUI] = shader_create("src/renderer/shaders/gui.vert", "src/renderer/shaders/gui.frag");
    renderer.usage[GUI] = GL_STATIC_DRAW;
    renderer.vaos[GUI] = vao_create();
    renderer.vaos[GUI].length = GUI_VERTEX_LENGTH;
    vao_attr(&renderer.vaos[GUI], 0, 2, GUI_VERTEX_LENGTH, 0);
    vao_attr(&renderer.vaos[GUI], 1, 3, GUI_VERTEX_LENGTH, 2);

    renderer.spritesheet = texture_create("assets/spritesheet.png");
    glUniform1i(renderer_uniform_location(TILE, "tex"), renderer.spritesheet.id);
    texture_bind(renderer.spritesheet);
    renderer_settings();
}

void renderer_malloc(buffertype type, u32 length)
{
    vao_malloc(&renderer.vaos[type], length, renderer.usage[type]);
}

void renderer_update(buffertype type, u32 offset, u32 length, f32* buffer)
{
    vao_update(&renderer.vaos[type], offset, length, buffer);
}

void renderer_render(void)
{
    glClearColor(0.6f, 0.7f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader_use(renderer.shaders[TILE]);
    glEnable(GL_DEPTH_TEST);
    vao_draw(renderer.vaos[TILE]);
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUI]);
    vao_draw(renderer.vaos[GUI]);
    shader_use(renderer.shaders[TILE]);
}

void renderer_destroy(void)
{
    vao_destroy(renderer.vaos[TILE]);
    vao_destroy(renderer.vaos[GUI]);
    shader_destroy(renderer.shaders[TILE]);
    shader_destroy(renderer.shaders[GUI]);
}

u32 renderer_uniform_location(buffertype type, char* identifier) {
    shader_use(renderer.shaders[TILE]);
    return glGetUniformLocation(renderer.shaders[type].id, identifier); 
}