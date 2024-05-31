#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 1, std430) readonly buffer ssbo
{
    uvec2 tex[5];
};

out vec4 FragColor;

in vec2 texCoord;
in flat int texID;

void main()
{
    FragColor = texture(sampler2D(tex[texID]), texCoord);
}