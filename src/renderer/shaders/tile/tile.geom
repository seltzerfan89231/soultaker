#version 460 core

#extension GL_ARB_bindless_texture : require

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

layout (std140) uniform GameTime
{
    float time;
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
    flat int texID;
};

void main()
{    
    vec4 position = inData[0].position;
    float t = time - int(time);
    vec2 offset;
    switch(inData[0].offset) {
        case 0:
            offset = vec2(0, 0); break;
        case 1:
            offset = vec2(1, 0); break;
        case 2:
            offset = vec2(0, -1); break;
        case 3:
            offset = vec2(1, -1); break;
    }
    offset *= t;
    texID = inData[0].texID;
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(offset.x, offset.y);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1, 0.0, 0.0, 0.0));
    texCoord = vec2(1.0f + offset.x, offset.y);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1, 0.0));
    texCoord = vec2(offset.x, 1.0f + offset.y);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1, 0.0, 1, 0.0));
    texCoord = vec2(1.0f + offset.x, 1.0f + offset.y);
    EmitVertex();
    EndPrimitive();
}