#pragma once

#include <memory>
#include <cstring>

namespace Et {
namespace Mem {

template<typename T>
class Buffer {
public:
    Buffer() {}
    
    Buffer(size_t size)
    {
        alloc(size);
    }
    
    Buffer(const Buffer& other)
        : allocated_{true}
        , size_{other.size_}
        , buffer_{new T[other.size_]()}
    {
        std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
    }
    
    Buffer(Buffer&& other) noexcept
        : allocated_{other.allocated_}
        , size_{other.size_}
        , buffer_{other.buffer_}
    {
        other.size_   = 0;
        other.buffer_ = nullptr;
    }
    
    virtual ~Buffer() { delete[] buffer_; }
    
    void alloc(size_t size) {
        if(!allocated_) {
            size_ = size;
            buffer_ = new T[size]();
            allocated_ = true;
        }
    }
    
    Buffer& operator=(const Buffer& other)
    {
        if(this != &other) {
            if(other.allocated_ && allocated_ && other.size_ != size_) {
                delete[] buffer_;
                // Puts the object in a sain state in case
                // the memory allocation throws
                buffer_ = nullptr;
                size_   = 0;
                // Setup buffer
                buffer_ = new T[other.size_]();
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
    
    bool operator==(Buffer& other) { return this == &other; }
    
    bool isAllocated()      const { return allocated_; }
    int  getSize()          const { return size_; }
    T*   getRawBuffer()     const { return buffer_; }

protected:
    bool allocated_ = false;
    size_t size_ = 0;
    T* buffer_ = nullptr;
};

} // namespace Mem
} // namespace Et
