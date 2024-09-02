#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 0, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

in VertexData
{
    vec2 texCoord;
    vec2 relCoord;
    flat int texID;
    flat int shadows;
};

void main()
{
    if (relCoord.x < 0 || relCoord.x >= 1 || relCoord.y < 0 || relCoord.y >= 1)
        discard;
    gl_FragColor = texture(sampler2D(tex[texID]), texCoord);
}