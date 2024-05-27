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

/**
 * @file Model.hpp
 * @brief File containing the Model class and its related functions.
 */

namespace EGE {

    /**
     * @class Model
     * @brief Class representing a 3D model.
     */
    class Model {
        public:

            /**
             * @class ModelError
             * @brief Exception class for Model related errors.
             */
            class ModelError : public EGE::Error {
                public:
                    /**
                     * @brief Constructor for ModelError.
                     * @param message The error message.
                     */
                    ModelError(const std::string &message) : EGE::Error(message) {}
            };

            /**
             * @brief Constructor for Model.
             * @param path The path to the model file.
             */
            Model(const std::string& path);

            /**
             * @brief Destructor for Model.
             */
            ~Model();

            /**
             * @brief Draws the model using a shader.
             * @param shader The shader to use for drawing.
             */
            void draw(Shader& shader);

        private:
            /**
             * @brief Loads a model from a file.
             * @param path The path to the model file.
             */
            void loadModel(const std::string& path);

            /**
             * @brief Processes a node in the model.
             * @param node The node to process.
             * @param scene The scene containing the node.
             */
            void processNode(aiNode *node, const aiScene *scene);

            /**
             * @brief Processes a mesh in the model.
             * @param mesh The mesh to process.
             * @param scene The scene containing the mesh.
             * @return The processed mesh.
             */
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);

            /**
             * @brief Loads the textures for a material.
             * @param mat The material to load textures for.
             * @param type The type of textures to load.
             * @param typeName The name of the type of textures to load.
             * @return A vector of the loaded textures.
             */
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);

            std::vector<Mesh> _meshes; ///< The meshes in the model.
            std::string _directory; ///< The directory of the model file.
            std::vector<Texture> _texturesLoaded; ///< The textures loaded for the model.
    };
}
