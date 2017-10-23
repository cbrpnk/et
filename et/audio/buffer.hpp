#pragma once
#ifndef ET_AUDIO_BUFFER_HPP
#define ET_AUDIO_BUFFER_HPP

#include <memory>
#include <cstring>
#include <iostream>

#include "../mem/buffer.hpp"

namespace Et {
namespace Audio {

// TODO: Put this in config
typedef float SampleType;


///////////////////////////////////////////////////////////////////////////////
class Buffer : public Mem::Buffer<SampleType>
{
public:
    enum Channel {
        Left  = 0,
        Right = 1
    };
public:
    Buffer() = delete;
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
        // TODO Assert
        if(size_ == other.size_) {
            for(int i=0; i<size_; ++i) {
                buffer_[i] += other.buffer_[i];
                if(buffer_[i] > 1.0f) buffer_[i] = 1.0f;
                else if(buffer_[i] < -1.0f) buffer_[i] = -1.0f;
            }
        }
        return *this;
    }
    
    SampleType getSample(Channel ch, int sample)
    {
        // TODO Assert
        if(ch >= 0 && ch <= nChannels_ && sample >=0 && sample <= length_) {
            return buffer_[ch * length_ + sample];
        }
    }
    
    void setSample(Channel ch, int sample, SampleType value)
    {
        // TODO Assert
        if(ch >= 0 && ch <= nChannels_ && sample >=0 && sample <= length_) {
            if(value >= -1.0f && value <= 1.0f) {
                buffer_[ch * length_ + sample] = value;
            }
        }
    }
    
    void set(float v) {
        // TODO assert
        if(v >= -1.0f && v <= 1.0f) {
            for(int i=0; i<size_; ++i) buffer_[i] = v;
        }
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


///////////////////////////////////////////////////////////////////////////////


// TODO Maybe delete Seteo and Mono buffer and simply use Buffer

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
    
    // TODO operator+= MonoBuffer
    
    StereoBuffer(StereoBuffer&& other)
        : Buffer(std::move(other))
        , left{other.left}
        , right{other.right}
    {}

public:
    SampleType* left;
    SampleType* right;
};


///////////////////////////////////////////////////////////////////////////////


class MonoBuffer : public Buffer
{
public:
    MonoBuffer() = delete;
    MonoBuffer(unsigned int length)
        : Buffer(1, length)
        // The two channels point to the same location in memory
        , left{buffer_}
        , right{buffer_}
    {}
    
    // TODO operator+= StereoBuffer
    
    MonoBuffer(MonoBuffer&& other)
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
