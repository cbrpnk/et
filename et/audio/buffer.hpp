#pragma once

#include <memory>
#include <cstring>
#include <iostream>
#include <cassert>

#include "mem/buffer.hpp"

namespace Et {
namespace Audio {

// TODO: Put this in config
typedef float SampleType;

///////////////////////////////////////////////////////////////////////////////
class Buffer : public Mem::Buffer<SampleType>
{
public:
    enum Type {
        Mono = 1,
        Stereo = 2
    };
    
    enum Channel {
        Left  = 0,
        Right = 1
    };
public:
    Buffer();
    Buffer(unsigned int nChannels, unsigned int length)
        : Mem::Buffer<SampleType>(nChannels * length) // Channels are layed side-by-side
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
        assert(size_ == other.size_);
        for(unsigned int i=0; i<size_; ++i) {
            buffer_[i] += other.buffer_[i];
            if(buffer_[i] > 1.0f) buffer_[i] = 1.0f;
            else if(buffer_[i] < -1.0f) buffer_[i] = -1.0f;
        }
        return *this;
    }
    
    Buffer& operator*=(float scalar)
    {
        for(unsigned int i=0; i<size_; ++i) {
            buffer_[i] *= scalar;
        }
        return *this;
    }
    
    SampleType getSample(Channel ch, unsigned int sample)
    {
        assert(ch >= 0 && ch <= nChannels_ && sample >=0 && sample <= length_);
        return buffer_[ch * length_ + sample];
    }
    
    SampleType* getChannel(Channel ch)
    {
        return buffer_ + ch * length_;
    }
    
    void setSample(Channel ch, unsigned int sample, SampleType value)
    {
        assert(ch >= 0 && ch <= nChannels_ && sample >=0 && sample <= length_);
        if(value >= -1.0f && value <= 1.0f) {
            buffer_[ch * length_ + sample] = value;
        }
    }
    
    void set(float v) {
        assert(v >= -1.0f && v <= 1.0f);
        for(unsigned int i=0; i<size_; ++i) buffer_[i] = v;
    }
    void silence() { set(0.0f); }
    
    unsigned int getChannelCount() const { return nChannels_; }
    unsigned int getLength()       const { return length_; }
    
protected:
    unsigned int nChannels_;
    // Size of a single channel, to know the size of the actual buffer, refer
    // to Mem::Buffer.size_;
    unsigned int length_;
};


} // namespace Audio
} // namespace Et
