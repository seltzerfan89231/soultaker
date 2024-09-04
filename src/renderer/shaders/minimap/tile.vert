#version 460 core

layout (location = 0) in vec2 aPos;

out VertexData
{
    vec4 position;
};

void main()
{
    position = vec4(aPos, 0.0, 1.0);
}