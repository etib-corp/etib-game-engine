/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Vertex
*/

#pragma once

// Engine include
#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"

// C++ include
#include <array>

#define MAX_BONE 4

/**
 * @file Vertex.hpp
 * @brief File containing the Vertex struct and its related functions.
 */

namespace EGE {

    /**
     * @struct Vertex
     * @brief Struct representing a vertex in 3D space.
     */
    struct Vertex {
        glm::vec3 _position; ///< The position of the vertex in 3D space.
        glm::vec3 _normal; ///< The normal vector of the vertex.
        glm::vec2 _texCoords; ///< The texture coordinates of the vertex.
        glm::vec3 _tangent; ///< The tangent vector at the vertex.
        glm::vec3 _bitangent; ///< The bitangent vector at the vertex.
        int _boneIDs[MAX_BONE]; ///< The IDs of the bones that influence this vertex.
        float _boneWeights[MAX_BONE]; ///< The weights of the influences of the bones on this vertex.
    };

    struct BoneInfo {
        int _id;            ///< The ID of the bone.
        glm::mat4 _offset;  ///< The offset matrix of the bone.
    };
}
