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
    struct KeyPosition {
        glm::vec3 position;
        float time;
    };

    struct KeyRotation {
        glm::quat rotation;
        float time;
    };

    struct KeyScale {
        glm::vec3 scale;
        float time;
    };

    class BoneError : public EGE::Error {
        public:
            BoneError(const std::string& message) : EGE::Error(message) {}
    };

    class Bone {
        public:
            Bone(const std::string& name, int id, const aiNodeAnim* channel);

            ~Bone() = default;

            void update(float time);

            glm::mat4 getLocalTransform() const;

            std::string getName() const;

            int getId() const;

            int getPositionIndex(float time);

            int getRotationIndex(float time);

            int getScaleIndex(float time);
        private:

            float getScaleFactor(float last, float next, float time);

            glm::mat4 interpolatePosition(float time);

            glm::mat4 interpolateRotation(float time);

            glm::mat4 interpolateScale(float time);

            std::vector<KeyPosition> _positions;
            std::vector<KeyRotation> _rotations;
            std::vector<KeyScale> _scales;
            int _numPositions;
            int _numRotations;
            int _numScales;

            glm::mat4 _localTransform;
            std::string _name;
            int _id;
    };
}