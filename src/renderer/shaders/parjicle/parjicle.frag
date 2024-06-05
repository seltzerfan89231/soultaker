#version 460 core

in vec2 texCoord;

void main()
{
    gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    if (texCoord.x > 0.05 && texCoord.x < 0.95 && texCoord.y > 0.05 && texCoord.y < 0.95)
        gl_FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}