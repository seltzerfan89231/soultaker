#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 0, std430) readonly buffer ssbo
{
    uvec2 tex[];
};


in VertexData
{
    flat int texID;
};

void main()
{
    gl_FragColor = texture(sampler2D(tex[texID]), vec2(0.5, 0.5));
}