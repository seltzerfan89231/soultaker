#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VertexData
{
    vec4 position;
} inData[];

out VertexData
{
    vec2 texCoord;
};

void main()
{   
    vec4 position = inData[0].position;
    float k = 1;
    gl_Position = k * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = k * (position + vec4(1, 0.0, 0.0, 0.0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = k * (position + vec4(0.0, 0.0, 1, 0.0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = k * (position + vec4(1, 0.0, 1, 0.0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    EndPrimitive();
}