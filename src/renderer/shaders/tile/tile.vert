#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aDimensions;
layout (location = 2) in float aShadows;
layout (location = 3) in float aTexID;

out VertexData
{
    int texID;
    int shadows;
    vec4 position;
    float w, l;
};

void main()
{
    position = vec4(aPos.x, 0.0f, aPos.y, 1.0f);
    w = aDimensions.x;
    l = aDimensions.y;
    shadows = int(round(aShadows));
    texID = int(round(aTexID));
}