#include "Texture.h"
#include "Shared.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string texturePath, std::string uniformName, int location = -1)
{
    textureUniformName = uniformName;
    if(location == -1)
    {
        textureUnit = GL_TEXTURE0;
        while(textureUnitIsTaken(textureUnit))
        {
            std::cout << "This shouldn't be hit yet!" << std::endl;
            textureUnit ++;
        }
    }
    else
    {
        textureUnit = GL_TEXTURE0 + location;
    }
    glGenTextures(1, &texture);
    bind();
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    if(data)
    {
        stbi_set_flip_vertically_on_load(true);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else std::cout << "[ ERROR ] Failed to load texture" << std::endl;
    unbind();
}

void Texture::bind()
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind()
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool textureUnitIsTaken(int location)
{
    int previousActiveTexture;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &previousActiveTexture);
    glActiveTexture(location);
    int state;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &state);
    glActiveTexture(previousActiveTexture);
    if(state != 0)
    {
        std::cout << "[ WARNING ] Texture unit is already in use, you are overriding an existing texture '"
                  << location - GL_TEXTURE0 << "'!" << std::endl;
        return true;
    }
    return false;
}
