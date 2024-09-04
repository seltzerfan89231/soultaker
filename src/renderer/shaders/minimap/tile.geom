#version 460 core

#extension GL_ARB_bindless_texture : require

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform Constants
{
    float pi;
    float sqrt2;
};

layout (std140) uniform Rotation
{
    float rotation;
};

layout (std140) uniform Minimap
{
    vec2 target;
    float zoom;
};

in VertexData
{
    flat int texID;
    vec2 position;
} inData[];

out VertexData
{
    flat int texID;
};

void main()
{   
    vec2 offset, pre, position;
    float theta = - rotation + pi / 2;
    texID = inData[0].texID;
    
    pre = zoom * (inData[0].position - target + vec2(0, 0));
    position.x =   pre.x * cos(theta) - pre.y * sin(theta);
    position.y = -(pre.y * cos(theta) + pre.x * sin(theta));
    gl_Position = vec4(position, 0, 1);
    EmitVertex();

    pre = zoom * (inData[0].position - target + vec2(0, 1));
    position.x =   pre.x * cos(theta) - pre.y * sin(theta);
    position.y = -(pre.y * cos(theta) + pre.x * sin(theta));
    gl_Position = vec4(position, 0, 1);
    EmitVertex();

    pre = zoom * (inData[0].position - target + vec2(1, 0));
    position.x =   pre.x * cos(theta) - pre.y * sin(theta);
    position.y = -(pre.y * cos(theta) + pre.x * sin(theta));
    gl_Position = vec4(position, 0, 1);
    EmitVertex();

    pre = zoom * (inData[0].position - target + vec2(1, 1));
    position.x =   pre.x * cos(theta) - pre.y * sin(theta);
    position.y = -(pre.y * cos(theta) + pre.x * sin(theta));
    gl_Position = vec4(position, 0, 1);
    EmitVertex();

    EndPrimitive();
}