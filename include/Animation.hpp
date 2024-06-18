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

/**
 * @brief Namespace EGE contains classes and structs related to the EGE library.
 */
namespace EGE {

    /**
     * @brief Struct representing data of a node in the Assimp scene graph.
     */
    struct AssimpNodeData {
        glm::mat4 _transformation; /**< Transformation matrix of the node. */
        std::string _name; /**< Name of the node. */
        int _childrenCount; /**< Number of children nodes. */
        std::vector<AssimpNodeData> _children; /**< Vector of children nodes. */
    };

    /**
     * @brief Custom exception class for animation errors.
     */
    class AnimationError : public EGE::Error {
        public:
            /**
             * @brief Constructs an AnimationError object with the given error message.
             * @param message The error message.
             */
            AnimationError(const std::string &message) : EGE::Error(message) {}
    };

    /**
     * @brief Class representing an animation.
     */
    class Animation {
        public:
            /**
             * @brief Default constructor.
             */
            Animation() = default;

            /**
             * @brief Constructs an Animation object with the given animation path and model.
             * @param animatioPath The path to the animation file.
             * @param model The model associated with the animation.
             */
            Animation(const std::string& animatioPath, Model *model);

            /**
             * @brief Destructor.
             */
            ~Animation();

            /**
             * @brief Finds a bone with the given name in the animation.
             * @param name The name of the bone to find.
             * @return A pointer to the found bone, or nullptr if not found.
             */
            Bone *findBone(const std::string& name);

            /**
             * @brief Gets the ticks per second of the animation.
             * @return The ticks per second.
             */
            inline float getTickPerSecond() const
            {
                return this->_ticksPerSecond;
            }

            /**
             * @brief Gets the duration of the animation.
             * @return The duration in seconds.
             */
            inline float getDuration()
            {
                return this->_duration;
            }

            /**
             * @brief Gets the root node of the animation.
             * @return The root node.
             */
            inline const AssimpNodeData& getRootNode() const
            {
                return this->_rootNode;
            }

            /**
             * @brief Gets the map of bone information.
             * @return The map of bone information.
             */
            inline const std::map<std::string, BoneInfo>& getBoneInfoMap() const
            {
                return this->_boneInfoMap;
            }
        private:
            /**
             * @brief Reads missing bones from the given animation and updates the model.
             * @param animation The animation to read from.
             * @param model The model to update.
             */
            void readMissingBones(const aiAnimation* animation, Model &model);

            /**
             * @brief Reads hierarchy data from the given source node and updates the destination node.
             * @param dest The destination node to update.
             * @param src The source node to read from.
             */
            void readHierarchyData(AssimpNodeData& dest, const aiNode* src);

            float _duration; /**< Duration of the animation in seconds. */
            int _ticksPerSecond; /**< Ticks per second of the animation. */
            std::vector<Bone> _bones; /**< Vector of bones in the animation. */
            AssimpNodeData _rootNode; /**< Root node of the animation. */
            std::map<std::string, BoneInfo> _boneInfoMap; /**< Map of bone information. */
    };
}