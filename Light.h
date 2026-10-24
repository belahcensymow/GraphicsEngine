#pragma once
#include "Shared.h"
#include "Object3D.h"
#include <optional>

class Light
{
    private:
        std::optional<Object3D> mesh;
    public:
        // Light(LightType lightType);
        Light(LightType lightType, Object3D &lightObject);
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<VertexLayout> verticesLayout;
        Shader *shader;
        Object3D* lightObject;
        LightType lightType;

    private:
        void initializationHelper(LightType lightType);
};
