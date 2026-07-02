#pragma once
#include "Shared.h"

class Texture
{
    public:
        unsigned int texture;
        int textureUnit;
        std::string textureUniformName;
        Texture(std::string texturePath, std::string uniformName, int location = -1);
        void bind();
        void unbind();
};
        bool textureUnitIsTaken(int location);
