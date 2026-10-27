#include "Shared.h"
#include "Shader.h"
#include "VertexArray.h"
#include <vector>

class Mesh
{
    public:
        VertexBuffer vbo;
        ElementArray ebo;
        VertexArray  vao;
        unsigned int indicesNumber;
        Mesh(std::vector<Vertex>& vertices, std::vector<VertexLayout>& verticesLayout, std::vector<unsigned int>& indices);
        // void Draw(Shader &shader);
};
