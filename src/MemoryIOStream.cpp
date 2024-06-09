/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** MemoryIOStream
*/

#include "MemoryIOStream.hpp"

size_t MemoryIOStream::Read(void *pvBuffer, size_t pSize, size_t pCount)
{
    __android_log_print(ANDROID_LOG_INFO, "MYTAG", "Reading %d bytes\n", pSize * pCount);
    size_t toRead = pSize * pCount;
    if (this->pos + toRead > this->length)
        toRead = this->length - this->pos;
    memcpy(pvBuffer, this->buffer + this->pos, toRead);
    this->pos += toRead;
    return toRead / pSize;
}

size_t MemoryIOStream::Write(const void *pvBuffer, size_t pSize, size_t pCount)
{
    return 0;
}

aiReturn MemoryIOStream::Seek(size_t pOffset, aiOrigin pOrigin)
{
    size_t newPos = 0;

    switch (pOrigin) {
    case aiOrigin_SET:
        newPos = pOffset;
        break;
    case aiOrigin_CUR:
        newPos = this->pos + pOffset;
        break;
    case aiOrigin_END:
        newPos = this->length + pOffset;
        break;
    default:
        break;
    }
    if (newPos > this->length)
        return aiReturn_FAILURE;
    this->pos = newPos;
    return aiReturn_SUCCESS;
}

size_t MemoryIOStream::Tell() const
{
    return this->pos;
}

size_t MemoryIOStream::FileSize() const
{
    return this->length;
}

void MemoryIOStream::Flush()
{
}

