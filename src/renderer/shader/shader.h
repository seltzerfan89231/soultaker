#ifndef SHADER_H
#define SHADER_H

#include <glad.h>
#include <glfw.h>
#include "../../util/type.h"

typedef struct {
    u32 id;
} Shader;

Shader shader_create(char* vs_path, char* fs_path, char* gs_path);
void shader_bind_block(Shader shader, u32 index, char* identifier);
void shader_use(Shader shader);
void shader_destroy(Shader shader);

#endif