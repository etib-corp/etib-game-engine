/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Bone
*/

#include "Bone.hpp"

EGE::Bone::Bone(const std::string& name, int id, const aiNodeAnim* channel) : _name(name), _id(id), _localTransform(1.0f)
{
    this->_numPositions = channel->mNumPositionKeys;
    for (int i = 0; i < this->_numPositions; ++i) {
        aiVector3D pos = channel->mPositionKeys[i].mValue;
        float time = channel->mPositionKeys[i].mTime;
        KeyPosition key = {glm::vec3(pos.x, pos.y, pos.z), time};
        this->_positions.push_back(key);
    }

    this->_numRotations = channel->mNumRotationKeys;
    for (int i = 0; i < this->_numRotations; ++i) {
        aiQuaternion quat = channel->mRotationKeys[i].mValue;
        float time = channel->mPositionKeys[i].mTime;
        KeyRotation key = {glm::quat(quat.w, quat.x, quat.y, quat.z), time};
        this->_rotations.push_back(key);
    }

    this->_numScales = channel->mNumScalingKeys;
    for (int i = 0; i < this->_numScales; ++i) {
        aiVector3D scale = channel->mScalingKeys[i].mValue;
        float time = channel->mPositionKeys[i].mTime;
        KeyScale key = {glm::vec3(scale.x, scale.y, scale.z), time};
        this->_scales.push_back(key);
    }
}

void EGE::Bone::update(float time)
{
    glm::mat4 position = this->interpolatePosition(time);
    glm::mat4 rotation = this->interpolateRotation(time);
    glm::mat4 scale = this->interpolateScale(time);
    this->_localTransform = position * rotation * scale;
}

glm::mat4 EGE::Bone::getLocalTransform() const
{
    return this->_localTransform;
}

std::string EGE::Bone::getName() const
{
    return this->_name;
}

int EGE::Bone::getPositionIndex(float time)
{
    for (int i = 0; i < this->_numPositions; i++) {
        if (time < this->_positions[i + 1].time)
            return i;
    }
    throw BoneError("No position index found");
}

int EGE::Bone::getRotationIndex(float time)
{
    for (int i = 0; i < this->_numRotations; i++) {
        if (time < this->_rotations[i + 1].time)
            return i;
    }
    throw BoneError("No rotation index found");
}

int EGE::Bone::getScaleIndex(float time)
{
    for (int i = 0; i < this->_numScales; i++) {
        if (time < this->_scales[i + 1].time)
            return i;
    }
    throw BoneError("No scale index found");
}

float EGE::Bone::getScaleFactor(float last, float next, float time)
{
    if (next - last == 0.0)
        return 0; // may throw an error
    return (time - last) / (next - last);
}

glm::mat4 EGE::Bone::interpolatePosition(float time)
{
    if (this->_numPositions == 1)
        return glm::translate(glm::mat4(1.0f), this->_positions[0].position);
    int p0 = this->getPositionIndex(time);
    int p1 = p0 + 1;
    float scaleFactor = this->getScaleFactor(this->_positions[p0].time, this->_positions[p1].time, time);
    glm::vec3 finalPosition = glm::mix(this->_positions[p0].position, this->_positions[p1].position, scaleFactor);
    return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 EGE::Bone::interpolateRotation(float time)
{
    if (this->_numRotations == 1)
        return glm::toMat4(this->_rotations[0].rotation);
    int r0 = this->getRotationIndex(time);
    int r1 = r0 + 1;
    float scaleFactor = this->getScaleFactor(this->_rotations[r0].time, this->_rotations[r1].time, time);
    glm::quat finalRotation = glm::slerp(this->_rotations[r0].rotation, this->_rotations[r1].rotation, scaleFactor);
    return glm::toMat4(finalRotation);
}

glm::mat4 EGE::Bone::interpolateScale(float time)
{
    if (this->_numScales == 1)
        return glm::scale(glm::mat4(1.0f), this->_scales[0].scale);
    int s0 = this->getScaleIndex(time);
    int s1 = s0 + 1;
    float scaleFactor = this->getScaleFactor(this->_scales[s0].time, this->_scales[s1].time, time);
    glm::vec3 finalScale = glm::mix(this->_scales[s0].scale, this->_scales[s1].scale, scaleFactor);
    return glm::scale(glm::mat4(1.0f), finalScale);
}