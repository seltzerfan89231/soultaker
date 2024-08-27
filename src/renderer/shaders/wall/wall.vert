#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aDimensions;
layout (location = 2) in vec2 aTexIDs;

out VertexData
{
    float x, z, w, h, l;
    int top_texID;
    int side_texID;
};

void main()
{
    x = aPos.x;
    z = aPos.y;
    w = aDimensions.x;
    h = aDimensions.y;
    l = aDimensions.z;
    top_texID = int(round(aTexIDs.x));
    side_texID = int(round(aTexIDs.y));
}