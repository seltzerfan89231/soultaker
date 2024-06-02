#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 1) in float texID;

out vec4 Col;

void main()
{
    gl_Position = vec4(aPos, 0.0f, 1.0f);
    Col = aCol;
}