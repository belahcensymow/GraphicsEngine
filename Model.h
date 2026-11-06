#include "Mesh.h"
#include "Shared.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

class Model
{
    public:
        std::vector<Mesh> meshes;
        std::string directory;
        Model(std::string path);
        Model(Mesh& mesh);
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        void processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
        void Draw(Shader &shader)
        {
            for (const Mesh& mesh : meshes)
            {
                // Draw(mesh);
                // mesh.Draw(shader);
            }
        }
};
