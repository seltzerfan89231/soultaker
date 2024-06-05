#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 0, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

void main()
{
    gl_FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}