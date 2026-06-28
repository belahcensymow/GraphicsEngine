#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include <math.h>

class Object3D
{
    public:
        VertexBuffer vbo;
        ElementArray ebo;
        VertexArray vao;
        Shader shader;
        float scaleX = 1, scaleY = 1, scaleZ = 1, rotationX = 0, rotationY = 0, rotationZ = 0, positionX = 0, positionY = 0, positionZ = 0;
        Object3D(std::vector<Vertex> &vertices, std::vector<VertexLayout> &verticesLayout, std::vector<unsigned int> &indices, std::string shaderPath);
        void show();
        void hide();
        void setTexture(Texture texture);
        void removeTexture(Texture texture);
        std::vector<float> SRT(float scale[3], float rotation[3], float translation[3]);
        void applySRT(std::vector<float> SRTMatrix, std::string uniformName);
        void applySRT();
        void SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ);
        void scale(float x, float y, float z);
        void rotate(float x, float y, float z);
        void translate(float x, float y, float z);
};
