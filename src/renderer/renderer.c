#include "renderer.h"
#include <math.h>

Renderer renderer;

static void renderer_settings(void)
{
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_STENCIL_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

static void link_shader_ubo(u32 shader_index, u32 ubo_index, char *identifier)
{
    shader_bind_block(renderer.shaders[shader_index], ubo_index, identifier);
    ubo_bind_buffer_base(renderer.ubos[ubo_index], ubo_index);
}

void renderer_init(void) 
{
    renderer.shaders = malloc(NUM_SHADERS * sizeof(Shader));
    renderer.vaos = malloc(NUM_VAOS * sizeof(VAO));
    renderer.ubos = malloc(NUM_UBOS * sizeof(UBO));

    u32 i;
    renderer.ubos[MATRICES_UBO_INDEX] = ubo_create(32 * sizeof(f32));
    renderer.ubos[ZOOM_UBO_INDEX] = ubo_create(sizeof(f32));
    renderer.ubos[ASPECT_RATIO_UBO_INDEX] = ubo_create(sizeof(f32));
    renderer.ubos[ROTATION_UBO_INDEX] = ubo_create(sizeof(f32));
    renderer.ubos[TILT_UBO_INDEX] = ubo_create(sizeof(f32));
    renderer.ubos[CONSTANTS_UBO_INDEX] = ubo_create(2 * sizeof(f32));

    renderer.shaders[TILE_SHADER_INDEX] = shader_create("src/renderer/shaders/tile/tile.vert", "src/renderer/shaders/tile/tile.frag", "src/renderer/shaders/tile/tile.geom");
    renderer.vaos[TILE_VAO_INDEX] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[TILE_VAO_INDEX].length = 2;
    vao_attr(&renderer.vaos[TILE_VAO_INDEX], 0, 2, 2, 0);
    link_shader_ubo(TILE_SHADER_INDEX, MATRICES_UBO_INDEX, "Matrices");

    renderer.shaders[WALL_SHADER_INDEX] = shader_create("src/renderer/shaders/wall/wall.vert", "src/renderer/shaders/wall/wall.frag", "src/renderer/shaders/wall/wall.geom");
    renderer.vaos[WALL_VAO_INDEX] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[WALL_VAO_INDEX].length = 4;
    vao_attr(&renderer.vaos[WALL_VAO_INDEX], 0, 3, 4, 0);
    vao_attr(&renderer.vaos[WALL_VAO_INDEX], 1, 1, 4, 3);
    link_shader_ubo(WALL_SHADER_INDEX, MATRICES_UBO_INDEX, "Matrices");

    //renderer.shaders[WALL_BACK_SHADER_INDEX] = shader_create("src/renderer/shaders/wall/wall.vert", "src/renderer/shaders/wall/wall_back.frag", "src/renderer/shaders/wall/wall_back.geom");
    //link_shader_ubo(WALL_BACK_SHADER_INDEX, MATRICES_UBO_INDEX, "Matrices");

    renderer.shaders[ENTITY_SHADER_INDEX] = shader_create("src/renderer/shaders/entity/entity.vert", "src/renderer/shaders/entity/entity.frag", "src/renderer/shaders/entity/entity.geom");
    renderer.vaos[ENTITY_VAO_INDEX] = vao_create(GL_DYNAMIC_DRAW);
    renderer.vaos[ENTITY_VAO_INDEX].length = 3;
    vao_attr(&renderer.vaos[ENTITY_VAO_INDEX], 0, 3, 3, 0);
    link_shader_ubo(ENTITY_SHADER_INDEX, MATRICES_UBO_INDEX, "Matrices");
    link_shader_ubo(ENTITY_SHADER_INDEX, ZOOM_UBO_INDEX, "Zoom");
    link_shader_ubo(ENTITY_SHADER_INDEX, ASPECT_RATIO_UBO_INDEX, "AspectRatio");

    renderer.shaders[PROJECTILE_SHADER_INDEX] = shader_create("src/renderer/shaders/projectile/projectile.vert", "src/renderer/shaders/projectile/projectile.frag", "src/renderer/shaders/projectile/projectile.geom");
    renderer.vaos[PROJECTILE_VAO_INDEX] = vao_create(GL_DYNAMIC_DRAW);
    renderer.vaos[PROJECTILE_VAO_INDEX].length = 4;
    vao_attr(&renderer.vaos[PROJECTILE_VAO_INDEX], 0, 3, 4, 0);
    vao_attr(&renderer.vaos[PROJECTILE_VAO_INDEX], 1, 1, 4, 3);
    link_shader_ubo(PROJECTILE_SHADER_INDEX, MATRICES_UBO_INDEX, "Matrices");
    link_shader_ubo(PROJECTILE_SHADER_INDEX, ZOOM_UBO_INDEX, "Zoom");
    link_shader_ubo(PROJECTILE_SHADER_INDEX, ASPECT_RATIO_UBO_INDEX, "AspectRatio");
    link_shader_ubo(PROJECTILE_SHADER_INDEX, ROTATION_UBO_INDEX, "Rotation");
    link_shader_ubo(PROJECTILE_SHADER_INDEX, TILT_UBO_INDEX, "Tilt");
    link_shader_ubo(PROJECTILE_SHADER_INDEX, CONSTANTS_UBO_INDEX, "Constants");

    renderer.shaders[GUI_SHADER_INDEX] = shader_create("src/renderer/shaders/gui/gui.vert", "src/renderer/shaders/gui/gui.frag", NULL);
    renderer.vaos[GUI_VAO_INDEX] = vao_create(GL_STATIC_DRAW);
    renderer.vaos[GUI_VAO_INDEX].length = 5;
    vao_attr(&renderer.vaos[GUI_VAO_INDEX], 0, 2, 5, 0);
    vao_attr(&renderer.vaos[GUI_VAO_INDEX], 1, 3, 5, 2);

    renderer.atlas = texture_create("assets/atlas.png");
    renderer_uniform_update_texture(WALL_SHADER_INDEX, "tex", renderer.atlas, 1);
    texture_bind(renderer.atlas, 1);
    renderer.entity = texture_create("assets/test.png");
    renderer_uniform_update_texture(ENTITY_SHADER_INDEX, "entity", renderer.entity, 2);
    texture_bind(renderer.entity, 2);

    f32 pi, sqrt2;
    pi = 3.1415926535;
    sqrt2 = sqrt(2);
    ubo_update(renderer.ubos[CONSTANTS_UBO_INDEX], 0, sizeof(f32), &pi);
    ubo_update(renderer.ubos[CONSTANTS_UBO_INDEX], sizeof(f32), sizeof(f32), &sqrt2);

    renderer_settings();
}

void renderer_malloc(u32 vao_index, u32 length)
{
    length *= renderer.vaos[vao_index].length;
    vao_malloc(&renderer.vaos[vao_index], length);
}

void renderer_update(u32 vao_index, u32 offset, u32 length, f32* buffer)
{
    length *= renderer.vaos[vao_index].length;
    vao_update(&renderer.vaos[vao_index], offset, length, buffer);
}

void renderer_render(void)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);  

    /* glStencilOpSeparate(GL_FRONT, GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilOpSeparate(GL_BACK, GL_KEEP, GL_REPLACE, GL_REPLACE);
    glStencilFuncSeparate(GL_FRONT, GL_NEVER, 1, 0xFF);
    glStencilFuncSeparate(GL_BACK, GL_ALWAYS, 1, 0xFF);
    glStencilMaskSeparate(GL_FRONT, 0xFF);
    glStencilMaskSeparate(GL_BACK, 0xFF); */

    //glStencilFunc(GL_NEVER, 1, 0xFF);
    //shader_use(renderer.shaders[WALL_BACK_SHADER_INDEX]);
    //vao_draw(renderer.vaos[WALL_VAO_INDEX], GL_POINTS);

    /* glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glStencilMask(0x00);  */

    texture_bind(renderer.atlas, 1);
    shader_use(renderer.shaders[TILE_SHADER_INDEX]);
    vao_draw(renderer.vaos[TILE_VAO_INDEX], GL_POINTS);
    shader_use(renderer.shaders[WALL_SHADER_INDEX]);
    vao_draw(renderer.vaos[WALL_VAO_INDEX], GL_POINTS);
    glClear(GL_DEPTH_BUFFER_BIT);

    texture_bind(renderer.entity, 2);
    shader_use(renderer.shaders[ENTITY_SHADER_INDEX]);
    vao_draw(renderer.vaos[ENTITY_VAO_INDEX], GL_POINTS);

    texture_bind(renderer.atlas, 1);
    shader_use(renderer.shaders[PROJECTILE_SHADER_INDEX]);
    vao_draw(renderer.vaos[PROJECTILE_VAO_INDEX], GL_POINTS);

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);  
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUI_SHADER_INDEX]);
    vao_draw(renderer.vaos[GUI_VAO_INDEX], GL_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
}

