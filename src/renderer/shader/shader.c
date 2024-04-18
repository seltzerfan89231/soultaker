#include "shader.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* read_file(char *path)
{
    FILE *ptr;
    char *content;
    ptr = fopen(path, "rb");
    fseek(ptr, 0, SEEK_END);
    i32 len = ftell(ptr);
    assert(len > 0);
    fseek(ptr, 0, SEEK_SET);
    content = calloc(1, len);
    assert(content != NULL);
    fread(content, 1, len, ptr);
    assert(strlen(content) > 0);
    fclose(ptr);
    return content;
}

static unsigned int compile(char *s_path, GLenum type)
{
    u32 shader;
    const char* shader_code;
    shader = glCreateShader(type);
    shader_code = read_file(s_path);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);
    char info_log[512];
    i32 success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        printf(info_log);
        exit(1);
    }
    return shader;
}

Shader shader_create(char* vs_path, char* fs_path, char* gs_path)
{
    Shader shader;
    u32 vertex, fragment, geometry;
    shader.id = glCreateProgram();
    vertex = compile(vs_path, GL_VERTEX_SHADER);
    glAttachShader(shader.id, vertex);
    fragment = compile(fs_path, GL_FRAGMENT_SHADER);
    glAttachShader(shader.id, fragment);
    if (gs_path != NULL) {
        geometry = compile(gs_path, GL_GEOMETRY_SHADER);
        glAttachShader(shader.id, geometry);
    }
    glLinkProgram(shader.id);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);
    char info_log[512];
    i32 success;
    glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader.id, 512, NULL, info_log);
        printf(info_log);
        exit(1);
    }
    return shader;
}

void shader_use(Shader shader)
{
    glUseProgram(shader.id);
}

void shader_destroy(Shader shader)
{
    glDeleteProgram(shader.id);
}