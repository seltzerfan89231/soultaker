#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 aPos;
layout (location = 3) in float aTexID;

layout (std140) uniform Constants
{
    float pi;
    float sqrt2;
};

layout (std140) uniform Rotation
{
    float rotation;
};

layout (std140) uniform Minimap
{
    vec2 target;
    float zoom;
};

out VertexData
{
    flat int texID;
};

void main()
{
    vec2 pre, position;
    float theta = - rotation + pi / 2;
    texID = int(round(aTexID));

    pre = zoom * (vec2(aPos.x, aPos.z) - target);
    position.x =   pre.x * cos(theta) - pre.y * sin(theta);
    position.y = -(pre.y * cos(theta) + pre.x * sin(theta));
    gl_Position = vec4(position, 0, 1);
}