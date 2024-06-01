#version 460 core

in float healthRatio;
in vec2 texCoord;

void main()
{
    float border_thickness = 0.05;
    if (texCoord.y < border_thickness || texCoord.y > 1.0f - border_thickness)
        gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else if (texCoord.x < border_thickness * 3 / 20 || texCoord.x > 1.0f - border_thickness * 3 / 20)
        gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else if (texCoord.x < healthRatio)
        gl_FragColor = vec4(0.3f, 0.9f, 0.3f, 1.0f);
    else
        gl_FragColor = vec4(0.9f, 0.3f, 0.3f, 1.0f);
}