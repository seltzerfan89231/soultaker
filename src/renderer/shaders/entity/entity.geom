#version 460 core

#extension GL_ARB_bindless_texture : require

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

layout (std140) uniform AspectRatio
{
    highp float ar;
};

layout (std140) uniform Zoom
{
    float zoom;
};

in VertexData
{
    vec4 position;
    float scale;
    int texID;
    float x, y, w, h;
} inData[];

out VertexData
{
    vec2 texCoord;
    flat int texID;
};

void main() {
    vec2 offset;
    vec4 position = proj * view * vec4(inData[0].position.x, 0.0, inData[0].position.z, 1.0);
    position.y += zoom * inData[0].position.y;
    float scale = inData[0].scale;
    texID = inData[0].texID;
    float x, y, w, h;
    x = inData[0].x, y = inData[0].y;
    w = inData[0].w, h = inData[0].h;

    // bottom left
    offset = scale * zoom * vec2((x - w / 2) * ar, y);
    texCoord = vec2(0.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // bottom right
    offset = scale * zoom * vec2((x + w / 2) * ar, y);
    texCoord = vec2(1.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top left
    offset = scale * zoom * vec2((x - w / 2) * ar, y + h);
    texCoord = vec2(0.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top right
    offset = scale * zoom * vec2((x + w / 2) * ar, y + h);
    texCoord = vec2(1.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}