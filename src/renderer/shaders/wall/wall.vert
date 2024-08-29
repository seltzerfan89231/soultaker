#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aDimensions;
layout (location = 2) in vec3 aTexIDs;

out VertexData
{
    float x, z, w, h, l;
    int top_texID;
    int side1_texID;
    int side2_texID;
};

void main()
{
    x = aPos.x;
    z = aPos.y;
    w = aDimensions.x;
    h = aDimensions.y;
    l = aDimensions.z;
    top_texID = int(round(aTexIDs.x));
    side1_texID = int(round(aTexIDs.y));
    side2_texID = int(round(aTexIDs.z));
}