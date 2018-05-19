#pragma once

#include <atomic>
#include <cstdint>

namespace Et {
namespace Mem {

template<typename T>
class RingBuffer {
public:
    RingBuffer(unsigned int size)
        : size_(size)
        , buff_(size)
    {
        read_.store(0);
        write_.store(0);
    }
    ~RingBuffer() {}
    
    bool push(T element)
    {
        auto pos = write_.load();
        if(pos - read_.load() <= size_-1) {
            buff_[pos%size_] = element;
            write_.store(pos + 1);
            return true;
        }
        return false;
    }
    
    bool pop(T* element)
    {
        auto pos = read_.load();
        if(pos < write_.load()) {
            *element = buff_[pos%size_];
            read_.store(pos+1);
            return true;
        }
        return false;
    }
    
private:
    // number of elements
    unsigned int size_;
    // Read and write position in buff_ will always increment and be modulo with size_
    std::atomic<std::uint64_t> read_;
    std::atomic<std::uint64_t> write_;
    std::vector<T> buff_;
};

} // namespace Mem
} // namespace Et
