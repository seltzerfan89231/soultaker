#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aScale;
layout (location = 2) in float aRatio;

layout (std140) uniform Zoom
{
    float zoom;
};

out VertexData
{
    vec4 position;
    float scale;
    float healthRatio;
};

void main()
{
    position = vec4(aPos, 1.0);
    scale = aScale;
    healthRatio = aRatio;
}