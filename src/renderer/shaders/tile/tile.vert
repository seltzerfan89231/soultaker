#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 aPos;
layout (location = 1) in float aTexID;

out VertexData
{
    int texID;
    vec4 position;
};

void main()
{
    position = vec4(aPos.x, 0.0f, aPos.y, 1.0f);
    texID = int(round(aTexID));
}