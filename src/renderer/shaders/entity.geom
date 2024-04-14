#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float ar;
uniform float zoom;

void build_house(vec4 position)
{   
    gl_Position = position + zoom * vec4(-0.5 * ar, 0.0, 0.0, 0.0);    // 1:bottom-left
    EmitVertex();
    gl_Position = position + zoom * vec4(-0.5 * ar, 1.0, 0.0, 0.0);    // 3:top-left
    EmitVertex();
    gl_Position = position + zoom * vec4( 0.5 * ar, 0.0, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();
    gl_Position = position + zoom * vec4( 0.5 * ar, 1.0, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_house(gl_in[0].gl_Position);
} 