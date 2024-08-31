#version 460 core

#extension GL_ARB_bindless_texture : require

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

in VertexData
{
    int texID;
    int shadows;
    vec2 offset;
    vec4 position;
    float w, l;
} inData[];

out VertexData
{
    vec2 texCoord;
    flat int texID;
    flat int shadows;
};

void main()
{    
    vec4 position = inData[0].position;
    float w = inData[0].w;
    float l = inData[0].l;
    shadows = inData[0].shadows;
    texID = inData[0].texID;
    float V = 0.25;
    float y_offset = 0.0001;
    gl_Position = proj * view * (position + vec4(0 - V, y_offset, 0 - V, 0));
    texCoord = vec2(0 - V, 0 - V);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w + V, y_offset, 0 - V, 0));
    texCoord = vec2(w + V, 0 - V);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0 - V, y_offset, l + V, 0));
    texCoord = vec2(0 - V, l + V);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w + V, y_offset, l + V, 0));
    texCoord = vec2(w + V, l + V);
    EmitVertex();
    EndPrimitive();
}