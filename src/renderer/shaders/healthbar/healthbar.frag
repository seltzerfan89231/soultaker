#version 460 core

layout (std140) uniform OutlineThickness
{
    float ot;
};

in float healthRatio;
in vec2 texCoord;

void main()
{
    if (texCoord.y < ot || texCoord.y > 1.0f - ot)
        gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else if (texCoord.x < ot * 3 / 20 || texCoord.x > 1.0f - ot * 3 / 20)
        gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else if (texCoord.x < healthRatio)
        gl_FragColor = vec4(0.3f, 0.9f, 0.3f, 1.0f);
    else
        gl_FragColor = vec4(0.9f, 0.3f, 0.3f, 1.0f);
}