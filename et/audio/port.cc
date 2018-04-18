#include "port.hpp"
#include "module.hpp"
#include "buffer.hpp"

namespace Et {
namespace Audio {
    
Port::Port(Module& owner)
    : owner{owner}
    , buffer(Buffer::Type::Stereo, owner.getBufferSize())
{}

Port::Port(Port&& other)
    : owner{other.owner}
    , buffer(std::move(other.buffer))
    , connections(std::move(other.connections))
{}
    
void Port::connect(Port& target)
{
    connections.push_back(&target);
    target.connections.push_back(this);
}

void Port::disconnect(Port& target)
{
    // TODO
}

void Port::setSample(Buffer::Channel ch, unsigned int sample, SampleType value)
{
    buffer.setSample(ch, sample, value);
}

SampleType Port::getSample(Buffer::Channel ch, unsigned int sample)
{
    return buffer.getSample(ch, sample);
}

} // namepsace Audio
} // namespace Et