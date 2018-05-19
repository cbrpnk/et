#pragma once

#include "port.hpp"

namespace Et {
namespace Audio {

class MidiOutput;

class MidiInput : public Port
{
public:
    MidiInput(Module& owner) : Port(owner) {}
    MidiInput(MidiInput&& other) : Port(std::move(other)) {}
    
    MidiInput& operator<<(Output& target);
};

}} // namespace Audio::Et
