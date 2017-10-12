#include "processor.hpp"

namespace Et {
namespace Audio {

////////////////////////////////////////////////////////////////////////////////


void Processor::AudioPort::connect(AudioPort& target, float scalar)
{}

void Processor::AudioPort::disconnect(AudioPort& target)
{}


////////////////////////////////////////////////////////////////////////////////


void Processor::AudioInput::update(uint64_t sampleId)
{
    buffer_.silence();
    for(auto& connection : connections_) {
        Processor::AudioOutput& output{
            static_cast<Processor::AudioOutput&>(connection.port)
        };
        connection.port.owner_.process(sampleId);
        buffer_ += output.buffer_;
    }
}


////////////////////////////////////////////////////////////////////////////////


void Processor::Parameter::update(uint64_t sampleId)
{
    if(connections_.size()) {
        // Sum inputs
        for(auto& connection : connections_) {
            Processor::AudioOutput& output{
                static_cast<Processor::AudioOutput&>(connection.port)
            };
            connection.port.owner_.process(sampleId);
            buffer_ += output.buffer_;
        }
        
        // Populate scaledBuffer_
        for(int i=0; i<owner_.bufferSize_; ++i) {
            // TODO Scaling calculation
            //scaledBuffer_[i] = 
        }
    } else {
        buffer_.set(value_);
    }
}

void Processor::Parameter::set(float value) {
    if(value < range.min) value_ = range.min;
    else if(value > range.max) value_ = range.max;
    else value_ = value;
}


////////////////////////////////////////////////////////////////////////////////


void Processor::process(uint64_t upToSampleId)
{
    if(on_ && upToSampleId != lastSampleId_) {
        // We update this as soon as possible because we might be call
        // again before the method is over. Eg: we update an input processor
        // that depends on us and therefore will try to call process on us.
        // To prevent infinite loops we update this now so we won't get into
        // this if statement if called later.
        lastSampleId_ = upToSampleId;
        
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

void Processor::ToggleBypass()
{
    if(bypass_) {
        bypass_ = false;
    } else bypass_ = true;
}

} // namepsace Audio
} // namespace Et
