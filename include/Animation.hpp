/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Animation
*/

#pragma once

// Engine include
#include "Bone.hpp"
#include "Model.hpp"

// C++ include

namespace EGE {
    struct AssimpNodeData {
        glm::mat4 _transformation;
        std::string _name;
        int _childrenCount;
        std::vector<AssimpNodeData> _children;
    };

    class AnimationError : public EGE::Error {
        public:
            AnimationError(const std::string &message) : EGE::Error(message) {}
    };

    class Animation {
        public:
            Animation() = default;

            Animation(const std::string& animatioPath, Model *model);

            ~Animation();

            Bone *findBone(const std::string& name);

            inline float getTickPerSecond() const
            {
                return _ticksPerSecond;
            }

            inline float getDuration()
            {
                return _duration;
            }

            inline const AssimpNodeData& getRootNode() const
            {
                return _rootNode;
            }

            inline const std::map<std::string, BoneInfo>& getBoneInfoMap() const
            {
                return _boneInfoMap;
            }
        private:
            void readMissingBones(const aiAnimation* animation, Model &model);

            void readHierarchyData(AssimpNodeData& dest, const aiNode* src);

            float _duration;
            int _ticksPerSecond;
            std::vector<Bone> _bones;
            AssimpNodeData _rootNode;
            std::map<std::string, BoneInfo> _boneInfoMap;
    };
}