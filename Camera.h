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
        void getInput(Shader &shader, GLFWwindow *window);
        std::array<float, 3> getPosition();
        std::array<float, 3> getDirection(std::array<float, 3> targetPosition);
        std::array<float, 3> getRight(std::array<float, 3> targetPosition);
        std::array<float, 3> getUp(std::array<float, 3> targetPosition);
        std::array<float, 3> getForward(std::array<float, 3> targetPosition);
        std::array<float, 3> lookAt(std::array<float, 3> targetPosition);





        void applyView(Shader &shader, std::string uniformName);
        void applyView(Shader &shader);
        void SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void SRT(std::array<float, 3> scale, std::array<float, 3> rotation, std::array<float, 3> translation, TRANSFORMATION_TYPE transformationType);
        void scale(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void rotate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);
        void translate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = ABSOLUTE);

        std::array<float, 3> getTargetPosition();
        std::array<float, 16> ViewMatrix();

        void goForward(float speed = 0.05f);
        void goBackward(float speed = 0.05f);
        void goRight(float speed = 0.05f);
        void goLeft(float speed = 0.05f);
        void lookUp(float speed = 0.05f);
        void lookDown(float speed = 0.05f);
        void lookRight(float speed = 0.05f);
        void lookLeft(float speed = 0.05f);

};
