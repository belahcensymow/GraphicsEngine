#ifndef SHARED_H
#define SHARED_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <array>

struct Vertex
{
    float coordinates[3];
    float color[3];
    float normal[3];
    float texture[2];
};

struct VertexLayout
{
    unsigned int count;
    int type;
    int location;
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
#endif
