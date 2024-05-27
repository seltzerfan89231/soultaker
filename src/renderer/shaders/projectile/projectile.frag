#version 330 core

layout (std140) uniform Tilt
{
    float tilt;
};

out vec4 FragColor;
in float depthValue;

in vec2 texCoord;

uniform sampler2D tex;

void main()
{
    gl_FragDepth = depthValue;
    vec4 texColor = texture(tex, texCoord);
    if (texColor.a < 0.1)
        discard;
    FragColor = texColor;
}