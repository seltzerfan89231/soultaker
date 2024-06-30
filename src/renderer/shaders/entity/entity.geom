#version 460 core

#extension GL_ARB_bindless_texture : require

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

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
    vec4 position = gl_in[0].gl_Position;
    vec2 offset;
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