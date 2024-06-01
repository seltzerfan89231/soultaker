#version 460 core

#extension GL_ARB_bindless_texture : require

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

out vec2 texCoord;

void build_entity(vec4 position)
{
    vec2 offset;
    float extra_space = 0.05;

    // bottom left
    offset = zoom * vec2((-0.5 - extra_space) * ar, 0.0 - extra_space);
    texCoord = vec2(0.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // bottom right
    offset = zoom * vec2((0.5 + extra_space) * ar, 0.0 - extra_space);
    texCoord = vec2(1.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top left
    offset = zoom * vec2((-0.5 - extra_space) * ar, 1.0 + extra_space);
    texCoord = vec2(0.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top right
    offset = zoom * vec2((0.5 + extra_space) * ar, 1.0 + extra_space);
    texCoord = vec2(1.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}

void main() {
    build_entity(gl_in[0].gl_Position);
}