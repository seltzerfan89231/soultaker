#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, texCoord);
    if (texColor.a < 0.1)
        discard;
    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}