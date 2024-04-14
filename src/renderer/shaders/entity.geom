#version 330 core
layout (points) in;
layout (points, max_vertices = 1) out;

uniform mat4 view;
uniform mat4 proj;

void main() {    
    gl_Position = gl_in[0].gl_Position; 
    EmitVertex();
    EndPrimitive();
}  