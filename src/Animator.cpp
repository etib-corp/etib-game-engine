/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Animator
*/

#include "Animator.hpp"

EGE::Animator2000::Animator2000(Animation *animation)
{
    this->_currentAnimation = animation;
    this->_animationTime = 0.0f;
    this->_deltaTime = 0.0f;
    this->_finalBoneMatrices.reserve(100);
    for (int i = 0; i < 100; i++) {
        this->_finalBoneMatrices.push_back(glm::mat4(1.0f));
    }
}

void EGE::Animator2000::updateAnimation(float deltaTime)
{
    this->_deltaTime = deltaTime;
    if (!this->_currentAnimation)
        return;
    this->_animationTime += this->_currentAnimation->getTickPerSecond() * deltaTime;
    this->_animationTime = fmod(this->_animationTime, this->_currentAnimation->getDuration());
    this->calculateBoneTransform(&this->_currentAnimation->getRootNode(), glm::mat4(1.0f));
}

void EGE::Animator2000::playAnimation(Animation *animation)
{
    this->_currentAnimation = animation;
    this->_animationTime = 0.0f;
}

void EGE::Animator2000::calculateBoneTransform(const AssimpNodeData *node, glm::mat4 parentTransform)
{
    std::string nodeName = node->_name;
    glm::mat4 nodeTransform = node->_transformation;

    Bone *bone = this->_currentAnimation->findBone(nodeName);

    if (bone) {
        bone->update(this->_animationTime);
        nodeTransform = bone->getLocalTransform();
    }
    glm::mat4 globalTransformation = parentTransform * nodeTransform;

    const std::map<std::string, EGE::BoneInfo>& boneInfoMap = this->_currentAnimation->getBoneInfoMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end()) {
        int index = boneInfoMap.at(nodeName)._id;
        glm::mat4 offset = boneInfoMap.at(nodeName)._offset;
        this->_finalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->_childrenCount; i++) {
        this->calculateBoneTransform(&node->_children[i], globalTransformation);
    }
}

std::vector<glm::mat4> EGE::Animator2000::getFinalBoneMatrices()
{
    return this->_finalBoneMatrices;
}