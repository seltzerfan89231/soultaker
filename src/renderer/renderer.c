#include "renderer.h"
#include <math.h>

Renderer renderer;

static void renderer_settings(void)
{
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  
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
    renderer.ubos = malloc(NUM_UBO_TYPES * sizeof(UBO));

    u32 i;
    renderer.ubos[MATRICES] = ubo_create(32 * sizeof(f32));
    renderer.ubos[ZOOM] = ubo_create(sizeof(f32));
    renderer.ubos[ASPECT_RATIO] = ubo_create(sizeof(f32));
    renderer.ubos[ROTATION] = ubo_create(sizeof(f32));
    renderer.ubos[TILT] = ubo_create(sizeof(f32));
    renderer.ubos[CONSTANTS] = ubo_create(2 * sizeof(f32));

    renderer.shaders[TILE] = shader_create("src/renderer/shaders/tile/tile.vert", "src/renderer/shaders/tile/tile.frag", "src/renderer/shaders/tile/tile.geom");
    renderer.vaos[TILE] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[TILE].length = 3;
    vao_attr(&renderer.vaos[TILE], 0, 3, 3, 0);

    i = glGetUniformBlockIndex(renderer.shaders[TILE].id, "Matrices");
    glUniformBlockBinding(renderer.shaders[TILE].id, i, MATRICES);
    glBindBufferRange(GL_UNIFORM_BUFFER, MATRICES, renderer.ubos[MATRICES].id, 0, 32 * sizeof(f32));

    renderer.shaders[ENTITY] = shader_create("src/renderer/shaders/entity/entity.vert", "src/renderer/shaders/entity/entity.frag", "src/renderer/shaders/entity/entity.geom");
    renderer.vaos[ENTITY] = vao_create(GL_DYNAMIC_DRAW);
    renderer.vaos[ENTITY].length = 3;
    vao_attr(&renderer.vaos[ENTITY], 0, 3, 3, 0);

    i = glGetUniformBlockIndex(renderer.shaders[ENTITY].id, "Matrices");
    glUniformBlockBinding(renderer.shaders[ENTITY].id, i, MATRICES);
    glBindBufferRange(GL_UNIFORM_BUFFER, MATRICES, renderer.ubos[MATRICES].id, 0, 32 * sizeof(f32));

    i = glGetUniformBlockIndex(renderer.shaders[ENTITY].id, "Zoom");
    glUniformBlockBinding(renderer.shaders[ENTITY].id, i, ZOOM);
    glBindBufferRange(GL_UNIFORM_BUFFER, ZOOM, renderer.ubos[ZOOM].id, 0, sizeof(f32));

    i = glGetUniformBlockIndex(renderer.shaders[ENTITY].id, "AspectRatio");
    glUniformBlockBinding(renderer.shaders[ENTITY].id, i, ASPECT_RATIO);
    glBindBufferRange(GL_UNIFORM_BUFFER, ASPECT_RATIO, renderer.ubos[ASPECT_RATIO].id, 0, sizeof(f32));

    renderer.shaders[PROJECTILE] = shader_create("src/renderer/shaders/projectile/projectile.vert", "src/renderer/shaders/projectile/projectile.frag", "src/renderer/shaders/projectile/projectile.geom");
    renderer.vaos[PROJECTILE] = vao_create(GL_DYNAMIC_DRAW);
    renderer.vaos[PROJECTILE].length = 4;
    vao_attr(&renderer.vaos[PROJECTILE], 0, 3, 4, 0);
    vao_attr(&renderer.vaos[PROJECTILE], 1, 1, 4, 3);

    i = glGetUniformBlockIndex(renderer.shaders[PROJECTILE].id, "Matrices");
    glUniformBlockBinding(renderer.shaders[PROJECTILE].id, i, MATRICES);
    glBindBufferRange(GL_UNIFORM_BUFFER, MATRICES, renderer.ubos[MATRICES].id, 0, 32 * sizeof(f32));

    i = glGetUniformBlockIndex(renderer.shaders[PROJECTILE].id, "Zoom");
    glUniformBlockBinding(renderer.shaders[PROJECTILE].id, i, ZOOM);
    glBindBufferRange(GL_UNIFORM_BUFFER, ZOOM, renderer.ubos[ZOOM].id, 0, sizeof(f32));

    i = glGetUniformBlockIndex(renderer.shaders[PROJECTILE].id, "AspectRatio");
    glUniformBlockBinding(renderer.shaders[PROJECTILE].id, i, ASPECT_RATIO);
    glBindBufferRange(GL_UNIFORM_BUFFER, ASPECT_RATIO, renderer.ubos[ASPECT_RATIO].id, 0, sizeof(f32));

    i = glGetUniformBlockIndex(renderer.shaders[PROJECTILE].id, "Rotation");
    glUniformBlockBinding(renderer.shaders[PROJECTILE].id, i, ROTATION);
    glBindBufferRange(GL_UNIFORM_BUFFER, ROTATION, renderer.ubos[ROTATION].id, 0, sizeof(f32));

    i = glGetUniformBlockIndex(renderer.shaders[PROJECTILE].id, "Tilt");
    glUniformBlockBinding(renderer.shaders[PROJECTILE].id, i, TILT);
    glBindBufferRange(GL_UNIFORM_BUFFER, TILT, renderer.ubos[TILT].id, 0, sizeof(f32));

    i = glGetUniformBlockIndex(renderer.shaders[PROJECTILE].id, "Constants");
    glUniformBlockBinding(renderer.shaders[PROJECTILE].id, i, CONSTANTS);
    glBindBufferRange(GL_UNIFORM_BUFFER, CONSTANTS, renderer.ubos[CONSTANTS].id, 0, sizeof(f32));

    renderer.shaders[GUIB] = shader_create("src/renderer/shaders/gui/gui.vert", "src/renderer/shaders/gui/gui.frag", NULL);
    renderer.vaos[GUIB] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[GUIB].length = 5;
    vao_attr(&renderer.vaos[GUIB], 0, 2, 5, 0);
    vao_attr(&renderer.vaos[GUIB], 1, 3, 5, 2);

    renderer.shaders[4] = shader_create("src/renderer/shaders/entity/entity_outline.vert", "src/renderer/shaders/entity/entity_outline.frag", "src/renderer/shaders/entity/entity_outline.geom");

    renderer.atlas = texture_create("assets/atlas.png");
    renderer_uniform_update_texture(ENTITY, "tex", renderer.atlas);
    texture_bind(renderer.atlas);
    renderer_settings();

    f32 pi, sqrt2;
    pi = 3.1415926535;
    sqrt2 = sqrt(2);
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubos[CONSTANTS].id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0 * sizeof(f32), sizeof(f32), &pi);
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(f32), sizeof(f32), &sqrt2);
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
    glStencilMask(0x00);
    shader_use(renderer.shaders[TILE]);
    vao_draw(renderer.vaos[TILE], GL_POINTS);
    glDepthFunc(GL_ALWAYS);

    glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should pass the stencil test
    glStencilMask(0xFF); // enable writing to the stencil buffer
    shader_use(renderer.shaders[ENTITY]);
    vao_draw(renderer.vaos[ENTITY], GL_POINTS);

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00); // disable writing to the stencil buffer
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[4]); 
    vao_draw(renderer.vaos[ENTITY], GL_POINTS);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);   
    glEnable(GL_DEPTH_TEST); 

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
    free(renderer.ubos);
}

void renderer_uniform_update_texture(buffertype type, char* identifier, Texture texture) {
    shader_use(renderer.shaders[type]);
    glUniform1i(glGetUniformLocation(renderer.shaders[type].id, identifier), texture.id);
}

void renderer_uniform_update_view(f32 *mat) {
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubos[MATRICES].id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 16 * sizeof(f32), mat);
}

void renderer_uniform_update_proj(f32 *mat) {
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubos[MATRICES].id);
    glBufferSubData(GL_UNIFORM_BUFFER, 16 * sizeof(f32), 16 * sizeof(f32), mat);
}

void renderer_uniform_update_zoom(f32 zoom) {
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubos[ZOOM].id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(f32), &zoom);
}

void renderer_uniform_update_rotation(f32 rotation) {
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubos[ROTATION].id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(f32), &rotation);
}

void renderer_uniform_update_tilt(f32 tilt) {
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubos[TILT].id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(f32), &tilt);
}

void renderer_uniform_update_aspect_ratio(f32 ar) {
    glBindBuffer(GL_UNIFORM_BUFFER, renderer.ubos[ASPECT_RATIO].id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(f32), &ar);
}