#include "module.hpp"

namespace Et {
namespace Audio {

Module::Module(unsigned int sampleRate, unsigned int bufferSize, unsigned int nInputs,
               unsigned int nParameters)
    : on_{true}
    , bypass_{false}
    , sampleRate_{sampleRate}
    , bufferSize_{bufferSize}
    , lastSampleId_{0}
    , output_(*this)
{
    inputs_.reserve(nInputs);
    for(unsigned int i=0; i<nInputs; ++i) {
        inputs_.push_back(std::move(Input(*this)));
    }
    
    params_.reserve(nParameters);
    for(unsigned int i=0; i<nParameters; ++i) {
        params_.push_back(std::move(Parameter(*this, { 0.0f, 1.0f }, 0.0f)));
    }
}

void Module::process(uint64_t upToSampleId)
{
    if(on_ && upToSampleId != lastSampleId_) {
        // We update this as soon as possible because we might be call
        // again before the method is over. Eg: we update an input module
        // that depends on us and therefore will try to call process on us.
        // To prevent infinite loops we update this now so we won't get into
        // this if statement if called later.
        lastSampleId_ = upToSampleId;
        
        for(auto& input : inputs_) {
            if(input.isConnected()) input.update(upToSampleId);
        }
        
        // TODO
        //for(auto& param : params_) {
        //  if(param.isAutomated()) {
        //      param.update(upToSampleId);
        //  }
        //}
        
        // TODO Better name perhaps generateBuffer or something
        doDsp();
    }
}

void Module::toggleOnOff()
{
    if(on_) {
        on_ = false;
        output_.buffer.silence();
    } else {
        on_ = true;
    }
}

void Module::ToggleBypass()
{
    if(bypass_) {
        bypass_ = false;
    } else bypass_ = true;
}

} // namepsace Audio
} // namespace Et
