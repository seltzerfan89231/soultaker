#version 460 core

layout (std140) uniform OutlineThickness
{
    float ot;
};

in VertexData
{
    flat float depthValue;
    vec2 texCoord;
    flat float healthRatio;
};

void main()
{
    gl_FragDepth = depthValue;
    if (texCoord.y < ot * 5 || texCoord.y > 1.0f - ot * 5)
        gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else if (texCoord.x < ot * 3 / 4 || texCoord.x > 1.0f - ot * 3 / 4)
        gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else if (texCoord.x < healthRatio)
        gl_FragColor = vec4(0.3f, 0.9f, 0.3f, 1.0f);
    else
        gl_FragColor = vec4(0.9f, 0.3f, 0.3f, 1.0f);
}