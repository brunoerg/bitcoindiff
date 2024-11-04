#include <span>

#include "module.h"
#include "streams.h"
#include "script/script.h"


namespace bitcoinfuzz
{
    namespace module
    {
        Bitcoin::Bitcoin(void) : BaseModule("Bitcoin") {}

        std::optional<bool> Bitcoin::script_parse(std::span<const uint8_t> buffer) const
        {
            DataStream ds{buffer};
            CScript script;
            try {
                ds >> script;
            } catch (const std::ios_base::failure& e) {
                return false;
            }
            if (script.IsUnspendable()) return false;
            return true;
        }

    }
}
