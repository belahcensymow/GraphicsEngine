#include "ElementArray.h"
#include <vector>

ElementArray::ElementArray(std::vector<unsigned int>& indices)
{
    glGenBuffers(1, &ebo);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    unbind();
}

void ElementArray::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void ElementArray::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
