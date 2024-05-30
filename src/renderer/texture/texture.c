#include "texture.h"
#include <assert.h>

Texture texture_create(const char* image_path)
{
    Texture texture;
    i32 width, height, nrChannels;
    unsigned char *data = stbi_load(image_path, &width, &height, &nrChannels, 0);
    assert(data != NULL);
    glCreateTextures(GL_TEXTURE_2D, 1, &texture.id);
    glTextureParameteri(texture.id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture.id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(texture.id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(texture.id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureStorage2D(texture.id, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(texture.id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateTextureMipmap(texture.id);
    stbi_image_free(data);
    return texture;
    /*
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    f32 col[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, col);
    i32 width, height, nrChannels;
    unsigned char *data = stbi_load(image_path, &width, &height, &nrChannels, 0); 
    assert(data != NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    */
}

void texture_bind(Texture texture, u32 binding)
{
    glBindTextureUnit(binding, texture.id);
}

void texture_destroy(Texture texture)
{
    glDeleteTextures(1, &texture.id);
}