#version 460 core

in VertexData
{
    vec3 color;
};

void main()
{
    gl_FragColor = vec4(color, 0.5f);
}