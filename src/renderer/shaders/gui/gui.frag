#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 1, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

uniform sampler2D minimapTexture;

in vec2 texCoord;
in flat int texID;
in flat vec4 color;

void main()
{
    vec4 col;
    switch (texID) {
        // minimap
        case 2:
            col = texture(minimapTexture, texCoord);
            break;
        default:
            col = texture(sampler2D(tex[texID]), texCoord);
            break;
    }
    if (col.a < 0.1)
        discard;
    gl_FragColor = col * color;
}