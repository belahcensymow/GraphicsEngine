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
        void draw(Shader &shader);
        void addTexture(Texture& texture);
        void setTexture(Shader &shader, Texture &texture, int location);
        void removeTexture(Texture &texture);

        std::array<float, 3> Scale = {1,1,1};
        std::array<float, 3> Rotation = {0,0,0};
        std::array<float, 3> Position = {0,0,0};
        void applySRT(std::array<float, 16> SRTMatrix, std::string uniformName);
        void applySRT();
        void SRT(float scaleX, float scaleY, float scaleZ, float rotateX, float rotateY, float rotateZ, float translateX, float translateY, float translateZ, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void SRT(const std::array<float, 3>& scale, const std::array<float, 3>& rotation, const std::array<float, 3>& translation, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void scale(float x, float y, float z, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void rotate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = RELATIVE);
        void translate(float x, float y, float z, TRANSFORMATION_TYPE transformationType = RELATIVE);
};
