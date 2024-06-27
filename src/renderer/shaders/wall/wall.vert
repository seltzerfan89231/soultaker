#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexIDs;

out VertexData
{
    int top_texID;
    int side_texID;
};

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    top_texID = int(round(aTexIDs.x));
    side_texID = int(round(aTexIDs.y));
}