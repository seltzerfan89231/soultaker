#version 330 core
layout (points) in;
layout (points, max_vertices = 1) out;

uniform float ar;
uniform float zoom;
uniform float camera_rotation;
uniform float c;
uniform float k;

out vec2 texCoord;

in float rotation[];

void build_projectile(vec4 position) 
{
    float a = rotation[0] - camera_rotation;
    vec2 offset;
    offset = zoom * vec2(k * ar * cos(a - 3 * c), k * sin(a - 3 * c));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 1:bottom-left
    texCoord = vec2(0.0f, 0.25f);
    EmitVertex();
    offset = zoom * vec2(k * ar * cos(a + 3 * c), k * sin(a + 3 * c));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 3:top-left
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    offset = zoom * vec2(k * ar * cos(a - c), k * sin(a - c));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 2:bottom-right
    texCoord = vec2(0.25f, 0.25f);
    EmitVertex();
    offset = zoom * vec2(k * ar * cos(a + c), k * sin(a + c));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 4:top-right
    texCoord = vec2(0.25f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

void main() {
    // build_projectile(gl_in[0].gl_Position);
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    EndPrimitive();
}