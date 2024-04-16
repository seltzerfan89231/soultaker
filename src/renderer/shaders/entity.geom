#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float ar;
uniform float zoom;

in float rotation[];
out vec2 texCoord;

void build_house(vec4 position)
{   
    float a = rotation[0];
    float k = 1 / sqrt(2);
    float c = 3.141592653589 / 4;
    vec2 offset;
    offset = zoom * vec2(-0.5 * ar, 0.0);
    offset = zoom * vec2(k / ar * cos(a - 3 * c), k * sin(a - 3 * c) + 0.5);
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 1:bottom-left
    texCoord = vec2(0.0f, 0.25f);
    EmitVertex();
    offset = zoom * vec2(-0.5 * ar, 1.0);
    offset = zoom * vec2(k / ar * cos(a + 3 * c), k * sin(a + 3 * c) + 0.5);
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 3:top-left
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    offset = zoom * vec2(0.5 * ar, 0.0);
    offset = zoom * vec2(k / ar * cos(a - c), k * sin(a - c) + 0.5);
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 2:bottom-right
    texCoord = vec2(0.25f, 0.25f);
    EmitVertex();
    offset = zoom * vec2( 0.5 * ar, 1.0);
    offset = zoom * vec2(k / ar * cos(a + c), k * sin(a + c) + 0.5);
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 4:top-right
    texCoord = vec2(0.25f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_house(gl_in[0].gl_Position);
}