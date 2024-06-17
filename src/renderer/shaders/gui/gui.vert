#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aTexID;
layout (location = 3) in float aOpacity;

out vec2 texCoord;
out flat float texID;
out flat float opacity;

void main()
{
    gl_Position = vec4(aPos, 0.0f, 1.0f);
    texCoord = aTexCoord;
    texID = aTexID;
    opacity = aOpacity;
}