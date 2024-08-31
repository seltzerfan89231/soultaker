#version 460 core

#extension GL_ARB_bindless_texture : require

layout (binding = 0, std430) readonly buffer ssbo
{
    uvec2 tex[];
};

in VertexData
{
    vec2 texCoord;
    flat int texID;
    flat int shadows;
};

void main()
{
    if (texCoord.x >= 0 && texCoord.x < 1 && texCoord.y >= 0 && texCoord.y < 1)
        discard;
    if (shadows == 0)
        discard;
    int bm = shadows;
    int DOWN = bm - 2 * (bm / 2);
    bm /= 2;
    int RIGHT = bm - 2 * (bm / 2);
    bm /= 2;
    int UP = bm - 2 * (bm / 2);
    bm /= 2;
    int LEFT = bm - 2 * (bm / 2);
    bm /= 2;

    // sides
    if (LEFT == 0 && texCoord.x < 0 && texCoord.y >= 0 && texCoord.y < 1)
        discard;
    if (RIGHT == 0 && texCoord.x > 1 && texCoord.y >= 0 && texCoord.y < 1)
        discard;
    if (UP == 0 && texCoord.y > 0 && texCoord.x >= 0 && texCoord.x < 1)
        discard;
    if (DOWN == 0 && texCoord.y < 0 && texCoord.x >= 0 && texCoord.x < 1)
        discard;
    
    // corners
    if ((LEFT == 0 || UP == 0) && texCoord.x < 0 && texCoord.y > 1)
        discard;
    if ((LEFT == 0 || DOWN == 0) && texCoord.x < 0 && texCoord.y < 0)
        discard;
    if ((RIGHT == 0 || UP == 0) && texCoord.x > 1 && texCoord.y > 1)
        discard;
    if ((RIGHT == 0 || DOWN == 0) && texCoord.x > 1 && texCoord.y < 0)
        discard;

    float dx = (texCoord.x < 0) ? - texCoord.x : texCoord.x - 1;
    float dy = (texCoord.y < 0) ? - texCoord.y : texCoord.y - 1;

    gl_FragColor = texture(sampler2D(tex[texID]), texCoord);
    gl_FragColor.a = 0.375;
}