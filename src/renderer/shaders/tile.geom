#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 20) out;

uniform mat4 view;
uniform mat4 proj;
uniform vec3 player_pos;

out vec2 texCoord;

void build_top(vec4 position)
{    
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1.0, 0.0));
    texCoord = vec2(0.25f, 0.25f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 1.0, 0.0));
    texCoord = vec2(0.5f, 0.25f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.25f, 0.0f);
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.5f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

void build_sides(vec4 position)
{
    gl_Position = proj * view * (position + vec4(0.0, -position.y, 0.0, 0.0));
    texCoord = vec2(0.00f, 0.5f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.00f, 0.25f);
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(1.0, -position.y, 0.0, 0.0));
    texCoord = vec2(0.25f, 0.5f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.25f, 0.25);
    EmitVertex();
    EndPrimitive();

    gl_Position = proj * view * (position + vec4(0.0, -position.y, 1.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1.0, 0.0));
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(0.0, -position.y, 0.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    EmitVertex();
    EndPrimitive();

    gl_Position = proj * view * (position + vec4(1.0, -position.y, 0.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(1.0, -position.y, 1.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 1.0, 0.0));
    EmitVertex();
    EndPrimitive();

    gl_Position = proj * view * (position + vec4(1.0, -position.y, 1.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 1.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, -position.y, 1.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1.0, 0.0));
    EmitVertex();
    EndPrimitive();
}

void main() 
{    
    build_top(gl_in[0].gl_Position);
    if (gl_in[0].gl_Position.y != 0) {
        build_sides(gl_in[0].gl_Position);
    }
}