#version 460 core

layout (std140) uniform OutlineThickness
{
    float ot;
};

in vec2 texCoord;

void main()
{
    gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    float a = 0.0;
    if (texCoord.x > a && texCoord.x < 1.0f - a && texCoord.y > a && texCoord.y < 1.0f - a)
        gl_FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}