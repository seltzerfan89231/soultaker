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
    float healthRatio;
} inData[];

out VertexData
{
    vec2 texCoord;
    flat float healthRatio;
};

void main() {
    vec4 position = gl_in[0].gl_Position;
    vec2 offset;
    float scale = inData[0].scale;
    healthRatio = inData[0].healthRatio;

    // bottom left
    offset = scale * zoom * vec2(-0.5 * ar, -0.30);
    texCoord = vec2(0.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // bottom right
    offset = scale * zoom * vec2(0.5 * ar, -0.30);
    texCoord = vec2(1.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top left
    offset = scale * zoom * vec2(-0.5 * ar, -0.15);
    texCoord = vec2(0.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top right
    offset = scale * zoom * vec2(0.5 * ar, -0.15);
    texCoord = vec2(1.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}