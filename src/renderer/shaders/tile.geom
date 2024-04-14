#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 20) out;

uniform mat4 view;
uniform mat4 proj;

void draw_top(vec4 position)
{    
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 1.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
    EmitVertex();
    EndPrimitive();
}

void draw_sides(vec4 position)
{
    gl_Position = proj * view * (position + vec4(0.0, -position.y, 0.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(1.0, -position.y, 0.0, 0.0));
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
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
    draw_top(gl_in[0].gl_Position);
    if (gl_in[0].gl_Position.y != 0) {
        draw_sides(gl_in[0].gl_Position);
    }
}