void renderer_destroy(void)
{
    for (i32 i = 0; i < NUM_VAOS; i++)
        vao_destroy(renderer.vaos[i]);
    for (i32 i = 0; i < NUM_SHADERS; i++)
        shader_destroy(renderer.shaders[i]);
    for (i32 i = 0; i < NUM_UBOS; i++)
        ubo_destroy(renderer.ubos[i]);
    texture_destroy(renderer.atlas);
    free(renderer.shaders);
    free(renderer.vaos);
    free(renderer.ubos);
}

void renderer_uniform_update_texture(u32 shader_index, char* identifier, Texture texture, u32 binding) {
    shader_use(renderer.shaders[shader_index]);
    glUniform1i(glGetUniformLocation(renderer.shaders[shader_index].id, identifier), binding);
}

void renderer_uniform_update_view(f32 *mat) {
    ubo_update(renderer.ubos[MATRICES_UBO_INDEX], 0, 16 * sizeof(f32), mat);
}

void renderer_uniform_update_proj(f32 *mat) {
    ubo_update(renderer.ubos[MATRICES_UBO_INDEX], 16 * sizeof(f32), 16 * sizeof(f32), mat);
}

void renderer_uniform_update_zoom(f32 zoom) {
    ubo_update(renderer.ubos[ZOOM_UBO_INDEX], 0, sizeof(f32), &zoom);
}

void renderer_uniform_update_rotation(f32 rotation) {
    ubo_update(renderer.ubos[ROTATION_UBO_INDEX], 0, sizeof(f32), &rotation);
}

void renderer_uniform_update_tilt(f32 tilt) {
    ubo_update(renderer.ubos[TILT_UBO_INDEX], 0, sizeof(f32), &tilt);
}

void renderer_uniform_update_aspect_ratio(f32 ar) {
    ubo_update(renderer.ubos[ASPECT_RATIO_UBO_INDEX], 0, sizeof(f32), &ar);
}