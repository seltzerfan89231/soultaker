#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aTexID;
layout (location = 3) in vec4 aColor;

out vec2 texCoord;
out flat int texID;
out flat vec4 color;

void main()
{
    gl_Position = vec4(aPos, 0.0f, 1.0f);
    texCoord = aTexCoord;
    texID = int(round(aTexID));
    color = aColor;
}