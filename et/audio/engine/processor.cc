#include "processor.hpp"

namespace Et {
namespace Audio {

////////////////////////////////////////////////////////////////////////////////


void Processor::AudioPort::connect(AudioPort& target, float scalar)
{}

void Processor::AudioPort::disconnect(AudioPort& target)
{}


////////////////////////////////////////////////////////////////////////////////


void Processor::AudioInput::update()
{}


////////////////////////////////////////////////////////////////////////////////


void Processor::Parameter::update()
{}


////////////////////////////////////////////////////////////////////////////////


void Processor::process(uint64_t upToSampleId)
{
    if(on_) {
    // TODO if upToSampleId != lastSampleId
        // TODO: Update Inputs
        // TODO: Update parameter modulators
        doDsp();
    }
}

void Processor::recvInput()
{}

void Processor::sendOutput()
{}

void Processor::modulateParameter()
{}

void Processor::toggleOnOff()
{
    if(on_) {
        on_ = false;
        for(auto& output : audioOutputs_) {
            output.buffer_.silence();
        }
    } else {
        on_ = true;
    }
}

void Processor::bypass() 
{}

} // namepsace Audio
} // namespace Et
