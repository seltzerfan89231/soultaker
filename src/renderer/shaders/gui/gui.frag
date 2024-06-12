#version 460 core

layout (binding = 1, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

in vec2 texCoord;
in flat int texID;
in flat float opacity;

void main()
{
    vec4 col = texture(sampler2D(tex[texID]), texCoord);
    if (col.a < 0.1)
        discard;
    gl_FragColor = col;
    gl_FragColor.a *= opacity;
}