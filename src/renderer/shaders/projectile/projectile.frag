#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 0, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

layout (std140) uniform Tilt
{
    float tilt;
};

in VertexData
{
    vec2 texCoord;
    flat int texID;
};

void main()
{
    vec4 texColor = texture(sampler2D(tex[texID]), texCoord);
    if (texColor.a < 0.1)
        discard;
    gl_FragColor = texColor;
}