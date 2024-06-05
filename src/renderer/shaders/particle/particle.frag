#version 460 core

layout (std140) uniform OutlineThickness
{
    float ot;
};

in vec2 texCoord;

void main()
{
    gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    if (texCoord.x > ot && texCoord.x < 1.0f - ot && texCoord.y > ot && texCoord.y < 1.0f- ot)
        gl_FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}