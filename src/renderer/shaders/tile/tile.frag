#version 460 core

#extension GL_ARB_bindless_texture : require

out vec4 FragColor;

layout (binding = 1, std430) readonly buffer ssbo
{
    uvec2 tex[5];
};

in vec2 texCoord;

void main()
{
    FragColor = texture(sampler2D(tex[2]), texCoord);
}