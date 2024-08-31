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
};

void main()
{    
    vec4 position = inData[0].position;
    float w = inData[0].w;
    float l = inData[0].l;
    vec2 offset = inData[0].offset;
    texID = inData[0].texID;
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(offset.x, offset.y);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, 0.0, 0.0, 0.0));
    texCoord = vec2((1.0f + offset.x) * w, offset.y);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, l, 0.0));
    texCoord = vec2(offset.x, (1.0f + offset.y) * l);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, 0.0, l, 0.0));
    texCoord = vec2((1.0f + offset.x) * w, (1.0f + offset.y) * l);
    EmitVertex();
    EndPrimitive();
}