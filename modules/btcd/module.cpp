#include <span>

#include "module.h"
#include "btcd_wrapper/libscript.h"

namespace bitcoinfuzz
{
    namespace module
    {
        Btcd::Btcd(void) : BaseModule("Btcd") {}

        std::optional<bool> Btcd::script_eval(const std::vector<uint8_t> &input_data, unsigned int flags, size_t version) const
        {
            ByteArray script_data{
                .data = reinterpret_cast<char *>(const_cast<uint8_t *>(input_data.data())),
                .length = static_cast<int>(input_data.size())};

            return BTCDEvalScript(script_data, /*flags=*/0) == 1;
        }

    } // namespace module
} // namespace bitcoinfuzz
