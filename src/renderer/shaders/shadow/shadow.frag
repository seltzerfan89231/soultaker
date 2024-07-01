#version 460 core

in VertexData
{
    float height;
    vec2 texCoord;
};

void main()
{
    float d = distance(texCoord, vec2(0.5, 0.5));
    float hsqrd = height * height;
    if (d > 0.5 - hsqrd)
        discard;
    gl_FragColor = vec4(0.2f, 0.2f, 0.2f, (0.5 - hsqrd - d));
}