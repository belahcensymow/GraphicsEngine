#ifndef SHARED_H
#define SHARED_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

struct Vertex
{
    float coordinates[3];
    float color[3];
};

struct VertexLayout
{
    unsigned int count;
    int type;
    int location;
};
#endif
