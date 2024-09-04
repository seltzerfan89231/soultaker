#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 aPos;
layout (location = 3) in float aTexID;

out VertexData
{
    flat int texID;
    vec2 position;
};

void main()
{
    position = aPos;
    texID = int(round(aTexID));
}