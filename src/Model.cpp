/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Model
*/

#include "Model.hpp"

std::map<std::string, EGE::Model *> EGE::Model::_modelsLoaded = {};

EGE::Model::Model(const std::string &path, const EGE::Maths::Vector3<float> &position, const EGE::Maths::Vector3<float> &rotation, const EGE::Maths::Vector3<float> &scale, bool flipTexture, bool forceReload)
{
    if (!forceReload && Model::_modelsLoaded.find(path) != Model::_modelsLoaded.end()) {
        *this = *Model::_modelsLoaded[path];
        this->_position = position;
        this->_rotation = rotation;
        this->_scale = scale;
        this->_shear = EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f);
        this->_originalModelMatrix = EGE::Maths::Matrix<4, 4, float>({
            {rotation.x, scale.x, 0.0f, position.x},
            {rotation.y, scale.y, 0.0f, position.y},
            {rotation.z, scale.z, 0.0f, position.z},
            {0.0f, 0.0f, 0.0f, 1.0f}
        });
        return;
    }
    this->_position = position;
    this->_rotation = rotation;
    this->_shear = EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f);
    this->_scale = scale;
    this->_originalModelMatrix = EGE::Maths::Matrix<4, 4, float>({
        {rotation.x, scale.x, 0.0f, position.x},
        {rotation.y, scale.y, 0.0f, position.y},
        {rotation.z, scale.z, 0.0f, position.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    });
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
    modelMat = glm::rotate(modelMat, glm::radians(this->_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(this->_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::rotate(modelMat, glm::radians(this->_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // modelMat = glm::shear(modelMat, this->_position.toGlmVec3(), glm::vec2(this->_shear.x, this->_shear.z), glm::vec2(this->_shear.y, this->_shear.z), glm::vec2(this->_shear.x, this->_shear.y));
    modelMat = glm::scale(modelMat, this->_scale.toGlmVec3());
    shader.setMat("model", EGE::Maths::Matrix<4, 4, float>(modelMat));
    for (auto &mesh : this->_meshes) {
        mesh.draw(shader);
    }
}

void EGE::Model::loadModel(const std::string& path, bool flipTexture)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

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

        this->setVertexBoneDataToDefault(vertex);

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

    this->extractBoneWeightForVertices(vertices, mesh, scene);
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
            texture.loadFromFile(this->_directory + "/" + str.C_Str(), flipTexture);
            texture.setType(typeName);
            texture.setPath(str.C_Str());
            textures.push_back(texture);
            this->_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

void EGE::Model::setOriginalModelMatrix(const EGE::Maths::Matrix<4, 4, float>& originalModelMatrix)
{
    this->_originalModelMatrix = originalModelMatrix;
}

void EGE::Model::setOriginalModelMatrix()
{
    this->_originalModelMatrix = EGE::Maths::Matrix<4, 4, float>({
        {this->_rotation.x, this->_scale.x, 0.0f, this->_position.x},
        {this->_rotation.y, this->_scale.y, 0.0f, this->_position.y},
        {this->_rotation.z, this->_scale.z, 0.0f, this->_position.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    });
}

EGE::Maths::Matrix<4, 4, float> EGE::Model::getOriginalModelMatrix() const
{
    return this->_originalModelMatrix;
}


void EGE::Model::setPosition(const EGE::Maths::Vector3<float>& position)
{
    this->_position = position;
}

EGE::Maths::Vector3<float> EGE::Model::getPosition() const
{
    return this->_position;
}

void EGE::Model::setRotation(const EGE::Maths::Vector3<float>& rotation)
{
    this->_rotation = rotation;
}

EGE::Maths::Vector3<float> EGE::Model::getRotation() const
{
    return this->_rotation;
}

void EGE::Model::setScale(const EGE::Maths::Vector3<float>& scale)
{
    this->_scale = scale;
}

EGE::Maths::Vector3<float> EGE::Model::getScale() const
{
    return this->_scale;
}

void EGE::Model::setShear(const EGE::Maths::Vector3<float>& shear)
{
    this->_shear = shear;
}

EGE::Maths::Vector3<float> EGE::Model::getShear() const
{
    return this->_shear;
}

std::map<std::string, EGE::BoneInfo>& EGE::Model::getBoneInfoMap()
{
    return this->_boneInfoMap;
}

int& EGE::Model::getBoneNumber()
{
    return this->_boneNumber;
}

void EGE::Model::setVertexBoneDataToDefault(Vertex& vertex)
{
    for (int i = 0; i < MAX_BONE; i++) {
        vertex._boneIDs[i] = -1;
        vertex._boneWeights[i] = 0.0f;
    }
}

void EGE::Model::setVertexBoneData(Vertex& vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE; i++) {
        if (vertex._boneIDs[i] < 0) {
            vertex._boneIDs[i] = boneID;
            vertex._boneWeights[i] = weight;
            break;
        }
    }
}

static inline glm::mat4 matrixToGlmFormat(const aiMatrix4x4& from)
{
    glm::mat4 to;
    to[0][0] = from.a1;
    to[1][0] = from.a2;
    to[2][0] = from.a3;
    to[3][0] = from.a4;
    to[0][1] = from.b1;
    to[1][1] = from.b2;
    to[2][1] = from.b3;
    to[3][1] = from.b4;
    to[0][2] = from.c1;
    to[1][2] = from.c2;
    to[2][2] = from.c3;
    to[3][2] = from.c4;
    to[0][3] = from.d1;
    to[1][3] = from.d2;
    to[2][3] = from.d3;
    to[3][3] = from.d4;
    return to;
}

void EGE::Model::extractBoneWeightForVertices(std::vector<EGE::Vertex>& vertices, aiMesh *mesh, const aiScene *scene)
{
    for (int i = 0; i < mesh->mNumBones; ++i) {
        int id = -1;
        std::string name(mesh->mBones[i]->mName.C_Str());
        if (this->_boneInfoMap.find(name) == this->_boneInfoMap.end()) {
            BoneInfo info;
            info._id = this->_boneNumber;
            info._offset = matrixToGlmFormat(mesh->mBones[i]->mOffsetMatrix);
            this->_boneInfoMap[name] = info;
            id = this->_boneNumber;
            this->_boneNumber++;
        } else {
            id = this->_boneInfoMap[name]._id;
        }
        if (id == -1)
            throw ModelError("ERROR\n\tBONE\n\t\tBone not found");
        if (id > mesh->mNumBones)
            continue;
        aiVertexWeight *weight = mesh->mBones[id]->mWeights;
        int nWeights = mesh->mBones[id]->mNumWeights;
        for (int wid = 0; wid < nWeights; ++wid) {
            int vid = weight[wid].mVertexId;
            float w = weight[wid].mWeight;
            if (vid > vertices.size())
                throw ModelError("ERROR\n\tVERTEX\n\t\tVertex not found");
            this->setVertexBoneData(vertices[vid], id, w);
        }
    }
}