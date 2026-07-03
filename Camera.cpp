#include "Camera.h"
#include "Mathematics.h"
#include "Shader.h"
#include "Shared.h"
#include <GLFW/glfw3.h>
#include <array>
#include <cmath>

Camera::Camera()
{
    Position = {0,0,0};
    Rotation = {0,0,0};
    Scale = {1,1,1};
    SRT(Scale, Rotation, Position, ABSOLUTE);

}
void Camera::getInput(Shader &shader, GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) goForward();
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) goBackward();
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) goLeft();
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) goRight();
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)    lookUp(2.0f);
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)  lookDown(2.0f);
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) lookRight(5.0f);
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)  lookLeft(5.0f);
    applyView(shader);
}

std::array<float, 3>Camera::getPosition() { return Position; }
std::array<float, 3> Camera::getDirection(std::array<float, 3> targetPosition) { return Normalize(Position - targetPosition); }
std::array<float, 3> Camera::getRight(std::array<float, 3> targetPosition) { return Normalize(crossProduct3({0, 1, 0}, getDirection(targetPosition))); }
std::array<float, 3> Camera::getUp(std::array<float, 3> targetPosition) { return crossProduct3(getDirection(targetPosition), getRight(targetPosition)); }
std::array<float, 3> Camera::getForward(std::array<float, 3> targetPosition) { return crossProduct3(getRight(targetPosition), getUp(targetPosition)); }
std::array<float, 3> Camera::lookAt(std::array<float, 3> targetPosition)
{
    std::array<float, 3> F = getDirection(targetPosition);
    return  { std::asin(F[1]), std::atan2(F[2],F[0]), 0.0f };
}

void Camera::applyView(Shader &shader, std::string uniformName)
{
    shader.bind();
    View = ViewMatrix();
    int location = glGetUniformLocation(shader.program, uniformName.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, View.data());
    shader.unbind();
}
void Camera::applyView(Shader &shader) { applyView(shader, "View");}

void Camera::SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ, TRANSFORMATION_TYPE transformationType)
{
    std::array<float, 3> scale = {scaleX, scaleY, scaleZ};
    std::array<float, 3> rotation = {rotateX, rotateY,rotateZ};
    std::array<float, 3> position = {translateX, translateY, translateZ};
    if(transformationType == ABSOLUTE)
    {
        Scale = {scaleX, scaleY, scaleZ};
        Rotation = {rotateX, rotateY,rotateZ};
        Position = {translateX, translateY, translateZ};
    }
    else
    {
        Scale *= scale;
        Rotation += rotation;
        Position += position;
    }
}
    void Camera::SRT(std::array<float, 3> scale, std::array<float, 3> rotation, std::array<float, 3> translation, TRANSFORMATION_TYPE transformationType)
{
    SRT(scale[0], scale[1], scale[2], rotation[0], rotation[1], rotation[2], translation[0], translation[1], translation[2], transformationType);
}
void Camera::scale(float x, float y, float z, TRANSFORMATION_TYPE transformationType)
{
    std::array<float, 3> scale = {x,y,z};
    if(transformationType == ABSOLUTE) Scale = scale;
    else Scale *= scale;
}
void Camera::rotate(float x, float y, float z, TRANSFORMATION_TYPE transformationType)
{
    std::array<float, 3> rotation = {x,y,z};
    if(transformationType == ABSOLUTE) Rotation = rotation;
    else Rotation += rotation;
}
void Camera::translate(float x, float y, float z, TRANSFORMATION_TYPE transformationType)
{
    std::array<float, 3> position = {x,y,z};
    if(transformationType == ABSOLUTE) Position = position;
    else Position += position;
}

std::array<float, 3> Camera::getTargetPosition()
{
    float radPitch = Rotation[0] * 3.14159265f / 180.0f;
    float radYaw   = Rotation[1] * 3.14159265f / 180.0f;
    return Position + Normalize({
        std::cos(radYaw) * std::cos(radPitch),
        std::sin(radPitch),
        std::sin(radYaw) * std::cos(radPitch)
    });
}
std::array<float, 16> Camera::ViewMatrix()
{
    std::array<float, 3> targetPosition = getTargetPosition();
    std::array<float, 3> D = getDirection(targetPosition);
    std::array<float, 3> R = getRight(targetPosition);
    std::array<float, 3> U = getUp(targetPosition);
    float sx = (Scale[0] != 0.0f) ? (1.0f / Scale[0]) : 1.0f;
    float sy = (Scale[1] != 0.0f) ? (1.0f / Scale[1]) : 1.0f;
    float sz = (Scale[2] != 0.0f) ? (1.0f / Scale[2]) : 1.0f;
    R *= sx; U *= sy; D *= sz;
    float transX = -dotProduct3(R, Position);
    float transY = -dotProduct3(U, Position);
    float transZ = -dotProduct3(D, Position);
    return {
        R[0],   U[0],   D[0],   0.0f,
        R[1],   U[1],   D[1],   0.0f,
        R[2],   U[2],   D[2],   0.0f,
        transX, transY, transZ, 1.0f
    };
}


void Camera::goForward(float speed)
{
    std::array<float, 3> M = getForward(getTargetPosition()) * speed;
    Position -= M;
}
void Camera::goBackward(float speed)
{
    std::array<float, 3> M = getForward(getTargetPosition()) * speed;
    Position += M;
}
void Camera::goRight(float speed)
{
    std::array<float, 3> M = getRight(getTargetPosition()) * speed;
    Position += M;
}
void Camera::goLeft(float speed)
{
    std::array<float, 3> M = getRight(getTargetPosition()) * speed;
    Position -= M;
}
void Camera::lookUp(float speed) { Rotation[0] += speed; }
void Camera::lookDown(float speed) { Rotation[0] -= speed; }
void Camera::lookRight(float speed) { Rotation[1] += speed; }
void Camera::lookLeft(float speed) { Rotation[1] -= speed; }
