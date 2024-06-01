#version 460 core

#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aRotation;

layout (std140) uniform Matrices {
    mat4 view;
    mat4 proj;
};

layout (std140) uniform Zoom {
    float zoom;
};

out float projectile_rotation;

void main()
{
    gl_Position = proj * view * vec4(aPos.x, 0.0, aPos.z, 1.0f);
    gl_Position.y += zoom * aPos.y;
    projectile_rotation = aRotation;
}