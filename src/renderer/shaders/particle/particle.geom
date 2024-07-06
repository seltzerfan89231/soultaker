#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform AspectRatio
{
    float ar;
};

layout (std140) uniform Zoom
{
    float zoom;
};

in VertexData
{
    float scale;
    vec3 color;
} inData[];

out VertexData
{
    vec3 color;
};

void main() {
    vec4 position = gl_in[0].gl_Position;
    vec2 offset;
    float scale = inData[0].scale;
    color = inData[0].color;

    // bottom left
    offset = zoom * scale * vec2(-0.5f * ar, -0.5f);
    gl_Position = position + vec4(offset, 0.0f, 0.0f);
    EmitVertex();

    // bottom right
    offset = zoom * scale * vec2(0.5f * ar, -0.5f);
    gl_Position = position + vec4(offset, 0.0f, 0.0f);
    EmitVertex();

    // top left
    offset = zoom * scale * vec2(-0.5f * ar, 0.5f);
    gl_Position = position + vec4(offset, 0.0f, 0.0f);
    EmitVertex();

    // top right
    offset = zoom * scale * vec2(0.5f * ar, 0.5f);
    gl_Position = position + vec4(offset, 0.0f, 0.0f);
    EmitVertex();
    
    EndPrimitive();
}