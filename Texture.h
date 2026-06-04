#include "Shared.h"

class Texture
{
    public:
        unsigned int texture;
        Texture(std::string texturePath);
        void bind();
        void unbind();
};
