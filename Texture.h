#pragma once
#include "Shared.h"

class Texture
{
    public:
        unsigned int texture;
        int textureUnit;
        std::string textureUniformName;
        std::string texturePath;
        Texture(std::string texturePath, std::string uniformName);
        ~Texture();
        void bind(int location);
        void unbind();
};
