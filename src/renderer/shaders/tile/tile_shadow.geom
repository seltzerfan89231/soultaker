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
    int offset;
    vec4 position;
} inData[];

out VertexData
{
    vec2 texCoord;
    vec2 relCoord;
    flat int texID;
    flat int shadows;
};

void main()
{    
    vec4 position = inData[0].position;
    vec2 offset;
    float ox[] = { 1,  0, -1,  1,  0, -1,  1,  0, -1};
    float oy[] = { 1,  1,  1,  0,  0,  0, -1, -1, -1};
    int oi = inData[0].offset;
    offset = vec2(ox[oi], -oy[oi]);
    shadows = inData[0].shadows;
    texID = inData[0].texID;
    float v = 0.25;

    gl_Position = proj * view * (position + vec4(-v, 0.0, -v, 0.0));
    texCoord = vec2(offset.x - v, offset.y - v);
    relCoord = vec2(-v, -v);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1 + v, 0.0, - v, 0.0));
    texCoord = vec2(1.0f + offset.x + v, offset.y - v);
    relCoord = vec2(1 + v, -v);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(-v, 0.0, 1 + v, 0.0));
    texCoord = vec2(offset.x - v, 1.0f + offset.y + v);
    relCoord = vec2(-v, 1 + v);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1 + v, 0.0, 1 + v, 0.0));
    texCoord = vec2(1.0f + offset.x + v, 1.0f + offset.y + v);
    relCoord = vec2(1 + v, 1 + v);
    EmitVertex();
    EndPrimitive();
}