#version 330 core
out vec4 FragColor;

in vec2 Col;

void main()
{
    FragColor = vec4(Col, 0.2f, 1.0f);
}