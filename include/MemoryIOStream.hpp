/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** MemoryIOStream
*/

#ifndef MEMORYIOSTREAM_HPP_
    #define MEMORYIOSTREAM_HPP_

#include <assimp/IOStream.hpp>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

/**
 * @brief A custom IOStream implementation for reading from and writing to memory buffers.
 */
class MemoryIOStream : public Assimp::IOStream {
    public:
        /**
         * @brief Constructs a MemoryIOStream object with the given buffer and length.
         *
         * @param buffer The memory buffer to read from or write to.
         * @param length The length of the memory buffer.
         */
        MemoryIOStream(const unsigned char* buffer, size_t length)
        : buffer(buffer), length(length), pos(0) {
        }

        /**
         * @brief Default destructor.
         */
        ~MemoryIOStream() = default;

        /**
         * @brief Reads data from the memory buffer.
         *
         * @param outBuffer Pointer to the buffer where the read data will be stored.
         * @param size Size of each element to be read.
         * @param count Number of elements to read.
         * @return The total number of elements successfully read.
         */
        size_t Read(void* outBuffer, size_t size, size_t count) override;

        /**
         * @brief Writes data to the memory buffer.
         *
         * @param buffer Pointer to the buffer containing the data to be written.
         * @param size Size of each element to be written.
         * @param count Number of elements to write.
         * @return The total number of elements successfully written.
         */
        size_t Write(const void* buffer, size_t size, size_t count) override;

        /**
         * @brief Sets the position indicator of the memory buffer.
         *
         * @param offset Number of bytes to offset from the specified origin.
         * @param origin Position used as reference for the offset.
         * @return aiReturn_SUCCESS if the operation was successful, otherwise an error code.
         */
        aiReturn Seek(size_t offset, aiOrigin origin) override;

        /**
         * @brief Returns the current position indicator of the memory buffer.
         *
         * @return The current position indicator.
         */
        size_t Tell() const override;

        /**
         * @brief Returns the size of the memory buffer.
         *
         * @return The size of the memory buffer.
         */
        size_t FileSize() const override;

        /**
         * @brief Flushes any buffered data to the memory buffer.
         */
        void Flush() override;

    private:
        const unsigned char* buffer; /**< The memory buffer. */
        size_t length; /**< The length of the memory buffer. */
        size_t pos; /**< The current position indicator. */
        AAssetManager *_mgr; /**< The asset manager. */

    protected:
};

#endif /* !MEMORYIOSTREAM_HPP_ */
