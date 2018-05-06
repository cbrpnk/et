#include "output.hpp"
#include "input.hpp"

namespace Et {
namespace Audio {

Output& Output::operator>>(Input& target)
{
    Port::connect(target);
    return *this;
}

void Output::connect(Input& target)
{
    Port::connect(target);
}

void Output::disonnect(Input& target)
{
    Port::disconnect(target);
}

} // namepsace Audio
} // namespace Et
