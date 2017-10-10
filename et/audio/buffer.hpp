#pragma once
#ifndef ET_AUDIO_BUFFER_HPP
#define ET_AUDIO_BUFFER_HPP

#include <memory>
#include <cstring>

#include "../mem/buffer.hpp"

namespace Et {
namespace Audio {

// TODO: Put this in config
typedef float SampleType;


///////////////////////////////////////////////////////////////////////////////
class Buffer : public Mem::Buffer<SampleType>
{
public:
    Buffer() = delete;
    Buffer(unsigned int nChannels, unsigned int length)
        : Mem::Buffer<SampleType>(nChannels * length)
        , nChannels_{nChannels}
        , length_{length}
    {}
    virtual ~Buffer() {}
    
    Buffer(Buffer&& other)
        : Mem::Buffer<SampleType>(std::move(other))
        , nChannels_{other.nChannels_}
        , length_{other.length_}
    {
        other.nChannels_ = 0;
        other.length_    = 0;
    }
    
    Buffer& operator+=(Buffer& other)
    {
        if(size_ == other.size_) {
            for(int i=0; i<size_; ++i) {
                buffer_[i] += other.buffer_[i];
            }
        }
        return *this;
    }
    
    void silence() { for(int i=0; i<size_; ++i) buffer_[i] = 0.0f; }
    void normalize() {
        for(int i=0; i<size_; ++i ) {
            if(buffer_[i] < -1.0f) buffer_[i] = -1.0f;
            else if(buffer_[i] > 1.0f) buffer_[i] = 1.0f;
        }
    }
    
    unsigned int getChannelCount() const { return nChannels_; }
    unsigned int getLength()       const { return length_; }
    
protected:
    unsigned int nChannels_;
    // Size of a single channel, to know the size of the actual buffer, refer
    // to Mem::Buffer.size_;
    unsigned int length_;
};


///////////////////////////////////////////////////////////////////////////////

class StereoBuffer : public Buffer
{
public:
    StereoBuffer() = delete;
    StereoBuffer(unsigned int length)
        : Buffer(2, length)
        // The two channels will be layed side by side in memory
        , left{buffer_}
        , right{buffer_ + length}
    {}
    
    StereoBuffer(StereoBuffer&& other)
        : Buffer(std::move(other))
        , left{other.left}
        , right{other.right}
    {}

public:
    SampleType* left;
    SampleType* right;
};

} // namespace Audio
} // namespace Et

#endif // ET_AUDIO_BUFFER
