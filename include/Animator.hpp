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
    /**
     * @class Animator2000
     * @brief The Animator2000 class is responsible for managing animations and calculating bone transformations.
     */
    class Animator2000 {
        public:
            /**
             * @brief Constructs an Animator2000 object with the given Animation.
             *
             * @param animation The Animation object to be associated with the Animator2000.
             */
            Animator2000(Animation *animation);

            /**
             * @brief Destructor for the Animator2000 class.
             *
             * This destructor is set to default, meaning it will perform the default destruction
             * behavior for the Animator2000 class.
             */
            ~Animator2000() = default;

            /**
             * @brief Updates the animation based on the elapsed time.
             *
             * This function is responsible for updating the animation based on the elapsed time.
             * It takes the deltaTime as a parameter, which represents the time elapsed since the last update.
             * This function should be called in the game loop to ensure smooth animation.
             *
             * @param deltaTime The time elapsed since the last update.
             */
            void updateAnimation(float deltaTime);

            /**
             * Plays the specified animation.
             *
             * @param animation A pointer to the Animation object to be played.
             */
            void playAnimation(Animation *animation);

            /**
             * Calculates the bone transform for a given node.
             *
             * @param node The AssimpNodeData representing the node.
             * @param parentTransform The parent transform matrix.
             */
            void calculateBoneTransform(const AssimpNodeData *node, glm::mat4 parentTransform);

            /**
             * @brief Retrieves the final bone matrices.
             *
             * This function returns a vector of `glm::mat4` representing the final bone matrices.
             * These matrices are typically used for skeletal animation.
             *
             * @return A vector of `glm::mat4` representing the final bone matrices.
             */
            std::vector<glm::mat4> getFinalBoneMatrices();
        private:
            std::vector<glm::mat4> _finalBoneMatrices;  /**< The final bone matrices. */
            Animation *_currentAnimation;               /**< The current animation. */
            float _animationTime;                       /**< The current animation time. */
            float _deltaTime;                           /**< The time elapsed since the last update. */
    };
}