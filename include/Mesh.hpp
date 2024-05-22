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

namespace EGE {
    class Mesh {
        public:
            Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
            ~Mesh();

            void draw(const Shader& shader);
        private:
            void setupMesh();
            std::vector<Vertex> _vertices;
            std::vector<unsigned int> _indices;
            std::vector<Texture> _textures;
            unsigned int _vao;
            unsigned int _vbo;
            unsigned int _ebo;
    };
}