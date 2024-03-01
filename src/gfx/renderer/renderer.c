#include "renderer.h"

Renderer renderer;

/* float vertices[] = {
    1.0f,  1.0f, 0.0f,  // top right
    1.0f, 0.0f, 0.0f,  // bottom right
    0.0f, 0.0f, 0.0f,  // bottom left
    0.0f,  1.0f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};
 */

float vertices[] = {
        0.0f, 0.0f, 0.0f,  0.2f, 1.0f,
        1.0f, 0.0f, 0.0f,  0.2f, 1.0f,
        1.0f,  1.0f, 0.0f,  0.2f, 1.0f,
        1.0f,  1.0f, 0.0f,  0.2f, 1.0f,
        0.0f,  1.0f, 0.0f,  0.2f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.2f, 1.0f,

        0.0f, 0.0f,  1.0f,  1.0f, 0.2f,
         1.0f, 0.0f,  1.0f,  1.0f, 0.2f,
         1.0f,  1.0f,  1.0f,  1.0f, 0.2f,
         1.0f,  1.0f,  1.0f,  1.0f, 0.2f,
        0.0f,  1.0f,  1.0f,  1.0f, 0.2f,
        0.0f, 0.0f,  1.0f,  1.0f, 0.2f,

        0.0f,  1.0f,  1.0f,  0.8f, 0.2f,
        0.0f,  1.0f, 0.0f,  0.8f, 0.2f,
        0.0f, 0.0f, 0.0f,  0.8f, 0.2f,
        0.0f, 0.0f, 0.0f,  0.8f, 0.2f,
        0.0f, 0.0f,  1.0f,  0.8f, 0.2f,
        0.0f,  1.0f,  1.0f,  0.8f, 0.2f,

         1.0f,  1.0f,  1.0f,  0.2f, 0.8f,
         1.0f,  1.0f, 0.0f,  0.2f, 0.8f,
         1.0f, 0.0f, 0.0f,  0.2f, 0.8f,
         1.0f, 0.0f, 0.0f,  0.2f, 0.8f,
         1.0f, 0.0f,  1.0f,  0.2f, 0.8f,
         1.0f,  1.0f,  1.0f,  0.2f, 0.8f,

        0.0f, 0.0f, 0.0f,  1.0f, 0.8f,
         1.0f, 0.0f, 0.0f,  1.0f, 0.8f,
         1.0f, 0.0f,  1.0f,  1.0f, 0.8f,
         1.0f, 0.0f,  1.0f,  1.0f, 0.8f,
        0.0f, 0.0f,  1.0f,  1.0f, 0.8f,
        0.0f, 0.0f, 0.0f,  1.0f, 0.8f,

        0.0f,  1.0f, 0.0f,  0.8f, 1.0f,
         1.0f,  1.0f, 0.0f,  0.8f, 1.0f,
         1.0f,  1.0f,  1.0f,  0.8f, 1.0f,
         1.0f,  1.0f,  1.0f,  0.8f, 1.0f,
        0.0f,  1.0f,  1.0f,  0.8f, 1.0f,
        0.0f,  1.0f, 0.0f,  0.8f, 1.0f,
    };

void renderer_init(void) 
{
    renderer.shader = shader_create("src/shaders/vert.sl", "src/shaders/frag.sl");
    renderer.vao = vao_create();
    renderer.vbo = vbo_create(GL_ARRAY_BUFFER);
    renderer.ebo = vbo_create(GL_ELEMENT_ARRAY_BUFFER);
    shader_use(renderer.shader);
    vao_bind(renderer.vao);
    vbo_bind(renderer.vbo);
    vbo_buffer(renderer.vbo, sizeof(vertices), vertices);
    // vbo_bind(renderer.ebo);
    // vbo_buffer(renderer.ebo, sizeof(indices), indices);
    vao_attr(0, 3, 5 * sizeof(f32), (void*)0);
    vao_attr(1, 2, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
}

void renderer_render(void)
{
    glClearColor(0.6f, 0.7f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/* abstractions */
u32 renderer_uniform_location(char *identifier) { return glGetUniformLocation(renderer.shader.ID, identifier); }