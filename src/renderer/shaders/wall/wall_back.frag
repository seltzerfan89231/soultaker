#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in float depthValue;

void main()
{
    gl_FragDepth = depthValue;
    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}