/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Animation
*/

#include "Animation.hpp"

EGE::Animation::Animation(const std::string& animatioPath, Model *model)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(animatioPath, aiProcess_Triangulate);
    if (!scene || !scene->mRootNode) {
        throw AnimationError("Failed to load animation file: " + animatioPath);
    }
    if (!scene->HasAnimations()) {
        throw AnimationError("No animations found in file: " + animatioPath);
    }
    aiAnimation *animation = scene->mAnimations[0];
    this->_duration = animation->mDuration;
    this->_ticksPerSecond = animation->mTicksPerSecond;
    this->readHierarchyData(this->_rootNode, scene->mRootNode);
    this->readMissingBones(animation, *model);
}

EGE::Animation::~Animation()
{
}

EGE::Bone *EGE::Animation::findBone(const std::string& name)
{
    auto iter = std::find_if(this->_bones.begin(), this->_bones.end()
    , [&name](const Bone& bone) {
        return bone.getName() == name;
    });
    if (iter == this->_bones.end()) {
        return nullptr;
    } else {
        return &(*iter);
    }
}

void EGE::Animation::readMissingBones(const aiAnimation* animation, Model &model)
{
    int size = animation->mNumChannels;

    std::map<std::string, BoneInfo>& boneInfoMap = model.getBoneInfoMap();

    int& boneCount = model.getBoneNumber();


    for (int i = 0; i < size; i++) {
        aiNodeAnim *channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
            boneInfoMap[boneName]._id = boneCount;
            boneCount++;
        }
        this->_bones.push_back(Bone(channel->mNodeName.data, boneInfoMap[boneName]._id, channel));
    }
    this->_boneInfoMap = boneInfoMap;
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

void EGE::Animation::readHierarchyData(AssimpNodeData& dest, const aiNode* src)
{
    if (!src)
        throw AnimationError("Given node is null");
    dest._name = src->mName.data;
    dest._transformation = matrixToGlmFormat(src->mTransformation);
    dest._childrenCount = src->mNumChildren;
    for (int i = 0; i < src->mNumChildren; i++) {
        AssimpNodeData newData;
        readHierarchyData(newData, src->mChildren[i]);
        dest._children.push_back(newData);
    }
}