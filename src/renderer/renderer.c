#include "renderer.h"

Renderer renderer;

static void renderer_settings(void)
{
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE); 
    glEnable(GL_MULTISAMPLE);
    glCullFace(GL_FRONT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwWindowHint(GLFW_SAMPLES, NUM_SAMPLES);
}

void renderer_init(void) 
{
    renderer.shaders = malloc(NUM_BUFFER_TYPES * sizeof(Shader));
    renderer.vaos = malloc(NUM_BUFFER_TYPES * sizeof(VAO));

    renderer.shaders[TILE] = shader_create("src/renderer/shaders/tile/tile.vert", "src/renderer/shaders/tile/tile.frag", "src/renderer/shaders/tile/tile.geom");
    renderer.vaos[TILE] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[TILE].length = 3;
    vao_attr(&renderer.vaos[TILE], 0, 3, 3, 0);

    renderer.shaders[ENTITY] = shader_create("src/renderer/shaders/entity/entity.vert", "src/renderer/shaders/entity/entity.frag", "src/renderer/shaders/entity/entity.geom");
    renderer.vaos[ENTITY] = vao_create(GL_DYNAMIC_DRAW);
    renderer.vaos[ENTITY].length = 3;
    vao_attr(&renderer.vaos[ENTITY], 0, 3, 3, 0);

    renderer.shaders[PROJECTILE] = shader_create("src/renderer/shaders/projectile/projectile.vert", "src/renderer/shaders/projectile/projectile.frag", "src/renderer/shaders/projectile/projectile.geom");
    renderer.vaos[PROJECTILE] = vao_create(GL_DYNAMIC_DRAW);
    renderer.vaos[PROJECTILE].length = 4;
    vao_attr(&renderer.vaos[PROJECTILE], 0, 3, 4, 0);
    vao_attr(&renderer.vaos[PROJECTILE], 1, 1, 4, 3);

    renderer.shaders[GUIB] = shader_create("src/renderer/shaders/gui/gui.vert", "src/renderer/shaders/gui/gui.frag", NULL);
    renderer.vaos[GUIB] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[GUIB].length = 5;
    vao_attr(&renderer.vaos[GUIB], 0, 2, 5, 0);
    vao_attr(&renderer.vaos[GUIB], 1, 3, 5, 2);

    renderer.atlas = texture_create("assets/atlas.png");
    renderer_uniform_update_texture(ENTITY, "tex", renderer.atlas);
    texture_bind(renderer.atlas);
    renderer_settings();
}

void renderer_malloc(buffertype type, u32 length)
{
    vao_malloc(&renderer.vaos[type], length);
}

void renderer_update(buffertype type, u32 offset, u32 length, f32* buffer)
{
    vao_update(&renderer.vaos[type], offset, length, buffer);
}

void renderer_render(void)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    shader_use(renderer.shaders[TILE]);
    vao_draw(renderer.vaos[TILE], GL_POINTS);
    glDepthFunc(GL_ALWAYS);
    shader_use(renderer.shaders[ENTITY]);
    vao_draw(renderer.vaos[ENTITY], GL_POINTS);
    shader_use(renderer.shaders[PROJECTILE]);
    vao_draw(renderer.vaos[PROJECTILE], GL_POINTS);
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUIB]);
    vao_draw(renderer.vaos[GUIB], GL_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
}

void renderer_destroy(void)
{
    vao_destroy(renderer.vaos[TILE]);
    vao_destroy(renderer.vaos[ENTITY]);
    vao_destroy(renderer.vaos[GUIB]);
    shader_destroy(renderer.shaders[TILE]);
    shader_destroy(renderer.shaders[ENTITY]);
    shader_destroy(renderer.shaders[GUIB]);
    texture_destroy(renderer.atlas);
    free(renderer.shaders);
    free(renderer.vaos);
}

static u32 renderer_uniform_location(buffertype type, char* identifier) {
    float t = glfwGetTime();
    shader_use(renderer.shaders[type]);
    printf("%.10", glfwGetTime() - t);
    return glGetUniformLocation(renderer.shaders[type].id, identifier);
}

void renderer_uniform_update_texture(buffertype type, char* identifier, Texture texture) {
    glUniform1i(renderer_uniform_location(type, identifier), texture.id);
}

void renderer_uniform_update_matrix(buffertype type, char* identifier, f32* mat4) {
    glUniformMatrix4fv(renderer_uniform_location(type, identifier), 1, GL_FALSE, mat4);
}

void renderer_uniform_update_float(buffertype type, char* identifier, f32 flt) {
    glUniform1f(renderer_uniform_location(type, identifier), flt);
}

void renderer_uniform_update_vec3(buffertype type, char* identifier, vec3f vec) {
    glUniform3f(renderer_uniform_location(type, identifier), vec.x, vec.y, vec.z);
}