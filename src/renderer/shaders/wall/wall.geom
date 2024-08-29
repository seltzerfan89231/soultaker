#version 460 core

#extension GL_ARB_bindless_texture : require

layout (points) in;
layout (triangle_strip, max_vertices = 20) out;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 proj;
};

in VertexData
{
    float x, z, w, h, l;
    int top_texID;
    int side1_texID;
    int side2_texID;
} inData[];

out VertexData
{
    vec2 texCoord;
    flat int texID;
    flat float depthValue;
};

void build_top(vec4 position)
{   
    
}

void build_sides(vec4 position)
{
    
}

void main() 
{   
    float x, z, w, h, l;
    x = inData[0].x, z = inData[0].z;
    w = inData[0].w, h = inData[0].h, l = inData[0].l;
    vec4 position = vec4(x, 0, z, 1.0f);
    vec4 center = proj * view * (position + vec4(w / 2, 0, l / 2, 0.0));
    depthValue = 0.5 + 0.5 * center.z / center.w;
    
    // ---- Top ----
    texID = inData[0].top_texID;
    gl_Position = proj * view * (position + vec4(0, h, 0, 0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, h, 0, 0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0, h, l, 0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, h, l, 0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    EndPrimitive();

    // --- Sides ---
    texID = inData[0].side1_texID;
    gl_Position = proj * view * (position + vec4(w, 0, 0, 0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, h, 0, 0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(0, 0, 0, 0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0, h, 0, 0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();

    texID = inData[0].side2_texID;
    gl_Position = proj * view * (position + vec4(0, 0, 0, 0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0, h, 0, 0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(0, 0, l, 0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0, h, l, 0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();

    texID = inData[0].side2_texID;
    gl_Position = proj * view * (position + vec4(w, 0, l, 0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, h, l, 0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();   
    gl_Position = proj * view * (position + vec4(w, 0, 0, 0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, h, 0, 0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();

    texID = inData[0].side1_texID;
    gl_Position = proj * view * (position + vec4(0, 0, l, 0));
    texCoord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(0, h, l, 0));
    texCoord = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, 0, l, 0));
    texCoord = vec2(0.0f, 1.0f);
    EmitVertex();
    gl_Position = proj * view * (position + vec4(w, h, l, 0.0));
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    EndPrimitive();
}