/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Model
*/

#include "Model.hpp"
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

std::map<std::string, EGE::Model *> EGE::Model::_modelsLoaded = {};

EGE::Model::Model(const std::string &path, const EGE::Maths::Vector3<float> &position, const EGE::Maths::Vector3<float> &scale, bool flipTexture)
{
    if (Model::_modelsLoaded.find(path) != Model::_modelsLoaded.end()) {
        *this = *Model::_modelsLoaded[path];
        this->_position = position;
        this->_scale = scale;
        return;
    }
    this->_position = position;
    this->_scale = scale;
    this->loadModel(path, flipTexture);
    Model::_modelsLoaded[path] = this;
}

EGE::Model::~Model()
{
}

void EGE::Model::draw(Shader &shader)
{
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, this->_position.toGlmVec3());
    modelMat = glm::scale(modelMat, this->_scale.toGlmVec3());
    shader.setMat("model", EGE::Maths::Matrix<4, 4, float>(modelMat));
    for (auto &mesh : this->_meshes) {
        mesh.draw(shader);
    }
}

void EGE::Model::loadModel(const std::string& path, bool flipTexture)
{
    Assimp::Importer importer;
    importer.SetIOHandler(gMemoryIOSystem);
    const aiScene *scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Loading model %s\n", path.c_str());
    if (scene == NULL || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw ModelError("ERROR\n\tASSIMP\n\t\t" + std::string(importer.GetErrorString()));
    }
    this->_directory = path.substr(0, path.find_last_of('/'));
    this->processNode(scene->mRootNode, scene, flipTexture);
}

void EGE::Model::processNode(aiNode *node, const aiScene *scene, bool flipTexture)
{
    // both loop could be parallelized
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->_meshes.push_back(this->processMesh(mesh, scene, flipTexture));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        // std::thread(&Model::processNode, this, node->mChildren[i], scene).detach();
        this->processNode(node->mChildren[i], scene, flipTexture);
    }
}

EGE::Mesh EGE::Model::processMesh(aiMesh *mesh, const aiScene *scene, bool flipTexture)
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
        std::vector<Texture> diffuses = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", flipTexture);
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

std::vector<EGE::Texture> EGE::Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName, bool flipTexture)
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
            AAssetManager *mgr = gMemoryIOSystem->getAssetManager();
            std::string path = this->_directory + str.C_Str();
            AAsset *file = AAssetManager_open(mgr, path.c_str(), AASSET_MODE_UNKNOWN);
            off_t fileLength = AAsset_getLength(file);
            unsigned char *buffer = (unsigned char *)calloc(fileLength + 1, sizeof(unsigned char));
            AAsset_read(file, buffer, fileLength);
            texture.loadFromFile(buffer, fileLength, flipTexture);
            texture.setType(typeName);
            texture.setPath(str.C_Str());
            textures.push_back(texture);
            this->_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

void EGE::Model::setPosition(const EGE::Maths::Vector3<float>& position)
{
    this->_position = position;
}

EGE::Maths::Vector3<float> EGE::Model::getPosition() const
{
    return this->_position;
}

void EGE::Model::setScale(const EGE::Maths::Vector3<float>& scale)
{
    this->_scale = scale;
}

EGE::Maths::Vector3<float> EGE::Model::getScale() const
{
    return this->_scale;
}
