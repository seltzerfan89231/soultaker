#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aOffset;
layout (location = 2) in float aShadows;
layout (location = 3) in float aTexID;

out VertexData
{
    int texID;
    int shadows;
    vec2 offset;
    vec4 position;
};

void main()
{
    position = vec4(aPos.x, 0.0f, aPos.y, 1.0f);
    shadows = int(round(aShadows));
    texID = int(round(aTexID));
    offset = aOffset;
}