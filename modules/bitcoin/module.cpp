#include <span>

#include "module.h"
#include "script/script.h"
#include "primitives/block.h"
#include "primitives/transaction.h"
#include "consensus/validation.h"
#include "streams.h"
#include "validation.h"


namespace bitcoinfuzz {
namespace module {
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

std::optional<std::vector<bool>> Bitcoin::deserialize_block(std::span<const uint8_t> buffer) const
{
    DataStream ds{buffer};
    CBlock block;
    std::vector<bool> res{};
    try {
        ds >> TX_WITH_WITNESS(block);
    } catch (const std::ios_base::failure&) {
        return res;
    }
    if (block.vtx.empty()) {
        res.push_back(false);
    } else {
        res.push_back(!IsBlockMutated(block, true));
    }
    return res;
}

} // namespace module
} // namespace bitcoinfuzz
