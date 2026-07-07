#include "Object3D.h"
#include "Camera.h"
#include "Texture.h"
#include "Mathematics.h"
#include <array>
#include <vector>

Object3D::Object3D(std::vector<Vertex> &vertices, std::vector<VertexLayout> &verticesLayout, std::vector<unsigned int> &indices, Shader& shader):
vbo(vertices, verticesLayout), ebo(indices), vao(vbo, ebo), shader(shader)
{
    indicesNumber = indices.size();
}

void Object3D::draw()
{
    applySRT();
    show();
    glDrawElements(GL_TRIANGLES, indicesNumber, GL_UNSIGNED_INT, NULL);
}
void Object3D::show()
{
    vbo.bind();
    ebo.bind();
    vao.bind();
    shader.bind();

}
void Object3D::hide()
{
    vbo.unbind();
    ebo.unbind();
    vao.unbind();
    shader.unbind();
}
void Object3D::setTexture(Texture &texture)
{
    shader.bind();
    shader.setTexture(texture);
    texture.bind();
    shader.unbind();
}
void Object3D::removeTexture(Texture &texture)
{
    texture.unbind();
}
void Object3D::applySRT(std::array<float, 16> SRTMatrix, std::string uniformName)
{
    shader.bind();
    int location = glGetUniformLocation(shader.program, uniformName.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, SRTMatrix.data());
    shader.unbind();
}
void Object3D::applySRT()
{
    shader.bind();
    std::array<float, 16> SRTMatrix;
    SRTMatrix = ::SRT(Scale, Rotation, Position);
    int location = glGetUniformLocation(shader.program, "Model");
    glUniformMatrix4fv(location, 1, GL_FALSE, SRTMatrix.data());
    shader.unbind();
}
void Object3D::SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ, TRANSFORMATION_TYPE transformationType)
{
    if(transformationType == ABSOLUTE)
    {
        Scale    = {scaleX,scaleY,scaleZ};
        Rotation = {rotateX,rotateY,rotateZ};
        Position = {translateX,translateY,translateZ};
    }
    else
    {
        Scale    *= {scaleX,scaleY,scaleZ};
        Rotation += {rotateX,rotateY,rotateZ};
        Position += {translateX,translateY,translateZ};
    }
    applySRT();
}
void Object3D::SRT(std::array<float, 3> scale, std::array<float, 3> rotation, std::array<float, 3> translation, TRANSFORMATION_TYPE transformationType)
{
    SRT(scale[0], scale[1], scale[2], rotation[0], rotation[1], rotation[2], translation[0], translation[1], translation[2], transformationType);
}
void Object3D::scale(float x, float y, float z, TRANSFORMATION_TYPE transformationType)
{
    if(transformationType == ABSOLUTE) Scale = {x,y,z};
    else Scale += {x,y,z};
    applySRT();
}
void Object3D::rotate(float x, float y, float z, TRANSFORMATION_TYPE transformationType)
{
    if(transformationType == ABSOLUTE) Rotation = {x,y,z};
    else Rotation += {x,y,z};
    applySRT();
}
void Object3D::translate(float x, float y, float z, TRANSFORMATION_TYPE transformationType)
{
    if(transformationType == ABSOLUTE) Position = {x,y,z};
    else Position += {x,y,z};
    applySRT();
}
