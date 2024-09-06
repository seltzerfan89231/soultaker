#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in float aRatio;

layout (std140) uniform Zoom
{
    float zoom;
};

out VertexData
{
    vec4 position;
    float healthRatio;
};

void main()
{
    position = vec4(aPos, 1.0);
    healthRatio = aRatio;
}