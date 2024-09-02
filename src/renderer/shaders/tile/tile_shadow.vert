#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aRelCoord;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aOffset;
layout (location = 4) in float aShadows;
layout (location = 5) in float aTexID;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

out VertexData
{
    vec2 texCoord;
    vec2 relCoord;
    flat int texID;
    flat int shadows;
};

void main()
{
    gl_Position = proj * view * vec4(aPos.x + aOffset.x, 0.0f, aPos.y + aOffset.y, 1.0f);
    texCoord = aTexCoord + aOffset;
    relCoord = aRelCoord + aOffset;
    shadows = int(round(aShadows));
    texID = int(round(aTexID));
}