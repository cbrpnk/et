#pragma once

#include "port.hpp"

namespace Et {
namespace Audio {

class Output;

class Input : public Port
{
public:
    Input(Module& owner) : Port(owner) {}
    Input(Input&& other) : Port(std::move(other)) {}
    
    Input& operator<<(Output& target);
    
    // Sum connection buffers into our own buffer
    void update(uint64_t sampleId);
    void connect(Output& target);
    void disonnect(Output& target);
};

} // namepsace Audio
} // namespace Et
