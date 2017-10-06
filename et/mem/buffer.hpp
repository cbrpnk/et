#pragma once
#ifndef ET_MEM_BUFFER_HPP
#define ET_MEM_BUFFER_HPP

#include <memory>
#include <cstring>

namespace Et {
namespace Mem {

template<typename T>
class Buffer {
public:
    Buffer()
        : size_{0}
        , buffer_{nullptr}
    {}
    
    Buffer(int size)
        : size_{size}
        , buffer_{new T[size]}
    {}
    
    Buffer(const Buffer& other)
        : size_{other.size_}
        , buffer_{new T[other.size_]}
    {
        std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
    }
    
    Buffer(Buffer&& other) noexcept
        : size_{other.size_}
        , buffer_{other.buffer_}
    {
        other.size_   = 0;
        other.buffer_ = nullptr;
    }
    
    ~Buffer() { delete[] buffer_; }
    
    Buffer& operator=(const Buffer& other)
    {
        if(this != &other) {
            if(other.size_ != size_) {
                delete[] buffer_;
                // Puts the object in a sain state in case
                // the memory allocation throws
                buffer_ = nullptr;
                size_   = 0;
                // Setup buffer
                buffer_ = new T[other.size_];
                size_   = other.size_;
            }
            std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
        }
        return *this;
    }
    
    Buffer& operator=(Buffer&& other) noexcept
    {
        size_         = other.size_;
        buffer_       = other.buffer_;
        other.size_   = 0;
        other.buffer_ = nullptr;
    }
    
    int getSize()          const { return size_; }
    T*  getRawBuffer()     const { return buffer_; }

private:
    int size_;
    T* buffer_;
};

} // namespace Mem
} // namespace Et

#endif // ET_MEM_BUFFER
