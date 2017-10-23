#include "module.hpp"

namespace Et {
namespace Audio {

void Module::process(uint64_t upToSampleId)
{
    if(on_ && upToSampleId != lastSampleId_) {
        // We update this as soon as possible because we might be call
        // again before the method is over. Eg: we update an input module
        // that depends on us and therefore will try to call process on us.
        // To prevent infinite loops we update this now so we won't get into
        // this if statement if called later.
        lastSampleId_ = upToSampleId;
        
        // TODO: Update Inputs
        // TODO: Update parameter modulators
        
        doDsp();
    }
}

void Module::recvInput()
{}

void Module::sendOutput()
{}

void Module::toggleOnOff()
{
    if(on_) {
        on_ = false;
        for(auto& output : outputs_) {
            output.buffer.silence();
        }
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
