#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Mathematics.h"
#include <array>

class Object3D
{
    public:
        VertexBuffer vbo;
        ElementArray ebo;
        VertexArray vao;
        Shader& shader;
        // float scaleX = 1, scaleY = 1, scaleZ = 1, rotationX = 0, rotationY = 0, rotationZ = 0, positionX = 0, positionY = 0, positionZ = 0;
        std::array<float, 3> Scale = {1,1,1};
        std::array<float, 3> Rotation = {0,0,0};
        std::array<float, 3> Position = {0,0,0};
        unsigned int indicesNumber;
        Object3D(std::vector<Vertex> &vertices, std::vector<VertexLayout> &verticesLayout, std::vector<unsigned int> &indices, Shader& shader);
        void draw();
        void show();
        void hide();
        void setTexture(Texture &texture);
        void removeTexture(Texture &texture);
        void applySRT(std::array<float, 16> SRTMatrix, std::string uniformName);
        void applySRT();
        void SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void SRT(std::array<float, 3> scale, std::array<float, 3> rotation, std::array<float, 3> translation, TRANSFORMATION_TYPE transformationType);
        void scale(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void rotate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void translate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
};
