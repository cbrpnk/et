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
    static constexpr SampleType kDefaultRangeMin = -1.0f;
    static constexpr SampleType kDefaultRangeMax =  1.0f;

public:
    Buffer() = delete;
    Buffer(unsigned int nChannels, unsigned int length,
           SampleType min = kDefaultRangeMin,
           SampleType max = kDefaultRangeMax
           )
        : Mem::Buffer<SampleType>(nChannels * length)
        , nChannels_{nChannels}
        , length_{length}
        , range_{min, max}
    {}
    virtual ~Buffer() {}
    
    Buffer(Buffer&& other)
        : Mem::Buffer<SampleType>(std::move(other))
        , nChannels_{other.nChannels_}
        , length_{other.length_}
        , range_{other.range_}
    {
        other.nChannels_ = 0;
        other.length_    = 0;
    }
    
    Buffer& operator+=(Buffer& other)
    {
        if(size_ == other.size_) {
            for(int i=0; i<size_; ++i) {
                buffer_[i] += other.buffer_[i];
                if(buffer_[i] > range_.max) buffer_[i] = range_.max;
                else if(buffer_[i] < range_.min) buffer_[i] = range_.min;
            }
        }
        return *this;
    }
    
    void set(float v) {
        if(v >= range_.min && v <= range_.max) {
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
    struct Range {
        SampleType min;
        SampleType max;
    };
    const Range range_;
};


///////////////////////////////////////////////////////////////////////////////

class StereoBuffer : public Buffer
{
public:
    StereoBuffer() = delete;
    StereoBuffer(unsigned int length,
                 SampleType min = Buffer::kDefaultRangeMin,
                 SampleType max = Buffer::kDefaultRangeMax
                )
        : Buffer(2, length, min, max)
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
    MonoBuffer(unsigned int length,
               SampleType min = Buffer::kDefaultRangeMin,
               SampleType max = Buffer::kDefaultRangeMax
              )
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
