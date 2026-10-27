#ifndef SHARED_H
#define SHARED_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <array>

struct Vertex
{
    std::array<float, 3> Position;
    std::array<float, 3> Normal;
    std::array<float, 2> TexCoords;
};

struct VertexLayout
{
    unsigned int count;
    int type;
};

enum ShaderType
{
    VERTEX_SHADER = 0,
    FRAGMENT_SHADER = 1,
    UNDEFINED_SHADER = 2,
};

enum TRANSFORMATION_TYPE
{
    RELATIVE,
    ABSOLUTE
};

enum LightType
{
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT,
};

struct ProjectionParameters
{
    float FOV = 45;
    float aspectRatio = 4.0f/3.0f;
    float near = 0.1f;
    float far = 100.0f;
};
#endif
