#include <cassert>
#include <set>
#include <algorithm>
#include <unistd.h>
#include <string>
#include <span>
#include <fuzzer/FuzzedDataProvider.h>

#include "driver.h"
#include <bitcoinfuzz/basemodule.h>

namespace bitcoinfuzz
{
    void Driver::LoadModule(std::shared_ptr<BaseModule> module)
    {
        modules[module->name] = module;
    }

    void Driver::ScriptTarget(std::span<const uint8_t> buffer) const
    {
        std::optional<bool> last_response{std::nullopt};
        for (auto& module : modules)
        {
            std::optional<bool> res{module.second->script_parse(buffer)};
            if (!res.has_value()) continue;
            if (last_response.has_value()) assert(*res == *last_response);
            last_response = *res;
        }
    }

    void Driver::BlockDeserializationTarget(std::span<const uint8_t> buffer) const
    {
        std::optional<std::vector<bool>> last_response{std::nullopt};
        for (auto& module : modules)
        {
            std::optional<std::vector<bool>> res{module.second->deserialize_block(buffer)};
            if (!res.has_value() || res->empty()) continue;
            if (last_response.has_value()) assert(*res == *last_response);
            last_response = res.value();
        }
    }

    void Driver::ScriptEvalTarget(std::span<const uint8_t> buffer) const 
    {
        FuzzedDataProvider provider(buffer.data(), buffer.size());
        std::vector<uint8_t> input_data = provider.ConsumeBytes<uint8_t>(
            provider.ConsumeIntegralInRange<size_t>(0, 1024)
        );

        auto flags = provider.ConsumeIntegral<unsigned int>();
        auto version = provider.ConsumeIntegralInRange<size_t>(0, 1);
        if (flags & (1U << 16)) return;
        // Skip if flags are not in conformity.
        if (flags & 256 && ~flags & (1 | 2048)) return;
        if (flags & 2048 && ~flags & 1) return;

        std::optional<bool> last_response{std::nullopt};
        for (auto& module : modules)
        {
            std::optional<bool> res{module.second->script_eval(input_data, flags, version)};
            if (!res.has_value()) continue;
            if (last_response.has_value()) assert(*res == *last_response);
            last_response = *res;
        }
    }

    void Driver::Run(const uint8_t *data, const size_t size, const std::string &target) const
    {
        if (target == "script") {
            std::span<const uint8_t> buffer{data, size};
            this->ScriptTarget(buffer);
        } else if (target == "block_deserialization") {
            std::span<const uint8_t> buffer{data, size};
            this->BlockDeserializationTarget(buffer);
        } else if (target == "script_eval") {
            std::span<const uint8_t> buffer{data, size};
            this->ScriptEvalTarget(buffer);
        } else {
            std::cout << "Target not defined!" << std::endl;
            assert(false);
        }
    };

}
