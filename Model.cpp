#include "Model.h"
#include "Mesh.h"
#include "Shared.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <vector>

Model::Model(Mesh& mesh) { meshes.push_back(mesh); }
Model::Model(std::string path) { loadModel(path); }

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ASSIMP ERROR: " << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
        meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
    for(unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position = {
             mesh->mVertices[i].x,
             mesh->mVertices[i].y,
             mesh->mVertices[i].z},
         vertex.Normal = {
             mesh->mNormals[i].x,
             mesh->mNormals[i].y,
             mesh->mNormals[i].z
         };
         if(mesh->HasTextureCoords(0))
             vertex.TexCoords = {
                 mesh->mTextureCoords[0][i].x,
                 mesh->mTextureCoords[0][i].y,
             };
         else vertex.TexCoords = {0.0f,0.0f};
        vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        for(unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            indices.push_back(mesh->mFaces[i].mIndices[j]);
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        loadMaterialTextures(material, aiTextureType_DIFFUSE);
        loadMaterialTextures(material, aiTextureType_SPECULAR);
    }
    std::vector<VertexLayout> verticesLayout = {
        {3, GL_FLOAT},
        {3, GL_FLOAT},
        {2, GL_FLOAT}
    };
    return Mesh(vertices, verticesLayout, indices);
}

void Model::loadMaterialTextures(aiMaterial *material, aiTextureType type)
{
    // std::vector<Texture> textures;
    for(unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString filename;
        material->GetTexture(type, i, &filename);
        std::string texturePath = directory + "/" + filename.C_Str();
        bool skip = false;
        for (Texture& texture: textures_loaded)
            if (texture.texturePath == texturePath) { skip = true; break; }
        if(!skip)
        {
            std::string uniformName = std::string("material.") + aiTextureTypeToString(type);
            std::cout << "Loading texture: " << texturePath << " | Uniform name: " << uniformName << std::endl;
            textures_loaded.emplace_back(texturePath, uniformName);
        }
    }
}

void Model::Draw(Shader &shader)
{
    shader.bind();
    unsigned int i = 0;
    for (Texture& texture: textures_loaded)
    {
        if(texture.textureUniformName == "material.Diffuse")  setTexture(shader, texture, 2);
        if(texture.textureUniformName == "material.Specular") setTexture(shader, texture, 3);
    }
    for (Mesh& mesh : meshes)
    {
        mesh.vao.bind();
        shader.bind();
        glDrawElements(GL_TRIANGLES, mesh.indicesNumber, GL_UNSIGNED_INT, NULL);
        shader.unbind();
    }
}

void Model::setTexture(Shader &shader, Texture &texture, int location)
{
    shader.bind();
    shader.setTexture(texture);
    texture.bind(location);
    shader.unbind();
}
void Model::removeTexture(Texture &texture)
{
    texture.unbind();
}
