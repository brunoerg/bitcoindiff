#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <span>

namespace bitcoinfuzz
{
    class BaseModule
    {
    public:
        const std::string name;

        BaseModule(const std::string &name) : name(name) {}

        virtual std::optional<bool> script_parse(std::span<const uint8_t> buffer) const;
        virtual std::optional<std::vector<bool>> deserialize_block(std::span<const uint8_t> buffer) const;

        virtual ~BaseModule() noexcept;
    };
}
