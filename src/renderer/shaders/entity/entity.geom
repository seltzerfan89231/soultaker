#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform AspectRatio
{
    float ar;
};

layout (std140) uniform Zoom
{
    float zoom;
};

layout (std140) uniform Constants
{
    float pi;
    float sqrt2;
};

layout (std140) uniform Rotation
{
    float rotation;
};

layout (std140) uniform Tilt
{
    float tilt;
};

out vec2 texCoord;
out float depthValue;

void build_entity(vec4 position)
{
    vec2 offset;
    float buffer = 0.05;
    depthValue = 0.5 + 0.5 * position.z;
    depthValue -= 0.001;

    // bottom left
    offset = zoom * vec2((-0.5 - buffer) * ar, 0.0 - buffer);
    texCoord = vec2(0.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top left
    offset = zoom * vec2((-0.5 - buffer) * ar, 1.0 + buffer);
    texCoord = vec2(0.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // bottom right
    offset = zoom * vec2((0.5 + buffer) * ar, 0.0 - buffer);
    texCoord = vec2(1.0f, 1.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();

    // top right
    offset = zoom * vec2((0.5 + buffer) * ar, 1.0 + buffer);
    texCoord = vec2(1.0f, 0.0f);
    gl_Position = position + vec4(offset, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}

void main() {
    build_entity(gl_in[0].gl_Position);
}