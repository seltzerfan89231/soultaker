#version 460 core

#extension GL_ARB_bindless_texture : require

layout (points) in;
layout (triangle_strip, max_vertices = 20) out;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

out vec2 texCoord;
out flat int texID;
out flat float depthValue;

void build_top(vec4 position)
{   
    texID = 3;
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1.0, 0.0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 1.0, 0.0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    EndPrimitive();
}

void build_sides(vec4 position)
{
    texID = 4;
    gl_Position = proj * view * (position + vec4(1.0, -position.y, 0.0, 0.0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(0.0, -position.y, 0.0, 0.0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();

    
    gl_Position = proj * view * (position + vec4(0.0, -position.y, 0.0, 0.0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 0.0, 0.0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(0.0, -position.y, 1.0, 0.0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1.0, 0.0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();

    gl_Position = proj * view * (position + vec4(1.0, -position.y, 1.0, 0.0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 1.0, 0.0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(1.0, -position.y, 0.0, 0.0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 0.0, 0.0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();

    gl_Position = proj * view * (position + vec4(0.0, -position.y, 1.0, 0.0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0.0, 0.0, 1.0, 0.0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, -position.y, 1.0, 0.0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(1.0, 0.0, 1.0, 0.0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

void main() 
{   
    vec4 center = proj * view * (gl_in[0].gl_Position + vec4(0.5, -gl_in[0].gl_Position.y, 0.5, 0.0));
    depthValue = 0.5 + 0.5 * center.z / center.w;
    build_top(gl_in[0].gl_Position);
    build_sides(gl_in[0].gl_Position);
}