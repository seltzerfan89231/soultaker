#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCenter;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexID;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

out VertexData
{
    vec2 texCoord;
    flat float depthValue;
    flat int texID;
};

void main()
{
    gl_Position = proj * view * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    vec4 center = proj * view * vec4(aCenter.x, 0.0, aCenter.y, 1.0);
    depthValue = 0.5 + 0.5 * center.z / center.w;
    texID = int(round(aTexID));
}