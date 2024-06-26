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
#include <map>
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
            Model(const std::string& path, const EGE::Maths::Vector3<float>& position = EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), const EGE::Maths::Vector3<float> &rotation = EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), const EGE::Maths::Vector3<float>& scale = EGE::Maths::Vector3<float>(1.0f, 1.0f, 1.0f), bool flipTexture = false, bool forceReload = false);

            /**
             * @brief Destructor for Model.
             */
            ~Model();

            /**
             * @brief Draws the model using a shader.
             * @param shader The shader to use for drawing.
             */
            void draw(Shader& shader);

            /**
             * @brief Set the original model matrix of the model
             *
             * @param originalModelMatrix Matrix<4, 4, float> that is the new original model matrix of the model
            */
            void setOriginalModelMatrix(const EGE::Maths::Matrix<4, 4, float>& originalModelMatrix);

            /**
             * @brief Set the original model matrix of the model
             * @note The current rotation, scale, shear and position of the model will be used
            */
            void setOriginalModelMatrix();

            /**
             * @brief Returns the original model matrix of the model
             *
             * @return Matrix<4, 4, float> that is the original model matrix of the model
            */
            EGE::Maths::Matrix<4, 4, float> getOriginalModelMatrix() const;

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
             * @brief Set the rotation of the model
             *
             * @param rotation Vector3 of float that is the new rotation of the model
             * @note The rotation is in degrees
            */
            void setRotation(const EGE::Maths::Vector3<float>& rotation);

            /**
             * @brief Returns the rotation of the model
             *
             * @return Vector3 of float that is the rotation of the model
             * @note The rotation is in degrees
            */
            EGE::Maths::Vector3<float> getRotation() const;

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
             * @brief Set the shear of the model
             *
             * @param shear Vector3 of float that is the new shear of the model
            */
            void setShear(const EGE::Maths::Vector3<float>& shear);

            /**
             * @brief Returns the shear of the model
             *
             * @return Vector3 of float that is the shear of the model
            */
            EGE::Maths::Vector3<float> getShear() const;

            /**
             * @brief Returns the map of boneInfo of the model.
             *
             * @return std::map<std::string, BoneInfo> that is the boneInfo of the model
             **/
            std::map<std::string, BoneInfo>& getBoneInfoMap();

            /**
             * @brief Returns the number of bones in the model.
             *
             * @return int& that is the number of bones in the model
             **/
            int& getBoneNumber();

            /**
             * @brief Returns the vector of meshes of the model.
             * 
             * @return std::vector<Mesh> that is the vector of meshes of the model
             **/
            std::vector<Mesh> getMeshes() const { return this->_meshes; }

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

            /**
             * @brief Resets the bone data of a vertex to default values.
             *
             * @param vertex The vertex to reset.
             */
            void setVertexBoneDataToDefault(Vertex& vertex);

            /**
             * @brief Sets the bone data for a vertex.
             *
             * @param vertex The vertex to set the bone data for.
             * @param boneID The ID of the bone.
             * @param weight The weight of the bone.
             */
            void setVertexBoneData(Vertex& vertex, int boneID, float weight);

            /**
             * @brief Extracts bone weight for vertices.
             *
             * @param vertices The vertices to extract bone weight for.
             * @param mesh The mesh containing the vertices.
             * @param scene The scene containing the mesh.
             */
            void extractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh *mesh, const aiScene *scene);

            std::vector<Mesh> _meshes; ///< The meshes in the model.
            std::string _directory; ///< The directory of the model file.
            std::vector<Texture> _texturesLoaded; ///< The textures loaded for the model.
            EGE::Maths::Vector3<float> _position; ///< The position of the model.
            EGE::Maths::Vector3<float> _rotation; ///< The rotation of the model.
            EGE::Maths::Vector3<float> _shear; ///< The shear of the model.
            EGE::Maths::Vector3<float> _scale; ///< The scale of the model.
            static std::map<std::string, Model *> _modelsLoaded; ///< The loaded models.
            std::map<std::string, BoneInfo> _boneInfoMap; ///< The boneInfo of the model.
            int _boneNumber;    ///< The number of bones in the model.
            EGE::Maths::Matrix<4, 4, float> _originalModelMatrix;   ///< The original model matrix of the model.
    };
}
