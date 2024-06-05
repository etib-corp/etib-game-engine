/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Animator
*/

#pragma once

// Engine include
#include "Animation.hpp"

// C++ include

namespace EGE {
    class Animator2000 {
        public:
            Animator2000(Animation *animation);

            ~Animator2000() = default;

            void updateAnimation(float deltaTime);

            void playAnimation(Animation *animation);

            void calculateBoneTransform(const AssimpNodeData *node, glm::mat4 parentTransform);

            std::vector<glm::mat4> getFinalBoneMatrices();
        private:
            std::vector<glm::mat4> _finalBoneMatrices;
            Animation *_currentAnimation;
            float _animationTime;
            float _deltaTime;
    };
}