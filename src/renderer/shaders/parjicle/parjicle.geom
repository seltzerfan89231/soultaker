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

layout (std140) uniform Constants
{
    float pi;
    float sqrt2;
};

layout (std140) uniform Rotation
{
    float rotation;
};

layout (std140) uniform Tilt
{
    float tilt;
};

in VertexData
{
    float scale;
    float projectileRotation;
    vec3 color;
} inData[];

out VertexData
{
    vec3 color;
};

void main() {
    vec4 position = gl_in[0].gl_Position;
    color = inData[0].color;
    float scale = inData[0].scale;
    float drot = inData[0].projectileRotation - rotation;
    drot = atan(tan(drot) / cos(pi / 2 + tilt)) + (cos(drot) > 0 ? 0 : pi);
    vec2 offset;
    offset = scale * zoom * (1 / sqrt2) * vec2(ar * cos(drot - 3 * pi / 4), sin(drot - 3 * pi / 4));
    gl_Position = position + vec4(offset, 0.0 , 0.0);    // 1:bottom-left
    EmitVertex();

    offset = scale * zoom * (1 / sqrt2) * vec2(ar * cos(drot - pi / 4), sin(drot - pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();

    offset = scale * zoom * (1 / sqrt2) * vec2(ar * cos(drot + 3 * pi / 4), sin(drot + 3 * pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 3:top-left
    EmitVertex();

    offset = scale * zoom * (1 / sqrt2) * vec2(ar * cos(drot + pi / 4), sin(drot + pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    EndPrimitive();
}