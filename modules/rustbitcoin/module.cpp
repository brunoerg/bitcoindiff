#include <span>

#include "module.h"

extern "C" bool rust_bitcoin_script(const uint8_t *data, size_t len);

namespace bitcoinfuzz
{
    namespace module
    {
        Rustbitcoin::Rustbitcoin(void) : BaseModule("Rustbitcoin") {}

        std::optional<bool> Rustbitcoin::script_parse(std::span<const uint8_t> buffer) const
        {
            return rust_bitcoin_script(buffer.data(), buffer.size());
        }

    }
}
