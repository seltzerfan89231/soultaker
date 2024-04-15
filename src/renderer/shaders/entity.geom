#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float ar;
uniform float zoom;

out vec2 texCoord;

void build_house(vec4 position)
{   
    gl_Position = position + zoom * vec4(-0.5 * ar, 0.0, 0.0, 0.0);    // 1:bottom-left
    texCoord = vec2(0.0f, 0.25f);
    EmitVertex();
    gl_Position = position + zoom * vec4(-0.5 * ar, 1.0, 0.0, 0.0);    // 3:top-left
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = position + zoom * vec4( 0.5 * ar, 0.0, 0.0, 0.0);    // 2:bottom-right
    texCoord = vec2(0.25f, 0.25f);
    EmitVertex();
    gl_Position = position + zoom * vec4( 0.5 * ar, 1.0, 0.0, 0.0);    // 4:top-right
    texCoord = vec2(0.25f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_house(gl_in[0].gl_Position);
}