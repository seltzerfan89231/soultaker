#ifndef SHADER_H
#define SHADER_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

typedef struct Shader {
    u32 id;
} Shader;

Shader shader_create(char* vs_path, char* fs_path);
void shader_use(Shader shader);
void shader_destroy(Shader shader);

#endif