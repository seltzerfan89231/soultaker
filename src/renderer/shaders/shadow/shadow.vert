#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aScale;

out VertexData
{
    float scale;
};

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    scale = aScale;
}