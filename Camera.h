#pragma once
#include "Shared.h"
#include "Mathematics.h"
#include <GLFW/glfw3.h>

class Shader;

class Camera
{
    public:
        float cameraSpeed = 1;
        std::array<float, 3> Position;
        std::array<float, 3> Rotation;
        std::array<float, 3> Scale;
        std::array<float, 16> View;
        Camera();
        void getInput(Shader &shader, GLFWwindow *window, float &deltaTime);
        std::array<float, 3> getPosition();
        std::array<float, 3> getDirection(std::array<float, 3> targetPosition);
        std::array<float, 3> getRight(std::array<float, 3> targetPosition);
        std::array<float, 3> getUp(std::array<float, 3> targetPosition);
        std::array<float, 3> lookAt(std::array<float, 3> targetPosition);
        void applyView(Shader &shader, std::string uniformName = "View");
        void applyView(Shader &shader);
        std::array<float, 3> getTargetPosition();
        std::array<float, 16> ViewMatrix();

        void goForward(float sensibility = 0.05f);
        void goBackward(float sensibility = 0.05f);
        void goRight(float sensibility = 0.05f);
        void goLeft(float sensibility = 0.05f);
        void lookUp(float sensibility = 1);
        void lookDown(float sensibility = 1);
        void lookRight(float sensibility = 2);
        void lookLeft(float sensibility = 2);

};
