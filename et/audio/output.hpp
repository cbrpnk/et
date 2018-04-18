#pragma once

#include "port.hpp"

namespace Et {
namespace Audio {

class Input;

class Output : public Port {
public:
    Output(Module& owner) : Port(owner) {}
    Output(Output&& other) : Port(std::move(other)) {}
    
    Output& operator>>(Input& target);
    
    void connect(Input& target);
    void disonnect(Input& target);
};

} // namepsace Audio
} // namespace Et
