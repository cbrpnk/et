#pragma once
#ifndef ET_AUDIO_SAMPLE_BUFFER_HPP
#define ET_AUDIO_SAMPLE_BUFFER_HPP

#include <memory>
#include <cstring>

namespace Et {
namespace Audio {

template<typename T>
class SampleBuffer {
public:
    SampleBuffer() : size_{0}, buffer_{nullptr} {}
    
    SampleBuffer(int size_) :
        size_{size_},
        buffer_{new T[size_]}
    {
        clear();
    }
    
    SampleBuffer(const SampleBuffer& other) :
        size_{other.size_},
        buffer_{new T[other.size_]}
    {
        std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
    }
    
    SampleBuffer(SampleBuffer&& other) noexcept :
        size_{other.size_},
        buffer_{other.buffer_}
    {
        other.size_ = 0;
        other.buffer_ = nullptr;
    }
    
    ~SampleBuffer() { delete[] buffer_; }
    
    SampleBuffer& operator=(const SampleBuffer& other)
    {
        if(this != &other) {
            if(other.size_ != size_) {
                delete[] buffer_;
                // Setup a sain object in case the memory allocation throws
                buffer_ = nullptr;
                size_ = 0;
                buffer_ = new T[other.size_];
                size_ = other.size_;
            }
            std::copy(other.buffer_, other.buffer_ + size_, buffer_);
        }
        return *this;
    }
    
    SampleBuffer& operator=(SampleBuffer&& other) noexcept
    {
        size_ = other.size_;
        buffer_ = other.buffer_;
        other.size_ = 0;
        other.buffer_ = nullptr;
    }
    
    // This is the way a client access individual sampels
    T& operator[](int index)          { return buffer_[index]; }
    
    SampleBuffer& operator+=(const T scalar)
    {
        for(int i=0; i<size_; ++i) {
            *(buffer_ + i) += scalar;
        }
        return *this;
    }
    
    SampleBuffer& operator+=(const SampleBuffer other)
    {
        if(other.size_ == size_) {
            for(int i=0; i<size_; ++i) {
                *(buffer_ + i) += *(other.buffer_ + i);
            }
        }
        return *this;
    }
    
    SampleBuffer& operator-=(const T scalar)
    {
        for(int i=0; i<size_; ++i) {
            *(buffer_ + i) -= scalar;
        }
        return *this;
    }
    
    SampleBuffer& operator-=(const SampleBuffer other)
    {
        if(other.size_ == size_) {
            for(int i=0; i<size_; ++i) {
                *(buffer_ + i) -= *(other.buffer_ + i);
            }
        }
        return *this;
    }
    
    SampleBuffer& operator*=(const T scalar)
    {
        for(int i=0; i<size_; ++i) {
            *(buffer_ + i) *= scalar;
        }
        return *this;
    }
    
    SampleBuffer& operator*=(const SampleBuffer other)
    {
        if(other.size_ == size_) {
            for(int i=0; i<size_; ++i) {
                *(buffer_ + i) *= *(other.buffer_ + i);
            }
        }
        return *this;
    }
    
    SampleBuffer& operator/=(const T scalar)
    {
        for(int i=0; i<size_; ++i) {
            *(buffer_ + i) /= scalar;
        }
        return *this;
    }
    
    SampleBuffer& operator/=(const SampleBuffer other)
    {
        if(other.size_ == size_) {
            for(int i=0; i<size_; ++i) {
                *(buffer_ + i) /= *(other.buffer_ + i);
            }
        }
        return *this;
    }
    
    SampleBuffer operator+(const T scalar) const
    {
        SampleBuffer tmp(*this);
        tmp += scalar;
        return tmp;
    }
    
    SampleBuffer operator+(const SampleBuffer& other) const
    {
        SampleBuffer tmp(*this);
        tmp += other;
        return tmp;
    }
    
    SampleBuffer operator-(const T scalar) const
    {
        SampleBuffer tmp(*this);
        tmp -= scalar;
        return tmp;
    }
    
    SampleBuffer operator-(const SampleBuffer& other) const
    {
        SampleBuffer tmp(*this);
        tmp -= other;
        return tmp;
    }
    
    SampleBuffer operator*(const T scalar) const
    {
        SampleBuffer tmp(*this);
        tmp *= scalar;
        return tmp;
    }
    
    SampleBuffer operator*(const SampleBuffer& other) const
    {
        SampleBuffer tmp(*this);
        tmp *= other;
        return tmp;
    }
    
    SampleBuffer operator/(const T scalar) const
    {
        SampleBuffer tmp(*this);
        tmp /= scalar;
        return tmp;
    }
    
    SampleBuffer operator/(const SampleBuffer& other) const
    {
        SampleBuffer tmp(*this);
        tmp /= other;
        return tmp;
    }
    
    void clear()         { std::memset(buffer_, 0, size_ * sizeof(T)); }
    int  getSize() const { return size_; }

private:
    int size_;
    T* buffer_;
};

} // namespace Audio
} // namespace Et

#endif
