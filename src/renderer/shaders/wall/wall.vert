#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
}