#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aRotation;

out float rotation;

uniform mat4 view;
uniform mat4 proj;
uniform float zoom;

void main()
{
    gl_Position = proj * view * vec4(aPos.x, 0.0, aPos.z, 1.0f);
    gl_Position.y += zoom * aPos.y;
    rotation = aRotation;
}