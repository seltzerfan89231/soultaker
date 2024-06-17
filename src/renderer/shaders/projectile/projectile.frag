#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 0, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

layout (std140) uniform Tilt
{
    float tilt;
};

in vec2 texCoord;

void main()
{
    vec4 texColor = texture(sampler2D(tex[1]), texCoord);
    if (texColor.a < 0.1)
        discard;
    gl_FragColor = texColor;
}