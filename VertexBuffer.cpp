#include "VertexBuffer.h"
#include "Shared.h"
#include <vector>

unsigned long glSize(unsigned int type)
{
    switch (type) {
        case GL_FLOAT:          return sizeof(float);
        case GL_INT:            return sizeof(int);
        case GL_UNSIGNED_INT:   return sizeof(unsigned int);
        default: {
            std::cout << "[ ERROR ] Type not yet implemented!!" << std::endl;
            return 0;
        };
    }
}

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices, std::vector<VertexLayout>& verticesLayout) : vertices(vertices), verticesLayout(verticesLayout)
{
    glGenBuffers(1, &vbo);
}
void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    int stride = 0;
    for (VertexLayout layout : verticesLayout) {
        stride += layout.count * glSize(layout.type);
    }
    unsigned long offset = 0;
    for (VertexLayout layout : verticesLayout) {
        glVertexAttribPointer(layout.location, layout.count, layout.type, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(layout.location);
        offset += layout.count * glSize(layout.type);
    }
}
void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
