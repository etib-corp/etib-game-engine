/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Bone
*/

#pragma once

// Engine include
#include "Error.hpp"
#include "OpenGL.hpp"
#include "Maths/Matrix.hpp"

// C++ include
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>

namespace EGE {
    /**
     * @brief Represents the position of a bone at a specific time.
     */
    struct KeyPosition {
        glm::vec3 position; /**< The position of the bone. */
        float time; /**< The time at which the position occurs. */
    };

    /**
     * @brief Represents the rotation of a bone at a specific time.
     */
    struct KeyRotation {
        glm::quat rotation; /**< The rotation of the bone. */
        float time; /**< The time at which the rotation occurs. */
    };

    /**
     * @brief Represents the scale of a bone at a specific time.
     */
    struct KeyScale {
        glm::vec3 scale; /**< The scale of the bone. */
        float time; /**< The time at which the scale occurs. */
    };

    /**
     * @brief Exception class for bone-related errors.
     */
    class BoneError : public EGE::Error {
        public:
            /**
             * @brief Constructs a BoneError object with the given error message.
             * @param message The error message.
             */
            BoneError(const std::string& message) : EGE::Error(message) {}
    };

    /**
     * @brief Represents a bone in a skeletal animation.
     */
    class Bone {
        public:
            /**
             * @brief Constructs a Bone object with the given name, ID, and animation channel.
             * @param name The name of the bone.
             * @param id The ID of the bone.
             * @param channel The animation channel for the bone.
             */
            Bone(const std::string& name, int id, const aiNodeAnim* channel);

            /**
             * @brief Default destructor for the Bone class.
             */
            ~Bone() = default;

            /**
             * @brief Updates the bone's state at the given time.
             * @param time The time at which to update the bone.
             */
            void update(float time);

            /**
             * @brief Gets the local transform matrix of the bone.
             * @return The local transform matrix.
             */
            glm::mat4 getLocalTransform() const;

            /**
             * @brief Gets the name of the bone.
             * @return The name of the bone.
             */
            std::string getName() const;

            /**
             * @brief Gets the ID of the bone.
             * @return The ID of the bone.
             */
            inline int getId() const
            {
                return this->_id;
            }

            /**
             * @brief Gets the index of the position keyframe at the given time.
             * @param time The time at which to find the position keyframe.
             * @return The index of the position keyframe.
             */
            int getPositionIndex(float time);

            /**
             * @brief Gets the index of the rotation keyframe at the given time.
             * @param time The time at which to find the rotation keyframe.
             * @return The index of the rotation keyframe.
             */
            int getRotationIndex(float time);

            /**
             * @brief Gets the index of the scale keyframe at the given time.
             * @param time The time at which to find the scale keyframe.
             * @return The index of the scale keyframe.
             */
            int getScaleIndex(float time);
        private:
            /**
             * @brief Calculates the scale factor between two keyframes at the given time.
             * @param last The time of the previous keyframe.
             * @param next The time of the next keyframe.
             * @param time The time at which to calculate the scale factor.
             * @return The scale factor.
             */
            float getScaleFactor(float last, float next, float time);

            /**
             * @brief Interpolates the position of the bone at the given time.
             * @param time The time at which to interpolate the position.
             * @return The interpolated position matrix.
             */
            glm::mat4 interpolatePosition(float time);

            /**
             * @brief Interpolates the rotation of the bone at the given time.
             * @param time The time at which to interpolate the rotation.
             * @return The interpolated rotation matrix.
             */
            glm::mat4 interpolateRotation(float time);

            /**
             * @brief Interpolates the scale of the bone at the given time.
             * @param time The time at which to interpolate the scale.
             * @return The interpolated scale matrix.
             */
            glm::mat4 interpolateScale(float time);

            std::vector<KeyPosition> _positions; /**< The keyframes for the bone's positions. */
            std::vector<KeyRotation> _rotations; /**< The keyframes for the bone's rotations. */
            std::vector<KeyScale> _scales; /**< The keyframes for the bone's scales. */
            int _numPositions; /**< The number of position keyframes. */
            int _numRotations; /**< The number of rotation keyframes. */
            int _numScales; /**< The number of scale keyframes. */

            glm::mat4 _localTransform; /**< The local transform matrix of the bone. */
            std::string _name; /**< The name of the bone. */
            int _id; /**< The ID of the bone. */
    };
}