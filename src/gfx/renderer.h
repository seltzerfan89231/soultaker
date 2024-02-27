#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>
#include "vao.h"
#include "vbo.h"
#include "shader.h"

typedef struct Renderer {
    VAO vao;
    VBO vbo, ebo;
    Shader shader;
} Renderer;

void renderer_init(void);
void renderer_render(void);

extern Renderer renderer;

#endif