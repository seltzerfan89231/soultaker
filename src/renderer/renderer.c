#include "renderer.h"
#include <math.h>

Renderer renderer;

static void renderer_settings(void)
{
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
    glEnable(GL_CULL_FACE); 
    glEnable(GL_MULTISAMPLE);
    glCullFace(GL_FRONT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwWindowHint(GLFW_SAMPLES, NUM_SAMPLES);
}

static void link_shader_ubo(u32 shader_index, u32 ubo_index, char *identifier)
{
    shader_bind_block(renderer.shaders[shader_index], ubo_index, identifier);
    ubo_bind_buffer_base(renderer.ubos[ubo_index], ubo_index);
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
    renderer.vaos[TILE].length = 2;
    vao_attr(&renderer.vaos[TILE], 0, 2, 2, 0);
    link_shader_ubo(TILE, MATRICES, "Matrices");

    renderer.shaders[WALL] = shader_create("src/renderer/shaders/wall/wall.vert", "src/renderer/shaders/wall/wall.frag", "src/renderer/shaders/wall/wall.geom");
    renderer.vaos[WALL] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[WALL].length = 4;
    vao_attr(&renderer.vaos[WALL], 0, 3, 4, 0);
    vao_attr(&renderer.vaos[WALL], 1, 1, 4, 3);
    link_shader_ubo(WALL, MATRICES, "Matrices");

    renderer.shaders[ENTITY] = shader_create("src/renderer/shaders/entity/entity.vert", "src/renderer/shaders/entity/entity.frag", "src/renderer/shaders/entity/entity.geom");
    renderer.vaos[ENTITY] = vao_create(GL_DYNAMIC_DRAW);
    renderer.vaos[ENTITY].length = 3;
    vao_attr(&renderer.vaos[ENTITY], 0, 3, 3, 0);
    link_shader_ubo(ENTITY, MATRICES, "Matrices");
    link_shader_ubo(ENTITY, ZOOM, "Zoom");
    link_shader_ubo(ENTITY, ASPECT_RATIO, "AspectRatio");

    renderer.shaders[PROJECTILE] = shader_create("src/renderer/shaders/projectile/projectile.vert", "src/renderer/shaders/projectile/projectile.frag", "src/renderer/shaders/projectile/projectile.geom");
    renderer.vaos[PROJECTILE] = vao_create(GL_DYNAMIC_DRAW);
    renderer.vaos[PROJECTILE].length = 4;
    vao_attr(&renderer.vaos[PROJECTILE], 0, 3, 4, 0);
    vao_attr(&renderer.vaos[PROJECTILE], 1, 1, 4, 3);
    link_shader_ubo(PROJECTILE, MATRICES, "Matrices");
    link_shader_ubo(PROJECTILE, ZOOM, "Zoom");
    link_shader_ubo(PROJECTILE, ASPECT_RATIO, "AspectRatio");
    link_shader_ubo(PROJECTILE, ROTATION, "Rotation");
    link_shader_ubo(PROJECTILE, TILT, "Tilt");
    link_shader_ubo(PROJECTILE, CONSTANTS, "Constants");

    renderer.shaders[GUIB] = shader_create("src/renderer/shaders/gui/gui.vert", "src/renderer/shaders/gui/gui.frag", NULL);
    renderer.vaos[GUIB] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[GUIB].length = 5;
    vao_attr(&renderer.vaos[GUIB], 0, 2, 5, 0);
    vao_attr(&renderer.vaos[GUIB], 1, 3, 5, 2);

    renderer.atlas = texture_create("assets/atlas.png");
    renderer_uniform_update_texture(WALL, "tex", renderer.atlas, 1);
    texture_bind(renderer.atlas, 1);
    renderer.entity = texture_create("assets/test.png");
    renderer_uniform_update_texture(ENTITY, "entity", renderer.entity, 2);
    texture_bind(renderer.entity, 2);

    f32 pi, sqrt2;
    pi = 3.1415926535;
    sqrt2 = sqrt(2);
    ubo_update(renderer.ubos[CONSTANTS], 0, sizeof(f32), &pi);
    ubo_update(renderer.ubos[CONSTANTS], sizeof(f32), sizeof(f32), &sqrt2);

    renderer_settings();
}

void renderer_malloc(buffertype type, u32 length)
{
    length *= renderer.vaos[type].length;
    vao_malloc(&renderer.vaos[type], length);
}

void renderer_update(buffertype type, u32 offset, u32 length, f32* buffer)
{
    length *= renderer.vaos[type].length;
    vao_update(&renderer.vaos[type], offset, length, buffer);
}

void renderer_render(void)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_REPLACE, GL_REPLACE);
    //glStencilOpSeparate(GL_BACK, GL_KEEP, GL_REPLACE, GL_REPLACE);  

    // glStencilMask(0x00);
    texture_bind(renderer.atlas, 1);
    
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[TILE]);
    vao_draw(renderer.vaos[TILE], GL_POINTS);
    glEnable(GL_DEPTH_TEST);    

    shader_use(renderer.shaders[WALL]);
    vao_draw(renderer.vaos[WALL], GL_POINTS);

    texture_bind(renderer.entity, 2);
    shader_use(renderer.shaders[ENTITY]);
    vao_draw(renderer.vaos[ENTITY], GL_POINTS);

    texture_bind(renderer.atlas, 1);
    shader_use(renderer.shaders[PROJECTILE]);
    vao_draw(renderer.vaos[PROJECTILE], GL_POINTS);

    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUIB]);
    vao_draw(renderer.vaos[GUIB], GL_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
}

void renderer_destroy(void)
{
    for (i32 i = 0; i < NUM_BUFFER_TYPES; i++) {
        vao_destroy(renderer.vaos[i]);
        shader_destroy(renderer.shaders[i]);
    }
    texture_destroy(renderer.atlas);
    free(renderer.shaders);
    free(renderer.vaos);
    free(renderer.ubos);
}

void renderer_uniform_update_texture(buffertype type, char* identifier, Texture texture, u32 binding) {
    shader_use(renderer.shaders[type]);
    glUniform1i(glGetUniformLocation(renderer.shaders[type].id, identifier), binding);
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