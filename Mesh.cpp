#include "Mesh.h"
#include "Shared.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<VertexLayout>& verticesLayout, std::vector<unsigned int>& indices):
vbo(vertices, verticesLayout), ebo(indices), vao(vbo, ebo)
{
    indicesNumber = indices.size();
    vao.bind();
    vbo.bind();
    ebo.bind();
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}
