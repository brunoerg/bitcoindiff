#include <cassert>
#include <set>
#include <algorithm>
#include <unistd.h>
#include <string>
#include <span>

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

    void Driver::Run(const uint8_t *data, const size_t size, const std::string &target) const
    {
        if (target == "script") {
            std::span<const uint8_t> buffer{data, size};
            this->ScriptTarget(buffer);
        } else {
            std::cout << "Target not defined!" << std::endl;
            assert(false);
        }
    };

}
