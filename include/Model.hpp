/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Model
*/

#pragma once

// Engine include
#include "Error.hpp"
#include "Mesh.hpp"
#include "Maths/Vector3.hpp"

// C++ include
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <thread>
#include <vector>

namespace EGE {
    class Model {
        public:
            class ModelError : public EGE::Error {
                public:
                    ModelError(const std::string &message) : EGE::Error(message) {}
            };
            Model(const std::string& path);
            ~Model();

            void draw(Shader& shader);
        private:
            void loadModel(const std::string& path);
            void processNode(aiNode *node, const aiScene *scene);
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);

            std::vector<Mesh> _meshes;
            std::string _directory;
            std::vector<Texture> _texturesLoaded;
    };
}
