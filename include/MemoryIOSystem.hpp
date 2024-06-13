/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** MemoryIOSystem
*/

#ifndef MEMORYIOSYSTEM_HPP_
    #define MEMORYIOSYSTEM_HPP_

    #include "MemoryIOStream.hpp"
    #include <assimp/IOSystem.hpp>
    #include <map>
    #include <string>


class MemoryIOSystem : public Assimp::IOSystem {
    public:

    void addFile(const std::string &path);

    bool Exists(const char *pFile) const override;

    char getOsSeparator() const override;

    Assimp::IOStream *Open(const char *pFile, const char *pMode) override;

    void Close(Assimp::IOStream *pFile) override;

    void setAssetManager(AAssetManager *mgr);

    AAssetManager *getAssetManager() const;

    private:
        std::map<std::string, std::pair<const unsigned char*, size_t>> files;
        AAssetManager *_mgr;
};

#endif /* !MEMORYIOSYSTEM_HPP_ */
