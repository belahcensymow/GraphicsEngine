#include "Mesh.h"
#include "Shared.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <deque>
#include <vector>

class Model
{
    public:
        std::vector<Mesh> meshes;
        std::deque<Texture> textures_loaded;
        std::string directory;
        Model(std::string path);
        Model(Mesh& mesh);
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        void loadMaterialTextures(aiMaterial *material, aiTextureType type);
        void Draw(Shader &shader);
        void setTexture(Shader &shader, Texture &texture, int location);
        void removeTexture(Texture &texture);

};
