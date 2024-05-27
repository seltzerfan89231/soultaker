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

in float projectile_rotation[];

void build_projectile(vec4 position) 
{
    depthValue = 0.5 + 0.5 * position.z;
    float drot = projectile_rotation[0] - rotation;
    drot = atan(tan(drot) / cos(pi / 2 + tilt)) + (cos(drot) > 0 ? 0 : pi);
    vec2 offset;
    offset = zoom * (1 / sqrt2) * vec2(ar * cos(drot - 3 * pi / 4), sin(drot - 3 * pi / 4));
    gl_Position = position + vec4(offset, 0.0 , 0.0);    // 1:bottom-left
    texCoord = vec2(0.0f, 0.25f);
    EmitVertex();
    offset = zoom * (1 / sqrt2) * vec2(ar * cos(drot - pi / 4), sin(drot - pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 2:bottom-right
    texCoord = vec2(0.25f, 0.25f);
    EmitVertex();
    offset = zoom * (1 / sqrt2) * vec2(ar * cos(drot + 3 * pi / 4), sin(drot + 3 * pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 3:top-left
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    offset = zoom * (1 / sqrt2) * vec2(ar * cos(drot + pi / 4), sin(drot + pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 4:top-right
    texCoord = vec2(0.25f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_projectile(gl_in[0].gl_Position);
}