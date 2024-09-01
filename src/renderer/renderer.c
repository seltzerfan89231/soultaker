#include "renderer.h"
#include <math.h>

#define OUTLINE_THICKNESS 0

Renderer renderer;

static u32 framebuffer, textureColorbuffer, rbo;

static void link_shader_ubo(u32 shader_index, u32 ubo_index, char *identifier);
static void link_shader_ssbo(u32 shader_index, u32 ssbo_index);
static void set_game_ssbo(void);
static void set_gui_ssbo(void);
static void set_constants_ubo(void);
static void set_outline_ubo(void);
static void set_quad_vao(void);
static void message_callback();
static void load_textures();

void renderer_init(void) 
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(message_callback, 0);
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_BACK);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* --------------------- */
    renderer.ubos = malloc(NUM_UBOS * sizeof(UBO));
    renderer.ubos[MATRICES_UBO]     = ubo_create(32 * sizeof(f32));
    renderer.ubos[ZOOM_UBO]         = ubo_create(sizeof(f32));
    renderer.ubos[ASPECT_RATIO_UBO] = ubo_create(sizeof(f32));
    renderer.ubos[ROTATION_UBO]     = ubo_create(sizeof(f32));
    renderer.ubos[TILT_UBO]         = ubo_create(sizeof(f32));
    renderer.ubos[CONSTANTS_UBO]    = ubo_create(2 * sizeof(f32));
    renderer.ubos[OUTLINE_UBO]      = ubo_create(sizeof(f32));
    set_constants_ubo();
    set_outline_ubo();
    /* --------------------- */
    renderer.ssbos = malloc(NUM_SSBOS * sizeof(SSBO));
    renderer.ssbos[GAME_SSBO] = ssbo_create(NUM_GAME_TEXTURES * sizeof(u64));
    renderer.ssbos[GUI_SSBO] = ssbo_create(NUM_GUI_TEXTURES * sizeof(u64));
    /* --------------------- */
    renderer.shaders = malloc(NUM_SHADERS * sizeof(Shader));
    renderer.shaders[TILE_SHADER]        = shader_create("src/renderer/shaders/tile/tile.vert", "src/renderer/shaders/tile/tile.frag", "src/renderer/shaders/tile/tile.geom");
    renderer.shaders[TILE_SHADOW_SHADER] = shader_create("src/renderer/shaders/tile/tile.vert", "src/renderer/shaders/tile/tile_shadow.frag", "src/renderer/shaders/tile/tile_shadow.geom");
    renderer.shaders[WALL_SHADER]        = shader_create("src/renderer/shaders/wall/wall.vert", "src/renderer/shaders/wall/wall.frag", "src/renderer/shaders/wall/wall.geom");
    renderer.shaders[ENTITY_SHADER]      = shader_create("src/renderer/shaders/entity/entity.vert", "src/renderer/shaders/entity/entity.frag", "src/renderer/shaders/entity/entity.geom");
    renderer.shaders[SHADOW_SHADER]      = shader_create("src/renderer/shaders/shadow/shadow.vert", "src/renderer/shaders/shadow/shadow.frag", "src/renderer/shaders/shadow/shadow.geom");
    renderer.shaders[HEALTHBAR_SHADER]   = shader_create("src/renderer/shaders/healthbar/healthbar.vert", "src/renderer/shaders/healthbar/healthbar.frag", "src/renderer/shaders/healthbar/healthbar.geom");
    renderer.shaders[PROJECTILE_SHADER]  = shader_create("src/renderer/shaders/projectile/projectile.vert", "src/renderer/shaders/projectile/projectile.frag", "src/renderer/shaders/projectile/projectile.geom");
    renderer.shaders[GUI_SHADER]         = shader_create("src/renderer/shaders/gui/gui.vert", "src/renderer/shaders/gui/gui.frag", NULL);
    renderer.shaders[PARTICLE_SHADER]    = shader_create("src/renderer/shaders/particle/particle.vert", "src/renderer/shaders/particle/particle.frag", "src/renderer/shaders/particle/particle.geom");
    renderer.shaders[OBSTACLE_SHADER]    = shader_create("src/renderer/shaders/obstacle/obstacle.vert", "src/renderer/shaders/obstacle/obstacle.frag", "src/renderer/shaders/obstacle/obstacle.geom");
    renderer.shaders[PARJICLE_SHADER]    = shader_create("src/renderer/shaders/parjicle/parjicle.vert", "src/renderer/shaders/parjicle/parjicle.frag", "src/renderer/shaders/parjicle/parjicle.geom");
    renderer.shaders[PARSTACLE_SHADER]   = shader_create("src/renderer/shaders/parstacle/parstacle.vert", "src/renderer/shaders/parstacle/parstacle.frag", "src/renderer/shaders/parstacle/parstacle.geom");
    renderer.shaders[SCREEN_SHADER]      = shader_create("src/renderer/shaders/screen/screen.vert", "src/renderer/shaders/screen/screen.frag", NULL);
    /* --------------------- */
    renderer.vaos = malloc(NUM_VAOS * sizeof(VAO));
    renderer.vaos[TILE_VAO]         = vao_create(GL_STATIC_DRAW, GL_POINTS, 8, FALSE);
    renderer.vaos[WALL_VAO]         = vao_create(GL_STATIC_DRAW, GL_POINTS, 8, FALSE);
    renderer.vaos[ENTITY_VAO]       = vao_create(GL_DYNAMIC_DRAW, GL_POINTS, 10, FALSE);
    renderer.vaos[PROJECTILE_VAO]   = vao_create(GL_DYNAMIC_DRAW, GL_POINTS, 6, FALSE);
    renderer.vaos[GUI_VAO]          = vao_create(GL_STATIC_DRAW, GL_TRIANGLES, 9, TRUE);
    renderer.vaos[PARTICLE_VAO]     = vao_create(GL_DYNAMIC_DRAW, GL_POINTS, 7, FALSE);
    renderer.vaos[OBSTACLE_VAO]     = vao_create(GL_STATIC_DRAW, GL_POINTS, 5, FALSE);
    renderer.vaos[PARJICLE_VAO]     = vao_create(GL_DYNAMIC_DRAW, GL_POINTS, 8, FALSE);
    renderer.vaos[PARSTACLE_VAO]    = vao_create(GL_STATIC_DRAW, GL_POINTS, 5, FALSE);
    renderer.vaos[QUAD_VAO]         = vao_create(GL_STATIC_DRAW, GL_TRIANGLES, 4, FALSE);
    vao_attr(renderer.vaos[TILE_VAO]        , 0, 2, 0);
    vao_attr(renderer.vaos[TILE_VAO]        , 1, 2, 2);
    vao_attr(renderer.vaos[TILE_VAO]        , 2, 2, 4);
    vao_attr(renderer.vaos[TILE_VAO]        , 3, 1, 6);
    vao_attr(renderer.vaos[TILE_VAO]        , 4, 1, 7);
    vao_attr(renderer.vaos[WALL_VAO]        , 0, 2, 0);
    vao_attr(renderer.vaos[WALL_VAO]        , 1, 3, 2);
    vao_attr(renderer.vaos[WALL_VAO]        , 2, 3, 5);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 0, 3, 0);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 1, 1, 3);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 2, 1, 4);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 3, 1, 5);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 4, 4, 6);
    vao_attr(renderer.vaos[PROJECTILE_VAO]  , 0, 3, 0);
    vao_attr(renderer.vaos[PROJECTILE_VAO]  , 1, 1, 3);
    vao_attr(renderer.vaos[PROJECTILE_VAO]  , 2, 1, 4);
    vao_attr(renderer.vaos[PROJECTILE_VAO]  , 3, 1, 5);
    vao_attr(renderer.vaos[GUI_VAO]         , 0, 2, 0);
    vao_attr(renderer.vaos[GUI_VAO]         , 1, 2, 2);
    vao_attr(renderer.vaos[GUI_VAO]         , 2, 1, 4);
    vao_attr(renderer.vaos[GUI_VAO]         , 3, 4, 5);
    vao_attr(renderer.vaos[PARTICLE_VAO]    , 0, 3, 0);
    vao_attr(renderer.vaos[PARTICLE_VAO]    , 1, 1, 3);
    vao_attr(renderer.vaos[PARTICLE_VAO]    , 2, 3, 4);
    vao_attr(renderer.vaos[OBSTACLE_VAO]    , 0, 3, 0);
    vao_attr(renderer.vaos[OBSTACLE_VAO]    , 1, 1, 3);
    vao_attr(renderer.vaos[OBSTACLE_VAO]    , 2, 1, 4);
    vao_attr(renderer.vaos[PARJICLE_VAO]    , 0, 3, 0);
    vao_attr(renderer.vaos[PARJICLE_VAO]    , 1, 1, 3);
    vao_attr(renderer.vaos[PARJICLE_VAO]    , 2, 1, 4);
    vao_attr(renderer.vaos[PARJICLE_VAO]    , 3, 3, 5);
    vao_attr(renderer.vaos[PARSTACLE_VAO]   , 0, 3, 0);
    vao_attr(renderer.vaos[PARSTACLE_VAO]   , 1, 1, 3);
    vao_attr(renderer.vaos[PARSTACLE_VAO]   , 2, 1, 4);
    vao_attr(renderer.vaos[QUAD_VAO]        , 0, 2, 0);
    vao_attr(renderer.vaos[QUAD_VAO]        , 1, 2, 2);
    set_quad_vao();
    /* --------------------- */
    renderer.game_textures = malloc(NUM_GAME_TEXTURES * sizeof(Texture));
    renderer.gui_textures = malloc(NUM_GUI_TEXTURES * sizeof(Texture));
    load_textures();
    set_game_ssbo();
    set_gui_ssbo();
    /* --------------------- */
    link_shader_ubo(TILE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(WALL_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(ENTITY_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(ENTITY_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(ENTITY_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(ENTITY_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(HEALTHBAR_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(HEALTHBAR_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(HEALTHBAR_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(HEALTHBAR_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(PROJECTILE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PROJECTILE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(PROJECTILE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PROJECTILE_SHADER, ROTATION_UBO, "Rotation");
    link_shader_ubo(PROJECTILE_SHADER, TILT_UBO, "Tilt");
    link_shader_ubo(PROJECTILE_SHADER, CONSTANTS_UBO, "Constants");
    link_shader_ubo(SHADOW_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PARTICLE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PARTICLE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PARTICLE_SHADER, ZOOM_UBO, "Zoom");
    //link_shader_ubo(PARTICLE_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(OBSTACLE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(OBSTACLE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(OBSTACLE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(OBSTACLE_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(PARJICLE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PARJICLE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PARJICLE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(PARJICLE_SHADER, ROTATION_UBO, "Rotation");
    link_shader_ubo(PARJICLE_SHADER, TILT_UBO, "Tilt");
    link_shader_ubo(PARJICLE_SHADER, CONSTANTS_UBO, "Constants");
    //link_shader_ubo(PARJICLE_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(PARSTACLE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PARSTACLE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PARSTACLE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(PARSTACLE_SHADER, OUTLINE_UBO, "OutlineThickness");
    /* --------------------- */
    link_shader_ssbo(TILE_SHADER, GAME_SSBO);
    link_shader_ssbo(WALL_SHADER, GAME_SSBO);
    link_shader_ssbo(ENTITY_SHADER, GAME_SSBO);
    link_shader_ssbo(PROJECTILE_SHADER, GAME_SSBO);
    link_shader_ssbo(OBSTACLE_SHADER, GAME_SSBO);
    link_shader_ssbo(PARSTACLE_SHADER, GAME_SSBO);
    link_shader_ssbo(GUI_SHADER, GUI_SSBO);
    /* --------------------- */
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.width, window.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window.width, window.height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        puts("?");
}

void renderer_malloc(u32 vao_index, u32 vbo_length, u32 ebo_length)
{
    if (renderer.vaos[vao_index].mode == GL_POINTS)
        vbo_length *= renderer.vaos[vao_index].length;
    vao_malloc(renderer.vaos[vao_index], vbo_length, ebo_length);
}

void renderer_update(u32 vao_index, u32 vbo_offset, u32 vbo_length, f32* vbo_buffer, u32 ebo_offset, u32 ebo_length, u32* ebo_buffer)
{
    if (renderer.vaos[vao_index].mode == GL_POINTS)
        vbo_length *= renderer.vaos[vao_index].length;
    vao_update(renderer.vaos[vao_index], vbo_offset, vbo_length, vbo_buffer, ebo_offset, ebo_length, ebo_buffer);
}

void renderer_render(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glStencilFunc(GL_ALWAYS, 1, 0x01);
    glStencilMask(0x01);

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[WALL_SHADER]);
    vao_draw(renderer.vaos[WALL_VAO]);
    glStencilFunc(GL_NOTEQUAL, 1, 0x01);
    glStencilMask(0x01);
    shader_use(renderer.shaders[HEALTHBAR_SHADER]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    glStencilFunc(GL_NOTEQUAL, 1, 0x01);
    glStencilMask(0x00);
    shader_use(renderer.shaders[TILE_SHADER]);
    vao_draw(renderer.vaos[TILE_VAO]);
    shader_use(renderer.shaders[SHADOW_SHADER]);
    vao_draw(renderer.vaos[PROJECTILE_VAO]);
    vao_draw(renderer.vaos[OBSTACLE_VAO]);
    vao_draw(renderer.vaos[PARSTACLE_VAO]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    glStencilMask(0x01);
    shader_use(renderer.shaders[TILE_SHADOW_SHADER]);
    vao_draw(renderer.vaos[TILE_VAO]);
    glStencilFunc(GL_ALWAYS, 1, 0x01);
    shader_use(renderer.shaders[ENTITY_SHADER]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    shader_use(renderer.shaders[PARTICLE_SHADER]);
    vao_draw(renderer.vaos[PARTICLE_VAO]);
    shader_use(renderer.shaders[PARJICLE_SHADER]);
    vao_draw(renderer.vaos[PARJICLE_VAO]);
    shader_use(renderer.shaders[PROJECTILE_SHADER]);
    vao_draw(renderer.vaos[PROJECTILE_VAO]);
    shader_use(renderer.shaders[OBSTACLE_SHADER]);
    vao_draw(renderer.vaos[OBSTACLE_VAO]);
    shader_use(renderer.shaders[PARSTACLE_SHADER]);
    vao_draw(renderer.vaos[PARSTACLE_VAO]);
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUI_SHADER]);
    vao_draw(renderer.vaos[GUI_VAO]);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    shader_use(renderer.shaders[SCREEN_SHADER]);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    vao_draw(renderer.vaos[QUAD_VAO]);
}

void renderer_destroy(void)
{
    i32 i;
    for (i = 0; i < NUM_VAOS; i++)
        vao_destroy(renderer.vaos[i]);
    free(renderer.vaos);

    for (i = 0; i < NUM_SHADERS; i++)
        shader_destroy(renderer.shaders[i]);
    free(renderer.shaders);

    for (i = 0; i < NUM_UBOS; i++)
        ubo_destroy(renderer.ubos[i]);
    free(renderer.ubos);

    for (i = 0; i < NUM_GAME_TEXTURES; i++)
        texture_destroy(renderer.game_textures[i]);
    free(renderer.game_textures);

    for (i = 0; i < NUM_GUI_TEXTURES; i++)
        texture_destroy(renderer.gui_textures[i]);
    free(renderer.gui_textures);

    for (i = 0; i < NUM_SSBOS; i++)
        ssbo_destroy(renderer.ssbos[i]);
    free(renderer.ssbos);
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

void link_shader_ubo(u32 shader_index, u32 ubo_index, char *identifier)
{
    shader_bind_uniform_block(renderer.shaders[shader_index], ubo_index, identifier);
    ubo_bind_buffer_base(renderer.ubos[ubo_index], ubo_index);
}

void link_shader_ssbo(u32 shader_index, u32 ssbo_index)
{
    shader_use(renderer.shaders[shader_index]);
    ssbo_bind_buffer_base(renderer.ssbos[ssbo_index], ssbo_index);
}

void set_game_ssbo(void)
{
    u64 *handles = malloc(NUM_GAME_TEXTURES * sizeof(u64));
    for (i32 i = 0; i < NUM_GAME_TEXTURES; i++)
        handles[i] = renderer.game_textures[i].handle;
    ssbo_update(renderer.ssbos[GAME_SSBO], 0, NUM_GAME_TEXTURES * sizeof(u64), handles);
    free(handles);
}

void set_gui_ssbo(void)
{
    u64 *handles = malloc(NUM_GUI_TEXTURES * sizeof(u64));
    for (i32 i = 0; i < NUM_GUI_TEXTURES; i++)
        handles[i] = renderer.gui_textures[i].handle;
    ssbo_update(renderer.ssbos[GUI_SSBO], 0, NUM_GUI_TEXTURES * sizeof(u64), handles);
    free(handles);
}

void set_constants_ubo(void)
{
    f32 pi, sqrt2;
    pi = PI;
    sqrt2 = SQRT2;
    ubo_update(renderer.ubos[CONSTANTS_UBO], 0, sizeof(f32), &pi);
    ubo_update(renderer.ubos[CONSTANTS_UBO], sizeof(f32), sizeof(f32), &sqrt2);
}

void set_quad_vao(void)
{
    f32 quad_vertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    vao_malloc(renderer.vaos[QUAD_VAO], 24, 0);
    vao_update(renderer.vaos[QUAD_VAO], 0, 24, quad_vertices, 0, 0, NULL);
}

void set_outline_ubo(void)
{
    f32 outline_thickness = OUTLINE_THICKNESS;
    ubo_update(renderer.ubos[OUTLINE_UBO], 0, sizeof(f32), &outline_thickness);
}

void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    printf("\nGL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message);
    exit(1);
}

void load_textures(void)
{
    renderer.game_textures[KNIGHT_IDLE_DOWN_TEX]  = texture_create("assets/textures/game/knight/knight_idle_down.png");
    renderer.game_textures[KNIGHT_IDLE_RIGHT_TEX] = texture_create("assets/textures/game/knight/knight_idle_right.png");
    renderer.game_textures[KNIGHT_IDLE_UP_TEX]    = texture_create("assets/textures/game/knight/knight_idle_up.png");
    renderer.game_textures[KNIGHT_IDLE_LEFT_TEX]  = texture_create("assets/textures/game/knight/knight_idle_left.png");
    renderer.game_textures[KNIGHT_WALK_DOWN_1_TEX]  = texture_create("assets/textures/game/knight/knight_walk_down_1.png");
    renderer.game_textures[KNIGHT_WALK_RIGHT_TEX] = texture_create("assets/textures/game/knight/knight_walk_right.png");
    renderer.game_textures[KNIGHT_WALK_UP_1_TEX]    = texture_create("assets/textures/game/knight/knight_walk_up_1.png");
    renderer.game_textures[KNIGHT_WALK_LEFT_TEX]  = texture_create("assets/textures/game/knight/knight_walk_left.png");
    renderer.game_textures[KNIGHT_WALK_DOWN_2_TEX]  = texture_create("assets/textures/game/knight/knight_walk_down_2.png");
    renderer.game_textures[KNIGHT_WALK_UP_2_TEX]    = texture_create("assets/textures/game/knight/knight_walk_up_2.png");
    renderer.game_textures[KNIGHT_SHOOT_DOWN_1_TEX]  = texture_create("assets/textures/game/knight/knight_shoot_down_1.png");
    renderer.game_textures[KNIGHT_SHOOT_RIGHT_1_TEX] = texture_create("assets/textures/game/knight/knight_shoot_right_1.png");
    renderer.game_textures[KNIGHT_SHOOT_UP_1_TEX]    = texture_create("assets/textures/game/knight/knight_shoot_up_1.png");
    renderer.game_textures[KNIGHT_SHOOT_LEFT_1_TEX]  = texture_create("assets/textures/game/knight/knight_shoot_left_1.png");
    renderer.game_textures[KNIGHT_SHOOT_DOWN_2_TEX]  = texture_create("assets/textures/game/knight/knight_shoot_down_2.png");
    renderer.game_textures[KNIGHT_SHOOT_RIGHT_2_TEX] = texture_create("assets/textures/game/knight/knight_shoot_right_2.png");
    renderer.game_textures[KNIGHT_SHOOT_UP_2_TEX]    = texture_create("assets/textures/game/knight/knight_shoot_up_2.png");
    renderer.game_textures[KNIGHT_SHOOT_LEFT_2_TEX]  = texture_create("assets/textures/game/knight/knight_shoot_left_2.png");
    renderer.game_textures[BULLET_TEX]       = texture_create("assets/textures/game/bullet.png");
    renderer.game_textures[BULLET_2_TEX]     = texture_create("assets/textures/game/bullet_2.png");
    renderer.game_textures[TILE_TEX]         = texture_create("assets/textures/game/tile.png");
    renderer.game_textures[WALL_TOP_TEX]     = texture_create("assets/textures/game/wall_top.png");
    renderer.game_textures[WALL_SIDE_TEX]    = texture_create("assets/textures/game/wall.png");
    renderer.game_textures[BUSH_TEX]         = texture_create("assets/textures/game/bush.png");
    renderer.game_textures[ROCK_TEX]         = texture_create("assets/textures/game/rock.png");
    renderer.game_textures[GRASS_1_TEX]      = texture_create("assets/textures/game/grass1.png");
    renderer.game_textures[GRASS_2_TEX]      = texture_create("assets/textures/game/grass2.png");
    renderer.game_textures[GRASS_3_TEX]      = texture_create("assets/textures/game/grass3.png");
    renderer.game_textures[HELLSTONE_TEX]    = texture_create("assets/textures/game/hellstone.png");
    renderer.game_textures[SLIME_TEX]        = texture_create("assets/textures/game/slime.png");
    renderer.game_textures[GRAVESTONE_TEX]   = texture_create("assets/textures/game/gravestone.png");
    renderer.game_textures[TRAINING_DUMMY_TEX] = texture_create("assets/textures/game/training_dummy.png");
    renderer.game_textures[SHAITAN_LAVA_TEX] = texture_create("assets/textures/game/shaitan/shaitan_lava.png");
    renderer.game_textures[SHAITAN_FLOOR_1_TEX] = texture_create("assets/textures/game/shaitan/shaitan_floor_1.png");
    renderer.game_textures[SHAITAN_FLOOR_2_TEX] = texture_create("assets/textures/game/shaitan/shaitan_floor_2.png");
    renderer.game_textures[SHAITAN_WALL_SIDE_TEX] = texture_create("assets/textures/game/shaitan/shaitan_wall_side.png");
    renderer.game_textures[SHAITAN_WALL_TOP_TEX] = texture_create("assets/textures/game/shaitan/shaitan_wall_top.png");
    renderer.game_textures[SHAITAN_BARS_SIDE_TEX] = texture_create("assets/textures/game/shaitan/shaitan_bars_side.png");
    renderer.game_textures[SHAITAN_BARS_TOP_TEX] = texture_create("assets/textures/game/shaitan/shaitan_bars_top.png");
    renderer.game_textures[SHAITAN_HELLSTONE_TEX] = texture_create("assets/textures/game/shaitan/shaitan_hellstone.png");
    renderer.game_textures[GAME_NO_TEX] = texture_create("assets/textures/gui/none.png");

    renderer.gui_textures[NO_TEX]     = texture_create("assets/textures/gui/none.png");
    renderer.gui_textures[EMPTY_TEX]  = texture_create("assets/textures/gui/empty.png");
    renderer.gui_textures[BUTTON_TEX] = texture_create("assets/textures/gui/button.png");
    renderer.gui_textures[SWORD_1_TEX] = texture_create("assets/textures/game/sword1.png");
    renderer.gui_textures[SWORD_2_TEX] = texture_create("assets/textures/game/sword2.png");
    renderer.gui_textures[UPPER_A_TEX]      = texture_create("assets/textures/gui/text/uppera.png");
    renderer.gui_textures[UPPER_B_TEX]      = texture_create("assets/textures/gui/text/upperb.png");
    renderer.gui_textures[UPPER_C_TEX]      = texture_create("assets/textures/gui/text/upperc.png");
    renderer.gui_textures[UPPER_D_TEX]      = texture_create("assets/textures/gui/text/upperd.png");
    renderer.gui_textures[UPPER_E_TEX]      = texture_create("assets/textures/gui/text/uppere.png");
    renderer.gui_textures[UPPER_F_TEX]      = texture_create("assets/textures/gui/text/upperf.png");
    renderer.gui_textures[UPPER_G_TEX]      = texture_create("assets/textures/gui/text/upperg.png");
    renderer.gui_textures[UPPER_H_TEX]      = texture_create("assets/textures/gui/text/upperh.png");
    renderer.gui_textures[UPPER_I_TEX]      = texture_create("assets/textures/gui/text/upperi.png");
    renderer.gui_textures[UPPER_J_TEX]      = texture_create("assets/textures/gui/text/upperj.png");
    renderer.gui_textures[UPPER_K_TEX]      = texture_create("assets/textures/gui/text/upperk.png");
    renderer.gui_textures[UPPER_L_TEX]      = texture_create("assets/textures/gui/text/upperl.png");
    renderer.gui_textures[UPPER_M_TEX]      = texture_create("assets/textures/gui/text/upperm.png");
    renderer.gui_textures[UPPER_N_TEX]      = texture_create("assets/textures/gui/text/uppern.png");
    renderer.gui_textures[UPPER_O_TEX]      = texture_create("assets/textures/gui/text/uppero.png");
    renderer.gui_textures[UPPER_P_TEX]      = texture_create("assets/textures/gui/text/upperp.png");
    renderer.gui_textures[UPPER_Q_TEX]      = texture_create("assets/textures/gui/text/upperq.png");
    renderer.gui_textures[UPPER_R_TEX]      = texture_create("assets/textures/gui/text/upperr.png");
    renderer.gui_textures[UPPER_S_TEX]      = texture_create("assets/textures/gui/text/uppers.png");
    renderer.gui_textures[UPPER_T_TEX]      = texture_create("assets/textures/gui/text/uppert.png");
    renderer.gui_textures[UPPER_U_TEX]      = texture_create("assets/textures/gui/text/upperu.png");
    renderer.gui_textures[UPPER_V_TEX]      = texture_create("assets/textures/gui/text/upperv.png");
    renderer.gui_textures[UPPER_W_TEX]      = texture_create("assets/textures/gui/text/upperw.png");
    renderer.gui_textures[UPPER_X_TEX]      = texture_create("assets/textures/gui/text/upperx.png");
    renderer.gui_textures[UPPER_Y_TEX]      = texture_create("assets/textures/gui/text/uppery.png");
    renderer.gui_textures[UPPER_Z_TEX]      = texture_create("assets/textures/gui/text/upperz.png");
    renderer.gui_textures[LOWER_A_TEX]      = texture_create("assets/textures/gui/text/lowera.png");
    renderer.gui_textures[LOWER_B_TEX]      = texture_create("assets/textures/gui/text/lowerb.png");
    renderer.gui_textures[LOWER_C_TEX]      = texture_create("assets/textures/gui/text/lowerc.png");
    renderer.gui_textures[LOWER_D_TEX]      = texture_create("assets/textures/gui/text/lowerd.png");
    renderer.gui_textures[LOWER_E_TEX]      = texture_create("assets/textures/gui/text/lowere.png");
    renderer.gui_textures[LOWER_F_TEX]      = texture_create("assets/textures/gui/text/lowerf.png");
    renderer.gui_textures[LOWER_G_TEX]      = texture_create("assets/textures/gui/text/lowerg.png");
    renderer.gui_textures[LOWER_H_TEX]      = texture_create("assets/textures/gui/text/lowerh.png");
    renderer.gui_textures[LOWER_I_TEX]      = texture_create("assets/textures/gui/text/loweri.png");
    renderer.gui_textures[LOWER_J_TEX]      = texture_create("assets/textures/gui/text/lowerj.png");
    renderer.gui_textures[LOWER_K_TEX]      = texture_create("assets/textures/gui/text/lowerk.png");
    renderer.gui_textures[LOWER_L_TEX]      = texture_create("assets/textures/gui/text/lowerl.png");
    renderer.gui_textures[LOWER_M_TEX]      = texture_create("assets/textures/gui/text/lowerm.png");
    renderer.gui_textures[LOWER_N_TEX]      = texture_create("assets/textures/gui/text/lowern.png");
    renderer.gui_textures[LOWER_O_TEX]      = texture_create("assets/textures/gui/text/lowero.png");
    renderer.gui_textures[LOWER_P_TEX]      = texture_create("assets/textures/gui/text/lowerp.png");
    renderer.gui_textures[LOWER_Q_TEX]      = texture_create("assets/textures/gui/text/lowerq.png");
    renderer.gui_textures[LOWER_R_TEX]      = texture_create("assets/textures/gui/text/lowerr.png");
    renderer.gui_textures[LOWER_S_TEX]      = texture_create("assets/textures/gui/text/lowers.png");
    renderer.gui_textures[LOWER_T_TEX]      = texture_create("assets/textures/gui/text/lowert.png");
    renderer.gui_textures[LOWER_U_TEX]      = texture_create("assets/textures/gui/text/loweru.png");
    renderer.gui_textures[LOWER_V_TEX]      = texture_create("assets/textures/gui/text/lowerv.png");
    renderer.gui_textures[LOWER_W_TEX]      = texture_create("assets/textures/gui/text/lowerw.png");
    renderer.gui_textures[LOWER_X_TEX]      = texture_create("assets/textures/gui/text/lowerx.png");
    renderer.gui_textures[LOWER_Y_TEX]      = texture_create("assets/textures/gui/text/lowery.png");
    renderer.gui_textures[LOWER_Z_TEX]      = texture_create("assets/textures/gui/text/lowerz.png");
    renderer.gui_textures[NUM_0_TEX]  = texture_create("assets/textures/gui/text/0.png");
    renderer.gui_textures[NUM_1_TEX]  = texture_create("assets/textures/gui/text/1.png");
    renderer.gui_textures[NUM_2_TEX]  = texture_create("assets/textures/gui/text/2.png");
    renderer.gui_textures[NUM_3_TEX]  = texture_create("assets/textures/gui/text/3.png");
    renderer.gui_textures[NUM_4_TEX]  = texture_create("assets/textures/gui/text/4.png");
    renderer.gui_textures[NUM_5_TEX]  = texture_create("assets/textures/gui/text/5.png");
    renderer.gui_textures[NUM_6_TEX]  = texture_create("assets/textures/gui/text/6.png");
    renderer.gui_textures[NUM_7_TEX]  = texture_create("assets/textures/gui/text/7.png");
    renderer.gui_textures[NUM_8_TEX]  = texture_create("assets/textures/gui/text/8.png");
    renderer.gui_textures[NUM_9_TEX]  = texture_create("assets/textures/gui/text/9.png");
    renderer.gui_textures[SOULTAKER_LOGO_TEX] = texture_create("assets/textures/gui/logo.png");
    
    renderer.gui_textures[AMPERSAND_TEX] = texture_create("assets/textures/gui/text/ampersand.png");
    renderer.gui_textures[APOSTROPHE_TEX] = texture_create("assets/textures/gui/text/apostrophe.png");
    renderer.gui_textures[ASTERISK_TEX] = texture_create("assets/textures/gui/text/asterisk.png");
    renderer.gui_textures[AT_TEX] = texture_create("assets/textures/gui/text/at.png");
    renderer.gui_textures[BACKSLASH_TEX] = texture_create("assets/textures/gui/text/backslash.png");
    renderer.gui_textures[BACKTICK_TEX] = texture_create("assets/textures/gui/text/backtick.png");
    renderer.gui_textures[CARROT_TEX] = texture_create("assets/textures/gui/text/carrot.png");
    renderer.gui_textures[COLON_TEX] = texture_create("assets/textures/gui/text/colon.png");
    renderer.gui_textures[COMMA_TEX] = texture_create("assets/textures/gui/text/comma.png");
    renderer.gui_textures[DOLLAR_TEX] = texture_create("assets/textures/gui/text/dollar.png");
    renderer.gui_textures[EQUALS_TEX] = texture_create("assets/textures/gui/text/equals.png");
    renderer.gui_textures[EXCLAMATIONMARK_TEX] = texture_create("assets/textures/gui/text/exclamationmark.png");
    renderer.gui_textures[FORWARDSLASH_TEX] = texture_create("assets/textures/gui/text/forwardslash.png");
    renderer.gui_textures[GREATERTHAN_TEX] = texture_create("assets/textures/gui/text/greaterthan.png");
    renderer.gui_textures[HASH_TEX] = texture_create("assets/textures/gui/text/hash.png");
    renderer.gui_textures[LEFTCURLYBRACKET_TEX] = texture_create("assets/textures/gui/text/leftcurlybracket.png");
    renderer.gui_textures[LEFTPARENTHESES_TEX] = texture_create("assets/textures/gui/text/leftparentheses.png");
    renderer.gui_textures[LEFTSQUAREBRACKET_TEX] = texture_create("assets/textures/gui/text/leftsquarebracket.png");
    renderer.gui_textures[LESSTHAN_TEX] = texture_create("assets/textures/gui/text/lessthan.png");
    renderer.gui_textures[MINUS_TEX] = texture_create("assets/textures/gui/text/minus.png");
    renderer.gui_textures[PERCENT_TEX] = texture_create("assets/textures/gui/text/percent.png");
    renderer.gui_textures[PERIOD_TEX] = texture_create("assets/textures/gui/text/period.png");
    renderer.gui_textures[PIPE_TEX] = texture_create("assets/textures/gui/text/pipe.png");
    renderer.gui_textures[PLUS_TEX] = texture_create("assets/textures/gui/text/plus.png");
    renderer.gui_textures[QUESTIONMARK_TEX] = texture_create("assets/textures/gui/text/questionmark.png");
    renderer.gui_textures[QUOTE_TEX] = texture_create("assets/textures/gui/text/quote.png");
    renderer.gui_textures[RIGHTCURLYBRACKET_TEX] = texture_create("assets/textures/gui/text/rightcurlybracket.png");
    renderer.gui_textures[RIGHTPARENTHESES_TEX] = texture_create("assets/textures/gui/text/rightparentheses.png");
    renderer.gui_textures[RIGHTSQUAREBRACKET_TEX] = texture_create("assets/textures/gui/text/rightsquarebracket.png");
    renderer.gui_textures[SEMICOLON_TEX] = texture_create("assets/textures/gui/text/semicolon.png");
    renderer.gui_textures[TILDE_TEX] = texture_create("assets/textures/gui/text/tilde.png");
    renderer.gui_textures[UNDERSCORE_TEX] = texture_create("assets/textures/gui/text/underscore.png");

}