#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float ar;
uniform float zoom;

void build_entity(vec4 position)
{
    vec2 offset;
    
    // bottom left
    offset = zoom * vec2(-0.55 * ar, 0.0);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top left
    offset = zoom * vec2(-0.55 * ar, 1.1);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // bottom right
    offset = zoom * vec2(0.55 * ar, 0.0);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top right
    offset = zoom * vec2( 0.55 * ar, 1.1);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}

void main() {
    build_entity(gl_in[0].gl_Position);
}