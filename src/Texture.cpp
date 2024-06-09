/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Texture
*/

#include "Texture.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
    #include "external/stb_image.hpp"
#endif

#include <android/log.h>

EGE::Texture::Texture()
{
}

EGE::Texture::Texture(const std::string& path, const std::string& type, unsigned int id) : _path(path), _type(type), _id(id)
{
}

EGE::Texture::~Texture()
{
}

void EGE::Texture::loadFromFile(const std::string& path, bool flip)
{
    stbi_set_flip_vertically_on_load(flip);
    GLenum format;
    glGenTextures(1, &this->_id);


    unsigned char *data = stbi_load(path.c_str(), &this->_width, &this->_height, &this->_nrChannels, STBI_default);

    if (data) {
        if (this->_nrChannels == 1)
            format = GL_RED;
        else if (this->_nrChannels == 3)
            format = GL_RGB;
        else if (this->_nrChannels == 4)
            format = GL_RGBA;
        else {
            stbi_image_free(data);
            throw TextureError("Texture format with " + std::to_string(format) + " channels are not supported : " + path);
        }
        glBindTexture(GL_TEXTURE_2D, this->_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, this->_width, this->_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        stbi_image_free(data);
        throw TextureError("Failed to load texture : " + path);
    }
}

void EGE::Texture::loadFromFile(const unsigned char *buffer, off_t size, bool flip)
{
    stbi_set_flip_vertically_on_load(flip);
    GLenum format;
    glGenTextures(1, &this->_id);

    unsigned char *data = stbi_load_from_memory(buffer, size, &this->_width, &this->_height, &this->_nrChannels, STBI_default);
    if (data) {
        if (this->_nrChannels == 1)
            format = GL_RED;
        else if (this->_nrChannels == 3)
            format = GL_RGB;
        else if (this->_nrChannels == 4)
            format = GL_RGBA;
        else {
            stbi_image_free(data);
            throw TextureError("Texture format with " + std::to_string(format) + " channels are not supported");
        }
        glBindTexture(GL_TEXTURE_2D, this->_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, this->_width, this->_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        stbi_image_free(data);
        throw TextureError("Failed to load texture");
    }
}

unsigned int EGE::Texture::getId() const
{
    return this->_id;
}

std::string EGE::Texture::getType() const
{
    return this->_type;
}

std::string EGE::Texture::getPath() const
{
    return this->_path;
}

void EGE::Texture::setId(unsigned int id)
{
    this->_id = id;
}

void EGE::Texture::setType(const std::string& type)
{
    this->_type = type;
}

void EGE::Texture::setPath(const std::string& path)
{
    this->_path = path;
}
