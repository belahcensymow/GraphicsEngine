#pragma once
#include "Shared.h"
#include "Mathematics.h"
#include <array>
#include "Mesh.h"

class Object3D
{
    public:
        Mesh* mesh = nullptr;
        Shader* shader = nullptr;
        std::array<float, 3> Scale = {1,1,1};
        std::array<float, 3> Rotation = {0,0,0};
        std::array<float, 3> Position = {0,0,0};
        ProjectionParameters projectionParameters = {};
        unsigned int indicesNumber;
        Object3D();
        Object3D(Mesh& mesh, Shader& shader);
        void draw();
        void show();
        void hide();
        void setTexture(Texture &texture);
        void removeTexture(Texture &texture);
        void applySRT(std::array<float, 16> SRTMatrix, std::string uniformName);
        void applySRT();
        void SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void SRT(const std::array<float, 3>& scale, const std::array<float, 3>& rotation, const std::array<float, 3>& translation, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void scale(float x, float y, float z, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void rotate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void translate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void setProjection(const ProjectionParameters& p);
        void setProjection();
        void defaultDataInit();
        void setShader(Shader& shader);
};
