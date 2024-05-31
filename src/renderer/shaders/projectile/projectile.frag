#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 1, std430) readonly buffer ssbo
{
    uvec2 tex[5];
};

layout (std140) uniform Tilt
{
    float tilt;
};

out vec4 FragColor;
in float depthValue;

in vec2 texCoord;

void main()
{
    gl_FragDepth = depthValue;
    vec4 texColor = texture(sampler2D(tex[1]), texCoord);
    if (texColor.a < 0.1)
        discard;
    FragColor = texColor;
}