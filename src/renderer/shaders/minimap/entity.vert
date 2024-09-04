#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aScale;

out VertexData
{
    vec2 position;
    float scale;
};

void main()
{
    position = vec2(aPos.x, aPos.z);
    scale = aScale;
}