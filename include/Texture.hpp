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

namespace EGE {
    class Texture {
        public:
            class TextureError : public Error {
                public:
                    TextureError(const std::string& message) : Error(message) {}
            };
            Texture();
            Texture(const std::string& path, const std::string& type, unsigned int id);
            ~Texture();

            void loadFromFile(const std::string& path);

            unsigned int getId() const;
            std::string getType() const;
            std::string getPath() const;

            void setId(unsigned int id);
            void setType(const std::string& type);
            void setPath(const std::string& path);
        private:
            unsigned int _id;
            std::string _type;
            std::string _path;
            int _width;
            int _height;
            int _nrChannels;
    };
}