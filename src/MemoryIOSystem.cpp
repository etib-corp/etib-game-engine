/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** MemoryIOSystem
*/

#include "MemoryIOSystem.hpp"

void MemoryIOSystem::addFile(const std::string &path)
{
    AAsset *file = AAssetManager_open(this->_mgr, path.c_str(), AASSET_MODE_UNKNOWN);
    off_t fileLength = AAsset_getLength(file);
    unsigned char *modelSource = (unsigned char *)calloc(fileLength, sizeof(unsigned char));
    AAsset_read(file, modelSource, fileLength);
    this->files[path] = std::make_pair(modelSource, fileLength);
    AAsset_close(file);
}

bool MemoryIOSystem::Exists(const char *pFile) const
{
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Checking if file %s exists\n", pFile);
    return this->files.find(pFile) != this->files.end();
}

char MemoryIOSystem::getOsSeparator() const
{
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Getting OS separator\n");
    return '/';
}

Assimp::IOStream *MemoryIOSystem::Open(const char *pFile, const char *pMode)
{
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Opening file %s\n", pFile);
    if (this->files.find(pFile) == this->files.end())
        return nullptr;
    return new MemoryIOStream(this->files[pFile].first, this->files[pFile].second);
}

void MemoryIOSystem::Close(Assimp::IOStream *pFile)
{
    delete pFile;
}

void MemoryIOSystem::setAssetManager(AAssetManager *mgr)
{
    this->_mgr = mgr;
}

AAssetManager *MemoryIOSystem::getAssetManager() const
{
    return this->_mgr;
}
