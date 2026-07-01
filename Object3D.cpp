#include "Object3D.h"
#include "Texture.h"
#include "Mathematics.h"
#include <vector>

Object3D::Object3D(std::vector<Vertex> &vertices, std::vector<VertexLayout> &verticesLayout, std::vector<unsigned int> &indices, std::string shaderPath):
vbo(vertices, verticesLayout), ebo(indices), vao(vbo, ebo), shader(shaderPath)
{
    indicesNumber = indices.size();
}

void Object3D::draw()
{
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
void Object3D::setTexture(Texture texture)
{
    shader.bind();
    shader.setTexture(texture);
    texture.bind();
    shader.unbind();
}
void Object3D::removeTexture(Texture texture)
{
    texture.unbind();
}
void Object3D::applySRT(std::vector<float> SRTMatrix, std::string uniformName)
{
    int location = glGetUniformLocation(shader.program, uniformName.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, SRTMatrix.data());
}
void Object3D::applySRT()
{
    shader.bind();
    std::vector<float> SRTMatrix(16);
    SRTMatrix = ::SRT({scaleX, scaleY, scaleZ}, {rotationX, rotationY, rotationZ}, {positionX, positionY, positionZ});
    int location = glGetUniformLocation(shader.program, "Model");
    glUniformMatrix4fv(location, 1, GL_FALSE, SRTMatrix.data());
    shader.unbind();
}
void Object3D::SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaleZ = scaleZ;
    this->rotationX = rotateX;
    this->rotationY = rotateY;
    this->rotationZ = rotateZ;
    this->positionX = translateX;
    this->positionY = translateY;
    this->positionZ = translateZ;
    applySRT();
}
void Object3D::scale(float x, float y, float z)
{
    scaleX = x;
    scaleY = y;
    scaleZ = z;
    applySRT();
}
void Object3D::rotate(float x, float y, float z)
{
    rotationX = x;
    rotationY = y;
    rotationZ = z;
    applySRT();
}
void Object3D::translate(float x, float y, float z)
{
    positionX = x;
    positionY = y;
    positionZ = z;
    applySRT();
}
