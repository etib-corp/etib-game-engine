/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Texture
*/

#pragma once

// Engine include
#include "Error.hpp"
#include "OpenGL.hpp"

// C++ include
#include <string>


/**
 * @file Texture.hpp
 * @brief File containing the Texture class and its related functions.
 */

/**
 * @namespace EGE
 * @brief Namespace for the ETIB Game Engine.
 * The EGE namespace contains all the classes, functions, and variables
 * related to the ETIB Game Engine.
*/
namespace EGE {

    /**
     * @class Texture
     * @brief Class representing a texture.
     */
    class Texture {
        public:

            /**
             * @class TextureError
             * @brief Exception class for Texture related errors.
             */
            class TextureError : public Error {
                public:
                    /**
                     * @brief Constructor for TextureError.
                     * @param message The error message.
                     */
                    TextureError(const std::string& message) : Error(message) {}
            };

            /**
             * @brief Default constructor for Texture.
             */
            Texture();

            /**
             * @brief Constructor for Texture.
             * @param path The path to the texture file.
             * @param type The type of the texture.
             * @param id The id of the texture.
             */
            Texture(const std::string& path, const std::string& type, unsigned int id);

            /**
             * @brief Destructor for Texture.
             */
            ~Texture();

            /**
             * @brief Loads a texture from a file.
             * @param path The path to the texture file.
             */
            void loadFromFile(const std::string& path, bool flip = false);

            /**
             * @brief Gets the id of the texture.
             * @return The id of the texture.
             */
            unsigned int getId() const;

            /**
             * @brief Gets the type of the texture.
             * @return The type of the texture.
             */
            std::string getType() const;

            /**
             * @brief Gets the path to the texture file.
             * @return The path to the texture file.
             */
            std::string getPath() const;

            /**
             * @brief Sets the id of the texture.
             * @param id The new id of the texture.
             */
            void setId(unsigned int id);

            /**
             * @brief Sets the type of the texture.
             * @param type The new type of the texture.
             */
            void setType(const std::string& type);

            /**
             * @brief Sets the path to the texture file.
             * @param path The new path to the texture file.
             */
            void setPath(const std::string& path);

        private:
            unsigned int _id; ///< The id of the texture.
            std::string _type; ///< The type of the texture.
            std::string _path; ///< The path to the texture file.
            int _width; ///< The width of the texture.
            int _height; ///< The height of the texture.
            int _nrChannels; ///< The number of channels in the texture.
    };
}
