#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 0, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

in vec2 texCoord;

void main()
{
    gl_FragColor = texture(sampler2D(tex[2]), texCoord);
}