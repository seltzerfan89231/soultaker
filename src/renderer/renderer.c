#include "renderer.h"
#include <math.h>

Renderer renderer;

static void renderer_settings(void)
{
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_STENCIL_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

static void link_shader_ubo(u32 shader, u32 ubo, char *identifier)
{
    shader_bind_uniform_block(renderer.shaders[shader], ubo, identifier);
    ubo_bind_buffer_base(renderer.ubos[ubo], ubo);
}

static void link_shader_ssbo(u32 shader_index, u32 ssbo_index)
{
    shader_use(renderer.shaders[shader_index]);
    ssbo_bind_buffer_base(renderer.ssbo, 1);
}

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  printf( "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void renderer_init(void) 
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback( MessageCallback, 0 );
    
    renderer.shaders = malloc(NUM_SHADERS * sizeof(Shader));
    renderer.vaos = malloc(NUM_VAOS * sizeof(VAO));
    renderer.ubos = malloc(NUM_UBOS * sizeof(UBO));

    renderer.ubos[MATRICES_UBO] = ubo_create(32 * sizeof(f32));
    renderer.ubos[ZOOM_UBO] = ubo_create(sizeof(f32));
    renderer.ubos[ASPECT_RATIO_UBO] = ubo_create(sizeof(f32));
    renderer.ubos[ROTATION_UBO] = ubo_create(sizeof(f32));
    renderer.ubos[TILT_UBO] = ubo_create(sizeof(f32));
    renderer.ubos[CONSTANTS_UBO] = ubo_create(2 * sizeof(f32));

    renderer.ssbo = ssbo_create(5 * sizeof(u64));
    renderer.handles = malloc(5 * sizeof(u64));

    renderer.shaders[TILE_SHADER] = shader_create("src/renderer/shaders/tile/tile.vert", "src/renderer/shaders/tile/tile.frag", "src/renderer/shaders/tile/tile.geom");
    renderer.vaos[TILE_VAO] = vao_create(GL_STATIC_DRAW, GL_POINTS);
    renderer.vaos[TILE_VAO].length = 2;
    vao_attr(&renderer.vaos[TILE_VAO], 0, 2, 2, 0);
    link_shader_ubo(TILE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ssbo(TILE_SHADER, 0);

    renderer.shaders[WALL_SHADER] = shader_create("src/renderer/shaders/wall/wall.vert", "src/renderer/shaders/wall/wall.frag", "src/renderer/shaders/wall/wall.geom");
    renderer.vaos[WALL_VAO] = vao_create(GL_STATIC_DRAW, GL_POINTS);
    renderer.vaos[WALL_VAO].length = 4;
    vao_attr(&renderer.vaos[WALL_VAO], 0, 3, 4, 0);
    vao_attr(&renderer.vaos[WALL_VAO], 1, 1, 4, 3);
    link_shader_ubo(WALL_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ssbo(WALL_SHADER, 0);

    //renderer.shaders[WALL_BACK_SHADER] = shader_create("src/renderer/shaders/wall/wall.vert", "src/renderer/shaders/wall/wall_back.frag", "src/renderer/shaders/wall/wall_back.geom");
    //link_shader_ubo(WALL_BACK_SHADER, MATRICES_UBO, "Matrices");

    renderer.shaders[ENTITY_SHADER] = shader_create("src/renderer/shaders/entity/entity.vert", "src/renderer/shaders/entity/entity.frag", "src/renderer/shaders/entity/entity.geom");
    renderer.vaos[ENTITY_VAO] = vao_create(GL_DYNAMIC_DRAW, GL_POINTS);
    renderer.vaos[ENTITY_VAO].length = 3;
    vao_attr(&renderer.vaos[ENTITY_VAO], 0, 3, 3, 0);
    link_shader_ubo(ENTITY_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(ENTITY_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(ENTITY_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ssbo(ENTITY_SHADER, 0);

    renderer.shaders[SHADOW_SHADER] = shader_create("src/renderer/shaders/shadow/shadow.vert", "src/renderer/shaders/shadow/shadow.frag", "src/renderer/shaders/shadow/shadow.geom");
    link_shader_ubo(SHADOW_SHADER, MATRICES_UBO, "Matrices");

    renderer.shaders[HEALTHBAR_SHADER] = shader_create("src/renderer/shaders/healthbar/healthbar.vert", "src/renderer/shaders/healthbar/healthbar.frag", "src/renderer/shaders/healthbar/healthbar.geom");
    link_shader_ubo(HEALTHBAR_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(HEALTHBAR_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(HEALTHBAR_SHADER, ASPECT_RATIO_UBO, "AspectRatio");

    renderer.shaders[PROJECTILE_SHADER] = shader_create("src/renderer/shaders/projectile/projectile.vert", "src/renderer/shaders/projectile/projectile.frag", "src/renderer/shaders/projectile/projectile.geom");
    renderer.vaos[PROJECTILE_VAO] = vao_create(GL_DYNAMIC_DRAW, GL_POINTS);
    renderer.vaos[PROJECTILE_VAO].length = 4;
    vao_attr(&renderer.vaos[PROJECTILE_VAO], 0, 3, 4, 0);
    vao_attr(&renderer.vaos[PROJECTILE_VAO], 1, 1, 4, 3);
    link_shader_ubo(PROJECTILE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PROJECTILE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(PROJECTILE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PROJECTILE_SHADER, ROTATION_UBO, "Rotation");
    link_shader_ubo(PROJECTILE_SHADER, TILT_UBO, "Tilt");
    link_shader_ubo(PROJECTILE_SHADER, CONSTANTS_UBO, "Constants");
    link_shader_ssbo(PROJECTILE_SHADER, 0);

    renderer.shaders[GUI_SHADER] = shader_create("src/renderer/shaders/gui/gui.vert", "src/renderer/shaders/gui/gui.frag", NULL);
    renderer.vaos[GUI_VAO] = vao_create(GL_STATIC_DRAW, GL_TRIANGLE_STRIP);
    renderer.vaos[GUI_VAO].length = 5;
    vao_attr(&renderer.vaos[GUI_VAO], 0, 2, 5, 0);
    vao_attr(&renderer.vaos[GUI_VAO], 1, 3, 5, 2);
    
    renderer.textures = malloc(5 * sizeof(Texture));
    renderer.textures[0] = texture_create("assets/knight.png");
    renderer.textures[1] = texture_create("assets/bullet.png");
    renderer.textures[2] = texture_create("assets/tile.png");
    renderer.textures[3] = texture_create("assets/wall_top.png");
    renderer.textures[4] = texture_create("assets/wall.png");
    for (i32 i = 0; i < 5; i++) {
        renderer.handles[i] = glGetTextureHandleARB(renderer.textures[i].id);
        glMakeTextureHandleResidentARB(renderer.handles[i]);
    }
    ssbo_update(renderer.ssbo, 0, 5 * sizeof(u64), renderer.handles);

    f32 pi, sqrt2;
    pi = 3.1415926535;
    sqrt2 = sqrt(2);
    ubo_update(renderer.ubos[CONSTANTS_UBO], 0, sizeof(f32), &pi);
    ubo_update(renderer.ubos[CONSTANTS_UBO], sizeof(f32), sizeof(f32), &sqrt2);

    renderer_settings();
}

void renderer_malloc(u32 vao, u32 length)
{
    length *= renderer.vaos[vao].length;
    vao_malloc(&renderer.vaos[vao], length);
}

void renderer_update(u32 vao, u32 offset, u32 length, f32* buffer)
{
    length *= renderer.vaos[vao].length;
    vao_update(&renderer.vaos[vao], offset, length, buffer);
}

void renderer_render(void)
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);  

    /* glStencilOpSeparate(GL_FRONT, GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilOpSeparate(GL_BACK, GL_KEEP, GL_REPLACE, GL_REPLACE);
    glStencilFuncSeparate(GL_FRONT, GL_NEVER, 1, 0xFF);
    glStencilFuncSeparate(GL_BACK, GL_ALWAYS, 1, 0xFF);
    glStencilMaskSeparate(GL_FRONT, 0xFF);
    glStencilMaskSeparate(GL_BACK, 0xFF); */

    //glStencilFunc(GL_NEVER, 1, 0xFF);
    //shader_use(renderer.shaders[WALL_BACK_SHADER]);
    //vao_draw(renderer.vaos[WALL_VAO], GL_POINTS);

    /* glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glStencilMask(0x00);  */

    shader_use(renderer.shaders[TILE_SHADER]);
    vao_draw(renderer.vaos[TILE_VAO]);
    shader_use(renderer.shaders[WALL_SHADER]);
    vao_draw(renderer.vaos[WALL_VAO]);
    glClear(GL_DEPTH_BUFFER_BIT);

    shader_use(renderer.shaders[ENTITY_SHADER]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    shader_use(renderer.shaders[SHADOW_SHADER]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    glDepthFunc(GL_ALWAYS);
    shader_use(renderer.shaders[HEALTHBAR_SHADER]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    glDepthFunc(GL_LESS);

    shader_use(renderer.shaders[PROJECTILE_SHADER]);
    vao_draw(renderer.vaos[PROJECTILE_VAO]);
    shader_use(renderer.shaders[SHADOW_SHADER]);
    vao_draw(renderer.vaos[PROJECTILE_VAO]);

    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUI_SHADER]);
    vao_draw(renderer.vaos[GUI_VAO]);
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
    for (i32 i = 0; i < 5; i++) {
        glMakeTextureHandleNonResidentARB(renderer.handles[i]);
        texture_destroy(renderer.textures[i]);
    }
    ssbo_destroy(renderer.ssbo);
    free(renderer.handles);
    free(renderer.textures);
    free(renderer.shaders);
    free(renderer.vaos);
    free(renderer.ubos);
}

void renderer_uniform_update_texture(u32 shader, char* identifier, Texture texture, u32 binding) {
    shader_use(renderer.shaders[shader]);
    glUniform1i(glGetUniformLocation(renderer.shaders[shader].id, identifier), binding);
}

void renderer_uniform_update_view(f32 *mat) {
    ubo_update(renderer.ubos[MATRICES_UBO], 0, 16 * sizeof(f32), mat);
}

void renderer_uniform_update_proj(f32 *mat) {
    ubo_update(renderer.ubos[MATRICES_UBO], 16 * sizeof(f32), 16 * sizeof(f32), mat);
}

void renderer_uniform_update_zoom(f32 zoom) {
    ubo_update(renderer.ubos[ZOOM_UBO], 0, sizeof(f32), &zoom);
}

void renderer_uniform_update_rotation(f32 rotation) {
    ubo_update(renderer.ubos[ROTATION_UBO], 0, sizeof(f32), &rotation);
}

void renderer_uniform_update_tilt(f32 tilt) {
    ubo_update(renderer.ubos[TILT_UBO], 0, sizeof(f32), &tilt);
}

void renderer_uniform_update_aspect_ratio(f32 ar) {
    ubo_update(renderer.ubos[ASPECT_RATIO_UBO], 0, sizeof(f32), &ar);
}