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
void Camera::updateView(Shader &shader)
{
    std::array<float, 3> translationCorrection = {1.0f, -1.0f, 1.0f};
    std::array<float, 3> rotationCorrection = {-1.0f, 1.0f, -1.0f};
    View = ::SRT(Scale * -1.0f, Rotation * rotationCorrection, Position * translationCorrection);
    applySRT(shader);
}
void Camera::getInput(Shader &shader, GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) translate(0,0,cameraSpeed,RELATIVE);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) translate(0,0,-cameraSpeed,RELATIVE);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) translate(cameraSpeed,0,0,RELATIVE);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) translate(-cameraSpeed,0,0, RELATIVE);
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)   rotate( cameraSpeed*5,0,0,RELATIVE);
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rotate(-cameraSpeed*5,0,0,RELATIVE);
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)rotate(0, cameraSpeed*5,0,RELATIVE);
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotate(0,-cameraSpeed*5,0,RELATIVE);
    updateView(shader);
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

void Camera::applySRT(Shader &shader, std::array<float, 16> SRTMatrix, std::string uniformName)
{
    shader.bind();
    int location = glGetUniformLocation(shader.program, uniformName.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, SRTMatrix.data());
    shader.unbind();
}
void Camera::applySRT(Shader &shader) { applySRT(shader ,View, "View");}

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
