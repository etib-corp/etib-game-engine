/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Mesh
*/

#pragma once

// Engine include
#include "Maths/Vector3.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

// C++ include
#include <string>
#include <vector>

/**
 * @file Mesh.hpp
 * @brief File containing the Mesh class and its related functions.
 */

namespace EGE {

    /**
     * @class Mesh
     * @brief Class representing a 3D mesh.
     */
    class Mesh {
        public:
            /**
             * @brief Constructor for Mesh.
             * @param vertices The vertices of the mesh.
             * @param indices The indices of the mesh.
             * @param textures The textures of the mesh.
             */
            Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);

            /**
             * @brief Destructor for Mesh.
             */
            ~Mesh();

            /**
             * @brief Draws the mesh using a shader.
             * @param shader The shader to use for drawing.
             */
            void draw(const Shader& shader);

            std::vector<Vertex> getVertices() const { return _vertices; }

        private:
            /**
             * @brief Sets up the mesh for rendering.
             */
            void setupMesh();

            std::vector<Vertex> _vertices; ///< The vertices of the mesh.
            std::vector<unsigned int> _indices; ///< The indices of the mesh.
            std::vector<Texture> _textures; ///< The textures of the mesh.
            unsigned int _vao; ///< The Vertex Array Object of the mesh.
            unsigned int _vbo; ///< The Vertex Buffer Object of the mesh.
            unsigned int _ebo; ///< The Element Buffer Object of the mesh.
    };
}