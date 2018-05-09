#include "module.hpp"

namespace Et {
namespace Audio {

Module::Module(unsigned int sampleRate, size_t bufferSize, size_t nInputs,
               size_t nParameters)
    : on_{true}
    , sampleRate_{sampleRate}
    , bufferSize_{bufferSize}
    , lastSampleId_{0}
    , output_(*this)
{
    inputs_.reserve(nInputs);
    for(size_t i=0; i<nInputs; ++i) {
        inputs_.push_back(std::move(Input(*this)));
    }
    
    params_.reserve(nParameters);
    for(size_t i=0; i<nParameters; ++i) {
        params_.push_back(std::move(Parameter(*this, -1.0f, 1.0f, 0.0f)));
    }
}

void Module::tick(uint64_t upToSampleId)
{
    if(on_ && upToSampleId != lastSampleId_) {
        // We update this as soon as possible because we might be call
        // again before the method is over. Eg: we update an input module
        // that depends on us and therefore will try to call tick on us.
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
        
        process();
    }
}

} // namepsace Audio
} // namespace Et
