/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Model
*/

#include "Model.hpp"

EGE::Model::Model(const std::string &path)
{
    this->loadModel(path);
}

EGE::Model::~Model()
{
}

void EGE::Model::draw(Shader &shader)
{
    for (auto &mesh : this->_meshes) {
        mesh.draw(shader);
    }
}

void EGE::Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (scene == NULL || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw ModelError("ERROR\n\tASSIMP\n\t\t" + std::string(importer.GetErrorString()));
    }
    this->_directory = path.substr(0, path.find_last_of('/'));
    this->processNode(scene->mRootNode, scene);
}

void EGE::Model::processNode(aiNode *node, const aiScene *scene)
{
    // both loop could be parallelized
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->_meshes.push_back(this->processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        // std::thread(&Model::processNode, this, node->mChildren[i], scene).detach();
        this->processNode(node->mChildren[i], scene);
    }
}

EGE::Mesh EGE::Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        EGE::Maths::Vector3<double> position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vertex._position = position.toGlmVec3();

        EGE::Maths::Vector3<double> normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        vertex._normal = normal.toGlmVec3();

        if (mesh->mTextureCoords[0]) {
            EGE::Maths::Vector2<double> texCoords;
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
            vertex._texCoords = texCoords.toGlmVec2();
        } else
            vertex._texCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuses = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuses.begin(), diffuses.end());
        // std::vector<Texture> speculars = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        // textures.insert(textures.end(), speculars.begin(), speculars.end());
        // std::vector<Texture> normals = this->loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        // textures.insert(textures.end(), normals.begin(), normals.end());
        // std::vector<Texture> heights = this->loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        // textures.insert(textures.end(), heights.begin(), heights.end());
    }
    return Mesh(vertices, indices, textures);
}

std::vector<EGE::Texture> EGE::Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (auto &texture : this->_texturesLoaded) {
            if (texture.getPath() == str.C_Str()) {
                textures.push_back(texture);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture;
            texture.loadFromFile(this->_directory + "/" + str.C_Str());
            texture.setType(typeName);
            texture.setPath(str.C_Str());
            textures.push_back(texture);
            this->_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}