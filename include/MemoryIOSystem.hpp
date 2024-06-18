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


/**
 * @brief The MemoryIOSystem class is a custom implementation of the Assimp::IOSystem interface.
 *        It provides functionality to add files to a memory buffer and retrieve them when needed.
 */
class MemoryIOSystem : public Assimp::IOSystem {
    public:

    /**
     * @brief Adds a file to the memory buffer.
     * @param path The path of the file to be added.
     */
    void addFile(const std::string &path);

    /**
     * @brief Adds a file to the memory buffer with a specified buffer content.
     * @param path The path of the file to be added.
     * @param buffer The content of the file to be added.
     */
    void addFile(const std::string &path, const std::string &buffer);

    /**
     * @brief Checks if a file exists in the memory buffer.
     * @param pFile The path of the file to check.
     * @return True if the file exists, false otherwise.
     */
    bool Exists(const char *pFile) const override;

    /**
     * @brief Retrieves the operating system separator character.
     * @return The operating system separator character.
     */
    char getOsSeparator() const override;

    /**
     * @brief Opens a file from the memory buffer.
     * @param pFile The path of the file to open.
     * @param pMode The mode in which to open the file.
     * @return A pointer to the opened file stream.
     */
    Assimp::IOStream *Open(const char *pFile, const char *pMode) override;

    /**
     * @brief Closes a file stream.
     * @param pFile A pointer to the file stream to close.
     */
    void Close(Assimp::IOStream *pFile) override;

    /**
     * @brief Sets the asset manager for accessing Android assets.
     * @param mgr A pointer to the asset manager.
     */
    void setAssetManager(AAssetManager *mgr);

    /**
     * @brief Retrieves the asset manager.
     * @return A pointer to the asset manager.
     */
    AAssetManager *getAssetManager() const;

    private:
        std::map<std::string, std::pair<const unsigned char*, size_t>> files; // Map of file paths and their corresponding buffer content
        AAssetManager *_mgr; // Pointer to the asset manager for accessing Android assets
};

#endif /* !MEMORYIOSYSTEM_HPP_ */
