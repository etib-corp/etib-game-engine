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

class MemoryIOStream : public Assimp::IOStream {
    public:
        MemoryIOStream(const unsigned char* buffer, size_t length)
        : buffer(buffer), length(length), pos(0) {
            __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Creating MemoryIOStream\n");
        }

        ~MemoryIOStream() = default;

        size_t Read(void* outBuffer, size_t size, size_t count) override;

        size_t Write(const void* buffer, size_t size, size_t count) override;

        aiReturn Seek(size_t offset, aiOrigin origin) override;

        size_t Tell() const override;

        size_t FileSize() const override;

        void Flush() override;

    private:
        const unsigned char* buffer;
        size_t length;
        size_t pos;
        AAssetManager *_mgr;

    protected:
};

#endif /* !MEMORYIOSTREAM_HPP_ */
