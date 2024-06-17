#version 460 core

layout (binding = 1, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

in vec2 texCoord;
in flat float texID;
in flat float opacity;

void main()
{
    vec4 col = texture(sampler2D(tex[int(round(texID))]), texCoord) * vec4(1.0f, 0.0f, 0.0f, 1.0f);
    if (col.a < 0.1)
        discard;
    gl_FragColor = col;
    gl_FragColor.a *= opacity;
}