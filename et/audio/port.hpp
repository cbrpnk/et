#pragma once

#include <vector>

#include "buffer.hpp"

namespace Et {
namespace Audio {

class Module;
class Buffer;

class Port {
protected:
    
    Port(Module& owner);
    Port(Port&& other);
    
    void connect(Port& target);
    void disconnect(Port& target);

public:
    virtual ~Port() {}
    
    void setSample(Buffer::Channel ch, unsigned int sample, SampleType value);
    SampleType getSample(Buffer::Channel ch, unsigned int sample);
    
    bool isConnected() { return (connections.size() ? true : false); }

public:
    // Who owns us
    Module& owner;
    Buffer buffer;
    std::vector<Port*> connections;
};

} // namepsace Audio
} // namespace Et
