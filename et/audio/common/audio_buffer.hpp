#pragma once
#ifndef ET_AUDIO_AUDIO_BUFFER_HPP
#define ET_AUDIO_AUDIO_BUFFER_HPP

#include <memory>
#include <cstring>

namespace Et {
namespace Audio {

template<typename T, int N_CHANNELS>
struct Sample {
    T value[N_CHANNELS];
};

template<typename T>
class AudioBuffer {
public:
    enum Type {
        kMono   = 1,
        kStereo = 2
    };
    
    enum Channel {
        kLeft  = 0,
        kRight = 1
    };
    

public:
    AudioBuffer() :
        nChannels_{0},
        length_{0},
        bufferSize_{0},
        buffer_{nullptr}
    {}
    
    AudioBuffer(int nChannels, int length) :
        nChannels_{nChannels},
        length_{length},
        bufferSize_{nChannels_ * length},
        buffer_{new T[bufferSize_]}
    {
        silence();
    }
    
    AudioBuffer(const AudioBuffer& other) :
        nChannels_{other.nChannels_},
        length_{other.length_},
        bufferSize_{other.bufferSize_},
        buffer_{new T[other.bufferSize_]}
    {
        std::copy(other.buffer_, other.buffer_ + other.bufferSize_, buffer_);
    }
    
    AudioBuffer(AudioBuffer&& other) noexcept :
        nChannels_{other.nChannels_},
        length_{other.length_},
        bufferSize_{other.bufferSize_},
        buffer_{other.buffer_}
    {
        other.nChannels_  = 0;
        other.length_     = 0;
        other.bufferSize_ = 0;
        other.buffer_     = nullptr;
    }
    
    ~AudioBuffer() { delete[] buffer_; }
    
    AudioBuffer& operator=(const AudioBuffer& other)
    {
        if(this != &other) {
            if(other.bufferSize_ != bufferSize_) {
                delete[] buffer_;
                // Puts the object in a sain state in case
                // the memory allocation throws
                buffer_     = nullptr;
                bufferSize_ = 0;
                // Setup buffer
                buffer_     = new T[other.bufferSize_];
                bufferSize_ = other.bufferSize_;
            }
            nChannels_ = other.nChannels_;
            length_    = other.length_;
            std::copy(other.buffer_, other.buffer_ + other.bufferSize_,
                      buffer_);
        }
        return *this;
    }
    
    AudioBuffer& operator=(AudioBuffer&& other) noexcept
    {
        nChannels_    = other.nChannels_;
        length_       = other.length_;
        bufferSize_   = other.bufferSize_;
        buffer_       = other.buffer_;
        other.size_   = 0;
        other.buffer_ = nullptr;
    }
    
    // This is the way a client access individual sampels
    //T& operator()(Channel ch, int index) {
    //    return buffer_[index*nChannels_ + ch];
    //}
    
    /*
    AudioBuffer& operator+=(const T scalar)
    {
        for(int i=0; i<nChannels_*size_; ++i) {
            *(buffer_ + i) += scalar;
        }
        return *this;
    }
    
    AudioBuffer& operator+=(const AudioBuffer other)
    {
        for(int i=0; i<nChannels_ * size_; ++i) {
            *(buffer_ + i) += *(other.buffer_ + i);
        }
        return *this;
    }
    */
    
    /* TODO
    AudioBuffer& operator-=(const T scalar)
    {
        for(int i=0; i<size_; ++i) {
            *(buffer_ + i) -= scalar;
        }
        return *this;
    }
    
    AudioBuffer& operator-=(const AudioBuffer other)
    {
        if(other.size_ == size_) {
            for(int i=0; i<size_; ++i) {
                *(buffer_ + i) -= *(other.buffer_ + i);
            }
        }
        return *this;
    }
    
    AudioBuffer& operator*=(const T scalar)
    {
        for(int i=0; i<size_; ++i) {
            *(buffer_ + i) *= scalar;
        }
        return *this;
    }
    
    AudioBuffer& operator*=(const AudioBuffer other)
    {
        if(other.size_ == size_) {
            for(int i=0; i<size_; ++i) {
                *(buffer_ + i) *= *(other.buffer_ + i);
            }
        }
        return *this;
    }
    
    AudioBuffer& operator/=(const T scalar)
    {
        for(int i=0; i<size_; ++i) {
            *(buffer_ + i) /= scalar;
        }
        return *this;
    }
    
    AudioBuffer& operator/=(const AudioBuffer other)
    {
        if(other.size_ == size_) {
            for(int i=0; i<size_; ++i) {
                *(buffer_ + i) /= *(other.buffer_ + i);
            }
        }
        return *this;
    }
    
    AudioBuffer operator+(const T scalar) const
    {
        AudioBuffer tmp(*this);
        tmp += scalar;
        return tmp;
    }
    
    AudioBuffer operator+(const AudioBuffer& other) const
    {
        AudioBuffer tmp(*this);
        tmp += other;
        return tmp;
    }
    
    AudioBuffer operator-(const T scalar) const
    {
        AudioBuffer tmp(*this);
        tmp -= scalar;
        return tmp;
    }
    
    AudioBuffer operator-(const AudioBuffer& other) const
    {
        AudioBuffer tmp(*this);
        tmp -= other;
        return tmp;
    }
    
    AudioBuffer operator*(const T scalar) const
    {
        AudioBuffer tmp(*this);
        tmp *= scalar;
        return tmp;
    }
    
    AudioBuffer operator*(const AudioBuffer& other) const
    {
        AudioBuffer tmp(*this);
        tmp *= other;
        return tmp;
    }
    
    AudioBuffer operator/(const T scalar) const
    {
        AudioBuffer tmp(*this);
        tmp /= scalar;
        return tmp;
    }
    
    AudioBuffer operator/(const AudioBuffer& other) const
    {
        AudioBuffer tmp(*this);
        tmp /= other;
        return tmp;
    }
    */
    
    void silence() { std::memset(buffer_, 0, bufferSize_ * sizeof(T)); }
    
    bool isMono()   const { if(nChannels_ == 1) return true; return false; }
    bool isStereo() const { if(nChannels_ == 2) return true; return false; }
    
    int getChannelCount()        const { return nChannels_; }
    int getLength()              const { return length_; }
    int getBufferSize()          const { return bufferSize_; }
    T*  getBuffer()              const { return buffer_; }
    T&  getSample(int ch, int i) const { return buffer_[i*nChannels_ + ch]; }

private:
    int nChannels_;
    // How many smaples per channel
    int length_;
    
    //
    // Channels are interleaved in memory to maximize cache coherency.
    // Here is an exemple of the memory layout for 2 channels
    //
    // *-------------*-------------*-------------*-------------*-------------*
    // | Ch0 Sample0 | Ch1 Sample0 | Ch0 Sample1 | Ch1 Sample1 |     ...     |
    // *-------------*-------------*-------------*-------------*-------------*
    //
    //
    int bufferSize_;
    T* buffer_;
};

} // namespace Audio
} // namespace Et

#endif // ET_AUDIO_AUDIO_BUFFER
