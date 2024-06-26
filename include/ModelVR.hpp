/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** ModelVR
*/

#pragma once

// Engine include
#include "Error.hpp"
#include "Mesh.hpp"
#include "Maths/Vector3.hpp"
#include "MemoryIOSystem.hpp"
#include "UtilsVR.hpp"

// C++ include
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <thread>
#include <vector>

extern MemoryIOSystem *gMemoryIOSystem;


/**
 * @file ModelVR.hpp
 * @brief File containing the ModelVR class and its related functions.
 */

namespace EGE {

    /**
     * @class ModelVR
     * @brief Class representing a 3D model.
     */
    class ModelVR {
        public:

            /**
             * @class ModelError
             * @brief Exception class for ModelVR related errors.
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
             * @brief Constructor for ModelVR.
             * @param path The path to the model file.
             */
            ModelVR(const std::string& path, const EGE::Maths::Vector3<float>& position = EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), const EGE::Maths::Vector3<float>& rotation = EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), const EGE::Maths::Vector3<float>& scale = EGE::Maths::Vector3<float>(1.0f, 1.0f, 1.0f), bool flipTexture = false, bool forceReload = false);

            /**
             * @brief Destructor for ModelVR.
             */
            ~ModelVR();

            /**
             * @brief Draws the model using a shader.
             * @param shader The shader to use for drawing.
             */
            void draw(Shader& shader);

            /**
             * @brief Set the position og the model
             *
             * @param position Vector3 of float that is the new position of the model
            */
            void setPosition(const EGE::Maths::Vector3<float>& position);

            /**
             * @brief Returns the position of the model
             *
             * @return Vector3 of float that is the position of the model
            */
            EGE::Maths::Vector3<float> getPosition() const;

            /**
             * @brief Set the scale of the model
             *
             * @param scale Vector3 of float that is the new scale of the model
            */
            void setScale(const EGE::Maths::Vector3<float>& scale);

            /**
             * @brief Returns the scale of the model
             *
             * @return Vector3 of float that is the scale of the model
            */
            EGE::Maths::Vector3<float> getScale() const;

            /**
             * @brief Returns the rotation of the model
             *
             * @return Vector3 of float that is the rotation of the model
            */
            EGE::Maths::Vector3<float> getRotation() const;

            /**
             * @brief Set the rotation of the model
             *
             * @param rotation Vector3 of float that is the new rotation of the model
            */
            void setRotation(const EGE::Maths::Vector3<float>& rotation);

        private:
            /**
             * @brief Loads a model from a file.
             * @param path The path to the model file.
             */
            void loadModel(const std::string& path, bool flipTexture = false);

            /**
             * @brief Processes a node in the model.
             * @param node The node to process.
             * @param scene The scene containing the node.
             */
            void processNode(aiNode *node, const aiScene *scene, bool flipTexture = false);

            /**
             * @brief Processes a mesh in the model.
             * @param mesh The mesh to process.
             * @param scene The scene containing the mesh.
             * @return The processed mesh.
             */
            Mesh processMesh(aiMesh *mesh, const aiScene *scene, bool flipTexture = false);

            /**
             * @brief Loads the textures for a material.
             * @param mat The material to load textures for.
             * @param type The type of textures to load.
             * @param typeName The name of the type of textures to load.
             * @return A vector of the loaded textures.
             */
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName, bool flipTexture = false);

            std::vector<Mesh> _meshes; ///< The meshes in the model.
            std::string _directory; ///< The directory of the model file.
            std::vector<Texture> _texturesLoaded; ///< The textures loaded for the model.
            EGE::Maths::Vector3<float> _position; ///< The position of the model.
            EGE::Maths::Vector3<float> _rotation; ///< The rotation of the model.
            EGE::Maths::Vector3<float> _scale; ///< The scale of the model.
            EGE::Maths::Vector3<float> _shear; ///< The shear of the model.
            static std::map<std::string, ModelVR *> _modelsLoaded; ///< The loaded models.
    };
}
