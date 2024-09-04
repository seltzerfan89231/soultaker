#version 460 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform Constants
{
    float pi;
    float sqrt2;
};

layout (std140) uniform Rotation
{
    float rotation;
};

layout (std140) uniform Minimap
{
    vec2 target;
    float zoom;
};

in VertexData
{
    vec2 position;
    float scale;
} inData[];

out VertexData
{
    vec2 texCoord;
};

void main() {
    vec2 offset, pre, position;
    float scale = inData[0].scale;
    pre = scale * zoom * (inData[0].position - target);
    float theta = - rotation + pi / 2;
    position.x =   pre.x * cos(theta) - pre.y * sin(theta);
    position.y = -(pre.y * cos(theta) + pre.x * sin(theta));

    // bottom left
    offset = scale * zoom * vec2(-0.5, -0.5);
    texCoord = vec2(0.0f, 0.0f);
    gl_Position = vec4(position + offset, 0.0, 1.0);
    EmitVertex();

    // bottom right
    offset = scale * zoom * vec2(0.5, -0.5);
    texCoord = vec2(1.0f, 0.0f);
    gl_Position = vec4(position + offset, 0.0, 1.0);
    EmitVertex();

    // top left
    offset = scale * zoom * vec2(-0.5, 0.5);
    texCoord = vec2(0.0f, 1.0f);
    gl_Position = vec4(position + offset, 0.0, 1.0);
    EmitVertex();

    // top right
    offset = scale * zoom * vec2(0.5, 0.5);
    texCoord = vec2(1.0f, 1.0f);
    gl_Position = vec4(position + offset, 0.0, 1.0);
    EmitVertex();
    
    EndPrimitive();
}