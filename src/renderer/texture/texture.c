#include "texture.h"
#include <assert.h>
#include <stdio.h>

Texture texture_create(const char* image_path, GLenum filter_param)
{
    Texture texture;
    i32 width, height, nrChannels;
    GLenum format1, format2;
    unsigned char *data = stbi_load(image_path, &width, &height, &nrChannels, 0);
    f32 col[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    assert(data != NULL);
    glCreateTextures(GL_TEXTURE_2D, 1, &texture.id);
    glTextureParameteri(texture.id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texture.id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texture.id, GL_TEXTURE_MIN_FILTER, filter_param);
    glTextureParameteri(texture.id, GL_TEXTURE_MAG_FILTER, filter_param);
    glTextureParameterfv(texture.id, GL_TEXTURE_BORDER_COLOR, col);

    if (nrChannels == 3)
        format1 = GL_RGB8, format2 = GL_RGB;
    else if (nrChannels == 4)
        format1 = GL_RGBA8, format2 = GL_RGBA;
    else
        printf("Unrecognized number of channels in texture %s\n", image_path);

    glTextureStorage2D(texture.id, 1, format1, width, height);
    glTextureSubImage2D(texture.id, 0, 0, 0, width, height, format2, GL_UNSIGNED_BYTE, data);
    texture.handle = glGetTextureHandleARB(texture.id);
    glMakeTextureHandleResidentARB(texture.handle);
    stbi_image_free(data);
    return texture;
}

void texture_destroy(Texture texture)
{
    glMakeTextureHandleNonResidentARB(texture.handle);
    glDeleteTextures(1, &texture.id);
}