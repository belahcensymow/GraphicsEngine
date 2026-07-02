#include <string>
#include "Texture.h"

class Shader
{
    private:
        std::string shaderPath;

        std::string vertexString = "";
        std::string fragmentString = "";
        const char* vertexShaderSource = "";
        const char* fragmentShaderSource = "";
    public:
        unsigned int vertexShader   = 0;
        unsigned int fragmentShader = 0;
        unsigned int program = 0;
        Shader(std::string shaderPath);
        void recompileShaders();
        void bind();
        void unbind();
        ~Shader();
        void setTexture(Texture& texture);
};
