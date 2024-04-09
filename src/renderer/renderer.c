#include "renderer.h"

Renderer renderer;

static void renderer_settings(void)
{
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE); 
    glEnable(GL_MULTISAMPLE);
    glCullFace(GL_FRONT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwWindowHint(GLFW_SAMPLES, NUM_SAMPLES);
}

void renderer_init(void) 
{
    renderer.shaders[TILE] = shader_create("src/renderer/shaders/tile.vert", "src/renderer/shaders/tile.frag", NULL);
    renderer.usage[TILE] = GL_STATIC_DRAW;
    renderer.vaos[TILE] = vao_create();
    renderer.vaos[TILE].length = TILE_VERTEX_LENGTH;
    vao_attr(&renderer.vaos[TILE], 0, 3, TILE_VERTEX_LENGTH, 0);
    vao_attr(&renderer.vaos[TILE], 1, 2, TILE_VERTEX_LENGTH, 3);

    renderer.shaders[ENTITY] = shader_create("src/renderer/shaders/entity.vert", "src/renderer/shaders/entity.frag", "src/renderer/shaders/entity.geom");
    renderer.usage[ENTITY] = GL_DYNAMIC_DRAW;
    renderer.vaos[ENTITY] = vao_create();
    renderer.vaos[ENTITY].length = ENTITY_VERTEX_LENGTH;
    vao_attr(&renderer.vaos[ENTITY], 0, 2, ENTITY_VERTEX_LENGTH, 0);
    vao_attr(&renderer.vaos[ENTITY], 1, 3, ENTITY_VERTEX_LENGTH, 2);

    renderer.shaders[GUI] = shader_create("src/renderer/shaders/gui.vert", "src/renderer/shaders/gui.frag", NULL);
    renderer.usage[GUI] = GL_STATIC_DRAW;
    renderer.vaos[GUI] = vao_create();
    renderer.vaos[GUI].length = GUI_VERTEX_LENGTH;
    vao_attr(&renderer.vaos[GUI], 0, 2, GUI_VERTEX_LENGTH, 0);

    renderer.spritesheet = texture_create("assets/spritesheet.png");
    renderer_uniform_update_texture(TILE, "tex", renderer.spritesheet);
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
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[TILE]);
    vao_draw(renderer.vaos[TILE], GL_TRIANGLES);
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[ENTITY]);
    vao_draw(renderer.vaos[ENTITY], GL_POINTS);
    shader_use(renderer.shaders[GUI]);
    vao_draw(renderer.vaos[GUI], GL_TRIANGLES);
    shader_use(renderer.shaders[TILE]);
}

void renderer_destroy(void)
{
    vao_destroy(renderer.vaos[TILE]);
    vao_destroy(renderer.vaos[GUI]);
    shader_destroy(renderer.shaders[TILE]);
    shader_destroy(renderer.shaders[GUI]);
}

static u32 renderer_uniform_location(buffertype type, char* identifier) {
    return glGetUniformLocation(renderer.shaders[type].id, identifier);
}

void renderer_uniform_update_texture(buffertype type, char* identifier, Texture texture) {
    shader_use(renderer.shaders[type]);
    glUniform1i(renderer_uniform_location(type, identifier), texture.id);
}

void renderer_uniform_update_matrix(buffertype type, char* identifier, f32* mat4) {
    shader_use(renderer.shaders[type]);
    glUniformMatrix4fv(renderer_uniform_location(type, identifier), 1, GL_FALSE, mat4);
}
