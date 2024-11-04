#include "basemodule.h"
#include <span>

namespace bitcoinfuzz
{
    BaseModule::~BaseModule() noexcept {} // Ensures vtable for `Module` is created

    std::optional<bool> BaseModule::script_parse(std::span<const uint8_t> buffer) const
    {
        return std::nullopt;
    }
}
