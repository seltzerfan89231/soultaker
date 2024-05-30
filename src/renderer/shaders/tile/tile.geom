#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

out vec2 texCoord;

void build_tile(vec4 position)
{    
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.25f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.5f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1.0, 0.0));
    texCoord = vec2(0.25f, 0.25f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 1.0, 0.0));
    texCoord = vec2(0.5f, 0.25f);
    EmitVertex();
    EndPrimitive();
}

void main()
{    
    build_tile(gl_in[0].gl_Position);
}