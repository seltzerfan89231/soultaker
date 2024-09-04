#version 460 core

in VertexData
{
    vec2 texCoord;
};

void main()
{
    if (distance(texCoord - vec2(0.5, 0.5), vec2(0, 0)) > 0.5)
        discard;
    gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}