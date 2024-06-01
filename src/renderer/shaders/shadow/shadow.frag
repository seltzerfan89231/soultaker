#version 460 core

in float height;
in vec2 texCoord;

void main()
{
    float d = distance(texCoord, vec2(0.5, 0.5));
    if (d > 0.5 - height * height)
        discard;
    gl_FragColor = vec4(0.2f, 0.2f, 0.2f, 0.3f);
}