#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

in VertexData
{
    float scale;
} inData[];

out VertexData
{
    float height;
    vec2 texCoord;
};

void main()
{
    vec4 position = gl_in[0].gl_Position;
    height = position.y;
    position.y = 0.0f;
    float scale = inData[0].scale;
    gl_Position = proj * view * (position + scale * vec4(-0.5, 0.0, -0.5, 0.0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + scale * vec4(0.5, 0.0, -0.5, 0.0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + scale * vec4(-0.5, 0.0, 0.5, 0.0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + scale * vec4(0.5, 0.0, 0.5, 0.0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    EndPrimitive();
}