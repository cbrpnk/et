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
        , left{*(buffer_)}
        , right{*(buffer_ + length)}
    {}

public:
    SampleType& left;
    SampleType& right;
};

} // namespace Audio
} // namespace Et

#endif // ET_AUDIO_BUFFER
