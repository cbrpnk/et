#include "input.hpp"
#include "buffer.hpp"
#include "output.hpp"
#include "module.hpp"

namespace Et {
namespace Audio {

Input& Input::operator<<(Output& target)
{
    Port::connect(target);
    return *this;
}

void Input::update(uint64_t sampleId)
{
    buffer.silence();
    for(auto& connection : connections) {
        Output& output{ static_cast<Output&>(*connection) };
        output.owner.tick(sampleId);
        buffer += output.buffer;
    }
}

void Input::connect(Output& target)
{
    Port::connect(target);
}

void Input::disonnect(Output& target)
{
    Port::disconnect(target);
}

} // namepsace Audio
} // namespace Et
