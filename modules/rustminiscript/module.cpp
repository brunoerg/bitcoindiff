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
            // Skip some descriptors
            if ((str.find("raw") != std::string::npos) || (str.find("combo") != std::string::npos)) return std::nullopt;
            return rust_miniscript_descriptor_parse(str.c_str());
        }
    }
}
