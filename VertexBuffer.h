#include "Shared.h"

class VertexBuffer
{
    private:
        std::vector<Vertex>& vertices;
        std::vector<VertexLayout>& verticesLayout;
    public:
        unsigned int vbo;
        VertexBuffer(std::vector<Vertex>& vertices, std::vector<VertexLayout>& verticesLayout);
        void bind();
        void unbind();
};
