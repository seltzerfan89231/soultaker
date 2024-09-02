#version 460 core

in VertexData
{
    float height;
    vec2 texCoord;
};

uniform sampler2D screenTexture;

void main()
{
    float d = distance(texCoord, vec2(0.5, 0.5));
    float hsqrd = height * height;
    if (d > 0.5 - hsqrd)
        discard;
    vec4 color = vec4(0.2f, 0.2f, 0.2f, (0.5 - hsqrd - d));
    vec2 tex_coord = vec2(gl_FragCoord.x, gl_FragCoord.y);
    gl_FragColor = texture(screenTexture, tex_coord) * color;
}