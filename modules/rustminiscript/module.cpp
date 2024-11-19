#include <span>

#include "module.h"

extern "C" bool rust_miniscript_descriptor_parse(const char* input);

namespace bitcoinfuzz
{
    namespace module
    {
        Rustminiscript::Rustminiscript(void) : BaseModule("Rustminiscript") {}

        std::optional<bool> Rustminiscript::descriptor_parse(std::string str) const
        {
            return rust_miniscript_descriptor_parse(str.c_str());
        }
    }
}
