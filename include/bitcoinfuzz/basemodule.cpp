#include "basemodule.h"
#include <span>

namespace bitcoinfuzz
{
    BaseModule::~BaseModule() noexcept {} // Ensures vtable for `Module` is created

    std::optional<bool> BaseModule::script_parse(std::span<const uint8_t> buffer) const
    {
        return std::nullopt;
    }

    std::optional<std::vector<bool>> BaseModule::deserialize_block(std::span<const uint8_t> buffer) const
    {
        return std::nullopt;
    }

    std::optional<bool> BaseModule::script_eval(const std::vector<uint8_t>& input_data, unsigned int flags, size_t version) const
    {
        return std::nullopt;
    }

    std::optional<bool> BaseModule::descriptor_parse(const std::string& str) const 
    {
        return std::nullopt;
    }
}
