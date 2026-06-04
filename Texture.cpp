#include "Texture.h"
#include "Shared.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string texturePath)
{
    glGenTextures(1, &texture);
    bind();
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, STBI_rgb);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "[ ERROR ] Failed to load texture" << std::endl;
    }
    unbind();
}
void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
