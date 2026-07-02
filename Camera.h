#pragma once
#include "Shared.h"
#include "Mathematics.h"
#include <GLFW/glfw3.h>

class Shader;

class Camera
{
    public:
        float cameraSpeed = 0.05f;
        std::array<float, 3> Position;
        std::array<float, 3> Rotation;
        std::array<float, 3> Scale;
        std::array<float, 16> View;
        Camera();
        void updateView(Shader &shader);
        void getInput(Shader &shader, GLFWwindow *window);
        std::array<float, 3> getPosition();
        std::array<float, 3> getDirection(std::array<float, 3> targetPosition);
        std::array<float, 3> getRight(std::array<float, 3> targetPosition);
        std::array<float, 3> getUp(std::array<float, 3> targetPosition);
        std::array<float, 3> getForward(std::array<float, 3> targetPosition);
        std::array<float, 3> lookAt(std::array<float, 3> targetPosition);





        void applySRT(Shader &shader, std::array<float, 16> SRTMatrix, std::string uniformName);
        void applySRT(Shader &shader);
        void SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void SRT(std::array<float, 3> scale, std::array<float, 3> rotation, std::array<float, 3> translation, TRANSFORMATION_TYPE transformationType);
        void scale(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void rotate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void translate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);

};
