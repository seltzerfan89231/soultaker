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

in float inputVars[];

out vec2 texCoord;
out flat float scale;

void main() {
    vec4 position = gl_in[0].gl_Position;
    vec2 offset;
    scale = inputVars[0];

    // bottom left
    offset = scale * zoom * vec2(-0.5 * ar, 0.0);
    texCoord = vec2(0.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // bottom right
    offset = scale * zoom * vec2(0.5 * ar, 0.0);
    texCoord = vec2(1.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top left
    offset = scale * zoom * vec2(-0.5 * ar, 1.0);
    texCoord = vec2(0.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top right
    offset = scale * zoom * vec2(0.5 * ar, 1.0);
    texCoord = vec2(1.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}