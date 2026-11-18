#include "Texture.h"
#include "Shared.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string texturePath, std::string uniformName)
{
    this->texturePath = texturePath;
    textureUniformName = uniformName;
    int currentlyBoundTexture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentlyBoundTexture);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else std::cout << "[ ERROR ] Failed to load texture" << std::endl;
    glBindTexture(GL_TEXTURE_2D, currentlyBoundTexture);
}

void Texture::bind(int location)
{
    textureUnit = GL_TEXTURE0 + location;
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind()
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    std::cout << "Deleting Texture id: " << texture << std::endl;
    glDeleteTextures(1, &texture);
}
